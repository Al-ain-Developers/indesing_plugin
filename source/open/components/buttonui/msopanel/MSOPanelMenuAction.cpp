//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelMenuAction.cpp $
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
#include "IBoolData.h"
#include "IDialog.h"
#include "IDialogController.h"
#include "IDocument.h"
#include "IFormFieldSuite.h"
#include "IIntData.h"
#include "INamedPageItemList.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ITreeViewWidgetMgr.h"

// ----- Includes -----

#include "CActionComponent.h"
#include "FormFieldUIDefs.h"
#include "K2Vector.tpp"
#include "MSOStateNodeID.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"
#include "IFormFieldUtils.h"
#include "MSOPanelUtils.h"
#include "IPalettePanelUtils.h"
#include "StringUtils.h"
#include "UserInterfaceUtils.h"

// ----- ID.h files -----

#include "AppUIID.h"
#include "FormFieldUIID.h"


class MSOPanelMenuAction : public CActionComponent
{
public:
	MSOPanelMenuAction(IPMUnknown *boss);
	
	virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
	virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
};

// =============================================================================
// *** MSOPanelMenuAction impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelMenuAction, kMSOPanelMenuActionImpl)

MSOPanelMenuAction::MSOPanelMenuAction(IPMUnknown *boss) : CActionComponent(boss)
{
} // end constructor

// -----------------------------------------------------------------------------

void MSOPanelMenuAction::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
#pragma unused(mousePoint)
	int32 count = listToUpdate->Length();

	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));
	if (!panelData)	return;
	
	Form::AppearanceState selectedAppearance = MSOPanelUtils::GetSelectedAppearance();

	while (count--)
	{
		ActionID action = listToUpdate->GetNthAction(count);
		
		switch (action.Get())
		{
			case kNewMSOStateActionID:
			{
				if (selectedAppearance == Form::kStateInvalid)
				{
					InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
					InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
					if ((iFormFieldSuite && iFormFieldSuite->CanCreateFieldFromSelection(kMultiStateObjectItemBoss)) ||
						(iAppearanceSuite && iAppearanceSuite->CanAddItemsAsStates(kMultiStateObjectItemBoss)))
					{
						listToUpdate->SetNthActionState(count, kEnabledAction);
					}
					else
						listToUpdate->SetNthActionState(count, kDisabled_Unselected);
				}
				else
					listToUpdate->SetNthActionState(count, kEnabledAction);
				break;
			}

			case kAddToMSOStateActionID:
			{
				int16 state = kDisabled_Unselected;
				InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
				if (iAppearanceSuite && iAppearanceSuite->CanAddItemsAsStates(kMultiStateObjectItemBoss))
					state = kEnabledAction;

				listToUpdate->SetNthActionState(count, state);
				break;
			}

			case kPasteIntoMSOStateActionID:
			{
				int16 state = kDisabled_Unselected;
				if (selectedAppearance != Form::kStateInvalid)
				{
					InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
					if (iAppearanceSuite && iAppearanceSuite->CanPasteIntoState(kMultiStateObjectItemBoss))
						state = kEnabledAction;
				}
				listToUpdate->SetNthActionState(count, state);
				break;
			}

			case kReleaseMSOStateActionID:
			case kReleaseAllMSOStatesActionID:
			{
				if (selectedAppearance == Form::kStateInvalid)
					listToUpdate->SetNthActionState(count, kDisabled_Unselected);
				else
				{
					bool16 flag;
					InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
					if (iFormFieldSuite && !iFormFieldSuite->CanDestroyFieldFromSelection(flag))
						listToUpdate->SetNthActionState(count, kDisabled_Unselected);
					else
						listToUpdate->SetNthActionState(count, kEnabledAction);
				}
				break;
			}

			case kDeleteMSOStateActionID:
			{
				if (selectedAppearance == Form::kStateInvalid)
					listToUpdate->SetNthActionState(count, kDisabled_Unselected);
				else
					listToUpdate->SetNthActionState(count, kEnabledAction);
				break;
			}

			case kDeleteMSOStateContextActionID:
			{
				int16 state = kDisabled_Unselected;
				PMString menuItemName("$$$/Menu/MSOPanel/DeleteStateContextMenu");
				menuItemName.Translate();
				InterfacePtr<const ITreeNodeIDData>	nodeData(widget, UseDefaultIID());
				if (nodeData)
				{
					TreeNodePtr<const MSOStateNodeID> msoStateNode(nodeData->Get());
					if (msoStateNode->GetAppearance() != Form::kStateInvalid)
					{
						state = kEnabledAction;

						InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
						::ReplaceStringParameters(&menuItemName, iAppearanceSuite->GetStateName(msoStateNode->GetAppearance()));
					}
				}
				listToUpdate->SetNthActionName(count, state == kEnabledAction ? menuItemName : PMString());
				listToUpdate->SetNthActionState(count, state);
				break;
			}

			case kPasteIntoMSOStateContextActionID:
			{
				int16 state = kDisabled_Unselected;
				PMString menuItemName("$$$/Menu/MSOPanel/PasteIntoStateContextMenu");
				menuItemName.Translate();
				InterfacePtr<const ITreeNodeIDData>	nodeData(widget, UseDefaultIID());
				if (nodeData)
				{
					InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
					if (iAppearanceSuite && iAppearanceSuite->CanPasteIntoState(kMultiStateObjectItemBoss))
					{
						TreeNodePtr<const MSOStateNodeID> msoStateNode(nodeData->Get());
						if (msoStateNode->GetAppearance() != Form::kStateInvalid)
						{
							state = kEnabledAction;

							::ReplaceStringParameters(&menuItemName, iAppearanceSuite->GetStateName(msoStateNode->GetAppearance()));
						}
					}
				}
				listToUpdate->SetNthActionName(count, state == kEnabledAction ? menuItemName : PMString());
				listToUpdate->SetNthActionState(count, state);
				break;
			}

			case kReleaseMSOStateContextActionID:
			{
				int16 state = kDisabled_Unselected;
				PMString menuItemName("$$$/Menu/MSOPanel/ReleaseStateContextMenu");
				menuItemName.Translate();
				InterfacePtr<const ITreeNodeIDData>	nodeData(widget, UseDefaultIID());
				if (nodeData)
				{
					TreeNodePtr<const MSOStateNodeID> msoStateNode(nodeData->Get());
					if (msoStateNode->GetAppearance() != Form::kStateInvalid)
					{
						state = kEnabledAction;

						InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
						::ReplaceStringParameters(&menuItemName, iAppearanceSuite->GetStateName(msoStateNode->GetAppearance()));
					}
				}
				listToUpdate->SetNthActionName(count, state == kEnabledAction ? menuItemName : PMString());
				listToUpdate->SetNthActionState(count, state);
				break;
			}

			case kMSOPanelOptionsActionID:
			{
				listToUpdate->SetNthActionState(count, kEnabledAction);
				break;
			}

			case kHiddenUntilTriggeredActionID:
			{
				int16 state = kDisabled_Unselected;

				InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
				if (iFormFieldSuite && !iFormFieldSuite->IsDefaultSelection() &&
					iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss))
				{
					state = kEnabledAction;

					InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
					if (iAppearanceSuite && iAppearanceSuite->GetIsInitiallyHidden())
						state = kEnabledAction|kSelectedAction;
				}
				listToUpdate->SetNthActionState(count, state);
				break;
			}

			case kResetAllMSOsActionID:
			{
				int16 state = kDisabled_Unselected;

				IDocument* doc = ac->GetContextDocument();
				if (doc)
				{
					IDataBase *db = ::GetDataBase(doc);
					UIDList msoList = Utils<IFormFieldUtils>()->GetAllFormItemsOfTypeInDocument(::GetUIDRef(doc), kMultiStateObjectItemBoss);

					for (UIDList::const_iterator i = msoList.begin(); i != msoList.end(); i++) 
					{
						InterfacePtr<IAppearanceList> appearanceList(db, *i, UseDefaultIID());
						if (appearanceList && appearanceList->GetActiveState() != appearanceList->GetNthState(0))
						{
							state = kEnabledAction;
							break;
						}
					}
				}
				listToUpdate->SetNthActionState(count, state);
				break;
			}
		}
	}
} // end UpdateActionStates()

void MSOPanelMenuAction::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	Form::AppearanceState selectedAppearance = MSOPanelUtils::GetSelectedAppearance();

	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (iAppearanceSuite)
		MSOPanelUtils::AcceptMSONameIfNeeded(iAppearanceSuite);

	switch (actionID.Get())
	{
		case kNewMSOStateActionID:
		{
			bool16 canAdd = iAppearanceSuite && iAppearanceSuite->CanAddItemsAsStates(kMultiStateObjectItemBoss);
			if (canAdd)
			{
				if (iAppearanceSuite->AddItemsAsStates(kMultiStateObjectItemBoss, IAppearanceSuite::kAddItemsAsIndividualStates) == kSuccess)
					iAppearanceSuite->SelectAssociatedAppearanceItemOfType(kMultiStateObjectItemBoss);
			}
			else if (selectedAppearance == Form::kStateInvalid)
				MSOPanelUtils::CreateMSO();
			else
				MSOPanelUtils::CreateNewState(MSOPanelUtils::kBelowActive, selectedAppearance);
			break;
		}

		case kDeleteMSOStateActionID:
		{
			ASSERT(selectedAppearance != Form::kStateInvalid);
			MSOPanelUtils::DeleteState(selectedAppearance);
			break;
		}
		case kDeleteMSOStateContextActionID:
		{
			InterfacePtr<const ITreeNodeIDData>	nodeData(widget, UseDefaultIID());
			if (nodeData)
			{
				TreeNodePtr<const MSOStateNodeID> msoStateNode(nodeData->Get());
				ASSERT(msoStateNode->GetAppearance() != Form::kStateInvalid);
				MSOPanelUtils::DeleteState(msoStateNode->GetAppearance());
			}
			break;
		}
		
		case kAddToMSOStateActionID:
		{
			if (iAppearanceSuite)
			{
				ErrorCode err = iAppearanceSuite->AddItemsAsStates(kMultiStateObjectItemBoss, IAppearanceSuite::kAddItemsToActiveState);
				if (err == kSuccess)
					iAppearanceSuite->SelectAssociatedAppearanceItemOfType(kMultiStateObjectItemBoss);
			}

			break;
		}
		
		case kPasteIntoMSOStateActionID:
		{
			ASSERT(selectedAppearance != Form::kStateInvalid);
			if (iAppearanceSuite)
				iAppearanceSuite->PasteIntoState(kMultiStateObjectItemBoss, selectedAppearance);
			break;
		}
		
		case kPasteIntoMSOStateContextActionID:
		{
			if (iAppearanceSuite)
			{
				InterfacePtr<const ITreeNodeIDData>	nodeData(widget, UseDefaultIID());
				if (nodeData)
				{
					TreeNodePtr<const MSOStateNodeID> msoStateNode(nodeData->Get());
					ASSERT(msoStateNode->GetAppearance() != Form::kStateInvalid);
					iAppearanceSuite->PasteIntoState(kMultiStateObjectItemBoss, msoStateNode->GetAppearance());
				}
			}
			break;
		}
		
		case kReleaseMSOStateActionID:
		{
			ASSERT(selectedAppearance != Form::kStateInvalid);
			MSOPanelUtils::ReleaseState(selectedAppearance);
			break;
		}
		case kReleaseMSOStateContextActionID:
		{
			InterfacePtr<const ITreeNodeIDData>	nodeData(widget, UseDefaultIID());
			if (nodeData)
			{
				TreeNodePtr<const MSOStateNodeID> msoStateNode(nodeData->Get());
				ASSERT(msoStateNode->GetAppearance() != Form::kStateInvalid);
				MSOPanelUtils::ReleaseState(msoStateNode->GetAppearance());
			}
			break;
		}
		
		case kReleaseAllMSOStatesActionID:
		{
			MSOPanelUtils::ReleaseAllStates();
			break;
		}

		case kResetAllMSOsActionID:
		{
			IDocument* doc = ac->GetContextDocument();
			if (doc)
				Utils<IFormFieldUtils>()->ResetAllMultiStateObjects(::GetUIDRef(doc));
			break;
		}

		case kMSOPanelOptionsActionID:
		{
			InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));
			if (panelData) 
			{
				IControlView* treeView = panelData->FindWidget(kMSOPanelTreeWidgetID);
				InterfacePtr<ITreeViewWidgetMgr> tvWidgetMgr(treeView, UseDefaultIID());
				IDialog* dialog = UserInterfaceUtils::GetModalDialog(kFormFieldUIPluginID, kAppearancePanelPrefsDialogRsrcID);

				IControlView* dialogView = dialog->GetDialogPanel();
				InterfacePtr<IDialogController> iDialogController(dialogView, IID_IDIALOGCONTROLLER);
				InterfacePtr<IIntData> iThumbSizeIndex(iDialogController, IID_IINTDATA);
				iThumbSizeIndex->Set(tvWidgetMgr->GetStyle());

				dialog->Open();
				dialog->WaitForDialog();

				InterfacePtr<IBoolData> iDialogCancelled(iDialogController, IID_IDIALOGWASCANCELLED);
				if (!iDialogCancelled || iDialogCancelled->Get() == kFalse)
				{
					InterfacePtr<IPanelDetailController> detailController(panelData, UseDefaultIID());
					detailController->ShowDetailLevel(iThumbSizeIndex->Get()-1);
				}
			}
			break;
		}

		case kHiddenUntilTriggeredActionID:
		{
			InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
			if (iFormFieldSuite && !iFormFieldSuite->IsDefaultSelection() &&
				iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss))
			{
				// Toggle the setting for initially hidden.
				if (iAppearanceSuite)
					iAppearanceSuite->SetIsInitiallyHidden(!iAppearanceSuite->GetIsInitiallyHidden());
			}
			break;
		}
	}
} // end DoAction()