//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/mso/SwitchToMSOStatePanelObserver.cpp $
//  
//  Owner: Greg St. Pierre
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

#include "IAppearanceList.h"
#include "IBehaviorData.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IFormFieldSuite.h"
#include "IHierarchy.h"
#include "IIntData.h"
#include "IListControlDataOf.h"
#include "IMultiStateObjectBehaviorData.h"
#include "INamedPageItemList.h"
#include "IPanelControlData.h"
#include "ISelectionUtils.h"
#include "IStringListControlData.h"
#include "ISpreadDynamicContentMgr.h"
#include "IDynamicTargetsFacade.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"
#include "ITriStateControlData.h"
#include "IUIDData.h"

// ----- Includes -----

#include "BehaviorUIDefs.h"
#include "CBehaviorPanelObserver.h"
#include "CoreResTypes.h"
#include "K2Pair.h"
#include "K2Vector.tpp"
#include "LocaleSetting.h"
#include "MSOBehaviorPanelTypes.h"
#include "RsrcSpec.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"
#include "Utils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "BehaviorUIID.h"


static const bool16 kInvalidate = kTrue;
static const bool16 kDontNotify = kFalse;

class SwitchToMSOStatePanelObserver : public CBehaviorPanelObserver
{
	typedef CBehaviorPanelObserver inherited;
	
	bool fIsAttached;
	
public:
	SwitchToMSOStatePanelObserver(IPMUnknown *boss) :
		inherited(boss),
		fIsAttached(false)
	{
	}

	virtual void AutoAttach();
	virtual void AutoDetach();

protected:
	virtual void HandleSelectionUpdate(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
	);
	
	virtual void InitializeFieldsFromActionData(const IBehaviorData* inActionData);
	virtual bool ApplyFieldsToActionData(IBehaviorData* inActionData);

private:
	static void LoadMSOChoices(IBehaviorData const *behaveData, IListControlDataOf<MSOTargetReference> *data);
	void LoadStateChoices(UIDRef const &mso);

	void InitializeMSOChoice(IBehaviorData const *inActionData);
	void InitializeStateChoice(IBehaviorData const *inActionData);
	void InitializeAutoReverse(IBehaviorData const *inActionData);
	
	void UpdateBehaviorNode();

	template<typename Ifc>
	inline InterfacePtr<Ifc> GetWidget(WidgetID const &id) const
	{
		// Pardon the mess
		return InterfacePtr<Ifc>(static_cast<Ifc *>(Utils<IWidgetUtils>()->QueryRelatedWidget(this, id, Ifc::kDefaultIID)));
	}
};

CREATE_PMINTERFACE(SwitchToMSOStatePanelObserver, kSwitchToMSOStatePanelObserverImpl)

void SwitchToMSOStatePanelObserver::AutoAttach()
{
	if (!fIsAttached)
	{
		inherited::AutoAttach();
		
		AttachToWidget(kMSOTargetChoiceWidgetID, IID_ISTRINGLISTCONTROLDATA);
		AttachToWidget(kMSOStateChoiceWidgetID, IID_IPANELCONTROLDATA);
		AttachToWidget(kMSOAutoReverseWidgetID, IID_ITRISTATECONTROLDATA);
		
		fIsAttached = true;
	}
}

void SwitchToMSOStatePanelObserver::AutoDetach()
{
	if (fIsAttached)
	{
		inherited::AutoDetach();
		
		DetachFromWidget(kMSOTargetChoiceWidgetID, IID_ISTRINGLISTCONTROLDATA);
		DetachFromWidget(kMSOStateChoiceWidgetID, IID_IPANELCONTROLDATA);
		DetachFromWidget(kMSOAutoReverseWidgetID, IID_ITRISTATECONTROLDATA);
		
		fIsAttached = false;
	}
}

void SwitchToMSOStatePanelObserver::HandleSelectionUpdate(
	const ClassID &bossClassID, 
	ISubject *subject, 
	const PMIID &protocol,
	void *message
)
{
	InterfacePtr<IFormFieldSuite> suite(FormFieldUIUtils::QueryFormSuite());
	
	if (suite && !suite->IsDefaultSelection() && suite->IsFieldSelectionOfType(kPushButtonItemBoss))
	{
		if (bossClassID.Get() == kPopupChangeStateMessage || protocol == IID_ITRISTATECONTROLDATA)
		{
			inherited::HandleSelectionUpdate(bossClassID, subject, protocol, message);
		}
		else
		{
			InitializeFieldsFromActionData(nil);
		}
	}
	else
	{
		ActiveSelectionObserver::HandleSelectionUpdate(bossClassID, subject, protocol, message);
	}
}

void SwitchToMSOStatePanelObserver::InitializeFieldsFromActionData(const IBehaviorData *inActionData)
{
	if (inActionData)
	{
		InitializeMSOChoice(inActionData);
		InitializeStateChoice(inActionData);
		InitializeAutoReverse(inActionData);
	}
	else
	{
		InterfacePtr<IUIDData const> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
		
		if (activeBehavior)
		{
			InterfacePtr<IBehaviorData const> behaviorData(activeBehavior->GetRef(), UseDefaultIID());
			
			if (behaviorData)
			{
				InitializeFieldsFromActionData(behaviorData);
			}
		}
	}
}

bool SwitchToMSOStatePanelObserver::ApplyFieldsToActionData(IBehaviorData *inActionData)
{
	IMultiStateObjectBehaviorData *actionData = static_cast<IMultiStateObjectBehaviorData *>(inActionData);
	
	InterfacePtr<IDropDownListController> msoChoice = GetWidget<IDropDownListController>(kMSOTargetChoiceWidgetID);
	InterfacePtr< IListControlDataOf<MSOTargetReference> > msoData(msoChoice, IID_ILISTCONTROLDATA);
	int32 selection = msoChoice->GetSelected();

	bool changed = false;
	UIDRef msoRef(UIDRef::gNull);

	if (selection != IDropDownListController::kNoSelection)
	{
		UID selectedItem = (*msoData)[selection].fReference.GetUID();
		msoRef = (*msoData)[selection].fReference;
		
		if (actionData->GetTarget() != selectedItem)
		{
			changed = true;
			actionData->SetTarget(selectedItem);
			actionData->SetState(Form::kStateInvalid);
			this->UpdateBehaviorNode();
		}
	}
	else if (actionData->GetTarget() != kInvalidUID)
	{
		changed = true;
		actionData->SetTarget(kInvalidUID);
		actionData->SetState(Form::kStateInvalid);
		this->UpdateBehaviorNode();
	}

	if (changed)
	{
		// MSO target changed, default to its first state.
		InterfacePtr<IAppearanceList const> appearanceList(msoRef, UseDefaultIID());
		if (appearanceList && appearanceList->NumStates() > 0)
			actionData->SetState(appearanceList->GetNthState(0));
	}
	else
	{
		// Did MSO state change?
		InterfacePtr<IDropDownListController> stateChoice = GetWidget<IDropDownListController>(kMSOStateChoiceWidgetID);
		InterfacePtr<IPanelControlData> data(stateChoice, UseDefaultIID());
		
		int32 stateSelection = stateChoice->GetSelected();
		Form::AppearanceState selectedState = Form::kStateInvalid;
		
		if (stateSelection >= 0)
		{
			InterfacePtr<IIntData> stateData(data->GetWidget(stateSelection), UseDefaultIID());
			selectedState = stateData->Get();
		}
		
		if (actionData->GetState() != selectedState)
		{
			changed = true;
			actionData->SetState(selectedState);
			this->UpdateBehaviorNode();
		}
	}
	
	InterfacePtr<ITriStateControlData const> checkbox = GetWidget<ITriStateControlData const>(kMSOAutoReverseWidgetID);
	bool isSelected = checkbox->IsSelected();
	
	if (actionData->GetSwitchToPriorStateOnRollOff() != isSelected)
	{
		changed = true;
		actionData->SetSwitchToPriorStateOnRollOff(isSelected);
	}
	
	return changed;
}

void SwitchToMSOStatePanelObserver::LoadMSOChoices(IBehaviorData const *behaveData, IListControlDataOf<MSOTargetReference> *data)
{	
	data->Clear();
	
	if (!behaveData) return;

	IDataBase *db = ::GetDataBase(behaveData);
	InterfacePtr<IHierarchy /*const*/> pageitem(db, behaveData->GetOwner(), UseDefaultIID());
	
	if (pageitem)
	{
		const bool kIncludeMasterItems = true;
		std::vector<UID> itemList;
		if (Utils<Facade::IDynamicTargetsFacade> ()->GetTargetList (UIDRef (db, behaveData->GetOwner()), ISpreadDynamicContentMgr::kMultiStateItemType, itemList, kIncludeMasterItems))
		{
			for (std::vector<UID>::const_iterator i = itemList.begin(), end = itemList.end(); i != end; ++i)
			{
				data->Add(MSOTargetReference(db, *i));
			}
		}

		if (data->Length() == 0)
			data->Add(MSOTargetReference(nil, kInvalidUID));
	}
}

void SwitchToMSOStatePanelObserver::InitializeMSOChoice(IBehaviorData const *inActionData)
{
	InterfacePtr<IDropDownListController> choice = GetWidget<IDropDownListController>(kMSOTargetChoiceWidgetID);
	InterfacePtr< IListControlDataOf<MSOTargetReference> > data(choice, IID_ILISTCONTROLDATA);
	
	LoadMSOChoices(inActionData, data);
	
	bool updated = false;
	
	if (!inActionData)
	{
		if (data->Length() > 0)
		{
			updated = true;
			choice->Select(0, kInvalidate, kDontNotify);
		}
	}
	else
	{
		InterfacePtr<IMultiStateObjectBehaviorData const> behaviorData(inActionData, UseDefaultIID());
		
		for (int32 i = 0; i < data->Length(); ++i)
		{
			if ((*data)[i].fReference.GetUID() == behaviorData->GetTarget())
			{
				updated = true;
				if (!choice->IsSelected(i)) choice->Select(i, kInvalidate, kDontNotify);
				
				break;
			}
		}
	}

	if (!updated)
	{
		choice->Deselect(kInvalidate, kDontNotify);
#ifdef DEBUG
		InterfacePtr<IMultiStateObjectBehaviorData const> behaviorData(inActionData, UseDefaultIID());
		if (behaviorData != nil && behaviorData->GetTarget() != kInvalidUID)
			ASSERT_FAIL(FORMAT_ARGS("Button has a multi-state object target (uid %d) that is not on the same spread!", behaviorData->GetTarget().Get()));
#endif
	}
}

void SwitchToMSOStatePanelObserver::LoadStateChoices(UIDRef const &mso)
{
	InterfacePtr<IDropDownListController> choice = GetWidget<IDropDownListController>(kMSOStateChoiceWidgetID);
	InterfacePtr<IPanelControlData> panelCtrlData(choice, UseDefaultIID());
	ASSERT(panelCtrlData != nil);

	// clear out the dropdown list
	panelCtrlData->ReleaseAll();

	InterfacePtr<IAppearanceList const> appearanceList(mso, UseDefaultIID());
	
	if (appearanceList)
	{
		for (int32 i = 0, count = appearanceList->NumStates(); i < count; ++i)
		{
			InterfacePtr<IControlView> view(::CreateObject2<IControlView>(kMSOStateDDLElementWidgetBoss));
			ASSERT_MSG(view != nil, "SwitchToMSOStatePanelObserver::LoadStateChoices - no view associated with this MSO state.");
			if (view == nil)
				return;

			Form::AppearanceState state = appearanceList->GetNthState(i);

			InterfacePtr<IUIDData> msoData(view, UseDefaultIID());
			msoData->Set(mso);
			InterfacePtr<IIntData> stateData(view, UseDefaultIID());
			stateData->Set(state);

			panelCtrlData->AddWidget(view, -1, kFalse);
		}
	}
}

void SwitchToMSOStatePanelObserver::InitializeStateChoice(IBehaviorData const *inActionData)
{
	InterfacePtr<IDropDownListController> choice = GetWidget<IDropDownListController>(kMSOStateChoiceWidgetID);
	InterfacePtr<IPanelControlData> data(choice, UseDefaultIID());

	InterfacePtr<IMultiStateObjectBehaviorData const> actionData(inActionData, UseDefaultIID());
	UIDRef mso;
	
	if (actionData)
	{
		mso = UIDRef(::GetDataBase(actionData), actionData->GetTarget());
	}
	
	LoadStateChoices(mso);
	
	bool updated = false;

	if (!inActionData)
	{
		if (data->Length() > 0)
		{
			updated = true;
			choice->Select(0, kInvalidate, kDontNotify);
		}
	}
	else
	{
		for (int32 i = 0; i < data->Length(); ++i)
		{
			InterfacePtr<IControlView> ddlElement(data->GetWidget(i), UseDefaultIID());
			InterfacePtr<IIntData> stateData(data->GetWidget(i), UseDefaultIID());
			if (stateData->Get() == actionData->GetState())
			{
				updated = true;
				if (!choice->IsSelected(i)) choice->Select(i, kInvalidate, kDontNotify);
				
				break;
			}
		}
	}

	if (!updated) 
	{
		choice->Deselect(kInvalidate, kDontNotify);
#ifdef DEBUG
		InterfacePtr<IMultiStateObjectBehaviorData const> behaviorData(inActionData, UseDefaultIID());
		if (behaviorData != nil && behaviorData->GetState() != Form::kStateInvalid)
			ASSERT_FAIL(FORMAT_ARGS("Button action \"go to state\" has a MSO state (%d) that doesn't exist!", behaviorData->GetState()));
#endif
	}
}

void SwitchToMSOStatePanelObserver::InitializeAutoReverse(IBehaviorData const *inActionData)
{
	InterfacePtr<ITriStateControlData> checkbox = GetWidget<ITriStateControlData>(kMSOAutoReverseWidgetID);
	InterfacePtr<IMultiStateObjectBehaviorData const> actionData(inActionData, UseDefaultIID());
	InterfacePtr<IControlView> view(checkbox, UseDefaultIID());

	if (checkbox && actionData && view)
	{
		// Enabled only when the event is set to On Roll Over

		ActionEvent selectedEvent = FormFieldUIUtils::GetSelectedEvent(this);
		if (selectedEvent == kMouseEnterEvt)
		{
			view->Enable();

			bool autoReverse = actionData->GetSwitchToPriorStateOnRollOff();

			if (autoReverse)
			{
				checkbox->Select(kInvalidate, kDontNotify);
			}
			else
			{
				checkbox->Deselect(kInvalidate, kDontNotify);
			}
		}
		else
			view->Disable();
	}
	else if (view)
		view->Disable();
}

void SwitchToMSOStatePanelObserver::UpdateBehaviorNode()
{
	InterfacePtr<ITreeViewController> behaviorsCntlr((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER));
	if (behaviorsCntlr)
	{
		K2Vector<NodeID> selection;
		behaviorsCntlr->GetSelectedItems(selection);
		if (selection.size() == 1)
		{
			InterfacePtr<ITreeViewMgr> treeViewMgr(behaviorsCntlr, UseDefaultIID());
			treeViewMgr->NodeChanged(selection[0]);
		}
	}
}