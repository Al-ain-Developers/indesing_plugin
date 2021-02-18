//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/showhide/ShowHideFieldsButtonObservr.cpp $
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
#include "IFieldsTreeViewAdapter.h"
#include "IPanelControlData.h"
#include "ISession.h"
#include "ISubject.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

// ----- Utils Includes -----

#include "Utils.h"

// ----- ID Includes -----

#include "CWidgetObserver.h"
#include "BehaviorUIID.h"
#include "FormFieldUIID.h"
#include "NodeID.h"
#include "widgetid.h"
#include "K2Vector.tpp"

//========================================================================================
// CLASS ShowHideFieldsButtonObserver
//========================================================================================

class ShowHideFieldsButtonObserver : public CWidgetObserver
{
public:
	ShowHideFieldsButtonObserver(IPMUnknown *boss);
	virtual ~ShowHideFieldsButtonObserver();
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
private:
	IControlView *fShowButton;
	IControlView *fHideButton;
	IControlView *fIgnoreButton;
	IControlView *fTreeView;
};

//========================================================================================
// METHODS ShowHideFieldsButtonObserver
//========================================================================================

CREATE_PMINTERFACE(ShowHideFieldsButtonObserver, kShowHideFieldsButtonObserverImpl)

//----------------------------------------------------------------------------------------
// ShowHideFieldsButtonObserver constructor 
//----------------------------------------------------------------------------------------

ShowHideFieldsButtonObserver::ShowHideFieldsButtonObserver(IPMUnknown *boss) :
	CWidgetObserver(boss),
	fShowButton(nil),
	fHideButton(nil),
	fIgnoreButton(nil),
	fTreeView(nil)
{
}


//----------------------------------------------------------------------------------------
// ShowHideFieldsButtonObserver::~ShowHideFieldsButtonObserver: 
//----------------------------------------------------------------------------------------

ShowHideFieldsButtonObserver::~ShowHideFieldsButtonObserver()
{
}


//----------------------------------------------------------------------------------------
// ShowHideFieldsButtonObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void ShowHideFieldsButtonObserver::AutoAttach()
{
	AttachToWidget(kShowFieldButtonWidgetID, IID_ITRISTATECONTROLDATA, IID_ISHOWHIDEBUTTONSOBSERVER);
	
	InterfacePtr<IControlView> showButton((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kShowFieldButtonWidgetID, IID_ICONTROLVIEW));
	fShowButton = showButton.get();
	
	AttachToWidget(kHideFieldButtonWidgetID, IID_ITRISTATECONTROLDATA, IID_ISHOWHIDEBUTTONSOBSERVER, fShowButton);
	AttachToWidget(kIgnoreFieldButtonWidgetID, IID_ITRISTATECONTROLDATA, IID_ISHOWHIDEBUTTONSOBSERVER, fShowButton);
	AttachToWidget(kSHFieldsWidgetID, IID_ITREEVIEWCONTROLLER, IID_ISHOWHIDEBUTTONSOBSERVER);

	InterfacePtr<IPanelControlData> iPanelControlData(this, IID_IPANELCONTROLDATA);
	fHideButton = iPanelControlData->FindWidget(kHideFieldButtonWidgetID);
	fIgnoreButton = iPanelControlData->FindWidget(kIgnoreFieldButtonWidgetID);
	
	InterfacePtr<ISubject> treeSubject((ISubject *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSHFieldsWidgetID, IID_ISUBJECT));
	if ( treeSubject )
		this->Update(kListSelectionChangedMessage, treeSubject, IID_ITREEVIEWCONTROLLER, this );
}

//----------------------------------------------------------------------------------------
// ShowHideFieldsButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void ShowHideFieldsButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> iSubject(fShowButton, UseDefaultIID());
	if ( iSubject && iSubject->IsAttached(this, IID_ITRISTATECONTROLDATA, IID_ISHOWHIDEBUTTONSOBSERVER) )
	{
		DetachFromWidget(kShowFieldButtonWidgetID, IID_ITRISTATECONTROLDATA, IID_ISHOWHIDEBUTTONSOBSERVER);
		DetachFromWidget(kHideFieldButtonWidgetID, IID_ITRISTATECONTROLDATA, IID_ISHOWHIDEBUTTONSOBSERVER);
		DetachFromWidget(kIgnoreFieldButtonWidgetID, IID_ITRISTATECONTROLDATA, IID_ISHOWHIDEBUTTONSOBSERVER);
		DetachFromWidget(kSHFieldsWidgetID, IID_ITREEVIEWCONTROLLER, IID_ISHOWHIDEBUTTONSOBSERVER);
	}
}

//----------------------------------------------------------------------------------------
// ShowHideFieldsButtonObserver::Update: 
//----------------------------------------------------------------------------------------

void ShowHideFieldsButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	InterfacePtr<IControlView> view(theSubject, UseDefaultIID());
	if (view
		&& theChange == kTrueStateMessage
		&& (view->GetWidgetID() == kShowFieldButtonWidgetID || view->GetWidgetID() == kHideFieldButtonWidgetID || view->GetWidgetID() == kIgnoreFieldButtonWidgetID))
	{
		// User clicked on one of: Show, Hide, Ignore
		InterfacePtr<IFieldsTreeViewAdapter> adapter((IFieldsTreeViewAdapter *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSHFieldsWidgetID, IID_ITREEVIEWHIERARCHYADAPTER));
		InterfacePtr<ITreeViewController> showHideFieldsTree((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(adapter, kSHFieldsWidgetID, IID_ITREEVIEWCONTROLLER));
		if ( showHideFieldsTree )
		{
			K2Vector<NodeID> selection;
			showHideFieldsTree->GetSelectedItems(selection);
			
			InterfacePtr<ISubject> treeSubject(showHideFieldsTree, UseDefaultIID());
			InterfacePtr<ITreeViewMgr> treeViewMgr(showHideFieldsTree, UseDefaultIID());
			
			const WidgetID widgetID(view->GetWidgetID());
			IShowHideFieldActionData::Action action(IShowHideFieldActionData::kNone);
			
			if (widgetID == kShowFieldButtonWidgetID)
				action = IShowHideFieldActionData::kShow;
			else if (widgetID == kHideFieldButtonWidgetID)
				action = IShowHideFieldActionData::kHide;
			
			bool bActionChanged(false);
			for ( K2Vector<NodeID>::const_iterator nodeIter = selection.begin(); nodeIter != selection.end(); ++nodeIter )
			{
				if (adapter->GetAction(*nodeIter) != action)
				{
					bActionChanged = true;
					adapter->SetAction(*nodeIter, action);
					treeViewMgr->NodeChanged( *nodeIter );
				}
			}
			
			if ( bActionChanged && treeSubject )
				treeSubject->Change(::GetClass(this), IID_ITREEVIEWCONTROLLER, this);
		}		
	}
	else if ( view && theChange == kListSelectionChangedMessage )
	{
		// User changed the selection in the List of fields. Update the state of the Show, Hide and Ignore buttons
		InterfacePtr<ITreeViewController> showHideFieldsTree((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(view, kSHFieldsWidgetID, IID_ITREEVIEWCONTROLLER));
		if ( showHideFieldsTree )
		{
			K2Vector<NodeID> selection;
			showHideFieldsTree->GetSelectedItems(selection);
			
			if ( !fTreeView )
				fTreeView = view;
				
			if (selection.size() == 0)
			{
				fShowButton->Disable();
				fHideButton->Disable();
				fIgnoreButton->Disable();
			}
			else
			{
				fShowButton->Enable();
				fHideButton->Enable();
				fIgnoreButton->Enable();
			}
		}
	}
}
