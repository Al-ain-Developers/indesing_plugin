//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/typekitinspector/TKIPanelWidgetObserver.cpp $
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
#include "IControlView.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "IDropDownListController.h"
#include "CObserver.h"
#include "IBooleanControlData.h"
#include "CreateObject.h"
#include "StreamUtil.h"
#include "ErrorUtils.h"
#include "IActiveContext.h"
#include "IDocument.h"
#include "IDocumentFontUsage.h"
#include "IFontFamily.h"
#include "TKITreeNodeID.h"
#include "IStoryList.h"
#include "ITextModel.h"
#include "TextRange.h"
#include "TextAttributeRunIterator.h"
#include "ITextAttrUID.h"
#include "IListControlData.h"
#include "IComposeScanner.h"
#include "RangeData.h"
#include <map>
#include "ITKIStringListData.h"
#include "ITreeViewMgr.h"

class TKIPanelWidgetObserver : public CObserver
{
public:
	TKIPanelWidgetObserver( IPMUnknown* boss );
	virtual ~TKIPanelWidgetObserver() ;
	void AutoAttach();
	void AutoDetach();

	/**
		Update is called for all registered observers, and is
		the method through which changes are broadcast. 
		@param theChange this is specified by the agent of change; it can be the class ID of the agent,
		or it may be some specialised message ID.
		@param theSubject this provides a reference to the object which has changed; in this case, the
		widget boss objects that are being observed.
		@param protocol the protocol along which the change occurred.
		@param changedBy this can be used to provide additional information about the change or a reference
		to the boss object that caused the change.
	*/
	void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	/** Detach this observer from the given widget.
		@param panelControlData refers to the panel that contains the widget
		@param widgetID gives the subject being observed
		@param interfaceID gives the protocol being observed
	 */
	void DetachWidget(const InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);

private:
	/** Attach this observer to the given widget.
		@param panelControlData refers to the panel that contains the widget
		@param widgetID gives the subject to be observed
		@param interfaceID gives the protocol to be observed
	 */
	void AttachWidget(const InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);

	/** Initialise the dropdown that displays the names of fonts.
		@param panelControlData refers to the panel that contains the widget
	 */
	void PopulateFonts(const InterfacePtr<IPanelControlData>& panelControlData);

	void HandleGetFontsButton(const ClassID& theChange);

	void FindTextWithFont(UID font);

	InDesign::TextRange FindFontInTextRange(InDesign::TextRange textRange, UID font);

	void HandleFontSelection();

	std::map <PMString,UID> fonts;
};

CREATE_PMINTERFACE(TKIPanelWidgetObserver, kTKIPanelWidgetObserverImpl)

TKIPanelWidgetObserver::TKIPanelWidgetObserver( IPMUnknown* boss ) : CObserver( boss )
{
}

TKIPanelWidgetObserver::~TKIPanelWidgetObserver()
{
}

void TKIPanelWidgetObserver::AutoAttach()
{
	do
	{
		// Initialise widget state.
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("AutoAttach() invalid panelControlData");
			break;
		}

		// Attach widget observers
		this->AttachWidget(panelControlData, kTKIGetFontsButtonWidgetID, IBooleanControlData::kDefaultIID);
		this->AttachWidget(panelControlData, kTKIRefreshFontsButtonWidgetID, IBooleanControlData::kDefaultIID);
		this->AttachWidget(panelControlData, kTKIUsageSampleWidgetID, ITextControlData::kDefaultIID);
		
	} while(kFalse);
}

void TKIPanelWidgetObserver::AutoDetach()
{
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("AutoDetach() invalid panelControlData");
			break;
		}	

		this->DetachWidget(panelControlData, kTKIGetFontsButtonWidgetID, IBooleanControlData::kDefaultIID);
		this->DetachWidget(panelControlData, kTKIRefreshFontsButtonWidgetID, IBooleanControlData::kDefaultIID);
		this->DetachWidget(panelControlData, kTKIUsageSampleWidgetID, ITextControlData::kDefaultIID);

	} while(kFalse);
}

void TKIPanelWidgetObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	do 
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (controlView == nil)
		{
			break;
		}

		WidgetID widgetID = controlView->GetWidgetID();
		switch (widgetID.Get())
		{
			case kTKIGetFontsButtonWidgetID:
				this->HandleGetFontsButton(theChange);
				break;
			case kTKIRefreshFontsButtonWidgetID:
				this->HandleGetFontsButton(theChange);
				break;
			case kTKIUsageSampleWidgetID:
				this->HandleFontSelection();
				break;
			default:
				ASSERT_FAIL(FORMAT_ARGS("Unknown WidgetID 0x%x", widgetID.Get()));
				break;
		}

	} while(kFalse);
}

void TKIPanelWidgetObserver::AttachWidget(const InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	do
	{
		IControlView* controlView = panelControlData->FindWidget(widgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid");
			break;
		}

		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());
		if (subject == nil)
		{
			ASSERT_FAIL("subject invalid");
			break;
		}
		subject->AttachObserver(this, interfaceID);

	} while(kFalse);
}

void TKIPanelWidgetObserver::DetachWidget(const InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	do
	{
		IControlView* controlView = panelControlData->FindWidget(widgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid.");
			break;
		}

		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());
		if (subject == nil)
		{
			ASSERT_FAIL("subject invalid");
			break;
		}
		subject->DetachObserver(this, interfaceID);

	} while(kFalse);
}

/**
  * Gets the currently selected font in the dropdown and
  * kicks off chain of method calls which finds any text in 
  * the document which uses the selected font.
  */
void TKIPanelWidgetObserver::HandleFontSelection()
{
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			break;
		}

		IControlView* controlView = panelControlData->FindWidget(kTKIUsageSampleWidgetID);
		if (controlView == nil)
		{
			break;
		}

		InterfacePtr<ITextControlData> textControlData(controlView, UseDefaultIID());
		if (textControlData == nil)
		{
			break;
		}

		PMString selectedFontName = textControlData->GetString();
		UID font = fonts.find(selectedFontName)->second;
		this->FindTextWithFont(font);

	} while(kFalse);
}

void TKIPanelWidgetObserver::PopulateFonts(const InterfacePtr<IPanelControlData>& panelControlData)
{
	do
	{
		IControlView* controlView = panelControlData->FindWidget(kTKIUsageSampleWidgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid.");
			break;
		}

		InterfacePtr<IStringListControlData> stringListControlData(controlView, UseDefaultIID());
		if (stringListControlData == nil)
		{
			ASSERT_FAIL("invalid stringListControlData");
			break;
		}

		// Clear the drop down list.
		stringListControlData->Clear(kFalse, kFalse);

		// clear the map
		fonts.clear();

		// get font names used in current document
		IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
		IDocument* iDocument = context->GetContextDocument();
		if (iDocument == nil)
		{
			break;
		}

		InterfacePtr<IDocumentFontUsage> iDocumentFontUsage(iDocument, UseDefaultIID());
		if (iDocumentFontUsage == nil) 
		{
			break;
		}

		iDocumentFontUsage->UpdateFontList();
		int32 numUsedFonts = iDocumentFontUsage->GetNumUsedFonts();

		for (int32 f = 0; f < numUsedFonts; f++)
		{
			UID font = iDocumentFontUsage->GetNthUsedFontUID(f);
			InterfacePtr<IFontFamily> iFontFamily(::GetDataBase(iDocument), font, UseDefaultIID());
			if (iFontFamily == nil)
			{
				break;
			}

			PMString fontStyle = iDocumentFontUsage->GetNthUsedFontFaceString(f);
			bool16 isTypekitFont = iFontFamily->IsTypekitFont(fontStyle);
			if (isTypekitFont == kTrue)
			{
				PMString family = iFontFamily->GetFamilyName();

				stringListControlData->AddString(family, IStringListControlData::kEnd, kFalse, kFalse);

				// add to fonts map
				fonts[family] = font;
			}
		}

		controlView->Invalidate();

		// enable/disable the fonts combo accordingly
		if (numUsedFonts > 0)
		{
			controlView->Enable(kTrue);
		}
		else
		{
			controlView->Enable(kFalse);
		}

	} while(kFalse);
}

void TKIPanelWidgetObserver::FindTextWithFont(UID font)
{
	// Get the tree widget and its associated data model (ITKIStringListData)
	InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
	if (panelControlData == nil)
	{
		ASSERT_FAIL("panelControlData invalid.");
		return;
	}

	IControlView* controlView = panelControlData->FindWidget(kTKITextListWidgetID);
	if (controlView == nil)
	{
		ASSERT_FAIL("controlView invalid.");
		return;
	}

	InterfacePtr<ITreeViewMgr> treeMgr(controlView, UseDefaultIID());
	InterfacePtr<ITKIStringListData> iListData(controlView, IID_ITKISTRINGLISTDATA);
	K2Vector<NodeID> list = iListData->GetStringList();
	list.clear(); // empty the tree data model

	// Get the list of stories in this document so we can iterate them
	// and find text which uses the font we are interested in
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	IDocument* document = context->GetContextDocument();
	InterfacePtr<IStoryList> storyList(document, UseDefaultIID());
	if (storyList == nil) 
	{
		return;
	}

	// Iterate stories in document and create a text range containing all the text in each..
	K2Vector<InDesign::TextRange> textRanges;
	K2Vector<NodeID> nodes;
	for (int32 i = 0; i < storyList->GetAllTextModelCount(); i++)
	{
		TextStory_StoryAccess storyAccess = storyList->GetNthTextModelAccess(i);
	
		if (storyAccess == kUserAccessible) 
		{
			// Note that not all stories in a document are for 
			// display in text frames.
		
			// Get the text model of the story.
			UIDRef storyUIDRef = storyList->GetNthTextModelUID(i);
			InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());
			if (textModel == nil) 
			{
				return;
			}

			int32 totalLength = textModel->TotalLength();

			// get text range for all text in this story
			InDesign::TextRange range(textModel, 0, textModel->TotalLength());
			if (range.IsValid() == kFalse) 
			{
				return;
			}

			//RangeData rangeData = this->FindFontInTextRange(range, font);
			InDesign::TextRange rangeData = this->FindFontInTextRange(range, font);
			if (rangeData.Length() > 0)
			{
				// get the text that uses the font we are interested in...
				WideString wideText;
				InterfacePtr<const IComposeScanner> pScanner(range.QueryModel(), UseDefaultIID());
				pScanner->CopyText(rangeData.GetRange(), &wideText);

				PMString text = PMString(wideText);
				text.SetTranslatable(kFalse);

				NodeID newNode = TKITreeNodeID::Create(text, rangeData);

				// add the text to the list data
				list.insert(list.end(), newNode); 
				
				// add a node to the list tree widget for the string
				nodes.push_back(newNode);
			}
		}
	}

	// reset/refresh the tree data model and the tree widget
	iListData->SetStringList(list);
	treeMgr->NodesAdded(nodes);
	treeMgr->ChangeRoot(kTrue);
}

InDesign::TextRange TKIPanelWidgetObserver::FindFontInTextRange(InDesign::TextRange textRange, UID font)
{
	InDesign::TextRange match;

	do 
	{
		// Create a K2Vector containing the ClassIDs of the
		// text attributes we want to find
		K2Vector<ClassID> attributeClasses;
		attributeClasses.push_back(kTextAttrFontUIDBoss);

		// build vector containing the text ranges (only one in this case)
		K2Vector<InDesign::TextRange> textRanges;
		textRanges.push_back(textRange);

		// Construct the iterator.
		TextAttributeRunIterator runIter(textRanges.begin(), textRanges.end(), attributeClasses.begin(), attributeClasses.end());

		// Iterate the range of text and check if any of the fonts in use
		// match the UID of the font we are looking for
		while (runIter)
		{
			InterfacePtr<const ITextAttrUID> family(static_cast<const ITextAttrUID*>(runIter->QueryByClassID(kTextAttrFontUIDBoss, ITextAttrUID::kDefaultIID)));
		
			if (family->Get() == font)
			{
				// this text range is using the font we are looking for..
				//data = runIter.GetRunRange();
				match = InDesign::TextRange(textRange.QueryModel(), runIter.GetRunRange());
			}

			++runIter;
		}

	} while (kFalse);

	return match;
}

void TKIPanelWidgetObserver::HandleGetFontsButton(const ClassID& theChange)
{
	if (theChange == kTrueStateMessage)
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("invalid panelControlData");
			return;
		}

		this->PopulateFonts(panelControlData);
	}
}