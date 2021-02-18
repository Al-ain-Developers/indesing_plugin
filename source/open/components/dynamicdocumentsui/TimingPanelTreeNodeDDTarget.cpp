//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelTreeNodeDDTarget.cpp $
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
//  Comments: Object style panel drag/drop target for delete button
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface files -----

#include "IDynamicEventTimingSuite.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "IWidgetParent.h"

// ----- Include files -----

#include "CTreeViewDragDropTarget.h"
#include "TimingPanelTreeNodeID.h"
#include "K2Vector.tpp"

// ----- Utilitity files -----

#include "DynamicDocumentsUIUtils.h"
#include "ISelectionUtils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

class TimingPanelTreeNodeDDTarget : public CTreeViewDragDropTarget
{
	public:
		TimingPanelTreeNodeDDTarget(IPMUnknown *boss) : CTreeViewDragDropTarget(boss) { }
		virtual	~TimingPanelTreeNodeDDTarget() { }
		
		// Can the target accept the data being dragged?
		//	(Drag source is provided to determine if data should be moved, copied or linked.)
		virtual DragDrop::TargetResponse CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;

		// Create the commands needed to complete a drop 
		// 	(targets will only receive kDragMove or kDrop)
		virtual ErrorCode ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);

		virtual void				DrawHilite(IControlView* targetWidget, int32 hitWhere);
		virtual void				DoDragEnter();
		virtual void				DoDragLeave();
		virtual void				DoDragWithin(const PMPoint& localPt) {}
		//virtual SysWireframe		DoMakeDropHiliteRegion() const	{ return SysWireframe(DragDrop::kTargetWillDrawDropHilite); }

	private:
		bool16 ShouldDrawHilite() const;
		void   ForceDraw(IControlView* iTreeNodeControlView) const;
};

CREATE_PMINTERFACE(TimingPanelTreeNodeDDTarget, kTimingPanelTreeNodeDDTargetImpl)

//--------------------------------------------------------------------------------------
// TimingPanelTreeNodeDDTarget::CouldAcceptTypes()
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse TimingPanelTreeNodeDDTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController* controller) const
{
	//
	// Check the available external flavors to see if we can handle any of them
	//
	if (dataIter)
	{		
		DataExchangeResponse response;
	
		// This DDTarget actually only handle timing item drop.
		response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMTimingPanelDragDropFlavor); 
        if (response.CanDo()) 
        { 
			return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);
		}
	}

	return DragDrop::kWontAcceptTargetResponse;
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeNodeDDTarget::DoDragEnter()
//--------------------------------------------------------------------------------------
void TimingPanelTreeNodeDDTarget::DoDragEnter()
{
	CTreeViewDragDropTarget::DoDragEnter();

#if 0
	InterfacePtr<IPanelControlData>	iTreeNodePanelControlData(this, UseDefaultIID());
	ASSERT(iTreeNodePanelControlData);

	InterfacePtr<IControlView> iTreeNodeControlView(iTreeNodePanelControlData,UseDefaultIID());

	if(ShouldDrawHilite())
	{
		iTreeNodeControlView->Hilite();
	}	
	else
	{
		CursorSpec newCursor(kCrsrBadDropTarget);
		InterfacePtr<IDragDropController> iDragDropController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
		iDragDropController->SetTrackingCursorFeedback(newCursor);		
	}
	
	ForceDraw(iTreeNodeControlView);
#endif
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeNodeDDTarget::DoDragLeave()
//--------------------------------------------------------------------------------------
void TimingPanelTreeNodeDDTarget::DoDragLeave() 
{
	CTreeViewDragDropTarget::DoDragLeave();
	
#if 0
	InterfacePtr<IPanelControlData>	iTreeNodePanelControlData(this, UseDefaultIID());
	ASSERT(iTreeNodePanelControlData);

	InterfacePtr<IControlView> iTreeNodeControlView(iTreeNodePanelControlData,UseDefaultIID());

	if(ShouldDrawHilite())
	{
		iTreeNodeControlView->Unhilite();
	}
	
	ForceDraw(iTreeNodeControlView);
#endif
}

void TimingPanelTreeNodeDDTarget::ForceDraw(IControlView* iTreeNodeControlView) const
{
	ASSERT(iTreeNodeControlView != nil);

	if (iTreeNodeControlView)
	{
		iTreeNodeControlView->Invalidate();
	
		iTreeNodeControlView->ForceRedraw(iTreeNodeControlView->GetDrawRegion(), kTrue);
	}
}

void TimingPanelTreeNodeDDTarget::DrawHilite(IControlView* targetWidget, int32 hitWhere)
{
	//if (targetWidget)
	//{
	//	if ((hitWhere == kAbove) || (hitWhere == kBelow))
	//	{
			CTreeViewDragDropTarget::DrawHilite(targetWidget,hitWhere);
	//	}
	//}
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeNodeDDTarget::ProcessDragDropCommand
//--------------------------------------------------------------------------------------
ErrorCode TimingPanelTreeNodeDDTarget::ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type)
{
	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	IDataBase* db = iSelectionMgr->GetDataBase();
	if (!db)
		return kSuccess;

	NodeIDList selectedNodes;
	InterfacePtr<IWidgetParent>	iWidgetParent(this, UseDefaultIID());
	InterfacePtr<ITreeViewController> iTreeViewController((ITreeViewController*)iWidgetParent->QueryParentFor(ITreeViewController::kDefaultIID));
	iTreeViewController->GetSelectedItems(selectedNodes);
	
	if (selectedNodes.size() > 0)
	{
		InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));

		EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
		ASSERT(eventType != kNoTriggerEvent);

		uint32 newGroup = iDynamicEventTimingSuite->GetNumGroupsInEvent(eventType)-1;

		InterfacePtr<const ITreeNodeIDData> nodeData(fOldTarget,UseDefaultIID()); 
		if (nodeData)
		{
			TreeNodePtr<const TimingPanelTreeNodeID> destNode(nodeData->Get()); 
			UIDRef destItemUIDRef = UIDRef(db, destNode->GetUID());
			newGroup = ddui_utils::GetTimingGroupIndex(eventType, destItemUIDRef);			
		
			if (destNode->IsGroupItem())
			{
				//
				// Move to a group
				// TODO::still need to figure out the location to insert.
				//
				for (int32 i = 0, n = selectedNodes.size(); i < n; ++i)
				{
					TreeNodePtr<const TimingPanelTreeNodeID> nthItemNode(selectedNodes[i]);
					UIDRef nthItemUIDRef = UIDRef(db, nthItemNode->GetUID());
					uint32 oldGroup = ddui_utils::GetTimingGroupIndex(eventType, nthItemUIDRef);			

					if (destNode->IsFirstItemInGroup())
					{
						iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, nthItemUIDRef, oldGroup, newGroup, 0);			
					}
					else if (destNode->IsLastItemInGroup())
					{
						iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, nthItemUIDRef, oldGroup, newGroup, -1);			
					}
					else
					{
						iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, nthItemUIDRef, oldGroup, newGroup, fHitLocation);			
					}
				}

				return kSuccess;
			}
		}

		//
		// Move to non-group
		//
		for (int32 i = 0, n = selectedNodes.size(); i < n; ++i)
		{
			TreeNodePtr<const TimingPanelTreeNodeID> nthItemNode(selectedNodes[i]);
			UIDRef nthItemUIDRef = UIDRef(db, nthItemNode->GetUID());
			uint32 oldGroup = ddui_utils::GetTimingGroupIndex(eventType, nthItemUIDRef);			

			if ((fHitLocation == kAbove) && (nodeData != nil))
				iDynamicEventTimingSuite->MoveTargetBeforeInEvent(eventType, nthItemUIDRef, oldGroup, newGroup);			
			else 
				iDynamicEventTimingSuite->MoveTargetAfterInEvent(eventType, nthItemUIDRef, oldGroup, newGroup);			
		}	
	}

	return kSuccess;
}


bool16 TimingPanelTreeNodeDDTarget::ShouldDrawHilite() const
{	
	InterfacePtr<IWidgetParent>	iWidgetParent(this, UseDefaultIID());
	InterfacePtr<ITreeViewController> iTreeViewController((ITreeViewController*)iWidgetParent->QueryParentFor(ITreeViewController::kDefaultIID));
	ASSERT(iTreeViewController != nil);

	NodeIDList selectedNodes;
	iTreeViewController->GetSelectedItems(selectedNodes);
	if (selectedNodes.size() > 0)
	{
		InterfacePtr<ITreeNodeIDData> iTreeNodeIDdata(this, UseDefaultIID());
		ASSERT(iTreeNodeIDdata != nil);
		TreeNodePtr<TimingPanelTreeNodeID> timingNodeID(iTreeNodeIDdata->Get());

		if ((timingNodeID->GetUID() != kInvalidUID) && 
			timingNodeID->IsGroupItem() && 
			(timingNodeID->IsFirstItemInGroup() || timingNodeID->IsLastItemInGroup()))
		{
			return kTrue;
		}
	}

	return kFalse;
}
