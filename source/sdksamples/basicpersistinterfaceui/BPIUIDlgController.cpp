//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterfaceui/BPIUIDlgController.cpp $
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
#include "IActiveContext.h"
#include "ISelectionManager.h"
#include "IStringListControlData.h"
#include "IDropDownListController.h"
#include "IPanelControlData.h"
#include "IControlView.h"
#include "ITextControlData.h"

// General includes
#include "CDialogController.h"

// Project includes
#include "BPIUIID.h"
#include "IBPISuite.h"

/** Implements a dialog controller, IDialogController based on CDialogController,
	that uses IBPISuite to access and change the IBPIData associated with the
	selected objects.

	Contains the code to initialize the widgets in the dialog and to apply
	them when the dialog is dismissed with the OK button. The suite IBPISuite
	is used to access and change the data in the model. By using the suite, 
	this client code is decoupled from the model format.

	@ingroup basicpersistinterface
	
*/
class BPIDlgController : public CDialogController
{
public:
	/**
		Constructor
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BPIDlgController(IPMUnknown* boss);

protected:
	/** Called when the dialog opens to initialise the dialog with data from IBPISuite.
		@param dlgContext context specifies the ISelectionManager to use to query IBPISuite
	*/
	virtual void InitializeDialogFields(IActiveContext* dlgContext);

	/** Called when the dialog is dismissed with the OK button to
		apply changes using IBPISuite.
		@param myContext context specifies the ISelectionManager to use to query IBPISuite
		@param widgetId identifies the widget used to dismiss the dialog.
	*/
	virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BPIDlgController, kBPIUIDlgControllerImpl)

/* Constructor
*/
BPIDlgController::BPIDlgController(IPMUnknown* boss)
: CDialogController(boss)
{
}

/*
*/
void BPIDlgController::InitializeDialogFields(IActiveContext* dlgContext)
{
	do {
		// Set up the widget kBPIUIEditBoxWidgetID.
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if (!panelControlData) {
			break;
		}
		IControlView* controlView = panelControlData->FindWidget(kBPIUIEditBoxWidgetID);
		ASSERT(controlView);
		if (!controlView) {
			break;
		}

		// Query the selection for IBPISuite and use it to get 
		// the data to be used to populate kBPIUIEditBoxWidgetID.
		InterfacePtr<IBPISuite> iBPISuite(dlgContext->GetContextSelection(), UseDefaultIID());
		ASSERT(iBPISuite && iBPISuite->CanApplyBPIData());	
		K2Vector<WideString>	bpiDataValues;
		if (iBPISuite && iBPISuite->CanApplyBPIData()) {
			iBPISuite->GetBPIData(bpiDataValues);
		}
		else {
			controlView->Disable();
			break;
		}

		// Display the values returned by the suite in a drop down list.
		// The suite can return several values and we display all of them
		// so the user can choose one.
		InterfacePtr<IStringListControlData> stringListControlData(controlView, UseDefaultIID());
		ASSERT(stringListControlData);
		if (!stringListControlData) {
			break;
		}
		stringListControlData->Clear(kFalse, kFalse);
		K2Vector<WideString>::iterator iter;
		int32 selectedIndex = IDropDownListController::kBeginning;
		for (iter = bpiDataValues.begin(); iter < bpiDataValues.end(); iter++) {
						
  			PMString currString(*iter);
  			currString.SetTranslatable(kFalse);		
			stringListControlData->AddString(currString, 
							IStringListControlData::kEnd, 	
							kFalse, 	// Invalidate?					
							kFalse);	// Notify of change?
		}	
		if (bpiDataValues.size() > 0) {
			InterfacePtr<IDropDownListController> dropDownListController(controlView, UseDefaultIID());
			ASSERT(dropDownListController);
			if (!dropDownListController) {
				break;
			}
			dropDownListController->Select(selectedIndex,	// ordinal place.
				kFalse,									// Invalidate?
				kFalse									// Notify of change?
			);
		}
		InterfacePtr<ITextControlData> textControlData(controlView, UseDefaultIID());
		ASSERT(textControlData);
		if (!textControlData) {
			break;
		}
		if (bpiDataValues.size() > 0) {
			PMString bpiDataString(bpiDataValues[0]);
			bpiDataString.SetTranslatable(kFalse);
			textControlData->SetString(bpiDataString);
		}
		else {
			textControlData->SetString(PMString(""));
		}

	} while (false);
}

/*
*/
void BPIDlgController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{
	// Use the context you are passed to get the selection manager 
	// to use to query for IBPISuite.
	InterfacePtr<IBPISuite> iBPISuite(myContext->GetContextSelection(), UseDefaultIID());
	ASSERT(iBPISuite && iBPISuite->CanApplyBPIData());	
	if (iBPISuite && iBPISuite->CanApplyBPIData()) {
		// Retrieve the value to be applied from the dialog
		const WideString value(this->GetTextControlData(kBPIUIEditBoxWidgetID));
		// Apply the value to selected objects via the suite.
		iBPISuite->ApplyBPIData(value);
	}
}

// End, BPIDlgController.cpp.




