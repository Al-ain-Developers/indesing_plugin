//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunDialogController.cpp $
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
#include "IPanelControlData.h"
#include "IControlView.h"
#include "ITextDataValidation.h"
#include "ITextControlData.h"
#include "IStringListControlData.h"
#include "IDropDownListController.h"

// General includes:
#include "CDialogController.h"
#include "ErrorUtils.h"

// Project includes:
#include "SnipRunID.h"
#include "ISnipRunDialogData.h"

/** Prompts the user for the value of a data type described by the caller in 
	ISnipRunDialogData.  Only one data type value can be gathered per dialog.
	
	The dialog has a widget per data type e.g.
	one for PMStrings, one for int32, one for PMReal and so on
	that are used to gather the value. 

	Implements IDialogController based on the partial implementation CDialogController.

	@ingroup snippetrunner
	
*/
class SnipRunDialogController : public CDialogController
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		SnipRunDialogController(IPMUnknown* boss);

		/** Destructor.
		*/
		virtual ~SnipRunDialogController();

		/** Called when the dialog is opened to initialize each widget 
			in the dialog with its default value.
			@param dlgContext IN
		*/
		virtual void InitializeDialogFields( IActiveContext* dlgContext);

		/** Validate the values in the widgets.
			By default, the widget with ID kOKButtonWidgetID causes
			ValidateFields to be called. When all widgets are valid,
			ApplyFields will be called.
			@param myContext
			@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.

		*/
		virtual WidgetID ValidateDialogFields(IActiveContext* myContext);

		/** Retrieve the values from the widgets and act on them.
			@param myContext
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId);

		/** Called when the dialog is closing & used to control widget
			visibility.
			@param lastChanceToUseMyContext
		 */
		virtual void ClosingDialog(IActiveContext* lastChanceToUseMyContext);

		/** Called when the user uses the cancel button to dismiss the dialog
		 */
		virtual void UserCancelled();

	private:
		// Initialise method per data type supported.
		void	InitStringDialog();
		void	InitChoiceDialog();
		void	InitIntDialog();
		void	InitRealDialog();

		// Apply method per data type supported.
		void	ApplyStringDialog();
		void	ApplyChoiceDialog();
		void	ApplyIntDialog();
		void	ApplyRealDialog();

	private:
		// Methods to control the dynamic visibilty of widgets.
		// Only one type of data is prompted for at any one time.
		void	SetActiveControl(const WidgetID& widgetID);
		void	ShowActiveControl();
		void	HideActiveControl();

	private:
		ISnipRunDialogData::SnipRunDialogMode	fDialogMode;
		IControlView*							fActiveControlView;
};

/* Make implementation available to the application.
*/
CREATE_PMINTERFACE(SnipRunDialogController, kSnipRunDialogControllerImpl)

/*
*/
SnipRunDialogController::SnipRunDialogController(IPMUnknown* boss) : CDialogController(boss), 
fDialogMode(ISnipRunDialogData::kSnipRunStringMode),
fActiveControlView(nil)
{
}

/*
*/
SnipRunDialogController::~SnipRunDialogController()
{
}

/*
*/
void SnipRunDialogController::InitializeDialogFields( IActiveContext* dlgContext)
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		dialogData->SetWasCancelled(kFalse);
		this->SetTextControlData(kSnipRunParamPromptWidgetID, dialogData->GetPrompt());
		this->SetTextControlData(kSnipRunParamTypeInfoWidgetID, dialogData->GetTypeInfo());
		fDialogMode = dialogData->GetMode();
		switch (fDialogMode) {
		default:
		case ISnipRunDialogData::kSnipRunStringMode:
			{
				this->SetActiveControl(kSnipRunStringParamWidgetID);
				this->InitStringDialog();
				break;
			}
		case ISnipRunDialogData::kSnipRunIntMode:
			{
				this->SetActiveControl(kSnipRunIntParamWidgetID);
				this->InitIntDialog();
				break;
			}
		case ISnipRunDialogData::kSnipRunRealMode:
			{
				this->SetActiveControl(kSnipRunRealParamWidgetID);
				this->InitRealDialog();
				break;
			}
		case ISnipRunDialogData::kSnipRunChoiceMode:
			{
				this->SetActiveControl(kSnipRunChoiceParamWidgetID);
				this->InitChoiceDialog();
				break;
			}
		}
	} while (false);
}

/*
*/
WidgetID SnipRunDialogController::ValidateDialogFields( IActiveContext* myContext)
{
	// No widget validation currently
	return kInvalidWidgetID;
}

/*
*/
void SnipRunDialogController::ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId)
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		fDialogMode = dialogData->GetMode();
		switch (fDialogMode) {
		default:
		case ISnipRunDialogData::kSnipRunStringMode:
			{
				this->ApplyStringDialog();
				break;
			}
		case ISnipRunDialogData::kSnipRunIntMode:
			{
				this->ApplyIntDialog();
				break;
			}
		case ISnipRunDialogData::kSnipRunRealMode:
			{
				this->ApplyRealDialog();
				break;
			}
		case ISnipRunDialogData::kSnipRunChoiceMode:
			{
				this->ApplyChoiceDialog();
				break;
			}
		}
	} while(false);
}

/* 
*/
void SnipRunDialogController::UserCancelled() 
{
	InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
	ASSERT(dialogData);
	if (dialogData) {
		dialogData->SetWasCancelled(kTrue);
	}
}

/* 
*/
void SnipRunDialogController::ClosingDialog(IActiveContext* lastChanceToUseMyContext)
{
	this->HideActiveControl();
}

/* 
*/
void  SnipRunDialogController::InitStringDialog()
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		IControlView* controlView = fActiveControlView;
		if (!controlView) {
			break;
		}

		// Initialise the parameter value.
		InterfacePtr<ITextControlData> textControlData(controlView, UseDefaultIID());
		ASSERT(textControlData);
		if (!textControlData) {
			break;
		}
		textControlData->SetString(dialogData->GetPMString(), kFalse, kFalse);
		this->ShowActiveControl();
	} while(false);
}

/* 
*/
void  SnipRunDialogController::InitChoiceDialog()
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		IControlView* controlView = fActiveControlView;
		if (!controlView) {
			break;
		}

		// Initialise the allowed parameter values.
		InterfacePtr<IStringListControlData> stringList(controlView, UseDefaultIID());
		ASSERT(stringList);
		if (!stringList) {
			break;
		}
		stringList->Clear(kFalse,	kFalse);
		K2Vector<PMString>::const_iterator iter;
		int32 selectedIndex = dialogData->GetChoiceIndex();
		const K2Vector<PMString>& choices = dialogData->GetChoices();
		for (iter = choices.begin(); iter < choices.end(); iter++) {
			stringList->AddString(*iter, 
							IStringListControlData::kEnd, 	
							kFalse, 						
							kFalse);
		}
		
		// Initialise the parameter value.
		InterfacePtr<IDropDownListController> dropDown(controlView, UseDefaultIID());
		ASSERT(dropDown);
		if (!dropDown) {
			break;
		}
		dropDown->Select(selectedIndex,	// ordinal place.
			kFalse,									// Invalidate?
			kFalse									// Notify of change?
		);
		this->ShowActiveControl();
	} while(false);
}

/* 
*/
void  SnipRunDialogController::InitIntDialog()
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		IControlView* controlView = fActiveControlView;
		if (!controlView) {
			break;
		}

		// Initialise range checking.
		PMReal lowerLimit = dialogData->GetLowerLimit();
		PMReal upperLimit = dialogData->GetUpperLimit();
		bool16 checkingOn = kFalse;
		if (lowerLimit != 0.0 || upperLimit != 0.0) {
			checkingOn = kTrue;
		}
		InterfacePtr<ITextDataValidation> textDataValidation(controlView, UseDefaultIID());
		if (textDataValidation) {
			textDataValidation->EnableRangeChecking(checkingOn);
			textDataValidation->SetLowerLimit(lowerLimit);
			textDataValidation->SetUpperLimit(upperLimit);
		}

		// Initialise the parameter value.
		InterfacePtr<ITextValue> textValue(controlView, UseDefaultIID());
		ASSERT(textValue);
		if (!textValue) {
			break;
		}
		textValue->SetTextFromValue(dialogData->GetInt32(), kFalse, kFalse);
		this->ShowActiveControl();
	} while(false);
}

/* 
*/
void  SnipRunDialogController::InitRealDialog()
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		IControlView* controlView = fActiveControlView;
		if (!controlView) {
			break;
		}

		// Initialise range checking.
		PMReal lowerLimit = dialogData->GetLowerLimit();
		PMReal upperLimit = dialogData->GetUpperLimit();
		bool16 checkingOn = kFalse;
		if (lowerLimit != 0.0 || upperLimit != 0.0) {
			checkingOn = kTrue;
		}
		InterfacePtr<ITextDataValidation> textDataValidation(controlView, UseDefaultIID());
		if (textDataValidation) {
			textDataValidation->EnableRangeChecking(checkingOn);
			textDataValidation->SetLowerLimit(lowerLimit);
			textDataValidation->SetUpperLimit(upperLimit);
		}

		// Initialise the parameter value.
		InterfacePtr<ITextValue> textValue(controlView, UseDefaultIID());
		ASSERT(textValue);
		if (!textValue) {
			break;
		}
		textValue->SetTextFromValue(dialogData->GetPMReal(), kFalse, kFalse);
		this->ShowActiveControl();
	} while(false);
}

/* 
*/
void  SnipRunDialogController::ApplyStringDialog()
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		IControlView* controlView = fActiveControlView;
		if (!controlView) {
			break;
		}
		InterfacePtr<ITextControlData> textControlData(controlView, UseDefaultIID());
		ASSERT(textControlData);
		if (!textControlData) {
			break;
		}
		PMString result = textControlData->GetString();
		result.SetTranslatable(kFalse); // user input does not require translation.
		dialogData->SetPMString(result);
	} while(false);
}

/* 
*/
void  SnipRunDialogController::ApplyChoiceDialog()
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		IControlView* controlView = fActiveControlView;
		if (!controlView) {
			break;
		}
		InterfacePtr<IDropDownListController> dropDown(controlView, UseDefaultIID());
		ASSERT(dropDown);
		if (!dropDown) {
			break;
		}
		const K2Vector<PMString>& choices = dialogData->GetChoices();
		int32 index = dropDown->GetSelected();
		if (index < 0 || index >= choices.size()) {
			ASSERT_FAIL("invalid drop down index on kSnipRunChoiceParamWidgetID");
			break;
		}
		dialogData->SetChoiceIndex(index);
	} while(false);
}

/* 
*/
void  SnipRunDialogController::ApplyIntDialog()
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		IControlView* controlView = fActiveControlView;
		if (!controlView) {
			break;
		}
		InterfacePtr<ITextValue> textValue(controlView, UseDefaultIID());
		ASSERT(textValue);
		if (!textValue) {
			break;
		}
		dialogData->SetInt32(::ToInt32(textValue->GetTextAsValue()));
	} while(false);
}

/* 
*/
void  SnipRunDialogController::ApplyRealDialog()
{
	do {
		InterfacePtr<ISnipRunDialogData> dialogData(this, UseDefaultIID());
		ASSERT(dialogData);
		if (!dialogData) {
			break;
		}
		IControlView* controlView = fActiveControlView;
		if (!controlView) {
			break;
		}
		InterfacePtr<ITextValue> textValue(controlView, UseDefaultIID());
		ASSERT(textValue);
		if (!textValue) {
			break;
		}
		dialogData->SetPMReal(textValue->GetTextAsValue());
	} while(false);
}

/*
*/
void SnipRunDialogController::SetActiveControl(const WidgetID& widgetID)
{
	fActiveControlView = nil;
	do {
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if (!panelControlData) {
			break;
		}
		IControlView* controlView = panelControlData->FindWidget(widgetID);
		ASSERT(controlView);
		if (!controlView) {
			break;
		}
		fActiveControlView = controlView;
	} while(false);

}

/*
*/
void SnipRunDialogController::ShowActiveControl()
{
	IControlView* controlView = fActiveControlView;
	if (controlView) {
		controlView->ShowView(kTrue);
		controlView->Enable(kTrue, kTrue);
	}
}

/*
*/
void SnipRunDialogController::HideActiveControl()
{
	IControlView* controlView = fActiveControlView;
	if (controlView) {
		controlView->Disable(kFalse);
		controlView->HideView();
	}
}

// End SnipRunDialogController.cpp
