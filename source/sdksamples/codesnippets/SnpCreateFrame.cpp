//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateFrame.cpp $
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
#include "IActiveContext.h"
#include "ILayoutControlData.h"
#include "IControlView.h"
#include "ILayoutTarget.h"
#include "IHierarchy.h"
#include "IDocFileHandler.h"
#include "ISelectionManager.h"
#include "ILayoutSelectionSuite.h"
#include "ITextSelectionSuite.h"
#include "ITool.h"
#include "IToolBoxUtils.h"
#include "ITextModel.h"
#include "IPageItemTypeUtils.h"
#include "IGraphicFrameData.h"

// General includes:
#include "Utils.h"
#include "UIDRef.h"
#include "UIDList.h"
#include "InstStrokeFillID.h" // for kFancyCornerBoss
#include "RangeData.h"
#include "TextEditorID.h"	// kIBeamToolBoss

// SDK includes:
#include "SDKLayoutHelper.h"
#include "SnpGraphicHelper.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

#include "SnpCreateFrame.h"

/*
*/
UIDRef SnpCreateFrame::CreateRectangleFrame(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords)
{
	UIDRef result = UIDRef::gNull;
	SDKLayoutHelper layoutHelper;
	do {
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
		result = layoutHelper.CreateRectangleFrame(parentUIDRef, boundsInParentCoords);
	} while(false);
	return result;
}


/*
*/
UIDRef SnpCreateFrame::CreateTextFrame(ILayoutControlData* layoutControlData,
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
		K2Vector<PMString> orientationChoices;
		orientationChoices.push_back(PMString("horizontal"));
		orientationChoices.push_back(PMString("vertical"));
		int32 orientation  = parameterUtils->GetChoice("Frame orientation?", orientationChoices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		bool16 verticalFrame = kFalse;
		if (orientation == 1) {
			verticalFrame = kTrue;
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
		result = layoutHelper.CreateTextFrame(parentUIDRef, boundsInParentCoords, numberOfColumns, verticalFrame);
	} while(false);
	return result;
}


/*
*/
UIDRef SnpCreateFrame::CreateRectangleGraphic(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords)
{
	UIDRef result = UIDRef::gNull;
	SDKLayoutHelper layoutHelper;
	do {
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
		result = layoutHelper.CreateRectangleGraphic(parentUIDRef, boundsInParentCoords);
	} while(false);
	return result;
}


/*
*/
UIDRef SnpCreateFrame::CreateSquareInFancyGraphic(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords)
{
	UIDRef result = UIDRef::gNull;
	SDKLayoutHelper layoutHelper;
	do {
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

		// Create a graphic.
		UIDRef frameUIDRef = layoutHelper.CreateRectangleGraphic(parentUIDRef, boundsInParentCoords);
		if (frameUIDRef == UIDRef::gNull) {
			break;
		}

		// Apply some attributes to make it a fancy graphic.
		SnpGraphicHelper graphicHelper(frameUIDRef);
		graphicHelper.AddStrokeWeight(4.0);
		graphicHelper.AddStrokeRendering(graphicHelper.GetNamedSwatch(PMString("Black"), frameUIDRef.GetDataBase()));
		graphicHelper.AddFillRendering(graphicHelper.GetNamedSwatch(PMString("C=100 M=0 Y=0 K=0"), frameUIDRef.GetDataBase()));
		graphicHelper.AddCornerImplementation(kFancyCornerBoss);
		graphicHelper.ApplyAttributes();

		// Create a filled square as a child of the fancy graphic.
		// The top left of the square will be positioned at the origin
		// of the fancy looking graphic's co-ordinate space.
		PMRect square2BoundingBox(0.0, 0.0, 25.0, 25.0);
		UIDRef square2UIDRef = layoutHelper.CreateRectangleGraphic(frameUIDRef, square2BoundingBox);
		if (square2UIDRef == UIDRef::gNull) {
			break;
		}
		graphicHelper.Reset(square2UIDRef);
		graphicHelper.AddFillRendering(graphicHelper.GetNamedSwatch(PMString("C=0 M=100 Y=0 K=0"), frameUIDRef.GetDataBase()));
		graphicHelper.ApplyAttributes();

		result = frameUIDRef;
	} while(false);
	return result;
}


/*
*/
UIDRef SnpCreateFrame::CreateArrowGraphic(ILayoutControlData* layoutControlData,
										const PMRect& boundsInPageCoords)
{
	UIDRef result = UIDRef::gNull;
	SDKLayoutHelper layoutHelper;
	do {
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

		// Create a series of path segments to describe the spline.
		PMRect boundingBoxInnerCoords (0.0, 0.0, 100.0, 100.0);
		PMPathPointList pathPointList;
		pathPointList.push_back(PMPathPoint(PMPoint(0.0, 0.0)));
		pathPointList.push_back(PMPathPoint(PMPoint(100.0, 0.0)));
		pathPointList.push_back(PMPathPoint(PMPoint(100.0, 70.0)));
		pathPointList.push_back(PMPathPoint(kCS,PMPoint(100.0,80.0), PMPoint(90.0, 90.0), PMPoint(80.0,100.0)));
		pathPointList.push_back(PMPathPoint(PMPoint(40.0, 100.0)));

		// Create the spline.
		UIDRef frameUIDRef = layoutHelper.CreateSplineGraphic(parentUIDRef, boundsInParentCoords, boundingBoxInnerCoords, pathPointList, kFalse /*not a closed path*/);
		ASSERT(frameUIDRef != UIDRef(nil, kInvalidUID));
		if (frameUIDRef == UIDRef::gNull) {
			break;
		}

		// Apply some graphic attributes to specify how the path should be drawn,
		SnpGraphicHelper graphicHelper(frameUIDRef);
		graphicHelper.AddStrokeWeight(10.0);
		graphicHelper.AddStrokeRendering(graphicHelper.GetNamedSwatch(PMString("Black"), frameUIDRef.GetDataBase()));
		graphicHelper.AddLineImplementation(kDashedPathStrokerBoss);
		K2Vector<PMReal> dashAndGapValues;
		const PMReal dash0(32.0);
		const PMReal gap0(16.0);
		dashAndGapValues.push_back(dash0);
		dashAndGapValues.push_back(gap0);
		graphicHelper.AddDashedValues(dashAndGapValues);
		graphicHelper.AddJoinType(SnpGraphicHelper::kJTRound);
		graphicHelper.AddLineCap(SnpGraphicHelper::kLCRound);
		graphicHelper.AddLineEndEndImplementation(kBarbedArrowHeadBoss);
		graphicHelper.ApplyAttributes();

		result = frameUIDRef;
	} while(false);
	return result;
}

/*
*/
bool16 SnpCreateFrame::SelectFrame(ISelectionManager* selectionManager, const UIDRef& frameUIDRef)
{
	bool16 result = kFalse;
	do {
		// If there's no selection manager available give up.
		if (selectionManager == nil) {
			break;
		}

		// Deselect everything.
		selectionManager->DeselectAll(nil); // deselect every active CSB
			

		// Make a text or a layout selection for the given frame.
		if (Utils<IPageItemTypeUtils>()->IsTextFrame(frameUIDRef)) {
			// Make a text selection.

			// Activate the text editor.
			this->ActivateTextEditor();

			// Find the story associated with the frame.
			SDKLayoutHelper layoutHelper;
			InterfacePtr<IGraphicFrameData> graphicFrameData(frameUIDRef, UseDefaultIID());
			ASSERT(graphicFrameData);
			if (!graphicFrameData) {
				break;
			}
			UIDRef storyUIDRef = layoutHelper.GetTextModelRef(graphicFrameData);

			// Make a text selection to set the text caret blinking at the start of the story.
			InterfacePtr<ITextSelectionSuite> textSelectionSuite(selectionManager, UseDefaultIID());
			if (!textSelectionSuite) {
				break;
			}
			result = textSelectionSuite->SetTextSelection(storyUIDRef, 
				RangeData(0, RangeData::kLeanForward),
				Selection::kScrollIntoView, 
				nil); // scrollTo
		}
		else {
			// Make a layout selection.
			InterfacePtr<ILayoutSelectionSuite> layoutSelectionSuite(selectionManager, UseDefaultIID());
			if (!layoutSelectionSuite) {
				break;
			}
			layoutSelectionSuite->SelectPageItems(UIDList(frameUIDRef), 
				Selection::kReplace,  Selection::kDontScrollLayoutSelection);
				
			result = kTrue;
		}
	} while(false);
	return result;
}

/*
*/
bool16 SnpCreateFrame::ActivateTextEditor()
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITool> activeTool(Utils<IToolBoxUtils>()->QueryActiveTool());
		if (activeTool->IsTextTool()) {
			// A text tool is already active so we've nothing to do.
			result = kTrue;
			break;
		}
		InterfacePtr<ITool> iBeamTool(Utils<IToolBoxUtils>()->QueryTool(kIBeamToolBoss));
		ASSERT(iBeamTool);
		if (!iBeamTool) {
			break;
		}
		result = Utils<IToolBoxUtils>()->SetActiveTool(iBeamTool);
	} while(false);
	return result;
}


// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpCreateFrame available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerCreateFrame : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerCreateFrame();

		/** Destructor.
		 */
		virtual			~_SnpRunnerCreateFrame();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/** Run my unit test
		*/
		ErrorCode RunUnitTest(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};
/* Constructor
*/
_SnpRunnerCreateFrame::_SnpRunnerCreateFrame() : SnpRunnable("CreateFrame")
{
	this->SetDescription("creates frames of various types");
	this->SetPreconditions("document open");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor
*/
_SnpRunnerCreateFrame::~_SnpRunnerCreateFrame()
{
}

/*
*/
bool16 _SnpRunnerCreateFrame::CanRun(ISnpRunnableContext* runnableContext)
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
ErrorCode _SnpRunnerCreateFrame::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		// ILayoutControlData is required to determine the active spread layer and the current page.
		InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		if (layoutControlData == nil) {
			SNIPLOG("Please open a document and try again.");
			break;
		}

		// Ask which kind of frame is wanted.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Rectangle frame"));
		choices.push_back(PMString("Text frame"));
		choices.push_back(PMString("Rectangle graphic"));
		choices.push_back(PMString("Square in a fancy graphic"));
		choices.push_back(PMString("Arrow graphic"));
		enum {kRectangleFrame, kTextFrame, kRectangleGraphic, kSquareInFancyGraphic, kArrowGraphic};
		int32 choice  = parameterUtils->GetChoice("What kind of frame?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Create the chosen type of frame.
		UIDRef frameUIDRef = UIDRef::gNull;
		SnpCreateFrame	instance;

		switch (choice) 
		{
		case kRectangleFrame:
			{
				frameUIDRef = instance.CreateRectangleFrame(layoutControlData, PMRect(0.0, 0.0, 100.0, 100.0));
				break;
			}
		case kTextFrame:
			{
				frameUIDRef = instance.CreateTextFrame(layoutControlData, PMRect(100.0, 0.0, 200.0, 100.0));
				break;
			}
		case kRectangleGraphic:
			{
				frameUIDRef = instance.CreateRectangleGraphic(layoutControlData, PMRect(200.0, 0.0, 300.0, 100.0));
				break;
			}
		case kSquareInFancyGraphic:
			{
				frameUIDRef = instance.CreateSquareInFancyGraphic(layoutControlData, PMRect(300.0, 0.0, 400.0, 100.0));
				break;
			}
		case kArrowGraphic:
			{
				frameUIDRef = instance.CreateArrowGraphic(layoutControlData, PMRect(0, 100, 400.0, 500.0));
				break;
			}
		default:
			{
				break;
			}
		}

		// Check a frame was created.
		if (frameUIDRef == UIDRef::gNull) {
			break;
		}
		// Select the frame.
		if (!instance.SelectFrame(runnableContext->GetActiveContext()->GetContextSelection(),
			frameUIDRef)) {
			break;
		}

		status = kSuccess;

	} while(false);
	return status;
}

/*
*/
ErrorCode	_SnpRunnerCreateFrame::RunUnitTest(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		// ILayoutControlData is required to determine the active spread layer and the current page.
		InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		if (layoutControlData == nil) {
			SNIPLOG("Unable to run unit test for SnpCreateFrame");
			break;
		}
		UIDRef frameUIDRef;
		SnpCreateFrame	instance;
		frameUIDRef = instance.CreateRectangleFrame(layoutControlData, PMRect(200.0, 250.0, 300.0, 350.0));
		if (instance.SelectFrame(runnableContext->GetActiveContext()->GetContextSelection(), frameUIDRef))
			status = kSuccess;
	} while(false);
	
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerCreateFrame instance_SnpRunnerCreateFrame;
DEFINE_SNIPPET(_SnpRunnerCreateFrame) 	
//End, SnpCreateFrame.cpp
