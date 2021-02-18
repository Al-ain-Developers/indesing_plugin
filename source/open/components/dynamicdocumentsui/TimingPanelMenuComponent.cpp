//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelMenuComponent.cpp $
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

// ----- Interface files -----

#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IApplication.h"

// ----- Include files -----

#include "CActionComponent.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "IDynamicEventTimingFacade.h"
#include "IDynamicEventTimingSuite.h"
#include "IPalettePanelUtils.h"
#include "ISelectionUtils.h"
#include "IAnimationUtils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"
#include "FormFieldID.h"

//========================================================================================
// CLASS TimingPanelMenuComponent
//========================================================================================
class TimingPanelMenuComponent : public CActionComponent
{
	public:
		TimingPanelMenuComponent(IPMUnknown *boss);
		
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
};

CREATE_PMINTERFACE(TimingPanelMenuComponent, kTimingPanelMenuComponentImpl)

//---------------------------------------------------------------
// Constructor
//---------------------------------------------------------------
TimingPanelMenuComponent::TimingPanelMenuComponent(IPMUnknown *boss) :
	CActionComponent(boss)
{
}

//---------------------------------------------------------------
// TimingPanelMenuComponent::UpdateActionStates()
//---------------------------------------------------------------
void TimingPanelMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *updateList, GSysPoint mousePoint, IPMUnknown* widget)
{		
	ISelectionManager* iSelectionMgr = ac->GetContextSelection();	
	IDataBase* db = iSelectionMgr->GetDataBase();

	IDynamicEventTimingMgr::DynamicTargetList itemList;
	ddui_utils::GetSelectedTimingItems(db, itemList);
	bool bEnable  = (itemList.size() > 0);

	EventTriggerType trigger = ddui_utils::GetCurrentEventTypeInTimingPanel();

	std::vector<EventTriggerType> eventTriggerTypeList;	
	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));

	bool hasMSOTiming = false;
	if (bEnable && iDynamicEventTimingSuite)
	{
		for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator iter = itemList.begin(); iter != itemList.end(); ++iter)
		{
			std::vector<EventTriggerType> triggerList;
			iDynamicEventTimingSuite->GetApplicableDynamicEventsForTarget(trigger, *iter, triggerList);

			// We should not worry about the duplication in eventTriggerTypeList after appending 
			// since as long as there is one applicable event trigger type, we will enable the menu.
			std::copy (triggerList.begin (), triggerList.end (), std::back_inserter (eventTriggerTypeList));
		}

		hasMSOTiming = iDynamicEventTimingSuite->GetTimingParentClassID () == kMultiStateObjectItemBoss;
	}

	InterfacePtr<IApplication> iApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> iActionMgr(iApp->QueryActionManager());

	int32 count = updateList->Length();

	for (int32 i = 0; i < count; ++i)
	{	
		ActionID nthActionID = updateList->GetNthAction(i);

		switch (nthActionID.Get()) 
		{		
			case kTimingPanelReassignPageLoadEventActionID:
			{
				bool inList = std::find (eventTriggerTypeList.begin (), eventTriggerTypeList.end (), kOnPageLoad) != eventTriggerTypeList.end ();

				const PMString& actionName = iActionMgr->GetActionName(nthActionID);

				//	Update aciton name.
				if (hasMSOTiming && actionName != "kTimingPanelAssignStateLoadEvent")
				{
					iActionMgr->UpdateActionName (nthActionID, "kTimingPanelAssignStateLoadEvent");
				}
				else if (!hasMSOTiming && actionName != "kTimingPanelAssignPageLoadEvent")
				{
					iActionMgr->UpdateActionName (nthActionID, "kTimingPanelAssignPageLoadEvent");
				}

				updateList->SetNthActionState(i, (bEnable && inList) ? kEnabledAction : kDisabled_Unselected);
				break;
			}
			case kTimingPanelReassignPageClickEventActionID:
			{
				bool inList = std::find (eventTriggerTypeList.begin (), eventTriggerTypeList.end (), kOnPageClick) != eventTriggerTypeList.end ();
				updateList->SetNthActionState(i, (bEnable && inList) ? kEnabledAction : kDisabled_Unselected);
				break;
			}
			case kTimingPanelRemoveItemActionID:	// Only enable "Remove Item" menu when there is selection in the tree.
			{
				updateList->SetNthActionState(i, (bEnable && (trigger != kNoTriggerEvent)) ? kEnabledAction : kDisabled_Unselected);
				break;
			}
			
			default:
			{
				break;
			}
		}
	}
}

//---------------------------------------------------------------
// TimingPanelMenuComponent::DoAction()
//---------------------------------------------------------------
void TimingPanelMenuComponent::DoAction(IActiveContext* ac, ActionID id, GSysPoint mousePoint, IPMUnknown* widget)
{		
	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));

	IDataBase* db = iSelectionMgr->GetDataBase();

	IDynamicEventTimingMgr::DynamicTargetList selectedItems;
	ddui_utils::GetSelectedTimingItems(db, selectedItems);

	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();

	switch (id.Get()) 
	{
		case kTimingPanelRemoveItemActionID:
		{
			ICommandSequence* iRemoveCmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
			ASSERT (iRemoveCmdSequence != nil);

			for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator iter = selectedItems.begin(); iter != selectedItems.end(); ++iter)
				iDynamicEventTimingSuite->RemoveTargetInEvent(eventType, *iter);

			ErrorCode result = CmdUtils::EndCommandSequence(iRemoveCmdSequence);
			ASSERT(result == kSuccess);

			break;
		}
		case kTimingPanelReassignPageLoadEventActionID:
		case kTimingPanelReassignPageClickEventActionID:
		{
			if (id.Get() == kTimingPanelReassignPageLoadEventActionID)
				iDynamicEventTimingSuite->ReassignEventForTargets(eventType, kOnPageLoad, selectedItems);
			else
				iDynamicEventTimingSuite->ReassignEventForTargets(eventType, kOnPageClick, selectedItems);
			break;
		}
		default:
			break;
	}
}
