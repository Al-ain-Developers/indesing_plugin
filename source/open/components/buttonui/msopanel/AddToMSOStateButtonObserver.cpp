//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/AddToMSOStateButtonObserver.cpp $
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

// ----- Includes -----

#include "SelectionObserver.h"
#include "K2Vector.tpp"
#include "MSOStateNodeID.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"
#include "MSOPanelUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "FormFieldID.h"
#include "FormFieldUIID.h"


class AddToMSOStateButtonObserver : public ActiveSelectionObserver
{
public:
	AddToMSOStateButtonObserver(IPMUnknown* boss);
	virtual ~AddToMSOStateButtonObserver();

	virtual void AutoAttach();
	virtual void AutoDetach();

	virtual		void	HandleSelectionUpdate(const ClassID&, ISubject*, const PMIID&, void*);
	virtual		void	HandleSelectionChanged(const ISelectionMessage* iSelectionMessage);

private:
	void EnableButton(IActiveContext* activeContext);
};

// =============================================================================
// *** AddToMSOStateButtonObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(AddToMSOStateButtonObserver, kAddToMSOStateButtonObserverImpl)

AddToMSOStateButtonObserver::AddToMSOStateButtonObserver(IPMUnknown* boss): ActiveSelectionObserver(boss) 
{
} // end constructor


AddToMSOStateButtonObserver::~AddToMSOStateButtonObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void AddToMSOStateButtonObserver::HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) 
{
	ActiveSelectionObserver::HandleSelectionUpdate(theChange, theSubject, protocol, changedBy);

	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();

	if (theChange == kTrueStateMessage)
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
		if (iAppearanceSuite)
		{
			ErrorCode err = iAppearanceSuite->AddItemsAsStates(kMultiStateObjectItemBoss, IAppearanceSuite::kAddItemsToActiveState);
			if (err == kSuccess)
				iAppearanceSuite->SelectAssociatedAppearanceItemOfType(kMultiStateObjectItemBoss);
		}

		this->EnableButton(activeContext);
	}
	else if (theChange == kListSelectionChangedMessage)
	{
		this->EnableButton(activeContext);
	}
} // end HandleSelectionUpdate()

// -----------------------------------------------------------------------------

void AddToMSOStateButtonObserver::HandleSelectionChanged(const ISelectionMessage* iSelectionMessage)
{
	EnableButton(GetExecutionContextSession()->GetActiveContext());
} // end HandleSelectionChanged()

// -----------------------------------------------------------------------------

void AddToMSOStateButtonObserver::AutoAttach()
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

void AddToMSOStateButtonObserver::AutoDetach() 
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

void AddToMSOStateButtonObserver::EnableButton(IActiveContext* activeContext) 
{
	InterfacePtr<IControlView> pView(this, IID_ICONTROLVIEW);
	if (!pView) return;

	if (activeContext == nil)
	{
		ASSERT_FAIL("AddToMSOStateButtonObserver::EnableButton - active context nil?");
		return;
	}

	IDocument* theDocument = activeContext->GetContextDocument();

	if (theDocument)
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
		if (iAppearanceSuite && iAppearanceSuite->CanAddItemsAsStates(kMultiStateObjectItemBoss))
			pView->Enable();
		else
			pView->Disable();
	}
	else
	{
		// Disable in no pub state
		pView->Disable();
	}
} // end EnableButton()