//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPencilDragDropTarget.cpp $
//  
//  Owner: Paul Sorrick
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
//  Implementation of a Drag and Drop target for layer panel pencil
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "LayerPanelID.h"
#include "DragDropID.h"
#include "LayerID.h"

#include "IEvent.h"
#include "IDragDropController.h"
#include "IUIDData.h"
#include "IControlView.h"
#include "IDocumentLayer.h"
#include "ILayoutUIUtils.h"
#include "IWidgetParent.h"
#include "IBoolData.h"
#include "IPanelControlData.h"
#include "ITreeNodeIDData.h"
#include "IPageItemLockFacade.h"
#include "ITreeViewMgr.h"
#include "IDocument.h"

#include "CDragDropTarget.h"
#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"
#include "CmdUtils.h"
#include "UIDList.h"
#include "LayerPanelDefs.h"
#include "LayerTreeUIDNodeID.h"
#include "LayerPanelUtils.h"

class LayerPencilDragDropTarget : public CDragDropTarget
{
	public:
									LayerPencilDragDropTarget(IPMUnknown *boss);
		virtual						~LayerPencilDragDropTarget();
		
		virtual DragDrop::TargetResponse	CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual void				DoDragEnter();
		virtual void				DoDragWithin(const PMPoint& localPt);
		virtual void				DoDragLeave();
			// Tracking the drag as it enters, drags, and leaves this target

		virtual SysWireframe				DoMakeDropHiliteRegion() const { return nil; }
			// Default drop outline not wanted for pencil
		
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
			// Create the commands needed to complete a drop 
			// 	(targets will only receive kDragMove or kDrop)
			
	private:
		
		DECLARE_HELPER_METHODS()
};

CREATE_PMINTERFACE(LayerPencilDragDropTarget, kLayerPencilDragDropTargetImpl)
DEFINE_HELPER_METHODS(LayerPencilDragDropTarget)

LayerPencilDragDropTarget::LayerPencilDragDropTarget(IPMUnknown *boss)  :
	CDragDropTarget(boss),
	HELPER_METHODS_INIT(boss)
{
}


LayerPencilDragDropTarget::~LayerPencilDragDropTarget()
{
}

//--------------------------------------------------------------------------------------
// WillAcceptDrop
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse LayerPencilDragDropTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* , const IDragDropController*) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMLayerPencilFlavor);
		if (!response.CanDo())
			return DragDrop::kWontAcceptTargetResponse;
		else
			return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);	// Always copy in the drag and drop sense
	}
	return DragDrop::kWontAcceptTargetResponse;
}

//--------------------------------------------------------------------------------------
// DoDragEnter
//--------------------------------------------------------------------------------------
void LayerPencilDragDropTarget::DoDragEnter()
{
	// Normally for drag and drop a command would be issued in ProcessDragDropCommand.
	// For the pencil though, we send the command as soon as the mouse enters the control.
	InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
	if (ddController)
		this->ProcessDragDropCommand(ddController, DragDrop::kDrop);
}

//--------------------------------------------------------------------------------------
// DoDragWithin
//--------------------------------------------------------------------------------------
void LayerPencilDragDropTarget::DoDragWithin(const PMPoint& )
{
}

//--------------------------------------------------------------------------------------
// DoDragLeave
//--------------------------------------------------------------------------------------
void LayerPencilDragDropTarget::DoDragLeave()
{
}

void SendLockCmd(const ITreeViewMgr* treeMgr, const UIDRef& objectRef, bool16 startingState)
{
	InterfacePtr<const IDocumentLayer> curLayer(objectRef,UseDefaultIID());
	if(curLayer)
	{
		if (curLayer->IsUILayer() && curLayer->IsLocked() == startingState)
		{
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kLockLayerCmdBoss));
			cmd->SetItemList(  UIDList(curLayer));
			InterfacePtr<IBoolData> data(cmd, UseDefaultIID());
			data->Set(!curLayer->IsLocked());
			CmdUtils::ProcessCommand(cmd);
						
		}
	}
	else
	{
		UIDList itemList(objectRef);
		if(!startingState && Utils<Facade::IPageItemLockFacade>()->CanLock(itemList))
		{
			Utils<Facade::IPageItemLockFacade>()->LockPageItems(itemList);
		}
		else if(startingState && Utils<Facade::IPageItemLockFacade>()->CanUnlock(itemList))
		{
			Utils<Facade::IPageItemLockFacade>()->UnlockPageItems(itemList);
		}
	}

	// Draw the new state. Normally observer would watch for kLockLayerCmdBoss, but
	// we want it to happen immediately so user sees feedback while mouse is still down.
	NodeID changedNode = LayerTreeUIDNodeID::Create(objectRef.GetUID(),curLayer != nil);						
	InterfacePtr<IControlView> layerRowView(treeMgr->QueryWidgetFromNode(changedNode));
	if (layerRowView)
	{	
		InterfacePtr<const IPanelControlData> rowPanelData(layerRowView,UseDefaultIID());
		IControlView * pencilControlView = rowPanelData->FindWidget(curLayer == nil ? kLayerPageItemElementPencilWidgetID : kLayerListElementPencilWidgetID);
		pencilControlView->SetRsrcID(startingState ? kLayerNotLockedIcon : kLayerLockedIcon);
		pencilControlView->ForceRedraw();
	}

}

ErrorCode	LayerPencilDragDropTarget::ProcessDragDropCommand(
		IDragDropController* controller,
		DragDrop::eCommandType )
{
	if (controller->InternalizeDrag(kPMLayerPencilFlavor, kPMLayerPencilFlavor) == kSuccess)
	{
		InterfacePtr<IDataExchangeHandler> handler(controller->QueryTargetHandler());
		
		// Grab the uid of the layer where the user moused down (startingDocLayerUID),
		// Also grab the starting layer states (startingState).
		InterfacePtr<const IUIDData> handlerUIDData(handler, UseDefaultIID());
		InterfacePtr<const IBoolData> handlerBoolData(handler, UseDefaultIID());
		if (handlerUIDData && handlerBoolData)
		{
			const UIDRef startingObjectRef = handlerUIDData->GetRef();
			bool16 startingState = handlerBoolData->GetBool();
			
			// Get the uid and state of the current target
			InterfacePtr<const IWidgetParent>	widgetParent(this, UseDefaultIID());
			InterfacePtr<const ITreeNodeIDData>	nodeData((ITreeNodeIDData*)widgetParent->QueryParentFor(IID_ITREENODEIDDATA));
			InterfacePtr<const ITreeViewMgr>	 treeMgr((ITreeViewMgr*)widgetParent->QueryParentFor(ITreeViewMgr::kDefaultIID));
			NodeID treeNode = nodeData->Get();
			TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(treeNode);
			UIDRef itemUIDRef = UIDRef(LayerPanelUtils::GetCurrentLayerPanelDB(this),uidNode->GetUID());
			
			SendLockCmd(treeMgr,startingObjectRef,startingState);
			SendLockCmd(treeMgr,itemUIDRef,startingState);
			
			return kSuccess;
		}
	}

	return kFailure;
}
