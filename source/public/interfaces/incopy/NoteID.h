//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/NoteID.h $
//  
//  Owner: Wai cheuk
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

#ifndef __NoteID__
#define __NoteID__

		// if this turns on, the sticky note feature will be disabled
#define NOTE_PALETTE_NOW

		// turn this on to see the note anchor flashes while active focus
		// is in the note palette.
//#define FLASH_NOTE_ANCHOR

		// turn this on to see persistent note palette - its content does
		// not change in the event of switching documents focus, which 
		// includes: close doc, click between doc, new doc, etc.
//#define KEEP_PALETTE_CONTENT_UPON_DOC_SWITCH

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define DEFAULTTEXTSIZE	12.0


#define kNotePrefix		RezLong(0xbb00)	 

// <PluginID>  
#define kNotePluginName 				"Note"


START_IDS()

DECLARE_PMID(kPlugInIDSpace, kNotePluginID, kNotePrefix + 1)

//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------
DECLARE_PMID(kClassIDSpace, kNoteTestMenuBoss, 					kNotePrefix + 1)
DECLARE_PMID(kClassIDSpace, kCreateNoteWindowCmdBoss, 			kNotePrefix + 10)
//gap
DECLARE_PMID(kClassIDSpace, kNoteStringRegisterBoss, 			kNotePrefix + 14)
DECLARE_PMID(kClassIDSpace, kNoteIconAdornmentBoss, 			kNotePrefix + 22)
DECLARE_PMID(kClassIDSpace, kNotePreInterceptorBoss, 			kNotePrefix + 25)
DECLARE_PMID(kClassIDSpace, kNoteMenuBoss, 						kNotePrefix + 26)
//gap
DECLARE_PMID(kClassIDSpace, kNoteToolBoss, 						kNotePrefix + 29)

DECLARE_PMID(kClassIDSpace, kNoteWindowWidgetBoss, 				kNotePrefix + 40)

DECLARE_PMID(kClassIDSpace, kNoteToolTrackerRegisterBoss, 		kNotePrefix + 43)
DECLARE_PMID(kClassIDSpace, kNoteToolTrackerBoss, 				kNotePrefix + 44)
DECLARE_PMID(kClassIDSpace, kNoteLayoutActionBoss, 				kNotePrefix + 47)
//DECLARE_PMID(kClassIDSpace, kCreateNoteCmdBoss, 				kNotePrefix + 49) // moved to InCopySharedID.h
DECLARE_PMID(kClassIDSpace, kDeleteNoteCmdBoss, 				kNotePrefix + 50)
DECLARE_PMID(kClassIDSpace, kNoteStartupShutdownBoss, 			kNotePrefix + 51)
DECLARE_PMID(kClassIDSpace, kCopyToNoteCmdBoss, 				kNotePrefix + 52)
DECLARE_PMID(kClassIDSpace, kConvertToNoteCmdBoss,				kNotePrefix + 53)
DECLARE_PMID(kClassIDSpace, kNoteColorCmdBoss, 					kNotePrefix + 59)
DECLARE_PMID(kClassIDSpace, kNoteSetSpreadCmdBoss, 				kNotePrefix + 67)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kNotePrefix + 68)
//gap

//DECLARE_PMID(kClassIDSpace, kShowNoteAnchorObserverBoss,		kNotePrefix + 70)
//DECLARE_PMID(kClassIDSpace, kShowNoteWindowObserverBoss,		kNotePrefix + 71)
DECLARE_PMID(kClassIDSpace, kNextNoteButtonObserverBoss,		kNotePrefix + 72)
DECLARE_PMID(kClassIDSpace, kPrevNoteButtonObserverBoss,		kNotePrefix + 73)
DECLARE_PMID(kClassIDSpace, kNoteCommandbarBoss,				kNotePrefix + 74)
DECLARE_PMID(kClassIDSpace, kNoteCmdBarTipsRegisterBoss,		kNotePrefix + 75)
DECLARE_PMID(kClassIDSpace, kNoteKitRegisterBoss,				kNotePrefix + 76)
   
// new note storage
//----- moved to InCopySharedID.h
//DECLARE_PMID(kClassIDSpace, kNoteDataBoss, 						kNotePrefix + 77)
DECLARE_PMID(kClassIDSpace, kApplyNoteContentCmdBoss, 			kNotePrefix + 78)
//DECLARE_PMID(kClassIDSpace, kDeleteNoteDataCmdBoss, 			kNotePrefix + 79) // moved to InCopySharedID.h
DECLARE_PMID(kClassIDSpace, kPostDeleteNoteDataCmdBoss, 		kNotePrefix + 80)
//DECLARE_PMID(kClassIDSpace, kAddNoteDataCmdBoss, 				kNotePrefix + 81) // moved to InCopySharedID.h
// gap DECLARE_PMID(kClassIDSpace, kAddStoryThreadCmdBoss,			kNotePrefix + 82)
//DECLARE_PMID(kClassIDSpace, kCopyNoteDataCmdBoss,				kNotePrefix + 83) // moved to InCopySharedID.h
//DECLARE_PMID(kClassIDSpace, kSetOwnedUIDCmdBoss,				kNotePrefix + 84) // moved to InCopySharedID.h

// for note writing widget
DECLARE_PMID(kClassIDSpace, kNewNoteWritingPanelCmdBoss,		kNotePrefix + 86)
DECLARE_PMID(kClassIDSpace, kNoteWindowWritingWidgetBoss,		kNotePrefix + 87)
DECLARE_PMID(kClassIDSpace, kNoteTextTrackerBoss,				kNotePrefix + 88)
DECLARE_PMID(kClassIDSpace, kNoteTextTrackerRegisterBoss,		kNotePrefix + 89)

//DECLARE_PMID(kClassIDSpace, kNoteTextISuiteBoss,				kNotePrefix + 90)
DECLARE_PMID(kClassIDSpace, kNoteTextSuiteBoss,					kNotePrefix + 91)

DECLARE_PMID(kClassIDSpace, kNoteTextSelectionBoss,				kNotePrefix + 92)


DECLARE_PMID(kClassIDSpace, kNoteTextSelectionServiceBoss,		kNotePrefix + 93)
DECLARE_PMID(kClassIDSpace, kNoteWritingParentBoss,				kNotePrefix + 94)
//DECLARE_PMID(kClassIDSpace, kCollapseStateCmdBoss,				kNotePrefix + 96)	// moved to InCopySharedID.h
DECLARE_PMID(kClassIDSpace, kNoteOwnedItemIBeamDataBoss,		kNotePrefix + 97)
//----- Moved to InCopyShared
//DECLARE_PMID(kClassIDSpace, kNoteDataTextModelMementoBoss,		kNotePrefix + 98)
DECLARE_PMID(kClassIDSpace, kInlineNoteTrackerBoss, 			kNotePrefix + 100)
//DECLARE_PMID(kClassIDSpace, kNoteScriptProviderBoss, 			kNotePrefix + 101)     // moved to InCOpySharedID.h

//gap
DECLARE_PMID(kClassIDSpace, kGoToNextNoteButtonBoss,			kNotePrefix + 103)
DECLARE_PMID(kClassIDSpace, kGoToPrevNoteButtonBoss,			kNotePrefix + 104)
DECLARE_PMID(kClassIDSpace, kDeleteNoteButtonBoss,				kNotePrefix + 105)
DECLARE_PMID(kClassIDSpace, kNewNoteButtonBoss,					kNotePrefix + 106)
DECLARE_PMID(kClassIDSpace, kBringAnchorToPaletteButtonBoss,	kNotePrefix + 107)
DECLARE_PMID(kClassIDSpace, kUserIconButtonBoss, 				kNotePrefix + 108)
DECLARE_PMID(kClassIDSpace, kNoteAnchorIdleTaskBoss, 			kNotePrefix + 109)
DECLARE_PMID(kClassIDSpace, kShowNoteInfoBoss,					kNotePrefix + 110)
DECLARE_PMID(kClassIDSpace, kHideNoteInfoBoss,					kNotePrefix + 111)
//DECLARE_PMID(kClassIDSpace, kNoteModifiedTimeCmdBoss,			kNotePrefix + 112)	// moved to InCopySharedID.h

//DECLARE_PMID(kClassIDSpace, kNoteCopyStoryCmdBoss,				kNotePrefix + 113)	// moved to InCopySharedID.h
DECLARE_PMID(kClassIDSpace, kNoteMoveStoryCmdBoss,				kNotePrefix + 114)
DECLARE_PMID(kClassIDSpace, kNoteWritingScrollSyncBoss,			kNotePrefix + 115)
DECLARE_PMID(kClassIDSpace, kDisplayNoteButtonBoss,				kNotePrefix + 116)
//gap
//DECLARE_PMID(kClassIDSpace, kSelectNoteTextCmdBoss,				kNotePrefix + 118)
//gap
//DECLARE_PMID(kClassIDSpace, kConvertNoteToTextCmdBoss,			kNotePrefix + 120)	// moved to InCopySharedID.h
//DECLARE_PMID(kClassIDSpace, kConvertNoteHelperCmdImplBoss,		kNotePrefix + 121)	// moved to InCopySharedID.h
DECLARE_PMID(kClassIDSpace, kNoteConversionProviderBoss, 		kNotePrefix + 122)
//gap

DECLARE_PMID(kClassIDSpace, kOversetTextInfoBoss,				kNotePrefix + 124)
DECLARE_PMID(kClassIDSpace, kPageNumberInfoBoss,				kNotePrefix + 125)
//DECLARE_PMID(kClassIDSpace, kDeleteNoteHelperCmdBoss,			kNotePrefix + 126)	// moved to InCopySharedID.h

//DECLARE_PMID(kClassIDSpace, kSplitNoteCmdBoss,					kNotePrefix + 127)	// moved to InCopySharedID.h
//DECLARE_PMID(kClassIDSpace, kSetHideNoteStateCmdBoss,					kNotePrefix + 128) // mvoe to InCOpyShared

//PDF review notes
/*
DECLARE_PMID(kClassIDSpace, kNoteEndMarkerAdornmentBoss,			kNotePrefix + 130)
DECLARE_PMID(kClassIDSpace, kTextNotesOpenDocResponderBoss,			kNotePrefix + 131)
*/

//---------------------------------------------------------------
//	ImplementationIDs
//---------------------------------------------------------------

// Gap 1
DECLARE_PMID(kImplementationIDSpace, kNoteTrackerRegisterImpl,			kNotePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kNoteTrackerImpl,					kNotePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCreateNoteWindowCmdImpl,			kNotePrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kAddNoteStorageCmdImpl,			kNotePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kNoteIconAdornmentImpl,			kNotePrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kNoteEditBoxAdornmentImpl,			kNotePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kNotePreServiceImpl,				kNotePrefix + 21)		// on kDocBoss
DECLARE_PMID(kImplementationIDSpace, kNotePreInterceptorImpl,			kNotePrefix + 22)		// on kDocBoss
DECLARE_PMID(kImplementationIDSpace, kNoteMenuImpl,						kNotePrefix + 23)		
DECLARE_PMID(kImplementationIDSpace, kNoteToolImpl,						kNotePrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kNoteEditBoxViewImpl,				kNotePrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kNoteToolTrackerImpl,				kNotePrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kNoteToolTrackerRegisterImpl,		kNotePrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kNoteToolCursorProviderImpl,		kNotePrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kNoteEditViewObserverImpl,			kNotePrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kNoteLayoutObserverImpl,			kNotePrefix + 41)		// on kNoteLayoutWidgetBoss
DECLARE_PMID(kImplementationIDSpace, kNoteLayoutActionImpl,				kNotePrefix + 42)
//DECLARE_PMID(kImplementationIDSpace, kCreateNoteCmdImpl,				kNotePrefix + 46)	// moved to InCopySharedID.h
DECLARE_PMID(kImplementationIDSpace, kDeleteNoteCmdImpl,				kNotePrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kNoteStartupShutdownImpl,			kNotePrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kNoteAppObserverImpl,				kNotePrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kCopyToNoteCmdImpl,				kNotePrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kConvertToNoteCmdImpl,				kNotePrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kNoteLayoutTipImpl,				kNotePrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kNoteGalleyTipImpl,				kNotePrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kNoteSettingsImpl_Obsolete,		kNotePrefix + 54) // move to InCOpyShared 6/30/04 cchen
DECLARE_PMID(kImplementationIDSpace, kCmdHistoryObserverImpl,			kNotePrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kSnapToAnchorTipsImpl,				kNotePrefix + 61)
//DECLARE_PMID(kImplementationIDSpace, kEditNoteAttributeCmdDataImpl,		kNotePrefix + 64)	// moved to InCopySharedID.h
DECLARE_PMID(kImplementationIDSpace, kNoteColorCmdImpl,					kNotePrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kNoteSelectionObserverImpl,		kNotePrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kNoteEditBoxTextControlDataImpl,	kNotePrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kCloseNoteCmdDataImpl,				kNotePrefix + 76)
//DECLARE_PMID(kImplementationIDSpace, kCopyToNewNoteCmdDataImpl,			kNotePrefix + 77)	// moved to InCopySharedID.h
//DECLARE_PMID(kImplementationIDSpace, kCreateNoteCmdDataImpl,			kNotePrefix + 81)	// moved to InCopySharedID.h
DECLARE_PMID(kImplementationIDSpace, kNoteSetSpreadCmdImpl,				kNotePrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kNoteTextObjectParentImpl,			kNotePrefix + 83)

// new note storage
//----- Moved to InCopySharedID.h
//DECLARE_PMID(kImplementationIDSpace, kNoteDataImpl,					kNotePrefix + 88)
//DECLARE_PMID(kImplementationIDSpace, kNoteOwnedItemImpl,				kNotePrefix + 89)
//DECLARE_PMID(kImplementationIDSpace, kNoteDataScrapImpl,				kNotePrefix + 90)

//DECLARE_PMID(kImplementationIDSpace, kDeleteNoteDataCmdImpl,			kNotePrefix + 92)	// moved to InCopySharedID.h
//----- Moved to InCopySharedID.h
//DECLARE_PMID(kImplementationIDSpace, kNoteDataStoryThreadImpl,		kNotePrefix + 93)
//DECLARE_PMID(kImplementationIDSpace, kNoteDataStoryThreadDictImpl,	kNotePrefix + 94)
//DECLARE_PMID(kImplementationIDSpace, kNoteDataParcelListImpl,			kNotePrefix + 95)
//DECLARE_PMID(kImplementationIDSpace, kNoteDataTextPLDataImpl,			kNotePrefix + 96)
//DECLARE_PMID(kImplementationIDSpace, kAddNoteDataCmdImpl,				kNotePrefix + 97)	// moved to InCopySharedID.h
//DECLARE_PMID(kImplementationIDSpace, kAddNoteDataCmdDataImpl,			kNotePrefix + 98)	// moved to InCopySharedID.h
DECLARE_PMID(kImplementationIDSpace, kAddStoryThreadCmdImpl,			kNotePrefix + 99)
//DECLARE_PMID(kImplementationIDSpace, kCopyNoteDataCmdImpl,				kNotePrefix + 100)	// moved to InCopySharedID.h
//DECLARE_PMID(kImplementationIDSpace, kCopyNoteDataCmdDataImpl,			kNotePrefix + 101)	// moved to InCopySharedID.h
//DECLARE_PMID(kImplementationIDSpace, kSetOwnedUIDCmdImpl,				kNotePrefix + 102)	// moved to InCopySharedID.h

// for note writing widget
DECLARE_PMID(kImplementationIDSpace, kNewNoteWritingPanelCmdImpl,		kNotePrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kNoteWritingModeControlViewImpl,	kNotePrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kNoteWritingEventHandlerImpl,		kNotePrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kNoteTextTrackerImpl,				kNotePrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kNoteTextTrackerRegisterImpl,		kNotePrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kNoteTextCaretImpl,				kNotePrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kNoteTextCaretThreadImpl,			kNotePrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kNoteWritingDisplayDataImpl,		kNotePrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kNoteWritingScrollDataImpl,		kNotePrefix + 112)

// selection monster
DECLARE_PMID(kImplementationIDSpace, kConcreteNoteTextSelectionImpl,	kNotePrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kNoteTextSelectionSuiteImpl,		kNotePrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kNoteTextSelectionHiliterImpl,		kNotePrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kNoteTextUniformTargetFactoryImpl,	kNotePrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kNoteHiliteObserverImpl,			kNotePrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kNoteShortcutContextImpl,			kNotePrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kNoteWritingParentImpl,			kNotePrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kNoteWritingObserverImpl,			kNotePrefix + 120)

// for note writing widget
DECLARE_PMID(kImplementationIDSpace, kNoteStoryThreadDataImpl,			kNotePrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kNoteStoryRefDataImpl,				kNotePrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kNoteTextNavigationSuiteImpl,		kNotePrefix + 123)
//DECLARE_PMID(kImplementationIDSpace, kCollapseStateCmdImpl,				kNotePrefix + 125)	// moved to InCopySharedID.h
DECLARE_PMID(kImplementationIDSpace, kNoteLayoutCustomIBeamDataImpl,	kNotePrefix + 128)
//DECLARE_PMID(kImplementationIDSpace, kNoteGalleyCustomIBeamDataImpl,	kNotePrefix + 129) // Renamed GalleyCustomIBeamDataImpl and moved to Galley plug-in part of footnote support
DECLARE_PMID(kImplementationIDSpace, kNoteUtilsImpl,					kNotePrefix + 130)
//----- Moved to InCopySharedID.h
//DECLARE_PMID(kImplementationIDSpace, kNoteDataTextModelMementoImpl,	kNotePrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kInlineNoteTrackerImpl, 			kNotePrefix + 133)
//DECLARE_PMID(kImplementationIDSpace, kNoteScriptProviderImpl, 			kNotePrefix + 134)  // moved to InCOpyShared 6/28/04 cchen
//gap
DECLARE_PMID(kImplementationIDSpace, kNoteLayoutIBeamDataImpl, 			kNotePrefix + 138)
//gap

DECLARE_PMID(kImplementationIDSpace, kGoToNextNoteButtonObserverImpl, 	kNotePrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kGoToPrevNoteButtonObserverImpl, 	kNotePrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kDeleteNoteButtonObserverImpl, 	kNotePrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kNewNoteButtonObserverImpl, 		kNotePrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kBringAnchorButtonObserverImpl, 	kNotePrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kNotePaletteObserverImpl, 			kNotePrefix + 145)

DECLARE_PMID(kImplementationIDSpace, kNoteUIUtilsImpl, 					kNotePrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kNoteDataUtilsImpl, 				kNotePrefix + 147)

DECLARE_PMID(kImplementationIDSpace, kUserIconControlViewImpl, 			kNotePrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kNoteAnchorIdleTaskImpl, 			kNotePrefix + 149)
//DECLARE_PMID(kImplementationIDSpace, kHideShowNoteInfoObserverImpl,	kNotePrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kShowNoteInfoObserverImpl,			kNotePrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kHideNoteInfoObserverImpl, 		kNotePrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kUserIconObserverImpl,				kNotePrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kNotePaletteDataImpl,				kNotePrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kNotePanelObserverImpl,			kNotePrefix + 154)
//DECLARE_PMID(kImplementationIDSpace, kNoteModifiedTimeCmdImpl,			kNotePrefix + 155)	// moved to InCopySharedID.h
DECLARE_PMID(kImplementationIDSpace, kNotePaletteUtilsImpl,				kNotePrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kNoteWritingScrapSuiteImpl, 		kNotePrefix + 157)
//DECLARE_PMID(kImplementationIDSpace, kNoteCopyStoryCmdImpl, 			kNotePrefix + 158)	// moved to InCopySharedID.h
DECLARE_PMID(kImplementationIDSpace, kNoteMoveStoryCmdImpl, 			kNotePrefix + 159)

// dummy parcel list composer, no-op
//DECLARE_PMID(kImplementationIDSpace, kNoteDataTextPLComposerImpl, 	kNotePrefix + 160)

DECLARE_PMID(kImplementationIDSpace, kDisplayNoteButtonObserverImpl, 	kNotePrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kNoteWritingCursorProviderImpl, 	kNotePrefix + 162)
//DECLARE_PMID(kImplementationIDSpace, kSelectNoteTextCmdImpl, 			kNotePrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kNoteTextScriptProviderImpl, 		kNotePrefix + 164)
//gap
//DECLARE_PMID(kImplementationIDSpace, kConvertNoteToTextCmdImpl, 		kNotePrefix + 166)	// moved to InCopySharedID.h
//DECLARE_PMID(kImplementationIDSpace, kConvertNoteHelperCmdImpl, 		kNotePrefix + 167)	// moved to InCopySharedID.h
// gap
DECLARE_PMID(kImplementationIDSpace, kNoteViewSelectionImpl, 			kNotePrefix + 169)

DECLARE_PMID(kImplementationIDSpace, kOversetTextObserverImpl, 			kNotePrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kPageNumberObserverImpl, 			kNotePrefix + 171)

// new selection architecture
DECLARE_PMID(kImplementationIDSpace, kNoteTextNavigationSuiteASBImpl, 	kNotePrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kNoteTextSelectionSuiteASBImpl, 	kNotePrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kMakeNewNoteSelectionSuiteASBImpl, kNotePrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kMakeNewNoteSelectionSuiteImpl, 	kNotePrefix + 175)

//DECLARE_PMID(kImplementationIDSpace, kDeleteNoteHelperCmdImpl, 			kNotePrefix + 176)	// moved to InCopySharedID.h
DECLARE_PMID(kImplementationIDSpace, kNoteDrawUtilsImpl, 				kNotePrefix + 177)

//DECLARE_PMID(kImplementationIDSpace, kSplitNoteCmdImpl, 				kNotePrefix + 178)	// moved to InCopySharedID.h
//DECLARE_PMID(kImplementationIDSpace, kSetHideNoteStateCmdImpl, 			kNotePrefix + 179) // move to InCOpyShared

DECLARE_PMID(kImplementationIDSpace, kNoteTextSelectionFactoryImpl,	kNotePrefix + 180)

//PDF review notes
/*
DECLARE_PMID(kImplementationIDSpace, kNoteEndMarkerAdornmentImpl,		kNotePrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kTextNotesListImpl,				kNotePrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kTextNotesOpenDocResponderImpl,	kNotePrefix + 183)
*/

DECLARE_PMID(kImplementationIDSpace, kNoteComposeTaskImpl,	kNotePrefix + 184)

//---------------------------------------------------------------
//	Interface IDs
//---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRNOTEDATA, 				kNotePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTESHOWHIDEDATA,				kNotePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEDOCOBSERVER,				kNotePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTELAYOUTOBSERVER,			kNotePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEDOCUMENTOBSERVER,			kNotePrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_INOTESETTINGS,					kNotePrefix + 7)  // move to InCopyShared 6/30/04 cchen
DECLARE_PMID(kInterfaceIDSpace, IID_IEDITNOTEATTRIBUTECMDDATA,		kNotePrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTESELECTIONOBSERVER,			kNotePrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOSENOTECMDDATA,				kNotePrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEOBSERVER,					kNotePrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYTONEWNOTECMDDATA,			kNotePrefix + 14)	// unused
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATENOTECMDDATA,				kNotePrefix + 15)

// new note storage
//----- moved to InCopySharedID.h
//DECLARE_PMID(kInterfaceIDSpace, IID_INOTEDATA,						kNotePrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDNOTEDATACMDDATA,			kNotePrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYNOTEDATACMDDATA,			kNotePrefix + 18)

// selection monster
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEWINDOWBOOL,					kNotePrefix + 20)

// $$$$ NEED TO FIND A RIGHT PLACE TO PUT THIS
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEUTILS, kNotePrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEUIUTILS, kNotePrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEDATAUTILS, kNotePrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEPALETTEDATA, kNotePrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEPALETTEUTILS, kNotePrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYDATA, kNotePrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IHITINDEX, kNotePrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWCOLORINDEX, kNotePrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ISRCSTARTINDEX, kNotePrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ISRCENDINDEX, kNotePrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ITARGETSTARTINDEX, kNotePrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ITARGETENDINDEX, kNotePrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTECOPYSTORYCMD, kNotePrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEMOVESTORYCMD, kNotePrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOADNOTESTATE, kNotePrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETTINGNOTE, kNotePrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_REMOVESTORYBOOLDATA, kNotePrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTARTFOCUSINTDATA, kNotePrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IENDFOCUSINTDATA, kNotePrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTNOTETOTEXTCMD, kNotePrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTNOTEHELPERCMD, kNotePrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IFOCUSINTEXTBOOLDATA, kNotePrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAKENEWNOTESELECTIONSUITE, kNotePrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_ICTEXTNAVIGATIONSUITE1, kNotePrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICTEXTSELECTION_SUITE1, kNotePrefix + 46)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDELETENOTEHELPERCMD, kNotePrefix + 47)	// Moved to InCopySharedID.h
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEDRAWUTILS, kNotePrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLITNOTECMD, kNotePrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_NOTEMODIFIED_DOCUMENT, kNotePrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_COLLAPSESTATE_DOCUMENT, kNotePrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IDAMAGEALLNOTE, kNotePrefix + 52)

//PDF review notes
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTNOTESLIST, kNotePrefix + 60)

//---------------------------------------------------------------
//	Action IDs
//---------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kNoteSubMenuMAID, 						kNotePrefix + 1)
DECLARE_PMID(kActionIDSpace, kNewNoteMenuMAID, 						kNotePrefix + 2)
DECLARE_PMID(kActionIDSpace, kOpenNoteMenuMAID, 					kNotePrefix + 3)
DECLARE_PMID(kActionIDSpace, kDeleteNoteMenuMAID, 					kNotePrefix + 4)
DECLARE_PMID(kActionIDSpace, kNoteSeparator1MenuMAID,	 			kNotePrefix + 5)
DECLARE_PMID(kActionIDSpace, kNoteToolActionID, 					kNotePrefix + 6)
DECLARE_PMID(kActionIDSpace, kCopyTextToNewNoteMAID,				kNotePrefix + 7)
DECLARE_PMID(kActionIDSpace, kConvertToNoteMenuMAID,				kNotePrefix + 8)
DECLARE_PMID(kActionIDSpace, kCopyNoteToTextMenuMAID,				kNotePrefix + 9)
DECLARE_PMID(kActionIDSpace, kConvertToTextMenuMAID,				kNotePrefix + 10)
DECLARE_PMID(kActionIDSpace, kNoteSeparator2MenuMAID,				kNotePrefix + 11)
DECLARE_PMID(kActionIDSpace, kNextNoteMenuMAID, 					kNotePrefix + 12)
DECLARE_PMID(kActionIDSpace, kPrevNoteMenuMAID, 					kNotePrefix + 13)
DECLARE_PMID(kActionIDSpace, kBringNoteHomeMenuMAID, 				kNotePrefix + 14)
DECLARE_PMID(kActionIDSpace, kNoteSeparator3MenuMAID,			 	kNotePrefix + 15)
DECLARE_PMID(kActionIDSpace, kNoteSeparator4MenuMAID,				kNotePrefix + 16)
DECLARE_PMID(kActionIDSpace, kNotesPanelActionID,					kNotePrefix + 17)
DECLARE_PMID(kActionIDSpace, kNoteSeparator5MenuMAID,		 		kNotePrefix + 18)
DECLARE_PMID(kActionIDSpace, kBringAllNotesHomeMenuMAID, 			kNotePrefix + 19)
DECLARE_PMID(kActionIDSpace, kNotesModeMAID, 						kNotePrefix + 20)
DECLARE_PMID(kActionIDSpace, kExpandCollapseAllNotesMAID,			kNotePrefix + 21)
DECLARE_PMID(kActionIDSpace, kCollapseNoteMAID, 					kNotePrefix + 22)
DECLARE_PMID(kActionIDSpace, kNoteSeparator6MenuMAID, 				kNotePrefix + 23)
DECLARE_PMID(kActionIDSpace, kRemoveAllNotesMAID, 					kNotePrefix + 24)
DECLARE_PMID(kActionIDSpace, kToggleNoteMenuMAID, 					kNotePrefix + 25)
DECLARE_PMID(kActionIDSpace, kWordToNoteMAID, 						kNotePrefix + 26)
DECLARE_PMID(kActionIDSpace, kLineToNoteMAID, 						kNotePrefix + 27)
DECLARE_PMID(kActionIDSpace, kParaToNoteMAID, 						kNotePrefix + 28)
DECLARE_PMID(kActionIDSpace, kStoryToNoteMAID, 						kNotePrefix + 29)
DECLARE_PMID(kActionIDSpace, kNoteToTextMAID, 						kNotePrefix + 30)
DECLARE_PMID(kActionIDSpace, kNotePaletteActionID, 					kNotePrefix + 31)
//gap
DECLARE_PMID(kActionIDSpace, kNotePaletteSep1MAID, 					kNotePrefix + 34)
DECLARE_PMID(kActionIDSpace, kShowAnchorLocationMAID, 				kNotePrefix + 35)
DECLARE_PMID(kActionIDSpace, kPaletteShowNoteInfoMAID, 				kNotePrefix + 36)
DECLARE_PMID(kActionIDSpace, kNotePaletteSep2MAID, 					kNotePrefix + 37)
DECLARE_PMID(kActionIDSpace, kPaletteScrollToNoteAnchorMAID,	 	kNotePrefix + 38)
//DECLARE_PMID(kActionIDSpace, kShowNotesMenuMAID,	 				kNotePrefix + 39)
DECLARE_PMID(kActionIDSpace, kShowNotesMenuSeparatorMAID,			kNotePrefix + 40)
DECLARE_PMID(kActionIDSpace, kNotePaletteSep3MAID,					kNotePrefix + 41)
//gap
DECLARE_PMID(kActionIDSpace, kToggleNoteToolKBSCActionID,			kNotePrefix + 45)
DECLARE_PMID(kActionIDSpace, kNoteContextSeparatorMAID,				kNotePrefix + 46)
DECLARE_PMID(kActionIDSpace, kSplitNoteMenuMAID,					kNotePrefix + 47)
//gap
DECLARE_PMID(kActionIDSpace, kNotePaletteSep4MAID,					kNotePrefix + 50)
DECLARE_PMID(kActionIDSpace, kNotePaletteSep5MAID,					kNotePrefix + 51)
DECLARE_PMID(kActionIDSpace, kNotePaletteSep6MAID,					kNotePrefix + 52)
DECLARE_PMID(kActionIDSpace, kNotePaletteSep7MAID,					kNotePrefix + 53)
DECLARE_PMID(kActionIDSpace, kRemoveStoryNotesMAID, 				kNotePrefix + 54)

//---------------------------------------------------------------
//	Widget IDs
//---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kNoteToolWidgetID, 				kNotePrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kMoabNoteEditBoxPaletteWidgetID, 	kNotePrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kMoabNoteParentWidgetID, 			kNotePrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kMoabNoteEditBoxWidgetID, 			kNotePrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kNoteScrollBarWidgetID, 			kNotePrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kNoteCommandbarPanelWidgetID,		kNotePrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kNoteCommandbarHBarViewWidgetID,	kNotePrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kNoteCommandbarTablessViewWidgetID,kNotePrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kShowNoteControlSetWidgetID,		kNotePrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kNavNoteControlSetWidgetID,		kNotePrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kNoteCommandbarVBarViewWidgetID,	kNotePrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kNotesButtonWidgetID,				kNotePrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kCloseNotesButtonWidgetID,			kNotePrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kNewNoteButtonWidgetID,			kNotePrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kDeleteNoteButtonWidgetID,			kNotePrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kUserNameLabelWidgetID,			kNotePrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kUserNameWidgetID,					kNotePrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kOriginalCreateDateLabelWidgetID,	kNotePrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kOriginalCreateDateWidgetID,		kNotePrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kLastModifiedCreateDateLabelWidgetID,	kNotePrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kLastModifiedCreateDateWidgetID,	kNotePrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kWorkingStoryLabelWidgetID,		kNotePrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kWorkingStoryWidgetID,				kNotePrefix + 25) 
DECLARE_PMID(kWidgetIDSpace, kAnchorPageNumberLabelWidgetID,	kNotePrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kAnchorPageNumberWidgetID,			kNotePrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kNoteOrderLabelWidgetID,			kNotePrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kNoteOrderWidget1ID,				kNotePrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kNoteOrderSeparatorWidgetID,		kNotePrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kNoteOrderWidget2ID,				kNotePrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kCharCountLabelWidgetID,			kNotePrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kCharCountWidgetID,				kNotePrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kWordCountLabelWidgetID,			kNotePrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kWordCountWidgetID,				kNotePrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kScrollToNoteAnchorWidgetID,		kNotePrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kGoNextNoteButtonWidgetID,			kNotePrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kGoPrevNoteButtonWidgetID,			kNotePrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kNoteWritingParentWidgetID,		kNotePrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kUserIconWidgetID,					kNotePrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kShowNoteInfoWidgetID,				kNotePrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kHideNoteInfoWidgetID,				kNotePrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kNoteWritingScrollBarWidgetID,		kNotePrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kDisplayNoteWidgetID,				kNotePrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kOversetTextWidgetID,				kNotePrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kNoteWritingBorderWidgetID, 		kNotePrefix + 46)

//---------------------------------------------------------------
//	Message IDs
//---------------------------------------------------------------
DECLARE_PMID(kMessageIDSpace, kShowNotesMsg, 					kNotePrefix + 1)
DECLARE_PMID(kMessageIDSpace, kHideNotesMsg, 					kNotePrefix + 2)
DECLARE_PMID(kMessageIDSpace, kAnchorNumChangeMsg, 				kNotePrefix + 5)
DECLARE_PMID(kMessageIDSpace, kActivateNoteMsg, 				kNotePrefix + 6)
DECLARE_PMID(kMessageIDSpace, kPreConvertNoteToTextMsg, 		kNotePrefix + 7)
DECLARE_PMID(kMessageIDSpace, kPostConvertNoteToTextMsg, 		kNotePrefix + 8)
DECLARE_PMID(kMessageIDSpace, kConvertNoteToTextMsg, 			kNotePrefix + 9)
DECLARE_PMID(kMessageIDSpace, kConvertNoteHelperMsg, 			kNotePrefix + 10)
DECLARE_PMID(kMessageIDSpace, kConvertNoteLosesStructureMsg, 	kNotePrefix + 11)
DECLARE_PMID(kMessageIDSpace, kNoteRemovedMsg, 					kNotePrefix + 12)
DECLARE_PMID(kMessageIDSpace, kMoveNoteToTextMsg, 				kNotePrefix + 13)
DECLARE_PMID(kMessageIDSpace, kSetNoteToPaletteMsg, 			kNotePrefix + 14)
DECLARE_PMID(kMessageIDSpace, kResetNoteToPaletteMsg, 			kNotePrefix + 15)
DECLARE_PMID(kMessageIDSpace, kDeleteNoteHelperMsg, 			kNotePrefix + 16)
DECLARE_PMID(kMessageIDSpace, kPreSplitNoteMsg, 				kNotePrefix + 17)
DECLARE_PMID(kMessageIDSpace, kPostSplitNoteMsg, 				kNotePrefix + 18)
DECLARE_PMID(kMessageIDSpace, kSplitNoteMsg, 					kNotePrefix + 19)
DECLARE_PMID(kMessageIDSpace, kRemoveNotesInCollapsedStoryMsg, 	kNotePrefix + 20)
DECLARE_PMID(kMessageIDSpace, kConvertNoteLosesRubyMsg, 		kNotePrefix + 21)

//////////////////////////////////////////////////////////////////////////////
//Script Element IDs
//////////////////////////////////////////////////////////////////////////////

//Suites
//DECLARE_PMID(kScriptInfoIDSpace, kYourNewSuiteScriptElement,						kNotePrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kNoteObjectScriptElement,							kNotePrefix + 40)
//DECLARE_PMID(kScriptInfoIDSpace, kYourNewObjectScriptElement,						kNotePrefix + 41)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kConvertNoteToTextMethodScriptElement,				kNotePrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kConvertTextToNoteMethodScriptElement,				kNotePrefix + 81)
//DECLARE_PMID(kScriptInfoIDSpace, kYourNewMethodScriptElement,						kNotePrefix + 82)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kNoteCollapsedPropertyScriptElement,				kNotePrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kNoteCreationDatePropertyScriptElement,			kNotePrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kNoteModificationDatePropertyScriptElement,		kNotePrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kNoteUserNamePropertyScriptElement,				kNotePrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kNoteTextFramePropertyScriptElement,				kNotePrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kNoteStoryOffsetPropertyScriptElement,				kNotePrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kCreateNoteMethodScriptElement,						kNotePrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kShowHideNotesPropertyScriptElement,				kNotePrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kMoveNoteMethodScriptElement,						kNotePrefix + 148)

//Enums
//DECLARE_PMID(kScriptInfoIDSpace, kYourNewEnumScriptElement,						kNotePrefix + 220)

END_IDS()


//GUIDS
// {8D79F198-0A85-43c6-A404-1F9CDCA33B27}
#define kNote_CLSID { 0x8d79f198, 0xa85, 0x43c6, { 0xa4, 0x4, 0x1f, 0x9c, 0xdc, 0xa3, 0x3b, 0x27 } }
// {BB06AB0C-EC55-4ee0-BBF9-555E878CDDA0}
#define kNotes_CLSID { 0xbb06ab0c, 0xec55, 0x4ee0, { 0xbb, 0xf9, 0x55, 0x5e, 0x87, 0x8c, 0xdd, 0xa0 } }

#endif	// kMaobNotePrefix

