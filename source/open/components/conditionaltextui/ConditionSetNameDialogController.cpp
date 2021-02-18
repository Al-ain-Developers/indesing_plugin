//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionSetNameDialogController.cpp $
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
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IBoolData.h"
#include "IActiveContext.h"
#include "IWStringData.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "IControlView.h"
#include "IConditionalTextFacade.h"
#include "IUIDData.h"

// ----- Includes -----
#include "CDialogController.h"
#include "UIDList.h"

// ----- Utility files -----
#include "CAlert.h"

// ----- ID.h files -----
#include "ConditionalTextUIID.h"

using namespace Facade;
/******************************************************************************
 * class ConditionSetNameDialogController
 ******************************************************************************/
class ConditionSetNameDialogController : public CDialogController
{
public:
	ConditionSetNameDialogController(IPMUnknown *boss);
	virtual	~ConditionSetNameDialogController();

	virtual void InitializeDialogFields(IActiveContext* dlgContext);
	virtual WidgetID ValidateDialogFields(IActiveContext* myContext);
	virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
	virtual void UserCancelled();
};

CREATE_PMINTERFACE(ConditionSetNameDialogController, kConditionSetNameDialogControllerImpl)

/******************************************************************************
 * ConditionSetNameDialogController::ConditionSetNameDialogController
 ******************************************************************************/
ConditionSetNameDialogController::ConditionSetNameDialogController(IPMUnknown *boss) :
	CDialogController(boss)
{
}

/******************************************************************************
 * ConditionSetNameDialogController::~ConditionSetNameDialogController
 ******************************************************************************/
ConditionSetNameDialogController::~ConditionSetNameDialogController()
{
}

/******************************************************************************
 * ConditionSetNameDialogController::InitializeDialogFields
 ******************************************************************************/
void ConditionSetNameDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	InterfacePtr<IWStringData> nameData(this, UseDefaultIID());
	InterfacePtr<IPanelControlData> controlData(this, UseDefaultIID());
	
	IControlView *nameEditField = controlData->FindWidget(kConditionSetNameEditBoxWidgetID);
	InterfacePtr<ITextControlData> textData(nameEditField, UseDefaultIID());
	PMString initialName(nameData->GetString());
	initialName.SetTranslatable(kFalse);
	textData->SetString(initialName);
	
}

/******************************************************************************
 * ConditionSetNameDialogController::ApplyDialogFields
 ******************************************************************************/
void ConditionSetNameDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId) 
{
	InterfacePtr<IPanelControlData> controlData(this, UseDefaultIID());
	IControlView *nameEditField = controlData->FindWidget(kConditionSetNameEditBoxWidgetID);
	InterfacePtr<ITextControlData> textData(nameEditField, UseDefaultIID());
	
	InterfacePtr<IWStringData> nameData(this, UseDefaultIID());
	nameData->Set(WideString(textData->GetString()));

	InterfacePtr<IBoolData> pressedOKData(this, UseDefaultIID());
	pressedOKData->Set(kTrue);

}

/******************************************************************************
 * ConditionSetNameDialogController::ValidateDialogFields
 ******************************************************************************/
WidgetID ConditionSetNameDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	InterfacePtr<IPanelControlData> controlData(this, UseDefaultIID());
	IControlView *nameEditField = controlData->FindWidget(kConditionSetNameEditBoxWidgetID);
	InterfacePtr<ITextControlData> textData(nameEditField, UseDefaultIID());
	if (textData->GetString().IsEmpty())
	{
		PMString message("#InvalidSetName");
		message.Translate();
		CAlert::WarningAlert(message);
		return kConditionSetNameEditBoxWidgetID;
	}
	
	// See if this name already exists if so report the error.
	InterfacePtr<IUIDData> setData(this, UseDefaultIID());
	WideString nameString(textData->GetString());
	UID tagSetUID;
	if (Utils<IConditionalTextFacade>()->FindConditionSet(myContext->GetContextWorkspace(), nameString, tagSetUID) == kSuccess && tagSetUID != setData->Get())
	{
		PMString message("#DuplicateSetName");
		message.Translate();
		CAlert::WarningAlert(message);
		return kConditionSetNameEditBoxWidgetID;
	}
	
	return kNoInvalidWidgets;
}

/******************************************************************************
 * ConditionSetNameDialogController::UserCancelled
 ******************************************************************************/
void ConditionSetNameDialogController::UserCancelled()
{
	InterfacePtr<IBoolData> pressedOKData(this, UseDefaultIID());
	pressedOKData->Set(kFalse);
} 
