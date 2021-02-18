//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelTreeViewAdapter.cpp $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IDropDownListController.h"
#include "IDynamicEventTimingSuite.h"
#include "ILayoutControlData.h"
#include "IPanelControlData.h"
#include "ITreeViewHierarchyAdapter.h"

// ----- Includes -----

#include "CPMUnknown.h"
#include "DynamicDocumentsUIDefs.h"
#include "TimingPanelTreeNodeID.h"

// ----- Utils -----

#include "DynamicDocumentsUIUtils.h"
#include "ISelectionUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewAdapter constructor
//----------------------------------------------------------------------------------------
class TimingPanelTreeViewAdapter : public CPMUnknown<ITreeViewHierarchyAdapter>
{
	public:
		TimingPanelTreeViewAdapter(IPMUnknown *boss);
		~TimingPanelTreeViewAdapter();
		
		virtual NodeID_rv	GetRootNode() const;
		virtual NodeID_rv	GetParentNode(const NodeID& node) const;
		virtual int32		GetNumChildren(const NodeID& node) const;
		virtual NodeID_rv	GetNthChild(const NodeID& node, const int32& nth) const;
		virtual int32		GetChildIndex(const NodeID& parent, const NodeID& child) const;
		virtual NodeID_rv	GetGenericNodeID() const;
		virtual bool16		ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }

	private:
		void GetGroupItemInfoByIndex(const int32 &nth, const EventTriggerType &eventType, 
									 UID &itemUID, PMReal &delay, 
									 bool16 &bIsGroupItem, bool16 &bIsFirstItemInGroup, bool16 &bIsLastItemInGroup,
									 uint32 &role, uint32 &action) const;
};

CREATE_PMINTERFACE(TimingPanelTreeViewAdapter, kTimingPanelTreeViewAdapterImpl)

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewAdapter constructor
//----------------------------------------------------------------------------------------
TimingPanelTreeViewAdapter::TimingPanelTreeViewAdapter(IPMUnknown *boss) :
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
}

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewAdapter::~TimingPanelTreeViewAdapter 
//----------------------------------------------------------------------------------------
TimingPanelTreeViewAdapter::~TimingPanelTreeViewAdapter()
{
}

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewAdapter::GetRootNode 
//----------------------------------------------------------------------------------------
NodeID_rv TimingPanelTreeViewAdapter::GetRootNode() const
{
	return TimingPanelTreeNodeID::Create(kInvalidUID, kFalse, kFalse, kFalse, kTimingTargetRoleDefault, kTimingTargetVerbPlay);
}
	
//----------------------------------------------------------------------------------------
// TimingPanelTreeViewAdapter::GetParentNode 
//----------------------------------------------------------------------------------------
NodeID_rv TimingPanelTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	if (node == this->GetRootNode())
		return kInvalidNodeID;

	return this->GetRootNode();
}

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewAdapter::GetNumChildren 
//----------------------------------------------------------------------------------------
int32 TimingPanelTreeViewAdapter::GetNumChildren(const NodeID& node) const
{			
	int32 numChildren = 0;

	if (node == this->GetRootNode())
	{			
		InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
		InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));
		if (iDynamicEventTimingSuite)
		{
			// Get current event
			EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
			if (eventType != kNoTriggerEvent)
			{
				int32 numGroups = iDynamicEventTimingSuite->GetNumGroupsInEvent(eventType);

				for (int32 i = 0; i < numGroups; ++i)
				{
					IDynamicEventTimingMgr::DynamicTargetList itemList;
					bool bSuccess = iDynamicEventTimingSuite->GetNthGroupInEvent(eventType, i, itemList);				
					ASSERT(bSuccess);

					numChildren += static_cast<int32>(itemList.size());
				}
			}
			else
			{
				std::vector<UID> unassignedTargetList;
				if (iDynamicEventTimingSuite->GetUnassignedTargets(unassignedTargetList))
					numChildren = static_cast<int32>(unassignedTargetList.size());
			}
		}
	}

	return numChildren;
}

NodeID_rv TimingPanelTreeViewAdapter::GetNthChild(const NodeID& parentTreeNode, const int32& nth) const
{
	if (parentTreeNode == this->GetRootNode())
	{
		// Get current event
		EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();

		// Given the flattened index nth, get the info about nthGroup and nthItemWithinGroup to generate the node.
		UID itemUID = kInvalidUID;
		PMReal delay(0.0);
		bool16 bIsGroupItem = kFalse;
		bool16 bIsFirstItemInGroup = kFalse;
		bool16 bIsLastItemInGroup = kFalse;
		uint32 role = kTimingTargetRoleDefault;
		uint32 action = kTimingTargetVerbPlay;

		if (eventType != kNoTriggerEvent)
		{
			this->GetGroupItemInfoByIndex(nth, eventType, itemUID, delay, bIsGroupItem, bIsFirstItemInGroup, bIsLastItemInGroup, role, action);
			ASSERT(itemUID != kInvalidUID);
		}
		else
		{
			InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
			InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));
			if (iDynamicEventTimingSuite)
			{
				std::vector<UID> unassignedTargetList;
				if (iDynamicEventTimingSuite->GetUnassignedTargets(unassignedTargetList))
					itemUID = unassignedTargetList[nth];
			}
		}

		return TimingPanelTreeNodeID::Create(itemUID, bIsGroupItem, bIsFirstItemInGroup, bIsLastItemInGroup, role, action);			
	}

	return TimingPanelTreeNodeID::Create(kInvalidUID, kFalse, kFalse, kFalse, kTimingTargetRoleDefault, kTimingTargetVerbPlay);	
}

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------
int32 TimingPanelTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	if (parent == this->GetRootNode())
	{
		TreeNodePtr<TimingPanelTreeNodeID>	parentNode(parent);
		TreeNodePtr<TimingPanelTreeNodeID>	childNode(child);

		if (parentNode && childNode)
		{
			UID childUID = childNode->GetUID();
			int32 numChildren = this->GetNumChildren(parent);
			for (int32 i = 0; i < numChildren; ++i)
			{
				NodeID nthNode = this->GetNthChild(parent, i); 
				TreeNodePtr<TimingPanelTreeNodeID> nthChildNode(nthNode); 
				if (nthChildNode->GetUID() == childUID) 
					return i; 
			}
		}
	}

	return -1;
}

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewAdapter::GetGenericNodeID() const
//----------------------------------------------------------------------------------------
NodeID_rv TimingPanelTreeViewAdapter::GetGenericNodeID() const
{
	return TimingPanelTreeNodeID::Create(kInvalidUID, kFalse, kFalse, kFalse, kTimingTargetRoleDefault, kTimingTargetVerbPlay);	
}

//----------------------------------------------------------------------------------------
// TimingPanelTreeViewAdapter::GetGroupItemInfoByIndex() 
//----------------------------------------------------------------------------------------
void TimingPanelTreeViewAdapter::GetGroupItemInfoByIndex(const int32 &nth, const EventTriggerType &eventType, 
														 UID &itemUID, PMReal &delay, 
														 bool16 &bIsGroupItem, bool16 &bIsFirstItemInGroup, bool16 &bIsLastItemInGroup,
														 uint32 &role, uint32 &action) const
{
	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	IDataBase* db = iSelectionMgr->GetDataBase();

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));
	int32 numGroups = iDynamicEventTimingSuite->GetNumGroupsInEvent(eventType);

	int32 startIndex = 0;

	for (int32 i = 0; i < numGroups; ++i)
	{
		IDynamicEventTimingMgr::DynamicTargetList itemList;				
		bool bSuccess = iDynamicEventTimingSuite->GetNthGroupInEvent(eventType, i, itemList);

		if (bSuccess)
		{
			int32 numItems = static_cast<int32>(itemList.size());

			if ((nth >= startIndex) && (nth < startIndex + numItems))
			{
				int32 nthItemWithinGroup = nth - startIndex;
				ASSERT(nthItemWithinGroup >= 0);

				delay = iDynamicEventTimingSuite->GetTargetDelayInEvent(eventType, itemList[nthItemWithinGroup], i);

				itemUID = itemList[nthItemWithinGroup]->GetTargetUID ();
				bIsGroupItem = (itemList.size() > 1);
				bIsFirstItemInGroup = (bIsGroupItem && (nthItemWithinGroup == 0));
				bIsLastItemInGroup = (bIsGroupItem && (nthItemWithinGroup == itemList.size() - 1));
				role = itemList[nthItemWithinGroup]->GetRole();
				action = itemList[nthItemWithinGroup]->GetAction();
				
				break;
			}

			startIndex += numItems;
		}
	}
}
