//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffectui/TranFxUIDialogController.cpp $
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
#include "ISelectionUtils.h"
#include "IDropDownListController.h"

// General includes:
#include "CDialogController.h"
//#include "SystemUtils.h"
#include "Utils.h"

// Project includes:
#include "TranFxUIID.h"
#include "TranFxID.h"
#include "ITranFxSuite.h"

/** Implements a dialog controller, IDialogController based on
	CDialogController, that uses ITranFxSuite to initialise the
	state of the dialog's widgets. The dialog observer, 
	TranFxUIDialogObserver, handles each change of
	a widget value made by the user.

	
	@ingroup transparencyeffectui
	@see TranFxUIDialogObserver
*/
class TranFxUIDialogController : public CDialogController
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TranFxUIDialogController(IPMUnknown* boss) : CDialogController(boss) {}

		/** Destructor.
		*/
		virtual ~TranFxUIDialogController() {}

		/** Initialises each widget in the dialog.
		*/
		virtual void InitializeDialogFields(IActiveContext* context);

		/** Null implementation.		
			@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.
		*/
		virtual WidgetID			ValidateDialogFields(IActiveContext* myContext);

		/** Null implementation.
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(TranFxUIDialogController, kTranFxUIDialogControllerImpl)

/*
*/
void TranFxUIDialogController::InitializeDialogFields(IActiveContext* context)
{
	do{
		// Get the interfaces needed to initialise the dialog's widget's.
		InterfacePtr<IDialogController> dc(this, UseDefaultIID());
		ASSERT(dc);
		if(!dc) {
			break;
		}
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}

		// Get the suite used to obtain widget values.
		ASSERT(context);
		if (!context) {
			break;
		}
		InterfacePtr<ITranFxSuite> tranFxSuite(context->GetContextSelection(), UseDefaultIID());
		if (!tranFxSuite) {
			ASSERT_FAIL("ITranFxSuite is not available, the dialog should not have been enabled");
			// Disable all the effect controls on the dialog, all the user can do is dismiss the dialog.
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIOptionsWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Disable();
			break;
		}
		else {
			// Enable all the effect controls.
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIOptionsWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Enable();
		}


		// Enable and set the value of each widget.

		// Adornment checkbox.
		if (tranFxSuite->CanApplyAdornment()) {
			// Enable the widget.
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIApplyEffectWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Enable();
			// Set the widget's value.
			ITranFxSuite::AttrState adornmentAttrState;
			tranFxSuite->HasAdornment(adornmentAttrState);
			ITriStateControlData::TriState adornmentWidgetState = ITriStateControlData::kUnknown;
			if (adornmentAttrState == ITranFxSuite::eNoValue) {
				adornmentWidgetState = ITriStateControlData::kUnselected;
			}
			else if (adornmentAttrState == ITranFxSuite::eCommonValue) {
				adornmentWidgetState = ITriStateControlData::kSelected;
			}
			dc->SetTriStateControlData(kTranFxUIApplyEffectWidgetID, adornmentWidgetState);
		}
		else {
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIApplyEffectWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Disable();
		}

		
		// X offset.
		if (tranFxSuite->CanApplyXOffset()) {
			// Enable the widget.
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIXOffsetEditBoxWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Enable();
			// Set the widget's value.
			PMReal xOffsetValue = 0.0; //kTranFxXOffsetDefault;
			ITranFxSuite::AttrState xOffsetAttrState;
			tranFxSuite->HasXOffset(xOffsetAttrState, xOffsetValue);
			if (xOffsetAttrState == ITranFxSuite::eCommonValue || xOffsetAttrState == ITranFxSuite::eNoValue) {
				dc->SetTextValue(kTranFxUIXOffsetEditBoxWidgetID, xOffsetValue);
			}
			else {
				// mixed value
				dc->SetTextValueControlState(kTranFxUIXOffsetEditBoxWidgetID, ITextValue::kUnknown);
			}
		}
		else {
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIXOffsetEditBoxWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Disable();
		}

		// Y offset.
		if (tranFxSuite->CanApplyYOffset()) {
			// Enable the widget.
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIYOffsetEditBoxWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Enable();
			// Set the widget's value.
			PMReal yOffsetValue = 0.0; //kTranFxXOffsetDefault;
			ITranFxSuite::AttrState yOffsetAttrState;
			tranFxSuite->HasYOffset(yOffsetAttrState, yOffsetValue);
			if (yOffsetAttrState == ITranFxSuite::eCommonValue || yOffsetAttrState == ITranFxSuite::eNoValue) {
				dc->SetTextValue(kTranFxUIYOffsetEditBoxWidgetID, yOffsetValue);
			}
			else {
				// mixed value
				dc->SetTextValueControlState(kTranFxUIYOffsetEditBoxWidgetID, ITextValue::kUnknown);
			}
		}
		else {
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIYOffsetEditBoxWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Disable();
		}

		// Use black as opaque checkbox.
		if (tranFxSuite->CanApplyUseBlackAsOpaque()) {
			// Enable the widget.
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIUseBlackAsOpaqueWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Enable();
			// Set the widget's value.
			bool16 value = kFalse;
			ITranFxSuite::AttrState attrState;
			tranFxSuite->HasUseBlackAsOpaque(attrState, value);
			ITriStateControlData::TriState checkBoxState = ITriStateControlData::kUnknown;
			if (attrState == ITranFxSuite::eNoValue || attrState == ITranFxSuite::eCommonValue) {
				if (value) {
					checkBoxState = ITriStateControlData::kSelected;
				}
				else {
					checkBoxState = ITriStateControlData::kUnselected;
				}
			}
			else {
				// mixed value
				checkBoxState = ITriStateControlData::kUnknown;
			}
			dc->SetTriStateControlData(kTranFxUIUseBlackAsOpaqueWidgetID, checkBoxState);
		}
		else {
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIUseBlackAsOpaqueWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Disable();
		}

		// Use alpha checkbox.
		if (tranFxSuite->CanApplyUseAlpha()) {
			// Enable the widget.
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIUseAlphaWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Enable();
			// Set the widget's value.
			bool16 value = kFalse;
			ITranFxSuite::AttrState attrState;
			tranFxSuite->HasUseAlpha(attrState, value);
			ITriStateControlData::TriState checkBoxState = ITriStateControlData::kUnknown;
			if (attrState == ITranFxSuite::eNoValue || attrState == ITranFxSuite::eCommonValue) {
				if (value) {
					checkBoxState = ITriStateControlData::kSelected;
				}
				else {
					checkBoxState = ITriStateControlData::kUnselected;
				}
			}
			else {
				// mixed value
				checkBoxState = ITriStateControlData::kUnknown;
			}
			dc->SetTriStateControlData(kTranFxUIUseAlphaWidgetID, checkBoxState);
		}
		else {
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIUseAlphaWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Disable();
		}

		// Use blur checkbox.
		if (tranFxSuite->CanApplyUseBlur()) {
			// Enable the widget.
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIUseBlurWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Enable();
			// Set the widget's value.
			bool16 value = kFalse;
			ITranFxSuite::AttrState attrState;
			tranFxSuite->HasUseBlur(attrState, value);
			ITriStateControlData::TriState checkBoxState = ITriStateControlData::kUnknown;
			if (attrState == ITranFxSuite::eNoValue || attrState == ITranFxSuite::eCommonValue) {
				if (value) {
					checkBoxState = ITriStateControlData::kSelected;
				}
				else {
					checkBoxState = ITriStateControlData::kUnselected;
				}
			}
			else {
				// mixed value
				checkBoxState = ITriStateControlData::kUnknown;
			}
			dc->SetTriStateControlData(kTranFxUIUseBlurWidgetID, checkBoxState);
		}
		else {
			IControlView* controlView = panelControlData->FindWidget(kTranFxUIUseBlurWidgetID);
			ASSERT(controlView);
			if (!controlView) {
				break;
			}
			controlView->Disable();
		}
	} while(false);	
}

/*
*/
WidgetID TranFxUIDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	// Deliberately empty.
	return kInvalidWidgetID;
}

/*
*/
void TranFxUIDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId)
{
	// Deliberately empty, changes are applied in the dialog observer.
}

//  Generated by Dolly build 17: template "Dialog".
// End, TranFxUIDialogController.cpp.


