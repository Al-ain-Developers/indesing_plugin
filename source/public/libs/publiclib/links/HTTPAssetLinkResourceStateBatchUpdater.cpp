
//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/links/HTTPAssetLinkResourceStateBatchUpdater.cpp $
//  
//  Owner: Arvinder Singh
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2015 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPublicHeaders.h"
#include "CPMUnknown.h"

#include "IHTTPLinkConnectionManager.h"
#include "IHTTPLinkResourceStateBatchUpdater.h"
#include "IHTTPLinkResourceServerAPIWrapper.h"
#include "IHTTPLinkManager.h"
#include "IHTTPServerInfo.h"
#include "IHTTPLinkUtils.h"

#include "DocHTTPBatchQueryManager.h"
#include "HTTPAssetLinkResourceStateUpdater.h"
#include "HTTPAssetLinkResourceStateBatchUpdater.h"

#include "dvaui/utility/OS_Time.h" 
#include "StringUtils.h"
#include "FileUtils.h"
#include "CAlert.h"
#include "StringUtils.h"
#include "URICommonUtils.h"

#include <set>

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
 */

// see  .../source/components/utilities/plugin/PublicImpl.cpp
//CREATE_PMINTERFACE(HTTPAssetLinkResourceStateBatchUpdater, kHTTPAssetLinkResourceStateBatchUpdaterImpl)

typedef std::vector<IHTTPLinkResourceServerAPIWrapper::RequestBatchAssetStatusCompletionFunction> RequestBatchAssetStatusCompletionFunctionVector;

HTTPAssetLinkResourceStateBatchUpdater::HTTPAssetLinkResourceStateBatchUpdater(IPMUnknown* boss)
: inherited(boss)
{
	const int32 kBatchSize = 10;
	const long kTimeLimit = 190000;
	const long kMinTimeBetweenCalls = 0;
	fIDBatchSize = fHTTPConfiguredBatchLimit = kBatchSize;
	fTimeLimitForBatchCall = kTimeLimit;
	fMinTimeBetweenCalls = kMinTimeBetweenCalls;

	RetrieveBatchLimitsConfigured();
	fIDBatchSize = (fHTTPConfiguredBatchLimit == 0 ? 1 : fHTTPConfiguredBatchLimit);
	fTimeLimitForBatchCall = (fTimeLimitForBatchCall == 0 ? 1 : fTimeLimitForBatchCall);
	PopulateBatchObjectTypeInfoMap();
}

HTTPAssetLinkResourceStateBatchUpdater::~HTTPAssetLinkResourceStateBatchUpdater()
{
}

ErrorCode HTTPAssetLinkResourceStateBatchUpdater::QueueLinkResourceUpdateRequestForBatch(const UID& resourceUID, const HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData& updateLinkResourceStateData)
{
	DocHTTPBatchQueryManager* instance = DocHTTPBatchQueryManager::Instance();
	IDataBase* db = instance->GetDatabase(updateLinkResourceStateData.fGuid);
	
	InterfacePtr<ILinkResource> iLinkResource(db, resourceUID, UseDefaultIID());
	if (!iLinkResource) return kFailure;

    // Get Batch object type for the given URI
	InterfacePtr<IHTTPLinkManager> httpLinkManager(GetExecutionContextSession(), UseDefaultIID());
	IHTTPLinkResourceServerAPIWrapper* serverAPIWrapper = httpLinkManager->GetHTTPLinkResourceServerAPIWrapper(fConnectionURI);
	HTTPLinkSubsystemTypes::BatchRequestObjectType objType;
	serverAPIWrapper->GetHTTPBatchRequestObjectType(iLinkResource->GetURI(), objType);
    
	instance->AddUIDForGuidAndConnectionURI(updateLinkResourceStateData.fGuid, fConnectionURI, resourceUID, objType);
	boost::system_time currentTime = boost::get_system_time();
	boost::posix_time::time_duration timeElapsedSinceLastBatchCall = currentTime - fBatchRequestObjectTypeInfo[objType];	

	long timeElapsedInMilliSec = timeElapsedSinceLastBatchCall.total_milliseconds();
	int32 numActiveDocUIDs = (int32)instance->GetNumberOfUIDsForGuidAndConnectionURI(updateLinkResourceStateData.fGuid, fConnectionURI, objType);

	//If the batch size exceeds or time since last batch call exceeds the time limit
	//do a batch call.

	if ((timeElapsedInMilliSec >= fTimeLimitForBatchCall || numActiveDocUIDs >= fIDBatchSize) && (timeElapsedInMilliSec >= fMinTimeBetweenCalls))
		InitiateBatchRequest(numActiveDocUIDs, objType, updateLinkResourceStateData);				

	return kSuccess;
}

bool HTTPAssetLinkResourceStateBatchUpdater::InitiateBatchRequest(const int32& numOfUIDs, const HTTPLinkSubsystemTypes::BatchRequestObjectType& objType, const HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData& updateLinkResourceStateData)
{
	size_t numberOfBatches;
	if (numOfUIDs % fIDBatchSize == 0)
		numberOfBatches = numOfUIDs / fIDBatchSize;
	else
		numberOfBatches = numOfUIDs / fIDBatchSize + 1;

	std::vector<IHTTPLinkResourceServerAPIWrapper::URIVector> batchRequestURIPathVectors(numberOfBatches);
	std::vector<std::vector<UID> >batchRequestUIDVectors(numberOfBatches);
	PopulateBatchRequestVectors(updateLinkResourceStateData.fGuid, objType, batchRequestURIPathVectors, batchRequestUIDVectors);

	InterfacePtr<IHTTPLinkManager> httpLinkManager(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IHTTPLinkResourceConnection> httpLinkResourceConnection(this, UseDefaultIID());

	IHTTPLinkResourceServerAPIWrapper* serverAPIWrapper = httpLinkManager->GetHTTPLinkResourceServerAPIWrapper(fConnectionURI);
	RequestBatchAssetStatusCompletionFunctionVector completionFunctionVector(batchRequestURIPathVectors.size());

	for (size_t i = 0; i < batchRequestURIPathVectors.size(); i++)
	{
		//TODO this assert is for debug purpose. Need to take this out.
		ASSERT_MSG((batchRequestURIPathVectors[i]).size() > 0, "Batch URI request containes no URI. Don't initiate a batch request when resource with given URI no longer exists.");
		if (batchRequestURIPathVectors[i].size() > 0)
		{
			completionFunctionVector[i] = boost::bind<void>(&HTTPAssetLinkResourceStateBatchUpdater::HandleFetchingBatchAssetMetadata,
				batchRequestUIDVectors[i], updateLinkResourceStateData, fConnectionURI, objType, _1);
			ASSERT_MSG((int32)((batchRequestURIPathVectors[i]).size()) <= fIDBatchSize, "Batch update request exceeds the batch limit");
			serverAPIWrapper->AsyncRequestBatchAssetStatusWithMetadata(httpLinkResourceConnection, batchRequestURIPathVectors[i], completionFunctionVector[i]);
			fBatchRequestObjectTypeInfo[objType] = boost::get_system_time();
		}
	}

	return true;

}

bool16 HTTPAssetLinkResourceStateBatchUpdater::PopulateBatchRequestVectors(const HTTPLinkSubsystemTypes::GUID& guid, HTTPLinkSubsystemTypes::BatchRequestObjectType objType, std::vector<IHTTPLinkResourceServerAPIWrapper::URIVector>&batchRequestURIPathVectors, std::vector<std::vector<UID> >&batchRequestUIDVectors)
{
	DocHTTPBatchQueryManager* instance = DocHTTPBatchQueryManager::Instance();
	InterfacePtr<IHTTPLinkResourceConnection> connection(this, UseDefaultIID());
	UIDSet uidSet;
	instance->GetUIDsForGuidAndConnectionURI(guid, fConnectionURI, uidSet, objType);
	IDataBase* db = instance->GetDatabase(guid);

	URI assetURI;
	int32 index = 0;

	for (UIDSet_iter it = uidSet.begin(); it != uidSet.end(); it++)
	{
		// If the resource gets deleted between the pool request and the actual batch call
		// resource UID would be invalid. Remove the uid from the map as well
		if (!db->IsValidUID(*it))
		{
			instance->RemoveUIDForGuidAndConnectionURI(guid, fConnectionURI, *it, objType);
			continue;
		}
		InterfacePtr<ILinkResource> iLinkResource(db, *it, UseDefaultIID());
		if (!iLinkResource) continue;
		assetURI = iLinkResource->GetURI();
		batchRequestURIPathVectors[index / fIDBatchSize].push_back(assetURI);
		batchRequestUIDVectors[index / fIDBatchSize].push_back(*it);
		index++;
	}

	return kTrue;
}
void HTTPAssetLinkResourceStateBatchUpdater::HandleFetchingBatchAssetMetadata(const std::vector<UID> &uidVector,
																			  HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData updateLinkResourceStateData,
																			  URI connectionURI,
																			  HTTPLinkSubsystemTypes::BatchRequestObjectType objType,
																			  IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtrVectorPtr assetStatusWithMetadataVectorPtr)
{
	ASSERT_MSG(IDThreading::IsMainThreadDomain(), "HTTPAssetLinkResourceStateBatchUpdater::HandleFetchingBatchAssetMetadata should be called on main thread only");
	if (!IDThreading::IsMainThreadDomain())
		return;

	InterfacePtr<IHTTPLinkConnectionManager> connectionMgr(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(connectionMgr);
	if (!connectionMgr)
		return;

	IHTTPLinkResourceConnection* connection = connectionMgr->GetHTTPConnection(connectionURI);
	ASSERT(connection);
	if (!connection || !connection->IsConnected())
		return;

	if (assetStatusWithMetadataVectorPtr == nil)
		return;

	ASSERT_MSG(uidVector.size() == assetStatusWithMetadataVectorPtr->size(), "No. of resources requested and returned in batch update request do not match.");
	if (uidVector.size() != assetStatusWithMetadataVectorPtr->size())
		return;

	DocHTTPBatchQueryManager* instance = DocHTTPBatchQueryManager::Instance();
	if (!instance) return;

	IDataBase* db = instance->GetDatabase(updateLinkResourceStateData.fGuid);

	if (!db || !Utils<IHTTPLinkUtils>()->IsValidDataBaseForHttpLink(db))
		return;

	std::string requestURIStr, responseURIStr;
	URI requestURI;
	WideString relativePath;
	PMString relativePathPMStr;
	for (size_t i = 0; i < uidVector.size(); i++)
	{
		if (!db->IsValidUID(uidVector[i])) continue;

		InterfacePtr<ILinkResource> iLinkResource(db, uidVector[i], UseDefaultIID());
		if (!iLinkResource) continue;

		ASSERT_MSG(((*assetStatusWithMetadataVectorPtr)[i]), "Something has gone wrong . Asset Pointer is not initialized.");
		if (!(*assetStatusWithMetadataVectorPtr)[i]) return;

		if (((*assetStatusWithMetadataVectorPtr)[i])->fAssetStatus == IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadata::kAvailable)
		{
			requestURI = iLinkResource->GetURI();
			GetHttpRequestPathForBatchRequest(requestURI, requestURIStr);

			ASSERT_MSG(((*assetStatusWithMetadataVectorPtr)[i])->fAssetMetadataPtr, "Something has gone wrong . Asset Metadata Pointer is not initialized.");
			if (!(((*assetStatusWithMetadataVectorPtr)[i])->fAssetMetadataPtr)) return;

			responseURIStr = ((*assetStatusWithMetadataVectorPtr)[i])->fAssetMetadataPtr->fPath;
			ASSERT_MSG(requestURIStr.compare(responseURIStr) == 0, FORMAT_ARGS("Requested asset %s does not match with %s asset returned.", requestURIStr.c_str(), responseURIStr.c_str()));
		}
		
	}

	for (size_t index = 0; index < uidVector.size(); index++)
	{
		HTTPAssetLinkResourceStateUpdater::HandleFetchingAssetMetadata(uidVector[index], updateLinkResourceStateData, (*assetStatusWithMetadataVectorPtr)[index]);
		instance->RemoveUIDForGuidAndConnectionURI(updateLinkResourceStateData.fGuid, connectionURI, uidVector[index], objType);
	}
}

void HTTPAssetLinkResourceStateBatchUpdater::GetHttpRequestPathForBatchRequest(const URI& uri, std::string& requestPath, bool encodedPathRequested)
{
	requestPath.clear();
	if (encodedPathRequested)
	{
		static const char* kOverrideChars[] = { "+",    // scheme characters to not encode 
			NULL,    // authority characters to not encode 
			"/\\:",    // path characters to not encode 
			"/?",    // query characters to not encode 
			"/?" };    // fragment characters to not encode 

		static const int kOverrideCharsSize = (sizeof kOverrideChars) / (sizeof kOverrideChars[0]);
		URICommonUtils::WideStringToURIEncoding(uri.GetComponent(URI::kPath), (URI::kPath < kOverrideCharsSize) ? kOverrideChars[URI::kPath] : NULL, requestPath);
	}
	else
		StringUtils::ConvertWideStringToUTF8(uri.GetComponent(URI::kPath), requestPath);
}

bool HTTPAssetLinkResourceStateBatchUpdater::RetrieveBatchLimitsConfigured(void)
{
	InterfacePtr<IHTTPLinkManager> httpLinkManager(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(httpLinkManager);

	InterfacePtr<IHTTPLinkResourceConnection> connection(this, UseDefaultIID());
	ASSERT(connection);
	if (!connection) return false;

	InterfacePtr<IHTTPServerInfo> httpServerInfo(connection, UseDefaultIID());
	fConnectionURI = httpServerInfo->GetServerURI();
	IHTTPLinkResourceServerAPIWrapper* serverAPIWrapper = httpLinkManager->GetHTTPLinkResourceServerAPIWrapper(fConnectionURI);
	serverAPIWrapper->GetConfiguredBatchLimits(connection, fHTTPConfiguredBatchLimit, fTimeLimitForBatchCall, fMinTimeBetweenCalls);
	return true;
}

void HTTPAssetLinkResourceStateBatchUpdater::PopulateBatchObjectTypeInfoMap(void)
{
	fBatchRequestObjectTypeInfo.insert(std::make_pair(HTTPLinkSubsystemTypes::kAsset, boost::get_system_time()));
	fBatchRequestObjectTypeInfo.insert(std::make_pair(HTTPLinkSubsystemTypes::kAssetMetadata, boost::get_system_time()));
}
