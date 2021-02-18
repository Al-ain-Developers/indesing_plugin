//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUIUtils.cpp $
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

// Interface includes
#include "IApplication.h"
#include "IDialogMgr.h"
#include "IDialogController.h"
#include "IIntData.h"
#include "IWindow.h"
#include "ISession.h"
#include "IDropDownListController.h"
#include "IPalettePanelUtils.h"
#include "IPanelControlData.h"
#include "IUIDListData.h"

// General includes
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "PMLocaleIds.h"
#include "RsrcSpec.h"

// PstLst Includes
#include "PstLstUIUtils.h"
#include "PstLstUIID.h"
#include "PstLstID.h" // from PersistentList plug-in.

/*	PstLstUIUtils::InvokePstLstDialog
*/
void PstLstUIUtils::InvokePstLstDialog(int32 mode, UIDList * &list)
{
	do
	{
		// Get the applicaton interface and the DialogMgr:	
		InterfacePtr<IApplication> iApp(GetExecutionContextSession()->QueryApplication());
		if (iApp == nil)
		{
			ASSERT_FAIL("Application does not exist!");
			break;
		}
		InterfacePtr<IDialogMgr> iDialogMgr(iApp, UseDefaultIID());
		if (iDialogMgr == nil)
		{
			ASSERT_FAIL("Can not create Dialog!");
			break;
		}

		// We need to load the plug-ins resource:
		PMLocaleId nLocale = LocaleSetting::GetLocale();

		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kPstLstUIPluginID,			// Our Plug-in ID. 
			kViewRsrcType,				// This is the kViewRsrcType.
			kSDKDefDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also
		// the type of dialog being created (kMovableModal).
		IDialog* dialog = iDialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);

		if (dialog == nil)
		{
			ASSERT_FAIL("Could not create dialog");
		}
		else
		{	
			IControlView* dialogView = dialog->GetDialogPanel();
			InterfacePtr<IDialogController> iDialogController(dialogView, IID_IDIALOGCONTROLLER);
			if (iDialogController == nil)
			{
				ASSERT_FAIL("Dialog Controller does not exist!");
				break;
			}

			// Set the dialog mode
			InterfacePtr<IIntData> iMode(iDialogController, UseDefaultIID());
			if (iMode == nil)
			{
				ASSERT_FAIL("Can not set dialog mode!");
				break;
			}
			iMode->Set(mode);
			UIDList * dialogList = new UIDList(*list); // We need a new UIDList * because IUIDListData gains ownership
			InterfacePtr<IUIDListData>    iUIDListData (iDialogController, UseDefaultIID ());
			iUIDListData->Set(dialogList);

			// Set appropriate window title based on mode
			InterfacePtr<IWindow> iWindow(dialog, UseDefaultIID());
			if (iWindow == nil)
			{
				ASSERT_FAIL("Dialog window does not exist!");
				break;
			}
			
			PMString windowTitle;
			switch (mode)
			{
			case kPstLstNew:
				windowTitle = kPstLstNewStringKey;
				break;
			case kPstLstModify:
				windowTitle = kPstLstModifyStringKey;
				break;
			}

			iWindow->SetTitle(windowTitle);

			// Open causes the dialog to be displayed and then returns immediately
			//	so WaitForDialog() is used.
			dialog->Open();
			dialog->WaitForDialog();
		}
	}
	while (kFalse);
}

