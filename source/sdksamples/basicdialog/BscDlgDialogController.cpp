//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdialog/BscDlgDialogController.cpp $
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

// General includes:
#include "CDialogController.h"
#include "SystemUtils.h"

// Project includes:
#include "BscDlgID.h"

/** Implements IDialogController based on the partial implementation CDialogController; 
	its methods allow for the initialization, validation, and application of dialog widget values.
  
	The methods take an additional parameter for 3.0, of type IActiveContext.
	See the design document for an explanation of the rationale for this
	new parameter and the renaming of the methods that CDialogController supports.
	
	
	@ingroup basicdialog
	
*/
class BscDlgDialogController : public CDialogController
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscDlgDialogController(IPMUnknown* boss) : CDialogController(boss) {}

		/**
			Initializes each widget in the dialog with its default value.
			Called when the dialog is opened.
			@param dlgContext
		*/
		virtual void InitializeDialogFields( IActiveContext* dlgContext);

		/**
			Validate the values in the widgets. 
			By default, the widget with ID kOKButtonWidgetID causes 
			this method to be called. When all widgets are valid, 
			ApplyFields will be called.		
			@param myContext
			@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.

		*/
		virtual WidgetID ValidateDialogFields( IActiveContext* myContext);

		/**
			Retrieve the values from the widgets and act on them.
			@param myContext
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(BscDlgDialogController, kBscDlgDialogControllerImpl)

/* ApplyFields
*/
void BscDlgDialogController::InitializeDialogFields( IActiveContext* dlgContext) 
{
	#pragma unused(dlgContext)
	// Put code to initialize widget values here.
}

/* ValidateFields
*/
WidgetID BscDlgDialogController::ValidateDialogFields( IActiveContext* myContext) 
{
	#pragma unused(myContext)
	WidgetID result = kNoInvalidWidgets;

	// Put code to validate widget values here.

	return result;
}

/* ApplyFields
*/
void BscDlgDialogController::ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId) 
{
	#pragma unused(myContext,widgetId)
	// Replace with code that gathers widget values and applies them.
	SystemBeep();  
}

// End, BscDlgDialogController.cpp.



