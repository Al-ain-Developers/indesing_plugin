//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/sound/SoundBehaviorPanelObserver.cpp $
//  
//  Owner: Mark VerMurlen
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

// ----- Interface Includes -----

#include "IControlView.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IFormFieldSuite.h"
#include "IHierarchy.h"
#include "IListControlDataOf.h"
#include "INamedPageItemList.h"
#include "IPanelControlData.h"
#include "ISelectionUtils.h"
#include "ISoundActionData.h"
#include "IDynamicTargetsFacade.h"
#include "ISpreadDynamicContentMgr.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"


// ----- Implementation Includes -----

#include "BehaviorUIDefs.h"
#include "CBehaviorPanelObserver.h"
#include "K2Pair.h"
#include "K2Vector.tpp"
#include "SoundListElement.h"

#include "ErrorUtils.h"
#include "FormFieldUIUtils.h"
#include "Utils.h"

#include "BehaviorUIID.h"
#include "widgetid.h"

//========================================================================================
// CLASS SoundBehaviorPanelObserver
//========================================================================================

class SoundBehaviorPanelObserver : public CBehaviorPanelObserver
{
public:
	SoundBehaviorPanelObserver(IPMUnknown *boss);
	virtual ~SoundBehaviorPanelObserver();

	virtual void 	AutoAttach();
	virtual void 	AutoDetach();

protected:
	virtual void HandleSelectionUpdate
		(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
		);
	virtual void	InitializeFieldsFromActionData(const IBehaviorData* inActionData);
	virtual bool	ApplyFieldsToActionData(IBehaviorData* inActionData);

private:
	void			LoadSoundChoices(const IBehaviorData* inActionData, IListControlDataOf<SoundListElement>* soundData);
	void			InitializeSoundChoice(ISoundActionData* inSoundActionData);
	
	void			LoadSoundOpChoices(IListControlDataOf< K2Pair<PMString, int32> >* soundOpData);
	void			InitializeSoundOpChoice(ISoundActionData* inSoundActionData);

	void			UpdateBehaviorNode();

	bool	isAttached;
};

//========================================================================================
// METHODS SoundBehaviorPanelObserver
//========================================================================================

CREATE_PMINTERFACE(SoundBehaviorPanelObserver, kSoundBehaviorPanelObserverImpl)

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver constructor 
//----------------------------------------------------------------------------------------

SoundBehaviorPanelObserver::SoundBehaviorPanelObserver(IPMUnknown *boss) :
	CBehaviorPanelObserver(boss),
	isAttached(false)
{
}


//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::~SoundBehaviorPanelObserver
//----------------------------------------------------------------------------------------

SoundBehaviorPanelObserver::~SoundBehaviorPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::AutoAttach
//----------------------------------------------------------------------------------------

void SoundBehaviorPanelObserver::AutoAttach()
{
	if ( ! isAttached ) {
		
		CBehaviorPanelObserver::AutoAttach();
		
		AttachToWidget(kSoundWidgetID, IID_ISTRINGLISTCONTROLDATA);
		AttachToWidget(kOperationWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = true;
#if 0
	InterfacePtr<IControlView> addUpdateButtonView((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAddBehaviorButtonWidgetID, IID_ICONTROLVIEW));
	
	if ( ! addUpdateButtonView->IsEnabled() )
		addUpdateButtonView->Enable();
#endif
	}
}

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::AutoDetach
//----------------------------------------------------------------------------------------

void SoundBehaviorPanelObserver::AutoDetach()
{
	if ( isAttached ) {
		
		CBehaviorPanelObserver::AutoDetach();
		
		DetachFromWidget(kSoundWidgetID, IID_ISTRINGLISTCONTROLDATA);
		DetachFromWidget(kOperationWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = false;
	}
}

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void SoundBehaviorPanelObserver::HandleSelectionUpdate
	(
	const ClassID&	inBossClassID, 
	ISubject* inSubject, 
	const PMIID& 	inProtocol,
	void* 			inMessage
	)
{
	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	
	if ( iFormSuite && !iFormSuite->IsDefaultSelection() && iFormSuite->IsFieldSelection() )
	{
		if ( inProtocol == IID_ISTRINGLISTCONTROLDATA )
		{
			CBehaviorPanelObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
		}
		else
		{
			InitializeFieldsFromActionData(nil);
		}
		return;
	}

	ActiveSelectionObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
}
//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

void SoundBehaviorPanelObserver::InitializeFieldsFromActionData(const IBehaviorData* inActionData)
{
	if ( inActionData == nil )
	{
		bool bUpdated(false);

		InterfacePtr<IUIDData> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
		if ( activeBehavior )
		{
			InterfacePtr<IBehaviorData> iBehaviorData(activeBehavior->GetRef(), UseDefaultIID());
			if ( iBehaviorData )
			{
				bUpdated = true;
				InitializeFieldsFromActionData(iBehaviorData);
			}
		}
		if ( !bUpdated )
		{
			InitializeSoundChoice(nil);
			InitializeSoundOpChoice(nil);
		}
	}
	else
	{
		InterfacePtr<ISoundActionData> soundActionData(inActionData, UseDefaultIID());
		InitializeSoundChoice(soundActionData);
		InitializeSoundOpChoice(soundActionData);
	}
}

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::ApplyFieldsToActionData
//----------------------------------------------------------------------------------------

bool SoundBehaviorPanelObserver::ApplyFieldsToActionData(IBehaviorData* inActionData)
{
	ISoundActionData* actionData = static_cast<ISoundActionData*>(inActionData);
	
	InterfacePtr<IDropDownListController> soundChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSoundWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf<SoundListElement> > soundData(soundChoice, IID_ILISTCONTROLDATA);
	int32 selection = soundChoice->GetSelected();

	bool bChanged(false);

	if (selection != IDropDownListController::kNoSelection)
	{
		if ( actionData->GetSound() != (*soundData)[selection].GetSoundRef().GetUID() )
		{
			actionData->SetSound((*soundData)[selection].GetSoundRef().GetUID());
			bChanged = true;
			this->UpdateBehaviorNode();
		}
	}
	else if ( actionData->GetSound() != kInvalidUID )
	{
		bChanged = true;
		actionData->SetSound(kInvalidUID);
		this->UpdateBehaviorNode();
	}

	InterfacePtr<IDropDownListController> operationChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kOperationWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > operationData(operationChoice, IID_ILISTCONTROLDATA);
	
	if ( bChanged || actionData->GetOperation() != (ISoundActionData::Operation) (*operationData)[operationChoice->GetSelected()].second )
	{
		bChanged = true;
		actionData->SetOperation((ISoundActionData::Operation) (*operationData)[operationChoice->GetSelected()].second);
	}

	actionData->SetVolume(1.0);

	actionData->SetRepeat(kFalse);
	return bChanged;
}

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::LoadSoundChoices
//----------------------------------------------------------------------------------------

void SoundBehaviorPanelObserver::LoadSoundChoices(const IBehaviorData* inSoundActionData, IListControlDataOf<SoundListElement>* soundData)
{	
	soundData->Clear();

	if (!inSoundActionData) return;

	IDataBase *db = ::GetDataBase(inSoundActionData);
	InterfacePtr<IHierarchy /*const*/> pageitem(db, inSoundActionData->GetOwner(), UseDefaultIID());
	
	if (pageitem)
	{
		const bool kIncludeMasterItems = true;
		std::vector<UID> itemList;
		if (Utils<Facade::IDynamicTargetsFacade> ()->GetTargetList (UIDRef (db, inSoundActionData->GetOwner()), ISpreadDynamicContentMgr::kSoundItemType, itemList, kIncludeMasterItems))
		{
			for (std::vector<UID>::const_iterator i = itemList.begin(), end = itemList.end(); i != end; ++i)
			{
				soundData->Add(SoundListElement(UIDRef(db, *i)));
			}
		}

		if (soundData->Length() == 0)
			soundData->Add(SoundListElement(UIDRef::gNull));
	}
}

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::InitializeSoundChoice
//----------------------------------------------------------------------------------------

void SoundBehaviorPanelObserver::InitializeSoundChoice(ISoundActionData* inSoundActionData)
{
	InterfacePtr<IDropDownListController> soundChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSoundWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf<SoundListElement> > soundData(soundChoice, IID_ILISTCONTROLDATA);
	
	LoadSoundChoices(inSoundActionData, soundData);
	
	bool bUpdated = false;

	if (inSoundActionData == nil)
	{
		if (soundData->Length() > 0)
		{
			bUpdated = true;
			soundChoice->Select(0, kTrue, kFalse);
		}
	}
	else
	{
		for (int32 i = 0; i < soundData->Length(); i++)
			if ((*soundData)[i].GetSoundRef().GetUID() == inSoundActionData->GetSound())
			{
				bUpdated = true;
				if ( !soundChoice->IsSelected(i) )
					soundChoice->Select(i, kTrue, kFalse);
				break;
			}
	}

	if ( !bUpdated )
	{
		soundChoice->Deselect(kTrue, kFalse);
#ifdef DEBUG
		InterfacePtr<ISoundActionData const> behaviorData(inSoundActionData, UseDefaultIID());
		if (behaviorData != nil && behaviorData->GetSound() != kInvalidUID)
			ASSERT_FAIL(FORMAT_ARGS("Button has a sound target (uid %d) that is not on the same spread!", behaviorData->GetSound().Get()));
#endif
	}
}

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::LoadSoundOpChoices
//----------------------------------------------------------------------------------------

void SoundBehaviorPanelObserver::LoadSoundOpChoices(IListControlDataOf< K2Pair<PMString, int32> >* soundOpData)
{	
	if ( soundOpData->Length() != 4 )
	{
		soundOpData->Clear();
		
		soundOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Sound/Play", ISoundActionData::kPlay));
		soundOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Sound/Stop", ISoundActionData::kStop));
		soundOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Sound/Pause", ISoundActionData::kPause));
		soundOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Sound/Resume", ISoundActionData::kResume));
		soundOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Sound/StopAll", ISoundActionData::kStopAll));
	}
}

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::InitializeSoundOpChoice
//----------------------------------------------------------------------------------------

void SoundBehaviorPanelObserver::InitializeSoundOpChoice(ISoundActionData* inSoundActionData)
{
	InterfacePtr<IDropDownListController> operationChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kOperationWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > operationData(operationChoice, IID_ILISTCONTROLDATA);
	
	LoadSoundOpChoices(operationData);
	
	bool bUpdated = false;
	if (inSoundActionData == nil)
	{
		if (operationData->Length() > 0)
		{
			bUpdated = true;
			operationChoice->Select(0, kTrue, kFalse);
		}
	}
	else
	{
		InterfacePtr<ISoundActionData> actionData(inSoundActionData, UseDefaultIID());
		for (int32 i = 0; i < operationData->Length(); i++)
		{
			if ((*operationData)[i].second == inSoundActionData->GetOperation())
			{
				bUpdated = true;
				operationChoice->Select(i, kTrue, kFalse);
				break;
			}
		}
		
		bool isStopAll = (actionData->GetOperation() == ISoundActionData::kStopAll);
		InterfacePtr<IControlView> targetChoice((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSoundWidgetID, IID_ICONTROLVIEW));		
		targetChoice->Enable(!isStopAll);
	}

	if ( !bUpdated )
		operationChoice->Deselect(kTrue, kFalse);

	ASSERT(operationChoice->GetSelected() != IDropDownListController::kNoSelection);
}

//----------------------------------------------------------------------------------------
// SoundBehaviorPanelObserver::UpdateBehaviorNode
//----------------------------------------------------------------------------------------

void SoundBehaviorPanelObserver::UpdateBehaviorNode()
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