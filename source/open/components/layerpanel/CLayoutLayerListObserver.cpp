//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/CLayoutLayerListObserver.cpp $
//  
//  Owner: Lonnie Millett
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

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IApplication.h"
#include "ICommand.h"
#include "IControlView.h"
#include "ICursorMgr.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IFrameList.h"
#include "IGeometry.h"
#include "IHierarchy.h"
#include "ILayerList.h"
#include "ILayerUtils.h"
#include "ILayoutCmdData.h"
#include "ILayoutControlData.h"
#include "ILayoutController.h"
#include "ISelectionManager.h"
#include "IShape.h"
#include "ISnapToInvalHandlerHelper.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "ISubject.h"
#include "ITool.h"
#include "IToolCmdData.h"
#include "ILayerSuite.h"
#include "IGuideDataSuite.h"
#include "ISpreadSelectionSuite.h"

// ----- Includes -----

#include "AGMGraphicsContext.h"
#include "CObserver.h"
#include "CursorDefs.h"
#include "UIDList.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "ILayerUtils.h"
#include "ILayoutUIUtils.h"
#include "PersistUtils.h"
#include "IToolBoxUtils.h"
#include "ISelectionUtils.h"
#include "LayerPanelUtils.h"

// ----- ID.h files -----

#include "CursorID.h"
#include "ToolboxID.h"
#include "LayoutUIID.h"
#include "LayerPanelID.h"

//----------------------------------------------------------------------------------------
// Class information
//----------------------------------------------------------------------------------------

class CLayoutLayerListObserver : public CObserver
{
	public:
		CLayoutLayerListObserver(IPMUnknown *boss);
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

	private:
		void InvalidateLayer(IDocumentLayer* theLayer, bool16 guideLayerOnly);
		void InvalidateView();
		void DeselectItems(IDocumentLayer* documentLayer, bool16 guideLayerOnly);
		void SetLocked(IDocumentLayer* theLayer, bool16 guideLayerOnly);
		void SetVisible(IDocumentLayer* theLayer, bool16 guideLayerOnly);
		void UpdateLockCursor();
		void UpdateDeleteLayer(UID layerToBeDeleted);

		static int32 fIsLocked;	// Is active layer in front doc locked/hidden (kTrue) or shown/unlocked (kFalse)?
};

int32 CLayoutLayerListObserver::fIsLocked = -1;	// Mark as uninitialized


CREATE_PMINTERFACE(CLayoutLayerListObserver, kCLayoutLayerListObserverImpl)

//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver constructor
//----------------------------------------------------------------------------------------

CLayoutLayerListObserver::CLayoutLayerListObserver(IPMUnknown *boss) :
	CObserver(boss, IID_ILAYOUTLAYERLISTOBSERVER)
{
}

//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver::LazyUpdate:
//----------------------------------------------------------------------------------------

void CLayoutLayerListObserver::LazyUpdate(ISubject* , const PMIID &protocol, const LazyNotificationData* )
{
	if (protocol == IID_ILAYERLIST)
	{
		UpdateLockCursor();
	}
}

//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver::Update:
//----------------------------------------------------------------------------------------

void CLayoutLayerListObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==
	bool16 bShouldClearSnapToCache = kFalse;

	ICommand* cmd = (ICommand*)changedBy;
	if (theChange == kSetLayerColorCmdBoss)	
	{
		InterfacePtr<IDocumentLayer> docLayer(cmd->GetItemList()->GetRef(0), IID_IDOCUMENTLAYER);
		this->InvalidateLayer(docLayer, kFalse);
	}
	else if (theChange == kLockLayerCmdBoss)	
	{
		InterfacePtr<IDocumentLayer> docLayer(cmd->GetItemList()->GetRef(0), IID_IDOCUMENTLAYER);
		this->SetLocked(docLayer, kFalse);
		UpdateLockCursor();	// In case all layers were locked or one layer got unlocked.
	}
	else if (theChange == kShowLayerCmdBoss)	
	{
		InterfacePtr<IDocumentLayer> docLayer(cmd->GetItemList()->GetRef(0), IID_IDOCUMENTLAYER);
		this->SetVisible(docLayer, kFalse);
		bShouldClearSnapToCache = kTrue;	// Guides might be hiding or showing
	}
	else if (theChange == kLockGuideLayerCmdBoss)	
	{
		InterfacePtr<IDocumentLayer> docLayer(cmd->GetItemList()->GetRef(0), IID_IDOCUMENTLAYER);
		this->SetLocked(docLayer, kTrue);
	}
	else if (theChange == kShowGuideLayerCmdBoss)	
	{
		InterfacePtr<IDocumentLayer> docLayer(cmd->GetItemList()->GetRef(0), IID_IDOCUMENTLAYER);
		this->SetVisible(docLayer, kTrue);
		bShouldClearSnapToCache = kTrue;	// Guides might be hiding or showing
	}
	else if (theChange == kMoveLayerCmdBoss || theChange == kMergeLayersCmdBoss)
	{
		InvalidateView();
	}
	else if (theChange == kDeleteLayerCmdBoss)	
	{
		ICommand *deleteLayerCmd = (ICommand*)changedBy;
		ICommand::CommandState	cmdState = deleteLayerCmd->GetCommandState();

		// the command pre-notifies
		if (cmdState == ICommand::kNotDone)
		{
			InterfacePtr<IDocumentLayer> docLayer(deleteLayerCmd->GetItemList()->GetRef(0), IID_IDOCUMENTLAYER);
			this->DeselectItems(docLayer, kFalse);

			UID layerToBeDeleted = cmd->GetItemList()->First();
			UpdateDeleteLayer(layerToBeDeleted);
			InvalidateView();
		}
		bShouldClearSnapToCache = kTrue;	// Guides might be hiding or showing
	}
	else if (theChange == kActiveLayerChangedMsg)
	{
		// Do only...
		// We now snapshot the cursor manager locked state.
		UpdateLockCursor();
	}
	else if (theChange == kSetToolCmdBoss)
	{
		// If we are using a tool in the "standard" set of tools, class ID will be kPointerToolBoss.
		// We potentially need to change the cursor. Ignore other tool groups.
		InterfacePtr<IToolCmdData> toolData(cmd, IID_ITOOLCMDDATA);
		if (toolData && toolData->GetToolType() == kPointerToolBoss)
			UpdateLockCursor();
	}
	else if (protocol == IID_IACTIVECONTEXT)  //this protocol sends IID instead of cmdID
	{
		InterfacePtr<IActiveContext> context(theSubject, UseDefaultIID());
		const PMIID& what = *((const PMIID*)changedBy);
		if (what == IID_ICONTROLVIEW)
			UpdateLockCursor();
	}

	if (bShouldClearSnapToCache)
	{
		// Clear out the cached cursor snap to interface
		// so that new page guides will be calculated.
		InterfacePtr<ILayoutControlData> layoutData(this, IID_ILAYOUTCONTROLDATA);
		if (layoutData)
		{
			layoutData->SetCursorSnapTo(nil);

			// Add info for undo/redo, done via intermediary interface so it's accessible from multiple plug-ins.
			InterfacePtr<ISnapToInvalHandlerHelper> snapToInvalHandlerHelper(layoutData, UseDefaultIID());
			snapToInvalHandlerHelper->SnapToCacheChanged();
		}
	}

}

//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver::Invalidate:
//----------------------------------------------------------------------------------------

void CLayoutLayerListObserver::InvalidateView()
{
	InterfacePtr<ILayoutController> iLayoutController(this, IID_ILAYOUTCONTROLLER);
	iLayoutController->InvalidateContent();
}


//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver::Invalidate:
// Invalidate the spread layers corresponding to the document layer passed in.
// Optionally just invalidate the guide spread layer.
// Depending on how many spreads are visible, it might be easier just to invalidate the
// whole window, rather than the affected layer.
//----------------------------------------------------------------------------------------

void CLayoutLayerListObserver::InvalidateLayer(IDocumentLayer* theLayer, bool16 guideLayerOnly)
{
	// Get a list of visible spreads that need to be invalidated.
	InterfacePtr<IControlView> thisView(this, IID_ICONTROLVIEW);
	UIDList visibleSpreads = Utils<ILayoutUIUtils>()->GetVisibleSpreads(thisView);

	NonMarkingAGMGraphicsContext gc(thisView);
	GraphicsDataPtr gd(&gc);

	// Invalidate visible spreads.
	int32 numSpreads = visibleSpreads.Length();
	for (int32 i = 0; i < numSpreads; i++)
	{
		InterfacePtr<ISpread> spread(visibleSpreads.GetRef(i), IID_ISPREAD);

		// Invalidate the guide spread layer
		InterfacePtr<ISpreadLayer> guideLayer(spread->QueryLayer(theLayer, nil, kTrue));

		InterfacePtr<IShape> guideLayerShape(guideLayer, IID_ISHAPE);
		guideLayerShape->Inval(gd);

		if (guideLayerOnly)
			continue;

		// Invalidate the regular spread layer
		int32 invalFlags = IShape::kNoFlags ;
		InterfacePtr<ISpreadLayer> layer(spread->QueryLayer(theLayer, nil, kFalse));
		InterfacePtr<IShape> layerShape(layer, IID_ISHAPE);
		layerShape->Inval( gd, kInvalidClass, invalFlags ) ;
	}
}


//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver::DeselectItems:
//----------------------------------------------------------------------------------------

void CLayoutLayerListObserver::DeselectItems(IDocumentLayer* documentLayer, bool16 guideLayerOnly)
{
	InterfacePtr<IControlView> view(this, IID_ICONTROLVIEW);
	ASSERT_MSG(view != nil, "CLayoutLayerListObserver::DeselectItems - view != nil");

	InterfacePtr<ISelectionManager> selectionMgr ( Utils<ISelectionUtils>()->QueryViewSelectionManager(view));
	if (selectionMgr)
	{
		InterfacePtr<IGuideDataSuite> iGuideSuite(selectionMgr, UseDefaultIID());
		bool16 bGuidesSelected = iGuideSuite && iGuideSuite->AreGuidesSelected();

		// Deselect items on this layer
		InterfacePtr<ILayerSuite>    iLayerSuite (selectionMgr, UseDefaultIID());
		if(iLayerSuite)
			iLayerSuite->DeselectAllItemsOnLayer(documentLayer, view, guideLayerOnly || bGuidesSelected);

		// Check for spread selection key object
		InterfacePtr<ISpreadSelectionSuite> spreadSelection(selectionMgr, UseDefaultIID());
		if (spreadSelection)
		{
			UIDRef keyObject = spreadSelection->GetSelectedKeyObject();
			if (keyObject != kInvalidUIDRef)
			{
				InterfacePtr<IHierarchy> keyObjHier(keyObject, UseDefaultIID());
				UID layerUID = Utils<ILayerUtils>()->GetLayerUID(keyObjHier); 
				InterfacePtr<ISpreadLayer> keyObjSpreadLayer(keyObject.GetDataBase(), layerUID, UseDefaultIID());
				if (keyObjSpreadLayer && keyObjSpreadLayer->GetDocLayerUID() == ::GetUID(documentLayer))
					spreadSelection->SelectKeyObject(kInvalidUIDRef);
			}
		}
	}
}


//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver::SetLocked:
//----------------------------------------------------------------------------------------

void CLayoutLayerListObserver::SetLocked(IDocumentLayer* theLayer, bool16 guideLayerOnly)
{
	if ((theLayer->IsLocked() && !guideLayerOnly) ||
		(theLayer->IsGuideLocked() && guideLayerOnly) )
		this->DeselectItems(theLayer, guideLayerOnly);

	// If the active layer was locked or unlocked, we need to update the tool mouse cursor.
	InterfacePtr<ILayoutControlData> layoutData(this, IID_ILAYOUTCONTROLDATA);
	InterfacePtr<IDocumentLayer> activeLayer(layoutData->QueryActiveDocLayer());
	if (theLayer == activeLayer && !guideLayerOnly)
		UpdateLockCursor();
}

//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver::SetVisible:
//----------------------------------------------------------------------------------------

void CLayoutLayerListObserver::SetVisible(IDocumentLayer* theLayer, bool16 guideLayerOnly)
{
	if ((!theLayer->IsVisible() && !guideLayerOnly) ||
		(!theLayer->IsGuideVisible() && guideLayerOnly) )
		this->DeselectItems(theLayer, guideLayerOnly);
	this->InvalidateLayer(theLayer, guideLayerOnly);

	// If the active layer was shown or hidden, we need to update the tool mouse cursor.
	InterfacePtr<ILayoutControlData> layoutData(this, IID_ILAYOUTCONTROLDATA);
	InterfacePtr<IDocumentLayer> activeLayer(layoutData->QueryActiveDocLayer());
	if (theLayer == activeLayer)
		UpdateLockCursor();
}


//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver::UpdateLockCursor:
//----------------------------------------------------------------------------------------

void CLayoutLayerListObserver::UpdateLockCursor()
	// Set the tool cursor to locked if the active is layer is locked or hidden and
	// the selected tool is not read-only.
{
	InterfacePtr<ITool> activeTool(Utils<IToolBoxUtils>()->QueryActiveTool());
//	ASSERT_MSG(tool != nil, "Couldn't get tool from active context!");
	if(activeTool == nil)
		return;

	// There is a CLayoutLayerListObserver attached to every layout widget, but
	// for the application lock cursor, we only track the frontmost document.
	// So, ignore message that aren't for the front document.
	InterfacePtr<ILayoutControlData> layoutData(this, IID_ILAYOUTCONTROLDATA);
	InterfacePtr<ILayoutControlData> activeLayoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
	if (layoutData != activeLayoutData)
		return;

	int32 wasLocked = fIsLocked;
	fIsLocked = kFalse;

	IDocument* theDoc = layoutData->GetDocument();
	if (!theDoc)
		return;

	// If all the layers are locked, we lock cursor regardless what tool we have.
	InterfacePtr<ILayerList> layerList(theDoc, IID_ILAYERLIST);
	int32 uiLayers = Utils<ILayerUtils>()->CountUILayers(layerList);
	int32 lockedUILayers = Utils<ILayerUtils>()->CountLayers(layerList, ILayerUtils::kFlagOn, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kDontCare, ILayerUtils::kFlagOn);

	if (uiLayers == lockedUILayers)
	{
		fIsLocked = kTrue;
	}
	else if (activeTool->IsCreationTool())
	{
		InterfacePtr<IDocumentLayer> activeLayer(layoutData->QueryActiveDocLayer());
		if (!activeLayer || activeLayer->IsLocked() || !activeLayer->IsVisible())
			fIsLocked = kTrue;
	}

	if (wasLocked != fIsLocked)
	{
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<ICursorMgr> cursorMgr(app, IID_ICURSORMGR);
		cursorMgr->LockToolCursor((bool16)fIsLocked);
	}
}


//----------------------------------------------------------------------------------------
// CLayoutLayerListObserver::UpdateDeleteLayer:
//----------------------------------------------------------------------------------------

void CLayoutLayerListObserver::UpdateDeleteLayer(UID layerToBeDeleted)
{
	InterfacePtr<ILayoutControlData> viewSpreadData(this, IID_ILAYOUTCONTROLDATA);

	// If the deleted layer is the active layer, reset it to an existing legal layer.
	InterfacePtr<IDocumentLayer> activeLayer(viewSpreadData->QueryActiveDocLayer());
	if (kLayoutWidgetBoss == ::GetClass(this) && (activeLayer == nil || ::GetUID(activeLayer) == layerToBeDeleted))	{

		// Figure out what layer will be the new active layer. It will pick the last available layer.
		IDocument* document = viewSpreadData->GetDocument();
		InterfacePtr<ILayerList> layerList(document, IID_ILAYERLIST);
		int32 layerCount = layerList->GetCount();
		UIDRef newActiveLayer;

		if (layerCount > 2)	{
			int32 layerIndex = layerList->GetLayerIndex(layerToBeDeleted);
			ASSERT_MSG(layerIndex!= -1 && layerIndex < layerCount, "CLayoutLayerListObserver::UpdateDeleteLayer Incorrect layer index");
			if (layerIndex == -1 || layerIndex >= layerCount)
				layerIndex = 0;
			newActiveLayer = layerList->GetNextActiveLayer(layerIndex);
		}

		if (newActiveLayer == nil)
				newActiveLayer = layerList->GetNextActiveLayer((int32)0);

		if (newActiveLayer != UIDRef()) {

			ASSERT_MSG(layerToBeDeleted != newActiveLayer.GetUID(), "CLayoutLayerListObserver::UpdateDeleteLayer. New active layer cannot be same as the deleted layer");

			InterfacePtr<ILayoutControlData> view(this, IID_ILAYOUTCONTROLDATA);
			LayerPanelUtils::DoSetActiveLayer(newActiveLayer,view);
		}
	}
}

