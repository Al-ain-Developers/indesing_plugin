//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/GalleyPrefID.h $
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

#ifndef __GalleyPrefID__
#define __GalleyPrefID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// TODO: ask Robin to allocate a new prefix number this is Keystone BusinessUI prefix
#define kGalleyPrefPrefix	 RezLong(0xf400)	// reserved in AdobePrefix.h

//PlugInID
#define kGalleyPrefPlugInName		"GalleyPreferences"
DECLARE_PMID(kPlugInIDSpace, kGalleyPrefPlugInID, kGalleyPrefPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kGalleyPrefPanelBoss, kGalleyPrefPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGalleyPrefMenuBoss, kGalleyPrefPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kGalleyPrefKitBoss, kGalleyPrefPrefix + 6)
DECLARE_PMID(kClassIDSpace, kGalleyPrefKitRegisterBoss, kGalleyPrefPrefix + 7)
DECLARE_PMID(kClassIDSpace, kGalleyPrefPaletteBoss, kGalleyPrefPrefix + 8)
DECLARE_PMID(kClassIDSpace, kGalleyLeadingDropDownBoss, kGalleyPrefPrefix + 9)
DECLARE_PMID(kClassIDSpace, kGalleyControlsHorizontalPanelBoss, kGalleyPrefPrefix + 10)
DECLARE_PMID(kClassIDSpace, kGalleyControlsFontFamilyBoss, kGalleyPrefPrefix + 11)
DECLARE_PMID(kClassIDSpace, kGalleyControlsZoomBoss, kGalleyPrefPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetSmoothTextCmdBoss, kGalleyPrefPrefix + 13)
DECLARE_PMID(kClassIDSpace, kLineNumberButtonBoss, kGalleyPrefPrefix + 14)
DECLARE_PMID(kClassIDSpace, kSetShowLineNumbersCmdBoss, kGalleyPrefPrefix + 15)
DECLARE_PMID(kClassIDSpace, kParaNameButtonBoss, kGalleyPrefPrefix + 17)
DECLARE_PMID(kClassIDSpace, kSetShowParaNameCmdBoss, kGalleyPrefPrefix + 18)
DECLARE_PMID(kClassIDSpace, kSetGalleyGalleyAleCmdBoss, kGalleyPrefPrefix + 19)
DECLARE_PMID(kClassIDSpace, kAleButtonBoss, kGalleyPrefPrefix + 20)
DECLARE_PMID(kClassIDSpace, kSetGalleyColorsCmdBoss, kGalleyPrefPrefix + 21)
DECLARE_PMID(kClassIDSpace, kSetLeadingCmdBoss, kGalleyPrefPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSetGalleyCursorCmdBoss, kGalleyPrefPrefix + 23)
DECLARE_PMID(kClassIDSpace, kGalleyPrefsScriptProviderBoss, kGalleyPrefPrefix + 24)
//gap
DECLARE_PMID(kClassIDSpace, kSetGalleyDisplayFontCmdBoss, kGalleyPrefPrefix + 26)
DECLARE_PMID(kClassIDSpace, kBackgroundColorDropDownBoss, kGalleyPrefPrefix + 27)
DECLARE_PMID(kClassIDSpace, kForegroundColorDropDownBoss, kGalleyPrefPrefix + 28)
DECLARE_PMID(kClassIDSpace, kThemeDropDownBoss, kGalleyPrefPrefix + 29)
DECLARE_PMID(kClassIDSpace, kTextPreviewBoss, kGalleyPrefPrefix + 30)
DECLARE_PMID(kClassIDSpace, kCursorPreviewBoss, kGalleyPrefPrefix + 31)
DECLARE_PMID(kClassIDSpace, kSmoothTextCheckBoxBoss, kGalleyPrefPrefix + 32)
DECLARE_PMID(kClassIDSpace, kSetOverrideDisplayFontCmdBoss, kGalleyPrefPrefix + 33)
DECLARE_PMID(kClassIDSpace, kFontOverrideCheckBoxBoss, kGalleyPrefPrefix + 34)
DECLARE_PMID(kClassIDSpace, kSetCursorBlinkCmdBoss, kGalleyPrefPrefix + 35)
DECLARE_PMID(kClassIDSpace, kSetUseFontOverrideCmdBoss, kGalleyPrefPrefix + 36)
DECLARE_PMID(kClassIDSpace, kDisplayFontWarningCmdBoss, kGalleyPrefPrefix + 37)
DECLARE_PMID(kClassIDSpace, kSetDisplayFontSizeCmdBoss, kGalleyPrefPrefix + 38)
DECLARE_PMID(kClassIDSpace, kSetShowParaBreaksCmdBoss, kGalleyPrefPrefix + 39)
DECLARE_PMID(kClassIDSpace, kStoryEditorDisplayFamilyObserverBoss, kGalleyPrefPrefix + 40)
DECLARE_PMID(kClassIDSpace, kStoryEditorDisplayFontUIDBoss, kGalleyPrefPrefix + 41)
DECLARE_PMID(kClassIDSpace, kGalleyPrefTestMenuBoss, kGalleyPrefPrefix + 42)
DECLARE_PMID(kClassIDSpace, kFontSizeZoomNumberBoss, kGalleyPrefPrefix + 43)
DECLARE_PMID(kClassIDSpace, kLineSpacingNumberBoss, kGalleyPrefPrefix + 44)
DECLARE_PMID(kClassIDSpace, kSetColumnWidthPrefCmdBoss, kGalleyPrefPrefix + 45)
DECLARE_PMID(kClassIDSpace, kSetColumnHiddenPrefCmdBoss, kGalleyPrefPrefix + 46)
DECLARE_PMID(kClassIDSpace, kOversetDropDownBoss, kGalleyPrefPrefix + 47)
DECLARE_PMID(kClassIDSpace, kSetOversetTextDisplayTypeCmdBoss, kGalleyPrefPrefix + 48)
DECLARE_PMID(kClassIDSpace, kSetGalleyOversetColorCmdBoss, kGalleyPrefPrefix + 49)
DECLARE_PMID(kClassIDSpace, kSetShowDepthRulerCmdBoss, kGalleyPrefPrefix + 50)
DECLARE_PMID(kClassIDSpace, kSetTextAntiAliasStyleCmdBoss, kGalleyPrefPrefix + 51)
DECLARE_PMID(kClassIDSpace, kAntiAliasDropDownBoss, kGalleyPrefPrefix + 52)
DECLARE_PMID(kClassIDSpace, kSetShowFootnotesCmdBoss, kGalleyPrefPrefix + 53)
DECLARE_PMID(kClassIDSpace, kSetFootNoteColorCmdBoss, kGalleyPrefPrefix + 54)

// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYFONTOBSERVER, kGalleyPrefPrefix + 1)

// WidgetIDs (ClassIDs)
DECLARE_PMID(kWidgetIDSpace, kGalleyPrefWidgetId,	kGalleyPrefPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kDisplayOptionsGroupWidgetId,	kGalleyPrefPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kDisplayOptionsGroupBorderWidgetId,	kGalleyPrefPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kTextColorStaticWidgetId,	kGalleyPrefPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kTextColorDropDownWidgetId,	kGalleyPrefPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kSampleTextStaticWidgetId,	kGalleyPrefPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kBackgroundStaticWidgetId,	kGalleyPrefPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kBackgroundDropDownWidgetId,	kGalleyPrefPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kThemeStaticWidgetId,	kGalleyPrefPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kThemeDropDownWidgetId,	kGalleyPrefPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kSmoothTextWidgetId,	kGalleyPrefPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kCursorOptionsGroupBorderWidgetId,	kGalleyPrefPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kCursorOptionsGroupWidgetId,	kGalleyPrefPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kStandardCursorRadioWidgetId,	kGalleyPrefPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kThickCursorRadioWidgetId,	kGalleyPrefPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kBarbellCursorRadioWidgetId,	kGalleyPrefPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kBlockCursorRadioWidgetId,	kGalleyPrefPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kCursorColorStaticWidgetId,	kGalleyPrefPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kCursorColorDropDownWidgetId,	kGalleyPrefPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kHaloColorStaticWidgetId,	kGalleyPrefPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kHaloColorDropDownWidgetId,	kGalleyPrefPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kShowHaloCheckBoxWidgetId,	kGalleyPrefPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kInfoCursorPositionCheckBoxWidgetId,	kGalleyPrefPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kCursorOptionsClusterWidgetId,	kGalleyPrefPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kGalleyPrefKitWidgetId,	kGalleyPrefPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kGalleyPrefKitHorizontalWidgetId,	kGalleyPrefPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kGalleyPrefKitPanelWidgetId,	kGalleyPrefPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kGalleyPrefKitHorizontalSetWidgetId,	kGalleyPrefPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kGalleyLeadingWidgetId,	kGalleyPrefPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kGalleyDisplayFontWidgetId,	kGalleyPrefPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kGalleyDisplaySizeWidgetId,	kGalleyPrefPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kAccurateLineEndingsWidgetID,	kGalleyPrefPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kPositionMarkersWidgetID,	kGalleyPrefPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kQCMarkersWidgetID,	kGalleyPrefPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kLineNumbersWidgetID,	kGalleyPrefPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kStyleNamesWidgetID,	kGalleyPrefPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kHidderCharactersWidgetID,	kGalleyPrefPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kGalleyPrefKitButtonsSetWidgetId,	kGalleyPrefPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kTextPreviewWidgetID,	kGalleyPrefPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kTextPreviewBevelWidgetID,	kGalleyPrefPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kFontFamilyDownWidgetID,	kGalleyPrefPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kFontFamilyCheckBoxWidgetId,	kGalleyPrefPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kBlinkCheckBoxWidgetId,	kGalleyPrefPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kTextThinCaretPreviewWidgetID,	kGalleyPrefPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kTextThickCaretPreviewWidgetID,	kGalleyPrefPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kTextBlockCaretPreviewWidgetID,	kGalleyPrefPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kTextBarbellCaretPreviewWidgetID,	kGalleyPrefPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kOversetStaticWidgetId,	kGalleyPrefPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kOversetDropDownWidgetId,	kGalleyPrefPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kOversetOptionsGroupWidgetId,	kGalleyPrefPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kOversetColorStaticWidgetId,	kGalleyPrefPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kOversetColorDropDownWidgetId,	kGalleyPrefPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kSmoothOptionsStaticTextId,	kGalleyPrefPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kSmoothOptionsWidgetId,	kGalleyPrefPrefix + 83)

// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kGalleyPrefControllerImpl,	kGalleyPrefPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGalleyPrefCreatorImpl,	kGalleyPrefPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGalleyPrefMenuImpl,	kGalleyPrefPrefix + 3)
//gap
DECLARE_PMID(kImplementationIDSpace, kGalleyLeadingObserverImpl, kGalleyPrefPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGalleyFontMenuObserverImpl, kGalleyPrefPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kAutoInitializeObserverImpl, kGalleyPrefPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kFontSizeZoomObserverImpl, kGalleyPrefPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSetSmoothTextCmdImpl, kGalleyPrefPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kLineNumberButtonObserverImpl, kGalleyPrefPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSetShowLineNumbersCmdImpl, kGalleyPrefPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kParaNameButtonObserverImpl, kGalleyPrefPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSetShowParaNameCmdImpl, kGalleyPrefPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSetGalleyGalleyAleCmdImpl, kGalleyPrefPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kAleButtonObserverImpl, kGalleyPrefPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSetGalleyColorsCmdImpl, kGalleyPrefPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSetLeadingCmdImpl, kGalleyPrefPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSetGalleyCursorCmdImpl, kGalleyPrefPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kGalleyPrefsScriptProviderImpl, kGalleyPrefPrefix + 19)
//gap
DECLARE_PMID(kImplementationIDSpace, kSetGalleyDisplayFontCmdImpl, kGalleyPrefPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kColorMenuObserverImpl, kGalleyPrefPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kGalleyFontFamilyObserverImpl, kGalleyPrefPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kLeadingEBTextValidationImpl, kGalleyPrefPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kTextPreviewViewImpl, kGalleyPrefPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kCursorPreviewViewImpl, kGalleyPrefPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSmoothBoxObserverImpl, kGalleyPrefPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSetOverrideDisplayFontCmdImpl, kGalleyPrefPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kFontOverrideObserverImpl, kGalleyPrefPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSetCursorBlinkCmdImpl, kGalleyPrefPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kGalleyPrefTipImpl, kGalleyPrefPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kSetUseFontOverrideCmdImpl, kGalleyPrefPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kDisplayFontWarningCmdImpl, kGalleyPrefPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kSetDisplayFontSizeCmdImpl, kGalleyPrefPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSetShowParaBreaksCmdImpl, kGalleyPrefPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kStoryEditorDisplayDataImpl, kGalleyPrefPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kStoryEditorTargetServerImpl, kGalleyPrefPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kGalleyPrefTestMenuImpl, kGalleyPrefPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, TextAttrGalleyDisplayFontSizeImpl, kGalleyPrefPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kGalleyAttributeListImpl, kGalleyPrefPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, TextAttrGalleyDisplayLineSpacingImpl, kGalleyPrefPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kSetColumnWidthPrefCmdImpl, kGalleyPrefPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kSetColumnHiddenPrefCmdImpl, kGalleyPrefPrefix + 43)
//DECLARE_PMID(kImplementationIDSpace, kZoomSizeMeasureTypeImpl, kGalleyPrefPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kSetOversetTextDisplayTypeCmdImpl, kGalleyPrefPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kSetGalleyOversetColorCmdImpl, kGalleyPrefPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kSetShowDepthRulerCmdImpl, kGalleyPrefPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kSetTextAntiAliasStyleCmdImpl, kGalleyPrefPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kAntiAliasDropDownObserverImpl, kGalleyPrefPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSetShowFootnotesCmdImpl, kGalleyPrefPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kSetFootNoteColorCmdImpl, kGalleyPrefPrefix + 50)

// Action ids
DECLARE_PMID(kActionIDSpace, kGalleyPrefActionID, kGalleyPrefPrefix + 1)
DECLARE_PMID(kActionIDSpace, kGalleyPrefKitActionID, kGalleyPrefPrefix + 2)

// Scripting ids
DECLARE_PMID(kScriptInfoIDSpace, kGalleyPreferencesObjectScriptElement, kGalleyPrefPrefix + 10)

DECLARE_PMID(kScriptInfoIDSpace, kBackgroundColorPropertyScriptElement, kGalleyPrefPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kBlinkCursorPropertyScriptElement, kGalleyPrefPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kCursorTypePropertyScriptElement, kGalleyPrefPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kOverridePreviewFontPropertyScriptElement, kGalleyPrefPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kSmoothTextPropertyScriptElement, kGalleyPrefPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kTextColorPropertyScriptElement, kGalleyPrefPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kUseOverridePreviewFontPropertyScriptElement, kGalleyPrefPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kGalleyPreferencesPropertyScriptElement, kGalleyPrefPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kShowDepthRulerElement, kGalleyPrefPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kDividerColorElement, kGalleyPrefPrefix + 29)

DECLARE_PMID(kScriptInfoIDSpace, kInCopyUIColorsEnumScriptElement, kGalleyPrefPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kCursorTypesEnumScriptElement, kGalleyPrefPrefix + 41)

DECLARE_PMID(kScriptInfoIDSpace, kAliasTypeEnumScriptElement, kGalleyPrefPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kAliasTypePropertyScriptElement, kGalleyPrefPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kShowFootnotePropertyScriptElement, kGalleyPrefPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteColorPropertyScriptElement, kGalleyPrefPrefix + 45)

DECLARE_PMID(kScriptInfoIDSpace, kShowParagraphStylesPropertyScriptElement, kGalleyPrefPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kShowParagraphMarksPropertyScriptElement, kGalleyPrefPrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kShowLineNumbersPropertyScriptElement, kGalleyPrefPrefix + 48)
DECLARE_PMID(kScriptInfoIDSpace, kLineSpacingValuePropertyScriptElement, kGalleyPrefPrefix + 49)
DECLARE_PMID(kScriptInfoIDSpace, kDisplayFontPropertyScriptElement, kGalleyPrefPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kDisplayFontSizePropertyScriptElement, kGalleyPrefPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kInfoColumnWidthPropertyScriptElement, kGalleyPrefPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kShowInfoColumnPropertyScriptElement, kGalleyPrefPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kLineSpacingEnumScriptElement, kGalleyPrefPrefix + 54)


//GUIDS
// {595F5387-2EAB-4c10-B66A-71A1908B49CE}
#define kGalleyPrefs_CLSID { 0x595f5387, 0x2eab, 0x4c10, { 0xb6, 0x6a, 0x71, 0xa1, 0x90, 0x8b, 0x49, 0xce } }

#endif // __GalleyPrefID__



