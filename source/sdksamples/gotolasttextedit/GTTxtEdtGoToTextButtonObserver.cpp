//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtGoToTextButtonObserver.cpp $
//  
//  Owner:  Adobe Developer Technologies
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

// Interfaces
#include "ISubject.h"
#include "IActiveContext.h"
#include "IDocument.h"
#include "IGTTxtEdtUtils.h"
#include "IGTTxtEdtSnapshotInterface.h"
#include "ISelectionUtils.h"

// Includes
#include "TextID.h"
#include "RangeData.h"
#include "CObserver.h"
#include "CAlert.h"
#include "widgetid.h"
#include "GTTxtEdtID.h"


/**
Observer implementation for the GoToText button.

@ingroup gotolasttextedit
*/
class GTTxtEdtGoToTextButtonObserver : public CObserver
{
public:

	/**
	Constructor
	*/
	GTTxtEdtGoToTextButtonObserver(IPMUnknown *boss);

	/**
	Destructor
	*/	
	~GTTxtEdtGoToTextButtonObserver();

	/**
	AutoAttach is only called for registered observers
	of widgets.  This method is called by the application
	core when the widget is shown.	
	*/	
	virtual void AutoAttach();

	/**
	AutoDetach is only called for registered observers
	of widgets. Called when widget hidden.
	*/	
	virtual void AutoDetach();

	/**
	Called when the button changes state.
	*/	
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

};

/*
*/
CREATE_PMINTERFACE(GTTxtEdtGoToTextButtonObserver, kGTTxtEdtGoToTextButtonObserverImpl)


/*
*/
GTTxtEdtGoToTextButtonObserver::GTTxtEdtGoToTextButtonObserver(IPMUnknown* boss)
: CObserver(boss)
{

}


/*
*/
GTTxtEdtGoToTextButtonObserver::~GTTxtEdtGoToTextButtonObserver()
{

}


/*
*/
void GTTxtEdtGoToTextButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject != nil)
	{
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
	}
}


/*
*/
void GTTxtEdtGoToTextButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject != nil)
	{
		subject->DetachObserver(this,IID_ITRISTATECONTROLDATA);
	}
}


/*
*/
void GTTxtEdtGoToTextButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	if(theChange == kTrueStateMessage) {
		// Then the button has been activated.
		do {
			IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
			if (iActiveContext == nil){
				ASSERT_FAIL("GTTxtEdtGoToTextButtonObserver::Update - Expected an active context in goto text observer");
				break;
			}

			IDocument* iDocument = iActiveContext->GetContextDocument();
			if (iDocument == nil){
				break;
			}

			InterfacePtr<IGTTxtEdtSnapshotInterface> iGTTxtEdtSnapshotInterface(iDocument,UseDefaultIID());
			if (iGTTxtEdtSnapshotInterface == nil || !iGTTxtEdtSnapshotInterface->StoryValid()){
				break;
			}

			UIDRef storyUIDRef = iGTTxtEdtSnapshotInterface->GetStory();
			if (storyUIDRef==UIDRef::gNull || storyUIDRef.GetUID()==kInvalidUID){
				PMString noLastStory(kNoLastStoryKey);
				CAlert::InformationAlert(noLastStory);
				ASSERT_FAIL("GTTxtEdtGoToTextButtonObserver::Update - Story invalid?");
				break;
			}
			int32 storyIndex = iGTTxtEdtSnapshotInterface->GetStoryIndex();

			ISelectionManager* iSelectionManager = iActiveContext->GetContextSelection();
			if (iSelectionManager==nil){
				ASSERT_FAIL("GTTxtEdtGoToTextButtonObserver::Update - No selection manager for my context?");
				break;
			}

			Utils<IGTTxtEdtUtils>()->ActivateStory(iSelectionManager,storyUIDRef, storyIndex);

		} while(0);
	}
}
