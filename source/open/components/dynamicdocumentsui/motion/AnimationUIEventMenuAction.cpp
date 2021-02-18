//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIEventMenuAction.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface files -----

#include "IActiveContext.h"
#include "IActionStateList.h"
#include "IAnimationAttributeSuite.h"
#include "IApplication.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "ISubject.h"

// ----- Include files -----

#include "CActionComponent.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "IAnimationUtils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

class AnimationUIEventMenuAction : public CActionComponent
{
	typedef CActionComponent inherited;

	typedef std::vector<std::pair<ActionID, EventTriggerType> > ActionIDToTriggerTypeList;
	ActionIDToTriggerTypeList fActionIDToTriggerTypeList;

	std::map<EventTriggerType, bool> fAppliedTriggertList;

public:
	AnimationUIEventMenuAction(IPMUnknown *boss) : CActionComponent (boss) {}

	virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
	{
		ISelectionManager* iSelectionMgr = ac->GetContextSelection ();
		IDataBase* db = iSelectionMgr->GetDataBase();

		bool result = true;		
		switch (actionID.Get ())
		{	
			case kAnimationUIAction_OnPageLoadEventActionID:
			case kAnimationUIAction_OnPageClickEventActionID:
			case kAnimationUIAction_OnClickSelfEventActionID:
			case kAnimationUIAction_OnRollOverSelfEventActionID:
			{
				//	No need to broadcast additional message. There will be a selection attribute changed message broadcast
				//	to the selection suite which will in turn notify any clients.
				InterfacePtr<IAnimationAttributeSuite> iAttrSuite (iSelectionMgr, UseDefaultIID ());
				for (ActionIDToTriggerTypeList::iterator iter = fActionIDToTriggerTypeList.begin(); iter != fActionIDToTriggerTypeList.end(); ++iter)
				{
					if (iter->first == actionID.Get ())
					{
						EventTriggerType triggerType = iter->second;

						if (fAppliedTriggertList.find (triggerType) != fAppliedTriggertList.end())
							result = iAttrSuite->RemoveAnimationTriggerEvent(triggerType);
						else
							result = iAttrSuite->AddAnimationTriggerEvent(triggerType);
					}
				}

				break;
			}

			//	Do nothing for onButtonEvent since it is only informational.
			case kAnimationUIAction_OnButtonEventActionID:
			default:
				break;

		}
	}

	virtual void UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
	{
		fActionIDToTriggerTypeList.clear();
		fAppliedTriggertList.clear();
		
		InterfacePtr<IAnimationAttributeSuite> iAttrSuite (ac->GetContextSelection (), UseDefaultIID ());
		ddui_utils::UpdateAnimationItemName (iAttrSuite, widget);

		bool uniuqe = false;
		std::vector<EventTriggerType> applicableList;
		bool hasMSOTiming = _GetAnimationTriggerEvents(ac, applicableList, fAppliedTriggertList, uniuqe);
		
		InterfacePtr<IApplication> iApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IActionManager> iActionMgr(iApp->QueryActionManager());

		for(int32 i = 0; i < listToUpdate->Length(); ++i)
		{	
			//
			// Construct a map (ActionID, triggerType) for add/remove animation trigger type in Do().
			//
			ActionID action = listToUpdate->GetNthAction(i);

			const PMString& actionName = iActionMgr->GetActionName(action);
			EventTriggerType triggerType = Utils<IAnimationUtils>()->GetEventTriggerFromString (actionName);

			//	Update aciton name.
			if (triggerType == kOnPageLoad)
			{
				if (hasMSOTiming && actionName != "kOnStateLoad")
				{
					iActionMgr->UpdateActionName (action, "kOnStateLoad");
				}
				else if (!hasMSOTiming && actionName != "kOnPageLoad")
				{
					iActionMgr->UpdateActionName (action, "kOnPageLoad");
				}
			}
			
			switch (action.Get ())
			{
				case kAnimationUIAction_OnPageClickEventActionID:
				case kAnimationUIAction_OnPageLoadEventActionID:
				case kAnimationUIAction_OnClickSelfEventActionID:
				case kAnimationUIAction_OnRollOverSelfEventActionID:
				{					
					if (uniuqe && std::find (applicableList.begin (), applicableList.end (), triggerType) == applicableList.end ())
					{
						//	Action not applicable.
						ASSERT (fAppliedTriggertList.find(triggerType) == fAppliedTriggertList.end());
						listToUpdate->SetNthActionState (i, kDisabled_Unselected); 
					}
					else
					{
						//	At least one selection for which the action is applicable.
						fActionIDToTriggerTypeList.push_back (std::make_pair(action.Get (), triggerType));
						
						std::map<EventTriggerType, bool>::const_iterator tt = fAppliedTriggertList.find (triggerType);
						if (tt != fAppliedTriggertList.end ())
						{
							if (tt->second)
								listToUpdate->SetNthActionState (i, kEnabledAction|kSelectedAction); 
							else
								listToUpdate->SetNthActionState (i, kEnabledAction|kMultiSelectedAction); 
						}
						else
						{
							listToUpdate->SetNthActionState (i, kEnabledAction); 
						}
					}
					break;
				}
				
				case kAnimationUIAction_OnButtonEventActionID:
				{
					bool unique = true;
					if (_HasButtonEvents (fAppliedTriggertList, unique))
					{
						if (unique)
							listToUpdate->SetNthActionState(i, kEnabledAction|kSelectedAction);
						else
							listToUpdate->SetNthActionState(i, kEnabledAction|kMultiSelectedAction);
					}
					else
					{
						listToUpdate->SetNthActionState(i, kDisabled_Unselected);
					}					
					break;
				}

				default:
					break;
			}
		}
	}

private:
	bool _GetAnimationTriggerEvents(IActiveContext* ac, std::vector<EventTriggerType> &applicableList, 
			std::map<EventTriggerType, bool>& animationTriggerList, bool& unique) const
	{
		animationTriggerList.clear();

		ISelectionManager* iSelectionMgr = ac->GetContextSelection ();
		IDataBase* db = iSelectionMgr->GetDataBase();
		InterfacePtr<IAnimationAttributeSuite> iAttrSuite (iSelectionMgr, UseDefaultIID ());

		unique = true;
		uint32 numTriggerEvents = 0;
		bool hasMSOTiming = false;
		if (iAttrSuite)
		{
			unique = iAttrSuite->GetApplicableTriggerEvents (applicableList);
			iAttrSuite->GetNumAnimationTriggerEvents(numTriggerEvents);
			if (unique)
			{
				hasMSOTiming = iAttrSuite->HasMSOAsTimingParent();
			}
		}

		for (uint32 i = 0; i < numTriggerEvents; ++i)
		{
			EventTriggerType trigger = kNoTriggerEvent;

			bool triggerUnique = iAttrSuite->GetNthAnimationTriggerEvent (i, trigger);
			animationTriggerList [trigger] = triggerUnique;
		}
		return hasMSOTiming;
	}

	bool _HasButtonEvents (const std::map<EventTriggerType, bool>& appliedTriggertList, bool& unique) const
	{
		//	If at least one mixed, then call it mixed seleciton.
		unique = true;
		for (std::map<EventTriggerType, bool>::const_iterator e = appliedTriggertList.begin ();
			e != appliedTriggertList.end (); ++e)
		{
			unique = unique && e->second;
		}

		for (std::map<EventTriggerType, bool>::const_iterator e = appliedTriggertList.begin ();
			e != appliedTriggertList.end (); ++e)
		{
			if (e->first == kOnClick || e->first == kOnRelease || e->first == kOnRollover || e->first == kOnRolloff)
				return true;
		}
		return false;
	}
};

CREATE_PMINTERFACE(AnimationUIEventMenuAction, kAnimationUIEventMenuActionImpl)



