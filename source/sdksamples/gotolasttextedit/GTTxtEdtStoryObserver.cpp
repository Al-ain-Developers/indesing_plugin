//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtStoryObserver.cpp $
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
#include "ISubject.h"
#include "IControlView.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "ISelectionUtils.h"
#include "ISelectionManager.h"
#include "IGenericTextSelectionSuite.h"
#include "IObjectModel.h"
#include "IControllingUnknown.h"
#include "ITextFocus.h"
#include "ITextFocusManager.h"
#include "ITextModel.h"
#include "IInvalHandler.h"
#include "IStoryList.h"

// General includes:
#include "NoteID.h"
#include "TextEditorID.h"
#include "TextID.h"
#include "InCopySharedID.h"
#include "CObserver.h"
#include "Utils.h"
#include "InCopyCoreID.h"
#include "OpenPlaceID.h" // kEndPlaceCmdBoss
#include "UIDList.h"
#include "RangeData.h"

// Project includes:
#include "IGTTxtEdtSnapshotInterface.h"
#include "GTTxtEdtID.h"

/**
Implements the IObserver interface using the CObserver helper class 
and listens along the IID_ITEXTMODEL protocol for changes in model. 
Handles AutoAttach, AutoDetach, and Update messages.

@ingroup gotolasttextedit
*/

class GTTxtEdtStoryObserver : public CObserver
{
public:
	/**
	Constructor.
	@param boss interface ptr from boss object on which interface is aggregated.
	*/
	GTTxtEdtStoryObserver(IPMUnknown* boss);

	/**
	Destructor.
	*/		
	~GTTxtEdtStoryObserver() {};

	/** Attaches the observer to the story.
	*/
	virtual void AutoAttach();

	/** Detaches the observer from the story/
	*/
	virtual void AutoDetach();

	/** All text edits are tracked through update. Updates the snapshot interface with the value of the current text edit story and index.
	@param theChange IN the change.
	@param theSubject IN the story that was being updated.
	@param protocol IN the channel the update signal is sent on.
	@param changedBy IN the agent that caused the update to be invoked.

	*/
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

};

/*
*/
CREATE_PMINTERFACE(GTTxtEdtStoryObserver, kGTTxtEdtStoryObserverImpl)


/* Constructor
*/
GTTxtEdtStoryObserver::GTTxtEdtStoryObserver(IPMUnknown* boss)
: CObserver(boss)
{
}


/* AutoAttach
*/
void GTTxtEdtStoryObserver::AutoAttach()
{
	do
	{
		InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
		if (subject != nil)
		{
			if (subject->IsAttached(ISubject::kRegularAttachment,this, IID_ITEXTMODEL,IID_IGTTXTEDTSTORYOBSERVER) == kFalse)
			{
				subject->AttachObserver(ISubject::kRegularAttachment,this, IID_ITEXTMODEL,IID_IGTTXTEDTSTORYOBSERVER);
			}
		}
	} while(kFalse);
}


/* AutoDetach
*/
void GTTxtEdtStoryObserver::AutoDetach()
{
	do
	{
		InterfacePtr<ISubject> subject(this, UseDefaultIID());
		if (subject != nil)
		{
			if (subject->IsAttached(ISubject::kRegularAttachment,this, IID_ITEXTMODEL,IID_IGTTXTEDTSTORYOBSERVER) == kTrue)
			{
				subject->DetachObserver(ISubject::kRegularAttachment,this, IID_ITEXTMODEL,IID_IGTTXTEDTSTORYOBSERVER);
			}
		}

	} while(kFalse);
}


/* Update
*/
void GTTxtEdtStoryObserver::Update(
								   const ClassID& theChange, 
								   ISubject* theSubject, 
								   const PMIID& protocol, 
								   void* changedBy)
{
	if (protocol == IID_ITEXTMODEL)
	{
		InterfacePtr<IObjectModel> iObjectModel(GetExecutionContextSession(), UseDefaultIID());
		TRACEFLOW(kGTTxtEdtPluginName,"GTTxtEdtStoryObserver::Update, pName %s cName %s subject %s\n", iObjectModel->GetIDName(theChange),iObjectModel->GetIDName(protocol),iObjectModel->GetIDName(::GetClass(theSubject)));
		ClassID changeClassID = theChange.Get();

		UIDRef storyUIDRef(::GetUIDRef(this));

		InterfacePtr<IDocument>	iDocument(storyUIDRef.GetDataBase(), storyUIDRef.GetDataBase()->GetRootUID(), UseDefaultIID());
		if (iDocument == nil){
			ASSERT_FAIL("GTTxtEdtStoryObserver::Update - no document associated with story?");
			return;
		}
		do {
			if (changeClassID == kEndPlaceCmdBoss){
				// if this model is subject to a place, and we are currently the cached
				// story, we need to reset the cache (last edited makes no sense in this condition)
				InterfacePtr<IGTTxtEdtSnapshotInterface> iGTTxtEdtSnapshotInterface(iDocument,UseDefaultIID());
				if (iGTTxtEdtSnapshotInterface == nil){
					break;
				}
				UIDRef currentStoryUIDRef = iGTTxtEdtSnapshotInterface->GetStory();
				if (currentStoryUIDRef == storyUIDRef){
					iGTTxtEdtSnapshotInterface->SetStoryAndIndex(UIDRef(UIDRef::gNull),0);
				}

			}
			//Observe changes to these cmd bosses for changes to text.
			else if (changeClassID == kDeleteTextCmdBoss ||
				changeClassID == kInsertTextCmdBoss ||
				changeClassID == kReplaceTextCmdBoss ||
				changeClassID == kMultiReplaceTextCmdBoss)
			{
				TextIndex focusStart = kInvalidTextIndex;

				InterfacePtr<IStoryList> iStoryList(iDocument,UseDefaultIID());
				if (iStoryList == nil){
					ASSERT_FAIL("");
					break;
				}

				// make sure it is a user accessible story before we update the cache
				int32 storyIndex = iStoryList->GetUserAccessibleStoryIndex(storyUIDRef.GetUID());
				// only update the UDI if the story is accessible
				if (storyIndex == -1){
					break; // this is not an error condition.
				}

				InterfacePtr<ITextModel> iTextModel(storyUIDRef,UseDefaultIID());
				if (iTextModel == nil){
					ASSERT_FAIL("GTTxtEdtStoryObserver::Update - no story for change?");
					break;
				}

				InterfacePtr<ITextFocusManager> iTextFocusManager(iTextModel,UseDefaultIID());
				if (iTextFocusManager == nil){
					ASSERT_FAIL("GTTxtEdtStoryObserver::Update - no text focus manager for focus?");
					break;
				}

				// with the focus manager, we need to find the focus that is for the text selection
				// ust in case more than a single focus exists
				ITextFocus* iTextFocus=nil;
				for (int32 loop = 0;loop < iTextFocusManager->GetFocusCount();loop++){
					InterfacePtr<ITextFocus > nthTextFocus(iTextFocusManager->QueryNthFocus(loop));
					if (::GetClass(nthTextFocus) == kTextSelectionFocusBoss){
						iTextFocus = nthTextFocus;
					}
				}
				InterfacePtr<ITextFocus> iSelectionTextFocus(iTextFocus, UseDefaultIID());
				if (iSelectionTextFocus != nil){
					focusStart = iSelectionTextFocus->GetStart(nil);
				}


				InterfacePtr<IGTTxtEdtSnapshotInterface> iGTTxtEdtSnapshotInterface(iDocument,UseDefaultIID());
				if (iGTTxtEdtSnapshotInterface == nil || focusStart == kInvalidTextIndex){
					break;
				}
				iGTTxtEdtSnapshotInterface->SetStoryAndIndex(storyUIDRef,focusStart);
				TRACEFLOW(kGTTxtEdtPluginName,"Text story observer range == %d\n", focusStart);
			}
		}while (kFalse);
	}
}

//	End GTTxtEdtStoryObserver.cpp
