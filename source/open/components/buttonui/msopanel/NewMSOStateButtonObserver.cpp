//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/NewMSOStateButtonObserver.cpp $
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
#include "IFormFieldSuite.h"
#include "IPanelControlData.h"
#include "ISelectionMessages.h"
#include "ISubject.h"
#include "ITreeViewMgr.h"

// ----- Includes -----

#include "SelectionObserver.h"

// ----- Utility files -----

#include "EventUtilities.h"
#include "FormFieldUIUtils.h"
#include "MSOPanelUtils.h"
#include "IPalettePanelUtils.h"

// ----- ID.h files -----

#include "FormFieldID.h"
#include "FormFieldUIID.h"
#include "GraphicStylesID.h"


class NewMSOStateButtonObserver : public ActiveSelectionObserver
{
public:
	NewMSOStateButtonObserver(IPMUnknown* boss);
	virtual ~NewMSOStateButtonObserver();

	virtual void AutoAttach();
	virtual void AutoDetach();

	virtual		void	HandleSelectionUpdate(const ClassID&, ISubject*, const PMIID&, void*);
	virtual		void	HandleSelectionChanged(const ISelectionMessage* iSelectionMessage);
	virtual		void	HandleSelectionAttributeChanged(const ISelectionMessage* iSelectionMessage);

private:
	void EnableButton(IActiveContext* activeContext);
};

// =============================================================================
// *** NewConditionTagButtonObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(NewMSOStateButtonObserver, kNewMSOStateButtonObserverImpl)

NewMSOStateButtonObserver::NewMSOStateButtonObserver(IPMUnknown* boss): ActiveSelectionObserver(boss) 
{
} // end constructor


NewMSOStateButtonObserver::~NewMSOStateButtonObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void NewMSOStateButtonObserver::HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* data)
{
	ActiveSelectionObserver::HandleSelectionUpdate(theChange, theSubject, protocol, data);

	if (protocol == IID_ITRISTATECONTROLDATA && theChange == kTrueStateMessage)
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
		if (iAppearanceSuite)
		{
			InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
			if (iFormFieldSuite && iFormFieldSuite->CanCreateFieldFromSelection(kMultiStateObjectItemBoss))
			{
				MSOPanelUtils::CreateMSO(::IsOptionAltKeyPressed() ? IAppearanceSuite::kHandleItemsAsAGroup : IAppearanceSuite::kHandleItemsIndividually);
			}
			else
			{
				if (iAppearanceSuite->CanAddItemsAsStates(kMultiStateObjectItemBoss))
				{
					ErrorCode err = iAppearanceSuite->AddItemsAsStates(kMultiStateObjectItemBoss, ::IsOptionAltKeyPressed() ? IAppearanceSuite::kAddAllItemsToOneNewState : IAppearanceSuite::kAddItemsAsIndividualStates);
					if (err == kSuccess)
						iAppearanceSuite->SelectAssociatedAppearanceItemOfType(kMultiStateObjectItemBoss);
				}
				else
				{
					Form::AppearanceState selectedAppearance = MSOPanelUtils::GetSelectedAppearance();
					if (selectedAppearance != Form::kStateInvalid)
						MSOPanelUtils::CreateNewState(MSOPanelUtils::kBelowActive, selectedAppearance);
				}
			}
		}

		EnableButton(GetExecutionContextSession()->GetActiveContext());
	}
} // end HandleSelectionUpdate()

// -----------------------------------------------------------------------------

void NewMSOStateButtonObserver::HandleSelectionChanged(const ISelectionMessage* iSelectionMessage)
{
	EnableButton(GetExecutionContextSession()->GetActiveContext());
} // end HandleSelectionChanged()

// -----------------------------------------------------------------------------

void NewMSOStateButtonObserver::HandleSelectionAttributeChanged(const ISelectionMessage* iSelectionMessage)
{
	EnableButton(GetExecutionContextSession()->GetActiveContext());
} // end HandleSelectionAttributeChanged()

// -----------------------------------------------------------------------------

void NewMSOStateButtonObserver::AutoAttach()
{
	ActiveSelectionObserver::AutoAttach();

	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

	EnableButton(GetExecutionContextSession()->GetActiveContext());
} // end AutoAttach()

// -----------------------------------------------------------------------------

void NewMSOStateButtonObserver::AutoDetach() 
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);

	ActiveSelectionObserver::AutoDetach();
} // end AutoDetach()

// -----------------------------------------------------------------------------

void NewMSOStateButtonObserver::EnableButton(IActiveContext* activeContext) 
{
	if (activeContext == nil)
	{
		ASSERT_FAIL("NewMSOStateButtonObserver::EnableButton - active context nil?");
		return;
	}

	InterfacePtr<IControlView> pView(this, IID_ICONTROLVIEW);
	if (!pView) return;

	IDocument* theDocument = activeContext->GetContextDocument();

	if (theDocument)
	{
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		if (iFormFieldSuite && iFormFieldSuite->CanCreateFieldFromSelection(kMultiStateObjectItemBoss))
		{
			// Enable to create new MSO
			pView->Enable();
		}
		else
		{
			// Enable to create new state for existing MSO or disable.
			InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
			if (iAppearanceSuite && (MSOPanelUtils::GetSelectedAppearance() != Form::kStateInvalid ||
				(iAppearanceSuite->CanAddItemsAsStates(kMultiStateObjectItemBoss))))
			{
				pView->Enable();
			}
			else
				pView->Disable();
		}
	}
	else
	{
		// Disable in no pub state
		pView->Disable();
	}
} // end EnableButton()

