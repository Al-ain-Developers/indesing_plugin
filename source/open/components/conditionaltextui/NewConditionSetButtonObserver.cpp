//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/NewConditionSetButtonObserver.cpp $
//  
//  Owner: Kevin Van Wiel
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
#include "IApplication.h"
#include "IBoolData.h"
#include "IConditionTag.h"
#include "IConditionTagList.h"
#include "IDialog.h"
#include "IDialogMgr.h"
#include "IDocument.h"
#include "ISubject.h"
#include "ITriStateControlData.h"
#include "IWorkspace.h"
#include "IWStringData.h"

// ----- Includes -----
#include "CObserver.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"

// ----- Utility files -----
#include "IConditionalTextFacade.h"
#include "IConditionalTextUIFacade.h"
#include "IDialogUtils.h"
#include "IEventUtils.h"
#include "IInCopySharedUtils.h"

// ----- ID.h files -----
#include "ConditionalTextUIID.h"
#include "ConditionalTextUIDefs.h"
#include "InCopyCoreID.h"
#include "LayoutUIID.h"

using namespace Facade;

/******************************************************************************
 * class NewConditionSetButtonObserver
 ******************************************************************************/
class NewConditionSetButtonObserver : public CObserver
{
public:
	NewConditionSetButtonObserver(IPMUnknown* boss);
	virtual ~NewConditionSetButtonObserver();

	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	
private:
	bool16 DoSetNameDialog(WideString &setName); 
	void EnableButton(IActiveContext* activeContext); 

};

CREATE_PMINTERFACE(NewConditionSetButtonObserver, kNewConditionSetButtonObserverImpl)

/******************************************************************************
 * NewConditionSetButtonObserver::NewConditionSetButtonObserver
 ******************************************************************************/
NewConditionSetButtonObserver::NewConditionSetButtonObserver(IPMUnknown* boss): CObserver(boss) 
{
}

/******************************************************************************
 * NewConditionSetButtonObserver::~NewConditionSetButtonObserver
 ******************************************************************************/
NewConditionSetButtonObserver::~NewConditionSetButtonObserver()
{
}

/******************************************************************************
 * NewConditionSetButtonObserver::Update
 ******************************************************************************/
void NewConditionSetButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) 
{
	if (theChange == kTrueStateMessage)
	{
		IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
		IWorkspace *workspace = context->GetContextWorkspace();
		
		WideString tagSetString;
		Utils<IConditionalTextFacade>()->GetFirstAvailableDefaultConditionSetName(workspace, tagSetString);

		if (DoSetNameDialog(tagSetString))
		{
			IDataBase *db = ::GetDataBase(workspace);
			InterfacePtr<IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
			
			IConditionalTextFacade::ConditionSetElementList tags;
			for (int32 i = 0; i < tagList->GetCount(); i++)
			{
				InterfacePtr<IConditionTag> tag(db, tagList->GetNthCondition(i), UseDefaultIID());
				IConditionalTextFacade::ConditionSetElement newTag(::GetUID(tag), tag->IsVisible());
				tags.push_back(newTag);
			}
		
			UID tagSetUID = kInvalidUID;
			if (Utils<Facade::IConditionalTextFacade>()->CreateConditionSet(workspace, tagSetString, tags, &tagSetUID) == kSuccess) 
			{
				Utils<Facade::IConditionalTextFacade>()->SetActiveConditionSet(workspace, tagSetUID);
			}
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
}

/******************************************************************************
 * NewConditionSetButtonObserver::AutoAttach
 ******************************************************************************/
void NewConditionSetButtonObserver::AutoAttach()
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
}

/******************************************************************************
 * NewConditionSetButtonObserver::AutoDetach
 ******************************************************************************/
void NewConditionSetButtonObserver::AutoDetach() 
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
}

/******************************************************************************
 * ConditionSetDropDownObserver::DoSetNameDialog
 ******************************************************************************/
bool16 NewConditionSetButtonObserver::DoSetNameDialog(WideString &setName)
{
	bool16 success = kTrue;
	
	const RsrcID kDialogRsrcID = kConditionSetNameDialogRsrcID;
	const IDialog::DialogType kDialogType = IDialog::kMovableModal;
	const PMLocaleId nLocale = LocaleSetting::GetLocale();
	const RsrcSpec aSpec(nLocale, kConditionalTextUIPluginID, kViewRsrcType,  kDialogRsrcID, kTrue);

	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(app, UseDefaultIID());
	
	IDialog *dialog = dialogMgr->CreateNewDialog(aSpec, kDialogType);
	ASSERT_MSG(dialog != nil, "NewConditionSetButtonObserver::DoSetNameDialog - can't create dialog!");

	IControlView* dialogView = dialog->GetDialogPanel();
	
	InterfacePtr<IWStringData> nameData(dialogView, UseDefaultIID());
	nameData->Set(setName);
	
	dialog->Open();
	dialog->WaitForDialog();
	
	// the dialog controller should set the bool data and string data for us.
	InterfacePtr<IBoolData> boolData(dialogView, UseDefaultIID());
	success = boolData->GetBool();
	
	if (success) setName = nameData->GetString();
	
	return success;
}

// -----------------------------------------------------------------------------

void NewConditionSetButtonObserver::EnableButton(IActiveContext* activeContext) 
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