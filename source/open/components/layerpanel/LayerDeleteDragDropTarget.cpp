//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerDeleteDragDropTarget.cpp $
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
//  Layer drop target for delete button
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CButtonDragDropTarget.h"

#include "LayerPanelID.h"
#include "DragDropID.h"
#include "LayoutUIID.h"
#include "AppUIID.h"

#include "ICmdCollection.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "IPageItemScrapFacade.h"

#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"
#include "CmdUtils.h"
#include "LayerPanelUtils.h"
#include "EventUtilities.h"
#include "IPalettePanelUtils.h"
#include "UIDList.h"

class LayerDeleteDragDropTarget : public CButtonDragDropTarget
{
	public:
									LayerDeleteDragDropTarget(IPMUnknown *boss);
		virtual						~LayerDeleteDragDropTarget();
		
		virtual DragDrop::TargetResponse		CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);

		void DoDragEnter();
		
		mutable ExternalPMFlavor			fDragFlavor;			// local cache: what is being dragged?
		
		DECLARE_HELPER_METHODS()
};


//========================================================================
// Class LayerDeleteDragDropTarget
//========================================================================
CREATE_PMINTERFACE(LayerDeleteDragDropTarget, kLayerDeleteDragDropTargetImpl)
DEFINE_HELPER_METHODS(LayerDeleteDragDropTarget)

LayerDeleteDragDropTarget::LayerDeleteDragDropTarget(IPMUnknown *boss) :
	CButtonDragDropTarget(boss),
	fDragFlavor(kNoExternalFlavor),
	HELPER_METHODS_INIT(boss)
{
}

LayerDeleteDragDropTarget::~LayerDeleteDragDropTarget()
{
}

//--------------------------------------------------------------------------------------
// WillAcceptDrop
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse LayerDeleteDragDropTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* /*fromSource*/, const IDragDropController* controller) const
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
			InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kLayerParentWidgetId));
			bool16 canDelete = LayerPanelUtils::CanDeleteTargetLayers(panelData);
			if (canDelete)
				return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy,DragDrop::kUseDefaultTrackingFeedback,DragDrop::kTargetWillProvideCursorFeedback);	// Always copy in the drag and drop sense
		}			
		response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMLayerPageItemZOrderFlavor);
		if (response.CanDo())
		{
			fDragFlavor = kPMLayerPageItemZOrderFlavor;
			UIDList itemsInDrag = LayerPanelUtils::GetPageItemsInDrag(this,controller);
			if(Utils<Facade::IPageItemScrapFacade>()->CanDeletePageItems(itemsInDrag))
				return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy,DragDrop::kUseDefaultTrackingFeedback,DragDrop::kTargetWillProvideCursorFeedback);	// Always copy in the drag and drop sense
		}
		response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMLayerPageItemDupDeleteFlavor);
		if (response.CanDo())
		{
			fDragFlavor = kPMLayerPageItemDupDeleteFlavor;
			UIDList itemsInDrag = LayerPanelUtils::GetPageItemsInDrag(this,controller);
			if(Utils<Facade::IPageItemScrapFacade>()->CanDeletePageItems(itemsInDrag))
				return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy,DragDrop::kUseDefaultTrackingFeedback,DragDrop::kTargetWillProvideCursorFeedback);	// Always copy in the drag and drop sense
		}
	}
	return DragDrop::kWontAcceptTargetResponse;
}

void LayerDeleteDragDropTarget::DoDragEnter()
{
	CButtonDragDropTarget::DoDragEnter();
	if(fDragFlavor == kPMLayerZOrderFlavor || fDragFlavor == kPMLayerPageItemZOrderFlavor || fDragFlavor == kPMLayerPageItemDupDeleteFlavor)
	{
		InterfacePtr<IDragDropController> ddController (GetExecutionContextSession(), UseDefaultIID ());
		CursorSpec	newCursor (kAppUIPluginID, kCrsrClosedHand); // make sure we're not showing the plus sign - even if they're holding down the option key.
		ddController->SetTrackingCursorFeedback (newCursor);		
	}
}

//--------------------------------------------------------------------------------------
// ProcessDragDropCommand
//--------------------------------------------------------------------------------------
ErrorCode	LayerDeleteDragDropTarget::ProcessDragDropCommand(
		IDragDropController* controller,
		DragDrop::eCommandType )
{
	ErrorCode errorCode = kFailure;

	if(fDragFlavor == kPMLayerZOrderFlavor)
	{
		ICommand* command = nil;
		
		IDataBase* docDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
		if (docDB)
		{
			bool16 optionKeyDown = ::IsOptionAltKeyPressed();
			command = LayerPanelUtils::CreateDeleteLayersCmd(!optionKeyDown, this);
		}
		
		if ( command )
		{
			errorCode = CmdUtils::ProcessCommand (command);
			command->Release();
		}
	}
	else if(fDragFlavor == kPMLayerPageItemZOrderFlavor || fDragFlavor == kPMLayerPageItemDupDeleteFlavor)
	{
		UIDList itemsInDrag = LayerPanelUtils::GetPageItemsInDrag(this,controller);
		errorCode = Utils<Facade::IPageItemScrapFacade>()->DeletePageItems(itemsInDrag);
	}
	
	return errorCode;
}
