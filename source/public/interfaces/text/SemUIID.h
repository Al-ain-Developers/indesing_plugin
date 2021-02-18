//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/SemUIID.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//  
//  Usage rights licenced to Adobe Inc. 1993 - 2008.
//  
//========================================================================================

#ifndef __SemUIID__
#define __SemUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSemUIPrefix	RezLong(0xf5800) 	/* doublecheck with DeveloperPrefix.h */

// PluginID
#define kSemUIPluginName 			"ME UI"
DECLARE_PMID(kPlugInIDSpace, kSemUIPluginID, kSemUIPrefix + 1)

//---------------------------------------------------------------
// Resource IDs
//---------------------------------------------------------------
#define kMEToolDefRsrcID			1285
#define kTOPMEToolDefRsrcID			1286
#define kAXtFontIconRsrcID			1287
#define kDTFontIconRsrcID			1288
//---------------------------------------------------------------
// <Class ID>
//---------------------------------------------------------------
//gap
DECLARE_PMID(kClassIDSpace, kSemUIHookBoss, kSemUIPrefix + 2)	// hooks the SemPanel into the TextPanel Dialog
DECLARE_PMID(kClassIDSpace, kSemUIDialogWidget, kSemUIPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kSemUIDialogWidgetBoss, kSemUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kOTOverlapswashCheckBoxBoss, kSemUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kOTStylisticAlternatesCheckBoxBoss, kSemUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kOTJustificationAlternatesCheckBoxBoss, kSemUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kOTStretchAlternatesCheckBoxBoss, kSemUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kDiacPosObserverBoss, kSemUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kDirOverrideObserverBoss, kSemUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kDigitsObserverBoss, kSemUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kKashidasObserverBoss, kSemUIPrefix + 13)
//gap
//gap
//gap
//gap
//gap
//gap
DECLARE_PMID(kClassIDSpace, kMEToolBoss,				kSemUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kMEToolTrackerBoss,			kSemUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kMEToolTrackerRegisterBoss,	kSemUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kMEFrameTrackerBoss,		kSemUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kMEFrameToolBoss,			kSemUIPrefix + 24)
#ifdef qME_CS3
DECLARE_PMID(kClassIDSpace, kMETextTrackerBoss,			kSemUIPrefix + 25)
#endif
DECLARE_PMID(kClassIDSpace, kTOPMEToolBoss,				kSemUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, kTOPMEToolTrackerBoss,		kSemUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kKashidaCheckBoxBoss,		kSemUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kDefaultDirCheckBoxBoss,	kSemUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kRTLDirCheckBoxBoss,		kSemUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kLTRDirCheckBoxBoss,		kSemUIPrefix + 31)
//DECLARE_PMID(kClassIDSpace, kSemUIKBSCBoss,				kSemUIPrefix + 36)	//Not needed - Merged with kSemUIActionComponentBoss
DECLARE_PMID(kClassIDSpace, kSemUIActionComponentBoss,	kSemUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kDefaultDigitsCheckBoxBoss,	kSemUIPrefix + 38)
DECLARE_PMID(kClassIDSpace, kNativeDigitsCheckBoxBoss,	kSemUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kArabicDigitsCheckBoxBoss,	kSemUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kHindiDigitsCheckBoxBoss,	kSemUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, kFarsiDigitsCheckBoxBoss,	kSemUIPrefix + 42)
DECLARE_PMID(kClassIDSpace, kDiacOffsetPanelWidgetBoss,	kSemUIPrefix + 43)
DECLARE_PMID(kClassIDSpace, kDiacXOffsetObserverBoss,	kSemUIPrefix + 44)
DECLARE_PMID(kClassIDSpace, kDiacYOffsetObserverBoss,	kSemUIPrefix + 45)
//gap
//gap
//gap
//gap
//gap
DECLARE_PMID(kClassIDSpace, kDefaultKbdDirCheckBoxBoss, kSemUIPrefix + 50)
DECLARE_PMID(kClassIDSpace, kLTRKbdDirCheckBoxBoss,     kSemUIPrefix + 51)
DECLARE_PMID(kClassIDSpace, kRTLKbdDirCheckBoxBoss,     kSemUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kMEInputOptionsPanelWidgetBoss, kSemUIPrefix + 53)
//gap

// Tables R2L
DECLARE_PMID(kClassIDSpace, kTablesUIChangeTableDirCmdBoss, kSemUIPrefix + 60)

DECLARE_PMID(kClassIDSpace, kMETitleNameEditBoxWidgetBoss,	kSemUIPrefix + 61)
DECLARE_PMID(kClassIDSpace, kMETitleLanguagePopupComponentBoss,kSemUIPrefix + 62)

DECLARE_PMID(kClassIDSpace, kSetMECursorOptionsPrefCmdBoss,kSemUIPrefix + 63)

//Reverse Layout
DECLARE_PMID (kClassIDSpace, kInvertR2LBoss, kSemUIPrefix + 64)
DECLARE_PMID (kClassIDSpace, kInvertR2LMenuComponentBoss, kSemUIPrefix + 65)
DECLARE_PMID (kClassIDSpace, kGraphicOptionsInvertR2LOnWidgetBoss, kSemUIPrefix + 66)
DECLARE_PMID (kClassIDSpace, kObjectOptionsInvertR2LOnWidgetBoss, kSemUIPrefix + 67)
DECLARE_PMID (kClassIDSpace, kStoriesOptionsInvertR2LOnWidgetBoss, kSemUIPrefix + 68)


//---------------------------------------------------------------
// <Message ID>
//---------------------------------------------------------------
// classid messages 100, protocol is IID_ITABRULERDATA
DECLARE_PMID(kMessageIDSpace, kLTRParaMessage, kSemUIPrefix + 100    /* changedBy is a TabStop. TabAlignObserver (TabPanel button) -> TabRulerObserver. */)
DECLARE_PMID(kMessageIDSpace, kRTLParaMessage, kSemUIPrefix + 101    /* changedBy is a TabStop. TabAlignObserver (TabPanel button) -> TabRulerObserver. */)

//---------------------------------------------------------------
// <Implementation ID>
//---------------------------------------------------------------
//gap
DECLARE_PMID(kImplementationIDSpace, kSemUICoreDialogRsrcData, kSemUIPrefix + 2)	// returns kSemPanelCoreDialogRsrcID
DECLARE_PMID(kImplementationIDSpace, kSemUIDiacPosObserverImpl, kSemUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSemUICharDirObserverImpl, kSemUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSemUIDigitsObserverImpl, kSemUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSemUIKashidasObserverImpl, kSemUIPrefix + 6)
//gap
//gap
DECLARE_PMID(kImplementationIDSpace, kTOPMEToolTrackerImpl,			kSemUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kMEToolImpl,					kSemUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kMEToolCursorProviderImpl,		kSemUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kMEToolTrackerImpl,			kSemUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kMEToolTrackerRegisterImpl,	kSemUIPrefix + 13)
//gap
DECLARE_PMID(kImplementationIDSpace, kTOPMEToolImpl,				kSemUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kKashidaObserverImpl,			kSemUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kTOPMEToolCursorProviderImpl,	kSemUIPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kTabRulerDataMEImpl,			kSemUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kDefaultDirObserverImpl,		kSemUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kRTLDirObserverImpl,			kSemUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kLTRDirObserverImpl,			kSemUIPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kSemUIKBSCImpl,				kSemUIPrefix + 22)	//Not needed
DECLARE_PMID(kImplementationIDSpace, kSemUIActionComponentImpl,		kSemUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kDefaultDigitsObserverImpl,	kSemUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kNativeDigitsObserverImpl,		kSemUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kArabicDigitsObserverImpl,		kSemUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kHindiDigitsObserverImpl,		kSemUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kFarsiDigitsObserverImpl,		kSemUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kDiacXOffsetObserverImpl,		kSemUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kDiacYOffsetObserverImpl,		kSemUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kMESymetrizeImpl,				kSemUIPrefix + 31)
//gap
DECLARE_PMID(kImplementationIDSpace, kDefaultKbdDirObserverImpl,    kSemUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kRTLKbdDirObserverImpl,        kSemUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kLTRKbdDirObserverImpl,        kSemUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kMEInputPrefsPanelCreatorImpl,      kSemUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kMEInputPrefsDialogControllerImpl,     kSemUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kMEInputPrefsDialogObserverImpl,     kSemUIPrefix + 45)
//gap

// Tables R2L
DECLARE_PMID(kImplementationIDSpace, kTablesUIChangeTableDirCmdImpl,kSemUIPrefix + 60)

DECLARE_PMID(kImplementationIDSpace,  kMETitleEditEHImpl,				kSemUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace,  kMETitlePopupMenuActionImpl,		kSemUIPrefix + 62)

DECLARE_PMID(kImplementationIDSpace,  kMECursorOptionsPrefImpl,			kSemUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace,  kSetMECursorOptionsPrefCmdImpl,		kSemUIPrefix + 64)

//Reverse Layout
DECLARE_PMID (kImplementationIDSpace, kButtonIconInfoWidgetObserver, kSemUIPrefix + 65)
DECLARE_PMID (kImplementationIDSpace, kInvertR2LMenuComponentImpl, kSemUIPrefix + 66)
DECLARE_PMID (kImplementationIDSpace, kInvertR2LControllerImpl, kSemUIPrefix + 67)
DECLARE_PMID (kImplementationIDSpace, kInvertR2LObserverImpl, kSemUIPrefix + 68)
DECLARE_PMID (kImplementationIDSpace, kObjectOptionsR2LOnObserverImpl, kSemUIPrefix + 69)
DECLARE_PMID (kImplementationIDSpace, kGraphicOptionsR2LOnObserverImpl, kSemUIPrefix + 70)
DECLARE_PMID (kImplementationIDSpace, kGradientOptionsR2LOnObserverImpl, kSemUIPrefix + 71)
DECLARE_PMID (kImplementationIDSpace, kStoriesOptionsR2LOnObserverImpl, kSemUIPrefix + 72)

#ifdef qME_CS3
//----------------------------------------------------------------------------------------
// <Interface ID>
//----------------------------------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLMEFRAME, kSemUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEFRAME, kSemUIPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITABRULERDATAME, kSemUIPrefix + 3)
#endif	//qME_CS3
DECLARE_PMID(kInterfaceIDSpace, IID_IMESYMETRIZE, kSemUIPrefix + 4)
//gap

// Tables R2L
DECLARE_PMID(kInterfaceIDSpace, IID_IDIRINTDATA, kSemUIPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IMECURSOROPTIONSPREF, kSemUIPrefix + 11)

//----------------------------------------------------------------------------------------
// Widget IDs
//----------------------------------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kSemUIWidgetId, kSemUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kDiacPosWidgetId, kSemUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kDiacPosDropDownWidgetId, kSemUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kDirOverrideWidgetId, kSemUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kDirOverrideDropDownWidgetId, kSemUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kDigitsWidgetId, kSemUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kDigitsDropDownWidgetId, kSemUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kKashidaWidgetId, kSemUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kKashidaDropDownWidgetId, kSemUIPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kSemUIDialogHookWidgetId, kSemUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kDiacPosGroupWidgetId, kSemUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kDiacPosGroupPopupWidgetId, kSemUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kOTOverlapswashWidgetID, kSemUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kOTStylisticAlternatesWidgetID, kSemUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kOTJustificationAlternatesWidgetID, kSemUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kOTStretchAlternatesWidgetID, kSemUIPrefix + 16)
//gap
//gap
//gap
DECLARE_PMID(kWidgetIDSpace, kTOPMEToolWidgetid, kSemUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kMEToolWidgetId, kSemUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kDiacOffsetPanelWidgetID, kSemUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kDiacXOffsetLabelWidgetID, kSemUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kDiacXOffsetEditWidgetID, kSemUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kDiacXOffsetNudgeWidgetID, kSemUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kDiacYOffsetLabelWidgetID, kSemUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kDiacYOffsetEditWidgetID, kSemUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kDiacYOffsetNudgeWidgetID, kSemUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kDiacOffsetTitleWidgetID, kSemUIPrefix + 39)

// Tables R2L
DECLARE_PMID(kWidgetIDSpace, kTableDirGroupWidgetID, kSemUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kTableDirBorderWidgetID, kSemUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kDirStaticTextWidgetID, kSemUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kTablesDirDropdownWidgetID, kSemUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kTableSetUpDirGroupWidgetID, kSemUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kTableSetUpDirBorderWidgetID, kSemUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kTableDirStaticTextWidgetID, kSemUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kTableSetUpDirDropdownWidgetID, kSemUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kDirectionSelectGroupWidgetID, kSemUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kIconTableLTRDirWidgetId, kSemUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kIconTableRTLDirWidgetId, kSemUIPrefix + 38)
//gap

//Eye Dropper
DECLARE_PMID(kWidgetIDSpace, kMEEyeDirOverrideWidgetId, kSemUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kMEEyeKeyboardDirWidgetId, kSemUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kMEEyeDigitsWidgetId, kSemUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kMEEyeKashidaWidgetId, kSemUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kMEEyeDiacVPosWidgetId, kSemUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kMEEyeDiacOffsetWidgetId, kSemUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kMEEyeOpenTypeWidgetId, kSemUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kMEEyeParagraphDirWidgetId, kSemUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kMEEyeJustifMethodWidgetId, kSemUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kMEEyeKashidaWidthWidgetId, kSemUIPrefix + 49)

//gap
DECLARE_PMID(kWidgetIDSpace, kMEPrefsCheckBoxWidgetID,		kSemUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kMEInputOptionPrefsDialogWidgetID,		kSemUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kMEWarningIconWidgetID,		kSemUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kMEWarningDescWidgetID,		kSemUIPrefix + 65)

//gap

DECLARE_PMID(kWidgetIDSpace, kBNRightIndentLabelWidgetId, kSemUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kBNRightIndentEBWidgetId, kSemUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kBNRightIndentNudgeWidgetId, kSemUIPrefix + 71)

DECLARE_PMID(kWidgetIDSpace, kObjStylesMEGenericWidgetID, kSemUIPrefix + 72)

DECLARE_PMID(kWidgetIDSpace, kMovingOrderStaticWidgetID, kSemUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kMovingOrderDropdownWidgetID, kSemUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kCursorControlGroupWidgetID, kSemUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kCursorControlLabelWidgetID, kSemUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kNeutralCharGroupWidgetID, kSemUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kNeutralCharLabelWidgetID, kSemUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kCursorWritingDirCheckBoxWidgetId, kSemUIPrefix + 79)

//DocSetup (binding)
DECLARE_PMID(kWidgetIDSpace,  kSemBindingLabelWidgetID,        kSemUIPrefix + 80) 
DECLARE_PMID(kWidgetIDSpace,  kDocOrientationHiliteBorderWidgetID,        kSemUIPrefix + 81) 
// Should be only for InvertRTL
DECLARE_PMID(kWidgetIDSpace,  kIRTLTitleClusterWidgetId,        kSemUIPrefix + 82) 
DECLARE_PMID(kWidgetIDSpace,  kIRTLPageBindingLeftToRightIconWidgetID,        kSemUIPrefix + 83) 
DECLARE_PMID(kWidgetIDSpace,  kIRTLPageBindingRightToLeftIconWidgetID,        kSemUIPrefix + 84)

// For DontShowAgain warning alerts 
DECLARE_PMID(kWidgetIDSpace,  kApplyMEComposerWidgetID,        kSemUIPrefix + 85)

//Reverse Layout
DECLARE_PMID (kWidgetIDSpace, kInvertR2LWidgetID, kSemUIPrefix + 86)
DECLARE_PMID (kWidgetIDSpace, kPagesGroupWidgetId, kSemUIPrefix + 87)
DECLARE_PMID (kWidgetIDSpace, kPagesGroupWidgetTextID, kSemUIPrefix + 88)
DECLARE_PMID (kWidgetIDSpace, kObjectsOptionsGroupWidgetId, kSemUIPrefix + 89)
//gap
//Reverse Layout-Objects Options
DECLARE_PMID (kWidgetIDSpace, kObjectOptionsOnWidget, kSemUIPrefix + 91)
DECLARE_PMID (kWidgetIDSpace, kFlipTextFramesWidget, kSemUIPrefix + 92)
DECLARE_PMID (kWidgetIDSpace, kFlipGraphicFramesWidget, kSemUIPrefix + 93)
DECLARE_PMID (kWidgetIDSpace, kFlipPathWidget, kSemUIPrefix + 94)
DECLARE_PMID (kWidgetIDSpace, kGraphicOptionsGroupWidgetId, kSemUIPrefix + 95)
//gap
//Reverse Layout-Flip Options
DECLARE_PMID (kWidgetIDSpace, kGraphicOptionsOnWidget, kSemUIPrefix + 97)
DECLARE_PMID (kWidgetIDSpace, kDeleteGraphicWidget, kSemUIPrefix + 98)
DECLARE_PMID (kWidgetIDSpace, kFlipGraphicWidget, kSemUIPrefix + 99)
//Reverse Layout-Pages Options
DECLARE_PMID (kWidgetIDSpace, kRangeWidgetId, kSemUIPrefix + 100)
DECLARE_PMID (kWidgetIDSpace, kAllPagesButtonWidgetId, kSemUIPrefix + 101)
DECLARE_PMID (kWidgetIDSpace, kRangesButtonWidgetId, kSemUIPrefix + 102)
DECLARE_PMID (kWidgetIDSpace, kCurrentButtonWidgetId, kSemUIPrefix + 103)
DECLARE_PMID (kWidgetIDSpace, kPMRangesEditBoxWidgetId, kSemUIPrefix + 104)
DECLARE_PMID (kWidgetIDSpace, kInvertMaster2TextWidgetId, kSemUIPrefix + 105)
DECLARE_PMID (kWidgetIDSpace, kInvertMasterPopupWidgetID, kSemUIPrefix + 106)
DECLARE_PMID (kWidgetIDSpace, kFlipObjectAngleWidget, kSemUIPrefix + 107)
DECLARE_PMID (kWidgetIDSpace, kFlipGradientAngleWidget, kSemUIPrefix + 108)
DECLARE_PMID (kWidgetIDSpace, kStoriesOptionsGroupWidgetId, kSemUIPrefix + 109)
//gap
DECLARE_PMID (kWidgetIDSpace, kStoriesOptionsOnWidget, kSemUIPrefix + 111)
DECLARE_PMID (kWidgetIDSpace, kDeleteStoriesWidget, kSemUIPrefix + 112)
DECLARE_PMID (kWidgetIDSpace, kReverseStoriesWidget, kSemUIPrefix + 113)
DECLARE_PMID (kWidgetIDSpace, kBindingOptionsGroupWidgetId, kSemUIPrefix + 114)
DECLARE_PMID (kWidgetIDSpace, kBindingOptionsGroupWidgetTextID, kSemUIPrefix + 115)
DECLARE_PMID (kWidgetIDSpace, kChangeTableDirWidget, kSemUIPrefix + 117)

//---------------------------------------------------------------
// <Action ID>
//---------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kSemDigitsActionID,	kSemUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kSemKashidaActionID,		kSemUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kSemDefaultDirActionID, kSemUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kSemLTRDirActionID, kSemUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kSemRTLDirActionID, kSemUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kSemPopupSepActionID, kSemUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kSemInsertLTRMarkActionID, kSemUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kSemInsertRTLMarkActionID, kSemUIPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kSemInsertZWNonJoinerActionID, kSemUIPrefix + 9)	//Not needed - Already managed by US
DECLARE_PMID(kActionIDSpace, kSemInsertZWJoinerActionID, kSemUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kSemInsertGereshActionID, kSemUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kSemInsertGershayimActionID, kSemUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kSemInsertMaqafActionID, kSemUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kSemInsertKashidaActionID, kSemUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kMEToolActionID, kSemUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kTOPMEToolActionID, kSemUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kDiacOffsetActionID,   kSemUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kSemInsertR2LDashActionID,		kSemUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kSemInsertL2RDashActionID,		kSemUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kSemDefaultDigitsActionID,	kSemUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kSemArabicDigitsActionID, kSemUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kSemHindiDigitsActionID, kSemUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kSemFarsiDigitsActionID, kSemUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kSemNativeDigitsActionID, kSemUIPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kSemInsertNarrowHardSpaceActionID, kSemUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kSemOTFOverlapActionID, kSemUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kSemOTFStylisticAlternatesActionID, kSemUIPrefix + 26)
DECLARE_PMID(kActionIDSpace, kSemOTFJustificationAlternatesActionID, kSemUIPrefix + 27)
DECLARE_PMID(kActionIDSpace, kSemOTFStretchAlternatesActionID, kSemUIPrefix + 28)
//gap
DECLARE_PMID(kActionIDSpace, kSem2DefaultKbdDirActionID, kSemUIPrefix + 30)
DECLARE_PMID(kActionIDSpace, kSem2LTRKbdDirActionID,	 kSemUIPrefix + 31)
DECLARE_PMID(kActionIDSpace, kSem2RTLKbdDirActionID,	 kSemUIPrefix + 32)
DECLARE_PMID(kActionIDSpace, kSem2PopupSepActionID,		 kSemUIPrefix + 33)
DECLARE_PMID(kActionIDSpace, kSem2RightToLeftPrefsActionID,		 kSemUIPrefix + 34)
//gap

//TitleLang
DECLARE_PMID(kActionIDSpace, kSemUIBulgarianActionID,            kSemUIPrefix + 36)
DECLARE_PMID(kActionIDSpace, kSemUIByeloRussianActionID,        kSemUIPrefix + 37)
DECLARE_PMID(kActionIDSpace, kSemUICroatianActionID,            kSemUIPrefix + 38)
DECLARE_PMID(kActionIDSpace, kSemUICzechActionID,                kSemUIPrefix + 39)
DECLARE_PMID(kActionIDSpace, kSemUIEnglishActionID,            kSemUIPrefix + 40)
DECLARE_PMID(kActionIDSpace, kSemUIEstonianActionID,            kSemUIPrefix + 41)
DECLARE_PMID(kActionIDSpace, kSemUIGreekActionID,                kSemUIPrefix + 42)
DECLARE_PMID(kActionIDSpace, kSemUIHungarianActionID,            kSemUIPrefix + 43)
DECLARE_PMID(kActionIDSpace, kSemUILatvianActionID,            kSemUIPrefix + 44)
DECLARE_PMID(kActionIDSpace, kSemUILithuanianActionID,        kSemUIPrefix + 45)
DECLARE_PMID(kActionIDSpace, kSemUIPolishActionID,            kSemUIPrefix + 46)
DECLARE_PMID(kActionIDSpace, kSemUIRomanianActionID,            kSemUIPrefix + 47)
DECLARE_PMID(kActionIDSpace, kSemUIRussianActionID,            kSemUIPrefix + 48)
DECLARE_PMID(kActionIDSpace, kSemUISlovakActionID,            kSemUIPrefix + 49)
DECLARE_PMID(kActionIDSpace, kSemUISlovenianActionID,            kSemUIPrefix + 50)
DECLARE_PMID(kActionIDSpace, kSemUITurkishActionID,            kSemUIPrefix + 51)
DECLARE_PMID(kActionIDSpace, kSemUIUkrainianActionID,            kSemUIPrefix + 52)
DECLARE_PMID(kActionIDSpace, kSemUIArabicActionID,            kSemUIPrefix + 53)
DECLARE_PMID(kActionIDSpace, kSemUIHebrewActionID,            kSemUIPrefix + 54)
DECLARE_PMID(kActionIDSpace, kSemUIFrenchActionID,            kSemUIPrefix + 55)
//gap
DECLARE_PMID(kActionIDSpace, kSemUIArabicSeparatorActionID,            kSemUIPrefix + 60)
DECLARE_PMID(kActionIDSpace, kSemUIHebrewSeparatorActionID,            kSemUIPrefix + 61)
DECLARE_PMID(kActionIDSpace, kSemUIDashSeparatorActionID,            kSemUIPrefix + 62)

//Type Menu- Composer
DECLARE_PMID(kActionIDSpace, kSemUIApplyMEComposerActionID,            kSemUIPrefix + 63)
DECLARE_PMID(kActionIDSpace, kSemUIApplyMEComposerSepActionID,            kSemUIPrefix + 64)


//Reverse Layout
DECLARE_PMID(kActionIDSpace, kInvertR2LUIActionID, kSemUIPrefix + 65)

//Unicode markers
DECLARE_PMID(kActionIDSpace, kSemInsertLREMarkActionID, kSemUIPrefix + 66)
DECLARE_PMID(kActionIDSpace, kSemInsertRLEMarkActionID, kSemUIPrefix + 67)
DECLARE_PMID(kActionIDSpace, kSemInsertPDFMarkActionID, kSemUIPrefix + 68)
DECLARE_PMID(kActionIDSpace, kSemInsertLROMarkActionID, kSemUIPrefix + 69)
DECLARE_PMID(kActionIDSpace, kSemInsertRLOMarkActionID, kSemUIPrefix + 70)
DECLARE_PMID(kActionIDSpace, kSemInsertDottedCircleActionID, kSemUIPrefix + 71)
DECLARE_PMID(kActionIDSpace, kSemUIDottedCircleSeparatorActionID,            kSemUIPrefix + 72)

//Sof Pasuk
DECLARE_PMID(kActionIDSpace, kSemInsertSofPasukActionID,            kSemUIPrefix + 73)

#define kTypographyKeyboardDirActionArea    "KBSCE Typography:Keyboard Direction"
#define kTypeMenuInsertSpecialCharacterMEActionArea    "KBSCE Type menu:Insert Special ME Character"
#define kTypographyOpenTypeActionArea    "KBSCE Typography:OpenType variants"
#define kTypographyDigitsActionArea    "KBSCE Typography:Digits"
#define kTypographyDirOverrideActionArea    "KBSCE Typography:Character Direction"
#define kTypographyParaDirActionArea    "KBSCE Typography:Paragraph Direction"

#endif // __SemUIID__

