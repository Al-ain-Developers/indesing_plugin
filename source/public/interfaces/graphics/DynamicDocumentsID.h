//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/DynamicDocumentsID.h $
//  
//  Owner: Greg St. Pierre
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

#ifndef DynamicDocuments_ID_h__
#define DynamicDocuments_ID_h__

#pragma once

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kDynamicDocumentsPrefix			RezLong(0x20500)

#define kDynamicDocumentsPluginName		"DynamicDocuments"
DECLARE_PMID(kPlugInIDSpace,			kDynamicDocumentsPluginID,				kDynamicDocumentsPrefix + 1)

// <Start IDC>

// <Class ID>
// Class IDs
DECLARE_PMID(kClassIDSpace,				kDynDocsExportViewPortBoss,				kDynamicDocumentsPrefix + 1)
DECLARE_PMID(kClassIDSpace,				kDynDocsExportProviderBoss,				kDynamicDocumentsPrefix + 2)
DECLARE_PMID(kClassIDSpace,				kDynDocsErrorStringServiceBoss,			kDynamicDocumentsPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace,				kSetPageTransitionCmdBoss,				kDynamicDocumentsPrefix + 5)
DECLARE_PMID(kClassIDSpace,				kPageTransitionScriptProviderBoss,		kDynamicDocumentsPrefix + 6)
//gap
DECLARE_PMID(kClassIDSpace,				kDynamicDocumentsConversionProviderBoss, kDynamicDocumentsPrefix + 12)
DECLARE_PMID(kClassIDSpace,				kDynamicDocumentsTemporaryStreamBoss,	kDynamicDocumentsPrefix + 13)
//gap
DECLARE_PMID(kClassIDSpace,				kSelectionDrawEventHandlerBoss,			kDynamicDocumentsPrefix + 15)
DECLARE_PMID(kClassIDSpace,				kDynamicDocumentsDrawEventHandlerBoss,	kDynamicDocumentsPrefix + 16)
DECLARE_PMID(kClassIDSpace,				kDynamicDocumentsTextXPAdornmentClassID,kDynamicDocumentsPrefix + 17)
DECLARE_PMID(kClassIDSpace,				kSetHTMLPreviewPrefsCmdBoss,			kDynamicDocumentsPrefix + 18)
//DECLARE_PMID(kClassIDSpace,				kPixelBenderAdornmentBoss,			kDynamicDocumentsPrefix + 19)
DECLARE_PMID(kClassIDSpace,				kApplyPixelBenderCommandBoss,			kDynamicDocumentsPrefix + 20)
DECLARE_PMID(kClassIDSpace,				kApplyPixelBenderParamsCommandBoss,		kDynamicDocumentsPrefix + 21)
DECLARE_PMID(kClassIDSpace,				kMotionStartupServiceBoss,				kDynamicDocumentsPrefix + 22)
DECLARE_PMID(kClassIDSpace,				kMotionPresetBoss,						kDynamicDocumentsPrefix + 23)
DECLARE_PMID(kClassIDSpace,				kApplyMotionToPageItemCmdBoss,			kDynamicDocumentsPrefix + 24)
DECLARE_PMID(kClassIDSpace,				kMotionPresetAdornmentBoss,				kDynamicDocumentsPrefix + 25)
DECLARE_PMID(kClassIDSpace,				kAnimationObjectBoss,					kDynamicDocumentsPrefix + 26)
DECLARE_PMID(kClassIDSpace,				kLoadMotionPresetFilesCmdBoss,			kDynamicDocumentsPrefix + 27)
DECLARE_PMID(kClassIDSpace,				kNewMotionPresetCmdBoss,				kDynamicDocumentsPrefix + 28)
DECLARE_PMID(kClassIDSpace,				kUpdateMotionPresetCmdBoss,				kDynamicDocumentsPrefix + 29)
DECLARE_PMID(kClassIDSpace,				kRemoveMotionPresetCmdBoss,				kDynamicDocumentsPrefix + 30)
//gap
//DECLARE_PMID(kClassIDSpace,				AVAILABLE,							kDynamicDocumentsPrefix + 32)
//gap
DECLARE_PMID(kClassIDSpace,				kMotionPresetScriptProviderBoss,		kDynamicDocumentsPrefix + 34)
//gap

DECLARE_PMID(kClassIDSpace,				kAnimationCoreDrawEventHandlerBoss,		kDynamicDocumentsPrefix + 41)
DECLARE_PMID(kClassIDSpace,				kMotionPresetAdornmentHandleShapeBoss,	kDynamicDocumentsPrefix + 42)
DECLARE_PMID(kClassIDSpace,				kAnimationDataScriptBoss,				kDynamicDocumentsPrefix + 43)
DECLARE_PMID(kClassIDSpace,				kAnimationSettingsScriptProviderBoss,	kDynamicDocumentsPrefix + 44)
DECLARE_PMID(kClassIDSpace,				kAnimationDataScriptProviderBoss,		kDynamicDocumentsPrefix + 45)
DECLARE_PMID(kClassIDSpace,				kUpdateAnimationCmdBoss,				kDynamicDocumentsPrefix + 46)
DECLARE_PMID(kClassIDSpace,				kAddAnimationCmdBoss,					kDynamicDocumentsPrefix + 47)
DECLARE_PMID(kClassIDSpace,				kRemoveAnimationCmdBoss,				kDynamicDocumentsPrefix + 48)
DECLARE_PMID(kClassIDSpace,				kSpreadDynContentM2MListnerServiceBoss,	kDynamicDocumentsPrefix + 49)
DECLARE_PMID(kClassIDSpace,				kAddItemsToDynamicEventCmdBoss,			kDynamicDocumentsPrefix + 50)
DECLARE_PMID(kClassIDSpace,				kRemoveItemsFromDynamicEventCmdBoss,	kDynamicDocumentsPrefix + 51)
DECLARE_PMID(kClassIDSpace,				kMoveItemForDynamicEventCmdBoss,		kDynamicDocumentsPrefix + 52)
DECLARE_PMID(kClassIDSpace,				kSetItemDelayForDynamicEventCmdBoss,	kDynamicDocumentsPrefix + 53)
DECLARE_PMID(kClassIDSpace,				kCreateDynamicEventCmdBoss,				kDynamicDocumentsPrefix + 54)
DECLARE_PMID(kClassIDSpace,				kRemoveDynamicEventCmdBoss,				kDynamicDocumentsPrefix + 55)
DECLARE_PMID(kClassIDSpace,				kReplaceItemInDynamicEventCmdBoss,		kDynamicDocumentsPrefix + 56)

DECLARE_PMID(kClassIDSpace,				kDynamicEventTimingM2MListnerServiceBoss,	kDynamicDocumentsPrefix + 57)
DECLARE_PMID(kClassIDSpace,				kDETimingListScriptBoss,				kDynamicDocumentsPrefix + 58)
DECLARE_PMID(kClassIDSpace,				kDETimingDataScriptBoss,				kDynamicDocumentsPrefix + 59)
DECLARE_PMID(kClassIDSpace,				kDETimingTargetItemScriptBoss,			kDynamicDocumentsPrefix + 60)
DECLARE_PMID(kClassIDSpace,				kDETimingSettingsScriptProviderBoss,	kDynamicDocumentsPrefix + 61)
DECLARE_PMID(kClassIDSpace,				kDETimingListScriptProviderBoss,		kDynamicDocumentsPrefix + 62)
DECLARE_PMID(kClassIDSpace,				kDETimingDataScriptProviderBoss,		kDynamicDocumentsPrefix + 63)
DECLARE_PMID(kClassIDSpace,				kDETimingTargetItemScriptProviderBoss,	kDynamicDocumentsPrefix + 64)
DECLARE_PMID(kClassIDSpace,				kSpreadAndTimingPhase2ConverterBoss,		kDynamicDocumentsPrefix + 65)
DECLARE_PMID(kClassIDSpace,				kPrivateAddItemsToDynamicEventINXCmdBoss,kDynamicDocumentsPrefix + 66)
DECLARE_PMID(kClassIDSpace,				kSpreadTimingM2MListnerServiceBoss,		kDynamicDocumentsPrefix + 67)
DECLARE_PMID(kClassIDSpace,				kMotionPresetRefConverterBoss,			kDynamicDocumentsPrefix + 68)
DECLARE_PMID(kClassIDSpace,				kMotionPresetRIDXNotifierHandlerBoss,	kDynamicDocumentsPrefix + 69)
DECLARE_PMID(kClassIDSpace,				kAnimationDataCodeConverterBoss,		kDynamicDocumentsPrefix + 70)
DECLARE_PMID(kClassIDSpace,				kLayerPreservationDrawEventHandlerBoss,	kDynamicDocumentsPrefix + 71)
DECLARE_PMID(kClassIDSpace,				kAnimationMotionPathPreventAllAttrBoss,	kDynamicDocumentsPrefix + 72)
DECLARE_PMID(kClassIDSpace,				kInvalAnimationProxyCmdBoss,			kDynamicDocumentsPrefix + 73)
DECLARE_PMID(kClassIDSpace,				kMotionPathItemProxyAdornmentBoss,		kDynamicDocumentsPrefix + 74)
DECLARE_PMID(kClassIDSpace,				kSetGroupDataForDynamicEventCmdBoss,	kDynamicDocumentsPrefix + 75)
DECLARE_PMID(kClassIDSpace,				kPrivateSetAnimationHasCustomINXCmdBoss,kDynamicDocumentsPrefix + 76)
DECLARE_PMID(kClassIDSpace,				k360ViewerOverlayDataBoss_Obsolete,		kDynamicDocumentsPrefix + 77)
DECLARE_PMID(kClassIDSpace,				kRemoveOverlayDataCodeConverterBoss,	kDynamicDocumentsPrefix + 78)
DECLARE_PMID(kClassIDSpace,				kPageTransitionsConverterBoss,			kDynamicDocumentsPrefix + 79)
DECLARE_PMID(kClassIDSpace,				kInteractiveOverlayDataBoss_Obsolete,	kDynamicDocumentsPrefix + 80)
DECLARE_PMID(kClassIDSpace,				kPanoramaOverlayDataBoss_Obsolete,		kDynamicDocumentsPrefix + 81)
DECLARE_PMID(kClassIDSpace,				kImagePanOverlayDataBoss_Obsolete,		kDynamicDocumentsPrefix + 82)
DECLARE_PMID(kClassIDSpace,				kWebViewOverlayDataBoss_Obsolete,		kDynamicDocumentsPrefix + 83)
//gap
DECLARE_PMID(kClassIDSpace,				kInteractiveOverlayAdornmentBoss_Obsolete,kDynamicDocumentsPrefix + 96)

// NOTE: big gap (+ 200) for the builtin page transitions
DECLARE_PMID(kClassIDSpace,				kBlindsPageTransitionBoss,				kDynamicDocumentsPrefix + 200)
DECLARE_PMID(kClassIDSpace,				kBoxPageTransitionBoss,					kDynamicDocumentsPrefix + 201)
DECLARE_PMID(kClassIDSpace,				kCombPageTransitionBoss,				kDynamicDocumentsPrefix + 202)
DECLARE_PMID(kClassIDSpace,				kCoverPageTransitionBoss,				kDynamicDocumentsPrefix + 203)
DECLARE_PMID(kClassIDSpace,				kDissolvePageTransitionBoss,			kDynamicDocumentsPrefix + 204)
DECLARE_PMID(kClassIDSpace,				kFadePageTransitionBoss,				kDynamicDocumentsPrefix + 205)
DECLARE_PMID(kClassIDSpace,				kPageTurnPageTransitionBoss,			kDynamicDocumentsPrefix + 206)
DECLARE_PMID(kClassIDSpace,				kPushPageTransitionBoss,				kDynamicDocumentsPrefix + 207)
DECLARE_PMID(kClassIDSpace,				kSplitPageTransitionBoss,				kDynamicDocumentsPrefix + 208)
DECLARE_PMID(kClassIDSpace,				kUncoverPageTransitionBoss,				kDynamicDocumentsPrefix + 209)
DECLARE_PMID(kClassIDSpace,				kWipePageTransitionBoss,				kDynamicDocumentsPrefix + 210)
DECLARE_PMID(kClassIDSpace,				kZoomInPageTransitionBoss,				kDynamicDocumentsPrefix + 211)
DECLARE_PMID(kClassIDSpace,				kZoomOutPageTransitionBoss,				kDynamicDocumentsPrefix + 212)
DECLARE_PMID(kClassIDSpace,				kMotionSettingsMigrationServiceProviderBoss,				kDynamicDocumentsPrefix + 213)

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNDOCSUTILS,						kDynamicDocumentsPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICDOCUMENTSCONTEXT,			kDynamicDocumentsPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,			IID_IAGMPORTSTACK,						kDynamicDocumentsPrefix + 3)
//gap
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICDOCUMENTSDEBUGPREFS,		kDynamicDocumentsPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNDOCSEXPORTCOMMANDDATA,			kDynamicDocumentsPrefix + 6)

DECLARE_PMID(kInterfaceIDSpace,			IID_IPAGETRANSITION,					kDynamicDocumentsPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,			IID_IPAGETRANSITIONINFO,				kDynamicDocumentsPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace,			IID_IPAGETRANSITIONFACADE,				kDynamicDocumentsPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace,			IID_IPAGETRANSITIONLIST,				kDynamicDocumentsPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISETPAGETRANSITIONCMDDATA,			kDynamicDocumentsPrefix + 11)
//gap
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNDOCSPUBLICUTILS,				kDynamicDocumentsPrefix + 16)
//gap
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNDOCSTEMPSTREAMDATA,				kDynamicDocumentsPrefix + 20)
//gap
DECLARE_PMID(kInterfaceIDSpace,			IID_IHTMLPREVIEWPREFERENCES,			kDynamicDocumentsPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace,			IID_IPRIVATEANIMATIONFACADE,			kDynamicDocumentsPrefix + 23)

DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONCOREHOST,					kDynamicDocumentsPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONCORE,						kDynamicDocumentsPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMOTIONFRAMEHELPER,					kDynamicDocumentsPrefix + 26)
//gap
DECLARE_PMID(kInterfaceIDSpace,			IID_IMOTIONPRESETDATA,					kDynamicDocumentsPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace,			IID_IAPPLYMOTIONTOPAGEITEMCMDDATA,		kDynamicDocumentsPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMOTIONPRESETMANAGER,				kDynamicDocumentsPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMOTIONPRESETCMDDATA,				kDynamicDocumentsPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMOTIONPRESETUTILS,					kDynamicDocumentsPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMOTIONFACADE,						kDynamicDocumentsPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONATTRIBUTESUITE,			kDynamicDocumentsPrefix + 34)

DECLARE_PMID(kInterfaceIDSpace,			IID_IPIXELBENDERDATA,					kDynamicDocumentsPrefix + 35)

DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICDOCUMENTSPORT,				kDynamicDocumentsPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICDOCUMENTSPORTCONTEXTHANDLER,	kDynamicDocumentsPrefix + 37)
//gap
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICDOCUMENTSEXPORTCONTROLLER,	kDynamicDocumentsPrefix + 41)
//gap

DECLARE_PMID(kInterfaceIDSpace,			IID_IEXTERNALINTERFACEUTILS,			kDynamicDocumentsPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONCOREDATA,					kDynamicDocumentsPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONATTRIBUTEDATA,			kDynamicDocumentsPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONDATA,						kDynamicDocumentsPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONDATAPTRACCESS,			kDynamicDocumentsPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONCMDDATA,					kDynamicDocumentsPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONFACADE,					kDynamicDocumentsPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISPREADDYNAMICCONTENTMGR,			kDynamicDocumentsPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICEVENTTIMINGMGR,				kDynamicDocumentsPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace,			IID_IEVENTTRIGGERANDTIMINGCMDDATA,		kDynamicDocumentsPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICEVENTTIMINGFACADE,			kDynamicDocumentsPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICEVENTTIMINGSUITE,			kDynamicDocumentsPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace,			IID_ITIMINGMGRUIDDATA,					kDynamicDocumentsPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICEVENTTIMINGINXCONTEXTDATA,	kDynamicDocumentsPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICEVENTTIMING_DOCUMENT,		kDynamicDocumentsPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONUTILS,					kDynamicDocumentsPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace,			IID_IPRIVATEDYNAMICEVENTSTATEDATA,		kDynamicDocumentsPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICTARGETSFACADE,				kDynamicDocumentsPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICTARGETSCRIPTDATA,			kDynamicDocumentsPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace,			IID_IPRIVATEDYNAMICEVENTTIMINGUTILS,	kDynamicDocumentsPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace,			IID_IAPPMOTIONPRESETRESUMEOBSERVER,		kDynamicDocumentsPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace,			IID_IANIMATIONADORNMENTDRAWER,			kDynamicDocumentsPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace,			IID_IDYNAMICEVENTTIMINGINVALIDATEMESSAGE,kDynamicDocumentsPrefix + 68)

DECLARE_PMID(kInterfaceIDSpace,			IID_IMOTIONTESTUTILS,					kDynamicDocumentsPrefix + 255)

// <Implementation ID>
// Implementation IDs
//gap
DECLARE_PMID(kImplementationIDSpace,	kDynDocsUtilsImpl,						kDynamicDocumentsPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,	kDynDocsViewPortAttributesImpl,			kDynamicDocumentsPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kDynamicDocumentsContextImpl,			kDynamicDocumentsPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kDynDocsAGMPortStackImpl,				kDynamicDocumentsPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,	kSWFExportPreferencesImpl,				kDynamicDocumentsPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,	kDynamicDocumentsDebugPrefsImpl,		kDynamicDocumentsPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,	kDynDocsErrorStringServiceImpl,			kDynamicDocumentsPrefix + 8)
DECLARE_PMID(kImplementationIDSpace,	kDynamicDocumentsExportCommandImpl,		kDynamicDocumentsPrefix + 9)
DECLARE_PMID(kImplementationIDSpace,	kDynamicDocumentsExportCommandDataImpl,	kDynamicDocumentsPrefix + 10)

DECLARE_PMID(kImplementationIDSpace,	kPageTransitionImpl,					kDynamicDocumentsPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionInfoImpl,				kDynamicDocumentsPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionFacadeImpl,				kDynamicDocumentsPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionListImpl,				kDynamicDocumentsPrefix + 14)
DECLARE_PMID(kImplementationIDSpace,	kSetPageTransitionCmdImpl,				kDynamicDocumentsPrefix + 15)
DECLARE_PMID(kImplementationIDSpace,	kSetPageTransitionCmdDataImpl,			kDynamicDocumentsPrefix + 16)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionScriptProviderImpl,		kDynamicDocumentsPrefix + 17)
DECLARE_PMID(kImplementationIDSpace,	kXFLExportPreferencesImpl,				kDynamicDocumentsPrefix + 18)
DECLARE_PMID(kImplementationIDSpace,	kDynDocsPublicUtilsImpl,				kDynamicDocumentsPrefix + 25)
//gap
DECLARE_PMID(kImplementationIDSpace,	kDynDocsTempStreamImpl,					kDynamicDocumentsPrefix + 31)
DECLARE_PMID(kImplementationIDSpace,	kDynDocsTempStreamDataImpl,				kDynamicDocumentsPrefix + 32)
DECLARE_PMID(kImplementationIDSpace,	kCheckFlashUnsupportedMediaProviderImpl,kDynamicDocumentsPrefix + 33)
DECLARE_PMID(kImplementationIDSpace,	kSelectionDrawEventHandlerImpl,			kDynamicDocumentsPrefix + 34)
DECLARE_PMID(kImplementationIDSpace,	kDynamicDocumentsDrawEventHandlerImpl,	kDynamicDocumentsPrefix + 35)
//gap
DECLARE_PMID(kImplementationIDSpace,	kHTMLPreviewPreferencesImpl,			kDynamicDocumentsPrefix + 39)
DECLARE_PMID(kImplementationIDSpace,	kSetHTMLPreviewPrefsCmdImpl,			kDynamicDocumentsPrefix + 40)
DECLARE_PMID(kImplementationIDSpace,	kApplyPixelBenderCommandImpl,			kDynamicDocumentsPrefix + 41)
DECLARE_PMID(kImplementationIDSpace,	kPixelBenderDataImpl,					kDynamicDocumentsPrefix + 42)
DECLARE_PMID(kImplementationIDSpace,	kApplyPixelBenderParamsCommandImpl,		kDynamicDocumentsPrefix + 43)
//DECLARE_PMID(kImplementationIDSpace,	kPixelBenderAdornmentImpl,				kDynamicDocumentsPrefix + 44)

DECLARE_PMID(kImplementationIDSpace,	kMotionStartupServiceImpl,				kDynamicDocumentsPrefix + 45)
DECLARE_PMID(kImplementationIDSpace,	kMotionStartupShutdownImpl,				kDynamicDocumentsPrefix + 46)
DECLARE_PMID(kImplementationIDSpace,	kAnimationCoreHostImpl,					kDynamicDocumentsPrefix + 47)
DECLARE_PMID(kImplementationIDSpace,	kPrivateAnimationFacadeImpl,			kDynamicDocumentsPrefix + 48)
DECLARE_PMID(kImplementationIDSpace,	kMotionTestUtilsImpl,					kDynamicDocumentsPrefix + 49)
DECLARE_PMID(kImplementationIDSpace,	kMotionPresetDataImpl,					kDynamicDocumentsPrefix + 50)
DECLARE_PMID(kImplementationIDSpace,	kApplyMotionToPageItemCmdImpl,			kDynamicDocumentsPrefix + 51)
DECLARE_PMID(kImplementationIDSpace,	kApplyMotionToPageItemCmdDataImpl,		kDynamicDocumentsPrefix + 52)
DECLARE_PMID(kImplementationIDSpace,	kMotionPresetAdornmentImpl,				kDynamicDocumentsPrefix + 53)
DECLARE_PMID(kImplementationIDSpace,	kAppMotionPresetMgrImpl,				kDynamicDocumentsPrefix + 54)
DECLARE_PMID(kImplementationIDSpace,	kLoadMotionPresetFilesCmdImpl,			kDynamicDocumentsPrefix + 55)
DECLARE_PMID(kImplementationIDSpace,	kNewMotionPresetCmdImpl,				kDynamicDocumentsPrefix + 56)
DECLARE_PMID(kImplementationIDSpace,	kUpdateMotionPresetCmdImpl,				kDynamicDocumentsPrefix + 57)
DECLARE_PMID(kImplementationIDSpace,	kRemoveMotionPresetCmdImpl,				kDynamicDocumentsPrefix + 58)
DECLARE_PMID(kImplementationIDSpace,	kImportMotionPresetCmdImpl,				kDynamicDocumentsPrefix + 59)
DECLARE_PMID(kImplementationIDSpace,	kExportMotionPresetCmdImpl,				kDynamicDocumentsPrefix + 60)
DECLARE_PMID(kImplementationIDSpace,	kMotionPresetCmdDataImpl,				kDynamicDocumentsPrefix + 61)
DECLARE_PMID(kImplementationIDSpace,	kDocMotionPresetMgrImpl,				kDynamicDocumentsPrefix + 62)
DECLARE_PMID(kImplementationIDSpace,	kMotionPresetLockInfoImpl,				kDynamicDocumentsPrefix + 63)
DECLARE_PMID(kImplementationIDSpace,	kMotionPresetUtilsImpl,					kDynamicDocumentsPrefix + 64)
DECLARE_PMID(kImplementationIDSpace,	kMotionFacadeImpl,						kDynamicDocumentsPrefix + 65)

DECLARE_PMID(kImplementationIDSpace,	kAnimationAttrSuiteASBImpl,				kDynamicDocumentsPrefix + 68)
DECLARE_PMID(kImplementationIDSpace,	kAnimationAttrSuiteDefaultCSBImpl,		kDynamicDocumentsPrefix + 69)
DECLARE_PMID(kImplementationIDSpace,	kAnimationAttrSuiteLayoutCSBImpl,		kDynamicDocumentsPrefix + 70)
DECLARE_PMID(kImplementationIDSpace,	kAnimationAttrSuiteASBSelectionExtImpl,	kDynamicDocumentsPrefix + 71)
DECLARE_PMID(kImplementationIDSpace,	kAnimationAttrSuiteDefaultSelectionExtImpl,	kDynamicDocumentsPrefix + 72)
DECLARE_PMID(kImplementationIDSpace,	kAnimationAttrSuiteLayoutSelectionExtImpl,	kDynamicDocumentsPrefix + 73)

DECLARE_PMID(kImplementationIDSpace,	kMotionPresetScriptImpl,				kDynamicDocumentsPrefix + 74)
DECLARE_PMID(kImplementationIDSpace,	kMotionPresetScriptProviderImpl,		kDynamicDocumentsPrefix + 75)
//gap

DECLARE_PMID(kImplementationIDSpace,	kExternalInterfaceUtilsImpl,			kDynamicDocumentsPrefix + 92)

DECLARE_PMID(kImplementationIDSpace,	kAnimationCoreDrawEventHandlerImpl,		kDynamicDocumentsPrefix + 93)

DECLARE_PMID(kImplementationIDSpace,	kMotionPresetAdornmentHandleShapeImpl,	kDynamicDocumentsPrefix + 94)
DECLARE_PMID(kImplementationIDSpace,	kAnimationAttributeDataImpl,			kDynamicDocumentsPrefix + 95)
DECLARE_PMID(kImplementationIDSpace,	kWhichAnimationDataImpl,				kDynamicDocumentsPrefix + 96)
DECLARE_PMID(kImplementationIDSpace,	kAnimationCoreObjectImpl,				kDynamicDocumentsPrefix + 97)
DECLARE_PMID(kImplementationIDSpace,	kAnimationCoreDataImpl,					kDynamicDocumentsPrefix + 98)
DECLARE_PMID(kImplementationIDSpace,	kAnimationDataScriptImpl,				kDynamicDocumentsPrefix + 99)
DECLARE_PMID(kImplementationIDSpace,	kAnimationDataScriptProviderImpl,		kDynamicDocumentsPrefix + 100)
DECLARE_PMID(kImplementationIDSpace,	kAnimationDataPtrAccessImpl,			kDynamicDocumentsPrefix + 101)
DECLARE_PMID(kImplementationIDSpace,	kAnimationSettingsScriptProviderImpl,	kDynamicDocumentsPrefix + 102)
DECLARE_PMID(kImplementationIDSpace,	kUpdateAnimationCmdImpl,				kDynamicDocumentsPrefix + 103)
DECLARE_PMID(kImplementationIDSpace,	kAddAnimationCmdImpl,					kDynamicDocumentsPrefix + 104)
DECLARE_PMID(kImplementationIDSpace,	kRemoveAnimationCmdImpl,				kDynamicDocumentsPrefix + 105)
DECLARE_PMID(kImplementationIDSpace,	kAnimationCmdDataImpl,					kDynamicDocumentsPrefix + 106)
DECLARE_PMID(kImplementationIDSpace,	kAnimationFacadeImpl,					kDynamicDocumentsPrefix + 107)
DECLARE_PMID(kImplementationIDSpace,	kSpreadDynamicContentMgrImpl,			kDynamicDocumentsPrefix + 108)
DECLARE_PMID(kImplementationIDSpace,	kDynamicEventTimingMgrImpl,				kDynamicDocumentsPrefix + 109)
DECLARE_PMID(kImplementationIDSpace,	kFormFieldDynamicEventTimingMgrImpl,	kDynamicDocumentsPrefix + 110)

DECLARE_PMID(kImplementationIDSpace,	kSpreadDynContentM2MListnerImpl,		kDynamicDocumentsPrefix + 111)
DECLARE_PMID(kImplementationIDSpace,	kAddItemsToDynamicEventCmdImpl,			kDynamicDocumentsPrefix + 112)
DECLARE_PMID(kImplementationIDSpace,	kRemoveItemsFromDynamicEventCmdImpl,	kDynamicDocumentsPrefix + 113)
DECLARE_PMID(kImplementationIDSpace,	kMoveItemForDynamicEventCmdImpl,		kDynamicDocumentsPrefix + 114)
DECLARE_PMID(kImplementationIDSpace,	kSetItemDelayForDynamicEventCmdImpl,	kDynamicDocumentsPrefix + 115)
DECLARE_PMID(kImplementationIDSpace,	kCreateDynamicEventCmdImpl,				kDynamicDocumentsPrefix + 116)
DECLARE_PMID(kImplementationIDSpace,	kRemoveDynamicEventCmdImpl,				kDynamicDocumentsPrefix + 117)
DECLARE_PMID(kImplementationIDSpace,	kDynamicEventAndTimingCmdDataImpl,		kDynamicDocumentsPrefix + 118)
DECLARE_PMID(kImplementationIDSpace,	kDynamicEventTimingFacadeImpl,			kDynamicDocumentsPrefix + 119)
DECLARE_PMID(kImplementationIDSpace,	kDynamicEventTimingM2MListnerImpl,		kDynamicDocumentsPrefix + 120)
DECLARE_PMID(kImplementationIDSpace,	kReplaceItemInDynamicEventCmdImpl,		kDynamicDocumentsPrefix + 121)

DECLARE_PMID(kImplementationIDSpace,	kDynamicEventTimingSuiteASBImpl,		kDynamicDocumentsPrefix + 122)
DECLARE_PMID(kImplementationIDSpace,	kDynamicEventTimingSuiteLayoutCSBImpl,	kDynamicDocumentsPrefix + 123)
DECLARE_PMID(kImplementationIDSpace,	kDynamicEventTimingSuiteLayoutSelectionExtImpl,	kDynamicDocumentsPrefix + 124)
DECLARE_PMID(kImplementationIDSpace,	kDynamicEventTimingSuiteDefaultCSBImpl,	kDynamicDocumentsPrefix + 125)
DECLARE_PMID(kImplementationIDSpace,	kDynamicEventTimingSuiteDefaultSelectionExtImpl,kDynamicDocumentsPrefix + 126)

DECLARE_PMID(kImplementationIDSpace,	kDETimingListScriptImpl,				kDynamicDocumentsPrefix + 127)
DECLARE_PMID(kImplementationIDSpace,	kDETimingDataScriptImpl,				kDynamicDocumentsPrefix + 128)
DECLARE_PMID(kImplementationIDSpace,	kDETimingTargetItemScriptImpl,			kDynamicDocumentsPrefix + 129)
DECLARE_PMID(kImplementationIDSpace,	kDETimingSettingsScriptProviderImpl,	kDynamicDocumentsPrefix + 130)
DECLARE_PMID(kImplementationIDSpace,	kDETimingListScriptProviderImpl,		kDynamicDocumentsPrefix + 131)
DECLARE_PMID(kImplementationIDSpace,	kDETimingDataScriptProviderImpl,		kDynamicDocumentsPrefix + 132)
DECLARE_PMID(kImplementationIDSpace,	kDETimingTargetItemScriptProviderImpl,	kDynamicDocumentsPrefix + 133)
DECLARE_PMID(kImplementationIDSpace,	kSpreadAndTimingPhase2ConverterImpl,	kDynamicDocumentsPrefix + 134)
DECLARE_PMID(kImplementationIDSpace,	kPrivateAddItemsToDynamicEventINXCmdImpl,kDynamicDocumentsPrefix + 135)
DECLARE_PMID(kImplementationIDSpace,	kSpreadTimingM2MListnerImpl,			kDynamicDocumentsPrefix + 136)
DECLARE_PMID(kImplementationIDSpace,	kAnimationUtilsImpl,					kDynamicDocumentsPrefix + 137)
DECLARE_PMID(kImplementationIDSpace,	kMotionPresetRefConverterImpl,			kDynamicDocumentsPrefix + 138)
DECLARE_PMID(kImplementationIDSpace,	kMotionPresetRIDXNotifierHandlerImpl,	kDynamicDocumentsPrefix + 139)
DECLARE_PMID(kImplementationIDSpace,	kSetGroupDataForDynamicEventCmdImpl,	kDynamicDocumentsPrefix + 140)
DECLARE_PMID(kImplementationIDSpace,	kDynamicTargetsFacadeImpl,				kDynamicDocumentsPrefix + 141)
DECLARE_PMID(kImplementationIDSpace,	kAnimationDataCodeConverterImpl,		kDynamicDocumentsPrefix + 142)
DECLARE_PMID(kImplementationIDSpace,	kDynamicTargetScriptDataImpl,			kDynamicDocumentsPrefix + 143)
DECLARE_PMID(kImplementationIDSpace,	kLayerPreservationDrawEventHandlerImpl,	kDynamicDocumentsPrefix + 144)
DECLARE_PMID(kImplementationIDSpace,	kDynamicEventTimingSuiteASBSelectionExtImpl,kDynamicDocumentsPrefix + 145)
DECLARE_PMID(kImplementationIDSpace,	kMSOStateDynamicEventTimingMgrImpl,		kDynamicDocumentsPrefix + 146)
DECLARE_PMID(kImplementationIDSpace,	kPrivateDynamicEventTimingUtilsImpl,	kDynamicDocumentsPrefix + 147)
DECLARE_PMID(kImplementationIDSpace,	kAppMotionPresetResumeObserverImpl,		kDynamicDocumentsPrefix + 148)
DECLARE_PMID(kImplementationIDSpace,	kInvalAnimationProxyCmdImpl,			kDynamicDocumentsPrefix + 149)
DECLARE_PMID(kImplementationIDSpace,	kMotionPathItemProxyAdornmentImpl,		kDynamicDocumentsPrefix + 150)
DECLARE_PMID(kImplementationIDSpace,	kTargetPrivateDynamicEventStateDataImpl,kDynamicDocumentsPrefix + 151)
DECLARE_PMID(kImplementationIDSpace,	kFormFieldPrivateDynamicEventStateDataImpl,kDynamicDocumentsPrefix + 152)
DECLARE_PMID(kImplementationIDSpace,	kMSOStatePrivateDynamicEventStateDataImpl,kDynamicDocumentsPrefix + 153)
DECLARE_PMID(kImplementationIDSpace,	kSpreadPrivateDynamicEventStateDataImpl,kDynamicDocumentsPrefix + 154)
DECLARE_PMID(kImplementationIDSpace,	kPrivateSetAnimationHasCustomINXCmdImpl,kDynamicDocumentsPrefix + 155)
//gap
DECLARE_PMID(kImplementationIDSpace,	kInteractiveOverlayUIDDataImpl_Obsolete,kDynamicDocumentsPrefix + 157)
//gap
DECLARE_PMID(kImplementationIDSpace,	k360ViewerOverlayDataImpl_Obsolete,		kDynamicDocumentsPrefix + 159)
DECLARE_PMID(kImplementationIDSpace,	kPanoramaOverlayDataImpl_Obsolete,		kDynamicDocumentsPrefix + 160)
DECLARE_PMID(kImplementationIDSpace,	kImagePanOverlayDataImpl_Obsolete,		kDynamicDocumentsPrefix + 161)
DECLARE_PMID(kImplementationIDSpace,	kWebViewOverlayDataImpl_Obsolete,		kDynamicDocumentsPrefix + 162)
DECLARE_PMID(kImplementationIDSpace,	kRemoveOverlayDataCodeConverterImpl,	kDynamicDocumentsPrefix + 163)
DECLARE_PMID(kImplementationIDSpace,	kPageTransitionsConverterImpl,			kDynamicDocumentsPrefix + 164)

// NOTE: big gap (+ 200) for the builtin page transitions
DECLARE_PMID(kImplementationIDSpace,	kBlindsPageTransitionImpl,				kDynamicDocumentsPrefix + 200)
DECLARE_PMID(kImplementationIDSpace,	kBoxPageTransitionImpl,					kDynamicDocumentsPrefix + 201)
DECLARE_PMID(kImplementationIDSpace,	kCombPageTransitionImpl,				kDynamicDocumentsPrefix + 202)
DECLARE_PMID(kImplementationIDSpace,	kCoverPageTransitionImpl,				kDynamicDocumentsPrefix + 203)
DECLARE_PMID(kImplementationIDSpace,	kDissolvePageTransitionImpl,			kDynamicDocumentsPrefix + 204)
DECLARE_PMID(kImplementationIDSpace,	kFadePageTransitionImpl,				kDynamicDocumentsPrefix + 205)
DECLARE_PMID(kImplementationIDSpace,	kPageTurnPageTransitionImpl,			kDynamicDocumentsPrefix + 206)
DECLARE_PMID(kImplementationIDSpace,	kPushPageTransitionImpl,				kDynamicDocumentsPrefix + 207)
DECLARE_PMID(kImplementationIDSpace,	kSplitPageTransitionImpl,				kDynamicDocumentsPrefix + 208)
DECLARE_PMID(kImplementationIDSpace,	kUncoverPageTransitionImpl,				kDynamicDocumentsPrefix + 209)
DECLARE_PMID(kImplementationIDSpace,	kWipePageTransitionImpl,				kDynamicDocumentsPrefix + 210)
DECLARE_PMID(kImplementationIDSpace,	kZoomInPageTransitionImpl,				kDynamicDocumentsPrefix + 211)
DECLARE_PMID(kImplementationIDSpace,	kZoomOutPageTransitionImpl,				kDynamicDocumentsPrefix + 212)
DECLARE_PMID(kImplementationIDSpace,	kMotionSettingsMigrationImpl,			kDynamicDocumentsPrefix + 213)

// <Error ID>
// Error IDs
DECLARE_PMID(kErrorIDSpace,				kDynDocs_ExportFailureError,			kDynamicDocumentsPrefix + 1)
DECLARE_PMID(kErrorIDSpace,				kDynDocs_FlatteningFailureError,		kDynamicDocumentsPrefix + 2)
DECLARE_PMID(kErrorIDSpace,				kDynDocs_OpenFileError,					kDynamicDocumentsPrefix + 3)
DECLARE_PMID(kErrorIDSpace,				kDynDocs_ImageConvertError,				kDynamicDocumentsPrefix + 7)
DECLARE_PMID(kErrorIDSpace,				kDynDocs_RasterizeError,				kDynamicDocumentsPrefix + 8)

DECLARE_PMID(kErrorIDSpace,				kPageTrans_CannotFindError,				kDynamicDocumentsPrefix + 9)
DECLARE_PMID(kErrorIDSpace,				kPageTrans_SettingError,				kDynamicDocumentsPrefix + 10)
DECLARE_PMID(kErrorIDSpace,				kPageTrans_BadDirectionError,			kDynamicDocumentsPrefix + 11)

DECLARE_PMID(kErrorIDSpace,				kMotion_OpenPresetFileError,			kDynamicDocumentsPrefix + 12)
DECLARE_PMID(kErrorIDSpace,				kMotion_BadPresetFileError,				kDynamicDocumentsPrefix + 13)
DECLARE_PMID(kErrorIDSpace,				kMotion_MotionXMLError,					kDynamicDocumentsPrefix + 14)
DECLARE_PMID(kErrorIDSpace,				kMotion_BadPresetDescriptionError,		kDynamicDocumentsPrefix + 15)
DECLARE_PMID(kErrorIDSpace,				kMotion_CannotDeleteLockedPresetError,	kDynamicDocumentsPrefix + 16)
DECLARE_PMID(kErrorIDSpace,				kMotion_CannotEditDefaultPresetError,	kDynamicDocumentsPrefix + 17)
DECLARE_PMID(kErrorIDSpace,				kMotion_RenameDefaultPresetError,		kDynamicDocumentsPrefix + 18)
DECLARE_PMID(kErrorIDSpace,				kMotion_PresetNameEmptyError,			kDynamicDocumentsPrefix + 19)
DECLARE_PMID(kErrorIDSpace,				kMotion_PresetNameAlreadyExistsError,	kDynamicDocumentsPrefix + 20)
DECLARE_PMID(kErrorIDSpace,				kMotion_PresetNameInvalidError,			kDynamicDocumentsPrefix + 21)
DECLARE_PMID(kErrorIDSpace,				kMotion_CannotEditPresetError,			kDynamicDocumentsPrefix + 22)
DECLARE_PMID(kErrorIDSpace,				kMotion_PresetExistsReplaceError,		kDynamicDocumentsPrefix + 23)
DECLARE_PMID(kErrorIDSpace,				kMotion_AnimationInvalidKeyframeError,	kDynamicDocumentsPrefix + 24)
DECLARE_PMID(kErrorIDSpace,				kMotion_AnimationMotionPathError,		kDynamicDocumentsPrefix + 25)
DECLARE_PMID(kErrorIDSpace,				kMotion_AnimationSetPropertyError,		kDynamicDocumentsPrefix + 26)
DECLARE_PMID(kErrorIDSpace,				kMotion_AnimationCannotSetObjectTriggerError, kDynamicDocumentsPrefix + 27)
DECLARE_PMID(kErrorIDSpace,				kMotion_AnimationSaveCopyError,			kDynamicDocumentsPrefix + 28)
DECLARE_PMID(kErrorIDSpace,				kMotion_AnimationSaveCustomError,		kDynamicDocumentsPrefix + 29)
DECLARE_PMID(kErrorIDSpace,				kMotion_DETimingListError,				kDynamicDocumentsPrefix + 30)
DECLARE_PMID(kErrorIDSpace,				kMotion_DEFailToRemoveEventError,		kDynamicDocumentsPrefix + 31)
DECLARE_PMID(kErrorIDSpace,				kMotion_DEFailToSetDelayError,			kDynamicDocumentsPrefix + 32)
DECLARE_PMID(kErrorIDSpace,				kMotion_DENotOnSameSpreadError,			kDynamicDocumentsPrefix + 33)
DECLARE_PMID(kErrorIDSpace,				kMotion_DEInternalINXContextOnlyError,	kDynamicDocumentsPrefix + 34)
DECLARE_PMID(kErrorIDSpace,				kMotion_DETargetAlreadyExistsError,		kDynamicDocumentsPrefix + 35)
DECLARE_PMID(kErrorIDSpace,				kMotion_DESelfTriggerMoveTargetError,	kDynamicDocumentsPrefix + 36)
DECLARE_PMID(kErrorIDSpace,				kMotion_DESelfTriggerAddTargetError,	kDynamicDocumentsPrefix + 37)
DECLARE_PMID(kErrorIDSpace,				kMotion_DESelfTriggerReplaceTargetError,kDynamicDocumentsPrefix + 38)
DECLARE_PMID(kErrorIDSpace,				kMotion_DESelfTriggerUnlinkTargetError,	kDynamicDocumentsPrefix + 39)
DECLARE_PMID(kErrorIDSpace,				kMotion_DEInvalidTriggerEventError,		kDynamicDocumentsPrefix + 40)
DECLARE_PMID(kErrorIDSpace,				kMotion_CannotDeleteUsedPresetError,	kDynamicDocumentsPrefix + 41)
DECLARE_PMID(kErrorIDSpace,				kMotion_CannotCreateDefaultAnimationError,kDynamicDocumentsPrefix + 42)
DECLARE_PMID(kErrorIDSpace,				kMotion_DEMediaNotAllowedInPageClickEventError,kDynamicDocumentsPrefix + 43)
DECLARE_PMID(kErrorIDSpace,				kMotion_AnimationUnknownEaseTypeError,	kDynamicDocumentsPrefix + 44)
DECLARE_PMID(kErrorIDSpace,				kMotion_DECantDeleteButtonTimingListError,kDynamicDocumentsPrefix + 45)
DECLARE_PMID(kErrorIDSpace,				kMotion_DEAddTargetError,				kDynamicDocumentsPrefix + 46)
DECLARE_PMID(kErrorIDSpace,				kMotion_DECannotMoveTargetError,		kDynamicDocumentsPrefix + 47)
DECLARE_PMID(kErrorIDSpace,				kMotion_DECreateDynamicTargetError,		kDynamicDocumentsPrefix + 48)
DECLARE_PMID(kErrorIDSpace,				kMotion_DEFailToRemoveTargetError,		kDynamicDocumentsPrefix + 49)
DECLARE_PMID(kErrorIDSpace,				kMotion_CustomPresetNameAlreadyExistsError,	kDynamicDocumentsPrefix + 50)
DECLARE_PMID(kErrorIDSpace,				kMotion_PresetFilesFailedToLoadError,	kDynamicDocumentsPrefix + 51)
DECLARE_PMID(kErrorIDSpace,				kMotion_DECannotMoveGroupError,			kDynamicDocumentsPrefix + 52)

// gap to allow for more motion preset errors

DECLARE_PMID(kErrorIDSpace,				kDynDocs_UnableToCopyRequiredResourceError, kDynamicDocumentsPrefix + 60)
DECLARE_PMID(kErrorIDSpace,				kDynDocs_MissingLinkForResourceError,		kDynamicDocumentsPrefix + 61)
	
// <message ID>
DECLARE_PMID(kMessageIDSpace,			kMotionPresetDeleteWarningMessageID,	kDynamicDocumentsPrefix + 1)

// <ViewPortAttr ID>
// ViewPort Attributes
DECLARE_PMID(kViewPortAttrIDSpace,		kDynDocsExportVPAttr,					kDynamicDocumentsPrefix + 1)
DECLARE_PMID(kViewPortAttrIDSpace,		kDynDocsRasterizePlacedGraphicsVPAttr,	kDynamicDocumentsPrefix + 2)
DECLARE_PMID(kViewPortAttrIDSpace,		kDynDocsRasterizePGfxResolutionVPAttr,	kDynamicDocumentsPrefix + 3)
DECLARE_PMID(kViewPortAttrIDSpace,		kDynDocsScaleFactorForExportVPAttr,		kDynamicDocumentsPrefix + 4)
DECLARE_PMID(kViewPortAttrIDSpace,		kDynDocsButtonsSupportedVPAttr,			kDynamicDocumentsPrefix + 5)

//	Timing target role ID
#define kTimingTargetRoleIDSpace		kDynamicDocumentsPrefix + 1
#define kTimingTargetVerbIDSpace		kDynamicDocumentsPrefix + 2
#define kTimingTargetDataIDSpace		kDynamicDocumentsPrefix + 3

DECLARE_PMID(kTimingTargetRoleIDSpace,	kTimingTargetRoleDefault,				kDynamicDocumentsPrefix + 1)
DECLARE_PMID(kTimingTargetRoleIDSpace,	kTimingTargetRoleVideo,					kDynamicDocumentsPrefix + 2)
DECLARE_PMID(kTimingTargetRoleIDSpace,	kTimingTargetRoleAnimation,				kDynamicDocumentsPrefix + 3)
DECLARE_PMID(kTimingTargetRoleIDSpace,	kTimingTargetRoleSound,					kDynamicDocumentsPrefix + 4)
DECLARE_PMID(kTimingTargetRoleIDSpace,	kTimingTargetRoleMSO,					kDynamicDocumentsPrefix + 5)

//	Timing target action verb
DECLARE_PMID(kTimingTargetVerbIDSpace,	kTimingTargetVerbPlay,					kDynamicDocumentsPrefix + 1)
DECLARE_PMID(kTimingTargetVerbIDSpace,	kTimingTargetVerbStop,					kDynamicDocumentsPrefix + 2)
DECLARE_PMID(kTimingTargetVerbIDSpace,	kTimingTargetVerbPause,					kDynamicDocumentsPrefix + 3)
DECLARE_PMID(kTimingTargetVerbIDSpace,	kTimingTargetVerbResume,				kDynamicDocumentsPrefix + 4)

DECLARE_PMID(kTimingTargetDataIDSpace,	kTimingTargetDataReverseAnimation,		kDynamicDocumentsPrefix + 1)
DECLARE_PMID(kTimingTargetDataIDSpace,	kTimingTargetDataNavigationPoint,		kDynamicDocumentsPrefix + 2)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kMotionPresetObjectScriptElement,					kDynamicDocumentsPrefix + 1)
//gap

//Events
DECLARE_PMID(kScriptInfoIDSpace, kMotionDuplicatePresetMethodScriptElement,			kDynamicDocumentsPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kMotionImportPresetMethodScriptElement,			kDynamicDocumentsPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kMotionExportPresetMethodScriptElement,			kDynamicDocumentsPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kMotionSavePresetMethodScriptElement,				kDynamicDocumentsPrefix + 53)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kPageTransitionTypePropertyScriptElement,			kDynamicDocumentsPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kPageTransitionDirectionPropertyScriptElement,		kDynamicDocumentsPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kPageTransitionDurationPropertyScriptElement,		kDynamicDocumentsPrefix + 102)
//gap

DECLARE_PMID(kScriptInfoIDSpace, kInsertHyphensForTLFPropertyScriptElement,			kDynamicDocumentsPrefix + 127)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentJPEGQualityPropertyScriptElement,				kDynamicDocumentsPrefix + 139)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentRasterResolutionPropertyScriptElement,			kDynamicDocumentsPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentResamplingTypePropertyScriptElement,			kDynamicDocumentsPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentResamplingThresholdPropertyScriptElement,		kDynamicDocumentsPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentReadersPerSpreadPropertyScriptElement,			kDynamicDocumentsPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentRasterizePagesPropertyScriptElement,			kDynamicDocumentsPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentTextExportPolicyPropertyScriptElement,			kDynamicDocumentsPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentTransparencyHandlingPropertyScriptElement,		kDynamicDocumentsPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentFlattenerStylePropertyScriptElement,			kDynamicDocumentsPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentSizeSelectionPropertyScriptElement,			kDynamicDocumentsPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentFitToOptionPropertyScriptElement,				kDynamicDocumentsPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentScaleToFitPropertyScriptElement,				kDynamicDocumentsPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentFitToWidthAndHeightPropertyScriptElement,		kDynamicDocumentsPrefix + 151)
//gap

DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataPlaysLoopPropertyScriptElement,		kDynamicDocumentsPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kMotionPresetContentsScriptElement,				kDynamicDocumentsPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kMotionPresetEditLockedScriptElement,				kDynamicDocumentsPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kMotionPresetDeleteLockedScriptElement,			kDynamicDocumentsPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kMotionPresetNameLockedScriptElement,				kDynamicDocumentsPrefix + 161)

DECLARE_PMID(kScriptInfoIDSpace, kAnimationSettingsObjectScriptElement,				kDynamicDocumentsPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationSettingsPropertyScriptElement,			kDynamicDocumentsPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataObjectScriptElement,					kDynamicDocumentsPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataPresetPropertyScriptElement,			kDynamicDocumentsPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataDurationPropertyScriptElement,		kDynamicDocumentsPrefix + 166)


DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataTransformOffsetsPropertyScriptElement,kDynamicDocumentsPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataMotionPathPropertyScriptElement,		kDynamicDocumentsPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataOpacityArrayPropertyScriptElement,	kDynamicDocumentsPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataRotationArrayPropertyScriptElement,	kDynamicDocumentsPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataScaleXArrayPropertyScriptElement,	kDynamicDocumentsPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataScaleYArrayPropertyScriptElement,	kDynamicDocumentsPrefix + 172)


DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataEaseTypeEnumScriptElement,			kDynamicDocumentsPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataTriggerObjectPropertyScriptElement,	kDynamicDocumentsPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataPlaysPropertyScriptElement,			kDynamicDocumentsPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataKeyFrameTypeDefScriptElement,		kDynamicDocumentsPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataPathKeyFrameTypeDefScriptElement,	kDynamicDocumentsPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataEaseTypePropertyScriptElement,		kDynamicDocumentsPrefix + 178)

DECLARE_PMID(kScriptInfoIDSpace, kDETimingSettingsObjectScriptElement,				kDynamicDocumentsPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingSettingsPropertyScriptElement,			kDynamicDocumentsPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingListObjectScriptElement,					kDynamicDocumentsPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingDataObjectScriptElement,					kDynamicDocumentsPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingTargetItemScriptElement,					kDynamicDocumentsPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingDelayPropertyScriptElement,				kDynamicDocumentsPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingPositionPropertyScriptElement,			kDynamicDocumentsPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingTriggerEventEnumScriptElement,			kDynamicDocumentsPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingTriggerEventPropertyScriptElement,		kDynamicDocumentsPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingTargetPropertyScriptElement,				kDynamicDocumentsPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingMoveMethodScriptElement,					kDynamicDocumentsPrefix + 189)

DECLARE_PMID(kScriptInfoIDSpace, kDETimingAddTimingListMethodScriptElement,			kDynamicDocumentsPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingAddTimingDataMethodScriptElement,			kDynamicDocumentsPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingAddTargetMethodScriptElement,				kDynamicDocumentsPrefix + 192)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingUnlinkGroupMethodScriptElement,			kDynamicDocumentsPrefix + 193)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingUnlinkTargetMethodScriptElement,			kDynamicDocumentsPrefix + 194)
DECLARE_PMID(kScriptInfoIDSpace, kSkipVerifyTimingDataParamMetadataScriptElement,	kDynamicDocumentsPrefix + 195)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingUnassignedTargetsPropertyScriptElement,	kDynamicDocumentsPrefix + 199)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kPageTransitionTypeEnumScriptElement,				kDynamicDocumentsPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kPageTransitionDirectionEnumScriptElement,			kDynamicDocumentsPrefix + 201)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentJPEGQualityEnumScriptElement,		kDynamicDocumentsPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentTextExportPolicyEnumScriptElement, kDynamicDocumentsPrefix + 204)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentSizeFitSettingsEnumScriptElement,	kDynamicDocumentsPrefix + 206)	
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentFitToOptionsEnumScriptElement,		kDynamicDocumentsPrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kPageTransitionDurationEnumScriptElement,			kDynamicDocumentsPrefix + 208)
//gap

DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentDynamicMediaHandlingEnumScriptElement,	kDynamicDocumentsPrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicDocumentDynamicMediaHandlingPropertyScriptElement,	kDynamicDocumentsPrefix + 211)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingReverseAnimationPropertyScriptElement,	kDynamicDocumentsPrefix + 212)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataAnimateOptionsEnumScriptElement,		kDynamicDocumentsPrefix + 213)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataAnimateOptionPropertyScriptElement,	kDynamicDocumentsPrefix + 214)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataHideInitiallyPropertyScriptElement,	kDynamicDocumentsPrefix + 215)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataMotionPathPointsPropertyScriptElement,kDynamicDocumentsPrefix + 216)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataHideAfterPropertyScriptElement,		kDynamicDocumentsPrefix + 217)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingGroupNumPlaysPropertyScriptElement,		kDynamicDocumentsPrefix + 218)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingGroupPlaysLoopPropertyScriptElement,		kDynamicDocumentsPrefix + 219)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingTargetRolePropertyScriptElement,			kDynamicDocumentsPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kDETimingTargetActionPropertyScriptElement,		kDynamicDocumentsPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationDataHasCustomPropertyScriptElement,		kDynamicDocumentsPrefix + 222)

//	Uncomment if required this enum type for all properties of animation settings pref object.
//DECLARE_PMID(kScriptInfoIDSpace, kAddNothingEnumAmSettingsPropsMetadataScriptElement,kDynamicDocumentsPrefix + 219)

// INX Ordering & snippet attribute meta data
DECLARE_PMID(kScriptInfoIDSpace, kINXOrderMotionPresetObject70MetadataScriptEmenet,	kDynamicDocumentsPrefix + 230)
DECLARE_PMID(kScriptInfoIDSpace, kINXOrderSpreadTimingObject70MetadataScriptEmenet,	kDynamicDocumentsPrefix + 231)
DECLARE_PMID(kScriptInfoIDSpace, kINXOrderButtonTimingObject70MetadataScriptEmenet,	kDynamicDocumentsPrefix + 232)
DECLARE_PMID(kScriptInfoIDSpace, kINXOrderMSOStateTimingObject70MetadataScriptEmenet,kDynamicDocumentsPrefix + 233)
DECLARE_PMID(kScriptInfoIDSpace, kINXSnippetAnimationSettings70MetadataScriptEmenet,kDynamicDocumentsPrefix + 234)
DECLARE_PMID(kScriptInfoIDSpace, kTimingMgrINXPolicy70MetadataScriptElement,		kDynamicDocumentsPrefix + 235)
DECLARE_PMID(kScriptInfoIDSpace, kMotionPresetINXMatchPolicy70MetadataScriptElement,kDynamicDocumentsPrefix + 236)
DECLARE_PMID(kScriptInfoIDSpace, kMotionPresetContentsMetadataScriptElement,		kDynamicDocumentsPrefix + 237)

#ifdef DEBUG
DECLARE_PMID(kScriptInfoIDSpace, kMotionDumpSWFXMLMethodScriptElement,				kDynamicDocumentsPrefix + 254)
DECLARE_PMID(kScriptInfoIDSpace, kMotionPresetSWFXMLScriptElement,					kDynamicDocumentsPrefix + 255)
#endif

//	INX order definition	(See INXOrderDefs.h)
//	This is placed after kTrapStyleObjectScriptElement and before kConditionTagObjectScriptElement
#define kMotionPresetObjectScriptElementPosition		2810.0

//	Should be after all others
//	Last object position is defined as kLastObjectScriptElementPosition, which is 999999.9. This number should be sufficiently large.
#define kDETimingSettingsObjectScriptElementPosition	5000.0

//Services

//GUIDS
// {CE3B9739-B038-4ea3-9C3E-FC783E6090B3}
#define kMotionPreset_CLSID		{ 0xce3b9739, 0xb038, 0x4ea3, { 0x9c, 0x3e, 0xfc, 0x78, 0x3e, 0x60, 0x90, 0xb3 } }
// {F8B3F2C9-FD1E-4040-90BB-369111963367}
#define kMotionPresets_CLSID	{ 0xf8b3f2c9, 0xfd1e, 0x4040, { 0x90, 0xbb, 0x36, 0x91, 0x11, 0x96, 0x33, 0x67} }
// {B8723342-BD26-4711-9C45-07F4C37B1068}
#define kTimingSettings_CLSID { 0xb8723342, 0xbd26, 0x4711, { 0x9c, 0x45, 0x7, 0xf4, 0xc3, 0x7b, 0x10, 0x68} }
// {70D1B136-070D-4121-A1B5-A64AB6AB26D6}
#define kAnimationSettings_CLSID { 0x70d1b136, 0x70d, 0x4121, {0xa1, 0xb5, 0xa6, 0x4a, 0xb6, 0xab, 0x26, 0xd6 } }
// {01F8A19E-E3CD-4451-A6D0-5C26A93412CD}
#define kAnimation_CLSID { 0x1f8a19e, 0xe3cd, 0x4451, { 0xa6, 0xd0, 0x5c, 0x26, 0xa9, 0x34, 0x12, 0xcd } }
// {DB9C0A41-9214-4cff-ACE3-9DDDE7913150}
#define kAnimations_CLSID { 0xdb9c0a41, 0x9214, 0x4cff, { 0xac, 0xe3, 0x9d, 0xdd, 0xe7, 0x91, 0x31, 0x50 } }
// {875399FB-5932-4115-83AD-55BA64278411}
#define kTimingListObject_CLSID { 0x875399fb, 0x5932, 0x4115, { 0x83, 0xad, 0x55, 0xba, 0x64, 0x27, 0x84, 0x11 } }
// {4F210CC3-D3DC-4815-AFF6-F66F2FAC97C3}
#define kTimingListObjects_CLSID { 0x4f210cc3, 0xd3dc, 0x4815, { 0xaf, 0xf6, 0xf6, 0x6f, 0x2f, 0xac, 0x97, 0xc3 } }
// {9EB3F4F2-9576-40d6-BF6E-65481C68317D}
#define kTimingDataObject_CLSID { 0x9eb3f4f2, 0x9576, 0x40d6, { 0xbf, 0x6e, 0x65, 0x48, 0x1c, 0x68, 0x31, 0x7d } }
// {71433E7C-129B-4267-96F9-7D4C02F7412E}
#define kTimingDataObjects_CLSID { 0x71433e7c, 0x129b, 0x4267, { 0x96, 0xf9, 0x7d, 0x4c, 0x2, 0xf7, 0x41, 0x2e } }
// {46A42B4B-FE82-4cec-A039-451EC980235A}
#define kTimingTargetItem_CLSID { 0x46a42b4b, 0xfe82, 0x4cec, { 0xa0, 0x39, 0x45, 0x1e, 0xc9, 0x80, 0x23, 0x5a } }
// {F3E58AC1-1249-4826-AB0C-C70CF92B3941}
#define kTimingTargetItems_CLSID { 0xf3e58ac1, 0x1249, 0x4826, { 0xab, 0xc, 0xc7, 0xc, 0xf9, 0x2b, 0x39, 0x41 } }

#endif // !def DynamicDocuments_ID_h__
