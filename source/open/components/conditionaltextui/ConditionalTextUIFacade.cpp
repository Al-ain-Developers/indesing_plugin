//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionalTextUIFacade.cpp $
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

#include "IApplication.h"
#include "IConditionTagList.h"
#include "IControlView.h"
#include "IDialogController.h"
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IPanelControlData.h"
#include "IStoryList.h"
#include "ITextReferences.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewMgr.h"
#include "ITreeViewWidgetMgr.h"
#include "IUIDData.h"
#include "IUIDListData.h"
#include "IWindow.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CAlert.h"
#include "ConditionalTextUIDefs.h"
#include "CoreResTypes.h"
#include "ErrorUtils.h"
#include "IconRsrcDefs.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "SysControlIds.h"
#include "UIDList.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "IConditionalTextUIFacade.h"
#include "ConditionalTextUIUtils.h"
#include "IDialogUtils.h"
#include "IInCopySharedUtils.h"
#include "IPalettePanelUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionalTextUIFacade : public CPMUnknown<Facade::IConditionalTextUIFacade>
{
public:
	ConditionalTextUIFacade(IPMUnknown *boss);

	ErrorCode DoConditionOptionsDialog(IWorkspace* ws, UID tagToEdit);
	void UpdateAppliedIcons(IWorkspace* ws, IPanelControlData* iPanelControlData) const;
	ErrorCode DeleteConditions(IWorkspace* ws, const K2Vector<UID>&  tagToDelete, bool16 suppressUI);
	ErrorCode LoadConditions(IWorkspace* ws, bool16 loadConditionTagSets);
	void SelectUnusedConditions(IWorkspace* ws);
private:
	ErrorCode DoConditionDeleteDialog(const UIDList& tagsToDelete);
};

// =============================================================================
// *** ConditionalTextUIFacade impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionalTextUIFacade, kConditionalTextUIFacadeImpl)

ConditionalTextUIFacade::ConditionalTextUIFacade(IPMUnknown *boss) :
	CPMUnknown<IConditionalTextUIFacade>(boss)
{
} // end constructor

// -----------------------------------------------------------------------------

ErrorCode ConditionalTextUIFacade::DoConditionOptionsDialog(IWorkspace* ws, UID tagToEdit)
{	
	// Don't show the options dialog if editing isn't allowed.
	if (!Utils<IInCopySharedUtils>()->StylesEditable(::GetDataBase(ws)))
	{
		CAlert::InformationAlert("InCopyCantModifyConditions");
		return kSuccess;
	}

	// Show the options dialog.
	const RsrcID kDialogRsrcID = kConditionTagOptionsDialogRsrcID;
	const IDialog::DialogType kDialogType = IDialog::kMovableModal;
	const PMLocaleId nLocale = LocaleSetting::GetLocale();
	const RsrcSpec aSpec(nLocale, kConditionalTextUIPluginID, kViewRsrcType,  kDialogRsrcID, kTrue);

	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(app, IID_IDIALOGMGR);
	
	IDialog *dialog = dialogMgr->CreateNewDialog(aSpec, kDialogType);
	ASSERT_MSG(dialog != nil, "ConditionalTextUIFacade::InvokeConditionTagOptionsDialog - can't create dialog!");

	IControlView* dialogView = dialog->GetDialogPanel();
	InterfacePtr<IDialogController> controller(dialogView, IID_IDIALOGCONTROLLER);
	if (controller)
	{
		// Set appropriate window title.
		InterfacePtr<IWindow> window(dialog, IID_IWINDOW);
		if (tagToEdit != kInvalidUID)
			window->SetTitle("#ConditionTag_OptionsDialog"); 
		else
			window->SetTitle("#ConditionTag_OptionsDialogNew"); 

		// Set the UID data for the dialog.
		InterfacePtr<IUIDData> tagData(controller, UseDefaultIID());
		if (tagData)
			tagData->Set(::GetDataBase(ws), tagToEdit);
	}
	dialog->Open();
	dialog->WaitForDialog();

	return kSuccess;
} // end DoConditionOptionsDialog()

// -----------------------------------------------------------------------------

void ConditionalTextUIFacade::UpdateAppliedIcons(IWorkspace* ws, IPanelControlData* iPanelControlData) const
{	
	if (iPanelControlData != nil)
	{
		IControlView* treeView = iPanelControlData->FindWidget(kConditionTagListTreeViewWidgetID);
		InterfacePtr<ITreeViewMgr> treeMgr(treeView, UseDefaultIID());
		ASSERT(treeMgr != nil);

		if (treeMgr != nil)
		{
			InterfacePtr<ITreeViewWidgetMgr> treeWidgetMgr(treeMgr, UseDefaultIID());
			InterfacePtr<IConditionTagList> conditionTagList(ws, UseDefaultIID());
			if (conditionTagList)
			{
				// Update for normal condition items.
				for (int32 i = 0; i < conditionTagList->GetCount(); i++)
				{
					UID tag = conditionTagList->GetNthCondition(i);
					NodeID tagNode = UIDNodeID::Create(tag);
					InterfacePtr<IControlView> tagView(treeMgr->QueryWidgetFromNode(tagNode));
					if (tagView == nil) continue;

					ConditionalTextUIUtils::ApplyAppliedIconToWidget(treeWidgetMgr, tagNode, tagView);
				}
			}

			// Now for the [Unconditional] item.
			InterfacePtr<ITreeViewHierarchyAdapter> adapter(treeMgr, UseDefaultIID());
			InterfacePtr<IControlView> unconditionalView(adapter ? treeMgr->QueryWidgetFromNode(adapter->GetRootNode()) : nil);
			if (unconditionalView)
				ConditionalTextUIUtils::ApplyAppliedIconToWidget(treeWidgetMgr, adapter->GetRootNode(), unconditionalView);
		}
	}
} // end UpdateAppliedIcons()

// -----------------------------------------------------------------------------

ErrorCode ConditionalTextUIFacade::DoConditionDeleteDialog(const UIDList& tagsToDelete)
{	
	const RsrcID kDialogRsrcID = kConditionTagDeleteDialogRsrcID;
	const IDialog::DialogType kDialogType = IDialog::kMovableModal;
	const PMLocaleId nLocale = LocaleSetting::GetLocale();
	const RsrcSpec aSpec(nLocale, kConditionalTextUIPluginID, kViewRsrcType,  kDialogRsrcID, kTrue);

	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(app, IID_IDIALOGMGR);
	
	IDialog *dialog = dialogMgr->CreateNewDialog(aSpec, kDialogType);
	ASSERT_MSG(dialog != nil, "ConditionalTextUIFacade::InvokeConditionTagOptionsDialog - can't create dialog!");

	IControlView* dialogView = dialog->GetDialogPanel();
	InterfacePtr<IDialogController> controller(dialogView, IID_IDIALOGCONTROLLER);
	if (controller)
	{
		// Set the UID data for the dialog.
		InterfacePtr<IUIDListData> tagData(controller, UseDefaultIID());
		if (tagData)
		{
			UIDList *uidList = new UIDList(tagsToDelete);
			tagData->Set(uidList);
		}
	}
	dialog->Open();
	dialog->WaitForDialog();

	return kSuccess;
} // end DoConditionDeleteDialog()

// -----------------------------------------------------------------------------

ErrorCode ConditionalTextUIFacade::DeleteConditions(IWorkspace* ws, const K2Vector<UID>& tagUIDsToDelete, bool16 suppressUI)
{	
	ErrorCode err(kSuccess);

	// If all conditions are being deleted we won't check if used or prompt for replacement.
	bool16 bAllConditionsBeingDeleted(kFalse);
	InterfacePtr<IConditionTagList> tagList(ws, UseDefaultIID());
	if (tagUIDsToDelete.size() >= tagList->GetCount())
	{
		bAllConditionsBeingDeleted = kTrue;
		for (int32 i=0; i < tagList->GetCount(); i++)
		{
			if (K2find(tagUIDsToDelete, tagList->GetNthCondition(i)) == tagUIDsToDelete.end())
			{
				bAllConditionsBeingDeleted = kFalse;
				break;
			}
		}
	}

	UIDList tagsToDelete(::GetDataBase(ws));
	std::copy(tagUIDsToDelete.begin(), tagUIDsToDelete.end(), std::back_inserter(tagsToDelete));
	if (!suppressUI && !bAllConditionsBeingDeleted)
	{
		// Gather list of used condition tags.
		IDataBase* db = ::GetDataBase(ws);
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
		UIDList usedList = doc ? UIDList(db) : UIDList();
		if (doc != nil)
		{
			// Iterate the story list to get the used conditions for the active doc.
			InterfacePtr<IStoryList> storyList(doc, UseDefaultIID());
			int32 storyCount = storyList->GetAllTextModelCount();
			for (int32 storyIndex = 0; storyIndex < storyCount; storyIndex++)
			{
				InterfacePtr<ITextReferences> refs(storyList->GetNthTextModelUID(storyIndex), UseDefaultIID());
				for (int32 i = 0; refs && i < refs->CountUsedConditions(); i++)
					usedList.Append(refs->GetUsedCondition(i));
			}
		}

		// See if any we are deleting are used.
		bool16 bIsUsedInDoc(kFalse);
		if (doc != nil)
		{
			for (int32 i=0; i < tagsToDelete.Length() && !bIsUsedInDoc; i++)
			{
				if (usedList.Location(tagsToDelete.At(i)) >= 0)
					bIsUsedInDoc = kTrue;
			}
		}

		// If used, prompt user for replacement; otherwise just delete it.
		if (bIsUsedInDoc)
			err = this->DoConditionDeleteDialog(tagsToDelete);
		else
			err = Utils<Facade::IConditionalTextFacade>()->DeleteConditions(tagsToDelete);
	}
	else
		err = Utils<Facade::IConditionalTextFacade>()->DeleteConditions(tagsToDelete);

	return err;
} // end DeleteCondition()

// -----------------------------------------------------------------------------

ErrorCode ConditionalTextUIFacade::LoadConditions(IWorkspace* ws, bool16 loadConditionTagSets)
{	
	ErrorCode err(kSuccess);

	IDFile sourceFile;
	bool16 gotIt = Utils<IDialogUtils>()->GetSourceFileViaDialog(sourceFile);
	if (gotIt)
	{
		err = Utils<Facade::IConditionalTextFacade>()->LoadConditions(ws, sourceFile, loadConditionTagSets);
	}

	return err;
} // end LoadConditions()

// -----------------------------------------------------------------------------

void ConditionalTextUIFacade::SelectUnusedConditions(IWorkspace* ws)
{
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kConditionalTextUIPanelWidgetID));
	IControlView* treeView = panelData->FindWidget(kConditionTagListTreeViewWidgetID);
	InterfacePtr<ITreeViewController> tvController(treeView, UseDefaultIID());
	InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());
	ASSERT(tvController != nil && tvAdapter != nil);
	if (!tvController || !tvAdapter) return;

	// Gather list of used condition tags.
	IDataBase* db = ::GetDataBase(ws);
	InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
	UIDList usedList = doc ? UIDList(db) : UIDList();
	if (doc != nil)
	{
		// Iterate the story list to get the used conditions for the active doc.
		InterfacePtr<IStoryList> storyList(doc, UseDefaultIID());
		int32 storyCount = storyList->GetAllTextModelCount();
		for (int32 storyIndex = 0; storyIndex < storyCount; storyIndex++)
		{
			InterfacePtr<ITextReferences> refs(storyList->GetNthTextModelUID(storyIndex), UseDefaultIID());
			for (int32 i = 0; refs && i < refs->CountUsedConditions(); i++)
				usedList.Append(refs->GetUsedCondition(i));
		}
	}

	// Select or deselect the node depending on whether it is in the used conditions list or not.
	int32 numNodes = tvAdapter->GetNumChildren(tvAdapter->GetRootNode());
	for (int32 i = 0; i < numNodes; i++)
	{
		NodeID node = tvAdapter->GetNthChild(tvAdapter->GetRootNode(), i);
		bool16 isSelected = tvController->IsSelected(node);
		TreeNodePtr<UIDNodeID>	uidNode(node);
		if (std::find(usedList.begin(), usedList.end(), uidNode->GetUID()) != usedList.end())
		{
			if (isSelected)
				tvController->Deselect(node);
		}
		else if (!isSelected)
			tvController->Select(node);
	}

	// Deselect [Unconditional], it should not be considered an unused condition.
	if (tvController->IsSelected(tvAdapter->GetRootNode()))
		tvController->Deselect(tvAdapter->GetRootNode());

} // end SelectUnusedConditions()