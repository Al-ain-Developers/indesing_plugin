//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/WritingModeUIID2.h $
//  
//  Owner: Kevin Van Wiel
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

#pragma once
#ifndef __WritingModeUIID2__
#define __WritingModeUIID2__

#define DEFAULTTEXTSIZE 12.0
#define DEFAULTLINENUMBERDISPLAYSIZE 9.0
#define MENUSIZEINDEX 1
#define MULTIINCREMENTMULTIPLE 20.0  // For scrolling
#define WIDGETBARHEIGHT 42.0
#define DEFAULTPARAINDENTMULTIPLIER 4.0
#define DEFAULTINFOCOLUMNWIDTH 136.0

#define TEXTLEFTINSET 6.0
#define TEXTRIGHTINSET 5.0

#define MAXDISPLAYDELETEDTEXTLENGTH 32000

//#define USETABLEDIVIDERLINE

#include "WritingModeUIID.h"

// <PlugInID>
//---------------------------------------------------------------
//	PlugInID
//---------
#define kWMUIPrefix2	kWMUIPrefix + 100

// <Class ID>
//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 1)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 2)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 3)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 4)
DECLARE_PMID(kClassIDSpace, kGalleyMenuBoss, kWMUIPrefix2 + 5)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 6)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 7)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 8)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 9)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 10)

//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 11)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 12)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 13)
DECLARE_PMID(kClassIDSpace, kOwnedIconTrackerBoss, kWMUIPrefix2 + 14)
DECLARE_PMID(kClassIDSpace, kOwnedIconTrackerRegisterBoss, kWMUIPrefix2 + 15)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 16)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 17)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 18)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 19)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 20)

DECLARE_PMID(kClassIDSpace, kInfoColumnWidgetBoss, kWMUIPrefix2 + 21)
DECLARE_PMID(kClassIDSpace, kCloseGalleyCmdBoss, kWMUIPrefix2 + 22)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 23)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 24)
// Selection Bosses
DECLARE_PMID(kClassIDSpace, kGalleyTextSelectionBoss, kWMUIPrefix2 + 25)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 26)
// Galley Text Tracker
DECLARE_PMID(kClassIDSpace, kGalleyTextTrackerBoss, kWMUIPrefix2 + 27)
DECLARE_PMID(kClassIDSpace, kGalleyTextTrackerRegisterBoss, kWMUIPrefix2 + 28)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 29)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 30)

// Keyboard shortcuts
DECLARE_PMID(kClassIDSpace, kWritingModeKeyboardShortcutsBoss, kWMUIPrefix2 + 31)
DECLARE_PMID(kClassIDSpace, kWritingModeShortcutContextBoss, kWMUIPrefix2 + 32)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 33)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 34)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 35)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 36)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 37)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 38)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 39)
// Tabbed UI
DECLARE_PMID(kClassIDSpace, kGalleyOpenLayoutWinResponderBoss, kWMUIPrefix2 + 40)

// DECLARE_PMID(kClassIDSpace, kChangeInCopyViewPrefsCmdBoss, kWMUIPrefix2 + 41)
// DECLARE_PMID(kClassIDSpace, kChangeInCopyViewPrefsWindowMsg, kWMUIPrefix2 + 42)
DECLARE_PMID(kClassIDSpace, kInCopyDocTabAreaBoss, kWMUIPrefix2 + 43)
DECLARE_PMID(kClassIDSpace, kInCopyDocPanelTabWidgetBoss, kWMUIPrefix2 + 44)
DECLARE_PMID(kClassIDSpace, kCreateGalleySignalBoss, kWMUIPrefix2 + 45)
// suspend / resume play pending invals
DECLARE_PMID(kClassIDSpace, kSuspendPlayPendingInvalsCmdBoss,		kWMUIPrefix2 + 46)
DECLARE_PMID(kClassIDSpace, kResumePlayPendingInvalsCmdBoss,		kWMUIPrefix2 + 47)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 48)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 49)
DECLARE_PMID(kClassIDSpace, kStoryEditorSelectionServiceBoss, kWMUIPrefix2 + 50)

//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 51)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 52)
DECLARE_PMID(kClassIDSpace, kStoryEditorPresentationBoss, kWMUIPrefix2 + 53) // CS4/OWL2: was kStoryEditorWindowBoss
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 54)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 55)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 56)
DECLARE_PMID(kClassIDSpace, kStoryEditorWindowServiceBoss, kWMUIPrefix2 + 57)
DECLARE_PMID(kClassIDSpace, kGalleySplitterBoss, kWMUIPrefix2 + 58)
// DECLARE_PMID(kClassIDSpace, kStoryPostProcessBoss, kWMUIPrefix2 + 59)
// DECLARE_PMID(kClassIDSpace, kStoryPreProcessBoss, kWMUIPrefix2 + 60)

// DECLARE_PMID(kClassIDSpace, kInsertNotificationBoss, kWMUIPrefix2 + 61)
// DECLARE_PMID(kClassIDSpace, kDeleteNotificationBoss, kWMUIPrefix2 + 62)
// DECLARE_PMID(kClassIDSpace, kReorderStoriesCmdBoss, kWMUIPrefix2 + 63)
// DECLARE_PMID(kClassIDSpace, kMergeStoriesRespBoss, kWMUIPrefix2 + 64)
DECLARE_PMID(kClassIDSpace, kStorySelectionTrackerBoss, kWMUIPrefix2 + 65)
// DECLARE_PMID(kClassIDSpace, kReplaceNotificationBoss, kWMUIPrefix2 + 66)
DECLARE_PMID(kClassIDSpace, kWorkflowChangeResponderBoss, kWMUIPrefix2 + 67)
// DECLARE_PMID(kClassIDSpace, kDamageAllNotificationCmdBoss, kWMUIPrefix2 + 68)
// DECLARE_PMID(kClassIDSpace, kCollapseFootnoteCmdBoss, kWMUIPrefix2 + 69)
// DECLARE_PMID(kClassIDSpace, kCollapseAllFootnotesCmdBoss, kWMUIPrefix2 + 70)

DECLARE_PMID(kClassIDSpace, kFootnoteTextTrackerBoss, kWMUIPrefix2 + 71)
DECLARE_PMID(kClassIDSpace, kFootnoteTrackerRegisterBoss, kWMUIPrefix2 + 72)
// DECLARE_PMID(kClassIDSpace, kOpenWindowInBackgroundPrefsWindowMsg, kWMUIPrefix2 + 73)
// DECLARE_PMID(kClassIDSpace, kGalleyOpenLayoutWinResponderDoneMsg, kWMUIPrefix2 + 74)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 75)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 76)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 77)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 78)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 79)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kWMUIPrefix2 + 80)
DECLARE_PMID(kClassIDSpace, kGalleyDoneBtnWidgetBoss, kWMUIPrefix2 + 81)
DECLARE_PMID(kClassIDSpace, kGalleyBtnPanelWidgetBoss, kWMUIPrefix2 + 82)
// <Interface ID>
//---------------------------------------------------------------
//	IIDs
//---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_IWRITINGDOCREFDATA, kWMUIPrefix2 + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTHIGHLIGHTER, kWMUIPrefix2 + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYREFDATA, kWMUIPrefix2 + 3)
// DECLARE_PMID(kInterfaceIDSpace, IID_ISINGLEFRAMEREFDATA, kWMUIPrefix2 + 4)
// DECLARE_PMID(kInterfaceIDSpace, IID_IMULTIFRAMEREFDATA, kWMUIPrefix2 + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYSCROLLDATA, kWMUIPrefix2 + 6)
//DO NOT REUSE (kWMUIPrefix2 + 8) - InDesign 2.0 thinks this is the ID for IID_IGALLEYSWITCH and draws text incorrectly
// DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYWAXARRANGER, kWMUIPrefix2 + 9)
// DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMEREF, kWMUIPrefix2 + 10)
// DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTCLIENTITEMSDATA, kWMUIPrefix2 + 11)
// DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTPAGENUMBER, kWMUIPrefix2 + 12)
// DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEDLINESCALCULATOR, kWMUIPrefix2 + 13)
// DECLARE_PMID(kInterfaceIDSpace, IID_IFAKESPREADLIST, kWMUIPrefix2 + 14)
// DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMEADDERTASK, kWMUIPrefix2 + 15)
// removed redlinerestoredata kWMUIPrefix2 + 16
// DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEDLINESCALCULATOR2, kWMUIPrefix2 + 17)
// // removed redlinerestoremenuitems kWMUIPrefix2 + 18
// DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYCOORDINATECONVERTER, kWMUIPrefix2 + 19)
 DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTLINES, kWMUIPrefix2 + 20)
// 
// DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYTEXTSELECTION_SUITE, kWMUIPrefix2 + 21)
// 
// //End Selection
 DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYWINDOWBOOL, kWMUIPrefix2 + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IQUICKCOMPOSER, kWMUIPrefix2 + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYTHREADDATA, kWMUIPrefix2 + 24)

// Galley selection navigation
// DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYTEXTNAVIGATIONSUITE, kWMUIPrefix2 + 25)
// DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYSERVICE, kWMUIPrefix2 + 26)
// DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYUTILS, kWMUIPrefix2 + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYUIUTILS, kWMUIPrefix2 + 27)
// 
 // Color Scheme
DECLARE_PMID(kInterfaceIDSpace, IID_IVIEWCOLORSCHEME, kWMUIPrefix2 + 28)
// 
// // This replaces IID_IGALLEYTEXTSELECTION_SUITE
// DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICTEXTSELECTION_SUITE, kWMUIPrefix2 + 29)
// // This replaces IID_IGALLEYTEXTNAVIGATIONSUITE
// DECLARE_PMID(kInterfaceIDSpace, IID_ICTEXTNAVIGATIONSUITE, kWMUIPrefix2 + 30)

// Draw tags (i.e. inline notes and xml)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWTAG, kWMUIPrefix2 + 31)

// Galley display settings (preferences)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYSETTINGS, kWMUIPrefix2 + 32)

// Galley text run information
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTRUNS, kWMUIPrefix2 + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGESTEXTRUN, kWMUIPrefix2 + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IINLINENOTETEXTRUN, kWMUIPrefix2 + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IINLINENOTETAGRUN, kWMUIPrefix2 + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTAGRUN, kWMUIPrefix2 + 38)

// Multiple story story management
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYMANAGER, kWMUIPrefix2 + 39)

// DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYSWITCH, kWMUIPrefix2 + 40)
// 
// // story info for print
// DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYINFOPRINT, kWMUIPrefix2 + 45)
// 
// // Tabbed UI
//DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYVIEWPREFS, kWMUIPrefix2 + 46)

// Owned item icon drawing and detection
DECLARE_PMID(kInterfaceIDSpace, IID_IOWNEDITEMICONS, kWMUIPrefix2 + 47)

// Galley/layout lines syncronization
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTLINESSYNC, kWMUIPrefix2 + 48)

// Galley text damage recording
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTDAMAGE, kWMUIPrefix2 + 49)

// Private interface to keep the deleted text selection state up to date.
//DECLARE_PMID(kInterfaceIDSpace, IID_ITCSELECTIONEXTRA, kWMUIPrefix2 + 50)

// Private interface used to optimize text caret position calculations
DECLARE_PMID(kInterfaceIDSpace, IID_ICARETVALIDATION, kWMUIPrefix2 + 51)

// Private interface to draw view contents
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYVIEWDRAWER, kWMUIPrefix2 + 52)

//GAP

// Selection Suite used to create an initial selection
// DECLARE_PMID(kInterfaceIDSpace, IID_IMAKENEWSELECTIONSUITE, kWMUIPrefix2 + 54)
// 
// // Used in InCopy to identify overset text containers
// DECLARE_PMID(kInterfaceIDSpace, IID_ICONTAINERCLASSIFICATION, kWMUIPrefix2 + 55)

// Used to draw icons with attributes of specific types like ruby, kenton and hyperlink source.
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTEICONS, kWMUIPrefix2 + 56)
// 
// DECLARE_PMID(kInterfaceIDSpace, IID_ITEMPTEXTSELECTION_SUITE, kWMUIPrefix2 + 57)
// DECLARE_PMID(kInterfaceIDSpace, IID_ILINELAYOUT, kWMUIPrefix2 + 58) //SEIssue move this

// Used to draw little red indicator for mispelled words found in hidden deleted text and more ?
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGEVIEWEXTRA, kWMUIPrefix2 + 59)

DECLARE_PMID(kInterfaceIDSpace, IID_IISSTORYEDITOR, kWMUIPrefix2 + 60)

//DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTCOMPOSEOBSERVER, kWMUIPrefix2 + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERSETADORNMENT, kWMUIPrefix2 + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IDEPTHRULER, kWMUIPrefix2 + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTNOTETAGRUN, kWMUIPrefix2 + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTNOTETEXTRUN, kWMUIPrefix2 + 65)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICOLLAPSEALLFOOTNOTES, kWMUIPrefix2 + 66)
// DECLARE_PMID(kInterfaceIDSpace, IID_ICOLLAPSEFOOTNOTE, kWMUIPrefix2 + 67)
// DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTNOTEVIEWSUITE, kWMUIPrefix2 + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVESCROLLOBSERVER, kWMUIPrefix2 + 69) 
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVELYSCROLLING, kWMUIPrefix2 + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMIBEAMDATA, kWMUIPrefix2 + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSETASKSETTINGS, kWMUIPrefix2 + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_IUNDOREDOINVALCACHE, kWMUIPrefix2 + 73)
// DECLARE_PMID(kInterfaceIDSpace, IID_IICOMPOSEINVALMANAGER, kWMUIPrefix2 + 74)
// DECLARE_PMID(kInterfaceIDSpace, IID_IDELAYOBSERVEATTACHTASK, kWMUIPrefix2 + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTRUNDATAHELPER, kWMUIPrefix2 + 76)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLECELLTEXTRUN, kWMUIPrefix2 + 77)
// DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEVIEWSUITE, kWMUIPrefix2 + 78)
// DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYTABLESHORCUTSUITE, kWMUIPrefix2 + 79)


// <Implementation ID>
//--------------------------------------------------------------- 
//	ImplementationIDs
//---------------------------------------------------------------
DECLARE_PMID(kImplementationIDSpace, kWritingDocRefDataImpl, kWMUIPrefix2 + 2)
DECLARE_PMID(kImplementationIDSpace, kTextHighlighterImpl, kWMUIPrefix2 + 3)
DECLARE_PMID(kImplementationIDSpace, kStoryRefDataImpl, kWMUIPrefix2 + 4)
DECLARE_PMID(kImplementationIDSpace, kGalleyScrollDataImpl, kWMUIPrefix2 + 6)
DECLARE_PMID(kImplementationIDSpace, kGalleyCustomIBeamDataImpl, kWMUIPrefix2 + 7)
DECLARE_PMID(kImplementationIDSpace, kUndoRedoInvalCacheImpl, kWMUIPrefix2 + 8)
// removed kBevelWidgetBoss
//DECLARE_PMID(kImplementationIDSpace, kBevelWidgetImpl, kWMUIPrefix2 + 9)
//DECLARE_PMID(kImplementationIDSpace, kGalleySwitchImpl, kWMUIPrefix2 + 10)
DECLARE_PMID(kImplementationIDSpace, kGalleyMenuImpl, kWMUIPrefix2 + 12)
// removed kGalleyPageMarginsImpl, kWMUIPrefix2 + 13
// removed kDeletedLinesCalculatorImpl, kWMUIPrefix2 + 14
DECLARE_PMID(kImplementationIDSpace, kOwnedIconTrackerImpl, kWMUIPrefix2 + 15)
DECLARE_PMID(kImplementationIDSpace, kOwnedIconTrackerRegisterImpl, kWMUIPrefix2 + 16)
// DECLARE_PMID(kImplementationIDSpace, kComposeInvalManagerImpl, kWMUIPrefix2 + 17)
// DECLARE_PMID(kImplementationIDSpace, kPersistUIDData2Impl, kWMUIPrefix2 + 18)
// DECLARE_PMID(kImplementationIDSpace, kFixWaxLinesCmdImpl, kWMUIPrefix2 + 19)
// DECLARE_PMID(kImplementationIDSpace, kPreDeleteWritingViewCmdImpl, kWMUIPrefix2 + 20)
// DECLARE_PMID(kImplementationIDSpace, kDetachWritingWidgetCmdImpl, kWMUIPrefix2 + 21)
// DECLARE_PMID(kImplementationIDSpace, kPostDeleteWritingViewCmdImpl, kWMUIPrefix2 + 22)
// DECLARE_PMID(kImplementationIDSpace, kPrvtFixWaxLinesCmdImpl, kWMUIPrefix2 + 24)
// removed redlinerestoredata kWMUIPrefix2 + 25
DECLARE_PMID(kImplementationIDSpace, kInfoColumnEventHandlerImpl, kWMUIPrefix2 + 26)
DECLARE_PMID(kImplementationIDSpace, kInfoColumnViewImpl, kWMUIPrefix2 + 27)
DECLARE_PMID(kImplementationIDSpace, kGalleyEventHandlerImpl, kWMUIPrefix2 + 28)
DECLARE_PMID(kImplementationIDSpace, kCloseGalleyPresentationCmdImpl, kWMUIPrefix2 + 29) // CS4/OWL2 Note: was kCloseGalleyWinCmdImpl
DECLARE_PMID(kImplementationIDSpace, kTextLinesImpl, kWMUIPrefix2 + 30)

// Selection Impls
// DECLARE_PMID(kImplementationIDSpace, kBaseWritingSelectionSnapshotCSBImpl, kWMUIPrefix2 + 31)
DECLARE_PMID(kImplementationIDSpace, kConcreteGalleyTextSelectionImpl, kWMUIPrefix2 + 32)
// DECLARE_PMID(kImplementationIDSpace, kGalleyTextSelectionSuiteImpl, kWMUIPrefix2 + 33)

DECLARE_PMID(kImplementationIDSpace, kGalleyTextSelectionHiliterImpl, kWMUIPrefix2 + 35)
DECLARE_PMID(kImplementationIDSpace, kGalleyHiliteObserverImpl, kWMUIPrefix2 + 36)

DECLARE_PMID(kImplementationIDSpace, kGalleyTextTrackerImpl, kWMUIPrefix2 + 37)
DECLARE_PMID(kImplementationIDSpace, kGalleyTextTrackerRegisterImpl, kWMUIPrefix2 + 38)
DECLARE_PMID(kImplementationIDSpace, kGalleyTextCaretImpl, kWMUIPrefix2 + 39)
DECLARE_PMID(kImplementationIDSpace, kGalleyTextCaretThreadImpl, kWMUIPrefix2 + 40)
DECLARE_PMID(kImplementationIDSpace, kQuickComposerImpl, kWMUIPrefix2 + 41)

// Keyboard Shortcut Context
DECLARE_PMID(kImplementationIDSpace, kGalleyShortcutContextImpl, kWMUIPrefix2 + 42)
//gap
DECLARE_PMID(kImplementationIDSpace, kTextRunDataHelperImpl, kWMUIPrefix2 + 44)
DECLARE_PMID(kImplementationIDSpace, kStoryThreadDataImpl, kWMUIPrefix2 + 45)

// For selection Nav
// DECLARE_PMID(kImplementationIDSpace, kGalleyTextNavigationSuiteImpl, kWMUIPrefix2 + 46)
// DECLARE_PMID(kImplementationIDSpace, kStoryServiceImpl, kWMUIPrefix2 + 47)	// on kTextStoryBoss

// Keyboard Shortcuts
DECLARE_PMID(kImplementationIDSpace, kWritingModeKeyboardShortcutsImpl, kWMUIPrefix2 + 48)
//DECLARE_PMID(kImplementationIDSpace, kGalleyUtilsImpl, kWMUIPrefix2 + 49)	// on kUtilsBoss
DECLARE_PMID(kImplementationIDSpace, kGalleyUIUtilsImpl, kWMUIPrefix2 + 49)	// on kUtilsBoss

// Color Scheme
DECLARE_PMID(kImplementationIDSpace, kViewColorSchemeImpl, kWMUIPrefix2 + 50)

// Draw tags (i.e. inline notes and xml)
DECLARE_PMID(kImplementationIDSpace, kDrawTagImpl, kWMUIPrefix2 + 51)

// Galley display settings
//DECLARE_PMID(kImplementationIDSpace, kGalleySettingsImpl, kWMUIPrefix2 + 52)

// Footnote view characteristics like hidden or collapsed are controlled by the footnote view suite
// DECLARE_PMID(kImplementationIDSpace, kGalleyFootnoteViewSuiteASBImpl, kWMUIPrefix2 + 53)
// DECLARE_PMID(kImplementationIDSpace, kGalleyFootnoteViewSuiteCSBImpl, kWMUIPrefix2 + 54)

DECLARE_PMID(kImplementationIDSpace, kTableCellTextRunImpl, kWMUIPrefix2 + 55)
//gap
// Galley text run information
DECLARE_PMID(kImplementationIDSpace, kTextRunsImpl, kWMUIPrefix2 + 57)
DECLARE_PMID(kImplementationIDSpace, kTrackChangesTextRunImpl, kWMUIPrefix2 + 58)
DECLARE_PMID(kImplementationIDSpace, kInlineNoteTextRunImpl, kWMUIPrefix2 + 59)
DECLARE_PMID(kImplementationIDSpace, kInlineNoteTagRunImpl, kWMUIPrefix2 + 60)
DECLARE_PMID(kImplementationIDSpace, kXMLTagRunImpl, kWMUIPrefix2 + 61)

// Multiple story management
DECLARE_PMID(kImplementationIDSpace, kStoryManagerImpl, kWMUIPrefix2 + 62)
DECLARE_PMID(kImplementationIDSpace, kActiveScrollObserverImpl, kWMUIPrefix2 + 63)

// for fill with placeholder text
//DECLARE_PMID(kImplementationIDSpace, kGalleyTextMiscellanySuiteCSBImpl, kWMUIPrefix2 + 64)

// Table view characteristics like collapsing
// DECLARE_PMID(kImplementationIDSpace, kGalleyTableViewSuiteASBImpl, kWMUIPrefix2 + 66)
// DECLARE_PMID(kImplementationIDSpace, kGalleyTableViewSuiteCSBImpl, kWMUIPrefix2 + 67)
//gap


// story info for print
//DECLARE_PMID(kImplementationIDSpace, kStoryInfoPrintImpl, kWMUIPrefix2 + 70)

// Tabbed UI
DECLARE_PMID(kImplementationIDSpace, kGalleyOpenLayoutWinRespImpl, kWMUIPrefix2 + 71)
//DECLARE_PMID(kImplementationIDSpace, kInCopyViewPrefsImpl, kWMUIPrefix2 + 72)
// DECLARE_PMID(kImplementationIDSpace, kChangeInCopyViewPrefsCmdImpl, kWMUIPrefix2 + 73)
DECLARE_PMID(kImplementationIDSpace, kDocViewTabObserverImpl, kWMUIPrefix2 + 74)
DECLARE_PMID(kImplementationIDSpace, kDocTabAreaViewPrefsObserverImpl, kWMUIPrefix2 + 75)
DECLARE_PMID(kImplementationIDSpace, kComposeTaskSettingsImpl, kWMUIPrefix2 + 76)
//DECLARE_PMID(kImplementationIDSpace, kDocTabAreaViewImpl, kWMUIPrefix2 + 77)
DECLARE_PMID(kImplementationIDSpace, kDocTabEventHandlerImpl, kWMUIPrefix2 + 78)
DECLARE_PMID(kImplementationIDSpace, kCreateGalleySignalServiceImpl, kWMUIPrefix2 + 79)

// Owned item icon drawing, detection
DECLARE_PMID(kImplementationIDSpace, kOwnedItemIconsImpl, kWMUIPrefix2 + 80)

// Galley/Layout line syncronization
//DECLARE_PMID(kImplementationIDSpace, kTextLinesSyncImpl, kWMUIPrefix2 + 81)

// Command to do/undo/redo replace damage for story/galley views
//DECLARE_PMID(kImplementationIDSpace, kReplaceNotificationImpl, kWMUIPrefix2 + 83)

// Galley Damage Recording
DECLARE_PMID(kImplementationIDSpace, kTextDamageImpl, kWMUIPrefix2 + 84)

// to suspend and resume play pending invals
DECLARE_PMID(kImplementationIDSpace, kSuspendPlayPendingInvalsCmdImpl, kWMUIPrefix2 + 85)
DECLARE_PMID(kImplementationIDSpace, kResumePlayPendingInvalsCmdImpl, kWMUIPrefix2 + 86)

// Private interface to keep the deleted text selection state up to date.
//DECLARE_PMID(kImplementationIDSpace, kTCSelectionExtraImpl, kWMUIPrefix2 + 87)

// Private interface used to optimize text caret position calculations
DECLARE_PMID(kImplementationIDSpace, kCaretValidationImpl, kWMUIPrefix2 + 88)

// DECLARE_PMID(kImplementationIDSpace, kStoryEditorSelectionServiceImpl, kWMUIPrefix2 + 89)
DECLARE_PMID(kImplementationIDSpace, kConcreteStoryEditorSelectionImpl, kWMUIPrefix2 + 90)

// Private interface implementation to create a scratch space for composing text
DECLARE_PMID(kImplementationIDSpace, kGalleyViewDrawerImpl, kWMUIPrefix2 + 91)
DECLARE_PMID(kImplementationIDSpace, kStoryEditorViewSelectionImpl, kWMUIPrefix2 + 92)
//gap
// DECLARE_PMID(kImplementationIDSpace, kGalleyTextNavigationSuiteASBImpl, kWMUIPrefix2 + 94)
// DECLARE_PMID(kImplementationIDSpace, kGalleyTextSelectionSuiteASBImpl, kWMUIPrefix2 + 95)
// 
// // Used to create new selections
// DECLARE_PMID(kImplementationIDSpace, kMakeNewSelectionSuiteImpl, kWMUIPrefix2 + 96)
// DECLARE_PMID(kImplementationIDSpace, kMakeNewSelectionSuiteASBImpl, kWMUIPrefix2 + 97)

//DECLARE_PMID(kImplementationIDSpace, kStoryWindowDocumentImpl, kWMUIPrefix2 + 98)	// FIXME_OWL2: unused?
//DECLARE_PMID(kImplementationIDSpace, kStoryEditorWindowTitleImpl, kWMUIPrefix2 + 99) // FIXME_OWL2: obsolete

// DECLARE_PMID(kImplementationIDSpace, kContainerClassificationImpl, kWMUIPrefix2 + 100)
// DECLARE_PMID(kImplementationIDSpace, kGalleyTextEditSuiteCSBImpl, kWMUIPrefix2 + 101)
DECLARE_PMID(kImplementationIDSpace, kStoryTextSelectionSuiteImpl, kWMUIPrefix2 + 102)


// Used to finish long compositions in the background
DECLARE_PMID(kImplementationIDSpace, kComposeTaskImpl, kWMUIPrefix2 + 103)

// Used to draw icons associated with certain attributes like ruby, kenton, hyperlinks
DECLARE_PMID(kImplementationIDSpace, kAttributeIconsImpl, kWMUIPrefix2 + 104)

DECLARE_PMID(kImplementationIDSpace, kTextSelectionIntegratorSuiteTempImpl, kWMUIPrefix2 + 105)
// 
// // Custom splitter widget handling interfaces
// DECLARE_PMID(kImplementationIDSpace, kGalleySplitterTrackerRegisterImpl, kWMUIPrefix2 + 106)
// DECLARE_PMID(kImplementationIDSpace, kGalleySplitterTrackerImpl, kWMUIPrefix2 + 107)
// DECLARE_PMID(kImplementationIDSpace, kGalleySplitterEHImpl, kWMUIPrefix2 + 108)
// 
DECLARE_PMID(kImplementationIDSpace, kStoryEditorWindowServiceProviderImpl, kWMUIPrefix2 + 109)
// DECLARE_PMID(kImplementationIDSpace, kStoryEditorWindowServiceImpl, kWMUIPrefix2 + 110)
// 
// DECLARE_PMID(kImplementationIDSpace, kGalleyIndexingDataSuiteCSBImpl, kWMUIPrefix2 + 111)
// 
 DECLARE_PMID(kImplementationIDSpace, kGalleySplitterObsImpl, kWMUIPrefix2 + 112)
// DECLARE_PMID(kImplementationIDSpace, kStoryPostProcessImpl, kWMUIPrefix2 + 113)
// DECLARE_PMID(kImplementationIDSpace, kStoryPreProcessImpl, kWMUIPrefix2 + 114)
// DECLARE_PMID(kImplementationIDSpace, kInsertNotificationImpl, kWMUIPrefix2 + 115)
// DECLARE_PMID(kImplementationIDSpace, kDeleteNotificationImpl, kWMUIPrefix2 + 116)
// DECLARE_PMID(kImplementationIDSpace, kGalleyCSBObserverImpl, kWMUIPrefix2 + 117)
// 
// DECLARE_PMID(kImplementationIDSpace, kReorderStoriesCmdImpl, kWMUIPrefix2 + 118)
// DECLARE_PMID(kImplementationIDSpace, kMergeStoriesRespImpl, kWMUIPrefix2 + 119)
DECLARE_PMID(kImplementationIDSpace, kStoryTextSelectTrackerImpl, kWMUIPrefix2 + 120)
// DECLARE_PMID(kImplementationIDSpace, kStoryLineLayoutImpl, kWMUIPrefix2 + 121)
DECLARE_PMID(kImplementationIDSpace, kTrackChangeViewExtraImpl, kWMUIPrefix2 + 122)

//DECLARE_PMID(kImplementationIDSpace, kTypeToolSuiteGalleyCSBImpl, kWMUIPrefix2 + 123)
DECLARE_PMID(kImplementationIDSpace, kWorkflowChangeResponderImpl, kWMUIPrefix2 + 124)
DECLARE_PMID(kImplementationIDSpace, kGBridgeCmdResponderServiceImpl, kWMUIPrefix2 + 125)
//DECLARE_PMID(kImplementationIDSpace, kDamageAllNotificationCmdImpl, kWMUIPrefix2 + 126)
//DECLARE_PMID(kImplementationIDSpace, kLayoutComposeObserverImpl, kWMUIPrefix2 + 127)
DECLARE_PMID(kImplementationIDSpace, kOversetTextAdornmentImpl, kWMUIPrefix2 + 128)

// DECLARE_PMID(kImplementationIDSpace, kGalleyTextUniformTargetFactoryImpl, kWMUIPrefix2 + 129)
// DECLARE_PMID(kImplementationIDSpace, kGalleyTextSelectionFactoryImpl, kWMUIPrefix2 + 130)
DECLARE_PMID(kImplementationIDSpace, kStoryEditorSelectionFactoryImpl, kWMUIPrefix2 + 131)
DECLARE_PMID(kImplementationIDSpace, kDepthRulerImpl, kWMUIPrefix2 + 132)
DECLARE_PMID(kImplementationIDSpace, kFootnoteTagRunImpl, kWMUIPrefix2 + 133)
DECLARE_PMID(kImplementationIDSpace, kFootnoteTextRunImpl, kWMUIPrefix2 + 134)
DECLARE_PMID(kImplementationIDSpace, kFootnoteTextTrackerImpl, kWMUIPrefix2 + 135)
DECLARE_PMID(kImplementationIDSpace, kFootnoteTrackerRegisterImpl, kWMUIPrefix2 + 136)

//TextTarget impl
// DECLARE_PMID(kImplementationIDSpace, kBaseWritingTextTargetImpl, kWMUIPrefix2 + 137)
// DECLARE_PMID(kImplementationIDSpace, kDelayObserveAttachTaskImpl, kWMUIPrefix2 + 138)

DECLARE_PMID(kImplementationIDSpace, kStoryEditorPresentationImpl, kWMUIPrefix2 + 139)
DECLARE_PMID(kImplementationIDSpace, kStoryEditorShortcutContextImpl, kWMUIPrefix2 + 140)

 DECLARE_PMID(kImplementationIDSpace, kGalleyViewButtonObserverImpl, kWMUIPrefix2 + 141)


// GalleyTextAdornment impls: These may go away if we support choose to support
// IGalleyTextAdornment::DrawPriority() in the future
// 
 DECLARE_PMID(kImplementationIDSpace, kGalleyTextAdornmentBeforeServiceImpl, kWMUIPrefix2 + 150)
 DECLARE_PMID(kImplementationIDSpace, kGalleyTextAdornmentAfterServiceImpl, kWMUIPrefix2 + 151)


// <Action ID>
//---------------------------------------------------------------
//	Action IDs
//---------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator1MAID, kWMUIPrefix2 + 1)
DECLARE_PMID(kActionIDSpace, kShowInfoColumnMenuMAID, kWMUIPrefix2 + 2)
DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator2MAID, kWMUIPrefix2 + 3)
DECLARE_PMID(kActionIDSpace, kGalleyViewMenuMAID, kWMUIPrefix2 + 4)
DECLARE_PMID(kActionIDSpace, kToggleAccurateLineEndsMAID, kWMUIPrefix2 + 11)
DECLARE_PMID(kActionIDSpace, kTempTestSpeedMAID, kWMUIPrefix2 + 12)

// gap

DECLARE_PMID(kActionIDSpace, kLayoutViewMenuMAID, kWMUIPrefix2 + 20)
DECLARE_PMID(kActionIDSpace, kStoryEditorViewMenuMAID, kWMUIPrefix2 + 21)
DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator3MAID, kWMUIPrefix2 + 22)
DECLARE_PMID(kActionIDSpace, kExpandStoryMenuMAID, kWMUIPrefix2 + 23)
DECLARE_PMID(kActionIDSpace, kExpandAllStoriesMenuMAID, kWMUIPrefix2 + 24)
DECLARE_PMID(kActionIDSpace, kCollapseAllStoriesMenuMAID, kWMUIPrefix2 + 25)
DECLARE_PMID(kActionIDSpace, kShowLineNumbersMenuMAID, kWMUIPrefix2 + 26)
DECLARE_PMID(kActionIDSpace, kShowStylesMenuMAID, kWMUIPrefix2 + 29)
DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator4MAID, kWMUIPrefix2 + 30)
//gap
DECLARE_PMID(kActionIDSpace, kShowParagraphsMenuMAID, kWMUIPrefix2 + 32)

DECLARE_PMID(kActionIDSpace, kGalleyDeleteWordActionID, kWMUIPrefix2 + 33)
DECLARE_PMID(kActionIDSpace, kGalleyDeleteSentenceActionID, kWMUIPrefix2 + 34) 
DECLARE_PMID(kActionIDSpace, kGalleyDeleteParagraphActionID, kWMUIPrefix2 + 35) 

DECLARE_PMID(kActionIDSpace, kGalleySelectPrevWordActionID, kWMUIPrefix2 + 37)
DECLARE_PMID(kActionIDSpace, kGalleySelectNextWordActionID, kWMUIPrefix2 + 38)

DECLARE_PMID(kActionIDSpace, kGalleySelectCurrentParagraphActionID, kWMUIPrefix2 + 39)

DECLARE_PMID(kActionIDSpace, kGalleySelectNextSentenceActionID, kWMUIPrefix2 + 41)
DECLARE_PMID(kActionIDSpace, kGalleySelectPreviousSentenceActionID, kWMUIPrefix2 + 42)

DECLARE_PMID(kActionIDSpace, kGalleyMoveToNextSentenceActionID, kWMUIPrefix2 + 43)
DECLARE_PMID(kActionIDSpace, kGalleyMoveToPreviousSentenceActionID, kWMUIPrefix2 + 44)
DECLARE_PMID(kActionIDSpace, kShowDepthRulerMenuMAID, kWMUIPrefix2 + 45)

//gap

DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator5MAID, kWMUIPrefix2 + 47)
DECLARE_PMID(kActionIDSpace, kCollapseAllFootnotesMAID, kWMUIPrefix2 + 48)
DECLARE_PMID(kActionIDSpace, kGalleyMoveToPreviousStoryActionID, kWMUIPrefix2 + 49)
DECLARE_PMID(kActionIDSpace, kGalleyMoveToNextStoryActionID, kWMUIPrefix2 + 50)

DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator6MAID, kWMUIPrefix2 + 51)
DECLARE_PMID(kActionIDSpace, kArrangeByRowsMAID, kWMUIPrefix2 + 52)
DECLARE_PMID(kActionIDSpace, kArrangeByColumnsMAID, kWMUIPrefix2 + 53)

// 
// // <Service id>
// //---------------------------------------------------------------
// //	Service id's
// //---------------------------------------------------------------
 DECLARE_PMID(kServiceIDSpace, kCreateGalleyWidgetServiceID, kWMUIPrefix2 + 1)
// 
// // NOTE: kGalleyTextAdornmentBeforeService & kGalleyTextAdornmentAfterService
// // may go away if we support choose to support IGalleyTextAdornment::DrawPriority()
// // in the future
 DECLARE_PMID(kServiceIDSpace, kGalleyTextAdornmentBeforeService, kWMUIPrefix2 + 2)
 DECLARE_PMID(kServiceIDSpace, kGalleyTextAdornmentAfterService, kWMUIPrefix2 + 3)
// 
 DECLARE_PMID(kServiceIDSpace, kOpenStoryEditorSignalServiceID, kWMUIPrefix2 + 4)
// 
// // <Widget id>
// //---------------------------------------------------------------
// //	Widget id's
// //---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace,		kBevelWidgetID, 			kWMUIPrefix2 + 1)
DECLARE_PMID(kWidgetIDSpace,		kMoabPageNavigateWidgetID, 	kWMUIPrefix2 + 2)
DECLARE_PMID(kWidgetIDSpace,		kMoabPageNavigateEditBoxWidgetID, 	kWMUIPrefix2 + 3)
DECLARE_PMID(kWidgetIDSpace,		kMoabFirstPageIconWidgetID, 	kWMUIPrefix2 + 4)
DECLARE_PMID(kWidgetIDSpace,		kMoabLastPageIconWidgetID, 	kWMUIPrefix2 + 5)
DECLARE_PMID(kWidgetIDSpace,		kMoabPageNumForwardIconWidgetID, 	kWMUIPrefix2 + 6)
DECLARE_PMID(kWidgetIDSpace,		kMoabPageNumBackwardIconWidgetID, 	kWMUIPrefix2 + 7)
DECLARE_PMID(kWidgetIDSpace,		kInfoColumnID, 	kWMUIPrefix2 + 9)
DECLARE_PMID(kWidgetIDSpace,		kInfoColumnSplitterID, 	kWMUIPrefix2 + 10)
DECLARE_PMID(kWidgetIDSpace,		kAreaRulerID, 	kWMUIPrefix2 + 11)
DECLARE_PMID(kWidgetIDSpace, 		kGalleyDoneBtnWidgetID, kWMUIPrefix2 + 12)
DECLARE_PMID(kWidgetIDSpace, 		kInDesignCommitBarWidgetID, kWMUIPrefix2 + 13)
DECLARE_PMID(kWidgetIDSpace, 		kGalleyCancelBtnWidgetID, kWMUIPrefix2 + 14)
DECLARE_PMID(kWidgetIDSpace, 		kGalleyBtnParentViewWidgetID, kWMUIPrefix2 + 15)

 
// //---------------------------------------------------
// // InvalHandlerTypeID
// //---------------------------------------------------
// DECLARE_PMID(kInvalHandlerIDSpace, kLayoutComposeAttachDetachInvalHandlerID, kWMUIPrefix2 + 1)
// 
// <Messages>
//---------------------------------------------------------------
//	Messages
//---------------------------------------------------------------
#define		kShowLineNumberMsg					kWMUIPrefix2 + 1
#define		kHideLineNumberMsg					kWMUIPrefix2 + 2
#define		kEnterRestoreModeMsg				kWMUIPrefix2 + 3
#define		kExitRestoreModeMsg					kWMUIPrefix2 + 4

#define		kPreSwitchToGalleyOneWindowMsg		kWMUIPrefix2 + 5
#define		kPostSwitchToGalleyOneWindowMsg		kWMUIPrefix2 + 6
#define		kPreSwitchToLayoutOneWindowMsg		kWMUIPrefix2 + 7
#define		kPostSwitchToLayoutOneWindowMsg		kWMUIPrefix2 + 8

#define		kPreSwitchToGalleyMsg		kWMUIPrefix2 + 9
#define		kPostSwitchToGalleyMsg		kWMUIPrefix2 + 10
#define		kPreSwitchToLayoutMsg		kWMUIPrefix2 + 11
#define		kPostSwitchToLayoutMsg		kWMUIPrefix2 + 12

#define		kPostToggleALEILEMsg		kWMUIPrefix2 + 13
#define		kPreToggleALEILEMsg			kWMUIPrefix2 + 14
#define		kPostSwitchSelectionCompleteMsg		kWMUIPrefix2 + 15
#endif // __WritingModeUIID2__
