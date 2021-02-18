//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/links/HTTPAssetLinkResourceStateUpdater.cpp $
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

//#include "VCPlugInHeaders.h"
#include "VCPublicHeaders.h"
#include "HTTPAssetLinkResourceStateUpdater.h"

#include "IHTTPLinkConnectionManager.h"
#include "IHTTPLinkManager.h"
#include "IHTTPLinkResourceServerCache.h"
#include "IHTTPLinkUtils.h"
#include "ILinkResourceStateUpdateCmdData.h"

#include "DBUtils.h"
#include "DocHTTPBatchQueryManager.h"
#include "FileUtils.h"
#include "IDTime.h"
#include "URI.h"
#include "Utils.h"
#include "IJsonUtils.h"


#if PRERELEASE
#include <fstream>
#endif

static const char* kID			= "id";
static const char* kVersion		= "version"; 

// see  .../source/components/utilities/plugin/PublicImpl.cpp
//CREATE_PMINTERFACE(HTTPAssetLinkResourceStateUpdater, kHTTPAssetLinkResourceStateUpdaterImpl)

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
 */

HTTPAssetLinkResourceStateUpdater::HTTPAssetLinkResourceStateUpdater(IPMUnknown* boss)
: inherited(boss)
{
}

ErrorCode HTTPAssetLinkResourceStateUpdater::UpdateResourceStateSync( const UIDRef& resourceRef, bool bNotify )
{
	return UpdateLinkResourceState( resourceRef, bNotify, false );
}

ErrorCode HTTPAssetLinkResourceStateUpdater::UpdateResourceStateAsync( const UIDRef& resourceRef )
{
	return UpdateLinkResourceState( resourceRef, true, true );
}

ErrorCode HTTPAssetLinkResourceStateUpdater::ResolveResource( const UIDRef& resourceRef, const URI& relativeURI, bool bIgnoreStamp )
{
	// No-op for now
	return kSuccess;
}

ErrorCode HTTPAssetLinkResourceStateUpdater::UpdateLinkResourceState( const UIDRef& resourceRef, bool bNotify, bool async )
{
	InterfacePtr<IHTTPLinkManager> httpLinkManager(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(httpLinkManager);
	if (!httpLinkManager)
		return kFailure;

	InterfacePtr<ILinkResource> iLinkResource(resourceRef, UseDefaultIID());
	URI uri = iLinkResource->GetURI();
	HTTPLinkSubsystemTypes::GUID guid;
    
	InterfacePtr<IHTTPLinkResourceConnection> httpLinkResourceConnection = Utils<IHTTPLinkUtils>()->GetHTTPLinkResourceConnection(uri);

	if (!httpLinkResourceConnection || !httpLinkResourceConnection->IsConnected())
	{
		if (iLinkResource->GetState() == ILinkResource::kInaccessible)
			return kSuccess;		
		InterfacePtr<ICommand> updateCmd(CmdUtils::CreateCommand(kLinkResourceStateUpdateCmdBoss));
		InterfacePtr<ILinkResourceStateUpdateCmdData> updateCmdData(updateCmd, UseDefaultIID());
		updateCmdData->SetState(ILinkResource::kInaccessible);
		updateCmdData->SetResource(resourceRef.GetUID());
		updateCmdData->SetDatabase(resourceRef.GetDataBase());
		updateCmdData->SetUpdateAction(ILinkResourceStateUpdateCmdData::kUpdateState);
		updateCmdData->SetNotify(bNotify);
        updateCmdData->SetDatabaseModified(kTrue);
		ErrorCode errorCode(kSuccess);
		if (async)
			errorCode = CmdUtils::ScheduleCommand(updateCmd, ICommand::kMediumPriority);
		else
			errorCode = CmdUtils::ProcessCommand(updateCmd);
		return errorCode;
	}

    DocHTTPBatchQueryManager* instance = DocHTTPBatchQueryManager::Instance();
    IDataBase* db = GetDataBase(iLinkResource);
    if (instance)
        guid = instance->GenerateGuidAndCreateMapping(db);
    
	HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData updateLinkResourceStateData;
	updateLinkResourceStateData.fNotify = bNotify;
	updateLinkResourceStateData.fAsync = async;
	updateLinkResourceStateData.fGuid = guid;
	

	IHTTPLinkResourceServerAPIWrapper* serverAPIWrapper = httpLinkManager->GetHTTPLinkResourceServerAPIWrapper(uri);
	ErrorCode status = kSuccess;
	UID resourceUID = resourceRef.GetUID();
    
	if (async)
	{
		if (serverAPIWrapper->IsBatchUpdateSupported(uri) == kTrue)
		{
			InterfacePtr<IHTTPLinkConnectionManager> httpConnectionManager(GetExecutionContextSession(), UseDefaultIID());
			IHTTPLinkResourceStateBatchUpdater* httpBatchUpdater = httpConnectionManager->GetHTTPResourceStateBatchUpdater(httpLinkResourceConnection);
			return httpBatchUpdater->QueueLinkResourceUpdateRequestForBatch(resourceUID, updateLinkResourceStateData);
		}
		else
		{
			IHTTPLinkResourceServerAPIWrapper::RequestAssetStatusCompletionFunction completionFunction = boost::bind<void>(&HTTPAssetLinkResourceStateUpdater::HandleFetchingAssetMetadata, resourceRef.GetUID(), updateLinkResourceStateData, _1);
			bool16 requestStatus = serverAPIWrapper->AsyncRequestAssetStatusWithMetadata(httpLinkResourceConnection, uri, completionFunction);
			status = requestStatus ? kSuccess : kFailure;
		}

	}
	else
	{
		IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr outData = serverAPIWrapper->RequestAssetStatusWithMetadata(httpLinkResourceConnection, uri);
		if (outData != nil)
		{
			status = kSuccess;
			HandleFetchingAssetMetadata(resourceUID, updateLinkResourceStateData, outData);
		}
		else
		{
			status = kFailure;
		}
	}

	return status;
}


WideString HTTPAssetLinkResourceStateUpdater::CreateResourceStamp(const URI& uri, const IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr& assetMetaData)
{
    /*
     Stamp is defined as following json -
     id: idValue from assetmetadata
     version: version value from assetmetadata
     */
    JSON jsonData;
    jsonData.addValue(kID, assetMetaData->fAssetMetadataPtr->fUniqueID);
    jsonData.addValue(kVersion, assetMetaData->fAssetMetadataPtr->fVersionData);
    
    std::string jsonString;
    jsonData.write_json(jsonString);
    return WideString(jsonString.c_str());
}

void HTTPAssetLinkResourceStateUpdater::CheckAndInvalidateCache(InterfacePtr<ILinkResource> iLinkResource, IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr assetStatusWithMetadataPtr, bool renditionUri)
{
    URI uri;
    bool16 isValidUri = false;
    
    if (renditionUri)
        isValidUri = Utils<IHTTPLinkUtils>()->GetRenditionURIForResource(iLinkResource, uri);
    else
        isValidUri = Utils<IHTTPLinkUtils>()->GetOriginalURIForResource(iLinkResource, uri);
    
    if (isValidUri)
    {
        InvalidateCacheIfStale(uri ,assetStatusWithMetadataPtr->fAssetMetadataPtr);
    }
}

void HTTPAssetLinkResourceStateUpdater::InvalidateCacheIfStale(URI uri, IHTTPLinkResourceServerAPIWrapper::AssetMetadataPtr assetMetadata)
{
    InterfacePtr<IHTTPLinkResourceServerCache> resourceCache = Utils<IHTTPLinkUtils>()->GetHTTPLinkResourceServerCache(uri);
    
    std::shared_ptr<IHTTPLinkCachedAssetEntry> entry = resourceCache->GetCachedAssetEntry(uri, /*shouldDownload*/kFalse);
    
    if (entry != nullptr)
    {
        // if entry in cache is old, invalidate it so that it can be removed
        bool isStale = entry->IsStale(assetMetadata);
        
        if (isStale)
            resourceCache->InvalidateCacheForURI(uri);
    }
}

void HTTPAssetLinkResourceStateUpdater::HandleFetchingAssetMetadata(UID	resourceUID, HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData updateLinkResourceStateData,  IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr assetStatusWithMetadataPtr)
{
	DocHTTPBatchQueryManager* instance = DocHTTPBatchQueryManager::Instance();
    
	//Unable to instantiate singleton class, there is some problem, return from here.
	if (!instance) 
		return;

	if (updateLinkResourceStateData.fGuid.empty())
		return;

	if(instance->GetDatabase(updateLinkResourceStateData.fGuid) == nil)
		return;

	IDataBase* db = instance->GetDatabase(updateLinkResourceStateData.fGuid);
	if (!db->IsValidUID(resourceUID))
		return;

	InterfacePtr<ILinkResource> iLinkResource(db, resourceUID, UseDefaultIID());
	if (!iLinkResource)
		return;

	URI uri = iLinkResource->GetURI();
	ASSERT_MSG(IDThreading::IsMainThreadDomain(), "HTTPAssetLinkResourceStateUpdater::HandleFetchingAssetMetadata should be called on main thread only");
	if (!IDThreading::IsMainThreadDomain())
		return;
	
	if (assetStatusWithMetadataPtr == nil)
		return;

	ILinkResource::ResourceState state = ILinkResource::kUnknown;
	ILinkResourceStateUpdateCmdData::UpdateAction updateAction = ILinkResourceStateUpdateCmdData::kUpdateState;
	ILinkResource::ResourceStamp existingStamp = iLinkResource->GetStamp();
	ILinkResource::ResourceStamp newStamp = existingStamp;
	uint64 existingSize = iLinkResource->GetSize();
	uint64 assetSize = existingSize;
	IDTime assetModifiedTime = iLinkResource->GetModTime();
    
	size_t shouldUseUpdateStateAction = 0;
    bool16 missingORInaccessible = kFalse;

	if (assetStatusWithMetadataPtr->fAssetStatus == IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadata::kUnknown)
	{
        ASSERT_FAIL(FORMAT_ARGS("HTTPAssetLinkResourceStateUpdater::HandleFetchingAssetMetadata failed to get valid asset status for uri: %s", uri.GetURI().c_str()));
		return;
	}

	if (assetStatusWithMetadataPtr->fAssetStatus == IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadata::kInaccessible)
    {
        state = ILinkResource::kInaccessible;
        missingORInaccessible = kTrue;
    }

	if (!missingORInaccessible && 
		assetStatusWithMetadataPtr->fAssetStatus == IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadata::kMissing)
    {
		state = ILinkResource::kMissing;
        missingORInaccessible = kTrue;
    }
    
	if(!missingORInaccessible )
	{
		InterfacePtr<IHTTPLinkManager> httpLinkManager(GetExecutionContextSession(), UseDefaultIID());

		if (assetSize != assetStatusWithMetadataPtr->fAssetMetadataPtr->fSize)
		{
			assetSize = assetStatusWithMetadataPtr->fAssetMetadataPtr->fSize;
			updateAction = ILinkResourceStateUpdateCmdData::kUpdateSize;
			++shouldUseUpdateStateAction;
		}


		if (assetModifiedTime != assetStatusWithMetadataPtr->fAssetMetadataPtr->fModifiedDate)
		{
			assetModifiedTime = assetStatusWithMetadataPtr->fAssetMetadataPtr->fModifiedDate;
			updateAction = ILinkResourceStateUpdateCmdData::kUpdateModTime;
			++shouldUseUpdateStateAction;
		}

#if 0
		if (uri != assetStatusWithMetadataPtr->fAssetMetadata.fURI)
		{
			uri = assetStatusWithMetadataPtr->fAssetMetadata.fURI;
			updateAction = ILinkResourceStateUpdateCmdData::kUpdateURI;
			++shouldUseUpdateStateAction;
		}

#endif

		newStamp = CreateResourceStamp(uri, assetStatusWithMetadataPtr);
        
		if (existingStamp != newStamp)
		{
			++shouldUseUpdateStateAction;
			updateAction = ILinkResourceStateUpdateCmdData::kUpdateStamp;
		}
        
        state = ILinkResource::kAvailable;
        
        // Making updater agnostic of cache
        // Only the resource handler will interact with cache, and if really needs it, then it will block and download the actual asset/fpo
        
        // If the update state action should change, that means some metadata has changed from last placement of asset from cache
        // Its time to invalidate the cache and update the state accordingly.
        InterfacePtr<IHTTPLinkResourceServerCache> resourceCache = Utils<IHTTPLinkUtils>()->GetHTTPLinkResourceServerCache(uri);
        if (resourceCache)
        {
            if (shouldUseUpdateStateAction > 0)
            {
                CheckAndInvalidateCache(iLinkResource, assetStatusWithMetadataPtr);
                CheckAndInvalidateCache(iLinkResource, assetStatusWithMetadataPtr, false);
            }
        }
    }

	if (state != iLinkResource->GetState() || shouldUseUpdateStateAction > 1)
	{
		updateAction = ILinkResourceStateUpdateCmdData::kUpdateState;
		++shouldUseUpdateStateAction;
	}

	if (shouldUseUpdateStateAction == 0)
		return;

	InterfacePtr<ICommand> updateCmd(CmdUtils::CreateCommand(kLinkResourceStateUpdateCmdBoss));
	InterfacePtr<ILinkResourceStateUpdateCmdData> updateCmdData(updateCmd, UseDefaultIID());

	switch (updateAction)
	{
		case ILinkResourceStateUpdateCmdData::kUpdateURI:
		{
			updateCmdData->SetURI(uri);
			break;
		}

		case ILinkResourceStateUpdateCmdData::kUpdateState:
		{
			updateCmdData->SetStamp(newStamp);
			updateCmdData->SetSize(assetSize);
			updateCmdData->SetModTime(assetModifiedTime);
			updateCmdData->SetState(state);
            updateCmdData->SetDatabaseModified(kTrue);
			break;
		}
		case ILinkResourceStateUpdateCmdData::kUpdateStamp:
		{
			updateCmdData->SetStamp(newStamp);
			break;
		}
		case ILinkResourceStateUpdateCmdData::kUpdateModTime:
		{
			updateCmdData->SetModTime(assetModifiedTime);
			break;
		}
		case ILinkResourceStateUpdateCmdData::kUpdateSize:
		{
			updateCmdData->SetSize(assetSize);
			break;
		}
	}

	updateCmdData->SetUpdateAction(updateAction);
	updateCmdData->SetResource(resourceUID);
	updateCmdData->SetDatabase(db);
	updateCmdData->SetNotify(updateLinkResourceStateData.fNotify);
	
	ErrorCode errorCode(kSuccess);
	if (updateLinkResourceStateData.fAsync)
		errorCode = CmdUtils::ScheduleCommand(updateCmd, ICommand::kMediumPriority);
	else
		errorCode = CmdUtils::ProcessCommand(updateCmd);

	ASSERT(errorCode == kSuccess);
}

