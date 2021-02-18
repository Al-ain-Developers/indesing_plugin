//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffectui/TranFxUIDialogObserver.cpp $
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
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "IDialogController.h"
#include "ITextControlData.h"
#include "IStringListControlData.h"
#include "IDropDownListController.h"
#include "ITextFocus.h"
#include "ILayoutUtils.h"
#include "IActiveContext.h"
#include "ISelectionManager.h"

// General includes:
#include "CDialogObserver.h"
#include "Utils.h"
#include "PMTextUtils.h"
#include "Trace.h"
#include "CAlert.h"

// Project includes:
#include "TranFxUIID.h"
#include "TranFxID.h"
#include "ITranFxSuite.h"

/** Implements a dialog observer based on CDialogObserver
	that handles widget changes made by the user in this
	plug-in's previewable dialog.

	Changes to the transparency effect are made
	via the suite ITranFxSuite.

	The description below talks about how commands get processed
	in previewable dialogs. Note however that this dialog does not process
	commands directly. Instead, it calls the suite that controls the
	effect, ITranFXSuite, that in turn calls a facade, TranFxUtils,
	that processes the commands. So the dialog works in tandem with
	the suite and the commands that it processes. However, it is 
	important to understand the special way in which commands are
	handled during a previewable dialog, as given below.

	Modal dialogs can have a preview checkbox. 	The preview checkbox 
	allows the user to see the immediate effect on the document of
	modifying some dialog control.

	A previewable dialog works like this. Typically it
	is implemented more like a panel in that each control has an
	observer that results in a command being processed to change something when
	clicked. In this implementation we have one observer watching
	all the widgets in the dialog for change. Each time a widget
	changes we make a suite call that processes a command to make 
	the requested change.

	When the preview checkbox is turned off commands are buffered. 
	When the preview checkbox is turned on buffered commands are 
	processed. When the preview checkbox is turned off again the 
	commands are undone. When the dialog is dismissed with the OK 
	button buffered commands are processed.

	Adding a preview checkbox to you modal dialog will give you:
	<ul>
	<li>buffering of commands when preview is not checked.
	<li>undoing of previewed commands when the dialog is cancelled.
	<li>grouping of commands into a single compound command.
	<li>replacement of commands with the same ICommand::GetCreatorID.
	i.e. if you process a command with the same creator id more than
	once the previous command is undone and replaced by the new command.
	So if you click 10 times to set the x offset to a different
	value only the last set x offset command is processed. See 
	the methods in TranFxUtils that gets called by ITranFxSuite
	for examples of how this is done.
	</ul>

	A preview checkbox is created by an ODFRez statement like this:
	<pre>
		// Note the preview button
		CheckBoxWidget
		(
			kPreviewButtonWidgetID,			// WidgetId
			kSysCheckBoxPMRsrcId,			// RsrcId
			kBindNone,
			Frame(192,76,272,96)			// Frame
			kTrue,							// Visible
			kTrue,							// Enabled
			// TriStateControlAttributes
			kAlignLeft,						// fAlignment
			// CTextControlData
			"Pre&view"						// Initial text 
		)
	</pre>

	You can have a preview checkbox but disable all of the
	processing described above simply by using replacing
	kPreviewButtonWidgetID with a WidgetID of your own. You
	would then have to implement your own command management
	using command sequences or whatever to achieve the result
	you want.

	
	@ingroup transparencyeffectui
	@see ITranFxSuite
	@see TranFxUtils
*/
class TranFxUIDialogObserver : public CDialogObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TranFxUIDialogObserver(IPMUnknown* boss) ;

		/** Destructor. */
		virtual ~TranFxUIDialogObserver() {}

		/** 
			Called by the application to allow the observer to attach to the subjects 
			to be observed, in this case the dialog's info button widget. If you want 
			to observe other widgets on the dialog you could add them here. 
		*/
		virtual void AutoAttach();

		/** Called by the application to allow the observer to detach from the subjects being observed. */
		virtual void AutoDetach();

		/**
			Called by the host when the observed object changes, in this case when
			the dialog's info button is clicked.
			@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
			@param theSubject points to the ISubject interface for the subject that has changed.
			@param protocol specifies the ID of the changed interface on the subject boss.
			@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
		*/
		virtual void Update
		(
			const ClassID& theChange, 
			ISubject* theSubject, 
			const PMIID& protocol, 
			void* changedBy
		);
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(TranFxUIDialogObserver, kTranFxUIDialogObserverImpl)

/* Constructor.
*/
TranFxUIDialogObserver::TranFxUIDialogObserver(IPMUnknown * boss) : CDialogObserver(boss)
{

}

/* 
*/
void TranFxUIDialogObserver::AutoAttach()
{
	// Call the base class AutoAttach() function so that default behavior
	// will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoAttach();
	do
	{
		// Get the IPanelControlData interface for the dialog:
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("TranFxUIDialogObserver::AutoAttach() panelControlData invalid");
			break;
		}
		
		// Now attach to dialog's info button widget.
		AttachToWidget(kTranFxUIIconSuiteWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
		// Attach to other widgets you want to handle dynamically here.
		AttachToWidget(kTranFxUIApplyEffectWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
		AttachToWidget(kTranFxUIXOffsetEditBoxWidgetID, ITextControlData::kDefaultIID, panelControlData);
		AttachToWidget(kTranFxUIYOffsetEditBoxWidgetID, ITextControlData::kDefaultIID, panelControlData);
		AttachToWidget(kTranFxUIUseBlackAsOpaqueWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
		AttachToWidget(kTranFxUIUseAlphaWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
		AttachToWidget(kTranFxUIUseBlurWidgetID, ITriStateControlData::kDefaultIID, panelControlData);

	} while (false);
}

/* 
*/
void TranFxUIDialogObserver::AutoDetach()
{
	// Call base class AutoDetach() so that default behavior will occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoDetach();

	do
	{
		// Get the IPanelControlData interface for the dialog:
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		if (panelControlData == nil)
		{
			ASSERT_FAIL("TranFxUIDialogObserver::AutoDetach() panelControlData invalid");
			break;
		}
		
		// Now we detach from dialog's info button widget.
		DetachFromWidget(kTranFxUIIconSuiteWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
		// Detach from other widgets you handle dynamically here.
		DetachFromWidget(kTranFxUIApplyEffectWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kTranFxUIXOffsetEditBoxWidgetID, ITextControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kTranFxUIYOffsetEditBoxWidgetID, ITextControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kTranFxUIUseBlackAsOpaqueWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kTranFxUIUseAlphaWidgetID, ITriStateControlData::kDefaultIID, panelControlData);
		DetachFromWidget(kTranFxUIUseBlurWidgetID, ITriStateControlData::kDefaultIID, panelControlData);

	} while (false);
}


/*
*/
void TranFxUIDialogObserver::Update
(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID &protocol, 
	void* changedBy
)
{
	// Call the base class Update function so that default behavior will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	do
	{
		// Get the control view and the dialog controller.
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		ASSERT(controlView);
		if (controlView == nil) {
			break;
		}
		InterfacePtr<IDialogController> dialogController(this, IID_IDIALOGCONTROLLER);
		if (dialogController == nil) {
			ASSERT_FAIL("dialogController invalid");
			break;
		}

		// Get the button ID from the view.
		WidgetID widgetID = controlView->GetWidgetID();

		// About box button.
		if (widgetID == kTranFxUIIconSuiteWidgetID && theChange == kTrueStateMessage) {
			// Bring up the About box.
			CAlert::ModalAlert
			(
				kTranFxUIAboutBoxStringKey,		// Alert string
				kOKString, 						// OK button
				kNullString, 					// No second button
				kNullString, 					// No third button
				1,								// Set OK button to default
				CAlert::eInformationIcon		// Information icon.
			);
			break;
		}
	
		// Cancel button.
		if (widgetID == kCancelButton_WidgetID && theChange == kTrueStateMessage) {
			// The user cancelled.
			break;
		}

		// OK button.
		if (widgetID == kOKButtonWidgetID && theChange == kTrueStateMessage) {
			// The user clicked OK.
			break;
		}

		// Get the suite we need to make changes.
		InterfacePtr<IDialogController> dc(this, UseDefaultIID());
		ASSERT(dc);
		if (!dc) {
			break;
		}
		InterfacePtr<IActiveContext> activeContext(dc->QueryDialogContext());
		ASSERT(activeContext);
		if (!activeContext) {
			break;
		}
		InterfacePtr<ITranFxSuite> tranFxSuite(activeContext->GetContextSelection(), UseDefaultIID());
		if (!tranFxSuite) {
			break;
		}

		// Make the change indicated by the widget.
		switch(widgetID.Get()) {

			case kTranFxUIApplyEffectWidgetID:
			{
				if (theChange == kTrueStateMessage) {
					tranFxSuite->ApplyAdornment(kTrue);
				}
				else if (theChange == kFalseStateMessage) {
					tranFxSuite->ApplyAdornment(kFalse);
				}
				break;
			}


			case kTranFxUIUseBlackAsOpaqueWidgetID:
			{
				if (theChange == kTrueStateMessage) {
					tranFxSuite->ApplyUseBlackAsOpaque(kTrue);
				}
				else if (theChange == kFalseStateMessage) {
					tranFxSuite->ApplyUseBlackAsOpaque(kFalse);
				}
				break;
			}

			case kTranFxUIUseAlphaWidgetID:
			{
				if (theChange == kTrueStateMessage) {
					tranFxSuite->ApplyUseAlpha(kTrue);
				}
				else if (theChange == kFalseStateMessage) {
					tranFxSuite->ApplyUseAlpha(kFalse);
				}
				break;
			}

			case kTranFxUIUseBlurWidgetID:
			{
				if (theChange == kTrueStateMessage) {
					tranFxSuite->ApplyUseBlur(kTrue);
				}
				else if (theChange == kFalseStateMessage) {
					tranFxSuite->ApplyUseBlur(kFalse);
				}
				break;
			}
			
			case kTranFxUIXOffsetEditBoxWidgetID:
			{
				PMReal xOffset = dialogController->GetTextValue(kTranFxUIXOffsetEditBoxWidgetID);
				tranFxSuite->ApplyXOffset(xOffset);
				break;	
			}

			case kTranFxUIYOffsetEditBoxWidgetID:
			{
				PMReal yOffset = dialogController->GetTextValue(kTranFxUIYOffsetEditBoxWidgetID);
				tranFxSuite->ApplyYOffset(yOffset);
				break;	
			}	

		} // end of switch on WidgetID
	} while (false);
}

//  Generated by Dolly build 17: template "Dialog".
// End, TranFxUIDialogObserver.cpp.


