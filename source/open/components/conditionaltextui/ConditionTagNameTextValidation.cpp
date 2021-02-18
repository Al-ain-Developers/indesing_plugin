//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagNameTextValidation.cpp $
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
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"

// ----- Includes -----

#include "CTextDataValidation.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionTagNameTextValidation : public CTextDataValidation
{
public:
	ConditionTagNameTextValidation(IPMUnknown *boss);
	~ConditionTagNameTextValidation();
	
	virtual bool16 IsEntryLegal();
	virtual PMString GetErrorString();
	virtual bool16 IsBlankEntryAllowed() const { return kFalse; }
};

// =============================================================================
// *** ConditionTagNameTextValidation impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(ConditionTagNameTextValidation, kConditionTagNameTextValidationImpl)

ConditionTagNameTextValidation::ConditionTagNameTextValidation(IPMUnknown *boss) :
	CTextDataValidation(boss)
{
} // end constructor

ConditionTagNameTextValidation::~ConditionTagNameTextValidation()
{
} // end destructor

// -----------------------------------------------------------------------------

bool16 ConditionTagNameTextValidation::IsEntryLegal()
{
	IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
	ASSERT(ac != nil);

	InterfacePtr<IPanelControlData> controlData(this, UseDefaultIID());
	IControlView *nameEditField = controlData->FindWidget(kInLineEditEditingWidgetID);
	InterfacePtr<ITextControlData> textData(nameEditField, UseDefaultIID());

	// See if name is empty.
	if (textData->GetString().IsEmpty())
		return kFalse;
	
	// See if this name already exists or reserved.
	WideString nameString(textData->GetString());
	UID conditionUID;
	PMString reservedName("#ConditionTag_Unconditional", PMString::kTranslateDuringCall);
	if (Utils<Facade::IConditionalTextFacade>()->FindCondition(ac->GetContextWorkspace(), nameString, conditionUID) == kSuccess
		 || textData->GetString() == reservedName)
		return kFalse;

	return kTrue;
} // end IsEntryLegal()

// -----------------------------------------------------------------------------

PMString ConditionTagNameTextValidation::GetErrorString()
{
	IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
	ASSERT(ac != nil);

	InterfacePtr<IPanelControlData> controlData(this, UseDefaultIID());
	IControlView *nameEditField = controlData->FindWidget(kInLineEditEditingWidgetID);
	InterfacePtr<ITextControlData> textData(nameEditField, UseDefaultIID());

	// See if name is empty.
	if (textData->GetString().IsEmpty())
	{
		PMString message("#ConditionTag_EmptyNameMsg", PMString::kTranslateDuringCall);
		return message;
	}
	
	// See if this name already exists or reserved.
	WideString nameString(textData->GetString());
	UID conditionUID;
	PMString reservedName("#ConditionTag_Unconditional", PMString::kTranslateDuringCall);
	if (Utils<Facade::IConditionalTextFacade>()->FindCondition(ac->GetContextWorkspace(), nameString, conditionUID) == kSuccess
		 || textData->GetString() == reservedName)
	{
		PMString message("#ConditionTag_NameInUseMsg", PMString::kTranslateDuringCall);
		return message;

	}
	return PMString();
} // end GetErrorString()