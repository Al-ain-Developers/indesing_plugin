//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtResponder.cpp $
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
#include "IApplication.h"
#include "IDialogMgr.h"
#include "INewStorySignalData.h"
#include "IDocumentSignalData.h"
#include "IUIDData.h"
#include "IDocument.h"
#include "IObserver.h"
#include "ISubject.h"
#include "IStoryList.h"
#include "ITextModel.h"
#include "IFrameList.h"
#include "IDataBase.h"
#include "ITextFrameColumn.h"
#include "IGTTxtEdtSnapshotInterface.h"
#include "ITextUtils.h"
#include "IPalettePanelUtils.h"
#include "IPanelControlData.h"

// Implementation includes:
#include "CreateObject.h"
#include "CResponder.h"
#include "GTTxtEdtID.h"
#include "TextID.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "RsrcSpec.h"
#include "UIDList.h"

/** GTTxtEdtResponder
Handles signals related to document file actions and text story creation/deletion. 

On document creation, we attach our story creation/deletion observer to the document 
(needed for the invalidation handler). 

On document open, we attach our story creation/deletion observer to the document, and 
attach our story edit observer to any existing stories.

On document close, we detach our story creation/deletion observer from the document, and
detach any story edit observers from stories in the document.

On creation of a new text story, we attach our story edit observer to the story. 

On deletion of a text story, we detach our story edit observer from the story and test to see if 
the story is maintained by our undoable snapshot interface. If it is, we reset the undoable data.

@ingroup gotolasttextedit

*/
class GTTxtEdtResponder : public CResponder
{
public:

	/**
	Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	GTTxtEdtResponder(IPMUnknown* boss);
	virtual ~GTTxtEdtResponder();

	/**
	Respond() handles the file action signals when they
	are dispatched by the signal manager.  
	@param signalMgr Pointer back to the signal manager to get
	additional information about the signal.
	*/
	virtual void Respond(ISignalMgr* signalMgr);

private:
	/** Attach or detach the story observer.
	@param storyUIDRef IN the story to which the observer is attached.
	@param bAttach IN kTrue to attach, kFalse to detach.
	@return kFailure on unexpected error.
	*/
	ErrorCode attachDetachStoryObserver(UIDRef storyUIDRef, bool16 bAttach);
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(GTTxtEdtResponder, kGTTxtEdtResponderImpl)

/* Constructor
*/
GTTxtEdtResponder::GTTxtEdtResponder(IPMUnknown* boss) :
CResponder(boss)
{
}


/* Destructor
*/
GTTxtEdtResponder::~GTTxtEdtResponder(){
	TRACEFLOW(kGTTxtEdtPluginName,"GTTxtEdtResponder::~GTTxtEdtResponder - Responder deletion\n");
}

/* Respond
*/
void GTTxtEdtResponder::Respond(ISignalMgr* signalMgr)
{
	do {
		// Get the service ID from the signal manager
		ServiceID serviceTrigger = signalMgr->GetServiceID();
		// Take action based on the service ID
		switch (serviceTrigger.Get())
		{
		case kAfterNewDocSignalResponderService:
			{
				InterfacePtr<IDocumentSignalData> data(signalMgr, UseDefaultIID());
				if (data == nil)
				{
					break;
				}

				InterfacePtr<IDocument> iDocument(data->GetDocument(), UseDefaultIID());
				if (iDocument == nil)
				{
					ASSERT_FAIL("GTTxtEdtResponder::Respond - document nil in responder?");
					break;
				}

				// attach the new/delete story observer
				InterfacePtr<IObserver> iNewDeleteStoryObserver(iDocument,IID_IGTTXTEDTSTORYCREATEDELETEOBSERVER);
				if (iNewDeleteStoryObserver == nil){
					ASSERT_FAIL("GTTxtEdtResponder::Respond - document has no story create/delete observer in responder?");
					break;
				}
				iNewDeleteStoryObserver->AutoAttach();
				break;
			}
		case kAfterOpenDocSignalResponderService:
			{
				InterfacePtr<IDocumentSignalData> data(signalMgr, UseDefaultIID());
				if (data == nil)
				{
					break;
				}

				InterfacePtr<IDocument> iDocument(data->GetDocument(), UseDefaultIID());
				if (iDocument == nil)
				{
					ASSERT_FAIL("GTTxtEdtResponder::Respond - document nil in responder?");
					break;
				}

				// attach the new/delete story observer
				InterfacePtr<IObserver> iNewDeleteStoryObserver(iDocument,IID_IGTTXTEDTSTORYCREATEDELETEOBSERVER);
				if (iNewDeleteStoryObserver == nil){
					ASSERT_FAIL("GTTxtEdtResponder::Respond - document has no story create/delete observer in responder?");
					break;
				}
				iNewDeleteStoryObserver->AutoAttach();

				// attach all story observers here
				InterfacePtr<IStoryList> iStoryList(iDocument,UseDefaultIID());
				if (iStoryList == nil){
					ASSERT_FAIL("GTTxtEdtResponder::Respond - no storylist on document opening");
					break;
				}
				for (int32 loop=0;loop<iStoryList->GetUserAccessibleStoryCount();loop++){
					UIDRef nthStoryUIDRef = iStoryList->GetNthUserAccessibleStoryUID(loop);
					this->attachDetachStoryObserver(nthStoryUIDRef,kTrue /*attach*/);
				}
				break;
			}

		case kBeforeCloseDocSignalResponderService:
			{
				InterfacePtr<IDocumentSignalData> data(signalMgr, UseDefaultIID());
				if (data == nil)
				{
					break;
				}

				InterfacePtr<IDocument> iDocument(data->GetDocument(), UseDefaultIID());
				if (iDocument == nil)
				{
					ASSERT_FAIL("GTTxtEdtResponder::Respond - document nil in responder?");
					break;
				}

				// detach the new/delete story observer
				InterfacePtr<IObserver> iNewDeleteStoryObserver(iDocument,IID_IGTTXTEDTSTORYCREATEDELETEOBSERVER);
				if (iNewDeleteStoryObserver == nil){
					ASSERT_FAIL("GTTxtEdtResponder::Respond - document has no story create/delete observer in responder?");
					break;
				}
				iNewDeleteStoryObserver->AutoDetach();

				InterfacePtr<IStoryList> iStoryList(iDocument,UseDefaultIID());
				if (iStoryList == nil){
					ASSERT_FAIL("GTTxtEdtResponder::Respond - no storylist on document opening");
					break;
				}
				for (int32 loop=0;loop<iStoryList->GetUserAccessibleStoryCount();loop++){
					UIDRef nthStoryUIDRef = iStoryList->GetNthUserAccessibleStoryUID(loop);
					this->attachDetachStoryObserver(nthStoryUIDRef,kFalse /*detach*/);
				}
				break;
			}


		case kNewStorySignalResponderService:
			{
				InterfacePtr<INewStorySignalData> iNewStorySignalData(signalMgr, UseDefaultIID());
				if (iNewStorySignalData == nil)
				{
					break;
				}
				// Attach observer to new story.
				UIDRef storyRef(iNewStorySignalData->GetTextModel());

				// attach our observer
				this->attachDetachStoryObserver(storyRef,kTrue /*attach*/);

				break;
			}

		case kDeleteStoryRespService:
			{
				InterfacePtr<ICommand> deleteStoryCmd(signalMgr, UseDefaultIID());
				if (deleteStoryCmd == nil)
				{
					break;
				}
				const UIDList* itemList = deleteStoryCmd->GetItemList();

				// with the item list, make sure if the one in our document cache is present, reset the cache
				for (int32 loop=0;loop<itemList->Length();loop++){
					UIDRef storyUIDRef = itemList->GetRef(loop);

					// detach our observer
					this->attachDetachStoryObserver(storyUIDRef,kFalse /*detach*/);

					// get the document
					InterfacePtr<IDocument> iDocument(itemList->GetDataBase(),itemList->GetDataBase()->GetRootUID(),UseDefaultIID());

					if (iDocument == nil){
						ASSERT_FAIL("GTTxtEdtResponder::Respond - no document for delete story?");
						return;
					}

					InterfacePtr<IGTTxtEdtSnapshotInterface> iGTTxtEdtSnapshotInterface(iDocument,UseDefaultIID());
					if (iGTTxtEdtSnapshotInterface == nil){
						ASSERT_FAIL("GTTxtEdtResponder::Respond - no undoable interface on document");
						return;
					}
					// if we do not have a valid story in the cache, we are done.
					if (iGTTxtEdtSnapshotInterface->StoryValid() == kFalse){
						return;
					}
					UIDRef storyCached = iGTTxtEdtSnapshotInterface->GetStory();
					if (storyCached == storyUIDRef){
						iGTTxtEdtSnapshotInterface->SetStoryAndIndex(UIDRef(UIDRef::gNull),0);
					}
				}
				break;
			}

		default:
			break;
		}
	} while (kFalse);

}

/* attachDetachStoryObserver
*/
ErrorCode 
GTTxtEdtResponder::attachDetachStoryObserver(UIDRef storyUIDRef, bool16 bAttach)
{
	ErrorCode status = kFailure;
	do{
		// while we observe all stories (whether they are accessible or not), we only let accessible
		// stories affect the cache. See the observer implementation for this logic.
		InterfacePtr<IObserver> iGTTxtEdtObserver(storyUIDRef,IID_IGTTXTEDTSTORYOBSERVER);
		if (iGTTxtEdtObserver == nil){
			ASSERT_FAIL("GTTxtEdtResponder::attachDetachStoryObserver - no observer on story?");
			break;
		}
		bAttach ? iGTTxtEdtObserver->AutoAttach() :iGTTxtEdtObserver->AutoDetach();
		status = kSuccess;
	}while (kFalse);
	return status;
}

// End, GTTxtEdtResponder.cpp.



