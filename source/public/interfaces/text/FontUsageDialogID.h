//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/FontUsageDialogID.h $
//  
//  Owner: lance bushore
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
//  Contains IDs used by the FontUsage, appinfo dialog, doc info dialog.
//  
//========================================================================================

#ifndef __FontUsageDialogID__
#define __FontUsageDialogID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kFontUsagePrefix	RezLong(0xaf00)

// <Start IDC>
// PluginID
#define kFontUsageDialogPluginName 				"Font Usage Dialog"
DECLARE_PMID(kPlugInIDSpace, kFontUsageDialogPluginID, kFontUsagePrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kFontUsageMenuBoss, kFontUsagePrefix + 1)
DECLARE_PMID(kClassIDSpace, kFontUsageDialogBoss, kFontUsagePrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kFindFontButtonBoss, kFontUsagePrefix + 4)
DECLARE_PMID(kClassIDSpace, kReplaceFontButtonBoss, kFontUsagePrefix + 5)
DECLARE_PMID(kClassIDSpace, kReplaceFontComboBoss, kFontUsagePrefix + 6)
DECLARE_PMID(kClassIDSpace, kSetOtherFindChangeOptionCmdBoss, kFontUsagePrefix + 7)
DECLARE_PMID(kClassIDSpace, kReplaceAllFontButtonBoss, kFontUsagePrefix + 8)
DECLARE_PMID(kClassIDSpace, kSyncFontCheckBoxWidgetBoss, kFontUsagePrefix + 9)
DECLARE_PMID(kClassIDSpace, kFontUsageNodeWidgetBoss, kFontUsagePrefix + 10)	

// ---- Moved from Font Manager plug-in
DECLARE_PMID(kClassIDSpace, kMissingFontsDialogBoss, kFontUsagePrefix + 11)
DECLARE_PMID(kClassIDSpace, kOpenFindFontsDialogCmdBoss, kFontUsagePrefix + 12)
DECLARE_PMID(kClassIDSpace, kOpenMapFontsCmdBoss, kFontUsagePrefix + 13)
// ---- end move.
DECLARE_PMID(kClassIDSpace, kMissingFontNodeWidgetBoss, kFontUsagePrefix + 14)
//gap
DECLARE_PMID(kClassIDSpace, kMissingFontListBoxWidgetBoss, kFontUsagePrefix + 16)
DECLARE_PMID(kClassIDSpace, kSyncFontsButtonBoss, kFontUsagePrefix + 17)
DECLARE_PMID(kClassIDSpace, kPlainBackgroundCheckBoxBoss, kFontUsagePrefix + 18)
// gap
DECLARE_PMID(kClassIDSpace, kMissingFontStaticMultiLineTextWidgetBoss, kFontUsagePrefix + 20)
DECLARE_PMID(kClassIDSpace, kGoToTypekitButtonBoss, kFontUsagePrefix + 21)
DECLARE_PMID(kClassIDSpace, kEVEIconSuiteWidgetWithToolTipBoss, kFontUsagePrefix + 22)
DECLARE_PMID(kClassIDSpace, kEVESpinningIconWidgetWithToolTipBoss, kFontUsagePrefix + 23)
DECLARE_PMID(kClassIDSpace, kPlainBackgroundGenericPanelWidgetBoss, kFontUsagePrefix + 24)
DECLARE_PMID(kClassIDSpace, kMissingFontPanelWidgetBoss, kFontUsagePrefix + 25)
DECLARE_PMID(kClassIDSpace, kTypekitTopAlignImageBoss, kFontUsagePrefix + 26)
DECLARE_PMID(kClassIDSpace, kTypekitInfoButtonBoss, kFontUsagePrefix + 27)
DECLARE_PMID(kClassIDSpace, kWhiteStaticTextWidgetBoss, kFontUsagePrefix + 28)
DECLARE_PMID(kClassIDSpace, kColorGenericPanelWidgetBoss, kFontUsagePrefix + 29)
DECLARE_PMID(kClassIDSpace, kTurnTypekitONButtonBoss, kFontUsagePrefix + 30)
DECLARE_PMID(kClassIDSpace, kAutoActivatePrefBoss, kFontUsagePrefix + 31)
DECLARE_PMID(kClassIDSpace, kOpenAutoActivateDialogCmdBoss, kFontUsagePrefix + 32)
DECLARE_PMID(kClassIDSpace, kAutoActivateDialogBoss, kFontUsagePrefix + 33)
DECLARE_PMID(kClassIDSpace, kThresholdWarningDialogBoss, kFontUsagePrefix + 34)

// <Message ID>		// note - message ids conflict with class id space.
DECLARE_PMID(kMessageIDSpace, kThorHasStartedUpMessage, kFontUsagePrefix + 31)
DECLARE_PMID(kMessageIDSpace, kVulcanFontSyncStatusResponseMessage, kFontUsagePrefix + 32)
DECLARE_PMID(kMessageIDSpace, kVulcanEnableFontSyncResponseMessage, kFontUsagePrefix + 33)
DECLARE_PMID(kMessageIDSpace, kThorPreferenceUpdateMessage, kFontUsagePrefix + 34)
DECLARE_PMID(kMessageIDSpace, kThorHasTerminatedMessage, kFontUsagePrefix + 35)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kFontUsageMenuComponentImpl, kFontUsagePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kFontUsageDialogControllerImpl, kFontUsagePrefix + 2)
// gap
DECLARE_PMID(kImplementationIDSpace, kFontUsageDialogObserverImpl, kFontUsagePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kFontFindChangeButtonsObsImpl, kFontUsagePrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDocumentFontUsageImpl, kFontUsagePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSetOtherFindChangeOptionCmdImpl, kFontUsagePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kOtherFindChangeOptionDataImpl, kFontUsagePrefix + 8)

// gap
//gap - was kFontUsageDataImpl  kFontUsagePrefix + 9
//DECLARE_PMID(kImplementationIDSpace, kFontListDataImpl, kFontUsagePrefix + 10)	//jwb 9/6/01 moved to FontMgrID.h
DECLARE_PMID(kImplementationIDSpace, kFontUsageTargetServerImpl, kFontUsagePrefix + 12)

// ---- Moved from Font Manager plug-in
DECLARE_PMID(kImplementationIDSpace, kFontMgrUIImpl, kFontUsagePrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kMissingFontsControllerImpl, kFontUsagePrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kMissingFontsDialogObserverImpl, kFontUsagePrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kShellTextControlDataImpl, kFontUsagePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kOpenFindFontsDialogCmdImpl, kFontUsagePrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kOpenMapFontsDialogImpl, kFontUsagePrefix + 18)
// ---- end move.
//gap
DECLARE_PMID(kImplementationIDSpace, kMissingFontListControlViewImpl, kFontUsagePrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kSyncFontsButtonObserverImpl, kFontUsagePrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kFontUsageDialogUIUtilsImpl, kFontUsagePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kSyncFontCheckBoxObserverImpl, kFontUsagePrefix + 24)
// gap
DECLARE_PMID(kImplementationIDSpace, kGoToTypeKitButtonObserverImpl, kFontUsagePrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kFindFontMissingIconToolTipImpl, kFontUsagePrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kFindFontSpinningIconToolTipImpl, kFontUsagePrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kDV_PlainBackgroundGenericPanelViewImpl, kFontUsagePrefix + 29)
// gap
DECLARE_PMID(kImplementationIDSpace, kPlainBackgroundCheckBoxToolTipImpl, kFontUsagePrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kSyncFontButtonToolTipImpl, kFontUsagePrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kSyncFontCheckBoxToolTipImpl, kFontUsagePrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kTypekitVulcanMessengerImpl, kFontUsagePrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kTypekitInfoButtonEHImpl, kFontUsagePrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kTypekitUsageTrackingImpl, kFontUsagePrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kAutoActivateFontPrefImpl, kFontUsagePrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kAutoActivateFontCmdImpl, kFontUsagePrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kOpenAutoActivateDialogCmdImpl, kFontUsagePrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kAutoActivateDialogObserverImpl, kFontUsagePrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kAutoActivateDialogControllerImpl, kFontUsagePrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kAutoActivateDocSelectionObserverImpl, kFontUsagePrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kThresholdWarningDialogObserverImpl, kFontUsagePrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kAutoActivateCmdDataImpl, kFontUsagePrefix + 44)

// <Interface ID>
// InterfaceIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTUSAGEDATA, kFontUsagePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROCESSFINDFONTDIALOG, kFontUsagePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IOTHERFINDCHANGEOPTIONDATA, kFontUsagePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTFONTUSAGE, kFontUsagePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IBUTTONOBSERVER, kFontUsagePrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMGRUI, kFontUsagePrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_DOCNAMETEXTCONTROLDATA, kFontUsagePrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTUSAGEDIALOGUIUTILS, kFontUsagePrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTPSNAMEDATA, kFontUsagePrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNCCHECKBOXWIDGETIDDATA, kFontUsagePrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNCBUTTONWIDGETIDDATA, kFontUsagePrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTSLISTBOXWIDGETIDDATA, kFontUsagePrefix + 12)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_ITYPEKITVULCANMESSENGER, kFontUsagePrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ITYPEKITUSAGETRACKING, 	kFontUsagePrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOACTIVATEFONTPREFS, kFontUsagePrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOACTIVATESELECTIONOBSERVER, kFontUsagePrefix + 17)

// <Widget ID>
// WidgetIDs
DECLARE_PMID(kWidgetIDSpace, kFontsUsedListBoxWidgetID, kFontUsagePrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kFontUsageCountLabelWidgetID, kFontUsagePrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kFontUsageCountWidgetID, kFontUsagePrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kFontUsageMissingCountLabelWidgetID, kFontUsagePrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kFontUsageMissingCountWidgetID, kFontUsagePrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kFontUsageGraphicsCountLabelWidgetID, kFontUsagePrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kFontUsageGraphicsCountWidgetID, kFontUsagePrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kFontUsageDialogWidgetID, kFontUsagePrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kFontUsageReplaceFontWidgetID, kFontUsagePrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kFontUsageSelectFontWidgetID, kFontUsagePrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kSyncFontCheckBoxWidgetId, kFontUsagePrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kReplaceAllLabelWidgetID, kFontUsagePrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kFontUsageMoreButtonWidgetID, kFontUsagePrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kFontUsageReplaceAllFontWidgetID, kFontUsagePrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kMoreInfoPanelWidgetId, kFontUsagePrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kFontUsageReplaceFindFontWidgetID, kFontUsagePrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kFontUsageFontStringWidgetID, kFontUsagePrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kFontUsageFontPanelWidgetID, kFontUsagePrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kFontUsageMissingFontIconWidgetID, kFontUsagePrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kFontUsageGraphicFontIconWidgetID, kFontUsagePrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kFontUsageDialogLabelWidgetID, kFontUsagePrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kFontUsageTypekitFontIconWidgetID, kFontUsagePrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfoLabelWidgetID, kFontUsagePrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kFontUsageType1FontIconWidgetID, kFontUsagePrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kFontUsageTrueTypeFontIconWidgetID, kFontUsagePrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kFontUsageATCFontIconWidgetID, kFontUsagePrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kFontUsageOpenTypeFontIconWidgetID, kFontUsagePrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kFontUsageOCFFontIconWidgetID, kFontUsagePrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kFontUsageCIDFontIconWidgetID, kFontUsagePrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel1WidgetID, kFontUsagePrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo1WidgetID, kFontUsagePrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel2WidgetID, kFontUsagePrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo2WidgetID, kFontUsagePrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel3WidgetID, kFontUsagePrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo3WidgetID, kFontUsagePrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel4WidgetID, kFontUsagePrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo4WidgetID, kFontUsagePrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel5WidgetID, kFontUsagePrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo5WidgetID, kFontUsagePrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel6WidgetID, kFontUsagePrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo6WidgetID, kFontUsagePrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel7WidgetID, kFontUsagePrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo7WidgetID, kFontUsagePrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel8WidgetID, kFontUsagePrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo8WidgetID, kFontUsagePrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kFontUsageFontDropDownWidgetId, kFontUsagePrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kFontUsageFamilyDropDownWidgetId, kFontUsagePrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kFontUsageStyleDropDownWidgetId, kFontUsagePrefix + 48)

DECLARE_PMID(kWidgetIDSpace, kFUButtonPanelWidgetID, kFontUsagePrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kFUInfoLabelPanelWidgetID, kFontUsagePrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kFUInfoTextPanelWidgetID, kFontUsagePrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kFUFontsInDocumentPanelWidgetID, kFontUsagePrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kFUFontCountPanelWidgetID, kFontUsagePrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kFUMissingFontCountPanelWidgetID, kFontUsagePrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kFUTopSectionPanelWidgetID, kFontUsagePrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kFontUsageFontStylePanelDropDownWidgetId, kFontUsagePrefix + 56)

DECLARE_PMID(kWidgetIDSpace, kFUCol2FontCountLabelsPanelWidgetID, kFontUsagePrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kFUGraphicFontCountPanelWidgetID, kFontUsagePrefix + 58)

// ---- Moved from Font Manager plug-in
DECLARE_PMID(kWidgetIDSpace, kMissingFontMultiLineStaticTextWidgetID, kFontUsagePrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kMissingFontParentWidgetID, kFontUsagePrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kMissingFontWarningSignWidgetID, kFontUsagePrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kMissingFontWarningMsgWidgetID, kFontUsagePrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kFontUsageSyncFontsButtonWidgetID, kFontUsagePrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kMissingFontListScrollBarWidgetID, kFontUsagePrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kMissingFontListGroupWidgetId, kFontUsagePrefix + 65)
// ---- end move.

DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel9WidgetID, kFontUsagePrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo9WidgetID, kFontUsagePrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kFontUsageShowFileButtonWidgetID, kFontUsagePrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kSpacerWidgetID, kFontUsagePrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kFUStaticText1WidgetID, kFontUsagePrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kFUStaticText2WidgetID, kFontUsagePrefix + 71)

DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel10WidgetID, kFontUsagePrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo10WidgetID, kFontUsagePrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kFontUsageLabel11WidgetID, kFontUsagePrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kFontUsageInfo11WidgetID, kFontUsagePrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kRedefineStylesID, kFontUsagePrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kSpacerWidget2ID, kFontUsagePrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kReplaceStylesPanelID, kFontUsagePrefix + 78)

DECLARE_PMID(kWidgetIDSpace, kStylesOverriddenID, kFontUsagePrefix + 79) // id for dont show again dialog
DECLARE_PMID(kWidgetIDSpace, kFontNotFoundOrNotChangedID, kFontUsagePrefix + 80) // id for dont show again dialog
DECLARE_PMID(kWidgetIDSpace, kMissingFontsListBoxWidgetID, kFontUsagePrefix + 81) 
DECLARE_PMID(kWidgetIDSpace, kMissingFontPanelWidgetID, kFontUsagePrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kMissingFontStringWidgetID, kFontUsagePrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kSyncTypeKitFontsButtonWidgetID, kFontUsagePrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kPlainBackgroundCheckBoxWidgetID, kFontUsagePrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kTypekitSeperatorWidgetID, kFontUsagePrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kHyperlinkTextWidgetID, kFontUsagePrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kSpinningIconWidgetID, kFontUsagePrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kErrorTextWidgetID, kFontUsagePrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kTypekitSignWidgetID, kFontUsagePrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kSyncFontButtonWidgetID, kFontUsagePrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kFontUsageReplacelabelWidgetID, kFontUsagePrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kFontUsageFontReplacePanelId, kFontUsagePrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kFontUsageFontReplaceWidgetId, kFontUsagePrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kReplaceAndInfoButtonPanelId, kFontUsagePrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kFUFontsInDocumentPanelInnerWidgetID, kFontUsagePrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kSyncFontButtonPanelWidgetId, kFontUsagePrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kFontUsageButtonsInner1PanelId, kFontUsagePrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kFontUsageButtonsInner2PanelId, kFontUsagePrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kFontUsageButtonsPanelId, kFontUsagePrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kTreeTopBarPanelId, kFontUsagePrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kTreeTopBarSplitterWidgetID, kFontUsagePrefix + 102)
DECLARE_PMID(kWidgetIDSpace, KFontInfoTextWidgetID, kFontUsagePrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kSyncTextWidgetID, kFontUsagePrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kSyncTextPanelWidgetID, kFontUsagePrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kErrorPanelWidgetID, kFontUsagePrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kMissingDialogTreeTopBarPanelId, kFontUsagePrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kMissingDialogSeparatorPanelId, kFontUsagePrefix + 108)
DECLARE_PMID(kWidgetIDSpace, KMissingDialogFontInfoTextWidgetID, kFontUsagePrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kMissingDialogSyncTextPanelWidgetID, kFontUsagePrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kMissingDialogSyncTextWidgetID, kFontUsagePrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kMissingDialogTreeTopBarSplitterWidgetID, kFontUsagePrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kMissingDialogSyncButtonPanel1WidgetID, kFontUsagePrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kMissingDialogSyncButtonPanel2WidgetID, kFontUsagePrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kManyMissingFontsWidgetID, kFontUsagePrefix + 115)

DECLARE_PMID(kWidgetIDSpace, kTypekitErrorDialogWidgetID, kFontUsagePrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kErrorMessageWidgetID, kFontUsagePrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kGoToTypekitButtonWidgetID, kFontUsagePrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kMissingFontWarningSignWidgetPanelID, kFontUsagePrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kNoMissingFontMsgWidgetPanelID, kFontUsagePrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kNoMissingFontMsgWidgetID, kFontUsagePrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kCustomCheckBoxPanelWidgetID, kFontUsagePrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kMissingFontInfoSignWidgetID, kFontUsagePrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kTypekitHeroImageWidgetID, kFontUsagePrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kMissingDlgMessagePanelID, kFontUsagePrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kErrorPanelMessageWidgetID, kFontUsagePrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kMissingFontWarningMsg2WidgetID, kFontUsagePrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kToggleTypekitButtonWidgetID, kFontUsagePrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kTypekitStatusContainerWidgetID, kFontUsagePrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kTypekitOnStatusPanelID, kFontUsagePrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kTypekitOFFStatusPanelID, kFontUsagePrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kCCBannerContainerWidgetID, kFontUsagePrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kFontUsageSVGFontIconWidgetID, kFontUsagePrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kFontUsageOTVarFontIconWidgetID, kFontUsagePrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kAutoActivateFontParentWidgetID, kFontUsagePrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kAutoActivateFontWarningMsg1WidgetID, kFontUsagePrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kAutoActivateFontWarningMsg2WidgetID, kFontUsagePrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kDontShowCheckBoxWidgetID, kFontUsagePrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kLearnMoreButtonWidgetID, kFontUsagePrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kMissingFontSecondaryStringWidgetID, kFontUsagePrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kThresholdWarningMsgWidgetID, kFontUsagePrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kThresholdParentWidgetID, kFontUsagePrefix + 142)
// <Action ID>
// ActionIDs
DECLARE_PMID(kActionIDSpace, kFontUsageActionID, kFontUsagePrefix + 1)

#endif // __FontUsageDialogID__




