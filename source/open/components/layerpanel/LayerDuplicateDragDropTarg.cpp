//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerDuplicateDragDropTarg.cpp $
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
//  Layer drop target for new button
//  
//  This drag and drop target duplicates the selected layers that are
//  dropped on it. New layers are created with same settings. Content
//  on layers is NOT duplicated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CButtonDragDropTarget.h"

#include "LayerPanelID.h"
#include "DragDropID.h"
#include "LayoutUIID.h"
#include "AppUIID.h"

#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"
#include "CmdUtils.h"
#include "LayerPanelUtils.h"
#include "EventUtilities.h"
#include "ILayerFacade.h"
#include "IDocument.h"
#include "UIDList.h"
#include "IPageItemScrapFacade.h"
#include "Utils.h"

class LayerDuplicateDragDropTarget : public CButtonDragDropTarget
{
	public:
									LayerDuplicateDragDropTarget(IPMUnknown *boss);
		virtual						~LayerDuplicateDragDropTarget();
		
		virtual DragDrop::TargetResponse	CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
		void DoDragEnter();
			// Create the commands needed to complete a drop 
			// 	(targets will only receive kDragMove or kDrop)
		mutable ExternalPMFlavor			fDragFlavor;			// local cache: what is being dragged?
		
		DECLARE_HELPER_METHODS()
};


//========================================================================
// Class LayerDuplicateDragDropTarget
//========================================================================
CREATE_PMINTERFACE(LayerDuplicateDragDropTarget, kLayerDuplicateDragDropTargetImpl)
DEFINE_HELPER_METHODS(LayerDuplicateDragDropTarget)

LayerDuplicateDragDropTarget::LayerDuplicateDragDropTarget(IPMUnknown *boss) :
	CButtonDragDropTarget(boss),
	fDragFlavor(kNoExternalFlavor),
	HELPER_METHODS_INIT(boss)
{
}

LayerDuplicateDragDropTarget::~LayerDuplicateDragDropTarget()
{
}

//--------------------------------------------------------------------------------------
// WillAcceptDrop
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse LayerDuplicateDragDropTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* , const IDragDropController* controller) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		// Unique layer panel flavor (same as the flavor for rearranging layers since the
		// source is also the listbox). Make ssure we don't accept drops from other palettes
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMLayerZOrderFlavor);
		if (response.CanDo())
		{
			fDragFlavor = kPMLayerZOrderFlavor;
			return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy,DragDrop::kUseDefaultTrackingFeedback,DragDrop::kTargetWillProvideCursorFeedback);	// Always copy in the drag and drop sense
		}			
		response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMLayerPageItemZOrderFlavor);
		if (response.CanDo())
		{
			fDragFlavor = kPMLayerPageItemZOrderFlavor;
			UIDList itemsInDrag = LayerPanelUtils::GetPageItemsInDrag(this,controller);
			if(Utils<Facade::IPageItemScrapFacade>()->CanDuplicatePageItems(itemsInDrag))
				return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy,DragDrop::kUseDefaultTrackingFeedback,DragDrop::kTargetWillProvideCursorFeedback);	// Always copy in the drag and drop sense
		}
		response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMLayerPageItemDupDeleteFlavor);
		if (response.CanDo())
		{
			fDragFlavor = kPMLayerPageItemDupDeleteFlavor;
			UIDList itemsInDrag = LayerPanelUtils::GetPageItemsInDrag(this,controller);
			if(Utils<Facade::IPageItemScrapFacade>()->CanDuplicatePageItems(itemsInDrag))
				return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy,DragDrop::kUseDefaultTrackingFeedback,DragDrop::kTargetWillProvideCursorFeedback);	// Always copy in the drag and drop sense
		}
	}
	return DragDrop::kWontAcceptTargetResponse;
}

void LayerDuplicateDragDropTarget::DoDragEnter()
{
	CButtonDragDropTarget::DoDragEnter();
	if(fDragFlavor == kPMLayerZOrderFlavor || fDragFlavor == kPMLayerPageItemZOrderFlavor || fDragFlavor == kPMLayerPageItemDupDeleteFlavor)
	{
		InterfacePtr<IDragDropController> ddController (GetExecutionContextSession(), UseDefaultIID ());
		CursorSpec	newCursor (kAppUIPluginID, kCrsrClosedHandCopy);
		ddController->SetTrackingCursorFeedback (newCursor);		
	}
}


//--------------------------------------------------------------------------------------
// ProcessDragDropCommand
//--------------------------------------------------------------------------------------
ErrorCode	LayerDuplicateDragDropTarget::ProcessDragDropCommand(
		IDragDropController* controller ,
		DragDrop::eCommandType )
{
	if(fDragFlavor == kPMLayerZOrderFlavor)
	{
		return LayerPanelUtils::DuplicateSelectedLayers();
	}
	else if(fDragFlavor == kPMLayerPageItemZOrderFlavor || fDragFlavor == kPMLayerPageItemDupDeleteFlavor)
	{
		UIDList itemsInDrag = LayerPanelUtils::GetPageItemsInDrag(this,controller);
		return Utils<Facade::IPageItemScrapFacade>()->DuplicatePageItems(itemsInDrag);
	}
	return kFailure;
}
