//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HTTPAssetLinkResourceStateBatchUpdater.h $
//  
//  Owner: Sanyam Jain
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
//  Copyright 2016 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#ifndef __HTTPAssetLinkResourceStateBatchUpdater__
#define __HTTPAssetLinkResourceStateBatchUpdater__

#include "CPMUnknown.h"

#include "IHTTPLinkConnectionManager.h"
#include "IHTTPLinkManager.h"
#include "IHTTPLinkUtils.h"
#include "IHTTPServerInfo.h"

#include "StringUtils.h"
#include "URICommonUtils.h"

#include "DocHTTPBatchQueryManager.h"

#include <boost/thread/thread_time.hpp>
#include <set>

/**
Experimental header - will be modified/documented in future.
*/
class PUBLIC_DECL HTTPAssetLinkResourceStateBatchUpdater : public CPMUnknown<IHTTPLinkResourceStateBatchUpdater>
{
public:
    typedef CPMUnknown<IHTTPLinkResourceStateBatchUpdater> inherited;
    HTTPAssetLinkResourceStateBatchUpdater(IPMUnknown* boss);
    ~HTTPAssetLinkResourceStateBatchUpdater();
    virtual ErrorCode QueueLinkResourceUpdateRequestForBatch(const UID& resourceUID, const HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData& updateLinkResourceStateData);

private:
    typedef std::set<UID> UIDSet;
    typedef UIDSet::iterator UIDSet_iter;
    //TODO extend it to associate batch size for each type if needed
    typedef std::map<HTTPLinkSubsystemTypes::BatchRequestObjectType, boost::system_time> BatchRequestObjectTypeInfoMap;
    typedef BatchRequestObjectTypeInfoMap::iterator BatchRequestObjectTypeInfoMap_iter;
    
    int32 fIDBatchSize;
    int32 fHTTPConfiguredBatchLimit;
    long fTimeLimitForBatchCall;					//Max time limit for successive batch calls in milliseconds
    long fMinTimeBetweenCalls;					    //Min time duration between two batch calls in milliseconds
    URI fConnectionURI;
    BatchRequestObjectTypeInfoMap fBatchRequestObjectTypeInfo;
    
	static void HandleFetchingBatchAssetMetadata(const std::vector<UID> &uidVector,
                                                 HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData updateLinkResourceStateData,
                                                 URI connectionURI,
                                                 HTTPLinkSubsystemTypes::BatchRequestObjectType objType,
                                                 IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtrVectorPtr assetStatusWithMetadataVectorPtr);
    bool16 PopulateBatchRequestVectors(const HTTPLinkSubsystemTypes::GUID& guid, HTTPLinkSubsystemTypes::BatchRequestObjectType objType, std::vector<IHTTPLinkResourceServerAPIWrapper::URIVector>&batchRequestURIPathVectors, std::vector<std::vector<UID> >&batchRequestUIDVectors);
    bool InitiateBatchRequest(const int32& numOfUIDs, const HTTPLinkSubsystemTypes::BatchRequestObjectType& objType, const HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData& updateLinkResourceStateData);
    bool RetrieveBatchLimitsConfigured(void);
    void PopulateBatchObjectTypeInfoMap(void);
    static void GetHttpRequestPathForBatchRequest(const URI& uri, std::string& requestPath, bool encodedPathRequested = false);
};

#endif // __HTTPAssetLinkResourceStateBatchUpdater__
