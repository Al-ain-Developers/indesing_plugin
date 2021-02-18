//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TextFrameOptionsID.h $
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
//========================================================================================

#ifndef __TextFrameOptionsID__
#define __TextFrameOptionsID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTextFrameOptionsPrefix		RezLong(0xad00)


// <Start IDC>
// PluginID
#define kTextFrameOptionsPluginName	"Text Frame Options"

DECLARE_PMID(kPlugInIDSpace, kTextFrameOptionsPluginID, kTextFrameOptionsPrefix + 1)


//---------------------------------------------------------------
// Resource IDs
//---------------------------------------------------------------

#define kFrameOptionsStringsRsrcID			800
#define kFrameOptionsStringsNoTransRsrcID	900

// <Service ID>
//---------------------------------------------------------------
// Service IDs
//---------------------------------------------------------------


// <Class ID>
//---------------------------------------------------------------
// Boss IDs
//---------------------------------------------------------------
DECLARE_PMID(kClassIDSpace, kFrameOptionsDialogBoss, kTextFrameOptionsPrefix + 1)
DECLARE_PMID(kClassIDSpace, kFrameOptionsMenuActionBoss, kTextFrameOptionsPrefix + 2)
DECLARE_PMID(kClassIDSpace, kBaselineFrameGridPanelBoss, kTextFrameOptionsPrefix + 3)
DECLARE_PMID(kClassIDSpace, kFrameGeneralOptionsPanelBoss, kTextFrameOptionsPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTextFrameOptionsDialogBoss, kTextFrameOptionsPrefix + 5)
DECLARE_PMID(kClassIDSpace, kObjStylesBaselineFrameGridPanelWidgetBoss, kTextFrameOptionsPrefix + 6)
DECLARE_PMID(kClassIDSpace, kObjStylesTextOptionsPanelWidgetBoss, kTextFrameOptionsPrefix + 7)
DECLARE_PMID(kClassIDSpace, kBaselineFrameGridColorWidgetBoss,	  kTextFrameOptionsPrefix + 8)
DECLARE_PMID(kClassIDSpace, kObjectFCTextOptionsPanelWidgetBoss, kTextFrameOptionsPrefix + 9)
DECLARE_PMID(kClassIDSpace, kObjectFCBaselineFrameGridPanelWidgetBoss, kTextFrameOptionsPrefix + 10)
//gap
DECLARE_PMID(kClassIDSpace, kFlexibleLimitEditBoxWidgetBoss,	kTextFrameOptionsPrefix + 12)
DECLARE_PMID(kClassIDSpace, kTextFrameAutoSizePanelBoss,	kTextFrameOptionsPrefix + 13)
DECLARE_PMID(kClassIDSpace, kObjStylesTextFrameAutoSizePanelWidgetBoss,	kTextFrameOptionsPrefix + 14)
DECLARE_PMID(kClassIDSpace, kObjectFCTextFrameAutoSizePanelWidgetBoss,	kTextFrameOptionsPrefix + 15)
DECLARE_PMID(kClassIDSpace, kTFAutoSizeYMeasureEditBoxWidgetBoss, kTextFrameOptionsPrefix + 16)
DECLARE_PMID(kClassIDSpace, kTFAutoSizeXMeasureEditBoxWidgetBoss, kTextFrameOptionsPrefix + 17)

DECLARE_PMID(kClassIDSpace, kTextFrameFootnoteOptionsPanelBoss,					kTextFrameOptionsPrefix + 18)
DECLARE_PMID(kClassIDSpace, kObjStylesTextFrameFootnoteOptionsPanelWidgetBoss,	kTextFrameOptionsPrefix + 19)
DECLARE_PMID(kClassIDSpace, kObjectFCTextFrameFootnoteOptionsPanelWidgetBoss, 	kTextFrameOptionsPrefix + 20)

DECLARE_PMID(kClassIDSpace, kTFFootnoteOptionsYMeasureEditBoxWidgetBoss, kTextFrameOptionsPrefix + 21 )
DECLARE_PMID(kClassIDSpace, kTFFootnoteOptionsXMeasureEditBoxWidgetBoss, kTextFrameOptionsPrefix + 22 )


//gap
DECLARE_PMID(kClassIDSpace, kAnchoredFrameDialogBoss, kTextFrameOptionsPrefix + 100)
DECLARE_PMID(kClassIDSpace, kAnchoredFrameMenuActionBoss, kTextFrameOptionsPrefix + 101)
DECLARE_PMID(kClassIDSpace, kVerticalRuleStrokeColorBoss, kTextFrameOptionsPrefix + 102)
DECLARE_PMID(kClassIDSpace, kVerticalRuleStrokeTypeBoss, kTextFrameOptionsPrefix + 103)
DECLARE_PMID(kClassIDSpace, kTextFrameColumnRulePanelBoss, kTextFrameOptionsPrefix + 104)
DECLARE_PMID(kClassIDSpace, kTextFrameOptDialogTitleBoss, kTextFrameOptionsPrefix + 105)
DECLARE_PMID(kClassIDSpace, kObjStylesColumnRulePanelWidgetBoss, kTextFrameOptionsPrefix + 106)
DECLARE_PMID(kClassIDSpace, kObjectFCColumnRulePanelWidgetBoss, kTextFrameOptionsPrefix + 107)


// Categories for Object Style Attributes
DECLARE_PMID(kClassIDSpace, kBaselineFrameGridDataAttributeCategory, kTextFrameOptionsPrefix + 200)
DECLARE_PMID(kClassIDSpace, kTextFrameAutoSizeDataAttributeCategory, kTextFrameOptionsPrefix + 201)
DECLARE_PMID(kClassIDSpace, kTextFrameFootnoteOptionsDataAttributeCategory, kTextFrameOptionsPrefix + 202)
DECLARE_PMID(kClassIDSpace, kColumnRuleDataAttributeCategory, kTextFrameOptionsPrefix + 203)
DECLARE_PMID(kClassIDSpace, kTFOInfoIconWidgetBoss, kTextFrameOptionsPrefix + 204)
DECLARE_PMID(kClassIDSpace, kColumnRuleMeasureEditWidgetBoss, kTextFrameOptionsPrefix + 205)

// <Interface ID>
//---------------------------------------------------------------
// Interface IDs
//---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOSIZEBOOLDATA, kTextFrameOptionsPrefix + 1)

// <Implementation ID>
//---------------------------------------------------------------
// Implementation IDs
//---------------------------------------------------------------
DECLARE_PMID(kImplementationIDSpace, kFrameOptionsObserverImpl, kTextFrameOptionsPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kFrameOptionsControllerImpl, kTextFrameOptionsPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kFrameOptionsMenuActionImpl, kTextFrameOptionsPrefix + 3)
// gap
DECLARE_PMID(kImplementationIDSpace, kTextFrameOptionsDataImpl, kTextFrameOptionsPrefix + 6)
// gap
DECLARE_PMID(kImplementationIDSpace, kTextFrameEventActionImpl, kTextFrameOptionsPrefix + 8)

DECLARE_PMID(kImplementationIDSpace, kTextFrameOptionsDialogCreatorImpl, kTextFrameOptionsPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kTextFrameGeneralPanelCreatorImpl,	 kTextFrameOptionsPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kBaselineFrameGridPanelCreatorImpl, kTextFrameOptionsPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kBaselineFrameGridObserverImpl,	 kTextFrameOptionsPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kBaselineFrameGridControllerImpl,	 kTextFrameOptionsPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kObjStylesBaselineFrameGridPanelCreatorImpl, kTextFrameOptionsPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kObjStylesBaselineFrameGridPanelObserverImpl, kTextFrameOptionsPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTextOptionsPanelCreatorImpl, kTextFrameOptionsPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kOSFrameOptionsPanelObserverImpl, kTextFrameOptionsPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kBaselineFrameGridColorListControlDataImpl, kTextFrameOptionsPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kObjStylesBaselineFrameGridPanelDataImpl, kTextFrameOptionsPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kObjStylesFrameOptionsPanelDataImpl, kTextFrameOptionsPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kTextFrameAutoSizeControllerImpl, kTextFrameOptionsPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kTextFrameAutoSizeObserverImpl, kTextFrameOptionsPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kTextFrameAutoSizePanelCreatorImpl, kTextFrameOptionsPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTextFrameAutoSizePanelDataImpl, kTextFrameOptionsPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTextFrameAutoSizePanelCreatorImpl, kTextFrameOptionsPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTextFrameAutoSizePanelObserverImpl, kTextFrameOptionsPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextFrameAutoSizePanelCreatorImpl, kTextFrameOptionsPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextFrameAutoSizePanelObserverImpl, kTextFrameOptionsPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextFrameAutoSizePanelDataImpl, kTextFrameOptionsPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kTFAutoSizeMeasurementTextValidationImpl, kTextFrameOptionsPrefix + 30)

DECLARE_PMID(kImplementationIDSpace, kTextFrameFootnoteOptionsPanelCreatorImpl, 			kTextFrameOptionsPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kTextFrameFootnoteOptionsObserverImpl, 				kTextFrameOptionsPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kTextFrameFootnoteOptionsControllerImpl, 				kTextFrameOptionsPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTextFrameFootnoteOptionsPanelCreatorImpl, 	kTextFrameOptionsPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTextFrameFootnoteOptionsPanelObserverImpl,	kTextFrameOptionsPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTextFrameFootnoteOptionsPanelDataImpl, 		kTextFrameOptionsPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextFrameFootnoteOptionsPanelCreatorImpl, 	kTextFrameOptionsPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextFrameFootnoteOptionsPanelObserverImpl, 	kTextFrameOptionsPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kTFFootnoteOptionsMeasurementTextValidationImpl, 		kTextFrameOptionsPrefix + 39)

DECLARE_PMID(kImplementationIDSpace, kFrameOptionsSelectableDialogObserverImpl, kTextFrameOptionsPrefix + 40)

//gap

//gap
DECLARE_PMID(kImplementationIDSpace, kFlexibleTextValueImpl, kTextFrameOptionsPrefix + 98)
//gap
DECLARE_PMID(kImplementationIDSpace, kAnchoredFrameObserverImpl, kTextFrameOptionsPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kAnchoredFrameControllerImpl, kTextFrameOptionsPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kAnchoredFrameMenuActionImpl, kTextFrameOptionsPrefix + 103)
//gap
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextFrameBaselineOptionsAttrInfoImpl, kTextFrameOptionsPrefix + 105 )
DECLARE_PMID(kImplementationIDSpace, kObjectFCBaselineFrameGridPanelCreatorImpl, kTextFrameOptionsPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kObjectFCBaselineFrameGridPanelObserverImpl, kTextFrameOptionsPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextOptionsPanelCreatorImpl, kTextFrameOptionsPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kObjectFCFrameOptionsPanelObserverImpl, kTextFrameOptionsPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kTextFrameColumnRulePanelCreatorImpl, kTextFrameOptionsPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kTextFrameColumnRuleObserverImpl, kTextFrameOptionsPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kTextFrameColumnRuleControllerImpl, kTextFrameOptionsPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kTextFrameOptDialogTitleViewImpl, kTextFrameOptionsPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kObjStylesColumnRulePanelCreatorImpl, kTextFrameOptionsPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kObjStylesColumnRulePanelObserverImpl, kTextFrameOptionsPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kObjStylesColumnRulePanelDataImpl, kTextFrameOptionsPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextFrameColumnRulePanelCreatorImpl, kTextFrameOptionsPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kObjectFCTextFrameColumnRulePanelObserverImpl, kTextFrameOptionsPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kTFOInfoIconTipImpl, kTextFrameOptionsPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kColumnRuleMeasureTypeImpl, kTextFrameOptionsPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kColumnRuleColorDropDownTipImpl, kTextFrameOptionsPrefix + 121)

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kTextFrameSelectableDialogService, kTextFrameOptionsPrefix + 1)

// <Widget ID>
//---------------------------------------------------------------
// Widget ID's
//---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kTopInsetEditWidgetID, kTextFrameOptionsPrefix + 1 )
DECLARE_PMID(kWidgetIDSpace, kLeftInsetEditWidgetID, kTextFrameOptionsPrefix + 2 )
DECLARE_PMID(kWidgetIDSpace, kTETopInsetTextWidgetID, kTextFrameOptionsPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kTELeftInsetTextWidgetID, kTextFrameOptionsPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kBottomInsetEditWidgetID, kTextFrameOptionsPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kRightInsetEditWidgetID, kTextFrameOptionsPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kTEBottomInsetTextWidgetID, kTextFrameOptionsPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kTERightInsetTextWidgetID, kTextFrameOptionsPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kVerticalCheckBoxWidgetID, kTextFrameOptionsPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kInsetSpacingTitleTextWidgetID, kTextFrameOptionsPrefix + 10)

DECLARE_PMID(kWidgetIDSpace, kNumberEditWidgetID, kTextFrameOptionsPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kNumberTextWidgetID, kTextFrameOptionsPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kGutterEditWidgetID, kTextFrameOptionsPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kGutterTextWidgetID, kTextFrameOptionsPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kWidthEditWidgetID, kTextFrameOptionsPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kWidthText_WidgetID, kTextFrameOptionsPrefix + 16)
// gap
DECLARE_PMID(kWidgetIDSpace, kColumnsTitleTextWidgetID, kTextFrameOptionsPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kPreviewCheckBoxWidgetID, kTextFrameOptionsPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kIgnoreWrapsCheckBoxWidgetID, kTextFrameOptionsPrefix + 20)

DECLARE_PMID(kWidgetIDSpace, kFrameOptInsetChainWidgetID, kTextFrameOptionsPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kColumnsGroupWidgetID, kTextFrameOptionsPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kFlexibleWidthMaxEditWidgetID, kTextFrameOptionsPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kFrameOptParentWidgetId, kTextFrameOptionsPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kFrameOptPosGroupWidgetId, kTextFrameOptionsPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kFrameOptMiscGroupWidgetId, kTextFrameOptionsPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kTopInsetNudgeWidgetID, kTextFrameOptionsPrefix + 27 )
DECLARE_PMID(kWidgetIDSpace, kResizingDropDownWidgetID, kTextFrameOptionsPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kLeftInsetNudgeWidgetID, kTextFrameOptionsPrefix + 29 )

DECLARE_PMID(kWidgetIDSpace, kBottomInsetNudgeWidgetID, kTextFrameOptionsPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kRightInsetNudgeWidgetID, kTextFrameOptionsPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kNumberNudgeWidgetID, kTextFrameOptionsPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kGutterNudgeWidgetID, kTextFrameOptionsPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kVJInterParaMaxStaticWidgetId, kTextFrameOptionsPrefix + 34)
// gap
DECLARE_PMID(kWidgetIDSpace, kWidthNudge_WidgetID, kTextFrameOptionsPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kFirstBaselineGroupWidgetId, kTextFrameOptionsPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kFirstBaselineTitleTextWidgetID, kTextFrameOptionsPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kOffsetWidgetID, kTextFrameOptionsPrefix + 39)

DECLARE_PMID(kWidgetIDSpace, kOffsetDropdownWidgetID, kTextFrameOptionsPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kFlexibleWidthMaxTextWidgetID, kTextFrameOptionsPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kVerticalTextToolWidgetID, kTextFrameOptionsPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kVerticalTextGroupWidgetId, kTextFrameOptionsPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kVerticalTextDropdownWidgetId, kTextFrameOptionsPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kVerticalTextToolTitleWidgetId, kTextFrameOptionsPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kVJInterParaMaxWidgetId, kTextFrameOptionsPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kVJInterParaMaxNudgeWidgetID, kTextFrameOptionsPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kMinFirstLineOffsetWidgetId, kTextFrameOptionsPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kMinFirstLineOffsetNudgeWidgetID, kTextFrameOptionsPrefix + 49)

DECLARE_PMID(kWidgetIDSpace, kMinFirstLineOffsetTextWidgetId, kTextFrameOptionsPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kTextFrameOptionsDialogWidgetID, kTextFrameOptionsPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kTFOSelectButtonsPanelWidgetID,	kTextFrameOptionsPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kTFOSelectOnlyButtonsPanelWidgetID,kTextFrameOptionsPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kBaselineOptionWidgetID,			kTextFrameOptionsPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kBaselineFrameGridGroupWidgetID,	kTextFrameOptionsPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kBaselineFrameGridTitleTextWidgetID,	kTextFrameOptionsPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kUseCustomBaselineGridCheckBoxWidgetID,	kTextFrameOptionsPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kStartingOffsetTextWidgetID,	kTextFrameOptionsPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kStartingOffsetWidgetID,		kTextFrameOptionsPrefix + 59)

DECLARE_PMID(kWidgetIDSpace, kRelativeToWidgetID,			kTextFrameOptionsPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kRelativeToDropDownWidgetID,	kTextFrameOptionsPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kIncrementEveryTextWidgetID,	kTextFrameOptionsPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kIncrementEveryWidgetID,		kTextFrameOptionsPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kStartingOffsetNudgeWidgetID,	kTextFrameOptionsPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kIncrementEveryNudgeWidgetID,	kTextFrameOptionsPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kObjStylesBaselineFrameGridPanelWidgetID, kTextFrameOptionsPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTextOptionsPanelWidgetID, kTextFrameOptionsPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kBaselineFrameGridColorTextWidgetID, kTextFrameOptionsPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kBaselineFrameGridColorDDWidgetID,	 kTextFrameOptionsPrefix + 69)

DECLARE_PMID(kWidgetIDSpace, kTextCopyFitOptionsGroupWidgetId,	 kTextFrameOptionsPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kTCFOptionsTitleTextWidgetID,	 kTextFrameOptionsPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kTCFEnableTrackingWidgetID,	 kTextFrameOptionsPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kTCFEnableLeadingWidgetID,	 kTextFrameOptionsPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kTCFEnablePtSizeWidgetID,	 kTextFrameOptionsPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kTCFTrackingPriorityWidgetID,	 kTextFrameOptionsPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kTCFLeadingPriorityWidgetID,	 kTextFrameOptionsPrefix + 79)

DECLARE_PMID(kWidgetIDSpace, kTCFPtSizePriorityWidgetID,	 kTextFrameOptionsPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kTCFTrackingMinimumWidgetID,	 kTextFrameOptionsPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kTCFLeadingMinimumWidgetID,	 kTextFrameOptionsPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kTCFPtSizeMinimumWidgetID,	 kTextFrameOptionsPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kTCFTrackingMaximumWidgetID,	kTextFrameOptionsPrefix +84)
DECLARE_PMID(kWidgetIDSpace, kTCFLeadingMaximumWidgetID,	 	kTextFrameOptionsPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kTCFPtSizeMaximumWidgetID,		kTextFrameOptionsPrefix + 86)

DECLARE_PMID(kWidgetIDSpace, kTCFEnableSpBeforeWidgetID,	 kTextFrameOptionsPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kTCFEnableSpAfterWidgetID,	 kTextFrameOptionsPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kTCFEnableSetWidthWidgetID,	 kTextFrameOptionsPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kTCFSpBeforePriorityWidgetID,	 kTextFrameOptionsPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kTCFSpAfterPriorityWidgetID,	 kTextFrameOptionsPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kTCFSetWidthPriorityWidgetID,	 kTextFrameOptionsPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kTCFSpBeforeMinimumWidgetID,	 kTextFrameOptionsPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kTCFSpAfterMinimumWidgetID,		 kTextFrameOptionsPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kTCFSetWidthMinimumWidgetID,	 kTextFrameOptionsPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kTCFSpBeforeMaximumWidgetID,	 kTextFrameOptionsPrefix + 99)

DECLARE_PMID(kWidgetIDSpace, kTCFSpAfterMaximumWidgetID,		 kTextFrameOptionsPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kTCFSetWidthMaximumWidgetID,	 kTextFrameOptionsPrefix + 101)

DECLARE_PMID(kWidgetIDSpace, kVJBalanceColumnsStaticWidgetID, kTextFrameOptionsPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kVJBalanceColumnsWidgetID, kTextFrameOptionsPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kFlexibleWidthMaxNudgeWidgetID, kTextFrameOptionsPrefix + 112)

DECLARE_PMID(kWidgetIDSpace, kAutoSizeWidgetID,							kTextFrameOptionsPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTextFrameAutoSizePanelWidgetID,	kTextFrameOptionsPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kASLabelWidgetID,							kTextFrameOptionsPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kASDimensionDropdownWidgetID,				kTextFrameOptionsPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kASAnchorPointClusterID,					kTextFrameOptionsPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kASTopLeftAnchorIconWidgetID,				kTextFrameOptionsPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kASTopCenterAnchorIconWidgetID,			kTextFrameOptionsPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kASTopRightAnchorIconWidgetID,				kTextFrameOptionsPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kASLeftCenterAnchorIconWidgetID,			kTextFrameOptionsPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kASCenterAnchorIconWidgetID,				kTextFrameOptionsPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kASRightCenterAnchorIconWidgetID,			kTextFrameOptionsPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kASBottomLeftAnchorIconWidgetID,			kTextFrameOptionsPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kASBottomCenterAnchorIconWidgetID,			kTextFrameOptionsPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kASBottomRightAnchorIconWidgetID,			kTextFrameOptionsPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kASConstraintsGroupWidgetID,				kTextFrameOptionsPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kASConstraintsGroupTitleWidgetID,			kTextFrameOptionsPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kASMinHeightCheckBoxWidgetID,				kTextFrameOptionsPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kASMinWidthCheckBoxWidgetID,				kTextFrameOptionsPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kASMinHeightDropDownWidgetID,				kTextFrameOptionsPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kASMinWidthDropDownWidgetID,				kTextFrameOptionsPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kASMinHeightNudgeWidgetID,					kTextFrameOptionsPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kASMinHeightEditBoxWidgetID,				kTextFrameOptionsPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kASMinWidthNudgeWidgetID,					kTextFrameOptionsPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kASMinWidthEditBoxWidgetID,				kTextFrameOptionsPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kASMinHeightNudgeEditBoxWidgetID,			kTextFrameOptionsPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kASMinWidthNudgeEditBoxWidgetID,			kTextFrameOptionsPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kASNoLineBreakCheckBoxWidgetID,			kTextFrameOptionsPrefix + 139)

DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsWidgetID,					 		    kTextFrameOptionsPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kObjStylesTextFrameFootnoteOptionsPanelWidgetID,		kTextFrameOptionsPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsSecondGroupWidgetID,			 		kTextFrameOptionsPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsEnableOverridesCheckBoxWidgetID,		kTextFrameOptionsPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsSpanAcrossCheckBoxWidgetID,	 		kTextFrameOptionsPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsSpacingOptionsTitleTextWidgetID,		kTextFrameOptionsPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsMinimumSpacingTextWidgetID,	 		kTextFrameOptionsPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsMinimumSpacingNudgeWidgetID,	 		kTextFrameOptionsPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsMinimumSpacingEditBoxWidgetID,	 		kTextFrameOptionsPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsSpaceBetweenFootnotesTextWidgetID,		kTextFrameOptionsPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsSpaceBetweenFootnotesNudgeWidgetID,	kTextFrameOptionsPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kFootnoteOptionsSpaceBetweenFootnotesEditBoxWidgetID,	kTextFrameOptionsPrefix + 151)

DECLARE_PMID(kWidgetIDSpace, kVerticalRuleEnableCheckBoxWID,						kTextFrameOptionsPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleOffsetNudgeWidgetID,						kTextFrameOptionsPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleOffsetEditWidgetID,						kTextFrameOptionsPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleTopInsetNudgeWidgetID,					kTextFrameOptionsPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleTopInsetEditWidgetID,						kTextFrameOptionsPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleInsetChainWidgetID,						kTextFrameOptionsPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleBottomInsetNudgeWidgetID,					kTextFrameOptionsPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleBottomInsetEditWidgetID,					kTextFrameOptionsPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleWidthNudgeWidgetID,						kTextFrameOptionsPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleWidthEditBoxWidgetID,						kTextFrameOptionsPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleStrokeColorWidgetID,						kTextFrameOptionsPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleStrokeTypeWidgetID,						kTextFrameOptionsPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleStrokeTintNudgeWidgetId,					kTextFrameOptionsPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleStrokeTintComboBoxWidgetID,				kTextFrameOptionsPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleStrokeOverprintCheckBoxWID,				kTextFrameOptionsPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kVerticalRulePanelWidgetID,							kTextFrameOptionsPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kTextFrameColumnRuleWidgetID,							kTextFrameOptionsPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kVROffsetTitleHeaderTextWidgetID,						kTextFrameOptionsPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kVRStrokeTitleHeaderTextWidgetID,						kTextFrameOptionsPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kTextFrameInfoIconWidgetID,							kTextFrameOptionsPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kTextFrameInfoIconGroupWidgetID,						kTextFrameOptionsPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kObjStylesColumnRulePanelWidgetID,						kTextFrameOptionsPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kVRInsetTitleHeaderTextWidgetID,						kTextFrameOptionsPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kVerticalRuleTintPanelWidgetID,						kTextFrameOptionsPrefix + 175)


//<Action ID>
DECLARE_PMID(kActionIDSpace, kFrameOptionsActionID, kTextFrameOptionsPrefix + 1)
DECLARE_PMID(kActionIDSpace, kTextFrameOptionsSepActionID, kTextFrameOptionsPrefix + 2)
DECLARE_PMID(kActionIDSpace, kFrameOptionsSepActionID, kTextFrameOptionsPrefix + 3)
DECLARE_PMID(kActionIDSpace, kBaselineOptionsActionID, kTextFrameOptionsPrefix + 4)
DECLARE_PMID(kActionIDSpace, kContextSearchAdobeStockActionID, kTextFrameOptionsPrefix + 5)
DECLARE_PMID(kActionIDSpace, kContextSearchAdobeStockSepActionID, kTextFrameOptionsPrefix + 6)

//gap

DECLARE_PMID(kActionIDSpace, kAnchoredFramesActionID, kTextFrameOptionsPrefix + 100)




#endif // __TextFrameOptionsID__
