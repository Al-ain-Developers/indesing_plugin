//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectPrefsDialogController.cpp $
//  
//  Owner: Heath Horton
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
//  
//  Proj:	AutoCorrectPanel
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "AutoCorrectPrefsDialogController.h"

// Interfaces:
#include "ITriStateControlData.h"
#include "ICmdCollection.h"
#include "ICommand.h"
#include "IControlView.h"
#include "IDialog.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IEventHandler.h"
#include "IAutoCorrectPrefs.h"
#include "IIntData.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ISwatchList.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"
#include "IColorListControlData.h"

// Includes:
#include "CAlert.h"

#include "UIDList.h"
#include "LocaleSetting.h"

// Utility files:
#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "PreferenceUtils.h"
#include "iuicolorutils.h"

// ID.h files:
#include "SpellPanelID.h"



CREATE_PMINTERFACE(AutoCorrectPrefsDialogController, kAutoCorrectPrefsDialogControllerImpl)

//========================================================================================
// CLASS AutoCorrectPrefsDialogController
//========================================================================================

AutoCorrectPrefsDialogController::AutoCorrectPrefsDialogController(IPMUnknown *boss) :
	CDialogController(boss)
{
}

AutoCorrectPrefsDialogController::~AutoCorrectPrefsDialogController()
{
}

void AutoCorrectPrefsDialogController::InitializeDialogFields(IActiveContext* context)
{
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelControlData> panel(parentHolder->GetParent(),IID_IPANELCONTROLDATA);

	// Set controls to their values for document AutoCorrect controls
	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));	
	if (autoCorrectPrefs)
	{
		this->SetTriStateControlData(kAutoCorrectEnableCheckboxWidgetID, autoCorrectPrefs->GetAutoCorrect() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
		this->SetTriStateControlData(kAutoCorrectCapitalizationErrorsCheckboxWidgetID, autoCorrectPrefs->GetAutoCorrectCapitalizationErrors() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
	}
}

// Validate the values in the edit boxes. Validate is all done
// through resources for this dialog.
WidgetID AutoCorrectPrefsDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	WidgetID badWidgetId = kDefaultWidgetId;
	return badWidgetId;
}

void AutoCorrectPrefsDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId) 
{
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelControlData> panel(parentHolder->GetParent(),IID_IPANELCONTROLDATA);

	// Apply the values for the AutoCorrect controls
	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));	
	if (autoCorrectPrefs)
	{
		AutoCorrectList autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();
		bool16 origAutoCorrectEnable = autoCorrectPrefs->GetAutoCorrect();
		bool16 origAutoCorrectCapitalizationErrors = autoCorrectPrefs->GetAutoCorrectCapitalizationErrors();

		ITriStateControlData::TriState triAutoCorrectEnable = this->GetTriStateControlData(kAutoCorrectEnableCheckboxWidgetID);
		ITriStateControlData::TriState triAutoCorrectCapitalizationErrors = this->GetTriStateControlData(kAutoCorrectCapitalizationErrorsCheckboxWidgetID);

		bool16 bAutoCorrectEnable = triAutoCorrectEnable == ITriStateControlData::kSelected;
		bool16 bAutoCorrectCapitalizationErrors = triAutoCorrectCapitalizationErrors == ITriStateControlData::kSelected;

		// Send a command if anything changed
		if (origAutoCorrectEnable != bAutoCorrectEnable || origAutoCorrectCapitalizationErrors != bAutoCorrectCapitalizationErrors)
		{
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kAutoCorrectPrefsCmdBoss));
			InterfacePtr<IAutoCorrectPrefs> newPrefs(cmd, IID_IAUTOCORRECTPREFS);	/* grab the prefs interface on the cmd boss */
			ASSERT_MSG(newPrefs != nil, "newPrefs != nil");
			
			newPrefs->SetAutoCorrect(bAutoCorrectEnable);
			newPrefs->SetAutoCorrectCapitalizationErrors(bAutoCorrectCapitalizationErrors);
			newPrefs->SetAutoCorrectList(autoCorrectList);

			CmdUtils::ProcessCommand(cmd);
		}
	}
}
