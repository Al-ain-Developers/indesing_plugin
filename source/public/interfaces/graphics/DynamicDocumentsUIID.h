//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/DynamicDocumentsUIID.h $
//  
//  Owner: DBerggren
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
//  Contains IDs used by the EPSImportUI plug-in
//  
//========================================================================================

#ifndef __DynamicDocumentsUIID__
#define __DynamicDocumentsUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kDynamicDocumentsUIPrefix	 RezLong(0x20C00)
#define kDynamicDocumentsUIPrefix2	 RezLong(0x21000)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

// PluginID
#define kDynamicDocumentsUIPluginName	"DynamicDocumentsUI"
DECLARE_PMID(kPlugInIDSpace,			kDynamicDocumentsUIPluginID,		kDynamicDocumentsUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kClassIDSpace,				kXFLExportDialogBoss,				kDynamicDocumentsUIPrefix + 2)
DECLARE_PMID(kClassIDSpace,				kPageTransitionsPanelBoss,			kDynamicDocumentsUIPrefix + 3)
DECLARE_PMID(kClassIDSpace,				kPageTransitionsPanelMenuBoss,		kDynamicDocumentsUIPrefix + 4)
DECLARE_PMID(kClassIDSpace,				kPageTransitionsDialogBoss,			kDynamicDocumentsUIPrefix + 5)
DECLARE_PMID(kClassIDSpace,				kPageTransitionPreviewProxyContainerWidgetBoss,		kDynamicDocumentsUIPrefix + 6)
DECLARE_PMID(kClassIDSpace,				kPageTransitionRadioButtonWidgetBoss, kDynamicDocumentsUIPrefix + 7)

//gap

//	Animation
DECLARE_PMID(kClassIDSpace,				kAnimationUIEventInfoWidgetBoss,	kDynamicDocumentsUIPrefix + 12)
DECLARE_PMID(kClassIDSpace,				kAnimationUIEventMenuBoss,			kDynamicDocumentsUIPrefix + 13)
DECLARE_PMID(kClassIDSpace,				kAnimationUIPanelBoss,				kDynamicDocumentsUIPrefix + 14)
DECLARE_PMID(kClassIDSpace,				kAnimationUIPanelMenuBoss,			kDynamicDocumentsUIPrefix + 15)
DECLARE_PMID(kClassIDSpace,				kAnimationUIPresetWidgetBoss,		kDynamicDocumentsUIPrefix + 16)
DECLARE_PMID(kClassIDSpace,				kAnimationUIAnimateOptionWidgetBoss,kDynamicDocumentsUIPrefix + 17)
DECLARE_PMID(kClassIDSpace,				kAnimationUIButtonTriggerWidgetBoss,kDynamicDocumentsUIPrefix + 18)
DECLARE_PMID(kClassIDSpace,				kAnimationUIButtonTriggerTrackerBoss,kDynamicDocumentsUIPrefix + 19)
DECLARE_PMID(kClassIDSpace,				kAnimationUIButtonTriggerTrackerRegisterBoss,kDynamicDocumentsUIPrefix + 20)
DECLARE_PMID(kClassIDSpace,				kAnimationPreviewPanelWidgetBoss,	kDynamicDocumentsUIPrefix + 22)

//gap

DECLARE_PMID(kClassIDSpace,				kMotionPathDrawServiceBoss,			kDynamicDocumentsUIPrefix + 24)
DECLARE_PMID(kClassIDSpace,				kTimingPanelPreviewSpreadWidgetBoss,kDynamicDocumentsUIPrefix + 25)
DECLARE_PMID(kClassIDSpace,				kAnimationPanelPreviewSpreadWidgetBoss, kDynamicDocumentsUIPrefix + 26)
DECLARE_PMID(kClassIDSpace,				kAnimationUIXFormPointWidgetBoss,	kDynamicDocumentsUIPrefix + 27)
DECLARE_PMID(kClassIDSpace,				kAnimationUIManagePresetsDialogBoss,kDynamicDocumentsUIPrefix + 28)
DECLARE_PMID(kClassIDSpace,				kAnimationUIManagePresetsListBoxBoss, kDynamicDocumentsUIPrefix + 29)

// Timing panel
DECLARE_PMID(kClassIDSpace,				kTimingPanelBoss,					kDynamicDocumentsUIPrefix + 30)
DECLARE_PMID(kClassIDSpace,				kTimingPanelTreeWidgetBoss,			kDynamicDocumentsUIPrefix + 31)
//gap
DECLARE_PMID(kClassIDSpace,				kTimingPanelTreeNodeBoss,			kDynamicDocumentsUIPrefix + 33)
DECLARE_PMID(kClassIDSpace,				kTimingPanelEventDDListWidgetBoss,  kDynamicDocumentsUIPrefix + 34)
DECLARE_PMID(kClassIDSpace,				kTimingPanelMenuBoss,				kDynamicDocumentsUIPrefix + 35)
DECLARE_PMID(kClassIDSpace,				kTimingPanelGroupButtonBoss,		kDynamicDocumentsUIPrefix + 36)
DECLARE_PMID(kClassIDSpace,				kTimingPanelUngroupButtonBoss,		kDynamicDocumentsUIPrefix + 37)
DECLARE_PMID(kClassIDSpace,				kTimingPanelDataExchangeHandlerBoss,kDynamicDocumentsUIPrefix + 38)
DECLARE_PMID(kClassIDSpace,				kTimingPanelTreeNodeGroupWidgetBoss,kDynamicDocumentsUIPrefix + 39)
DECLARE_PMID(kClassIDSpace,				kTimingPanelPageItemNameBoss,		kDynamicDocumentsUIPrefix + 40)

//gap

DECLARE_PMID(kClassIDSpace,				kAnimationUIManagePresetsDialogListNodeWidgetBoss, kDynamicDocumentsUIPrefix + 42)
DECLARE_PMID(kClassIDSpace,				kAnimationUIManagePresetsDialogStaticTextWidgetBoss, kDynamicDocumentsUIPrefix + 43)
DECLARE_PMID(kClassIDSpace,				kAnimationUIPresetCBWidgetBoss, kDynamicDocumentsUIPrefix + 44)
//gap
DECLARE_PMID(kClassIDSpace,				kLiquidLayoutPanelBoss,				kDynamicDocumentsUIPrefix + 60)
DECLARE_PMID(kClassIDSpace,				kLiquidLayoutPanelMenuBoss,			kDynamicDocumentsUIPrefix + 61)
//gap
//gap
DECLARE_PMID(kClassIDSpace,             kHTMLFXLPreviewPanelMenuBoss,       kDynamicDocumentsUIPrefix + 80)
//gap

// Animation panel
DECLARE_PMID(kClassIDSpace,				kAnimationUISavePresetDialogBoss,	kDynamicDocumentsUIPrefix + 100)
DECLARE_PMID(kClassIDSpace,				kAnimationUIPresetPopupMenuBoss,	kDynamicDocumentsUIPrefix + 101)

//	UI Test
DECLARE_PMID(kClassIDSpace,				kMotionTestColorSwatchWidgetBoss,	kDynamicDocumentsUIPrefix + 252)
DECLARE_PMID(kClassIDSpace,				kMotinTestFilterListWidgetBoss,		kDynamicDocumentsUIPrefix + 253)
DECLARE_PMID(kClassIDSpace,				kMotionTestDialogBoss,				kDynamicDocumentsUIPrefix + 254)
DECLARE_PMID(kClassIDSpace,				kMotinonTestMenuBoss,				kDynamicDocumentsUIPrefix + 255)


//----------------------------------------------------------------------------------------
// Interface ID identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace,			IID_IASSICIATEDPAGETRANSITIONCLASSIDDATA,	kDynamicDocumentsUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISELECTEDCONTAINERWIDGETIDDATA,			kDynamicDocumentsUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,			IID_IAUTOLAYOUTWARNINGOBSERVER,				kDynamicDocumentsUIPrefix + 3)
//gap

DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONPATHDATA,						kDynamicDocumentsUIPrefix + 7)

//----------------------------------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace,			IID_ISAVEPREVIEWSETTINGS,					kDynamicDocumentsUIPrefix + 8)
//gap
DECLARE_PMID(kInterfaceIDSpace,			IID_ISLIDERWIDGETCURSORPROVIDER,			kDynamicDocumentsUIPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICTARGETLISTDATA,					kDynamicDocumentsUIPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONEVENTLISTCONTROLDATA,			kDynamicDocumentsUIPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONTRIGGERTYPEDATA,				kDynamicDocumentsUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace,			IID_ILASTCUSTOMPRESETINDEX,					kDynamicDocumentsUIPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace,         IID_IHTMLFXLPREVIEWMANUALLAUNCHBOOLDATA,    kDynamicDocumentsUIPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace,         IID_IHTMLFXLPREVIEWDOCUMENTBOOLDATA,        kDynamicDocumentsUIPrefix + 16)
//gap

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------
//DECLARE_PMID(kImplementationIDSpace,	kSWFExportDlgControllerImpl,		kDynamicDocumentsUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kXFLExportDlgControllerImpl,		kDynamicDocumentsUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kXFLExportDlgObserverImpl,			kDynamicDocumentsUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionsPanelObserverImpl,	kDynamicDocumentsUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionsMenuComponentImpl,			kDynamicDocumentsUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionsDialogControllerImpl,		kDynamicDocumentsUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionsDialogObserverImpl,			kDynamicDocumentsUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace,	kAssociatedPageTransitionClassIDDataImpl,	kDynamicDocumentsUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace,	kSelectedContainerWidgetIDDataImpl,			kDynamicDocumentsUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionStaticTextToolTipsImpl,      kDynamicDocumentsUIPrefix + 11)

//gap


// Aninmation

DECLARE_PMID(kImplementationIDSpace,	kAnimationUIPanelViewImpl,					kDynamicDocumentsUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIPanelMenuActionImpl,			kDynamicDocumentsUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIEventMenuActionImpl,			kDynamicDocumentsUIPrefix + 27)

DECLARE_PMID(kImplementationIDSpace,	kAnimationUIPanelDetailControllerImpl,		kDynamicDocumentsUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIManagePresetItemListBoxCtrlImpl,kDynamicDocumentsUIPrefix + 30)

DECLARE_PMID(kImplementationIDSpace,	kAnimationAdornmentDrawerImpl,				kDynamicDocumentsUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace,	kMotionPathDrawServiceImpl,					kDynamicDocumentsUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace,	kMotionPathAdornmentTipImpl,				kDynamicDocumentsUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace,	kEasingPathAdornmentTipImpl,				kDynamicDocumentsUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIManagePresetsDialogObserverImpl, kDynamicDocumentsUIPrefix + 36)

DECLARE_PMID(kImplementationIDSpace,	kAnimationPanelObserverImpl,				kDynamicDocumentsUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUISavePresetDialogControllerImpl, kDynamicDocumentsUIPrefix + 38)
//DECLARE_PMID(kImplementationIDSpace,	kAnimationUIEventOwnerDrawDDItemImpl,		kDynamicDocumentsUIPrefix + 39)
//DECLARE_PMID(kImplementationIDSpace,	kAnimationEventListControlDataImpl,			kDynamicDocumentsUIPrefix + 40)
//DECLARE_PMID(kImplementationIDSpace,	kAnimationUIEventListElementViewImpl,		kDynamicDocumentsUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIEventInfoTipImpl,				kDynamicDocumentsUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIAnimateOptionTipImpl,			kDynamicDocumentsUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIButtonTriggerEHImpl,			kDynamicDocumentsUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIButtonTriggerTrackerRegisterImpl,kDynamicDocumentsUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIButtonTriggerTrackerImpl,		kDynamicDocumentsUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIButtonTriggerTrackerEHImpl,		kDynamicDocumentsUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIXFProxyEHImpl,					kDynamicDocumentsUIPrefix + 49)

//gap

DECLARE_PMID(kImplementationIDSpace,	kAnimationUIPresetPopupMenuActionImpl,		kDynamicDocumentsUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIPresetPopupDynamicMenuImpl,		kDynamicDocumentsUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIManagePresetsDialogListNodeViewImpl, kDynamicDocumentsUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIManagePresetsDialogStaticTextWidgetViewImpl, kDynamicDocumentsUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIManagePresetListBoxWidgetMgrImpl,	kDynamicDocumentsUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUIPresetCBObserverImpl,			kDynamicDocumentsUIPrefix + 57)
//gap
DECLARE_PMID(kImplementationIDSpace,    kHTMLFXLPreviewPanelMenuComponentImpl,      kDynamicDocumentsUIPrefix + 59)
// Timing panel
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelViewImpl,						kDynamicDocumentsUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeViewWidgetMgrImpl,			kDynamicDocumentsUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeViewAdapterImpl,			kDynamicDocumentsUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelMenuComponentImpl,				kDynamicDocumentsUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelObserverImpl,					kDynamicDocumentsUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelGroupButtonDDTargetImpl,		kDynamicDocumentsUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelUngroupButtonDDTargetImpl,		kDynamicDocumentsUIPrefix + 66)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelDataExchangeHandlerImpl,		kDynamicDocumentsUIPrefix + 67)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeNodeDDSourceImpl,			kDynamicDocumentsUIPrefix + 68)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeNodeViewImpl,				kDynamicDocumentsUIPrefix + 69)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeNodeGroupWidgetViewImpl,    kDynamicDocumentsUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeNodeClickIconViewImpl,		kDynamicDocumentsUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeDDTargetImpl,				kDynamicDocumentsUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeNodeEHImpl,					kDynamicDocumentsUIPrefix + 73)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelCursorProviderImpl,				kDynamicDocumentsUIPrefix + 74)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelEventDDListTipsImpl,			kDynamicDocumentsUIPrefix + 75)
DECLARE_PMID(kImplementationIDSpace,	kDynamicTargetListDataImpl,					kDynamicDocumentsUIPrefix + 76)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelPageItemNameObserverImpl,		kDynamicDocumentsUIPrefix + 77)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelNameILEEditingAttributesImpl,	kDynamicDocumentsUIPrefix + 78)
DECLARE_PMID(kImplementationIDSpace,	kDDPreviewSpreadButtonWidgetTipImpl,		kDynamicDocumentsUIPrefix + 79)

//gap

DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeNodeGroupWidgetEHImpl,		kDynamicDocumentsUIPrefix + 81)
DECLARE_PMID(kImplementationIDSpace,	kTimingPanelTreeNodeGroupWidgetTipImpl,		kDynamicDocumentsUIPrefix + 82)
//gap
DECLARE_PMID(kImplementationIDSpace,	kLiquidLayoutPanelMenuComponentImpl,		kDynamicDocumentsUIPrefix + 95)
DECLARE_PMID(kImplementationIDSpace,	kLiquidLayoutPanelObserverImpl,				kDynamicDocumentsUIPrefix + 96)
DECLARE_PMID(kImplementationIDSpace,	kLayoutAdjustmentWarningObserverImpl,		kDynamicDocumentsUIPrefix + 97)
//gap
//DECLARE_PMID(kImplementationIDSpace,	kMotionTestColorSwatchEHImpl ,				kDynamicDocumentsUIPrefix + 253)
DECLARE_PMID(kImplementationIDSpace,	kMotionTestFilterLBControllerImpl,			kDynamicDocumentsUIPrefix + 252)
DECLARE_PMID(kImplementationIDSpace,	kMotionTestDlgControllerImpl,				kDynamicDocumentsUIPrefix + 253)
DECLARE_PMID(kImplementationIDSpace,	kMotionTestDlgObserverImpl,					kDynamicDocumentsUIPrefix + 254)
DECLARE_PMID(kImplementationIDSpace,	kMotionTestMenuImpl,						kDynamicDocumentsUIPrefix + 255)

//----------------------------------------------------------------------------------------
// Service identifiers
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace,			kXFLExportDialogWidgetID,			kDynamicDocumentsUIPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace,			kExpFieldNamesColumnWidgetID,		kDynamicDocumentsUIPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace,			kSpaceWidgetID,						kDynamicDocumentsUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,			kSizeStrWidgetID,					kDynamicDocumentsUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace,			kPagesStrWidgetID,					kDynamicDocumentsUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace,			kTextStrWidgetID,					kDynamicDocumentsUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace,			kInteractStrWidgetID,				kDynamicDocumentsUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace,			kImageCompStrWidgetID,				kDynamicDocumentsUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace,			kQualityStrWidgetID,				kDynamicDocumentsUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace,			kCurveQualStrWidgetID,				kDynamicDocumentsUIPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace,			kExpFieldsGroupColumnWidgetID,		kDynamicDocumentsUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace,			kSizeGroupColumnWidgetID,			kDynamicDocumentsUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace,			kSize_GroupWidgetID,				kDynamicDocumentsUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace,			kSizeAndPagesColumnWidgetID,		kDynamicDocumentsUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace,			kFitTo_RadioButtonWidgetID,			kDynamicDocumentsUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace,			kWidth_RadioButtonWidgetID,			kDynamicDocumentsUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace,			kScale_RadioButtonWidgetID,			kDynamicDocumentsUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace,			kSizeFieldsGroupColumnWidgetID,		kDynamicDocumentsUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace,			kScalePopupPanelWID,				kDynamicDocumentsUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace,			kScalePopupWID,						kDynamicDocumentsUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace,			kWidthRowWidgetID,					kDynamicDocumentsUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace,			kWidthPopupWID,						kDynamicDocumentsUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace,			kHeightWidgetID,					kDynamicDocumentsUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace,			kHeightPopupWID,					kDynamicDocumentsUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace,			kHeight_Width_ConstrainWID,			kDynamicDocumentsUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace,			kFitToPopupWID,						kDynamicDocumentsUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace,			kPages_GroupWidgetID,				kDynamicDocumentsUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace,			kAll_RadioButtonWidgetID,			kDynamicDocumentsUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace,			kRange_RadioButtonWidgetID,			kDynamicDocumentsUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace,			kPagesPageRangeEditWID,				kDynamicDocumentsUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace,			kSpreadsCheckboxWID,				kDynamicDocumentsUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace,			kRastorizeCheckboxWID,				kDynamicDocumentsUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace,			kGenHTMLCheckboxWID,				kDynamicDocumentsUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace,			kFlattenXPCheckboxWID,				kDynamicDocumentsUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace,			kTextPopupWID,						kDynamicDocumentsUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace,			kInclButtonCheckboxWID,				kDynamicDocumentsUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace,			kInclHyperCheckboxWID,				kDynamicDocumentsUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace,			kPageTransWidgetID,					kDynamicDocumentsUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace,			kPageCurlWidgetID,					kDynamicDocumentsUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace,			kImageCompPopupWID,					kDynamicDocumentsUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace,			kQualityPopupWID,					kDynamicDocumentsUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace,			kCurveQualPopupWID,					kDynamicDocumentsUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace,			kOKCancelWID,						kDynamicDocumentsUIPrefix + 44)
//gap
DECLARE_PMID(kWidgetIDSpace,			kBlendSpaceConflictWarningWID,		kDynamicDocumentsUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace,			kInsertHyphensCheckboxWID,			kDynamicDocumentsUIPrefix + 47)
//gap
// panel
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsPanelWidgetID,				kDynamicDocumentsUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsPanelControlStripWidgetID,	kDynamicDocumentsUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace,			kApplyToAllSpreadsButtonWidgetID,			kDynamicDocumentsUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsPanelSeparatorWidgetID,		kDynamicDocumentsUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsPanelGroupWidgetID,			kDynamicDocumentsUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsPanelPreviewProxyWidgetID,	kDynamicDocumentsUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionGroupWidgetID,				kDynamicDocumentsUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionStaticTextWidgetID,			kDynamicDocumentsUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionDropDownWidgetID,			kDynamicDocumentsUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace,			kPageSpeedGroupWidgetID,					kDynamicDocumentsUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace,			kPageSpeedStaticTextWidgetID,				kDynamicDocumentsUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace,			kPageSpeedDropDownWidgetID,					kDynamicDocumentsUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace,			kPageDirectionGroupWidgetID,				kDynamicDocumentsUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace,			kPageDirectionStaticTextWidgetID,			kDynamicDocumentsUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace,			kPageDirectionDropDownWidgetID,				kDynamicDocumentsUIPrefix + 64)
//dialog
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogWidgetID,					kDynamicDocumentsUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsApplyToAllCheckBoxWidgetID,		kDynamicDocumentsUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogProxyGroup1WidgetID,		kDynamicDocumentsUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogProxyGroup2WidgetID,		kDynamicDocumentsUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogProxyColumnWidgetID,		kDynamicDocumentsUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogOKCancelGroupWidgetID,	kDynamicDocumentsUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogProxyRow1WidgetID,		kDynamicDocumentsUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogProxyRow2WidgetID,		kDynamicDocumentsUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogProxyRow3WidgetID,		kDynamicDocumentsUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionFakeStaticTextWidgetID,			kDynamicDocumentsUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogPreviewProxyWidgetID,		kDynamicDocumentsUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogProxyRadioButtonWidgetID,	kDynamicDocumentsUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogBlindsContainerWidgetID,	kDynamicDocumentsUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogBoxContainerWidgetID,		kDynamicDocumentsUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogCombContainerWidgetID,	kDynamicDocumentsUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogCoverContainerWidgetID,	kDynamicDocumentsUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogDissolveContainerWidgetID,	kDynamicDocumentsUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogFadeContainerWidgetID,		kDynamicDocumentsUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogPageTurnContainerWidgetID,	kDynamicDocumentsUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogPushContainerWidgetID,		kDynamicDocumentsUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogSplitContainerWidgetID,		kDynamicDocumentsUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogUncoverContainerWidgetID,		kDynamicDocumentsUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogWipeContainerWidgetID,		kDynamicDocumentsUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogZoomInContainerWidgetID,		kDynamicDocumentsUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace,			kPageTransitionsDialogZoomOutContainerWidgetID,		kDynamicDocumentsUIPrefix + 89)
//gap
DECLARE_PMID(kWidgetIDSpace,			kDynDocUIGenericPanel1WID,							kDynamicDocumentsUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace,			kDynDocUIGenericPanel2WID,							kDynamicDocumentsUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace,			kDynDocUIGenericPanel3WID,							kDynamicDocumentsUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace,			kDynDocUIGenericPanel4WID,							kDynamicDocumentsUIPrefix + 113)
DECLARE_PMID(kWidgetIDSpace,			kDynDocUIGenericPanel5WID,							kDynamicDocumentsUIPrefix + 114)
DECLARE_PMID(kWidgetIDSpace,			kDynDocUIGenericPanel6WID,							kDynamicDocumentsUIPrefix + 115)
//gap
DECLARE_PMID(kWidgetIDSpace,			kLiquidLayoutPanelWidgetID,							kDynamicDocumentsUIPrefix + 140)
DECLARE_PMID(kWidgetIDSpace,			kLiquidLayoutPanelPolicyDropdownListWidgetID,		kDynamicDocumentsUIPrefix + 141)
DECLARE_PMID(kWidgetIDSpace,			kLayoutPolicyTextLabelWidgetID,						kDynamicDocumentsUIPrefix + 142)
DECLARE_PMID(kWidgetIDSpace,			kConstraintsLabelWID,								kDynamicDocumentsUIPrefix + 143)
//gap
DECLARE_PMID(kWidgetIDSpace,			kLayoutPolicySeperatorWID,							kDynamicDocumentsUIPrefix + 145)
DECLARE_PMID(kWidgetIDSpace,			kObjectConstraintsSubPanelGroupWID,					kDynamicDocumentsUIPrefix + 146)
DECLARE_PMID(kWidgetIDSpace,			kFixedHeightConstraintCheckboxWidgetID,				kDynamicDocumentsUIPrefix + 147)
DECLARE_PMID(kWidgetIDSpace,			kFixedWidthConstraintCheckboxWidgetID,				kDynamicDocumentsUIPrefix + 148)
DECLARE_PMID(kWidgetIDSpace,			kPinLeftConstraintCheckboxWidgetID,					kDynamicDocumentsUIPrefix + 149)
DECLARE_PMID(kWidgetIDSpace,			kPinRightConstraintCheckboxWidgetID,				kDynamicDocumentsUIPrefix + 150)
DECLARE_PMID(kWidgetIDSpace,			kPinTopConstraintCheckboxWidgetID,					kDynamicDocumentsUIPrefix + 151)
DECLARE_PMID(kWidgetIDSpace,			kPinBottomConstraintCheckboxWidgetID,				kDynamicDocumentsUIPrefix + 152)
DECLARE_PMID(kWidgetIDSpace,			kLiquidLayoutAutoFitObserverWidgetId,				kDynamicDocumentsUIPrefix + 153)
DECLARE_PMID(kWidgetIDSpace,			kLayoutAdjustmentWarningWID,						kDynamicDocumentsUIPrefix + 154)
DECLARE_PMID(kWidgetIDSpace,			kPageRangeWidgetID,									kDynamicDocumentsUIPrefix + 155)
//gap
DECLARE_PMID(kWidgetIDSpace,			kDynaMediaStrWidgetID,								kDynamicDocumentsUIPrefix + 200)
DECLARE_PMID(kWidgetIDSpace,			kSelection_RadioButtonWidgetID,						kDynamicDocumentsUIPrefix + 201)
DECLARE_PMID(kWidgetIDSpace,			kIncludeAll_RadioButtonWidgetID,					kDynamicDocumentsUIPrefix + 202)
DECLARE_PMID(kWidgetIDSpace,			kAppearanceOnly_RadioButtonWidgetID,				kDynamicDocumentsUIPrefix + 203)
DECLARE_PMID(kWidgetIDSpace,			kImageCompressGroupWidgetId,						kDynamicDocumentsUIPrefix + 204)
DECLARE_PMID(kWidgetIDSpace,			kImageCompressBorderWidgetID,						kDynamicDocumentsUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace,			kImageCompressColWidgetID,							kDynamicDocumentsUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace,			kICFieldNamesWidgetID,								kDynamicDocumentsUIPrefix + 207)
DECLARE_PMID(kWidgetIDSpace,			kCompressionStrWidgetID,							kDynamicDocumentsUIPrefix + 208)
DECLARE_PMID(kWidgetIDSpace,			kJPEGQualityStrWidgetID,							kDynamicDocumentsUIPrefix + 209)
DECLARE_PMID(kWidgetIDSpace,			kResolutionStrWidgetID,								kDynamicDocumentsUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace,			kICFieldsWidgetID,									kDynamicDocumentsUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace,			kCompressionPopupWID,								kDynamicDocumentsUIPrefix + 212)
DECLARE_PMID(kWidgetIDSpace,			kJPEGQualityPopupWID,								kDynamicDocumentsUIPrefix + 213)
DECLARE_PMID(kWidgetIDSpace,			kResolutionComboWID,								kDynamicDocumentsUIPrefix + 214)
DECLARE_PMID(kWidgetIDSpace,			kDynamicMedia_GroupWidgetID,						kDynamicDocumentsUIPrefix + 215)

//gap
//DECLARE_PMID(kWidgetIDSpace,			kSWFExportMiscGroupWidgetId,						kDynamicDocumentsUIPrefix + 217)

DECLARE_PMID(kWidgetIDSpace,			kBackgroundStrWidgetID,								kDynamicDocumentsUIPrefix + 219)
DECLARE_PMID(kWidgetIDSpace,			kPageTransStrWidgetID,								kDynamicDocumentsUIPrefix + 220)
DECLARE_PMID(kWidgetIDSpace,			kPageTransPopupWID,									kDynamicDocumentsUIPrefix + 221)
DECLARE_PMID(kWidgetIDSpace,			kOptionsStrWidgetID,								kDynamicDocumentsUIPrefix + 222)
DECLARE_PMID(kWidgetIDSpace,			kBackground_GroupWidgetID,							kDynamicDocumentsUIPrefix + 223)
DECLARE_PMID(kWidgetIDSpace,			kPaperColor_RadioButtonWidgetID,					kDynamicDocumentsUIPrefix + 224)
DECLARE_PMID(kWidgetIDSpace,			kTransparent_RadioButtonWidgetID,					kDynamicDocumentsUIPrefix + 225)
DECLARE_PMID(kWidgetIDSpace,			kDescriptionGroupWidgetId,							kDynamicDocumentsUIPrefix + 226)
DECLARE_PMID(kWidgetIDSpace,			kDescriptionStrWidgetID,							kDynamicDocumentsUIPrefix + 227)
//gap
DECLARE_PMID(kWidgetIDSpace,			kFrameRateStrWidgetID,								kDynamicDocumentsUIPrefix + 229)
DECLARE_PMID(kWidgetIDSpace,			kFramesPerSecEditWidgetID,							kDynamicDocumentsUIPrefix + 230)
DECLARE_PMID(kWidgetIDSpace,			kFrameSecStrWidgetID,								kDynamicDocumentsUIPrefix + 231)
DECLARE_PMID(kWidgetIDSpace,			kFlattenWarningIconWidgetId,						kDynamicDocumentsUIPrefix + 232)
DECLARE_PMID(kWidgetIDSpace,			kRastorizeWarningIconWidgetId,						kDynamicDocumentsUIPrefix + 233)

// Animation Panel
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPanelWID,								kDynamicDocumentsUIPrefix2 + 1)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIMainPanelWID,							kDynamicDocumentsUIPrefix2 + 2)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPreviewLabelWID,						kDynamicDocumentsUIPrefix2 + 3)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPreviewProxyWID,						kDynamicDocumentsUIPrefix2 + 4)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUINameGroupWID,							kDynamicDocumentsUIPrefix2 + 5)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUINameLabelWID,							kDynamicDocumentsUIPrefix2 + 6)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUINameEditBoxWID,							kDynamicDocumentsUIPrefix2 + 7)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPresetGroupWID,							kDynamicDocumentsUIPrefix2 + 8)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPresetLabelWID,							kDynamicDocumentsUIPrefix2 + 9)		
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPresetDropDownWID,						kDynamicDocumentsUIPrefix2 + 10)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUISavePresetDialogWID,					kDynamicDocumentsUIPrefix2 + 11)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUISavePresetGroupWID,						kDynamicDocumentsUIPrefix2 + 12)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUISavePresetNameStaticWID,				kDynamicDocumentsUIPrefix2 + 13)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUISavePresetNameWID,						kDynamicDocumentsUIPrefix2 + 14)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUISavePresetOKCancelGroupWID,				kDynamicDocumentsUIPrefix2 + 15)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIEventGroupWID,							kDynamicDocumentsUIPrefix2 + 16)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIEventLabelWID,							kDynamicDocumentsUIPrefix2 + 17)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIEventDropDownWID,						kDynamicDocumentsUIPrefix2 + 18)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIDurationGroupWID,						kDynamicDocumentsUIPrefix2 + 19)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIDurationLabelWID,						kDynamicDocumentsUIPrefix2 + 20)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIDurationILEWID,							kDynamicDocumentsUIPrefix2 + 21)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIDurationSecondLabelWID,					kDynamicDocumentsUIPrefix2 + 22)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPlayGroupWID,							kDynamicDocumentsUIPrefix2 + 23)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPlayLabelWID,							kDynamicDocumentsUIPrefix2 + 24)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPlayILEWID,								kDynamicDocumentsUIPrefix2 + 25)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUITimeLabelWID,							kDynamicDocumentsUIPrefix2 + 26)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUILoopCheckboxWID,						kDynamicDocumentsUIPrefix2 + 27)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUISpeedGroupWID,							kDynamicDocumentsUIPrefix2 + 28)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUISpeedLabelWID,							kDynamicDocumentsUIPrefix2 + 29)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUISpeedDropDownWID,						kDynamicDocumentsUIPrefix2 + 30)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyGroupWID,						kDynamicDocumentsUIPrefix2 + 31)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIControlStripWID,						kDynamicDocumentsUIPrefix2 + 32)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUISeperatorWID,							kDynamicDocumentsUIPrefix2 + 33)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPreviewButtonWID,						kDynamicDocumentsUIPrefix2 + 34)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIOnRollOffCheckboxWID,					kDynamicDocumentsUIPrefix2 + 35)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIVisibilityGroupWID,						kDynamicDocumentsUIPrefix2 + 36)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIVisibilityLabelWID,						kDynamicDocumentsUIPrefix2 + 37)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIHideBeforeAnimateCheckboxWID,			kDynamicDocumentsUIPrefix2 + 38)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyTitleGroupWID,					kDynamicDocumentsUIPrefix2 + 39)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyExpanderWidgetIconWID,			kDynamicDocumentsUIPrefix2 + 40)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyExpanderWidgetLabelWID,			kDynamicDocumentsUIPrefix2 + 41)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertySubPanelGroupWID,				kDynamicDocumentsUIPrefix2 + 42)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyDesignLabelWID,					kDynamicDocumentsUIPrefix2 + 43)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyDesignCheckBoxWID,				kDynamicDocumentsUIPrefix2 + 44)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyDesignInfoLabelWID,				kDynamicDocumentsUIPrefix2 + 45)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyScaleLabelWID,					kDynamicDocumentsUIPrefix2 + 46)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyScaleHorzLabelWID,				kDynamicDocumentsUIPrefix2 + 47)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIScaleHorzILEWID,						kDynamicDocumentsUIPrefix2 + 48)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyScaleVertLabelWID,				kDynamicDocumentsUIPrefix2 + 49)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIScaleVertILEWID,						kDynamicDocumentsUIPrefix2 + 50)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyRotateLabelWID,					kDynamicDocumentsUIPrefix2 + 51)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIRotateILEWID,							kDynamicDocumentsUIPrefix2 + 52)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyOpacityGroupWID,				kDynamicDocumentsUIPrefix2 + 53)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyDesignOpacityLabelWID,			kDynamicDocumentsUIPrefix2 + 54)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyOpacityDropDownWID,				kDynamicDocumentsUIPrefix2 + 55)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIDesignGroupWID,							kDynamicDocumentsUIPrefix2 + 56)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIScaleLockButtonWID,						kDynamicDocumentsUIPrefix2 + 57)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIButtonTriggerWID,						kDynamicDocumentsUIPrefix2 + 58)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIShowProxyButtonWID,						kDynamicDocumentsUIPrefix2 + 59)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIEventMenuSelectorWID,					kDynamicDocumentsUIPrefix2 + 60)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIEventStaticTextWID,						kDynamicDocumentsUIPrefix2 + 61)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIConvertToMotionPathButtonWID,			kDynamicDocumentsUIPrefix2 + 62)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPreviewGroupWID,						kDynamicDocumentsUIPrefix2 + 63)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPresetSettingsGroupWID,					kDynamicDocumentsUIPrefix2 + 64)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPropertyDesignDropDownWID,				kDynamicDocumentsUIPrefix2 + 65)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIDurationNudgeWID,						kDynamicDocumentsUIPrefix2 + 66)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPlayNudgeWID,							kDynamicDocumentsUIPrefix2 + 67)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIScaleHorzNudgeWID,						kDynamicDocumentsUIPrefix2 + 68)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIScaleVertNudgeWID,						kDynamicDocumentsUIPrefix2 + 69)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIRotateNudgeWID,							kDynamicDocumentsUIPrefix2 + 70)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIShowTimingButtonWID,					kDynamicDocumentsUIPrefix2 + 71)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIClearAnimationButtonWID,				kDynamicDocumentsUIPrefix2 + 72)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIXFPointProxyLabelWID,					kDynamicDocumentsUIPrefix2 + 73)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIXFPointProxyWID,						kDynamicDocumentsUIPrefix2 + 74)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIHideAfterAnimateCheckboxWID,			kDynamicDocumentsUIPrefix2 + 75)

DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsDialogWidgetID,			kDynamicDocumentsUIPrefix2 + 76)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsDialogGroupWidgetID,		kDynamicDocumentsUIPrefix2 + 77)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsListBoxGroupWidgetID,		kDynamicDocumentsUIPrefix2 + 78)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsListBoxWidgetID,			kDynamicDocumentsUIPrefix2 + 79)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsButtonGroupWidgetID,		kDynamicDocumentsUIPrefix2 + 80)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsDoneButtonWidgetID,		kDynamicDocumentsUIPrefix2 + 81)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsDeleteButtonWidgetID,		kDynamicDocumentsUIPrefix2 + 82)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsDuplicateButtonWidgetID,	kDynamicDocumentsUIPrefix2 + 83)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsLoadButtonWidgetID,		kDynamicDocumentsUIPrefix2 + 84)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIManagePresetsSaveAsButtonWidgetID,		kDynamicDocumentsUIPrefix2 + 85)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPresetStaticTextWID,					kDynamicDocumentsUIPrefix2 + 86)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUIPresetPopupMenuWID,						kDynamicDocumentsUIPrefix2 + 87)
DECLARE_PMID(kWidgetIDSpace,			kAnimationUINoSelectionPreviewProxyWID,				kDynamicDocumentsUIPrefix2 + 88)
//gap
// Timing Panel
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelWidgetID,								kDynamicDocumentsUIPrefix2 + 100)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelEventStaticWidgetID,					kDynamicDocumentsUIPrefix2 + 101)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelDelayStaticWidgetID,					kDynamicDocumentsUIPrefix2 + 102)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelTreeBorderPanelWidgetID,				kDynamicDocumentsUIPrefix2 + 103)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelTreeWidgetID,							kDynamicDocumentsUIPrefix2 + 104)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelControlStripWidgetID,					kDynamicDocumentsUIPrefix2 + 105)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelGroupButtonWidgetID,					kDynamicDocumentsUIPrefix2 + 106)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelUngroupButtonWidgetID,					kDynamicDocumentsUIPrefix2 + 107)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelEventGroupWidgetID,						kDynamicDocumentsUIPrefix2 + 108)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelEventDropDownWidgetID,					kDynamicDocumentsUIPrefix2 + 109)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelDelayGroupWidgetID,						kDynamicDocumentsUIPrefix2 + 110)
DECLARE_PMID(kWidgetIDSpace,			kTimingDelayILEWidgetID,							kDynamicDocumentsUIPrefix2 + 111)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelDelaySecondStaticWidgetID,				kDynamicDocumentsUIPrefix2 + 112)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelElementWidgetID,						kDynamicDocumentsUIPrefix2 + 113)
DECLARE_PMID(kWidgetIDSpace,			kTimingItemElementItemNameWidgetID,					kDynamicDocumentsUIPrefix2 + 114)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelTreeNodeGroupWidgetID,					kDynamicDocumentsUIPrefix2 + 115)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelPreviewButtonWidgetID,					kDynamicDocumentsUIPrefix2 + 116)
DECLARE_PMID(kWidgetIDSpace,			kTimingDelayNudgeWidgetID,							kDynamicDocumentsUIPrefix2 + 117)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelNumPlaysGroupWidgetID,					kDynamicDocumentsUIPrefix2 + 118)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelPlayLinkedItemStaticWidgetID,			kDynamicDocumentsUIPrefix2 + 119)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelPlayLinkedItemNudgeWidgetID,			kDynamicDocumentsUIPrefix2 + 120)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelPlayLinkedItemEditBoxWidgetID,			kDynamicDocumentsUIPrefix2 + 121)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelPlayLinkedItemTimeStaticWidgetID,		kDynamicDocumentsUIPrefix2 + 122)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelLoopCheckBoxWidgetID,					kDynamicDocumentsUIPrefix2 + 123)
DECLARE_PMID(kWidgetIDSpace,			kTimingPanelLinkedItemStaticWidgetID,				kDynamicDocumentsUIPrefix2 + 124)
//gap

//Font Embedding
DECLARE_PMID(kWidgetIDSpace,			kEmbeddedFontsListBoxWidgetID,						kDynamicDocumentsUIPrefix2 + 130)
DECLARE_PMID(kWidgetIDSpace,			kTotalEmbeddedFontsWidgetID,						kDynamicDocumentsUIPrefix2 + 131)
DECLARE_PMID(kWidgetIDSpace,			kEmbeddedFontPanelWidgetID,							kDynamicDocumentsUIPrefix2 + 132)
DECLARE_PMID(kWidgetIDSpace,			kEmbeddedFontDescWidgetID,							kDynamicDocumentsUIPrefix2 + 133)
DECLARE_PMID(kWidgetIDSpace,			kFontInfoWidgetID,									kDynamicDocumentsUIPrefix2 + 134)
DECLARE_PMID(kWidgetIDSpace, kGIFPlayerWidgetID, kDynamicDocumentsUIPrefix2 + 135)


//----------------------------------------------------------------------------------------
// Error identifiers
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kActionIDSpace,			kPageTransitionsPanelActionID,					kDynamicDocumentsUIPrefix + 1)
DECLARE_PMID(kActionIDSpace,			kTransitionPanelChooseActionID,					kDynamicDocumentsUIPrefix + 2)
DECLARE_PMID(kActionIDSpace,			kTransitionPanelApplyToAllSpreadsActionID,		kDynamicDocumentsUIPrefix + 3)
DECLARE_PMID(kActionIDSpace,			kTransitionPanelClearAllTransitionsActionID,	kDynamicDocumentsUIPrefix + 4)

//gap

DECLARE_PMID(kActionIDSpace,			kAnimationUIPanelActionID,						kDynamicDocumentsUIPrefix + 12)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_LoadPresetID,				kDynamicDocumentsUIPrefix + 13)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_SavePresetID,				kDynamicDocumentsUIPrefix + 14)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_SaveAsPresetID,				kDynamicDocumentsUIPrefix + 15)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_DeletePresetID,				kDynamicDocumentsUIPrefix + 16)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_SepPresetID,					kDynamicDocumentsUIPrefix + 17)
//gap
DECLARE_PMID(kActionIDSpace,			kTimingPanelActionID,							kDynamicDocumentsUIPrefix + 20)
DECLARE_PMID(kActionIDSpace,			kTimingPanelReassignPageLoadEventActionID,		kDynamicDocumentsUIPrefix + 21)
DECLARE_PMID(kActionIDSpace,			kTimingPanelReassignPageClickEventActionID,		kDynamicDocumentsUIPrefix + 22)
DECLARE_PMID(kActionIDSpace,			kTimingPanelRemoveItemActionID,					kDynamicDocumentsUIPrefix + 23)
DECLARE_PMID(kActionIDSpace,			kTimingPanelSepActionID,						kDynamicDocumentsUIPrefix + 24)
DECLARE_PMID(kActionIDSpace,			kLiquidLayoutPanelActionID,						kDynamicDocumentsUIPrefix + 25)
// DECLARE_PMID(kActionIDSpace,			kLayoutAdjustmentPrefsActionID,					kDynamicDocumentsUIPrefix + 26)
DECLARE_PMID(kActionIDSpace,			kLiquidLayoutActionID,							kDynamicDocumentsUIPrefix + 27)
DECLARE_PMID(kActionIDSpace,			kLiquidLayoutSepActionID,						kDynamicDocumentsUIPrefix + 28)
DECLARE_PMID(kActionIDSpace,			kAlternateLayoutSepActionID,					kDynamicDocumentsUIPrefix + 29)
//gap
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_OnPageLoadEventActionID,		kDynamicDocumentsUIPrefix + 31)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_OnPageClickEventActionID,	kDynamicDocumentsUIPrefix + 32)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_OnClickSelfEventActionID,	kDynamicDocumentsUIPrefix + 33)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_OnRollOverSelfEventActionID,	kDynamicDocumentsUIPrefix + 34)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_SepEventActionID,			kDynamicDocumentsUIPrefix + 35)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_OnButtonEventActionID,		kDynamicDocumentsUIPrefix + 36)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_ManagePresetID,				kDynamicDocumentsUIPrefix + 37)
//gap
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_ConvertToMotionPathActionID,	kDynamicDocumentsUIPrefix + 50)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_PresetPopupMenuActionID,		kDynamicDocumentsUIPrefix + 51)
//gap
DECLARE_PMID(kActionIDSpace,            kHTMLFXLPreviewActionID,                        kDynamicDocumentsUIPrefix + 60)
//gap

// DONT USE THE IDS 100-255 (155) they are reserved for presets (dynamic menu)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_FirstPresetDynamicActionID,	kDynamicDocumentsUIPrefix + 100)
DECLARE_PMID(kActionIDSpace,			kAnimationUIAction_LastPresetDynamicActionID,	kDynamicDocumentsUIPrefix + 255)

//----------------------------------------------------------------------------------------
// Message identifiers
//----------------------------------------------------------------------------------------
//gap

//----------------------------------------------------------------------------------------
// Tree Node ID types
//----------------------------------------------------------------------------------------
#define kTimingPanelTreeNodeID        kDynamicDocumentsUIPrefix + 1 

//----------------------------------------------------------------------------------------
// Service identifiers
//----------------------------------------------------------------------------------------

#define kPageTransitionsDialogRsrcID	6000	// I have to define the resource ID in the public file so that other plugins can access it.

//----------------------------------------------------------------------------------------
// Misc defines
//----------------------------------------------------------------------------------------

#define kMinSize						10		// Minimum output width and height
#define kMaxSize						4096	// Maximum output width and height
#define kMinScale						1		// Minimum output scale percentage
#define kMaxScale						1000	// Maximum output scale percentage
#define kMinFrameRate					1		// Minimum frame rate
#define kMaxFrameRate					48		// Maximum frame rate
#define kDefaultFrameRate				24		// Default frame rate
#define kMinRasterRes					72		// Minimum raster resolution
#define kMaxRasterRes					300		// Maximum raster resolution
#define kDefaultRasterRes				72		// Default raster resolution

#endif // __DynamicDocumentsUIID__

