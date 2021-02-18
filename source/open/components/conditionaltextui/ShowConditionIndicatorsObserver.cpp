//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ShowConditionIndicatorsObserver.cpp $
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
#include "IConditionalTextOptions.h"
#include "IDropDownListController.h"
#include "ISubject.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CObserver.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "PreferenceUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ShowConditionIndicatorsObserver : public CObserver
{
public:
	ShowConditionIndicatorsObserver(IPMUnknown * boss);
	
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

private:
	void	AttachTo(UIDRef workspaceRef);
	void	DetachFromWorkspace();
	void	UpdateListState();

	UIDRef	fCurrentWorkspaceRef;
};

// =============================================================================
// *** ShowConditionIndicatorsObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ShowConditionIndicatorsObserver, kShowConditionIndicatorsObserverImpl);

ShowConditionIndicatorsObserver::ShowConditionIndicatorsObserver(IPMUnknown * boss) :
	CObserver(boss)
{
} // end constructor

// -----------------------------------------------------------------------------

void ShowConditionIndicatorsObserver::AutoAttach()
{
	// Attach to the active context
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, IID_ISUBJECT);
		if (contextSubject && !contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
			contextSubject->AttachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
	}

	InterfacePtr<ISubject> mySubject(this, IID_ISUBJECT);
	if (mySubject && !mySubject->IsAttached(this, IID_ISTRINGLISTCONTROLDATA))
		mySubject->AttachObserver(this, IID_ISTRINGLISTCONTROLDATA);

	IWorkspace* ws = context->GetContextWorkspace();
	if (ws)
		this->AttachTo(::GetUIDRef(ws));
} // end AutoAttach()

// -----------------------------------------------------------------------------

void ShowConditionIndicatorsObserver::AutoDetach()
{
	CObserver::AutoDetach();

	// Detach from whatever workspace we are observing

	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, IID_ISUBJECT);
		if (contextSubject && contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
			contextSubject->DetachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
	}

	InterfacePtr<ISubject> mySubject(this, IID_ISUBJECT);
	if (mySubject && mySubject->IsAttached(this, IID_ISTRINGLISTCONTROLDATA))
		mySubject->DetachObserver(this, IID_ISTRINGLISTCONTROLDATA);

	DetachFromWorkspace();
} // end AutoDetach()

// -----------------------------------------------------------------------------

void ShowConditionIndicatorsObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (protocol == IID_IACTIVECONTEXT)
	{
		InterfacePtr<IActiveContext> newContext(theSubject, UseDefaultIID());
		IWorkspace* newWS = newContext->GetContextWorkspace();
		UIDRef newWorkspaceRef = ::GetUIDRef(newWS);

		if (fCurrentWorkspaceRef != newWorkspaceRef)
		{
			// Detach the old workspace and attach to the new one.
			this->DetachFromWorkspace();
			
			if (newWS)
			{
				this->AttachTo(newWorkspaceRef);
			}
		}
	}
	else if (protocol == IID_ISTRINGLISTCONTROLDATA)
	{
		InterfacePtr<IWorkspace> workspace(fCurrentWorkspaceRef, UseDefaultIID());
		if (theChange.Get() == kPopupChangeStateMessage)
		{
			InterfacePtr<IConditionalTextOptions> options((IConditionalTextOptions*)::QueryPreferences(IConditionalTextOptions::kDefaultIID, workspace));		
			InterfacePtr<IDropDownListController> listController(theSubject, UseDefaultIID());
			IConditionalTextOptions::ConditionIndicatorsMode newSelection;
			switch (listController->GetSelected())
			{
				case 0:
				default:
					newSelection = IConditionalTextOptions::kShow;
					break;
				case 1:
					newSelection = IConditionalTextOptions::kShowAndPrint;
					break;
				case 2:
					newSelection = IConditionalTextOptions::kHide;
					break;
			}

			Utils<Facade::IConditionalTextFacade>()->SetShowConditionIndicators(workspace, newSelection);
		}
	}
} // end Update()

// -----------------------------------------------------------------------------

void ShowConditionIndicatorsObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	if (protocol == IID_ICONDITIONALTEXTOPTIONS)
	{
		this->UpdateListState();
	}
}

// -----------------------------------------------------------------------------

void ShowConditionIndicatorsObserver::AttachTo(UIDRef workspaceRef)
{
	InterfacePtr<ISubject> wsSubject(workspaceRef, IID_ISUBJECT);
	if (wsSubject)
	{
		if (!wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONALTEXTOPTIONS, IID_IOBSERVER))
			wsSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONALTEXTOPTIONS, IID_IOBSERVER);

		fCurrentWorkspaceRef = workspaceRef;

		this->UpdateListState();
	}	
} // end AttachTo()

// -----------------------------------------------------------------------------

void ShowConditionIndicatorsObserver::DetachFromWorkspace()
{
	InterfacePtr<ISubject> wsSubject(fCurrentWorkspaceRef, IID_ISUBJECT);
	if (wsSubject && wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONALTEXTOPTIONS, IID_IOBSERVER))
		wsSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONALTEXTOPTIONS, IID_IOBSERVER);

	if (fCurrentWorkspaceRef != UIDRef(nil,kInvalidUID))
		fCurrentWorkspaceRef = UIDRef(nil,kInvalidUID);
} // end DetachFromWorkspace()

// -----------------------------------------------------------------------------

void ShowConditionIndicatorsObserver::UpdateListState()
{
	InterfacePtr<IConditionalTextOptions> options((IConditionalTextOptions*)::QueryPreferences(IConditionalTextOptions::kDefaultIID, fCurrentWorkspaceRef));		
	if (options)
	{
		InterfacePtr<IDropDownListController> dropDownCntr(this, UseDefaultIID());
		if (dropDownCntr)
		{
			int32 showModeIndex;
			switch (options->GetShowConditionIndicators())
			{
				case IConditionalTextOptions::kShow:
				default:
					showModeIndex = 0;
					break;
				case IConditionalTextOptions::kShowAndPrint:
					showModeIndex = 1;
					break;
				case IConditionalTextOptions::kHide:
					showModeIndex = 2;
					break;
			}
			dropDownCntr->Select(showModeIndex, kTrue, kFalse);
		}
	}
}
