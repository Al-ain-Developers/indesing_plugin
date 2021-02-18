//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellPrefsDialogController.cpp $
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
//  Proj:	SpellPanel
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "SpellPrefsDialogController.h"

// Interfaces:
#include "ITriStateControlData.h"
#include "ICmdCollection.h"
#include "ICommand.h"
#include "IControlView.h"
#include "IDialog.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IEventHandler.h"
#include "ISpellingPrefs.h"
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



CREATE_PMINTERFACE(SpellPrefsDialogController, kSpellPrefsDialogControllerImpl)

//========================================================================================
// CLASS SpellPrefsDialogController
//========================================================================================

SpellPrefsDialogController::SpellPrefsDialogController(IPMUnknown *boss) :
	CDialogController(boss)
{
}

SpellPrefsDialogController::~SpellPrefsDialogController()
{
}

void SpellPrefsDialogController::InitializeDialogFields(IActiveContext* context)
{
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelControlData> panel(parentHolder->GetParent(),IID_IPANELCONTROLDATA);

	ColorArray emptyColor;

	// Set controls to their values for document Spell controls
	InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));	
	if (spellingPrefs)
	{
		this->SetTriStateControlData(kSpellPrefsMisspelledWordsCheckboxWidgetID, spellingPrefs->GetCheckMisspelledWords() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
		this->SetTriStateControlData(kSpellPrefsRepeatedWordsCheckboxWidgetID, spellingPrefs->GetCheckRepeatedWords() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
		this->SetTriStateControlData(kSpellPrefsUncapitalizedWordsCheckboxWidgetID, spellingPrefs->GetCheckCapitalizeWords() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
		this->SetTriStateControlData(kSpellPrefsUncapitalizedSentencesCheckboxWidgetID, spellingPrefs->GetCheckCapitalizeSentences() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);
		this->SetTriStateControlData(kSpellPrefsEnableDSCCheckboxWidgetID, spellingPrefs->GetDynamicSpellCheck() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected);

		// Find the UID for the default document Spell color
		int32 misspelledWordColorIndex = spellingPrefs->GetDynamicSpellMisspelledWordColorIndex();
		int32 repeatedWordColorIndex = spellingPrefs->GetDynamicSpellRepeatedWordColorIndex();
		int32 uncapitalizedWordColorIndex = spellingPrefs->GetDynamicSpellUncapitalizedWordColorIndex();
		int32 uncapitalizedSentenceColorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();

		UIDRef misspelledWordColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(misspelledWordColorIndex, /* doc */nil);
		UIDRef repeatedWordColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(repeatedWordColorIndex, /* doc */nil);
		UIDRef uncapitalizedWordColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(uncapitalizedWordColorIndex, /* doc */nil);
		UIDRef uncapitalizedSentenceColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(uncapitalizedSentenceColorIndex, /* doc */nil);

		// If color invalid, get a color as a last resort.
		if (misspelledWordColorUIDRef.GetUID() == kInvalidUID)
			misspelledWordColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(IUIColorUtils::kStockDynamicSpell, nil);
		if (repeatedWordColorUIDRef.GetUID() == kInvalidUID)
			repeatedWordColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(IUIColorUtils::kStockDynamicSpellGrammar , nil);
		if (uncapitalizedWordColorUIDRef.GetUID() == kInvalidUID)
			uncapitalizedWordColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(IUIColorUtils::kStockDynamicSpellGrammar , nil);
		if (uncapitalizedSentenceColorUIDRef.GetUID() == kInvalidUID)
			uncapitalizedSentenceColorUIDRef = Utils<IUIColorUtils>()->GetUIColor(IUIColorUtils::kStockDynamicSpellGrammar , nil);

		InterfacePtr<IWorkspace> workSpace(GetExecutionContextSession()->QueryWorkspace());

		IControlView* misspelledColorDropDownView = panel->FindWidget(kDynamicSpellCheckMisspelledColorDropDownWidgetID);
		InterfacePtr<IColorListControlData> misspelledColorListControlData(misspelledColorDropDownView, IID_ICOLORLISTCONTROLDATA);
		if (misspelledColorListControlData)
			misspelledColorListControlData->Setup(::GetUIDRef(workSpace), IID_IUICOLORLIST, IColorListControlData::kIncludeCustom, misspelledWordColorUIDRef.GetUID());

		IControlView* repeatedWordColorDropDownView = panel->FindWidget(kDynamicSpellCheckRepeatedWordColorDropDownWidgetID);
		InterfacePtr<IColorListControlData> repeatedWordColorListControlData(repeatedWordColorDropDownView, IID_ICOLORLISTCONTROLDATA);
		if (repeatedWordColorListControlData)
			repeatedWordColorListControlData->Setup(::GetUIDRef(workSpace), IID_IUICOLORLIST, IColorListControlData::kIncludeCustom, repeatedWordColorUIDRef.GetUID());

		IControlView* uncapitalizedWordColorDropDownView = panel->FindWidget(kDynamicSpellCheckCapitalizedWordColorDropDownWidgetID);
		InterfacePtr<IColorListControlData> uncapitalizedWordColorListControlData(uncapitalizedWordColorDropDownView, IID_ICOLORLISTCONTROLDATA);
		if (uncapitalizedWordColorListControlData)
			uncapitalizedWordColorListControlData->Setup(::GetUIDRef(workSpace), IID_IUICOLORLIST, IColorListControlData::kIncludeCustom, uncapitalizedWordColorUIDRef.GetUID());

		IControlView* uncapitalizedSentenceColorDropDownView = panel->FindWidget(kDynamicSpellCheckCapitalizedSentenceColorDropDownWidgetID);
		InterfacePtr<IColorListControlData> uncapitalizedSentenceColorListControlData(uncapitalizedSentenceColorDropDownView, IID_ICOLORLISTCONTROLDATA);
		if (uncapitalizedSentenceColorListControlData)
			uncapitalizedSentenceColorListControlData->Setup(::GetUIDRef(workSpace), IID_IUICOLORLIST, IColorListControlData::kIncludeCustom, uncapitalizedSentenceColorUIDRef.GetUID());
	}
}

// Validate the values in the edit boxes. Validate is all done
// through resources for this dialog.
WidgetID SpellPrefsDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	WidgetID badWidgetId = kDefaultWidgetId;
	return badWidgetId;
}

void SpellPrefsDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId) 
{
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelControlData> panel(parentHolder->GetParent(),IID_IPANELCONTROLDATA);

	ColorArray emptyColor;

	// Apply the values for the Spell controls
	InterfacePtr<ISpellingPrefs> spellingPrefs((ISpellingPrefs*)::QuerySessionPreferences(IID_ISPELLINGPREFS));	
	if (spellingPrefs)
	{
		bool16 origCheckMisspelledWords 	= spellingPrefs->GetCheckMisspelledWords();
		bool16 origCheckRepeatedWords 		= spellingPrefs->GetCheckRepeatedWords();
		bool16 origCheckCapitalizeWords 	= spellingPrefs->GetCheckCapitalizeWords();
		bool16 origCheckCapitalizeSentences = spellingPrefs->GetCheckCapitalizeSentences();
		bool16 origDynamicSpellCheck = spellingPrefs->GetDynamicSpellCheck();

		ITriStateControlData::TriState triCheckMisspelledWords 		= this->GetTriStateControlData(kSpellPrefsMisspelledWordsCheckboxWidgetID);
		ITriStateControlData::TriState triCheckRepeatedWords 		= this->GetTriStateControlData(kSpellPrefsRepeatedWordsCheckboxWidgetID);
		ITriStateControlData::TriState triCheckCapitalizeWords 		= this->GetTriStateControlData(kSpellPrefsUncapitalizedWordsCheckboxWidgetID);
		ITriStateControlData::TriState triCheckCapitalizeSentences 	= this->GetTriStateControlData(kSpellPrefsUncapitalizedSentencesCheckboxWidgetID);
		ITriStateControlData::TriState triDynamicSpellCheck 		= this->GetTriStateControlData(kSpellPrefsEnableDSCCheckboxWidgetID);

		bool16 bCheckMisspelledWords 		= triCheckMisspelledWords == ITriStateControlData::kSelected;
		bool16 bCheckRepeatedWords 			= triCheckRepeatedWords == ITriStateControlData::kSelected;
		bool16 bCheckCapitalizeWords 		= triCheckCapitalizeWords == ITriStateControlData::kSelected;
		bool16 bCheckCapitalizeSentences 	= triCheckCapitalizeSentences == ITriStateControlData::kSelected;
		bool16 bDynamicSpellCheck			= triDynamicSpellCheck == ITriStateControlData::kSelected;

		int32 misspelledWordColorIndex = 0;
		int32 repeatedWordColorIndex = 0;
		int32 uncapitalizedWordColorIndex = 0;
		int32 uncapitalizedSentenceColorIndex = 0;

		int32 origMisspelledWordColorIndex = spellingPrefs->GetDynamicSpellMisspelledWordColorIndex();
		int32 origRepeatedWordColorIndex = spellingPrefs->GetDynamicSpellRepeatedWordColorIndex();
		int32 origUncapitalizedWordColorIndex = spellingPrefs->GetDynamicSpellUncapitalizedWordColorIndex();
		int32 origUncapitalizedSentenceColorIndex = spellingPrefs->GetDynamicSpellUncapitalizedSentenceColorIndex();
		
		IControlView* misspelledColorDropDownView = panel->FindWidget(kDynamicSpellCheckMisspelledColorDropDownWidgetID);
		InterfacePtr<IColorListControlData> misspelledColorListControlData(misspelledColorDropDownView, IID_ICOLORLISTCONTROLDATA);
		if (misspelledColorListControlData && misspelledColorListControlData->IsSetup())
		{
			UID uiColorUID = misspelledColorListControlData->GetSelection();
			if (uiColorUID != kInvalidUID)
			{
				misspelledWordColorIndex = Utils<IUIColorUtils>()->GetUIColorIndex(uiColorUID, nil);
			}
		}
			
		IControlView* capitalizedWordColorDropDownView = panel->FindWidget(kDynamicSpellCheckCapitalizedWordColorDropDownWidgetID);
		InterfacePtr<IColorListControlData> capitalizedWordColorListControlData(capitalizedWordColorDropDownView, IID_ICOLORLISTCONTROLDATA);
		if (capitalizedWordColorListControlData && capitalizedWordColorListControlData->IsSetup())
		{
			UID uiColorUID = capitalizedWordColorListControlData->GetSelection();
			if (uiColorUID != kInvalidUID)
			{
				uncapitalizedWordColorIndex = Utils<IUIColorUtils>()->GetUIColorIndex(uiColorUID, nil);
			}
		}
		
		IControlView* capitalizedSentenceColorDropDownView = panel->FindWidget(kDynamicSpellCheckCapitalizedSentenceColorDropDownWidgetID);
		InterfacePtr<IColorListControlData> capitalizedSentenceColorListControlData(capitalizedSentenceColorDropDownView, IID_ICOLORLISTCONTROLDATA);
		if (capitalizedSentenceColorListControlData && capitalizedSentenceColorListControlData->IsSetup())
		{
			UID uiColorUID = capitalizedSentenceColorListControlData->GetSelection();
			if (uiColorUID != kInvalidUID)
			{
				uncapitalizedSentenceColorIndex = Utils<IUIColorUtils>()->GetUIColorIndex(uiColorUID, nil);
			}
		}
		
		IControlView* repeatWordColorDropDownView = panel->FindWidget(kDynamicSpellCheckRepeatedWordColorDropDownWidgetID);
		InterfacePtr<IColorListControlData> repeatWordColorListControlData(repeatWordColorDropDownView, IID_ICOLORLISTCONTROLDATA);
		if (repeatWordColorListControlData && repeatWordColorListControlData->IsSetup())
		{
			UID uiColorUID = repeatWordColorListControlData->GetSelection();
			if (uiColorUID != kInvalidUID)
			{
				repeatedWordColorIndex = Utils<IUIColorUtils>()->GetUIColorIndex(uiColorUID, nil);
			}
		}

		// Send a command if anything changed
		if (origCheckMisspelledWords !=  bCheckMisspelledWords || 
			origCheckRepeatedWords != bCheckRepeatedWords || 
			origCheckCapitalizeWords != bCheckCapitalizeWords || 
			origCheckCapitalizeSentences != bCheckCapitalizeSentences ||
			origDynamicSpellCheck != bDynamicSpellCheck ||
			origMisspelledWordColorIndex != misspelledWordColorIndex ||
			origRepeatedWordColorIndex != repeatedWordColorIndex ||
			origUncapitalizedWordColorIndex != uncapitalizedWordColorIndex ||
			origUncapitalizedSentenceColorIndex != uncapitalizedSentenceColorIndex)
		{
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSpellingPrefsCmdBoss));
			InterfacePtr<ISpellingPrefs> newPrefs(cmd, IID_ISPELLINGPREFS);	/* grab the prefs interface on the cmd boss */
			ASSERT_MSG(newPrefs != nil, "newPrefs != nil");
			
			newPrefs->SetDynamicSpellCheck(bDynamicSpellCheck);
			newPrefs->SetCheckMisspelledWords(bCheckMisspelledWords);
			newPrefs->SetCheckRepeatedWords(bCheckRepeatedWords);
			newPrefs->SetCheckCapitalizeWords(bCheckCapitalizeWords);
			newPrefs->SetCheckCapitalizeSentences(bCheckCapitalizeSentences);
			
			newPrefs->SetDynamicSpellMisspelledWordColorIndex(misspelledWordColorIndex);
			newPrefs->SetDynamicSpellRepeatedWordColorIndex(repeatedWordColorIndex);
			newPrefs->SetDynamicSpellUncapitalizedWordColorIndex(uncapitalizedWordColorIndex);
			newPrefs->SetDynamicSpellUncapitalizedSentenceColorIndex(uncapitalizedSentenceColorIndex);

			CmdUtils::ProcessCommand(cmd);
		}
	}
}
