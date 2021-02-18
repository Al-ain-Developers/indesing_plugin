//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelStateNameTextValidation.cpp $
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

#include "MSOPanelUtils.h"
#include "CTextDataValidation.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelStateNameTextValidation : public CTextDataValidation
{
public:
	MSOPanelStateNameTextValidation(IPMUnknown *boss);
	~MSOPanelStateNameTextValidation();
	
	virtual bool16 IsEntryLegal();
	virtual PMString GetErrorString();
	virtual bool16 IsBlankEntryAllowed() const { return kFalse; }
};

// =============================================================================
// *** MSOPanelStateNameTextValidation impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(MSOPanelStateNameTextValidation, kMSOPanelStateNameTextValidationImpl)

MSOPanelStateNameTextValidation::MSOPanelStateNameTextValidation(IPMUnknown *boss) :
	CTextDataValidation(boss)
{
} // end constructor

MSOPanelStateNameTextValidation::~MSOPanelStateNameTextValidation()
{
} // end destructor

// -----------------------------------------------------------------------------

bool16 MSOPanelStateNameTextValidation::IsEntryLegal()
{
	InterfacePtr<IPanelControlData> controlData(this, UseDefaultIID());
	IControlView *nameEditField = controlData->FindWidget(kInLineEditEditingWidgetID);
	InterfacePtr<ITextControlData> textData(nameEditField, UseDefaultIID());

	// See if name is empty.
	if (textData->GetString().IsEmpty())
		return kFalse;

	if (MSOPanelUtils::StateExists(textData->GetString()))
		return kFalse;

	return kTrue;
} // end IsEntryLegal()

// -----------------------------------------------------------------------------

PMString MSOPanelStateNameTextValidation::GetErrorString()
{
	IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
	ASSERT(ac != nil);

	InterfacePtr<IPanelControlData> controlData(this, UseDefaultIID());
	IControlView *nameEditField = controlData->FindWidget(kInLineEditEditingWidgetID);
	InterfacePtr<ITextControlData> textData(nameEditField, UseDefaultIID());

	// See if name is empty.
	if (textData->GetString().IsEmpty())
	{
		PMString message("$$$/Error/YouNeedToSpecifyAName", PMString::kTranslateDuringCall);
		return message;
	}
	
	// See if this name already exists.
	if (MSOPanelUtils::StateExists(textData->GetString()))
	{
		PMString message("$$$/Error/YouNeedToSpecifyAUniqueName", PMString::kTranslateDuringCall);
		return message;

	}
	return PMString();
} // end GetErrorString()