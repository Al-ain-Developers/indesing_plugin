//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellMenuComponent.cpp $
//  
//  Owner: Bernd Paradies
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

// ----- Interfaces -----

#include "IActionStateList.h"
#include "IApplication.h"
#include "IAutoCorrectPrefs.h"
#include "IDialog.h"
#include "IDialogCreator.h"
#include "IDialogMgr.h"
#include "IEventHandler.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "INoteFindChangeSpelling.h"	
#include "IObserver.h"
#include "IPanelControlData.h"
#include "ISelectableDialogSwitcher.h"
#include "ISession.h"
#include "ISpellPanelOptions.h"
#include "ISpellingPrefs.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CActionComponent.h"
#include "CoreResTypes.h"
#include "CreateObject.h"
#include "LocaleSetting.h"
#include "PMLocaleIds.h"

#include "RsrcSpec.h"
#include "UIDList.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "IWidgetUtils.h"
#include "PreferenceUtils.h"

// ----- ID.h files -----

#include "SpellPanelID.h"

//----------------------------------------------------------------------------------------
// Class SpellMenuComponent
//----------------------------------------------------------------------------------------

class SpellMenuComponent : public CActionComponent
{
public:
				SpellMenuComponent(IPMUnknown *boss);
	
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
		virtual void    UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);


private:
	IDialog * 		CreateTheDialog( RsrcID kDialogRsrcID , IDialog::DialogType nDialogType ) const;
	bool16 		CheckForEnable() const;
};

CREATE_PMINTERFACE(SpellMenuComponent, kSpellMenuComponent)

#define INHERITED	CActionComponent
//---------------------------------------------------------------
// SpellMenuComponent constructor 
//---------------------------------------------------------------

SpellMenuComponent::SpellMenuComponent(IPMUnknown *boss) :
	INHERITED(boss)
{
}

void SpellMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	int32 count = listToUpdate->Length();

	while (count--)
	{
		ActionID actionID = listToUpdate->GetNthAction(count);
		int16 state = kDisabled_Unselected;
		switch (actionID.Get())
		{
			case kSpellCheckActionID:
				state = kEnabledAction;
				break;

			case kDynamicSpellCheckActionID:
			{
				InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
				if (spellingPrefs)
				{
					state = kEnabledAction;
					if (spellingPrefs->GetDynamicSpellCheck())
						state |= kSelectedAction;
				}
			}
			break;

			case kAutoCorrectActionID:
			{
				InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
				if (autoCorrectPrefs)
				{
					state = kEnabledAction;
					if (autoCorrectPrefs->GetAutoCorrect())
						state |= kSelectedAction;
				}
			}
			break;
		}

		listToUpdate->SetNthActionState(count, state);
	}
}


//---------------------------------------------------------------
// SpellMenuComponent::DoAction() 
//---------------------------------------------------------------

void SpellMenuComponent::DoAction(IActiveContext* ac, ActionID id, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (id.Get())
	{
		case kSpellCheckActionID:
		{
			// in InCopy, turn on flag so showing "Skip Tables" warning in galley view
			InterfacePtr<INoteFindChangeSpelling> fcs(GetExecutionContextSession(), UseDefaultIID());
			ASSERT(fcs != nil);
			fcs->SetSpellingWarningSkipTables(true);
		
			IDialog *pDialog = this->CreateTheDialog( kSpellDialogRsrcID, IDialog::kModeless );
			ASSERT_MSG( pDialog != nil, "SpellMenuComponent - can't create Dialog" );
			if( pDialog )
			{
		        pDialog->SetDefaultButton(kSpellSkipButtonID);
				pDialog->Open();

				// Start up spelling, saves the user a click and mimics most other apps with spell check.
				InterfacePtr<IControlView> pStartButton(static_cast<IControlView *>(Utils<IWidgetUtils>()->QueryRelatedWidget(pDialog, kSpellSkipButtonID, IID_ICONTROLVIEW)));
				if (pStartButton && pStartButton->IsEnabled())
				{
					InterfacePtr<IEventHandler> startEH(pStartButton, UseDefaultIID());
					Utils<IWidgetUtils>()->SimulateClick(startEH);
				}
			}
			break;
		}
		case kDynamicSpellCheckActionID:
		{
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSpellingPrefsCmdBoss));
			if (cmd)
			{
				InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));
				ASSERT_MSG(spellingPrefs != nil, "spellingPrefs != nil");
				
				//cmd->SetItemList(UIDList(spellingPrefs));
				
				InterfacePtr<ISpellingPrefs> newPrefs(cmd, IID_ISPELLINGPREFS);
				ASSERT_MSG(spellingPrefs != nil, "spellingPrefs != nil");
				
				newPrefs->SetDynamicSpellCheck(! spellingPrefs->GetDynamicSpellCheck());

				newPrefs->SetCheckMisspelledWords(spellingPrefs->GetCheckMisspelledWords());
				newPrefs->SetCheckRepeatedWords(spellingPrefs->GetCheckRepeatedWords());
				newPrefs->SetCheckCapitalizeWords(spellingPrefs->GetCheckCapitalizeWords());
				newPrefs->SetCheckCapitalizeSentences(spellingPrefs->GetCheckCapitalizeSentences());
				
				newPrefs->SetDynamicSpellMisspelledWordColorIndex(spellingPrefs->GetDynamicSpellMisspelledWordColorIndex());
				newPrefs->SetDynamicSpellRepeatedWordColorIndex(spellingPrefs->GetDynamicSpellRepeatedWordColorIndex());
				newPrefs->SetDynamicSpellUncapitalizedWordColorIndex(spellingPrefs->GetDynamicSpellUncapitalizedWordColorIndex());
				newPrefs->SetDynamicSpellUncapitalizedSentenceColorIndex(spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex());
				
				CmdUtils::ProcessCommand(cmd);
			}
			break;
		}
		case kSpellPrefsActionID:
		{
			RsrcID dialogID = kSpellPrefsPaletteRsrcID;
			WidgetID dialogPanelID = kSpellPrefsDialogPanelWidgetID;

			InterfacePtr<IK2ServiceRegistry>	serviceReg(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
			InterfacePtr<IK2ServiceProvider>	selectableDialogService(serviceReg->QueryServiceProviderByClassID(kSelectableDialogServiceImpl, kGlobalPrefsDialogBoss));
			InterfacePtr<IDialogCreator> dialogCreator(selectableDialogService, IID_IDIALOGCREATOR);
			IDialog* dialog = dialogCreator->CreateDialog();

			InterfacePtr<IPanelControlData> panelData(dialog, IID_IPANELCONTROLDATA);
			IControlView* dialogView = panelData->FindWidget(kPreferencesDialogWidgetID);
			InterfacePtr<ISelectableDialogSwitcher> dialogSwitcher(dialogView, IID_ISELECTABLEDIALOGSWITCHER);
			dialogSwitcher->SetDialogServiceID(kGlobalPrefsDialogServiceImpl);
			dialogSwitcher->SwitchDialogPanelByID(dialogPanelID);

			dialog->Open();
			break;
		}
	
		case kAutoCorrectActionID:
		{
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kAutoCorrectPrefsCmdBoss));
			if (cmd)
			{
				InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
				ASSERT_MSG(autoCorrectPrefs != nil, "autoCorrectPrefs != nil");
				
				InterfacePtr<IAutoCorrectPrefs> newPrefs(cmd, IID_IAUTOCORRECTPREFS);
				ASSERT_MSG(autoCorrectPrefs != nil, "autoCorrectPrefs != nil");
				
				newPrefs->SetAutoCorrect(! autoCorrectPrefs->GetAutoCorrect());
				newPrefs->SetAutoCorrectCapitalizationErrors(autoCorrectPrefs->GetAutoCorrectCapitalizationErrors());

				AutoCorrectList autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();
				newPrefs->SetAutoCorrectList(autoCorrectList);
				
				CmdUtils::ProcessCommand(cmd);
			}
			break;
		}
		case kAutoCorrectPrefsActionID:
		{
			RsrcID dialogID = kAutoCorrectPrefsPaletteRsrcID;
			WidgetID dialogPanelID = kAutoCorrectPrefsDialogPanelWidgetID;

			InterfacePtr<IK2ServiceRegistry>	serviceReg(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
			InterfacePtr<IK2ServiceProvider>	selectableDialogService(serviceReg->QueryServiceProviderByClassID(kSelectableDialogServiceImpl, kGlobalPrefsDialogBoss));
			InterfacePtr<IDialogCreator> dialogCreator(selectableDialogService, IID_IDIALOGCREATOR);
			IDialog* dialog = dialogCreator->CreateDialog();

			InterfacePtr<IPanelControlData> panelData(dialog, IID_IPANELCONTROLDATA);
			IControlView* dialogView = panelData->FindWidget(kPreferencesDialogWidgetID);
			InterfacePtr<ISelectableDialogSwitcher> dialogSwitcher(dialogView, IID_ISELECTABLEDIALOGSWITCHER);
			dialogSwitcher->SetDialogServiceID(kGlobalPrefsDialogServiceImpl);
			dialogSwitcher->SwitchDialogPanelByID(dialogPanelID);

			dialog->Open();
			break;
		}
	}
}

//---------------------------------------------------------------
// SpellMenuComponent::CreateTheDialog() 
//---------------------------------------------------------------

IDialog * SpellMenuComponent::CreateTheDialog( RsrcID kDialogRsrcID , IDialog::DialogType nDialogType ) const
{
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> pDialogMgr( app, IID_IDIALOGMGR);
	
	const PMLocaleId nLocale = LocaleSetting::GetLocale();
	const RsrcSpec aSpec( nLocale, kSpellPanelPluginID, kViewRsrcType,  kDialogRsrcID, kTrue );

	IDialog *pDialog = pDialogMgr->CreateNewDialog( aSpec, nDialogType );
	return pDialog;
}
