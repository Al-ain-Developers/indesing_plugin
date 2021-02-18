//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/TxtExpDialogController.cpp $
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
#include "IStringListControlData.h"
#include "IDropDownListController.h"
#include "IIntData.h"

// General includes:
#include "CreateObject.h"
#include "CDialogController.h"
#include "SystemUtils.h"
#include "TextChar.h"
#include "LocaleSetting.h"
#include "PMLocaleId.h"

// Project includes:
#include "TxtExpID.h"
#include "TxtExpUtils.h"


/** TxtExpDialogController
	Methods allow for the initialization, validation, and application of dialog widget values.
  
	Implements IDialogController based on the partial implementation CDialogController. 
	@ingroup textexportfilter
	
*/
class TxtExpDialogController : public CDialogController
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TxtExpDialogController(IPMUnknown* boss) : CDialogController(boss) {}

		/** 
			Destructor.
		*/
		virtual ~TxtExpDialogController() {}

protected:
		/**
			Initialize each widget in the dialog with its default value.
			Called when the dialog is opened.
		*/
		virtual void InitializeDialogFields(IActiveContext* context);

		/**
			Validate the values in the widgets. 
			By default, the widget with ID kOKButtonWidgetID causes 
			ValidateFields to be called. When all widgets are valid, 
			ApplyFields will be called.			
			@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.

		*/
		virtual WidgetID ValidateDialogFields(IActiveContext* myContext);

		/**
			Retrieve the values from the widgets and act on them.
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
		
		/** Called when the user clicks the "cancel" button.
		*/
		virtual void UserCancelled(void);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(TxtExpDialogController, kTxtExpDialogControllerImpl)

/* ApplyFields
*/
void TxtExpDialogController::InitializeDialogFields(IActiveContext* context)
{
	CDialogController::InitializeDialogFields(context);

	do {

		InterfacePtr<IStringListControlData> encodingList(this->QueryListControlDataInterface(kTxtExpDropdownWidgetId));
		if (encodingList == nil)
		{
			ASSERT_FAIL("TxtExpDialogController::InitializeFields() : Can't get encodingList");
			break;
		}
	
		// Clear and invalidate the drop list
		encodingList->Clear();
		// initialize widget values using string keys
		encodingList->AddString(PMString(kTxtExpEncodingASCIIKey));
		encodingList->AddString(PMString(kTxtExpEncodingUNICODEKey));

		if (LocaleSetting::GetLocale().GetFeatureSetId() == kInDesignJapaneseFS)
		{
			encodingList->AddString(PMString(kTxtExpEncodingShiftJISKey));
			encodingList->AddString(PMString(kTxtExpEncodingJISKey));
		}
	
		// Get a pointer to the controller for the drop list
		InterfacePtr<IDropDownListController> encodingListController (encodingList, UseDefaultIID());
		if (encodingListController == nil)
		{
			ASSERT_FAIL("TxtExpDialogController::InitializeFields() : Can't get encodingListController");
			break;
		}
	
		// set selection to last selected item
		IIntData* encoding = TxtExpUtils::GetEncodingIntData();
	
		int32 value = encoding->Get();
		if (value == (int32)ITxtExpFileWriter::kTxtExpEncodingInvalid)
		{
			// the encoding data hasn't been set before
			// for the dialog, default to ASCII
			value = (int32)ITxtExpFileWriter::kTxtExpEncodingASCII;
		}
		encodingListController->Select(value, kTrue, kFalse);

	} while (kFalse);

}

/* ValidateFields
*/
WidgetID TxtExpDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	WidgetID result = CDialogController::ValidateDialogFields(myContext);

	// Nothing else to do...

	return result;
}


/* ApplyFields
*/
void TxtExpDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId) 
{
	// user clicked OK -  Get the encoding code from the drop down list.

	do {
		InterfacePtr<IStringListControlData> encodingList(this->QueryListControlDataInterface(kTxtExpDropdownWidgetId));
		if (!encodingList)
		{
			ASSERT_FAIL("TxtExpDialogController::ApplyFields : Can't get encodingList");
			break;
		}

		InterfacePtr<IDropDownListController> encodingListController (encodingList, UseDefaultIID());
		if (!encodingListController)
		{
			ASSERT_FAIL("TxtExpDialogController::ApplyFields : Can't get encodingListController");
			break;
		}

		// get the intdata variable to pass back to the filter
        IIntData* encoding = TxtExpUtils::GetEncodingIntData();
        if (!encoding)
        {
            ASSERT_FAIL("TxtExpDialogController::ApplyFields : 'encoding' not created!");
            break;
        }
		// set the value from the actual selected value in the drop down list
        int32 value = encodingListController->GetSelected();
		encoding->Set(value);
        
        // just to check that it got set correctly (for debugging)
		TRACEFLOW("TextExportFilter","TxtExpDialogController::ApplyFields : encoding IntData is %d\n", encoding->Get());

	} while (kFalse);
		
}

/* UserCancelled
*/
void TxtExpDialogController::UserCancelled(void) 
{
	do 
	{
		// get the intdata variable to pass back to the filter
        IIntData* encoding = TxtExpUtils::GetEncodingIntData();
        if (!encoding)
        {
            ASSERT_FAIL("TxtExpDialogController::UserCancelled : 'encoding' not created!");
            break;
        }
		// set the value to Invalid
		encoding->Set(ITxtExpFileWriter::kTxtExpEncodingInvalid);
        
        // just to check that it got set correctly (for debugging)
		TRACEFLOW("TextExportFilter","TxtExpDialogController::ApplyFields : encoding IntData is %d\n", encoding->Get());

	} while (kFalse);
}


//  Generated by Dolly build 17: template "Dialog".
// End, TxtExpDialogController.cpp.




