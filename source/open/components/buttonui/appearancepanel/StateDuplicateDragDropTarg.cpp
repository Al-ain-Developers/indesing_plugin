//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/StateDuplicateDragDropTarg.cpp $
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
//  This drag and drop target duplicates the selected states that are
//  dropped on it. 
//  
//  Based on LayerDuplicateDragDropTarg.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"



#include "ICmdCollection.h"
#include "IControlView.h"
#include "IPanelControlData.h"

#include "DragDropID.h"
#include "LayoutUIID.h"
#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"
#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "EventUtilities.h"
#include "IPalettePanelUtils.h"
#include "CButtonDragDropTarget.h"

#include "IAppearanceSuite.h"
#include "FormFieldUIID.h"
#include "AppearancePanelUtils.h"
#include "FormFieldUIUtils.h"
#include "PMFlavorTypes.h"

class StateDuplicateDragDropTarget : public CButtonDragDropTarget
{
	public:
									StateDuplicateDragDropTarget(IPMUnknown *boss);
		virtual						~StateDuplicateDragDropTarget();
		
		virtual DragDrop::TargetResponse	CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
			// Create the commands needed to complete a drop 
			// 	(targets will only receive kDragMove or kDrop)
		
		DECLARE_HELPER_METHODS()
};


//========================================================================
// Class StateDuplicateDragDropTarget
//========================================================================
CREATE_PMINTERFACE(StateDuplicateDragDropTarget, kStateDuplicateDragDropTargetImpl)
DEFINE_HELPER_METHODS(StateDuplicateDragDropTarget)

StateDuplicateDragDropTarget::StateDuplicateDragDropTarget(IPMUnknown *boss) :
	CButtonDragDropTarget(boss),
	HELPER_METHODS_INIT(boss)
{
}

StateDuplicateDragDropTarget::~StateDuplicateDragDropTarget()
{
}

//--------------------------------------------------------------------------------------
// WillAcceptDrop
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse StateDuplicateDragDropTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController*) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		// Unique layer panel flavor (same as the flavor for rearranging layers since the
		// source is also the listbox). Make ssure we don't accept drops from other palettes
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMStateProxyFlavor);
		if (!response.CanDo())
			return DragDrop::kWontAcceptTargetResponse;
		
		// Check if we can add a new state or not
		if ( CanCreateNewState() )
			return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);	// Always copy in the drag and drop sense
		else
			return DragDrop::kWontAcceptTargetResponse;
		
	}
	return DragDrop::kWontAcceptTargetResponse;
}

//--------------------------------------------------------------------------------------
// ProcessDragDropCommand
//--------------------------------------------------------------------------------------
ErrorCode	StateDuplicateDragDropTarget::ProcessDragDropCommand(
		IDragDropController* controller,
		DragDrop::eCommandType type)
{
	ErrorCode errorCode = kFailure;

	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	InterfacePtr<IControlView> frontView(Utils<ILayoutUIUtils>()->QueryFrontView());
	
	if (frontView && iAppearanceSuite)
	{
		// Get IPanelControlData for the layer panel itself, 2 levels up
		InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId));

		errorCode = DuplicateStates(panelData);
	}
	return errorCode;
}
