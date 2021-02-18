//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerTreeDragDropTarget.cpp $
//  
//  Owner: Yeming Liu
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface files -----

#include "IActiveContext.h"
#include "IBoolData.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IFormFieldUtils.h"
#include "IWidgetParent.h"
#include "IPanelControlData.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewMgr.h"
#include "IWorkspace.h"
#include "ILayoutUIUtils.h"
#include "ISelectionProxyDrawData.h"
#include "IHierarchy.h"
#include "IDocumentLayer.h"
#include "IPageItemTypeUtils.h"
#include "IArrangeFacade.h"
#include "ILayerFacade.h"
#include "ILayerUtils.h"
#include "ISpreadLayer.h"
#include "ILayerList.h"
#include "IUIDData.h"
#include "ILayerUIUtils.h"
#include "ILayerSuite.h"
#include "ITransformFacade.h"
#include "IHierarchyUtils.h"
#include "IBoundsData.h"
#include "ITransformCmdData.h"
#include "ICopyCmdData.h"
#include "ISpread.h"
#include "IAnimationFacade.h"

// ----- Include files -----

#include "CTreeViewDragDropTarget.h"
#include "DataObjectIterator.h"
#include "LocaleSetting.h"
#include "PMFlavorTypes.h"
#include "DragDropConstants.h"
#include "LayerTreeUIDNodeID.h"
#include "LayerPanelUtils.h"
#include "KeyStates.h"
#include "SelectionUtils.h"
#include "K2Vector.tpp"
#include "ErrorUtils.h"

// ----- Utilitity files -----

#include "Utils.h"

// ----- ID files -----
#include "FormFieldID.h"
#include "LayerPanelID.h"
#include "PageItemScrapID.h"

class LayerTreeDragDropTarget : public CTreeViewDragDropTarget
{
	public:
				LayerTreeDragDropTarget(IPMUnknown *boss);
		virtual	~LayerTreeDragDropTarget();
		
		// Can the target accept the data being dragged?
		//	(Drag source is provided to determine if data should be moved, copied or linked.)
		virtual DragDrop::TargetResponse CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;

		// Create the commands needed to complete a drop 
		// 	(targets will only receive kDragMove or kDrop)
		virtual ErrorCode ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);

		virtual	void				DrawHilite(IControlView*	targetWidget, int32 hitWhere);
				void				AdjustHiliteLine( IControlView* widget, PMReal& left, PMReal& right );

		void DoDragWithin(const PMPoint& localPt);
		void DoDragLeave();

		virtual	IControlView* 	GetTarget( IControlView*	widget, int32* hitWhere, const PMPoint& localPt );
		SysWireframe DoMakeDropHiliteRegion() const;
		
	private:

		ErrorCode CalculateWhereToMovePageItem(IDragDropController* controller, UID * outNewParentUID, NodeID & placeAfterThisNode ) const;
		ErrorCode HandleLayerProxyDrop(IDragDropController* controller) const;
		ErrorCode HandleLayerDrop(IDragDropController* controller) const;
		ErrorCode HandlePageItemDrop(IDragDropController* controller) const;
		ErrorCode MovePageItemToLayer(UID desiredLayer, UID pageItem) const;
		ErrorCode ChangeIndexWithinParentIfDifferent(const NodeID & placeAfterThisNode, UID pageItem) const;
		ErrorCode ChangeHierarchyParentsIfDifferent(UID desiredParentUID, UID pageItem) const;

		bool	SupportedFlavorExists(ExternalPMFlavor flavor, DataObjectIterator* dataIter, DataExchangeResponse &inOutResponse ) const;
		bool	IsParentChangeAllowed(const IHierarchy* pageItemHier, const IHierarchy* desiredParentHier) const;

		UIDList GetLayersToMove(IDragDropController* controller, UIDRef relativeToLayerRef) const;
		UIDList GetPageItemsToMove(IDragDropController* controller) const;
		UID GetSpreadLayerUIDFromDocLayer(UID docLayerUID) const;

		void DrawTargetIcon(IControlView* whichWidget, bool16 erase);
		bool16 CouldDropOnLayer();

		mutable ExternalPMFlavor			fDragFlavor;			// local cache: what is being dragged?
		bool fCouldDropOnLayer;
		IDataBase *fFrontDocDBForDrop;
};

CREATE_PMINTERFACE(LayerTreeDragDropTarget, kLayerTreeDragDropTargetImpl)

//--------------------------------------------------------------------------------------
// LayerTreeDragDropTarget::LayerTreeDragDropTarget()
//-------------------------------------------------------------------------------------
LayerTreeDragDropTarget::LayerTreeDragDropTarget(IPMUnknown *boss) :
	CTreeViewDragDropTarget(boss),fDragFlavor(kNoExternalFlavor), fCouldDropOnLayer(false),fFrontDocDBForDrop(nil)
{
}

//--------------------------------------------------------------------------------------
// LayerTreeDragDropTarget::~LayerTreeDragDropTarget()
//-------------------------------------------------------------------------------------
LayerTreeDragDropTarget::~LayerTreeDragDropTarget()
{
}

SysWireframe LayerTreeDragDropTarget::DoMakeDropHiliteRegion() const
{
	return (SysWireframe) DragDrop::kNoDropHilite;
}


bool LayerTreeDragDropTarget::SupportedFlavorExists(ExternalPMFlavor flavor, DataObjectIterator* dataIter, DataExchangeResponse &inOutResponse ) const
{
//	TRACEFLOW("LayerPanel","LayerTreeDragDropTarget::SupportedFlavorExists called for flavor %d\n",flavor);
	inOutResponse = dataIter->FlavorExistsWithPriorityInAllObjects(flavor);
	if (inOutResponse.CanDo())
	{
		fDragFlavor = flavor;
		return true;
	}
	return false;
}

DragDrop::TargetResponse LayerTreeDragDropTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* , const IDragDropController* ) const
{
	//
	// Check the available external flavors to see if we can handle any of them
	//
	if (dataIter)
	{		
		DataExchangeResponse response;
	
		// we claim to accept eye & pencil drags just so scrolling works.
		// This DDTarget actually does handle layer drops, page item drops, and layer proxy drops.
		if(SupportedFlavorExists(kPMLayerEyeFlavor,dataIter,response) || SupportedFlavorExists(kPMLayerPencilFlavor,dataIter,response) || 
			SupportedFlavorExists(kPMLayerZOrderFlavor,dataIter,response) || SupportedFlavorExists(kPMLayerPageItemZOrderFlavor,dataIter,response) || 
			SupportedFlavorExists(kPMLayerProxyFlavor,dataIter,response)) 
		{
		//	TRACEFLOW("LayerPanel","LayerTreeDragDropTarget::CouldAcceptTypes returning kDropWillCopy\n");
			if(fDragFlavor == kPMLayerPageItemZOrderFlavor)
				return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy,DragDrop::kUseDefaultTrackingFeedback,DragDrop::kTargetWillProvideCursorFeedback);
			else
				return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);
		}
	}
//	TRACEFLOW("LayerPanel","LayerTreeDragDropTarget::CouldAcceptTypes returning kWontAcceptTargetResponse\n");
	
	return DragDrop::kWontAcceptTargetResponse;
}


//--------------------------------------------------------------------------------------
// AdjustHiliteLine
//--------------------------------------------------------------------------------------
void	LayerTreeDragDropTarget::AdjustHiliteLine( IControlView*	widget, PMReal& left, PMReal&  /*right*/)
{
	InterfacePtr<const IPanelControlData> panelData(widget,UseDefaultIID());
	InterfacePtr<const ITreeNodeIDData>		nodeData(widget, UseDefaultIID());
	TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
	if(uidNode->IsLayerEntry())
	{
		IControlView * nameParentWidget = panelData->FindWidget(kLayerListElementNamePanelWidgetID);
		IControlView * nameWidget = panelData->FindWidget(kLayerListElementNameWidgetID);
		left = nameWidget->GetFrame().Left() + nameParentWidget->GetFrame().Left();
	}
	else
	{
		IControlView * nameParentWidget = panelData->FindWidget(kLayerPageItemNamePanelWidgetID);
		IControlView * nameWidget = panelData->FindWidget(kLayerPageItemElementTextWidgetID);		
		left = nameWidget->GetFrame().Left() + nameParentWidget->GetFrame().Left();
	}
}


IControlView* 	LayerTreeDragDropTarget::GetTarget( IControlView*	widget, int32* hitWhere, const PMPoint& localPt )
{
	IControlView *possibleTarget = CTreeViewDragDropTarget::GetTarget(widget,hitWhere,localPt);
	if(possibleTarget)
	{
		if (fDragFlavor == kPMLayerProxyFlavor || fDragFlavor == kPMLayerZOrderFlavor)
		{
			InterfacePtr<const ITreeNodeIDData>	nodeData(possibleTarget,UseDefaultIID());
			TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
		
			if(!uidNode->IsLayerEntry())
				return nil; // page item is not valid target for these drag types.
		}
	}
	return possibleTarget;
}

void LayerTreeDragDropTarget::DrawHilite(IControlView*	targetWidget, int32 hitWhere)
{
	IDataBase* curDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
//	TRACEFLOW("LayerPanel","LayerTreeDragDropTarget::DrawHilite targetWidget 0x%x, fOldTarget 0x%x, hitWhere %d\n",targetWidget,fOldTarget,hitWhere);
	if(fDragFlavor == kPMLayerProxyFlavor)
	{
		if(fOldTarget)
		{
			InterfacePtr<const ITreeNodeIDData>	nodeData(fOldTarget,UseDefaultIID());
			TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
			if(uidNode->IsLayerEntry())
			{
				this->DrawTargetIcon(fOldTarget,kTrue); // erase
			}
		}
	
		fOldTarget = targetWidget; // don;t want to draw the hilite line, we draw our own hiliting for kPMLayerProxyFlavor, but we do need to update fOldTarget and fHitLocation
		fHitLocation = hitWhere;
		// fPreviousHilite will be set by the call to DrawTargetIcon
	
		// Draw the outline around the page tab.
		if(fOldTarget)
		{
			InterfacePtr<const ITreeNodeIDData>	nodeData(fOldTarget,UseDefaultIID());
			TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
			if(uidNode->IsLayerEntry())
			{
				fCouldDropOnLayer = this->CouldDropOnLayer();
				this->DrawTargetIcon(fOldTarget,kFalse);
			}
		}
	}
	else if (fDragFlavor == kPMLayerPageItemZOrderFlavor && targetWidget)
	{
		InterfacePtr<const ITreeNodeIDData>	nodeData(targetWidget,UseDefaultIID());
		TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
		bool drawHilite = true;
		if(uidNode->IsLayerEntry())
		{
			if(hitWhere == kAbove)
			{
				InterfacePtr<const ILayerList> layerList(curDocDB,curDocDB->GetRootUID(),UseDefaultIID());
				const int32 dropLayerIndex = Utils<ILayerUIUtils>()->GetUILayerIndex(layerList,uidNode->GetUID());
				if(dropLayerIndex == 0)
					drawHilite = false;
			}

			InterfacePtr<const IDocumentLayer> docLayer(curDocDB,uidNode->GetUID(), UseDefaultIID());
			if(docLayer->IsLocked() && !::IsCommandKeyPressed())
				drawHilite = false;
			
		}
		else	if(uidNode->GetUID() == curDocDB->GetRootUID())
		{
			drawHilite = false;
		}
		else
		{
			// we're dragging a page item over another page item. If the page item we're over is on a locked layer, don't allow the drop.
			InterfacePtr<const IHierarchy> piHier(curDocDB,uidNode->GetUID(),UseDefaultIID());
			InterfacePtr<const ISpreadLayer> spreadLayer(curDocDB,piHier->GetLayerUID(), UseDefaultIID());
			if(spreadLayer->IsLocked() && !::IsCommandKeyPressed())
				drawHilite = false;
		}
			
		if(drawHilite)
		{
			CTreeViewDragDropTarget::DrawHilite(targetWidget,hitWhere);

			InterfacePtr<IDragDropController> ddController (GetExecutionContextSession(), UseDefaultIID ());
			CursorSpec	newCursor (kAppUIPluginID, ::IsOptionAltKeyPressed() ? kCrsrClosedHandCopy : kCrsrClosedHand); 
			ddController->SetTrackingCursorFeedback (newCursor);		
		}
		else
		{
			fOldTarget = targetWidget;// we do need to update fOldTarget and fHitLocation
			fHitLocation = hitWhere;
			fPreviousHilite = targetWidget->GetBBox(); // have to set this to something.
			
			InterfacePtr<IDragDropController> ddController (GetExecutionContextSession(), UseDefaultIID ());
			CursorSpec	newCursor (kAppUIPluginID, kCrsrPlaceBadDropTarget); 
			ddController->SetTrackingCursorFeedback (newCursor);		
			
		}
	}
	else if (fDragFlavor == kPMLayerEyeFlavor || fDragFlavor == kPMLayerPencilFlavor)
	{
		//nothing to do
	}
	else
	{
		CTreeViewDragDropTarget::DrawHilite(targetWidget,hitWhere);
	}
}

void LayerTreeDragDropTarget::DoDragWithin(const PMPoint& localPt)
{
	
	CTreeViewDragDropTarget::DoDragWithin(localPt);
	
}

void LayerTreeDragDropTarget::DoDragLeave()
{
	CTreeViewDragDropTarget::DoDragLeave();
}

//--------------------------------------------------------------------------------------
// DrawTargetIcon
//	We drag our own drop target hilite here. This way we get core behavior.
//--------------------------------------------------------------------------------------
void LayerTreeDragDropTarget::DrawTargetIcon(IControlView* whichWidget, bool16 erase)
{	
	InterfacePtr<const IPanelControlData>	panelData(whichWidget, UseDefaultIID());
	IControlView* proxyView = panelData->FindWidget(kLayerListElementProxyWidgetID);
	if (!proxyView)
		return;

	// Check to make sure view is still around (could have been hidden).
	if (proxyView && proxyView->IsVisible() && proxyView->GetDrawRegion())
	{
		fPreviousHilite = proxyView->GetBBox();

		InterfacePtr<ISelectionProxyDrawData> drawData(proxyView, UseDefaultIID());
		ISelectionProxyDrawData::ProxyDrawType oldDrawMode = drawData->GetDrawingMode();
		ASSERT_MSG(oldDrawMode == ISelectionProxyDrawData::kUnselected || oldDrawMode == ISelectionProxyDrawData::kSelected,"Proxy draw mode is already drag&drop?"); 
		drawData->SetDrawingMode(fCouldDropOnLayer ? ISelectionProxyDrawData::kDropOK:ISelectionProxyDrawData::kNoDropAllowed);

		proxyView->Invalidate();
		drawData->SetDrawingMode(oldDrawMode);
		if(erase)
		{
			proxyView->Invalidate();
		}
 	}
}

bool16 LayerTreeDragDropTarget::CouldDropOnLayer()
{		
	if(!fOldTarget)
		return kFalse;
		
	InterfacePtr<const ITreeNodeIDData>	nodeData(fOldTarget,UseDefaultIID());
	TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
	InterfacePtr<const IDocumentLayer> docLayer(LayerPanelUtils::GetCurrentLayerPanelDB(this),uidNode->GetUID(), UseDefaultIID());
	
	// If layer is locked, not a drop target unless command key is pressed.
	bool16 commandKeyDown = ::IsCommandKeyPressed();
	if (docLayer && (!docLayer->IsLocked() || commandKeyDown))
		return kTrue;
	else
		return kFalse;
}

static ErrorCode ChangeHierarchyPreservingTransform(UIDRef itemToChange, UID newParent)
{
	// first, one last sanity check - make sure we're not moving a parent into a child, or parenting an item to itself
	if(itemToChange.GetUID() == newParent)
	{
		TRACE("failing drop because we're trying to parent something to itself\n");
		return kFailure;
	}

	InterfacePtr<const IHierarchy> newAncestorHier(itemToChange.GetDataBase(),newParent,UseDefaultIID());
	while(newAncestorHier && newAncestorHier->GetParentUID() != kInvalidUID)
	{
	//	TRACE("ChangeHierarchyPreservingTransform checking parents. newAncestorHier->GetParentUID() %d, itemToChange.GetUID() %d\n",newAncestorHier->GetParentUID().Get(),itemToChange.GetUID().Get());
		if(newAncestorHier->GetParentUID() == itemToChange.GetUID())
		{
			TRACE("failing drag because we're trying to parent something to a decendant\n");
			return kFailure;
		}
			
		newAncestorHier.reset(newAncestorHier->QueryParent());
	}

	UIDList listOfItems(itemToChange);
	K2Vector<PMMatrix> matricies;
	Utils<Facade::ITransformFacade>()->GetItemsTransform(listOfItems,Transform::SpreadCoordinates(),matricies);
	
	ErrorCode result = Utils<IHierarchyUtils>()->RemoveFromHierarchy(itemToChange);
	
	if(result == kSuccess)
		result = Utils<IHierarchyUtils>()->AddToHierarchy(itemToChange,newParent);

	if(result == kSuccess)
	{
		InterfacePtr<ICommand> transformCommand( CmdUtils::CreateCommand( kTransformPageItemsCmdBoss));
		transformCommand->SetItemList( listOfItems);
		InterfacePtr<IBoundsData> boundsData( transformCommand, UseDefaultIID());
		boundsData->SetDefaultBoundsChecking();
		InterfacePtr<ITransformCmdData> data( transformCommand, UseDefaultIID());
		data->SetTransformData( Transform::SpreadCoordinates(), Transform::CurrentOrigin(),Transform::TransformTo( matricies[0], PMMatrix::kHasAllTransformContent), Transform::UseLensScaling());
		result = CmdUtils::ProcessCommand( transformCommand);
	}
	return result;
}

ErrorCode LayerTreeDragDropTarget::HandleLayerProxyDrop(IDragDropController* controller) const
{
	ErrorCode errorCode = kSuccess;
	if(controller->InternalizeDrag(kPMLayerProxyFlavor, kPMLayerProxyFlavor) == kSuccess)
	{
		InterfacePtr<IDataExchangeHandler> handler(controller->QueryTargetHandler());
		
		// Grab the uid of the layer and create a move to layer command onto the target layer
		InterfacePtr<IUIDData> handlerUIDData(handler, UseDefaultIID());
		InterfacePtr<const ITreeNodeIDData>	nodeData(fOldTarget,UseDefaultIID());
		TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
		IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
		IControlView* frontView = context->GetContextView();
		ASSERT_MSG(uidNode->IsLayerEntry(),"Can't drop proxy on non-layer row");
		if (handlerUIDData && frontView)
		{
			bool16 bDuplicate = ::IsOptionAltKeyPressed();
			InterfacePtr<IDocumentLayer> sourceLayer(handlerUIDData->GetRef(), UseDefaultIID());
			InterfacePtr<IDocumentLayer> targetLayer(handlerUIDData->GetItemDataBase(),uidNode->GetUID(), UseDefaultIID());

			if (fCouldDropOnLayer && sourceLayer != targetLayer)
			{
				// Get the UIDs for the source and target layers
				InterfacePtr<ILayerSuite> layerSuite (SelectionUtils::QuerySuite<ILayerSuite>());
				if (layerSuite)
					errorCode = layerSuite->MoveToLayer(sourceLayer, targetLayer, frontView, Selection::kAddTo, bDuplicate);
			}
		}
	}
	return errorCode;
}

ErrorCode LayerTreeDragDropTarget::HandleLayerDrop(IDragDropController* controller) const
{
	ErrorCode errorCode = kSuccess;
	// Get the uid of the current target

	InterfacePtr<const ITreeNodeIDData> iNodeData (fOldTarget, UseDefaultIID());
	TreeNodePtr<const LayerTreeUIDNodeID> oldTargetNode (iNodeData->Get ());
	if(oldTargetNode->IsLayerEntry()) // can't drop layer onto page item
	{
		UID dropLayerUID = oldTargetNode->GetUID();
		UIDRef relativeToLayerRef(fFrontDocDBForDrop, dropLayerUID);

		
		InterfacePtr<const ILayerList> layerList(LayerPanelUtils::GetCurrentLayerPanelDB(this),LayerPanelUtils::GetCurrentLayerPanelDB(this)->GetRootUID(),UseDefaultIID());
		UIDList layersSelectedInPanel = GetLayersToMove(controller,relativeToLayerRef);
		const int32 dropLayerIndex = Utils<ILayerUIUtils>()->GetUILayerIndex(layerList,dropLayerUID);
		int32 dragLayerIndex = -2; // need this to always be invalid.
		if(layersSelectedInPanel.size() == 1)
			dragLayerIndex = Utils<ILayerUIUtils>()->GetUILayerIndex(layerList,layersSelectedInPanel[0]);
			
		if(fHitLocation == kAbove)
		{
			if(dragLayerIndex == dropLayerIndex)
				return kSuccess; // nothing to do.
				
			if(dropLayerIndex == 0)
			{
				relativeToLayerRef = UIDRef(nil, kInvalidUID);
			}
			else
			{
				InterfacePtr<const IDocumentLayer> aboveLayer(Utils<ILayerUIUtils>()->QueryNthUILayer(layerList,dropLayerIndex - 1));
				relativeToLayerRef.ResetUID(::GetUID(aboveLayer));
			}
		}
		else
		{
			if(dragLayerIndex == dropLayerIndex + 1)
				return kSuccess; // nothing to do.
		}

		
		
//		TRACEFLOW("LayerPanel","LayerTreeDragDropTarget::ProcessDragDropCommand old targetUID %d, fHitLocation %d(%s), dropLayerIndex %d\n",dropLayerUID.Get(),fHitLocation,fHitLocation == CTreeViewDragDropTarget::kAbove ? "kAbove" : "not above",dropLayerIndex);
		
		// Make a move layer command for each layer that is selected.
		bool16 bDuplicate = ::IsOptionAltKeyPressed();
		errorCode = Utils<Facade::ILayerFacade>()->MoveLayers(layersSelectedInPanel,relativeToLayerRef,bDuplicate);
	}
	return errorCode;

}

ErrorCode LayerTreeDragDropTarget::MovePageItemToLayer(UID desiredSpreadLayerUID, UID pageItemUID) const
{
	InterfacePtr<const ISpreadLayer> targetSpreadLayer(fFrontDocDBForDrop,desiredSpreadLayerUID, UseDefaultIID());
	InterfacePtr<IDocumentLayer> targetDocLayer(targetSpreadLayer->QueryDocLayer());
//
//#ifdef DEBUG
//	{
//		InterfacePtr<const IPMUnknown> pageItem(fFrontDocDBForDrop, pageItemUID,IID_IUNKNOWN);
//		InterfacePtr<const IDocumentLayer> sourceLayer(QueryDocLayerForPageItem(pageItem));
//		ASSERT_MSG (sourceLayer != targetDocLayer,"Why are we calling MovePageItemToLayer - already on the right layer!");
//	}
//#endif
	{
		if(!targetDocLayer->IsLocked() || ::IsCommandKeyPressed())
		{
			// Get the UIDs for the source and target layers
			UIDList listOfOneItemToMove(fFrontDocDBForDrop,pageItemUID);
			return Utils<Facade::ILayerFacade>()->MoveToLayer(listOfOneItemToMove,targetDocLayer,kFalse);
		}
		return kFailure; // want to move to different layer, but it's locked or not visible.
	}
	return kSuccess;
}

ErrorCode LayerTreeDragDropTarget::ChangeIndexWithinParentIfDifferent(const NodeID & afterThisNode, UID pageItemUID) const
{
	UIDList listOfOneItemToMove(fFrontDocDBForDrop,pageItemUID);
	TreeNodePtr<const LayerTreeUIDNodeID> placeAfterThisNode (afterThisNode);
	TRACEFLOW("LayerPanel","LayerTreeDragDropTarget::ChangeIndexWithinParentIfDifferent - Want to change UID %d to be after UID %d\n",pageItemUID.Get(),placeAfterThisNode->GetUID().Get());
	if(placeAfterThisNode->GetUID() == kInvalidUID)
	{
//		if(Utils<Facade::IArrangeFacade>()->CanBringToFront(listOfOneItemToMove))
		return Utils<Facade::IArrangeFacade>()->ProcessBringToFront(listOfOneItemToMove);
	}
	else
	{
//		if(Utils<Facade::IArrangeFacade>()->CanSendToBack(listOfOneItemToMove,placeAfterThisNode->GetUID()))
		return Utils<Facade::IArrangeFacade>()->ProcessSendToBack(listOfOneItemToMove,placeAfterThisNode->GetUID());
	}
	return kSuccess;
}

ErrorCode LayerTreeDragDropTarget::ChangeHierarchyParentsIfDifferent(UID desiredParentUID, UID pageItemUID) const
{
	InterfacePtr<const IHierarchy> piHier(fFrontDocDBForDrop,pageItemUID,UseDefaultIID());
	UID currentParentUID = piHier->GetParentUID();
	if(desiredParentUID != currentParentUID)
	{
		InterfacePtr<const IHierarchy> desiredParentHier(fFrontDocDBForDrop,desiredParentUID,UseDefaultIID());
		if(desiredParentHier->GetLayerUID() != piHier->GetLayerUID())
		{
			ErrorCode errorCode = MovePageItemToLayer(desiredParentHier->GetLayerUID(),pageItemUID);
			if(errorCode != kSuccess)
				return errorCode;
			currentParentUID = piHier->GetParentUID();
		}
		if(desiredParentUID == currentParentUID)
			return kSuccess; // layer change was all that was needed.
			
		// items have different hierarchy parents. This generally means at least one is in a group.

		// 1. check if this change is allowed
		if(IsParentChangeAllowed(piHier, desiredParentHier))
		{
			// 2. do the hierarchy change
			ErrorCode errorCode = ChangeHierarchyPreservingTransform(::GetUIDRef(piHier),desiredParentUID);

			if(errorCode == kSuccess)
			{
				// 3. if we dragged out of a group and the group now has 1 or 0 items, delete the group.
				InterfacePtr<const IHierarchy> dragParentHier(fFrontDocDBForDrop,currentParentUID,UseDefaultIID());
				if(Utils<IPageItemTypeUtils>()->IsGroup(dragParentHier))
				{
					if(dragParentHier->GetChildCount() < 2)
					{
						if(dragParentHier->GetChildCount() == 1)
						{
							UIDRef onlyChild(fFrontDocDBForDrop,dragParentHier->GetChildUID(0));
							errorCode = ChangeHierarchyPreservingTransform(onlyChild,desiredParentUID);
						}
						if(errorCode == kSuccess)
						{
							InterfacePtr<ICommand> deleteGroupCmd(CmdUtils::CreateCommand(kDeleteCmdBoss));
							deleteGroupCmd->SetItemList(UIDList(::GetUIDRef(dragParentHier)));
							errorCode = CmdUtils::ProcessCommand(deleteGroupCmd);
						}
					}

				}
				// if we're changing hierarchy, we're going to rebuild the tree. Until we do, we can't draw because we have things in the tree that don't exist anymore.
				::SetSysRect(((LayerTreeDragDropTarget*)this)->fPreviousHilite, 0,0,0,0);
			}

			return errorCode;
		}
		else
			return kFailure;

			
	}
	return kSuccess;

}

ErrorCode LayerTreeDragDropTarget::HandlePageItemDrop(IDragDropController* controller) const
{
	ErrorCode errorCode = kSuccess;	

	CmdUtils::SequencePtr cmdSeq; // rolls everything back if anything fails.
	
	if (controller->InternalizeDrag(kPMLayerPageItemZOrderFlavor, kPMLayerPageItemZOrderFlavor) == kSuccess)
	{
		UID newParentUID = kInvalidUID;
		NodeID placeAfterThisNode = LayerTreeUIDNodeID::Create(kInvalidUID,kFalse);						
		errorCode = CalculateWhereToMovePageItem(controller,&newParentUID, placeAfterThisNode );
		if(errorCode != kSuccess)
			return errorCode;
		
		// figure out which items to move, and duplicate them if needed.
		Utils<Facade::IAnimationFacade> iAnimationFacade;
		UIDList pageItemsToMove = GetPageItemsToMove(controller);
		bool doDuplicate = ::IsOptionAltKeyPressed();
		for(int32 i = 0; i < pageItemsToMove.Length() && errorCode == kSuccess; ++i)
		{
			UIDList listOfOneItemToMove(pageItemsToMove.GetRef(i));
			bool isMotionPathItem = iAnimationFacade->IsPageItemMotionPathPageItem (pageItemsToMove.GetRef(i));

			//	Allow drop if duplicating or if dragged item is not a motion path item.
			//	We can duplicate a motion path item.
			if (doDuplicate)
			{
				// duplicate the page item(s)
				InterfacePtr<ICommand> pasteCmd(CmdUtils::CreateCommand(kPasteCmdBoss));
				InterfacePtr<ICopyCmdData> cmdData(pasteCmd, IID_ICOPYCMDDATA);
				InterfacePtr<const IHierarchy> originalDragHier(pageItemsToMove.GetRef(i),UseDefaultIID());
				UID parentUIDOfDrag  = originalDragHier->GetParentUID();
				UIDList *cmdList = new UIDList(listOfOneItemToMove);
				cmdData->Set(pasteCmd, cmdList, UIDRef(fFrontDocDBForDrop, parentUIDOfDrag));
				errorCode = CmdUtils::ProcessCommand(pasteCmd);
				ASSERT_MSG(pasteCmd->GetItemListReference().size() == 1 && listOfOneItemToMove.size() == 1,"Duplicate cmd should have 1 item, and so should my list!");
				TRACEFLOW("LayerPanel","LayerTreeDragDropTarget::HandlePageItemDrop duplicated UID %d. New UID is %d\n",listOfOneItemToMove[0].Get(),pasteCmd->GetItemListReference()[0].Get());
				listOfOneItemToMove.Replace(0,pasteCmd->GetItemListReference().At(0)) ;
			}

			if(errorCode == kSuccess)
			{
				if (doDuplicate || !isMotionPathItem)
				{
					errorCode = ChangeHierarchyParentsIfDifferent(newParentUID,listOfOneItemToMove[0]);
					if(errorCode == kSuccess)
					{
						errorCode = ChangeIndexWithinParentIfDifferent(placeAfterThisNode,listOfOneItemToMove[0]);

					}
				}
			}
		}
	}
	ErrorUtils::PMSetGlobalErrorCode(errorCode); // have to set this so cmdSeq knows something's wrong and it should roll back.
	return errorCode;

}

ErrorCode LayerTreeDragDropTarget::ProcessDragDropCommand(IDragDropController* controller,DragDrop::eCommandType)
{
	ErrorCode errorCode = kSuccess;
	fFrontDocDBForDrop = LayerPanelUtils::GetCurrentLayerPanelDB(this);
	if(!fFrontDocDBForDrop || !fOldTarget)
		return kFailure;
		

	if (fDragFlavor == kPMLayerProxyFlavor)
	{
		errorCode = HandleLayerProxyDrop(controller);
	}
	else	if (fDragFlavor == kPMLayerZOrderFlavor)
	{
		errorCode = HandleLayerDrop(controller);
	}
	else if (fDragFlavor == kPMLayerPageItemZOrderFlavor)
	{
		errorCode = HandlePageItemDrop(controller);
	}
	fFrontDocDBForDrop = nil;
	return errorCode;
}


UIDList LayerTreeDragDropTarget::GetLayersToMove(IDragDropController* controller, UIDRef relativeToLayerRef) const
{		
// figure out which layers we're moving. If the source for the drag is a selected layer, then we'll move all the selected layers. If not, we'll just move that one layer.
	InterfacePtr<const IDataExchangeHandler> handler(controller->QuerySourceHandler());
	InterfacePtr<const IUIDData> uidData(handler,UseDefaultIID());
	UID dragSourceUID = uidData->GetItemUID();
	
	UIDList layersSelectedInPanel(LayerPanelUtils::GetCurrentLayerPanelDB(this));
	LayerPanelUtils::GetTargetLayers(layersSelectedInPanel);
	
	bool foundSourceInSelection = false;
	for (int32 i = layersSelectedInPanel.Length() - 1; i >= 0; --i)
	{
		if(layersSelectedInPanel[i] == dragSourceUID)
		{
			foundSourceInSelection = true;
			break;
		}
	}
	if(!foundSourceInSelection)
	{
		layersSelectedInPanel.Clear();
		layersSelectedInPanel.push_back(dragSourceUID);
	}
	
	// can't move a layer to be relative to itself, so remove it from source list if it's in there.
	for (int32 i = layersSelectedInPanel.Length() - 1; i >= 0; --i)
	{
		if(layersSelectedInPanel[i] == relativeToLayerRef.GetUID())
			layersSelectedInPanel.Remove(i);
	}

	// Fix for #2796762, layers move will be reversed in z-order since they get moved relative to a layer (the same layer for each move).
	// However, if we reverse the list first, this won't happen.
	std::reverse(layersSelectedInPanel.begin(), layersSelectedInPanel.end());
	return layersSelectedInPanel;
}


UIDList LayerTreeDragDropTarget::GetPageItemsToMove(IDragDropController* controller) const
{	
	UIDList listOfPageItems = LayerPanelUtils::GetPageItemsInDrag(this,controller);
			
	// can't move a page item to be relative to itself, so remove it from source list if it's in there. Also can't change z-order of an inline.
	// motion path page item is a temporary page item for editing motion path only, should not be moved.
	InterfacePtr<const ITreeNodeIDData> iNodeData (fOldTarget, UseDefaultIID());
	TreeNodePtr<const LayerTreeUIDNodeID> dropNode (iNodeData->Get ());
	UID dropNodeUID = dropNode->GetUID();
	
	for (int32 i = listOfPageItems.Length() - 1; i >= 0; --i)
	{
		UIDRef itemRef(fFrontDocDBForDrop,listOfPageItems[i]);
		if(listOfPageItems[i] == dropNodeUID || Utils<IPageItemTypeUtils>()->IsPlacedInsideText(itemRef))
			listOfPageItems.Remove(i);
			
	}

	// Fix for #2796762, items moved will be reversed in z-order since they get moved relative to a page item (the same item for each move).
	// However, if we reverse the list first, this won't happen.
	std::reverse(listOfPageItems.begin(), listOfPageItems.end());
	return listOfPageItems;

}

UID LayerTreeDragDropTarget::GetSpreadLayerUIDFromDocLayer(UID docLayerUID) const
{
	InterfacePtr<const ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
	if(layoutData)
	{
		UIDRef spreadRef = layoutData->GetSpreadRef();
		InterfacePtr<const ISpread> activeSpread(spreadRef,UseDefaultIID());
		InterfacePtr<const IDocumentLayer> docLayer(fFrontDocDBForDrop,docLayerUID,UseDefaultIID());
		InterfacePtr<const ISpreadLayer> spreadLayer(activeSpread->QueryLayer(docLayer));
		return ::GetUID(spreadLayer);
	}
	return kInvalidUID;
}

ErrorCode LayerTreeDragDropTarget::CalculateWhereToMovePageItem(IDragDropController* controller, UID* outNewParentUID, NodeID & afterThisNode ) const
{		
		// first check if they dropped on a layer.
	InterfacePtr<ITreeNodeIDData>		dropWidgetNodeData(fOldTarget, UseDefaultIID());	
	TreeNodePtr<const LayerTreeUIDNodeID>	layerPanelDropNode(dropWidgetNodeData->Get());
	TRACEFLOW("LayerPanel","CalculateWhereToMovePageItem thinks we dropped relative to UID %d\n",layerPanelDropNode->GetUID().Get());

	InterfacePtr<const ITreeViewHierarchyAdapter>	adapter(this, UseDefaultIID());

	NodeID rootNode = adapter->GetRootNode();
	TreeNodePtr<const LayerTreeUIDNodeID> rootElement(rootNode);
	if (rootElement->GetUID() == layerPanelDropNode->GetUID() || layerPanelDropNode->GetUID() == kInvalidUID)
		return kFailure; // can't drop on root node
		
	if(layerPanelDropNode->IsLayerEntry())
	{
		// dropped on a layer - if it's kBelow, move it to first position in layer.
		// if it's kAbove, move it to end of previous layer.
		if (fHitLocation != kAbove) 
		{
			*outNewParentUID = GetSpreadLayerUIDFromDocLayer(layerPanelDropNode->GetUID());
			afterThisNode = LayerTreeUIDNodeID::Create(kInvalidUID,kFalse);						
		}
		else
		{
			InterfacePtr<const ILayerList> layerList(fFrontDocDBForDrop,fFrontDocDBForDrop->GetRootUID(),UseDefaultIID());
			int32 layerIndex = Utils<ILayerUIUtils>()->GetUILayerIndex(layerList,layerPanelDropNode->GetUID());
			if(layerIndex <= 0)
				return kFailure;
			InterfacePtr<IDocumentLayer> prevDocLayer(Utils<ILayerUIUtils>()->QueryNthUILayer(layerList,layerIndex - 1));
			*outNewParentUID = GetSpreadLayerUIDFromDocLayer(::GetUID(prevDocLayer));
			NodeID parentNode = LayerTreeUIDNodeID::Create(::GetUID(prevDocLayer),kTrue);	
			if(adapter->GetNumChildren(parentNode) > 0)					
				afterThisNode = adapter->GetNthChild(parentNode,adapter->GetNumChildren(parentNode) - 1);
			else
				afterThisNode = LayerTreeUIDNodeID::Create(kInvalidUID,kFalse);						
		}
		//TRACEFLOW("LayerPanel","CalculateWhereToMovePageItem thinks we dropped on a layer and should parent this drag to UID %d at index %d\n",outNewParentUID->Get(), *indexWithinParent);
		return kSuccess;
			
	}
			
	NodeID parentNode = adapter->GetParentNode( dropWidgetNodeData->Get() );
	afterThisNode = dropWidgetNodeData->Get();
	
	TreeNodePtr<const LayerTreeUIDNodeID>	parentUIDNode(parentNode);
	if(parentUIDNode->IsLayerEntry())
	{
		// the UID in the panel is the document layer.
		// we want the UID for the spread layer.
		*outNewParentUID = GetSpreadLayerUIDFromDocLayer(parentUIDNode->GetUID());
	}
	else
	{
		*outNewParentUID = parentUIDNode->GetUID();
	}
	// If we are not moving to the top of the list AND
	// We are moving above the selected node AND
	// We are not moving the object into its own location
	// Then subtract one to move the node before rather than after
	// the specified node.

	InterfacePtr<const IDataExchangeHandler> handler(controller->QuerySourceHandler());
	InterfacePtr<const IUIDData> uidData(handler,UseDefaultIID());
	UID dragSourceUID = uidData->GetItemUID();
	NodeID movingNode = LayerTreeUIDNodeID::Create(dragSourceUID,kFalse);						
	TreeNodePtr<const LayerTreeUIDNodeID>	movingNodeUID(movingNode);
	if (movingNodeUID->GetUID() == layerPanelDropNode->GetUID())
		return kFailure; // dropped on self

	if (fHitLocation == kAbove) 
	{
		TRACEFLOW("LayerPanel","CalculateWhereToMovePageItem thinks we dropped above UID %d\n",layerPanelDropNode->GetUID().Get());
		
		int32 dropItemIndex = adapter->GetChildIndex(parentNode, afterThisNode);
		if(dropItemIndex == 0)
			afterThisNode = LayerTreeUIDNodeID::Create(kInvalidUID,kFalse);	
		else
			afterThisNode = adapter->GetNthChild(parentNode,dropItemIndex - 1);
		
	}
	
//	TRACEFLOW("LayerPanel","CalculateWhereToMovePageItem thinks we should parent this drag to UID %d at index %d\n",outNewParentUID->Get(), *indexWithinParent);
	return kSuccess;
}

bool LayerTreeDragDropTarget::IsParentChangeAllowed(const IHierarchy* pageItemHier, const IHierarchy* desiredParentHier) const
{
	if(!pageItemHier || !desiredParentHier) 
		return false;

	Utils<IPageItemTypeUtils> pitUtils;

	// only allow parent change if new parent is group or spreadlayer
	if (!pitUtils->IsGroup(desiredParentHier) 
		&& ::GetUID(desiredParentHier) != desiredParentHier->GetLayerUID())
		return false;

	// The following checks have been added to address bug #2415970.
	// - MC 08/31/09

	// do not allow the direct child of a button or mso to be moved
	InterfacePtr<IHierarchy> parentOfPIHier(pageItemHier->QueryParent());
	if (parentOfPIHier 
		&& (pitUtils->PageItemHasAppearanceList(parentOfPIHier)))
	{
		return false;
	}
	
	// if the desired parent has an MSO or button ancestor, make sure that we can place the page item in it
	IDataBase* db = ::GetDataBase(desiredParentHier);
	UIDList appearanceItemAncestors(db);

	desiredParentHier->GetAncestors(&appearanceItemAncestors, IID_IAPPEARANCELIST);
	if (!appearanceItemAncestors.IsEmpty())
	{
		UIDRef pageItemRef = ::GetUIDRef(pageItemHier);
		for(UIDList::const_iterator itr = appearanceItemAncestors.begin();
			itr != appearanceItemAncestors.end();
			++itr)
		{
			if(!Utils<IFormFieldUtils>()->CanPlaceInState(pageItemRef, db->GetClass(*itr)))
				return false;
		}
	}

	return true;
}