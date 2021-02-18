//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLink/CusHttpLnkLinkResourceStateUpdater.cpp $
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
#include "HTTPAssetLinkResourceStateUpdater.h"

// Project includes
#include "CustomHttpLinkID.h"

class CusHttpLnkLinkResourceStateUpdater : HTTPAssetLinkResourceStateUpdater
{
public:
    typedef HTTPAssetLinkResourceStateUpdater inherited;
    
    CusHttpLnkLinkResourceStateUpdater(IPMUnknown* boss);
    ~CusHttpLnkLinkResourceStateUpdater();
    
    
    /*
     Callback for fetching asset metadata
     @param resourceUID [IN] UID of the res.
     @param updateLinkResourceStateData [IN] state data for res.
     @param assetStatusWithMetadataPtr [OUT] status metadata pointer filled after fetching the asset.
     */
    static void HandleFetchingAssetMetadata(UID    resourceUID, HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData updateLinkResourceStateData, IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr assetStatusWithMetadataPtr);
    
protected:
    
    /*
     @param resourceRef [IN] UIDRef of the Link Resource.
     @param bNotify [IN] true for notify on Update.
     @param async [IN] true async update.
     @return kSuccess on success else false.
     */
    virtual ErrorCode UpdateLinkResourceState(const UIDRef& resourceRef, bool bNotify, bool async);
    
};


CREATE_PMINTERFACE(CusHttpLnkLinkResourceStateUpdater, kCusHttpLnkLinkResourceStateUpdaterImpl)


//========================================================================================
// CusHttpLnkLinkResourceStateUpdater::Constructor
//========================================================================================
CusHttpLnkLinkResourceStateUpdater::CusHttpLnkLinkResourceStateUpdater(IPMUnknown* boss)
: inherited(boss)
{
}

//========================================================================================
// CusHttpLnkLinkResourceStateUpdater::Destructor
//========================================================================================
CusHttpLnkLinkResourceStateUpdater::~CusHttpLnkLinkResourceStateUpdater()
{
}


ErrorCode CusHttpLnkLinkResourceStateUpdater::UpdateLinkResourceState(const UIDRef& resourceRef, bool bNotify, bool async)
{
    // Add custom logic for state updation of assets here
    return inherited::UpdateLinkResourceState(resourceRef, bNotify, async);
}


void CusHttpLnkLinkResourceStateUpdater::HandleFetchingAssetMetadata(UID resourceUID, HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData updateLinkResourceStateData, IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr assetStatusWithMetadataPtr)
{
    // Add custom logic for extracting the metadat from status calls here
    inherited::HandleFetchingAssetMetadata(resourceUID, updateLinkResourceStateData, assetStatusWithMetadataPtr);
}

