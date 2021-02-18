//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLink/CusHttpLnkLinkResourceHelperHandler.cpp $
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

#include "CustomHttpLinkID.h"
#include "HTTPAssetLinkResourceHelperHandler.h"
#include "IActionManager.h"
#include "IApplication.h"
#include "CustomHttpLinkUIID.h"

/**
 Provide methods to manipulate the resource
 
 @ingroup customhttplink.sdk
 */

class CusHttpLnkLinkResourceHelperHandler : HTTPAssetLinkResourceHelperHandler
{
public:
	typedef HTTPAssetLinkResourceHelperHandler inherited;
	typedef object_type data_type;

	CusHttpLnkLinkResourceHelperHandler(IPMUnknown* boss);
	virtual ~CusHttpLnkLinkResourceHelperHandler();
    //replace fpo with original asset.
    virtual void ReplaceWithOriginalAsset() const;

};

CREATE_PMINTERFACE(CusHttpLnkLinkResourceHelperHandler, kCusHttpLnkLinkResourceHelperHandlerImpl)

/* Constructor
*/
CusHttpLnkLinkResourceHelperHandler::CusHttpLnkLinkResourceHelperHandler(IPMUnknown* boss)
: inherited(boss)
{
}

/* Destructor
*/
CusHttpLnkLinkResourceHelperHandler::~CusHttpLnkLinkResourceHelperHandler()
{
}


//Replace FPO with original Asset
void CusHttpLnkLinkResourceHelperHandler::ReplaceWithOriginalAsset() const
{
    InterfacePtr<const IApplication> app(GetExecutionContextSession()->QueryApplication());
    InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
    actionMgr->PerformAction(GetExecutionContextSession()->GetActiveContext(), kReplaceFPOWithOriginalLinkActionID);
}
