//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/NewConditionTagButtonObserver.cpp $
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
#include "IDocument.h"
#include "ISubject.h"
#include "ITriStateControlData.h"

// ----- Includes -----

#include "CObserver.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "IConditionalTextUIFacade.h"
#include "IEventUtils.h"
#include "IInCopySharedUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"
#include "InCopyCoreID.h"
#include "LayoutUIID.h"

class NewConditionTagButtonObserver : public CObserver
{
public:
	NewConditionTagButtonObserver(IPMUnknown* boss);
	virtual ~NewConditionTagButtonObserver();

	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) ; 

private:
	void EnableButton(IActiveContext* activeContext);
};

// =============================================================================
// *** NewConditionTagButtonObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(NewConditionTagButtonObserver, kNewConditionTagButtonObserverImpl)

NewConditionTagButtonObserver::NewConditionTagButtonObserver(IPMUnknown* boss): CObserver(boss) 
{
} // end constructor


NewConditionTagButtonObserver::~NewConditionTagButtonObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void NewConditionTagButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) 
{
	if (theChange == kTrueStateMessage)
	{
		IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
		if (::IsOptionAltKeyPressed())
		{
			// Just create a default tag
			// This is different from other panels by design because it makes the feature more usable.
			// Other panels should change too ;).
			Utils<Facade::IConditionalTextFacade>()->CreateCondition(context->GetContextWorkspace());
		}
		else
		{
			// New dialog
			// This is different from other panels by design because it makes the feature more usable.
			// Other panels should change too ;).
			Utils<Facade::IConditionalTextUIFacade>()->DoConditionOptionsDialog(context->GetContextWorkspace(), kInvalidUID);
		}
	}
 	else if (protocol == IID_IACTIVECONTEXT)  //this protocol sends IID instead of cmdID
 	{
 		const PMIID& what = *((const PMIID*)changedBy);
 		if (what == IID_IDOCUMENT || what == IID_ILAYOUTCONTROLDATA)
 		{
			IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
			EnableButton(activeContext);
 		}
 	}
 	else if (protocol == IID_IDOCUMENT)
 	{
 		// check the SaveAs
 		if (theChange == kSetStandAloneCmdBoss)
 		{		
 			IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
			EnableButton(activeContext);
		}
 	}
} // end Update()

// -----------------------------------------------------------------------------

void NewConditionTagButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

	// active context
 	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
 	InterfacePtr<ISubject> acSubject(activeContext, IID_ISUBJECT);

 	if (acSubject && !acSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
 	{
 		acSubject->AttachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
		EnableButton(activeContext);
 	}

 	if (acSubject && !acSubject->IsAttached(this, IID_IDOCUMENT))
 		acSubject->AttachObserver(this, IID_IDOCUMENT);
} // end AutoAttach()

// -----------------------------------------------------------------------------

void NewConditionTagButtonObserver::AutoDetach() 
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);

	// active context
 	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
 	InterfacePtr<ISubject> acSubject(activeContext, IID_ISUBJECT);

 	if (acSubject && acSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
 		acSubject->DetachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);

	if (acSubject && acSubject->IsAttached(this, IID_IDOCUMENT))
 		acSubject->DetachObserver(this, IID_IDOCUMENT);
} // end AutoDetach()

// -----------------------------------------------------------------------------

 void NewConditionTagButtonObserver::EnableButton(IActiveContext* activeContext) 
 {
	 if (activeContext == nil)
	 {
		 ASSERT_FAIL("NewConditionTagButtonObserver::EnableButton - active context nil?");
		 return;
	 }

	 IDocument* theDocument = activeContext->GetContextDocument();

	 if (theDocument)
	 {
		 if (!Utils<IInCopySharedUtils>()->StylesEditable(::GetDataBase(theDocument)))
			{
				InterfacePtr<IControlView> pView(this, IID_ICONTROLVIEW);
				if (pView)
					pView->Disable();
			}
		 else
			{
				InterfacePtr<IControlView> pView(this, IID_ICONTROLVIEW);
				if (pView)
					pView->Enable();
			}
	 }
	 else
	 {
		 InterfacePtr<IControlView> pView(this, IID_ICONTROLVIEW);
		 if (pView)
			 pView->Enable();
	 }
 } // end EnableButton()
