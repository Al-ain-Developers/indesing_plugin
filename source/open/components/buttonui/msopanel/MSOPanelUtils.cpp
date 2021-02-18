//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelUtils.cpp $
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

#include "IAppearanceSuite.h"
#include "IAppearanceItemFacade.h"
#include "IDocument.h"
#include "IDragDropController.h"
#include "IFormFieldSuite.h"
#include "IInLineEditController.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "IStateData.h"
#include "ITextControlData.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "CAlert.h"
#include "FormFieldUIDefs.h"
#include "K2Vector.tpp"
#include "MSOStateNodeID.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "EventUtilities.h"
#include "FormFieldUIUtils.h"
#include "IFormFieldUtils.h"
#include "MSOPanelUtils.h"
#include "IPalettePanelUtils.h"
#include "ErrorUtils.h"

// ----- ID.h files -----

#include "FormFieldID.h"
#include "FormFieldUIID.h"


// -----------------------------------------------------------------------------

void MSOPanelUtils::RebuildTreeViewList(ITreeViewMgr *treeViewMgr)
{
	ASSERT(treeViewMgr != nil);
	if (!treeViewMgr) return;

	InterfacePtr<IFormFieldSuite> formFieldSuite(FormFieldUIUtils::QueryFormSuite());
	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (formFieldSuite && formFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss) &&
		iAppearanceSuite && iAppearanceSuite->NumStates())
	{
		// Update the tree and make sure the active appearance is selected
		treeViewMgr->ChangeRoot();
		SelectActiveAppearance(treeViewMgr);
	}
	else
	{
		// Clear the tree
		treeViewMgr->ChangeRoot();
	}
} // end RebuildTreeViewList()

// -----------------------------------------------------------------------------

bool16 MSOPanelUtils::SelectActiveAppearance(ITreeViewMgr *treeViewMgr)
{
	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (iAppearanceSuite)
	{
		NodeID activeMSOStateNode = MSOStateNodeID::Create(iAppearanceSuite->GetActiveState());

		InterfacePtr<ITreeViewController> treeViewController(treeViewMgr, UseDefaultIID());
		if (!treeViewController)
		{
			InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));

			IControlView* treeView = panelData->FindWidget(kMSOPanelTreeWidgetID);
			treeViewController.reset(InterfacePtr<ITreeViewController>(treeView, UseDefaultIID()).forget());
			ASSERT(treeViewController != nil);
		}

		if (!treeViewController->IsSelected(activeMSOStateNode))
		{
			treeViewController->DeselectAll();
			if (treeViewController->Select(activeMSOStateNode) == ITreeViewController::eSuccess && treeViewController->IsSelected(activeMSOStateNode))
			{
				InterfacePtr<ITreeViewMgr> tvMgr(treeViewController, UseDefaultIID());
				// 3213826: It may be so that the node has not been yet added to the tree. The tree would get
				// updated later, if the node has not been added, don't do anything and just return from here.
				if(tvMgr->Search(activeMSOStateNode) != kInvalidNodeID )
					tvMgr->ScrollToNode(activeMSOStateNode, ITreeViewMgr::eScrollIntoView);
				return kTrue;
			}
		}
	}
	return kFalse;
} // end SelectActiveAppearance()

// -----------------------------------------------------------------------------

Form::AppearanceState MSOPanelUtils::GetSelectedAppearance()
{
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));

	IControlView* treeView = panelData->FindWidget(kMSOPanelTreeWidgetID);
	InterfacePtr<ITreeViewController> tvController(treeView, UseDefaultIID());
	ASSERT(tvController != nil);

	NodeIDList selNodes;
	tvController->GetSelectedItems(selNodes);
	if (selNodes.size() == 1)
	{
		TreeNodePtr<MSOStateNodeID> msoStateNode(selNodes[0]);
		return msoStateNode->GetAppearance();
	}

	return Form::kStateInvalid;
} // end GetSelectedAppearance()

// -----------------------------------------------------------------------------

void MSOPanelUtils::EnableSelectedStateNameILE()
{
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));
	if (!panelData) return;

	IControlView* treeView = panelData->FindWidget(kMSOPanelTreeWidgetID);
	InterfacePtr<ITreeViewMgr> treeViewMgr(treeView, UseDefaultIID());
	if (treeViewMgr)
	{
		InterfacePtr<ITreeViewController> tvController(treeViewMgr, UseDefaultIID());

		NodeIDList selNodes;
		tvController->GetSelectedItems(selNodes);
		if (selNodes.size() == 1)
		{
			InterfacePtr<IControlView> nameWidget(treeViewMgr->QueryWidgetFromNode(selNodes[0]));
			if (!nameWidget)
			{
				// force the tree to apply widgets to nodes
				treeViewMgr->ChangeRoot();
				nameWidget.reset((IControlView *)treeViewMgr->QueryWidgetFromNode(selNodes[0]));
			}

			if (nameWidget)
			{
				InterfacePtr<IPanelControlData>	childWidgets(nameWidget, UseDefaultIID());
				IControlView* editableWidget = childWidgets->FindWidget(kTreeNodeNameWidgetID);
				InterfacePtr<IInLineEditController> iController(editableWidget, UseDefaultIID());
				if (iController)
					iController->BeginEditing();
			}
		}
	}
}

// -----------------------------------------------------------------------------

ErrorCode MSOPanelUtils::CreateMSO(IAppearanceSuite::MultiItemSelectionPolicy multiItemSelectionPolicy)
{
	ErrorCode err (kSuccess);

	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (iAppearanceSuite)
	{
		bool16 haveMixedSelection(kFalse);
		InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));
		if (panelData)
		{
			IControlView* mixedSelectionView = panelData->FindWidget(kMSOMixedStaticWidgetID);
			haveMixedSelection = mixedSelectionView && mixedSelectionView->IsVisible();
		}

		if (haveMixedSelection)
		{
			// The top-most state which is also the top-most in z-order is active.
			err = iAppearanceSuite->CreateAppearanceItem(kMultiStateObjectItemBoss, multiItemSelectionPolicy);

			// Select the active state
			if (err == kSuccess)
				MSOPanelUtils::SelectActiveAppearance();
		}
		else
		{
			// The bottom-most state which is the copy of the original page item is active.
			ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
			err = iAppearanceSuite->CreateAppearanceItem(kMultiStateObjectItemBoss);
			if (err == kSuccess)
				iAppearanceSuite->SetActiveState(iAppearanceSuite->GetNthState(iAppearanceSuite->NumStates()-1));
			err = CmdUtils::EndCommandSequence(cmdSeq);

			if (err == kSuccess)
			{
				// Select the active state and enable inline edit mode.
				MSOPanelUtils::SelectActiveAppearance();
				MSOPanelUtils::EnableSelectedStateNameILE();
			}
		}
	}

	return err;
} // end CreateMSO()

// -----------------------------------------------------------------------------

ErrorCode MSOPanelUtils::CreateNewState(StateLocation location, Form::AppearanceState wrtToThisState)
{
	ErrorCode err (kSuccess);

	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (iAppearanceSuite)
	{
		Form::AppearanceState newState = iAppearanceSuite->GetNewState();
		if (newState != Form::kStateInvalid)
		{
			ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
			cmdSeq->SetName("$$$/Command/NewState");

			int32 wrtStatePos = iAppearanceSuite->GetStatePosition(wrtToThisState);
			if (location == kOnTop)
			{
				err = iAppearanceSuite->NewState(newState, 0);
			}
			else if (location == kBelowActive)
			{
				if (wrtStatePos < iAppearanceSuite->NumStates()-1)
					err = iAppearanceSuite->NewState(newState, wrtStatePos+1);
				else
					err = iAppearanceSuite->NewState(newState, IAppearanceList::kLastInOrder);
			}
			else // kAboveActive
			{
				err = iAppearanceSuite->NewState(newState, wrtStatePos);
			}

			if (err == kSuccess)
			{
				iAppearanceSuite->SetActiveState(newState);
				iAppearanceSuite->SelectActiveState();
			}

			err = CmdUtils::EndCommandSequence(cmdSeq);

			if (err == kSuccess)
			{
				// Select the active state and enable inline edit mode unless it is a result of drag
				// and drop in which case there is an outer command sequence that is not ended yet
				// so the tree isn't updated and this will assert. Alternatively, enabling could be
				// done when the nodes are added but that would enable for undo of a delete as well
				// and Tom M. agrees that side-effect is too strange.
				InterfacePtr<IDragDropController> dragdropController(GetExecutionContextSession(), UseDefaultIID());
				if (!dragdropController || !dragdropController->IsDragInProgress())
				{
					MSOPanelUtils::SelectActiveAppearance();
					MSOPanelUtils::EnableSelectedStateNameILE();
				}
			}
		}
	}
	return err;
} // end CreateNewState()

// -----------------------------------------------------------------------------

ErrorCode MSOPanelUtils::DeleteState(Form::AppearanceState stateToDelete)
{
	ErrorCode err(kSuccess);

	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (iAppearanceSuite)
	{
		// Check if the MSO has 2 states and alert user it will be destroyed.
		if (iAppearanceSuite->NumStates() == 2) 
		{
			// Display a warning dialog
			PMString alertStr("$$$/Dialog/MSOPanel/DeletesMSOAlert");
			int16 whatToDo = CAlert::ModalAlert(alertStr,
				kOKString, 
				kCancelString, 
				kNullString, 
				1,                        // pass in 1, 2, or 3 to make that button the default button or 0 for no default
				CAlert::eWarningIcon);
			// If they don't want to continue, then punt
			if ( whatToDo == 2 )
				return kCancel;
			else
			{
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
				cmdSeq->SetName("$$$/Command/DeleteState");

				err = iAppearanceSuite->DeleteState(stateToDelete);

				if (err == kSuccess)
					err = iAppearanceSuite->ReleaseAllAppearancesAsObjects();

				CmdUtils::EndCommandSequence(cmdSeq);
			}
		}
		else
		{
			// Check if the Alt/Option key is down
			bool16 optionKeyDown = ::IsOptionAltKeyPressed();
			if (!optionKeyDown && iAppearanceSuite->HasAppearanceContent(stateToDelete)) 
			{
				// Display a delete warning dialog
				PMString alertStr("$$$/Dialog/FormFieldUI/DeleteAlert");
				int16 whatToDo = CAlert::ModalAlert(alertStr,
					kOKString, 
					kCancelString, 
					kNullString, 
					1,                        // pass in 1, 2, or 3 to make that button the default button or 0 for no default
					CAlert::eWarningIcon);
				// If they don't want to continue, then punt
				if ( whatToDo == 2 )
					return kCancel;
			}
		}

		// Delete the state
		err = iAppearanceSuite->DeleteState(stateToDelete);
	}

	return err;
} // end DeleteState()

// -----------------------------------------------------------------------------

ErrorCode MSOPanelUtils::ReleaseState(Form::AppearanceState stateToRelease)
{
	ErrorCode err(kSuccess);

	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (iAppearanceSuite)
	{
		// Check if the MSO has 2 states and alert user it will be destroyed.
		if (iAppearanceSuite->NumStates() == 2) 
		{
			// Display a warning dialog
			PMString alertStr("$$$/Dialog/MSOPanel/ReleaseAlert");
			int16 whatToDo = CAlert::WarningAlertWithDontShowAgain(alertStr,
				kReleaseMSOStateAlertMsgID,
				kTrue);
			// If they don't want to continue, then punt
			if ( whatToDo == 3 )
				return kCancel;
			else
				return iAppearanceSuite->ReleaseAllAppearancesAsObjects();
		}

		err = iAppearanceSuite->ReleaseAppearanceAsObject(stateToRelease);
	}

	return err;
} // end ReleaseActiveState()

// -----------------------------------------------------------------------------

ErrorCode MSOPanelUtils::ReleaseAllStates()
{
	ErrorCode err(kSuccess);

	InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (iAppearanceSuite)
	{
		// Display a warning dialog
		PMString alertStr("$$$/Dialog/MSOPanel/ReleaseAllAlert");
		int16 whatToDo = CAlert::WarningAlertWithDontShowAgain(alertStr,
			kReleaseAllMSOStateAlertMsgID, 
			kTrue);
		// If they don't want to continue, then punt
		if ( whatToDo == 3 )
			return kCancel;

		err = iAppearanceSuite->ReleaseAllAppearancesAsObjects();
	}

	return err;
} // end ReleaseAllStates()

// -----------------------------------------------------------------------------

bool MSOPanelUtils::StateExists(const PMString& stateName)
{
	InterfacePtr<IAppearanceSuite> appearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (appearanceSuite)
	{
		int32 numStates = appearanceSuite->NumStates();
		for (int32 i=0; i < numStates; ++i)
		{
			if (appearanceSuite->GetStateName(appearanceSuite->GetNthState(i)) == stateName)
				return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

void MSOPanelUtils::AcceptMSONameIfNeeded(IAppearanceSuite *iAppearanceSuite)
{
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));
	if (panelData && iAppearanceSuite)
	{
		PMString currentName = "";
		if (iAppearanceSuite->GetName(currentName))
		{
			IControlView* msoNameView = panelData->FindWidget(kMSONameEditWidgetID);
			InterfacePtr<ITextControlData> iEdit(msoNameView, UseDefaultIID());

			if (iEdit && !iEdit->GetString().IsEmpty() && iEdit->GetString() != currentName) {
				ErrorCode setNameResult = iAppearanceSuite->SetName(iEdit->GetString());
				if (setNameResult != kSuccess)
				{
					PMString string = ErrorUtils::PMGetErrorString(setNameResult);
					if (!string.IsNull()) {
						ErrorUtils::PMSetGlobalErrorCode(kSuccess);
						CAlert::ErrorAlert(string);
					}
				}
			}
		}
	}
} // AcceptMSONameIfNeeded()
