//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentexteditor/HidTxtEdActionComponent.cpp $
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
#include "ITextFocus.h"
#include "ITextModel.h"
#include "ISelectionUtils.h"
#include "IActionStateList.h"
#include "IApplication.h"
#include "IDialogMgr.h"
#include "IDialogController.h"
#include "IIntData.h"
#include "IWindow.h"
#include "IActiveContext.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "Utils.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "PMLocaleIds.h"
#include "RsrcSpec.h"

// HiddenText includes:
#include "HidTxtID.h"
#include "IHidTxtSuite.h"
#include "IHidTxtModel.h"

// Project includes:
#include "HidTxtEdID.h"


/** Implements the actions that are executed when the plug-in's
	menu items are selected.

	
	@ingroup hiddentexteditor
*/
class HidTxtEdActionComponent : public CActionComponent
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		HidTxtEdActionComponent(IPMUnknown* boss);

		/** Called by the framework to allow actions to be enabled or disabled
			dependent on the capability of the selection.
			@param ac context in which the action is to be performed.
			@param listToUpdate list containing items to be enabled disabled.
			@param mousePoint ontains the global mouse location at time of event causing action (e.g. context menus), kInvalidMousePoint otherwise.
			@param widget the widget that invoked the action or nil otherwise
		*/
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

		/** Called by the framework when the action is to be performed.
			@param ac context in which the action is to be performed.
			@param actionID identifies the action to be performed.
			@param mousePoint ontains the global mouse location at time of event causing action (e.g. context menus), kInvalidMousePoint otherwise.
			@param widget the widget that invoked the action or nil otherwise
		 */
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

	private:
		/**
		 */
		void DoAbout();

		/**
		 */
		void DoCreate();

		/**
		 */
		void DoModify();

		/** 
		 */
		void DoDelete(IActiveContext* ac);

		/**
		 */
		void InvokeEditDialog(int32 mode);

};

/* 
*/
CREATE_PMINTERFACE(HidTxtEdActionComponent, kHidTxtEdActionComponentImpl)

/*
*/
HidTxtEdActionComponent::HidTxtEdActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/*
*/
void HidTxtEdActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	do {			
		ASSERT(listToUpdate);
		if(listToUpdate==nil) {
			break;
		}
		InterfacePtr<IHidTxtSuite> hidTxtSuite(ac->GetContextSelection(), UseDefaultIID()); 
		ASSERT(hidTxtSuite);
		if (hidTxtSuite == nil) {
			break;
		}

		for(int i=0; i < listToUpdate->Length(); i++) 
		{
			ActionID actionID = listToUpdate->GetNthAction(i);
			switch (actionID.Get())
			{
				case kHidTxtEdCreateActionID:
				{
					if(hidTxtSuite->CanCreateHiddenText() == kTrue) {
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
					else {
						listToUpdate->SetNthActionState(i,kDisabled_Unselected);
					}
					break;
				}

				case kHidTxtEdModifyActionID:
				{
					if(hidTxtSuite->CanModifyHiddenText() == kTrue) {
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
					else {
						listToUpdate->SetNthActionState(i,kDisabled_Unselected);
					}
					break;
				}

				case kHidTxtEdDeleteActionID:
				{
					if(hidTxtSuite->CanDeleteHiddenText() == kTrue) {
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
					else {
						listToUpdate->SetNthActionState(i,kDisabled_Unselected);
					}
					break;
				}			

				default: 
				{
					break;
				}
			} // end switch

		} // end for

	} while(false);
}

/*
*/
void HidTxtEdActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kHidTxtEdPopupAboutThisActionID:
		case kHidTxtEdAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kHidTxtEdCreateActionID:
		{
			this->DoCreate();
			break;
		}

		case kHidTxtEdModifyActionID:
		{
			this->DoModify();
			break;
		}

		case kHidTxtEdDeleteActionID:
		{
			this->DoDelete(ac);
			break;
		}

		default:
		{
			break;
		}
	}
}

/*
*/
void HidTxtEdActionComponent::DoAbout()
{
	// Bring up the About box
	CAlert::ModalAlert
	(
	   kHidTxtEdAboutBoxStringKey,			// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

/*
*/
void HidTxtEdActionComponent::DoCreate()
{
	this->InvokeEditDialog(kHidTxtEdCreate);
}

/*
*/
void HidTxtEdActionComponent::DoModify()
{
	this->InvokeEditDialog(kHidTxtEdModify);
}

/*
*/
void HidTxtEdActionComponent::DoDelete(IActiveContext* ac)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IHidTxtSuite> hidTxtSuite(ac->GetContextSelection(), UseDefaultIID()); 
		ASSERT(hidTxtSuite);
		if (hidTxtSuite == nil) {
			break;
		}
		status = hidTxtSuite->DeleteHiddenText();

	} while(false);
	if (status != kSuccess) {
		CAlert::WarningAlert(kHidTxtEdDeleteFailedStringKey);
	}
}

/*
*/
void HidTxtEdActionComponent::InvokeEditDialog(int32 mode)
{
	do {
		// Get the applicaton interface and the DialogMgr:	
		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		ASSERT(application != nil);
		if (application == nil) {
			break;
		}
		InterfacePtr<IDialogMgr> dialogMgr(application, UseDefaultIID());
		ASSERT(dialogMgr != nil);
		if (dialogMgr == nil) {
			break;
		}

		// We need to load the plug-ins resource:
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kHidTxtEdPluginID,			// Our Plug-in ID. 
			kViewRsrcType,				// This is the kViewRsrcType.
			kSDKDefDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also
		// the type of dialog being created (kMovableModal).
		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
		ASSERT(dialog != nil);
		if (dialog == nil) {
			break;
		}
		IControlView* dialogView = dialog->GetDialogPanel();
		InterfacePtr<IDialogController> dialogController(dialogView, IID_IDIALOGCONTROLLER);
		ASSERT(dialogController != nil);
		if (dialogController == nil) {
			break;
		}
		
		// Set the dialog mode
		InterfacePtr<IIntData> modeIntData(dialogController, UseDefaultIID());
		ASSERT(modeIntData != nil);
		if (modeIntData == nil) {
			break;
		}
		modeIntData->Set(mode);
		
		// Set appropriate window title based on mode
		InterfacePtr<IWindow> window(dialog, UseDefaultIID());
		ASSERT(window != nil);
		if (window == nil) {
			break;
		}
		
		PMString windowTitle;
		switch (mode) {
		case kHidTxtEdCreate:
			windowTitle = kHidTxtEdCreateDialogTitleKey;
			break;
		case kHidTxtEdModify:
			windowTitle = kHidTxtEdModifyDialogTitleKey;
			break;
		}
		
		window->SetTitle(windowTitle);
		
		// Open causes the dialog to be displayed and then returns immediately
		//	so WaitForDialog() is used.
		dialog->Open();
		dialog->WaitForDialog();
	}
	while(false);
}

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, HidTxtEdActionComponent.cpp.




