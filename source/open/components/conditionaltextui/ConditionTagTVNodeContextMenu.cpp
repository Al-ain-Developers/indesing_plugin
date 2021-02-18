//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagTVNodeContextMenu.cpp $
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
#include "IBoolData.h"
#include "IConditionTagSuite.h"
#include "IConditionalTextFacade.h"
#include "IConditionalTextUIFacade.h"
#include "IPanelControlData.h"
#include "IStringData.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"

// ----- Include files -----

#include "CActionComponent.h"

// ----- Utility files -----

#include "EventUtilities.h"
#include "IInCopySharedUtils.h"
#include "IMenuUtils.h"
#include "IPalettePanelUtils.h"
#include "ISelectionUtils.h"
#include "StringUtils.h"
#include "Utils.h"

// ----- ID files -----

#include "GenericID.h"
#include "ConditionalTextUIID.h"
#include "UIDNodeID.h"

class ConditionTagTVNodeContextMenu : public CActionComponent
{
	public:
		ConditionTagTVNodeContextMenu(IPMUnknown *boss) : CActionComponent(boss) {}

		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

	private:
		virtual IPMUnknown* QueryConditionTagTreeViewPanel() const;
#if 0
		PMString GetStyleName(IPMUnknown* widget);
		void SetMenuName(PMString& menuItemString, IActionStateList *listToUpdate, int32 actionIndex, const PMString& styleName);

#endif
};

CREATE_PMINTERFACE(ConditionTagTVNodeContextMenu, kConditionTagTVNodeContextMenuImpl)

#if 0
PMString ConditionTagTVNodeContextMenu::GetStyleName(IPMUnknown* widget)
{
	InterfacePtr<IStringData> iStyleNameData(widget, UseDefaultIID());
	ASSERT(iStyleNameData != nil);
	PMString styleName ;
	if ( iStyleNameData )
		styleName = iStyleNameData->GetString();
	return styleName;
}

void ConditionTagTVNodeContextMenu::SetMenuName(PMString& menuItemString, IActionStateList* listToUpdate, int32 actionIndex, const PMString& styleName)
{
	menuItemString.Translate();

	PMString localStyleName(styleName);
	if (!localStyleName.HasTranslated())
		localStyleName.Translate();

	// Convert & to && if user-entered style name contains &.
	// Prevents it from being interpreted as an accelerator.
	Utils<IMenuUtils>()->InsertAmpersandForDisplay(&localStyleName);
	::ReplaceStringParameters(&menuItemString, localStyleName);

	listToUpdate->SetNthActionName(actionIndex, menuItemString);
}
#endif

void ConditionTagTVNodeContextMenu::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	InterfacePtr<const IWidgetParent> parentInterface(widget, UseDefaultIID());
	if ( !widget || !parentInterface )
		return ;	//called from scripting

	IWorkspace* ws = ac->GetContextWorkspace();
	InterfacePtr<IPMUnknown> iTreeViewWidgetParent(QueryConditionTagTreeViewPanel());
	InterfacePtr<IUIDData>	forDB((IUIDData*)parentInterface->QueryParentFor(IID_IUIDDATA));
	IDataBase* db = forDB ? forDB->GetItemDataBase() : nil;
	if ( db == nil )
		return ;	//called from scripting

	if (!Utils<IInCopySharedUtils>()->StylesEditable(db))
		return;	// Bail - no context menu if not editable.

	InterfacePtr<ITreeNodeIDData> nodeIDData(widget, UseDefaultIID());
	TreeNodePtr<UIDNodeID> tagNode(nodeIDData->Get());
	NodeID nodeID = nodeIDData->Get();
	InterfacePtr<ITreeViewController> treeController((ITreeViewController*)parentInterface->QueryParentFor(IID_ITREEVIEWCONTROLLER));
	if (treeController)
	{
		InterfacePtr<ITreeViewHierarchyAdapter> adapter(treeController, IID_ITREEVIEWHIERARCHYADAPTER);
		bool16 bUnconditional = (nodeID == adapter->GetRootNode());
		if (bUnconditional)
			return;		// Bail -- no context menu on "[Unconditional]" item; TODO - perhaps Apply [Unconditional] like style [None]?
	}

	UID selectedConditionTagUID = tagNode->GetUID();
	InterfacePtr<IConditionTag> tag(db, tagNode->GetUID(), UseDefaultIID());
	PMString selectedTagName(tag->GetName());
	selectedTagName.SetTranslatable(kFalse);

	const int32 nCount = listToUpdate->Length();
	bool16 bIsUnconditionalItem = kFalse;
	for (int32 i = 0; i < nCount; i++)
	{
		ActionID nAction = listToUpdate->GetNthAction(i);

		switch (nAction.Get())
		{
		case kContextMenuUnapplyConditionTagActionID:
			{
				if (!bIsUnconditionalItem)
				{
					ISelectionManager* selMgr = ac->GetContextSelection();
					InterfacePtr<IConditionTagSuite> conditionsSuite(static_cast<IConditionTagSuite*>(selMgr->QueryIntegratorSuite(IID_ICONDITIONTAGSUITE, ISelectionManager::kEnabledInterface)));
					bool16 bOKtoEnable = kFalse;
					if (conditionsSuite)
					{
						UIDList toAllChars;
						UIDList toSomeChars;
						conditionsSuite->GetAppliedConditionTags(toAllChars, toSomeChars);
						// See whether the tag is in either list
						if (toAllChars.Location(selectedConditionTagUID) >= 0 || toSomeChars.Location(selectedConditionTagUID) >= 0)
							bOKtoEnable = kTrue;
					}
					listToUpdate->SetNthActionState(i, bOKtoEnable ? kEnabledAction : kDisabled_Unselected);
					PMString actionName("#CondTextUI_RtMenuUnapplyTag", PMString::kTranslateDuringCall);
					ReplaceStringParameters(&actionName, selectedTagName);
					listToUpdate->SetNthActionName(i, actionName);
				}
				break;
			}
		case kContextMenuDeleteConditionTagActionID:
			{
				if (!bIsUnconditionalItem)
				{
					listToUpdate->SetNthActionState(i, kEnabledAction);
					PMString actionName("#CondTextUI_RtMenuDeleteTag", PMString::kTranslateDuringCall);
					ReplaceStringParameters(&actionName, selectedTagName);
					listToUpdate->SetNthActionName(i, actionName);
				}
				break;
			}
		case kContextMenuEditConditionTagActionID:
			{
				if (!bIsUnconditionalItem)
				{
					listToUpdate->SetNthActionState(i, kEnabledAction);
					PMString actionName("#CondTextUI_RtMenuEditTag", PMString::kTranslateDuringCall);
					ReplaceStringParameters(&actionName, selectedTagName);
					listToUpdate->SetNthActionName(i, actionName);
				}
				break;
			}
		default:
			ASSERT_FAIL("Unrecognized ActionID in ConditionTagTVNodeContextMenu::UpdateActionStates");
			break;
		}

	}
}


void ConditionTagTVNodeContextMenu::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	IWorkspace* ws = ac->GetContextWorkspace();

	InterfacePtr<IPMUnknown> iTreeViewWidgetParent(QueryConditionTagTreeViewPanel());

	Utils<Facade::IConditionalTextUIFacade> UIfacade;
//    InterfacePtr<IWidgetParent> parentInterface(widget, UseDefaultIID());
  //  InterfacePtr<IWidgetParent> treeNodeWidget(parentInterface->GetParent(), UseDefaultIID());

    InterfacePtr<ITreeNodeIDData> nodeID(widget, UseDefaultIID());
    TreeNodePtr<UIDNodeID> tagNode(nodeID->Get());
	UID selectedConditionTagUID = tagNode->GetUID();

	switch (actionID.Get())
	{
		case kContextMenuUnapplyConditionTagActionID:
			{
				K2Vector<UID> tags;
				tags.push_back(selectedConditionTagUID);
				ISelectionManager* selMgr = ac->GetContextSelection();
				InterfacePtr<IConditionTagSuite> conditionsSuite(static_cast<IConditionTagSuite*>(selMgr->QueryIntegratorSuite(IID_ICONDITIONTAGSUITE, ISelectionManager::kEnabledInterface)));
				if (conditionsSuite)
					conditionsSuite->UnapplyConditionTags(tags);
				break;
			}

		case kContextMenuDeleteConditionTagActionID:
			{
				K2Vector<UID> tagToDelete;
				tagToDelete.push_back(selectedConditionTagUID);
				UIfacade->DeleteConditions(ws, tagToDelete, kFalse);
				break;
			}

		case kContextMenuEditConditionTagActionID:
			{
				UIfacade->DoConditionOptionsDialog(ws, selectedConditionTagUID);
				break;
			}

		default:
			ASSERT_FAIL("Unrecognized ActionID in StyleListContextMenu::DoAction");
			break;
	}
}

//----------------------------------------------------------------------------------------
// ConditionTagTVNodeContextMenu::QueryConditionTagTreeViewPanel	
// TODO -- make this a util?
//----------------------------------------------------------------------------------------
IPMUnknown* ConditionTagTVNodeContextMenu::QueryConditionTagTreeViewPanel() const
{
    IPMUnknown* listParent = nil;

    InterfacePtr<IPanelControlData> iPanelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kConditionalTextUIPanelWidgetID));
    if (iPanelData)
    {
        IControlView* treeView = iPanelData->FindWidget(kConditionTagListTreeViewWidgetID);
        if (treeView)
        {
            listParent = treeView->QueryInterface(IID_IWIDGETPARENT);
        }
    }

    return listParent;
}

