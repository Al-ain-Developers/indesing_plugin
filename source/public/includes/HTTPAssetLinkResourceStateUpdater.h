//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HTTPAssetLinkResourceStateUpdater.h $
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

#ifndef __HTTPAssetLinkResourceStateUpdater__
#define __HTTPAssetLinkResourceStateUpdater__

#include "CPMUnknown.h"

#include "IBoolData.h"
#include "ILinkResource.h"
#include "ILinkResourceStateUpdater.h"
#include "IHTTPLinkResourceServerAPIWrapper.h"

#include "HTTPLinkSubsystemTypes.h"

/**
Experimental header - will be modified/documented in future.
*/
class PUBLIC_DECL HTTPAssetLinkResourceStateUpdater : public CPMUnknown<ILinkResourceStateUpdater>
{
public:
    typedef CPMUnknown<ILinkResourceStateUpdater> inherited;

	HTTPAssetLinkResourceStateUpdater(IPMUnknown* boss);

	/*
	@param resourceRef [IN] UIDRef of the Link Resource.
	@param bNotify [IN] true for notify on Update.
	@return kSuccess on succes else kFailure.
	*/
	ErrorCode UpdateResourceStateSync(const UIDRef& resourceRef, bool bNotify);
	
	/*
	@param resourceRef [IN] UIDRef of the Link Resource.
	@return kSuccess on succes else kFailure.
	*/
	ErrorCode UpdateResourceStateAsync(const UIDRef& resourceRef);
	
	/*
	@param resourceRef [IN] UIDRef of the Link Resource.
	@ return Nothing. It just cancel the update if can.
	*/
	void CancelUpdateResourceState(const UIDRef& resourceRef){}
	
	/*
	@param resourceRef [IN] UIDRef of the Link Resource.
	@ return Nothing. It just wait for the completion for resurce state update.
	*/
	void WaitForUpdateResourceStateCompletion(const UIDRef& resourceRef) {}
	
	/*
	@param resourceRef [IN] UIDRef of the Link Resource.
	@param relativeURI [IN] uri of the resource.
	@param bIgnoreStamp [IN] true if we want to ignore the stamp else false.
	@ return kSuccess on success else false.
	*/
	ErrorCode ResolveResource(const UIDRef& resourceRef, const URI& relativeURI, bool bIgnoreStamp);
	// Callback for fetching asset metadata
	
	/*
	@param resourceUID [IN] UID of the res.
	@param updateLinkResourceStateData [IN] state data for res.
	@param assetStatusWithMetadataPtr [OUT] status metadata pointer filled after fetching the asset.
	*/
	static void HandleFetchingAssetMetadata(UID	resourceUID, HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData updateLinkResourceStateData, IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr assetStatusWithMetadataPtr);

protected:

	/*
	@param resourceRef [IN] UIDRef of the Link Resource.
	@param bNotify [IN] true for notify on Update.
	@param async [IN] true async update.
	@return kSuccess on success else false.
	*/
	virtual ErrorCode UpdateLinkResourceState(const UIDRef& resourceRef, bool bNotify, bool async);

    /*
    @param uri [IN] uri of the Link
    @param assetMetaData[IN] assetmetadata values of given link resource
    @return resource stamp to identify the state of resource
    */
    static WideString CreateResourceStamp(const URI& uri, const IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr& assetMetaData);
private:

	// Prevent copy construction and assignment.
	HTTPAssetLinkResourceStateUpdater(const HTTPAssetLinkResourceStateUpdater&);
	HTTPAssetLinkResourceStateUpdater& operator=(const HTTPAssetLinkResourceStateUpdater&);
    
    // Invalidates cache if its stale
    static void InvalidateCacheIfStale(URI uri, IHTTPLinkResourceServerAPIWrapper::AssetMetadataPtr assetMetadata);
    
    // Extracts uri from linkresource and invalidate it if its stale
    static void CheckAndInvalidateCache(InterfacePtr<ILinkResource> iLinkResource, IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr assetStatusWithMetadataPtr, bool renditionUri = true);
};

#endif // __HTTPAssetLinkResourceStateUpdater__
