//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdialog/BscDlgActionComponent.cpp $
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

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"

// Project includes:
#include "BscDlgID.h"


/** Implements IActionComponent based on
	the partial implementation CActionComponent; executes the actions that are executed when the plug-in's
	menu items are selected. 
  
	@ingroup basicdialog
*/
class BscDlgActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscDlgActionComponent(IPMUnknown* boss);

		/**
			The action component should do the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the action manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen. 
			@param ac active context
			@param actionID identifies the menu item that was selected.
			@param mousePoint where the widget was clicked
			@param widget which widget was clicked
			@see CActionComponent::DoAction
			*/
		void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	private:
		/** Pops this plug-in's about box. */
		void DoAbout();

		/** Opens this plug-in's dialog. */
		void DoDialog();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(BscDlgActionComponent, kBscDlgActionComponentImpl)

/* BscDlgActionComponent Constructor
*/
BscDlgActionComponent::BscDlgActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void BscDlgActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	#pragma unused(ac,mousePoint,widget)
	switch (actionID.Get())
	{
		case kBscDlgAboutActionID:
		{
			this->DoAbout();
			break;
		}	

		case kBscDlgDialogActionID:
		{
			this->DoDialog();
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
void BscDlgActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kBscDlgAboutBoxStringKey,		// Alert string
		kOKString, 						// OK button
		kNullString, 					// No second button
		kNullString, 					// No third button
		1,								// Set OK button to default
		CAlert::eInformationIcon		// Information icon.
	);
}

/* DoDialog
*/
void BscDlgActionComponent::DoDialog()
{
	do
	{
		// Get the application interface and the DialogMgr.	
		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		if (application == nil)
		{
			ASSERT_FAIL("BscDlgActionComponent::DoDialog: application invalid"); 
			break;
		}
		InterfacePtr<IDialogMgr> dialogMgr(application, UseDefaultIID());
		if (dialogMgr == nil)
		{ 
			ASSERT_FAIL("BscDlgActionComponent::DoDialog: dialogMgr invalid"); 
			break;
		}

		// Load the plug-in's resource.
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kBscDlgPluginID,			// Our Plug-in ID from BasicDialogID.h. 
			kViewRsrcType,				// This is the kViewRsrcType.
			kSDKDefDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also the type of dialog 
		// being created (kMovableModal). This example demonstrates a re-sizable dialog.
		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal, IDialogMgr::kAllowMultipleCopies, IDialogMgr::kCacheDialog, IDialogMgr::kAllowUserResize);
		if (dialog == nil)
		{ 
			ASSERT_FAIL("BscDlgActionComponent::DoDialog: can't create dialog"); 
			break;
		}

		// Open the dialog.
		dialog->Open(); 
	
	} while (false);			
}

// End, BscDlgActionComponent.cpp.


