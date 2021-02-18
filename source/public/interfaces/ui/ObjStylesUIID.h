//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ObjStylesUIID.h $
//  
//  Owner: Danielle Darling
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

#ifndef __ObjStylesUIID__
#define __ObjStylesUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kObjStylesUIPrefix		RezLong(0x1ba00)			
#define kObjStylesUIPrefix2		RezLong(0x1f800)	
// <Start IDC>
// PluginID
#define kObjStylesUIPluginName						"ObjectStylesUI"
DECLARE_PMID(kPlugInIDSpace, kObjStylesUIPluginID, kObjStylesUIPrefix + 1)

// Resource IDs
#define kObjStylesTreeViewPanelRsrcID				1000
#define kObjStylesUIStringsRsrcID					1100
#define kObjStylesUIActionResID						1200
#define kObjectStylesKitListRsrcID					1300
#define kObjStylesTreeViewSmallNodeRsrcID			1400
#define kObjStylesStringsNoTransRsrcID				1500
#define kObjStylesLargeTreeNodeRsrcID				1600
#define kObjStylesSmallTreeNodeRsrcID				1700
#define kDeleteObjStylesDialogRsrcID				1800
#define kObjStylesSelDialogOrderingRsrcID           1900
#define kObjStylesSelDialogRsrcID					2000
#define kObjStylesGeneralPanelRsrcID				2100
#define kObjStylesGeneralPanelCreatorRsrcID			2200
#define kObjStylesFillPanelRsrcID					2300
#define kObjStylesFillPanelCreatorRsrcID			2400
#define kObjStylesStrokeOptionsPanelRsrcID			2500
#define kObjStylesStrokeOptionsPanelCreatorRsrcID	2600
#define kObjStylesTransparencyPanelRsrcID			2700
#define kObjStylesTransparencyPanelCreatorRsrcID	2800
#define kObjStylesDropShadowPanelRsrcID				2900
#define kObjStylesDropShadowPanelCreatorRsrcID		3000
#define kObjStylesStrokePanelRsrcID					3100
#define kObjStylesStrokePanelCreatorRsrcID			3200
#define kObjStyleDropDownElementRsrcID				3300
#define kObjStylesSelDialogGroupTreeNodeRsrcID		3350
#define kObjStylesSelDialogNoCheckBoxTreeNodeRsrcID	3375
#define kObjStylesSelDialogLeafTreeNodeRsrcID		3400
#define kObjStylesSummaryTreeNodeRsrcID				3500
#define kObjStylesParaStylePanelCreatorRsrcID		3600
#define kObjStylesParaStylePanelRsrcID				3700
#define kLoadObjectStyleDialogRsrcID				3800
#define kLoadObjectStyleListElementRsrcID			3900

#define kObjStylesPanelMenuRsrcID					4000
#define kObjStylesPanelActionRsrcID					4100

#define kObjectFCFillPanelRsrcID					4200
#define kObjectFCFillPanelCreatorRsrcID				4300
#define kObjectFCStrokePanelRsrcID					4400
#define kObjectFCStrokePanelCreatorRsrcID			4500

#define kStyleToTagObjStylesDialogRsrcID			5000
#define kStyleToTagObjStylesCreatorRsrcID		    5200
#define kObjStylesTransformAttrsPanelCreatorRsrcID  5300
#define kObjStylesTransformAttrsPanelRsrcID              5400
	

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kObjStylesTreeViewPanelBoss,		kObjStylesUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kObjStylesTreeViewWidgetBoss,		kObjStylesUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kObjStylesPanelMenuComponentBoss,	kObjStylesUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kObjStylesNewButtonBoss,			kObjStylesUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kObjStylesDeleteButtonBoss,			kObjStylesUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kObjStylesTreeNodeWidgetBoss,		kObjStylesUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kObjStylesZOrderDEHandlerBoss,		kObjStylesUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kDeleteObjStylesDialogWidgetBoss,	kObjStylesUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kPageItemDDTargetOSFlavorHelperBoss,  kObjStylesUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kObjStylesSelDialogWidgetBoss,		kObjStylesUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kObjStylesNameWidgetBoss,			kObjStylesUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kObjStylesGeneralPanelWidgetBoss,   kObjStylesUIPrefix + 12)
// gap
DECLARE_PMID(kClassIDSpace, kObjStyleKBShortCutWidgetBoss,		kObjStylesUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kObjStylesFillPanelWidgetBoss,		kObjStylesUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kObjStylesStrokePanelWidgetBoss,	kObjStylesUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kObjStylesStrokeOptionsPanelWidgetBoss,	kObjStylesUIPrefix + 17)
DECLARE_PMID(kClassIDSpace, kObjStylesTransparencyPanelWidgetBoss,	kObjStylesUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, kObjStylesDropShadowPanelWidgetBoss,	kObjStylesUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, kObjStylesParaStylePanelWidgetBoss,		kObjStylesUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kObjStyleCurrentActionWidgetBoss,		kObjStylesUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kObjStylesBreaklinkButtonBoss,			kObjStylesUIPrefix + 22)
//gap
DECLARE_PMID(kClassIDSpace, kObjStylesColorStrokeFillObserverBoss,	kObjStylesUIPrefix + 24)
DECLARE_PMID(kClassIDSpace, kObjStyleIconButtonBoss,		kObjStylesUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, kObjStyleDDListBoss,			kObjStylesUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, kObjStyleControlStripBoss,		kObjStylesUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kControlStripObjStyleRegisterBoss, kObjStylesUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kObjStyleDropDownElementBoss,	kObjStylesUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kObjStyleViewBoss,				kObjStylesUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kObjStylesSelDialogTreeViewWidgetBoss,	kObjStylesUIPrefix + 31)
DECLARE_PMID(kClassIDSpace, kObjStylesSelDialogTreeNodeWidgetBoss,	kObjStylesUIPrefix + 32)
DECLARE_PMID(kClassIDSpace, kObjStylesSelDialogTNLeafCheckBoxWidgetBoss,kObjStylesUIPrefix + 33)
DECLARE_PMID(kClassIDSpace, kObjStyleTreeNodeContextMenuBoss,		kObjStylesUIPrefix + 34)
DECLARE_PMID(kClassIDSpace, kObjStylesSummaryTreeNodeWidgetBoss,	kObjStylesUIPrefix + 35)
DECLARE_PMID(kClassIDSpace, kObjStylesSummaryTreeViewWidgetBoss,	kObjStylesUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kObjStylesSummaryTreeNodeTextWidgetBoss,kObjStylesUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kObjStylesTreeNodeNameViewBoss,			kObjStylesUIPrefix + 38)
DECLARE_PMID(kClassIDSpace, kObjStylesTreeNodeShortCutBoss,			kObjStylesUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kObjStylesTreeNodeIconBoss,				kObjStylesUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kOSTextDefaultMenuComponentBoss,		kObjStylesUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, kDefaultTextObjStyleIconBoss,			kObjStylesUIPrefix + 42)
DECLARE_PMID(kClassIDSpace, kDefaultTextObjStyleHandlerBoss,		kObjStylesUIPrefix + 43)
DECLARE_PMID(kClassIDSpace, kLoadObjectStyleDialogBoss,				kObjStylesUIPrefix + 44)
DECLARE_PMID(kClassIDSpace, kDefaultGraphicObjStyleHandlerBoss,		kObjStylesUIPrefix + 45)
DECLARE_PMID(kClassIDSpace, kOSGraphicDefaultMenuComponentBoss,		kObjStylesUIPrefix + 46)
DECLARE_PMID(kClassIDSpace, kObjStylesSelDialogTreeNodeTextWidgetBoss, kObjStylesUIPrefix + 47)
DECLARE_PMID(kClassIDSpace, kObjStylesClearOverrideButtonBoss,		kObjStylesUIPrefix + 48)
DECLARE_PMID(kClassIDSpace, kOSFrameGridDefaultMenuComponentBoss,	kObjStylesUIPrefix + 49)
DECLARE_PMID(kClassIDSpace, kDefaultFrameGridObjStyleHandlerBoss,   kObjStylesUIPrefix + 50)
DECLARE_PMID(kClassIDSpace, kObjStylesClearOverrideNoneButtonBoss,  kObjStylesUIPrefix + 51)
DECLARE_PMID(kClassIDSpace, kObjectStyleTestMenuBoss,  				kObjStylesUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kNewObjStyleGroupButtonBoss,  			kObjStylesUIPrefix + 53)
DECLARE_PMID(kClassIDSpace, kAppliedObjectStyleStaticTextBoss,  	kObjStylesUIPrefix + 54)
DECLARE_PMID(kClassIDSpace, kEditableObjectStyleNameWidgetBoss,  	kObjStylesUIPrefix + 55)
DECLARE_PMID(kClassIDSpace, kObjStylesAnyValueSupportedCheckBoxWidgetBoss, kObjStylesUIPrefix + 56)
DECLARE_PMID(kClassIDSpace, kObjStylesSimpleIconSuiteButtonWidgetBoss, kObjStylesUIPrefix + 57)
DECLARE_PMID(kClassIDSpace, kObjStylesSelDialogTNGroupCheckBoxWidgetBoss, kObjStylesUIPrefix + 58)
DECLARE_PMID(kClassIDSpace, kObjectStyleQuickApplyServiceBoss, kObjStylesUIPrefix + 59)
DECLARE_PMID(kClassIDSpace, kObjectFCFillPanelWidgetBoss,			kObjStylesUIPrefix + 60)
DECLARE_PMID(kClassIDSpace, kObjectFCStrokePanelWidgetBoss,			kObjStylesUIPrefix + 61)
DECLARE_PMID(kClassIDSpace, kObjectFCColorListDropDownWidgetBoss,	kObjStylesUIPrefix + 62)
DECLARE_PMID(kClassIDSpace, kObjectStyleToTagMapPanelBoss,			kObjStylesUIPrefix + 63)
DECLARE_PMID(kClassIDSpace, kObjectStyleExportTagComboBoxWidgetBoss,kObjStylesUIPrefix + 64)
DECLARE_PMID(kClassIDSpace, kObjectStyleExportClassEditBoxWidgetBoss,kObjStylesUIPrefix + 65)
DECLARE_PMID(kClassIDSpace, kObjStylesTransformAttrsPanelWidgetBoss, kObjStylesUIPrefix + 66)
DECLARE_PMID(kClassIDSpace, kObjStylesTransformAttrDropDownWidgetBoss, kObjStylesUIPrefix + 67)
DECLARE_PMID(kClassIDSpace, kXFAttrXMeasureEditBoxBoss, kObjStylesUIPrefix + 68)
DECLARE_PMID(kClassIDSpace, kXFAttrYMeasureEditBoxBoss, kObjStylesUIPrefix + 69)
DECLARE_PMID(kClassIDSpace, kObjStylesPositionRefPointBoss, kObjStylesUIPrefix + 70)





// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeViewObserverImpl,  kObjStylesUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeViewWidgetMgrImpl, kObjStylesUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeViewAdapterImpl,	  kObjStylesUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kObjStylesMenuComponentImpl,	  kObjStylesUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesUIUtilsImpl,		  kObjStylesUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kObjStylesDuplicateDDTargetImpl, kObjStylesUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kObjStylesDeleteDDTargetImpl,	  kObjStylesUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kObjStylesZOrderDDSourceImpl,	  kObjStylesUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kObjStylesZOrderDDTargetImpl,	  kObjStylesUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kObjStylesZOrderDEHandlerImpl,	  kObjStylesUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeNodeEHImpl,		  kObjStylesUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDeleteObjStylesDialogControllerImpl,	kObjStylesUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPageItemDDTargetOSFlavorHelperImpl,	kObjStylesUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kObjStylesNameValidationImpl,			kObjStylesUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogCreatorImpl,			kObjStylesUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogControllerImpl,			kObjStylesUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kObjStylesGeneralPanelCreatorImpl,			kObjStylesUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kObjStyleTreeNodeContextMenuImpl,			kObjStylesUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kObjStylesGeneralPanelObserverImpl,		kObjStylesUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kObjStylesFillPanelCreatorImpl,		kObjStylesUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogTreeViewAdapterImpl,	kObjStylesUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kObjStylesFillStrokePanelObserverImpl,		kObjStylesUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kObjStylesStrokeOptionsPanelCreatorImpl,	kObjStylesUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogTreeViewWidgetMgrImpl,	kObjStylesUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kObjStylesStrokeOptionsPanelObserverImpl,	kObjStylesUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTransparencyPanelCreatorImpl,	kObjStylesUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kTreeViewSelDlgSwitcherImpl,				kObjStylesUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTransparencyPanelObserverImpl,	kObjStylesUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kObjStylesDropShadowPanelCreatorImpl,		kObjStylesUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSwatchProxyViewImpl,				kObjStylesUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kObjStylesDropShadowPanelObserverImpl,		kObjStylesUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kObjStylesStrokePanelCreatorImpl,			kObjStylesUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kObjStylesParaStylePanelObserverImpl,		kObjStylesUIPrefix + 33)
//gap
DECLARE_PMID(kImplementationIDSpace, kObjStyleKBShortCutObserverImpl,			kObjStylesUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kObjStylesBreaklinkDDTargetImpl,			kObjStylesUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kObjStylesBLButtonObserverImpl,			kObjStylesUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kObjStylesColorStrokeFillObserverImpl,		kObjStylesUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogObserverImpl,			kObjStylesUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kForceSelectSubPanelDataImpl,				kObjStylesUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kObjStyleDDListObserverImpl,				kObjStylesUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kControlStripObjStylesSuiteImpl,			kObjStylesUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kControlStripObjStyleRegisterImpl,			kObjStylesUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kObjStyleDDListElementViewImpl,			kObjStylesUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeViewControllerImpl,			kObjStylesUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogTNLeafCheckBoxImpl,		kObjStylesUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSummaryTreeViewWidgetMgrImpl,	kObjStylesUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSummaryTreeViewAdapterImpl,		kObjStylesUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kObjStylesCategoryAttrDataImpl,			kObjStylesUIPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSummaryTNControlViewImpl,		kObjStylesUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeNodeNameViewImpl,			kObjStylesUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kObjStyleTreeNodeShortCutViewImpl,			kObjStylesUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTypeIconViewImpl,				kObjStylesUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kDeleteObjStylesDialogObserverImpl,		kObjStylesUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeViewTypeAheadImpl,			kObjStylesUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kOSTextDefaultMenuComponentImpl,			kObjStylesUIPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kOSTextDefaultMenuImpl,					kObjStylesUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kDefaultObjStyleIconDDSourceImpl,			kObjStylesUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kDefaultTextObjStyleHandlerImpl,			kObjStylesUIPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeViewNodeDDTargetImpl,		kObjStylesUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kObjStylesIconEventHandlerImpl,			kObjStylesUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTypeIconTipImpl,					kObjStylesUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeNodeNameTipImpl,				kObjStylesUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTreeViewEventHandlerImpl,		kObjStylesUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kObjStylesPanelViewImpl,					kObjStylesUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kObjStylesParaStylePanelCreatorImpl,		kObjStylesUIPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kTextToolIsActive_ForObjStylesImpl,		kObjStylesUIPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kLoadObjectStyleDialogControllerImpl,		kObjStylesUIPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kLoadObjectStyleDialogObserverImpl,		kObjStylesUIPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kDefaultGraphicObjStyleHandlerImpl,		kObjStylesUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kOSGraphicDefaultMenuImpl,					kObjStylesUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kOSGraphicDefaultMenuComponentImpl,		kObjStylesUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogTreeViewEHImpl,			kObjStylesUIPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogTreeNodeTipImpl,		kObjStylesUIPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kNavigateCategoryDataImpl,					kObjStylesUIPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kObjStylesCOButtonObserverImpl,			kObjStylesUIPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogTreeViewControllerImpl, kObjStylesUIPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kOSFrameGridDefaultMenuImpl,				kObjStylesUIPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kOSFrameGridDefaultMenuComponentImpl,		kObjStylesUIPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kGridToolIsActive_ForObjStylesImpl,		kObjStylesUIPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kDefaultFrameGridObjStyleHandlerImpl,		kObjStylesUIPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogTNGroupCheckBoxImpl,	kObjStylesUIPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kCategoryNodeChangedMessageImpl,			kObjStylesUIPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kObjStylesCONotDefinedDDTargetImpl,		kObjStylesUIPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kObjStylesCONoneButtonObserverImpl,		kObjStylesUIPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kObjStylesClearOverrideDDTargetImpl,		kObjStylesUIPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleTestMenuImpl, 					kObjStylesUIPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kObjStylesGroupDuplicateDDTargetImpl, 		kObjStylesUIPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kAppliedObjectStyleStaticTextEHImpl, 		kObjStylesUIPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleNameTextValidationImpl, 		kObjStylesUIPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleNameILEEditingAttributesImpl, 	kObjStylesUIPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleNameInLineEditObserverImpl, 	kObjStylesUIPrefix + 92)
//gap
DECLARE_PMID(kImplementationIDSpace, kObjStylesSIconSuiteButtonEventHandlerImpl, kObjStylesUIPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleQuickApplyServiceImpl,			kObjStylesUIPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kObjectFCFillPanelCreatorImpl,				kObjStylesUIPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kObjectFCStrokePanelCreatorImpl,			kObjStylesUIPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogSwitcherImpl,			kObjStylesUIPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogNewTreeViewWidgetMgrImpl,kObjStylesUIPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogNewTreeViewAdapterImpl,	kObjStylesUIPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDialogTNCheckBoxImpl,			kObjStylesUIPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kHonorUnknownStateForCheckBoxDataImpl,		kObjStylesUIPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kObjectFCColorListControlDataImpl,			kObjStylesUIPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleNameInLineEditControllerImpl,	kObjStylesUIPrefix + 104)

DECLARE_PMID(kImplementationIDSpace, kObjStylesGeneralPanelDataImpl,			kObjStylesUIPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kObjStylesFillPanelDataImpl,				kObjStylesUIPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kObjStylesStrokePanelDataImpl,				kObjStylesUIPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kObjStylesStrokeOptionsPanelDataImpl,		kObjStylesUIPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kObjStylesParaStylePanelDataImpl,			kObjStylesUIPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSelDlgSwitcherHelperImpl,		kObjStylesUIPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleToTagPanelCreatorImpl,			kObjStylesUIPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kObjStyleToTagPanelDataImpl,				kObjStylesUIPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleToTagMapObserverImpl,			kObjStylesUIPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kExportTagNameValidationImpl,				kObjStylesUIPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTransformAttrsPanelCreatorImpl, kObjStylesUIPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTransformAttrsPanelObserverImpl, kObjStylesUIPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTransformAttrsPanelDataImpl, kObjStylesUIPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kObjStylesPositionProxyEHImpl, kObjStylesUIPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTransformPanelEWImpl, kObjStylesUIPrefix + 119)





// <Widget ID>
// Widgets
DECLARE_PMID(kWidgetIDSpace, kObjStylesTreeViewPanelWidgetID,	kObjStylesUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTreeViewWidgetID,		kObjStylesUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kNewObjStyleButtonWidgetID,		kObjStylesUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStyleButtonWidgetID,		kObjStylesUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTreeNodeLargeWidgetID,	kObjStylesUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTreeNodeSmallWidgetID,	kObjStylesUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kObjStylesNodeNameWidgetID,		kObjStylesUIPrefix + 7)

// The following is for delete style dialog.
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesDialogWidgetID,		kObjStylesUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesDialogColumnWidgetID,	kObjStylesUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesDialogColumn1WidgetID,	kObjStylesUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesDialogColumn2WidgetID,	kObjStylesUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesDialogRow1WidgetID,	kObjStylesUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesLabelWidgetID,			kObjStylesUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesDropDownWidgetID,		kObjStylesUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStyleDialogWarningIconWidgetId, kObjStylesUIPrefix + 15)

// The following is for object style selectable dialog
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogWidgetID,		kObjStylesUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kObjStylesNameStaticTextWidgetID,	kObjStylesUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kObjStylesNameWidgetID,			kObjStylesUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogColumnWidgetID, kObjStylesUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogRow1WidgetID,	kObjStylesUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogRow2WidgetID,	kObjStylesUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogRow3WidgetID,	kObjStylesUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogRow4WidgetID,	kObjStylesUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogRow5WidgetID,	kObjStylesUIPrefix + 24)

// The following is for object style general panel in selectable dialog
DECLARE_PMID(kWidgetIDSpace, kObjStylesGeneralPanelWidgetID,		kObjStylesUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGeneralPanelRow1WidgetID,kObjStylesUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kObjStyleBasedOnStaticTextWidgetID,kObjStylesUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kObjStyleBasedOnWidgetID,			kObjStylesUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGeneralPanelRow2WidgetID,kObjStylesUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kObjStyleShortcutStaticTextWidgetID,kObjStylesUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kObjStyleShortCutEditBoxWidgetID,	kObjStylesUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGeneralPanelRow3WidgetID,kObjStylesUIPrefix + 32)

DECLARE_PMID(kWidgetIDSpace, kClearOverrideObjStyleButtonWidgetID, kObjStylesUIPrefix + 33)

DECLARE_PMID(kWidgetIDSpace, kObjStylesGeneralPanelRow4WidgetID,kObjStylesUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStyleSettingGroupWidgetID,kObjStylesUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSummaryTreeViewWidgetID,	kObjStylesUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kObjStyleSettingsScrollWidgetID,	kObjStylesUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCurrentActionPanelWidgetID, kObjStylesUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCurrentActionLabelWidgetID, kObjStylesUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCurrentActionTextWidgetID,  kObjStylesUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGeneralPanelRow5WidgetID,  kObjStylesUIPrefix + 41)

DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesFakeLabelWidgetID,	kObjStylesUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesDialogRow2WidgetID,kObjStylesUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesDialogRow3WidgetID,kObjStylesUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kDeleteObjStylesDialogPanelOKCancelWidetID,	kObjStylesUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kObjStylesPreserveFormatCheckBoxWidgetID,		kObjStylesUIPrefix + 46)

DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowSpreadEditWidgetID,		kObjStylesUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowNoiseEditWidgetID,			kObjStylesUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowSpreadStaticTextWidgetID,	kObjStylesUIPrefix + 49)

// The following is for object style stroke options panel in selectable dialog
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeOptionsPanelWidgetID, kObjStylesUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeEffectsTitleTextWidgetID,kObjStylesUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeAlignmentStaticTextWidgetID,	kObjStylesUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeJoinStaticTextWidgetID,		kObjStylesUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeEndCapStaticTextWidgetID,		kObjStylesUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeMiterLimitStaticTextWidgetID,	kObjStylesUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeLineStartStaticTextWidgetID,	kObjStylesUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeLineEndStaticTextWidgetID,		kObjStylesUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeAlignCenterIconWidgetID,		kObjStylesUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeAlignInsideIconWidgetID,		kObjStylesUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeAlignOutsideIconWidgetID,		kObjStylesUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kObjStylesMiterJoinIconWidgetID,		kObjStylesUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kObjStylesRoundedJoinIconWidgetID,		kObjStylesUIPrefix + 62)	
DECLARE_PMID(kWidgetIDSpace, kObjStylesBevelJoinIconWidgetID,		kObjStylesUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kObjStylesButCapIconWidgetID,			kObjStylesUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kObjStylesRoundCapIconWidgetID,		kObjStylesUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kObjStylesProjectingCapIconWidgetID,	kObjStylesUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kObjStylesMiterNudgeWidgetID,			kObjStylesUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kObjStylesMiterTextWidgetID,			kObjStylesUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kObjStylesXTextWidgetID,				kObjStylesUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kObjStylesLineEndStartPopupWidgetID,	kObjStylesUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kObjStylesLineEndEndPopupWidgetID,		kObjStylesUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectsTitleTextWidgetID,	kObjStylesUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kObjStylesEffectStaticTextWidgetID,		kObjStylesUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerSizeStaticTextWidgetID,	kObjStylesUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectPopupWidgetID,		kObjStylesUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectsSizeEditWidgetID,	kObjStylesUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSApplyGroupWidgetID,			kObjStylesUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherApplyGroupWidgetID,		kObjStylesUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSColumn1WidgetID,				kObjStylesUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSColumn2WidgetID,				kObjStylesUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSRow1WidgetID,					kObjStylesUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSRow2WidgetID,					kObjStylesUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSRow3WidgetID,					kObjStylesUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSRow4WidgetID,					kObjStylesUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSRow5WidgetID,					kObjStylesUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSRow6WidgetID,					kObjStylesUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSRow7WidgetID,					kObjStylesUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowSpreadPanelWidgetID,	kObjStylesUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowNoisePanelWidgetID,	kObjStylesUIPrefix + 89)

// The following is for object style transparency panel in selectable dialog
DECLARE_PMID(kWidgetIDSpace, kObjStylesTransparencyPanelWidgetID,	kObjStylesUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTransOptionTitleTextWidgetID,kObjStylesUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kObjStylesBlendModeStaticTextWidgetID,	kObjStylesUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kObjStylesBlendModePopupWID,			kObjStylesUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kObjStylesOpacityStaticTextWidgetID,	kObjStylesUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kObjStylesOpacityComboBoxWID,			kObjStylesUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kObjStylesIsolateBlendingWidgetID,		kObjStylesUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kObjStylesKnockoutGroupCheckBoxWidgetID,kObjStylesUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kObjStylesOpacityStaticPercentTextWID,  kObjStylesUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowNoiseStaticTextWidgetID, kObjStylesUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherNoiseStaticTextWidgetID,	kObjStylesUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherNoiseEditWidgetID,		kObjStylesUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherNoisePanelWidgetID,		kObjStylesUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherNoisePercentSTWidgetID,   kObjStylesUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowSpreadPercentSTWidgetID,	kObjStylesUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowNoisePercentSTWidgetID,	kObjStylesUIPrefix + 105)

// The following is for object style drop shadow panel in selectable dialog
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget1WidgetID,					kObjStylesUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget2WidgetID,					kObjStylesUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget3WidgetID,					kObjStylesUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget4WidgetID,					kObjStylesUIPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget5WidgetID,					kObjStylesUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget6WidgetID,					kObjStylesUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget7WidgetID,					kObjStylesUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget8WidgetID,					kObjStylesUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget9WidgetID,					kObjStylesUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget10WidgetID,					kObjStylesUIPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget11WidgetID,					kObjStylesUIPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget12WidgetID,					kObjStylesUIPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget13WidgetID,					kObjStylesUIPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget14WidgetID,					kObjStylesUIPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget15WidgetID,					kObjStylesUIPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget16WidgetID,					kObjStylesUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget17WidgetID,					kObjStylesUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget18WidgetID,					kObjStylesUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget19WidgetID,					kObjStylesUIPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget20WidgetID,					kObjStylesUIPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget21WidgetID,					kObjStylesUIPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget22WidgetID,					kObjStylesUIPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget23WidgetID,					kObjStylesUIPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget24WidgetID,					kObjStylesUIPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget25WidgetID,					kObjStylesUIPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget26WidgetID,					kObjStylesUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget27WidgetID,					kObjStylesUIPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget28WidgetID,					kObjStylesUIPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget29WidgetID,					kObjStylesUIPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget30WidgetID,					kObjStylesUIPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget31WidgetID,					kObjStylesUIPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget32WidgetID,					kObjStylesUIPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget33WidgetID,					kObjStylesUIPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget34WidgetID,					kObjStylesUIPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget35WidgetID,					kObjStylesUIPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget36WidgetID,					kObjStylesUIPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget37WidgetID,					kObjStylesUIPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget38WidgetID,					kObjStylesUIPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget39WidgetID,					kObjStylesUIPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget40WidgetID,					kObjStylesUIPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget41WidgetID,					kObjStylesUIPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget42WidgetID,					kObjStylesUIPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget43WidgetID,					kObjStylesUIPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget44WidgetID,					kObjStylesUIPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget45WidgetID,					kObjStylesUIPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget46WidgetID,					kObjStylesUIPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget47WidgetID,					kObjStylesUIPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget48WidgetID,					kObjStylesUIPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget49WidgetID,					kObjStylesUIPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget50WidgetID,					kObjStylesUIPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget51WidgetID,					kObjStylesUIPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget52WidgetID,					kObjStylesUIPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTitleWithCheckBoxWidgetID,				kObjStylesUIPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTitleWithoutCheckBoxWidgetID,			kObjStylesUIPrefix + 159)


// The following is for object style drop shadow panel in selectable dialog
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowPanelWidgetID,					kObjStylesUIPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget53WidgetID,					kObjStylesUIPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowBlendModeStaticTextWidgetID,	kObjStylesUIPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowBlendModePopupWidgetID,		kObjStylesUIPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowOpacityStaticTextWidgetID,		kObjStylesUIPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowOpacityEditWidgetID,			kObjStylesUIPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowOpacityPercentSTWidgetID,		kObjStylesUIPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowOffsetXStaticTextWidgetID,		kObjStylesUIPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowOffsetXEditWidgetID,			kObjStylesUIPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowOffsetYStaticTextWidgetID,		kObjStylesUIPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowOffsetYEditWidgetID,			kObjStylesUIPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowBlurRadiusStaticTextWidgetID,	kObjStylesUIPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowBlurRadiusEditWidgetID,		kObjStylesUIPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kObjStylesApplyBorderWidgetID,						kObjStylesUIPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowApplyCheckBoxWidgetID,			kObjStylesUIPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowColorWidgetID,					kObjStylesUIPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherWidthStaticTextWidgetID,			kObjStylesUIPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherWidthEditWidgetID,				kObjStylesUIPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherCornersStaticTextWidgetID,		kObjStylesUIPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherCornersPopupWidgetID,				kObjStylesUIPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowColorProxyWidgetID,			kObjStylesUIPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kObjStylesFeatherApplyCheckBoxWidgetID,			kObjStylesUIPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSColorPopupGroupWID,					kObjStylesUIPrefix + 182)				
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSColorStaticWID,						kObjStylesUIPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDSColorPopupWID,							kObjStylesUIPrefix + 184)

// Various nudge widgets IDs
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectsSizeNudgeWidgetID,			kObjStylesUIPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGradientAngleNudgeWidgetID,				kObjStylesUIPrefix + 186)

// The following is for object style fill/stroke panel in selectable dialog
DECLARE_PMID(kWidgetIDSpace, kObjStylesFillPanelWidgetID,		kObjStylesUIPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTintStaticTextWidgetID,		kObjStylesUIPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTintNudgeWidgetID,			kObjStylesUIPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTintEditWidgetID,			kObjStylesUIPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGradientAngleStaticTextWidgetID,	kObjStylesUIPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGradientAngleEditWidgetID,		kObjStylesUIPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kObjStylesWeightStaticTextWidgetID,		kObjStylesUIPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kObjStylesWeightComboNudgeWidgetID,		kObjStylesUIPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kObjStylesWeightComboWidgetID,				kObjStylesUIPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStroketypeStaticTextWidgetID,	kObjStylesUIPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokeTypePopupWidgetID,			kObjStylesUIPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kObjStylesOverprintFillCheckBoxWidgetID,	kObjStylesUIPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kObjStylesOverprintStrokeCheckBoxWidgetID,	kObjStylesUIPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGapColorTitleTextWidgetID,		kObjStylesUIPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGapColorStaticTextWidgetID,		kObjStylesUIPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGapColorColorDDWidgetID,			kObjStylesUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGapColorTintStaticTextWidgetID,	kObjStylesUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGapColorTintNudgeWidgetID,		kObjStylesUIPrefix + 207)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGapColorTintEditWidgetID,		kObjStylesUIPrefix + 208)
DECLARE_PMID(kWidgetIDSpace, kObjStylesOverprintGapCheckBoxWidgetID,	kObjStylesUIPrefix + 209)

DECLARE_PMID(kWidgetIDSpace, kObjStylePanelControlStripWidgetID,		kObjStylesUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kObjStyleIconWidgetID,						kObjStylesUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kObjStyleDDListWidgetID,					kObjStylesUIPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kObjStyleControlStripPanelWidgetID,		kObjStylesUIPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kObjStyleListParentWidgetID,				kObjStylesUIPrefix + 214)
DECLARE_PMID(kWidgetIDSpace, kObjStyleListElementNameWidgetID,			kObjStylesUIPrefix + 215)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogLeafTreeNodeWidgetID,	kObjStylesUIPrefix + 216)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogTreeViewWidgetID,		kObjStylesUIPrefix + 217)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogTreeNodeCheckBoxWidgetID,kObjStylesUIPrefix + 218)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogTreeNodeStaticTextWidgetID, kObjStylesUIPrefix + 219)

// Breaklink button.
DECLARE_PMID(kWidgetIDSpace, kBreaklinkObjStyleButtonWidgetID,	kObjStylesUIPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kObjStylesStrokePanelWidgetID,		kObjStylesUIPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kObjStylesClearOverrideNoneButtonWidgetID, kObjStylesUIPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kObjStylesClearOverrideButtonWidgetID, kObjStylesUIPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kOSSelectDialogTitleCheckBoxWidgetID, kObjStylesUIPrefix + 224)

DECLARE_PMID(kWidgetIDSpace, kObjStylesSummaryTreeNodeWidgetID,	kObjStylesUIPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kObjStyleTreeNodeShortCutWidgetID,	kObjStylesUIPrefix + 226)
DECLARE_PMID(kWidgetIDSpace, kObjStyleTreeNodeIconWidgetID,		kObjStylesUIPrefix + 227)
DECLARE_PMID(kWidgetIDSpace, kObjStylesPanelControlStripWidgetID, kObjStylesUIPrefix + 228)
DECLARE_PMID(kWidgetIDSpace, kObjStyleTreeNodeExtraIconWidgetID, kObjStylesUIPrefix + 229)
DECLARE_PMID(kWidgetIDSpace, kObjStyleStyleSettingStaticTextWidgetID, kObjStylesUIPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDropShadowOpacityPanelWidgetID, kObjStylesUIPrefix + 231)

// Paragraph Styles Panel
DECLARE_PMID(kWidgetIDSpace, kObjStylesParaStylePanelWidgetID,	kObjStylesUIPrefix + 232)
DECLARE_PMID(kWidgetIDSpace, kObjStylesParaStylesApplyGroupWidgetID,	kObjStylesUIPrefix + 233)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogGroupTreeNodeWidgetID,	kObjStylesUIPrefix + 234)
DECLARE_PMID(kWidgetIDSpace, kObjStyleParaStyleStaticTextWidgetID,	kObjStylesUIPrefix + 235)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogHierarchyTreeNodeWidgetID, kObjStylesUIPrefix + 236)
DECLARE_PMID(kWidgetIDSpace, kObjStylesParaStylesDropDownWidgetID,	kObjStylesUIPrefix + 237)
DECLARE_PMID(kWidgetIDSpace, kObjStylesParaStyleTitleTextWidgetID,	kObjStylesUIPrefix + 238)
DECLARE_PMID(kWidgetIDSpace, kObjStyleTreeNodeExtraExtraIconWidgetID,	kObjStylesUIPrefix + 239)
DECLARE_PMID(kWidgetIDSpace, kObjStylesParaStylesGroupWidgetID,	kObjStylesUIPrefix + 240)
DECLARE_PMID(kWidgetIDSpace, kObjStylesApplyNextParaStyleCheckBoxWidgetID,	kObjStylesUIPrefix + 241)
DECLARE_PMID(kWidgetIDSpace, kObjStyleTreeNodeExtraExtraExtraIconWidgetID,  kObjStylesUIPrefix + 242)
DECLARE_PMID(kWidgetIDSpace, kObjStylesResetStyleToBaseButtonID,	kObjStylesUIPrefix + 243)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGeneralPanelLine4WidgetID,  kObjStylesUIPrefix + 244)
DECLARE_PMID(kWidgetIDSpace, kNewObjStyleGroupButtonWidgetID,  kObjStylesUIPrefix + 245)
DECLARE_PMID(kWidgetIDSpace, kObjectStyleGroupIconWidgetID,  kObjStylesUIPrefix + 246)
DECLARE_PMID(kWidgetIDSpace, kObjectStyleTypeIconWidgetID,  kObjStylesUIPrefix + 247)
DECLARE_PMID(kWidgetIDSpace, kAppliedObjectStyleWidgetID,  kObjStylesUIPrefix + 248)
DECLARE_PMID(kWidgetIDSpace, kAppliedObjectStyleStripWidgetId,  kObjStylesUIPrefix + 249)
DECLARE_PMID(kWidgetIDSpace, kReplaceWithObjectStyleLabelWidgetId,  kObjStylesUIPrefix + 250)
DECLARE_PMID(kWidgetIDSpace, kObjectStyleApplyToAllWidgetId,  kObjStylesUIPrefix + 251)
DECLARE_PMID(kWidgetIDSpace, kObjectStyleListNameILEWidgetID,  kObjStylesUIPrefix + 252)
DECLARE_PMID(kWidgetIDSpace, kObjStyleApplyStyletoSelectionWidgetID, kObjStylesUIPrefix + 253)
DECLARE_PMID(kWidgetIDSpace, kObjStylesLocationStaticTextWidgetID,  kObjStylesUIPrefix + 254)
DECLARE_PMID(kWidgetIDSpace, kObjStylesLocationValueWidgetID,  kObjStylesUIPrefix + 255)

DECLARE_PMID(kWidgetIDSpace, kObjStylesTurnOnAttributeRadioButtonWidgetID,		kObjStylesUIPrefix2 + 1)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTurnOffAttributeRadioButtonWidgetID,		kObjStylesUIPrefix2 + 2)
DECLARE_PMID(kWidgetIDSpace, kObjStylesIgnoreAttributeRadioButtonWidgetID,		kObjStylesUIPrefix2 + 3)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSelDialogNoCheckBoxTreeNodeWidgetID,		kObjStylesUIPrefix2 + 4)

DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget54WidgetID,		kObjStylesUIPrefix2 + 5)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget55WidgetID,		kObjStylesUIPrefix2 + 6)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget56WidgetID,		kObjStylesUIPrefix2 + 7)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget57WidgetID,		kObjStylesUIPrefix2 + 8)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget58WidgetID,		kObjStylesUIPrefix2 + 9)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget59WidgetID,		kObjStylesUIPrefix2 + 10)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidget60WidgetID,		kObjStylesUIPrefix2 + 11)

DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectTopLeftWidgetID,			kObjStylesUIPrefix2 + 12)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectTopRightWidgetID,		kObjStylesUIPrefix2 + 13)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectBottomLeftWidgetID,		kObjStylesUIPrefix2 + 14)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectBottomRightWidgetID,		kObjStylesUIPrefix2 + 15)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerSizeTopLeftWidgetID,			kObjStylesUIPrefix2 + 16)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerSizeTopRightWidgetID,			kObjStylesUIPrefix2 + 17)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerSizeBottomLeftWidgetID,		kObjStylesUIPrefix2 + 18)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerSizeBottomRightWidgetID,		kObjStylesUIPrefix2 + 19)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerNudgeTopLeftWidgetID,			kObjStylesUIPrefix2 + 20)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerNudgeTopRightWidgetID,			kObjStylesUIPrefix2 + 21)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerNudgeBottomLeftWidgetID,		kObjStylesUIPrefix2 + 22)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerNudgeBottomRightWidgetID,		kObjStylesUIPrefix2 + 23)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerIconTopLeftWidgetID,			kObjStylesUIPrefix2 + 24)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerIconTopRightWidgetID,			kObjStylesUIPrefix2 + 25)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerIconBottomLeftWidgetID,		kObjStylesUIPrefix2 + 26)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerIconBottomRightWidgetID,		kObjStylesUIPrefix2 + 27)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectChainWidgetID,			kObjStylesUIPrefix2 + 28)
DECLARE_PMID(kWidgetIDSpace, kObjStylesCornerEffectNSizeStaticTextWidgetID,	kObjStylesUIPrefix2 + 29)

DECLARE_PMID(kWidgetIDSpace, kObjectStyleToTagMapPanelWidgetId,	kObjStylesUIPrefix2 + 30)
DECLARE_PMID(kWidgetIDSpace, kObjStylesExpOptsTreeViewWidgetID,	kObjStylesUIPrefix2 + 31)
DECLARE_PMID(kWidgetIDSpace, kObjStylesGenericWidgetArrowHeadScalingWidgetID, kObjStylesUIPrefix2 + 32)
DECLARE_PMID(kWidgetIDSpace, kObjStylesArrowHeadScalingStaticTextWidgetID, kObjStylesUIPrefix2 + 33)
DECLARE_PMID(kWidgetIDSpace, kObjStylesArrowHeadStartScaleNudgeWidgetID, kObjStylesUIPrefix2 + 34)
DECLARE_PMID(kWidgetIDSpace, kObjStylesArrowHeadStartScaleEditBoxWidgetID, kObjStylesUIPrefix2 + 35)
DECLARE_PMID(kWidgetIDSpace, kObjStylesConstrainArrowHeadScaleWidgetID, kObjStylesUIPrefix2 + 36)
DECLARE_PMID(kWidgetIDSpace, kObjStylesArrowHeadEndScaleNudgeWidgetID, kObjStylesUIPrefix2 + 37)
DECLARE_PMID(kWidgetIDSpace, kObjStylesArrowHeadEndScaleEditBoxWidgetID, kObjStylesUIPrefix2 + 38)
DECLARE_PMID(kWidgetIDSpace, kObjStylesArrowHeadSwapIconWidgetID, kObjStylesUIPrefix2 + 39)
DECLARE_PMID(kWidgetIDSpace, kObjstylesArrowHeadAlignClusterWidgetId, kObjStylesUIPrefix2 + 40)
DECLARE_PMID(kWidgetIDSpace, kObjStylesArrowHeadAlignOutsideIconWidgetID, kObjStylesUIPrefix2 + 41)
DECLARE_PMID(kWidgetIDSpace, kObjStylesArrowHeadAlignInsideIconWidgetID, kObjStylesUIPrefix2 + 42)
DECLARE_PMID(kWidgetIDSpace, kObjStylesArrowHeadAlignmentStaticTextWidgetID, kObjStylesUIPrefix2 + 43)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTransformAttrsPanelWidgetID, kObjStylesUIPrefix2 + 44)
DECLARE_PMID(kWidgetIDSpace, kTransformAttrsPanel1WidgetID, kObjStylesUIPrefix2 + 45)
DECLARE_PMID(kWidgetIDSpace, kTransformAttrsPanel1TitleWID, kObjStylesUIPrefix2 + 46)
DECLARE_PMID(kWidgetIDSpace, kTransformAttrsPanel2WidgetID, kObjStylesUIPrefix2 + 47)
DECLARE_PMID(kWidgetIDSpace, kTransformAttrsPanel2TitleWID, kObjStylesUIPrefix2 + 48)
DECLARE_PMID(kWidgetIDSpace, kPositionAttrsSubGroupWidgetID, kObjStylesUIPrefix2 + 49)
DECLARE_PMID(kWidgetIDSpace, kAdjustTextWidgetID, kObjStylesUIPrefix2 + 50)
DECLARE_PMID(kWidgetIDSpace, kAdjustOptionsDropDownWidgetID, kObjStylesUIPrefix2 + 51)
DECLARE_PMID(kWidgetIDSpace, kAdjustXRelativeToWidgetID, kObjStylesUIPrefix2 + 52)
DECLARE_PMID(kWidgetIDSpace, kAdjustXRelativeToOptionsDropDownWidgetID, kObjStylesUIPrefix2 + 53)
DECLARE_PMID(kWidgetIDSpace, kAdjustXOffSetWidgetID, kObjStylesUIPrefix2 + 54)
DECLARE_PMID(kWidgetIDSpace, kAdjustYRelativeToWidgetID, kObjStylesUIPrefix2 + 55)
DECLARE_PMID(kWidgetIDSpace, kAdjustYRelativeToOptionsDropDownWidgetID, kObjStylesUIPrefix2 + 56)
DECLARE_PMID(kWidgetIDSpace, kAdjustYOffSetWidgetID, kObjStylesUIPrefix2 + 57)
DECLARE_PMID(kWidgetIDSpace, kAdjustXOffsetNudgeWidgetID, kObjStylesUIPrefix2 + 58)
DECLARE_PMID(kWidgetIDSpace, kXOffsetWidgetID, kObjStylesUIPrefix2 + 59)
DECLARE_PMID(kWidgetIDSpace, kAdjustYOffsetNudgeWidgetID, kObjStylesUIPrefix2 + 60)
DECLARE_PMID(kWidgetIDSpace, kYOffsetWidgetID, kObjStylesUIPrefix2 + 61)
DECLARE_PMID(kWidgetIDSpace, kAdjustWhichDimensionDropDownWidgetID, kObjStylesUIPrefix2 + 62)
DECLARE_PMID(kWidgetIDSpace, kAdjustWidthTextWidgetID, kObjStylesUIPrefix2 + 63)
DECLARE_PMID(kWidgetIDSpace, kAdjustWidthNudgeWidgetID, kObjStylesUIPrefix2 + 64)
DECLARE_PMID(kWidgetIDSpace, kWidthEditBoxWidgetID, kObjStylesUIPrefix2 + 65)
DECLARE_PMID(kWidgetIDSpace, kAdjustHeightTextWidgetID, kObjStylesUIPrefix2 + 66)
DECLARE_PMID(kWidgetIDSpace, kAdjustHeightNudgeWidgetID, kObjStylesUIPrefix2 + 67)
DECLARE_PMID(kWidgetIDSpace, kHeightEditBoxWidgetID, kObjStylesUIPrefix2 + 68)
DECLARE_PMID(kWidgetIDSpace, kChainHeightWidthWID, kObjStylesUIPrefix2 + 69)
DECLARE_PMID(kWidgetIDSpace, kWidthAttrLabelRowWidgetID, kObjStylesUIPrefix2 + 70)
DECLARE_PMID(kWidgetIDSpace, kHeightRowWidgetID, kObjStylesUIPrefix2 + 71)
DECLARE_PMID(kWidgetIDSpace, kDimensionSectionWidgetID, kObjStylesUIPrefix2 + 72)
DECLARE_PMID(kWidgetIDSpace, kXRefPointRowWidgetID, kObjStylesUIPrefix2 + 73)
DECLARE_PMID(kWidgetIDSpace, kXOffsetRowWidgetID, kObjStylesUIPrefix2 + 74)
DECLARE_PMID(kWidgetIDSpace, kYRefPointRowWidgetID, kObjStylesUIPrefix2 + 75)
DECLARE_PMID(kWidgetIDSpace, kYOffsetRowWidgetID, kObjStylesUIPrefix2 + 76)
DECLARE_PMID(kWidgetIDSpace, kReferencePointProxyLabelTextWID ,kObjStylesUIPrefix2 + 77)
DECLARE_PMID(kWidgetIDSpace, kPositionRefPointProxyWidgetID ,kObjStylesUIPrefix2 + 78)
DECLARE_PMID(kWidgetIDSpace, kObjStylesDescWidgetID ,kObjStylesUIPrefix2 + 79)
DECLARE_PMID(kWidgetIDSpace, kObjStylesSizeGroupWidgetID ,kObjStylesUIPrefix2 + 80)
DECLARE_PMID(kWidgetIDSpace, kObjStylesPositionWidgetID ,kObjStylesUIPrefix2 + 81)
DECLARE_PMID(kWidgetIDSpace, kTransformAttrsPanel3TitleWID ,kObjStylesUIPrefix2 + 82)




// <Interface ID>
// Interfaces
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLESUIUTILS, kObjStylesUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISUBPANELCALLBACKMSG, kObjStylesUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPOBJECTSTYLEPANELSUITE, kObjStylesUIPrefix + 3)	
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLESCATEGORYATTRDATA, kObjStylesUIPrefix + 4)	
DECLARE_PMID(kInterfaceIDSpace, IID_ICATEGORYCHECKBOXMSG, kObjStylesUIPrefix + 5)	
DECLARE_PMID(kInterfaceIDSpace, IID_INAVIGATECATEGORYDATA,  kObjStylesUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IOLDOBJECTSTYLENAME,  kObjStylesUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICATEGORYNODECHANGED,  kObjStylesUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTUSEDCOLORSONLY, kObjStylesUIPrefix + 9) // Essentially IID_IBOOLDATA specifying whether the used colors should be listed or all colors
DECLARE_PMID(kInterfaceIDSpace, IID_IHONORANYSTATE, kObjStylesUIPrefix + 10) // Essentially IID_IBOOLDATA specifying whether "Any" state should be supported or not in the widgets
DECLARE_PMID(kInterfaceIDSpace, IID_IIGNOREDATTRIBUTESCLASSIDDATA, kObjStylesUIPrefix + 11) // Essentially IID_ICLASSIDLISTDATA holding all the classid's of attributes that need to be ignored
DECLARE_PMID(kInterfaceIDSpace, IID_IHONORUNKNOWNSTATEFORCHECKBOX, kObjStylesUIPrefix + 12) // This is IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IFORCESELECTSUBPANELDATA,	   kObjStylesUIPrefix + 13) // This is IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLIEDOBJECTSTYLESTATICBOOLDATA,	   kObjStylesUIPrefix + 14) // This is IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IXPSELECTABLEDIALOGSWITCHERHELPER2,	   kObjStylesUIPrefix + 15) // This is IID_IXPSELECTABLEDIALOGSWITCHERHELPER for effects specific
DECLARE_PMID(kInterfaceIDSpace, IID_ICACHEDTOOLWASTEXT_FOROBJSTYLEPALETTE, kObjStylesUIPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ICACHEDTOOLWASGRID_FOROBJSTYLEPALETTE, kObjStylesUIPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IGROUPCATEGORYTYPE, kObjStylesUIPrefix + 18)
// <Service ID>
// Service Providers
//DECLARE_PMID(kServiceIDSpace, kObjStylesSelectableDialogService, kObjStylesUIPrefix + 1)

// <Error ID>
// Error Codes
//DECLARE_PMID(kErrorIDSpace, , kObjStylesUIPrefix + 1)

// <Message ID>
// Message IDs
DECLARE_PMID(kMessageIDSpace, kObjStylesSwatchProxyMsg, kObjStylesUIPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kUpdateObjectStylePaletteDeleteButtonMsg, kObjStylesUIPrefix + 2)

// <Global ID>
// Global IDs
//DECLARE_PMID(kActionIDSpace, , kObjStylesUIPrefix + 1)

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kObjectStylePanelActionID,			kObjStylesUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kNewObjectStylesActionID,			kObjStylesUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDuplicateObjectStylesActionID,	kObjStylesUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kDeleteObjectStylesActionID,		kObjStylesUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep1ActionID,			kObjStylesUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kRedefineObjectStylesActionID,		kObjStylesUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kObjectStylesOptionsActionID,		kObjStylesUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kReplaceObjectStylesActionID,		kObjStylesUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep2ActionID,			kObjStylesUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kObjectStylesThumbnailViewActionID,kObjStylesUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kObjectStylesSmallListViewActionID,kObjStylesUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kObjectStylesLargeListViewActionID,kObjStylesUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep3ActionID,			kObjStylesUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kBreakLinkToObjectStylesActionID,	kObjStylesUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kSelectAllUnusedObjectStylesActionID,	kObjStylesUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kSortByNameObjectStylesActionID,		kObjStylesUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep4ActionID, kObjStylesUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kLoadObjectStylesActionID, kObjStylesUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep5ActionID, kObjStylesUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kClearOSOverridesActionID,	kObjStylesUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kContextMenuObjStyleOptionsActionID,	kObjStylesUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kContextMenuDuplicateObjStyleActionID,	kObjStylesUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kContextMenuDeleteObjStyleActionID,	kObjStylesUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kContextMenuRedefineObjStyleActionID,	kObjStylesUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyObjStyleActionID,		kObjStylesUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyObjStyleRemoveOActionID,	kObjStylesUIPrefix + 26)
DECLARE_PMID(kActionIDSpace, kContextMenuClearOverridesObjStyleActionID,kObjStylesUIPrefix + 27)
DECLARE_PMID(kActionIDSpace, kContextMenuObjStylePopupSep1ActionID,	kObjStylesUIPrefix + 28)
DECLARE_PMID(kActionIDSpace, kContextMenuObjStylePopupSep2ActionID,	kObjStylesUIPrefix + 29)
DECLARE_PMID(kActionIDSpace, kExportObjectStylesActionID,			kObjStylesUIPrefix + 30)
DECLARE_PMID(kActionIDSpace, kClearOSOverridesNotDefinedByStyleActionID, kObjStylesUIPrefix + 31)
DECLARE_PMID(kActionIDSpace, kChangeDefaultTextStyleID,				kObjStylesUIPrefix + 32)
DECLARE_PMID(kActionIDSpace, kChangeDefaultTextStyleToSelectedID,	kObjStylesUIPrefix + 33)
DECLARE_PMID(kActionIDSpace, kChangeDefaultGraphicStyleID,				kObjStylesUIPrefix + 34)
DECLARE_PMID(kActionIDSpace, kChangeDefaultGraphicStyleToSelectedID,	kObjStylesUIPrefix + 35)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyObjStyleWithRootAttrsActionID,	kObjStylesUIPrefix + 36)
DECLARE_PMID(kActionIDSpace, kContextMenuApplyObjStyleWithRootAttrsAndClearActionID,kObjStylesUIPrefix + 37)
DECLARE_PMID(kActionIDSpace, kChangeDefaultFrameGridStyleID,				kObjStylesUIPrefix + 38)
DECLARE_PMID(kActionIDSpace, kChangeDefaultFrameGridStyleToSelectedID,		kObjStylesUIPrefix + 39)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep6ActionID, kObjStylesUIPrefix + 40)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep7ActionID, kObjStylesUIPrefix + 41)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep8ActionID, kObjStylesUIPrefix + 42)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep9ActionID, kObjStylesUIPrefix + 43)

//for style groups
DECLARE_PMID(kActionIDSpace, kObjectNewStyleGroupActionID, kObjStylesUIPrefix + 44)
DECLARE_PMID(kActionIDSpace, kObjectOpenAllStyleGroupsActionID, kObjStylesUIPrefix + 45)
DECLARE_PMID(kActionIDSpace, kObjectCloseAllStyleGroupsActionID, kObjStylesUIPrefix + 46)
DECLARE_PMID(kActionIDSpace, kObjectStylesSep10ActionID, kObjStylesUIPrefix + 47)
DECLARE_PMID(kActionIDSpace, kObjectCopyToStyleGroupActionID, kObjStylesUIPrefix + 48)
DECLARE_PMID(kActionIDSpace, kCreateGroupFromObjectStyleActionID, kObjStylesUIPrefix + 49)

// Reserved for the dynamic object styles meny  50 - 255
DECLARE_PMID(kActionIDSpace, kChangeDefaultTextStyleMenuStartID,		kObjStylesUIPrefix + 50)
DECLARE_PMID(kActionIDSpace, kChangeDefaultTextStyleMenuEndID,			kObjStylesUIPrefix + 125)
DECLARE_PMID(kActionIDSpace, kChangeDefaultGraphicStyleMenuStartID,		kObjStylesUIPrefix + 126)
DECLARE_PMID(kActionIDSpace, kChangeDefaultGraphicStyleMenuEndID,		kObjStylesUIPrefix + 200)
DECLARE_PMID(kActionIDSpace, kChangeDefaultFrameGridStyleMenuStartID,	kObjStylesUIPrefix + 201)
DECLARE_PMID(kActionIDSpace, kChangeDefaultFrameGridStyleMenuEndID,		kObjStylesUIPrefix + 255)

//for style groups continuing with next prefix
DECLARE_PMID(kActionIDSpace, kObjectStylesSep11ActionID,				kObjStylesUIPrefix2 + 1)
DECLARE_PMID(kActionIDSpace, kContextMenuObjStyleGroupOptoinsActionID,	kObjStylesUIPrefix2 + 2)
DECLARE_PMID(kActionIDSpace, kContextMenuDuplicateObjStyleGroupActionID,kObjStylesUIPrefix2 + 3)
DECLARE_PMID(kActionIDSpace, kContextMenuDeleteObjStyleGroupActionID,	kObjStylesUIPrefix2 + 4)
DECLARE_PMID(kActionIDSpace, kContextMenuCopyToObjStyleGroupActionID,	kObjStylesUIPrefix2 + 5)
DECLARE_PMID(kActionIDSpace, kContextMenuCreateObjStyleGroupActionID,	kObjStylesUIPrefix2 + 6)
DECLARE_PMID(kActionIDSpace, kContextMenuCreateObjectStyleInGroupActionID,	kObjStylesUIPrefix2 + 7)
DECLARE_PMID(kActionIDSpace, kQuickApplyObjectStyleGroupPrefActionID,	kObjStylesUIPrefix2 + 8)
DECLARE_PMID(kActionIDSpace, kClearOSOverridesWhenApplyStyleActionID, kObjStylesUIPrefix2 + 9)

DECLARE_PMID(kActionIDSpace, kContextMenuObjStylePopupSep3ActionID,	kObjStylesUIPrefix2 + 10)
DECLARE_PMID(kActionIDSpace, kContextMenuObjStylePopupSep4ActionID,	kObjStylesUIPrefix2 + 11)
DECLARE_PMID(kActionIDSpace, kContextMenuObjStylePopupSep5ActionID,	kObjStylesUIPrefix2 + 12)
DECLARE_PMID(kActionIDSpace, kNewObjectStylesDuringDialogActionID,	kObjStylesUIPrefix2 + 13)
DECLARE_PMID(kActionIDSpace, kEditAllStyleToTagObjectStylesActionID,	kObjStylesUIPrefix2 + 14)

//#define kObjStylesSelDialogNodeID	kObjStylesUIPrefix + 1	//	Moved to WidgetID
#define kObjStylesSummaryNodeID		kObjStylesUIPrefix + 2
#define kObjStylesSelectablePanelInfoID	kObjStylesUIPrefix + 3

#endif
