//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/StylePanelID.h $
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
//  IDs used by the color panel
//  
//  Updated: Wai Cheuk 10/22/97
//  
//========================================================================================

#ifndef __StylePanelID__
#define __StylePanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kStylePanelPrefix			RezLong( 0x2100 )

// <Start IDC>
// PluginID
#define kStylePanelPluginName 			"Style Panel"
DECLARE_PMID(kPlugInIDSpace, kStylePanelPluginID, kStylePanelPrefix + 1)

// <Class ID>
// ClassIDs
// DECLARE_PMID(kClassIDSpace, kCharStylePanelBoss, kStylePanelPrefix + 1)
// DECLARE_PMID(kClassIDSpace, kParaStylePanelBoss, kStylePanelPrefix + 26)

DECLARE_PMID(kClassIDSpace, kCharStyleTreeViewBoss, kStylePanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kParaStyleTreeViewBoss, kStylePanelPrefix + 28)

DECLARE_PMID(kClassIDSpace, kNewCharStyleButtonBoss, kStylePanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kNewParaStyleButtonBoss, kStylePanelPrefix + 27)

DECLARE_PMID(kClassIDSpace, kDeleteCharStyleButtonBoss, kStylePanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kDeleteParaStyleButtonBoss, kStylePanelPrefix + 33)

DECLARE_PMID(kClassIDSpace, kCharStyleViewBoss, kStylePanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kParaStyleViewBoss, kStylePanelPrefix + 30)

//gap
DECLARE_PMID(kClassIDSpace, kCharStylePanelMenuComponentBoss, kStylePanelPrefix + 8)
DECLARE_PMID(kClassIDSpace, kParaStylePanelMenuComponentBoss, kStylePanelPrefix + 34)

DECLARE_PMID(kClassIDSpace, kCharStyleListElementBoss, kStylePanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kParaStyleListElementBoss, kStylePanelPrefix + 29)


DECLARE_PMID(kClassIDSpace, kCharImportedTypeIconBoss, kStylePanelPrefix + 17		)
DECLARE_PMID(kClassIDSpace, kParaImportedTypeIconBoss, kStylePanelPrefix + 32)

//DECLARE_PMID(kClassIDSpace, kCopyStyleCmdBoss, kStylePanelPrefix + 18)

DECLARE_PMID(kClassIDSpace, kCharStyleListDEHandlerBoss, kStylePanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kParaStyleListDEHandlerBoss, kStylePanelPrefix + 35)

DECLARE_PMID(kClassIDSpace, kStylePanelPrefsCmdBoss, kStylePanelPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kLoadStyleCmdBoss, kStylePanelPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kReplaceStyleCmdBoss, kStylePanelPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kEditStyleCmdBoss, kStylePanelPrefix + 23)

DECLARE_PMID(kClassIDSpace, kCharShortCutIconBoss, kStylePanelPrefix + 24)
DECLARE_PMID(kClassIDSpace, kParaShortCutIconBoss, kStylePanelPrefix + 31)


DECLARE_PMID(kClassIDSpace, kExportCharStyleToCCLibrariesButtonBoss, kStylePanelPrefix + 36)
DECLARE_PMID(kClassIDSpace, kExportParaStyleToCCLibrariesButtonBoss, kStylePanelPrefix + 37)

//gap
DECLARE_PMID(kClassIDSpace, kParaStyleSyncBoss, kStylePanelPrefix + 39)
DECLARE_PMID(kClassIDSpace, kCharStyleSyncBoss, kStylePanelPrefix + 40)
//DECLARE_PMID(kClassIDSpace, kRemoveRedundantOverridesCmdBoss, kStylePanelPrefix + 41)

//DECLARE_PMID(kClassIDSpace, kStyleKitRegisterBoss, kStylePanelPrefix + 41)

DECLARE_PMID(kClassIDSpace, kStyleKitBoss, kStylePanelPrefix + 42)

DECLARE_PMID(kClassIDSpace, kCharStyleDDListBoss, kStylePanelPrefix + 43)
DECLARE_PMID(kClassIDSpace, kDeleteCharStyleDBarButtonBoss, kStylePanelPrefix + 44)
DECLARE_PMID(kClassIDSpace, kNewCharStyleDBarButtonBoss, kStylePanelPrefix + 45)

DECLARE_PMID(kClassIDSpace, kParaStyleDDListBoss, kStylePanelPrefix + 46)
DECLARE_PMID(kClassIDSpace, kDeleteParaStyleDBarButtonBoss, kStylePanelPrefix + 47)
DECLARE_PMID(kClassIDSpace, kNewParaStyleDBarButtonBoss, kStylePanelPrefix + 48)

DECLARE_PMID(kClassIDSpace, kCharStyleDropDownElementBoss, kStylePanelPrefix + 49)
DECLARE_PMID(kClassIDSpace, kParaStyleDropDownElementBoss, kStylePanelPrefix + 50)

DECLARE_PMID(kClassIDSpace, kStyleControlSetBoss, kStylePanelPrefix + 51)
DECLARE_PMID(kClassIDSpace, kControlStripStyleRegisterBoss, kStylePanelPrefix + 52)
DECLARE_PMID(kClassIDSpace, kControlStripStyleDefaultRegisterBoss, kStylePanelPrefix + 53)
DECLARE_PMID(kClassIDSpace, kJParaStyleControlSetBoss, kStylePanelPrefix + 54)

DECLARE_PMID(kClassIDSpace, kCharStyleIconButtonBoss, kStylePanelPrefix + 55)
DECLARE_PMID(kClassIDSpace, kParaStyleIconButtonBoss, kStylePanelPrefix + 56)

DECLARE_PMID(kClassIDSpace, kStyleListContextMenuBoss, kStylePanelPrefix + 57)
DECLARE_PMID(kClassIDSpace, kDeleteStyleDialogBoss, kStylePanelPrefix + 58)   //added by sasatte

//gap

DECLARE_PMID(kClassIDSpace, kLoadStyleDialogBoss, kStylePanelPrefix + 61)   //added by sasatte

DECLARE_PMID(kClassIDSpace, kClearOverridesButtonBoss, kStylePanelPrefix + 62)

DECLARE_PMID(kClassIDSpace, kNewParaStyleGroupButtonBoss, kStylePanelPrefix + 63)
DECLARE_PMID(kClassIDSpace, kNewCharStyleGroupButtonBoss, kStylePanelPrefix + 64)
DECLARE_PMID(kClassIDSpace, kStyleGroupOptionsDialogBoss, kStylePanelPrefix + 65)
DECLARE_PMID(kClassIDSpace, kEditableStyleNameWidgetBoss, kStylePanelPrefix + 66)
DECLARE_PMID(kClassIDSpace, kEditableParaStyleNameWidgetBoss, kStylePanelPrefix + 67)
DECLARE_PMID(kClassIDSpace, kEditableCharStyleNameWidgetBoss, kStylePanelPrefix + 68)
DECLARE_PMID(kClassIDSpace, kAppliedParaStyleStaticTextBoss, kStylePanelPrefix + 69)
DECLARE_PMID(kClassIDSpace, kAppliedCharStyleStaticTextBoss, kStylePanelPrefix + 70)
DECLARE_PMID(kClassIDSpace, kSelectStyleGroupDialogBoss, kStylePanelPrefix + 71)
DECLARE_PMID(kClassIDSpace, kTextStyleQuickApplyServiceBoss, kStylePanelPrefix + 72)
DECLARE_PMID(kClassIDSpace, kCharacterStyleDropDownBoss, kStylePanelPrefix + 73)

DECLARE_PMID(kClassIDSpace, kEditAllStyleToTagDialogBoss, kStylePanelPrefix + 74)
DECLARE_PMID(kClassIDSpace, kExportStyleMappingListWidgetBoss, kStylePanelPrefix + 75)
DECLARE_PMID(kClassIDSpace, kExportStyleMappingListItemWidgetBoss, kStylePanelPrefix + 76)
DECLARE_PMID(kClassIDSpace, kExportTagInLineMappingDropdownListWidgetBoss, kStylePanelPrefix + 77)
DECLARE_PMID(kClassIDSpace, kExportTagMappingDropdownListWidgetBoss, kStylePanelPrefix + 78)
DECLARE_PMID(kClassIDSpace, kEVEExportTypeWidgetBoss, kStylePanelPrefix + 79)
DECLARE_PMID(kClassIDSpace, kExportTagMappingComboBoxWidgetBoss, kStylePanelPrefix + 80)
DECLARE_PMID(kClassIDSpace, kStyleToTagBreakEPUBCheckBoxWidgetBoss, kStylePanelPrefix + 81)
DECLARE_PMID(kClassIDSpace, kStyleToTagEmitCSSCheckBoxWidgetBoss, kStylePanelPrefix + 82)
DECLARE_PMID(kClassIDSpace, kHighlightOverrideButtonBoss, kStylePanelPrefix + 83)
DECLARE_PMID(kClassIDSpace, kCharParaStylePropsPanelBoss, kStylePanelPrefix + 84)
DECLARE_PMID(kClassIDSpace, kCharStylePropsPanelDDListBoss, kStylePanelPrefix + 85)
DECLARE_PMID(kClassIDSpace, kStyleGroupPropsPanelDDElementWidgetBoss, kStylePanelPrefix + 86)
DECLARE_PMID(kClassIDSpace, kParaStylePropsPanelDDListBoss, kStylePanelPrefix + 87)
DECLARE_PMID(kClassIDSpace, kCharStylePopupTreeViewWidgetBoss, kStylePanelPrefix + 88)
DECLARE_PMID(kClassIDSpace, kParaStylePopupTreeViewWidgetBoss, kStylePanelPrefix + 89)
DECLARE_PMID(kClassIDSpace, kStyleSampleTextWidgetBoss, kStylePanelPrefix + 90)
DECLARE_PMID(kClassIDSpace, kParaStyleTreeBasedDropDownListWidgetBoss, kStylePanelPrefix + 91)
DECLARE_PMID(kClassIDSpace, kCharStyleTreeBasedDropDownListWidgetBoss, kStylePanelPrefix + 92)
DECLARE_PMID(kClassIDSpace, kStyleTreeNodeWidgetBoss, kStylePanelPrefix + 93)
//DECLARE_PMID(kClassIDSpace, kStyleInfoTextWidgetBoss, kStylePanelPrefix + 94)
DECLARE_PMID(kClassIDSpace, kStyleTreeBasedPopupEditBoxBoss, kStylePanelPrefix + 95)
DECLARE_PMID(kClassIDSpace, kManageStylesTextWidgetBoss, kStylePanelPrefix + 96)
DECLARE_PMID(kClassIDSpace, kParaStyleTreeBasedPopupWindowBoss, kStylePanelPrefix + 97)
DECLARE_PMID(kClassIDSpace, kCharStyleTreeBasedPopupWindowBoss, kStylePanelPrefix + 98)
DECLARE_PMID(kClassIDSpace, kManageStylesWidgetBoss, kStylePanelPrefix + 99)
DECLARE_PMID(kClassIDSpace, kStyleNameTextWidgetBoss, kStylePanelPrefix + 100)
DECLARE_PMID(kClassIDSpace, kStylePopupTreeExpanderWidgetBoss, kStylePanelPrefix + 101)
DECLARE_PMID(kClassIDSpace, kCreateStyleButtonWidgetBoss, kStylePanelPrefix + 102)
DECLARE_PMID(kClassIDSpace, kOpenStyleDialogButtonWidgetBoss, kStylePanelPrefix + 103)
DECLARE_PMID(kClassIDSpace, kParaStylePropertiesPanelMenuComponentBoss, kStylePanelPrefix + 104)
DECLARE_PMID(kClassIDSpace, kCharStylePropertiesPanelMenuComponentBoss, kStylePanelPrefix + 105)

// <Widget ID>
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kCharStyleTreeViewWidgetID, kStylePanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kClearOverridesButtonWidgetID, kStylePanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kParaStyleTreeViewWidgetID, kStylePanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kParaStyleControlStripWidgetID, kStylePanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kParaStyleButtonWidgetID, kStylePanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kCharStyleButtonWidgetID, kStylePanelPrefix + 6)

DECLARE_PMID(kWidgetIDSpace, kDeleteCharStyleButtonWidgetID, kStylePanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kDeleteParaStyleButtonWidgetID, kStylePanelPrefix + 8)

DECLARE_PMID(kWidgetIDSpace, kNewCharStyleButtonWidgetID, kStylePanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kNewParaStyleButtonWidgetID, kStylePanelPrefix + 10)

DECLARE_PMID(kWidgetIDSpace, kResizeButtonWidgetID, kStylePanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kStatusBarWidgetID, kStylePanelPrefix + 12)

DECLARE_PMID(kWidgetIDSpace, kCharStyleListElementNameWidgetID, kStylePanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kParaStyleListElementNameWidgetID, kStylePanelPrefix + 14)

DECLARE_PMID(kWidgetIDSpace, kCharStyleListElementImportedTypeWidgetID, kStylePanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kParaStyleListElementImportedTypeWidgetID, kStylePanelPrefix + 16)

DECLARE_PMID(kWidgetIDSpace, kCharStylePanelWidgetID, kStylePanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kParaStylePanelWidgetID, kStylePanelPrefix + 18)

DECLARE_PMID(kWidgetIDSpace, kCharStyleListElementShortCutWidgetID, kStylePanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kParaStyleListElementShortCutWidgetID, kStylePanelPrefix + 20)

DECLARE_PMID(kWidgetIDSpace, kControlStripWidgetId, kStylePanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kCharStyleListParentWidgetId, kStylePanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kParaStyleListParentWidgetId, kStylePanelPrefix + 23)

DECLARE_PMID(kWidgetIDSpace, kCharStyleKitPanelViewWidgetID, kStylePanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kCharStyleKitDockBarViewWidgetID, kStylePanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kCharStylePanelCtrlSetWidgetID, kStylePanelPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kCharStyleDockBarDDListCtrlSetWidgetID, kStylePanelPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kCharStyleDockBarButtonsCtrlSetWidgetID, kStylePanelPrefix + 28)

DECLARE_PMID(kWidgetIDSpace, kParaStyleKitPanelViewWidgetID, kStylePanelPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kParaStylePanelCtrlSetWidgetID, kStylePanelPrefix + 30)

DECLARE_PMID(kWidgetIDSpace, kCharStyleDDListWidgetID, kStylePanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kNewCharStyleDBarButtonWidgetID, kStylePanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kDeleteCharStyleDBarButtonWidgetID, kStylePanelPrefix + 33)

DECLARE_PMID(kWidgetIDSpace, kParaStyleDDListWidgetID, kStylePanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kNewParaStyleDBarButtonWidgetID, kStylePanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kDeleteParaStyleDBarButtonWidgetID, kStylePanelPrefix + 36)

DECLARE_PMID(kWidgetIDSpace, kParaStyleKitDockBarViewWidgetID, kStylePanelPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kParaStyleDockBarDDListCtrlSetWidgetID, kStylePanelPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kParaStyleDockBarButtonsCtrlSetWidgetID, kStylePanelPrefix + 39)

DECLARE_PMID(kWidgetIDSpace, kStyleTreeViewBorderWidgetID, kStylePanelPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kCharStyleControlStripWidgetID, kStylePanelPrefix + 41)

DECLARE_PMID(kWidgetIDSpace, kCharStyleIconWidgetID, kStylePanelPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kParaStyleIconWidgetID, kStylePanelPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kCharRunInStyleWidgetID, kStylePanelPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kDeleteStyleDialogWidgetID, kStylePanelPrefix + 45)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kDeleteStyleWarningIconWidgetId, kStylePanelPrefix + 46)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kDeleteStylePopupWidgetID, kStylePanelPrefix + 47)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kRemoveStyleLabelWidgetId, kStylePanelPrefix + 49)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kPreserveFormattingWidgetId, kStylePanelPrefix + 50)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kStyleDDListWidgetID, kStylePanelPrefix + 51)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kBreakLinkCharStyleButtonWidgetID, kStylePanelPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kBreakLinkParaStyleButtonWidgetID, kStylePanelPrefix + 53)


DECLARE_PMID(kWidgetIDSpace, kLoadStyleDialogWidgetID, kStylePanelPrefix + 54)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace,kMiddleLoadStyleSplitterWidgetID, kStylePanelPrefix + 55)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kLeftLoadStyleSplitterWidgetID, kStylePanelPrefix + 56)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kRightLoadStyleSplitterWidgetID, kStylePanelPrefix + 57)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kIncomingStyleTitleWidgetID, kStylePanelPrefix + 58)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kconflictResolutonTitleWidgetID, kStylePanelPrefix + 59)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kCheckAllButtonWidgetID, kStylePanelPrefix + 60)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kUnCheckAllButtonWidgetID, kStylePanelPrefix + 61)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kLoadtyleListElementWidgetID, kStylePanelPrefix + 62)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kLinkedLoadStyleSplitterWidgetID, kStylePanelPrefix + 63)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kLinkedLeftSplitterPanelWidgetID, kStylePanelPrefix + 64)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kLinkedRightSplitterPanelWidgetID, kStylePanelPrefix + 65)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kResolveStyleClashDropDownWidgetID, kStylePanelPrefix + 66)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kLoadStyleCheckBoxWidgetID, kStylePanelPrefix + 67)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kSourceIDStyleNameWidgetID, kStylePanelPrefix + 68)  //added by sasatte
DECLARE_PMID(kWidgetIDSpace, kLoadStyleListWidgetID, kStylePanelPrefix + 69) 
DECLARE_PMID(kWidgetIDSpace, kResolveStyleClashNameWidgetID, kStylePanelPrefix + 70) 
DECLARE_PMID(kWidgetIDSpace, kLoadStyleInLineEditEditingWidgetID, kStylePanelPrefix + 71) 
DECLARE_PMID(kWidgetIDSpace, kStyleIconWidgetID, kStylePanelPrefix + 72) 
DECLARE_PMID(kWidgetIDSpace, kSourceStyleInfoScrollWidgetID, kStylePanelPrefix + 73) 
DECLARE_PMID(kWidgetIDSpace, kDestStyleInfoWidgetID, kStylePanelPrefix + 74) 
DECLARE_PMID(kWidgetIDSpace, kSourceStyleInfoWidgetID, kStylePanelPrefix + 75) 
DECLARE_PMID(kWidgetIDSpace, kDestStyleInfoScrollWidgetID, kStylePanelPrefix + 76) 
DECLARE_PMID(kWidgetIDSpace, kDestStyleTitleWidgetID, kStylePanelPrefix + 77) 
DECLARE_PMID(kWidgetIDSpace, kDestStyleInfoPanelID, kStylePanelPrefix + 78) 
DECLARE_PMID(kWidgetIDSpace, kBaselineGridControlStripWidgetID, kStylePanelPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kIncomingStyleTitlePanelWidgetID, kStylePanelPrefix + 80) 
DECLARE_PMID(kWidgetIDSpace, kSelectTitlePanelWidgetID, kStylePanelPrefix + 81) 
DECLARE_PMID(kWidgetIDSpace, kTypeTitlePanelWidgetID, kStylePanelPrefix + 82) 
DECLARE_PMID(kWidgetIDSpace, kconflictResolutonTitlePanelWidgetID, kStylePanelPrefix + 83)

DECLARE_PMID(kWidgetIDSpace, kParaStyleIconId, kStylePanelPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kCharStyleIconId, kStylePanelPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kLoadStyleDialogRsrcID, kStylePanelPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kLoadStyleDropDownElementWidgetRsrcID, kStylePanelPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kLoadStyleListElementRsrcID, kStylePanelPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kJParaStyleIconId, kStylePanelPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kJCharStyleIconId, kStylePanelPrefix + 90)

DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel1WidgetId, kStylePanelPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel2WidgetId, kStylePanelPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel3WidgetId, kStylePanelPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel4WidgetId, kStylePanelPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel5WidgetId, kStylePanelPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel6WidgetId, kStylePanelPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel7WidgetId, kStylePanelPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel8WidgetId, kStylePanelPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel9WidgetId, kStylePanelPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel10WidgetId, kStylePanelPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel11WidgetId, kStylePanelPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel12WidgetId, kStylePanelPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel13WidgetId, kStylePanelPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel14WidgetId, kStylePanelPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel15WidgetId, kStylePanelPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel16WidgetId, kStylePanelPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kLoadObjectStyleDialogGenericPanel17WidgetId, kStylePanelPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kStylePanelGenericWidget1WidgetId, kStylePanelPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kStylePanelGenericWidget2WidgetId, kStylePanelPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kStylePanelGenericWidget3WidgetId, kStylePanelPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kNewCharStyleGroupButtonWidgetID, kStylePanelPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kNewParaStyleGroupButtonWidgetID, kStylePanelPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kStyleGroupOptionsDialogRsrcID, kStylePanelPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kStyleGroupOptionsDialogWidgetID, kStylePanelPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kStyleGroupOptionsDialogDialogGenericPanel1WidgetId, kStylePanelPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kStyleGroupOptionsDialogStyleGroupNameWidgetId, kStylePanelPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kStyleGroupIconWidgetID, kStylePanelPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kParaStyleListNameILEWidgetID, kStylePanelPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kCharStyleListNameILEWidgetID, kStylePanelPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kAppliedStyleStripWidgetId, kStylePanelPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kStyleTypeIconWidgetID, kStylePanelPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kApplyToAllWidgetId, kStylePanelPrefix + 122)
//icons
DECLARE_PMID(kWidgetIDSpace, kStyleFolderIconId, kStylePanelPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kStyleFolderSmallIconId, kStylePanelPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kStyleFolderWideIconId, kStylePanelPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kSelectStyleGroupDialogRsrcID, kStylePanelPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kSelectStyleGroupDialogWidgetID, kStylePanelPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kSelectStyleGroupDialogGenericPanel1WidgetId, kStylePanelPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kSelectStyleGroupTreeViewWidgetID, kStylePanelPrefix + 129)

DECLARE_PMID(kWidgetIDSpace, kReplaceWithStyleLabelWidgetId, kStylePanelPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kStyleGroupOptionsColumn1WidgetID, kStylePanelPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kStyleGroupOptionsColumn3WidgetID, kStylePanelPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kStyleGroupOptionsColumn2WidgetID, kStylePanelPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kNestedCharStyleWidgetID, kStylePanelPrefix + 134)

DECLARE_PMID(kWidgetIDSpace, kEditAllStyleToTagDialogWidgetID, kStylePanelPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kEditAllStylePanelWidgetID, kStylePanelPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kEditAllSplitterTitleOuterWidgetID, kStylePanelPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kExportMappingSplitterWidgetID, kStylePanelPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kExportLeftSplitterPanelWidgetID, kStylePanelPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kExportStylesTextWidgetID, kStylePanelPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kExportRightSplitterPanelWidgetID, kStylePanelPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kExportTagsTextWidgetID, kStylePanelPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kExportTagMappingListPanelWidgetID, kStylePanelPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kExportStyleMappingListWidgetID, kStylePanelPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kExportStyleToTagMappingListItemWidgetID, kStylePanelPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kExportTreeNodeImageIconWidgetID, kStylePanelPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kExportTreeNodeDropDownWidgetID, kStylePanelPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kExportTypeTextWidgetID, kStylePanelPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kExportTypePopupWidgetID, kStylePanelPrefix + 149)

DECLARE_PMID(kWidgetIDSpace, kPDFEditAllStylePanelWidgetID, kStylePanelPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kPDFEditAllSplitterTitleOuterWidgetID, kStylePanelPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kPDFMappingSplitterWidgetID, kStylePanelPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kPDFLeftSplitterPanelWidgetID, kStylePanelPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kPDFExportStylesTextWidgetID, kStylePanelPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kPDFRightSplitterPanelWidgetID, kStylePanelPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kPDFExportTagsTextWidgetID, kStylePanelPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kPDFTagMappingListPanelWidgetID, kStylePanelPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kPDFStyleMappingListWidgetID, kStylePanelPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kExportStyleToPDFTagMappingListItemWidgetID, kStylePanelPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kExportClassTextWidgetID, kStylePanelPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kExportTagSplitterPanelWidgetID, kStylePanelPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kExportTreeNodeClassEditBoxWidgetID, kStylePanelPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, k2ndExportMappingSplitterWidgetID, kStylePanelPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kEPUBExportTypeRadioWidgetID, kStylePanelPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kPDFExportTypeRadioWidgetID, kStylePanelPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kExportTypeRadioWidgetID, kStylePanelPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, k3rdExportMappingSplitterWidgetID, kStylePanelPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kExportBreakEPUBSplitterPanelWidgetID, kStylePanelPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kExportBreakEPUBCheckboxWidgetID, kStylePanelPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kExportEmitCSSSplitterPanelWidgetID, kStylePanelPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kExportEmitCSSCheckboxWidgetID, kStylePanelPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, k4thExportMappingSplitterWidgetID, kStylePanelPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kExportCharStyleToCCLibrariesButtonWidgetID, kStylePanelPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kExportParaStyleToCCLibrariesButtonWidgetID, kStylePanelPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kHighlightOverrideButtonId, kStylePanelPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kIncludeInHTMLSplitterPanelWidgetID, kStylePanelPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kIncludeInHTMLCheckboxWidgetID, kStylePanelPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, k5thExportMappingSplitterWidgetID, kStylePanelPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kCharParaStylesKitWidgetID, kStylePanelPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kCharParaStylesBarWidgetID, kStylePanelPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kCreateStyleWidgetID, kStylePanelPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kNewStyleNameWidgetID, kStylePanelPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kDeleteStylesIconID, kStylePanelPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kStyleTreeElementWidgetID, kStylePanelPrefix + 184)
//DECLARE_PMID(kWidgetIDSpace, kStyleInfoWidgetID, kStylePanelPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kStyleSampleTextWidgetID, kStylePanelPrefix + 186)
DECLARE_PMID(kWidgetIDSpace, kTreeViewWidgetID, kStylePanelPrefix + 187)
DECLARE_PMID(kWidgetIDSpace, kFolderIconWidgetID, kStylePanelPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kManageStylesIconWidgetID, kStylePanelPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kManageStylesTextWidgetID, kStylePanelPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kManageStylesElementWidgetID, kStylePanelPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kStyleNameWidgetID, kStylePanelPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kOverrideStyleWidgetID, kStylePanelPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kRedefineStyleWidgetID, kStylePanelPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kOpenStyleDialogWidgetID, kStylePanelPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kParaStylePropertiesPanelIconWidgetID, kStylePanelPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kCharStylePropertiesPanelIconWidgetID, kStylePanelPrefix + 197)

// <Implementation ID>
// ImplementationIDs

DECLARE_PMID(kImplementationIDSpace, kStylePanelKitViewImpl, kStylePanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCharacterStyleDropDownObserverImpl, kStylePanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCharStyleViewImpl, kStylePanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kParaStyleViewImpl, kStylePanelPrefix + 4)

DECLARE_PMID(kImplementationIDSpace, kCharStyleTreeViewObserverImpl, kStylePanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kParaStyleTreeViewObserverImpl, kStylePanelPrefix + 6)

DECLARE_PMID(kImplementationIDSpace, kNewCharStyleButtonObserverImpl, kStylePanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kNewParaStyleButtonObserverImpl, kStylePanelPrefix + 8)

DECLARE_PMID(kImplementationIDSpace, kDeleteCharStyleButtonObserverImpl, kStylePanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kDeleteParaStyleButtonObserverImpl, kStylePanelPrefix + 10)

DECLARE_PMID(kImplementationIDSpace, kCharStylePanelMenuComponentImpl, kStylePanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kParaStylePanelMenuComponentImpl, kStylePanelPrefix + 12)

DECLARE_PMID(kImplementationIDSpace, kStylePanelUIDDataImpl, kStylePanelPrefix + 13)

DECLARE_PMID(kImplementationIDSpace, kCharStyleListElementEHImpl, kStylePanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kParaStyleListElementEHImpl, kStylePanelPrefix + 15)

DECLARE_PMID(kImplementationIDSpace, kCharImportedTypeIconViewImpl, kStylePanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kParaImportedTypeIconViewImpl, kStylePanelPrefix + 17	)

DECLARE_PMID(kImplementationIDSpace, kDeleteButtonCharDragDropTargetImpl, kStylePanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kDeleteButtonParaDragDropTargetImpl, kStylePanelPrefix + 19)

DECLARE_PMID(kImplementationIDSpace, kNewButtonCharDragDropTargetImpl, kStylePanelPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kNewButtonParaDragDropTargetImpl, kStylePanelPrefix + 21)

//DECLARE_PMID(kImplementationIDSpace, kCopyStyleCmdImpl, kStylePanelPrefix + 22)

DECLARE_PMID(kImplementationIDSpace, kCharStyleListDEHandlerImpl, kStylePanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kParaStyleListDEHandlerImpl, kStylePanelPrefix + 24)

DECLARE_PMID(kImplementationIDSpace, kCharStyleListDragDropSourceImpl, kStylePanelPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kParaStyleListDragDropSourceImpl, kStylePanelPrefix + 26)

DECLARE_PMID(kImplementationIDSpace, kStyleElementResizeRuleImpl, kStylePanelPrefix + 27)
//DECLARE_PMID(kImplementationIDSpace, kLoadStyleCmd, kStylePanelPrefix + 28)
//DECLARE_PMID(kImplementationIDSpace, kReplaceStyleCmd, kStylePanelPrefix + 29)
//DECLARE_PMID(kImplementationIDSpace, kEditStyleCmd, kStylePanelPrefix + 30)

DECLARE_PMID(kImplementationIDSpace, kCharStyleShortCutView, kStylePanelPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kParaStyleShortCutView, kStylePanelPrefix + 32	)

//gap
//DECLARE_PMID(kImplementationIDSpace, kStyleListBoxControllerImpl, kStylePanelPrefix + 33)

DECLARE_PMID(kImplementationIDSpace, kParaStyleSyncServiceImpl, kStylePanelPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kCharStyleSyncServiceImpl, kStylePanelPrefix + 35)

DECLARE_PMID(kImplementationIDSpace, kCharStyleDDListObserverImpl, kStylePanelPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kDeleteCharStyleDBarButtonObserverImpl, kStylePanelPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kNewCharStyleDBarButtonObserverImpl, kStylePanelPrefix + 38)

DECLARE_PMID(kImplementationIDSpace, kParaStyleDDListObserverImpl, kStylePanelPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kDeleteParaStyleDBarButtonObserverImpl, kStylePanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kNewParaStyleDBarButtonObserverImpl, kStylePanelPrefix + 41)

// Tree view stuff
DECLARE_PMID(kImplementationIDSpace, kCharStyleTreeViewAdapterImpl, kStylePanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kCharStyleTreeViewWidgetMgrImpl, kStylePanelPrefix + 43)

DECLARE_PMID(kImplementationIDSpace, kParaStyleTreeViewAdapterImpl, kStylePanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kParaStyleTreeViewWidgetMgrImpl, kStylePanelPrefix + 45)
//gap
DECLARE_PMID(kImplementationIDSpace, kDeleteStyleDialogImpl, kStylePanelPrefix+49) //added by sasatte
DECLARE_PMID(kImplementationIDSpace, kDeleteStyleDialogObsImpl, kStylePanelPrefix+50) //added by sasatte
DECLARE_PMID(kImplementationIDSpace, kExportCharStyleToCCLibrariesButtonObserverImpl, kStylePanelPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kExportParaStyleToCCLibrariesButtonObserverImpl, kStylePanelPrefix + 52)
// gap

//DECLARE_PMID(kImplementationIDSpace, kParaStyleSyncServiceImpl, kStylePanelPrefix + 56)
//DECLARE_PMID(kImplementationIDSpace, kCharStyleSyncServiceImpl, kStylePanelPrefix + 58)
//DECLARE_PMID(kImplementationIDSpace, kRemoveRedundantOverridesCmd, kStylePanelPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kControlStripStyleSuiteImpl, kStylePanelPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kControlStripStyleRegisterImpl, kStylePanelPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kControlStripStyleDefaultSuiteImpl, kStylePanelPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kControlStripStyleDefaultRegisterImpl, kStylePanelPrefix + 63)

DECLARE_PMID(kImplementationIDSpace, kStyleListContextMenuImpl, kStylePanelPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kParaStyleTreeViewTypeAheadImpl, kStylePanelPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kCharStyleTreeViewTypeAheadImpl, kStylePanelPrefix + 66)

//gap

DECLARE_PMID(kImplementationIDSpace, kParaCharLoadStyleDialogImpl, kStylePanelPrefix + 69)
// gap
DECLARE_PMID(kImplementationIDSpace, kParaCharLoadStyleDialogObserverImpl, kStylePanelPrefix + 71)

DECLARE_PMID(kImplementationIDSpace, kClearOverridesButtonObserverImpl, kStylePanelPrefix + 72)

DECLARE_PMID(kImplementationIDSpace, kCharStyleOverridesToolTipImpl, kStylePanelPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kParaStyleOverridesToolTipImpl, kStylePanelPrefix + 74)

DECLARE_PMID(kImplementationIDSpace, kNewParaStyleGroupButtonObserverImpl, kStylePanelPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kNewCharStyleGroupButtonObserverImpl, kStylePanelPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kStyleGroupOptionsDialogControllerImpl, kStylePanelPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kStyleGroupOptionsDialogObserverImpl, kStylePanelPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kStyleGroupActionDataImpl, kStylePanelPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kStyleNameTextValidationImpl, kStylePanelPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kParaStyleNameInLineEditObserverImpl, kStylePanelPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kCharStyleNameInLineEditObserverImpl, kStylePanelPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kParaStyleNameILEEditingAttributesImpl, kStylePanelPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kCharStyleNameILEEditingAttributesImpl, kStylePanelPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kIntoParaStyleDDTargetImpl, kStylePanelPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kIntoCharStyleDDTargetImpl, kStylePanelPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kNextParaStyleDDTargetImpl, kStylePanelPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kNextCharStyleDDTargetImpl, kStylePanelPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kNewButtonCharStyleGroupDragDropTargetImpl, kStylePanelPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kNewButtonParaStyleGroupDragDropTargetImpl, kStylePanelPrefix + 90)

DECLARE_PMID(kImplementationIDSpace, kCharStylePanelTreeViewMgrImpl, kStylePanelPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kParaStylePanelTreeViewMgrImpl, kStylePanelPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kParaStyleTreeControlViewImpl, kStylePanelPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kCharStyleTreeControlViewImpl, kStylePanelPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kAppliedParaStyleStaticTextEHImpl, kStylePanelPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kAppliedCharStyleStaticTextEHImpl, kStylePanelPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kPrivateStyleUIUtilsImpl, kStylePanelPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kSelectStyleGroupDialogControllerImpl, kStylePanelPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kTextStyleQuickApplyServiceImpl, kStylePanelPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kStyleNameInLineEditControllerImpl, kStylePanelPrefix + 100)

DECLARE_PMID(kImplementationIDSpace, kEditAllStyleToTagDialogControllerImpl, kStylePanelPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kExportMappingStyleViewWidgetMgrImpl, kStylePanelPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kExportMappingStyleTreeViewAdaptorImpl, kStylePanelPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kExportMappingDialogSingleClickEHImpl, kStylePanelPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kExportTagControllerImpl, kStylePanelPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kExportTagDropDownTypeAheadImpl, kStylePanelPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kExportStyleMappingNodeObserverImpl, kStylePanelPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kEVEExportTypeWidgetObserverImpl, kStylePanelPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kStyleToExportTagMapImpl, kStylePanelPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kStyleToTagBreakEPUBCheckBoxEHImpl, kStylePanelPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kStyleToTagEmitCSSCheckBoxEHImpl, kStylePanelPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kHighlightOverrideButtonObserverImpl, kStylePanelPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kHighlightOverrideButtonTipImpl, kStylePanelPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kCharParaStylePropsPanelObserverImpl, kStylePanelPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kCStylePropsPanelGroupListControlDataImpl, kStylePanelPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kStyleGroupPropsPanelDDElementViewImpl, kStylePanelPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kStylePropsPanelGroupOwnerDrawDDItemImpl, kStylePanelPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kStyleNameEditBoxWidgetEHImpl, kStylePanelPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kStylePopupTreeControlViewImpl, kStylePanelPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kDVStylePopupTreeNodeViewImpl, kStylePanelPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kDV_StyleSampleTextViewImpl, kStylePanelPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kCharStylePopupTreeViewWidgetMgrImpl, kStylePanelPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kParaStylePopupTreeViewWidgetMgrImpl, kStylePanelPrefix + 124)
//DECLARE_PMID(kImplementationIDSpace, kDV_StyleInfoTextViewImpl, kStylePanelPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kStylePopupTreeNodeEHImpl, kStylePanelPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kStyleDropDownObserverImpl, kStylePanelPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kStyleUIDToIndexMapImpl, kStylePanelPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kParaStyleDropDownRelatedDataImpl, kStylePanelPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kCharStyleDropDownRelatedDataImpl, kStylePanelPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kDV_ManageStylesTextViewImpl, kStylePanelPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kDV_TreeBasedPopupWindowImpl, kStylePanelPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kParaStyleTreeBasedPopupFlyoutViewImpl, kStylePanelPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kCharStyleTreeBasedPopupFlyoutViewImpl, kStylePanelPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kDV_ManageStylesNodeViewImpl, kStylePanelPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kDV_StyleNameTextViewImpl, kStylePanelPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kStylePopupTreeExpanderWidgetEHImpl, kStylePanelPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kStylePopupEventHandlerImpl, kStylePanelPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kDrawStylePreviewUtilsImpl, kStylePanelPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kCreateStyleIconTipImpl, kStylePanelPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kStyleDropDownEventHandlerImpl, kStylePanelPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kOpenStyleDialogButtonEHImpl, kStylePanelPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kParaStylePropertiesPanelMenuComponentImpl, kStylePanelPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kCharStylePropertiesPanelMenuComponentImpl, kStylePanelPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kOpenStyleDialogButtonViewImpl, kStylePanelPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kExpanderCollapseObserverImpl, kStylePanelPrefix + 146)

// <Interface ID>
// Interface ID
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEDIALOGINTDATA, kStylePanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEPANELUIDLIST, kStylePanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEPANELPREFS, kStylePanelPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPSTYLESUITE, kStylePanelPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPSTYLEDEFAULTSUITE, kStylePanelPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERCANCELLEDBOOLDATA, kStylePanelPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEGROUPACTIONDATA, kStylePanelPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWAPPLYTOALLBOOLDATA, kStylePanelPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEGROUPUIDDATA, kStylePanelPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENEDPARASTYLEGROUPLISTDATA, kStylePanelPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENEDCHARSTYLEGROUPLISTDATA, kStylePanelPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATESTYLEUIUTILS, kStylePanelPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLIEDSTYLESTATICTEXTBOOLDATA, kStylePanelPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTMAPOBSERVER, kStylePanelPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLETOEXPORTTAGMAP, kStylePanelPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMDDITEM, kStylePanelPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPSPANELSTYLETYPE, kStylePanelPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDTOINDEXMAP, kStylePanelPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPDOWNDATA, kStylePanelPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDMANAGESTYLEWIDGET, kStylePanelPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLETEXTDATA, kStylePanelPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWSTYLEPREVIEWUTILS, kStylePanelPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENDIALOGBOOLDATA, kStylePanelPrefix + 23)

// <Service ID>
// Service IDs
DECLARE_PMID(kServiceIDSpace, kStyleOptionDialogService, kStylePanelPrefix + 1)

// Messages ID
DECLARE_PMID(kMessageIDSpace, kEnableCharDeleteButtonMsg, kStylePanelPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kDisableCharDeleteButtonMsg, kStylePanelPrefix + 2)
DECLARE_PMID(kMessageIDSpace, kStyleSelectedMsg, kStylePanelPrefix + 3)
DECLARE_PMID(kMessageIDSpace, kNoStyleSelectedMsg, kStylePanelPrefix + 4)
DECLARE_PMID(kMessageIDSpace, kDisableParaDeleteButtonMsg, kStylePanelPrefix + 5)
DECLARE_PMID(kMessageIDSpace, kEnableParaDeleteButtonMsg, kStylePanelPrefix + 6)

DECLARE_PMID(kMessageIDSpace, kRemoveOverrideIconMsg, kStylePanelPrefix + 7)
DECLARE_PMID(kMessageIDSpace, kAddOverrideIconMsg, kStylePanelPrefix + 8)

DECLARE_PMID(kMessageIDSpace, kMultipleStylesSelectedMsg, kStylePanelPrefix + 9)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kCharacterStylesPanelActionID, kStylePanelPrefix + 1)
DECLARE_PMID(kActionIDSpace, kParagraphStylesPanelActionID, kStylePanelPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDeleteParaStyleActionID, kStylePanelPrefix + 3)
DECLARE_PMID(kActionIDSpace, kDuplicateCharStyleActionID, kStylePanelPrefix + 4)
DECLARE_PMID(kActionIDSpace, kCharStyleOptionsActionID, kStylePanelPrefix + 5)
DECLARE_PMID(kActionIDSpace, kSelectAllUnusedCharStylesActionID, kStylePanelPrefix + 6)
DECLARE_PMID(kActionIDSpace, kLoadParaStylesActionID, kStylePanelPrefix + 7)
DECLARE_PMID(kActionIDSpace, kLoadCharStylesActionID, kStylePanelPrefix + 8)
DECLARE_PMID(kActionIDSpace, kCharLoadAllStylesActionID, kStylePanelPrefix + 9)
DECLARE_PMID(kActionIDSpace, kRedefineParaStyleActionID, kStylePanelPrefix + 10)
DECLARE_PMID(kActionIDSpace, kRedefineCharStyleActionID, kStylePanelPrefix + 11)
DECLARE_PMID(kActionIDSpace, kSmallCharPaletteRowsActionID, kStylePanelPrefix + 12)
DECLARE_PMID(kActionIDSpace, kSmallParaPaletteRowsActionID, kStylePanelPrefix + 13)
DECLARE_PMID(kActionIDSpace, kNewCharStyleActionID, kStylePanelPrefix + 14)
DECLARE_PMID(kActionIDSpace, kNewParaStyleActionID, kStylePanelPrefix + 15)
DECLARE_PMID(kActionIDSpace, kCharStylePopupSep1ActionID, kStylePanelPrefix + 16)
DECLARE_PMID(kActionIDSpace, kCharStylePopupSep2ActionID, kStylePanelPrefix + 17)
DECLARE_PMID(kActionIDSpace, kCharStylePopupSep3ActionID, kStylePanelPrefix + 18)
DECLARE_PMID(kActionIDSpace, kCharStylePopupSep4ActionID, kStylePanelPrefix + 19)
DECLARE_PMID(kActionIDSpace, kCharStylePopupSep5ActionID, kStylePanelPrefix + 20)
DECLARE_PMID(kActionIDSpace, kParaStylePopupSep1ActionID, kStylePanelPrefix + 21)
DECLARE_PMID(kActionIDSpace, kParaStylePopupSep2ActionID, kStylePanelPrefix + 22)
DECLARE_PMID(kActionIDSpace, kParaStylePopupSep3ActionID, kStylePanelPrefix + 23)
DECLARE_PMID(kActionIDSpace, kParaStylePopupSep4ActionID, kStylePanelPrefix + 24)
DECLARE_PMID(kActionIDSpace, kParaStylePopupSep5ActionID, kStylePanelPrefix + 25)
DECLARE_PMID(kActionIDSpace, kSelectAllUnusedParaStylesActionID, kStylePanelPrefix + 26)
DECLARE_PMID(kActionIDSpace, kDeleteCharStyleActionID, kStylePanelPrefix + 27)
DECLARE_PMID(kActionIDSpace, kConvertStyleBNToTextActionID, kStylePanelPrefix + 28)
DECLARE_PMID(kActionIDSpace, kContextMenuConvertBNStyleActionID, kStylePanelPrefix + 29)

DECLARE_PMID(kActionIDSpace, kClearAllOverridesStyleActionID, kStylePanelPrefix + 30)
DECLARE_PMID(kActionIDSpace, kClearCharacterOverridesStyleActionID, kStylePanelPrefix + 31)

DECLARE_PMID(kActionIDSpace, kParaLoadAllStylesActionID, kStylePanelPrefix + 32)
DECLARE_PMID(kActionIDSpace, kParaStyleOptionsActionID, kStylePanelPrefix + 33)
DECLARE_PMID(kActionIDSpace, kDuplicateParaStyleActionID, kStylePanelPrefix + 34)

DECLARE_PMID(kActionIDSpace, kContextMenuStyleOptionsActionID, kStylePanelPrefix + 35)
DECLARE_PMID(kActionIDSpace, kContextMenuDuplicateStyleActionID, kStylePanelPrefix + 36)
DECLARE_PMID(kActionIDSpace, kContextMenuDeleteStyleActionID, kStylePanelPrefix + 37)
DECLARE_PMID(kActionIDSpace, kContextMenuRedefineStyleActionID, kStylePanelPrefix + 38)

DECLARE_PMID(kActionIDSpace, kClearParagraphOverridesStyleActionID, kStylePanelPrefix + 39)

DECLARE_PMID(kActionIDSpace, kContextMenuApplyStyleActionID, kStylePanelPrefix + 40)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyStyleRemoveOActionID, kStylePanelPrefix + 41)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyStyleRemoveCSActionID, kStylePanelPrefix + 42)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyStyleRemoveAllActionID, kStylePanelPrefix + 43)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyNStyleActionID, kStylePanelPrefix + 44)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyNStyleRemoveOActionID, kStylePanelPrefix + 45)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyNStyleRemoveCSActionID, kStylePanelPrefix + 46)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyNStyleRemoveAllActionID, kStylePanelPrefix + 47)
DECLARE_PMID(kActionIDSpace, kCharStylePopupSep6ActionID, kStylePanelPrefix + 49)
DECLARE_PMID(kActionIDSpace, kParaClearOverridesActionID, kStylePanelPrefix + 50)
DECLARE_PMID(kActionIDSpace, kParaStylePopupSep6ActionID, kStylePanelPrefix + 51)

DECLARE_PMID(kActionIDSpace, kParaBreakLinkActionID, kStylePanelPrefix + 52)
DECLARE_PMID(kActionIDSpace, kCharBreakLinkActionID, kStylePanelPrefix + 53)

//Style set related
DECLARE_PMID(kActionIDSpace, kParaNewStyleGroupActionID, kStylePanelPrefix + 54)
DECLARE_PMID(kActionIDSpace, kParaOpenAllStyleGroupsActionID, kStylePanelPrefix + 55)
DECLARE_PMID(kActionIDSpace, kParaCloseAllStyleGroupsActionID, kStylePanelPrefix + 56)
DECLARE_PMID(kActionIDSpace, kParaSortByNameActionID, kStylePanelPrefix + 57)
DECLARE_PMID(kActionIDSpace, kParaStylePopupSep7ActionID, kStylePanelPrefix + 58)
DECLARE_PMID(kActionIDSpace, kParaStylePopupSep8ActionID, kStylePanelPrefix + 59)

DECLARE_PMID(kActionIDSpace, kCharNewStyleGroupActionID, kStylePanelPrefix + 60)
DECLARE_PMID(kActionIDSpace, kCharOpenAllStyleGroupsActionID, kStylePanelPrefix + 61)
DECLARE_PMID(kActionIDSpace, kCharCloseAllStyleGroupsActionID, kStylePanelPrefix + 62)
DECLARE_PMID(kActionIDSpace, kCharSortByNameActionID, kStylePanelPrefix + 63)
DECLARE_PMID(kActionIDSpace, kCharStylePopupSep7ActionID, kStylePanelPrefix + 64)
DECLARE_PMID(kActionIDSpace, kCharStylePopupSep8ActionID, kStylePanelPrefix + 65)

//Style set context menu
DECLARE_PMID(kActionIDSpace, kContextMenuStyleGroupOptoinsActionID, kStylePanelPrefix + 66)
DECLARE_PMID(kActionIDSpace, kContextMenuDuplicateStyleGroupActionID, kStylePanelPrefix + 67)
DECLARE_PMID(kActionIDSpace, kContextMenuDeleteStyleGroupActionID, kStylePanelPrefix + 68)

DECLARE_PMID(kActionIDSpace, kCharCopyToStyleGroupActionID, kStylePanelPrefix + 69)
DECLARE_PMID(kActionIDSpace, kParaCopyToStyleGroupActionID, kStylePanelPrefix + 70)
DECLARE_PMID(kActionIDSpace, kParaStylePopupSep9ActionID, kStylePanelPrefix + 71)
DECLARE_PMID(kActionIDSpace, kCharStylePopupSep9ActionID, kStylePanelPrefix + 72)
DECLARE_PMID(kActionIDSpace, kContextMenuCopyToStyleGroupActionID, kStylePanelPrefix + 73)
DECLARE_PMID(kActionIDSpace, kContextMenuCreateStyleGroupActionID, kStylePanelPrefix + 74)
DECLARE_PMID(kActionIDSpace, kParaCreateStyleGroupActionID, kStylePanelPrefix + 75)
DECLARE_PMID(kActionIDSpace, kCharCreateStyleGroupActionID, kStylePanelPrefix + 76)
DECLARE_PMID(kActionIDSpace, kContextMenuCreateStyleInGroupActionID, kStylePanelPrefix + 77)
DECLARE_PMID(kActionIDSpace, kQuickApplyParaStyleGroupPrefActionID, kStylePanelPrefix + 78)
DECLARE_PMID(kActionIDSpace, kQuickApplyCharStyleGroupPrefActionID, kStylePanelPrefix + 79)

DECLARE_PMID(kActionIDSpace, kNewCharStyleDuringDialogActionID, kStylePanelPrefix + 80)
DECLARE_PMID(kActionIDSpace, kNewParaStyleDuringDialogActionID, kStylePanelPrefix + 81)

DECLARE_PMID(kActionIDSpace, kEditAllStyleToTagParaStylesActionID, kStylePanelPrefix + 82)
DECLARE_PMID(kActionIDSpace, kEditAllStyleToTagCharStylesActionID, kStylePanelPrefix + 83)

DECLARE_PMID(kActionIDSpace, kToggleStylePreviewModeParaPanelActionID, kStylePanelPrefix + 84)
DECLARE_PMID(kActionIDSpace, kToggleStylePreviewModeCharPanelActionID, kStylePanelPrefix + 85)
DECLARE_PMID(kActionIDSpace, kManageStylesActionID, kStylePanelPrefix + 86)


//DECLARE_PMID(kActionIDSpace, kManageParaStylesPropertiesActionID, kStylePanelPrefix + 87)
DECLARE_PMID(kActionIDSpace, kDuplicateParaStylePropertiesActionID, kStylePanelPrefix + 88)
DECLARE_PMID(kActionIDSpace, kDeleteParaStylePropertiesActionID, kStylePanelPrefix + 89)
DECLARE_PMID(kActionIDSpace, kConvertStyleBNToTextPropertiesActionID, kStylePanelPrefix + 90)
DECLARE_PMID(kActionIDSpace, kParaStyleOptionsPropertiesActionID, kStylePanelPrefix + 91)
DECLARE_PMID(kActionIDSpace, kParaBreakLinkPropertiesActionID, kStylePanelPrefix + 92)
DECLARE_PMID(kActionIDSpace, kLoadParaStylesPropertiesActionID, kStylePanelPrefix + 93)
DECLARE_PMID(kActionIDSpace, kParaLoadAllStylesPropertiesActionID, kStylePanelPrefix + 94)
//gap
//DECLARE_PMID(kActionIDSpace, kManageCharStylesPropertiesActionID, kStylePanelPrefix + 95)
DECLARE_PMID(kActionIDSpace, kDuplicateCharStylePropertiesActionID, kStylePanelPrefix + 96)
DECLARE_PMID(kActionIDSpace, kDeleteCharStylePropertiesActionID, kStylePanelPrefix + 97)
DECLARE_PMID(kActionIDSpace, kCharStyleOptionsPropertiesActionID, kStylePanelPrefix + 98)
DECLARE_PMID(kActionIDSpace, kCharBreakLinkPropertiesActionID, kStylePanelPrefix + 99)
DECLARE_PMID(kActionIDSpace, kLoadCharStylesPropertiesActionID, kStylePanelPrefix + 100)
DECLARE_PMID(kActionIDSpace, kCharLoadAllStylesPropertiesActionID, kStylePanelPrefix + 101)
#endif // __StylePanelID__
