//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basictextadornment/BscTADocResponder.cpp $
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
#include "IDocument.h"
#include "IWorkspace.h"
#include "ITextAttributes.h"
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"

// General  includes:
#include "CResponder.h"
#include "Trace.h"
#include "UIDList.h"
#include "ShuksanID.h"

// project includes:
#include "BscTAID.h"

/** From SDK sample; Implements a responder, IResponder based on CResponder, that adds
	this plug-in's text attribute into the root style and defaults if
	it is not already present when a document is opened or a new document
	is created.

	If this plug-in is around when the application starts without any defaults
	then this plug-ins text attribute, kBscTAAttrBoss, is added to the root
	style and to text defaults on the session workspace. 
	However, if the plug-in is added after defaults are already initialised, 
	then kBscTAAttrBoss won't be in the root style or text defaults. This
	responder checks and fixes the document's root style and defaults if necessary.
	
	@ingroup basictextadornment
*/
class BscTADocResponder : public CResponder
{
	public:
		/** Constructor.
			@param boss object this object is aggregated on.
		*/
		BscTADocResponder(IPMUnknown* boss);

		/** Destructor.
		 */
		virtual ~BscTADocResponder() {}

		/** Responds to new and open document signals.
			@param signalMgr provides information about the signal.
		 */
		virtual void Respond(ISignalMgr* signalMgr);

private:
		/** Handles new and open document signals.
			@param signalMgr provides information about the signal.
		 */
		virtual void HandleDocSignal(ISignalMgr* signalMgr);

		/** Add kBscTAAttrBoss to the given set of attributes
			if it is not already present.
			@param textAttributes
		*/
		void AddAttributeIfNotPresent(ITextAttributes* textAttributes); 

private:
	// ClassID of attribute to be checked and added if not already present.
	const ClassID fAttributeClass;
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(BscTADocResponder, kBscTADocResponderImpl)

/*
*/
BscTADocResponder::BscTADocResponder(IPMUnknown* boss) :
	CResponder(boss), 
	fAttributeClass(kBscTAAttrBoss) // This plug-in's text attribute.
{
}

/*
*/
void BscTADocResponder::Respond(ISignalMgr* signalMgr)
{
	do {
		const ServiceID serviceID = signalMgr->GetServiceID();
		if (serviceID == kAfterNewDocSignalResponderService || 
			serviceID == kAfterOpenDocSignalResponderService ) {
			this->HandleDocSignal(signalMgr);
		}
		else {
			ASSERT_FAIL("BscTADocResponder::Respond called with invalid signal");
		}
	} while(false);
}

/*
*/
void BscTADocResponder::HandleDocSignal(ISignalMgr* signalMgr)
{
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

		// Get the document workspace.
		InterfacePtr<IWorkspace> workspace(document->GetDocWorkSpace(), UseDefaultIID());
		if (!workspace) {
			break;
		}

		// Any edits that the code below makes to text attributes on
		// should not affect the "modified" state of the document.
		IDataBase * db = ::GetDataBase(workspace);
		IDataBase::SaveRestoreModifiedState saveRestoreModifiedState(db);

		// Add fAttributeClass to the root style if it is not already there.
		InterfacePtr<IStyleGroupManager> paraStyleNameTable(workspace, IID_IPARASTYLEGROUPMANAGER);
		ASSERT(paraStyleNameTable);
		if (paraStyleNameTable == nil) {
			break;
		}
		UID rootStyleUID = paraStyleNameTable->GetRootStyleUID();
		ASSERT(rootStyleUID != kInvalidUID);
		if(rootStyleUID == kInvalidUID) {
			break;
		}
		InterfacePtr<ITextAttributes> rootTextAttributes(db, rootStyleUID, UseDefaultIID());
		ASSERT(rootTextAttributes);
		if (!rootTextAttributes) {
			break;
		}
		this->AddAttributeIfNotPresent(rootTextAttributes);

		// Add fAttributeClass to text defaults if it is not already there.
		InterfacePtr<ITextAttributes> defaultTextAttributes(workspace, UseDefaultIID());
		ASSERT(defaultTextAttributes);
		if (!defaultTextAttributes) {
			break;
		}
		this->AddAttributeIfNotPresent(defaultTextAttributes);
	} while(false);
}

/*
*/
void BscTADocResponder::AddAttributeIfNotPresent(ITextAttributes* textAttributes)
{
	do {
		InterfacePtr<const IPMUnknown> exists(textAttributes->QueryByClassID(fAttributeClass, IID_IUNKNOWN));
		if (exists) {
			// Already exists - nothing to do.
			break;
		}
		// Add attribute to the list of attributes.
		InterfacePtr<IPMUnknown> defaultAttribute(::CreateObject(fAttributeClass));
		ASSERT(defaultAttribute);
		if (!defaultAttribute) {
			break;
		}
		textAttributes->ApplyAttribute(defaultAttribute, fAttributeClass);
	} while(false);
}

// End, BscTADocResponder.cpp.


