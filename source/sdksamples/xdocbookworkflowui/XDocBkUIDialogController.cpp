//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflowui/XDocBkUIDialogController.cpp $
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
#include "IObserver.h"
#include "IPanelControlData.h"
#include "IXDocBkFacade.h"

// General includes:
#include "CDialogController.h"
#include "Utils.h"

// Project includes:
#include "XDocBkUIID.h"

/** XDocBkUIDialogController
	Methods allow for the initialization, validation, and application of dialog widget values.
  
	Implements IDialogController based on the partial implementation CDialogController. 
	@ingroup xdocbookworkflowui
	
*/
class XDocBkUIDialogController : public CDialogController
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	XDocBkUIDialogController(IPMUnknown* boss) : CDialogController(boss) {}

	/** Destructor.
	*/
	virtual ~XDocBkUIDialogController() {}

	/** Initializes each widget in the dialog with its default value.
		Called when the dialog is opened.
		@param dlgContext
	*/
	virtual void InitializeDialogFields(IActiveContext* dlgContext);

	/**	Validate the values in the widgets. 
		By default, the widget with ID kOKButtonWidgetID causes 
		this method to be called. When all widgets are valid, 
		ApplyFields will be called.		
		@param myContext
		@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.
	*/
	virtual WidgetID ValidateDialogFields(IActiveContext* myContext);

	/**	Retrieve the values from the widgets and act on them.
		@param myContext
		@param widgetId identifies the widget on which to act.
	*/
	virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);

	/** Called during the process of closing the dialog, 
		an opportunity to do some special cleanup.
	*/
	virtual void ClosingDialog(IActiveContext* myContext);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(XDocBkUIDialogController, kXDocBkUIDialogControllerImpl)

/* InitializeFields
*/
void XDocBkUIDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	this->SetInitialized(kFalse);
	do
	{
		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if (!facade) {
			break;
		}
		PMString templateFile = facade->GetTemplatePath();
		PMString stylesheetFile = facade->GetStylesheetPath();

		InterfacePtr<IDialogController> dialogController(this, UseDefaultIID());
		ASSERT(dialogController);
		if (!dialogController) {
			break;
		}
		templateFile.SetTranslatable(kFalse);
		stylesheetFile.SetTranslatable(kFalse);

		dialogController->SetTextControlData(kXDocBkUITemplateTextEditWidgetID, templateFile);
		dialogController->SetTextControlData(kXDocBkUIStylesheetTextEditWidgetID, stylesheetFile);

		dialogController->SetTriStateControlData(kXDocBkUIUseImagePostImportResponderWidgetID, 
			facade->IsUsingPostImportIterator() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
		dialogController->SetTriStateControlData(kXDocBkUIUseXMLTransformerWidgetID, 
			facade->IsUsingXMLTransformer() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
		dialogController->SetTriStateControlData(kXDocBkUIUseCALSContentHandlerWidgetID, 
			facade->IsUsingCALSContentHandler() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
		dialogController->SetTriStateControlData(kXDocBkUISuppliedOverridesPIWidgetID, 
			facade->IsSuppliedXSLOverridingPI() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);


		InterfacePtr<IObserver> myWidgetObserver(this, IID_IXDOCBKUIWIDGETOBSERVER);
		ASSERT(myWidgetObserver);
		if (!myWidgetObserver) {
			break;
		}
		myWidgetObserver->AutoAttach();

		this->SetInitialized(kTrue);
	} while (kFalse);
}


/* ApplyFields
*/
void XDocBkUIDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId) 
{
	// TODO sa+ update this comment
	// Apologies for the cut and paste re-use
	// in case the user has changed the paths through the text edit controls,
	// we set the options again on an ApplyDialogFields
	do
	{
		InterfacePtr<IDialogController> dialogController(this, UseDefaultIID());
		ASSERT(dialogController);
		if (!dialogController)
		{
			break;
		}

        K2Vector<WideString> optionsVec;
        optionsVec.reserve(cXDocBkOptionCardinality);

		PMString templatePath = dialogController->GetTextControlData(kXDocBkUITemplateTextEditWidgetID);
		optionsVec.push_back(WideString(templatePath));
		
		PMString stylesheetPath = dialogController->GetTextControlData(kXDocBkUIStylesheetTextEditWidgetID);
		optionsVec.push_back(WideString(stylesheetPath));

	
		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if (!facade)
		{
			break;
		}
		facade->SetOptions(optionsVec);
	} while (kFalse);
}

/* ValidateFields
*/
WidgetID XDocBkUIDialogController::ValidateDialogFields(IActiveContext* myContext) 
{
	// Initialize a return value of bad drop list values
	WidgetID invalidWidget = kDefaultWidgetId;
	return(invalidWidget);
}

/* ClosingDialog
*/
void XDocBkUIDialogController::ClosingDialog(IActiveContext* myContext)
{   
	// Stop listening too
	do
	{
		InterfacePtr<IObserver> myWidgetObserver(this, IID_IXDOCBKUIWIDGETOBSERVER);
		ASSERT(myWidgetObserver);
		if (!myWidgetObserver) {
			break;
		}
		myWidgetObserver->AutoDetach();
	} while (kFalse);
}

// End, XDocBkUIDialogController.cpp.
