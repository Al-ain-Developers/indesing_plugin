//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/SpellPanelID.h $
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

#ifndef __SpellPanelID__
#define __SpellPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


// Firedrake: kSpellingServicePrefix is now 0x5200, kSpellPanelPrefix used to have this value.
#define kSpellPanelPrefix			RezLong(0x1da00) 	

// PluginID
#define kSpellPanelPluginName 				"Spelling Panel"
DECLARE_PMID(kPlugInIDSpace, kSpellPanelPluginID, kSpellPanelPrefix + 1)


#define kSpellPanelRsrcID					1000
#define kSpellDialogRsrcID					1100
#define kSpellActionRsrcID					1200
#define kSpellPrefsPaletteRsrcID			1300	// Resource ID of Spell Prefs Panel/Dialog
#define kSpellPrefsDialogCreatorRsrcID		1400	// Resource ID of Spell Prefs Dialog-related resource
#define kSpellPanelMenuRsrcID				1500

#define kAutoCorrectPrefsPaletteRsrcID				1350	// Resource ID of AutoCorrect Prefs Panel/Dialog
#define kAutoCorrectTreeWidgetNodeRsrcID			1375	// Resource ID of AutoCorrect widget
#define kAutoCorrectPrefsDialogCreatorRsrcID		1450	// Resource ID of AutoCorrect Prefs Dialog-related resource
#define kAutoCorrectAddPairDialogRsrcID				1550	// Resource ID of AutoCorrect Prefs Dialog-related resource


#define kSpellPanelStringsRsrcID				2000
#define kSpellPanelStringsNoTransRsrcID			2100


// SpellPanel icons
#define kSpellPanelIconNoWord				20992
#define kSpellPanelIconCorrectWord			20993
#define kSpellPanelIconIncorrectWord		20994

#define kSpellPanelIconBackground           		20995
#define kSpellPanelIconService				20996
#define kSpellPanelIconOverset				20997
#define kSpellPanelIconWrap				20998

#define kSpellPanelIconApplyToText         		21000
#define kSpellPanelIconAdd              			21001
#define kSpellPanelIconRemove              		21002
#define kSpellPanelIconCheck				21003
#define kSpellPanelIconIgnore				21004
#define kSpellPanelIconSkip				21005
#define kSpellPanelIconReplace				21006

#define kSpellPanelIconFlag 				21007

#define kIconSpellCheckComplete            2000



// <Start IDC>
// <Class ID>
// Panel: 0 to 9
// gap
DECLARE_PMID(kClassIDSpace, kSpellMenuComponentBoss, kSpellPanelPrefix +  4)
DECLARE_PMID(kClassIDSpace, kSpellPanelDialogBoss, kSpellPanelPrefix +  5)
DECLARE_PMID(kClassIDSpace, kSpellPanelTestMenuBoss, kSpellPanelPrefix +  6)
//gap
//DECLARE_PMID(kClassIDSpace, kDynamicSpellCheckAdornmentBoss, kSpellPanelPrefix + 9)	// Now defined in SpellingServiceID.h. Related to changelist 248176 (Model-UI separation).


// Spell Panel Observer, buttons: 10 to 39
DECLARE_PMID(kClassIDSpace, kSpellCorrectObserverBoss, kSpellPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kSpellAddRemoveObserverBoss, kSpellPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSpellIgnoreObserverBoss, kSpellPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSpellCheckObserverBoss, kSpellPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kSpellSkipObserverBoss, kSpellPanelPrefix + 14)

DECLARE_PMID(kClassIDSpace, kSpellChangeButtonBoss, kSpellPanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kSpellChangeAllButtonBoss, kSpellPanelPrefix + 16)
DECLARE_PMID(kClassIDSpace, kSpellSkipButtonBoss, kSpellPanelPrefix + 17)
DECLARE_PMID(kClassIDSpace, kSpellIgnoreButtonBoss, kSpellPanelPrefix + 18)
DECLARE_PMID(kClassIDSpace, kSpellAddToListButtonBoss, kSpellPanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kSpellMisspelledWordBoss, kSpellPanelPrefix + 20)
DECLARE_PMID(kClassIDSpace, kSpellLanguageBoss, kSpellPanelPrefix + 21)
DECLARE_PMID(kClassIDSpace, kSpellMisspelledTextBoss, kSpellPanelPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSpellStatusTextBoss, kSpellPanelPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSpellAddAndContinueButtonBoss, kSpellPanelPrefix + 24)
DECLARE_PMID(kClassIDSpace, kSpellTargetListBoss, kSpellPanelPrefix + 25)
DECLARE_PMID(kClassIDSpace, kSpellCaseSensitiveObserverBoss, kSpellPanelPrefix + 26)

DECLARE_PMID(kClassIDSpace, kAutoCorrectEditButtonBoss, kSpellPanelPrefix + 29)
DECLARE_PMID(kClassIDSpace, kAutoCorrectPrefsDialogBoss, kSpellPanelPrefix + 30)
DECLARE_PMID(kClassIDSpace, kAutoCorrectCheckBoxObserverBoss, kSpellPanelPrefix + 31)
DECLARE_PMID(kClassIDSpace, kAutoCorrectTreeViewWidgetBoss, kSpellPanelPrefix + 32)
DECLARE_PMID(kClassIDSpace, kAutoCorrectTypingBoss, kSpellPanelPrefix + 33)
DECLARE_PMID(kClassIDSpace, kAutoCorrectTreeNodeWidgetBoss, kSpellPanelPrefix + 34)
DECLARE_PMID(kClassIDSpace, kAutoCorrectAddButtonBoss, kSpellPanelPrefix + 35)
DECLARE_PMID(kClassIDSpace, kAutoCorrectRemoveButtonBoss, kSpellPanelPrefix + 36)
DECLARE_PMID(kClassIDSpace, kAutoCorrectAddPairDialogBoss, kSpellPanelPrefix + 37)
DECLARE_PMID(kClassIDSpace, kAutoCorrectTreeViewObserverBoss, kSpellPanelPrefix + 38)
DECLARE_PMID(kClassIDSpace, kAutoCorrectCapCheckBoxObserverBoss, kSpellPanelPrefix + 39)
DECLARE_PMID(kClassIDSpace, kAutoCorrectLanguageObserverBoss, kSpellPanelPrefix + 40)
//gap
DECLARE_PMID(kClassIDSpace, kAutoCorrectNewWSResponderBoss, kSpellPanelPrefix + 42)
DECLARE_PMID(kClassIDSpace, kAutoCorrectFolderIdleTaskBoss, kSpellPanelPrefix + 43)


// Spell Panel Observer, editboxes: 50 to 69
DECLARE_PMID(kClassIDSpace, kSpellWordObserverBoss, kSpellPanelPrefix + 50)

// Spell Panel Observer, checkbox: 70 to 99
DECLARE_PMID(kClassIDSpace, kSpellBackgroundObserverBoss, kSpellPanelPrefix + 70)
DECLARE_PMID(kClassIDSpace, kSpellWrapObserverBoss, kSpellPanelPrefix + 71)
DECLARE_PMID(kClassIDSpace, kSpellOversetObserverBoss, kSpellPanelPrefix + 72)

// Spell Panel Observer, popups: 100 to 129
DECLARE_PMID(kClassIDSpace, kSpellLanguageObserverBoss, kSpellPanelPrefix + 100)
DECLARE_PMID(kClassIDSpace, kSpellScopeObserverBoss, kSpellPanelPrefix + 101)

// Rest, 140
DECLARE_PMID(kClassIDSpace, kSpellPanelPluginFileBoss, kSpellPanelPrefix + 130)
DECLARE_PMID(kClassIDSpace, kSpellFlagObserverBoss, kSpellPanelPrefix + 131)
DECLARE_PMID(kClassIDSpace, kSpellAlternativesObserverBoss, kSpellPanelPrefix + 132)
// DECLARE_PMID(kClassIDSpace, kSpellLightObserverBoss, kSpellPanelPrefix + 133)
DECLARE_PMID(kClassIDSpace, kSpellServiceObserverBoss, kSpellPanelPrefix + 134)
//gap
DECLARE_PMID(kClassIDSpace, kApplySpellPanelOptionsCmdBoss, kSpellPanelPrefix + 136)
//gap
DECLARE_PMID(kClassIDSpace, kSpellReplaceClientBoss, kSpellPanelPrefix + 143)
DECLARE_PMID(kClassIDSpace, kSpellCheckClientBoss, kSpellPanelPrefix + 144)
DECLARE_PMID(kClassIDSpace, kDynamicSpellCheckThreadBoss, kSpellPanelPrefix + 145)
DECLARE_PMID(kClassIDSpace, kDynamicSpellCheckNewDocResponderBoss, kSpellPanelPrefix + 146)
DECLARE_PMID(kClassIDSpace, kDynamicSpellCheckOpenDocResponderBoss, kSpellPanelPrefix + 147)
DECLARE_PMID(kClassIDSpace, kDynamicSpellCheckCloseDocResponderBoss, kSpellPanelPrefix + 148)

//gap
DECLARE_PMID(kClassIDSpace, kSpellPrefsDialogBoss, kSpellPanelPrefix + 150)
DECLARE_PMID(kClassIDSpace, kLinguisticTestMenuBoss, kSpellPanelPrefix + 151)
DECLARE_PMID(kClassIDSpace, kSpellForwardRadioButtonWidgetBoss, kSpellPanelPrefix + 152)
DECLARE_PMID(kClassIDSpace, kSpellBackwardRadioButtonWidgetBoss, kSpellPanelPrefix + 153)



DECLARE_PMID(kMessageIDSpace, kAutoCorrectEditorMsgLanguageHasChanged, kSpellPanelPrefix + 100)


// Spell Panel messages fired on IID_ISPELLPANELMSG, 200 to 250
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgSelectNextItem, kSpellPanelPrefix + 200)
	// sent by SpellWordEventHandler::NotifySpellNextAlternative arrow key hit.
	// received by SpellAlternativesObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgSelectPrevItem, kSpellPanelPrefix + 201)
	// sent by SpellWordEventHandler::NotifySpellNextAlternative arrow key hit.
	// received by SpellAlternativesObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgSelectedItemHasChanged, kSpellPanelPrefix + 202)
	// sent by SpellAlternativesObserver::NotifyListBoxSelectionChanged on selection changes,
	// received by SpellWordObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgWordHasChanged, kSpellPanelPrefix + 203)
	// sent by SpellWordObserver::NotifySpellWordObserver and SpellWordEventHandler::NotifySpellWordObserver on word changes
	// received by SpellAlternativesObserver and SpellLightObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgWordHasBeenCorrected, kSpellPanelPrefix + 204)
	// sent by SpellAlternativesObserver::NotifySpellCorrect on detected mispelling.
	// received by SpellLightObserver.
	// changeby is SpellAlternativesObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgFindAlternatives, kSpellPanelPrefix + 205)
	// sent by SpellWordEventHandler::NotifySpellNextAlternative space key hit.
	// received by SpellAlternativesObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgDelayThread, kSpellPanelPrefix + 206)
	// sent by SpellWordEventHandler::NotifySpellNextAlternative every kSleepMilliseconds (1000) milliseconds.
	// received by SpellWordObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgApplyToText, kSpellPanelPrefix + 207)
	// sent by SpellWordEventHandler and  SpellWordCorrectObserver when the word should be applied.
	// received by SpellWordObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgDone, kSpellPanelPrefix + 208)
	// sent by SpellWordObserver after applying the text.
	// received by SpellCheckObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgWrapHasChanged, kSpellPanelPrefix + 209)
	// sent by SpellWrapObserver.
	// received by SpellCheckObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgScopeHasChanged, kSpellPanelPrefix + 210)
	// sent by SpellScopeObserver.
	// received by SpellCheckObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgOversetHasChanged, kSpellPanelPrefix + 211)
	// sent by SpellOversetObserver.
	// received by SpellCheckObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgFocusHasChanged, kSpellPanelPrefix + 212)
	// sent by SpellWordObserver on TextFocus and Selection changes, protocol: IID_ISPELLFOCUSCHANGED
	// received by SpellCheckObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgTextWalker, kSpellPanelPrefix + 213)
	// sent by SpellCheckObserver before ITextWalker::Walk() call.
	// received by SpellProgressBarObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgStartCorrect, kSpellPanelPrefix + 214)
	// sent by SpellCheckObserver in StartCorrect() before entering the interactive spelling mode.
	// received by SpellScopeObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgEndCorrect, kSpellPanelPrefix + 215)
	// sent by SpellCheckObserver in EndCorrect() before leaving the interactive spelling mode.
	// received by SpellScopeObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgGrammarOfText, kSpellPanelPrefix + 216)
	// sent by SpellWordObserver::NotifySpellWordObserver on grammar changes
	// received by SpellAlternativesObserver
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgResumeChecking, kSpellPanelPrefix + 217)
	// sent by SpellSkipObserver::NotifySpellWordObserver on button down
	// received by SpellAlternativesObserver
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgResetToMisspelledWord, kSpellPanelPrefix + 218)
	// sent by SpellMisspelledEH::NotifySpellWordObserver() on button down.
	// received by SpellWordObserver.
	// changeby is SpellMisspelledEH.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgReadyToStart, kSpellPanelPrefix + 219)
	// sent by SpellChangeObserver::NotifyObserver() on SetMode( kStart ).
	// received by SpellWordObserver.
	// changeby is SpellChangeObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgReadyToChange, kSpellPanelPrefix + 220)
	// sent by SpellChangeObserver::NotifyObserver() on SetMode( kChange ).
	// received by SpellMisspelledObserver.
	// changeby is SpellChangeObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgClearStatusText, kSpellPanelPrefix + 221)
	// sent by anybody who wants to clear the status line.
	// received by SpellStatusTextObserver.
	// changeby is IPMUnknown.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgSetStatusText, kSpellPanelPrefix + 222)
	// sent by anybody who wants to set the status line.
	// received by SpellStatusTextObserver.
	// changeby is PMString.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgNewWordToSpell, kSpellPanelPrefix + 223)
	// sent by SpellWordObserver::SetNewWordToSpell after setting the new word to spell.
	// received by SpellMisspelledObserver.
	// changeby is PMString.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgSetToStart, kSpellPanelPrefix + 224)
	// sent by SpellWordObserver::NotifyMsgSetToStart.
	// received by SpellChangeObserver, that changes to 'Start'.
	// changeby is SpellWordObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgSetToChange, kSpellPanelPrefix + 225)
	// sent by ???.
	// received by SpellChangeObserver, that changes to 'Change'.
	// changeby is SpellWordObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgChangeEnabled, kSpellPanelPrefix + 226)
	// sent by SpellChangeObserver.
	// received by SpellChangeAllObserver, that does the same.
	// changeby is SpellChangeObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgChangeDisabled, kSpellPanelPrefix + 227)
	// sent by SpellChangeObserver.
	// received by SpellChangeAllObserver, that does the same.
	// changeby is SpellChangeObserver.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgItemSelected, kSpellPanelPrefix + 228)
	// sent by SpellListBoxEH on SpellListBoxEH::LButtonDn().
	// received by SpellWordObserver.
	// changeby is SpellListBoxEH.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgItemExecuted, kSpellPanelPrefix + 229)
	// sent by SpellListBoxEH on SpellListBoxEH::ButtonDblClk().
	// received by SpellWordObserver.
	// changeby is SpellListBoxEH.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgWordGetsFocus, kSpellPanelPrefix + 230)
	// sent by SpellWordEH on SpellWordEH::GetFocus().
	// received by ???.
	// changeby is SpellWordEH.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgFinished, kSpellPanelPrefix + 231)
	// sent by ???.
	// received by ???.
	// changeby by ???.
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgTargetHasChanged, kSpellPanelPrefix + 232)
	// sent by SpellPreviousObserver
	// received by SpellScopeObserver
	// changeby by SpellPreviousObserver
DECLARE_PMID(kMessageIDSpace, kSpellPanelMsgDirectionHasChanged, kSpellPanelPrefix + 233)



// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLPANELMSG, kSpellPanelPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLDELAYTHREAD, kSpellPanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLFOCUSCHANGED, kSpellPanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLPANELOPTIONS, kSpellPanelPrefix + 3	/* added to the session, kSpellPanelOptions */)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEDSPELLPANELOPTIONS, kSpellPanelPrefix + 4	/* used by kApplySpellPanelOptionsCmdBoss. */)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IWORDTOSPELL, kSpellPanelPrefix + 6	/* used by kSpellAlternativesObserverBoss,  contains the word in the text. */)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLCHECKWALKERDATA, kSpellPanelPrefix + 7	/* used by kSpellCheckWalker. */)
DECLARE_PMID(kInterfaceIDSpace, IID_IDSCACTIVEFLAG, kSpellPanelPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICSPELLCHECKCACHE, kSpellPanelPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICSPELLINGRANGEDATA, kSpellPanelPrefix + 11) /* implemented via IRangeData */
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOCORRECTRANGEDATA, kSpellPanelPrefix + 12) /* implemented via IRangeData */
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATESPELLINGUTILS, kSpellPanelPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOCORRECTPANELMSG, kSpellPanelPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ICORRECTEDSTRINGDATA, kSpellPanelPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTDSCOBSERVER, kSpellPanelPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDINGWORDMODEBOOLDATA, kSpellPanelPrefix + 17)



// <Implementation ID>
// Implementations
DECLARE_PMID(kImplementationIDSpace, kSpellPanel, kSpellPanelPrefix + 0)
// gap
DECLARE_PMID(kImplementationIDSpace, kMsgSpellSetupWidget, kSpellPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kMsgSpellUpdateWidget, kSpellPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSpellPanelObserver, kSpellPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSpellMenuComponent, kSpellPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSpellCheckClientImpl, kSpellPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSpellPanelOptionsImpl, kSpellPanelPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSpellStatusTextObserverImpl, kSpellPanelPrefix + 9)

// Spell Panel Observer, buttons: 10 to 39
DECLARE_PMID(kImplementationIDSpace, kSpellCorrectObserver, kSpellPanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSpellAddRemoveObserver, kSpellPanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSpellIgnoreObserver, kSpellPanelPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSpellCheckObserver, kSpellPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSpellSkipObserver, kSpellPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSpellAddToListObserver, kSpellPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSpellChangeObserver, kSpellPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSpellChangeAllObserver, kSpellPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSpellTargetListObserverImpl, kSpellPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSpellCaseSensitiveObserverImpl, kSpellPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kSpellPreviousObserverImpl, kSpellPanelPrefix + 20)

// Spell Panel Observer, editboxes: 40 to 69
DECLARE_PMID(kImplementationIDSpace, kSpellWordObserver, kSpellPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kSpellWordEventHandler, kSpellPanelPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kSpellMisspelledObserver, kSpellPanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kSpellMisspelledEH, kSpellPanelPrefix + 43)

// Spell Panel Observer, checkbox: 70 to 99
DECLARE_PMID(kImplementationIDSpace, kSpellBackgroundObserver, kSpellPanelPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kSpellWrapObserver, kSpellPanelPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kSpellOversetObserver, kSpellPanelPrefix + 72)

// Spell Panel Observer, popups: 100 to 129
DECLARE_PMID(kImplementationIDSpace, kSpellLanguageObserver, kSpellPanelPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kSpellScopeObserver, kSpellPanelPrefix + 101)

// Rest
DECLARE_PMID(kImplementationIDSpace, kSpellPanelPluginFile, kSpellPanelPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kSpellFlagObserver, kSpellPanelPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kSpellAlternativesObserver, kSpellPanelPrefix + 132)
//DECLARE_PMID(kImplementationIDSpace, kSpellLightObserver, kSpellPanelPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kSpellServiceObserver, kSpellPanelPrefix + 134)
//DECLARE_PMID(kImplementationIDSpace, kSpellProgressBarObserver, kSpellPanelPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kSpellDelayThread, kSpellPanelPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kApplySpellPanelOptionsCmd, kSpellPanelPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kSpellListBoxEH, kSpellPanelPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kSpellStatusTextView, kSpellPanelPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kSpellTargetServer, kSpellPanelPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kSpellPanelTestMenu, kSpellPanelPrefix + 141			/* implementation in SpellPanelPlugin.cpp */)
DECLARE_PMID(kImplementationIDSpace, kSpellReplaceClientImpl, kSpellPanelPrefix + 142)
// gap
DECLARE_PMID(kImplementationIDSpace, kSpellCheckWalkerDataImpl, kSpellPanelPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kSpellPanelOptionsImpl2, kSpellPanelPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kDynamicSpellCheckAdornmentImpl, kSpellPanelPrefix + 146)
// gap
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectCheckBoxObserverImpl, kSpellPanelPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectCapCheckBoxObserverImpl, kSpellPanelPrefix + 161)
//gap
DECLARE_PMID(kImplementationIDSpace, kDynamicSpellCheckDocResponderImpl, kSpellPanelPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kSpellPrefsPanelCreatorImpl, kSpellPanelPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kSpellPrefsDialogControllerImpl, kSpellPanelPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kDynamicSpellCheckObserverImpl, kSpellPanelPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kGalleyDynamicSpellCheckAdornmentImpl, kSpellPanelPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kDynamicSpellCheckKeyEventWatcherImpl, kSpellPanelPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kDynamicSpellCheckTypingIdleTaskImpl, kSpellPanelPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kDynamicSpellCheckServiceProviderImpl, kSpellPanelPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kDynamicSpellCheckStartupShutdownImpl, kSpellPanelPrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kDynamicSpellCheckCacheImpl, kSpellPanelPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kDocumentDynamicSpellCheckObserverImpl, kSpellPanelPrefix + 189)

DECLARE_PMID(kImplementationIDSpace, kAutoCorrectPrefsPanelCreatorImpl, kSpellPanelPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectPrefsDialogControllerImpl, kSpellPanelPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectListObserverImpl, kSpellPanelPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectTypingIdleTaskImpl, kSpellPanelPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectKeyEventWatcherImpl, kSpellPanelPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectServiceProviderImpl, kSpellPanelPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectStartupShutdownImpl, kSpellPanelPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectObserverImpl, kSpellPanelPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectTreeViewWidgetMgrImpl, kSpellPanelPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectTreeViewAdapterImpl, kSpellPanelPrefix + 199)


// InCopy use
DECLARE_PMID(kImplementationIDSpace, kSpellPanelDialogControllerImpl, kSpellPanelPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kLinguisticTestMenuImpl, kSpellPanelPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kPrivateSpellingUtilsImpl, kSpellPanelPrefix + 202)

DECLARE_PMID(kImplementationIDSpace, kAutoCorrectEditButtonObserverImpl, kSpellPanelPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectAddButtonObserverImpl, kSpellPanelPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectRemoveButtonObserverImpl, kSpellPanelPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectAddPairDialogControllerImpl, kSpellPanelPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kCorrectedStringDataImpl, kSpellPanelPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectTreeViewObserverImpl, kSpellPanelPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectLanguageObserverImpl, kSpellPanelPrefix + 215)
//gap
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectNewWSResponderImpl, kSpellPanelPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kAutoCorrectFolderIdleTaskImpl, kSpellPanelPrefix + 218)


// <Widget ID>
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kSpellChangeButtonID, kSpellPanelPrefix +  1)
DECLARE_PMID(kWidgetIDSpace, kSpellChangeAllButtonID, kSpellPanelPrefix +  2)
DECLARE_PMID(kWidgetIDSpace, kSpellSkipButtonID, kSpellPanelPrefix +  3)
DECLARE_PMID(kWidgetIDSpace, kSpellIgnoreButtonID, kSpellPanelPrefix +  4)
DECLARE_PMID(kWidgetIDSpace, kSpellAddToListButtonID, kSpellPanelPrefix +  5)
DECLARE_PMID(kWidgetIDSpace, kSpellWordEditBoxID, kSpellPanelPrefix +  6)
DECLARE_PMID(kWidgetIDSpace, kSpellAlternativeEditBoxID, kSpellPanelPrefix +  7)
DECLARE_PMID(kWidgetIDSpace, kSpellAlternativesID, kSpellPanelPrefix +  8)
#define  kAlternativeListWidgetId kSpellAlternativesID
DECLARE_PMID(kWidgetIDSpace, kSpellOversetCheckBoxID, kSpellPanelPrefix +  9)
DECLARE_PMID(kWidgetIDSpace, kSpellLanguagePopupID, kSpellPanelPrefix +  10)
DECLARE_PMID(kWidgetIDSpace, kSpellScopePopupID, kSpellPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kSpellStatusIconID, kSpellPanelPrefix + 12)

DECLARE_PMID(kWidgetIDSpace, kSpellDlgParentWidgetID, kSpellPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kSpellStatusTextWidgetID, kSpellPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kSpellChangeToTextWidgetID, kSpellPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kSpellLanguageTextWidgetID, kSpellPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kSpellLanguageBossWidgetID, kSpellPanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kSpellSearchTextWidgetID, kSpellPanelPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kSpellOversetObserverWidgetID, kSpellPanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kSpellStatusTextBossWidgetID, kSpellPanelPrefix + 20)

DECLARE_PMID(kWidgetIDSpace, kSpellPnlParentWidgetID, kSpellPanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kSpellTAFlagObserverWidgetID, kSpellPanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kSpellTALanguagebserverWidgetID, kSpellPanelPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kSpellIconWidgetID, kSpellPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kSpellServiceObserverWidgetID, kSpellPanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kSpellLightObserverWidgetID, kSpellPanelPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kSpellCorrectObserverWidgetID, kSpellPanelPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kSpellAddRemoveObserverWidgetID, kSpellPanelPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kSpellIgnoreObserverWidgetID, kSpellPanelPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kSpellAddAndContinueButtonID, kSpellPanelPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kSpellSkipIconWidgetID, kSpellPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kSpellBackgroundObserverWidgetID, kSpellPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kSpellWordObserverWidgetID, kSpellPanelPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kSpellCheckObserverWidgetID, kSpellPanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kSpellDropTextWidgetID, kSpellPanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kSpellWrapIconWidgetID, kSpellPanelPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kSpellWrapObserverWidgetID, kSpellPanelPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kSpellProgressBarObserverWidgetID, kSpellPanelPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kSpellOversetIconWidgetID, kSpellPanelPrefix + 39)
//DECLARE_PMID(kWidgetIDSpace, kSpellOversetObserverWidgetID, kSpellPanelPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kSpellCorrectionsTextWidgetID, kSpellPanelPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kSpellCompleteIconWidgetID, kSpellPanelPrefix + 42)

DECLARE_PMID(kWidgetIDSpace, kAutoCorrectMisspelledEditTextWidgetID, kSpellPanelPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectCorrectedEditTextWidgetID, kSpellPanelPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectLanguageGroupWidgetID, kSpellPanelPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectLanguageWidgetID, kSpellPanelPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectLanguageTextWidgetID, kSpellPanelPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectMispelledColumnTextWidgetID, kSpellPanelPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectCorrectionColumnTextWidgetID, kSpellPanelPrefix + 76)

DECLARE_PMID(kWidgetIDSpace, kAutoCorrectPrefsDialogPanelWidgetID, kSpellPanelPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectPrefsPanelWidgetID, kSpellPanelPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectPrefsTitleTextWidgetID, kSpellPanelPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectCapitalizationErrorsCheckboxWidgetID, kSpellPanelPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectSettingsPanelWidgetID, kSpellPanelPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectSettingsTitleTextWidgetID, kSpellPanelPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectListWidgetID, kSpellPanelPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectPrefsDialogWidgetID, kSpellPanelPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectTreeViewWidgetID, kSpellPanelPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectTreeViewBorderWidgetID, kSpellPanelPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectEnableCheckboxWidgetID, kSpellPanelPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectTreeLeafWidgetId, kSpellPanelPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectTreeMisspelledWidgetId, kSpellPanelPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectTreeNodeWidgetId, kSpellPanelPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectMisspelledStaticTextWidgetID, kSpellPanelPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectCorrectedStaticTextWidgetID, kSpellPanelPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectAddButtonWidgetID, kSpellPanelPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectRemoveButtonWidgetID, kSpellPanelPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectColumnLabelBorderWidgetID, kSpellPanelPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kAutoCorrectEditButtonWidgetID, kSpellPanelPrefix + 99)

DECLARE_PMID(kWidgetIDSpace, kSpellPrefsDialogPanelWidgetID, kSpellPanelPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kSpellPrefsPanelWidgetID, kSpellPanelPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kSpellPrefsTitleTextWidgetID, kSpellPanelPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kSpellPrefsMisspelledWordsCheckboxWidgetID, kSpellPanelPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kSpellPrefsRepeatedWordsCheckboxWidgetID, kSpellPanelPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kSpellPrefsUncapitalizedWordsCheckboxWidgetID, kSpellPanelPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kSpellPrefsUncapitalizedSentencesCheckboxWidgetID, kSpellPanelPrefix + 106)

DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckPanelWidgetID, kSpellPanelPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckTitleTextWidgetID, kSpellPanelPrefix + 111)
//DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckGenericPanelWidgetID, kSpellPanelPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckMisspelledColorTextWidgetID, kSpellPanelPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckMisspelledColorDropDownWidgetID, kSpellPanelPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckMisspelledChangeColorSwatchWidgetID, kSpellPanelPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckCapitalizedWordColorTextWidgetID, kSpellPanelPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckCapitalizedWordColorDropDownWidgetID, kSpellPanelPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckCapitalizedWordChangeColorSwatchWidgetID, kSpellPanelPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckCapitalizedSentenceColorTextWidgetID, kSpellPanelPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckCapitalizedSentenceColorDropDownWidgetID, kSpellPanelPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckCapitalizedSentenceChangeColorSwatchWidgetID, kSpellPanelPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckRepeatedWordColorTextWidgetID, kSpellPanelPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckRepeatedWordColorDropDownWidgetID, kSpellPanelPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckRepeatedWordChangeColorSwatchWidgetID, kSpellPanelPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kSpellPrefsEnableDSCCheckboxWidgetID, kSpellPanelPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kUnderlineColorGroupWidgetId, kSpellPanelPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kUnderlineColorTitleTextWidgetID, kSpellPanelPrefix + 127)


DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckGeneric1PanelWidgetID, kSpellPanelPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckGeneric2PanelWidgetID, kSpellPanelPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckGeneric3PanelWidgetID, kSpellPanelPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kDynamicSpellCheckGeneric4PanelWidgetID, kSpellPanelPrefix + 133)

//DECLARE_PMID(kWidgetIDSpace, kDoneButtonWidgetID, kSpellPanelPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kUserDictTargetPopupID, kSpellPanelPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kSpellCaseSensitiveWidgetID, kSpellPanelPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kSpellDirectionWidgetID, kSpellPanelPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kSpellDirectionChooserWidgetID, kSpellPanelPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kSpellForwardRadioWidgetID, kSpellPanelPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kSpellBackwardsRadioWidgetID, kSpellPanelPrefix + 146)


// <Action ID>
// Action IDs
// ---- Action IDs, these are from SpellingServiceID.h

DECLARE_PMID(kActionIDSpace, kSpellCheckActionID,					kSpellPanelPrefix +  1)
DECLARE_PMID(kActionIDSpace, kNothingTextSpellSepActionID,			kSpellPanelPrefix +  2)
DECLARE_PMID(kActionIDSpace, kTextSpellSepActionID,					kSpellPanelPrefix +  3)
DECLARE_PMID(kActionIDSpace, kDynamicSpellCheckActionID,			kSpellPanelPrefix +  4)
DECLARE_PMID(kActionIDSpace, kSpellPrefsActionID,					kSpellPanelPrefix +  5)
DECLARE_PMID(kActionIDSpace, kSpellCheckSeparatorActionID,			kSpellPanelPrefix +  6)
DECLARE_PMID(kActionIDSpace, kAutoCorrectActionID,					kSpellPanelPrefix +  7)
DECLARE_PMID(kActionIDSpace, kAutoCorrectPrefsActionID,				kSpellPanelPrefix +  8)
DECLARE_PMID(kActionIDSpace, kSpellPrefsSepActionID,				kSpellPanelPrefix +  9)


#define    kAutoCorrectNodeIDClass    kSpellPanelPrefix + 1

#endif // __SpellPanelID__
