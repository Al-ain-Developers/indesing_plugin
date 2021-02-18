//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/ButtonPDFOptionsDialogController.cpp $
//  
//  Owner: Michele Stutzman
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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

#include "IBoolData.h"
#include "IGraphicAttributeSuite.h"
#include "IIntData.h"
#include "IPanelControlData.h"
#include "ITriStateControlData.h"

// ----- Includes -----

#include "CDialogController.h"
#include "FormFieldUIDefs.h"

// ----- Utility files -----

#include "AttributesUtils.h"
#include "IGraphicStateUtils.h"

// ----- ID.h files -----

#include "AppUIID.h"
#include "FormFieldUIID.h"


class ButtonPDFOptionsDialogController : public CDialogController
{
public:
	ButtonPDFOptionsDialogController(IPMUnknown* boss);
	void InitializeDialogFields( IActiveContext* dlgContext);
	void ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId);
};

// =============================================================================
// *** ButtonPDFOptionsDialogController impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ButtonPDFOptionsDialogController, kButtonPDFOptionsDialogControllerImpl)

ButtonPDFOptionsDialogController::ButtonPDFOptionsDialogController(IPMUnknown* boss) : 
	CDialogController(boss)
{
} // end constructor

// -----------------------------------------------------------------------------

void ButtonPDFOptionsDialogController::InitializeDialogFields( IActiveContext* dlgContext)
{
	InterfacePtr<IGraphicAttributeSuite> iGfxAttrSuite ( Utils<IGraphicStateUtils>()->QueryActiveGraphicAttrSuite ());

	bool16 bPrintable = kFalse;
	this->SetTriStateControlData(kButtonPDFPrintableCheckBoxWID,
		AttributesUtils::HasUniqueValue(iGfxAttrSuite, kFormPrintVisibleAttrBoss, &bPrintable) && bPrintable);

	PMString description;
	this->SetTextControlData(kButtonPDFDescriptionWID, AttributesUtils::HasUniqueValue(iGfxAttrSuite, kFormDescriptionAttrBoss, &description) ? description : PMString());
}

// -----------------------------------------------------------------------------

void ButtonPDFOptionsDialogController::ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId)
{
	InterfacePtr<IGraphicAttributeSuite> iGfxAttrSuite ( Utils<IGraphicStateUtils>()->QueryActiveGraphicAttrSuite ());

	AttributesUtils::SetBoolValue( "$$$/Dialog/CmdName/ChangeFormSettings", iGfxAttrSuite, kFormPrintVisibleAttrBoss, this->GetTriStateControlData(kButtonPDFPrintableCheckBoxWID) );
	AttributesUtils::SetStringValue( "$$$/Dialog/CmdName/ChangeFormSettings", iGfxAttrSuite, kFormDescriptionAttrBoss, this->GetTextControlData(kButtonPDFDescriptionWID) );
}
