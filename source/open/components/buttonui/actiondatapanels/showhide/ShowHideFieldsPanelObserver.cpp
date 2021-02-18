//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/showhide/ShowHideFieldsPanelObserver.cpp $
//  
//  Owner: Michael Burbidge
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
#include "IDynamicTargetsFacade.h"
#include "IFieldsTreeViewAdapter.h"
#include "IFormFieldSuite.h"
#include "IFormFieldUtils.h"
#include "IGraphicStyleDescriptor.h"
#include "IHierarchy.h"
#include "ISelectionUtils.h"
#include "IShowHideFieldActionData.h"
#include "ISpread.h"
#include "ISpreadFieldOrder.h"
#include "ISubject.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewMgr.h"
#include "ITriStateControlData.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "CBehaviorPanelObserver.h"
#include "IntNodeID.h"
#include "K2Pair.h"
#include "K2Vector.tpp"

#include <set>

#include "AttributesUtils.h"
#include "FormFieldUIUtils.h"
#include "Utils.h"

#include "BehaviorUIID.h"
#include "BehaviorID.h"
#include "GenericID.h"
#include "widgetid.h"

//========================================================================================
// CLASS ShowHideFieldsPanelObserver
//========================================================================================

class ShowHideFieldsPanelObserver : public CBehaviorPanelObserver
{
public:
	ShowHideFieldsPanelObserver(IPMUnknown *boss);
	virtual ~ShowHideFieldsPanelObserver();
	
	virtual void AutoAttach();
	virtual void AutoDetach();

	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

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
	void			LoadShowHideFields(IFieldsTreeViewAdapter* fieldsAdapter, const IBehaviorData *inActionData);
	void			InitializeShowHideFields(const IBehaviorData *inActionData);
	PMString		GetFieldName(IDataBase* db, UID uid) const;

	void SetAction(const IShowHideFieldActionData::Action& action);

	UIDRef fCurrentDocRef;
};

//========================================================================================
// METHODS ShowHideFieldsPanelObserver
//========================================================================================

CREATE_PMINTERFACE(ShowHideFieldsPanelObserver, kShowHideFieldsPanelObserverImpl)

//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver constructor 
//----------------------------------------------------------------------------------------

ShowHideFieldsPanelObserver::ShowHideFieldsPanelObserver(IPMUnknown *boss) :
	CBehaviorPanelObserver(boss),
	fCurrentDocRef(UIDRef::gNull)
{
}


//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver::~ShowHideFieldsPanelObserver: 
//----------------------------------------------------------------------------------------

ShowHideFieldsPanelObserver::~ShowHideFieldsPanelObserver()
{
}


//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void ShowHideFieldsPanelObserver::AutoAttach()
{
	CBehaviorPanelObserver::AutoAttach();
	AttachToWidget(kSHFieldsWidgetID, IID_ITREEVIEWCONTROLLER);
	
	InterfacePtr<IObserver> buttonsObserver(this, IID_ISHOWHIDEBUTTONSOBSERVER);
	if ( buttonsObserver )
		buttonsObserver->AutoAttach();

	if (fCurrentSelection)
	{
		InterfacePtr<IDocument> doc(fCurrentSelection->GetDataBase(), fCurrentSelection->GetDataBase()->GetRootUID(), UseDefaultIID());
		InterfacePtr<ISubject> docSubject(doc, IID_ISUBJECT);
		if (docSubject)
		{
			if (!docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IHIERARCHY_DOCUMENT, IID_IOBSERVER)) 
				docSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IHIERARCHY_DOCUMENT, IID_IOBSERVER); 

			fCurrentDocRef = UIDRef(fCurrentSelection->GetDataBase(), fCurrentSelection->GetDataBase()->GetRootUID());
		}	
	}
}

//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void ShowHideFieldsPanelObserver::AutoDetach()
{
	CBehaviorPanelObserver::AutoDetach();
	DetachFromWidget(kSHFieldsWidgetID, IID_ITREEVIEWCONTROLLER);

	InterfacePtr<IObserver> buttonsObserver(this, IID_ISHOWHIDEBUTTONSOBSERVER);
	if ( buttonsObserver )
		buttonsObserver->AutoDetach();

	InterfacePtr<ISubject> docSubject(fCurrentDocRef, IID_ISUBJECT);
	if (docSubject)
	{
		if (docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IHIERARCHY_DOCUMENT, IID_IOBSERVER))
			docSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IHIERARCHY_DOCUMENT, IID_IOBSERVER);

		fCurrentDocRef = UIDRef::gNull;
	}

}

//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver::LazyUpdate
//----------------------------------------------------------------------------------------

void ShowHideFieldsPanelObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	if (protocol.Get() == IID_IHIERARCHY_DOCUMENT)
	{
		InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
		
		if ( iFormSuite && !iFormSuite->IsDefaultSelection() && iFormSuite->IsFieldSelection() )
		{
			// This is needed so tree will update when add/remove buttons from the hierarchy via scripting.

			InitializeFieldsFromActionData(nil);

			InterfacePtr<ITreeViewMgr> treeViewMgr((ITreeViewMgr *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSHFieldsWidgetID, IID_ITREEVIEWMGR));
			if (treeViewMgr)
				treeViewMgr->ChangeRoot();
		}
	}
}

//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void ShowHideFieldsPanelObserver::HandleSelectionUpdate
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
		if ( inProtocol == IID_ITREEVIEWCONTROLLER )
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
// ShowHideFieldsPanelObserver::InitializeFields
//----------------------------------------------------------------------------------------

void ShowHideFieldsPanelObserver::InitializeFieldsFromActionData(const IBehaviorData *inActionData)
{
	if ( inActionData )
		InitializeShowHideFields(inActionData);
	else
	{
		InterfacePtr<IUIDData> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
		if ( activeBehavior )
		{
			InterfacePtr<IBehaviorData> iBehaviorData(activeBehavior->GetRef(), UseDefaultIID());
			if ( iBehaviorData )
				InitializeFieldsFromActionData(iBehaviorData);
		}
	}
}

//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver::ApplyFields
//----------------------------------------------------------------------------------------

bool ShowHideFieldsPanelObserver::ApplyFieldsToActionData(IBehaviorData *inActionData)
{
	IShowHideFieldActionData* actionData = static_cast<IShowHideFieldActionData*>(inActionData);
	InterfacePtr<IFieldsTreeViewAdapter> fieldsAdapter((IFieldsTreeViewAdapter *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSHFieldsWidgetID, IID_ITREEVIEWHIERARCHYADAPTER));
	
	actionData->SetFields(fieldsAdapter->Get());
	return true;
}

//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver::LoadShowHideFields
//----------------------------------------------------------------------------------------

void ShowHideFieldsPanelObserver::LoadShowHideFields(IFieldsTreeViewAdapter* fieldsAdapter, const IBehaviorData *inActionData)
{	
	IDataBase* db = Utils<ISelectionUtils>()->GetActiveSelection()->GetDataBase();
	InterfacePtr<IDocument> document(db, db->GetRootUID(), UseDefaultIID());
	
	K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> > fields;
	
	if (document)
	{
		std::set<PMString> formNames;
		
		InterfacePtr<IHierarchy> formFieldHier(db, inActionData->GetOwner(), UseDefaultIID());
		UID spreadUID = Utils<IFormFieldUtils>()->GetSpreadUID(formFieldHier);
		
		ASSERT_MSG(spreadUID != kInvalidUID, "No Valid Spread");

		if (spreadUID == kInvalidUID )
			return;

		InterfacePtr<ISpread> iSpread(db, spreadUID, ::UseDefaultIID());
		InterfacePtr<ISpreadFieldOrder> iSpreadFieldOrder(iSpread, ::UseDefaultIID());

		for(int32 j = 0; j < iSpread->GetNumPages(); j++)
		{
			UID pageUID = iSpread->GetNthPageUID(j);
			ISpreadFieldOrder::TabOrder forms = iSpreadFieldOrder->GetTabOrder( pageUID );

            for (const auto &theForm : forms)
			{
				PMString name =  GetFieldName(db, theForm);

				// Check that the name is not empty and don't insert duplicate names.
				if (!name.IsEmpty() && formNames.find(name) == formNames.end())
				{
					fields.push_back(K2Pair<UID, IShowHideFieldActionData::Action>(theForm, IShowHideFieldActionData::kNone));
					formNames.insert(name);
				}
			}
		}
	}
	
	fieldsAdapter->Set(db, fields);
}

//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver::InitializeShowHideFields
//----------------------------------------------------------------------------------------

void ShowHideFieldsPanelObserver::InitializeShowHideFields(const IBehaviorData *inActionData)
{
	
	InterfacePtr<IFieldsTreeViewAdapter> fieldsAdapter((IFieldsTreeViewAdapter *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSHFieldsWidgetID, IID_ITREEVIEWHIERARCHYADAPTER));
	LoadShowHideFields(fieldsAdapter, inActionData);
	
	IDataBase* db = fieldsAdapter->GetDataBase();
	
	K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> > fields(fieldsAdapter->Get());
	
	if (inActionData != 0)
	{
		InterfacePtr<IShowHideFieldActionData> actionData(inActionData, UseDefaultIID());
		K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> > selectFields(actionData->GetFields());
		for (K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> >::iterator i = selectFields.begin(); i != selectFields.end(); i++)
		{
			for (K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> >::iterator j = fields.begin(); j != fields.end(); j++)
			{
				UID iFirst = (*i).first;
				UID jFirst = (*j).first;

				if (GetFieldName(db,iFirst) == GetFieldName(db,jFirst))
					*j = *i;
			}
		}
		
		fieldsAdapter->Set(fieldsAdapter->GetDataBase(), fields);
	}
}

//----------------------------------------------------------------------------------------
// ShowHideFieldsPanelObserver::GetFieldName
//----------------------------------------------------------------------------------------

PMString ShowHideFieldsPanelObserver::GetFieldName(IDataBase* db, UID uid) const
{
	InterfacePtr<IGraphicStyleDescriptor> styleDesc(db, uid, ::UseDefaultIID());
	return AttributesUtils::GetStringValue(styleDesc,  kFormNameAttrBoss);
}
