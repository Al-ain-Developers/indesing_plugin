//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerEyeDragDropTarget.cpp $
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
//  Implementation of a Drag and Drop target for layer panel eye
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "LayerPanelID.h"
#include "DragDropID.h"
#include "LayerID.h"

#include "IEvent.h"
#include "IDragDropController.h"
#include "IUIDData.h"
#include "IControlView.h"
#include "ILayoutUIUtils.h"
#include "IDocumentLayer.h"
#include "IWidgetParent.h"
#include "IBoolData.h"
#include "IPanelControlData.h"
#include "ITreeNodeIDData.h"
#include "IPageItemVisibilityFacade.h"
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

class LayerEyeDragDropTarget : public CDragDropTarget
{
	public:
									LayerEyeDragDropTarget(IPMUnknown *boss);
		virtual						~LayerEyeDragDropTarget();
		
		virtual DragDrop::TargetResponse		CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual void				DoDragEnter();
		virtual void				DoDragWithin(const PMPoint& localPt);
		virtual void				DoDragLeave();
			// Tracking the drag as it enters, drags, and leaves this target

		virtual SysWireframe				DoMakeDropHiliteRegion() const { return nil; }
			// Default drop outline not wanted for eye
		
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
			// Create the commands needed to complete a drop 
			// 	(targets will only receive kDragMove or kDrop)
			
	private:		
		DECLARE_HELPER_METHODS()
};

CREATE_PMINTERFACE(LayerEyeDragDropTarget, kLayerEyeDragDropTargetImpl)
DEFINE_HELPER_METHODS(LayerEyeDragDropTarget)

LayerEyeDragDropTarget::LayerEyeDragDropTarget(IPMUnknown *boss)  :
	CDragDropTarget(boss),
	HELPER_METHODS_INIT(boss)
{
}


LayerEyeDragDropTarget::~LayerEyeDragDropTarget()
{
}

//--------------------------------------------------------------------------------------
// WillAcceptDrop
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse LayerEyeDragDropTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* , const IDragDropController*) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMLayerEyeFlavor);
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
void LayerEyeDragDropTarget::DoDragEnter()
{
	// Normally for drag and drop a command would be issued in ProcessDragDropCommand.
	// For the eyeball though, we send the command as soon as the mouse enters the control.
	InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
	if (ddController)
		this->ProcessDragDropCommand(ddController, DragDrop::kDrop);
}

//--------------------------------------------------------------------------------------
// DoDragWithin
//--------------------------------------------------------------------------------------
void LayerEyeDragDropTarget::DoDragWithin(const PMPoint& )
{
}

//--------------------------------------------------------------------------------------
// DoDragLeave
//--------------------------------------------------------------------------------------
void LayerEyeDragDropTarget::DoDragLeave()
{
}

void SendVisibilityChangeCmd(const ITreeViewMgr* treeMgr, const UIDRef& objectRef, bool16 startingState)
{
	InterfacePtr<const IDocumentLayer> curLayer(objectRef,UseDefaultIID());
	if(curLayer)
	{
		if (curLayer->IsUILayer() && curLayer->IsVisible() == startingState)
		{
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kShowLayerCmdBoss));
			cmd->SetItemList(  UIDList(curLayer));
			InterfacePtr<IBoolData> data(cmd, IID_IBOOLDATA);
			data->Set(!curLayer->IsVisible());
			CmdUtils::ProcessCommand(cmd);
		}
	}
	else
	{
		if(startingState)
		{
			Utils<Facade::IPageItemVisibilityFacade>()->Hide(objectRef);
		}
		else
		{
			Utils<Facade::IPageItemVisibilityFacade>()->Show(objectRef);
		}
	}

	// Draw the new state. Normally observer would watch for messages, but
	// we want it to happen immediately so user sees feedback while mouse is still down.
	NodeID changedNode = LayerTreeUIDNodeID::Create(objectRef.GetUID(),curLayer != nil);						
	InterfacePtr<IControlView> layerRowView(treeMgr->QueryWidgetFromNode(changedNode));
	if (layerRowView)
	{	
		InterfacePtr<const IPanelControlData> rowPanelData(layerRowView,UseDefaultIID());
		IControlView * pencilControlView = rowPanelData->FindWidget(kLayerListElementEyeballWidgetID);
		pencilControlView->SetRsrcID(startingState ? kNoIcon : kEyeballIcon);
		pencilControlView->ForceRedraw();
	}
}

//--------------------------------------------------------------------------------------
// ProcessDragDropCommand
//--------------------------------------------------------------------------------------
ErrorCode	LayerEyeDragDropTarget::ProcessDragDropCommand(
		IDragDropController* controller,
		DragDrop::eCommandType )
{
	ErrorCode errorCode = kFailure;

	if (controller->InternalizeDrag(kPMLayerEyeFlavor, kPMLayerEyeFlavor) == kSuccess)
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
			
			SendVisibilityChangeCmd(treeMgr,startingObjectRef,startingState);
			SendVisibilityChangeCmd(treeMgr,itemUIDRef,startingState);
			
			return kSuccess;
		}
	}
	
	return errorCode;
}
