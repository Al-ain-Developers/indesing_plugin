//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/BNUIID.h $
//  
//  Owner:
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once

#ifndef __BNUIID__
#define __BNUIID__

// Plug-In:
#define kBNUIPrefix		    RezLong(0x1A700)
#define kBNUIStringPrefix	"0x1A700"
#define kBNUIPluginName	    "BNUI" // Name of this Plug-In

#define kBNUIBoss			kBNUIPrefix + 1

// Plugin ID:
DECLARE_PMID(kPlugInIDSpace, kBNUIPluginId, kBNUIPrefix + 0)

// Class IDs:
DECLARE_PMID(kClassIDSpace, kBNMainDialogActionComponentBoss, kBNUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kBNTestMenuBoss, kBNUIPrefix + 1)
// Gap 2-3
DECLARE_PMID(kClassIDSpace, kBNMainDialogBoss, kBNUIPrefix + 4)
// Gap 6-11
DECLARE_PMID(kClassIDSpace, kBNListTypeWidgetBoss, kBNUIPrefix + 12)
// Gap 13
DECLARE_PMID(kClassIDSpace, kBNCorePanelBoss, kBNUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kBNFindPanelBoss, kBNUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kBNNumberStyleWidgetBoss, kBNUIPrefix + 16)
// Gap 17-21
DECLARE_PMID(kClassIDSpace, kBNStartAtWidgetBoss, kBNUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kBNDialogHookWidgetBoss, kBNUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kBNBulletDialogBoss, kBNUIPrefix + 24)
DECLARE_PMID(kClassIDSpace, kBNOkDoneWidgetBoss, kBNUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, kBNControlStripRegisterBoss, kBNUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, kBNBulletsButtonBoss, kBNUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kBNNumbersButtonBoss, kBNUIPrefix + 28)
// DECLARE_PMID(kClassIDSpace, kBNUsedColorWidgetBoss, kBNUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kBNFindDialogHookWidgetBoss, kBNUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kBNTabPositionWidgetBoss, kBNUIPrefix + 31)
DECLARE_PMID(kClassIDSpace, kBNAlignmentWidgetBoss, kBNUIPrefix + 32)
// Gap 33
DECLARE_PMID(kClassIDSpace, kBNAddBulletWidgetBoss, kBNUIPrefix + 34)
DECLARE_PMID(kClassIDSpace, kBNBaseGlyphGridBoss, kBNUIPrefix + 35)
DECLARE_PMID(kClassIDSpace, kBNMainGlyphGridBoss, kBNUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kBNSimpleGlyphGridBoss, kBNUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kBNCharacterFormatWidgetBoss, kBNUIPrefix + 38)
DECLARE_PMID(kClassIDSpace, kBNLeftIndentWidgetBoss, kBNUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kBNFLIndentWidgetBoss, kBNUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kBNGroupLabelWidgetBoss, kBNUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, kBNUsedFontFamilyWidgetBoss, kBNUIPrefix + 42)
// Gap 43-44
DECLARE_PMID(kClassIDSpace, kBNAddBulletsFontFamilyWidgetBoss, kBNUIPrefix + 45)
DECLARE_PMID(kClassIDSpace, kBNAddBulletsFontStyleWidgetBoss, kBNUIPrefix + 46)
DECLARE_PMID(kClassIDSpace, kBNKeyboardShortcutActionsBoss, kBNUIPrefix + 47)
//Gap 48-52
DECLARE_PMID(kClassIDSpace, kBNRightIndentWidgetBoss, kBNUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kBNListStyleWidgetBoss,		kBNUIPrefix + 53)
DECLARE_PMID(kClassIDSpace, kBNListLevelWidgetBoss,		kBNUIPrefix + 54)
DECLARE_PMID(kClassIDSpace, kBNCFPreviousWidgetBoss,	kBNUIPrefix + 55)
DECLARE_PMID(kClassIDSpace, kBNNumberMetaCharButtonWidgetBoss,	kBNUIPrefix + 56)
DECLARE_PMID(kClassIDSpace, kBNRestartCheckboxWidgetBoss,	kBNUIPrefix + 57)
DECLARE_PMID(kClassIDSpace, kBNRestartComboboxWidgetBoss,	kBNUIPrefix + 58)
DECLARE_PMID(kClassIDSpace, kBNListStyleNameWidgetBoss,	kBNUIPrefix + 59)

DECLARE_PMID(kClassIDSpace, kDefineListDialogBoss,		kBNUIPrefix + 100)
DECLARE_PMID(kClassIDSpace, kListStyleListWidgetBoss,	kBNUIPrefix + 101)
DECLARE_PMID(kClassIDSpace, kListNameDialogBoss,		kBNUIPrefix + 102)
DECLARE_PMID(kClassIDSpace, kBNNumberMetaMenuComponentBoss,		kBNUIPrefix + 103)
DECLARE_PMID(kClassIDSpace, kBNBulletCharStyleWidgetBoss,		kBNUIPrefix + 104)
DECLARE_PMID(kClassIDSpace, kBNNumberCharStyleWidgetBoss,		kBNUIPrefix + 105)
DECLARE_PMID(kClassIDSpace, kBNTextAfterMetaCharButtonWidgetBoss,		kBNUIPrefix + 106)
DECLARE_PMID(kClassIDSpace, kBNTextAfterMetaMenuComponentBoss,		kBNUIPrefix + 107)
DECLARE_PMID(kClassIDSpace, kBNNumberingNumberWidgetBoss,		kBNUIPrefix + 108)
DECLARE_PMID(kClassIDSpace, kBNBulletTextAfterWidgetBoss,		kBNUIPrefix + 109)
DECLARE_PMID(kClassIDSpace, kDeleteListStyleDialogBoss,			kBNUIPrefix + 110)
//DECLARE_PMID(kClassIDSpace, kBNChapterNumDialogBoss,			kBNUIPrefix + 111)
//DECLARE_PMID(kClassIDSpace, kBNChapterNumStyleWidgetBoss,		kBNUIPrefix + 112)
//DECLARE_PMID(kClassIDSpace, kBNChapterNumDialogActionComponentBoss,		kBNUIPrefix + 113)
DECLARE_PMID(kClassIDSpace, kLaunchBNModalDialogCmdBoss,			kBNUIPrefix + 114)
DECLARE_PMID(kClassIDSpace, kBNTextEditBoxWidgetBoss,	kBNUIPrefix + 115)
DECLARE_PMID(kClassIDSpace, kBulletsAndNumberingPropPnlActiveKitWidgetBoss,    kBNUIPrefix + 116)

// Interface IDs:
// Gap 0, 1
DECLARE_PMID(kInterfaceIDSpace, IID_IBNTEXTSUITE, kBNUIPrefix + 2)
// Gap 3, 4
DECLARE_PMID(kInterfaceIDSpace, IID_IBNCONTROLSTRIPSUITE, kBNUIPrefix + 5)
// Gap 6
DECLARE_PMID(kInterfaceIDSpace, IID_IBNGLYPHGRIDSELDATA, kBNUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNGLYPHGRIDARRAY, kBNUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNGLYPHGRIDPANELDATA, kBNUIPrefix + 9)
// Gap 10
DECLARE_PMID(kInterfaceIDSpace, IID_IBNSCROLLBARREFERENCE, kBNUIPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNSHOWNPANELINTDATA, kBNUIPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNTABVALIDATED, kBNUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNPANELPRIVATEUTILS, kBNUIPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNISBNDIALOG, kBNUIPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IISNEWLISTDIALOG, kBNUIPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNNUMBERVALIDATED, kBNUIPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNTEXTAFTERVALIDATED, kBNUIPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNPLUGINIDDATA, kBNUIPrefix + 19)		//IID_IINTDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGRESOURCEIDDATA, kBNUIPrefix + 20) //IID_IINTDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IBNWIDGETVALIDATED, kBNUIPrefix + 21) //IID_IBOOLDATA


// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kBNMainDialogActionComponentImpl, kBNUIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kBNTestMenuImpl, kBNUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kBNFontGlyphGridArrayImpl, kBNUIPrefix + 2)
// Gap 3
DECLARE_PMID(kImplementationIDSpace, kBNPreferencesImpl_obsolete, kBNUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kBNTextSuiteCSBImpl, kBNUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kBNTextSuiteASBImpl, kBNUIPrefix + 6)
// Gap 7-11
DECLARE_PMID(kImplementationIDSpace, kBNLeftIndentObserverImpl, kBNUIPrefix + 12)
// Gap 13, 14
DECLARE_PMID(kImplementationIDSpace, kBNListTypeObserverImpl, kBNUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kBNStartAtObserverImpl, kBNUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kBNMainDialogResDataImpl, kBNUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kBNCorePanelResDataImpl, kBNUIPrefix + 18)
// Gap 19-23
DECLARE_PMID(kImplementationIDSpace, kBNNumberStyleObserverImpl, kBNUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kBNCorePanelObserverImpl, kBNUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kBNCorePanelControllerImpl, kBNUIPrefix + 26)
// Gap 27
DECLARE_PMID(kImplementationIDSpace, kBNBulletDialogObserverImpl, kBNUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kBNAddBulletObserverImpl, kBNUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kBNKeyboardShortcutActionsImpl, kBNUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kBNControlStripRegisterImpl, kBNUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kBNControlStripSuiteImpl, kBNUIPrefix + 32)
// Gap 33
DECLARE_PMID(kImplementationIDSpace, kBNBulletsButtonObserverImpl, kBNUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kBNNumbersButtonObserverImpl, kBNUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kBNFLIndentObserverImpl, kBNUIPrefix + 36)
// Gap 37
DECLARE_PMID(kImplementationIDSpace, kBNTabPositionObserverImpl, kBNUIPrefix + 38)
// Gap 39
DECLARE_PMID(kImplementationIDSpace, kBNBaseGlyphGridViewImpl, kBNUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kBNGlyphGridSelDataImpl, kBNUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kBNGlyphGridArrayImpl, kBNUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kBNMainGlyphGridObserverImpl, kBNUIPrefix + 43)
// Gap - 44
DECLARE_PMID(kImplementationIDSpace, kBNGlyphGridTipImpl, kBNUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kBNGlyphGridPanelEHImpl, kBNUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kBNGlyphGridPanelDataImpl, kBNUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kBNGlyphGridObserverImpl, kBNUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kBNBulletDialogControllerImpl, kBNUIPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kBNTabPositionValidationImpl, kBNUIPrefix + 50)
// Gap 51-52
DECLARE_PMID(kImplementationIDSpace, kBNTabPositionHandlerImpl, kBNUIPrefix + 53)
// Gap 54-58
DECLARE_PMID(kImplementationIDSpace, kBNGroupLabelObserverImpl, kBNUIPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kBNNumberingNumberValidationImpl, kBNUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kBNBulletTextAfterValidationImpl, kBNUIPrefix + 61)
// Gap 62-89
DECLARE_PMID(kImplementationIDSpace, kBNAddBulletsTargetServerImpl, kBNUIPrefix + 90)
// Gap 91
DECLARE_PMID(kImplementationIDSpace, kBNAddBulletsFontFamilyObserverImpl, kBNUIPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kBNAddBulletsFontStyleObserverImpl, kBNUIPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kBNScrollBarReferenceImpl, kBNUIPrefix + 94)
// Gap 95
DECLARE_PMID(kImplementationIDSpace, kBNButtonEventHandlerImpl, kBNUIPrefix + 96)
//DECLARE_PMID(kImplementationIDSpace, kBNUsedColorObserverImpl, kBNUIPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kBNFindPanelResDataImpl, kBNUIPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kBNFindMainDialogResDataImpl, kBNUIPrefix + 99)
// DECLARE_PMID(kImplementationIDSpace, kBNUsedFontFamilyObserverImpl, kBNUIPrefix + 100)

DECLARE_PMID(kImplementationIDSpace, kDefineListDialogObserverImpl, kBNUIPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kDefineListDialogControllerImpl,kBNUIPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kListNameDialogControllerImpl,	kBNUIPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kBNListStyleObserverImpl,	kBNUIPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kBNListLevelObserverImpl,	kBNUIPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kBNCFPreviousObserverImpl,	kBNUIPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kBNNumberMetaMenuComponentImpl, kBNUIPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kBNRestartCheckboxObserverImpl, kBNUIPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kBNRestartComboboxObserverImpl, kBNUIPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kBNRestartValidationImpl, kBNUIPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kBNTextAfterMetaMenuComponentImpl, kBNUIPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kBNAlignmentObserverImpl, kBNUIPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kBNNumberingNumberObserverImpl, kBNUIPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kBNBulletTextAfterObserverImpl, kBNUIPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kBNBulletCharStyleObserverImpl, kBNUIPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kBNNumberCharStyleObserverImpl, kBNUIPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kDeleteListStyleDialogControllerImpl, kBNUIPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kBNListStylesNameValidationImpl, kBNUIPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kListNameDialogObserverImpl, kBNUIPrefix + 119)

//DECLARE_PMID(kImplementationIDSpace, kBNChapterNumControllerImpl, kBNUIPrefix + 120)
//DECLARE_PMID(kImplementationIDSpace, kBNChapterNumStyleObserverImpl, kBNUIPrefix + 121)
//DECLARE_PMID(kImplementationIDSpace, kBNChapterNumDialogObserverImpl, kBNUIPrefix + 122)
//DECLARE_PMID(kImplementationIDSpace, kBNChapterNumDialogActionComponentImpl, kBNUIPrefix + 123)

DECLARE_PMID(kImplementationIDSpace, kBNTextDefaultsSuiteCSBImpl, kBNUIPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kLaunchBNModalDialogCmdImpl, kBNUIPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kBNListStyleListEHImpl, kBNUIPrefix + 126)

DECLARE_PMID(kImplementationIDSpace, kBNTextEditBoxScrapSuiteImpl, kBNUIPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kBNTextComboBoxAttributesImpl, kBNUIPrefix + 128)

DECLARE_PMID(kImplementationIDSpace, kBNRightIndentObserverImpl, kBNUIPrefix + 129)

DECLARE_PMID(kImplementationIDSpace, kBNPanelPrivateUtilsImpl, kBNUIPrefix + 255)


// Messages:
// Gap 0
DECLARE_PMID(kMessageIDSpace, kBNGridSelectionChangeMessage, kBNUIPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kBNGridFontChangeMessage, kBNUIPrefix + 2)

// ActionIDs:
// Gap 0
DECLARE_PMID(kActionIDSpace, kBNMainDialogActionId, kBNUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kBNSeparatorActionId, kBNUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kBNToggleBulletsActionId, kBNUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kBNToggleNumbersActionId, kBNUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kBNConvertBNActionId, kBNUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kBNConvertBNSepActionId, kBNUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kDefineListActionId, kBNUIPrefix + 7)
// Advanced Numbering Menu Items
DECLARE_PMID(kActionIDSpace, kRestartContinueNumberingActionID,	kBNUIPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kBNChapterNumActionId, kBNUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kListSepActionId,	kBNUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kBNParaPanelMainSepActionId,	kBNUIPrefix + 11)

// gap


// Meta characters Action IDs
DECLARE_PMID(kActionIDSpace, kBNNumberMetaEllipsisActionID,					kBNUIPrefix + 100)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaSep1ActionID,						kBNUIPrefix + 101)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaEmDashActionID,					kBNUIPrefix + 102)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaEnDashActionID,					kBNUIPrefix + 103)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaSep2ActionID,						kBNUIPrefix + 104)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaMSpaceActionID,					kBNUIPrefix + 105)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaNSpaceActionID,					kBNUIPrefix + 106)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaSep3ActionID,						kBNUIPrefix + 107)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaTabActionID,						kBNUIPrefix + 108)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaSep4ActionID,						kBNUIPrefix + 109)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholder1ActionID,		kBNUIPrefix + 110)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholder2ActionID,		kBNUIPrefix + 111)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholder3ActionID,		kBNUIPrefix + 112)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholder4ActionID,		kBNUIPrefix + 113)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholder5ActionID,		kBNUIPrefix + 114)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholder6ActionID,		kBNUIPrefix + 115)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholder7ActionID,		kBNUIPrefix + 116)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholder8ActionID,		kBNUIPrefix + 117)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholder9ActionID,		kBNUIPrefix + 118)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaChapterNoPlaceholderActionID,		kBNUIPrefix + 119)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaCurrentLevelPlaceholderActionID,	kBNUIPrefix + 120)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholderActionID,			kBNUIPrefix + 121)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholderSep1ActionID,		kBNUIPrefix + 122)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaLevelPlaceholderSep2ActionID,		kBNUIPrefix + 123)

// Newly added
DECLARE_PMID(kActionIDSpace, kBNNumberMetaParagraphSymbolActionID,			kBNUIPrefix + 124)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaSectionSymbolActionID,			kBNUIPrefix + 125)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaBulletCharacterActionID,			kBNUIPrefix + 126)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaHairSpaceActionID,				kBNUIPrefix + 127)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaThinSpaceActionID,				kBNUIPrefix + 128)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaFigureSpaceActionID,				kBNUIPrefix + 129)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaPunctuationSpaceActionID,			kBNUIPrefix + 130)

// Japanese Specific Action IDs
DECLARE_PMID(kActionIDSpace, kBNNumberMetaIdeoSpaceActionID,				kBNUIPrefix + 131)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaQtrSpaceActionID,					kBNUIPrefix + 132)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJOpenParenActionID,				kBNUIPrefix + 133)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJOpenSquareBracketActionID,		kBNUIPrefix + 134)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJOpenSquareQuoteActionID,			kBNUIPrefix + 135)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJOpenThickBracketActionID,		kBNUIPrefix + 136)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJKomeMarkActionID,				kBNUIPrefix + 137)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJAsteriskActionID,				kBNUIPrefix + 138)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJCircleActionID,					kBNUIPrefix + 139)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJChuuActionID,					kBNUIPrefix + 140)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJTradChuuActionID,				kBNUIPrefix + 141)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJCloseParenActionID,				kBNUIPrefix + 142)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJCloseSquareBracketActionID,		kBNUIPrefix + 143)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJCloseSquareQuoteActionID,		kBNUIPrefix + 144)
DECLARE_PMID(kActionIDSpace, kBNNumberMetaJCloseThickBracketActionID,		kBNUIPrefix + 145)

// ---

// Meta characters Action IDs

DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaEllipsisActionID,					kBNUIPrefix + 150)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaSep1ActionID,						kBNUIPrefix + 151)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaEmDashActionID,					kBNUIPrefix + 152)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaEnDashActionID,					kBNUIPrefix + 153)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaSep2ActionID,						kBNUIPrefix + 154)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaMSpaceActionID,					kBNUIPrefix + 155)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaNSpaceActionID,					kBNUIPrefix + 156)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaSep3ActionID,						kBNUIPrefix + 157)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaTabActionID,						kBNUIPrefix + 158)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaSep4ActionID,						kBNUIPrefix + 159)

// Newly added
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaParagraphSymbolActionID,			kBNUIPrefix + 160)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaSectionSymbolActionID,				kBNUIPrefix + 161)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaBulletCharacterActionID,			kBNUIPrefix + 162)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaHairSpaceActionID,					kBNUIPrefix + 163)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaThinSpaceActionID,					kBNUIPrefix + 164)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaFigureSpaceActionID,				kBNUIPrefix + 165)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaPunctuationSpaceActionID,			kBNUIPrefix + 166)

// Japanese Specific Action IDs
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaIdeoSpaceActionID,				kBNUIPrefix + 171)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaQtrSpaceActionID,					kBNUIPrefix + 172)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJOpenParenActionID,				kBNUIPrefix + 173)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJOpenSquareBracketActionID,		kBNUIPrefix + 174)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJOpenSquareQuoteActionID,			kBNUIPrefix + 175)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJOpenThickBracketActionID,		kBNUIPrefix + 176)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJKomeMarkActionID,				kBNUIPrefix + 177)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJAsteriskActionID,				kBNUIPrefix + 178)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJCircleActionID,					kBNUIPrefix + 179)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJChuuActionID,					kBNUIPrefix + 180)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJTradChuuActionID,				kBNUIPrefix + 181)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJCloseParenActionID,				kBNUIPrefix + 182)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJCloseSquareBracketActionID,		kBNUIPrefix + 183)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJCloseSquareQuoteActionID,		kBNUIPrefix + 184)
DECLARE_PMID(kActionIDSpace, kBNTextAfterMetaJCloseThickBracketActionID,		kBNUIPrefix + 185)



// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kBNCorePanelWidgetId, kBNUIPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kBNMainDialogWidgetId, kBNUIPrefix + 1)
// Gap 2
DECLARE_PMID(kWidgetIDSpace, kBNListTypeLabelWidgetId, kBNUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kBNListTypeDDWidgetId, kBNUIPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kBNBulletsPanelWidgetId, kBNUIPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kBNNumbersPanelWidgetId, kBNUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kBNMainGlyphGridWidgetId, kBNUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kBNBulletDialogWidgetId, kBNUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kBNBulletGroupPanelWidgetId, kBNUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kBNOkDoneWidgetId, kBNUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kBNAddToGridWidgetId, kBNUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kBNRememberFontWidgetId, kBNUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kBNBulletInfoWidgetId, kBNUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kBNNumberStyleDDWidgetId,  kBNUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kBNNumberStyleLabelWidgetId, kBNUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kBNSizeLabelWidgetId, kBNUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kBNSizeCBWidgetId, kBNUIPrefix + 17)
// Gap 18-25
DECLARE_PMID(kWidgetIDSpace, kBNModeLabelWidgetId, kBNUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kBNStartAtEBWidgetId, kBNUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kBNLeftIndentNudgeWidgetId, kBNUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kBNDialogHookWidgetId, kBNUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kBNBulletGroupLabelWidgetId, kBNUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kBNShowLabelWidgetId, kBNUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kBNGlyphGridPanelId, kBNUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kBNControlStripPanelWidgetId, kBNUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kBNControlStripClusterWidgetId, kBNUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kBNBulletsButtonWidgetId, kBNUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kBNNumbersButtonWidgetId, kBNUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kBNLeftIndentEBWidgetId, kBNUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kBNFLIndentEBWidgetId, kBNUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kBNTabPositionEBWidgetId, kBNUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kBNAlignmentDDWidgetId, kBNUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kBNPositionPanelWidgetId, kBNUIPrefix + 41)
// Gap 42
DECLARE_PMID(kWidgetIDSpace, kBNGlyphGridWidgetId, kBNUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kBNAlignmentLabelWidgetId, kBNUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kBNPositionTopLabelWidgetId, kBNUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kBNTabPositionLabelWidgetId, kBNUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kBNLeftIndentLabelWidgetId, kBNUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kBNFLIndentLabelWidgetId, kBNUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kBNAddBulletWidgetId, kBNUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kBNDeleteBulletWidgetId, kBNUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kBNCharFmtPanelWidgetId, kBNUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kBNChrFmtLabelWidgetId, kBNUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kBNFontFamilyLblWidgetId, kBNUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kBNFontFamilyLstWidgetId, kBNUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kBNFontStyleLblWidgetId, kBNUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kBNFontStyleLstWidgetId, kBNUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kBNGlyphGridScrollWidgetID, kBNUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kBNFLIndentNudgeWidgetId, kBNUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kBNTabPositionNudgeWidgetId, kBNUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kBNPositionTopLabelPanelWidgetId, kBNUIPrefix + 60)
// Gap 61-62
DECLARE_PMID(kWidgetIDSpace, kBNNumberGroupPanelWidgetId, kBNUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kBNNumberGroupLabelWidgetId, kBNUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kBNListStyleLabelWidgetId, kBNUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kBNListStyleDDWidgetId, kBNUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kBNListLevelLabelWidgetId, kBNUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kBNListLevelEditBoxWidgetId, kBNUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kBNListLevelNudgeWidgetId, kBNUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kCFPreviousButtonWidgetID, kBNUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kBNNumberingNumberEditBoxWidgetID, kBNUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kBNNumberMetaCharButtonWidgetID, kBNUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kBNRestartCheckBoxWidgetId, kBNUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kBNRestartComboBoxWidgetId, kBNUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kBNNumberLabelWidgetID, kBNUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kBNTextAfterLabelWidgetID,	kBNUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kBNBulletTextAfterEditBoxWidgetID,kBNUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kBNBulletTextAfterMetaCharButtonWidgetID,kBNUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kBNBulletCharStyleLabelWidgetID,kBNUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kBNBulletCharStyleDDWidgetID,kBNUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kBNNumberCharStyleLabelWidgetID,kBNUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kBNNumberCharStyleDDWidgetID,	kBNUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kBNBulletsParentPanelWidgetID,	kBNUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kBNNumbersParentPanelWidgetID,	kBNUIPrefix + 84)



DECLARE_PMID(kWidgetIDSpace, kDefineListDialogWidgetId, kBNUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kListNewButtonWidgetId,	kBNUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kListEditButtonWidgetId, 	kBNUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kListDeleteButtonWidgetId, kBNUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kListsLabelWidgetId,		kBNUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kListsGroupWidgetId,		kBNUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kListStyleListWidgetId,	kBNUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kListOptionsGroupWidgetId,			kBNUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kListOptionsGroupTextWidgetId,		kBNUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kListContinueStoryCheckboxWidgetId,kBNUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kListContinueBookCheckboxWidgetId,	kBNUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kListNameDialogWidgetId,			kBNUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kListNameStaticWidgetId,			kBNUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kListNameTextEditWidgetId,			kBNUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kListLoadButtonWidgetId, 			kBNUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kDeleteListStyleDialogWidgetId,	kBNUIPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kDeleteListStyleLabelWidgetId,		kBNUIPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kDeleteListStyleDropDownWidgetId, 	kBNUIPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kDeleteListStyleWarningIconWidgetId,kBNUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kBNPropertiesPanelWidgetId,		kBNUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kBNMoreOptionsWidgetID,			kBNUIPrefix + 120)
//Gap 119-129
//DECLARE_PMID(kWidgetIDSpace, kBNChapterNumDialogWidgetId,kBNUIPrefix + 130)
//DECLARE_PMID(kWidgetIDSpace, kBNChapterNumberStyleLabelWidgetId,kBNUIPrefix + 131)
//DECLARE_PMID(kWidgetIDSpace, kBNChapterNumStyleDDWidgetId,kBNUIPrefix + 132)
//DECLARE_PMID(kWidgetIDSpace, kBNUserDefinedChapterNumWidgetID,kBNUIPrefix + 133)
//DECLARE_PMID(kWidgetIDSpace, kBNContinueChapterNumFromPrevDocWidgetID,kBNUIPrefix + 134)
//DECLARE_PMID(kWidgetIDSpace, kBNSameChapterNumAsPrevDocWidgetID,kBNUIPrefix + 135)
//DECLARE_PMID(kWidgetIDSpace, kChapterNumValueWidgetID,kBNUIPrefix + 136)
//DECLARE_PMID(kWidgetIDSpace, kCNBookNameLabelWidgetId,kBNUIPrefix + 137)
//DECLARE_PMID(kWidgetIDSpace, kCNRadioClusterWidgetID,kBNUIPrefix + 138)
//DECLARE_PMID(kWidgetIDSpace, kChapterNumStringWidgetID,kBNUIPrefix + 139)

// Other StringKeys:
//#define kBNUIInvalidNumberLevelPlaceholdersKey    kBNUIStringPrefix "kBNUIInvalidNumberLevelPlaceholdersKey"
//#define kBNUIInvalidNumberFormatNoneKey           kBNUIStringPrefix "kBNUIInvalidNumberFormatNoneKey"
//#define kBNUIInvalidNumberTabSpaceKey             kBNUIStringPrefix "kBNUIInvalidNumberTabSpaceKey"


#endif // __BNUIID__
