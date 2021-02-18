//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionSetDropDownObserver.cpp $
//  
//  Owner: Kevin Van Wiel	
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

#include "IActiveContext.h"
#include "IApplication.h"
#include "IBoolData.h"
#include "IConditionalTextFacade.h"
#include "IConditionTag.h"
#include "IConditionTagList.h"
#include "IControlView.h"
#include "IDialog.h"
#include "IDialogMgr.h"
#include "IDropDownListController.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"
#include "IWStringData.h"

// ----- Includes -----

#include "CObserver.h"
#include "ConditionalTextUIDefs.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "SysControlIds.h"
#include "UIDList.h"

// ----- Utility files -----

#include "IDialogUtils.h"
#include "IInCopySharedUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


using namespace Facade;

#define NOTHINGACTIVEINDEX 0

class ConditionSetDropDownObserver : public CObserver
{
public:
	ConditionSetDropDownObserver(IPMUnknown *boss);
	virtual ~ConditionSetDropDownObserver();
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

private:
	void ApplyConditionSet(const PMString &tagSetName);
	void AddConditionSet();
	void RenameConditionSet();
	void DeleteConditionSet();
	void CheckWorkspace(const UIDRef &activeWorkspaceRef);
	void Repopulate();
	void SelectActiveItem();
	bool16 GetActiveSetName(WideString &activeSetName, bool16 includeOversetSymbol);
	bool16 DoSetNameDialog(WideString &setName, const UIDRef& setUIDRef = UIDRef::gNull);
	void RedefineConditionSet();
	bool16 CheckForOverride();
	void UpdateOverrideState(int32 selectedItem);
	void UpdateConditionSet(UID setUID);
	void UpdateAllConditionSets();
	bool16 CheckForAddedConditionOverride(UID setUID);
	bool16 CheckForAddedConditionOverrides();
	
	int32 fActiveIndex;
	UIDRef fCachedWorkspaceRef;
};

CREATE_PMINTERFACE(ConditionSetDropDownObserver, kConditionSetDropDownObserverImpl)

/******************************************************************************
 * ConditionSetDropDownObserver::ConditionSetDropDownObserver
 ******************************************************************************/
ConditionSetDropDownObserver::ConditionSetDropDownObserver(IPMUnknown *boss) :
	CObserver(boss), fActiveIndex(NOTHINGACTIVEINDEX)
{
}

/******************************************************************************
 * ConditionSetDropDownObserver::~ConditionSetDropDownObserver
 ******************************************************************************/
ConditionSetDropDownObserver::~ConditionSetDropDownObserver()
{
}

/******************************************************************************
 * ConditionSetDropDownObserver::AutoAttach
 ******************************************************************************/
void ConditionSetDropDownObserver::AutoAttach()
{
	CObserver::AutoAttach();
	
	fCachedWorkspaceRef = UIDRef::gNull;

	// Attach to string list to get changes to drop down
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject != nil)
		subject->AttachObserver(this, IID_ISTRINGLISTCONTROLDATA);
		
	// Attach to the active context for updates to active document
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());
		if (contextSubject && !contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
			contextSubject->AttachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
			
		IWorkspace* newWS = context->GetContextWorkspace();
		UIDRef newWorkspaceRef = ::GetUIDRef(newWS);
		
		CheckWorkspace(newWorkspaceRef);
	}
	
}
													    
/******************************************************************************
 * ConditionSetDropDownObserver::AutoDetach
 ******************************************************************************/
void ConditionSetDropDownObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject != nil)
		subject->DetachObserver(this, IID_ISTRINGLISTCONTROLDATA);
		
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());
		if (contextSubject && contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
			contextSubject->DetachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
	}
	
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	if (workspace)
	{
		InterfacePtr<ISubject> workspaceSubject(workspace, UseDefaultIID());
		if (workspaceSubject && workspaceSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSETLIST, IID_IOBSERVER))
			workspaceSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSETLIST, IID_IOBSERVER);
			
		if (workspaceSubject && workspaceSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER))
			workspaceSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER);	
			
		if (workspaceSubject && workspaceSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER))
			workspaceSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER);	
	}

	CObserver::AutoDetach();

}

/******************************************************************************
 * ConditionSetDropDownObserver::CheckWorkspace
 ******************************************************************************/
void ConditionSetDropDownObserver::CheckWorkspace(const UIDRef &activeWorkspaceRef)
{
	if (activeWorkspaceRef != fCachedWorkspaceRef) 
	{
		// first detach from old workspace.
		if (fCachedWorkspaceRef != UIDRef::gNull)
		{
			InterfacePtr<IWorkspace> priorWorkspace(fCachedWorkspaceRef, UseDefaultIID());
			if (priorWorkspace)
			{
				InterfacePtr<ISubject> priorSubject(priorWorkspace, UseDefaultIID());
				if (priorSubject && priorSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSETLIST, IID_IOBSERVER))
					priorSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSETLIST, IID_IOBSERVER);
					
				if (priorSubject && priorSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER))
					priorSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER);
					
				if (priorSubject && priorSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER))
					priorSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER);
			}
		}
		
		// attach to new workspace
		InterfacePtr<IWorkspace> newWorkspace(activeWorkspaceRef, UseDefaultIID());
		if (newWorkspace)
		{
			InterfacePtr<ISubject> newSubject(newWorkspace, UseDefaultIID());
			if (newSubject && !newSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSETLIST, IID_IOBSERVER))
				newSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSETLIST, IID_IOBSERVER);
				
			if (newSubject && !newSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER))
				newSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER);
				
			if (newSubject && !newSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER))
				newSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER);
		}

		fCachedWorkspaceRef = activeWorkspaceRef;
		Repopulate();
		SelectActiveItem();
	}
}

/******************************************************************************
 * ConditionSetDropDownObserver::LazyUpdate
 ******************************************************************************/
void ConditionSetDropDownObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	switch (protocol.Get())
	{
		case IID_ICONDITIONTAGSETLIST:
		case IID_ICONDITIONTAGSET:
		{
			Repopulate();
			SelectActiveItem();
		}
			break;
			
		case IID_ICONDITIONTAGLIST:
		{
			InterfacePtr<IDropDownListController> listController(this, UseDefaultIID());
			int32 currentSetIndex = listController->GetSelected();
			UpdateOverrideState(currentSetIndex);
			if (listController->GetSelected() != currentSetIndex)
				listController->Select(currentSetIndex, kTrue, kFalse);
		}
			break;
	}
}

/******************************************************************************
 * ConditionSetDropDownObserver::Update
 ******************************************************************************/
void ConditionSetDropDownObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{	
	switch (protocol.Get())
	{
		case IID_IACTIVECONTEXT:
		{
			InterfacePtr<IActiveContext> newContext(theSubject, UseDefaultIID());
			IWorkspace* newWS = newContext->GetContextWorkspace();
			UIDRef newWorkspaceRef = ::GetUIDRef(newWS);
			CheckWorkspace(newWorkspaceRef);
		}
			break;
		
		case IID_ISTRINGLISTCONTROLDATA:
		{
			switch (theChange.Get())
			{
				case kPopupChangeStateMessage:
				{
					InterfacePtr<IDropDownListController> listController(theSubject, UseDefaultIID());
					int32 newSelection = listController->GetSelected();
					if (newSelection > -1)
					{
						InterfacePtr<IStringListControlData> stringList(this, UseDefaultIID());
						PMString dropDownString = stringList->GetString(newSelection);
						
						PMString createTagSetString("#ConditionSetNewSet");
						createTagSetString.Translate();

						WideString activeSetName("");
						GetActiveSetName(activeSetName, kFalse);
						PMString activeSetPMStrName(activeSetName);
						activeSetPMStrName.SetTranslatable(kFalse);

						PMString deleteTagSetString("#ConditionSetDeleteSet");
						deleteTagSetString.Translate();
						ReplaceStringParameters(&deleteTagSetString, activeSetPMStrName);
						
						PMString renameTagSetString("#ConditionSetRenameSet");
						renameTagSetString.Translate();
						ReplaceStringParameters(&renameTagSetString, activeSetPMStrName);
						
						PMString redefineTagSetString("#ConditionSetRedefineSet");
						redefineTagSetString.Translate();
						ReplaceStringParameters(&redefineTagSetString, activeSetPMStrName);

						PMString updateAllTagSetsString("#ConditionSetUpdateAllSets");
						updateAllTagSetsString.Translate();

						if (dropDownString == createTagSetString) AddConditionSet();
						else if (dropDownString == deleteTagSetString) DeleteConditionSet();
						else if (dropDownString == renameTagSetString) RenameConditionSet();
						else if (dropDownString == redefineTagSetString) RedefineConditionSet();
						else if (dropDownString == updateAllTagSetsString) UpdateAllConditionSets();
						else ApplyConditionSet(dropDownString);
						
					}
				}
					break;
			}
		}
			break;
	}
}

/******************************************************************************
 * ConditionSetDropDownObserver::AddConditionSet
 ******************************************************************************/
void ConditionSetDropDownObserver::AddConditionSet()
{
	WideString tagSetString;
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	Utils<IConditionalTextFacade>()->GetFirstAvailableDefaultConditionSetName(workspace, tagSetString);
	
	if (DoSetNameDialog(tagSetString))
	{
		IDataBase *db = fCachedWorkspaceRef.GetDataBase();
		InterfacePtr<IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
		
		IConditionalTextFacade::ConditionSetElementList tags;
		for (int32 i = 0; i < tagList->GetCount(); i++)
		{
			InterfacePtr<IConditionTag> tag(db, tagList->GetNthCondition(i), UseDefaultIID());
			IConditionalTextFacade::ConditionSetElement newTag(::GetUID(tag), tag->IsVisible());
			tags.push_back(newTag);
		}
	
		UID tagSetUID = kInvalidUID;
		if (Utils<Facade::IConditionalTextFacade>()->CreateConditionSet(workspace, tagSetString, tags, &tagSetUID) == kSuccess) 
		{
			Utils<Facade::IConditionalTextFacade>()->SetActiveConditionSet(workspace, tagSetUID);
			Repopulate();
			SelectActiveItem();
		}
	}
	else SelectActiveItem();
}

/******************************************************************************
 * ConditionSetDropDownObserver::DeleteConditionSet
 ******************************************************************************/
void ConditionSetDropDownObserver::DeleteConditionSet()
{
	IDataBase *db = fCachedWorkspaceRef.GetDataBase();

	UID activeTagSetUID = kInvalidUID;
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(workspace, activeTagSetUID);
	if (activeTagSetUID != kInvalidUID && Utils<Facade::IConditionalTextFacade>()->DeleteConditionSet(UIDRef(db, activeTagSetUID)) == kSuccess) 
	{
		fActiveIndex = NOTHINGACTIVEINDEX;
		Repopulate();
		SelectActiveItem();
	}
}

/******************************************************************************
 * ConditionSetDropDownObserver::RenameConditionSet
 ******************************************************************************/
void ConditionSetDropDownObserver::RenameConditionSet()
{
	IDataBase *db = fCachedWorkspaceRef.GetDataBase();

	UID activeTagSetUID = kInvalidUID;
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(workspace, activeTagSetUID);
	WideString name;
	UIDRef activeSetRef = UIDRef(db, activeTagSetUID);
	if (activeTagSetUID != kInvalidUID && (Utils<Facade::IConditionalTextFacade>()->GetConditionSetName(activeSetRef, name) == kSuccess) && DoSetNameDialog(name, activeSetRef))
	{
		Utils<Facade::IConditionalTextFacade>()->SetConditionSetName(activeSetRef, name);
		Repopulate();
	}
	
	SelectActiveItem();
}

/******************************************************************************
 * ConditionSetDropDownObserver::RedefineConditionSet
 ******************************************************************************/
void ConditionSetDropDownObserver::RedefineConditionSet()
{
	IDataBase *db = fCachedWorkspaceRef.GetDataBase();

	UID activeTagSetUID = kInvalidUID;
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(workspace, activeTagSetUID);
	if (activeTagSetUID != kInvalidUID)
	{
		InterfacePtr<IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
		
		IConditionalTextFacade::ConditionSetElementList tags;
		for (int32 i = 0; i < tagList->GetCount(); i++)
		{
			InterfacePtr<IConditionTag> tag(db, tagList->GetNthCondition(i), UseDefaultIID());
			IConditionalTextFacade::ConditionSetElement newTag(::GetUID(tag), tag->IsVisible());
			tags.push_back(newTag);
		}

		Utils<Facade::IConditionalTextFacade>()->RedefineConditionSet(UIDRef(db, activeTagSetUID), tags);
	}
}

/******************************************************************************
 * ConditionSetDropDownObserver::UpdateConditionSet
 ******************************************************************************/
void ConditionSetDropDownObserver::UpdateConditionSet(UID setUID)
{
	IDataBase *db = fCachedWorkspaceRef.GetDataBase();

	ASSERT(setUID != kInvalidUID);
	if (setUID != kInvalidUID)
	{
		IConditionalTextFacade::ConditionSetElementList tagsInSet;
		Utils<IConditionalTextFacade>()->GetConditionsInConditionSet(UIDRef(db, setUID), tagsInSet);

		InterfacePtr<IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));

		IConditionalTextFacade::ConditionSetElementList tags;
		for (int32 i = 0; i < tagList->GetCount(); i++)
		{
			InterfacePtr<IConditionTag> tag(db, tagList->GetNthCondition(i), UseDefaultIID());

			bool16 conditionIsInSet = kFalse;
			for (IConditionalTextFacade::ConditionSetElementList::iterator tagInSetIter = tagsInSet.begin(); tagInSetIter != tagsInSet.end(); tagInSetIter++)	
			{
				if ((*tagInSetIter).first == ::GetUID(tag)) 
				{
					// Keep this tag's visibility
					IConditionalTextFacade::ConditionSetElement existingTag((*tagInSetIter).first, (*tagInSetIter).second);
					tags.push_back(existingTag);

					conditionIsInSet = kTrue;
					break;
				}
			}
			if (conditionIsInSet) continue;

			IConditionalTextFacade::ConditionSetElement newTag(::GetUID(tag), tag->IsVisible());
			tags.push_back(newTag);
		}

		Utils<Facade::IConditionalTextFacade>()->RedefineConditionSet(UIDRef(db, setUID), tags);
	}
}

/******************************************************************************
 * ConditionSetDropDownObserver::UpdateAllConditionSets
 ******************************************************************************/
void ConditionSetDropDownObserver::UpdateAllConditionSets()
{
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());

	PMString seqName("#ConditionSetUpdateAllSetsUndoName");
	CmdUtils::SequenceContext seq(&seqName);

	UIDList conditionSets;
	Utils<IConditionalTextFacade>()->GetAllConditionSets(workspace, &conditionSets);
	for (UIDList::iterator iter = conditionSets.begin(); iter != conditionSets.end(); iter++)
	{
		if (CheckForAddedConditionOverride(*iter))
			UpdateConditionSet(*iter);
	}

	SelectActiveItem();
}


/******************************************************************************
 * ConditionSetDropDownObserver::GetActiveSetName
 ******************************************************************************/
bool16 ConditionSetDropDownObserver::GetActiveSetName(WideString &activeSetName, bool16 includeOversetSymbol)
{
	bool16 haveAnActiveSet = kFalse;
	
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	UID activeTagSetUID = kInvalidUID;
	Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(workspace, activeTagSetUID);
	if (activeTagSetUID != kInvalidUID && 
		Utils<Facade::IConditionalTextFacade>()->GetConditionSetName(UIDRef(::GetDataBase(workspace), activeTagSetUID), activeSetName) == kSuccess)
	{
		haveAnActiveSet = kTrue;
		
		if (includeOversetSymbol && CheckForOverride())
		{
			activeSetName.Append(kTextChar_PlusSign);
		}
	}
	else
	{
		PMString noActiveSet("#ConditionSetNone");
		noActiveSet.Translate();
		activeSetName = WideString(noActiveSet);
	}
	
	return haveAnActiveSet;
}

/******************************************************************************
 * ConditionSetDropDownObserver::ApplyConditionSet
 ******************************************************************************/
void ConditionSetDropDownObserver::ApplyConditionSet(const PMString &tagSetName)
{
	IDataBase *db = fCachedWorkspaceRef.GetDataBase();

	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	UID tagSetUID = kInvalidUID;
	if (Utils<Facade::IConditionalTextFacade>()->FindConditionSet(workspace, WideString(tagSetName), tagSetUID) == kSuccess)
	{
		Utils<Facade::IConditionalTextFacade>()->SetActiveConditionSet(workspace, tagSetUID);
	}
	else
	{
		PMString noActiveSet("#ConditionSetNone");
		noActiveSet.Translate();

		// possible it didn't match because of the override symbol do a compare with the active set to check that possibility
		WideString activeWSSetName;
		GetActiveSetName(activeWSSetName, kTrue);
		PMString activePMSetName(activeWSSetName);
		activePMSetName.SetTranslatable(kFalse);
		if (tagSetName == activePMSetName)
		{
			// reapply active set
			Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(workspace, tagSetUID);
			Utils<Facade::IConditionalTextFacade>()->SetActiveConditionSet(workspace, tagSetUID);
		}
		else if (noActiveSet == tagSetName)
		{
			// apply none
			Utils<Facade::IConditionalTextFacade>()->SetActiveConditionSet(workspace, kInvalidUID);
		}
	}
}

/******************************************************************************
 * ConditionSetDropDownObserver::Repopulate
 ******************************************************************************/
void ConditionSetDropDownObserver::Repopulate()
{
	bool16 bCanEdit = Utils<IInCopySharedUtils>()->StylesEditable(fCachedWorkspaceRef.GetDataBase());

	InterfacePtr<IStringListControlData> stringList(this, UseDefaultIID());
	stringList->Clear(kTrue, kFalse);
	
	PMString addString("#ConditionSetNone");
	addString.Translate();
	stringList->AddString(addString);
	
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	UIDList tagSets;
	if (Utils<IConditionalTextFacade>()->GetAllConditionSets(workspace, &tagSets) == kSuccess)
	{
		for (UIDList::iterator setIter = tagSets.begin(); setIter != tagSets.end(); setIter++)
		{
			WideString setWName;
			if (Utils<IConditionalTextFacade>()->GetConditionSetName(UIDRef(tagSets.GetDataBase(), *setIter), setWName) == kSuccess)
			{
				addString = PMString(setWName);
				addString.SetTranslatable(kFalse);
				stringList->AddString(addString);
			}
		}
	}
	
	if (bCanEdit)
	{
		addString = PMString("-"); // divider
		addString.Translate();
		stringList->AddString(addString);

		addString = PMString("#ConditionSetNewSet");
		addString.Translate();
		stringList->AddString(addString);

		WideString activeSetName("");
		bool16 activeSet = GetActiveSetName(activeSetName, kFalse);
		PMString activeSetPMStrName(activeSetName);
		activeSetPMStrName.SetTranslatable(kFalse);

		addString = PMString("#ConditionSetDeleteSet");
		addString.Translate();
		ReplaceStringParameters(&addString, activeSetPMStrName);
		stringList->AddString(addString);
		if (!activeSet) stringList->Disable(stringList->Length()-1);
		else stringList->Enable(stringList->Length()-1);

		addString = PMString("#ConditionSetRenameSet");
		addString.Translate();
		ReplaceStringParameters(&addString, activeSetPMStrName);
		stringList->AddString(addString);	
		if (!activeSet) stringList->Disable(stringList->Length()-1);
		else stringList->Enable(stringList->Length()-1);

		addString = PMString("#ConditionSetRedefineSet");
		addString.Translate();
		ReplaceStringParameters(&addString, activeSetPMStrName);
		stringList->AddString(addString);
		if (!activeSet || !CheckForOverride()) stringList->Disable(stringList->Length()-1);
		else stringList->Enable(stringList->Length()-1);

		addString = PMString("#ConditionSetUpdateAllSets");
		addString.Translate();
		stringList->AddString(addString);
		if (CheckForAddedConditionOverrides()) stringList->Enable(stringList->Length()-1);
		else stringList->Disable(stringList->Length()-1);
	}
}

/******************************************************************************
 * ConditionSetDropDownObserver::SelectActiveItem
 ******************************************************************************/
void ConditionSetDropDownObserver::SelectActiveItem()
{
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	
	UID activeTagSetUID = kInvalidUID;
	if (Utils<IConditionalTextFacade>()->GetActiveConditionSet(workspace, activeTagSetUID) == kSuccess)
	{
		InterfacePtr<IDropDownListController> dropDownCntr(this, UseDefaultIID());

		if (activeTagSetUID != kInvalidUID)
		{
			WideString name;
	
			if (Utils<IConditionalTextFacade>()->GetConditionSetName(UIDRef(::GetDataBase(workspace), activeTagSetUID), name) == kSuccess)
			{
				InterfacePtr<IStringListControlData> stringList(this, UseDefaultIID());
				PMString pmStrName(name);
				pmStrName.SetTranslatable(kFalse);
				PMString pmStrNameOverride(pmStrName);
				pmStrNameOverride.Append(kTextChar_PlusSign);

				int32 dropDownIndex = -1;
				if ((dropDownIndex = stringList->GetIndex(pmStrName)) != -1 ||
					(dropDownIndex = stringList->GetIndex(pmStrNameOverride)) != -1)
				{
					UpdateOverrideState(dropDownIndex);
					dropDownCntr->Select(dropDownIndex, kTrue, kFalse);
				}
				else
				{
					dropDownCntr->Select(fActiveIndex, kTrue, kFalse);
				}
			}
		}
		else
		{
			dropDownCntr->Select(fActiveIndex, kTrue, kFalse);
		}
	}
}

/******************************************************************************
 * ConditionSetDropDownObserver::DoSetNameDialog
 ******************************************************************************/
bool16 ConditionSetDropDownObserver::DoSetNameDialog(WideString &setName, const UIDRef& setUIDRef)
{
	bool16 success = kTrue;
	
	const RsrcID kDialogRsrcID = kConditionSetNameDialogRsrcID;
	const IDialog::DialogType kDialogType = IDialog::kMovableModal;
	const PMLocaleId nLocale = LocaleSetting::GetLocale();
	const RsrcSpec aSpec(nLocale, kConditionalTextUIPluginID, kViewRsrcType,  kDialogRsrcID, kTrue);

	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(app, UseDefaultIID());
	
	IDialog *dialog = dialogMgr->CreateNewDialog(aSpec, kDialogType);
	ASSERT_MSG(dialog != nil, "ConditionSetDropDownObserver::DoSetNameDialog - can't create dialog!");

	IControlView* dialogView = dialog->GetDialogPanel();
	
	InterfacePtr<IWStringData> nameData(dialogView, UseDefaultIID());
	nameData->Set(setName);

	// Set the UID data for the dialog.
	InterfacePtr<IUIDData> setData(dialogView, UseDefaultIID());
	if (setData) setData->Set(setUIDRef);
	
	dialog->Open();
	dialog->WaitForDialog();
	
	// the dialog controller should set the bool data and string data for us.
	InterfacePtr<IBoolData> boolData(dialogView, UseDefaultIID());
	success = boolData->GetBool();
	
	if (success) setName = nameData->GetString();
	
	return success;
}

/******************************************************************************
 * ConditionSetDropDownObserver::CheckForOverride
 ******************************************************************************/
bool16 ConditionSetDropDownObserver::CheckForOverride()
{
	bool16 hasOverride = kFalse;
	
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());
	IDataBase *db = fCachedWorkspaceRef.GetDataBase();

	UID activeTagSetUID = kInvalidUID;
	if (Utils<Facade::IConditionalTextFacade>()->GetActiveConditionSet(workspace, activeTagSetUID) == kSuccess && activeTagSetUID != kInvalidUID)
	{
		IConditionalTextFacade::ConditionSetElementList tagsInSet;
		Utils<IConditionalTextFacade>()->GetConditionsInConditionSet(UIDRef(db, activeTagSetUID), tagsInSet);

		InterfacePtr<IConditionTagList> tagList(fCachedWorkspaceRef, UseDefaultIID());
		if (tagList && tagList->GetCount() > tagsInSet.size())
		{
			// There are new conditions since set was created, treat it as "override".
			hasOverride = kTrue;
		}
		else
		{
			for (IConditionalTextFacade::ConditionSetElementList::iterator iter = tagsInSet.begin(); iter != tagsInSet.end(); iter++)
			{
				bool16 currentVisibility;
				Utils<IConditionalTextFacade>()->GetConditionVisibleState(UIDRef(db, (*iter).first), currentVisibility);

				if (currentVisibility != (bool16)(*iter).second)
				{
					hasOverride = kTrue;
					break;
				}
			}
		}
	}

	return hasOverride;
}

/******************************************************************************
 * ConditionSetDropDownObserver::CheckForAddedConditionOverride
 ******************************************************************************/
bool16 ConditionSetDropDownObserver::CheckForAddedConditionOverride(UID setUID)
{
	bool16 hasOverride = kFalse;
	IDataBase *db = fCachedWorkspaceRef.GetDataBase();

	ASSERT(setUID != kInvalidUID);
	if (setUID != kInvalidUID)
	{
		IConditionalTextFacade::ConditionSetElementList tagsInSet;
		Utils<IConditionalTextFacade>()->GetConditionsInConditionSet(UIDRef(db, setUID), tagsInSet);

		InterfacePtr<IConditionTagList> tagList(fCachedWorkspaceRef, UseDefaultIID());
		if (tagList && tagList->GetCount() > tagsInSet.size())
		{
			// There are new conditions since set was created, treat it as "override".
			hasOverride = kTrue;
		}
	}

	return hasOverride;
}

/******************************************************************************
 * ConditionSetDropDownObserver::CheckForAddedConditionOverrides
 ******************************************************************************/
bool16 ConditionSetDropDownObserver::CheckForAddedConditionOverrides()
{
	InterfacePtr<IWorkspace> workspace(fCachedWorkspaceRef, UseDefaultIID());

	UIDList conditionSets;
	Utils<IConditionalTextFacade>()->GetAllConditionSets(workspace, &conditionSets);
	for (UIDList::iterator iter = conditionSets.begin(); iter != conditionSets.end(); iter++)
	{
		if (CheckForAddedConditionOverride(*iter))
			return kTrue;
	}

	return kFalse;
}

/******************************************************************************
 * ConditionSetDropDownObserver::UpdateOverrideState
 ******************************************************************************/
void ConditionSetDropDownObserver::UpdateOverrideState(int32 selectedItem)
{
	if (selectedItem > NOTHINGACTIVEINDEX)
	{
		WideString setName;
		if (GetActiveSetName(setName, kTrue))
		{
			PMString pmSetName(setName);
			pmSetName.SetTranslatable(kFalse);
			InterfacePtr<IStringListControlData> stringList(this, UseDefaultIID());
			if (pmSetName != stringList->GetString(selectedItem))
			{
				stringList->SetString(selectedItem, pmSetName);

				// Update Redefine "<setname>" enablement
				if (CheckForOverride()) stringList->Enable(stringList->Length()-2, kTrue, kFalse, kFalse); // params are itemindex, enable, inval, notify using notify with true causes asserts on mac
				else stringList->Disable(stringList->Length()-2, kFalse, kFalse); // params are itemindex, inval, notify
			}
		}
	}

	// Update Redefine All enablement
	InterfacePtr<IStringListControlData> stringList(this, UseDefaultIID());
	if (stringList->GetString(stringList->Length()-1) == PMString("#ConditionSetUpdateAllSets", PMString::kTranslateDuringCall))
	{
		if (CheckForAddedConditionOverrides()) stringList->Enable(stringList->Length()-1, kTrue, kFalse, kFalse); // params are itemindex, enable, inval, notify using notify with true causes asserts on mac
		else stringList->Disable(stringList->Length()-1, kFalse, kFalse); // params are itemindex, inval, notify
	}
}
