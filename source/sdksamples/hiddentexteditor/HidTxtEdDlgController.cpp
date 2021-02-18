//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentexteditor/HidTxtEdDlgController.cpp $
//  
//  Owner: Adobe Developer Technologies
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

//Interface includes
#include "IIntData.h"
#include "IActiveContext.h"
#include "ISelectionManager.h"
//#include "ISelectionUtils.h"

// API includes
#include "CAlert.h" // For Alert
#include "CDialogController.h"
#include "WideString.h"
#include "PMString.h"

// HiddenText includes
#include "HidTxtID.h"
#include "IHidTxtSuite.h"

// Project includes:
#include "HidTxtEdID.h"

/** Implements the dialog controller(CDialogController) for editing hidden text.
	
	@ingroup hiddentexteditor
*/
class HidTxtEdDlgController : public CDialogController
{
	public:
		HidTxtEdDlgController(IPMUnknown* boss);


	public:

	/** Called when the dialog opens to initialise the dialog.
		The dialog used in this plug-in is shared between Modify and New operations, 
		so the dialog needs to be initialized with proper mode
		@param dlgContext context specifies the ISelectionManager to use to query IBPISuite
	*/
	virtual void InitializeDialogFields(IActiveContext* dlgContext);

	/** This method is called if the dialog settings should be applied to the model. The WidgetID 
			is the ID of the widget that caused this method to be invoked (typically the 'OK' button.)
			In this plug-in, when the OK is hit, we need to determine if the dialog data is entered
			for the New or Modify action, after that, we will use functions in the IHidTxtSuite to
			change the data
		@param myContext context specifies the ISelectionManager to use to query IBPISuite
		@param widgetId identifies the widget used to dismiss the dialog.
	*/
	virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
		
private:
	int32 fMode;
};

/*
*/
CREATE_PMINTERFACE(HidTxtEdDlgController, kHidTxtEdDlgControllerImpl)

/*
*/
HidTxtEdDlgController::HidTxtEdDlgController(IPMUnknown* boss)
: CDialogController(boss)
, fMode(kHidTxtEdCreate)
{
}

/*
*/
void HidTxtEdDlgController::InitializeDialogFields(IActiveContext* dlgContext)
{
	do {
		this->SetTextControlData(kHidTxtEdDialogEditBoxWidgetID, "");
		InterfacePtr<IHidTxtSuite>	hidTxtSuite(dlgContext->GetContextSelection(), UseDefaultIID());
		ASSERT(hidTxtSuite != nil);
		if (hidTxtSuite == nil) {
			break;
		}

		// Determine if the dialog is for new or modify
		InterfacePtr<IIntData> mode(this, UseDefaultIID());
		ASSERT(mode != nil);
		if (mode == nil) {
			break;
		}
		fMode = mode->Get();
		if (fMode == kHidTxtEdCreate) {
			break;
		}
		else if (fMode == kHidTxtEdModify) {
			if (hidTxtSuite->CanGetHiddenText() == kTrue) {
				WideString hiddenTextW;
				hidTxtSuite->GetHiddenText(hiddenTextW);
				// Only show characters that the dialog can render.
				PMString hiddenText;
				for (WideStringConstUTF32Iter iter = hiddenTextW.begin(); iter < hiddenTextW.end(); iter++) {
					if (TextChar::IsK2SpecificChar(*iter) == kFalse) {
						hiddenText.AppendW(*iter);
					}
				}
				hiddenText.SetTranslatable(kFalse);
				this->SetTextControlData(kHidTxtEdDialogEditBoxWidgetID, hiddenText);
			}
		}
		else {
			ASSERT_FAIL("Dialog mode unknown");
			break;
		}
	} while(false);
}

/*
*/
void HidTxtEdDlgController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{
	do {
		InterfacePtr<IHidTxtSuite>	hidTxtSuite(myContext->GetContextSelection(), UseDefaultIID());
		ASSERT(hidTxtSuite != nil);
		if (hidTxtSuite == nil) {
			break;
		}
		if (fMode == kHidTxtEdCreate) {

			if (hidTxtSuite->CanCreateHiddenText() == kTrue) {
				// Retrieve the values set in the dialog
				PMString hiddenText = this->GetTextControlData(kHidTxtEdDialogEditBoxWidgetID);
				WideString hiddenTextW(hiddenText);
				ErrorCode status = hidTxtSuite->CreateHiddenText(hiddenTextW);
				if (status != kSuccess) {
					CAlert::WarningAlert(kHidTxtEdCreateFailedStringKey);
				}
			}
		}
		else if (fMode == kHidTxtEdModify) {
			if (hidTxtSuite->CanModifyHiddenText() == kTrue) {
				// Retrieve the values set in the dialog
				PMString hiddenText = this->GetTextControlData(kHidTxtEdDialogEditBoxWidgetID);
				WideString hiddenTextW(hiddenText);
				ErrorCode status  = hidTxtSuite->ModifyHiddenText(hiddenTextW);
				if (status != kSuccess) {
					CAlert::WarningAlert(kHidTxtEdModifyFailedStringKey);
				}
			}
		}
		
	} while(false);

}

// End, HidTxtEdDlgController.cpp.

