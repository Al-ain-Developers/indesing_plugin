//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/typekitinspector/TKITreeWidgetObserver.cpp $
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
#include "TKIID.h"
#include "CObserver.h"
#include "ISelectionManager.h"
#include "ISubject.h"
#include "ITreeViewController.h"
#include "IActiveContext.h"
#include "IDocument.h"
#include "TKITreeNodeID.h"
#include "RangeData.h"
#include "ITextSelectionSuite.h"
#include "K2Vector.tpp" // For NodeIDList to compile

class TKITreeWidgetObserver : public CObserver
{
public:
	TKITreeWidgetObserver( IPMUnknown* boss );
	virtual ~TKITreeWidgetObserver() ;
	void AutoAttach();
	void AutoDetach();
	void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
	ErrorCode SelectText(InDesign::TextRange textRange);
};

CREATE_PMINTERFACE(TKITreeWidgetObserver, kTKITreeWidgetObserverImpl)

TKITreeWidgetObserver::TKITreeWidgetObserver( IPMUnknown* boss ) : CObserver( boss )
{
}

TKITreeWidgetObserver::~TKITreeWidgetObserver()
{
}

void TKITreeWidgetObserver::AutoAttach()
{
	InterfacePtr<ISubject> subj(this, UseDefaultIID()); 
	subj->AttachObserver(this, IID_ITREEVIEWCONTROLLER);
}

void TKITreeWidgetObserver::AutoDetach()
{
	InterfacePtr<ISubject> subj(this, UseDefaultIID()); 
	subj->DetachObserver(this, IID_ITREEVIEWCONTROLLER);
}

/**
  * Responds to tree widget node selection by getting the selected node,
  * getting the text range data out of it, and then selecting the text range
  * in the document.
  */
void TKITreeWidgetObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	do
	{
		if (theChange.Get() == kListSelectionChangedMessage) 
		{
			InterfacePtr<ITreeViewController> treeController(this, UseDefaultIID());
			if (treeController == nil)
			{
				ASSERT_FAIL("Invalid treeController");
				break;
			}

			NodeIDList selectedItems;
			treeController->GetSelectedItems(selectedItems);
			int numberOfSelectedItems = selectedItems.size();
			if (numberOfSelectedItems == 0 || numberOfSelectedItems > 1)
			{
				// this sample does not support multiple selection
				break;
			}

			K2Vector<NodeID>::const_iterator iter = selectedItems.begin();
			const TKITreeNodeID* node = static_cast<const TKITreeNodeID*>(iter->Get());
			
			/*
			// Optional - you could do something with the node text too..
			PMString nodeString = node->GetString();
			nodeString.SetTranslatable(kFalse);
			CAlert::InformationAlert(nodeString);
			*/

			this->SelectText(node->GetTextRange());
		}

	} while(kFalse);
}

ErrorCode TKITreeWidgetObserver::SelectText(InDesign::TextRange textRange)
{
	ErrorCode status = kFailure;

	do
	{
		ISelectionManager* selectionManager = GetExecutionContextSession()->GetActiveContext()->GetContextSelection();
		if (selectionManager == nil)
		{
			ASSERT_FAIL("Unable to get ISelectionManager");
			break;
		}
		
		if (!textRange.IsValid()) 
		{ 
			ASSERT_FAIL("Text range is invalid");
			break;
		}

		// select the text
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		UIDRef storyRef(::GetDataBase(textModel), ::GetUID(textModel));

		// clear any existing selection
		if (selectionManager->SelectionExists(kInvalidClass/*any CSB*/, ISelectionManager::kAnySelection)) 
		{
			selectionManager->DeselectAll(nil);
		}

		InterfacePtr<ITextSelectionSuite> textSelectionSuite(selectionManager, UseDefaultIID());
		if (textSelectionSuite == nil)
		{
			ASSERT_FAIL("Selection manager doesn't support text selection.");
			break;
		}

		Selection::ScrollChoice doScroll = Selection::kScrollIntoView;
		const RangeData* scrollTo = nil;
		if (!textSelectionSuite->SetTextSelection(storyRef, textRange.GetRange(), doScroll, scrollTo)) 
		{
			ASSERT_FAIL("ITxtSelectionSuite::SetTextSelection failed");
			break;
		}

		status = kSuccess;

	} while(kFalse);

	return status;
}
