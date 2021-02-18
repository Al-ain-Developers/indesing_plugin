//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/GeneralPrefsID.h $
//  
//  Owner: Yeming Liu
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
//  Contains IDs used by the GeneralPrefsDialog plug-in
//  
//========================================================================================

#ifndef __GeneralPrefsID__
#define __GeneralPrefsID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGeneralPrefsDialogPrefix	 RezLong(0x9900)

// <Start IDC>
// PluginID
#define kGeneralPrefsPluginName		"General Preferences Panel"
DECLARE_PMID(kPlugInIDSpace, kGeneralPrefsPluginID, kGeneralPrefsDialogPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kGeneralPrefsMenuActionBoss, kGeneralPrefsDialogPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGeneralPrefsDialogBoss, kGeneralPrefsDialogPrefix + 2)
DECLARE_PMID(kClassIDSpace, kFileHandlingPrefsPanelBoss, kGeneralPrefsDialogPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPDFQuitClipboardCheckboxBoss, kGeneralPrefsDialogPrefix + 4)
//gap
DECLARE_PMID(kClassIDSpace, kChooseFolderButtonWidgetBoss, kGeneralPrefsDialogPrefix + 7)
DECLARE_PMID(kClassIDSpace, kTempFolderPathStaticTextBoss, kGeneralPrefsDialogPrefix + 8)
DECLARE_PMID(kClassIDSpace, kResetWarningDialogButtonWidgetBoss, kGeneralPrefsDialogPrefix + 9)
DECLARE_PMID(kClassIDSpace, kPreviewImageSizeCheckboxBoss, kGeneralPrefsDialogPrefix + 10)
DECLARE_PMID(kClassIDSpace, kClipboardPrefsPanelBoss, kGeneralPrefsDialogPrefix + 11)
DECLARE_PMID(kClassIDSpace, kCheckLinksAtOpenCheckboxBoss, kGeneralPrefsDialogPrefix + 12)


// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kGeneralPrefsMenuActionImpl, kGeneralPrefsDialogPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGeneralPrefsDialogControllerImpl, kGeneralPrefsDialogPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGeneralPrefsPanelCreatorImpl, kGeneralPrefsDialogPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kFileHandlingPrefsPanelControllerImpl, kGeneralPrefsDialogPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kFileHandlingPrefsPanelCreatorImpl, kGeneralPrefsDialogPrefix + 5)
// DECLARE_PMID(kImplementationIDSpace, kDisplayOptionsMenuActionImpl, kGeneralPrefsDialogPrefix + 6)	OBSOLETE
DECLARE_PMID(kImplementationIDSpace, kChooseFolderButtonObserverImpl, kGeneralPrefsDialogPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kTempFolderPathStaticTextTipImpl, kGeneralPrefsDialogPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kResetWarningDlgButtonObserverImpl, kGeneralPrefsDialogPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kPDFQuitClipboardCheckboxObserverImpl, kGeneralPrefsDialogPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPreviewImageSizeCheckboxObserverImpl, kGeneralPrefsDialogPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kClipboardPrefsPanelControllerImpl, kGeneralPrefsDialogPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kClipboardPrefsPanelCreatorImpl, kGeneralPrefsDialogPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kCheckLinksAtOpenCheckboxObserverImpl, kGeneralPrefsDialogPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kGeneralPrefsDialogObserverImpl, kGeneralPrefsDialogPrefix + 15)

// <Widget ID>
// Widget IDs for General Prefs Dialog
DECLARE_PMID(kWidgetIDSpace, kGeneralPrefsDialogWidgetID, kGeneralPrefsDialogPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kImageDisplayTextWidgetID, kGeneralPrefsDialogPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kImageDisplayDropDownWidgetID, kGeneralPrefsDialogPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kPageNumberingTextWidgetID, kGeneralPrefsDialogPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kPageNumberingDropDownWidgetID, kGeneralPrefsDialogPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPreventSelectingLockedItemsCheckboxWidgetId, kGeneralPrefsDialogPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kImagesTitleTextWidgetID, kGeneralPrefsDialogPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kPageNumberingTitleTextWidgetID, kGeneralPrefsDialogPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kWhenScalingTextWidgetID, kGeneralPrefsDialogPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kGlobalPrefsPopupGroupWidgetID, kGeneralPrefsDialogPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kGeneralPrefsGroupWidgetId, kGeneralPrefsDialogPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kGeneralPrefsGroup2WidgetId, kGeneralPrefsDialogPrefix + 13)
//gap
DECLARE_PMID(kWidgetIDSpace, kWelcomeScreenPrefsTitleWidgetID, kGeneralPrefsDialogPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kWelcomeScreenGroupPanelWidgetID, kGeneralPrefsDialogPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kCCXStartPrefCheckboxWidgetId, kGeneralPrefsDialogPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kGeneralPrefsDialogPanelWidgetID, kGeneralPrefsDialogPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kLegacyNewDocDlgPrefCheckboxWidgetId, kGeneralPrefsDialogPrefix + 19)
// print options
DECLARE_PMID(kWidgetIDSpace, kGeneralPrefsGroup4WidgetId, kGeneralPrefsDialogPrefix + 20)
// formerly kPrintTextWidgetID, currently unused kGeneralPrefsDialogPrefix + 22
// formerly kPrintUnitsDropDownWidgetID, currently unused kGeneralPrefsDialogPrefix + 23
// gap
DECLARE_PMID(kWidgetIDSpace, kResetWarningDialogButtonWidgetID,		kGeneralPrefsDialogPrefix + 34)

DECLARE_PMID(kWidgetIDSpace, kClipboardPrefsDialogWID,				kGeneralPrefsDialogPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kClipboardPrefsPreferPDFWID,			kGeneralPrefsDialogPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kClipboardPrefsCopyPDFWID,				kGeneralPrefsDialogPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kClipboardPanelTitleWidgetID,			kGeneralPrefsDialogPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kClipboardPrefsPreferStyledTextWID,	kGeneralPrefsDialogPrefix + 39)

DECLARE_PMID(kWidgetIDSpace, kGlyphThresholdWidgetID,				kGeneralPrefsDialogPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kGlyphThresholdTextWidgetID,			kGeneralPrefsDialogPrefix + 41)

DECLARE_PMID(kWidgetIDSpace, kPastePrefsDialogWidgetID,				kGeneralPrefsDialogPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kPastePanelTitleWidgetID,				kGeneralPrefsDialogPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kPasteFormattedRadioWidgetID,			kGeneralPrefsDialogPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kPasteUnformattedRadioWidgetID,		kGeneralPrefsDialogPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kPasteOptionsClusterWidgetID,			kGeneralPrefsDialogPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kPastePanelLabelWidgetID,				kGeneralPrefsDialogPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kUIOpenRecentLengthTextWidgetID,		kGeneralPrefsDialogPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kUIOpenRecentLengthWidgetID,			kGeneralPrefsDialogPrefix + 49)

// Widget IDs for Saved Files Prefs Panel
DECLARE_PMID(kWidgetIDSpace, kFileHandlingPrefsPanelWidgetID,		kGeneralPrefsDialogPrefix + 50)

DECLARE_PMID(kWidgetIDSpace, kDocRecoveryDataGroupWidgetID,			kGeneralPrefsDialogPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kDocRecoveryDataLabelWidgetID,			kGeneralPrefsDialogPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kRecoveryFolderLabelWidgetID,			kGeneralPrefsDialogPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kRecoveryFolderTextWidgetID,			kGeneralPrefsDialogPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kChooseFolderButtonWidgetID,			kGeneralPrefsDialogPrefix + 55)

DECLARE_PMID(kWidgetIDSpace, kSavingInDesignFilesGroupWidgetID,		kGeneralPrefsDialogPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kSavingInDesignFilesLabelWidgetID,		kGeneralPrefsDialogPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kSaveDocPreviewCheckBoxWidgetID,		kGeneralPrefsDialogPrefix + 58)

DECLARE_PMID(kWidgetIDSpace, kGeneralPrefsGroup5WidgetId,			kGeneralPrefsDialogPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kFontDownloadTitleTextWidgetID,		kGeneralPrefsDialogPrefix + 60)

//gap
DECLARE_PMID(kWidgetIDSpace, kClipboardPrefsQuitWidgetID,			kGeneralPrefsDialogPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kPreviewSizeStaticTextId,				kGeneralPrefsDialogPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kPreviewSizeDropDownWidgetID,			kGeneralPrefsDialogPrefix + 66)

DECLARE_PMID(kWidgetIDSpace, kClipboardPrefsPanelWidgetID,			kGeneralPrefsDialogPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kCheckLinksAtOpenCheckBoxWidgetID,			kGeneralPrefsDialogPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kAutoFindMissingLinksCheckBoxWidgetID,			kGeneralPrefsDialogPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kCreateTextLinksCheckBoxWidgetID,			kGeneralPrefsDialogPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kDefaultRelinkFolderLabelWidgetID,			kGeneralPrefsDialogPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kDefaultRelinkFolderDropDownWidgetID,			kGeneralPrefsDialogPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kSnippetPositionLabelWidgetID,			kGeneralPrefsDialogPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kSnippetLocationDropdownWidgetID,			kGeneralPrefsDialogPrefix + 74)

//gap
DECLARE_PMID(kWidgetIDSpace, kSnippetImportGroupWidgetID,			kGeneralPrefsDialogPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kSnippetImportGroupBorderWidgetID,		kGeneralPrefsDialogPrefix + 77)
//gap

DECLARE_PMID(kWidgetIDSpace, kImageGroupWidgetID, kGeneralPrefsDialogPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kRelinkBehaviorLabelWidgetID, kGeneralPrefsDialogPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kRelinkPreserveDimensionsCheckBoxWidgetID, kGeneralPrefsDialogPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kImageGroupLabelWidgetID, kGeneralPrefsDialogPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kThumbnailPagesDropdownWidgetID, kGeneralPrefsDialogPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kThumbnailPagesStaticTextWidgetID, kGeneralPrefsDialogPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kUpdateLinkBringNewLayersAsHiddenCheckBoxWidgetID, kGeneralPrefsDialogPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kContentAwareFitMoreInfoWidgetID, kGeneralPrefsDialogPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kAutoActivateFontWidgetID, kGeneralPrefsDialogPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kAutoActivationCheckBoxWidgetID, kGeneralPrefsDialogPrefix + 91)

//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 92)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 93)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 94)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 95)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 96)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 97)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 98)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kGeneralPrefsGroup6WidgetId, kGeneralPrefsDialogPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kTransformPoliciesTitleTextWidgetID, kGeneralPrefsDialogPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kScaleContentRadioWidgetId, kGeneralPrefsDialogPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kAdjustScalingPercentageRadioWidgetId, kGeneralPrefsDialogPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kTransformPoliciesClusterWidgetID, kGeneralPrefsDialogPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kScaleStrokeWeightCheckBoxWidgetID, kGeneralPrefsDialogPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kScaleEffectsCheckBoxWidgetID, kGeneralPrefsDialogPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kGeneralPrefsGroup7WidgetId, kGeneralPrefsDialogPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kSpotColorHandlingTitleWidgetID, kGeneralPrefsDialogPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kUseIncomingSpotColorCheckboxWidgetId, kGeneralPrefsDialogPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kSpotColorWarningIconWidgetId, kGeneralPrefsDialogPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kGeneralPrefsGroup8WidgetId, kGeneralPrefsDialogPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kContentAwareCropPrefTitleWidgetID, kGeneralPrefsDialogPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kContentAwareCropPrefCheckboxWidgetID, kGeneralPrefsDialogPrefix + 113)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 114)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 115)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 116)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 117)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 118)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 119)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 120)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 121)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 122)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 123)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 124)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 125)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 126)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 127)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 128)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 129)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 130)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 131)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 132)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 133)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 134)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 135)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 136)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 137)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 138)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 139)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 140)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 141)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 142)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 143)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 144)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 145)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 146)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 147)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 148)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 149)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 150)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 151)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 152)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 153)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 154)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 155)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 156)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 157)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 158)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 159)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 160)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 161)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 162)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 163)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 164)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 165)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 166)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 167)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 168)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 169)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 170)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 171)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 172)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 173)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 174)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 175)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 176)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 177)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 178)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 179)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 180)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 181)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 182)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 183)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 184)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 185)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 186)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 187)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 188)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 189)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 190)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 191)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 192)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 193)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 194)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 195)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 196)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 197)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 198)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 199)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 200)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 201)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 202)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 203)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 204)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 205)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 206)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 207)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 208)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 209)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 210)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 211)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 212)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 213)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 214)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 215)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 216)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 217)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 218)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 219)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 220)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 221)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 222)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 223)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 224)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 225)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 226)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 227)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 228)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 229)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 230)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 231)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 232)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 233)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 234)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 235)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 236)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 237)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 238)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 239)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 240)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 241)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 242)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 243)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 244)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 245)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 246)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 247)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 248)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 249)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 250)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 251)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 252)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 253)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 254)
//DECLARE_PMID(kWidgetIDSpace, kMyFancyNewWidgetID, kGeneralPrefsDialogPrefix + 255)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kGeneralPrefsActionID,					kGeneralPrefsDialogPrefix + 1)
DECLARE_PMID(kActionIDSpace, kGeneralPrefsSepActionID,				kGeneralPrefsDialogPrefix + 2)
DECLARE_PMID(kActionIDSpace, kFileHandlingPrefsActionID,			kGeneralPrefsDialogPrefix + 3)
DECLARE_PMID(kActionIDSpace, kClipboardPrefsActionID,				kGeneralPrefsDialogPrefix + 4)
//gap

#endif // __GeneralPrefsID__
