//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/common/SDKLayoutHelper.cpp $
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
#include "IDocument.h"
#include "IDocumentCommands.h"
#include "IOpenLayoutCmdData.h"
#include "IDocumentUtils.h"
#include "IDocFileHandler.h"
#include "INewDocCmdData.h"
#include "IDocumentLayer.h"
#include "ILayerList.h"
#include "IWindow.h"
#include "ICreateMCFrameData.h"
#include "IMultiColumnItemData.h"
#include "INewPageItemCmdData.h"
#include "IPlacePIData.h"
#include "IImportResourceCmdData.h"
#include "IPathUtils.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "IGraphicFrameData.h"
#include "ITransform.h"
#include "IGeometry.h"
#include "IHierarchy.h"
#include "IMargins.h"
#include "IMultiColumnTextFrame.h"
#include "ITextFrameColumn.h"
#include "ITextModel.h"
#include "ITOPFrameData.h"
#include "ISpreadList.h"
#include "IBaselineFrameGridData.h"
#include "ILayerUtils.h"
#include "ITextFrameFacade.h"
#include "ITextColumnSizer.h"
#include "IURIUtils.h"

// General includes:
#include "CmdUtils.h"
#include "UIDList.h"
#include "SplineID.h"		// kSplineItemBoss
#include "TransformUtils.h" // InnerToPasteboard
#include "OpenPlaceID.h"
#include "PMPathPoint.h"
#include "Utils.h"
#include "PreferenceUtils.h"

// Project includes.
#include "SDKLayoutHelper.h"

// By default frames created will pickup the default standoff (text wrap)
// that is in operation.
const bool16 kSDKLayoutAllowDefaultStandOff = kTrue;

/* Default constructor
*/
SDKLayoutHelper::SDKLayoutHelper()
{

}

/* Destructor
*/
SDKLayoutHelper::~SDKLayoutHelper()
{

}


UIDRef SDKLayoutHelper::CreateDocument(UIFlags	uiflags,
	const	PMReal& width,
	const	PMReal& height,
	const	int32 numPages,
	const	int32 numPagesPerSpread,
	const	int32 pageBinding
)
{
	UIDRef result = UIDRef::gNull;
	do {
		// Create the command.
		InterfacePtr<ICommand> newDocCmd(Utils<IDocumentCommands>()->CreateNewCommand(uiflags));
		ASSERT(newDocCmd);
		if (newDocCmd == nil) {
			break;
		}
		
		// Set the command's parameterised data.
		InterfacePtr<INewDocCmdData> newDocCmdData(newDocCmd, UseDefaultIID());
		ASSERT(newDocCmdData);
		if (newDocCmdData == nil) {
			break;
		}
		newDocCmdData->SetCreateBasicDocument(kFalse); // Override the following defaults.
		PMPageSize pageSize( width, height);
		newDocCmdData->SetNewDocumentPageSize(pageSize);
		bool16 bWide = kTrue; // landscape orientation.
		if (width < height)
		{
			// portrait orientation.
			bWide = kFalse;
		}
		newDocCmdData->SetWideOrientation(bWide);
		// Size margin proportional to document width and height.
		PMReal horMargin = width / 20;
		PMReal verMargin = height / 20;
		newDocCmdData->SetMargins(horMargin, verMargin, horMargin, verMargin);
		newDocCmdData->SetNumPages(numPages);
		newDocCmdData->SetPagesPerSpread(numPagesPerSpread);
		newDocCmdData->SetPageBinding(pageBinding);

		// Create the new document.
		if (CmdUtils::ProcessCommand(newDocCmd) != kSuccess) {
			ASSERT_FAIL("IDocumentCommands::CreateNewCommand failed");
			break;
		}

		// Pass the UIDRef of the new document back to the caller.
		const UIDList& newDocCmdUIDList = newDocCmd->GetItemListReference();
		result = newDocCmdUIDList.GetRef(0);
		if (result == UIDRef::gNull) {
			ASSERT_FAIL("newDocCmd returned invalid document UIDRef!");
			break;
		}
	} while (false);
	return result;
}


UIDRef SDKLayoutHelper::OpenDocument(const IDFile& sysFile, UIFlags uiFlags)
{
	UIDRef result = UIDRef::gNull;
	do 
	{
		UIDRef tempRef;
		ErrorCode status = Utils<IDocumentCommands>()->Open(&tempRef,
															sysFile, 
															uiFlags, 
															IOpenFileCmdData::kOpenDefault,
															IOpenFileCmdData::kUseLockFile, kFalse);
		ASSERT(status == kSuccess);
		if(status != kSuccess){
			break;
		}

		// Grab the UIDRef of the newly opened document and verify it.
		InterfacePtr<IDocument> document(tempRef, UseDefaultIID());
		ASSERT(document);
		if (!document)	{
			// If we could not get an IDocument the postconditions are not met
			break;
		}
		// OK the document is now open but not on view.
		result = tempRef;
	} while(false);
	return result;
}


ErrorCode SDKLayoutHelper::CloseDocument(const UIDRef& documentUIDRef,
			bool16 saveOnClose,
			UIFlags uiFlags, 
			bool8 allowCancel, 
			IDocFileHandler::CloseCmdMode cmdMode)
{
	ErrorCode result = kFailure;
	do {
		// Get the IDocFileHandler interface.

		// Starting from InDesign 3.0, IDocumentUtils has been added to 
		// the utils boss where it is more logically placed. 
		// The version of IDocumentUtils on the session boss is being deprecated. 
		InterfacePtr<IDocFileHandler> docFileHandler(Utils<IDocumentUtils>()->QueryDocFileHandler(documentUIDRef));
		if (!docFileHandler) {
			break;
		}

		// Save before closing if asked.
		if(saveOnClose && docFileHandler->CanSave(documentUIDRef) ) {
			docFileHandler->Save(documentUIDRef, uiFlags);
			result = ErrorUtils::PMGetGlobalErrorCode();
			ASSERT_MSG(result == kSuccess, "IDocFileHandler::Save failed");
			if (result != kSuccess) {
				break;
			}
		}

		// Close document.
		if (docFileHandler->CanClose(documentUIDRef)) {
			docFileHandler->Close(documentUIDRef, uiFlags, allowCancel, cmdMode);
			result = ErrorUtils::PMGetGlobalErrorCode();
			ASSERT_MSG(result == kSuccess || result == kCancel, "IDocFileHandler::Close failed");
			if (result != kSuccess) {
				break;
			}
		}
	} while(false);
	return result;
}


ErrorCode SDKLayoutHelper::SaveDocumentAs(const UIDRef& documentUIDRef,
										const IDFile& sysFile,
										UIFlags uiFlags)
{
	ErrorCode result = kFailure;
	do {
		// Save the document to another file.

		// Starting from InDesign 3.0, IDocumentUtils has been added to 
		// the utils boss where it is more logically placed. 
		// The version of IDocumentUtils on the session boss is being deprecated. 
		InterfacePtr<IDocFileHandler> docFileHandler(Utils<IDocumentUtils>()->QueryDocFileHandler(documentUIDRef));
		if (!docFileHandler) {
			break;
		}
		//Try to do SaveAs
		if(docFileHandler->CanSaveAs(documentUIDRef) ) {
			docFileHandler->SaveAs (documentUIDRef, &sysFile, uiFlags);
			result = ErrorUtils::PMGetGlobalErrorCode();
			ASSERT_MSG(result == kSuccess, "IDocFileHandler::SaveAs failed");
			if (result != kSuccess) {
				break;
			}
		}
	} while(false);
	return result;
}


ErrorCode SDKLayoutHelper::OpenLayoutWindow(const UIDRef& documentUIDRef)
{
	ErrorCode result = kFailure;
	do
	{
		// Create the command.
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kOpenLayoutCmdBoss));
		ASSERT(cmd);
		if (cmd == nil){
			break;
		}

		// Pass the command the UIDRef of the document.
		cmd->SetItemList(UIDList(documentUIDRef));
		
		// You could override the command's default options if necessary...
		InterfacePtr<IOpenLayoutPresentationCmdData> winData(cmd, IID_IOPENLAYOUTCMDDATA);
		ASSERT(winData);
		if (winData == nil) {
			break;
		}
		// ...we just take the defaults.

		// Open a window on the document.
		if (CmdUtils::ProcessCommand(cmd) != kSuccess) {
			ASSERT_FAIL("kOpenLayoutCmdBoss failed");
			break;
		}

		// Validate the the newly opened window is returned.
		InterfacePtr<IWindow> window(winData->GetResultingPresentation(), UseDefaultIID());
		ASSERT(window);
		if (window == nil) {
			// If we couldn't get an IWindow the postconditions won't be met
			break;
		}

		result = kSuccess;

	} while (false);
	return result;
}


UIDRef  SDKLayoutHelper::GetActiveSpreadLayerRef(const UIDRef& spreadUIDRef, 
												bool16 wantGuideLayer)
{
	UIDRef result = UIDRef::gNull;
	do {
		// Navigate from spread to document.
		InterfacePtr<ISpread> spread(spreadUIDRef, UseDefaultIID());
		ASSERT(spread);
		if(!spread) {
			break;
		}
		IDataBase* db = spreadUIDRef.GetDataBase();
		InterfacePtr<IDocument> document(db, db->GetRootUID(), UseDefaultIID());
		ASSERT(document);
		if (document == nil) {
			break;
		}

		// We need to get the active document layer before we can find the corresponding spread layer
		InterfacePtr<IDocumentLayer> documentLayer(Utils<ILayerUtils>()->QueryDocumentActiveLayer(document));
		if (!documentLayer) {
			// If for some reason ILayerUtils doesn't give the active document layer then find a document layer via ILayerList.
			InterfacePtr<ILayerList> layerList(document, IID_ILAYERLIST); //no kDefaultIID UseDefaultIID());
			ASSERT(layerList);
			if(!layerList) {
				break;
			}
			UIDRef layerRef = layerList->GetNextActiveLayer(int32(0));
			if (layerRef != UIDRef()) {
				documentLayer = InterfacePtr<IDocumentLayer>(layerRef, UseDefaultIID());
			}
		}
		ASSERT(documentLayer);
		if(!documentLayer) {
			break;
		}

		int32 spreadLayerPosition;
		// to navigate to a kSpreadLayerBoss from kSpreadBoss we need the help of kDocumentLayerBoss
		InterfacePtr<ISpreadLayer> contentSpreadLayer(spread->QueryLayer(documentLayer, &spreadLayerPosition, wantGuideLayer));
		ASSERT(contentSpreadLayer);
		result = ::GetUIDRef(contentSpreadLayer);
		
	} while(false);
	return result;
}


UIDRef  SDKLayoutHelper::GetSpreadLayerRef(const UIDRef& spreadUIDRef, 
												int32 documentLayerIndex, 
												bool16 wantGuideLayer)
{
	UIDRef result = UIDRef::gNull;
	do {
		InterfacePtr<ISpread> spread(spreadUIDRef, UseDefaultIID());
		ASSERT(spread);
		if(!spread) {
			break;
		}

		// Find the document layer indicated by the given documentLayerIndex. 
		IDataBase* db = spreadUIDRef.GetDataBase();
		InterfacePtr<IDocument> document(db, db->GetRootUID(), UseDefaultIID());
		ASSERT(document);
		if (!document) {
			break;
		}
		InterfacePtr<ILayerList> layerList(document, IID_ILAYERLIST); //UseDefaultIID());
		ASSERT(layerList);
		if(!layerList) {
			break;
		}
		InterfacePtr<IDocumentLayer> documentLayer(layerList->QueryLayer(documentLayerIndex));
		ASSERT(documentLayer);
		if(!documentLayer) {
			break;
		}

		// Use the spread to find the spread layer associated with this document layer.
		int32 spreadLayerIndex;
		InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(documentLayer, &spreadLayerIndex, wantGuideLayer));
		ASSERT(spreadLayer);
		if (!spreadLayer) {
			break;
		}

		result = ::GetUIDRef(spreadLayer);
		
	} while(false);
	return result;
}


PMRect SDKLayoutHelper::PageToSpread(const UIDRef& pageUIDRef, const PMRect& boundsInPageCoords)	
{
	PMRect result(boundsInPageCoords);
	do {
		InterfacePtr<ITransform> transform(pageUIDRef, UseDefaultIID());
		ASSERT(transform);
		if (!transform) {
			break;
		}
		PMRect marginBBox;
		InterfacePtr<IMargins> margins(transform, IID_IMARGINS);
		// Note it's OK if the page does not have margins.
		if (margins) {
			margins->GetMargins(&marginBBox.Left(), &marginBBox.Top(), &marginBBox.Right(), &marginBBox.Bottom());
		}
		result.MoveRel(marginBBox.Left(), marginBBox.Top());
		::TransformInnerRectToParent(transform, &result);
	} while (false);
	return result;
}


UIDRef SDKLayoutHelper::PlaceFileInFrame(const IDFile& contentFile, 
							const UIDRef& parentUIDRef, 
							const PMRect& boundsInParentCoords, 
							const UIFlags uiFlags, 
							const bool16 retainFormat, 
							const bool16 convertQuotes, 
							const bool16 applyCJKGrid,
							const UID& uidPreview)
{
	UIDRef result = UIDRef::gNull;
	do {
		InterfacePtr<IHierarchy> hierarchy(parentUIDRef, UseDefaultIID());
		ASSERT(hierarchy);
		if (!hierarchy) {
			break;
		}

		// Set up the co-ordinates for the frame. The caller passes in the
		// co-ordinates in the co-ordinate space of the parent. kImportAndPlaceCmdBoss
		// expects pasteboard co-ordinates so we have to transform the points before passing
		// them to the command.
		InterfacePtr<ITransform> transform(parentUIDRef, UseDefaultIID());
		ASSERT(transform);
		if (transform == nil) {
			break;
		}
		PBPMPoint topLeft = boundsInParentCoords.LeftTop();
		PBPMPoint rightBottom = boundsInParentCoords.RightBottom();
		::TransformParentPointToPasteboard(transform, &topLeft);
		::TransformParentPointToPasteboard(transform, &rightBottom);
		// Fill in the PointList. If you know you are only placing graphics
		// kImportAndPlaceCmdBoss will automatically size the frame to fit the content
		// if you just specify one point, the leftTop co-ordinate. Since we
		// want to be able to place both text and graphics we specify two
		// points that together give the bounding box. We subsequently process 
		// kFitFrameToContentCmdBoss, that way we can have a single method that places 
		// pictures or text.
		PMPointList pointList;
		pointList.push_back(topLeft);
		pointList.push_back(rightBottom);

		// Create kImportAndPlaceCmdBoss.
		InterfacePtr<ICommand> importAndPlaceCmd(CmdUtils::CreateCommand(kImportAndPlaceCmdBoss));
		ASSERT(importAndPlaceCmd != nil);
		if (importAndPlaceCmd == nil) {
			break;
		}

		// Set up the command's data interfaces.
		InterfacePtr<IPlacePIData> placePIData(importAndPlaceCmd, UseDefaultIID());
		ASSERT(placePIData != nil);
		if (placePIData == nil) {
			break;
		}
		placePIData->Set(parentUIDRef, &pointList, kFalse/*Don't use place gun contents, use the file.*/);

	// TODO: LINKREWORK fix.

	URI tmpURI;
	Utils<IURIUtils>()->IDFileToURI(contentFile, tmpURI);
		InterfacePtr<IImportResourceCmdData> importResourceCmdData(importAndPlaceCmd, IID_IIMPORTRESOURCECMDDATA); // no kDefaultIID
		ASSERT(importResourceCmdData != nil);
		if (importResourceCmdData == nil) {
			break;
		}
		importResourceCmdData->Set(parentUIDRef.GetDataBase(), tmpURI, uiFlags, retainFormat, convertQuotes, applyCJKGrid, uidPreview);

		// Process the command.
		if (CmdUtils::ProcessCommand(importAndPlaceCmd) != kSuccess) {
			ASSERT_FAIL("kImportAndPlaceCmdBoss failed");
			break;
		}

		// Get a reference to the created frame to the caller.
		const UIDList& outItemList = importAndPlaceCmd->GetItemListReference();
		ASSERT(outItemList.Length() > 0);
		if (!(outItemList.Length() > 0)) {
			break;
		}
		UIDRef frameUIDRef = importAndPlaceCmd->GetItemListReference().GetRef(0);
		InterfacePtr<IGraphicFrameData> graphicFrameData(frameUIDRef, UseDefaultIID());
		ASSERT(graphicFrameData);
		if (!graphicFrameData) {
			break;
		}

		result = frameUIDRef;

		// Fit the frame to the text content we placed.
		InterfacePtr<ICommand> fitFrameToContentCmd(CmdUtils::CreateCommand(kFitFrameToContentCmdBoss));
		ASSERT(fitFrameToContentCmd != nil);
		if (fitFrameToContentCmd == nil) {
			break;
		}
		fitFrameToContentCmd->SetItemList(UIDList(result));
		if (CmdUtils::ProcessCommand(fitFrameToContentCmd) != kSuccess) {
			ASSERT_FAIL("kFitFrameToContentCmdBoss failed");
			break;
		}
	} while(false);

	return result;
}


UIDRef SDKLayoutHelper::CreateRectangleFrame(const UIDRef& parentUIDRef, const PMRect& boundsInParentCoords)	
{
	UIDRef result = UIDRef::gNull;
	PMRect bounds(boundsInParentCoords);
	result = Utils<IPathUtils>()->CreateRectangleSpline(parentUIDRef,
			bounds, 
			INewPageItemCmdData::kGraphicFrameAttributes,
			kSDKLayoutAllowDefaultStandOff,
			Transform::InnerCoordinates());
	//ASSERT(result != UIDRef::gNull);
	// If the above call returned UIDRef::gNull do we consider this a failure?
	// (JZhou)
	return result;
}


UIDRef SDKLayoutHelper::CreateTextFrame(const UIDRef& parentUIDRef,
										const PMRect& boundsInParentCoords,
										int32 numberOfColumns,
										bool16 verticalFrame,
										UIDRef* storyUIDRef,
										bool16 isLeftToRight)
{
	UIDRef result = UIDRef::gNull;
	do
	{
		// Set up the co-ordinates for the frame. The caller passes in the
		// co-ordinates in the co-ordinate space of the parent. kCreateMultiColumnItemCmdBoss
		// expects pasteboard co-ordinates so we have to transform the points before passing
		// them to the command.
		PMPoint topLeft = boundsInParentCoords.LeftTop();
		PMPoint rightBottom = boundsInParentCoords.RightBottom();
		InterfacePtr<ITransform> transform(parentUIDRef, UseDefaultIID());
		ASSERT(transform);
		if (transform == nil) {
			break;
		}
		::TransformParentPointToPasteboard(transform, &topLeft);
		::TransformParentPointToPasteboard(transform, &rightBottom);
		
		// Process command to create multi-column frame.
		if (Utils<Facade::ITextFrameFacade>()->CreateTextFrame(parentUIDRef, result, PMRect(topLeft, rightBottom), kTrue/*noGraphicAttr*/, !verticalFrame, kFalse/*isFrameGrid*/, isLeftToRight) != kSuccess)
		{
			ASSERT_FAIL("kCreateMultiColumnItemCmdBoss failed");
			break;
		}
		ASSERT(result != UIDRef::gNull);

		InterfacePtr<IGraphicFrameData> frame(result, IID_IGRAPHICFRAMEDATA);
		InterfacePtr<IMultiColumnTextFrame> mcFrame(result.GetDataBase(), frame->GetTextContentUID(), UseDefaultIID());

		// Set up ITextColumnSizer to override defaults.
		if (numberOfColumns > 0)
		{
			InterfacePtr<ITextColumnSizer> columnSizer(mcFrame, UseDefaultIID());
			columnSizer->SetNumberOfColumns(numberOfColumns);
		}

		// If the caller requested it by passing in a pointer return a reference
		// to the story associated with the text frame.
		if (storyUIDRef) {
			*storyUIDRef = UIDRef(parentUIDRef.GetDataBase(), mcFrame->GetTextModelUID());
		}

	} while(false);

	return result;
}


UIDRef SDKLayoutHelper::CreateRectangleGraphic(const UIDRef& parentUIDRef, const PMRect& boundsInParentCoords)	
{
	UIDRef result = UIDRef::gNull;
	PMRect bounds(boundsInParentCoords);
	result = Utils<IPathUtils>()->CreateRectangleSpline(parentUIDRef,
			bounds, 
			INewPageItemCmdData::kDefaultGraphicAttributes,
			kSDKLayoutAllowDefaultStandOff,
			Transform::InnerCoordinates());
	ASSERT(result != UIDRef::gNull);
	return result;
}


UIDRef SDKLayoutHelper::CreateSplineGraphic(const UIDRef& parentUIDRef, const PMRect& boundsInParentCoords, const PMRect& boundsInInnerCoords, PMPathPointList& pathPointList, bool16 bClosedPath)
{
	UIDRef result  = UIDRef::gNull;

	// Create a transformation matrix that transforms the path to the given boundsInParentCoords.
	PMReal scaleX = boundsInParentCoords.Width()/boundsInInnerCoords.Width();
	PMReal scaleY = boundsInParentCoords.Height()/boundsInInnerCoords.Height();
	PMMatrix transformationMatrix(scaleX, 0, 0, scaleY, boundsInParentCoords.Left(), boundsInParentCoords.Top());
	
	// Transform each point in the path.
	PMPathPointList::iterator iter;
	InterfacePtr<IGeometry> parentGeometry(parentUIDRef, UseDefaultIID());
	for (iter = pathPointList.begin(); iter < pathPointList.end(); iter++) {
		iter->TransformPoints(transformationMatrix);
	}
	
	// Create the spline.
	result = Utils<IPathUtils>()->CreateSpline(parentUIDRef,
		pathPointList, 
		INewPageItemCmdData::kDefaultGraphicAttributes,
		kSDKLayoutAllowDefaultStandOff,
		bClosedPath,
		Transform::InnerCoordinates());
	ASSERT(result != UIDRef::gNull);
	return result;
} 


UIDRef SDKLayoutHelper::GetGraphicFrameRef(const InterfacePtr<ITextFrameColumn>& textFrameColumn)
{
	UIDRef result = UIDRef::gNull;

	do {
		ASSERT(textFrameColumn);
		if (!textFrameColumn) {
			break;
		}

		// Check for a text frame for text on a path.
		InterfacePtr<ITOPFrameData> topFrameData(textFrameColumn, UseDefaultIID());
		if (topFrameData != nil) {
			// This is a text on a path text frame. Refer to the
			// spline that the text on a path is associated with.
			result = UIDRef(::GetDataBase(textFrameColumn), topFrameData->GetMainSplineItemUID());
			break;
		}

		// Check for a regular text frame
		InterfacePtr<IHierarchy> graphicFrameHierarchy(Utils<ITextUtils>()->QuerySplineFromTextFrame(textFrameColumn));
		result = ::GetUIDRef(graphicFrameHierarchy);

	} while(false);

	return result;
}


UIDRef SDKLayoutHelper::GetTextModelRef(const InterfacePtr<IGraphicFrameData>& graphicFrameData)
{
	UIDRef result = UIDRef::gNull;
	do {
		ASSERT(graphicFrameData);
		if (!graphicFrameData) {
			break;
		}
		// IGraphicFrameData references any associated kMultiColumnItemBoss object.
		UID textframeUID = graphicFrameData->GetTextContentUID();
		if (textframeUID == kInvalidUID) {
			break;
		}

		InterfacePtr<IMultiColumnTextFrame> mcf(::GetDataBase(graphicFrameData), textframeUID, UseDefaultIID());
		ASSERT(mcf);
		if(!mcf) {
			break;
		}
		UID textModelUID = mcf->GetTextModelUID();
		ASSERT(textModelUID != kInvalidUID);
		if (textModelUID == kInvalidUID) {
			break;
		}
		result = UIDRef(::GetDataBase(graphicFrameData), textModelUID);
	} while(false);
	return result;
}
