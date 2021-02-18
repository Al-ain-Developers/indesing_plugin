//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hostadapter/IDHAResponder.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: lrymarz
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

//
//  This code came mostly from:
//		Adobe InDesign CS6 Plugin SDK\source\sdksamples\linkwatcher\LnkWtchDocResponder.cpp
//

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IClassIDData.h"
#include "isignalmgr.h"
#include "IDocumentSignalData.h"
#include "IObserver.h"
#include "IPMStream.h"
#include "IScriptEvent.h"
#include "IScriptEventTarget.h"
#include "IScriptUtils.h"
#include "OpenPlaceID.h"
#include "MasterPageID.h"

// General  includes:
#include "CResponder.h"
#include "Trace.h"
#include "IDFile.h"
#include "StreamUtil.h"
#include "FileUtils.h"

// Project includes:
#include "IDHAID.h"

/** 
	Responds to events registered in IDHA.fr and dispatches the events
	to the scripting layer for CSAW.

	This implemented the IID_IRESPONDER interface in the InDesign SDK.
	see IDHAObserver for the implementation of the IID_IOBSERVER interface.
*/
class IDHAResponder : public CResponder
{
public:
	/** Constructor.
	@param boss object this object is aggregated on.
	*/
	IDHAResponder(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~IDHAResponder() {}

	/** will dispatch events to the scripting layer as necessary
		@param signalMgr provides information about the signal.
	*/
	virtual void Respond(ISignalMgr* signalMgr);

private:


	void DispatchAppScriptEvent( ScriptElementID eventID );
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(IDHAResponder, kIDHAResponderImpl)

/*
*/
IDHAResponder::IDHAResponder(IPMUnknown* boss) :
CResponder(boss)
{
}

void IDHAResponder::Respond(ISignalMgr* signalMgr)
{
	do {		
		// Get the service ID from the signal manager
		ServiceID serviceID = signalMgr->GetServiceID();

		char str[64];
		sprintf(str, "Respond ID: %x\n", serviceID.Get());
		TRACE(str);

		// Take action based on the service ID
		switch (serviceID.Get()) 
		{
		case kApplyMasterSignalResponderService:
			{
				DispatchAppScriptEvent(kMasterPageAppliedEventScriptElement);
				break;
			}
		default:
			break;
		}
	} while(false);
}



/* Dispatches the event using the IScriptEventTarget API.
*/
void IDHAResponder::DispatchAppScriptEvent( ScriptElementID eventID )
{
	InterfacePtr<IScript> appScript( Utils<IScriptUtils>()->QueryApplicationScript() ) ;
	InterfacePtr<IScriptEventTarget> target( appScript, UseDefaultIID() ) ;
	if(target)
		target->DispatchScriptEvent( eventID ) ;
}

// End, IDHAResponder.cpp.


