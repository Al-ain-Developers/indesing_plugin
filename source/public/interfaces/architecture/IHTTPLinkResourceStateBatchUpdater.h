//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkResourceStateBatchUpdater.h $
//  
//  Owner: Ramnik Singh
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

#pragma once
#ifndef __IHTTPLinkResourceStateBatchUpdater__
#define __IHTTPLinkResourceStateBatchUpdater__

#include "IPMUnknown.h"
#include "LinksID.h"
#include "IHTTPLinkResourceServerAPIWrapper.h"
#include "UIDList.h"

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
 */

/**
 IHTTPLinkResourceStateBatchUpdater contains functions for updating states in batch mode.
 This will only be used when web-api supports batch mode.
 
 For custom imlementation return true from IsBatchUpdateSupported function
 of IHTTPLinkResourceServerAPIWrapper.Then subclass this interface by creating a boss based on
 kHTTPAssetLinkResourceHelperBoss with the implementation of this interface. Also, custom
 implementations should aggregate this interface on the boss serving
 IID_IHTTPLINKRESOURCECONNECTION.
*/
class IHTTPLinkResourceStateBatchUpdater : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPLINKRESOURCESTATEBATCHUPDATER };

	/*
	Queue the batch update request for the given Link resource UID.
	@param resourceUID					[IN] UID of the link resource who request is to be batched.
	@param updateLinkResourceStateData	[IN] Link Resource State Data.
	@return kSuccess if operation is successful otherwise kFailure
	*/
	virtual ErrorCode QueueLinkResourceUpdateRequestForBatch(const UID& resourceUID,  const HTTPLinkSubsystemTypes::UpdateLinkResourceStateClientData& updateLinkResourceStateData) = 0;
};

#endif	// __IHTTPLinkResourceStateBatchUpdater__
