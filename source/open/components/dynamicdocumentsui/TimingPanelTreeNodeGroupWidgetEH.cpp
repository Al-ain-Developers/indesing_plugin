//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelTreeNodeGroupWidgetEH.cpp $
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
//  Copyright 1998
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface files -----

#include "IDragDropController.h"
#include "IDragDropSource.h"
#include "IDynamicEventTimingFacade.h"
#include "IDynamicEventTimingSuite.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "ISelectionUtils.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewMgr.h"
#include "ITreeAttributes.h"
#include "IViewPort.h"
#include "IWidgetParent.h"
#include "IWindow.h"

// ----- Include files -----

#include "DVHostedWidgetEH.h"
#include "TimingPanelTreeNodeID.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "EventUtilities.h"
#include "K2Vector.tpp"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

class TimingPanelTreeNodeGroupWidgetEH : public DVHostedWidgetEH
{
	public:
		typedef DVHostedWidgetEH inherited;
		TimingPanelTreeNodeGroupWidgetEH(IPMUnknown *boss) : inherited(boss) { }
		virtual ~TimingPanelTreeNodeGroupWidgetEH() { }

		virtual bool16 LButtonDn(IEvent* e);

	private:
		void SelectAllItemsInGroup(IEvent* e, ITreeViewController* iTreeViewController, IDynamicEventTimingMgr::DynamicTargetList itemList);
};

CREATE_PMINTERFACE(TimingPanelTreeNodeGroupWidgetEH, kTimingPanelTreeNodeGroupWidgetEHImpl)

bool16 TimingPanelTreeNodeGroupWidgetEH::LButtonDn(IEvent* e)
{
	InterfacePtr<IWidgetParent>	iWidgetParent(this, UseDefaultIID());
	InterfacePtr<ITreeNodeIDData> iHolderData(iWidgetParent->GetParent(), UseDefaultIID());
	if (!iHolderData)
		return kTrue;

	//
	// Get node information.
	//
	NodeID nodeIDHolder = iHolderData->Get();	
	TreeNodePtr<TimingPanelTreeNodeID> itemNode(nodeIDHolder);

	//
	// If it is not group item, we don't need to do anything.
	//
	bool16 bIsGroupItem = itemNode->IsGroupItem();
	if (!bIsGroupItem)
		return kTrue;	

	// 
	// If it is group item, we select all items in the group.
	//
	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
	if (eventType == kNoTriggerEvent)
		return kTrue;
		
	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	IDataBase* db = iSelectionMgr->GetDataBase();

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));
	if (!iDynamicEventTimingSuite)
		return kTrue;

	InterfacePtr<ITreeAttributes> iTreeAttrs ((ITreeAttributes*)iWidgetParent->QueryParentFor(IID_ITREEATTRIBUTES));
	InterfacePtr<ITreeViewController> iTVController (iTreeAttrs, UseDefaultIID());
	
	//	Get the list of currently selected node.
	//	Uncommited changes from the edit boxes get applied to this list before the node selection changes.
	NodeIDList currentNodes;
	iTVController->GetSelectedItems(currentNodes);

	//	Apply uncomitted changes if necessary.
	//	Uncommited changes could be delay or number of group plays.
	bool canUpdate = (ddui_utils::UpdateTimingItemsIfNecessary (this, currentNodes) == kDefaultWidgetId);

	//
	//Check for drag-n-drop	
	//
	int32 numNodesSelected = static_cast<int32>(currentNodes.size());
	InterfacePtr<IDragDropSource> dragSource(this, UseDefaultIID());
	if (canUpdate && dragSource && dragSource->WillDrag(e) && numNodesSelected > 0) 
	{
		// Check to see if user is trying to start a drag
		bool16 isPatientUser;
		if (/*EventUtilities*/::IsUserStartingDrag(e, isPatientUser)) 
		{
			InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), UseDefaultIID());
			if (ddController)
			{
				ddController->StartDrag(dragSource, e);	
				e->SetSystemHandledState(IEvent::kDontCall);
				return kTrue; // Make up for the fact that StartDrag will swallow the mouse up
			}
		}
	}

	//	Select group if appropriate.
	if (canUpdate)
	{
		UIDRef itemUIDRef = UIDRef(db, itemNode->GetUID());
		uint32 role = itemNode->GetRole();
		uint32 action = itemNode->GetAction();

		uint32 position = -1;
		IDynamicEventTimingMgr::DynamicTargetPtr dynamicTarget (Utils<Facade::IDynamicEventTimingFacade> ()->CreateDynamicTarget(itemUIDRef, role, action));
		int32 group = iDynamicEventTimingSuite->FindTargetInEvent(eventType, dynamicTarget, position);
		ASSERT(group >= 0);

		if (group >= 0)
		{
			IDynamicEventTimingMgr::DynamicTargetList itemList;
			if (iDynamicEventTimingSuite->GetNthGroupInEvent(eventType, group, itemList) && (itemList.size() > 1))
			{
				// Select all the items in the group.
				this->SelectAllItemsInGroup(e, iTVController, itemList);
			}
		}
	}

	return kTrue;
}

void TimingPanelTreeNodeGroupWidgetEH::SelectAllItemsInGroup(IEvent* e, ITreeViewController* iTreeViewController, IDynamicEventTimingMgr::DynamicTargetList itemList)
{
    InterfacePtr<ITreeViewHierarchyAdapter> iTreeAdapter (iTreeViewController, UseDefaultIID ()); 

	NodeID rootNode = iTreeAdapter->GetRootNode();
	int32 numChildren = iTreeAdapter->GetNumChildren(rootNode);
	int32 numItems = static_cast<int32>(itemList.size());

	// Check if all items in this group is already all selected or not.
	// If all items in group is selected, we will deselect them; otherwise, we will select all of them.
	bool bAllSelected = true;
	for (int32 m = 0; m < numItems && bAllSelected; ++m)
	{
		for (int32 n = 0; n < numChildren && bAllSelected; ++n)
		{
			NodeID nthChild = iTreeAdapter->GetNthChild(rootNode, n);
			TreeNodePtr<TimingPanelTreeNodeID> itemNode(nthChild); 

			if ((itemNode->GetUID() == itemList[m]->GetTargetUID()) && 
				(itemNode->GetRole() == itemList[m]->GetRole()) &&  
				(itemNode->GetAction() == itemList[m]->GetAction()))
			{
				if (!iTreeViewController->IsSelected(nthChild))
				{
					bAllSelected = false;
					break;
				}
			}
		}
	}

	// If no modified key is pressed, deselect all.
	// If modified key is pressed, we only want to deselect the group which already has all items selected.
	if (!e->CmdKeyDown() && !e->ShiftKeyDown())
		iTreeViewController->DeselectAll();

	for (int32 i = 0; i < numItems; ++i)
	{
		for (int32 j = 0; j < numChildren; ++j)
		{
			NodeID nthChild = iTreeAdapter->GetNthChild(rootNode, j);
			TreeNodePtr<TimingPanelTreeNodeID> itemNode(nthChild); 

			if ((itemNode->GetUID() == itemList[i]->GetTargetUID()) && 
				(itemNode->GetRole() == itemList[i]->GetRole()) &&  
				(itemNode->GetAction() == itemList[i]->GetAction()))
			{
				if (bAllSelected)
					iTreeViewController->Deselect(nthChild);
				else
					iTreeViewController->Select(nthChild);
				break;
			}
		}
	}
}
