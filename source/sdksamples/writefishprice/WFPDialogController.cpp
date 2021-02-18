//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/writefishprice/WFPDialogController.cpp $
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

// Interface includes:
#include "IActiveContext.h"
#include "ITextEditSuite.h"  			// STEP 7.1
#include "ISelectionManager.h"			// STEP 7.1
#include "IPanelControlData.h" 			// STEP 9.1
#include "IDropDownListController.h" 	// STEP 9.1

// General includes:
#include "CDialogController.h"

// Project includes:
#include "WFPID.h"

/** WFPDialogController
	Methods allow for the initialization, validation, and application of dialog widget
	values.
	Implements IDialogController based on the partial implementation CDialogController.

	
	@ingroup writefishprice
*/
class WFPDialogController : public CDialogController
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		WFPDialogController(IPMUnknown* boss) : CDialogController(boss) {}

		/** Destructor.
		*/
		virtual ~WFPDialogController() {}

		/** Initialize each widget in the dialog with its default value.
			Called when the dialog is opened.
		*/
	    virtual void InitializeDialogFields(IActiveContext* dlgContext);

		/** Validate the values in the widgets.
			By default, the widget with ID kOKButtonWidgetID causes
			ValidateFields to be called. When all widgets are valid,
			ApplyFields will be called.
			@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.

		*/
	       virtual WidgetID ValidateDialogFields(IActiveContext* myContext);


		/** Retrieve the values from the widgets and act on them.
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
};

CREATE_PMINTERFACE(WFPDialogController, kWFPDialogControllerImpl)

/* ApplyFields
*/
void WFPDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	CDialogController::InitializeDialogFields(dlgContext);

	// STEP 9.1  - BEGIN
	do {
		// Get current panel control data.
		InterfacePtr<IPanelControlData> pPanelData(QueryIfNilElseAddRef(nil));
		if (pPanelData == nil)
		{
			ASSERT_FAIL("WFPDialogController::InitializeFields: PanelControlData is nil!");
			break;
		}
		else
		{
			// Find dropdown list menu control view from panel data.
			IControlView* pDropDownListControlView = pPanelData->FindWidget(kWFPDropDownListWidgetID);
			if (pDropDownListControlView == nil)
			{
				// Is the widget on the dialog?
				ASSERT_FAIL("WFPDialogController::InitializeFields: DDListCtrlView is nil!");
				break;
			}
			
			// Get IDropDownListController interface pointer.
			InterfacePtr<IDropDownListController> pDropDownListController(pDropDownListControlView, UseDefaultIID());
			if (pDropDownListController == nil)
			{
				// Is the controller available?
				ASSERT_FAIL("WFPDialogController::InitializeFields: DDListController is nil!");
				break;
			}
			
			// Select the element at the given position in the list.
			pDropDownListController->Select(0);
			
			// Initialize TextEditBox.
			PMString InitialString("");
			SetTextControlData(kWFPTextEditBoxWidgetID, InitialString);
		}
	} while (kFalse);
	// STEP 9.1  - END

}

/* ValidateFields
*/
WidgetID WFPDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	WidgetID result = CDialogController::ValidateDialogFields(myContext);
	// Put code to validate widget values here.
	return result;
}

/* ApplyFields
*/
void WFPDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{
	// STEP 5.1 - BEGIN
	// DropDownList result string.
	PMString resultString;
	
	//Get Selected text of DropDownList.
	resultString = this->GetTextControlData(kWFPDropDownListWidgetID);
	resultString.Translate(); // Look up our string and replace.
	// STEP 5.1 - END

	// STEP 6.1 - BEGIN
	// Get the editbox list widget string.
	PMString editBoxString = this->GetTextControlData(kWFPTextEditBoxWidgetID);
	// STEP 6.1 - END

	// STEP 6.2 - BEGIN
	PMString moneySign(kWFPStaticTextKey);
	moneySign.Translate(); // Look up our string and replace.
	
	resultString.Append('\t'); // Append tab code.
	resultString.Append(moneySign);
	resultString.Append(editBoxString);
	resultString.Append('\r'); // Append return code.
	// STEP 6.2 - END

	// STEP 7.1 - BEGIN
    if (myContext == nil)
	{
		ASSERT(myContext);
		return;
	}
	// Insert resultString to TextFrame.
    InterfacePtr<ITextEditSuite> textEditSuite(myContext->GetContextSelection(), UseDefaultIID());

	// STEP 7.2 - BEGIN
    if (textEditSuite && textEditSuite->CanEditText())
    {
		// STEP 7.3 - BEGIN
        ErrorCode status = textEditSuite->InsertText(WideString(resultString));
        ASSERT_MSG(status == kSuccess, "WFPDialogController::ApplyDialogFields: can't insert text"); 
		// STEP 7.3 - END
    }
	// STEP 7.2 - END
}

//  Code generated by DollyXs code generator
