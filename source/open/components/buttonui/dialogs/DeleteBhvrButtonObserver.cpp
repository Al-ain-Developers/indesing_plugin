//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/DeleteBhvrButtonObserver.cpp $
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

#include "IBehaviorSuite.h"
#include "IControlView.h"
#include "ITreeViewController.h"
#include "IWidgetUtils.h"
#include "ITreeViewHierarchyAdapter.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "CActiveSelectionObserver.h"
#include "CAlert.h"
#include "EventUtilities.h"
#include "K2Vector.tpp"
#include "SelectionUtils.h"
#include "UIDNodeID.h"
#include "Utils.h"
#include "widgetid.h"

//========================================================================================
// CLASS DeleteBehaviorButtonObserver
//========================================================================================

class DeleteBehaviorButtonObserver : public CActiveSelectionObserver
{
public:
	DeleteBehaviorButtonObserver(IPMUnknown *boss);
	virtual ~DeleteBehaviorButtonObserver();
	
	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	virtual void 	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	
protected:
	virtual void HandleSelectionChanged(const ISelectionMessage*);

private:
	void		UpdateEnableState();
	void 		DeleteSelectedAction();
	UID		GetBehaviorToDelete();
};

//========================================================================================
// METHODS DeleteBehaviorButtonObserver
//========================================================================================

CREATE_PMINTERFACE(DeleteBehaviorButtonObserver, kDeleteBehaviorButtonObserverImpl)

//----------------------------------------------------------------------------------------
// DeleteBehaviorButtonObserver constructor 
//----------------------------------------------------------------------------------------

DeleteBehaviorButtonObserver::DeleteBehaviorButtonObserver(IPMUnknown *boss) :
	CActiveSelectionObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// DeleteBehaviorButtonObserver::~DeleteBehaviorButtonObserver
//----------------------------------------------------------------------------------------

DeleteBehaviorButtonObserver::~DeleteBehaviorButtonObserver()
{
}

//----------------------------------------------------------------------------------------
// DeleteBehaviorButtonObserver::AutoAttach
//----------------------------------------------------------------------------------------

void DeleteBehaviorButtonObserver::AutoAttach()
{	
	CActiveSelectionObserver::AutoAttach();
	AttachToWidget(kDeleteBehaviorButtonWidgetID, IID_ITRISTATECONTROLDATA);
	AttachToWidget(kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER);
}

//----------------------------------------------------------------------------------------
// DeleteBehaviorButtonObserver::AutoDetach
//----------------------------------------------------------------------------------------

void DeleteBehaviorButtonObserver::AutoDetach()
{
	CActiveSelectionObserver::AutoDetach();
	DetachFromWidget(kDeleteBehaviorButtonWidgetID, IID_ITRISTATECONTROLDATA);
	DetachFromWidget(kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER);
}

//----------------------------------------------------------------------------------------
// DeleteBehaviorButtonObserver::Update
//----------------------------------------------------------------------------------------

void DeleteBehaviorButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (theChange == kTrueStateMessage)	
		DeleteSelectedAction();
	else if (theChange == kListSelectionChangedMessage)
		UpdateEnableState();
	else
		CActiveSelectionObserver::Update(theChange, theSubject, protocol, changedBy);
}

//----------------------------------------------------------------------------------------
// DeleteBehaviorButtonObserver::HandleSelectionChanged
//----------------------------------------------------------------------------------------

void DeleteBehaviorButtonObserver::HandleSelectionChanged(const ISelectionMessage*)
{
	UpdateEnableState();
}

//----------------------------------------------------------------------------------------
// DeleteBehaviorButtonObserver::UpdateEnableState
//----------------------------------------------------------------------------------------

void DeleteBehaviorButtonObserver::UpdateEnableState()
{
	InterfacePtr<IBehaviorSuite> actionSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
	InterfacePtr<IControlView> view(this, UseDefaultIID());
	
	if (actionSuite && actionSuite->CanApplyActions())
	{
		InterfacePtr<ITreeViewController> behaviorsCntlr((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER));
		
		K2Vector<NodeID> selection;
		behaviorsCntlr->GetSelectedItems(selection);
		ASSERT(selection.size() <= 1 && selection.size() >= 0);

		if (selection.size() == 0)
			view->Disable();
		else
			view->Enable();
	}
	else
		view->Disable();
}

//----------------------------------------------------------------------------------------
// DeleteBehaviorButtonObserver::DeleteSelectedAction
//----------------------------------------------------------------------------------------

void DeleteBehaviorButtonObserver::DeleteSelectedAction()
{
	InterfacePtr<IBehaviorSuite> actionSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
	if (actionSuite)
	{
		// Check if the Alt/Option key is down
		bool16 optionKeyDown = ::IsOptionAltKeyPressed();
		if ( !optionKeyDown ) {
			
			// Display a delete warning dialog
	        PMString alertStr("$$$/Dialog/Behaviors/DeleteAlert");
	        int16 whatToDo = CAlert::ModalAlert(alertStr,
	                                            kOKString, 
	                                            kCancelString, 
	                                            kNullString, 
	                                            1,                        // pass in 1, 2, or 3 to make that button the default button or 0 for no default
	                                            CAlert::eWarningIcon);
	        // If they don't want to continue, then punt
			if ( whatToDo == 2 )
				return;
		}

		actionSuite->DeleteAction(GetBehaviorToDelete());
	}
}

//----------------------------------------------------------------------------------------
// DeleteBehaviorButtonObserver::GetBehaviorToDelete
//----------------------------------------------------------------------------------------

UID DeleteBehaviorButtonObserver::GetBehaviorToDelete()
{
	InterfacePtr<ITreeViewController> behaviorsCntlr((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER));
	InterfacePtr<ITreeViewHierarchyAdapter> behaviorsAdapter(behaviorsCntlr, UseDefaultIID());

	K2Vector<NodeID> selection;
	behaviorsCntlr->GetSelectedItems(selection);
	ASSERT(selection.size() == 1);
	
	TreeNodePtr<UIDNodeID>	behaviorNode(selection[0]);
	return behaviorNode->GetUID();
}

