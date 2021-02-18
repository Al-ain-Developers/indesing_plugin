//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflowui/XDocBkUIActionComponent.cpp $
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
#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IDialog.h"
#include "IDialogCreator.h"
#include "IDocument.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IPanelControlData.h"
#include "ISelectableDialogSwitcher.h"
#include "IXDocBkFacade.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "SDKFileHelper.h"
#include "SDKLayoutHelper.h"
#include "Utils.h"

// Project includes:
#include "XDocBkUIID.h"

/** Implements IActionComponent; performs the actions that are executed when the plug-in's
	menu items are selected, delegating mainly to IXDocBkFacade.
	@ingroup xdocbookworkflowui 
	
*/
class XDocBkUIActionComponent : public CActionComponent
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	XDocBkUIActionComponent(IPMUnknown* boss);

	/** The action component should perform the requested action.
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
	

private:
	/** Encapsulates functionality for the about menu item. */
	void DoAbout();

	/** Encapsulates functionality for the SetOptions menu item. */
	void DoSetOptions(IActiveContext* ac);


	
	void DoUnitTestFacade(IActiveContext* ac);


};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XDocBkUIActionComponent, kXDocBkUIActionComponentImpl)

/* XDocBkUIActionComponent Constructor
*/
XDocBkUIActionComponent::XDocBkUIActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void XDocBkUIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
	
	case kXDocBkUIAboutActionID:
		{
			this->DoAbout();
			break;
		}

	case kXDocBkUISetOptionsActionID:
		{
			this->DoSetOptions(ac);
			break;
		}

	
	case kXDocBkUIUnitTestActionID:
		{
			this->DoUnitTestFacade(ac);
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
void XDocBkUIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kXDocBkUIAboutBoxStringKey,			// Alert string
		kOKString,							// OK button
		kNullString,						// No second button
		kNullString,						// No third button
		1,									// Set OK button to default
		CAlert::eInformationIcon			// Information icon.
	);
}


/* 
*/
void XDocBkUIActionComponent::DoUnitTestFacade(IActiveContext* ac)
{
	do
	{
		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if (!facade)
		{
			break;
		}
		facade->UnitTestFacade();

	} while (kFalse);
}


/* DoSetOptions
*/
void XDocBkUIActionComponent::DoSetOptions(IActiveContext* ac)
{
	do
	{
		InterfacePtr<IK2ServiceRegistry> serviceReg(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
		ASSERT(serviceReg);
		if (!serviceReg)
		{
			break;
		}
		InterfacePtr<IK2ServiceProvider> selectableDialogService(serviceReg->QueryServiceProviderByClassID(kSelectableDialogServiceImpl, kGlobalPrefsDialogBoss));
		ASSERT(selectableDialogService);
		if (!selectableDialogService)
		{
			break;
		}

		// Create a dialog using the global prefs selectable dialog service provider
		InterfacePtr<IDialogCreator> dialogCreator(selectableDialogService, IID_IDIALOGCREATOR);
		ASSERT(dialogCreator);
		if (!dialogCreator)
		{
			break;
		}
		IDialog* dialog = dialogCreator->CreateDialog();
		//Framework processes kCloseWinCmdBoss, which releases the reference
		//in case you're wondering who owns this
		ASSERT(dialog);
		if (!dialog)
		{
			break;
		}
		// Set the panel in the dialog to our preferences panel
		InterfacePtr<IPanelControlData> panelData(dialog, UseDefaultIID());
		ASSERT(panelData);
		if (!panelData)
		{
			break;
		}
		IControlView* dialogView = panelData->FindWidget(kPreferencesDialogWidgetID);
		InterfacePtr<ISelectableDialogSwitcher> dialogSwitcher(dialogView, IID_ISELECTABLEDIALOGSWITCHER);
		ASSERT(dialogSwitcher);
		if (!dialogSwitcher)
		{
			break;
		}
		// Set the service to service Impl for the global prefs switchable dialog
		dialogSwitcher->SetDialogServiceID(kGlobalPrefsDialogServiceImpl);
		dialogSwitcher->SwitchDialogPanelByID(kXDocBkUIPanelWidgetID);	// Our panel widget

		// Open the dialog
		dialog->Open();
	} while (kFalse);       
}

//  Code generated by DollyXS code generator
// End, XDocBkUIActionComponent.cpp.
