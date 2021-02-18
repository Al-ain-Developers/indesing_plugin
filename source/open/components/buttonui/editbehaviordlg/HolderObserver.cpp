//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/editbehaviordlg/HolderObserver.cpp $
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
//  
//  This observer is responsible for swapping in the ui panel for the selected
//  behavior in the edit behaviors dialog.  It watches for changes in the behavior menu...
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IBehaviorData.h"
#include "IDropDownListController.h"
#include "IEventHandler.h"
#include "IIntData.h"
#include "IKeyFocusHandler.h"
#include "IListControlDataOf.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "ISubject.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "UIDNodeID.h"
#include "CWidgetObserver.h"
#include "K2Pair.h"
#include "K2Vector.tpp"
#include "NodeID.h"
#include "UIDNodeID.h"

#include "FormFieldUIUtils.h"
#include "ISelectionUtils.h"
#include "Utils.h"

#include "BehaviorID.h"
#include "BehaviorUIID.h"
#include "FormFieldUIID.h"
#include "widgetid.h"

//========================================================================================
// CLASS HolderObserver
//========================================================================================

class HolderObserver : public CWidgetObserver
{
public:
	HolderObserver(IPMUnknown *boss);
	virtual ~HolderObserver();
	
	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	virtual void 	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

private:
	void			UpdateActionID(IControlView* view);
	void			ActivatePanelForSelectedBehavior();
	IControlView*	GetWidget(const int32& action);
	IControlView* 	GetBehaviorChoiceWidget();

	IControlView*	fVisiblePanel;
	int32			fActionID;
};

//========================================================================================
// METHODS HolderObserver
//========================================================================================

CREATE_PMINTERFACE(HolderObserver, kHolderObserverImpl)

//----------------------------------------------------------------------------------------
// HolderObserver constructor 
//----------------------------------------------------------------------------------------

HolderObserver::HolderObserver(IPMUnknown *boss) :
	CWidgetObserver(boss),
	fVisiblePanel(nil),
	fActionID(0)
{
}


//----------------------------------------------------------------------------------------
// HolderObserver::~HolderObserver
//----------------------------------------------------------------------------------------

HolderObserver::~HolderObserver()
{
}

//----------------------------------------------------------------------------------------

IControlView* HolderObserver::GetBehaviorChoiceWidget()
{
	InterfacePtr<IUIDData> behaviorRef(FormFieldUIUtils::QueryActiveBehavior());
	InterfacePtr<IPanelControlData> panelData(behaviorRef, ::UseDefaultIID());
	
	if ( panelData )
		return panelData->FindWidget(kBehaviorsTreeWidgetID);
	
	return nil;
}

//----------------------------------------------------------------------------------------
// HolderObserver::AutoAttach
//----------------------------------------------------------------------------------------

void HolderObserver::AutoAttach()
{	
	UpdateActionID(GetBehaviorChoiceWidget());
	ActivatePanelForSelectedBehavior();
	AttachToWidget(kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER);
}

//----------------------------------------------------------------------------------------
// HolderObserver::AutoDetach
//----------------------------------------------------------------------------------------

void HolderObserver::AutoDetach()
{
	if (fVisiblePanel != nil)
	{
		fVisiblePanel->HideView();
		fVisiblePanel = nil;
	}
	DetachFromWidget(kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER);
}

//----------------------------------------------------------------------------------------
// HolderObserver::Update
//----------------------------------------------------------------------------------------

void HolderObserver::Update(const ClassID& theChange, ISubject* subject, const PMIID& protocol, void* changedBy)
{
	InterfacePtr<IControlView> view(subject, UseDefaultIID());
	
	if (view && view->GetWidgetID() == kBehaviorsTreeWidgetID 
	&& theChange == kListSelectionChangedMessage && protocol.Get() == IID_ITREEVIEWCONTROLLER )
	{
		// update the active action id
		UpdateActionID(view);
		
		// activate the subpanel
		ActivatePanelForSelectedBehavior();
	}
}

//----------------------------------------------------------------------------------------
// HolderObserver::UpdateActionID
//----------------------------------------------------------------------------------------

void HolderObserver::UpdateActionID(IControlView* view)
{
	if (view == nil) return;

	InterfacePtr<ITreeViewController> controller(view, UseDefaultIID());
	InterfacePtr<ITreeViewHierarchyAdapter> behaviorsAdapter(view, UseDefaultIID());

	NodeIDList selection;
	controller->GetSelectedItems(selection);

	// Store the UIDRef of the selected behavior in an interface on the button's panel.
	InterfacePtr<IUIDData> uidData(FormFieldUIUtils::QueryActiveBehavior());
	if ( selection.size() && behaviorsAdapter->GetNumChildren(behaviorsAdapter->GetRootNode()) )
	{
		TreeNodePtr<UIDNodeID>	behaviorNode(selection[0]);
		UIDRef ref(Utils<ISelectionUtils>()->GetActiveSelection()->GetDataBase(), behaviorNode->GetUID());
		uidData->Set(ref);

		InterfacePtr<IBehaviorData> iBehaviorData(ref, UseDefaultIID());
		if ( iBehaviorData )
		{
			fActionID = iBehaviorData->GetAction();

			InterfacePtr<IIntData> behaviorID(uidData, IID_IINTDATA);
			behaviorID->Set(fActionID);
		}
	}
	else
	{
		fActionID = kNoAction;
		uidData->Set(UIDRef(nil, kInvalidUID));
	}
}

//----------------------------------------------------------------------------------------
// HolderObserver::ActivatePanelForSelectedBehavior
//----------------------------------------------------------------------------------------

void HolderObserver::ActivatePanelForSelectedBehavior()
{		
	if (fVisiblePanel != nil)
	{
		//twright 07/19/2002
		//If the selected behavior is already showing, don't hide/show/intialize the sub panel...
		//Vantive 525841

		// The following code causes bug #1681216 - "Refresh issue in Button Palette"
		//if (fActionID )
		//{
		//	if 	(fVisiblePanel == GetWidget(fActionID) )
		//		return;
		//}
		
		fVisiblePanel->Invalidate();
		fVisiblePanel->HideView();
		fVisiblePanel->InvalidateTransform();
	}
	
	if ( fActionID )
	{
		fVisiblePanel = GetWidget(fActionID);
		if (fVisiblePanel)
		{
			fVisiblePanel->Invalidate();
			fVisiblePanel->ShowView();
		}
	}
	else
		fVisiblePanel = nil;
		
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelDetailController> detailController((IPanelDetailController *)parentHolder->QueryParentFor(IID_ILISTBOXDETAILCONTROLLER));
	if(detailController)
		detailController->ShowDetailLevel(detailController->GetDetailLevel());
}

//----------------------------------------------------------------------------------------
// HolderObserver::GetWidget
//----------------------------------------------------------------------------------------

IControlView* HolderObserver::GetWidget(const int32& action)
{
	InterfacePtr<IPanelControlData> panels(this, UseDefaultIID());
	for (int32 i = 0; i < panels->Length(); i++)
	{
		InterfacePtr<IIntData> behaviorId(panels->GetWidget(i), UseDefaultIID());		
		if (behaviorId && action == behaviorId->Get())
			return panels->GetWidget(i);
	}
	
	return nil;
}

