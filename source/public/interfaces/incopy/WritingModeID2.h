//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/WritingModeID2.h $
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
#ifndef __WritingModeID2__
#define __WritingModeID2__

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

#include "WritingModeID.h"

// <PlugInID>
//---------------------------------------------------------------
//	PlugInID
//---------
#define kWMPrefix2	kWMPrefix + 100

// <Class ID>
//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------
// removed galleyfitprogressbar kWMPrefix2 + 3
//DECLARE_PMID(kClassIDSpace, kBevelWidgetBoss, kWMPrefix2 + 4)
//DECLARE_PMID(kClassIDSpace, kGalleyMenuBoss, kWMPrefix2 + 5)
DECLARE_PMID(kClassIDSpace, kMoabPageNavigateEditBoxWidgetBoss, kWMPrefix2 + 6)
DECLARE_PMID(kClassIDSpace, kMoabFirstPageWidgetBoss, kWMPrefix2 + 7)
DECLARE_PMID(kClassIDSpace, kMoabLastPageWidgetBoss, kWMPrefix2 + 8)
DECLARE_PMID(kClassIDSpace, kMoabPageNumForwardWidgetBoss, kWMPrefix2 + 9)
DECLARE_PMID(kClassIDSpace, kMoabPageNumBackwardWidgetBoss, kWMPrefix2 + 10)
DECLARE_PMID(kClassIDSpace, kMoabPageNavigateWidgetBoss, kWMPrefix2 + 11)
DECLARE_PMID(kClassIDSpace, kFixWaxLinesCmdBoss, kWMPrefix2 + 12)
//DECLARE_PMID(kClassIDSpace, kPreDeleteWritingViewCmdBoss, kWMPrefix2 + 13)
//DECLARE_PMID(kClassIDSpace, kOwnedIconTrackerBoss, kWMPrefix2 + 14)
//DECLARE_PMID(kClassIDSpace, kOwnedIconTrackerRegisterBoss, kWMPrefix2 + 15)
//gap
//DECLARE_PMID(kClassIDSpace, kWritingModeMenuRegisterBoss, kWMPrefix2 + 19)
//DECLARE_PMID(kClassIDSpace, kWritingModeActionRegisterBoss, kWMPrefix2 + 20)
//DECLARE_PMID(kClassIDSpace, kInfoColumnWidgetBoss, kWMPrefix2 + 21)

// Selection Bosses
//DECLARE_PMID(kClassIDSpace, kGalleyTextISuiteBoss, kWMPrefix2 + 23)
DECLARE_PMID(kClassIDSpace, kGalleyTextSuiteBoss, kWMPrefix2 + 24)
//DECLARE_PMID(kClassIDSpace, kGalleyTextSelectionBoss, kWMPrefix2 + 25)
DECLARE_PMID(kClassIDSpace, kGalleyTextSelectionServiceBoss, kWMPrefix2 + 26)

// Galley Text Tracker
//DECLARE_PMID(kClassIDSpace, kGalleyTextTrackerBoss, kWMPrefix2 + 27)
//DECLARE_PMID(kClassIDSpace, kGalleyTextTrackerRegisterBoss, kWMPrefix2 + 28)

//gap

// Keyboard shortcuts
//DECLARE_PMID(kClassIDSpace, kWritingModeKeyboardShortcutsBoss, kWMPrefix2 + 31)
//DECLARE_PMID(kClassIDSpace, kWritingModeShortcutContextBoss, kWMPrefix2 + 32)

// inline note tracker (now moved into note plugin)
//DECLARE_PMID(kClassIDSpace, kInlineNoteTrackerBoss, kWMPrefix2 + 33)
//DECLARE_PMID(kClassIDSpace, kInlineNoteTrackerRegisterBoss, kWMPrefix2 + 34)
//gap
//DECLARE_PMID(kClassIDSpace, kSelectGalleyTextCmdBoss, kWMPrefix2 + 36)

// Used for setting up observers on new document creation
DECLARE_PMID(kClassIDSpace, kGalleyNewDocResponderBoss, kWMPrefix2 + 37)
DECLARE_PMID(kClassIDSpace, kGalleyOpenDocResponderBoss, kWMPrefix2 + 38)
//DECLARE_PMID(kClassIDSpace, kGalleyTextSuiteRegisterBoss, kWMPrefix2 + 39)

// Tabbed UI
//DECLARE_PMID(kClassIDSpace, kGalleyOpenLayoutWinResponderBoss, kWMPrefix2 + 40)
DECLARE_PMID(kClassIDSpace, kChangeInCopyViewPrefsCmdBoss, kWMPrefix2 + 41)
DECLARE_PMID(kClassIDSpace, kChangeInCopyViewPrefsWindowMsg, kWMPrefix2 + 42)
//DECLARE_PMID(kClassIDSpace, kInCopyDocTabAreaBoss, kWMPrefix2 + 43)
//DECLARE_PMID(kClassIDSpace, kInCopyDocPanelTabWidgetBoss, kWMPrefix2 + 44)
//DECLARE_PMID(kClassIDSpace, kCreateGalleySignalBoss, kWMPrefix2 + 45)

// suspend / resume play pending invals
//DECLARE_PMID(kClassIDSpace, kSuspendPlayPendingInvalsCmdBoss,		kWMPrefix2 + 46)
//DECLARE_PMID(kClassIDSpace, kResumePlayPendingInvalsCmdBoss,		kWMPrefix2 + 47)

// Schema stuff
DECLARE_PMID(kClassIDSpace, kGalleySettingsConversionProviderBoss,		kWMPrefix2 + 48)


DECLARE_PMID(kClassIDSpace, kStoryEditorSelectionBoss, kWMPrefix2 + 49)
//DECLARE_PMID(kClassIDSpace, kStoryEditorSelectionServiceBoss, kWMPrefix2 + 50)
DECLARE_PMID(kClassIDSpace, kStoryEditorSuiteBoss, kWMPrefix2 + 51)
//DECLARE_PMID(kClassIDSpace, kStoryEditorISuiteBoss, kWMPrefix2 + 52)

//DECLARE_PMID(kClassIDSpace, kStoryEditorWindowServiceBoss, kWMPrefix2 + 57)
//DECLARE_PMID(kClassIDSpace, kGalleySplitterBoss, kWMPrefix2 + 58)

DECLARE_PMID(kClassIDSpace, kStoryPostProcessBoss, kWMPrefix2 + 59)
DECLARE_PMID(kClassIDSpace, kStoryPreProcessBoss, kWMPrefix2 + 60)
DECLARE_PMID(kClassIDSpace, kInsertNotificationBoss, kWMPrefix2 + 61)
DECLARE_PMID(kClassIDSpace, kDeleteNotificationBoss, kWMPrefix2 + 62)

DECLARE_PMID(kClassIDSpace, kReorderStoriesCmdBoss, kWMPrefix2 + 63)
DECLARE_PMID(kClassIDSpace, kMergeStoriesRespBoss, kWMPrefix2 + 64)

//DECLARE_PMID(kClassIDSpace, kStorySelectionTrackerBoss, kWMPrefix2 + 65)

DECLARE_PMID(kClassIDSpace, kReplaceNotificationBoss, kWMPrefix2 + 66)

//DECLARE_PMID(kClassIDSpace, kWorkflowChangeResponderBoss, kWMPrefix2 + 67)

DECLARE_PMID(kClassIDSpace, kDamageAllNotificationCmdBoss, kWMPrefix2 + 68)

DECLARE_PMID(kClassIDSpace, kCollapseFootnoteCmdBoss, kWMPrefix2 + 69)
DECLARE_PMID(kClassIDSpace, kCollapseAllFootnotesCmdBoss, kWMPrefix2 + 70)
//DECLARE_PMID(kClassIDSpace, kFootnoteTextTrackerBoss, kWMPrefix2 + 71)
//DECLARE_PMID(kClassIDSpace, kFootnoteTrackerRegisterBoss, kWMPrefix2 + 72)
DECLARE_PMID(kClassIDSpace, kOpenWindowInBackgroundPrefsWindowMsg, kWMPrefix2 + 73)
DECLARE_PMID(kClassIDSpace, kGalleyOpenLayoutWinResponderDoneMsg, kWMPrefix2 + 74)



// <Interface ID>
//---------------------------------------------------------------
//	IIDs
//---------------------------------------------------------------
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRITINGDOCREFDATA, kWMPrefix2 + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IUNUSED, kWMPrefix2 + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYREFDATA, kWMPrefix2 + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISINGLEFRAMEREFDATA, kWMPrefix2 + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IMULTIFRAMEREFDATA, kWMPrefix2 + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYSCROLLDATA, kWMPrefix2 + 6)
//DO NOT REUSE (kWMPrefix2 + 8) - InDesign 2.0 thinks this is the ID for IID_IGALLEYSWITCH and draws text incorrectly
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYWAXARRANGER, kWMPrefix2 + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMEREF, kWMPrefix2 + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTCLIENTITEMSDATA, kWMPrefix2 + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRINTPAGENUMBER, kWMPrefix2 + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEDLINESCALCULATOR, kWMPrefix2 + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IFAKESPREADLIST, kWMPrefix2 + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMEADDERTASK, kWMPrefix2 + 15)
// removed redlinerestoredata kWMPrefix2 + 16
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEDLINESCALCULATOR2, kWMPrefix2 + 17)
// removed redlinerestoremenuitems kWMPrefix2 + 18
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYCOORDINATECONVERTER, kWMPrefix2 + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTLINES, kWMPrefix2 + 20)

DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYTEXTSELECTION_SUITE, kWMPrefix2 + 21)

//End Selection
//DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYWINDOWBOOL, kWMPrefix2 + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IQUICKCOMPOSER, kWMPrefix2 + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYTHREADDATA, kWMPrefix2 + 24)

// Galley selection navigation
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYTEXTNAVIGATIONSUITE, kWMPrefix2 + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYSERVICE, kWMPrefix2 + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYUTILS, kWMPrefix2 + 27)

// Color Scheme
//DECLARE_PMID(kInterfaceIDSpace, IID_IVIEWCOLORSCHEME, kWMPrefix2 + 28)

// This replaces IID_IGALLEYTEXTSELECTION_SUITE
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICTEXTSELECTION_SUITE, kWMPrefix2 + 29)
// This replaces IID_IGALLEYTEXTNAVIGATIONSUITE
DECLARE_PMID(kInterfaceIDSpace, IID_ICTEXTNAVIGATIONSUITE, kWMPrefix2 + 30)

// Draw tags (i.e. inline notes and xml)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWTAG, kWMPrefix2 + 31)

// Galley display settings (preferences)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYSETTINGS, kWMPrefix2 + 32)

// Galley text run information
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTRUNS, kWMPrefix2 + 34)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGESTEXTRUN, kWMPrefix2 + 35)
//DECLARE_PMID(kInterfaceIDSpace, IID_IINLINENOTETEXTRUN, kWMPrefix2 + 36)
//DECLARE_PMID(kInterfaceIDSpace, IID_IINLINENOTETAGRUN, kWMPrefix2 + 37)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTAGRUN, kWMPrefix2 + 38)

// Multiple story story management
//DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYMANAGER, kWMPrefix2 + 39)

DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYSWITCH, kWMPrefix2 + 40)

// story info for print
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYINFOPRINT, kWMPrefix2 + 45)

// Tabbed UI
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYVIEWPREFS, kWMPrefix2 + 46)

// Owned item icon drawing and detection
//DECLARE_PMID(kInterfaceIDSpace, IID_IOWNEDITEMICONS, kWMPrefix2 + 47)

// Galley/layout lines syncronization
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTLINESSYNC, kWMPrefix2 + 48)

// Galley text damage recording
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTDAMAGE, kWMPrefix2 + 49)

// Private interface to keep the deleted text selection state up to date.
DECLARE_PMID(kInterfaceIDSpace, IID_ITCSELECTIONEXTRA, kWMPrefix2 + 50)

// Private interface used to optimize text caret position calculations
//DECLARE_PMID(kInterfaceIDSpace, IID_ICARETVALIDATION, kWMPrefix2 + 51)

// Private interface to draw view contents
//DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYVIEWDRAWER, kWMPrefix2 + 52)

//GAP

// Selection Suite used to create an initial selection
DECLARE_PMID(kInterfaceIDSpace, IID_IMAKENEWSELECTIONSUITE, kWMPrefix2 + 54)

// Used in InCopy to identify overset text containers
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTAINERCLASSIFICATION, kWMPrefix2 + 55)

// Used to draw icons with attributes of specific types like ruby, kenton and hyperlink source.
//DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTEICONS, kWMPrefix2 + 56)

DECLARE_PMID(kInterfaceIDSpace, IID_ITEMPTEXTSELECTION_SUITE, kWMPrefix2 + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINELAYOUT, kWMPrefix2 + 58) //SEIssue move this

// Used to draw little red indicator for mispelled words found in hidden deleted text and more ?
//DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGEVIEWEXTRA, kWMPrefix2 + 59)

//DECLARE_PMID(kInterfaceIDSpace, IID_IISSTORYEDITOR, kWMPrefix2 + 60)

DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTCOMPOSEOBSERVER, kWMPrefix2 + 61)
//DECLARE_PMID(kInterfaceIDSpace, IID_IOVERSETADORNMENT, kWMPrefix2 + 62)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDEPTHRULER, kWMPrefix2 + 63)
//DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTNOTETAGRUN, kWMPrefix2 + 64)
//DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTNOTETEXTRUN, kWMPrefix2 + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLLAPSEALLFOOTNOTES, kWMPrefix2 + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLLAPSEFOOTNOTE, kWMPrefix2 + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTNOTEVIEWSUITE, kWMPrefix2 + 68)
//DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVESCROLLOBSERVER, kWMPrefix2 + 69) 
//DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVELYSCROLLING, kWMPrefix2 + 70)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMIBEAMDATA, kWMPrefix2 + 71)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSETASKSETTINGS, kWMPrefix2 + 72)
//DECLARE_PMID(kInterfaceIDSpace, IID_IUNDOREDOINVALCACHE, kWMPrefix2 + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_IICOMPOSEINVALMANAGER, kWMPrefix2 + 74)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELAYOBSERVEATTACHTASK, kWMPrefix2 + 75)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTRUNDATAHELPER, kWMPrefix2 + 76)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITABLECELLTEXTRUN, kWMPrefix2 + 77)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEVIEWSUITE, kWMPrefix2 + 78)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYTABLESHORCUTSUITE, kWMPrefix2 + 79)


// <Implementation ID>
//--------------------------------------------------------------- 
//	ImplementationIDs
//---------------------------------------------------------------
//DECLARE_PMID(kImplementationIDSpace, kWritingDocRefDataImpl, kWMPrefix2 + 2)
DECLARE_PMID(kImplementationIDSpace, kWritingPanelRefDataImpl, kWMPrefix2 + 3)
//gap
//DECLARE_PMID(kImplementationIDSpace, kGalleyScrollDataImpl, kWMPrefix2 + 6)
//DECLARE_PMID(kImplementationIDSpace, kGalleyCustomIBeamDataImpl, kWMPrefix2 + 7)
//DECLARE_PMID(kImplementationIDSpace, kUndoRedoInvalCacheImpl, kWMPrefix2 + 8)
//DECLARE_PMID(kImplementationIDSpace, kBevelWidgetImpl, kWMPrefix2 + 9)
DECLARE_PMID(kImplementationIDSpace, kGalleySwitchImpl, kWMPrefix2 + 10)
//DECLARE_PMID(kImplementationIDSpace, kGalleyMenuImpl, kWMPrefix2 + 12)
// removed kGalleyPageMarginsImpl, kWMPrefix2 + 13
// removed kDeletedLinesCalculatorImpl, kWMPrefix2 + 14
//DECLARE_PMID(kImplementationIDSpace, kOwnedIconTrackerImpl, kWMPrefix2 + 15)
//DECLARE_PMID(kImplementationIDSpace, kOwnedIconTrackerRegisterImpl, kWMPrefix2 + 16)
DECLARE_PMID(kImplementationIDSpace, kComposeInvalManagerImpl, kWMPrefix2 + 17)
DECLARE_PMID(kImplementationIDSpace, kPersistUIDData2Impl, kWMPrefix2 + 18)
DECLARE_PMID(kImplementationIDSpace, kFixWaxLinesCmdImpl, kWMPrefix2 + 19)
DECLARE_PMID(kImplementationIDSpace, kPreDeleteWritingViewCmdImpl, kWMPrefix2 + 20)
DECLARE_PMID(kImplementationIDSpace, kDetachWritingWidgetCmdImpl, kWMPrefix2 + 21)
DECLARE_PMID(kImplementationIDSpace, kPostDeleteWritingViewCmdImpl, kWMPrefix2 + 22)
DECLARE_PMID(kImplementationIDSpace, kPrvtFixWaxLinesCmdImpl, kWMPrefix2 + 24)
// removed redlinerestoredata kWMPrefix2 + 25
//DECLARE_PMID(kImplementationIDSpace, kInfoColumnEventHandlerImpl, kWMPrefix2 + 26)
//DECLARE_PMID(kImplementationIDSpace, kInfoColumnViewImpl, kWMPrefix2 + 27)
//DECLARE_PMID(kImplementationIDSpace, kGalleyEventHandlerImpl, kWMPrefix2 + 28)
//DECLARE_PMID(kImplementationIDSpace, kTextLinesImpl, kWMPrefix2 + 30)

// Selection Impls
DECLARE_PMID(kImplementationIDSpace, kBaseWritingSelectionSnapshotCSBImpl, kWMPrefix2 + 31)
//DECLARE_PMID(kImplementationIDSpace, kConcreteGalleyTextSelectionImpl, kWMPrefix2 + 32)
DECLARE_PMID(kImplementationIDSpace, kGalleyTextSelectionSuiteImpl, kWMPrefix2 + 33)

//DECLARE_PMID(kImplementationIDSpace, kGalleyTextSelectionHiliterImpl, kWMPrefix2 + 35)
//DECLARE_PMID(kImplementationIDSpace, kGalleyHiliteObserverImpl, kWMPrefix2 + 36)

//DECLARE_PMID(kImplementationIDSpace, kGalleyTextTrackerImpl, kWMPrefix2 + 37)
//DECLARE_PMID(kImplementationIDSpace, kGalleyTextTrackerRegisterImpl, kWMPrefix2 + 38)
//DECLARE_PMID(kImplementationIDSpace, kGalleyTextCaretImpl, kWMPrefix2 + 39)
//DECLARE_PMID(kImplementationIDSpace, kGalleyTextCaretThreadImpl, kWMPrefix2 + 40)
//DECLARE_PMID(kImplementationIDSpace, kQuickComposerImpl, kWMPrefix2 + 41)

// Keyboard Shortcut Context
//DECLARE_PMID(kImplementationIDSpace, kGalleyShortcutContextImpl, kWMPrefix2 + 42)
//gap
//DECLARE_PMID(kImplementationIDSpace, kTextRunDataHelperImpl, kWMPrefix2 + 44)
//DECLARE_PMID(kImplementationIDSpace, kStoryThreadDataImpl, kWMPrefix2 + 45)

// For selection Nav
DECLARE_PMID(kImplementationIDSpace, kGalleyTextNavigationSuiteImpl, kWMPrefix2 + 46)
DECLARE_PMID(kImplementationIDSpace, kStoryServiceImpl, kWMPrefix2 + 47)	// on kTextStoryBoss

// Keyboard Shortcuts
//DECLARE_PMID(kImplementationIDSpace, kWritingModeKeyboardShortcutsImpl, kWMPrefix2 + 48)
DECLARE_PMID(kImplementationIDSpace, kGalleyUtilsImpl, kWMPrefix2 + 49)	// on kUtilsBoss

// Color Scheme
//DECLARE_PMID(kImplementationIDSpace, kViewColorSchemeImpl, kWMPrefix2 + 50)

// Draw tags (i.e. inline notes and xml)
//DECLARE_PMID(kImplementationIDSpace, kDrawTagImpl, kWMPrefix2 + 51)

// Galley display settings
DECLARE_PMID(kImplementationIDSpace, kGalleySettingsImpl, kWMPrefix2 + 52)

// Footnote view characteristics like hidden or collapsed are controlled by the footnote view suite
DECLARE_PMID(kImplementationIDSpace, kGalleyFootnoteViewSuiteASBImpl, kWMPrefix2 + 53)
DECLARE_PMID(kImplementationIDSpace, kGalleyFootnoteViewSuiteCSBImpl, kWMPrefix2 + 54)

//DECLARE_PMID(kImplementationIDSpace, kTableCellTextRunImpl, kWMPrefix2 + 55)
//gap

// Galley text run information
//DECLARE_PMID(kImplementationIDSpace, kTextRunsImpl, kWMPrefix2 + 57)
//DECLARE_PMID(kImplementationIDSpace, kTrackChangesTextRunImpl, kWMPrefix2 + 58)
//DECLARE_PMID(kImplementationIDSpace, kInlineNoteTextRunImpl, kWMPrefix2 + 59)
//DECLARE_PMID(kImplementationIDSpace, kInlineNoteTagRunImpl, kWMPrefix2 + 60)
//DECLARE_PMID(kImplementationIDSpace, kXMLTagRunImpl, kWMPrefix2 + 61)

// Multiple story management
//DECLARE_PMID(kImplementationIDSpace, kStoryManagerImpl, kWMPrefix2 + 62)
//DECLARE_PMID(kImplementationIDSpace, kActiveScrollObserverImpl, kWMPrefix2 + 63)

// for fill with placeholder text
DECLARE_PMID(kImplementationIDSpace, kGalleyTextMiscellanySuiteCSBImpl, kWMPrefix2 + 64)

// For setting up preference and other observers that are changed when making a new document.
DECLARE_PMID(kImplementationIDSpace, kGalleyDocResponderImpl, kWMPrefix2 + 65)

// Table view characteristics like collapsing
DECLARE_PMID(kImplementationIDSpace, kGalleyTableViewSuiteASBImpl, kWMPrefix2 + 66)
DECLARE_PMID(kImplementationIDSpace, kGalleyTableViewSuiteCSBImpl, kWMPrefix2 + 67)
//gap


// story info for print
DECLARE_PMID(kImplementationIDSpace, kStoryInfoPrintImpl, kWMPrefix2 + 70)

// Tabbed UI
//DECLARE_PMID(kImplementationIDSpace, kGalleyOpenLayoutWinRespImpl, kWMPrefix2 + 71)
DECLARE_PMID(kImplementationIDSpace, kInCopyViewPrefsImpl, kWMPrefix2 + 72)
DECLARE_PMID(kImplementationIDSpace, kChangeInCopyViewPrefsCmdImpl, kWMPrefix2 + 73)
//DECLARE_PMID(kImplementationIDSpace, kDocViewTabObserverImpl, kWMPrefix2 + 74)
//DECLARE_PMID(kImplementationIDSpace, kDocTabAreaViewPrefsObserverImpl, kWMPrefix2 + 75)
//DECLARE_PMID(kImplementationIDSpace, kComposeTaskSettingsImpl, kWMPrefix2 + 76)
//DECLARE_PMID(kImplementationIDSpace, kDocTabAreaViewImpl, kWMPrefix2 + 77)
//DECLARE_PMID(kImplementationIDSpace, kDocTabEventHandlerImpl, kWMPrefix2 + 78)
//DECLARE_PMID(kImplementationIDSpace, kCreateGalleySignalServiceImpl, kWMPrefix2 + 79)

// Owned item icon drawing, detection
//DECLARE_PMID(kImplementationIDSpace, kOwnedItemIconsImpl, kWMPrefix2 + 80)

// Galley/Layout line syncronization
DECLARE_PMID(kImplementationIDSpace, kTextLinesSyncImpl, kWMPrefix2 + 81)

// Command to do/undo/redo replace damage for story/galley views
DECLARE_PMID(kImplementationIDSpace, kReplaceNotificationImpl, kWMPrefix2 + 83)

// Galley Damage Recording
//DECLARE_PMID(kImplementationIDSpace, kTextDamageImpl, kWMPrefix2 + 84)

// to suspend and resume play pending invals
//DECLARE_PMID(kImplementationIDSpace, kSuspendPlayPendingInvalsCmdImpl, kWMPrefix2 + 85)
//DECLARE_PMID(kImplementationIDSpace, kResumePlayPendingInvalsCmdImpl, kWMPrefix2 + 86)

// Private interface to keep the deleted text selection state up to date.
DECLARE_PMID(kImplementationIDSpace, kTCSelectionExtraImpl, kWMPrefix2 + 87)

// Private interface used to optimize text caret position calculations
//DECLARE_PMID(kImplementationIDSpace, kCaretValidationImpl, kWMPrefix2 + 88)

DECLARE_PMID(kImplementationIDSpace, kStoryEditorSelectionServiceImpl, kWMPrefix2 + 89)
//DECLARE_PMID(kImplementationIDSpace, kConcreteStoryEditorSelectionImpl, kWMPrefix2 + 90)

// Private interface implementation to create a scratch space for composing text
//DECLARE_PMID(kImplementationIDSpace, kGalleyViewDrawerImpl, kWMPrefix2 + 91)
//DECLARE_PMID(kImplementationIDSpace, kStoryEditorViewSelectionImpl, kWMPrefix2 + 92)
//gap
DECLARE_PMID(kImplementationIDSpace, kGalleyTextNavigationSuiteASBImpl, kWMPrefix2 + 94)
DECLARE_PMID(kImplementationIDSpace, kGalleyTextSelectionSuiteASBImpl, kWMPrefix2 + 95)

// Used to create new selections
DECLARE_PMID(kImplementationIDSpace, kMakeNewSelectionSuiteImpl, kWMPrefix2 + 96)
DECLARE_PMID(kImplementationIDSpace, kMakeNewSelectionSuiteASBImpl, kWMPrefix2 + 97)

//DECLARE_PMID(kImplementationIDSpace, kStoryWindowDocumentImpl, kWMPrefix2 + 98)	// FIXME_OWL2: unused?
//DECLARE_PMID(kImplementationIDSpace, kStoryEditorWindowTitleImpl, kWMPrefix2 + 99) // FIXME_OWL2: obsolete

DECLARE_PMID(kImplementationIDSpace, kContainerClassificationImpl, kWMPrefix2 + 100)
DECLARE_PMID(kImplementationIDSpace, kGalleyTextEditSuiteCSBImpl, kWMPrefix2 + 101)
//DECLARE_PMID(kImplementationIDSpace, kStoryTextSelectionSuiteImpl, kWMPrefix2 + 102)


// Used to finish long compositions in the background
//DECLARE_PMID(kImplementationIDSpace, kComposeTaskImpl, kWMPrefix2 + 103)

// Used to draw icons associated with certain attributes like ruby, kenton, hyperlinks
//DECLARE_PMID(kImplementationIDSpace, kAttributeIconsImpl, kWMPrefix2 + 104)

//DECLARE_PMID(kImplementationIDSpace, kTextSelectionIntegratorSuiteTempImpl, kWMPrefix2 + 105)

// Custom splitter widget handling interfaces
DECLARE_PMID(kImplementationIDSpace, kGalleySplitterTrackerRegisterImpl, kWMPrefix2 + 106)
DECLARE_PMID(kImplementationIDSpace, kGalleySplitterTrackerImpl, kWMPrefix2 + 107)
DECLARE_PMID(kImplementationIDSpace, kGalleySplitterEHImpl, kWMPrefix2 + 108)

//DECLARE_PMID(kImplementationIDSpace, kStoryEditorWindowServiceProviderImpl, kWMPrefix2 + 109)
DECLARE_PMID(kImplementationIDSpace, kStoryEditorWindowServiceImpl, kWMPrefix2 + 110)

DECLARE_PMID(kImplementationIDSpace, kGalleyIndexingDataSuiteCSBImpl, kWMPrefix2 + 111)

//DECLARE_PMID(kImplementationIDSpace, kGalleySplitterObsImpl, kWMPrefix2 + 112)
DECLARE_PMID(kImplementationIDSpace, kStoryPostProcessImpl, kWMPrefix2 + 113)
DECLARE_PMID(kImplementationIDSpace, kStoryPreProcessImpl, kWMPrefix2 + 114)
DECLARE_PMID(kImplementationIDSpace, kInsertNotificationImpl, kWMPrefix2 + 115)
DECLARE_PMID(kImplementationIDSpace, kDeleteNotificationImpl, kWMPrefix2 + 116)
DECLARE_PMID(kImplementationIDSpace, kGalleyCSBObserverImpl, kWMPrefix2 + 117)

DECLARE_PMID(kImplementationIDSpace, kReorderStoriesCmdImpl, kWMPrefix2 + 118)
DECLARE_PMID(kImplementationIDSpace, kMergeStoriesRespImpl, kWMPrefix2 + 119)
//DECLARE_PMID(kImplementationIDSpace, kStoryTextSelectTrackerImpl, kWMPrefix2 + 120)
DECLARE_PMID(kImplementationIDSpace, kStoryLineLayoutImpl, kWMPrefix2 + 121)
//DECLARE_PMID(kImplementationIDSpace, kTrackChangeViewExtraImpl, kWMPrefix2 + 122)

DECLARE_PMID(kImplementationIDSpace, kTypeToolSuiteGalleyCSBImpl, kWMPrefix2 + 123)
//DECLARE_PMID(kImplementationIDSpace, kWorkflowChangeResponderImpl, kWMPrefix2 + 124)
//DECLARE_PMID(kImplementationIDSpace, kGBridgeCmdResponderServiceImpl, kWMPrefix2 + 125)
DECLARE_PMID(kImplementationIDSpace, kDamageAllNotificationCmdImpl, kWMPrefix2 + 126)
DECLARE_PMID(kImplementationIDSpace, kLayoutComposeObserverImpl, kWMPrefix2 + 127)
//DECLARE_PMID(kImplementationIDSpace, kOversetTextAdornmentImpl, kWMPrefix2 + 128)

DECLARE_PMID(kImplementationIDSpace, kGalleyTextUniformTargetFactoryImpl, kWMPrefix2 + 129)
DECLARE_PMID(kImplementationIDSpace, kGalleyTextSelectionFactoryImpl, kWMPrefix2 + 130)
//DECLARE_PMID(kImplementationIDSpace, kStoryEditorSelectionFactoryImpl, kWMPrefix2 + 131)
//DECLARE_PMID(kImplementationIDSpace, kDepthRulerImpl, kWMPrefix2 + 132)
//DECLARE_PMID(kImplementationIDSpace, kFootnoteTagRunImpl, kWMPrefix2 + 133)
//DECLARE_PMID(kImplementationIDSpace, kFootnoteTextRunImpl, kWMPrefix2 + 134)
//DECLARE_PMID(kImplementationIDSpace, kFootnoteTextTrackerImpl, kWMPrefix2 + 135)
//DECLARE_PMID(kImplementationIDSpace, kFootnoteTrackerRegisterImpl, kWMPrefix2 + 136)

//TextTarget impl
DECLARE_PMID(kImplementationIDSpace, kBaseWritingTextTargetImpl, kWMPrefix2 + 137)
DECLARE_PMID(kImplementationIDSpace, kDelayObserveAttachTaskImpl, kWMPrefix2 + 138)

//DECLARE_PMID(kImplementationIDSpace, kStoryEditorPresentationImpl, kWMPrefix2 + 139)
//DECLARE_PMID(kImplementationIDSpace, kStoryEditorShortcutContextImpl, kWMPrefix2 + 140)


// GalleyTextAdornment impls: These may go away if we support choose to support
// IGalleyTextAdornment::DrawPriority() in the future
// 
//DECLARE_PMID(kImplementationIDSpace, kGalleyTextAdornmentBeforeServiceImpl, kWMPrefix2 + 150)
//DECLARE_PMID(kImplementationIDSpace, kGalleyTextAdornmentAfterServiceImpl, kWMPrefix2 + 151)


// <Action ID>
//---------------------------------------------------------------
//	Action IDs
//---------------------------------------------------------------
// DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator1MAID, kWMPrefix2 + 1)
// DECLARE_PMID(kActionIDSpace, kShowInfoColumnMenuMAID, kWMPrefix2 + 2)
// DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator2MAID, kWMPrefix2 + 3)
// DECLARE_PMID(kActionIDSpace, kGalleyViewMenuMAID, kWMPrefix2 + 4)
// DECLARE_PMID(kActionIDSpace, kToggleAccurateLineEndsMAID, kWMPrefix2 + 11)
// DECLARE_PMID(kActionIDSpace, kTempTestSpeedMAID, kWMPrefix2 + 12)
// 
// // gap
// 
// DECLARE_PMID(kActionIDSpace, kLayoutViewMenuMAID, kWMPrefix2 + 20)
// DECLARE_PMID(kActionIDSpace, kStoryEditorViewMenuMAID, kWMPrefix2 + 21)
// DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator3MAID, kWMPrefix2 + 22)
// DECLARE_PMID(kActionIDSpace, kExpandStoryMenuMAID, kWMPrefix2 + 23)
// DECLARE_PMID(kActionIDSpace, kExpandAllStoriesMenuMAID, kWMPrefix2 + 24)
// DECLARE_PMID(kActionIDSpace, kCollapseAllStoriesMenuMAID, kWMPrefix2 + 25)
// DECLARE_PMID(kActionIDSpace, kShowLineNumbersMenuMAID, kWMPrefix2 + 26)
// DECLARE_PMID(kActionIDSpace, kShowStylesMenuMAID, kWMPrefix2 + 29)
// DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator4MAID, kWMPrefix2 + 30)
// //gap
// DECLARE_PMID(kActionIDSpace, kShowParagraphsMenuMAID, kWMPrefix2 + 32)
// 
// DECLARE_PMID(kActionIDSpace, kGalleyDeleteWordActionID, kWMPrefix2 + 33)
// DECLARE_PMID(kActionIDSpace, kGalleyDeleteSentenceActionID, kWMPrefix2 + 34) 
// DECLARE_PMID(kActionIDSpace, kGalleyDeleteParagraphActionID, kWMPrefix2 + 35) 
// 
// DECLARE_PMID(kActionIDSpace, kGalleySelectPrevWordActionID, kWMPrefix2 + 37)
// DECLARE_PMID(kActionIDSpace, kGalleySelectNextWordActionID, kWMPrefix2 + 38)
// 
// DECLARE_PMID(kActionIDSpace, kGalleySelectCurrentParagraphActionID, kWMPrefix2 + 39)
// 
// DECLARE_PMID(kActionIDSpace, kGalleySelectNextSentenceActionID, kWMPrefix2 + 41)
// DECLARE_PMID(kActionIDSpace, kGalleySelectPreviousSentenceActionID, kWMPrefix2 + 42)
// 
// DECLARE_PMID(kActionIDSpace, kGalleyMoveToNextSentenceActionID, kWMPrefix2 + 43)
// DECLARE_PMID(kActionIDSpace, kGalleyMoveToPreviousSentenceActionID, kWMPrefix2 + 44)
// DECLARE_PMID(kActionIDSpace, kShowDepthRulerMenuMAID, kWMPrefix2 + 45)
// 
// //gap
// 
// DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator5MAID, kWMPrefix2 + 47)
// DECLARE_PMID(kActionIDSpace, kCollapseAllFootnotesMAID, kWMPrefix2 + 48)
// DECLARE_PMID(kActionIDSpace, kGalleyMoveToPreviousStoryActionID, kWMPrefix2 + 49)
// DECLARE_PMID(kActionIDSpace, kGalleyMoveToNextStoryActionID, kWMPrefix2 + 50)
// 
// DECLARE_PMID(kActionIDSpace, kGalleyMenuSeparator6MAID, kWMPrefix2 + 51)
// DECLARE_PMID(kActionIDSpace, kArrangeByRowsMAID, kWMPrefix2 + 52)
// DECLARE_PMID(kActionIDSpace, kArrangeByColumnsMAID, kWMPrefix2 + 53)
// 

// <Service id>
//---------------------------------------------------------------
//	Service id's
//---------------------------------------------------------------
//DECLARE_PMID(kServiceIDSpace, kCreateGalleyWidgetServiceID, kWMPrefix2 + 1)

// NOTE: kGalleyTextAdornmentBeforeService & kGalleyTextAdornmentAfterService
// may go away if we support choose to support IGalleyTextAdornment::DrawPriority()
// in the future
//DECLARE_PMID(kServiceIDSpace, kGalleyTextAdornmentBeforeService, kWMPrefix2 + 2)
//DECLARE_PMID(kServiceIDSpace, kGalleyTextAdornmentAfterService, kWMPrefix2 + 3)

//DECLARE_PMID(kServiceIDSpace, kOpenStoryEditorSignalServiceID, kWMPrefix2 + 4)

// <Widget id>
//---------------------------------------------------------------
//	Widget id's
//---------------------------------------------------------------
// DECLARE_PMID(kWidgetIDSpace,		kBevelWidgetID, 			kWMPrefix2 + 1)
// DECLARE_PMID(kWidgetIDSpace,		kMoabPageNavigateWidgetID, 	kWMPrefix2 + 2)
// DECLARE_PMID(kWidgetIDSpace,		kMoabPageNavigateEditBoxWidgetID, 	kWMPrefix2 + 3)
// DECLARE_PMID(kWidgetIDSpace,		kMoabFirstPageIconWidgetID, 	kWMPrefix2 + 4)
// DECLARE_PMID(kWidgetIDSpace,		kMoabLastPageIconWidgetID, 	kWMPrefix2 + 5)
// DECLARE_PMID(kWidgetIDSpace,		kMoabPageNumForwardIconWidgetID, 	kWMPrefix2 + 6)
// DECLARE_PMID(kWidgetIDSpace,		kMoabPageNumBackwardIconWidgetID, 	kWMPrefix2 + 7)
// DECLARE_PMID(kWidgetIDSpace,		kInfoColumnID, 	kWMPrefix2 + 9)
// DECLARE_PMID(kWidgetIDSpace,		kInfoColumnSplitterID, 	kWMPrefix2 + 10)
// DECLARE_PMID(kWidgetIDSpace,		kAreaRulerID, 	kWMPrefix2 + 11)

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kLayoutComposeAttachDetachInvalHandlerID, kWMPrefix2 + 1)

// <Messages>
//---------------------------------------------------------------
//	Messages
//---------------------------------------------------------------
// #define		kShowLineNumberMsg					kWMPrefix2 + 1
// #define		kHideLineNumberMsg					kWMPrefix2 + 2
// #define		kEnterRestoreModeMsg				kWMPrefix2 + 3
// #define		kExitRestoreModeMsg					kWMPrefix2 + 4
// 
// #define		kPreSwitchToGalleyOneWindowMsg		kWMPrefix2 + 5
// #define		kPostSwitchToGalleyOneWindowMsg		kWMPrefix2 + 6
// #define		kPreSwitchToLayoutOneWindowMsg		kWMPrefix2 + 7
// #define		kPostSwitchToLayoutOneWindowMsg		kWMPrefix2 + 8
// 
// #define		kPreSwitchToGalleyMsg		kWMPrefix2 + 9
// #define		kPostSwitchToGalleyMsg		kWMPrefix2 + 10
// #define		kPreSwitchToLayoutMsg		kWMPrefix2 + 11
// #define		kPostSwitchToLayoutMsg		kWMPrefix2 + 12
// 
// #define		kPostToggleALEILEMsg		kWMPrefix2 + 13
// #define		kPreToggleALEILEMsg			kWMPrefix2 + 14
// #define		kPostSwitchSelectionCompleteMsg		kWMPrefix2 + 15
#endif // __WritingModeID2__
