//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/docwatch/DocWchResponder.cpp $
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

// Implementation includes:
#include "CreateObject.h"
#include "CResponder.h"
#include "DocWchUtils.h"
#include "DocWchID.h"

/** DocWchResponder
	Handles signals related to document file actions.  The file action 
	signals it receives are dictated by the DocWchServiceProvider class.

	DocWchResponder implements IResponder based on
	the partial implementation CResponder.


	@ingroup docwatch
	
*/
class DocWchResponder : public CResponder
{
	public:
	
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		DocWchResponder(IPMUnknown* boss);

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
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(DocWchResponder, kDocWchResponderImpl)

/* DocWchActionComponent Constructor
*/
DocWchResponder::DocWchResponder(IPMUnknown* boss) :
	CResponder(boss)
{
}

/* Respond
*/
void DocWchResponder::Respond(ISignalMgr* signalMgr)
{
	// Exit if the responder should do nothing
	if (DocWchUtils::QueryDocResponderMode() != kTrue)
		return;

	// Get the service ID from the signal manager
	ServiceID serviceTrigger = signalMgr->GetServiceID();

	// Get a UIDRef for the document.  It will be an invalid UIDRef
	// for BeforeNewDoc, BeforeOpenDoc, AfterSaveACopy, and AfterCloseDoc because
	// the document doesn't exist at that point.
	InterfacePtr<IDocumentSignalData> docData(signalMgr, UseDefaultIID());
	if (docData == nil)
	{
		ASSERT_FAIL("Invalid IDocumentSignalData* - DocWchResponder::Respond");
		return;
	}
	UIDRef doc = docData->GetDocument();

	// Take action based on the service ID
	switch (serviceTrigger.Get())
	{
		case kBeforeNewDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kBeforeNewDocSignalStringKey);
			break;
		}
		case kDuringNewDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kDuringNewDocSignalStringKey);
			break;
		}
		case kAfterNewDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kAfterNewDocSignalStringKey);
			break;
		}
		case kBeforeOpenDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kBeforeOpenDocSignalStringKey);
			break;
		}
		case kDuringOpenDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kDuringOpenDocSignalStringKey);
			break;
		}
		case kAfterOpenDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kAfterOpenDocSignalStringKey);
			break;
		}
		case kBeforeSaveDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kBeforeSaveDocSignalStringKey);
			break;
		}
		case kAfterSaveDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kAfterSaveDocSignalStringKey);
			break;
		}
		case kBeforeSaveAsDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kBeforeSaveAsDocSignalStringKey);
			break;
		}
		case kAfterSaveAsDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kAfterSaveAsDocSignalStringKey);
			break;
		}
		case kBeforeSaveACopyDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kBeforeSaveACopyDocSignalStringKey);
			break;
		}
		case kDuringSaveACopyDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kDuringSaveACopyDocSignalStringKey);
			break;
		}
		case kAfterSaveACopyDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kAfterSaveACopyDocSignalStringKey);
			break;
		}
		case kBeforeRevertDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kBeforeRevertDocSignalStringKey);
			break;
		}
		case kAfterRevertDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kAfterRevertDocSignalStringKey);
			break;
		}
		case kBeforeCloseDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kBeforeCloseDocSignalStringKey);
			break;
		}
		case kAfterCloseDocSignalResponderService:
		{
			DocWchUtils::DwAlert(doc, kAfterCloseDocSignalStringKey);
			break;
		}

		default:
			break;
	}
}

// End, DocWchResponder.cpp.



