//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/dialogs/selectabledialogs/CSelectableDialogController.cpp $
//  
//  Owner: Tom Taylor
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

#include "CSelectableDialogController.h"

// ----- Interface Includes -----

#include "IPanelControlData.h"
#include "IControlView.h"
#include "ISubject.h"
#include "IDialog.h"
#include "ITextControlData.h"
#include "IWidgetParent.h"
#include "IKeyFocusHandler.h"
#include "ICommand.h"
#include "IBoolData.h"
#include "IEventHandler.h"
#include "IWorkspace.h"
#include "IStringListControlData.h"
#include "IObserver.h"
#include "IDialogMgr.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ISelectableDialogSwitcher.h"
#include "IPanelCreator.h"

// ----- Implementation Includes -----

#include "CmdUtils.h"
#include "PMLocaleIds.h"
#include "PMLocaleId.h"

#include "RsrcSpec.h"
#include "CoreResTypes.h"

// BP 04/24/01: moved to  .../source/components/WidgetBin/WidgetBinImpl.cpp
// CREATE_PMINTERFACE(CSelectableDialogController, kCSelectableDialogControllerImpl)

//========================================================================================
// CLASS CSelectableDialogController
//========================================================================================

CSelectableDialogController::CSelectableDialogController(IPMUnknown *boss) :
	CDialogController(boss)
{
}

CSelectableDialogController::~CSelectableDialogController()
{
}

void CSelectableDialogController::ResetDialogFields(IActiveContext* dlgContext)
{
	CDialogController::ResetDialogFields(dlgContext);

	InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);
	ASSERT_MSG(panelSwitcher != nil, "CSelectableDialogController::InitializeFields - Hey, you forgot to add a SelectableDialogSwitcher interface to the boss");

	// Reset the frontmost panel, if there is one.
	int32 currentPanel = panelSwitcher->GetCurrentPanelIndex();
	if (currentPanel >= 0) {
		WidgetID panelWidgetID = panelSwitcher->GetPanelWidgetID(currentPanel);

		InterfacePtr<IPanelControlData> groupPanelData(panelSwitcher->QueryGroupPanelControlData());
		IControlView* dialogPanel = groupPanelData->FindWidget(panelWidgetID);
		if (dialogPanel) {
			InterfacePtr<IDialogController> dialogPanelController(dialogPanel, IID_IDIALOGCONTROLLER);
			if (dialogPanelController)
				dialogPanelController->ResetDialog();
		}
	}
}

void CSelectableDialogController::ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId)
{
	// Tell each dialog panel to apply its fields
	InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);
	InterfacePtr<IPanelControlData> groupPanelData(panelSwitcher->QueryGroupPanelControlData());
	
	int32 dialogPanelCount = groupPanelData->Length();
	for (int32 i = 0; i < dialogPanelCount; i++) {
		IControlView* dialogPanel = groupPanelData->GetWidget(i);
		InterfacePtr<IDialogController> dialogPanelController(dialogPanel, IID_IDIALOGCONTROLLER);

		// Only ask panels that have been initialized to apply themselves.  If a user never
		// turns to a panel, it doesn't ever get initialized.  This is just a small optimization.
		if (dialogPanelController != nil && dialogPanelController->HasBeenInitialized())
			dialogPanelController->ApplyDialog(widgetId);
	}
}

WidgetID CSelectableDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	// Ask each dialog panel to validate
	InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);
	InterfacePtr<IPanelControlData> groupPanelData(panelSwitcher->QueryGroupPanelControlData());
	
	int32 dialogPanelCount = groupPanelData->Length();
	for (int32 i = 0; i < dialogPanelCount; i++) {
		IControlView* dialogPanel = groupPanelData->GetWidget(i);
		InterfacePtr<IDialogController> dialogPanelController(dialogPanel, IID_IDIALOGCONTROLLER);

		// Only ask panels that have been initialized to validate themselves.  If a user never
		// turns to a panel, it doesn't ever get initialized.  This is just a small optimization.
		if (dialogPanelController != nil && dialogPanelController->HasBeenInitialized()) {
			WidgetID illegalWidget = dialogPanelController->ValidateDialog();
			
			// return the first bad field
			if (illegalWidget != kNoInvalidWidgets) {
				// Make sure the panel with the bad data is frontmost so the user won't get confused.
				WidgetID panelID = dialogPanel->GetWidgetID();
				WidgetID currentPanelWidgetID = panelSwitcher->GetPanelWidgetID(panelSwitcher->GetCurrentPanelIndex());
				if (panelID != currentPanelWidgetID)	// only switch if we have to
					panelSwitcher->SwitchDialogPanelByID(panelID);
				return illegalWidget;
			}
		}
	}
	return kNoInvalidWidgets;
}


void CSelectableDialogController::SelectDialogWidget(const WidgetID& widgetId)
{
	// We're told to select a particular widget.  We've got to make sure
	// that the panel containing the widgetId is the one that is visible.
	InterfacePtr<ISelectableDialogSwitcher> dialogSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);
	InterfacePtr<IPanelControlData> groupPanelData(dialogSwitcher->QueryGroupPanelControlData());
	
	int32 dialogPanelCount = groupPanelData->Length();
	for (int32 i = 0; i < dialogPanelCount; i++) {
		IControlView* dialogPanel = groupPanelData->GetWidget(i);
		InterfacePtr<IPanelControlData> panelControlData(dialogPanel, IID_IPANELCONTROLDATA);
		
		if (panelControlData != nil) {
			if (panelControlData->FindWidget(widgetId) != nil) {
				WidgetID panelID = dialogPanel->GetWidgetID();
				WidgetID currentPanelWidgetID = dialogSwitcher->GetPanelWidgetID(dialogSwitcher->GetCurrentPanelIndex());
				if (panelID != currentPanelWidgetID)	// only switch if we have to
					dialogSwitcher->SwitchDialogPanelByID(panelID);
				break;
			}
		}
	}
	// Now tell the base class to really select the widget.  We fall through to here
	// even if we never found the widget to be in one of the panel's hierarchy.
	CDialogController::SelectDialogWidget(widgetId);
}

void CSelectableDialogController::UserCancelled()
{
	// Tell each dialog panel that its being cancelled
	InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);
	InterfacePtr<IPanelControlData> groupPanelData(panelSwitcher->QueryGroupPanelControlData());
	
	int32 dialogPanelCount = groupPanelData->Length();
	for (int32 i = 0; i < dialogPanelCount; i++) {
		IControlView* dialogPanel = groupPanelData->GetWidget(i);
		InterfacePtr<IDialogController> dialogPanelController(dialogPanel, IID_IDIALOGCONTROLLER);

		// Only ask panels that have been initialized to apply themselves.  If a user never
		// turns to a panel, it doesn't ever get initialized.  This is just a small optimization.
		if (dialogPanelController != nil && dialogPanelController->HasBeenInitialized())
			dialogPanelController->UserCancelled();
	}
}

void CSelectableDialogController::ClosingDialog(IActiveContext* lastChanceToUseMyContext)
{
	InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);
	panelSwitcher->HideNonAutoShownPanels();

	// Tell each dialog panel which has been shown that it is closing.
	InterfacePtr<IPanelControlData> groupPanelData(panelSwitcher->QueryGroupPanelControlData());
	
	int32 dialogPanelCount = groupPanelData->Length();
	for (int32 i = 0; i < dialogPanelCount; i++) 
	{
		IControlView* dialogPanel = groupPanelData->GetWidget(i);
		InterfacePtr<IDialogController> dialogPanelController(dialogPanel, IID_IDIALOGCONTROLLER);

		// Only ask panels that have been initialized to apply themselves.  If a user never
		// turns to a panel, it doesn't ever get initialized.  This is just a small optimization.
		if (dialogPanelController != nil && dialogPanelController->HasBeenInitialized())
			dialogPanelController->DialogClosing();
	}
}
