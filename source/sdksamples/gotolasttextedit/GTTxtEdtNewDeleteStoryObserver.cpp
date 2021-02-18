//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtNewDeleteStoryObserver.cpp $
//  
//  Owner: Adrian O'Lenskie
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

// Interface includes
#include "IDocument.h"
#include "ISubject.h"
#include "ILayoutUIUtils.h"
#include "IObjectModel.h"
#include "GTTxtEdtInvalHandler.h"
#include "DBUtils.h"

// General includes
#include "CObserver.h"
#include "GenericID.h"
#include "TextID.h"
#include "PreferenceUtils.h"

// Project includes:
#include "GTTxtEdtID.h"

/** An observer watching for stories being created and deleted. This observer gets attached on document
creation/open by the GTTxtEdtResponder. While the responder also receives new/delete story events, this
observer allows us to manage the invalhandler appropriately (we require an inval handler 
per document). If this was managed within the responder, we would require to manintain the list of invalidation
handlers per document.

The invalidation hander is created on attach (which relates to a document create/open event), and destroyed on
detach (document close). If we receive a story create/delete signal, we indicate that the event if of interest
by calling the inval handler.

@see GTTxtEdtInvalHandler
@ingroup gotolasttextedit
*/
class GTTxtEdtNewDeleteStoryObserver : public CObserver
{
public:
	/**
	Constructor
	*/
	GTTxtEdtNewDeleteStoryObserver(IPMUnknown *boss);
	/**
	Destructor
	*/
	virtual ~GTTxtEdtNewDeleteStoryObserver();
	/**
	Attach this observer to the document.
	*/
	virtual void AutoAttach();
	/**
	Detach this observer from the document
	*/
	virtual void AutoDetach();
	/**
	Signal the observer that a change has occurred (used to determine whether we want to record this event through
	our invalidation handler).
	*/
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
private:
	/**
	Our invalidation handler. 
	*/
	GTTxtEdtInvalHandler* fGTTxtEdtInvalHandler;

};

/*
*/
CREATE_PMINTERFACE(GTTxtEdtNewDeleteStoryObserver, kGTTxtEdtNewDeleteStoryObserverImpl)

/*
*/
GTTxtEdtNewDeleteStoryObserver::GTTxtEdtNewDeleteStoryObserver(IPMUnknown *boss) :
CObserver(boss),
fGTTxtEdtInvalHandler(nil)
{
}

/*
*/
GTTxtEdtNewDeleteStoryObserver::~GTTxtEdtNewDeleteStoryObserver()
{

}


/*
*/
void GTTxtEdtNewDeleteStoryObserver::AutoAttach()
{
	do {
		InterfacePtr<IDocument> iDocument(this, UseDefaultIID());
		if (iDocument == nil){	
			ASSERT(iDocument);
			break;
		}
		// Attach the inval handler to the database.
		if (fGTTxtEdtInvalHandler == nil) {
			fGTTxtEdtInvalHandler = new GTTxtEdtInvalHandler();
			DBUtils::AttachInvalHandler(::GetDataBase(iDocument), fGTTxtEdtInvalHandler, kGTTxtEdtInvalHandlerID);
		}
		// Attach this observer to the story list.
		InterfacePtr<ISubject> iSubject(iDocument, UseDefaultIID());
		if (iSubject && !iSubject->IsAttached(ISubject::kRegularAttachment,this, IID_ISTORYLIST, IID_IGTTXTEDTSTORYCREATEDELETEOBSERVER)) {
			iSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_ISTORYLIST, IID_IGTTXTEDTSTORYCREATEDELETEOBSERVER);
		}
	} while (kFalse);
}

/*
*/
void GTTxtEdtNewDeleteStoryObserver::AutoDetach()
{
	do {
		InterfacePtr<IDocument> iDocument(this, UseDefaultIID());
		if (iDocument == nil){	
			ASSERT(iDocument);
			break;
		}
		// Detach the inval handler from the database.
		if (fGTTxtEdtInvalHandler != nil){
			DBUtils::DetachInvalHandler(::GetDataBase(iDocument), fGTTxtEdtInvalHandler);
			fGTTxtEdtInvalHandler = nil;
		}
		//Detach this observer from the story list.
		InterfacePtr<ISubject> iSubject(iDocument, UseDefaultIID());
		if (iSubject && iSubject->IsAttached(ISubject::kRegularAttachment,this, IID_ISTORYLIST, IID_IGTTXTEDTSTORYCREATEDELETEOBSERVER)) {
			iSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_ISTORYLIST, IID_IGTTXTEDTSTORYCREATEDELETEOBSERVER);
		}
	} while (kFalse);

}

/*
*/
void GTTxtEdtNewDeleteStoryObserver::Update(const ClassID& theChange, ISubject* theSubject,
											const PMIID &protocol, void* changedBy)
{
	do {      
		if (theChange != kNewStoryCmdBoss && theChange != kDeleteStoryCmdBoss){
			break;
		}
#ifdef DEBUG
		InterfacePtr<IObjectModel> iObjectModel(GetExecutionContextSession(), UseDefaultIID());
		if (iObjectModel == nil){
			break;
		}
		TRACEFLOW(kGTTxtEdtPluginName,"GTTxtEdtNewDeleteStoryObserver::Update, pName %s cName %s subject %s\n", iObjectModel->GetIDName(theChange),iObjectModel->GetIDName(protocol),iObjectModel->GetIDName(::GetClass(theSubject)));
#endif

		ASSERT(fGTTxtEdtInvalHandler != nil);
		if (fGTTxtEdtInvalHandler == nil) {
			break;
		}

		ICommand* theCmd = static_cast<ICommand *>(changedBy);
		if (theCmd && theCmd->GetCommandState() == ICommand::kDone ) {
			const UIDList* itemList = theCmd->GetItemList();
			if (itemList && itemList->Length()>0){
				// Story created or story deleted. Call the inval handler
				// so that the plug-in is called on undo or redo of this event.
				bool16 storyCreated = (theChange == kNewStoryCmdBoss) ? kTrue : kFalse;
				fGTTxtEdtInvalHandler->AddStoryInvalInfo(itemList->GetRef(0), storyCreated);
			}
		}

	} while (kFalse);
}

