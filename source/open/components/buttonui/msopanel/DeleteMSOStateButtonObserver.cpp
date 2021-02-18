//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/DeleteMSOStateButtonObserver.cpp $
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

#include "IActiveContext.h"
#include "IAppearanceSuite.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"

// ----- Includes -----

#include "SelectionObserver.h"
#include "K2Vector.tpp"
#include "MSOStateNodeID.h"

// ----- Utility files -----

#include "IFormFieldUtils.h"
#include "MSOPanelUtils.h"
#include "IPalettePanelUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "FormFieldID.h"
#include "FormFieldUIID.h"
#include "GraphicStylesID.h"
#include "LayoutUIID.h"


class DeleteMSOStateButtonObserver : public ActiveSelectionObserver
{
public:
	DeleteMSOStateButtonObserver(IPMUnknown* boss);
	virtual ~DeleteMSOStateButtonObserver();

	virtual void AutoAttach();
	virtual void AutoDetach();

	virtual		void	HandleSelectionUpdate(const ClassID&, ISubject*, const PMIID&, void*);
	virtual		void	HandleSelectionChanged(const ISelectionMessage* iSelectionMessage);

private:
	void EnableButton(IActiveContext* activeContext);
};

// =============================================================================
// *** DeleteMSOStateButtonObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(DeleteMSOStateButtonObserver, kDeleteMSOStateButtonObserverImpl)

DeleteMSOStateButtonObserver::DeleteMSOStateButtonObserver(IPMUnknown* boss): ActiveSelectionObserver(boss) 
{
} // end constructor


DeleteMSOStateButtonObserver::~DeleteMSOStateButtonObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void DeleteMSOStateButtonObserver::HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) 
{
	ActiveSelectionObserver::HandleSelectionUpdate(theChange, theSubject, protocol, changedBy);

	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();

	if (theChange == kTrueStateMessage)
	{
		Form::AppearanceState selectedAppearance = MSOPanelUtils::GetSelectedAppearance();
		if (selectedAppearance != Form::kStateInvalid)
			MSOPanelUtils::DeleteState(selectedAppearance);

		this->EnableButton(activeContext);
	}
	else if (theChange == kListSelectionChangedMessage)
	{
		this->EnableButton(activeContext);
	}
} // end HandleSelectionUpdate()

// -----------------------------------------------------------------------------

void DeleteMSOStateButtonObserver::HandleSelectionChanged(const ISelectionMessage* iSelectionMessage)
{
	EnableButton(GetExecutionContextSession()->GetActiveContext());
} // end HandleSelectionChanged()

// -----------------------------------------------------------------------------

void DeleteMSOStateButtonObserver::AutoAttach()
{
	ActiveSelectionObserver::AutoAttach();

	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
	{
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

		InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this, kMSOPanelTreeWidgetID, IID_ISUBJECT));
		if (treeSubject && !treeSubject->IsAttached(this, IID_ITREEVIEWCONTROLLER))
			treeSubject->AttachObserver(this, IID_ITREEVIEWCONTROLLER);
	}

	this->EnableButton(GetExecutionContextSession()->GetActiveContext());
} // end AutoAttach()

// -----------------------------------------------------------------------------

void DeleteMSOStateButtonObserver::AutoDetach() 
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
	{
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);

		InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this, kMSOPanelTreeWidgetID, IID_ISUBJECT));
		if (treeSubject && treeSubject->IsAttached(this, IID_ITREEVIEWCONTROLLER))
			treeSubject->DetachObserver(this, IID_ITREEVIEWCONTROLLER);
	}

	ActiveSelectionObserver::AutoDetach();
} // end AutoDetach()

// -----------------------------------------------------------------------------

void DeleteMSOStateButtonObserver::EnableButton(IActiveContext* activeContext) 
{
	InterfacePtr<IControlView> pView(this, IID_ICONTROLVIEW);
	if (!pView) return;

	if (activeContext == nil)
	{
		ASSERT_FAIL("DeleteMSOStateButtonObserver::EnableButton - active context nil?");
		return;
	}

	IDocument* theDocument = activeContext->GetContextDocument();

	if (theDocument)
	{
		InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));

		IControlView* treeView = panelData->FindWidget(kMSOPanelTreeWidgetID);
		InterfacePtr<ITreeViewController> tvController(treeView, UseDefaultIID());
		ASSERT(tvController != nil);
		
		InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());

		NodeIDList selNodes;
		tvController->GetSelectedItems(selNodes);
		if (selNodes.size() == 1)
		{
			TreeNodePtr<MSOStateNodeID> msoStateNode(selNodes[0]);
			if (Utils<IFormFieldUtils>()->CanDeleteState(msoStateNode->GetAppearance()))
				pView->Enable();
			else
				pView->Disable();
		}
		else
			pView->Disable();
	}
	else
	{
		// Disable in no pub state
		pView->Disable();
	}
} // end EnableButton()