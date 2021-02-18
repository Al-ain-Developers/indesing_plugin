//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicselectabledialog/BscSlDlgActionComponent.cpp $
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
#include "IDialog.h"
#include "IDialogCreator.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IPanelControlData.h"
#include "ISelectableDialogSwitcher.h"
#include "ISession.h"

// General includes:
#include "CAlert.h"
#include "CActionComponent.h"

// Project includes:
#include "BscSlDlgID.h"


/** Implements the actions that are executed when the plug-in's
	menu items are selected. 
  
	@ingroup basicselectabledialog
	
*/
class BscSlDlgActionComponent : public CActionComponent
{
public:
	/** Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	BscSlDlgActionComponent(IPMUnknown* boss);

	/** Destructor.
	*/
	~BscSlDlgActionComponent();

	/**	The action component should do the requested action.
		This is where the menu item's action is taken.
		When a menu item is selected, the Menu Manager determines
		which plug-in is responsible for it, and calls its DoAction
		with the ID for the menu item chosen. 

		@see IActionComponent::DoAction
		*/
	void DoAction(IActiveContext* ac, 
				  ActionID actionID, 
				  GSysPoint mousePoint = kInvalidMousePoint, 
				  IPMUnknown* widget = nil);

private:
	/** Pops this plug-in's about box. */
	void DoAbout();

	/** Opens this plug-in's dialog. 
		@param isTabStyle tells this function if the current dialog is tab style or not
	*/
	void DoBasicSelectableDialog(bool16 isTabStyle = kFalse);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(BscSlDlgActionComponent, kBscSlDlgActionComponentImpl)

/* Constructor
*/
BscSlDlgActionComponent::BscSlDlgActionComponent(IPMUnknown* boss)
	: CActionComponent(boss)
{
}

/* Destructor
*/
BscSlDlgActionComponent::~BscSlDlgActionComponent()	
{
	// Add code to delete extra private data, if any.
}


/* DoAction
*/
void BscSlDlgActionComponent::DoAction(IActiveContext* ac, 
									 ActionID actionID, 
									 GSysPoint mousePoint,
									 IPMUnknown* widget)
{
	switch (actionID.Get())
	{
	case kBscSlDlgAboutActionID:
		{
			this->DoAbout();
			break;
		}   

	case kBscSlDlgDialogActionID:
		{
			this->DoBasicSelectableDialog();
			break;
		}

	case kBscSlDlgTabDialogActionID:
		{
			this->DoBasicSelectableDialog(kTrue);
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
void BscSlDlgActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
	   kBscSlDlgAboutBoxStringKey,			// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

/* DoBasicSelectableDialog
*/
void BscSlDlgActionComponent::DoBasicSelectableDialog(bool16 isTabStyle)
{
	//RsrcID dialogID = kBscSlDlgDialogResourceID;
	//WidgetID panelID = kYangPanelWidgetID;
	do
	{
		// Get the registered services, including our selectable dialog service:
		InterfacePtr<IK2ServiceRegistry> sRegistry(GetExecutionContextSession(), UseDefaultIID());
		if (sRegistry == nil)
		{
			ASSERT_FAIL("BscSlDlgActionComponent::DoBasicSelectableDialog: sRegistry invalid");
			break;
		}

		// The service is provided based on the service ID and the boss passed in 
		ClassID classID;
		if (isTabStyle)
		{
			classID = kBscSlDlgTabDialogBoss;
		}
		else
		{
			classID = kBscSlDlgDialogBoss;
		}
		InterfacePtr<IK2ServiceProvider> 
			sdService(sRegistry->QueryServiceProviderByClassID(kSelectableDialogServiceImpl, classID));

		if (sdService == nil)
		{
			ASSERT_FAIL("BscSlDlgActionComponent::DoBasicSelectableDialog: sdService invalid");
			break;
		}

		// This is an interface to our service, which will end up calling our 
		// plug-in's dialog creator implementation:
		InterfacePtr<IDialogCreator> dialogCreator(sdService, IID_IDIALOGCREATOR);
		if (dialogCreator == nil)
		{
			ASSERT_FAIL("BscSlDlgActionComponent::DoBasicSelectableDialog: dialogCreator invalid");
			break;
		}

		// This is our CreateDialog, which loads the dialog from our resource:
		IDialog* dialog = dialogCreator->CreateDialog();
		if (dialog == nil)
		{
			ASSERT_FAIL("BscSlDlgActionComponent::DoBasicSelectableDialog: could not create dialog");
			break;
		}

		// The panel data will be the selectable panel of the dialog:
		InterfacePtr<IPanelControlData> panelData(dialog, UseDefaultIID());
		if (panelData == nil)
		{
			ASSERT_FAIL("BscSlDlgActionComponent::DoBasicSelectableDialog: panelData invalid");
			break;
		}

		// Find the panel:
		WidgetID    widgetID;
		if (isTabStyle)
		{
			widgetID = kBscSlDlgTabDialogWidgetID;
		}
		else
		{
			widgetID = kBscSlDlgDialogWidgetID;
		}
		IControlView* dialogView = panelData->FindWidget(widgetID);
		if (dialogView == nil)
		{
			ASSERT_FAIL("BscSlDlgActionComponent::DoBasicSelectableDialog: dialogView invalid");
			break;
		}

		// The dialog switcher controls how the panels are switched between:
		InterfacePtr<ISelectableDialogSwitcher> 
			dialogSwitcher(dialogView, IID_ISELECTABLEDIALOGSWITCHER);
		if (dialogSwitcher == nil)
		{
			ASSERT_FAIL("BscSlDlgActionComponent::DoBasicSelectableDialog: dialogSwitcher invalid");
			break;
		}

		dialogSwitcher->SetDialogServiceID(kBscSlDlgService);

		// Sets default panel.
		dialogSwitcher->SwitchDialogPanelByID(kYinPanelWidgetID);

		// Open the dialog.
		dialog->Open(); 

	} while (false);            
}

// End, BscSlDlgActionComponent.cpp.

