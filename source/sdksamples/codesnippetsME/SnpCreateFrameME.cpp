//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippetsME/SnpCreateFrameME.cpp $
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
//  
//  Usage rights licenced to Adobe Inc. 1997 - 2010.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ILayoutControlData.h"
#include "IControlView.h"
#include "IHierarchy.h"
#include "ISelectionManager.h"
#include "ITextSelectionSuite.h"
#include "ITool.h"
#include "IToolBoxUtils.h"
#include "ITextModel.h"
#include "IGraphicFrameData.h"
#include "IBoolData.h"
#include "IFrameList.h"
#include "IStoryOptions.h"

// General includes:
#include "UIDList.h"
#include "SemUIID.h"

// SDK includes:
#include "SDKLayoutHelper.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

/** 
	\li How to to create frames(IGraphicFrameData) of various types on a spread 
		positioned relative to the current page,
	\li rectangle frame, text frame and various styled graphics are created,
	\li how to use ILayoutControlData to find the active spread layer and page.

  	@ingroup sdk_snippet
	@ingroup sdk_layout
	@author Seoras Ashby
	@see IGraphicFrameData
	@see ILayoutControlData
	@see SDKLayoutHelper
	@see SnpGraphicHelper
*/
class SnpCreateFrameME : public SnpRunnable
{
	public:
		/** Create a text frame.
			@param layoutControlData IN gives the active spread layer the frame will be parented on
				and the page it will be positioned on.
			@param boundsInPageCoords IN bounding box of the frame in page co-ordinates.
			@result UIDRef of created frame (IGraphicFrameData), UIDRef::gNull on failure.
		 */
		UIDRef	CreateTextFrameME(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords);

		/**	If the frame is a text frame activate the text editor and make a text selection
			to set the text caret at the start of the story, otherwise make a layout selection
			of the frame.
			@param selectionManager 
			@param frameUIDRef 
			@return kTrue on success, kFalse otherwise.
		 */
		bool16	SelectFrame(ISelectionManager* selectionManager, const UIDRef& frameUIDRef);

		 /** Activate kIBeamToolBoss if a text tool is not already active. 
            @return kTrue on success, kFalse otherwise. 
         */ 
        bool16    ActivateTextEditor(bool16 isRTL); 

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		*/
		SnpCreateFrameME();

		/** Destructor
		*/
		virtual ~SnpCreateFrameME();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if a document is open, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunLayoutTargetContext;}

};


/*
*/
UIDRef SnpCreateFrameME::CreateTextFrameME(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords)
{
	UIDRef result = UIDRef::gNull;
	SDKLayoutHelper layoutHelper;
	do {
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 numberOfColumns = parameterUtils->GetInt32("Number of columns(0 for default)", 0, 0, 40);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		K2Vector<PMString> directionChoices;
		directionChoices.push_back(PMString("Left To Right"));
		directionChoices.push_back(PMString("Right To Left"));
		int32 direction  = parameterUtils->GetChoice("Frame direction?", directionChoices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		bool16 isLeftToRight = kTrue;
		if (direction == 1) {
			isLeftToRight = kFalse;
		}

		// Parent the frame on the active spread layer.
		InterfacePtr<IHierarchy> activeSpreadLayerHierarchy(layoutControlData->QueryActiveLayer());
		ASSERT(activeSpreadLayerHierarchy != nil);
		if (activeSpreadLayerHierarchy == nil) {
			break;
		}
		UIDRef parentUIDRef = ::GetUIDRef(activeSpreadLayerHierarchy);

		// Transform the bounds of the frame from page co-ordinates
		// into the parent co-ordinates, i.e. the spread.
		ASSERT(layoutControlData->GetPage() != kInvalidUID);
		if (layoutControlData->GetPage() == kInvalidUID) {
			break;
		}
		UIDRef pageUIDRef(parentUIDRef.GetDataBase(), layoutControlData->GetPage());
		PMRect boundsInParentCoords = layoutHelper.PageToSpread(pageUIDRef, boundsInPageCoords);

		// Create the frame.
		result = layoutHelper.CreateTextFrame(parentUIDRef, boundsInParentCoords, numberOfColumns, kFalse, nil, isLeftToRight);
	} while(false);
	return result;
}


/*
*/
bool16 SnpCreateFrameME::SelectFrame(ISelectionManager* selectionManager, const UIDRef& frameUIDRef)
{
	bool16 result = kFalse;
	do {
		// If there's no selection manager available give up.
		if (selectionManager == nil) {
			break;
		}

		// Deselect everything.
		selectionManager->DeselectAll(nil); // deselect every active CSB
			
		// Make a text selection.
		// Find the story associated with the frame.
		SDKLayoutHelper layoutHelper;
		InterfacePtr<IGraphicFrameData> graphicFrameData(frameUIDRef, UseDefaultIID());
		ASSERT(graphicFrameData);
		if (!graphicFrameData) {
			break;
		}
		UIDRef storyUIDRef = layoutHelper.GetTextModelRef(graphicFrameData);

		// Determine if the given text frame is ME.
		InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());
		if (!textModel) {
			break;
		}
        InterfacePtr<IStoryOptions> storyOptions(textModel, UseDefaultIID()); 
        bool16 isRTL = storyOptions && storyOptions->IsRightToLeft(); 
		
		// Activate the text editor.
		this->ActivateTextEditor(isRTL);

		// Make a text selection to set the text caret blinking at the start of the story.
		InterfacePtr<ITextSelectionSuite> textSelectionSuite(selectionManager, UseDefaultIID());
		if (!textSelectionSuite) {
			break;
		}
		result = textSelectionSuite->SetTextSelection(storyUIDRef, 
			RangeData(0, RangeData::kLeanForward),
			Selection::kScrollIntoView, 
			nil); // scrollTo
	} while(false);
	return result;
}

/*
*/
bool16 SnpCreateFrameME::ActivateTextEditor(bool16 isRTL)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITool> activeTool(Utils<IToolBoxUtils>()->QueryActiveTool());
		if (activeTool->IsTextTool()) {
			// A text tool is already active so we've nothing to do.
			result = kTrue;
			break;
		}
		InterfacePtr<ITool> iBeamTool(Utils<IToolBoxUtils>()->QueryTool(isRTL ? kMEToolBoss : kIBeamToolBoss));
		ASSERT(iBeamTool);
		if (!iBeamTool) {
			break;
		}
		result = Utils<IToolBoxUtils>()->SetActiveTool(iBeamTool);
	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/* Constructor
*/
SnpCreateFrameME::SnpCreateFrameME() : SnpRunnable("CreateFrameME")
{
	this->SetDescription("creates ME Text Frames");
	this->SetPreconditions("document open");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor
*/
SnpCreateFrameME::~SnpCreateFrameME()
{
}

/*
*/
bool16 SnpCreateFrameME::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	// ILayoutControlData is required to determine the active spread layer and the current page.
	InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
	if (layoutControlData != nil) {
		result = kTrue;
	}
	return result;
}

/* 
*/
ErrorCode SnpCreateFrameME::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		// ILayoutControlData is required to determine the active spread layer and the current page.
		InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		if (layoutControlData == nil) {
			SNIPLOG("Please open a document and try again.");
			break;
		}


		// Create the chosen type of frame.
		UIDRef frameUIDRef = UIDRef::gNull;
		frameUIDRef = this->CreateTextFrameME(layoutControlData, PMRect(100.0, 0.0, 200.0, 100.0));

		// Check a frame was created.
		if (frameUIDRef == UIDRef::gNull) {
			break;
		}

		// Select the frame.
		if (!this->SelectFrame(runnableContext->GetActiveContext()->GetContextSelection(), frameUIDRef)) {
			break;
		}

		status = kSuccess;

	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
SnpCreateFrameME instanceSnpCreateFrameME;

//End, SnpCreateFrameME.cpp
