//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/dialogs/CDialogObserver.cpp $
//  
//  Owner: Michael Burbidge
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

#include "VCWidgetHeaders.h"

#include "CDialogObserver.h"

// ----- Interface Includes -----
#include "IPanelControlData.h"
#include "ISubject.h"
#include "IDialog.h"
#include "IWidgetParent.h"
//#include "ICommand.h"
#include "IBoolData.h"
//#include "IEventHandler.h"
#include "IDialogController.h"
#include "IIntegerControlData.h"
#include "ISignalMgr.h"

// ----- Implementation Includes -----
#include "ErrorUtils.h"

// BP 04/17/01: moved to  .../source/components/WidgetBin/WidgetBinImpl.cpp
// CREATE_PMINTERFACE(CDialogObserver, kCDialogObserverImpl)

//========================================================================================
// CLASS CDialogObserver
//========================================================================================

CDialogObserver::CDialogObserver(IPMUnknown *boss) :
	AbstractDialogObserver(boss),
	fIsDialogInitialized(kFalse),
	fCloseOnCancel(kTrue)
{
#ifdef DEBUG
	// make sure this is main dialog (has OK, Cancel buttions...)
	InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
	InterfacePtr<IWidgetParent> self(panelData, IID_IWIDGETPARENT);
	InterfacePtr<IDialog> iDialog(self->GetParent(), IID_IDIALOG);
	ASSERT_MSG(iDialog != nil, "This is not main dialog panel (the one with OK, Cancel buttons). Please inherit from AbstractDialogObserver");
#endif
}

CDialogObserver::~CDialogObserver()
{
}

void CDialogObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* /* changedBy */)
{
	ASSERT_MSG(theSubject != nil, "theSubject != nil");
	InterfacePtr<IControlView> view(theSubject, IID_ICONTROLVIEW);
	if (view) 
	{
		InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
		InterfacePtr<IDialog> dialog((IDialog*) parentHolder->QueryParentFor(IID_IDIALOG));
		InterfacePtr<IDialogController> dialogController(this, IID_IDIALOGCONTROLLER);
		//----------------------------
		// Handle OK or Cancel Button
		//----------------------------
		if (theChange == kTrueStateMessage) // react only when the button is turned on
		{	
			if (view->GetWidgetID() == kOKButtonWidgetID)
			{
				InterfacePtr<IWidgetParent> parentPtr(this, UseDefaultIID());
				InterfacePtr<IBoolData> dataInvalid((IBoolData *)parentPtr->QueryParentFor(IID_IDIALOGVALIDATIONFAILED));

				// Reset the Dialog Validation status Flag, Set the following flag on failed dialog validation, 
				// so that dialog should not be closed
				SetDialogValidationStatusFailed(kFalse);

				WidgetID illegalWidget = dialogController->ValidateDialog();

				if (dataInvalid && illegalWidget == kDefaultWidgetId)
				{
					ASSERT_MSG(dataInvalid->Get() == kFalse,
						"IID_IDIALOGVALIDATIONFAILED flag is set to kTrue, although dialog validation passed.");
				}

				// Check if either the IID_IDIALOGVALIDATIONFAILED is not defined on the dialog boss, or if defined than it should be set to false
				if ((illegalWidget == kDefaultWidgetId && !dataInvalid) ||
					(illegalWidget == kDefaultWidgetId && dataInvalid && dataInvalid->Get() == kFalse))
				{	
					// all dialog fields valid
					if (dialog->HasPreviewButton()) 
					{
						// When a dialog has a preview button, the dialog really shouldn't
						// be doing anything in ApplyFields, such as firing off commands.
						dialogController->ApplyDialog(view->GetWidgetID());
						
						FireOffEndDialogCmd(kTrue);
					} 
					else 
					{
						// Some dialogs seem to be firing off multiple commands in 
						// ApplyFields. This makes undoing the dialog as a single command
						// impossible. In order to catch those offenders, I'll group the
						// commands in a command sequence.
						PMString name;							
						dialogController->GetName(name);							
						CmdUtils::SequenceContext	sequence(&name);
						dialogController->ApplyDialog(view->GetWidgetID());
						if( dialog->GetBufferCommands())
							FireOffEndDialogCmd(kTrue);
					}

					// With some preview dialog, dialog may have already been closed due to an error
					// occuring in a sequence the dialog fires. See DialogCommandInterceptor::ProcessACommand.
					CloseDialog(!dialog->IsOpen());
				} 
				else 
				{	
					SetDialogValidationStatusFailed(kTrue);
					// a dialog field has some bad data
					// Try and select the control as the keyboard target
					dialogController->SelectDialogWidget(illegalWidget);
				}
			}
			else if (view->GetWidgetID() == kCancelButton_WidgetID) 
			{
				if(!fCloseOnCancel)
				{					
					InterfacePtr<IWidgetParent> parentPtr(this, UseDefaultIID());
					InterfacePtr<IBoolData> shouldCloseDialog((IBoolData *)parentPtr->QueryParentFor(IID_IDEFAULTCLOSEONCANCEL));
					if(shouldCloseDialog)
					{
						shouldCloseDialog -> Set(kFalse);
						return;
					}
				}

				InterfacePtr<IIntegerControlData> supportReset(view, IID_IINTEGERCONTROLDATA);
				// Check to see if the cancel button currently is a "Reset" button
				if (supportReset && supportReset->GetValue() > kTrue) 
				{
					// The cancel button is currently a reset button, reinitialize the dialog
					dialogController->ResetDialog();
				} 
				else 
				{
					if (dialog->HasPreviewButton() || dialog->GetBufferCommands())
						FireOffEndDialogCmd(kFalse);
					
					dialogController->UserCancelled();	
					dialog->DialogCancelled();
					CloseDialog(kFalse);
				}
			}
		}

		//----------------------------
		// Handle Dialog Closed
		//----------------------------
		// This block of code catches the case where a user dismisses a modeless dialog
		// by clicking the dialog's close box.	In that case, the window is closed by
		// a CloseWindowCmd and we find out about it "after the fact."	We still must
		// clean up by removing our event handler and observer.  When the dialog is
		// dismissed by clicking ok or cancel, we still get a "kCloseWinCmdBoss" change.
		// In that case, we don't want to execute this block of code.  Hence, the reason
		// why "fDialogHasBeenClosed" exists.
		
		if (theChange == kAboutToCloseWindowMsgBoss) 
		{
			if (dialog != nil && dialog->IsOpen())
				CloseDialog(kTrue); // the dialog window has already been closed!  Gotta clean up...
		}
		
		//----------------------------
		// Handle Preview Checkbox
		//----------------------------
		if (view->GetWidgetID() == kPreviewButtonWidgetID)
		{
			if (theChange == kTrueStateMessage) 
			{
				// The user just turned on the preview button.
				WidgetID illegalWidget = dialogController->ValidateDialog();
				if (illegalWidget == kDefaultWidgetId) 
				{	
					// all dialog fields valid
					// Execute all the backlogged commands
					dialogController->SetPreviewModeOn( kTrue );
				}				
				else 
				{	
					// a dialog field has some bad data. Set the preview checkbox back to off(but don't notify)
					InterfacePtr<ITriStateControlData> tristateData(view,IID_ITRISTATECONTROLDATA);
					tristateData->Deselect(kTrue,kFalse);
					
					// Try and select the control as the keyboard target
					dialogController->SelectDialogWidget(illegalWidget);
				}
				
			}
			else if (theChange == kFalseStateMessage) 
			{
				// The user just turned off the preview button
				// Start buffering all commands
				dialogController->SetPreviewModeOn( kFalse );
			}
			InterfacePtr<ICommand> previewDialogCmd(CmdUtils::CreateCommand(kPreviewDialogCmdBoss));
			InterfacePtr<IBoolData> data(previewDialogCmd, IID_IBOOLDATA);
			data->Set(dialogController->GetPreviewModeOn());
			CmdUtils::ProcessCommand(previewDialogCmd);
		}

		//----------------------------
		// Handle PreviewControlData: Almost identical to preview checkbox above
		//----------------------------
		if (protocol == IID_IPREVIEWCONTROLDATA)
		{
			if (theChange == kTrueStateMessage) 
			{
				// preview functionality turned on programattically
				WidgetID illegalWidget = dialogController->ValidateDialog();
				if (illegalWidget == kDefaultWidgetId) 
				{	
					// all dialog fields valid
					// Execute all the backlogged commands
					dialogController->SetPreviewModeOn( kTrue );
				}				
				else 
				{	
					// a dialog field has some bad data. Set preview data back to off(but don't notify)
					InterfacePtr<ITriStateControlData> tristateData(view,IID_IPREVIEWCONTROLDATA);
					tristateData->Deselect(kTrue,kFalse);
					
					// Try and select the control as the keyboard target
					dialogController->SelectDialogWidget(illegalWidget);
				}
				
			}
			else if (theChange == kFalseStateMessage) 
			{
				// The user just turned off the preview button
				// Start buffering all commands
				dialogController->SetPreviewModeOn( kFalse );
			}

			InterfacePtr<ICommand> previewDialogCmd(CmdUtils::CreateCommand(kPreviewDialogCmdBoss));
			InterfacePtr<IBoolData> data(previewDialogCmd, IID_IBOOLDATA);
			data->Set(dialogController->GetPreviewModeOn());
			CmdUtils::ProcessCommand(previewDialogCmd);
		}
	}
}

void CDialogObserver::AutoAttach()
{
	InterfacePtr<ITriStateControlData> previewControlData(this,IID_IPREVIEWCONTROLDATA);
	InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
	ASSERT(panelData != nil);
	if (!fIsDialogInitialized)
	{
		InterfacePtr<IDialogController> dialogController(this, IID_IDIALOGCONTROLLER);
		ASSERT_MSG(dialogController != nil, "CDialogObserver::AutoAttach: Did you forget to add a CDialogController to your boss?");
		
		// Notify the DialogCommandManager the initial state of the preview checkbox
		// by sending it a preview command.
		// Only check for preview Widget here, not the PreviewControlData interface
		// That can be set in DialogController::Initialize()
		IControlView* previewButton = panelData->FindWidget(kPreviewButtonWidgetID);
		if (previewButton != nil || previewControlData != nil)
		{
			if (previewButton != nil)
				dialogController->SetPreviewModeOn( dialogController->GetTriStateControlData(kPreviewButtonWidgetID, panelData) == ITriStateControlData::kSelected);
			else if (previewControlData != nil)
				dialogController->SetPreviewModeOn( previewControlData->GetState()	== ITriStateControlData::kSelected);
			
			InterfacePtr<ICommand> previewDialogCmd(CmdUtils::CreateCommand(kPreviewDialogCmdBoss));
			InterfacePtr<IBoolData> data(previewDialogCmd, IID_IBOOLDATA);
			data->Set(dialogController->GetPreviewModeOn());
			
			//Process the command now since we have installed interceptor before show dialog 
			CmdUtils::ProcessCommand(previewDialogCmd);
		}
		
		// Attach to the dialog's window so we can catch when the window is closed.
		// For modal dialogs, the window can only be close by clicking ok and cancel.
		// Because modeless dialogs have a close box, the dialog can be closed behind
		// our back.  When the dialog is closed with the close box, we have to carefully
		// remove our custom dialog event handler.
		InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
		InterfacePtr<IDialog> dialog((IDialog*) parentHolder->QueryParentFor(IID_IDIALOG));
		ASSERT(dialog != nil);
		InterfacePtr<ISubject> subject(dialog, IID_ISUBJECT);
		if (subject)
			subject->AttachObserver(this, IID_IWINDOW);
		
		fIsDialogInitialized = kTrue;
	}
	
	if (previewControlData != nil)
	{
		InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
		if (subject)
			subject->AttachObserver(this, IID_IPREVIEWCONTROLDATA);
	}

	// ----- By default we attach to the Ok, Cancel, and Preview buttons, which are defined to be
	//		 the widgets with Id kOKButtonWidgetID, kCancelButton_WidgetID, and kPreviewButtonWidgetID respectively.
	//       These buttons may not exist for every dialog
	{
		AttachToWidget(kOKButtonWidgetID, IID_IBOOLEANCONTROLDATA, panelData);
		AttachToWidget(kCancelButton_WidgetID, IID_IBOOLEANCONTROLDATA, panelData);
		AttachToWidget(kPreviewButtonWidgetID, IID_ITRISTATECONTROLDATA, panelData);
	}
}

void CDialogObserver::AutoDetach()
{
	InterfacePtr<ITriStateControlData> previewControlData(this,IID_IPREVIEWCONTROLDATA);
	if (previewControlData != nil)
	{
		InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
		if (subject)
			subject->DetachObserver(this, IID_IPREVIEWCONTROLDATA);
	}
	
	// ----- By default we detach from the Ok, Cancel, and Preview buttons, which are defined to be
	//		 the widgets with Id kOKButtonWidgetID, kCancelButton_WidgetID, and kPreviewButtonWidgetID respectively.
	//       These buttons may not exist for every dialog
	InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
	ASSERT(panelData != nil);
	{
		DetachFromWidget(kOKButtonWidgetID, IID_IBOOLEANCONTROLDATA, panelData);
		DetachFromWidget(kCancelButton_WidgetID, IID_IBOOLEANCONTROLDATA, panelData);
		DetachFromWidget(kPreviewButtonWidgetID, IID_ITRISTATECONTROLDATA, panelData);
	}
}

void CDialogObserver::CloseDialog(bool16 windowAlreadyClosed)
{
	// Detach from the dialog's window so we can catch when the window is closed.
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IDialog> dialog((IDialog*) parentHolder->QueryParentFor(IID_IDIALOG));
	if (dialog) 
	{
		InterfacePtr<ISubject> subject(dialog, IID_ISUBJECT);
		if (subject)
			subject->DetachObserver(this, IID_IWINDOW);
	}
	
	if (windowAlreadyClosed) 
	{
		bool16 dialogOpen = dialog->IsOpen();	
		dialog->CleanUpAfterClose();
		
		InterfacePtr<IDialogController> dialogController(this, IID_IDIALOGCONTROLLER);
		if(dialogController)
			dialogController->DialogClosing(); //notify the controller.
		
		// Normally the dialog gets released by the CloseDialogCmd.  But the path we
		// came to get here was from the user clicking the dialog's close box.	That simply
		// fires off a CloseWindowCmd and the dialog never gets released.  We manually
		// release the dialog here.	
		if (dialogOpen)
			dialog->Release();
	} 
	else
	{
		dialog->Close();
        
        //Sending Dialog Closed service notification as it is required to
        //show Properties Panel FTUE after any modal dialog comes up on
        //opening the document.
	}

	fIsDialogInitialized = kFalse;		// reset so next time dialog is opened it will reinitialize the fields
}

void CDialogObserver::FireOffEndDialogCmd(bool16 hitOK)
{
	// hkhalfal: GlobalErrorStatePreserver followed by setting global error to success 
	GlobalErrorStatePreserver errState;
	ErrorUtils::PMSetGlobalErrorCode(kSuccess);
	
	InterfacePtr<ICommand> endDialogCmd(CmdUtils::CreateCommand(kEndDialogCmdBoss));
	InterfacePtr<IBoolData> data(endDialogCmd, IID_IBOOLDATA);
	data->Set(hitOK);
	
	CmdUtils::ProcessCommand(endDialogCmd);
}

void CDialogObserver::SetDialogValidationStatusFailed(bool16 bStatus) 
{
	InterfacePtr<IWidgetParent> parentPtr(this, UseDefaultIID());
	//We set the following flag If dialog validation fails.
	InterfacePtr<IBoolData> dataInvalid((IBoolData *)parentPtr->QueryParentFor(IID_IDIALOGVALIDATIONFAILED));

	if (dataInvalid )
	{
		dataInvalid->Set(bStatus);
	}
}

void CDialogObserver::SetCloseOnCancel(bool16 shouldCloseOnCancel) 
{
	fCloseOnCancel = shouldCloseOnCancel;
}
