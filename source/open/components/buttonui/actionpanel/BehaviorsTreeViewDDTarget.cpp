//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorsTreeViewDDTarget.cpp $
//  
//  Owner: Michael Burbidge
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

// ----- Interface Includes -----

#include "IBehaviorSuite.h"
#include "IDragDropController.h"
#include "IBehaviorDragDropData.h"
#include "ITreeNodeIDData.h"
#include "IBehaviorData.h"
#include "IBehaviorEventData.h"
#include "FormFieldUIUtils.h"
#include "IIntData.h"
#include "IMoveBehaviorData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "SelectionUtils.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "HelperInterface.h"
#include "CTreeViewDragDropTarget.h"
#include "DataObjectIterator.h"
#include "BehaviorFlavorTypes.h"
#include "UIDNodeID.h"
#include "UIDList.h"

//========================================================================================
// Class BehaviorsTreeViewDDTarget
//========================================================================================

class BehaviorsTreeViewDDTarget : public CTreeViewDragDropTarget
{
public:
	typedef CTreeViewDragDropTarget inherited;
	
	BehaviorsTreeViewDDTarget(IPMUnknown *boss);
	virtual ~BehaviorsTreeViewDDTarget();
	
	virtual ErrorCode ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
	virtual void DrawHilite(IControlView* targetWidget, int32 hitWhere);

protected:
	virtual	IControlView*  GetTarget(IControlView* widget, int32* hitWhere, const PMPoint& localPt);
	virtual DragDrop::TargetResponse CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;

private:
	ErrorCode GetEventAndPosition(IControlView* target, const int32& whereInTarget, ActionEvent& event, int32& position);
	
private:
	IControlView*	fTarget;
	int32			fWhereInTarget;
	mutable UID		fSourceBehaviorUID;
	
	DECLARE_HELPER_METHODS()
};

//--------------------------------------------------------------------------------------
// Implementation PageItemDDTargetBehaviorHelper
//--------------------------------------------------------------------------------------

CREATE_PMINTERFACE(BehaviorsTreeViewDDTarget, kBehaviorsTreeViewDDTargetImpl)
DEFINE_HELPER_METHODS(BehaviorsTreeViewDDTarget)

//--------------------------------------------------------------------------------------
// BehaviorsTreeViewDDTarget::BehaviorsTreeViewDDTarget
//--------------------------------------------------------------------------------------

BehaviorsTreeViewDDTarget::BehaviorsTreeViewDDTarget(IPMUnknown *boss) :
	inherited(boss), HELPER_METHODS_INIT(boss), fTarget(nil), fSourceBehaviorUID(kInvalidUID), fWhereInTarget(kNotHit)
{
}

//--------------------------------------------------------------------------------------
// BehaviorsTreeViewDDTarget::~BehaviorsTreeViewDDTarget
//--------------------------------------------------------------------------------------

BehaviorsTreeViewDDTarget::~BehaviorsTreeViewDDTarget()
{
}

//--------------------------------------------------------------------------------------
// BehaviorsTreeViewDDTarget::ProcessDragDropCommand
//--------------------------------------------------------------------------------------

ErrorCode BehaviorsTreeViewDDTarget::ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType)
{
	ErrorCode result = kSuccess;

	if (fTarget != nil && controller->InternalizeDrag(kNoExternalFlavor, kBehaviorDragDropFlavor) == kSuccess)
	{
		InterfacePtr<IDataExchangeHandler> handler(controller->QueryHandler(kBehaviorDragDropFlavor));
		if (handler)
		{
			ActionEvent event;
			int32 position;
			
			if ((result = GetEventAndPosition(fTarget, fWhereInTarget, event, position)) == kSuccess)
			{
				InterfacePtr<IBehaviorDragDropData> data(handler, UseDefaultIID());
				std::vector< std::pair<ActionEvent, UID> > behaviors = data->Get();
				
				InterfacePtr<IMoveBehaviorData> moveData(this, UseDefaultIID());
				moveData->Set(data->GetDataBase(), data->Get(), event, position);
				
				// ---- Normally we would process the move commands here, but both the dialog
				//		manager and the drag and drop manager create command sequences and there
				//		can't be more than one command sequence active at a time. So here we
				//		store away the data required to do the move commands and then in
				//		BehaviorTreeNodeEH, the event handler that initiates the drag, we
				//		retrieve the data and process the commands. Note: The dialog manager
				//		only creates a command sequence when using the preview mechanism. [amb 1-7-03]
			}
		}
	}
			
	return result;
}

//--------------------------------------------------------------------------------------
// BehaviorsTreeViewDDTarget::GetTarget
//--------------------------------------------------------------------------------------

IControlView* BehaviorsTreeViewDDTarget::GetTarget(IControlView* widget, int32* hitWhere, const PMPoint& localPt)
{
	fTarget = inherited::GetTarget(widget, hitWhere, localPt);
	
	fWhereInTarget = *hitWhere;
	
	return fTarget;
}

//--------------------------------------------------------------------------------------
// BehaviorsTreeViewDDTarget::CouldAcceptTypes
//--------------------------------------------------------------------------------------

DragDrop::TargetResponse BehaviorsTreeViewDDTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* source, const IDragDropController* controller) const
{
	if (dataIter)
	{
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kBehaviorDragDropFlavor);
		if (response.CanDo())
		{
			InterfacePtr<IDataExchangeHandler> handler(controller->QueryHandler(kBehaviorDragDropFlavor));
			if (handler)
			{
				InterfacePtr<IBehaviorDragDropData> data(handler, UseDefaultIID());
				std::vector< std::pair<ActionEvent, UID> > behaviors = data->Get();
				if (!behaviors.empty())
					fSourceBehaviorUID = behaviors.begin()->second;
			}

			return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);
		}
	}
	
	return DragDrop::kWontAcceptTargetResponse;
}

//--------------------------------------------------------------------------------------
// BehaviorsTreeViewDDTarget::GetEventAndPosition
//--------------------------------------------------------------------------------------

ErrorCode BehaviorsTreeViewDDTarget::GetEventAndPosition(IControlView* target, const int32& whereInTarget, ActionEvent& event, int32& position)
{
	ErrorCode result = kSuccess;
	
	InterfacePtr<ITreeNodeIDData> treeNodeData(target, UseDefaultIID());	
	InterfacePtr<ITreeViewHierarchyAdapter> adapter(this, UseDefaultIID());

	ASSERT(treeNodeData->Get() != adapter->GetRootNode() && treeNodeData->Get() != adapter->GetGenericNodeID());
	ASSERT(whereInTarget == kAbove || whereInTarget == kBelow);
	
	event = FormFieldUIUtils::GetSelectedEvent(this);
	if (whereInTarget == kAbove)
		position = adapter->GetChildIndex(adapter->GetRootNode(), treeNodeData->Get());
	else if (whereInTarget == kBelow)
		position = adapter->GetChildIndex(adapter->GetRootNode(), treeNodeData->Get()) + 1;
	
	return result;
}

//--------------------------------------------------------------------------------------
// BehaviorsTreeViewDDTarget::DrawHilite
//--------------------------------------------------------------------------------------

void BehaviorsTreeViewDDTarget::DrawHilite(IControlView* targetWidget, int32 hitWhere)
{
	// Check if we can add a new state or not
	if (fTarget != nil && fSourceBehaviorUID != kInvalidUID)
	{
		ActionEvent newEvent;
		int32 newPosition;

		if (GetEventAndPosition(fTarget, fWhereInTarget, newEvent, newPosition) == kSuccess)
		{
			InterfacePtr<IBehaviorSuite> behaviorSuite(SelectionUtils::QuerySuite<IBehaviorSuite>());
			if (behaviorSuite && behaviorSuite->CanMoveAction(fSourceBehaviorUID, newEvent, newPosition))
				return CTreeViewDragDropTarget::DrawHilite(targetWidget, hitWhere);
		}
	}
}