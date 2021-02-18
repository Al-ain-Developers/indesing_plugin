//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/mso/SwitchToNextPrevMSOStatePanelObserver.cpp $
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
#include "IDropDownListController.h"
#include "IFormFieldSuite.h"
#include "IHierarchy.h"
#include "IListControlDataOf.h"
#include "IMultiStateObjectBehaviorData.h"
#include "IDynamicTargetsFacade.h"
#include "ISpreadDynamicContentMgr.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"
#include "ITriStateControlData.h"
#include "IUIDData.h"

// ----- Includes -----

#include "CBehaviorPanelObserver.h"
#include "K2Pair.h"
#include "K2Vector.tpp"
#include "MSOBehaviorPanelTypes.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"
#include "ISelectionUtils.h"
#include "IWidgetUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "BehaviorUIID.h"
#include "BehaviorUIDefs.h"


static const bool16 kInvalidate = kTrue;
static const bool16 kDontNotify = kFalse;

template<int ChoiceWID>
class SwitchToNextOrPrevMSOStatePanelObserver : public CBehaviorPanelObserver
{
	typedef CBehaviorPanelObserver inherited;
	
	bool fIsAttached;
	
public:
	SwitchToNextOrPrevMSOStatePanelObserver(IPMUnknown *boss) :
		inherited(boss),
		fIsAttached(false)
	{
	}

	virtual void AutoAttach()
	{
		if (!fIsAttached)
		{
			inherited::AutoAttach();
			
			AttachToWidget(ChoiceWID, IID_ISTRINGLISTCONTROLDATA);
			AttachToWidget(kLoopAtBeginningOrEndWidgetID, IID_ITRISTATECONTROLDATA);
			
			fIsAttached = true;
		}
	}
	
	virtual void AutoDetach()
	{
		if (fIsAttached)
		{
			inherited::AutoDetach();
			
			DetachFromWidget(ChoiceWID, IID_ISTRINGLISTCONTROLDATA);
			DetachFromWidget(kLoopAtBeginningOrEndWidgetID, IID_ITRISTATECONTROLDATA);
			
			fIsAttached = false;
		}
	}

protected:
	virtual void HandleSelectionUpdate(
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
	
	virtual void InitializeFieldsFromActionData(const IBehaviorData* inActionData)
	{
		if (inActionData)
		{
			InitializeMSOChoice(inActionData);
			InitializeLoopAtBeginningOrEnd(inActionData);
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
	
	virtual bool ApplyFieldsToActionData(IBehaviorData* inActionData)
	{
		IMultiStateObjectBehaviorData *actionData = static_cast<IMultiStateObjectBehaviorData *>(inActionData);
		
		InterfacePtr<IDropDownListController> msoChoice = GetWidget<IDropDownListController>(ChoiceWID);
		InterfacePtr< IListControlDataOf<MSOTargetReference> > msoData(msoChoice, IID_ILISTCONTROLDATA);
		int32 selection = msoChoice->GetSelected();

		bool changed = false;

		if (selection != IDropDownListController::kNoSelection)
		{
			UID selectedItem = (*msoData)[selection].fReference.GetUID();
			
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
	
		InterfacePtr<ITriStateControlData const> checkbox = GetWidget<ITriStateControlData const>(kLoopAtBeginningOrEndWidgetID);
		bool bLoops = !checkbox->IsSelected();
		
		if (actionData->GetLoopAtBeginningOrEnd() != bLoops)
		{
			changed = true;
			actionData->SetLoopAtBeginningOrEnd(bLoops);
		}
		
		return changed;
	}

private:
	static void LoadMSOChoices(IBehaviorData const *behaveData, IListControlDataOf<MSOTargetReference> *data)
	{
		data->Clear();
		
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

	void InitializeMSOChoice(IBehaviorData const *inActionData)
	{
		InterfacePtr<IDropDownListController> choice = GetWidget<IDropDownListController>(ChoiceWID);
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

	void InitializeLoopAtBeginningOrEnd(IBehaviorData const *inActionData)
	{
		InterfacePtr<ITriStateControlData> checkbox = GetWidget<ITriStateControlData>(kLoopAtBeginningOrEndWidgetID);
		InterfacePtr<IMultiStateObjectBehaviorData const> actionData(inActionData, UseDefaultIID());
		InterfacePtr<IControlView> view(checkbox, UseDefaultIID());

		if (checkbox && actionData && view)
		{
			bool loopAtBeginningOrEnd = actionData->GetLoopAtBeginningOrEnd();

			if (loopAtBeginningOrEnd)
				checkbox->Deselect(kInvalidate, kDontNotify);
			else
				checkbox->Select(kInvalidate, kDontNotify);
		}
	}

	void UpdateBehaviorNode()
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

	template<typename Ifc>
	inline InterfacePtr<Ifc> GetWidget(WidgetID const &id) const
	{
		// Pardon the mess
		return InterfacePtr<Ifc>(static_cast<Ifc *>(Utils<IWidgetUtils>()->QueryRelatedWidget(this, id, Ifc::kDefaultIID)));
	}
};

CREATE_PMINTERFACE(SwitchToNextOrPrevMSOStatePanelObserver<kNextMSOTargetChoiceWidgetID>, kSwitchToNextMSOStatePanelObserverImpl)
CREATE_PMINTERFACE(SwitchToNextOrPrevMSOStatePanelObserver<kPrevMSOTargetChoiceWidgetID>, kSwitchToPrevMSOStatePanelObserverImpl)
