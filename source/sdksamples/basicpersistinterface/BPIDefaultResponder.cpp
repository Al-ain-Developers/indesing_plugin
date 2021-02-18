//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPIDefaultResponder.cpp $
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
#include "isignalmgr.h"
#include "IDocumentSignalData.h"
#include "INewPISignalData.h"
#include "IDocument.h"
#include "IWorkspace.h"

// General  includes:
#include "CResponder.h"
#include "Trace.h"
#include "UIDList.h"
#include "ShuksanID.h"

// project includes:
#include "BPIID.h"
#include "IBPIData.h"
#include "BPIHelper.h"

/** Implements a responder, IResponder based on CResponder, that sets up default IBPIData
	when a new document is created, and when a new page item is created.

	
	@ingroup basicpersistinterface
*/
class BPIDefaultResponder : public CResponder
{
	public:
		/** Constructor.
			@param boss object this object is aggregated on.
		*/
		BPIDefaultResponder(IPMUnknown* boss);

		/** Destructor.
		 */
		virtual ~BPIDefaultResponder() {}

		/** Sets up default IBPIData.
			On receiving a new document signal the application default
			IBPIData is copied into the document default. On receiving
			a new page item signal the document default IBPIData is 
			copied into the page item.
			@param signalMgr provides information about the signal.
		 */
		virtual void Respond(ISignalMgr* signalMgr);

private:
		/** Copies the application default IBPIData 
			from the kWorkspaceBoss into its document default on
			kDocWorkspaceBoss.
			@param signalMgr provides information about the signal.
		 */
		virtual void HandleNewDocSignal(ISignalMgr* signalMgr);

		/** Copies document default IBPIData from kDocWorkspaceBoss
			into the new page item.
			@param signalMgr provides information about the signal.
		 */
		virtual void HandleNewPISignal(ISignalMgr* signalMgr);
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(BPIDefaultResponder, kBPIDefaultResponderImpl)

/*
*/
BPIDefaultResponder::BPIDefaultResponder(IPMUnknown* boss) :
	CResponder(boss)
{
}

/*
*/
void BPIDefaultResponder::Respond(ISignalMgr* signalMgr)
{
//	TRACEFLOW(kBPIPluginName, "BPIDefaultResponder::Respond()-->In\n");
	do {
		const ServiceID serviceID = signalMgr->GetServiceID();
		if (serviceID == kDuringNewDocSignalResponderService) {
			this->HandleNewDocSignal(signalMgr);
		}
		else if (serviceID == kNewPISignalResponderService) {
			this->HandleNewPISignal(signalMgr);
		}
		else {
			ASSERT_FAIL("BPIDefaultResponder::Respond called with invalid signal");
		}
	} while(false);
//	TRACEFLOW(kBPIPluginName, "BPIDefaultResponder::Respond()-->Out\n");
}

/*
*/
void BPIDefaultResponder::HandleNewDocSignal(ISignalMgr* signalMgr)
{
//	TRACEFLOW(kBPIPluginName, "BPIDefaultResponder::HandleNewDocSignal()-->In\n");
	do {		
		// Get reference to the document from the signal.
		InterfacePtr<IDocumentSignalData> documentSignalData(signalMgr, UseDefaultIID());
		ASSERT(documentSignalData != nil);
		if (documentSignalData == nil) {
			break;
		}
		InterfacePtr<IDocument> document(documentSignalData->GetDocument(), UseDefaultIID());
		if (!document) {
			break;
		}

		// Get the application defaults.
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		if (!workspace) {
			break;
		}
		InterfacePtr<IBPIData> appDefaultBPIData(workspace, UseDefaultIID());
		ASSERT(appDefaultBPIData);
		if (!appDefaultBPIData) {
			break;
		}

		// Copy the application default IBPIData into the document default.
		BPIHelper bpiHelper;
		if (bpiHelper.ProcessBPISetDataCmd(UIDList(document->GetDocWorkSpace()), appDefaultBPIData->Get()) != kSuccess) {
			ASSERT_FAIL("BPINewPIResponder failed to set default IBPIData");
		}

	} while(false);
//	TRACEFLOW(kBPIPluginName, "BPIDefaultResponder::HandleNewDocSignal()-->Out\n");
}

/*
*/
void BPIDefaultResponder::HandleNewPISignal(ISignalMgr* signalMgr)
{
//	TRACEFLOW(kBPIPluginName, "BPINewPIResponder::Respond()-->In\n");
	do {
		// Get a reference to the page item from the signal.
		ASSERT(signalMgr != nil);
		if (signalMgr == nil) {
			break;
		}
		InterfacePtr<INewPISignalData> newPISignalData(signalMgr, UseDefaultIID());
		ASSERT(newPISignalData != nil);
		if (newPISignalData == nil) {
			break;
		}

		// Check the page item has IBPIData.
		UIDRef pageItemRef = newPISignalData->GetPageItem();
		InterfacePtr<IBPIData> bpiData(pageItemRef, UseDefaultIID());
		if (bpiData == nil) {
			break;
		}

		// Get the document's default IBPIData.
		IDataBase* database = pageItemRef.GetDataBase();
		UID rootUID = database->GetRootUID();
		InterfacePtr<IDocument> document(database, rootUID, UseDefaultIID());
		ASSERT(document);
		if (!document) {
			break;
		}
		InterfacePtr<IBPIData> defaultBPIData(document->GetDocWorkSpace(), UseDefaultIID());
		if (!defaultBPIData) {
			break;
		}

		// Copy the default IBPIData into the new page item.
		BPIHelper bpiHelper;
		if (bpiHelper.ProcessBPISetDataCmd(UIDList(pageItemRef), defaultBPIData->Get()) != kSuccess) {
			ASSERT_FAIL("BPINewPIResponder failed to set default IBPIData");
		}

	} while(false);
//	TRACEFLOW(kBPIPluginName, "BPINewPIResponder::HandleNewPISignal()-->Out\n");
}

// End, BPIDefaultResponder.cpp.


