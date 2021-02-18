//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/widgetid.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by widgets
//  
//========================================================================================

#ifndef __WidgetID__
#define __WidgetID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// <Start IDC>
#define kWidgetPrefix	 RezLong(0x600)
// second is consecutive so no entry
#define kWidgetPrefix3	 RezLong(0x20E00)
//note: widgetbin uses 3 prefixes! They are 0x600 and 0x700. normally
// id files would stop at 255, but the second one just spills over into the next prefix.
// An adjacent space was not available for the third so numbering starts over with kWidgetPrefix3


// PlugInIDs (GlobalPrefsDialog uses WidgetBin prefix)
DECLARE_PMID(kPlugInIDSpace, kGlobalPrefsDialogPluginID, kWidgetPrefix + 1)
#define kGlobalPrefsDialogPluginName	"Global Preferences Panel"

DECLARE_PMID(kPlugInIDSpace, kWidgetsPluginID, kWidgetPrefix + 2)
#define kWidgetsPluginName	"Widgets"

// <Class ID>

DECLARE_PMID(kClassIDSpace, kIconSuiteButtonWidgetBoss, kWidgetPrefix + 1)
DECLARE_PMID(kClassIDSpace, kIconPopupBoss, kWidgetPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPasswordEditBoxWidgetBoss, kWidgetPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSeparatorWidgetBoss, kWidgetPrefix + 4)
DECLARE_PMID(kClassIDSpace, kClusterPanelMuteWidgetBoss, kWidgetPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSelectablePanelBoss, kWidgetPrefix + 6)
DECLARE_PMID(kClassIDSpace, kButtonWidgetBoss, kWidgetPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCheckBoxWidgetBoss, kWidgetPrefix + 8)
DECLARE_PMID(kClassIDSpace, kRadioButtonWidgetBoss, kWidgetPrefix + 9)
DECLARE_PMID(kClassIDSpace, kPlatformWidgetBoss, kWidgetPrefix + 10					/*60A	hex */)
DECLARE_PMID(kClassIDSpace, kStaticTextWidgetBoss, kWidgetPrefix + 11)
DECLARE_PMID(kClassIDSpace, kPanelWithHiliteBorderWidgetBoss, kWidgetPrefix + 12)
DECLARE_PMID(kClassIDSpace, kIgnoreStrokeTypeSelection, kWidgetPrefix + 13)
DECLARE_PMID(kClassIDSpace, kOWLCanvasDialogControllerBoss, kWidgetPrefix + 14)
DECLARE_PMID(kClassIDSpace, kDropDownListMapperBoss, kWidgetPrefix + 15)
DECLARE_PMID(kClassIDSpace, kLinkedSplitterPanelWidgetBoss, kWidgetPrefix + 16 )
DECLARE_PMID(kClassIDSpace, kResizePresentationWidgetBoss, kWidgetPrefix + 17)
DECLARE_PMID(kClassIDSpace, kTabAreaWidgetBoss, kWidgetPrefix + 18)
DECLARE_PMID(kClassIDSpace, kBridgeIconButtonBoss, kWidgetPrefix + 19)
DECLARE_PMID(kClassIDSpace, kScrollBarWidgetBoss, kWidgetPrefix + 20)
DECLARE_PMID(kClassIDSpace, kDialogWindowBoss, kWidgetPrefix + 21)
DECLARE_PMID(kClassIDSpace, kGroupPanelWidgetBoss, kWidgetPrefix + 22)
DECLARE_PMID(kClassIDSpace, kPalettePanelWidgetBoss, kWidgetPrefix + 23)
DECLARE_PMID(kClassIDSpace, kScrollBarPanoramaSyncBoss, kWidgetPrefix + 24)
DECLARE_PMID(kClassIDSpace, kResizeDialogBoss, kWidgetPrefix + 25 )
DECLARE_PMID(kClassIDSpace, kLayoutSplitterPanelWidgetBoss, kWidgetPrefix + 26 )
DECLARE_PMID(kClassIDSpace, kGridBoss, kWidgetPrefix + 27)
DECLARE_PMID(kClassIDSpace, kGenericPanelWidgetBoss, kWidgetPrefix + 28)
DECLARE_PMID(kClassIDSpace, kGenericPanelWithBorderWidgetBoss, kWidgetPrefix + 29)
DECLARE_PMID(kClassIDSpace, kGridScrollBarPanoramaSyncBoss, kWidgetPrefix + 30)
DECLARE_PMID(kClassIDSpace, kInLineEditBaseWidgetBoss, kWidgetPrefix + 31)
DECLARE_PMID(kClassIDSpace, kInLineEditChildStaticTextWidgetBoss, kWidgetPrefix + 32)
DECLARE_PMID(kClassIDSpace, kTextInLineEditChildEditBoxWidgetBoss, kWidgetPrefix + 33)
DECLARE_PMID(kClassIDSpace, kInLineEditEventMonitorBoss, kWidgetPrefix + 34)
DECLARE_PMID(kClassIDSpace, kTextInLineEditWidgetBoss, kWidgetPrefix + 35)
DECLARE_PMID(kClassIDSpace, kInLineEditContainerWidgetBoss, kWidgetPrefix + 36)
DECLARE_PMID(kClassIDSpace, kCellPanelBoss, kWidgetPrefix + 37)
DECLARE_PMID(kClassIDSpace, kMeasurementPopupMenuBoss, kWidgetPrefix + 38)
DECLARE_PMID(kClassIDSpace, kPrimaryResourcePanelWidgetBoss, kWidgetPrefix + 39)
DECLARE_PMID(kClassIDSpace, kBaseWidgetBoss, kWidgetPrefix + 40)
DECLARE_PMID(kClassIDSpace, kStaticMultiLineTextWidgetBoss, kWidgetPrefix + 41)
DECLARE_PMID(kClassIDSpace, kPageNumEditBoxWidgetBoss, kWidgetPrefix + 42)
DECLARE_PMID(kClassIDSpace, kPageRangeEditBoxWidgetBoss, kWidgetPrefix + 43)
DECLARE_PMID(kClassIDSpace, kErasablePrimaryResourcePanelWidgetBoss, kWidgetPrefix + 44)
DECLARE_PMID(kClassIDSpace, kPageNumPlusMasterEditBoxWidgetBoss, kWidgetPrefix + 45)
DECLARE_PMID(kClassIDSpace, kUnitsPopupMenuActionBoss, kWidgetPrefix + 46 )
DECLARE_PMID(kClassIDSpace, kUnitsPopupActionRegisterBoss, kWidgetPrefix + 47 )
DECLARE_PMID(kClassIDSpace, kModalWindowBoss, kWidgetPrefix + 48)
DECLARE_PMID(kClassIDSpace, kMovableModalWindowBoss, kWidgetPrefix + 49)
DECLARE_PMID(kClassIDSpace, kModelessWindowBoss, kWidgetPrefix + 50)
DECLARE_PMID(kClassIDSpace, kDialogEventFilterBoss, kWidgetPrefix + 51)
DECLARE_PMID(kClassIDSpace, kCancelButtonWidgetBoss, kWidgetPrefix + 52)

DECLARE_PMID(kClassIDSpace, kEnableCommandPassThroughCmdBoss, kWidgetPrefix + 53 )
DECLARE_PMID(kClassIDSpace, kDisableCommandPassThroughCmdBoss, kWidgetPrefix + 54 )
DECLARE_PMID(kClassIDSpace, kPNGIconButtonWidgetBoss, kWidgetPrefix + 55 )
DECLARE_PMID(kClassIDSpace, kOverPrintIconPushButtonBoss, kWidgetPrefix + 56 )
DECLARE_PMID(kClassIDSpace, kSplitterPanelWidgetBoss, kWidgetPrefix + 57 )

DECLARE_PMID(kClassIDSpace, kPreviewDialogCmdBoss, kWidgetPrefix + 58)
DECLARE_PMID(kClassIDSpace, kEndDialogCmdBoss, kWidgetPrefix + 59)
DECLARE_PMID(kClassIDSpace, kGlobalPrefsDialogBoss, kWidgetPrefix + 60)
DECLARE_PMID(kClassIDSpace, kSelectableDialogPanelBoss, kWidgetPrefix + 61)
DECLARE_PMID(kClassIDSpace, kDialogBoss, kWidgetPrefix + 62)
DECLARE_PMID(kClassIDSpace, kGroupPanelNewWidgetBoss, kWidgetPrefix + 63)
DECLARE_PMID(kClassIDSpace, kSelectableDialogManagerBoss, kWidgetPrefix + 64)
DECLARE_PMID(kClassIDSpace, kProgressBarWidgetBoss, kWidgetPrefix + 65)
DECLARE_PMID(kClassIDSpace, kSimpleIconSuiteButtonWidgetBoss, kWidgetPrefix + 66)
DECLARE_PMID(kClassIDSpace, kDocProgressBarWidgetBoss, kWidgetPrefix + 67 )
DECLARE_PMID(kClassIDSpace, kRollOverIconPushButtonBoss, kWidgetPrefix + 68)
DECLARE_PMID(kClassIDSpace, kGlobalPreferencesBoss, kWidgetPrefix + 69)
DECLARE_PMID(kClassIDSpace, kPanelWithInverseHiliteBorderWidgetBoss, kWidgetPrefix + 70)
DECLARE_PMID(kClassIDSpace, kZoomToCmdBoss, kWidgetPrefix + 71)
DECLARE_PMID(kClassIDSpace, kFitInViewCmdBoss, kWidgetPrefix + 72)
DECLARE_PMID(kClassIDSpace, kFullViewCmdBoss, kWidgetPrefix + 73)
DECLARE_PMID(kClassIDSpace, kInfoStaticTextIntWidgetBoss, kWidgetPrefix + 74 )
DECLARE_PMID(kClassIDSpace, kWidgetTestMenuBoss, kWidgetPrefix + 75)
DECLARE_PMID(kClassIDSpace, kTextCursorThreadBoss, kWidgetPrefix + 76)
DECLARE_PMID(kClassIDSpace, kColorListDropDownWidgetBoss, kWidgetPrefix + 77 )
DECLARE_PMID(kClassIDSpace, kClusterPanelWidgetBoss, kWidgetPrefix + 78)
DECLARE_PMID(kClassIDSpace, kDropDownListWidgetBoss, kWidgetPrefix + 79)
DECLARE_PMID(kClassIDSpace, kNudgeEditBoxWidgetBoss, kWidgetPrefix + 80)
DECLARE_PMID(kClassIDSpace, kColorListDropDownElementWidgetBoss, kWidgetPrefix + 81 )
DECLARE_PMID(kClassIDSpace, kComboBoxWidgetBoss, kWidgetPrefix + 82)
DECLARE_PMID(kClassIDSpace, kNudgeControlWidgetBoss, kWidgetPrefix + 83)
DECLARE_PMID(kClassIDSpace, kUIColorSwatchWidgetBoss, kWidgetPrefix + 84)
DECLARE_PMID(kClassIDSpace, kSplitterWidgetBoss, kWidgetPrefix + 85)
DECLARE_PMID(kClassIDSpace, kComboBoxEditBoxWidgetBoss, kWidgetPrefix + 86)
DECLARE_PMID(kClassIDSpace, kComboBoxDropDownWidgetBoss, kWidgetPrefix + 87)
DECLARE_PMID(kClassIDSpace, kADBEIconToggleButtonWidgetBoss, kWidgetPrefix + 88)
DECLARE_PMID(kClassIDSpace, kWidgetRefBoss, kWidgetPrefix + 89)
DECLARE_PMID(kClassIDSpace, kEditBoxlMenuComponentBoss, kWidgetPrefix + 90)
DECLARE_PMID(kClassIDSpace, kSelectableDialogBoss, kWidgetPrefix + 91)
DECLARE_PMID(kClassIDSpace, kStrokeFillWidgetBoss, kWidgetPrefix + 92)
DECLARE_PMID(kClassIDSpace, kIconFieldWidgetBoss, kWidgetPrefix + 93)
DECLARE_PMID(kClassIDSpace, kToolsPopupWindowBoss, kWidgetPrefix + 94)
DECLARE_PMID(kClassIDSpace, kStdSliderWidgetBoss, kWidgetPrefix + 95)
DECLARE_PMID(kClassIDSpace, kSliderTrackerBoss, kWidgetPrefix + 96)
DECLARE_PMID(kClassIDSpace, kRealEditBoxWidgetBoss, kWidgetPrefix + 97)
DECLARE_PMID(kClassIDSpace, kIntEditBoxWidgetBoss, kWidgetPrefix + 98)
DECLARE_PMID(kClassIDSpace, kPercentageEditBoxWidgetBoss, kWidgetPrefix + 99)
DECLARE_PMID(kClassIDSpace, kXMeasureEditBoxWidgetBoss, kWidgetPrefix + 100)
DECLARE_PMID(kClassIDSpace, kYMeasureEditBoxWidgetBoss, kWidgetPrefix + 101)
DECLARE_PMID(kClassIDSpace, kTextMeasureEditBoxWidgetBoss, kWidgetPrefix + 102)
DECLARE_PMID(kClassIDSpace, kLineWtMeasureEditBoxWidgetBoss, kWidgetPrefix + 103)
DECLARE_PMID(kClassIDSpace, kTextEditBoxWidgetBoss, kWidgetPrefix + 104)
DECLARE_PMID(kClassIDSpace, kIntComboBoxWidgetBoss, kWidgetPrefix + 105)
DECLARE_PMID(kClassIDSpace, kPercentageComboBoxWidgetBoss, kWidgetPrefix + 106)
DECLARE_PMID(kClassIDSpace, kXMeasureComboBoxWidgetBoss, kWidgetPrefix + 107)
DECLARE_PMID(kClassIDSpace, kYMeasureComboBoxWidgetBoss, kWidgetPrefix + 108)
DECLARE_PMID(kClassIDSpace, kTextMeasureComboBoxWidgetBoss, kWidgetPrefix + 109)
DECLARE_PMID(kClassIDSpace, kLineWtMeasureComboBoxWidgetBoss, kWidgetPrefix + 110)
DECLARE_PMID(kClassIDSpace, kRealComboBoxWidgetBoss, kWidgetPrefix + 111)
DECLARE_PMID(kClassIDSpace, kMeasureEditBoxWidgetBoss, kWidgetPrefix + 112)
DECLARE_PMID(kClassIDSpace, kMeasureComboBoxWidgetBoss, kWidgetPrefix + 113)
DECLARE_PMID(kClassIDSpace, kSearchBoxPanelWidgetBoss, kWidgetPrefix + 114)
DECLARE_PMID(kClassIDSpace, kSearchDropDownListWidgetBoss, kWidgetPrefix + 115)
DECLARE_PMID(kClassIDSpace, kPreviewDialogResetCmdBoss, kWidgetPrefix + 116)
DECLARE_PMID(kClassIDSpace, kAngleEditBoxWidgetBoss, kWidgetPrefix + 117)
DECLARE_PMID(kClassIDSpace, kAngleComboBoxWidgetBoss, kWidgetPrefix + 118)
DECLARE_PMID(kClassIDSpace, kTextComboBoxWidgetBoss, kWidgetPrefix + 119)
DECLARE_PMID(kClassIDSpace, kTypeaheadTextComboBoxWidgetBoss, kWidgetPrefix + 120)
DECLARE_PMID(kClassIDSpace, kTypeaheadComboBoxEditBoxWidgetBoss, kWidgetPrefix + 121)
DECLARE_PMID(kClassIDSpace, kUIColorDropDownListWidgetBoss, kWidgetPrefix + 122)
DECLARE_PMID(kClassIDSpace, kUIColorPickerWidgetBoss, kWidgetPrefix + 123)
DECLARE_PMID(kClassIDSpace, kErasableKitPanelWidgetBoss, kWidgetPrefix + 124)
DECLARE_PMID(kClassIDSpace, kChainButtonBoss, kWidgetPrefix + 125)
DECLARE_PMID(kClassIDSpace, kPanelWithRolloverWidgetBoss, kWidgetPrefix + 126)
DECLARE_PMID(kClassIDSpace, kTypeaheadComboBoxDropDownWidgetBoss, kWidgetPrefix + 127)
DECLARE_PMID(kClassIDSpace, kDefinedBreakMultiLineTextWidgetBoss, kWidgetPrefix + 128)

DECLARE_PMID(kClassIDSpace, kInfoStaticTextWidgetBoss, kWidgetPrefix + 129)
DECLARE_PMID(kClassIDSpace, kIconSuiteWidgetBoss, kWidgetPrefix + 130)

DECLARE_PMID(kClassIDSpace, kXMeasureSessionEditBoxWidgetBoss, kWidgetPrefix + 131)
DECLARE_PMID(kClassIDSpace, kYMeasureSessionEditBoxWidgetBoss, kWidgetPrefix + 132)
DECLARE_PMID(kClassIDSpace, kOwnerDrawStdListBoxWidgetBoss, kWidgetPrefix + 133)
DECLARE_PMID(kClassIDSpace, kFontSpecTextEditBoxWidgetBoss, kWidgetPrefix + 134)
DECLARE_PMID(kClassIDSpace, kPageRangeComboBoxWidgetBoss, kWidgetPrefix + 135)
DECLARE_PMID(kClassIDSpace, kPictureTextButtonWidgetBoss, kWidgetPrefix + 136)
DECLARE_PMID(kClassIDSpace, kPanelWithWhiteBackgroundWidgetBoss, kWidgetPrefix + 137)
DECLARE_PMID(kClassIDSpace, kMSynchDocumentProxyThreadBoss, kWidgetPrefix + 138)
DECLARE_PMID(kClassIDSpace, kPopupPanelWrapperBoss, kWidgetPrefix + 139)
DECLARE_PMID(kClassIDSpace, kTextSizeMeasureComboBoxWidgetBoss, kWidgetPrefix + 141)
DECLARE_PMID(kClassIDSpace, kTextSizeMeasureEditBoxWidgetBoss, kWidgetPrefix + 142)
DECLARE_PMID(kClassIDSpace, kCreativeCloudButtonWidgetBoss, kWidgetPrefix + 143)
DECLARE_PMID(kClassIDSpace, kSelectableDialogActionBoss, kWidgetPrefix + 144)
DECLARE_PMID(kClassIDSpace, kModelessDialogActionBoss, kWidgetPrefix + 145)
DECLARE_PMID(kClassIDSpace, kCustomXMeasureEditBoxWidgetBoss, kWidgetPrefix + 146)
DECLARE_PMID(kClassIDSpace, kCustomYMeasureEditBoxWidgetBoss, kWidgetPrefix + 147)
DECLARE_PMID(kClassIDSpace, kCustomXMeasureSessionEditBoxWidgetBoss, kWidgetPrefix + 148)
DECLARE_PMID(kClassIDSpace, kCustomYMeasureSessionEditBoxWidgetBoss, kWidgetPrefix + 149)

DECLARE_PMID(kClassIDSpace, kKitPanelWidgetBoss, kWidgetPrefix + 150) // If you have a different PanelDetailController that SimplePanelDetailController, use kDetailKitPanelWidgetBoss
DECLARE_PMID(kClassIDSpace, kKitMenuWidgetBoss, kWidgetPrefix + 151)
DECLARE_PMID(kClassIDSpace, kTextTypeaheadComboBoxEditBoxWidgetBoss, kWidgetPrefix + 152)
DECLARE_PMID(kClassIDSpace, kEyeballCheckboxBoss, kWidgetPrefix + 153)
DECLARE_PMID(kClassIDSpace, kControlSetBoss, kWidgetPrefix + 154)
DECLARE_PMID(kClassIDSpace, kKitViewHorzBoss, kWidgetPrefix + 155)
DECLARE_PMID(kClassIDSpace, kKitViewVertBoss, kWidgetPrefix + 156)
DECLARE_PMID(kClassIDSpace, kKitDragWidgetBoss, kWidgetPrefix + 157)
DECLARE_PMID(kClassIDSpace, kBusinessUIStartupShutdownBoss, kWidgetPrefix + 158)
DECLARE_PMID(kClassIDSpace, kHyperlinkTextWidgetBoss, kWidgetPrefix + 159)
DECLARE_PMID(kClassIDSpace, kRollOverIconButtonBoss, kWidgetPrefix + 160)
DECLARE_PMID(kClassIDSpace, kOwnerDrawDDListWidgetBoss, kWidgetPrefix + 161)
DECLARE_PMID(kClassIDSpace, kControlStripWidgetBoss, kWidgetPrefix + 162)
DECLARE_PMID(kClassIDSpace, kComboBoxSliderWidgetBoss, kWidgetPrefix + 163)
DECLARE_PMID(kClassIDSpace, kGoURLHyperlinkTextWidgetBoss, kWidgetPrefix + 164)
DECLARE_PMID(kClassIDSpace, kPopupSliderBoss, kWidgetPrefix + 165)
DECLARE_PMID(kClassIDSpace, kPopupSliderComboBoxWidgetBoss, kWidgetPrefix + 166)
DECLARE_PMID(kClassIDSpace, kRealPopupSliderComboWidgetBoss, kWidgetPrefix + 167)
DECLARE_PMID(kClassIDSpace, kIntPopupSliderComboWidgetBoss, kWidgetPrefix + 168)
DECLARE_PMID(kClassIDSpace, kPercentPopupSliderComboWidgetBoss, kWidgetPrefix + 169)
DECLARE_PMID(kClassIDSpace, kStrokeTypePopupWidgetBoss, kWidgetPrefix + 170)
DECLARE_PMID(kClassIDSpace, kCntlMgrTabsWidgetBoss, kWidgetPrefix + 171)

DECLARE_PMID(kClassIDSpace, kTreeNodeWidgetBoss, kWidgetPrefix + 172)
DECLARE_PMID(kClassIDSpace, kTreeViewWidgetBoss, kWidgetPrefix + 173)
DECLARE_PMID(kClassIDSpace, kTreeExpanderWidgetBoss, kWidgetPrefix + 174)

DECLARE_PMID(kClassIDSpace, kTabSelectableDialogBoss, kWidgetPrefix + 175)
DECLARE_PMID(kClassIDSpace, kStrokeTypePopupElementWidgetBoss, kWidgetPrefix + 176)
DECLARE_PMID(kClassIDSpace, kNudgeOverrideComboBoxEditBoxWidgetBoss, kWidgetPrefix + 177)
DECLARE_PMID(kClassIDSpace, kPrintMeasureEditBoxWidgetBoss, kWidgetPrefix + 178)
DECLARE_PMID(kClassIDSpace, kDialogShortcutContextBoss, kWidgetPrefix + 179)
DECLARE_PMID(kClassIDSpace, kPopupPanelButtonBoss, kWidgetPrefix + 180)

#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.
DECLARE_PMID(kClassIDSpace, kStdListBoxWidgetNewBoss, kWidgetPrefix + 181)
DECLARE_PMID(kClassIDSpace, kWidgetListBoxWidgetNewBoss, kWidgetPrefix + 182)
#endif
DECLARE_PMID(kClassIDSpace, kShortcutEditBoxWidgetBoss, kWidgetPrefix + 183)
DECLARE_PMID(kClassIDSpace, kAutoPercentageComboBoxWidgetBoss, kWidgetPrefix + 184)
DECLARE_PMID(kClassIDSpace, kTreeViewScrollBarWidgetBoss, kWidgetPrefix + 185)

DECLARE_PMID(kClassIDSpace, kCellStrokeSelectionBoss, kWidgetPrefix + 186)
DECLARE_PMID(kClassIDSpace, kAutoLineWtMeasureComboBoxWidgetBoss, kWidgetPrefix + 187)
DECLARE_PMID(kClassIDSpace, kDropDownSelectableDialogBoss, kWidgetPrefix + 188 )
DECLARE_PMID(kClassIDSpace, kTreeScrollerWidgetBoss, kWidgetPrefix + 189 )
DECLARE_PMID(kClassIDSpace, kKitViewTabPanelBoss, kWidgetPrefix + 190 )
DECLARE_PMID(kClassIDSpace, kListTreeViewWidgetBoss, kWidgetPrefix + 191 )
DECLARE_PMID(kClassIDSpace, kListTreeScrollerWidgetBoss, kWidgetPrefix + 192 )
DECLARE_PMID(kClassIDSpace, kInfoStaticTextMeasurementWidgetBoss, kWidgetPrefix + 193 )
DECLARE_PMID(kClassIDSpace, kInfoStaticTextXMeasurementWidgetBoss, kWidgetPrefix + 194 )
DECLARE_PMID(kClassIDSpace, kInfoStaticTextYMeasurementWidgetBoss, kWidgetPrefix + 195 )
DECLARE_PMID(kClassIDSpace, kInfoStaticTextAngleWidgetBoss, kWidgetPrefix + 196 )
DECLARE_PMID(kClassIDSpace, kIconSuitePopupWidgetBoss, kWidgetPrefix + 197 )
DECLARE_PMID(kClassIDSpace, kInfoStaticTextPercentageWidgetBoss, kWidgetPrefix + 198 )
DECLARE_PMID(kClassIDSpace, kGenericInfoPanelWidgetBoss, kWidgetPrefix + 199 )
DECLARE_PMID(kClassIDSpace, kDetailKitPanelWidgetBoss, kWidgetPrefix + 200 )  // Use this if you have a different PanelDetailController than SimplePanelDetailController
DECLARE_PMID(kClassIDSpace, kKitViewTabPanelWithDetailBoss, kWidgetPrefix + 201 )
DECLARE_PMID(kClassIDSpace, kIgnoreColorSelection, kWidgetPrefix + 202 )
DECLARE_PMID(kClassIDSpace, kSplitterBarWidgetBoss, kWidgetPrefix + 203 )

// ---- Moved from Graphic Styles plug-in
DECLARE_PMID(kClassIDSpace, kStrokeFillIconFieldWidgetBoss, kWidgetPrefix + 204)
// ---- end move.

DECLARE_PMID(kClassIDSpace, kLineEndPopupBoss, kWidgetPrefix + 205)
DECLARE_PMID(kClassIDSpace, kPathEndStrokerWidgetBoss, kWidgetPrefix + 206)
DECLARE_PMID(kClassIDSpace, kCornerEffectPopupBoss, kWidgetPrefix + 207)
DECLARE_PMID(kClassIDSpace, kNudgeComboBoxWidgetBoss, kWidgetPrefix + 208)
DECLARE_PMID(kClassIDSpace, kEmptyDragDropCommandBoss, kWidgetPrefix + 209)
DECLARE_PMID(kClassIDSpace, kPanelWithRolloverFocusWidgetBoss, kWidgetPrefix + 210)
DECLARE_PMID(kClassIDSpace, kDropDesktopFileCmdBoss, kWidgetPrefix + 211)

DECLARE_PMID(kClassIDSpace, kLoadStyleSplitterWidgetBoss, kWidgetPrefix + 212)   //added by sasatte
DECLARE_PMID(kClassIDSpace, kLoadStyleListElementWidgetBoss, kWidgetPrefix + 213)   //added by sasatte
DECLARE_PMID(kClassIDSpace, kLoadStyleListWidgetBoss, kWidgetPrefix + 214)   //added by sasatte
DECLARE_PMID(kClassIDSpace, kLoadStyleInlineDropDownWidgetBoss, kWidgetPrefix + 215)   //added by sasatte
DECLARE_PMID(kClassIDSpace, kLoadStyleDropDownWidgetBoss, kWidgetPrefix + 216)   //added by sasatte
DECLARE_PMID(kClassIDSpace, kLoadStyleDropDownElementWidgetBoss, kWidgetPrefix + 217) 
DECLARE_PMID(kClassIDSpace, kLoadStyleSplitterPanelwidgetBoss, kWidgetPrefix + 218) 
DECLARE_PMID(kClassIDSpace, kGroupButtonFocusPanelBoss, kWidgetPrefix + 219) 
DECLARE_PMID(kClassIDSpace, kClusterButtonFocusPanelBoss, kWidgetPrefix + 220) 
DECLARE_PMID(kClassIDSpace, kInfoFittedStaticTextWidgetBoss, kWidgetPrefix + 221) 
DECLARE_PMID(kClassIDSpace, kKillerFindButtonBoss, kWidgetPrefix + 222)
DECLARE_PMID(kClassIDSpace, kPageRangeComboBoxDropDownWidgetBoss, kWidgetPrefix + 223)
DECLARE_PMID(kClassIDSpace, kTouchDropDownListWidgetBoss, kWidgetPrefix + 224)
DECLARE_PMID(kClassIDSpace, kPlacePageNumberWidgetBoss, kWidgetPrefix + 225)
DECLARE_PMID(kClassIDSpace, kTreeBasedListBoxWidgetNewBoss, kWidgetPrefix + 226)
DECLARE_PMID(kClassIDSpace, kTreeBasedListBoxNodeWidgetBoss, kWidgetPrefix + 227)
DECLARE_PMID(kClassIDSpace, kTreeBasedViewListBoxWidgetBoss, kWidgetPrefix + 228)
DECLARE_PMID(kClassIDSpace, kTouchPanelEmbeddedWindowContainerBoss, kWidgetPrefix + 229)
DECLARE_PMID(kClassIDSpace, kTypeaheadCBDDWithSubMenusWidgetBoss, kWidgetPrefix + 230)
DECLARE_PMID(kClassIDSpace, kStyleGroupDropDownWidgetBoss, kWidgetPrefix + 232)
DECLARE_PMID(kClassIDSpace, kStyleGroupDropDownElementWidgetBoss, kWidgetPrefix + 233)
DECLARE_PMID(kClassIDSpace, kRuleWidgetBoss, kWidgetPrefix + 234)
DECLARE_PMID(kClassIDSpace, kTouchPanelSubViewAdapterWidgetBoss, kWidgetPrefix + 235)
DECLARE_PMID(kClassIDSpace, kFlatButtonWidgetBoss, kWidgetPrefix + 236)
DECLARE_PMID(kClassIDSpace, kOwnerDrawStdListBoxNoSeparatorWidgetBoss, kWidgetPrefix + 237)
//gap
DECLARE_PMID(kClassIDSpace, kBasePalettePanelWidgetBoss, kWidgetPrefix + 241)
DECLARE_PMID(kClassIDSpace, kPageNumComboBoxWidgetBoss, kWidgetPrefix + 242)
DECLARE_PMID(kClassIDSpace, kPageNumComboBoxDropDownWidgetBoss, kWidgetPrefix + 243)
DECLARE_PMID(kClassIDSpace, kStyleGroupTreeViewBoss, kWidgetPrefix + 244)
DECLARE_PMID(kClassIDSpace, kStyleGroupTreeNodeBoss, kWidgetPrefix + 245)
//gap
DECLARE_PMID(kClassIDSpace, kLoadStyleMultiLineTextWidgetBoss, kWidgetPrefix + 248)
DECLARE_PMID(kClassIDSpace, kAnyStateSupportedRadioButtonWidgetBoss, kWidgetPrefix + 249)
DECLARE_PMID(kClassIDSpace, kAnyStateSupportedFittedRadioButtonWidgetBoss, kWidgetPrefix + 250)
DECLARE_PMID(kClassIDSpace, kGroupASSButtonFocusPanelBoss, kWidgetPrefix + 251)
DECLARE_PMID(kClassIDSpace, kDV_SliderWidgetBoss,kWidgetPrefix + 252)
DECLARE_PMID(kClassIDSpace, kIconEraseBackgroundSuiteWidgetBoss, kWidgetPrefix + 253)
DECLARE_PMID(kClassIDSpace, kColumnHeaderReorderChangeMsgBoss, kWidgetPrefix + 254) 
DECLARE_PMID(kClassIDSpace, kColumnHeaderWidgetBoss, kWidgetPrefix + 255)
DECLARE_PMID(kClassIDSpace, kTreeBasedListBoxSmallWidgetBoss, kWidgetPrefix + 256)
DECLARE_PMID(kClassIDSpace, kCornerEffectWidgetBoss, kWidgetPrefix + 257)
DECLARE_PMID(kClassIDSpace, kReleaseOWLCanvasDialogControllerCmdBoss, kWidgetPrefix + 258)
DECLARE_PMID(kClassIDSpace, kRollOverIconWithAttributesWidgetBoss, kWidgetPrefix + 259)
// Slider Widgets
DECLARE_PMID(kClassIDSpace,	kSliderILEWidgetBoss,				kWidgetPrefix + 260)
DECLARE_PMID(kClassIDSpace,	kSlideInlineStaticTextBoss,			kWidgetPrefix + 261)
DECLARE_PMID(kClassIDSpace,	kSliderInLineEditBoxWidgetBoss,		kWidgetPrefix + 262)
DECLARE_PMID(kClassIDSpace,	kSliderILEPercentWidgetBoss,		kWidgetPrefix + 263)
DECLARE_PMID(kClassIDSpace,	kSlideInlinePercentStaticTextBoss,	kWidgetPrefix + 264)
DECLARE_PMID(kClassIDSpace,	kSliderILEAngleWidgetBoss,			kWidgetPrefix + 265)

DECLARE_PMID(kClassIDSpace,	kSlideInlineAngleStaticTextBoss,	kWidgetPrefix + 266)
DECLARE_PMID(kClassIDSpace,	kStyleGroupComboBoxWidgetBoss,		kWidgetPrefix + 267)
DECLARE_PMID(kClassIDSpace,	kStyleGroupComboBoxDropDownWidgetBoss,		kWidgetPrefix + 268)
DECLARE_PMID(kClassIDSpace,	kStyleGroupComboBoxEditBoxWdigetBoss,		kWidgetPrefix + 269)
DECLARE_PMID(kClassIDSpace,	kSearchableTextEditBoxBoss,		kWidgetPrefix + 270)
DECLARE_PMID(kClassIDSpace,	kAGMOwnerDrawnStaticTextWidgetBoss,	kWidgetPrefix + 271)
DECLARE_PMID(kClassIDSpace,	kAGMStaticMultiLineTextWidgetBoss,	kWidgetPrefix + 272)
DECLARE_PMID(kClassIDSpace,	kTabsWidgetBoss,	kWidgetPrefix + 273)
DECLARE_PMID(kClassIDSpace, kButtonBarWidgetBoss, kWidgetPrefix + 274)
DECLARE_PMID(kClassIDSpace, kSpinningIconWidgetBoss, kWidgetPrefix + 275)
DECLARE_PMID(kClassIDSpace, kDesktopColorSamplerIconButtonBoss,		kWidgetPrefix + 276)
DECLARE_PMID(kClassIDSpace, kDesktopColorSamplerTrackerRegisterBoss,	kWidgetPrefix + 277)
DECLARE_PMID(kClassIDSpace, kDesktopColorSamplerTrackerBoss,			kWidgetPrefix + 278)
//gap
DECLARE_PMID(kClassIDSpace, kSearchablePopupTextEditBoxBoss,			kWidgetPrefix + 282)
DECLARE_PMID(kClassIDSpace, kRoundedRampWidgetBoss,					kWidgetPrefix + 283)
DECLARE_PMID(kClassIDSpace, kColorHSBSelectorWidgetBoss,			kWidgetPrefix + 284)
DECLARE_PMID(kClassIDSpace, kRGBColorEditorWidgetBoss,				kWidgetPrefix + 285)
DECLARE_PMID(kClassIDSpace, kCMYKColorEditorWidgetBoss,				kWidgetPrefix + 286)
DECLARE_PMID(kClassIDSpace, kTouchNudgeControlWidgetBoss,			kWidgetPrefix + 287)
DECLARE_PMID(kClassIDSpace, kTouchCustomXMeasureEditBoxWidgetBoss,	kWidgetPrefix + 288)
DECLARE_PMID(kClassIDSpace, kTouchCustomYMeasureEditBoxWidgetBoss,	kWidgetPrefix + 289)
DECLARE_PMID(kClassIDSpace, kToggleWidgetBoss,						kWidgetPrefix + 290)
DECLARE_PMID(kClassIDSpace, kPopupWindowBoss,						kWidgetPrefix + 291)
DECLARE_PMID(kClassIDSpace, kPopupWindowDialogBoss,					kWidgetPrefix + 292)
DECLARE_PMID(kClassIDSpace, kButtonBarGenericWidgetBoss,			kWidgetPrefix + 293)
DECLARE_PMID(kClassIDSpace, kButtonBarItemBoss,						kWidgetPrefix + 294)
DECLARE_PMID(kClassIDSpace, kTouchIntEditBoxWidgetBoss,				kWidgetPrefix + 295)
DECLARE_PMID(kClassIDSpace, kAddToCCLibraryPanelWidgetBoss,			kWidgetPrefix + 296)

DECLARE_PMID(kClassIDSpace, kUIBrightnessButtonWidgetBoss,			kWidgetPrefix + 297)
DECLARE_PMID(kClassIDSpace, kClusterButtonCommitFocusPanelBoss,		kWidgetPrefix + 298)
DECLARE_PMID(kClassIDSpace, kGenericPanelWithCustomBorderWidgetBoss, kWidgetPrefix + 299)

DECLARE_PMID(kClassIDSpace, kGenericPanelWidgetWithEHGettingRemovedFlagBoss, kWidgetPrefix + 300)
DECLARE_PMID(kClassIDSpace, kPropertiesPanelQuickActionButtonWidgetBoss, kWidgetPrefix + 301)
DECLARE_PMID(kClassIDSpace, kClickableTextWidgetBoss, kWidgetPrefix + 302)
DECLARE_PMID(kClassIDSpace, kPropsPanelClickableTextWidgetBoss, kWidgetPrefix + 303)
DECLARE_PMID(kClassIDSpace, kScalingWidgetTrackerRegisterBoss, kWidgetPrefix + 304)
DECLARE_PMID(kClassIDSpace, kScalingWidgetTrackerBoss, kWidgetPrefix + 305)
DECLARE_PMID(kClassIDSpace, kScalingWidgetBoss, kWidgetPrefix + 306)
DECLARE_PMID(kClassIDSpace, kPopupTextWidgetBoss, kWidgetPrefix + 307)
DECLARE_PMID(kClassIDSpace, kPropsPanelButtonBarGenericWidgetBoss, kWidgetPrefix + 308)
DECLARE_PMID(kClassIDSpace, kRectangularButtonWidgetBoss, kWidgetPrefix + 309)
DECLARE_PMID(kClassIDSpace, kIconSuiteWidgetWithClickBoss, kWidgetPrefix + 310)
DECLARE_PMID(kClassIDSpace, kRectangularButtonWidgetWithActionBoss, kWidgetPrefix + 311)
DECLARE_PMID(kClassIDSpace, kRectangularButtonWidgetWithObserverBoss, kWidgetPrefix + 312)
DECLARE_PMID(kClassIDSpace, kTreeBasedDropDownListWidgetBoss, kWidgetPrefix + 313)
DECLARE_PMID(kClassIDSpace, kTreeBasedPopupTextEditBoxBoss, kWidgetPrefix + 314)
DECLARE_PMID(kClassIDSpace, kGenericPanelCustomColorWidgetBoss, kWidgetPrefix + 315)
DECLARE_PMID(kClassIDSpace, kFlatButtonBorderWidgetBoss, kWidgetPrefix + 316)
DECLARE_PMID(kClassIDSpace, kFontSizeLimitObserverBoss, kWidgetPrefix + 317)
DECLARE_PMID(kClassIDSpace, kCustomWidthMeasureEditBoxWidgetBoss, kWidgetPrefix + 318)
DECLARE_PMID(kClassIDSpace, kCustomHeightMeasureEditBoxWidgetBoss, kWidgetPrefix + 319)
DECLARE_PMID(kClassIDSpace, kCustomMarginXMeasureSessionEditBoxWidgetBoss, kWidgetPrefix + 320)
DECLARE_PMID(kClassIDSpace, kCustomMarginYMeasureSessionEditBoxWidgetBoss, kWidgetPrefix + 321)
DECLARE_PMID(kClassIDSpace, kGIFPlayerWidgetBoss, kWidgetPrefix + 322)
DECLARE_PMID(kClassIDSpace, kDialogOnHyperlinkWidgetBoss, kWidgetPrefix + 323)
DECLARE_PMID(kClassIDSpace, kTaskProgressBarWidgetBoss, kWidgetPrefix + 324)




// NOTE: For kClassIDSpace additions, you can go up to kWidgetPrefix + 355
// because there are two prefixes for Widgets. Part of the second Widget prefix is already used for MessageIDs below.

//========================================================================================
// <Message ID>
// ----- Message IDs -----
// Messages sent by various Data Objects
// -- these are ClassIDs but have no classes!
// -- they are only used for sending messages
//========================================================================================

// DECLARE_PMID(kMessageIDSpace, kUnusedMessage, kWidgetPrefix + 356)	// NOTE: In our second prefix (0x0700)!
	// Messages sent by CounterControlData
DECLARE_PMID(kMessageIDSpace, kBeginLowResScrollMessage, kWidgetPrefix + 357)
DECLARE_PMID(kMessageIDSpace, kEndLowResScrollMessage, kWidgetPrefix + 358)

	// Messages sent by CBooleanControlData
DECLARE_PMID(kMessageIDSpace, kFalseStateMessage, kWidgetPrefix + 359)
DECLARE_PMID(kMessageIDSpace, kTrueStateMessage, kWidgetPrefix + 360)
DECLARE_PMID(kMessageIDSpace, kUnknownStateMessage, kWidgetPrefix + 361		/* for tri-state checkboxes/radio buttons */)

	// Messages sent by CounterControlData
DECLARE_PMID(kMessageIDSpace, kCounterChangeStateMessage, kWidgetPrefix + 362)

	// Messages sent by listboxes control data
#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.
DECLARE_PMID(kMessageIDSpace, kListSelectionChangedMessage, kWidgetPrefix + 363)
DECLARE_PMID(kMessageIDSpace, kListSelectionChangedByUserMessage, kWidgetPrefix + 364)
DECLARE_PMID(kMessageIDSpace, kMasterItemChangedMessage, kWidgetPrefix + 365)
DECLARE_PMID(kMessageIDSpace, kListItemAddedMessage, kWidgetPrefix + 366)
DECLARE_PMID(kMessageIDSpace, kListItemRemovedMessage, kWidgetPrefix + 367)
DECLARE_PMID(kMessageIDSpace, kListItemContentsChangedMessage, kWidgetPrefix + 368)
#endif
	// MeSssages sent by CPanelControlData
DECLARE_PMID(kMessageIDSpace, kPanelChangedMessage, kWidgetPrefix + 369)

	// Messages sent by CIntegerControlData
DECLARE_PMID(kMessageIDSpace, kIntegerChangeStateMessage, kWidgetPrefix + 370)

	// Messages sent by CRealNumberControlData
DECLARE_PMID(kMessageIDSpace, kRealChangeStateMessage, kWidgetPrefix + 371)

	// Messages sent by CTextControlData
DECLARE_PMID(kMessageIDSpace, kTextChangeStateMessage, kWidgetPrefix + 372)

	// Messages sent by PopupControlData
DECLARE_PMID(kMessageIDSpace, kPopupChangeStateMessage, kWidgetPrefix + 373)

	// Messages sent by NudgeButton
DECLARE_PMID(kMessageIDSpace, kSmallNudgeUpMessage, kWidgetPrefix + 374)
DECLARE_PMID(kMessageIDSpace, kLargeNudgeUpMessage, kWidgetPrefix + 375)
DECLARE_PMID(kMessageIDSpace, kSmallNudgeDownMessage, kWidgetPrefix + 376)
DECLARE_PMID(kMessageIDSpace, kLargeNudgeDownMessage, kWidgetPrefix + 377)
DECLARE_PMID(kMessageIDSpace, kStartNudgeMessage, kWidgetPrefix + 378)
DECLARE_PMID(kMessageIDSpace, kEndNudgeMessage, kWidgetPrefix + 379)

	// Messages sent out by widgets when their geometry changes. Children
	// are notified of changes in their parent's size by the ParentResized
	// method.
DECLARE_PMID(kMessageIDSpace, kWidgetSizeChangedMessage, kWidgetPrefix + 380)
DECLARE_PMID(kMessageIDSpace, kWidgetPositionChangedMessage, kWidgetPrefix + 381)

	// Messages sent by StrokeFillWidget
DECLARE_PMID(kMessageIDSpace, kWidgetFillActiveMessage, kWidgetPrefix + 382)
DECLARE_PMID(kMessageIDSpace, kWidgetStrokeActiveMessage, kWidgetPrefix + 383)
// I used kWidgetPrefix + 329 up above in the listbox messages

	// Messages sent by uidlistcontroldata
DECLARE_PMID(kMessageIDSpace, kUIDListItemAddedMessage, kWidgetPrefix + 384)
DECLARE_PMID(kMessageIDSpace, kUIDListItemRemovedMessage, kWidgetPrefix + 385)
DECLARE_PMID(kMessageIDSpace, kUIDListClearedMessage, kWidgetPrefix + 386)

DECLARE_PMID(kMessageIDSpace, kSplitterTrackerRegisterBossMessage, kWidgetPrefix + 387)
DECLARE_PMID(kMessageIDSpace, kSplitterTrackerBossMessage, kWidgetPrefix + 388)
DECLARE_PMID(kMessageIDSpace, kSelectedTabChangedMessage, kWidgetPrefix + 389)
DECLARE_PMID(kMessageIDSpace, kToggleTreeViewExpansionMessage, kWidgetPrefix + 390)

	// Messages sent by ListBox
#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.
DECLARE_PMID(kMessageIDSpace, kListSelectionChangedByUserDragMessage, kWidgetPrefix + 391)
#endif

	// Messages sent by PopupSlider
DECLARE_PMID(kMessageIDSpace, kPopupSliderOpenMessage, kWidgetPrefix + 392)
DECLARE_PMID(kMessageIDSpace, kPopupSliderCloseMessage, kWidgetPrefix + 393)
DECLARE_PMID(kMessageIDSpace, kPopupSliderApplyChangeMessage, kWidgetPrefix + 394)

	// Messages sent by Editbox
DECLARE_PMID(kMessageIDSpace, kEditBoxKeyStrokeMessage, kWidgetPrefix + 395)
DECLARE_PMID(kMessageIDSpace, kEditBoxGetKeyFocusMessage, kWidgetPrefix + 396)
DECLARE_PMID(kMessageIDSpace, kEditBoxGiveUpKeyFocusMessage, kWidgetPrefix + 397)

	// Messages sent by TreeView
DECLARE_PMID(kMessageIDSpace, kTreeNodeExpandedMsg, kWidgetPrefix + 398)
DECLARE_PMID(kMessageIDSpace, kTreeNodeCollapsedMsg, kWidgetPrefix + 399)
	// Messages sent by InLineEdit
DECLARE_PMID(kMessageIDSpace, kInLineEditStartEditingMessageID,	kWidgetPrefix + 400)
DECLARE_PMID(kMessageIDSpace, kInLineEditStopEditingMessageID, kWidgetPrefix + 401)

DECLARE_PMID(kMessageIDSpace, kTreePlaceWidgetsMessage, kWidgetPrefix + 402)

DECLARE_PMID(kMessageIDSpace, kFinishedSettingupEventFilteringMsg, kWidgetPrefix + 403)
DECLARE_PMID(kMessageIDSpace, kSplitterPanelTrackerBossMessage, kWidgetPrefix + 404)

DECLARE_PMID(kMessageIDSpace, kSELECTED_OVERPRINTICON_MSG, kWidgetPrefix + 405 )
DECLARE_PMID(kMessageIDSpace, kUNSELECTED_OVERPRINTICON_MSG, kWidgetPrefix + 406 )
DECLARE_PMID(kMessageIDSpace, kMIXED_OVERPRINTICON_MSG, kWidgetPrefix + 407 )


DECLARE_PMID(kMessageIDSpace, kSPLITTER_TRACKERSTART_MSG, kWidgetPrefix + 408 )
DECLARE_PMID(kMessageIDSpace, kSPLITTER_TRACKERCONTINUE_MSG, kWidgetPrefix + 409 )
DECLARE_PMID(kMessageIDSpace, kSPLITTER_TRACKEREND_MSG, kWidgetPrefix + 410 )

// Messages sent by IID_ISTYLEGROUPLISTCONTROLDATA
DECLARE_PMID(kMessageIDSpace, kRebuildStyleGroupListMessage, kWidgetPrefix + 411 )
DECLARE_PMID(kMessageIDSpace, kCustomStyleGroupListMessage, kWidgetPrefix + 412 )

// Messages sent by IID_IPANORAMA
DECLARE_PMID(kMessageIDSpace, kScrollToMessage, kWidgetPrefix + 413 )
DECLARE_PMID(kMessageIDSpace, kScrollByMessage, kWidgetPrefix + 414 )
DECLARE_PMID(kMessageIDSpace, kScaleToMessage, kWidgetPrefix + 415 )
DECLARE_PMID(kMessageIDSpace, kScaleByMessage, kWidgetPrefix + 416 )
DECLARE_PMID(kMessageIDSpace, kBeforeScrollByMessage, kWidgetPrefix + 417 )

	// Messages sent by SplitterPanelControlData
DECLARE_PMID(kMessageIDSpace, kSplitterChangeStateMessage, kWidgetPrefix + 418)

	// Additional Messages sent by Editbox
DECLARE_PMID(kMessageIDSpace, kEditBoxPasteFromScrapMessage, kWidgetPrefix + 419)

DECLARE_PMID(kMessageIDSpace, kButtonChangedMessage, kWidgetPrefix + 420)

DECLARE_PMID(kMessageIDSpace, kSearchPolicyChangedMessage, kWidgetPrefix + 421)
DECLARE_PMID(kMessageIDSpace, kDesktopColorSampler_TrackerContinue_Msg, kWidgetPrefix + 422)

DECLARE_PMID(kMessageIDSpace, kColorChangeStateMessage, kWidgetPrefix + 423)

DECLARE_PMID(kMessageIDSpace, kBeginSliderChangeMessage, kWidgetPrefix + 424)
DECLARE_PMID(kMessageIDSpace, kEndSliderChangeMessage, kWidgetPrefix + 425)
DECLARE_PMID(kMessageIDSpace, kGoUrlClickEventMessage, kWidgetPrefix + 426)

// NOTE for additions to kMessageIDSpace: We are now in our second prefix (0x0700)! Hence the >255 offset. You can go up to 255*2 = 510


// <Interface ID>
//========================================================================================
// ----- Interface IDs -----
//========================================================================================

DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLVIEW, kWidgetPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOLEANCONTROLDATA, kWidgetPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTCONTROLDATA, kWidgetPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTCONTROLDATA, kWidgetPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTEGERCONTROLDATA, kWidgetPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IREALNUMBERCONTROLDATA, kWidgetPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELCONTROLDATA, kWidgetPrefix + 7)
#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTBOXATTRIBUTES, kWidgetPrefix + 8)
#endif
DECLARE_PMID(kInterfaceIDSpace, IID_IPROGRESSBARCONTROLDATA, kWidgetPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IOWNERDRAWITEM, kWidgetPrefix + 10)

DECLARE_PMID(kInterfaceIDSpace, IID_IWIDGETPARENT, kWidgetPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANEL, kWidgetPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELPTR, kWidgetPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOUNTERCONTROLDATA, kWidgetPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMENUWIDGETVIEW, kWidgetPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGEVENTFILTERDATA, kWidgetPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOG, kWidgetPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANORAMA, kWidgetPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCROLLBARPANORAMASYNC, kWidgetPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONOBSERVER, kWidgetPrefix + 20)

DECLARE_PMID(kInterfaceIDSpace, IID_ISPLITTERCURSORPROVIDER, kWidgetPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROGRESSBARDATA, kWidgetPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELMENUDATA, kWidgetPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELSERVICEDATA, kWidgetPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IWIDGETCREATOR, kWidgetPrefix + 25			/* generic pageitem widget */)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMCONTROLDATA, kWidgetPrefix + 26			/* generic pageitem widget */)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMOBSERVER, kWidgetPrefix + 27			/* generic pageitem widget */)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMFOCUS, kWidgetPrefix + 28			/* generic pageitem widget */)
DECLARE_PMID(kInterfaceIDSpace, IID_IZOOMCMDDATA, kWidgetPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLVIEWCMDDATA, kWidgetPrefix + 30)

DECLARE_PMID(kInterfaceIDSpace, IID_IADBE3DBUTTONCURSORPROVIDER, kWidgetPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRIDATTRIBUTES, kWidgetPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESIZERULE, kWidgetPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPDOWNLISTMAPPER, kWidgetPrefix + 34	)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORVIEWDATA, kWidgetPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEASURECLASSCONTROLDATA, kWidgetPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCKALTERNATEICONATTR, kWidgetPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IBUTTONATTRIBUTES, kWidgetPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IKEYFOCUSHANDLER, kWidgetPrefix + 39)
#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTBOXDETAILCONTROLLER, kWidgetPrefix + 40)
#endif

DECLARE_PMID(kInterfaceIDSpace, IID_ILISTVIEW, kWidgetPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGCONTROLLER, kWidgetPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRISTATECONTROLDATA, kWidgetPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTABLEDIALOGSWITCHER, kWidgetPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELCREATOR, kWidgetPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGCREATOR, kWidgetPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IEDITBOXATTRIBUTES, kWidgetPrefix + 47)

// IID_ILISTBOXCONTROLLER(& listboxes generally) will disappear from a future version of InDesign. Please use TreeViews instead.
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTBOXCONTROLLER, kWidgetPrefix + 48)

DECLARE_PMID(kInterfaceIDSpace, IID_IGROUPPANELATTRIBUTES, kWidgetPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMBOBOXOBSERVER, kWidgetPrefix + 50)

DECLARE_PMID(kInterfaceIDSpace, IID_INUDGEHANDLER, kWidgetPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_INUDGETHREAD, kWidgetPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IWIDGETREFDATA, kWidgetPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPDOWNLISTCONTROLLER, kWidgetPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGLISTCONTROLDATA, kWidgetPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTDATAVALIDATION, kWidgetPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTVALUE, kWidgetPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEASUREMENTSYSTEMOBSERVER, kWidgetPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_INUDGEOBSERVER, kWidgetPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEFILLCONTROLDATA, kWidgetPrefix + 60)

DECLARE_PMID(kInterfaceIDSpace, IID_IUIDLISTCONTROLDATA, kWidgetPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_ISLIDERCONTROLDATA, kWidgetPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_ISLIDERSTATEDATA, kWidgetPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMUNKNOWNREFLISTDATA, kWidgetPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEASUREMENTTYPE, kWidgetPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTVALIDTEXTCONTROLDATA, kWidgetPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_IOTHERENTRYDATA, kWidgetPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTATICTEXTLINEBREAKER, kWidgetPrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTATICMULTILINETEXTATTR, kWidgetPrefix + 69)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGSTEP, kWidgetPrefix + 70)

DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTUIDLISTVALUE, kWidgetPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELDETAILCONTROLLER, kWidgetPrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_ISIZEBOXCURSORPROVIDER, kWidgetPrefix + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESOURCESRCFILEINFO, kWidgetPrefix + 74)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLITTERCONTROLDATA, kWidgetPrefix + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLUSTERCONTROLLER, kWidgetPrefix + 76)
DECLARE_PMID(kInterfaceIDSpace, IID_PROXYWIDGETGETSFOCUSONSHORTCUT, kWidgetPrefix + 77)
DECLARE_PMID(kInterfaceIDSpace, IID_IALERTHANDLER, kWidgetPrefix + 78)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTATICTEXTATTRIBUTES, kWidgetPrefix + 79)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMBOBOXCALCULATEDVALUE, kWidgetPrefix + 80)

DECLARE_PMID(kInterfaceIDSpace, IID_ICELLWIDGETCONTROLLER, kWidgetPrefix + 81)
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLWIDGETFACTORY, kWidgetPrefix + 82)
DECLARE_PMID(kInterfaceIDSpace, IID_IWIDGETLISTBOXHELPER, kWidgetPrefix + 83	)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTSYSTEMCOLORCHANGETICK, kWidgetPrefix + 84)
DECLARE_PMID(kInterfaceIDSpace, IID_IWINDOWSIZEBOXALLOWRESIZE, kWidgetPrefix + 85)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIFONTSPEC, kWidgetPrefix + 86)
DECLARE_PMID(kInterfaceIDSpace, IID_IEDITBOXCURSORPROVIDER, kWidgetPrefix + 87)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOLDROPDOWNLISTSTRINGCHANGED, kWidgetPrefix + 88)
DECLARE_PMID(kInterfaceIDSpace, IID_IMULTILINETEXTOBSERVER, kWidgetPrefix + 89)
DECLARE_PMID(kInterfaceIDSpace, IID_IBREAKSTRINGDATA, kWidgetPrefix + 90)

DECLARE_PMID(kInterfaceIDSpace, IID_ITYPEAHEADNOTACTIVE, kWidgetPrefix + 91)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROXYWIDGETATTRIBUTES, kWidgetPrefix + 92)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEFILLMSGDATA, kWidgetPrefix + 93)
DECLARE_PMID(kInterfaceIDSpace, IID_IDDLSTRINGDATA, kWidgetPrefix + 94)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREVIEWDIALOGERRORHANDLER, kWidgetPrefix + 95 )
DECLARE_PMID(kInterfaceIDSpace, IID_IVIEWSELECTION, kWidgetPrefix + 96)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOUSEROLLOVER, kWidgetPrefix + 97)
DECLARE_PMID(kInterfaceIDSpace, IID_IKIT, kWidgetPrefix + 98)
DECLARE_PMID(kInterfaceIDSpace, IID_IKITREGISTER, kWidgetPrefix + 99)
DECLARE_PMID(kInterfaceIDSpace, IID_IKITDRAGTARGET, kWidgetPrefix + 100)

DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEGROUPOBSERVER, kWidgetPrefix + 101)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKERKEYDATA, kWidgetPrefix + 102)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLVIEWOBSERVERS, kWidgetPrefix + 103)
DECLARE_PMID(kInterfaceIDSpace, IID_ISORTDATA, kWidgetPrefix + 104)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEATTRIBUTES, kWidgetPrefix + 105)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEVIEWCONTROLLER, kWidgetPrefix + 106)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEVIEWMGR, kWidgetPrefix + 107)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUREFDATA, kWidgetPrefix + 108)
DECLARE_PMID(kInterfaceIDSpace, IID_IDISABLEMULTIBYTESCRIPT, kWidgetPrefix + 109)
DECLARE_PMID(kInterfaceIDSpace, IID_IUICOLORSPEC, kWidgetPrefix + 110)

DECLARE_PMID(kInterfaceIDSpace, IID_IEXPANDEROBSERVER, kWidgetPrefix + 111)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREESCROLLOBSERVER, kWidgetPrefix + 112)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREENODEIDDATA, kWidgetPrefix + 113)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEVIEWWIDGETMGR, kWidgetPrefix + 114)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEVIEWHIERARCHYADAPTER, kWidgetPrefix + 115)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREVIEWCONTROLDATA, kWidgetPrefix + 116)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSOCIATEDWIDGETATTRIBUTES, kWidgetPrefix + 117)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRUNCATEDSTATICNAME, kWidgetPrefix + 118)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMBOBOXATTRIBUTES, kWidgetPrefix + 119)

// Table Stroke Selection Widget
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKESELECTATTRIBUTES, kWidgetPrefix + 120)
DECLARE_PMID(kInterfaceIDSpace, IID_IICONSTYLEATTRIBUTES, kWidgetPrefix + 121)
DECLARE_PMID(kInterfaceIDSpace, IID_IISFILLDATA, kWidgetPrefix + 122)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORKEWIDGET_OBSERVER, kWidgetPrefix + 123)
DECLARE_PMID(kInterfaceIDSpace, IID_IVALIDATECONTENTS, kWidgetPrefix + 124 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITRISTATECONTROLATTRIBUTES, kWidgetPrefix + 125)
DECLARE_PMID(kInterfaceIDSpace, IID_IACCELERATECONTROLDATA, kWidgetPrefix + 126 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPANELMOVER, kWidgetPrefix + 127 )
DECLARE_PMID(kInterfaceIDSpace, IID_IWIDGETUTILS, kWidgetPrefix + 128 )
DECLARE_PMID(kInterfaceIDSpace, IID_IWINDOWUTILS, kWidgetPrefix + 129 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPALETTEPANELUTILS, kWidgetPrefix + 130 )

DECLARE_PMID(kInterfaceIDSpace, IID_IPNGBUTTONCONTROLVIEW, kWidgetPrefix + 131 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEEXPANDEROPTIONS, kWidgetPrefix + 132 )
DECLARE_PMID(kInterfaceIDSpace, IID_IVERTICALSPLITTERCURSORPROVIDER, kWidgetPrefix + 133 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICERASEBEFOREDRAWFLAG, kWidgetPrefix + 134 )
DECLARE_PMID(kInterfaceIDSpace, IID_IWIDGETIDDATA, kWidgetPrefix + 135 )
DECLARE_PMID(kInterfaceIDSpace, IID_IXLOCWIDGETIDDATA, kWidgetPrefix + 136 )
DECLARE_PMID(kInterfaceIDSpace, IID_IYLOCWIDGETIDDATA, kWidgetPrefix + 137 )
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOLISDROPDOWNOPEN, kWidgetPrefix + 138 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPNGICONATTRIBUTES, kWidgetPrefix + 139 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPDOWNTYPEAHEAD, kWidgetPrefix + 140 )

DECLARE_PMID(kInterfaceIDSpace, IID_IINLINEEDITWIDGETATTRIBUTES, kWidgetPrefix + 141)
DECLARE_PMID(kInterfaceIDSpace, IID_IINLINEEDITCONTROLLER, kWidgetPrefix + 142)
DECLARE_PMID(kInterfaceIDSpace, IID_IINLINEEDITEDITINGATTRIBUTES, kWidgetPrefix + 143)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABSHAPEUTILS, kWidgetPrefix + 144 )
DECLARE_PMID(kInterfaceIDSpace, IID_IWINXPTHEME, kWidgetPrefix + 145 )
DECLARE_PMID(kInterfaceIDSpace, IID_IINLINEEDITCURSORPROVIDER, kWidgetPrefix + 146 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKETYPELISTCONTROLDATA, kWidgetPrefix + 147 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGENAMESTYLEDATA, kWidgetPrefix + 148)
DECLARE_PMID(kInterfaceIDSpace, IID_IAMBIGUOUSPAGE, kWidgetPrefix + 149 )
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDWIDGETATTRIBUTES, kWidgetPrefix + 150 )

#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTBOXDRAWFOCUSRING, kWidgetPrefix + 151 )
#endif
DECLARE_PMID(kInterfaceIDSpace, IID_IMOUSEROLLOVERINVAL, kWidgetPrefix + 152 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEVIEWTYPEAHEAD, kWidgetPrefix + 153 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORLISTCONTROLDATA, kWidgetPrefix + 154 )
DECLARE_PMID(kInterfaceIDSpace, IID_IISLASTCHANGEVALID, kWidgetPrefix + 155 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPOPUPPANELWIDGETATTRIBUTES, kWidgetPrefix + 156 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISMALLPALETTEROWSBOOLDATA, kWidgetPrefix + 157 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPOPUPCLASSIDVALUE, kWidgetPrefix + 158 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLITTERPANELCONTROLDATA, kWidgetPrefix + 159 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLITTERPANELCONTROLLER, kWidgetPrefix + 160 )

DECLARE_PMID(kInterfaceIDSpace, IID_IMULTIRESOURCE, kWidgetPrefix + 161 )
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDSPLITTERPANELCONTROLDATA, kWidgetPrefix + 162 )
DECLARE_PMID(kInterfaceIDSpace, IID_INODECHANGEDMESSAGE, kWidgetPrefix + 163 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPOPUPCLASSWIDGETCONTROLDATA, kWidgetPrefix + 164 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHESPANELATTRIBUTES, kWidgetPrefix + 165)
DECLARE_PMID(kInterfaceIDSpace, IID_IOWNERDRAWMENU, kWidgetPrefix + 166 )
DECLARE_PMID(kInterfaceIDSpace, IID_IGROUPBUTTONFOCUSDATA, kWidgetPrefix + 167 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLTOGGLEBEHAVIOR, kWidgetPrefix + 168 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLITTERPANELCURSORPROVIDER, kWidgetPrefix + 169)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEGROUPLISTCONTROLDATA, kWidgetPrefix + 170 )

DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEGROUPDROPDOWNELEMENTDATA, kWidgetPrefix + 171 )
DECLARE_PMID(kInterfaceIDSpace, IID_IALTPOPUPPANELWIDGETATTRIBUTES, kWidgetPrefix + 172 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTEDUIDDATA, kWidgetPrefix + 173 )
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICFINDLISTDATA, kWidgetPrefix + 174 )
DECLARE_PMID(kInterfaceIDSpace, IID_IKILLERFINDLISTDATA, kWidgetPrefix + 175 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPLATFORMPANELVIEWREF, kWidgetPrefix + 176)
DECLARE_PMID(kInterfaceIDSpace, IID_IMKDDLISTCONTROLDATA, kWidgetPrefix + 177 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJSTYLESASSOCIATEDCATEGORIESDATA, kWidgetPrefix + 178 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICATEGORYREALNUMBERDATA, kWidgetPrefix + 179 )
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUVISIBILITYTEXTDATA, kWidgetPrefix + 180 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICATEGORYNAMETEXTDATA, kWidgetPrefix + 181 )
DECLARE_PMID(kInterfaceIDSpace, IID_IFORCEACCEPTENTERKEY,	kWidgetPrefix + 182 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJSTYLESSELECTABLEPANELINFODATA, kWidgetPrefix + 183 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLUMNHEADERPANELDATA, kWidgetPrefix + 184)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLUMNHEADERATTRIBUTES, kWidgetPrefix + 185 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLUMNHEADERDROPINDEX, kWidgetPrefix + 186 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLUMNHEADERMOUSEUPNOTIFY, kWidgetPrefix + 187 )
DECLARE_PMID(kInterfaceIDSpace, IID_IUSETHEMECOLORS, kWidgetPrefix + 188)
DECLARE_PMID(kInterfaceIDSpace, IID_PREVENT_BUILTIN_EDITBOX_SHORTCUT_HANDLING, kWidgetPrefix + 189)
DECLARE_PMID(kInterfaceIDSpace, IID_ISEARCHABLEFONTMENUOBSERVER, kWidgetPrefix + 190)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMRSRCIDLISTDATA, kWidgetPrefix + 191)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWLINEBOOLDATA, kWidgetPrefix + 192)
DECLARE_PMID(kInterfaceIDSpace, IID_ISLIDERINLINERANGECONTROLDATA, kWidgetPrefix + 193 )
DECLARE_PMID(kInterfaceIDSpace, IID_IREQUIRESROLLBACK, kWidgetPrefix + 194 )
DECLARE_PMID(kInterfaceIDSpace, IID_IKEYFOCUSDELEGATE, kWidgetPrefix + 195 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGPRIVATEUTILS, kWidgetPrefix + 196)
DECLARE_PMID(kInterfaceIDSpace, IID_IRELINQUISHFOCUSSTATUS, kWidgetPrefix + 197)
DECLARE_PMID(kInterfaceIDSpace, IID_IVALIDATEKEYFOCUS, kWidgetPrefix + 198)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDITBOXVALIDATIONSTATUS, kWidgetPrefix + 199)
DECLARE_PMID(kInterfaceIDSpace, IID_IEDITBOXWANTSMOUSEEVENTS, kWidgetPrefix + 200)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITINGAWAREPANEL, kWidgetPrefix + 201 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDISABLESTYLEGROUP,		kWidgetPrefix + 202 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPDOWNLISTOPENCLOSEHANDLER,  kWidgetPrefix + 203 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGLISTBOXNODEWIDTH,  kWidgetPrefix + 204 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITABSWIDGETOBSERVER,  kWidgetPrefix + 205 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPOPUPPANELWINDOW,  kWidgetPrefix + 206 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPRECHILDEVENTHANDLING,  kWidgetPrefix + 207 )
DECLARE_PMID(kInterfaceIDSpace, IID_IIGNORECHILDINCLUSTER,  kWidgetPrefix + 208 ) // use for child widgets which do not want to participate in cluster panel widget
DECLARE_PMID(kInterfaceIDSpace, IID_ICANICONEXCEEDWIDGET,  kWidgetPrefix + 209 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMITFONTCHANGES,  kWidgetPrefix + 210 )
DECLARE_PMID(kInterfaceIDSpace, IID_IURLCONTROLDATA, kWidgetPrefix + 211)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOINTYHANDCURSORPROVIDER, kWidgetPrefix + 212)
DECLARE_PMID(kInterfaceIDSpace, IID_IDISABLEDUICOLORSPEC, kWidgetPrefix + 213)
DECLARE_PMID(kInterfaceIDSpace, IID_IHASPOPUP, kWidgetPrefix + 214)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOGGLEMODEDEFAULT, kWidgetPrefix + 215)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOGLEMODETOGGLED, kWidgetPrefix + 216)
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERRIDDENEVENTHANDLER, kWidgetPrefix + 217)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOSITIONINGHELPER, kWidgetPrefix + 218)
DECLARE_PMID(kInterfaceIDSpace, IID_IRELAYOUTDIALOG, kWidgetPrefix + 219)
DECLARE_PMID(kInterfaceIDSpace, IID_IINVOKEDFROMPALETTE, kWidgetPrefix + 220)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWONLEFT, kWidgetPrefix + 221)
DECLARE_PMID(kInterfaceIDSpace, IID_IISARROWTOBEDRAWNONRIGHT, kWidgetPrefix + 222)
DECLARE_PMID(kInterfaceIDSpace, IID_IBUTTONBARITEM, kWidgetPrefix + 223)
DECLARE_PMID(kInterfaceIDSpace, IID_IBUTTONBARCONTROLDATA,	kWidgetPrefix + 224)
DECLARE_PMID(kInterfaceIDSpace, IID_IBUTTONBARATTRIBUTES,	kWidgetPrefix + 225)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTEDUICOLORSPEC, kWidgetPrefix + 226)
DECLARE_PMID(kInterfaceIDSpace, IID_IROUNDINGRADIUS, kWidgetPrefix + 227)
DECLARE_PMID(kInterfaceIDSpace, IID_IREGISTERTEXTEDITCALLBACKS, kWidgetPrefix + 228)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOPUPSTROKECOLOR, kWidgetPrefix + 229)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOPUPWINDOWHASDROPSHADOW, kWidgetPrefix + 230)
DECLARE_PMID(kInterfaceIDSpace, IID_IADD_START_END_PADDING, kWidgetPrefix + 231)
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTBOXBOTTOMINSETFLAG, kWidgetPrefix + 232)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWINGFOCUSRECT, kWidgetPrefix + 233)
DECLARE_PMID(kInterfaceIDSpace, IID_IGROUPBORDERBINDINGTORESTORE, kWidgetPrefix + 234)
DECLARE_PMID(kInterfaceIDSpace, IID_IGROUPBORDER_KEEPHALF_GAP, kWidgetPrefix + 235)
DECLARE_PMID(kInterfaceIDSpace, IID_ISLIDERTICKCOUNTDATA, kWidgetPrefix + 236)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMITFOCUSCHANGE, kWidgetPrefix + 237)
DECLARE_PMID(kInterfaceIDSpace, IID_IBORDERCONTROLATTRIBUTES, kWidgetPrefix + 238)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWNODESEPARATOR, kWidgetPrefix + 239)
DECLARE_PMID(kInterfaceIDSpace, IID_ICANHIDESCROLLBAR, kWidgetPrefix + 240)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONWIDGETDATA, kWidgetPrefix + 241)
DECLARE_PMID(kInterfaceIDSpace, IID_IQUICKACTIONBUTTONATTRIBUTES, kWidgetPrefix + 242)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIALOGPOPUPATTRIBUTES, kWidgetPrefix + 243)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMRESIZABILITYATTRIBUTES, kWidgetPrefix + 244)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESIZABLEDIALOGCURSORPROVIDER, kWidgetPrefix + 245)
DECLARE_PMID(kInterfaceIDSpace, IID_IISDIALOGPOPUP, kWidgetPrefix + 246)
DECLARE_PMID(kInterfaceIDSpace, IID_ISGOURLBASEDHYPERLINK, kWidgetPrefix + 247)
DECLARE_PMID(kInterfaceIDSpace, IID_IWIDGETBORDERCOLOR, kWidgetPrefix + 248)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTSWITCHOBSERVER, kWidgetPrefix + 249)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTPMREALLISTVALUE, kWidgetPrefix + 250)
//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kWidgetPrefix + 255 )
// End of the road, need another prefix.

// <Implementation ID>
//========================================================================================
// ----- Implementation IDs -----
//========================================================================================

DECLARE_PMID(kImplementationIDSpace, kADBEControlDataImpl, kWidgetPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCBooleanControlDataImpl, kWidgetPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCIntegerControlDataImpl, kWidgetPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDV_SearchableEditBoxViewImpl, kWidgetPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCPanelControlDataImpl, kWidgetPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCDynamicPanelControlDataImpl, kWidgetPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCRealNumberControlDataImpl, kWidgetPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCTextControlDataImpl, kWidgetPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCPanelMenuDataImpl, kWidgetPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kDropDownListMapperImpl, kWidgetPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kControlViewTransformImpl, kWidgetPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDV_TouchDropDownListViewImpl, kWidgetPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPanelWithBorderViewImpl, kWidgetPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kWTextOwnerDrawItemImpl, kWidgetPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kErasablePanelViewImpl, kWidgetPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kTouchPanelEmbeddedWindowContainerViewImpl, kWidgetPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kPanelEventHandlerImpl, kWidgetPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kTouchPanelSubViewAdapterImpl, kWidgetPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kProgressBarControlViewImpl, kWidgetPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kWidgetParentImpl, kWidgetPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCDialogImpl, kWidgetPrefix +	21)
DECLARE_PMID(kImplementationIDSpace, kCToolImpl, kWidgetPrefix +	22)
DECLARE_PMID(kImplementationIDSpace, kCDialogObserverImpl, kWidgetPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kDialogEventFilterDataImpl, kWidgetPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kScrollBarStateObjectImpl, kWidgetPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kCPanelServiceDataImpl, kWidgetPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kAGMDrawnPanelViewImpl, kWidgetPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kScrollPanoramaActivatorImpl, kWidgetPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kMeasurementPopupMenuObserverImpl, kWidgetPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kScrollBarPanoramaSyncObserverImpl, kWidgetPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCSelectionObserverImpl, kWidgetPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kScrollBarPanoramaSyncImpl, kWidgetPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kProgressBarControlData, kWidgetPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kZoomToCmdImpl, kWidgetPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kZoomCmdDataImpl, kWidgetPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kFitInViewCmdImpl, kWidgetPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kFullViewCmdImpl, kWidgetPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kControlViewCmdDataImpl, kWidgetPrefix + 39)

DECLARE_PMID(kImplementationIDSpace, kEditBoxViewImpl, kWidgetPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kBrowseButtonObserverImpl, kWidgetPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kForceAcceptEnterKeyImpl, kWidgetPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kDialogEventFilterAppSuspendObserverImpl, kWidgetPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kDV_HyperlinkTextEventHandlerImpl, kWidgetPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kHandPointerCursorProviderImpl, kWidgetPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kHyperlinkRollOverImpl, kWidgetPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kColorPopupPanelWidgetAttributesImpl, kWidgetPrefix + 47 )
DECLARE_PMID(kImplementationIDSpace, kMenuPopupEventHandlerImpl, kWidgetPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kScrollBarEHImpl, kWidgetPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kControlStripRegisterServiceImpl, kWidgetPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kPanelWithWhiteBackgroundViewImpl,		kWidgetPrefix + 52)

DECLARE_PMID(kImplementationIDSpace, kColorViewDataImpl, kWidgetPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kDataPaletteRefTypeImpl, kWidgetPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kCControlViewImpl, kWidgetPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kCTextSelectionObserverImpl, kWidgetPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kPanelWithHiliteBorderViewImpl, kWidgetPrefix + 57)

DECLARE_PMID(kImplementationIDSpace, kIconSuiteButtonViewImpl, kWidgetPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kIconButtonViewImpl, kWidgetPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kArrowPopupViewImpl, kWidgetPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kTristateControlViewImpl, kWidgetPrefix + 61)
//gap
DECLARE_PMID(kImplementationIDSpace, kGenericButtonViewImpl, kWidgetPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kCMouseInfoEventWatcherImpl, kWidgetPrefix + 65 )
DECLARE_PMID(kImplementationIDSpace, kSwatchesPopupPanelWidgetAttributesImpl, kWidgetPrefix + 66 )
DECLARE_PMID(kImplementationIDSpace, kAmbiguousPageImpl, kWidgetPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kScrollBarViewImpl, kWidgetPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kStaticTextViewImpl, kWidgetPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kEraseBackgroundIconViewImpl, kWidgetPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kStaticMultiLineTextViewImpl, kWidgetPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kLineEndPopupControlDataImpl, kWidgetPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kFlatButtonViewImpl, kWidgetPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kTextTypeaheadComboBoxEditBoxEHImpl, kWidgetPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kTextTypeaheadComboboxAttributesImpl, kWidgetPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kTypeaheadComboboxAttributesImpl, kWidgetPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kEditBoxEventHandlerImpl, kWidgetPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kEditBoxTextControlDataImpl, kWidgetPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kCornerEffectPopupControlDataImpl, kWidgetPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kButtonEnablerMUXImpl, kWidgetPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kAGMOwnerDrawnStaticTextViewImpl, kWidgetPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kPageItemEventHandlerImpl, kWidgetPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kPageItemControlDataImpl, kWidgetPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kPageItemFocusImpl, kWidgetPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kSelectedUIColorSpecImpl, kWidgetPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kInLineEditSingleClickEHImpl, kWidgetPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kWControlEventHandlerImpl, kWidgetPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kPalettePanelView, kWidgetPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kDV_TouchNudgeControlViewImpl, kWidgetPrefix + 89)

// ----- Grids -----
DECLARE_PMID(kImplementationIDSpace, kGridAttributesImpl, kWidgetPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kGridResizeRuleImpl, kWidgetPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kGridPanelImpl, kWidgetPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kGridPanoramaImpl, kWidgetPrefix + 93)

DECLARE_PMID(kImplementationIDSpace, kStaticMultiLineEventHandlerImpl, kWidgetPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kTabAreaDataObserverImpl, kWidgetPrefix + 95)

// ----- List boxes -----
#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.
DECLARE_PMID(kImplementationIDSpace, kListBoxResizeRuleImpl, kWidgetPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kWidgetListBoxPanoramaImpl, kWidgetPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kDisabledUIColorSpecImpl, kWidgetPrefix + 98)
//gap
DECLARE_PMID(kImplementationIDSpace, kListBoxEventHandlerImpl, kWidgetPrefix + 100)
//gap
DECLARE_PMID(kImplementationIDSpace, kListBoxAttributesImpl, kWidgetPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kWidgetListBoxEHImpl, kWidgetPrefix + 103)
//gap
#endif

DECLARE_PMID(kImplementationIDSpace, kCCounterControlDataImpl, kWidgetPrefix + 105)
//gap
DECLARE_PMID(kImplementationIDSpace, kDialogEventFilterEHImpl, kWidgetPrefix + 107)

DECLARE_PMID(kImplementationIDSpace, kCMeasureTypeImpl, kWidgetPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kStdButtonEHImpl, kWidgetPrefix + 109)

DECLARE_PMID(kImplementationIDSpace, kAssociatedActionEventHandlerImpl, kWidgetPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kButtonAttributesImpl, kWidgetPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kKeyFocusHandlerImpl, kWidgetPrefix + 113)

DECLARE_PMID(kImplementationIDSpace, kDialogMgrImpl, kWidgetPrefix + 114)

DECLARE_PMID(kImplementationIDSpace, kDialogCommandMgrImpl, kWidgetPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kModelessDialogWindowImpl, kWidgetPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kModelessDialogWindowEHImpl, kWidgetPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kDocProgressBarControlViewImpl, kWidgetPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kStyleTVControllerImpl, kWidgetPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kCellWidgetControllerImpl, kWidgetPrefix + 120)

DECLARE_PMID(kImplementationIDSpace, kXTreeControlViewImpl, kWidgetPrefix + 121)
// gap
DECLARE_PMID(kImplementationIDSpace, kCPreviewDialogErrorHandlerImpl, kWidgetPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kPreviewDialogCmdImpl, kWidgetPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kEndDialogCmdImpl, kWidgetPrefix + 125)

DECLARE_PMID(kImplementationIDSpace, kAbstractTextControlDataImpl, kWidgetPrefix + 126)
//DECLARE_PMID(kImplementationIDSpace, kDocWindowImpl, kWidgetPrefix + 127	) // FIXME_OWL2: obsolete see kDocumentPresentationBoss in AppUIClass.fr
DECLARE_PMID(kImplementationIDSpace, kPresentationListImpl, kWidgetPrefix + 127) // OK to reuse? kDocWindowImpl was not persisted.
DECLARE_PMID(kImplementationIDSpace, kObsoleteBooleanControlDataImpl, kWidgetPrefix + 128)

DECLARE_PMID(kImplementationIDSpace, kCListBoxDragDropSourceImpl, kWidgetPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kCListBoxDragDropTargetImpl, kWidgetPrefix + 130)
#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.
//DECLARE_PMID(kImplementationIDSpace, kListBoxControllerImpl, kWidgetPrefix + 131)
#endif
DECLARE_PMID(kImplementationIDSpace, kGroupPanelAttributesImpl, kWidgetPrefix + 132)

DECLARE_PMID(kImplementationIDSpace, kAGMOwnerDrawnStaticMultiLineTextViewImpl, kWidgetPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kUIColorSwatchViewImpl, kWidgetPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kSplitterWidgetEventHandlerImpl, kWidgetPrefix + 135)
//gap
DECLARE_PMID(kImplementationIDSpace, kCButtonDragDropTargetImpl, kWidgetPrefix + 137)

DECLARE_PMID(kImplementationIDSpace, kCSelectableDialogObserverImpl, kWidgetPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kDialogWindowPanelControlDataImpl, kWidgetPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kPopupClassIDValue, kWidgetPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kCDialogControllerImpl, kWidgetPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kCSelectableDialogControllerImpl, kWidgetPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kSplitBarCtrlViewImpl, kWidgetPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kTriStateControlEventHandlerImpl, kWidgetPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kWidgetUtilsImpl, kWidgetPrefix + 146)
//gap
DECLARE_PMID(kImplementationIDSpace, kClusterPanelObserverImpl, kWidgetPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kClusterPanelViewImpl, kWidgetPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kPersistPMRsrcIDListDataImpl, kWidgetPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kSelectableDialogMgrImpl, kWidgetPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kSelectableDialogServiceImpl, kWidgetPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kGlobalPrefsDialogServiceImpl, kWidgetPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kCSelectableDialogSwitcherImpl, kWidgetPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kGlobalPrefsDialogCreatorImpl, kWidgetPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kClusterControllerImpl, kWidgetPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kDropDownListViewImpl, kWidgetPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kDropDownListEHImpl, kWidgetPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kDropDownListControlDataImpl, kWidgetPrefix + 159)

DECLARE_PMID(kImplementationIDSpace, kDialogPanelServiceImpl, kWidgetPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kCPanelCreatorImpl, kWidgetPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kInfoWidgetServiceImpl, kWidgetPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kCDialogCreatorImpl, kWidgetPrefix + 163)

DECLARE_PMID(kImplementationIDSpace, kEditBoxAttributesImpl, kWidgetPrefix + 164)
//gap
DECLARE_PMID(kImplementationIDSpace, kNudgeControlViewImpl, kWidgetPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kCNudgeObserverImpl, kWidgetPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kCTouchNudgeObserverImpl, kWidgetPrefix + 168)

// gap

DECLARE_PMID(kImplementationIDSpace, kComboBoxChildDDLControllerImpl, kWidgetPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kComboBoxChildDDLDataImpl, kWidgetPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kComboBoxChildEBAttributesImpl, kWidgetPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kComboBoxChildLastValidTextImpl, kWidgetPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kComboBoxChildSubjectImpl, kWidgetPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kComboBoxChildTextDataImpl, kWidgetPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kComboBoxChildTextValidationImpl, kWidgetPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kComboBoxChildTextValueImpl, kWidgetPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kComboBoxDDLControlDataImpl, kWidgetPrefix + 177)
//gap
DECLARE_PMID(kImplementationIDSpace, kComboBoxTextControlDataImpl, kWidgetPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kComboBoxDropDownListViewImpl, kWidgetPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kComboBoxEditBoxViewImpl, kWidgetPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kComboBoxViewImpl, kWidgetPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kComboBoxObserverImpl, kWidgetPrefix + 184)

DECLARE_PMID(kImplementationIDSpace, kNudgeEditBoxViewImpl, kWidgetPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kTouchNudgeEditBoxViewImpl, kWidgetPrefix + 186)

//gap
DECLARE_PMID(kImplementationIDSpace, kPopupPanelViewImpl, kWidgetPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kPopupPanelWrapperWindowEHImpl, kWidgetPrefix + 190)
//gap
DECLARE_PMID(kImplementationIDSpace, kNudgeHandlerImpl, kWidgetPrefix + 192)

DECLARE_PMID(kImplementationIDSpace, kWidgetRefDataImpl, kWidgetPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kClusterPanelControlDataImpl, kWidgetPrefix + 194)
//gap
DECLARE_PMID(kImplementationIDSpace, kClusterPanelMuteObserverImpl, kWidgetPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kXMeasureTypeImpl, kWidgetPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kYMeasureTypeImpl, kWidgetPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kTextMeasureTypeImpl, kWidgetPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kLineWtMeasureTypeImpl, kWidgetPrefix + 200)

DECLARE_PMID(kImplementationIDSpace, kIntTextValidationImpl, kWidgetPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kRealTextValidationImpl, kWidgetPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kPercentTextValidationImpl, kWidgetPrefix + 203)
//gap
DECLARE_PMID(kImplementationIDSpace, kSelectableDialogActionComponentImpl, kWidgetPrefix + 205)

DECLARE_PMID(kImplementationIDSpace, kStrokeFillControlViewImpl, kWidgetPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillControlDataImpl, kWidgetPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillEventHandlerImpl, kWidgetPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kIconFieldEventHandlerImpl, kWidgetPrefix + 209)

DECLARE_PMID(kImplementationIDSpace, kCSelectionAndContentObserverImpl, kWidgetPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillTipImpl, kWidgetPrefix + 211)
//gap
DECLARE_PMID(kImplementationIDSpace, kCSliderEHImpl, kWidgetPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kCSliderViewImpl, kWidgetPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kCSliderTrackerImpl, kWidgetPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kSliderStateDataImpl, kWidgetPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kCSliderControlDataImpl, kWidgetPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kMeasurementClassControlDataImpl, kWidgetPrefix + 220)

DECLARE_PMID(kImplementationIDSpace, kIntTextValueImpl, kWidgetPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kRealTextValueImpl, kWidgetPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kPercentTextValueImpl, kWidgetPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kDropDownListTextControlDataImpl, kWidgetPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kTextEBTextValidationImpl, kWidgetPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kCMeasurementTextValueImpl, kWidgetPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kCMeasurementTextValidationImpl, kWidgetPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kCMeasurementNudgeObserverImpl, kWidgetPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kTextEBTextValueImpl, kWidgetPrefix + 229)

//DECLARE_PMID(kImplementationIDSpace, kNudgeUpButtonViewImpl, kWidgetPrefix + 230)
//DECLARE_PMID(kImplementationIDSpace, kNudgeDownButtonViewImpl, kWidgetPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kPreviewDialogResetCmdImpl, kWidgetPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kPersistentWidgetParentImpl, kWidgetPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kMeasurementSystemObserverImpl, kWidgetPrefix + 234)

DECLARE_PMID(kImplementationIDSpace, kDialogCommandInterceptorImpl, kWidgetPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kOtherEntryDataImpl, kWidgetPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kSplitterCursorProviderImpl, kWidgetPrefix + 237)

DECLARE_PMID(kImplementationIDSpace, kAngleTextValidationImpl, kWidgetPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, kAngleTextValueImpl, kWidgetPrefix + 239)
DECLARE_PMID(kImplementationIDSpace, kStaticTextLineBreakerImpl, kWidgetPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kStaticMultiLineTextAttrImpl, kWidgetPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kADBE3DButtonCursorProviderImpl, kWidgetPrefix + 242)

DECLARE_PMID(kImplementationIDSpace, kPageNumTextValidationImpl, kWidgetPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kPageNumTextValueImpl, kWidgetPrefix + 244)

DECLARE_PMID(kImplementationIDSpace, kCTextUIDListValueImpl, kWidgetPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kPageRangeTextUIDListValueImpl, kWidgetPrefix + 246)
DECLARE_PMID(kImplementationIDSpace, kUIDListTextValidationImpl, kWidgetPrefix + 247)

DECLARE_PMID(kImplementationIDSpace, kSplitterTrackerRegisterImpl, kWidgetPrefix + 248)
DECLARE_PMID(kImplementationIDSpace, kSplitterTrackerImpl, kWidgetPrefix + 249)
DECLARE_PMID(kImplementationIDSpace, kSplitterTrackerEHImpl, kWidgetPrefix + 250)

DECLARE_PMID(kImplementationIDSpace, kDV_SliderViewImpl, kWidgetPrefix + 251)

DECLARE_PMID(kImplementationIDSpace, kSizePanelDetailControllerImpl, kWidgetPrefix + 252)
DECLARE_PMID(kImplementationIDSpace, kOwnerDrawStyleGroupDDListControllerImpl, kWidgetPrefix + 253)
DECLARE_PMID(kImplementationIDSpace, kSetsPanelDetailControllerImpl, kWidgetPrefix + 254)

DECLARE_PMID(kImplementationIDSpace, kCellPanelControlDataImpl, kWidgetPrefix + 255)
																/* NOTE NOTE NOTE NOTE NOTE */
																/* WidgetBin uses 2 adjacent prefixes(0x06 and 0x07) */
																/* kWidgetPrefix is 0x06, so kWidgetPrefix + 256 == 0x07 */
																/* so from here down, these Impl IDs are in another prefix. */
																/* normally you would need to get another id, and start over */
																/* at kFooPrefix +1, but since widgetbin has 2 adjacent prefixes */
																/* we have chosen to do it this way. */
DECLARE_PMID(kImplementationIDSpace, kGridPanelControlDataImpl, kWidgetPrefix + 256 /* now we are into our second prefix! */)

DECLARE_PMID(kImplementationIDSpace, kResourceSrcFileInfoImpl, kWidgetPrefix + 257)
DECLARE_PMID(kImplementationIDSpace, kTreeBasedListBoxControllerImpl, kWidgetPrefix + 258)
DECLARE_PMID(kImplementationIDSpace, kStringListBoxTreeAdapterImpl, kWidgetPrefix + 259)
DECLARE_PMID(kImplementationIDSpace, kTypeaheadEditBoxEHImpl, kWidgetPrefix + 260)
// 261
DECLARE_PMID(kImplementationIDSpace, kTypeaheadComboboxStringDataImpl, kWidgetPrefix + 262)

DECLARE_PMID(kImplementationIDSpace, kComboBoxEBAttributesImpl, kWidgetPrefix + 263)
DECLARE_PMID(kImplementationIDSpace, kEditboxScrapSuiteImpl, kWidgetPrefix + 264)
DECLARE_PMID(kImplementationIDSpace, kTypeaheadEditboxScrapSuiteImpl, kWidgetPrefix + 265)

DECLARE_PMID(kImplementationIDSpace, kCColorSwatchViewObserverImpl, kWidgetPrefix + 266)
DECLARE_PMID(kImplementationIDSpace, kCColorSwatchEHImpl, kWidgetPrefix + 267)

DECLARE_PMID(kImplementationIDSpace, kDialogWindowImpl, kWidgetPrefix + 268)
DECLARE_PMID(kImplementationIDSpace, kTriStateControlAttributesImpl, kWidgetPrefix + 269)
DECLARE_PMID(kImplementationIDSpace, kSplitterControlDataImpl, kWidgetPrefix + 270)
//gap
DECLARE_PMID(kImplementationIDSpace, kStringListBoxControlDataImpl, kWidgetPrefix + 272)
DECLARE_PMID(kImplementationIDSpace, kPageNumPlusMasterTextValueImpl, kWidgetPrefix + 273)
DECLARE_PMID(kImplementationIDSpace, kCAlertHandlerProviderImpl, kWidgetPrefix + 274)

DECLARE_PMID(kImplementationIDSpace, kGridScrollBarPanoramaSync, kWidgetPrefix + 275)
DECLARE_PMID(kImplementationIDSpace, kGridScrollBarPanoramaSyncObserver, kWidgetPrefix + 276)

DECLARE_PMID(kImplementationIDSpace, kPageNumPlusMasterValidation, kWidgetPrefix + 277)
DECLARE_PMID(kImplementationIDSpace, kSetsHPanelDetailController, kWidgetPrefix + 278)

DECLARE_PMID(kImplementationIDSpace, kStaticTextEHImpl, kWidgetPrefix + 279)
DECLARE_PMID(kImplementationIDSpace, kStaticTextAttributesImpl, kWidgetPrefix + 280)

DECLARE_PMID(kImplementationIDSpace, kComboBoxEditBoxEHImpl, kWidgetPrefix + 281)
//DECLARE_PMID(kImplementationIDSpace, kComboBoxEventHandlerImpl, kWidgetPrefix + 282)
DECLARE_PMID(kImplementationIDSpace, kViewSubjectImpl, kWidgetPrefix + 283)
DECLARE_PMID(kImplementationIDSpace, kViewListBoxControlDataImpl, kWidgetPrefix + 284)

DECLARE_PMID(kImplementationIDSpace, kModelessActionComponentImpl, kWidgetPrefix + 285)
DECLARE_PMID(kImplementationIDSpace, kTypeaheadDropDownEHImpl, kWidgetPrefix + 286)
DECLARE_PMID(kImplementationIDSpace, kUIFontSpecImpl, kWidgetPrefix + 287)
DECLARE_PMID(kImplementationIDSpace, kDefinedBreakLineBreakerImpl, kWidgetPrefix + 288)
DECLARE_PMID(kImplementationIDSpace, kIconEHImpl, kWidgetPrefix + 289)
DECLARE_PMID(kImplementationIDSpace, kEditBoxCursorProviderImpl, kWidgetPrefix + 290)
DECLARE_PMID(kImplementationIDSpace, kStaticMultiLineObserverImpl, kWidgetPrefix + 291)
DECLARE_PMID(kImplementationIDSpace, kComboBoxChildBoolDataImpl, kWidgetPrefix + 292)
DECLARE_PMID(kImplementationIDSpace, kCTextControlData2Impl, kWidgetPrefix + 293)
DECLARE_PMID(kImplementationIDSpace, kXSessionPrefsMeasureTypeImpl, kWidgetPrefix + 294)
DECLARE_PMID(kImplementationIDSpace, kYSessionPrefsMeasureTypeImpl, kWidgetPrefix + 295)
DECLARE_PMID(kImplementationIDSpace, kStyleNameValidationImpl, kWidgetPrefix + 296)
DECLARE_PMID(kImplementationIDSpace, kEditboxDragDropTextTargetImpl, kWidgetPrefix + 297)
//gap
DECLARE_PMID(kImplementationIDSpace, kMSynchDocumentProxyThreadImpl, kWidgetPrefix + 300)
//gap
DECLARE_PMID(kImplementationIDSpace, kSwatchesPanelAttributesImpl, kWidgetPrefix + 302)
DECLARE_PMID(kImplementationIDSpace, kDataSysControlImpl, kWidgetPrefix + 303)
DECLARE_PMID(kImplementationIDSpace, kTextSizeMeasureTypeImpl, kWidgetPrefix + 304)
DECLARE_PMID(kImplementationIDSpace, kViewSelectionImpl, kWidgetPrefix + 305)
DECLARE_PMID(kImplementationIDSpace, kKeyFocusDelegateImpl, kWidgetPrefix + 306)
DECLARE_PMID(kImplementationIDSpace, kTextMeasureOffsetTypeImpl, kWidgetPrefix + 307)
DECLARE_PMID(kImplementationIDSpace, kAutoPercentTextValueImpl	, kWidgetPrefix + 308)
DECLARE_PMID(kImplementationIDSpace, kMouseRollOverImpl, kWidgetPrefix + 309)
DECLARE_PMID(kImplementationIDSpace, kRollOverIconButtonViewImpl, kWidgetPrefix + 310)
DECLARE_PMID(kImplementationIDSpace, kStringListBoxWidgetMgrImpl, kWidgetPrefix + 311)
DECLARE_PMID(kImplementationIDSpace, kKitViewDataImpl, kWidgetPrefix + 312)
DECLARE_PMID(kImplementationIDSpace, kSelectedTabDataImpl_Obsolete, kWidgetPrefix + 313)
DECLARE_PMID(kImplementationIDSpace, kUIBrightnessButtonWidgetViewImpl, kWidgetPrefix + 314)

//gap
DECLARE_PMID(kImplementationIDSpace, kOwnerDrawDDItemImpl, kWidgetPrefix + 317)
//gap
DECLARE_PMID(kImplementationIDSpace, kRecessedWellIconViewImpl, kWidgetPrefix + 320)
DECLARE_PMID(kImplementationIDSpace, kEyeballCheckboxEventHandlerImpl, kWidgetPrefix + 321)
DECLARE_PMID(kImplementationIDSpace, kKitViewControlViewHorzImpl, kWidgetPrefix + 322)
DECLARE_PMID(kImplementationIDSpace, kKitViewControlViewVertImpl, kWidgetPrefix + 323)
DECLARE_PMID(kImplementationIDSpace, kViewListBoxWidgetMgrImpl, kWidgetPrefix + 324)
DECLARE_PMID(kImplementationIDSpace, kCControlViewObserversImpl, kWidgetPrefix + 325)

DECLARE_PMID(kImplementationIDSpace, kDialogPrivateUtilsImpl, kWidgetPrefix + 329)
//gap
DECLARE_PMID(kImplementationIDSpace, kPopupSliderViewImpl, kWidgetPrefix + 331)


DECLARE_PMID(kImplementationIDSpace, kTreeWidgetControlViewImpl, kWidgetPrefix + 332)
DECLARE_PMID(kImplementationIDSpace, kTreeExpanderOptionsImpl, kWidgetPrefix + 333)
DECLARE_PMID(kImplementationIDSpace, kTreeExpanderWidgetEHImpl, kWidgetPrefix + 335)
DECLARE_PMID(kImplementationIDSpace, kOwnerDrawMenuImpl, kWidgetPrefix + 336)
DECLARE_PMID(kImplementationIDSpace, kTreeAttributesImpl, kWidgetPrefix + 337)
DECLARE_PMID(kImplementationIDSpace, kTreeScrollBarObserverImpl, kWidgetPrefix + 338)
DECLARE_PMID(kImplementationIDSpace, kAutoPercentTextValidationImpl, kWidgetPrefix + 339)
DECLARE_PMID(kImplementationIDSpace, kBranchExpandedBoolDataImpl, kWidgetPrefix + 340)
DECLARE_PMID(kImplementationIDSpace, kTreeNodeEventHandlerImpl, kWidgetPrefix + 341)
//gap
DECLARE_PMID(kImplementationIDSpace, kGroupButtonPanelEHImpl, kWidgetPrefix + 343)
DECLARE_PMID(kImplementationIDSpace, kGroupButtonPanelControlViewImpl, kWidgetPrefix + 344)
DECLARE_PMID(kImplementationIDSpace, kTreeBasedListBoxNodeEventHandlerImpl, kWidgetPrefix + 345)
DECLARE_PMID(kImplementationIDSpace, kCSliderInlineRangeControlDataImpl, kWidgetPrefix + 346)
//gap
DECLARE_PMID(kImplementationIDSpace, kTabSelectableDlgSwitcherImpl, kWidgetPrefix + 350)
DECLARE_PMID(kImplementationIDSpace, kSysTabControlListDataImpl, kWidgetPrefix + 351)
DECLARE_PMID(kImplementationIDSpace, kViewListBoxTreeAdapterImpl, kWidgetPrefix + 352)
DECLARE_PMID(kImplementationIDSpace, kDialogShortcutContextImpl, kWidgetPrefix + 353)
DECLARE_PMID(kImplementationIDSpace, kUIColorSpecImpl, kWidgetPrefix + 354)
DECLARE_PMID(kImplementationIDSpace, kTreeNodeControlViewImpl, kWidgetPrefix + 355)
DECLARE_PMID(kImplementationIDSpace, kPanelMouseRollOverImpl, kWidgetPrefix + 356)
DECLARE_PMID(kImplementationIDSpace, kNudgeComboBoxViewImpl, kWidgetPrefix + 357)
DECLARE_PMID(kImplementationIDSpace, kPrintMeasureTypeImpl, kWidgetPrefix + 358)
DECLARE_PMID(kImplementationIDSpace, kNodeExpanderWidgetObserverImpl, kWidgetPrefix + 359)
DECLARE_PMID(kImplementationIDSpace, kTreeExpanderWidgetViewImpl, kWidgetPrefix + 360)
DECLARE_PMID(kImplementationIDSpace, kSimplePanelDetailControllerImpl, kWidgetPrefix + 361)
DECLARE_PMID(kImplementationIDSpace, kZoomSetsDetailControllerImpl, kWidgetPrefix + 362)
DECLARE_PMID(kImplementationIDSpace, kTreeNodeIDDataImpl, kWidgetPrefix + 364)
DECLARE_PMID(kImplementationIDSpace, kCTreeViewMgrImpl, kWidgetPrefix + 365)
DECLARE_PMID(kImplementationIDSpace, kClickableStaticTextViewImpl, kWidgetPrefix + 366)
DECLARE_PMID(kImplementationIDSpace, kListControlDataViewImpl, kWidgetPrefix + 367)
DECLARE_PMID(kImplementationIDSpace, kListControlDataStringImpl, kWidgetPrefix + 368)
DECLARE_PMID(kImplementationIDSpace, kSysTabControllerImpl, kWidgetPrefix + 369)
DECLARE_PMID(kImplementationIDSpace, kCTreeViewControllerImpl, kWidgetPrefix + 370)
DECLARE_PMID(kImplementationIDSpace, kShortcutEditBoxEHImpl, kWidgetPrefix + 371)
DECLARE_PMID(kImplementationIDSpace, kPasswordEditBoxScrapSuiteImpl, kWidgetPrefix + 372)
DECLARE_PMID(kImplementationIDSpace, kPasswordEditBoxViewImpl, kWidgetPrefix + 374)
//gap
DECLARE_PMID(kImplementationIDSpace, kWidgetBinStartupShutdownImpl, kWidgetPrefix + 376)
DECLARE_PMID(kImplementationIDSpace, kAssociatedWidgetAttributesImpl, kWidgetPrefix + 377)
//gap
DECLARE_PMID(kImplementationIDSpace, kShortcutEditBoxViewImpl, kWidgetPrefix + 379)
DECLARE_PMID(kImplementationIDSpace, kStyleShortcutEditBoxEHImpl, kWidgetPrefix + 380)

// Table Stroke SelectionWidget
DECLARE_PMID(kImplementationIDSpace, kStrokeSelectAttributesImpl, kWidgetPrefix + 382)
DECLARE_PMID(kImplementationIDSpace, kCellStrokeWidgetObserverImpl, kWidgetPrefix + 383)
DECLARE_PMID(kImplementationIDSpace, kCellStrokeSelectionWidgetImpl, kWidgetPrefix + 384)
DECLARE_PMID(kImplementationIDSpace, kStrokeWidgetPanelSelectionObsImpl, kWidgetPrefix + 385)
DECLARE_PMID(kImplementationIDSpace, kAutoMeasurementTextValueImpl, kWidgetPrefix + 386)
DECLARE_PMID(kImplementationIDSpace, kMPopupSliderMenuObserverImpl, kWidgetPrefix + 387 )
DECLARE_PMID(kImplementationIDSpace, kCAccelerateControlDataImpl, kWidgetPrefix + 388 )
DECLARE_PMID(kImplementationIDSpace, kWindowUtilsImpl, kWidgetPrefix + 389 )
DECLARE_PMID(kImplementationIDSpace, kPalettePanelUtilsImpl, kWidgetPrefix + 390 )
DECLARE_PMID(kImplementationIDSpace, kTreeViewEventHandlerImpl, kWidgetPrefix + 391 )
DECLARE_PMID(kImplementationIDSpace, kDropDownSelDlgObserverImpl, kWidgetPrefix + 392 )
DECLARE_PMID(kImplementationIDSpace, kDropDownSelDlgSwitcherImpl, kWidgetPrefix + 393 )
DECLARE_PMID(kImplementationIDSpace, kAutoMeasurementTextValidationImpl, kWidgetPrefix + 394)
DECLARE_PMID(kImplementationIDSpace, kIconStyleAttributesImpl, kWidgetPrefix + 395 )
DECLARE_PMID(kImplementationIDSpace, kVertSplitterCursorProviderImpl, kWidgetPrefix + 396 )
//gap
DECLARE_PMID(kImplementationIDSpace, kGenericTreeViewObserverImpl, kWidgetPrefix + 398 )

DECLARE_PMID(kImplementationIDSpace, kTextColorListControlDataImpl, kWidgetPrefix + 399 )

DECLARE_PMID(kImplementationIDSpace, kCPanelEmptyMenuDataImpl, kWidgetPrefix + 400)
DECLARE_PMID(kImplementationIDSpace, kCategoryRealNumberDataImpl, kWidgetPrefix + 401 )
DECLARE_PMID(kImplementationIDSpace, kKitViewControlViewTabPanelImpl, kWidgetPrefix + 402 )
DECLARE_PMID(kImplementationIDSpace, kWidgetIDDataImpl, kWidgetPrefix + 403 )
DECLARE_PMID(kImplementationIDSpace, kXLocWidgetIDDataImpl, kWidgetPrefix + 404 )
DECLARE_PMID(kImplementationIDSpace, kYLocWidgetIDDataImpl, kWidgetPrefix + 405 )
DECLARE_PMID(kImplementationIDSpace, kUnitsPopupMenuActionImpl, kWidgetPrefix + 406 )
DECLARE_PMID(kImplementationIDSpace, kUnitsPopupActionRegisterImpl, kWidgetPrefix + 407 )
DECLARE_PMID(kImplementationIDSpace, kPNGIconAttributesImpl, kWidgetPrefix + 408 )
//gap

DECLARE_PMID(kImplementationIDSpace, kPathStrokerWidgetImpl, kWidgetPrefix + 410 )
DECLARE_PMID(kImplementationIDSpace, kToolBoxIconButtonViewImpl, kWidgetPrefix + 411 )
// gap
DECLARE_PMID(kImplementationIDSpace, kTabShapeUtilsImpl, kWidgetPrefix + 413 )
DECLARE_PMID(kImplementationIDSpace, kObjStylesAssociatedCategoriesDataImpl, kWidgetPrefix + 414 )
DECLARE_PMID(kImplementationIDSpace, kWXPThemeImpl, kWidgetPrefix + 415 )
DECLARE_PMID(kImplementationIDSpace, kColorListOwnerDrawDDItemImpl, kWidgetPrefix + 416 )
DECLARE_PMID(kImplementationIDSpace, kLayoutSplitterPanelControlDataImpl, kWidgetPrefix + 417 )
DECLARE_PMID(kImplementationIDSpace, kColorListControlDataImpl, kWidgetPrefix + 418 )
DECLARE_PMID(kImplementationIDSpace, kColorListObserverImpl, kWidgetPrefix + 419 )
DECLARE_PMID(kImplementationIDSpace, kDialogOnHyperlinkEventHandlerImpl, kWidgetPrefix + 420)
//DECLARE_PMID(kImplementationIDSpace, kColorListElementViewImpl, kWidgetPrefix + 420 )  // deprecated - replaced with kDV_ColorListElementViewImpl
DECLARE_PMID(kImplementationIDSpace, kInLineEditViewImpl, kWidgetPrefix + 421)
//gap
DECLARE_PMID(kImplementationIDSpace, kInLineEditChildStaticTextViewImpl, kWidgetPrefix + 423)
DECLARE_PMID(kImplementationIDSpace, kTextInLineEditChildEBViewImpl, kWidgetPrefix + 424)
DECLARE_PMID(kImplementationIDSpace, kTextInLineEditControllerImpl, kWidgetPrefix + 425)
//gap
DECLARE_PMID(kImplementationIDSpace, kInLineEditChildStaticTextAttributesImpl, kWidgetPrefix + 427)
DECLARE_PMID(kImplementationIDSpace, kInLineEditControllerImpl,	kWidgetPrefix + 428)
DECLARE_PMID(kImplementationIDSpace, kInLineEditEditingAttributesImpl, kWidgetPrefix + 429)
DECLARE_PMID(kImplementationIDSpace, kInLineEditEventMonitorEHImpl,	kWidgetPrefix + 430)
DECLARE_PMID(kImplementationIDSpace, kInLineEditContainerPanelControlDataImpl, kWidgetPrefix + 431)
DECLARE_PMID(kImplementationIDSpace, kInLineEditIdleTaskImpl, kWidgetPrefix + 432 )
DECLARE_PMID(kImplementationIDSpace, kInLineEditObserverImpl, kWidgetPrefix + 433 )
DECLARE_PMID(kImplementationIDSpace, kInLineEditClickPauseClickEHImpl, kWidgetPrefix + 434 )
DECLARE_PMID(kImplementationIDSpace, kTextInLineEditChildEBTextControlDataImpl, kWidgetPrefix + 435 )
DECLARE_PMID(kImplementationIDSpace, kInLineEditChildEditboxEHImpl, kWidgetPrefix + 436 )
//gap
DECLARE_PMID(kImplementationIDSpace, kInLineEditChildDropDownListEHImpl, kWidgetPrefix + 438 )
DECLARE_PMID(kImplementationIDSpace, kTextInLineEditChildEBAttributesImpl, kWidgetPrefix + 439 )
DECLARE_PMID(kImplementationIDSpace, kNoKeyFocusTriStateControlEHImpl, kWidgetPrefix + 440 )
DECLARE_PMID(kImplementationIDSpace, kStrokeTypeOwnerDrawDDItemImpl, kWidgetPrefix + 441 )
DECLARE_PMID(kImplementationIDSpace, kStrokeTypeListElementViewImpl, kWidgetPrefix + 442 )
DECLARE_PMID(kImplementationIDSpace, kStrokeTypeListControlDataImpl, kWidgetPrefix + 443 )
DECLARE_PMID(kImplementationIDSpace, kInLineEditPointyHandCursorProviderImpl, kWidgetPrefix + 444 )
DECLARE_PMID(kImplementationIDSpace, kInLineEditSingleClickTreeNodeEHImpl, kWidgetPrefix + 445 )
DECLARE_PMID(kImplementationIDSpace, kControlSetsDetailControllerImpl, kWidgetPrefix + 446 )
DECLARE_PMID(kImplementationIDSpace, kListTreeWidgetControlViewImpl, kWidgetPrefix + 447 )
//gap


DECLARE_PMID(kImplementationIDSpace, kSmallRowsTreeDtlControllerImpl, kWidgetPrefix + 449 )
DECLARE_PMID(kImplementationIDSpace, kTextWidgetTipImpl, kWidgetPrefix + 450 )
DECLARE_PMID(kImplementationIDSpace, kKitPanelDetailControllerImpl, kWidgetPrefix + 451 )
DECLARE_PMID(kImplementationIDSpace, kQuickApplyButtonTipImpl, kWidgetPrefix + 452)
DECLARE_PMID(kImplementationIDSpace, kLineEndOwnerDrawDDItemImpl, kWidgetPrefix + 453 )
DECLARE_PMID(kImplementationIDSpace, kCategoryNameTextDataImpl, kWidgetPrefix + 454 )
DECLARE_PMID(kImplementationIDSpace, kSplitterPanelCursorProviderImpl, kWidgetPrefix + 455 )
DECLARE_PMID(kImplementationIDSpace, kSplitterPanelControlViewImpl, kWidgetPrefix + 456 )
DECLARE_PMID(kImplementationIDSpace, kSplitterPanelControlDataImpl, kWidgetPrefix + 457 )
DECLARE_PMID(kImplementationIDSpace, kSplitterPanelEHImpl, kWidgetPrefix + 458 )
DECLARE_PMID(kImplementationIDSpace, kSplitterPanelTrackerRegImpl, kWidgetPrefix + 459 )
DECLARE_PMID(kImplementationIDSpace, kSplitterPanelTrackerImpl, kWidgetPrefix + 460 )
DECLARE_PMID(kImplementationIDSpace, kSplitterPanelControllerImpl, kWidgetPrefix + 461 )
DECLARE_PMID(kImplementationIDSpace, kMultiResourceImpl, kWidgetPrefix + 462 )
DECLARE_PMID(kImplementationIDSpace, kStyleGroupObserverImpl, kWidgetPrefix + 463 )
DECLARE_PMID(kImplementationIDSpace, kOverPrintIconEventHandlerImpl, kWidgetPrefix + 464 )
DECLARE_PMID(kImplementationIDSpace, kOverPrintIconObserverImpl, kWidgetPrefix + 465 )
DECLARE_PMID(kImplementationIDSpace, kKillerFindButtonObserverImpl, kWidgetPrefix + 466)
DECLARE_PMID(kImplementationIDSpace, kChainButtonViewImpl, kWidgetPrefix + 467 )
DECLARE_PMID(kImplementationIDSpace, kLinkedSplitCtrlViewImpl, kWidgetPrefix + 468 )
DECLARE_PMID(kImplementationIDSpace, kLinkedSplitCtrlDataImpl, kWidgetPrefix + 469 )
DECLARE_PMID(kImplementationIDSpace, kSplitObserverImpl, kWidgetPrefix + 470 )
DECLARE_PMID(kImplementationIDSpace, kCTreeViewWidgetMgrImpl, kWidgetPrefix + 471 )
DECLARE_PMID(kImplementationIDSpace, kListTreeViewAdapterImpl, kWidgetPrefix + 472 )
DECLARE_PMID(kImplementationIDSpace, kGenericFindListDataImpl, kWidgetPrefix + 473 )

// ---- Moved from Graphic Styles plug-in
//gap
DECLARE_PMID(kImplementationIDSpace, kImpl_StrokeFillProxyTip, kWidgetPrefix + 474)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillObserverImpl, kWidgetPrefix + 475)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateProxyObserverImpl, kWidgetPrefix + 476)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillDDSourceImpl, kWidgetPrefix + 477)
// ---- end move.

// ---- Moved from Utilities plug-in
DECLARE_PMID(kImplementationIDSpace, kDragDropSourceEHImpl, kWidgetPrefix + 478)
DECLARE_PMID(kImplementationIDSpace, kEmptyDragDropCommandImpl, kWidgetPrefix + 479)
DECLARE_PMID(kImplementationIDSpace, kDropDesktopFileCmdImpl, kWidgetPrefix + 480)
DECLARE_PMID(kImplementationIDSpace, kColumnHeaderPanelDataImpl, kWidgetPrefix + 481)	
DECLARE_PMID(kImplementationIDSpace, kColumnHeaderPanelEventHandlerImpl, kWidgetPrefix + 482)	

DECLARE_PMID(kImplementationIDSpace, kLoadStyleListElementEHImpl,		kWidgetPrefix + 483)
DECLARE_PMID(kImplementationIDSpace, kLoadStyleListTreeViewAdapterImpl, kWidgetPrefix + 484)
DECLARE_PMID(kImplementationIDSpace, kLoadStyleListWidgetMgrImpl,		kWidgetPrefix + 485)
DECLARE_PMID(kImplementationIDSpace, kLoadStyleSplitterRollOverImpl,	kWidgetPrefix + 486)
DECLARE_PMID(kImplementationIDSpace, kLoadstyleDropDownControllerImpl,	kWidgetPrefix + 487)
DECLARE_PMID(kImplementationIDSpace, kLoadStyleDropDownWidgetAttributesImpl, kWidgetPrefix + 488)
//gap
DECLARE_PMID(kImplementationIDSpace, kLoadStyleTreeViewObserverImpl,	kWidgetPrefix + 490)
DECLARE_PMID(kImplementationIDSpace, kLoadStyleListElementObserverImpl, kWidgetPrefix +491)
DECLARE_PMID(kImplementationIDSpace, kLoadstyleTreeViewMgrImpl,			kWidgetPrefix + 492)
DECLARE_PMID(kImplementationIDSpace, kLoadStyleSplitterPanelEHImpl,		kWidgetPrefix +493)

DECLARE_PMID(kImplementationIDSpace, kIconStaticTextViewImpl, kWidgetPrefix + 494 )
DECLARE_PMID(kImplementationIDSpace, kCStyleDropDownTypeAheadImpl, kWidgetPrefix + 495 )
DECLARE_PMID(kImplementationIDSpace, kStyleGroupOwnerDrawDDItemImpl, kWidgetPrefix + 496 )
DECLARE_PMID(kImplementationIDSpace, kStyleGroupDropDownElementViewImpl, kWidgetPrefix + 497 )
DECLARE_PMID(kImplementationIDSpace, kCStyleGroupListControlDataImpl, kWidgetPrefix + 498 )
DECLARE_PMID(kImplementationIDSpace, kStyleGroupDropDownElementDataImpl, kWidgetPrefix + 499 )
DECLARE_PMID(kImplementationIDSpace, kMKDDListControlDataImpl, kWidgetPrefix  + 500)
//gap
DECLARE_PMID(kImplementationIDSpace, kAdaptiveEditBoxTextValidationImpl, kWidgetPrefix + 501)

DECLARE_PMID(kImplementationIDSpace, kStyleGroupTreeViewAdapterImpl, kWidgetPrefix + 502 )
DECLARE_PMID(kImplementationIDSpace, kStyleGroupTreeViewWidgetMgrImpl, kWidgetPrefix + 503 )
DECLARE_PMID(kImplementationIDSpace, kLoadStyleMultiLineBreakerImpl, kWidgetPrefix + 504 )
DECLARE_PMID(kImplementationIDSpace, kColumnHeaderPanelViewImpl, kWidgetPrefix + 505)	
DECLARE_PMID(kImplementationIDSpace, kColumnHeaderCursorProviderImpl, kWidgetPrefix + 506) 
DECLARE_PMID(kImplementationIDSpace, kCachedIconSuiteButtonViewImpl, kWidgetPrefix + 507) 
DECLARE_PMID(kImplementationIDSpace, kASRadioTriStateControlEventHandlerImpl, kWidgetPrefix + 508 )
DECLARE_PMID(kImplementationIDSpace, kGroupASSButtonFocusPanelEHImpl, kWidgetPrefix + 509 )
DECLARE_PMID(kImplementationIDSpace, kLoadStyleStaticMultiLineTextViewImpl, kWidgetPrefix + 510 )
DECLARE_PMID(kImplementationIDSpace, kColumnHeaderAttributesImpl, kWidgetPrefix + 511 )
DECLARE_PMID(kImplementationIDSpace, kFontSizeLimitTextValidationImpl, kWidgetPrefix + 512)

																/* NOTE NOTE NOTE NOTE NOTE */
																/* WidgetBin uses 2 adjacent prefixes(0x06 and 0x07) */
																/* kWidgetPrefix is 0x06, so kWidgetPrefix + 256 == 0x07 */
																/* If you need more implementation IDs than kWidgetPrefix + 511, */
																/*  you'll need to start over with another prefix */
																
// Start of third prefix. First two are adjacent but there was no adjacent space available in AdobePrefix for a third. Therefore
// the third one starts numbering again.
DECLARE_PMID(kImplementationIDSpace, kQuickApplyRegisterProviderImpl, kWidgetPrefix3 + 1) // moved from findchange
DECLARE_PMID(kImplementationIDSpace, kDefaultQuickApplyRegisterProviderImpl, kWidgetPrefix3 + 2) // moved from findchange
DECLARE_PMID(kImplementationIDSpace, kStringListBoxSmallWidgetMgrImpl, kWidgetPrefix3 + 3)
DECLARE_PMID(kImplementationIDSpace, kCornerEffectOwnerDrawDDItemImpl, kWidgetPrefix3 + 4)
DECLARE_PMID(kImplementationIDSpace, kCornerEffectViewImpl, kWidgetPrefix3 + 5)
DECLARE_PMID(kImplementationIDSpace, kOWLCanvasDialogManagerImpl, kWidgetPrefix3 + 6)
DECLARE_PMID(kImplementationIDSpace, kUpdateDialogIdleTaskImpl, kWidgetPrefix3 + 7)
DECLARE_PMID(kImplementationIDSpace, kOWLCanvasIdleTaskDataImpl, kWidgetPrefix3 + 8)
DECLARE_PMID(kImplementationIDSpace, kReleaseOWLDialogCmdImpl, kWidgetPrefix3 + 9)
DECLARE_PMID(kImplementationIDSpace, kReleaseOWLCanvasDialogCmdDataImpl, kWidgetPrefix3 + 10)

DECLARE_PMID(kImplementationIDSpace,	kSliderInlineEditEditingAttributesImpl,		kWidgetPrefix3 + 11)
DECLARE_PMID(kImplementationIDSpace,	kSlideInlineWidgetEHImpl,					kWidgetPrefix3 + 12)
DECLARE_PMID(kImplementationIDSpace,	kSliderInlineEditControllerImpl,			kWidgetPrefix3 + 13)
DECLARE_PMID(kImplementationIDSpace,	kSliderInlineTextValidationImpl,			kWidgetPrefix3 + 14)
DECLARE_PMID(kImplementationIDSpace,	kSlideInlineStaticViewImpl,					kWidgetPrefix3 + 15)
DECLARE_PMID(kImplementationIDSpace,	kSliderInLineEditBoxTextControlDataImpl,    kWidgetPrefix3 + 16)
DECLARE_PMID(kImplementationIDSpace,	kSliderInlineEditWidgetAttributesImpl,		kWidgetPrefix3 + 17)
DECLARE_PMID(kImplementationIDSpace,	kSliderInlineEditPercentWidgetAttributesImpl,kWidgetPrefix3 + 18)
DECLARE_PMID(kImplementationIDSpace,	kSliderInlineEditAngleWidgetAttributesImpl,	kWidgetPrefix3 + 19)
DECLARE_PMID(kImplementationIDSpace,	kSliderWidgetCursorProviderImpl,			kWidgetPrefix3 + 20)
DECLARE_PMID(kImplementationIDSpace,	kSliderInLineWidgetViewImpl,				kWidgetPrefix3 + 21)
DECLARE_PMID(kImplementationIDSpace,	kSlideInlineWidgetEventWatcherImpl,			kWidgetPrefix3 + 22)
DECLARE_PMID(kImplementationIDSpace,	kPopupPanelControlDataImpl,					kWidgetPrefix3 + 23)
DECLARE_PMID(kImplementationIDSpace,	kPopupPanelWrapperWindowImpl,				kWidgetPrefix3 + 24)

DECLARE_PMID(kImplementationIDSpace,	kDV_PageRangeComboBoxDDLOpenCloseHandlerImpl,			kWidgetPrefix3 + 25)
DECLARE_PMID(kImplementationIDSpace,	kPageRangeComboboxAttributesImpl,		kWidgetPrefix3 + 26)
DECLARE_PMID(kImplementationIDSpace,	kPageNumComboboxAttributesImpl,			kWidgetPrefix3 + 27)
DECLARE_PMID(kImplementationIDSpace,	kSelectedUIDDataImpl,					kWidgetPrefix3 + 28)
//gap
DECLARE_PMID(kImplementationIDSpace,	kParentStyleGroupListControlDataImpl,	kWidgetPrefix3 + 30)
//gap
DECLARE_PMID(kImplementationIDSpace,	kStyleGroupComboBoxObserverImpl,		kWidgetPrefix3 + 32)
DECLARE_PMID(kImplementationIDSpace,	kOwnerDrawComboDDListViewImpl,			kWidgetPrefix3 + 33)
DECLARE_PMID(kImplementationIDSpace,	kDisableStyleGroupCBChildBoolDataImpl,	kWidgetPrefix3 + 34)
DECLARE_PMID(kImplementationIDSpace,	kRuleViewImpl,							kWidgetPrefix3 + 35)
DECLARE_PMID(kImplementationIDSpace,	kSpinningIconViewImpl,							kWidgetPrefix3 + 36)
DECLARE_PMID(kImplementationIDSpace,	kStringListBoxLargeSmallWidgetMgrImpl, kWidgetPrefix3 + 37)

DECLARE_PMID(kImplementationIDSpace,	kInlineEditChildTextControlDataImpl,			kWidgetPrefix3 + 50)
DECLARE_PMID(kImplementationIDSpace,	kDVTests_TestMenuImpl,							kWidgetPrefix3 + 51)
DECLARE_PMID(kImplementationIDSpace,	kTreeViewPreChildEventHandlerImpl,				kWidgetPrefix3 + 52)
DECLARE_PMID(kImplementationIDSpace,	kStringListBoxNodeWidthImpl,					kWidgetPrefix3 + 53)
DECLARE_PMID(kImplementationIDSpace,	kStyleImportedTypeIconEHImpl,					kWidgetPrefix3 + 54)

DECLARE_PMID(kImplementationIDSpace,	kTreeNodePreChildEventHandlerImpl,				kWidgetPrefix3 + 55)

DECLARE_PMID(kImplementationIDSpace,	kDesktopColorSamplerTrackerRegImpl,				kWidgetPrefix3 + 56)
DECLARE_PMID(kImplementationIDSpace,	kDesktopColorSamplerTrackerImpl,				kWidgetPrefix3 + 57)
DECLARE_PMID(kImplementationIDSpace,	kDesktopColorSamplerTrackerEHImpl,				kWidgetPrefix3 + 58)
DECLARE_PMID(kImplementationIDSpace,	kDesktopColorSamplerIconButtonEHImpl,			kWidgetPrefix3 + 59)
DECLARE_PMID(kImplementationIDSpace,	kPopupWindowImpl,								kWidgetPrefix3 + 60)
DECLARE_PMID(kImplementationIDSpace,	kOverriddenEventHandlerImpl,					kWidgetPrefix3 + 61)
DECLARE_PMID(kImplementationIDSpace,	kPopupWindowControlViewImpl,					kWidgetPrefix3 + 62)
DECLARE_PMID(kImplementationIDSpace,	kPopupWindowObserverImpl,						kWidgetPrefix3 + 63)
DECLARE_PMID(kImplementationIDSpace,	kSearchMethodStringListControlDataImpl,			kWidgetPrefix3 + 64)
DECLARE_PMID(kImplementationIDSpace,	kToggleModeToggledTextDataImpl,					kWidgetPrefix3 + 65)
DECLARE_PMID(kImplementationIDSpace,	kPopupDialogViewImpl,							kWidgetPrefix3 + 69)
DECLARE_PMID(kImplementationIDSpace,	kPopupDialogImpl,								kWidgetPrefix3 + 70)
DECLARE_PMID(kImplementationIDSpace,	kAddToCCLibraryPanelTipImpl,					kWidgetPrefix3 + 71)
DECLARE_PMID(kImplementationIDSpace,	kDV_TreeBasedDropDownListViewImpl,			 	kWidgetPrefix3 + 72)

// Properties Panel Implementation ID Space.
//DECLARE_PMID(kImplementationIDSpace, kPropertiesPanelServiceProviderImpl, kWidgetPrefix3 + 72)
DECLARE_PMID(kImplementationIDSpace, kPropertiesPanelQuickActionButtonAttributesImpl, kWidgetPrefix3 + 73)
DECLARE_PMID(kImplementationIDSpace, kPropertiesPanelQuickActionButtonObserverImpl, kWidgetPrefix3 + 74)
DECLARE_PMID(kImplementationIDSpace, kClickableTextEventHandlerImpl, kWidgetPrefix3 + 75)
DECLARE_PMID(kImplementationIDSpace, kPopupTextEventHandlerImpl, kWidgetPrefix3 + 76)
DECLARE_PMID(kImplementationIDSpace, kDialogPopupAttributesImpl, kWidgetPrefix3 + 77)
DECLARE_PMID(kImplementationIDSpace, kScalingWidgetTrackerRegisterImpl, kWidgetPrefix3 + 78)
DECLARE_PMID(kImplementationIDSpace, kScalingWidgetTrackerImpl, kWidgetPrefix3 + 79)
DECLARE_PMID(kImplementationIDSpace, kScalingWidgetEventHandlerImpl, kWidgetPrefix3 + 80)
DECLARE_PMID(kImplementationIDSpace, kRectangularButtonViewImpl, kWidgetPrefix3 + 81)
DECLARE_PMID(kImplementationIDSpace, kCustomResizabilityAttributesImpl, kWidgetPrefix3 + 82)
DECLARE_PMID(kImplementationIDSpace, kResizableDialogEventHandlerImpl, kWidgetPrefix3 + 83)
DECLARE_PMID(kImplementationIDSpace, kResizableDialogCursorProviderImpl, kWidgetPrefix3 + 84)
DECLARE_PMID(kImplementationIDSpace, kOpenTypeMenuObserverImpl , kWidgetPrefix3 + 85)
DECLARE_PMID(kImplementationIDSpace, kPopupPositioningHelperImpl , kWidgetPrefix3 + 86)
DECLARE_PMID(kImplementationIDSpace, kPopupOverriddenEventHandlerImpl, kWidgetPrefix3 + 87)
DECLARE_PMID(kImplementationIDSpace, kPropertiesPanelPopupWindowImpl, kWidgetPrefix3 + 88)


//Leaving prefixes till 90 for Properties Panel
DECLARE_PMID(kImplementationIDSpace, kDV_TreeBasedPopupEditBoxViewImpl, kWidgetPrefix3 + 91)
DECLARE_PMID(kImplementationIDSpace, kWidgetBorderColorImpl, kWidgetPrefix3 + 92)
DECLARE_PMID(kImplementationIDSpace, kFlatButtonBorderViewImpl, kWidgetPrefix3 + 93)
DECLARE_PMID(kImplementationIDSpace, kRectangularOptionEventHandlerImpl, kWidgetPrefix3 + 94)
DECLARE_PMID(kImplementationIDSpace, kFontSizeMeasureTypeImpl, kWidgetPrefix3 + 95)
DECLARE_PMID(kImplementationIDSpace, kDocumentSwitchObserverImpl, kWidgetPrefix3 + 96)
DECLARE_PMID(kImplementationIDSpace, kGIFPlayerViewImpl, kWidgetPrefix3 + 97)
DECLARE_PMID(kImplementationIDSpace, kGIFMouseRollOverImpl, kWidgetPrefix3 + 98)
DECLARE_PMID(kImplementationIDSpace, kTaskProgressBarControlViewImpl, kWidgetPrefix3 + 99)
DECLARE_PMID(kImplementationIDSpace, kCTextPMRealListValueImpl, kWidgetPrefix3 + 100)

DECLARE_PMID(kImplementationIDSpace, kDV_ColorListElementViewImpl, kWidgetPrefix3 + 101)
DECLARE_PMID(kImplementationIDSpace, kDV_ColorDropDownListImpl, kWidgetPrefix3 + 102)

// <Service ID>
//========================================================================================
// ----- Service IDs -----
//========================================================================================
DECLARE_PMID(kServiceIDSpace, kAlertHandlerService, kWidgetPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kControlStripRegisterService, kWidgetPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kInfoWidgetService,	kWidgetPrefix + 3)


// Properties Panel Service ID Space 32 onwards.
DECLARE_PMID(kServiceIDSpace, kPropertiesPanelRegisterService, kWidgetPrefix + 32)

// <Widget ID>
//========================================================================================
// ----- Widget IDs -----
//========================================================================================
DECLARE_PMID(kWidgetIDSpace, kResizePresentationWidgetID, kWidgetPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kCellPanelWidgetID, kWidgetPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kOKButtonWidgetID, kWidgetPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kCancelButton_WidgetID, kWidgetPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kPreviewButtonWidgetID, kWidgetPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kNextDialogButtonWidgetID, kWidgetPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPreviousDialogButtonWidgetID, kWidgetPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kSelectDialogSelectionWidgetID, kWidgetPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kDialogGroupPanelWidgetID, kWidgetPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPreferencesDialogWidgetID, kWidgetPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kDefaultDialogPanelWidgetID, kWidgetPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kNudgeUpWidgetID, kWidgetPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kNudgeDownWidgetID, kWidgetPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kComboEditBoxWidgetID, kWidgetPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kComboDropDownWidgetID, kWidgetPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kSubViewAdapeterWidgetID, kWidgetPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kSelectableDialogMenuSeparatorWidgetID, kWidgetPrefix + 16)
		// use kSelectableDialogMenuSeparatorWidgetID in a orderable panel ID list to make a menu
		// separator in the selectable dialog panel popup.

DECLARE_PMID(kWidgetIDSpace, kWdgtTestParentWidgetId, kWidgetPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kWdgtTestClusterWidgetId, kWidgetPrefix + 18)

DECLARE_PMID(kWidgetIDSpace, kPBDlgProgressBarWidgetID, kWidgetPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kPBDlgMajorTaskEditBoxWidgetID, kWidgetPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kPBDlgMinorTaskEditBoxWidgetID, kWidgetPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kPBDlgCancelButtonWidgetID, kWidgetPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kPBDlgParentWidgetID, kWidgetPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kKitMenuButtonWidgetID, kWidgetPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kControlSetButtonWidgetID, kWidgetPrefix + 25)

DECLARE_PMID(kWidgetIDSpace, kComboPopupBtnWidgetID, kWidgetPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kPopupSliderWidgetID, kWidgetPrefix + 27)

DECLARE_PMID(kWidgetIDSpace, kTreeHScrollBarWidgetID, kWidgetPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kTreeVScrollBarWidgetID, kWidgetPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kTreeNodeExpanderWidgetID, kWidgetPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kTreeScrollerWidgetID, kWidgetPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kPBDlgSecondParentWidgetID, kWidgetPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kPBDlgSecondProgressBarWidgetID, kWidgetPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kSelectDlgSelectionPanelWidgetID, kWidgetPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kSelectDialogTitleTextWidgetID, kWidgetPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kPBDlgTaskStatusEditBoxWidgetID, kWidgetPrefix + 36)

DECLARE_PMID(kWidgetIDSpace, kNextButtonWidgetID, kWidgetPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kPreviousButtonWidgetID, kWidgetPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kFirstButtonWidgetID, kWidgetPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kLastButtonWidgetID, kWidgetPrefix + 40)

DECLARE_PMID(kWidgetIDSpace, kInLineEditStaticTextWidgetID,	kWidgetPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kInLineEditEditingWidgetID, kWidgetPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kStandardTreeNodeWidgetID, kWidgetPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kTreeNodeNameWidgetID, kWidgetPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kTreeNodeIconWidgetID, kWidgetPrefix + 45)

DECLARE_PMID(kWidgetIDSpace, kKillerFindButtonID, kWidgetPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kFontMenuEditBoxWidgetID, kWidgetPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kBridgeButtonWidgetID, kWidgetPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kStaticTextWidgetID, kWidgetPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kViewListBoxRowWidgetId, kWidgetPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kViewListBoxRootWidgetId, kWidgetPrefix + 51)

DECLARE_PMID(kWidgetIDSpace, kTouchNudgeDownWidgetId, kWidgetPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kTouchNudgeUpWidgetId, kWidgetPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kTouchAdjustDocWidthWidgetID, kWidgetPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kTouchAdjustDocHeightWidgetID, kWidgetPrefix + 55)

DECLARE_PMID(kWidgetIDSpace, kLastMileMerchandisingGroupWidgetID, kWidgetPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kLastMileMerchandisingGroupLabelWidgetID, kWidgetPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kLastMileMerchandisingTryNowCheckWidgetID, kWidgetPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kLastMileMerchandisingCommonGroupWidgetID, kWidgetPrefix + 59)

// Define some generic widget IDs can be shared. With EVE, a lot of panel widgets are used.
// They really don't need an ID in most of case. So use following generic id for debug purpose.
DECLARE_PMID(kWidgetIDSpace, kGenericPanelWidgetID, kWidgetPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kGenericPanel1WidgetID, kWidgetPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kGenericPanel2WidgetID, kWidgetPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kGenericPanel3WidgetID, kWidgetPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kGenericPanel4WidgetID, kWidgetPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kGenericPanel5WidgetID, kWidgetPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kGenericPanel6WidgetID, kWidgetPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kGroupPanelWidgetID, kWidgetPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kTabsButtonBarWidgetID, kWidgetPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kDesktopColorSamplerButtonWidgetID, kWidgetPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kAddToCCLibrariesCheckboxWidgetID, kWidgetPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kCCLibraryDropdownWidgetID, kWidgetPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kBottomLeftResizingGripperIconWigdetID, kWidgetPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kTopLeftResizingGripperIconWigdetID, kWidgetPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kBottomRightResizingGripperIconWigdetID, kWidgetPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kTopRightResizingGripperIconWigdetID, kWidgetPrefix + 118)

// <Ignore>
//========================================================================================
// ----- Widget Attribute IDs -----
//========================================================================================

#define kWidgetSize					kWidgetPrefix + 1
#define kWidgetPosition				kWidgetPrefix + 2
#define kWidgetVisibleState			kWidgetPrefix + 3

// <Ignore>
//========================================================================================
// ----- Tree Node ID types -----
//========================================================================================
#define kUIDNodeID					kWidgetPrefix + 1
#define kListIndexNodeID			kWidgetPrefix + 2
#define kFileNodeID					kWidgetPrefix + 3
#define kStringNodeID				kWidgetPrefix + 4
#define kObjStylesSelDialogNodeID	kWidgetPrefix + 5
#define kViewNodeID					kWidgetPrefix + 6
//========================================================================================
// ----- Action/Menu IDs -----
//========================================================================================

//gap
DECLARE_PMID(kActionIDSpace, kYesActionID, kWidgetPrefix + 3)
DECLARE_PMID(kActionIDSpace, kNoActionID, kWidgetPrefix + 4)
DECLARE_PMID(kActionIDSpace, kOKActionID, kWidgetPrefix + 5)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel1ActionID, kWidgetPrefix + 6)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel2ActionID, kWidgetPrefix + 7)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel3ActionID, kWidgetPrefix + 8)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel4ActionID, kWidgetPrefix + 9)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel5ActionID, kWidgetPrefix + 10)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel6ActionID, kWidgetPrefix + 11)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel7ActionID, kWidgetPrefix + 12)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel8ActionID, kWidgetPrefix + 13)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel9ActionID, kWidgetPrefix + 14)
DECLARE_PMID(kActionIDSpace, kShowDialogPanel10ActionID, kWidgetPrefix + 15)

DECLARE_PMID(kActionIDSpace, kShowPreviousPanelActionID, kWidgetPrefix + 16)
DECLARE_PMID(kActionIDSpace, kShowNextPanelActionID, kWidgetPrefix + 17)
DECLARE_PMID(kActionIDSpace, kShowFirstPanelActionID, kWidgetPrefix + 18)
DECLARE_PMID(kActionIDSpace, kShowLastPanelActionID, kWidgetPrefix + 19)

DECLARE_PMID(kActionIDSpace, kGiveUpFocusActionID, kWidgetPrefix + 20)

DECLARE_PMID(kActionIDSpace, kUnitsPopupMenuActionID, kWidgetPrefix + 21)
// kWidgetPrefix + 21 to kMeasureToolPrefix + 40 is reserved for the measure system,
// please start from kWidgetPrefix + 41 to define new actionIDs.

// DV related - this def prevents duplicate instatiation of widget ID's
// since we now have 2 widget plug-ins (widgets & dv_widgets) but we 
// only want to keep one ID include file.
#ifndef _WIDGETID_DONT_DEFINE_DVWIDGETIDS_
	#include "DV_WidgetID.h"
#endif

#endif // __WidgetID__

