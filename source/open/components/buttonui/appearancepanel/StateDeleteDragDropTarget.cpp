//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/StateDeleteDragDropTarget.cpp $
//  
//  Owner: Tim Wright
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
//  Based on LayerDeleteDragDropTarget.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CButtonDragDropTarget.h"

#include "DragDropID.h"
#include "LayoutUIID.h"

#include "ICmdCollection.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"

#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"
#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "EventUtilities.h"
#include "IPalettePanelUtils.h"

#include "FormFieldUIID.h"
#include "AppearancePanelUtils.h"
#include "PMFlavorTypes.h"

class StateDeleteDragDropTarget : public CButtonDragDropTarget
{
	public:
									StateDeleteDragDropTarget(IPMUnknown *boss);
		virtual						~StateDeleteDragDropTarget();
		
		virtual DragDrop::TargetResponse		CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
			// Create the commands needed to complete a drop 
			// 	(targets will only receive kDragMove or kDrop)
		
		DECLARE_HELPER_METHODS()
};


//========================================================================
// Class StateDeleteDragDropTarget
//========================================================================
CREATE_PMINTERFACE(StateDeleteDragDropTarget, kStateDeleteDragDropTargetImpl)
DEFINE_HELPER_METHODS(StateDeleteDragDropTarget)

StateDeleteDragDropTarget::StateDeleteDragDropTarget(IPMUnknown *boss) :
	CButtonDragDropTarget(boss),
	HELPER_METHODS_INIT(boss)
{
}

StateDeleteDragDropTarget::~StateDeleteDragDropTarget()
{
}

//--------------------------------------------------------------------------------------
// WillAcceptDrop
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse StateDeleteDragDropTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController*) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		// Unique layer panel flavor (same as the flavor for rearranging layers since the
		// source is also the listbox). Make ssure we don't accept drops from other palettes
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMStateProxyFlavor);
		if (!response.CanDo())
			return DragDrop::kWontAcceptTargetResponse;

		// Get IPanelControlData for the layer panel itself
		InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId));

		bool16 canDelete = CanDeleteSelectedStates(panelData);
		if (canDelete)
			return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);	// Always copy in the drag and drop sense
	}
	return DragDrop::kWontAcceptTargetResponse;
}

//--------------------------------------------------------------------------------------
// ProcessDragDropCommand
//--------------------------------------------------------------------------------------
ErrorCode	StateDeleteDragDropTarget::ProcessDragDropCommand(
		IDragDropController* controller,
		DragDrop::eCommandType type)
{
	ErrorCode errorCode = kFailure;
	
	InterfacePtr<IControlView> frontView(Utils<ILayoutUIUtils>()->QueryFrontView());
	if (frontView)
	{
		bool16 optionKeyDown = ::IsOptionAltKeyPressed();

		// Get widgetparent for the layer panel itself, 2 levels up
		InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId));
		errorCode = DeleteSelectedStates(panelData);
	}
		
	return errorCode;
}
