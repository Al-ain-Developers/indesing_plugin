//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkResponder.cpp $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ICommand.h"
#include "IDocument.h"
#include "ILinkCmdSignalData.h"
#include "isignalmgr.h"

// General includes:
#include "CResponder.h"
#include "DebugClassUtils.h"
#include "LinksID.h"
#include "Utils.h"
// Project includes:

#include "CusDtLnkID.h"



/** Implementation of IResponder that responds to link signals.
	@see CusDtLnkRespServiceProvider for signals we receive
	@ingroup customdatalink
*/
class CusDtLnkLinkResponder: public CResponder
{
public:
	/** Constructor
		@param boss object on which this interface aggregated
	*/
	CusDtLnkLinkResponder(IPMUnknown *boss);

	/** @see IResponder::Respond
	*/
	virtual void Respond(ISignalMgr* signalMgr);


};

/*
*/
CREATE_PMINTERFACE(CusDtLnkLinkResponder, kCusDtLnkLinkResponderImpl)

/*
*/
CusDtLnkLinkResponder::CusDtLnkLinkResponder(IPMUnknown *boss) : 
	CResponder(boss)
{
}

/*
*/

void CusDtLnkLinkResponder::Respond( ISignalMgr* signalMgr )
{
	do {
		// TRACE the service raising the signal.
		const ServiceID serviceID = signalMgr->GetServiceID();
#ifdef DEBUG
		DebugClassUtilsBuffer serviceBuf;
		const char* serviceName = DebugClassUtils::GetIDName(&serviceBuf, serviceID);
		TRACEFLOW(kCusDtLnkPluginName, "Respond: serviceName=%s, ", serviceName);
#endif

		// TRACE the command associated with the signal.
		InterfacePtr<ILinkCmdSignalData> linkCmdSignalData(signalMgr, UseDefaultIID());
		if (linkCmdSignalData == nil) {
			break;
		}
		ICommand* signallingCommand = linkCmdSignalData->GetCommand();
		ASSERT(signallingCommand);
		if (!signallingCommand) {
			break;
		}
		const ICommand::CommandState cmdState = signallingCommand->GetCommandState();
#ifdef DEBUG		
			DebugClassUtilsBuffer classBuf;
			const char* className = DebugClassUtils::GetIDName(&classBuf, ::GetClass(signallingCommand));
			TRACEFLOW(kCusDtLnkPluginName, " signalling cmd=%s, cmdState=%d\n", 
				className,
				cmdState);			
#endif

		// Non-document databases should be ignored. For instance, the app might be adding
		// a link to a book (kBookBoss)
		IDataBase *db = linkCmdSignalData->GetDataBase();
		UIDRef docRef = UIDRef(db, db->GetRootUID());
		InterfacePtr<IDocument> theDocument(docRef, UseDefaultIID());
		if (theDocument == nil) {
			break;
		}
		
		switch(serviceID.Get()) {

			case kBeforeAddLinkSignalResponderService:
				break;
			case kAfterAddLinkSignalResponderService:	
				break;
			case kBeforeAddExtraLinkSignalResponderService:
				break;
			case kAfterAddExtraLinkSignalResponderService:
				break;
			case kBeforeAttachDataLinkSignalResponderService:
				break;
			case kAfterAttachDataLinkSignalResponderService:
				break;
			case kBeforeRemoveLinksSignalResponderService:
				break;
			case kAfterRemoveLinksSignalResponderService:
				break;
			case kBeforeRestoreLinkSignalResponderService:
				break;
			case kAfterRestoreLinkSignalResponderService:
				break;
			case kBeforeUpdateLinkSignalResponderService:
				break;
			case kAfterUpdateLinkSignalResponderService:
				break;
			case kBeforeAddEmbedSignalResponderService:
				break;
			case kAfterAddEmbedSignalResponderService:
				break;
			case kBeforeRemoveEmbedSignalResponderService:
				break;
			case kAfterRemoveEmbedSignalResponderService:
				break;
		}
	} while(false);
}
