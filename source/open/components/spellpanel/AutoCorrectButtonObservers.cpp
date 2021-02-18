//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectButtonObservers.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IApplication.h"
#include "IAutoCorrectPrefs.h"
#include "IBoolData.h"
#include "IControlView.h"
#include "IDialog.h"
#include "IDialogController.h"
#include "IDialogMgr.h"
#include "ILanguage.h"
#include "IListBoxController.h"
#include "IListControlDataOf.h"	
#include "IPanelControlData.h"
#include "ISession.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"
#include "ITreeViewWidgetMgr.h"
#include "ITriStateControlData.h"
#include "IWidgetParent.h"
#include "IWindow.h"

// ----- Includes -----

#include "AutoCorrect.h"
#include "AutoCorrectButtonObservers.h"
#include "CAlert.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"

// ----- Utility files -----

#include "IAutoCorrectUtils.h"
#include "IWidgetUtils.h"
#include "PMTextUtils.h"
#include "PreferenceUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "AutoCorrectNodeID.h"
#include "SpellPanelID.h"
#include "SpellingServiceID.h"
#include "StringNodeID.h"


#define UNCLEAR 		""
#define RESET			"???"
#define CONTROL_PMIID	IID_IBOOLEANCONTROLDATA


CAutoCorrectButtonObserver::CAutoCorrectButtonObserver(IPMUnknown *boss):
	AutoCorrectPanelObserver(boss)
{
	this->SetControlID( CONTROL_PMIID );
	this->SetReset( kTrue );
}

void	CAutoCorrectButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
    if (theChange == kTrueStateMessage) 
	{
        // No behaviour in this sample: but indicate at least that the message has been received.
        ApplyToFocus();
    }
}

bool16	CAutoCorrectButtonObserver::ApplyToWidget()
{
	return kFalse;
}

bool16	CAutoCorrectButtonObserver::ApplyToFocus()
{
	return kFalse;
}

bool16	CAutoCorrectButtonObserver::SetupWidget()
{
	return kFalse;
}

void	CAutoCorrectButtonObserver::NotifyObserver( ClassID nMsg )
{
	//InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	//if( pPanel )
	//	pPanel->Change( nMsg, IID_IAUTOCORRECTPANELMSG, this );
}


ISubject * CAutoCorrectButtonObserver::QueryTreeViewSubject()
{
	InterfacePtr<ITreeViewController> iTreeViewController((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAutoCorrectTreeViewWidgetID, IID_ITREEVIEWCONTROLLER));
	return (ISubject *)iTreeViewController->QueryInterface(IID_ISUBJECT);
}

//===============================================================
// CLASS AutoCorrectAddButtonObserver
//===============================================================

CREATE_PMINTERFACE(AutoCorrectAddButtonObserver, kAutoCorrectAddButtonObserverImpl)

//---------------------------------------------------------------
// AutoCorrectAddButtonObserver constructor 
//---------------------------------------------------------------

AutoCorrectAddButtonObserver::AutoCorrectAddButtonObserver(IPMUnknown *boss) :
	CAutoCorrectButtonObserver(boss)
{
}

bool16	AutoCorrectAddButtonObserver::SetupWidget()
{
	bool16 	bHandled = kTrue;

	InterfacePtr<IControlView> view(this, UseDefaultIID());
	if (! view)
		return kFalse;
	
	InterfacePtr<ILanguage> language(this->QueryLanguage());
	LanguageID languageID = kLanguageNeutral;
	
	if (language)
		languageID = language->GetLanguageID();

	LanguageID nPrim = GetPrimaryLanguageID(languageID);

	if (!language )
		view->Disable();
	else
		view->Enable();
	
	return bHandled;
}

void AutoCorrectAddButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	switch (theChange.Get()) 
	{
		case kAutoCorrectEditorMsgLanguageHasChanged: 
		{
			if (protocol == IID_IAUTOCORRECTPANELMSG)
			{
				SetupWidget();
			}
			break;
		}
		default:
		{
			CAutoCorrectButtonObserver::Update(theChange, theSubject, protocol, changedBy);
			break;
		}
    }
}
bool16 AutoCorrectAddButtonObserver::ApplyToWidget()
{
	return SetupWidget();
}

//Add (or Edit) a single pair to the auto correct list for the specified language
bool16 AutoCorrectAddButtonObserver::AddOrEditStandardAutoCorrections( WideString& misspelledWide,  WideString& correctedWide, LanguageID languageID)
{
    InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
    if (autoCorrectPrefs)
	{
		AutoCorrectList autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();
		bool16 bFound = kFalse;

		for (int32 i = 0; i < autoCorrectList.Length(); i++)
		{
			if (autoCorrectList[i].fLanguageID == languageID)
			{	
				/* if this misspelling exists already, remove it, rebind new misspelling */
				{
					int32 j = autoCorrectList[i].fAutoStringPair.Location(misspelledWide);
					if (j >= 0)
					{
						autoCorrectList[i].fAutoStringPair.Remove(j);
						autoCorrectList[i].fAutoStringPair.Bind(misspelledWide, correctedWide);
						bFound = kTrue;
						break;
					}
				}
				
				if (!bFound)
				{
					autoCorrectList[i].fAutoStringPair.Bind(misspelledWide, correctedWide);
					bFound = kTrue;
				}
				break;
			}
		}


		/* if we didn't find it, add it */
		if (!bFound)
		{
			AutoCorrectItem autoCorrectItem;
			autoCorrectItem.fLanguageID = languageID;
			
			autoCorrectItem.fAutoStringPair.Bind(misspelledWide, correctedWide);
			autoCorrectList.Insert(autoCorrectItem);
		}

        InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kAutoCorrectPrefsCmdBoss));
        InterfacePtr<IAutoCorrectPrefs> newPrefs(cmd, IID_IAUTOCORRECTPREFS);    /* grab the prefs interface on the cmd boss */
        ASSERT_MSG(newPrefs != nil, "newPrefs != nil");

        newPrefs->SetAutoCorrect(autoCorrectPrefs->GetAutoCorrect());
        newPrefs->SetAutoCorrectCapitalizationErrors(autoCorrectPrefs->GetAutoCorrectCapitalizationErrors());
        newPrefs->SetAutoCorrectList(autoCorrectList);

        ErrorCode err = CmdUtils::ExecuteCommand(cmd);

		/* write out xml file to prefs */
		if (err == kSuccess)
		{
			IDFile file;
			PMString autoCorrectPathname;
			InterfacePtr<ILanguage> language(this->QueryLanguage());

			if (Utils<IAutoCorrectUtils>()->GetAutocorrectPrefsFile(file, language, autoCorrectPathname))
			{
				ErrorCode localErr = Utils<IAutoCorrectUtils>()->ExportAutoCorrectXML(file, language);
			}

			// When editing, update selection since tree will be cleared and selection lost, Edit will now be disabled. Add always enabled.
			if (bFound)
			{
				InterfacePtr<ITreeViewController> iTreeViewController((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAutoCorrectTreeViewWidgetID, IID_ITREEVIEWCONTROLLER));
				if (iTreeViewController)
					iTreeViewController->DeselectAll();
			}

		}
	}

	return kTrue;
}

bool16 AutoCorrectAddButtonObserver::ApplyToFocus()
{
	return AddOrEditEntry();
}

bool16 AutoCorrectAddButtonObserver::AddOrEditEntry()
{
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(app, IID_IDIALOGMGR);
	
	const RsrcSpec aSpec(LocaleSetting::GetLocale(), kSpellPanelPluginID, kViewRsrcType,  kAutoCorrectAddPairDialogRsrcID);

	IDialog* dialog = dialogMgr->CreateNewDialog(aSpec, IDialog::kMovableModal);
	ASSERT(dialog != nil);
    IControlView* dialogView = dialog->GetDialogPanel();
    ASSERT_MSG(dialogView != nil, "missing dialog panel.");

    InterfacePtr<IDialogController> controller( dialogView, IID_IDIALOGCONTROLLER );
	InterfacePtr<IStringData> misspelledStringData( controller, UseDefaultIID() );
	InterfacePtr<IStringData> correctedStringData( controller, IID_ICORRECTEDSTRINGDATA );

    InterfacePtr<IWindow> window(dialog, IID_IWINDOW);
	if (window)
		window->SetTitle(GetAddingWordMode() ? "AddToAutoCorrectList" : "EditAutoCorrectList");	// Set window title

	// Let dialog know if it is in "Adding" or "Editing" mode
	InterfacePtr<IBoolData> addingWordMode(dialogView, IID_IADDINGWORDMODEBOOLDATA);
	addingWordMode->Set(GetAddingWordMode());
	
	NodeIDList selectedItems;
	InterfacePtr<ITreeViewController> iTreeViewController((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAutoCorrectTreeViewWidgetID, IID_ITREEVIEWCONTROLLER));
	if (iTreeViewController)
		iTreeViewController->GetSelectedItems(selectedItems);
	
	if (!GetAddingWordMode() && selectedItems.size())
	{
		const NodeID& node = selectedItems[0];
		PMString misspelledName = static_cast<AutoCorrectNodeID*>(node.Get())->GetMisspelledName();
		PMString correctedName = static_cast<AutoCorrectNodeID*>(node.Get())->GetCorrectedName();
		misspelledName.SetTranslatable(kFalse);
		correctedName.SetTranslatable(kFalse);
		misspelledStringData->Set(misspelledName);
		correctedStringData->Set(correctedName);
	}

	InterfacePtr<ICommand> enableCommandPassThrough(CmdUtils::CreateCommand(kEnableCommandPassThroughCmdBoss));
	CmdUtils::ProcessCommand (enableCommandPassThrough);

	dialog->Open();
	dialog->WaitForDialog();	// Wait for user to close dialog
	
	InterfacePtr<ICommand> disableCommandPassThrough(CmdUtils::CreateCommand(kDisableCommandPassThroughCmdBoss));
	CmdUtils::ScheduleCommand (disableCommandPassThrough);	//Weird I know, but the kCloseDialogCmd is scheduled, so I schedule this after the close cmd

	InterfacePtr<IBoolData> iData(controller, IID_IBOOLDATA);
    if (! iData->GetBool())	// if the user clicked OK add the word pair
	{
		// Now get the data back out
		PMString misspelledWord = misspelledStringData->GetString();
		
		// Now get the data back out
		PMString correctedWord = correctedStringData->GetString();

		// Must be 1 or more characters and no spaces in misspelled word
		if (misspelledWord.WCharLength() > 0 && correctedWord.WCharLength() > 0 && misspelledWord.IndexOfCharacter(kTextChar_Space) == -1 && misspelledWord != correctedWord)
		{
			// first char can't be punctuation. last char can't be punctuation because code in AutoCorrectTypingIdleTask::DoTask
			// will not find it. If that code is fixed that autocorrect could handle I.M.B -> I.B.M
			bool16 bContainsInvalidChar = !PMCharFilters::SpellingIsWordCharNoPunctuation(0, misspelledWord.GetWChar(0))
				|| !PMCharFilters::SpellingIsWordCharNoPunctuation(0, misspelledWord.GetWChar(misspelledWord.CharCount()-1));
			for (int32 i = 1; i < misspelledWord.WCharLength(); i++)
			{
				UTF32TextChar tc = misspelledWord.GetWChar(i);
				if (!PMCharFilters::SpellingIsWordChar(0, tc))
				{
					bContainsInvalidChar = kTrue;
					break;
				}
			}

			if (!bContainsInvalidChar)
			{
				for (int32 i = 0; i < correctedWord.WCharLength(); i++)
				{
					UTF32TextChar tc = correctedWord.GetWChar(i);
					if (!PMCharFilters::SpellingIsWordChar(0, tc) && tc != kTextChar_Space)
					{
						bContainsInvalidChar = kTrue;
						break;
					}
				}
			}

			if (! bContainsInvalidChar)
			{
				WideString misspelledWide(misspelledWord);
				WideString correctedWide(correctedWord);
				
				InterfacePtr<ILanguage> langauge(this->QueryLanguage());
				LanguageID languageID = MakeLanguageID(kLanguageEnglish, kSubLanguageEnglishUS);
				if (langauge)
					languageID = langauge->GetLanguageID();

				bool16 added = AddOrEditStandardAutoCorrections(misspelledWide, correctedWide, languageID);
			}
			else
				CAlert::WarningAlert("ACAlert5");
		}
		else
		{
			if (misspelledWord.WCharLength() == 0 || correctedWord.WCharLength() == 0)
				CAlert::WarningAlert("ACAlert1");
			else if (misspelledWord.IndexOfCharacter(kTextChar_Space) != -1)
				CAlert::WarningAlert("ACAlert6");
			else if (misspelledWord == correctedWord)
				CAlert::WarningAlert("ACAlert2");
		}
	}

	return kTrue;
}


//===============================================================
// CLASS AutoCorrectEditButtonObserver
//===============================================================

CREATE_PMINTERFACE(AutoCorrectEditButtonObserver, kAutoCorrectEditButtonObserverImpl)

//---------------------------------------------------------------
// AutoCorrectEditButtonObserver constructor 
//---------------------------------------------------------------

AutoCorrectEditButtonObserver::AutoCorrectEditButtonObserver(IPMUnknown *boss) :
	AutoCorrectAddButtonObserver(boss)
{
}

bool16	AutoCorrectEditButtonObserver::SetupWidget()
{
	bool16 	bHandled = kTrue;
	
	NodeIDList selectedItems;
	InterfacePtr<ITreeViewController> iTreeViewController((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAutoCorrectTreeViewWidgetID, IID_ITREEVIEWCONTROLLER));
	if (iTreeViewController)
		iTreeViewController->GetSelectedItems(selectedItems);
	
	InterfacePtr<IControlView> view(this, UseDefaultIID());
	if (!view)
		return kFalse;
	
	view->Enable(selectedItems.size() == 1);
	return bHandled;
}

void AutoCorrectEditButtonObserver::AutoAttach()
{
 	AutoCorrectPanelObserver::AutoAttach();

	InterfacePtr<ISubject> subject( this->QueryTreeViewSubject() );
	if (subject)
	{
		if ( !subject->IsAttached( this, IID_ITREEVIEWCONTROLLER ) )
			subject->AttachObserver( this, IID_ITREEVIEWCONTROLLER );
	}
}


void AutoCorrectEditButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject( this->QueryTreeViewSubject() );
    if (subject)
    {
        if (subject->IsAttached( this, IID_ITREEVIEWCONTROLLER ) )
            subject->DetachObserver( this, IID_ITREEVIEWCONTROLLER );
    }
	
	AutoCorrectPanelObserver::AutoDetach();
}

void AutoCorrectEditButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	switch (theChange.Get()) 
	{
		case kListSelectionChangedMessage: 
		{
			if (protocol == IID_ITREEVIEWCONTROLLER && theChange == kListSelectionChangedMessage)
			{
				SetupWidget();
			}
			break;
		}
		default:
		{
			CAutoCorrectButtonObserver::Update(theChange, theSubject, protocol, changedBy);
			break;
		}
    }
}



//===============================================================
// CLASS AutoCorrectRemoveButtonObserver
//===============================================================

CREATE_PMINTERFACE(AutoCorrectRemoveButtonObserver, kAutoCorrectRemoveButtonObserverImpl)


AutoCorrectRemoveButtonObserver::AutoCorrectRemoveButtonObserver(IPMUnknown *boss) :
	CAutoCorrectButtonObserver(boss)
{
}

void AutoCorrectRemoveButtonObserver::AutoAttach()
{
 	AutoCorrectPanelObserver::AutoAttach();

	InterfacePtr<ISubject> subject( this->QueryTreeViewSubject() );
	if (subject)
	{
		if ( !subject->IsAttached( this, IID_ITREEVIEWCONTROLLER ) )
			subject->AttachObserver( this, IID_ITREEVIEWCONTROLLER );
	}
}


void AutoCorrectRemoveButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject( this->QueryTreeViewSubject() );
    if (subject)
    {
        if (subject->IsAttached( this, IID_ITREEVIEWCONTROLLER ) )
            subject->DetachObserver( this, IID_ITREEVIEWCONTROLLER );
    }
	
	AutoCorrectPanelObserver::AutoDetach();
}



bool16	AutoCorrectRemoveButtonObserver::SetupWidget()
{
	bool16 	bHandled = kTrue;
	InterfacePtr<ITreeViewController> iTreeViewController((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAutoCorrectTreeViewWidgetID, IID_ITREEVIEWCONTROLLER));
	NodeIDList selectedItems;

	if (iTreeViewController)
		iTreeViewController->GetSelectedItems(selectedItems);
	
	InterfacePtr<IControlView> view(this, UseDefaultIID());
	if (! view)
		return kFalse;
	
	if (selectedItems.size() > 0)
		view->Enable();
	else
		view->Disable();
	
	return bHandled;
}

bool16 AutoCorrectRemoveButtonObserver::ApplyToWidget()
{
	return SetupWidget();
}

bool16 AutoCorrectRemoveButtonObserver::ApplyToFocus()
{
	bool16 entriesRemovied = RemoveEntries();
	return kTrue;
}

void AutoCorrectRemoveButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	switch (theChange.Get()) 
	{
		case kListSelectionChangedMessage: 
		{
			if (protocol == IID_ITREEVIEWCONTROLLER && theChange == kListSelectionChangedMessage)
			{
				SetupWidget();
			}
			break;
		}
		default:
		{
			CAutoCorrectButtonObserver::Update(theChange, theSubject, protocol, changedBy);
			break;
		}
    }
}


bool16 AutoCorrectRemoveButtonObserver::RemoveEntries()
{
	int32 numSelected = 0;
	NodeIDList selectedItems;

	InterfacePtr<ITreeViewController> iTreeViewController((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAutoCorrectTreeViewWidgetID, IID_ITREEVIEWCONTROLLER));
	if (iTreeViewController)
		iTreeViewController->GetSelectedItems(selectedItems);
	
	numSelected = selectedItems.size();

	InterfacePtr<ISubject> subject(QueryPanelSubject());	
	InterfacePtr<ILanguage> language(QueryLanguage());

	if (language)
	{
		AutoCorrectItem autoCorrectItem;

		autoCorrectItem.fLanguageID = language->GetLanguageID();

		for (int32 i = 0; i < numSelected; i++)
		{
			const NodeID& node = selectedItems[i];
			const WideString& misspelledWord = static_cast<AutoCorrectNodeID*>(node.Get())->GetMisspelledName();
			const WideString& correctedWord = static_cast<AutoCorrectNodeID*>(node.Get())->GetCorrectedName();

			autoCorrectItem.fAutoStringPair.Bind(misspelledWord, correctedWord);
		}

		RemoveStandardAutoCorrections(autoCorrectItem);
	}

	// Update selection since this item no longer exists, Remove will now be disabled.
	if (iTreeViewController)
		iTreeViewController->DeselectAll();

	return kTrue;
}


bool16 AutoCorrectRemoveButtonObserver::RemoveStandardAutoCorrections(const AutoCorrectItem& autoCorrectItem)
{
    InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
    if (autoCorrectPrefs)
	{
		AutoCorrectList autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();
		
		bool16 bFound = kFalse;

		for (int32 i = 0; i < autoCorrectList.Length(); i++)
		{
			if (autoCorrectList[i].fLanguageID == autoCorrectItem.fLanguageID)
			{	
				for (int32 ii = 0; ii < autoCorrectItem.fAutoStringPair.Length(); ii++)
				{
					const WideString& key = autoCorrectItem.fAutoStringPair.Key(ii);

					int32 index = autoCorrectList[i].fAutoStringPair.Location(key);
					if (index >= 0)
						autoCorrectList[i].fAutoStringPair.Remove(index);
				}
				break;
			}
		}
		
        InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kAutoCorrectPrefsCmdBoss));
        InterfacePtr<IAutoCorrectPrefs> newPrefs(cmd, IID_IAUTOCORRECTPREFS);    /* grab the prefs interface on the cmd boss */
        ASSERT_MSG(newPrefs != nil, "newPrefs != nil");

        newPrefs->SetAutoCorrect(autoCorrectPrefs->GetAutoCorrect());
        newPrefs->SetAutoCorrectCapitalizationErrors(autoCorrectPrefs->GetAutoCorrectCapitalizationErrors());
        newPrefs->SetAutoCorrectList(autoCorrectList);

        ErrorCode err = CmdUtils::ExecuteCommand(cmd);

		/* write out xml file to prefs */
		if (err == kSuccess)
		{
			IDFile file;
			PMString autoCorrectPathname;
			InterfacePtr<ILanguage> language(this->QueryLanguage());

			if (Utils<IAutoCorrectUtils>()->GetAutocorrectPrefsFile(file, language, autoCorrectPathname))
			{
				ErrorCode localErr = Utils<IAutoCorrectUtils>()->ExportAutoCorrectXML(file, language);
			}
		}
	}

	return kTrue;
}

//===============================================================
// CLASS AutoCorrectRemoveButtonObserver
//===============================================================

CREATE_PMINTERFACE(AutoCorrectCheckBoxObserver, kAutoCorrectCheckBoxObserverImpl)

AutoCorrectCheckBoxObserver::AutoCorrectCheckBoxObserver(IPMUnknown *boss) :
	AutoCorrectPanelObserver(boss)
{
	this->SetControlID( IID_ITRISTATECONTROLDATA );
	this->SetReset( kTrue );
}

bool16 AutoCorrectCheckBoxObserver::ApplyToWidget()
{
	return kTrue;	//SetupWidget();
}

bool16 AutoCorrectCheckBoxObserver::ApplyToFocus()
{
	return kTrue;
}

void AutoCorrectCheckBoxObserver::AutoAttach()
{
 	AutoCorrectPanelObserver::AutoAttach();

	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelControlData> panel(parentHolder->GetParent(),IID_IPANELCONTROLDATA);
	IControlView* acCheckBox = panel->FindWidget(kAutoCorrectEnableCheckboxWidgetID);

	InterfacePtr<ISubject> subject( acCheckBox, UseDefaultIID() );
	if (subject)
	{
		if ( !subject->IsAttached( this, IID_ITRISTATECONTROLDATA ) )
			subject->AttachObserver( this, IID_ITRISTATECONTROLDATA );
	}
}


void AutoCorrectCheckBoxObserver::AutoDetach()
{
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelControlData> panel(parentHolder->GetParent(),IID_IPANELCONTROLDATA);
	IControlView* acCheckBox = panel->FindWidget(kAutoCorrectEnableCheckboxWidgetID);

	InterfacePtr<ISubject> subject( acCheckBox, UseDefaultIID() );
    if (subject)
    {
        if (subject->IsAttached( this, IID_ITRISTATECONTROLDATA ) )
            subject->DetachObserver( this, IID_ITRISTATECONTROLDATA );
    }
	
	AutoCorrectPanelObserver::AutoDetach();
}

void AutoCorrectCheckBoxObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	if (theChange.Get() == kTrueStateMessage )
	{
		AutoCorrectList autoCorrectList;
		InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences(IID_IAUTOCORRECTPREFS));
		if (autoCorrectPrefs)
			autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();

		// if we do not have an auto-correct list, try importing the auto-correct dictionaries
		if ( autoCorrectList.Length() == 0 )
		{
			Utils<IAutoCorrectUtils>()->ImportAllAutoCorrectFiles();
			autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();

			// now let the tree view know that it needs to update
			InterfacePtr<ISubject> pPanel( QueryPanelSubject() );
			if( pPanel )
				pPanel->Change( kAutoCorrectEditorMsgLanguageHasChanged, IID_IAUTOCORRECTPANELMSG, nil );
		}
	}

	AutoCorrectPanelObserver::Update(theChange, theSubject, protocol, changedBy);
}
//===============================================================
// CLASS AutoCorrectRemoveButtonObserver
//===============================================================

CREATE_PMINTERFACE(AutoCorrectCapCheckBoxObserver, kAutoCorrectCapCheckBoxObserverImpl)


AutoCorrectCapCheckBoxObserver::AutoCorrectCapCheckBoxObserver(IPMUnknown *boss) :
	AutoCorrectPanelObserver(boss)
{
	this->SetControlID( IID_ITRISTATECONTROLDATA );
	this->SetReset( kTrue );
}


void AutoCorrectCapCheckBoxObserver::AutoAttach()
{
 	AutoCorrectPanelObserver::AutoAttach();

	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IWidgetParent> grandParentHolder(parentHolder->GetParent(),UseDefaultIID());
	InterfacePtr<IPanelControlData> panel(grandParentHolder->GetParent(),IID_IPANELCONTROLDATA);
	IControlView* acCheckBox = panel->FindWidget(kAutoCorrectEnableCheckboxWidgetID);

	InterfacePtr<ISubject> subject( acCheckBox, UseDefaultIID() );
	if (subject)
	{
		if ( !subject->IsAttached( this, IID_ITRISTATECONTROLDATA ) )
			subject->AttachObserver( this, IID_ITRISTATECONTROLDATA );
	}
}


void AutoCorrectCapCheckBoxObserver::AutoDetach()
{
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IWidgetParent> grandParentHolder(parentHolder->GetParent(),UseDefaultIID());
	InterfacePtr<IPanelControlData> panel(grandParentHolder->GetParent(),IID_IPANELCONTROLDATA);
	IControlView* acCheckBox = panel->FindWidget(kAutoCorrectEnableCheckboxWidgetID);

	InterfacePtr<ISubject> subject( acCheckBox, UseDefaultIID() );
    if (subject)
    {
        if (subject->IsAttached( this, IID_ITRISTATECONTROLDATA ) )
            subject->DetachObserver( this, IID_ITRISTATECONTROLDATA );
    }
	
	AutoCorrectPanelObserver::AutoDetach();
}


bool16	AutoCorrectCapCheckBoxObserver::SetupWidget()
{
	bool16 	bHandled = kTrue;
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IWidgetParent> grandParentHolder(parentHolder->GetParent(),UseDefaultIID());
	InterfacePtr<IPanelControlData> panel(grandParentHolder->GetParent(),IID_IPANELCONTROLDATA);

	IControlView* acCheckBox = panel->FindWidget(kAutoCorrectEnableCheckboxWidgetID);
	
	InterfacePtr<IControlView> view(this, UseDefaultIID());
	if (! view)
		return kFalse;
	
    InterfacePtr<ITriStateControlData> checkBoxData(acCheckBox, IID_ITRISTATECONTROLDATA);
    if (checkBoxData->IsSelected())
		view->Enable();
	else
		view->Disable();
	
	return bHandled;
}

bool16 AutoCorrectCapCheckBoxObserver::ApplyToWidget()
{
	return SetupWidget();
}

bool16 AutoCorrectCapCheckBoxObserver::ApplyToFocus()
{
	return kTrue;
}

void AutoCorrectCapCheckBoxObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	switch (theChange.Get()) 
	{
		case kTrueStateMessage:
		case kFalseStateMessage:
			if (IID_ITRISTATECONTROLDATA == protocol)
			{
				SetupWidget();
			}
			break;

		default:
		{
			AutoCorrectPanelObserver::Update(theChange, theSubject, protocol, changedBy);
			break;
		}
    }
}




//template num nums
#include "K2Vector.tpp"
#include "k2sortedvector.tpp"
#include "k2sortedlookup.tpp"

#ifdef WINDOWS
#pragma warning (disable: 4660)
#endif

template class	K2SortedVector<WideString>;
template class	K2SortedLookup<WideString, WideString>;
