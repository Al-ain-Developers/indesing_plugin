//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabelui/FrmLblUIActionComponent.cpp $
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
#include "ISession.h"
#include "IApplication.h"
#include "IDialogMgr.h"
#include "IDialog.h"
#include "IActionStateList.h"
#include "IBoolData.h"
#include "IWorkspace.h"

// Dialog-specific resource includes:
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "UIDList.h"
#include "Utils.h"

// Project includes:
#include "FrmLblUIID.h"
#include "FrmLblID.h"
#include "IFrmLblDataFacade.h"


/** Implements IActionComponent; performs the actions that are executed when the plug-in's
	menu items are selected.
	@ingroup framelabelui

*/
class FrmLblUIActionComponent : public CActionComponent
{
	public:
		/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		FrmLblUIActionComponent(IPMUnknown* boss);

		/** 
		The action component should perform the requested action.
		This is where the menu item's action is taken.
		When a menu item is selected, the Menu Manager determines
		which plug-in is responsible for it, and calls its DoAction
		with the ID for the menu item chosen.

		@param actionID identifies the menu item that was selected.
		@param ac active context
		@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
		@param widget contains the widget that invoked this action. May be nil. 
		*/
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

		/**
		Called to determine if an action should be enabled.
		This call enables the action that pops this
		plug-in's dialog.
		@see CActionComponent::UpdateActionStates
		*/
		void UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();
		
		/** Opens this plug-in's dialog. */
		void DoDialog();

	    /** Update FrameLabel print preference setting*/	
        ErrorCode UpdateFrameLabelPrintPreference();

		/** Get FrameLabel print preference setting*/	
		ErrorCode GetFrameLabelPrintPreference();

	private:
		/** Set to kTrue if we are printing framelable adornment. */
		bool16             fPrintFrmLbl;

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(FrmLblUIActionComponent, kFrmLblUIActionComponentImpl)

/* FrmLblUIActionComponent Constructor
*/
FrmLblUIActionComponent::FrmLblUIActionComponent(IPMUnknown* boss)
	: CActionComponent(boss),fPrintFrmLbl(kFalse)
{		
}

/* DoAction
*/
void FrmLblUIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kFrmLblUIAboutActionID:
		{
			this->DoAbout();
			break;
		}
		case kFrmLblUIDialogActionID:
		{
			this->DoDialog();
			break;
		}
		//update print preference 
		case  kFrmLblUIPrintFrmLblActionID:
		{		
			this->UpdateFrameLabelPrintPreference();
			break;
		}
		default:
		{
			break;
		}
	}
}

/* DoAbout
*/
void FrmLblUIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kFrmLblUIAboutBoxStringKey,				// Alert string
		kOKString, 								// OK button
		kNullString, 							// No second button
		kNullString, 							// No third button
		1,										// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
	);
}

/* DoDialog
*/
void FrmLblUIActionComponent::DoDialog()
{
	do
	{
		// Get the application interface and the DialogMgr.	
		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		ASSERT(application);
		if (application == nil) {	
			break;
		}
		InterfacePtr<IDialogMgr> dialogMgr(application, UseDefaultIID());
		ASSERT(dialogMgr);
		if (dialogMgr == nil) {
			break;
		}

		// Load the plug-in's resource.
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kFrmLblUIPluginID,			// Our Plug-in ID  
			kViewRsrcType,				// This is the kViewRsrcType.
			kSDKDefDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also
		// the type of dialog being created (kMovableModal).
		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
		ASSERT(dialog);
		if (dialog == nil) {
			break;
		}
		// Open the dialog.
		dialog->Open(); 

	} while (false);			
}

/* UpdateActionStates
*/
void FrmLblUIActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	do
	{
		if (ac == nil)
		{
			ASSERT_FAIL("IActiveContext is invalid");
			break;
		}

		int32  listToUpdateLength = listToUpdate->Length();

		//set the print preference menu item state
		for (int32 iter = 0; iter < listToUpdateLength; iter++)
		{
			int16 actionState = kEnabledAction;
			ActionID actionID = listToUpdate->GetNthAction(iter);
			if (actionID.Get() == kFrmLblUIPrintFrmLblActionID)
			{
				if (GetFrameLabelPrintPreference() != kSuccess)
				{
					break;
				}
				if (fPrintFrmLbl == kTrue)
				{
					actionState |= kSelectedAction;	
				
				}	
			}
			//set and initial the menu item action state
			listToUpdate->SetNthActionState(iter, actionState);
		}
	} while (false);	
}

/* UpdateFrameLabelPrintPreference
*/
ErrorCode FrmLblUIActionComponent::UpdateFrameLabelPrintPreference()
{
	ErrorCode error = kFailure;
	do
	{
	    InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		if (sessionWorkspace == nil)
		{
			ASSERT_FAIL("IWorkspace is invalid");
			break;
		}
		//Set the print preference action state
		error = Utils<IFrmLblDataFacade>()->SetFrameLabelPrintPreference(sessionWorkspace, !fPrintFrmLbl);
		if ( error == kSuccess)
		{
			fPrintFrmLbl = !fPrintFrmLbl;
		}
	
	} while (false);

	return error;
}

/* GetFrameLabelPrintPreference
*/
ErrorCode FrmLblUIActionComponent::GetFrameLabelPrintPreference() 
{
	ErrorCode error = kFailure;
	
	do
	{
		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		if (sessionWorkspace == nil)
		{
			ASSERT_FAIL("IWorkspace is invalid");
			break;
		}

		error = Utils<IFrmLblDataFacade>()->GetFrameLabelPrintPreference(sessionWorkspace, fPrintFrmLbl);
		if (error != kSuccess)
		{
			// Bring up the Error alert box, for the plug-ins dependency checking.
			CAlert::ModalAlert(kFrmLblUIDepChkErrorStringKey,             // Alert string
				kOKString,											// OK button
				kNullString,			                            // No second button
				kNullString,						                // No third button
				1,													// Set OK button to default
				CAlert::eInformationIcon			                // Information icon.
			);
			break;
		}

	} while (false);

	return error;
}