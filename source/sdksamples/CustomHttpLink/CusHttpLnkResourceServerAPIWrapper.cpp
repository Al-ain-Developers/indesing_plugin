//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLink/CusHttpLnkResourceServerAPIWrapper.cpp $
//  
//  Owner: Adobe Developer Technologies
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
//  Copyright 2019 Adobe
//  All Rights Reserved.
//
//  NOTICE: Adobe permits you to use, modify, and distribute this file in
//  accordance with the terms of the Adobe license agreement accompanying
//  it. If you have received this file from a source other than Adobe,
//  then your use, modification, or distribution of it requires the prior
//  written permission of Adobe. 
//
//========================================================================================

#include "VCPlugInHeaders.h"

//Definitions
#include "CustomHttpLinkID.h"

// Interfaces
#include "CPMUnknown.h"
#include "IHTTPLinkResourceServerAPIWrapper.h"
#include "IHTTPServerInfo.h"
#include "IHTTPLinkUtils.h"
#include "IHTTPLinkConnectionManager.h"

//Boost
#include <boost/bind.hpp> 
#include "boost/config.hpp" 
#include "boost/shared_ptr.hpp" 
#include "boost/function.hpp" 

// Utils
#include "IDHTTPWrapper.h"
#include "IJsonUtils.h"
#include "StringUtils.h"

struct IsServerAccessibleData
{
	bool16	fIsServerAccessible;
};
typedef boost::shared_ptr<IsServerAccessibleData> IsServerAccessibleDataPtr;

const char* kGetBatchAssetMetaDataStatus = "batchassetstatus.json"; // for asset status & batch limit
const int   kTimeoutRequest_InMS = 50 * 1000; // Time out for asset status request

//Necessary String initialization to parse response 
const static char* kQueryParameterChar  = "?";
const static char* kEqualToChar         = "=";
const static char* kAmpersandChar       = "&";

const static char* kFileSize    = "size";
const static char* kUniqueID    = "sha";
const static char* kPath        = "path";
const static char* kItems       = "items";

//Header keys
static const HTTPLinkSubsystemTypes::HeaderKey  kHEADER_AUTHORIZATION(L"authorization");

//
// CusHttpLnkResourceServerAPIWrapper
//
class CusHttpLnkResourceServerAPIWrapper : public CPMUnknown<IHTTPLinkResourceServerAPIWrapper>
{

public:
	typedef CPMUnknown<IHTTPLinkResourceServerAPIWrapper> inherited;

	CusHttpLnkResourceServerAPIWrapper(IPMUnknown* boss);

	~CusHttpLnkResourceServerAPIWrapper();

	/**
	 * Request the status of the Metadata asset specified by the assetURI on connection. e.g missing, modified etc 
	 */
	virtual AssetStatusWithMetadataPtr RequestAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection, const URI& assetURI);
	virtual bool16 AsyncRequestAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection,
														const URI& assetURI,
														RequestAssetStatusCompletionFunction completionFunction);
	virtual bool16 AsyncRequestBatchAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection,
		const URIVector &assetURIVector,
		RequestBatchAssetStatusCompletionFunction completionFunction);

	/**
	 * Generates the session token for the given connection 
	 */
    virtual bool16 GenerateSessionToken(IHTTPLinkResourceConnection* connection, std::string& token);

	/**
	 * Set the configured batch limit for batch request
     * Set the timeinMs to the configured maximum time limit for batch request
	 * Set minium time between two batch calls
	 */
	virtual bool16 GetConfiguredBatchLimits(IHTTPLinkResourceConnection* connection, int32& batchLimit, long& maxTimeinMs, long& minTimeinMs)
    {
        return kFalse;
    }

	/**
	**
	*/
	virtual bool16 IsServerAccessible(IHTTPLinkResourceConnection* connection, bool16& serverAccessible);
	
	/**
	**
	*/
	virtual bool16 FetchAssetPathAndRequestHeadersForDownload(IHTTPLinkResourceConnection* connection, const URI& inURI, URI& assetURL, HTTPLinkSubsystemTypes::Headers& headers) const;

	/*
	 *
	 */
	virtual bool16 IsBatchUpdateSupported(const URI& uri) const
	{
		return kTrue;
	}


    URI GetAssetURI(const URI& inURI, ILinkResourceRenditionData::ResourceRenditionType type) const
    {
        ILinkResourceRenditionData::ResourceRenditionType renditionTypeOfInURI = GetURIRenditionType(inURI);
        
        // If the curent rendition type is same as parameter, return URI
        if (type == renditionTypeOfInURI)
            return inURI;
        
        /**
         * For a given sample asset:
         * Original URI format : http://localhost:3000/image/abc.jpeg
         * FPO URI format : http://localhost:3000/image/abc.jpeg/fpo
         */
        if (type == ILinkResourceRenditionData::kOriginal)
        {
            URI originalURI(inURI);
            WideString pathComponent = originalURI.GetComponent(URI::kPath);
            // Remove FPI from path to convert it to original URI
            int index = pathComponent.IndexOf(WideString("/fpo"));
            if (index >= 0)
            {
                pathComponent.replace(pathComponent.end() - 4 , pathComponent.end(), WideString(""));
                originalURI.SetComponent(URI::kPath, pathComponent);
            }
            return originalURI;
        }
        else
        {
            URI renditionURI(inURI);
            // Append fpo to path to convert it to rendition URI
            WideString pathComponenet = inURI.GetComponent(URI::kPath);
            pathComponenet.Append(WideString("/fpo"));
            renditionURI.SetComponent(URI::kPath, pathComponenet);
            return renditionURI;
        }
    }

	/**
	 * GetURIRenditionType
	 */
	virtual ILinkResourceRenditionData::ResourceRenditionType GetURIRenditionType(const URI& inURI) const
	{
        WideString pathComponent = inURI.GetComponent(URI::kPath);
        if (pathComponent.Contains(WideString("/fpo")))
        {
            return ILinkResourceRenditionData::kFPO;
        }
		return ILinkResourceRenditionData::kOriginal;
	}
    
    
    /**
     * For internal use only
     */
    virtual AssetMetadataContentPtr RequestAssetTextFragmentContent(IHTTPLinkResourceConnection* connection, const URI& inURI, ErrorCode err = kCantPlaceMetadataError)
    {
        return nil;
    }
    
    /**
     * This API is for internal use only
     * Set the objType to kAsset
     */
    bool16 GetHTTPBatchRequestObjectType(const URI& uri, HTTPLinkSubsystemTypes::BatchRequestObjectType& objType) const
    {
        objType = HTTPLinkSubsystemTypes::kAsset;
        return kTrue;
    }
    
    /**
     * For internal use only
     */
    virtual bool16 AdjustURI(const URI& inUri, URI &outUri)
    {
        return kFalse;
    }


private:

	virtual bool16 CommonRequestBatchAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection,
																const URIVector &assetURIVector,
																const bool isAsyncRequest,
																const int timeoutInMS = 2000, //0 means non-blocking,
																RequestBatchAssetStatusCompletionFunction completionFunction = NULL);
    
	virtual IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtrVectorPtr RequestBatchAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection,
		const URIVector &assetURIVector);
    
    // Headers related functions
    bool16 GetHeadersCommon(HTTPLinkSubsystemTypes::Headers& headers, IHTTPLinkResourceConnection* connection) const;

	// Request Asset Status related calls
	static void RequestAssetStatusWithMetadataCallbackOnMainThread(RequestAssetStatusCompletionFunction completionFunction,
																		AssetStatusWithMetadataPtrVectorPtr assetStatusWithMetadataPtrVectorPtr);
    static void RequestBatchAssetStatusWithMetadataCallbackOnMainThread(RequestBatchAssetStatusCompletionFunction completionFunction,IDHTTPWrapper::RequestID inRequestID,
                                                                        AssetStatusWithMetadataPtrVectorPtr assetStatusWithMetadataPtrVectorPtr);


	// Batch status related calls
	bool16 GetBatchRequestUrl(IHTTPLinkResourceConnection* connection, IDHTTPWrapper::URL& serverurl, const URIVector &assetURIVector);
	static void RequestBatchAssetStatusWithMetadataCallbackOnWorkerThread(const bool isAsyncRequest,
																		  RequestBatchAssetStatusCompletionFunction completionFunction,
																		  const URIVector &assetURIVector,
																		  IDHTTPWrapper::RequestID inRequestID,
																		  IDHTTPWrapper::Response inResponse);

	static bool16 GetBatchAssetMetaDataFromResponse(const IDHTTPWrapper::Response& responsePtr, const URIVector &assetURIVector, AssetStatusWithMetadataPtrVector &assetStatusWithMetadataPtrVector);

	// Server Accessible related calls
	static void IsServerAccessibleCallbackOnWorkerThread(IDHTTPWrapper::RequestID inRequestID, IDHTTPWrapper::Response inResponse);

	// Sync requests data
	static IsServerAccessibleDataPtr			ts_Sync_IsServerAccessiblePtr;
	static AssetStatusWithMetadataPtrVectorPtr	ts_Sync_AssetStatusWithMetadataPtrVectorPtr;

};

CREATE_PMINTERFACE(CusHttpLnkResourceServerAPIWrapper, kCusHttpLnkResourceServerAPIWrapperImpl)

IsServerAccessibleDataPtr												CusHttpLnkResourceServerAPIWrapper::ts_Sync_IsServerAccessiblePtr = nil;
IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtrVectorPtr	CusHttpLnkResourceServerAPIWrapper::ts_Sync_AssetStatusWithMetadataPtrVectorPtr = nil;

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::Constructor
//========================================================================================
CusHttpLnkResourceServerAPIWrapper::CusHttpLnkResourceServerAPIWrapper(IPMUnknown* boss)
: inherited(boss)
{
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::Destructor
//========================================================================================
CusHttpLnkResourceServerAPIWrapper::~CusHttpLnkResourceServerAPIWrapper()
{
	ts_Sync_AssetStatusWithMetadataPtrVectorPtr = nil;
	ts_Sync_IsServerAccessiblePtr				= nil;
}

//
// RequestAssetStatusWithMetadata
//
#pragma mark - RequestAssetStatusWithMetaData

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::RequestAssetStatusWithMetadata
//========================================================================================
IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr CusHttpLnkResourceServerAPIWrapper::RequestAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection, const URI& assetURI)
{
	IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr assetStatusWithMetadataPtr = nil;
	URIVector uriVector;
	uriVector.push_back(assetURI);

	IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtrVectorPtr assetStatusWithMetadataPtrVectorPtr = RequestBatchAssetStatusWithMetadata(connection, uriVector);
	if (assetStatusWithMetadataPtrVectorPtr == nil || 
		assetStatusWithMetadataPtrVectorPtr->size() != 1)
	{
		return nil;
	}
	assetStatusWithMetadataPtr = assetStatusWithMetadataPtrVectorPtr->at(0);
	return assetStatusWithMetadataPtr;
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::AsyncRequestAssetStatusWithMetadata
//========================================================================================
bool16 CusHttpLnkResourceServerAPIWrapper::AsyncRequestAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection,
																			const URI& assetURI,
																			RequestAssetStatusCompletionFunction completionFunction)
{
	URIVector uriVector;
	uriVector.push_back(assetURI);
	RequestBatchAssetStatusCompletionFunction batchStatusCompletionFunction = boost::bind<void>(&CusHttpLnkResourceServerAPIWrapper::RequestAssetStatusWithMetadataCallbackOnMainThread,
		completionFunction,
		_1);
	return AsyncRequestBatchAssetStatusWithMetadata(connection, uriVector, batchStatusCompletionFunction);
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::RequestAssetStatusWithMetadataCallbackOnMainThread
//========================================================================================
void CusHttpLnkResourceServerAPIWrapper::RequestAssetStatusWithMetadataCallbackOnMainThread(RequestAssetStatusCompletionFunction completionFunction,
																							AssetStatusWithMetadataPtrVectorPtr assetStatusWithMetadataPtrVectorPtr)
{
	if (assetStatusWithMetadataPtrVectorPtr != nil && assetStatusWithMetadataPtrVectorPtr->size() != 1)
		return;

	if (completionFunction)
	{
		completionFunction((*assetStatusWithMetadataPtrVectorPtr)[0]);
	}
}


#pragma mark - RequestBatchAssetStatusWithMetadata
//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::RequestBatchAssetStatusWithMetadata
//========================================================================================
IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtrVectorPtr CusHttpLnkResourceServerAPIWrapper::RequestBatchAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection,
																			const URIVector &assetURIVector)
{
	AssetStatusWithMetadataPtrVectorPtr assetStatusWithMetadataPtrVectorPtr = nil;
	if (!CommonRequestBatchAssetStatusWithMetadata(connection, assetURIVector, kFalse /*isAsyncRequest*/, kTimeoutRequest_InMS))
	{
		return assetStatusWithMetadataPtrVectorPtr;
	}

	assetStatusWithMetadataPtrVectorPtr = ts_Sync_AssetStatusWithMetadataPtrVectorPtr;
	ts_Sync_AssetStatusWithMetadataPtrVectorPtr = nil;

	return assetStatusWithMetadataPtrVectorPtr;
}


//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::AsyncRequestBatchAssetStatusWithMetadata
//========================================================================================
bool16 CusHttpLnkResourceServerAPIWrapper::AsyncRequestBatchAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection,
	const URIVector &assetURIVector,
	RequestBatchAssetStatusCompletionFunction completionFunction)
{
	return CommonRequestBatchAssetStatusWithMetadata(connection, assetURIVector, kTrue /*isAsyncRequest*/, 0, completionFunction);
}


//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::CommonRequestBatchAssetStatusWithMetadata
//========================================================================================
bool16 CusHttpLnkResourceServerAPIWrapper::CommonRequestBatchAssetStatusWithMetadata(IHTTPLinkResourceConnection* connection,
																					const URIVector &assetURIVector,
																					const bool isAsyncRequest,
																					const int timeoutInMS,
                                                                                RequestBatchAssetStatusCompletionFunction completionFunction)
{
	HTTPLinkSubsystemTypes::Headers headers;
    if (!GetHeadersCommon(headers, connection))
        return kFalse;
    
	IDHTTPWrapper::URL requestURL;

	if (!GetBatchRequestUrl(connection, requestURL, assetURIVector))
		return kFalse;

	IDHTTPWrapper::CompletionFunction requestCompletionFunction = boost::bind<void>(&CusHttpLnkResourceServerAPIWrapper::RequestBatchAssetStatusWithMetadataCallbackOnWorkerThread,
		isAsyncRequest, /*isAsyncRequest*/
		completionFunction,
		assetURIVector,
		_1,
		_2);

	IDHTTPWrapper::Payload payload;
	IDHTTPWrapper::HTTP http;
	if (!http.POST(requestCompletionFunction, requestURL, payload, timeoutInMS, headers))
	{
		return kFalse;
	}
	return kTrue;
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::GetBatchRequestUrl
//========================================================================================
bool16 CusHttpLnkResourceServerAPIWrapper::GetBatchRequestUrl(IHTTPLinkResourceConnection* connection, IDHTTPWrapper::URL& requestUrl, const URIVector &assetURIVector)
{
    URI serverURI(kCusHttpLnkServerURL);
    std::string serverURIStr = serverURI.GetURI();
    serverURIStr.append(kGetBatchAssetMetaDataStatus);
    
    int listSize = (int)assetURIVector.size();
    int currentElementIndex = 1; // To mark the last element
    serverURIStr.append(kQueryParameterChar);
    for (auto it = assetURIVector.begin(); it != assetURIVector.end(); it++)
    {
        serverURIStr.append(kPath);
        serverURIStr.append(kEqualToChar);
        URI pathString((*it).GetComponent(URI::kPath));
        serverURIStr.append(pathString.GetURI());
        if (currentElementIndex != listSize) // Do not add kAmpersandChar if is the last element of the list
            serverURIStr.append(kAmpersandChar);
        currentElementIndex++;
    }
    
    StringUtils::ConvertUTF8ToWideString(serverURIStr, requestUrl);
	return kTrue;
}


//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::RequestBatchAssetStatusWithMetadataCallbackOnWorkerThread
//========================================================================================
void CusHttpLnkResourceServerAPIWrapper::RequestBatchAssetStatusWithMetadataCallbackOnWorkerThread(const bool isAsyncRequest,
																								RequestBatchAssetStatusCompletionFunction completionFunction,
																								const URIVector &assetURIVector,
																								IDHTTPWrapper::RequestID inRequestID,
																								IDHTTPWrapper::Response inResponse)
{
	// Parse the response and form the AssetStatusWithMetadata vector
	AssetStatusWithMetadataPtrVectorPtr assetStatusWithMetadataPtrVectorPtr(new AssetStatusWithMetadataPtrVector(assetURIVector.size()));
	bool16 responseParsingStatus = GetBatchAssetMetaDataFromResponse(inResponse, assetURIVector, *assetStatusWithMetadataPtrVectorPtr);

	if (responseParsingStatus == kFalse)
	{
		ASSERT_FAIL(FORMAT_ARGS("%s:%s:%d, failed to get interpreted batch asset meta data with status code:%d", __FILE__, __FUNCTION__, __LINE__, inResponse.GetStatus()));
		assetStatusWithMetadataPtrVectorPtr.reset();
	}

	if (isAsyncRequest)
	{
		IDHTTPWrapper::HTTP http;
		http.AsyncCallFromMainThread(boost::bind(&CusHttpLnkResourceServerAPIWrapper::RequestBatchAssetStatusWithMetadataCallbackOnMainThread,
			completionFunction,
			inRequestID,
			assetStatusWithMetadataPtrVectorPtr));
	}
	else
	{
		ts_Sync_AssetStatusWithMetadataPtrVectorPtr = assetStatusWithMetadataPtrVectorPtr;
	}
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::RequestBatchAssetStatusWithMetadataCallbackOnMainThread
//========================================================================================
void CusHttpLnkResourceServerAPIWrapper::RequestBatchAssetStatusWithMetadataCallbackOnMainThread(RequestBatchAssetStatusCompletionFunction completionFunction,
																							  IDHTTPWrapper::RequestID inRequestID,
																							  AssetStatusWithMetadataPtrVectorPtr assetStatusWithMetadataPtrVectorPtr)
{
	if (completionFunction)
	{
		completionFunction(assetStatusWithMetadataPtrVectorPtr);
	}

	inRequestID.DeleteRequest();
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::GetHeadersCommon
//========================================================================================
bool16 CusHttpLnkResourceServerAPIWrapper::GetHeadersCommon(HTTPLinkSubsystemTypes::Headers& headers, IHTTPLinkResourceConnection* connection) const
{
    if (!connection || !connection->IsConnected())
        return kFalse;
    
    std::stringstream logincred;
    std::string token;
    if (!connection->GetLoginCredentials(logincred))
        token = "";
    else
    {
        try {
            JSON loginjson;
            loginjson.read_json(logincred);
            token = loginjson.GetString(token_key);
        } catch (...) {
            ASSERT_FAIL("INVALID_TOKEN");
        }
    }

	if (token == "")
		return kFalse;
    
    // Insert more headers for API calls here
    HTTPLinkSubsystemTypes::HeaderValue authHeaderValWideString;
    StringUtils::ConvertUTF8ToWideString(token, authHeaderValWideString);
    headers.insert(std::make_pair(kHEADER_AUTHORIZATION, authHeaderValWideString));
    return kTrue;
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::GetBatchAssetMetaDataFromResponse
//========================================================================================
bool16 CusHttpLnkResourceServerAPIWrapper::GetBatchAssetMetaDataFromResponse(const IDHTTPWrapper::Response& responsePtr, const URIVector &assetURIVector, AssetStatusWithMetadataPtrVector &assetStatusWithMetadataPtrVector)
{
    for (size_t i = 0; i < assetStatusWithMetadataPtrVector.size(); i++)
    {
        AssetStatusWithMetadataPtr assetMetaDataPtr(new AssetStatusWithMetadata());
        assetMetaDataPtr->fAssetStatus = AssetStatusWithMetadata::kInaccessible;
        assetStatusWithMetadataPtrVector[i] = assetMetaDataPtr;
    }
    
	if (responsePtr.GetStatus() != 200) //kHTTPStatus_OK
	{
		return kTrue;
	}

	const IDHTTPWrapper::Payload& payload(responsePtr.GetPayload());
    
	if (payload == "")
		return kTrue;

	AssetPathToMetadataMap assetPathToAssetMetadataMap;
	if (!payload.empty())
	{
		JSON jsonObject;
        //Create JsonObject From Payload
        std::stringstream jsonInput(payload);
        try
        {
            jsonObject.read_json(jsonInput);
        }
        catch (...)
        {
            return kFalse;
        }
		std::string path;
        
        // Parse response
		JSONArray itemsList;
        if (jsonObject.isList(kItems))
            jsonObject.GetListAt(kItems, itemsList);
        else
            return kFalse;

		for (auto& asset : itemsList)
		{
			bool parseResultForCurrentAsset = true;
			AssetStatusWithMetadataPtr assetStatusWithMetaDataPtr(new AssetStatusWithMetadata());
			AssetStatusWithMetadata::AssetMetadataPtr assetMetadataPtr(new IHTTPLinkResourceServerAPIWrapper::AssetMetadata());
			assetStatusWithMetaDataPtr->fAssetMetadataPtr = assetMetadataPtr;
			
			if (asset.checkKey(kPath))
			{
				if (asset.isString(kPath))
				{
					path = asset.GetString(kPath);
					assetStatusWithMetaDataPtr->fAssetMetadataPtr->fPath = path;
				}
				else
					parseResultForCurrentAsset = false;
			}

			if (!parseResultForCurrentAsset) continue;

			if (asset.checkKey(kFileSize))
			{
				if (asset.isNumber(kFileSize))
					assetStatusWithMetaDataPtr->fAssetMetadataPtr->fSize = asset.GetNumber(kFileSize);
				else
					parseResultForCurrentAsset = false;
			}

			if (!parseResultForCurrentAsset) continue;

			if (asset.checkKey(kUniqueID))
			{
				if (asset.isString(kUniqueID))
					assetStatusWithMetaDataPtr->fAssetMetadataPtr->fUniqueID = asset.GetString(kUniqueID);
				else
					parseResultForCurrentAsset = false;
			}

			if (!parseResultForCurrentAsset) continue;
			
			//Add it to the map
			assetPathToAssetMetadataMap[path] = assetStatusWithMetaDataPtr;

			assetStatusWithMetaDataPtr->fAssetStatus = AssetStatusWithMetadata::kAvailable;
		}		
	}

	AssetPathToMetadataMap_iter it;
	for (size_t i = 0; i < assetURIVector.size(); i++)
	{
        URI pathString(assetURIVector[i].GetComponent(URI::kPath));
        std::string requestPath = pathString.GetURI();
		it = assetPathToAssetMetadataMap.find(requestPath);
        // if it is not found in map then we can safely conclude that the asset has gone missing
		if (it == assetPathToAssetMetadataMap.end())
			(assetStatusWithMetadataPtrVector[i])->fAssetStatus = AssetStatusWithMetadata::kMissing;
        else
            assetStatusWithMetadataPtrVector[i] = it->second;
	}

	return kTrue;
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::IsServerAccessible
//========================================================================================
bool16 CusHttpLnkResourceServerAPIWrapper::GenerateSessionToken(IHTTPLinkResourceConnection* connection, std::string& token)
{
    if (connection == nil)
        return kFalse;
    
    std::stringstream loginCredetials;
    if (!connection->GetLoginCredentials(loginCredetials))
        return kFalse;
    
    // Currently using a dummy token
    // An API call can be made to generate the token
    token = "dummy-token";
    
    return kTrue;
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::IsServerAccessible
//========================================================================================
#pragma mark - IsServerAccessible
bool16 CusHttpLnkResourceServerAPIWrapper::IsServerAccessible(IHTTPLinkResourceConnection* connection, bool16& serverAccessible)
{
	HTTPLinkSubsystemTypes::Headers headers;
    if (!GetHeadersCommon(headers, connection))
        return kFalse;
    
    IDHTTPWrapper::HTTP http;
    
    InterfacePtr<IHTTPServerInfo> httpServerInfo(connection, UseDefaultIID());
    URI completeAssetURI = httpServerInfo->GetServerURI();
    completeAssetURI.SetComponent(URI::kScheme, WideString(kHTTPAssetURIScheme));
    IDHTTPWrapper::URL requestURL = completeAssetURI.GetURIW();
    
    IDHTTPWrapper::CompletionFunction requestCompletionFunction = boost::bind<void>(&CusHttpLnkResourceServerAPIWrapper::IsServerAccessibleCallbackOnWorkerThread, _1, _2);

	ts_Sync_IsServerAccessiblePtr = nil;
	if (!http.GET(requestCompletionFunction, requestURL, kTimeoutRequest_InMS, headers))
		return kFalse;

	bool16 isSuccess = kTrue;
	if (ts_Sync_IsServerAccessiblePtr == nil)
		isSuccess = kFalse;
    
	if (isSuccess)
		serverAccessible = ts_Sync_IsServerAccessiblePtr->fIsServerAccessible;

	return isSuccess;
}


//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::IsServerAccessibleCallbackOnWorkerThread
//========================================================================================
void CusHttpLnkResourceServerAPIWrapper::IsServerAccessibleCallbackOnWorkerThread(IDHTTPWrapper::RequestID inRequestID, IDHTTPWrapper::Response inResponse)
{
	bool16 isServerAccessible = kTrue;

	if (inResponse.IsNetworkConnectivityError())
	{
		isServerAccessible = kFalse;
	}
	ts_Sync_IsServerAccessiblePtr.reset(new IsServerAccessibleData);
	ts_Sync_IsServerAccessiblePtr->fIsServerAccessible = isServerAccessible;
}

//========================================================================================
// CusHttpLnkResourceServerAPIWrapper::FetchAssetPathAndRequestHeadersForDownload
//========================================================================================
bool16 CusHttpLnkResourceServerAPIWrapper::FetchAssetPathAndRequestHeadersForDownload(IHTTPLinkResourceConnection* connection, const URI& inURI, URI& assetURL, HTTPLinkSubsystemTypes::Headers& headers) const
{
    assetURL.SetComponent(URI::kScheme, WideString(kHTTPAssetURIScheme));
    assetURL.SetComponent(URI::kAuthority, WideString(kCusHttpLnkAuthority));
    assetURL.SetComponent(URI::kPath, inURI.GetComponent(URI::kPath));
    
    if (!GetHeadersCommon(headers, connection))
        return kFalse;
    
	return kTrue;
}
