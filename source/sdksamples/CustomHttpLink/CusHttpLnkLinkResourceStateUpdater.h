//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLink/CusHttpLnkLinkResourceStateUpdater.h $
//
//  Owner: Adobe Developer Technologies
//
//  $Author: vans $
//
//  $DateTime: 2020/11/06 05:06:09 $
//
//  $Revision: #1 $
//
//  $Change: 1088554 $
//
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or
//  distribution of it requires the prior written permission of Adobe.
//
//========================================================================================

#ifndef __CustomAssetLinkResourceStateUpdater__
#define __CustomAssetLinkResourceStateUpdater__

#include "CPMUnknown.h"

#include "LinksID.h"

#include "ILinkResourceStateUpdater.h"
#include "IHTTPLinkResourceServerAPIWrapper.h"

#include "HTTPLinkSubsystemTypes.h"

class CusHttpLnkLinkResourceStateUpdater : public CPMUnknown<ILinkResourceStateUpdater>
{
public:
    typedef CPMUnknown<ILinkResourceStateUpdater> inherited;

	CusHttpLnkLinkResourceStateUpdater(IPMUnknown* boss);
	~CusHttpLnkLinkResourceStateUpdater();

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
	
    /*
    Callback for fetching asset metadata
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

private:

	// Prevent copy construction and assignment.
	CusHttpLnkLinkResourceStateUpdater(const CusHttpLnkLinkResourceStateUpdater&);
	CusHttpLnkLinkResourceStateUpdater& operator=(const CusHttpLnkLinkResourceStateUpdater&);
};


#endif //__CustomAssetLinkResourceStateUpdater__
