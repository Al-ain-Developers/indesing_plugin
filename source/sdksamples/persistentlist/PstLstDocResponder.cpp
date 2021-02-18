//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstDocResponder.cpp $
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
#include "IClassIDData.h"
#include "isignalmgr.h"
#include "IDocumentSignalData.h"
#include "IUIDData.h"
#include "IObserver.h"

// Implementation includes:
#include "CreateObject.h"
#include "CResponder.h"
#include "PstLstID.h"

/** 
	Handles signals related to document file actions.  The file
	action signals it receives are dictated by the PstLstDocServiceProvider
	class.

	PstLstDocResponder implements IResponder based on
	the partial implementation CResponder.

	We are interested in knowing when a documnet is opened or closed.  When these events happen,
	we have to attach/detach a document observer which will get notified when a document's hierarchy 
	is changed.  This allows us to purge the custom data associated with the page item.  In
	PstLstDocServiceProvider, we registered our interests in kAfterNewDocSignalResponderService,
	kDuringOpenDocSignalResponderService, and kBeforeCloseDocSignalResponderService, that will allow
	us being notified when these event occurs.  In that case we will attach/detach the document
	observer accordingly.
	
	@ingroup persistentlist
	
*/
class PstLstDocResponder : public CResponder
{
	public:
	
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PstLstDocResponder(IPMUnknown* boss);

		/**
			Respond() handles the file action signals when they
			are dispatched by the signal manager.  This implementation
			simply creates alerts to display each signal.

			@param signalMgr Pointer back to the signal manager to get
			additional information about the signal.
		*/
		virtual void Respond(ISignalMgr* signalMgr);

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstDocResponder, kPstLstDocResponderImpl)

/* PstLstDocResponder Constructor
*/
PstLstDocResponder::PstLstDocResponder(IPMUnknown* boss) :
	CResponder(boss)
{
}

/* PstLstDocResponder::Respond
*/
void PstLstDocResponder::Respond(ISignalMgr* signalMgr)
{
	// Get the service ID from the signal manager
	ServiceID serviceTrigger = signalMgr->GetServiceID();

	// Get a UIDRef for the document.  It will be an invalid UIDRef
	// for BeforeNewDoc, BeforeOpenDoc, AfterSaveACopy, and AfterCloseDoc because the
	// document doesn't exist at that point.
	InterfacePtr<IDocumentSignalData> iDocData(signalMgr, UseDefaultIID());
	if (iDocData == nil)
	{
		ASSERT_FAIL("Invalid IDocumentSignalData* - PstLstDocResponder::Respond");
		return;
	}
	UIDRef docRef = iDocData->GetDocument();

	// Take action based on the service ID
	switch (serviceTrigger.Get())
	{
		case kAfterNewDocSignalResponderService:
		case kDuringOpenDocSignalResponderService:
		{
			InterfacePtr<IObserver> iDocObserver(docRef, IID_IPSTLSTOBSERVER);
			if (iDocObserver != nil)
			{
				iDocObserver->AutoAttach();
			}
			break;
		}
		case kBeforeCloseDocSignalResponderService:
		{
			InterfacePtr<IObserver> iDocObserver(docRef, IID_IPSTLSTOBSERVER);
			if (iDocObserver != nil)
			{
				iDocObserver->AutoDetach();
			}
			break;
		}

		default:
			break;
	}

}

// End, PstLstDocResponder.cpp.



