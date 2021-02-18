//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionalTextUIPanelMenuAction.cpp $
//  
//  Owner: Michele Stutzman
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

#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IConditionalTextOptions.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IWorkspace.h"
#include "IConditionTagList.h"
#include "IConditionTag.h"

// ----- Includes -----

#include "CActionComponent.h"
#include "K2Vector.tpp"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "IConditionalTextUIFacade.h"
#include "IInCopySharedUtils.h"
#include "IPalettePanelUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionalTextUIPanelMenuAction : public CActionComponent
{
public:
	ConditionalTextUIPanelMenuAction(IPMUnknown *boss);
	
	virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
	virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
	
private:
	bool16 CanShowAll(IActiveContext* ac);
	bool16 CanHideAll(IActiveContext* ac);
};

// =============================================================================
// *** ConditionalTextUIPanelMenuAction impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionalTextUIPanelMenuAction, kConditionalTextUIPanelMenuActionImpl)

ConditionalTextUIPanelMenuAction::ConditionalTextUIPanelMenuAction(IPMUnknown *boss) : CActionComponent(boss) 
{
} // end constructor

// -----------------------------------------------------------------------------

void ConditionalTextUIPanelMenuAction::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
#pragma unused(mousePoint)
	const int32 count = listToUpdate->Length();

	bool16 stylesEditable = Utils<IInCopySharedUtils>()->StylesEditable(::GetDataBase(ac->GetContextWorkspace()));

	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kConditionalTextUIPanelWidgetID));
	if (!panelData) // can't assume panel is open, could be quick apply or a keyboard shortcut that is asking. In which case just return.
		return;
	
	IControlView* treeView = panelData->FindWidget(kConditionTagListTreeViewWidgetID);
	InterfacePtr<ITreeViewController> tvController(treeView, UseDefaultIID());
	ASSERT(tvController != nil);

	NodeIDList selNodes;
	tvController->GetSelectedItems(selNodes);

	for (int32 i = 0; i < count; i++)
	{
		ActionID actionID = listToUpdate->GetNthAction(i);
		int16 state = kDisabled_Unselected;

		switch (actionID.Get())
		{
			case kShowAllTagsActionID:
				if (CanShowAll(ac)) state = kEnabledAction;
				else state = kDisabled_Unselected;
				break;
				
			case kHideAllTagsActionID:
				if (CanHideAll(ac)) state = kEnabledAction;
				else state = kDisabled_Unselected;
				break;
				
			case kNewConditionTagActionID:
				if (stylesEditable)
					state = kEnabledAction;
				else
					state = kDisabled_Unselected;
				break;

			case kLoadConditionTagsActionID:
			case kLoadConditionTagsAndSetsActionID:
				if (stylesEditable)
					state = kEnabledAction;
				else
					state = kDisabled_Unselected;
				break;

			case kEditConditionTagActionID:
				{
					InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());
					if (stylesEditable && selNodes.size() == 1 && selNodes[0] != tvAdapter->GetRootNode())
						state = kEnabledAction;
					else
						state = kDisabled_Unselected;
				}
				break;

			case kDeleteConditionTagActionID:
				if (stylesEditable && selNodes.size() > 0)
				{
					PMString menuString(selNodes.size() == 1 ? "#CondTextUI_DeleteConditionTagMenu" : "#CondTextUI_DeleteConditionTagsMenu");
					listToUpdate->SetNthActionName(i, menuString);
					state = kEnabledAction;

					InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());
					for (int32 k = 0; k < selNodes.size(); k++)
					{
						if (selNodes[k] == tvAdapter->GetRootNode())
						{
							state = kDisabled_Unselected;	// can't delete [Unconditional]
							break;
						}
					}
				}
				else
					state = kDisabled_Unselected;
				break;

			case kShowHideConditionSetOptionsActionID:
				{
					PMString menuString = Utils<IPalettePanelUtils>()->GetCurrentOptionString(kConditionalTextUIPanelBoss);
					InterfacePtr<IPanelControlData> panelControlData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kConditionalTextUIPanelBoss));
					if (panelControlData)
						state = kEnabledAction;
					else
						state = kDisabled_Unselected;
					listToUpdate->SetNthActionName(i, menuString);
				}
				break;

			case kSelectUnusedConditionsActionID:
				{
					InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());
					if (tvAdapter->GetNumChildren(tvAdapter->GetRootNode()) > 0)
						state = kEnabledAction;
					else
						state = kDisabled_Unselected;
				}
				break;

			default:
				ASSERT_FAIL(FORMAT_ARGS("ConditionalTextUIPanelMenuAction asked to update an unknown actionID (%lX)", actionID.Get()));
				break;
		}

		listToUpdate->SetNthActionState(i, state);
	}
} // end UpdateActionStates()

// -----------------------------------------------------------------------------

void ConditionalTextUIPanelMenuAction::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{	
#pragma unused(mousePoint)
	switch (actionID.Get()) 
	{
		case kShowAllTagsActionID:
			Utils<Facade::IConditionalTextFacade>()->ShowAllConditions(ac->GetContextWorkspace(), kTrue);
			break;
			
		case kHideAllTagsActionID:
			Utils<Facade::IConditionalTextFacade>()->ShowAllConditions(ac->GetContextWorkspace(), kFalse);
			break;

		case kNewConditionTagActionID:
			Utils<Facade::IConditionalTextUIFacade>()->DoConditionOptionsDialog(ac->GetContextWorkspace(), kInvalidUID);
			break;

		case kLoadConditionTagsActionID:
			Utils<Facade::IConditionalTextUIFacade>()->LoadConditions(ac->GetContextWorkspace(), kFalse);
			break;

		case kLoadConditionTagsAndSetsActionID:
			Utils<Facade::IConditionalTextUIFacade>()->LoadConditions(ac->GetContextWorkspace(), kTrue);
			break;

		case kEditConditionTagActionID:
			{
				InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kConditionalTextUIPanelWidgetID));
				IControlView* treeView = panelData->FindWidget(kConditionTagListTreeViewWidgetID);
				InterfacePtr<ITreeViewController> tvController(treeView, UseDefaultIID());
				ASSERT(tvController != nil);

				NodeIDList selNodes;
				tvController->GetSelectedItems(selNodes);
				
				TreeNodePtr<UIDNodeID> uidNodeID(selNodes[0]);
				Utils<Facade::IConditionalTextUIFacade>()->DoConditionOptionsDialog(ac->GetContextWorkspace(), uidNodeID->GetUID());
			}
			break;

		case kDeleteConditionTagActionID:
			{
				InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kConditionalTextUIPanelWidgetID));
				IControlView* treeView = panelData->FindWidget(kConditionTagListTreeViewWidgetID);
				InterfacePtr<ITreeViewController> tvController(treeView, UseDefaultIID());
				ASSERT(tvController != nil);

				NodeIDList selNodes;
				tvController->GetSelectedItems(selNodes);

				K2Vector<UID> tagUIDsToDelete;
				for (int32 i = 0; i < selNodes.size(); i++)
				{
					TreeNodePtr<UIDNodeID> uidNodeID(selNodes[i]);
					tagUIDsToDelete.push_back(uidNodeID->GetUID());
				}
				Utils<Facade::IConditionalTextUIFacade>()->DeleteConditions(ac->GetContextWorkspace(), tagUIDsToDelete, kFalse);
			}
			break;

		case kShowConditionIndicatorsActionID:
			{
				Utils<Facade::IConditionalTextFacade>()->SetShowConditionIndicators(ac->GetContextWorkspace(), IConditionalTextOptions::kShow);
			}
			break;

		case kShowAndPrintConditionIndicatorsActionID:
			{
				Utils<Facade::IConditionalTextFacade>()->SetShowConditionIndicators(ac->GetContextWorkspace(), IConditionalTextOptions::kShowAndPrint);
			}
			break;

		case kHideConditionIndicatorsActionID:
			{
				Utils<Facade::IConditionalTextFacade>()->SetShowConditionIndicators(ac->GetContextWorkspace(), IConditionalTextOptions::kHide);
			}
			break;

		case kShowHideConditionSetOptionsActionID:
			{
				Utils<IPalettePanelUtils>()->ShowHideOptions(kConditionalTextUIPanelBoss);
			}
			break;

		case kSelectUnusedConditionsActionID:
			{
				Utils<Facade::IConditionalTextUIFacade>()->SelectUnusedConditions(ac->GetContextWorkspace());
			}
			break;

		default: 
			ASSERT_FAIL(FORMAT_ARGS("ConditionalTextUIPanelMenuAction received an unknown actionID (%lX)", actionID.Get()));
			break;
	}
} // end DoAction()

// -----------------------------------------------------------------------------

bool16 ConditionalTextUIPanelMenuAction::CanShowAll(IActiveContext* ac)
{
	bool16 someToShow = kFalse;
	IDataBase *db = ::GetDataBase(ac->GetContextWorkspace());
	
	InterfacePtr<IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryActiveConditionList(ac));
	if (tagList)
	{
		for (int32 i = 0; i < tagList->GetCount(); i++)
		{
			InterfacePtr<IConditionTag> condition(db, tagList->GetNthCondition(i), UseDefaultIID());
			if (!condition->IsVisible()) 
			{
				someToShow = kTrue;
				break;
			}
		}
	}
	
	return someToShow;
}

// -----------------------------------------------------------------------------

bool16 ConditionalTextUIPanelMenuAction::CanHideAll(IActiveContext* ac)
{
	bool16 someToHide = kFalse;
	IDataBase *db = ::GetDataBase(ac->GetContextWorkspace());
	
	InterfacePtr<IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryActiveConditionList(ac));
	if (tagList)
	{
		for (int32 i = 0; i < tagList->GetCount(); i++)
		{
			InterfacePtr<IConditionTag> condition(db, tagList->GetNthCondition(i), UseDefaultIID());
			if (condition->IsVisible()) 
			{
				someToHide = kTrue;
				break;
			}
		}
	}
	
	return someToHide;
}

