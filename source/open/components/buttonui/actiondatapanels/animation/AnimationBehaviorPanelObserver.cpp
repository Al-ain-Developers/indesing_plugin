//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/animation/AnimationBehaviorPanelObserver.cpp $
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

#include "CBehaviorPanelObserver.h"
#include "AnimationBehaviorPanelTypes.h"

#include "IBehaviorData.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "ITriStateControlData.h"
#include "IFormFieldSuite.h"
#include "IListControlDataOf.h"
#include "IAnimationBehaviorData.h"
#include "INamedPageItemList.h"
#include "ISelectionUtils.h"
#include "IStringListControlData.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"
#include "IHierarchy.h"
#include "ISpreadDynamicContentMgr.h"
#include "IDynamicTargetsFacade.h"
#include "IControlView.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"

#include "K2Pair.h"
#include "K2Vector.tpp"

#include "BehaviorUIID.h"
#include "BehaviorUIDefs.h"

#include "FormFieldUIUtils.h"
#include "Utils.h"

static const bool16 kInvalidate = kTrue;
static const bool16 kDontNotify = kFalse;

class AnimationBehaviorPanelObserver : public CBehaviorPanelObserver
{
	typedef CBehaviorPanelObserver inherited;
	
	bool fIsAttached;
	
public:
	AnimationBehaviorPanelObserver(IPMUnknown *boss) :
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
	static void LoadAnimationChoices(IBehaviorData const *behaveData, IListControlDataOf<AnimationTargetReference> *data);
	static void LoadAnimationOpChoices(IListControlDataOf< K2Pair<PMString, int32> >* opData);

	void InitializeAnimationChoice(IBehaviorData const *inActionData);
	void InitializeAnimationOpChoice(IBehaviorData const *inActionData);
	void InitializeAnimationAutoReverse(IBehaviorData const *inActionData);
	
	void UpdateBehaviorNode();

	template<typename Ifc>
	inline InterfacePtr<Ifc> GetWidget(WidgetID const &id) const
	{
		// Pardon the mess
		return InterfacePtr<Ifc>(static_cast<Ifc *>(Utils<IWidgetUtils>()->QueryRelatedWidget(this, id, Ifc::kDefaultIID)));
	}
};

CREATE_PMINTERFACE(AnimationBehaviorPanelObserver, kAnimationBehaviorPanelObserverImpl)

void AnimationBehaviorPanelObserver::AutoAttach()
{
	if (!fIsAttached)
	{
		inherited::AutoAttach();
		
		AttachToWidget(kAnimationWidgetID, IID_ISTRINGLISTCONTROLDATA);
		AttachToWidget(kAnimationOperationWidgetID, IID_ISTRINGLISTCONTROLDATA);
		AttachToWidget(kAnimationAutoReverseWidgetID, IID_ITRISTATECONTROLDATA);
		
		fIsAttached = true;
	}
}

void AnimationBehaviorPanelObserver::AutoDetach()
{
	if (fIsAttached)
	{
		inherited::AutoDetach();
		
		DetachFromWidget(kAnimationWidgetID, IID_ISTRINGLISTCONTROLDATA);
		DetachFromWidget(kAnimationOperationWidgetID, IID_ISTRINGLISTCONTROLDATA);
		DetachFromWidget(kAnimationAutoReverseWidgetID, IID_ITRISTATECONTROLDATA);
		
		fIsAttached = false;
	}
}

void AnimationBehaviorPanelObserver::HandleSelectionUpdate(
	const ClassID &bossClassID, 
	ISubject *subject, 
	const PMIID &protocol,
	void *message
)
{
	InterfacePtr<IFormFieldSuite> suite(FormFieldUIUtils::QueryFormSuite());
	
	if (suite && !suite->IsDefaultSelection() && suite->IsFieldSelectionOfType(kPushButtonItemBoss))
	{
		if (protocol == IID_ISTRINGLISTCONTROLDATA || protocol == IID_ITRISTATECONTROLDATA)
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

void AnimationBehaviorPanelObserver::InitializeFieldsFromActionData(const IBehaviorData *inActionData)
{
	if (inActionData)
	{
		InitializeAnimationChoice(inActionData);
		InitializeAnimationOpChoice(inActionData);
		InitializeAnimationAutoReverse(inActionData);
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

bool AnimationBehaviorPanelObserver::ApplyFieldsToActionData(IBehaviorData *inActionData)
{
	IAnimationBehaviorData *actionData = static_cast<IAnimationBehaviorData *>(inActionData);
	
	InterfacePtr<IDropDownListController> choice = GetWidget<IDropDownListController>(kAnimationWidgetID);
	InterfacePtr< IListControlDataOf<AnimationTargetReference> > data(choice, IID_ILISTCONTROLDATA);
	int32 selection = choice->GetSelected();

	bool changed = false;

	if (selection != IDropDownListController::kNoSelection)
	{
		UID selectedItem = (*data)[selection].GetUID();
		
		if (actionData->GetTarget() != selectedItem)
		{
			changed = true;
			actionData->SetTarget(selectedItem);
			this->UpdateBehaviorNode();
		}
	}
	else if (actionData->GetTarget() != kInvalidUID)
	{
		changed = true;
		actionData->SetTarget(kInvalidUID);
		this->UpdateBehaviorNode();
	}

	InterfacePtr<IDropDownListController> operationChoice = GetWidget<IDropDownListController>(kAnimationOperationWidgetID);
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > operationData(operationChoice, IID_ILISTCONTROLDATA);
	IAnimationBehaviorData::Operation selectedOperation = static_cast<IAnimationBehaviorData::Operation>((*operationData)[operationChoice->GetSelected()].second);
	
	if (changed || actionData->GetOperation() != selectedOperation)
	{
		changed = true;
		actionData->SetOperation(selectedOperation);
	}
	
	InterfacePtr<ITriStateControlData const> checkbox = GetWidget<ITriStateControlData const>(kAnimationAutoReverseWidgetID);
	bool isSelected = checkbox->IsSelected();
	
	if (actionData->GetAutoReverseOnRollOff() != isSelected)
	{
		changed = true;
		actionData->SetAutoReverseOnRollOff(isSelected);
	}
	
	return changed;
}

void AnimationBehaviorPanelObserver::LoadAnimationChoices(IBehaviorData const *behaveData, IListControlDataOf<AnimationTargetReference> *data)
{	
	data->Clear();

	if (!behaveData) return;
	
	IDataBase *db = ::GetDataBase(behaveData);
	InterfacePtr<IHierarchy /*const*/> pageitem(db, behaveData->GetOwner(), UseDefaultIID());
	
	if (pageitem)
	{
		const bool kIncludeMasterItems = true;
		std::vector<UID> itemList;
		if (Utils<Facade::IDynamicTargetsFacade> ()->GetTargetList (UIDRef (db, behaveData->GetOwner()), ISpreadDynamicContentMgr::kAnimationItemType, itemList, kIncludeMasterItems))
		{
			for (std::vector<UID>::const_iterator i = itemList.begin(), end = itemList.end(); i != end; ++i)
			{
				data->Add(AnimationTargetReference(db, *i));
			}
		}

		if (data->Length() == 0)
			data->Add(AnimationTargetReference(UIDRef::gNull));
	}
}

void AnimationBehaviorPanelObserver::InitializeAnimationChoice(IBehaviorData const *inActionData)
{
	InterfacePtr<IDropDownListController> choice = GetWidget<IDropDownListController>(kAnimationWidgetID);
	InterfacePtr< IListControlDataOf<AnimationTargetReference> > data(choice, IID_ILISTCONTROLDATA);
	
	LoadAnimationChoices(inActionData, data);
	
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
		InterfacePtr<IAnimationBehaviorData const> behaviorData(inActionData, UseDefaultIID());
		
		for (int32 i = 0; i < data->Length(); ++i)
		{
			if ((*data)[i].GetUID() == behaviorData->GetTarget())
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
		InterfacePtr<IAnimationBehaviorData const> behaviorData(inActionData, UseDefaultIID());
		if (behaviorData != nil && behaviorData->GetTarget() != kInvalidUID)
			ASSERT_FAIL(FORMAT_ARGS("Button has an animation target (uid %d) that is not on the same spread!", behaviorData->GetTarget().Get()));
#endif
	}
}

void AnimationBehaviorPanelObserver::LoadAnimationOpChoices(IListControlDataOf< K2Pair<PMString, int32> > *opData)
{	
	if (opData->Length() != 6)
	{
		opData->Clear();
		
		opData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Animation/Play", IAnimationBehaviorData::kPlay));
		opData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Animation/Stop", IAnimationBehaviorData::kStop));
		opData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Animation/Pause", IAnimationBehaviorData::kPause));
		opData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Animation/Resume", IAnimationBehaviorData::kResume));
		
		opData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Animation/Reverse", IAnimationBehaviorData::kReverse));
		opData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Animation/StopAll", IAnimationBehaviorData::kStopAll));
	}
}

void AnimationBehaviorPanelObserver::InitializeAnimationOpChoice(IBehaviorData const *inActionData)
{
	InterfacePtr<IDropDownListController> choice = GetWidget<IDropDownListController>(kAnimationOperationWidgetID);
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > data(choice, IID_ILISTCONTROLDATA);
	
	LoadAnimationOpChoices(data);
	
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
		InterfacePtr<IAnimationBehaviorData const> actionData(inActionData, UseDefaultIID());
		
		for (int32 i = 0; i < data->Length(); ++i)
		{
			if ((*data)[i].second == actionData->GetOperation())
			{
				updated = true;
				if (!choice->IsSelected(i)) choice->Select(i, kInvalidate, kDontNotify);
				
				break;
			}
		}
		
		bool isStopAll = (actionData->GetOperation() == IAnimationBehaviorData::kStopAll);
		InterfacePtr<IControlView> targetChoice = GetWidget<IControlView>(kAnimationWidgetID);
		
		targetChoice->Enable(!isStopAll);
	}
	
	if (!updated) 
	{
		choice->Deselect(kInvalidate, kDontNotify);
	}

	ASSERT(choice->GetSelected() != IDropDownListController::kNoSelection);
}

void AnimationBehaviorPanelObserver::InitializeAnimationAutoReverse(IBehaviorData const *inActionData)
{
	InterfacePtr<ITriStateControlData> checkbox = GetWidget<ITriStateControlData>(kAnimationAutoReverseWidgetID);
	InterfacePtr<IAnimationBehaviorData const> actionData(inActionData, UseDefaultIID());
	InterfacePtr<IControlView> view(checkbox, UseDefaultIID());

	if (checkbox && actionData && view)
	{
		// Enabled only when the event is set to On Roll Over and the action's verb is Play

		ActionEvent selectedEvent = FormFieldUIUtils::GetSelectedEvent(this);
		if (selectedEvent == kMouseEnterEvt && actionData->GetOperation() == IAnimationBehaviorData::kPlay)
		{
			view->Enable();

			bool autoReverse = actionData->GetAutoReverseOnRollOff();
		
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

void AnimationBehaviorPanelObserver::UpdateBehaviorNode()
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