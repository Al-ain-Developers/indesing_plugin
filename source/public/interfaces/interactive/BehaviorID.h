//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/BehaviorID.h $
//  
//  Owner: Mark VerMurlen
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

#ifndef __BehaviorID_h__
#define __BehaviorID_h__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kBehaviorPrefix	 		RezLong(0x15600)

// ----- Define a new ID space

#define kBehaviorEventIDSpace			kBehaviorPrefix + 1
#define kBehaviorIDSpace			kBehaviorPrefix + 2

// ----- Plug-in ID -----

#define kBehaviorPluginName 			"Behavior"
DECLARE_PMID(kPlugInIDSpace,			kBehaviorPluginID,					kBehaviorPrefix + 1)

// ----- Class IDs -----

//DECLARE_PMID(kClassIDSpace, 		kBehaviorSuiteRegisterBoss,				kBehaviorPrefix + 1)
DECLARE_PMID(kClassIDSpace, 		kBehaviorAfterNewDocResponderBoss,		kBehaviorPrefix + 2)
DECLARE_PMID(kClassIDSpace, 		kBehaviorAfterOpenDocResponderBoss,		kBehaviorPrefix + 3)
DECLARE_PMID(kClassIDSpace, 		kBehaviorBeforeCloseDocResponderBoss,	kBehaviorPrefix + 4)

DECLARE_PMID(kClassIDSpace, 		kActionFactoryBoss,						kBehaviorPrefix + 6)
DECLARE_PMID(kClassIDSpace, 		kCreateBehaviorCmdBoss,					kBehaviorPrefix + 7)
DECLARE_PMID(kClassIDSpace, 		kEditBehaviorCmdBoss,					kBehaviorPrefix + 8)
DECLARE_PMID(kClassIDSpace, 		kBehaviorDataBoss,						kBehaviorPrefix + 9)

DECLARE_PMID(kClassIDSpace, 		kGoToFirstPageFactoryBoss,				kBehaviorPrefix + 10)
DECLARE_PMID(kClassIDSpace, 		kCreateGoToFirstPageBehaviorCmdBoss,	kBehaviorPrefix + 11)
DECLARE_PMID(kClassIDSpace, 		kCreateGoToLastPageBehaviorCmdBoss,		kBehaviorPrefix + 12)
DECLARE_PMID(kClassIDSpace, 		kCreateGoToNextPageBehaviorCmdBoss,		kBehaviorPrefix + 13)
DECLARE_PMID(kClassIDSpace, 		kCreateGoToPreviousPageBehaviorCmdBoss,	kBehaviorPrefix + 14)
DECLARE_PMID(kClassIDSpace, 		kEditGoToFirstPageBehaviorCmdBoss,		kBehaviorPrefix + 15)
DECLARE_PMID(kClassIDSpace, 		kEditGoToLastPageBehaviorCmdBoss,		kBehaviorPrefix + 16)
DECLARE_PMID(kClassIDSpace, 		kEditGoToNextPageBehaviorCmdBoss,		kBehaviorPrefix + 17)
DECLARE_PMID(kClassIDSpace, 		kEditGoToPreviousPageBehaviorCmdBoss,	kBehaviorPrefix + 18)
DECLARE_PMID(kClassIDSpace, 		kGoToFirstPageBehaviorDataBoss,			kBehaviorPrefix + 19)
DECLARE_PMID(kClassIDSpace, 		kGoToLastPageBehaviorDataBoss,			kBehaviorPrefix + 20)
DECLARE_PMID(kClassIDSpace, 		kGoToNextPageBehaviorDataBoss,			kBehaviorPrefix + 21)
DECLARE_PMID(kClassIDSpace, 		kGoToPreviousPageBehaviorDataBoss,		kBehaviorPrefix + 22)
DECLARE_PMID(kClassIDSpace, 		kGoToLastPageFactoryBoss,				kBehaviorPrefix + 23)
DECLARE_PMID(kClassIDSpace, 		kGoToNextPageFactoryBoss,				kBehaviorPrefix + 24)
DECLARE_PMID(kClassIDSpace, 		kGoToPreviousPageFactoryBoss,			kBehaviorPrefix + 25)
DECLARE_PMID(kClassIDSpace, 		kGoToPositionBehaviorBoss,				kBehaviorPrefix + 26)
DECLARE_PMID(kClassIDSpace, 		kGoToURLBehaviorBoss,					kBehaviorPrefix + 27)
DECLARE_PMID(kClassIDSpace, 		kGoToURLFactoryBoss,					kBehaviorPrefix + 28)
DECLARE_PMID(kClassIDSpace, 		kCreateGoToURLBehaviorCmdBoss,			kBehaviorPrefix + 29)
DECLARE_PMID(kClassIDSpace, 		kEditGoToURLBehaviorCmdBoss,			kBehaviorPrefix + 30)
DECLARE_PMID(kClassIDSpace, 		kGoToURLBhvrScriptProviderBoss,			kBehaviorPrefix + 31)
DECLARE_PMID(kClassIDSpace, 		kGoToPosBhvrScriptProviderBoss,			kBehaviorPrefix + 32)
DECLARE_PMID(kClassIDSpace, 		kGoToAnchorBhvrScriptProviderBoss,		kBehaviorPrefix + 33)
DECLARE_PMID(kClassIDSpace, 		kGoToPageFactoryBoss,					kBehaviorPrefix + 34)
DECLARE_PMID(kClassIDSpace, 		kCreateGoToPageBehaviorCmdBoss,			kBehaviorPrefix + 35)
DECLARE_PMID(kClassIDSpace, 		kEditGoToPageBehaviorCmdBoss,			kBehaviorPrefix + 36)
DECLARE_PMID(kClassIDSpace, 		kGoToPageBehaviorDataBoss,				kBehaviorPrefix + 37)
DECLARE_PMID(kClassIDSpace, 		kAnimationBhvrScriptProviderBoss,		kBehaviorPrefix + 38)
DECLARE_PMID(kClassIDSpace, 		kMSOBhvrScriptProviderBoss,				kBehaviorPrefix + 39)

DECLARE_PMID(kClassIDSpace, 		kCreateMovieActionCmdBoss,			kBehaviorPrefix + 40)
DECLARE_PMID(kClassIDSpace, 		kEditMovieActionCmdBoss,			kBehaviorPrefix + 41)
DECLARE_PMID(kClassIDSpace, 		kDeleteMovieBhvrCmdBoss,			kBehaviorPrefix + 42)
DECLARE_PMID(kClassIDSpace, 		kFixupMovieBhvrCmdBoss,				kBehaviorPrefix + 43)
DECLARE_PMID(kClassIDSpace, 		kMovieActionBoss,					kBehaviorPrefix + 44)
DECLARE_PMID(kClassIDSpace, 		kMovieActionFactoryBoss,			kBehaviorPrefix + 45)
DECLARE_PMID(kClassIDSpace, 		kMovieBhvrScriptProviderBoss,		kBehaviorPrefix + 46)

DECLARE_PMID(kClassIDSpace,			kAnimationBehaviorDataBoss,			kBehaviorPrefix + 47)
DECLARE_PMID(kClassIDSpace,			kCreateAnimationBehaviorCmdBoss,	kBehaviorPrefix + 48)
DECLARE_PMID(kClassIDSpace,			kEditAnimationBehaviorCmdBoss,		kBehaviorPrefix + 49)

DECLARE_PMID(kClassIDSpace, 		kCreateShowHideFieldActionCmdBoss,	kBehaviorPrefix + 50)
DECLARE_PMID(kClassIDSpace, 		kEditShowHideFieldActionCmdBoss,	kBehaviorPrefix + 51)
DECLARE_PMID(kClassIDSpace, 		kDeleteShowHideFieldBhvrCmdBoss,	kBehaviorPrefix + 52)
DECLARE_PMID(kClassIDSpace, 		kFixupShowHideFieldsBhvrCmdBoss,	kBehaviorPrefix + 53)
DECLARE_PMID(kClassIDSpace, 		kShowHideFieldActionBoss,			kBehaviorPrefix + 54)
DECLARE_PMID(kClassIDSpace, 		kShowHideFieldActionFactoryBoss,	kBehaviorPrefix + 55)
DECLARE_PMID(kClassIDSpace, 		kShowHideBhvrScriptProviderBoss,	kBehaviorPrefix + 56)
DECLARE_PMID(kClassIDSpace, 		kShowHideFieldDeleteTargetCmdBoss,	kBehaviorPrefix + 57)

DECLARE_PMID(kClassIDSpace,			kAnimationActionFactoryBoss,		kBehaviorPrefix + 58)

//gap

DECLARE_PMID(kClassIDSpace, 		kDeleteBehaviorCmdBoss,				kBehaviorPrefix + 60)
DECLARE_PMID(kClassIDSpace, 		kAddToNamedPageItemListCmdBoss,		kBehaviorPrefix + 61)
DECLARE_PMID(kClassIDSpace, 		kRemoveFromNamedPageItemListCmdBoss,kBehaviorPrefix + 62)

DECLARE_PMID(kClassIDSpace,			kSwitchToMSOStateBehaviorDataBoss,			kBehaviorPrefix + 63)
DECLARE_PMID(kClassIDSpace,			kCreateSwitchToMSOStateBehaviorCmdBoss,		kBehaviorPrefix + 64)
DECLARE_PMID(kClassIDSpace,			kEditSwitchToMSOStateBehaviorCmdBoss,		kBehaviorPrefix + 65)
DECLARE_PMID(kClassIDSpace,			kSwitchToMSOStateActionFactoryBoss,			kBehaviorPrefix + 66)
DECLARE_PMID(kClassIDSpace,			kSwitchToNextMSOStateBehaviorDataBoss,		kBehaviorPrefix + 67)
DECLARE_PMID(kClassIDSpace,			kCreateSwitchToNextMSOStateBehaviorCmdBoss,	kBehaviorPrefix + 68)
DECLARE_PMID(kClassIDSpace,			kEditSwitchToNextMSOStateBehaviorCmdBoss,	kBehaviorPrefix + 69)

DECLARE_PMID(kClassIDSpace, 		kMouseEnterEventBoss,				kBehaviorPrefix + 70)
DECLARE_PMID(kClassIDSpace, 		kMouseExitEventBoss,				kBehaviorPrefix + 71)
DECLARE_PMID(kClassIDSpace, 		kMouseUpEventBoss,					kBehaviorPrefix + 72)
DECLARE_PMID(kClassIDSpace, 		kMouseDownEventBoss,				kBehaviorPrefix + 73)
DECLARE_PMID(kClassIDSpace, 		kOnBlurEventBoss,					kBehaviorPrefix + 74)
DECLARE_PMID(kClassIDSpace, 		kOnFocusEventBoss,					kBehaviorPrefix + 75)

DECLARE_PMID(kClassIDSpace, 		kPageOpenEventBoss,					kBehaviorPrefix + 76)
DECLARE_PMID(kClassIDSpace, 		kPageCloseEventBoss,				kBehaviorPrefix + 77)
DECLARE_PMID(kClassIDSpace, 		kValidateEventBoss,					kBehaviorPrefix + 78)
DECLARE_PMID(kClassIDSpace, 		kCalculateEventBoss,				kBehaviorPrefix + 79)
DECLARE_PMID(kClassIDSpace, 		kFormatEventBoss,					kBehaviorPrefix + 80) // format and/or keystroke ??? event in PDF
DECLARE_PMID(kClassIDSpace, 		kSignedEventBoss,					kBehaviorPrefix + 81) // format event in PDF
DECLARE_PMID(kClassIDSpace, 		kSelectionChangedEventBoss,			kBehaviorPrefix + 82) // keystroke event in PDF
DECLARE_PMID(kClassIDSpace, 		kKeystrokeEventBoss,				kBehaviorPrefix + 83)
DECLARE_PMID(kClassIDSpace, 		kDocumentOpenEventBoss,				kBehaviorPrefix + 84)
DECLARE_PMID(kClassIDSpace, 		kDocumentWillCloseEventBoss,		kBehaviorPrefix + 85)
DECLARE_PMID(kClassIDSpace, 		kDocumentWillSaveEventBoss,			kBehaviorPrefix + 86)
DECLARE_PMID(kClassIDSpace, 		kDocumentDidSaveEventBoss,			kBehaviorPrefix + 87)
DECLARE_PMID(kClassIDSpace, 		kDocumentWillPrintEventBoss,		kBehaviorPrefix + 88)
DECLARE_PMID(kClassIDSpace, 		kDocumentDidPrintEventBoss,			kBehaviorPrefix + 89)

DECLARE_PMID(kClassIDSpace, 		kImportDataBehaviorBoss,			kBehaviorPrefix + 90)
DECLARE_PMID(kClassIDSpace, 		kCreateImportDataBehaviorCmdBoss,	kBehaviorPrefix + 91)
DECLARE_PMID(kClassIDSpace, 		kEditImportDataBehaviorCmdBoss,		kBehaviorPrefix + 92)
DECLARE_PMID(kClassIDSpace, 		kImportDataFactoryBoss,				kBehaviorPrefix + 93)
DECLARE_PMID(kClassIDSpace, 		kImportDataBhvrScriptProviderBoss,	kBehaviorPrefix + 94)

DECLARE_PMID(kClassIDSpace,			kSwitchToNextMSOStateActionFactoryBoss,		kBehaviorPrefix + 95)
DECLARE_PMID(kClassIDSpace,			kSwitchToPrevMSOStateBehaviorDataBoss,		kBehaviorPrefix + 96)
DECLARE_PMID(kClassIDSpace,			kCreateSwitchToPrevMSOStateBehaviorCmdBoss,	kBehaviorPrefix + 97)
DECLARE_PMID(kClassIDSpace,			kEditSwitchToPrevMSOStateBehaviorCmdBoss,	kBehaviorPrefix + 98)
DECLARE_PMID(kClassIDSpace,			kSwitchToPrevMSOStateActionFactoryBoss,		kBehaviorPrefix + 99)

DECLARE_PMID(kClassIDSpace, 		kResetFormBehaviorBoss,				kBehaviorPrefix + 100)
DECLARE_PMID(kClassIDSpace, 		kCreateResetFormBehaviorCmdBoss,	kBehaviorPrefix + 101)
DECLARE_PMID(kClassIDSpace, 		kEditResetFormBehaviorCmdBoss,		kBehaviorPrefix + 102)
DECLARE_PMID(kClassIDSpace, 		kDeleteResetFormBehaviorCmdBoss,	kBehaviorPrefix + 103)
DECLARE_PMID(kClassIDSpace, 		kResetFormFactoryBoss,				kBehaviorPrefix + 104)
DECLARE_PMID(kClassIDSpace, 		kResetFormBhvrScriptProviderBoss,	kBehaviorPrefix + 105)
DECLARE_PMID(kClassIDSpace, 		kFixupResetFormBhvrCmdBoss,			kBehaviorPrefix + 106)

DECLARE_PMID(kClassIDSpace, 		kSubmitFormBehaviorBoss,			kBehaviorPrefix + 110)
DECLARE_PMID(kClassIDSpace, 		kCreateSubmitFormBehaviorCmdBoss,	kBehaviorPrefix + 111)
DECLARE_PMID(kClassIDSpace, 		kEditSubmitFormBehaviorCmdBoss,		kBehaviorPrefix + 112)
DECLARE_PMID(kClassIDSpace, 		kDeleteSubmitFormBehaviorCmdBoss,	kBehaviorPrefix + 113)
DECLARE_PMID(kClassIDSpace, 		kSubmitFormFactoryBoss,				kBehaviorPrefix + 114)
DECLARE_PMID(kClassIDSpace, 		kSubmitFormBhvrScriptProviderBoss,	kBehaviorPrefix + 115)
DECLARE_PMID(kClassIDSpace, 		kFixupSubmitFormBhvrCmdBoss,		kBehaviorPrefix + 116)

DECLARE_PMID(kClassIDSpace, 		kOpenFileBehaviorBoss,				kBehaviorPrefix + 120)
DECLARE_PMID(kClassIDSpace, 		kCreateOpenFileBehaviorCmdBoss,		kBehaviorPrefix + 121)
DECLARE_PMID(kClassIDSpace, 		kEditOpenFileBehaviorCmdBoss,		kBehaviorPrefix + 122)
DECLARE_PMID(kClassIDSpace, 		kOpenFileFactoryBoss,				kBehaviorPrefix + 123)
DECLARE_PMID(kClassIDSpace, 		kOpenFileBhvrScriptProviderBoss,	kBehaviorPrefix + 124)

DECLARE_PMID(kClassIDSpace, 		kDeleteAnimationBhvrCmdBoss,		kBehaviorPrefix + 125)
DECLARE_PMID(kClassIDSpace, 		kFixupAnimationBhvrCmdBoss,			kBehaviorPrefix + 126)
DECLARE_PMID(kClassIDSpace, 		kDeleteSwitchMSOStateBhvrCmdBoss,	kBehaviorPrefix + 127)
DECLARE_PMID(kClassIDSpace, 		kFixupSwitchMSOStateBhvrCmdBoss,	kBehaviorPrefix + 128)

DECLARE_PMID(kClassIDSpace, 		kCloseBehaviorBoss,					kBehaviorPrefix + 130)
DECLARE_PMID(kClassIDSpace, 		kCreateCloseBehaviorCmdBoss,		kBehaviorPrefix + 131)
DECLARE_PMID(kClassIDSpace, 		kEditCloseBehaviorCmdBoss,			kBehaviorPrefix + 132)
DECLARE_PMID(kClassIDSpace, 		kCloseFactoryBoss,					kBehaviorPrefix + 133)
DECLARE_PMID(kClassIDSpace, 		kCloseBhvrScriptProviderBoss,		kBehaviorPrefix + 134)

DECLARE_PMID(kClassIDSpace, 		kExitBehaviorBoss,					kBehaviorPrefix + 140)
DECLARE_PMID(kClassIDSpace, 		kCreateExitBehaviorCmdBoss,			kBehaviorPrefix + 141)
DECLARE_PMID(kClassIDSpace, 		kEditExitBehaviorCmdBoss,			kBehaviorPrefix + 142)
DECLARE_PMID(kClassIDSpace, 		kExitFactoryBoss,					kBehaviorPrefix + 143)
DECLARE_PMID(kClassIDSpace, 		kExitBhvrScriptProviderBoss,		kBehaviorPrefix + 144)

DECLARE_PMID(kClassIDSpace, 		kJavaScriptBehaviorBoss,			kBehaviorPrefix + 150)
DECLARE_PMID(kClassIDSpace, 		kCreateJavaScriptBehaviorCmdBoss,	kBehaviorPrefix + 151)
DECLARE_PMID(kClassIDSpace, 		kEditJavaScriptBehaviorCmdBoss,		kBehaviorPrefix + 152)
DECLARE_PMID(kClassIDSpace, 		kJavaScriptFactoryBoss,				kBehaviorPrefix + 153)
DECLARE_PMID(kClassIDSpace, 		kJavaScriptBhvrScriptProviderBoss,	kBehaviorPrefix + 154)

DECLARE_PMID(kClassIDSpace, 		kFormulaBehaviorBoss,				kBehaviorPrefix + 155)
DECLARE_PMID(kClassIDSpace, 		kCreateFormulaBehaviorCmdBoss,		kBehaviorPrefix + 156)
DECLARE_PMID(kClassIDSpace, 		kEditFormulaBehaviorCmdBoss,		kBehaviorPrefix + 157)
DECLARE_PMID(kClassIDSpace, 		kFormulaFactoryBoss,				kBehaviorPrefix + 158)
DECLARE_PMID(kClassIDSpace, 		kFormulaBhvrScriptProviderBoss,		kBehaviorPrefix + 159)

DECLARE_PMID(kClassIDSpace, 		kValidateRangeBehaviorBoss,				kBehaviorPrefix + 160)
DECLARE_PMID(kClassIDSpace, 		kCreateValidateRangeBehaviorCmdBoss,	kBehaviorPrefix + 161)
DECLARE_PMID(kClassIDSpace, 		kEditValidateRangeBehaviorCmdBoss,		kBehaviorPrefix + 162)
DECLARE_PMID(kClassIDSpace, 		kValidateRangeFactoryBoss,				kBehaviorPrefix + 163)
DECLARE_PMID(kClassIDSpace, 		kValidateBhvrScriptProviderBoss,		kBehaviorPrefix + 164)

DECLARE_PMID(kClassIDSpace, 		kMarkReadOnlyBehaviorBoss,				kBehaviorPrefix + 165)
DECLARE_PMID(kClassIDSpace, 		kCreateMarkReadOnlyBehaviorCmdBoss,		kBehaviorPrefix + 166)
DECLARE_PMID(kClassIDSpace, 		kEditMarkReadOnlyBehaviorCmdBoss,		kBehaviorPrefix + 167)
DECLARE_PMID(kClassIDSpace, 		kMarkReadOnlyFactoryBoss,				kBehaviorPrefix + 168)
DECLARE_PMID(kClassIDSpace, 		kMarkReadOnlyBhvrScriptProviderBoss,	kBehaviorPrefix + 169)

DECLARE_PMID(kClassIDSpace, 		kFormatNumberBehaviorBoss,				kBehaviorPrefix + 170)
DECLARE_PMID(kClassIDSpace, 		kCreateFormatNumberBehaviorCmdBoss,		kBehaviorPrefix + 171)
DECLARE_PMID(kClassIDSpace, 		kEditFormatNumberBehaviorCmdBoss,		kBehaviorPrefix + 172)
DECLARE_PMID(kClassIDSpace, 		kFormatNumberFactoryBoss,				kBehaviorPrefix + 173)
DECLARE_PMID(kClassIDSpace, 		kFormatNumberBhvrScriptProviderBoss,	kBehaviorPrefix + 174)

DECLARE_PMID(kClassIDSpace, 		kFormatDateBehaviorBoss,				kBehaviorPrefix + 175)
DECLARE_PMID(kClassIDSpace, 		kCreateFormatDateBehaviorCmdBoss,		kBehaviorPrefix + 176)
DECLARE_PMID(kClassIDSpace, 		kEditFormatDateBehaviorCmdBoss,			kBehaviorPrefix + 177)
DECLARE_PMID(kClassIDSpace, 		kFormatDateFactoryBoss,					kBehaviorPrefix + 178)
DECLARE_PMID(kClassIDSpace, 		kFormatDateBhvrScriptProviderBoss,		kBehaviorPrefix + 179)

DECLARE_PMID(kClassIDSpace, 		kFormatPercentBehaviorBoss,				kBehaviorPrefix + 180)
DECLARE_PMID(kClassIDSpace, 		kCreateFormatPercentBehaviorCmdBoss,	kBehaviorPrefix + 181)
DECLARE_PMID(kClassIDSpace, 		kEditFormatPercentBehaviorCmdBoss,		kBehaviorPrefix + 182)
DECLARE_PMID(kClassIDSpace, 		kFormatPercentFactoryBoss,				kBehaviorPrefix + 183)
DECLARE_PMID(kClassIDSpace, 		kFormatPercentBhvrScriptProviderBoss,	kBehaviorPrefix + 184)

DECLARE_PMID(kClassIDSpace, 		kFormatTimeBehaviorBoss,				kBehaviorPrefix + 185)
DECLARE_PMID(kClassIDSpace, 		kCreateFormatTimeBehaviorCmdBoss,		kBehaviorPrefix + 186)
DECLARE_PMID(kClassIDSpace, 		kEditFormatTimeBehaviorCmdBoss,			kBehaviorPrefix + 187)
DECLARE_PMID(kClassIDSpace, 		kFormatTimeFactoryBoss,					kBehaviorPrefix + 188)
DECLARE_PMID(kClassIDSpace, 		kFormatTimeBhvrScriptProviderBoss,		kBehaviorPrefix + 189)

DECLARE_PMID(kClassIDSpace, 		kFormatSpecialBehaviorBoss,				kBehaviorPrefix + 190)
DECLARE_PMID(kClassIDSpace, 		kCreateFormatSpecialBehaviorCmdBoss,	kBehaviorPrefix + 191)
DECLARE_PMID(kClassIDSpace, 		kEditFormatSpecialBehaviorCmdBoss,		kBehaviorPrefix + 192)
DECLARE_PMID(kClassIDSpace, 		kFormatSpecialFactoryBoss,				kBehaviorPrefix + 193)
DECLARE_PMID(kClassIDSpace, 		kFormatSpecialBhvrScriptProviderBoss,	kBehaviorPrefix + 194)

DECLARE_PMID(kClassIDSpace, 		kStandardSupportedEventsBoss,			kBehaviorPrefix + 200)
DECLARE_PMID(kClassIDSpace, 		kDuplicateBehaviorCmdBoss,				kBehaviorPrefix + 201)
DECLARE_PMID(kClassIDSpace, 		kDeleteAllBehaviorsCmdBoss,				kBehaviorPrefix + 202)
//gap
DECLARE_PMID(kClassIDSpace, 		kBehaviorScriptProviderBoss,			kBehaviorPrefix + 205)

DECLARE_PMID(kClassIDSpace, 		kGoToAnchorFactoryBoss,					kBehaviorPrefix + 210)
DECLARE_PMID(kClassIDSpace, 		kGoToAnchorBehaviorBoss,				kBehaviorPrefix + 211)
DECLARE_PMID(kClassIDSpace, 		kCreateGoToAnchorBehaviorCmdBoss,		kBehaviorPrefix + 212)
DECLARE_PMID(kClassIDSpace, 		kEditGoToAnchorBehaviorCmdBoss,			kBehaviorPrefix + 213)

DECLARE_PMID(kClassIDSpace, 		kGoToPreviousViewFactoryBoss,			kBehaviorPrefix + 216)
DECLARE_PMID(kClassIDSpace, 		kGoToPreviousViewBehaviorBoss,			kBehaviorPrefix + 217)
DECLARE_PMID(kClassIDSpace, 		kCreateGoToPreviousViewBehaviorCmdBoss,	kBehaviorPrefix + 218)
DECLARE_PMID(kClassIDSpace, 		kEditGoToPreviousViewBehaviorCmdBoss,	kBehaviorPrefix + 219)

DECLARE_PMID(kClassIDSpace, 		kGoToNextViewFactoryBoss,				kBehaviorPrefix + 220)
DECLARE_PMID(kClassIDSpace, 		kGoToNextViewBehaviorBoss,				kBehaviorPrefix + 221)
DECLARE_PMID(kClassIDSpace, 		kCreateGoToNextViewBehaviorCmdBoss,		kBehaviorPrefix + 222)
DECLARE_PMID(kClassIDSpace, 		kEditGoToNextViewBehaviorCmdBoss,		kBehaviorPrefix + 223)

DECLARE_PMID(kClassIDSpace, 		kBehaviorDeleteCleanupBoss,				kBehaviorPrefix + 224)
DECLARE_PMID(kClassIDSpace, 		kBehaviorReferenceConverterBoss,		kBehaviorPrefix + 225)
DECLARE_PMID(kClassIDSpace, 		kEnableBehaviorCmdBoss,					kBehaviorPrefix + 226)
DECLARE_PMID(kClassIDSpace, 		kCopyBehaviorCmdBoss,					kBehaviorPrefix + 227)
DECLARE_PMID(kClassIDSpace, 		kNoOpCmdBoss,							kBehaviorPrefix + 228)
DECLARE_PMID(kClassIDSpace, 		kFixupMovieActionCmdBoss,				kBehaviorPrefix + 229)
DECLARE_PMID(kClassIDSpace, 		kAdoptBehaviorCmdBoss,					kBehaviorPrefix + 230)

DECLARE_PMID(kClassIDSpace, 		kViewZoomFactoryBoss,					kBehaviorPrefix + 231)
DECLARE_PMID(kClassIDSpace, 		kViewZoomBehaviorBoss,					kBehaviorPrefix + 232)
DECLARE_PMID(kClassIDSpace, 		kCreateViewZoomBehaviorCmdBoss,			kBehaviorPrefix + 233)
DECLARE_PMID(kClassIDSpace, 		kEditViewZoomBehaviorCmdBoss,			kBehaviorPrefix + 234)
DECLARE_PMID(kClassIDSpace, 		kViewZoomBhvrScriptProviderBoss,		kBehaviorPrefix + 235)

DECLARE_PMID(kClassIDSpace, 		kMoveBehaviorCmdBoss,					kBehaviorPrefix + 236)
DECLARE_PMID(kClassIDSpace, 		kNamedListHandlerBoss,					kBehaviorPrefix + 237)

DECLARE_PMID(kClassIDSpace, 		kFixupSoundActionCmdBoss,				kBehaviorPrefix + 238)

DECLARE_PMID(kClassIDSpace, 		kInCopyImportCopyHandlerBoss,			kBehaviorPrefix + 239)

	// More Action bosses...
	
DECLARE_PMID(kClassIDSpace, 		kCreateSoundActionCmdBoss,			kBehaviorPrefix + 240)
DECLARE_PMID(kClassIDSpace, 		kEditSoundActionCmdBoss,			kBehaviorPrefix + 241)
DECLARE_PMID(kClassIDSpace, 		kDeleteSoundBhvrCmdBoss,			kBehaviorPrefix + 242)
DECLARE_PMID(kClassIDSpace, 		kFixupSoundBhvrCmdBoss,				kBehaviorPrefix + 243)
DECLARE_PMID(kClassIDSpace, 		kSoundActionBoss,					kBehaviorPrefix + 244)
DECLARE_PMID(kClassIDSpace, 		kSoundActionFactoryBoss,			kBehaviorPrefix + 245)
DECLARE_PMID(kClassIDSpace, 		kSoundBhvrScriptProviderBoss,		kBehaviorPrefix + 246)

DECLARE_PMID(kClassIDSpace, 		kBehaviorConversionBoss,			kBehaviorPrefix + 247)
DECLARE_PMID(kClassIDSpace, 		kBehaviorPhase2ConversionBoss,		kBehaviorPrefix + 248)

DECLARE_PMID(kClassIDSpace, 		kPrintFormBehaviorBoss,				kBehaviorPrefix + 249)
DECLARE_PMID(kClassIDSpace, 		kCreatePrintFormBehaviorCmdBoss,	kBehaviorPrefix + 250)
DECLARE_PMID(kClassIDSpace, 		kDeletePrintFormBehaviorCmdBoss,	kBehaviorPrefix + 251)
DECLARE_PMID(kClassIDSpace, 		kPrintFormFactoryBoss,				kBehaviorPrefix + 252)
DECLARE_PMID(kClassIDSpace, 		kPrintFormBhvrScriptProviderBoss,	kBehaviorPrefix + 253)


// ----- Interface IDs -----

DECLARE_PMID(kInterfaceIDSpace, 	IID_IBEHAVIORLIST,					kBehaviorPrefix + 1) //GAP
DECLARE_PMID(kInterfaceIDSpace, 	IID_IGOTOVIEWACTIONDATA,			kBehaviorPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IBEHAVIORSUITE,					kBehaviorPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IBEHAVIOREVENTDATA,				kBehaviorPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, 	IID_ICOMMANDFACTORY,				kBehaviorPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IBEHAVIORDATA,					kBehaviorPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IBEHAVIOREVENT,					kBehaviorPrefix + 10) //GAP
DECLARE_PMID(kInterfaceIDSpace, 	IID_IACTIONSCHANGED_DOCUMENT,		kBehaviorPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IACTIONSADDED_DOCUMENT,			kBehaviorPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IACTIONSDELETED_DOCUMENT,		kBehaviorPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, 	IID_ISOUNDPAGEITEMLIST,				kBehaviorPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, 	IID_INAMEDPAGEITEMLIST,				kBehaviorPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IMOVIEPAGEITEMLIST,				kBehaviorPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IFORMPAGEITEMLIST,				kBehaviorPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, 	IID_INAMEDPAGEITEMLISTCMDDATA,		kBehaviorPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, 	IID_ISUPPORTEDEVENTS,				kBehaviorPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, 	IID_ISUPPORTEDEVENTSSERVICE,		kBehaviorPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, 	IID_PAGEITEMBEHAVIORXREF,			kBehaviorPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, 	IID_ICOPYBEHAVIORCMDDATA,			kBehaviorPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IFIXUPBEHAVIORCMDDATA,			kBehaviorPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IMOVEBEHAVIORDATA,				kBehaviorPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IACTIONSMOVED_DOCUMENT,			kBehaviorPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, 	IID_IACTIONSENABLED_DOCUMENT,		kBehaviorPrefix + 26)


// ----- Implementatin IDs -----

DECLARE_PMID(kImplementationIDSpace, kBehaviorListImpl, 				kBehaviorPrefix + 1) //GAP
DECLARE_PMID(kImplementationIDSpace, kBehaviorSuiteASBImpl, 			kBehaviorPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kBehaviorSuiteCSBImpl, 			kBehaviorPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kBehaviorEventDataImpl, 			kBehaviorPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kBehaviorCmdDataImpl, 				kBehaviorPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kDeleteBehaviorCmdImpl, 			kBehaviorPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kBehaviorEventProviderImpl, 			kBehaviorPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kBehaviorProviderImpl, 			kBehaviorPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kBehaviorSuiteCSBSelectionExtImpl,kBehaviorPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kBehaviorDocResponderImpl,			kBehaviorPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kBehaviorDocObserverImpl,			kBehaviorPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kNamedPageItemListImpl1,			kBehaviorPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kNamedPageItemListImpl2,			kBehaviorPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kAddToNamedPageItemListCmdImpl,	kBehaviorPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kRemoveFromNamedPageItemListCmdImpl,kBehaviorPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kNamedPageItemListCmdDataImpl,		kBehaviorPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kNamedPageItemListImpl3,			kBehaviorPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kDuplicateBehaviorCmdImpl,			kBehaviorPrefix + 19)

DECLARE_PMID(kImplementationIDSpace, kGoToFirstPageBehaviorDataImpl, 	kBehaviorPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kGoToFirstPageCmdFactoryImpl, 		kBehaviorPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kGoToLastPageCmdFactoryImpl, 		kBehaviorPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kGoToNextPageCmdFactoryImpl, 		kBehaviorPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kGoToPreviousPageCmdFactoryImpl, 	kBehaviorPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kGoToLastPageBehaviorDataImpl, 	kBehaviorPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kGoToNextPageBehaviorDataImpl, 	kBehaviorPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kGoToPreviousPageBehaviorDataImpl, kBehaviorPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kGoToPositionCmdFactoryImpl, 		kBehaviorPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kCreateGoToFirstPageBehaviorCmdImpl,kBehaviorPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kCreateGoToLastPageBehaviorCmdImpl,kBehaviorPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCreateGoToNextPageBehaviorCmdImpl,kBehaviorPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCreateGoToPreviousPageBehaviorCmdImpl,kBehaviorPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kEditGoToPositionBehaviorCmdImpl,	kBehaviorPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kGoToURLBehaviorDataImpl,			kBehaviorPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kCreateGoToURLBehaviorCmdImpl,		kBehaviorPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kEditGoToURLBehaviorCmdImpl,		kBehaviorPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kGoToURLCmdFactoryImpl, 			kBehaviorPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kGoToURLBhvrScriptProviderImpl, 	kBehaviorPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kGoToPosBhvrScriptProviderImpl, 	kBehaviorPrefix + 39)

DECLARE_PMID(kImplementationIDSpace, kCreateMovieActionCmdImpl, 		kBehaviorPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kEditMovieActionCmdImpl, 			kBehaviorPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kDeleteMovieBhvrCmdImpl,			kBehaviorPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kFixupMovieBhvrCmdImpl,			kBehaviorPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kMovieActionDataImpl, 				kBehaviorPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kMovieActionCmdFactoryImpl, 		kBehaviorPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kMovieBhvrScriptProviderImpl, 		kBehaviorPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kMovieBhvrDeleteCleanupImpl,		kBehaviorPrefix + 47)

DECLARE_PMID(kImplementationIDSpace, kCreateShowHideFieldActionCmdImpl, kBehaviorPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kEditShowHideFieldActionCmdImpl, 	kBehaviorPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kDeleteShowHideFieldBhvrCmdImpl,	kBehaviorPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kFixupShowHideFieldsBhvrCmdImpl,	kBehaviorPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kShowHideFieldActionDataImpl, 		kBehaviorPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kShowHideFieldActionCmdFactoryImpl, kBehaviorPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kShowHideBhvrScriptProviderImpl, 	kBehaviorPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kShowHideBhvrDeleteCleanupImpl,	kBehaviorPrefix + 55)

DECLARE_PMID(kImplementationIDSpace, kMouseEnterDataImpl, 				kBehaviorPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kMouseExitDataImpl, 				kBehaviorPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kMouseUpDataImpl, 					kBehaviorPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kMouseDownDataImpl, 				kBehaviorPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kOnBlurDataImpl, 					kBehaviorPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kOnFocusDataImpl, 					kBehaviorPrefix + 61)

DECLARE_PMID(kImplementationIDSpace, kPageOpenDataImpl,					kBehaviorPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kPageCloseDataImpl,				kBehaviorPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kValidateDataImpl,					kBehaviorPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kCalculateDataImpl,				kBehaviorPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kFormatDataImpl,					kBehaviorPrefix + 66) // format and/or keystroke ??? event in PDF
DECLARE_PMID(kImplementationIDSpace, kSignedDataImpl,					kBehaviorPrefix + 67) // format event in PDF
DECLARE_PMID(kImplementationIDSpace, kSelectionChangedDataImpl,			kBehaviorPrefix + 68) // keystroke event in PDF
DECLARE_PMID(kImplementationIDSpace, kKeystrokeDataImpl,				kBehaviorPrefix + 69)

DECLARE_PMID(kImplementationIDSpace, kDocumentOpenDataImpl,				kBehaviorPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kDocumentWillCloseDataImpl,		kBehaviorPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kDocumentWillSaveDataImpl,			kBehaviorPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kDocumentDidSaveDataImpl,			kBehaviorPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kDocumentWillPrintDataImpl,		kBehaviorPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kDocumentDidPrintDataImpl,			kBehaviorPrefix + 75)

DECLARE_PMID(kImplementationIDSpace, kGoToAnchorBhvrScriptProviderImpl, kBehaviorPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kAnimationBhvrScriptProviderImpl,	kBehaviorPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kMSOBhvrScriptProviderImpl,		kBehaviorPrefix + 78)

DECLARE_PMID(kImplementationIDSpace, kResetFormBehaviorDataImpl,		kBehaviorPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kCreateResetFormBehaviorCmdImpl,	kBehaviorPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kEditResetFormBehaviorCmdImpl,		kBehaviorPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kDeleteResetFormBhvrCmdImpl,		kBehaviorPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kResetFormBehaviorCmdFactoryImpl,	kBehaviorPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kResetFormBhvrScriptProviderImpl,	kBehaviorPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kResetFormBhvrDeleteCleanupImpl,	kBehaviorPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kFixupResetFormBhvrCmdImpl,		kBehaviorPrefix + 87)

DECLARE_PMID(kImplementationIDSpace, kSubmitFormBehaviorDataImpl,		kBehaviorPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kCreateSubmitFormBehaviorCmdImpl,	kBehaviorPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kEditSubmitFormBehaviorCmdImpl,	kBehaviorPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kDeleteSubmitFormBhvrCmdImpl,		kBehaviorPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kSubmitFormBehaviorCmdFactoryImpl,	kBehaviorPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kSubmitFormBhvrScriptProviderImpl,	kBehaviorPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kSubmitFormBhvrDeleteCleanupImpl,	kBehaviorPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kFixupSubmitFormBhvrCmdImpl,		kBehaviorPrefix + 97)

DECLARE_PMID(kImplementationIDSpace, kOpenFileBehaviorDataImpl,			kBehaviorPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kCreateOpenFileBehaviorCmdImpl,	kBehaviorPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kEditOpenFileBehaviorCmdImpl,		kBehaviorPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kOpenFileBehaviorCmdFactoryImpl,	kBehaviorPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kOpenFileBhvrScriptProviderImpl,	kBehaviorPrefix + 104)

DECLARE_PMID(kImplementationIDSpace, kAnimationActionCmdFactoryImpl,	kBehaviorPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kCreateAnimationBehaviorCmdImpl,	kBehaviorPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kEditAnimationBehaviorCmdImpl,		kBehaviorPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kAnimationBehaviorDataImpl,		kBehaviorPrefix + 108)

DECLARE_PMID(kImplementationIDSpace, kSwitchToMSOStateBehaviorDataImpl,	kBehaviorPrefix + 109)

DECLARE_PMID(kImplementationIDSpace, kCloseBehaviorDataImpl,			kBehaviorPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kCreateCloseBehaviorCmdImpl,		kBehaviorPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kEditCloseBehaviorCmdImpl,			kBehaviorPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kCloseBehaviorCmdFactoryImpl,		kBehaviorPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kCloseBhvrScriptProviderImpl,		kBehaviorPrefix + 114)

DECLARE_PMID(kImplementationIDSpace, kSwitchToMSOStateActionCmdFactoryImpl,			kBehaviorPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kCreateSwitchToMSOStateBehaviorCmdImpl,		kBehaviorPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kEditSwitchToMSOStateBehaviorCmdImpl,			kBehaviorPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kSwitchToNextMSOStateActionCmdFactoryImpl,		kBehaviorPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kCreateSwitchToNextMSOStateBehaviorCmdImpl,	kBehaviorPrefix + 119)

DECLARE_PMID(kImplementationIDSpace, kExitBehaviorDataImpl,				kBehaviorPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kCreateExitBehaviorCmdImpl,		kBehaviorPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kEditExitBehaviorCmdImpl,			kBehaviorPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kExitBehaviorCmdFactoryImpl,		kBehaviorPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kExitBhvrScriptProviderImpl,		kBehaviorPrefix + 124)

DECLARE_PMID(kImplementationIDSpace, kSwitchToNextMSOStateBehaviorDataImpl,			kBehaviorPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kEditSwitchToNextMSOStateBehaviorCmdImpl,		kBehaviorPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kSwitchToPrevMSOStateActionCmdFactoryImpl,		kBehaviorPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kSwitchToPrevMSOStateBehaviorDataImpl,			kBehaviorPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kCreateSwitchToPrevMSOStateBehaviorCmdImpl,	kBehaviorPrefix + 129)

DECLARE_PMID(kImplementationIDSpace, kJavaScriptBehaviorDataImpl,		kBehaviorPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kCreateJavaScriptBehaviorCmdImpl,	kBehaviorPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kEditJavaScriptBehaviorCmdImpl,	kBehaviorPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptBehaviorCmdFactoryImpl,	kBehaviorPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptBhvrScriptProviderImpl,	kBehaviorPrefix + 134)

DECLARE_PMID(kImplementationIDSpace, kFormulaBehaviorDataImpl,				kBehaviorPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kCreateFormulaBehaviorCmdImpl,			kBehaviorPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kEditFormulaBehaviorCmdImpl,			kBehaviorPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kFormulaBehaviorCmdFactoryImpl,		kBehaviorPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kFormulaBhvrScriptProviderImpl,		kBehaviorPrefix + 139)

DECLARE_PMID(kImplementationIDSpace, kValidateRangeBehaviorDataImpl,		kBehaviorPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kCreateValidateRangeBehaviorCmdImpl,	kBehaviorPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kEditValidateRangeBehaviorCmdImpl,		kBehaviorPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kValidateRangeBehaviorCmdFactoryImpl,	kBehaviorPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kValidateBhvrScriptProviderImpl,		kBehaviorPrefix + 144)

DECLARE_PMID(kImplementationIDSpace, kMarkReadOnlyBehaviorDataImpl,			kBehaviorPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kCreateMarkReadOnlyBehaviorCmdImpl,	kBehaviorPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kEditMarkReadOnlyBehaviorCmdImpl,		kBehaviorPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kMarkReadOnlyBehaviorCmdFactoryImpl,	kBehaviorPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kMarkReadOnlyBhvrScriptProviderImpl,	kBehaviorPrefix + 149)

DECLARE_PMID(kImplementationIDSpace, kFormatNumberBehaviorDataImpl,			kBehaviorPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kCreateFormatNumberBehaviorCmdImpl,	kBehaviorPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kEditFormatNumberBehaviorCmdImpl,		kBehaviorPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kFormatNumberBehaviorCmdFactoryImpl,	kBehaviorPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kFormatNumberBhvrScriptProviderImpl,	kBehaviorPrefix + 154)

DECLARE_PMID(kImplementationIDSpace, kFormatDateBehaviorDataImpl,			kBehaviorPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kCreateFormatDateBehaviorCmdImpl,		kBehaviorPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kEditFormatDateBehaviorCmdImpl,		kBehaviorPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kFormatDateBehaviorCmdFactoryImpl,		kBehaviorPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kFormatDateBhvrScriptProviderImpl,		kBehaviorPrefix + 159)

DECLARE_PMID(kImplementationIDSpace, kFormatPercentBehaviorDataImpl,		kBehaviorPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kCreateFormatPercentBehaviorCmdImpl,	kBehaviorPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kEditFormatPercentBehaviorCmdImpl,		kBehaviorPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kFormatPercentBehaviorCmdFactoryImpl,	kBehaviorPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kFormatPercentBhvrScriptProviderImpl,	kBehaviorPrefix + 164)

DECLARE_PMID(kImplementationIDSpace, kFormatTimeBehaviorDataImpl,			kBehaviorPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kCreateFormatTimeBehaviorCmdImpl,		kBehaviorPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kEditFormatTimeBehaviorCmdImpl,		kBehaviorPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kFormatTimeBehaviorCmdFactoryImpl,		kBehaviorPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kFormatTimeBhvrScriptProviderImpl,		kBehaviorPrefix + 169)

DECLARE_PMID(kImplementationIDSpace, kFormatSpecialBehaviorDataImpl,		kBehaviorPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kCreateFormatSpecialBehaviorCmdImpl,	kBehaviorPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kEditFormatSpecialBehaviorCmdImpl,		kBehaviorPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kFormatSpecialBehaviorCmdFactoryImpl,	kBehaviorPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kFormatSpecialBhvrScriptProviderImpl,	kBehaviorPrefix + 174)

DECLARE_PMID(kImplementationIDSpace, kEditSwitchToPrevMSOStateBehaviorCmdImpl,		kBehaviorPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kDeleteAnimationBhvrCmdImpl,					kBehaviorPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kFixupAnimationBhvrCmdImpl,					kBehaviorPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kDeleteSwitchMSOStateBhvrCmdImpl,				kBehaviorPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kFixupSwitchMSOStateBhvrCmdImpl,				kBehaviorPrefix + 179)

DECLARE_PMID(kImplementationIDSpace, kImportDataBehaviorDataImpl,			kBehaviorPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kCreateImportDataBehaviorCmdImpl,		kBehaviorPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kEditImportDataBehaviorCmdImpl,		kBehaviorPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kImportDataBehaviorCmdFactoryImpl,		kBehaviorPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kImportDataBhvrScriptProviderImpl, 	kBehaviorPrefix + 184)

DECLARE_PMID(kImplementationIDSpace, kAnimationAndMSOBhvrDeleteCleanupImpl,	kBehaviorPrefix + 185)

DECLARE_PMID(kImplementationIDSpace, kDefaultFieldSupportedEventsImpl,	kBehaviorPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kTextFieldSupportedEventsImpl,		kBehaviorPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kListBoxSupportedEventsImpl,		kBehaviorPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kComboBoxSupportedEventsImpl,		kBehaviorPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kSignatureSupportedEventsImpl,		kBehaviorPrefix + 204)

DECLARE_PMID(kImplementationIDSpace, kSupportedEventsProviderImpl, 		kBehaviorPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kStandardSupportedEventsImpl, 		kBehaviorPrefix + 206)

DECLARE_PMID(kImplementationIDSpace, kDefaultActionSupportedEventsImpl,	kBehaviorPrefix + 210)

DECLARE_PMID(kImplementationIDSpace, kAllEventsSupportedImpl,			kBehaviorPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kFormatEventsSupportedImpl,		kBehaviorPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kCalculateEventsSupportedImpl,		kBehaviorPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kValidateEventsSupportedImpl,		kBehaviorPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kSignedEventsSupportedImpl,		kBehaviorPrefix + 215)

DECLARE_PMID(kImplementationIDSpace, kDeleteAllBehaviorsCmdImpl,		kBehaviorPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kShowHideFieldDeleteTargetCmdImpl,	kBehaviorPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kGoToPageBehaviorDataImpl, 	kBehaviorPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kGoToPageCmdFactoryImpl, 		kBehaviorPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kCreateGoToPageBehaviorCmdImpl,kBehaviorPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kBehaviorScriptImpl,				kBehaviorPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kBehaviorScriptProviderImpl,		kBehaviorPrefix + 226)
//gap
DECLARE_PMID(kImplementationIDSpace, kBehaviorEventScriptDeletedImpl,	kBehaviorPrefix + 228)

DECLARE_PMID(kImplementationIDSpace, kGoToAnchorBehaviorDataImpl,		kBehaviorPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kGoToAnchorCmdFactoryImpl, 		kBehaviorPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kEditGoToAnchorBehaviorCmdImpl,	kBehaviorPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kCreateGoToAnchorBehaviorCmdImpl,	kBehaviorPrefix + 243)

DECLARE_PMID(kImplementationIDSpace, kBehaviorDeleteCleanupImpl,		kBehaviorPrefix + 250)
DECLARE_PMID(kImplementationIDSpace, kPageItemBehaviorXRefImpl,			kBehaviorPrefix + 251)
DECLARE_PMID(kImplementationIDSpace, kBehaviorReferenceConverterImpl,	kBehaviorPrefix + 252)
DECLARE_PMID(kImplementationIDSpace, kEnableBehaviorCmdImpl,			kBehaviorPrefix + 253)
DECLARE_PMID(kImplementationIDSpace, kCopyBehaviorCmdImpl,				kBehaviorPrefix + 254)

DECLARE_PMID(kImplementationIDSpace, kGoToPreviousViewBehaviorDataImpl,		kBehaviorPrefix + 255)
DECLARE_PMID(kImplementationIDSpace, kGoToPreviousViewCmdFactoryImpl, 		kBehaviorPrefix + 256)
DECLARE_PMID(kImplementationIDSpace, kEditGoToPreviousViewBehaviorCmdImpl,	kBehaviorPrefix + 257)
DECLARE_PMID(kImplementationIDSpace, kCreateGoToPreviousViewBehaviorCmdImpl,kBehaviorPrefix + 258)

DECLARE_PMID(kImplementationIDSpace, kGoToNextViewBehaviorDataImpl,		kBehaviorPrefix + 259)
DECLARE_PMID(kImplementationIDSpace, kGoToNextViewCmdFactoryImpl, 		kBehaviorPrefix + 260)
DECLARE_PMID(kImplementationIDSpace, kEditGoToNextViewBehaviorCmdImpl,	kBehaviorPrefix + 261)
DECLARE_PMID(kImplementationIDSpace, kCreateGoToNextViewBehaviorCmdImpl,kBehaviorPrefix + 262)

DECLARE_PMID(kImplementationIDSpace, kCopyBehaviorCmdDataImpl,			kBehaviorPrefix + 263)
DECLARE_PMID(kImplementationIDSpace, kAdoptBehaviorCmdImpl,				kBehaviorPrefix + 264)
DECLARE_PMID(kImplementationIDSpace, kFixupBehaviorCmdDataImpl,			kBehaviorPrefix + 265)

DECLARE_PMID(kImplementationIDSpace, kViewZoomBehaviorDataImpl,			kBehaviorPrefix + 266)
DECLARE_PMID(kImplementationIDSpace, kViewZoomCmdFactoryImpl, 			kBehaviorPrefix + 267)
DECLARE_PMID(kImplementationIDSpace, kEditViewZoomBehaviorCmdImpl,		kBehaviorPrefix + 268)
DECLARE_PMID(kImplementationIDSpace, kCreateViewZoomBehaviorCmdImpl,	kBehaviorPrefix + 269)
DECLARE_PMID(kImplementationIDSpace, kViewZoomBhvrScriptProviderImpl, 	kBehaviorPrefix + 270)

DECLARE_PMID(kImplementationIDSpace, kMoveBehaviorCmdImpl, 				kBehaviorPrefix + 271)

DECLARE_PMID(kImplementationIDSpace, kNamedListHandlerImpl, 			kBehaviorPrefix + 272)

DECLARE_PMID(kImplementationIDSpace, kInCopyImportCopyHandlerImpl, 		kBehaviorPrefix + 273)


DECLARE_PMID(kImplementationIDSpace, kCreateSoundActionCmdImpl, 		kBehaviorPrefix + 280)
DECLARE_PMID(kImplementationIDSpace, kEditSoundActionCmdImpl, 			kBehaviorPrefix + 281)
DECLARE_PMID(kImplementationIDSpace, kDeleteSoundBhvrCmdImpl,			kBehaviorPrefix + 282)
DECLARE_PMID(kImplementationIDSpace, kFixupSoundBhvrCmdImpl,			kBehaviorPrefix + 283)
DECLARE_PMID(kImplementationIDSpace, kSoundActionDataImpl, 				kBehaviorPrefix + 284)
DECLARE_PMID(kImplementationIDSpace, kSoundActionCmdFactoryImpl, 		kBehaviorPrefix + 285)
DECLARE_PMID(kImplementationIDSpace, kSoundBhvrScriptProviderImpl, 		kBehaviorPrefix + 286)
DECLARE_PMID(kImplementationIDSpace, kSoundBhvrDeleteCleanupImpl,		kBehaviorPrefix + 287)
DECLARE_PMID(kImplementationIDSpace, kBehaviorPhase2ConversionImpl,		kBehaviorPrefix + 288)

DECLARE_PMID(kImplementationIDSpace, kPrintFormBehaviorDataImpl,		kBehaviorPrefix + 289)
DECLARE_PMID(kImplementationIDSpace, kCreatePrintFormBehaviorCmdImpl,	kBehaviorPrefix + 290)
DECLARE_PMID(kImplementationIDSpace, kDeletePrintFormBhvrCmdImpl,		kBehaviorPrefix + 291)
DECLARE_PMID(kImplementationIDSpace, kPrintFormBehaviorCmdFactoryImpl,	kBehaviorPrefix + 292)
DECLARE_PMID(kImplementationIDSpace, kPrintFormBhvrScriptProviderImpl,	kBehaviorPrefix + 293)

// ----- Widget IDs -----

// ----- Action IDs -----

// ----- Service IDs -----

DECLARE_PMID(kServiceIDSpace,			kBehaviorEventService,				kBehaviorPrefix + 1)
DECLARE_PMID(kServiceIDSpace,			kBehaviorService,				kBehaviorPrefix + 2)
DECLARE_PMID(kServiceIDSpace,			kSupportedEventsService,		kBehaviorPrefix + 3)

// ----- Error IDs -----

DECLARE_PMID(kErrorIDSpace, kMoveActionPositionInvalidError,		kBehaviorPrefix + 1)

// ----- Behavior Event IDs (these include the all supported events for a PDF-style action)  -----

DECLARE_PMID(kBehaviorEventIDSpace, kNoEvt, 								kBehaviorPrefix + 0)
DECLARE_PMID(kBehaviorEventIDSpace, kAnyEvt, 								kBehaviorPrefix + 1)
DECLARE_PMID(kBehaviorEventIDSpace, kMouseDownEvt, 							kBehaviorPrefix + 2)
DECLARE_PMID(kBehaviorEventIDSpace, kMouseUpEvt, 							kBehaviorPrefix + 3)
DECLARE_PMID(kBehaviorEventIDSpace, kMouseEnterEvt, 						kBehaviorPrefix + 4)
DECLARE_PMID(kBehaviorEventIDSpace, kMouseExitEvt, 							kBehaviorPrefix + 5)
DECLARE_PMID(kBehaviorEventIDSpace, kOnBlurEvt, 							kBehaviorPrefix + 6)
DECLARE_PMID(kBehaviorEventIDSpace, kOnFocusEvt, 							kBehaviorPrefix + 7)

DECLARE_PMID(kBehaviorEventIDSpace, kPageOpenEvt,							kBehaviorPrefix + 8)
DECLARE_PMID(kBehaviorEventIDSpace, kPageCloseEvt,							kBehaviorPrefix + 9)
DECLARE_PMID(kBehaviorEventIDSpace, kValidateEvt,							kBehaviorPrefix + 10)
DECLARE_PMID(kBehaviorEventIDSpace, kCalculateEvt,							kBehaviorPrefix + 11)
DECLARE_PMID(kBehaviorEventIDSpace, kFormatEvt,								kBehaviorPrefix + 12) // format (and/or keystroke ???) event in PDF
DECLARE_PMID(kBehaviorEventIDSpace, kSignedEvt,								kBehaviorPrefix + 13) // format event in PDF
DECLARE_PMID(kBehaviorEventIDSpace, kSelectionChangedEvt,					kBehaviorPrefix + 14) // keystroke event in PDF
DECLARE_PMID(kBehaviorEventIDSpace, kKeystrokeEvt,							kBehaviorPrefix + 15)

DECLARE_PMID(kBehaviorEventIDSpace, kDocumentOpenEvt,						kBehaviorPrefix + 16)
DECLARE_PMID(kBehaviorEventIDSpace, kDocumentWillCloseEvt,					kBehaviorPrefix + 17)
DECLARE_PMID(kBehaviorEventIDSpace, kDocumentWillSaveEvt,					kBehaviorPrefix + 18)
DECLARE_PMID(kBehaviorEventIDSpace, kDocumentDidSaveEvt,					kBehaviorPrefix + 19)
DECLARE_PMID(kBehaviorEventIDSpace, kDocumentWillPrintEvt,					kBehaviorPrefix + 20)
DECLARE_PMID(kBehaviorEventIDSpace, kDocumentDidPrintEvt,					kBehaviorPrefix + 21)

DECLARE_PMID(kBehaviorEventIDSpace, kInvalidEvt, 							kBehaviorPrefix + 254)

// ----- Behavior IDs (these include the all supported PDF-style actions)  -----

DECLARE_PMID(kBehaviorIDSpace, kNoAction, 							kBehaviorPrefix + 0)
DECLARE_PMID(kBehaviorIDSpace, kGoToFirstPageBehavior, 				kBehaviorPrefix + 1)
DECLARE_PMID(kBehaviorIDSpace, kGoToLastPageBehavior, 				kBehaviorPrefix + 2)
DECLARE_PMID(kBehaviorIDSpace, kGoToNextPageBehavior, 				kBehaviorPrefix + 3)
DECLARE_PMID(kBehaviorIDSpace, kGoToPreviousPageBehavior, 			kBehaviorPrefix + 4)
DECLARE_PMID(kBehaviorIDSpace, kGoToURLBehavior, 					kBehaviorPrefix + 5)
DECLARE_PMID(kBehaviorIDSpace, kMovieBehavior, 						kBehaviorPrefix + 6)
DECLARE_PMID(kBehaviorIDSpace, kShowHideFieldsBehavior, 			kBehaviorPrefix + 7)
DECLARE_PMID(kBehaviorIDSpace, kImportDataBehavior, 				kBehaviorPrefix + 8)
DECLARE_PMID(kBehaviorIDSpace, kResetFormBehavior, 					kBehaviorPrefix + 9)
DECLARE_PMID(kBehaviorIDSpace, kSubmitFormBehavior, 				kBehaviorPrefix + 10)
DECLARE_PMID(kBehaviorIDSpace, kOpenFileBehavior, 					kBehaviorPrefix + 11)
DECLARE_PMID(kBehaviorIDSpace, kCloseBehavior, 						kBehaviorPrefix + 12)
DECLARE_PMID(kBehaviorIDSpace, kExitBehavior, 						kBehaviorPrefix + 13)
DECLARE_PMID(kBehaviorIDSpace, kJavaScriptBehavior, 				kBehaviorPrefix + 14)

DECLARE_PMID(kBehaviorIDSpace, kFormulaBehavior, 					kBehaviorPrefix + 15) // calculate action
DECLARE_PMID(kBehaviorIDSpace, kValidateRangeBehavior, 				kBehaviorPrefix + 16) // validate action
DECLARE_PMID(kBehaviorIDSpace, kMarkReadOnlyBehavior, 				kBehaviorPrefix + 17) // signed action

DECLARE_PMID(kBehaviorIDSpace, kFormatNumberBehavior, 				kBehaviorPrefix + 18) // format/keystroke actions...
DECLARE_PMID(kBehaviorIDSpace, kFormatDateBehavior, 				kBehaviorPrefix + 19) // (i.e. there are both format and
DECLARE_PMID(kBehaviorIDSpace, kFormatPercentBehavior, 				kBehaviorPrefix + 20) // keystroke actions associated with these.
DECLARE_PMID(kBehaviorIDSpace, kFormatTimeBehavior, 				kBehaviorPrefix + 21)
DECLARE_PMID(kBehaviorIDSpace, kFormatSpecialBehavior, 				kBehaviorPrefix + 22)

DECLARE_PMID(kBehaviorIDSpace, kGoToAnchorBehavior, 				kBehaviorPrefix + 23)

DECLARE_PMID(kBehaviorIDSpace, kGoToPreviousViewBehavior, 			kBehaviorPrefix + 24)
DECLARE_PMID(kBehaviorIDSpace, kGoToNextViewBehavior, 				kBehaviorPrefix + 25)

DECLARE_PMID(kBehaviorIDSpace, kViewZoomBehavior, 					kBehaviorPrefix + 26)

DECLARE_PMID(kBehaviorIDSpace, kSoundBehavior, 						kBehaviorPrefix + 27)
DECLARE_PMID(kBehaviorIDSpace, kGoToPageBehavior,					kBehaviorPrefix + 28)

DECLARE_PMID(kBehaviorIDSpace, kAnimationBehavior,					kBehaviorPrefix + 29)
DECLARE_PMID(kBehaviorIDSpace, kSwitchToMSOStateBehavior,			kBehaviorPrefix + 30)
DECLARE_PMID(kBehaviorIDSpace, kSwitchToNextMSOStateBehavior,		kBehaviorPrefix + 31)
DECLARE_PMID(kBehaviorIDSpace, kSwitchToPrevMSOStateBehavior,		kBehaviorPrefix + 32)
DECLARE_PMID(kBehaviorIDSpace, kPrintFormBehavior, 					kBehaviorPrefix + 33)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kBehaviorObjectScriptElement,						kBehaviorPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kGotoFirstPageBehaviorObjectScriptElement,			kBehaviorPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kGotoLastPageBehaviorObjectScriptElement,			kBehaviorPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kGotoNextPageBehaviorObjectScriptElement,			kBehaviorPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kGotoPreviousPageBehaviorObjectScriptElement,		kBehaviorPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kGotoNextViewBehaviorObjectScriptElement,			kBehaviorPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kGotoPreviousViewBehaviorObjectScriptElement,		kBehaviorPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kGotoURLBehaviorObjectScriptElement,				kBehaviorPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kMovieBehaviorObjectScriptElement,					kBehaviorPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kShowHideFieldsBehaviorObjectScriptElement,		kBehaviorPrefix + 29)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationBehaviorObjectScriptElement,				kBehaviorPrefix + 30)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kOpenFileBehaviorObjectScriptElement,				kBehaviorPrefix + 33)
DECLARE_PMID(kScriptInfoIDSpace, kCloseWindowBehaviorObjectScriptElement,			kBehaviorPrefix + 34)
DECLARE_PMID(kScriptInfoIDSpace, kQuitBehaviorObjectScriptElement,					kBehaviorPrefix + 35)
DECLARE_PMID(kScriptInfoIDSpace, kGoToNextStateBehaviorObjectScriptElement,			kBehaviorPrefix + 36)
DECLARE_PMID(kScriptInfoIDSpace, kGoToPreviousStateBehaviorObjectScriptElement,		kBehaviorPrefix + 37)
DECLARE_PMID(kScriptInfoIDSpace, kGoToStateBehaviorObjectScriptElement,				kBehaviorPrefix + 38)
DECLARE_PMID(kScriptInfoIDSpace, kGotoStateNamePropertyScriptElement,				kBehaviorPrefix + 39)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kViewZoomBehaviorObjectScriptElement,				kBehaviorPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kSoundBehaviorObjectScriptElement,					kBehaviorPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kGotoAnchorBehaviorObjectScriptElement,			kBehaviorPrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kGotoPageBehaviorObjectScriptElement,				kBehaviorPrefix + 48)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kBehaviorEventPropertyScriptElement,				kBehaviorPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kEventPropertyScriptElement,						kBehaviorPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kGotoZoomPropertyScriptElement,					kBehaviorPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kURLPropertyScriptElement,							kBehaviorPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kMoviePropertyScriptElement,						kBehaviorPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kOperationPropertyScriptElement,					kBehaviorPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kGoToPageNumberPropertyScriptElement,				kBehaviorPrefix + 164)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kSoundPropertyScriptElement,						kBehaviorPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kFieldsToHidePropertyScriptElement,				kBehaviorPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kFieldsToShowPropertyScriptElement,				kBehaviorPrefix + 169)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kViewZoomStylePropertyScriptElement,				kBehaviorPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kEnableBehaviorPropertyScriptElement,				kBehaviorPrefix + 189)
DECLARE_PMID(kScriptInfoIDSpace, kAnchorNamePropertyScriptElement,					kBehaviorPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kAnchorObjPropertyScriptElement,					kBehaviorPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationPropertyScriptElement,					kBehaviorPrefix + 192)
DECLARE_PMID(kScriptInfoIDSpace, kAutoReverseOnRollOffPropertyScriptElement,		kBehaviorPrefix + 193)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationOperationPropertyScriptElement,			kBehaviorPrefix + 194)
DECLARE_PMID(kScriptInfoIDSpace, kMSOPropertyScriptElement,							kBehaviorPrefix + 195)
DECLARE_PMID(kScriptInfoIDSpace, kGoBackOnRollOffPropertyScriptElement,				kBehaviorPrefix + 196)
DECLARE_PMID(kScriptInfoIDSpace, kLoopPropertyScriptElement,						kBehaviorPrefix + 197)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kEventEnumScriptElement,						kBehaviorPrefix + 239)
DECLARE_PMID(kScriptInfoIDSpace, kGoToZoomOptionsEnumScriptElement,				kBehaviorPrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kPlayOperationsEnumScriptElement,				kBehaviorPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kAnimationPlayOperationsEnumScriptElement,		kBehaviorPrefix + 242)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kViewZoomStyleEnumScriptElement,				kBehaviorPrefix + 247)
DECLARE_PMID(kScriptInfoIDSpace, kNavPointIDPropertyScriptElement,				kBehaviorPrefix + 248)

DECLARE_PMID(kScriptInfoIDSpace, kResetFormBehaviorObjectScriptElement,				kBehaviorPrefix + 249)
DECLARE_PMID(kScriptInfoIDSpace, kPrintFormBehaviorObjectScriptElement,				kBehaviorPrefix + 250)
DECLARE_PMID(kScriptInfoIDSpace, kSubmitFormBehaviorObjectScriptElement,				kBehaviorPrefix + 251)

enum BehaviorsScriptClasses 
{
	c_BehaviorsApplication =		'BAPP',
	
	c_Behavior =					'bhvr',
	c_Behaviors =					'bhvs',
	
	c_GoToPageBehavior =			'bgsp',
	c_GoToPageBehaviors =			'bgps',
	
	c_GoToFirstPageBehavior =		'bgfp',
	c_GoToFirstPageBehaviors =		'bgfs',
	
	c_GoToLastPageBehavior = 		'bglp',
	c_GoToLastPageBehaviors = 		'bgls',
	
	c_GoToNextPageBehavior = 		'bgnp',
	c_GoToNextPageBehaviors = 		'bgns',
	
	c_GoToPreviousPageBehavior = 	'pgpp',
	c_GoToPreviousPageBehaviors = 	'pgps',
	
	c_GoToNextViewBehavior = 		'bgnv',
	c_GoToNextViewBehaviors = 		'bnvs',
	
	c_GoToPreviousViewBehavior = 	'pgpv',
	c_GoToPreviousViewBehaviors = 	'ppvs',

	c_GoToURLBehavior = 			'bgur',
	c_GoToURLBehaviors = 			'bgus',

	c_GoToAnchorBehavior = 			'bgan',
	c_GoToAnchorBehaviors = 		'bgas',
	
	c_MovieBehavior = 				'bmov',
	c_MovieBehaviors = 				'bmos',

	c_SoundBehavior = 				'bsnd',
	c_SoundBehaviors = 				'bsns',
	
	c_ShowHideFieldsBehavior = 		'bshF',
	c_ShowHideFieldsBehaviors = 	'bshS',
	
	c_ImportDataBehavior = 			'bimd',
	c_ImportDataBehaviors = 		'bims',
	
	c_ResetFormBehavior = 			'bref',
	c_ResetFormBehaviors = 			'bres',
	
	c_SubmitFormBehavior = 			'bsuf',
	c_SubmitFormBehaviors = 		'bsus',
	
	c_OpenFileBehavior = 			'bopf',
	c_OpenFileBehaviors = 			'bops',
	
	c_CloseBehavior = 				'bclo',
	c_CloseBehaviors = 				'bcls',
	
	c_QuitBehavior = 				'bext',
	c_QuitBehaviors = 				'bexs',
	
	c_JavaScriptBehavior = 			'bjas',
	c_JavaScriptBehaviors = 		'bjss',
	
	c_FormulaBehavior = 			'frml',
	c_FormulaBehaviors = 			'frms',
	
	c_ValidateRangeBehavior = 		'vdrg',
	c_ValidateRangeBehaviors = 		'vdrs',
	
	c_MarkReadOnlyBehavior = 		'mron',
	c_MarkReadOnlyBehaviors = 		'mros',
	
	c_FormatNumberBehavior = 		'bfrn',
	c_FormatNumberBehaviors = 		'bfns',
	
	c_FormatDateBehavior = 			'fmdt',
	c_FormatDateBehaviors = 		'fmds',
	
	c_FormatPercentBehavior = 		'fmpc',
	c_FormatPercentBehaviors = 		'fmps',
	
	c_FormatTimeBehavior = 			'fmtm',
	c_FormatTimeBehaviors = 		'tmts',
	
	c_FormatSpecialBehavior = 		'fmsp',
	c_FormatSpecialBehaviors = 		'fmss',

	c_ViewZoomBehavior =			'vzom',
	c_ViewZoomBehaviors =			'vzms',

	c_AnimationBehavior = 			'aniB',
	c_AnimationBehaviors = 			'ansB',

	c_GoToNextStateBehavior = 		'gnxB',
	c_GoToNextStateBehaviors = 		'gnsB',

	c_GoToPreviousStateBehavior = 	'gprB',
	c_GoToPreviousStateBehaviors = 	'gpsB',

	c_GoToStateBehavior = 			'gstB',
	c_GoToStateBehaviors = 			'gssB',

	c_PrintFormBehavior =			'bpfm',
	c_PrintFormBehaviors =			'bpfs',

};

enum BehaviorsScriptProperties 
{
	p_Event = 						'evnt',	//obsoleted in Cobalt to avoid conflicting with c_Event
	p_BehaviorEvent = 				'Bevt',	//added in Cobalt to avoid conflicting with c_Event
	p_EnableBehavior = 				'enbh',
	p_GoToZoom = 					'gtzm',
	p_URL =							'gurl',
	p_AnchorName = 					'gaan',
	p_Anchor = 						'gaao',
	p_Movie =						'movi',
	p_Operation =					'oper',
	p_Sound =						'soun',
	p_FieldsToShow =				'ftos',
	p_FieldsToHide =				'ftoh',
	p_Fields =						'frst',
	p_FieldsToReset =				p_Fields,
	p_FormFormat = 					'bffm',
	p_IncludeFieldData = 			'bifd',
	p_IncludeComments = 			'bifc',
	p_ExportIncrementalChanges = 	'beic',
	p_IncludeEmptyFields = 			'bief',
	p_ConvertDatesToStandardFormat = 'bcdt',
	p_FieldsToSubmit = 				p_Fields,
	p_DecimalStyle = 				'bdes',
	p_CurrencySymbol = 				'bcur',
	p_NegativeStyle = 				'bnes',
	p_CurrencyPrepend = 			'bcpe',
	p_DateStyle = 					'bdst',
	p_TimeStyle = 					'btst',
	p_SpecialStyle = 				'bspc',
	p_LowerBound = 					'blwb',
	p_UpperBound = 					'bupb',
	p_FieldsToMarkReadOnly = 		p_Fields,
	p_Formula = 					'bfor',
	p_FieldsInFormula = 			p_Fields,
	p_ViewZoom =					'vzmp',
	p_JavaScript =					'jScr',
	p_LinkToFile =					'sLnk',
	p_ScriptName =					'sNam',
	p_Animation =					'anim',
	p_AutoReverseOnRollOff =		'aurv',
	p_MultiStateObject =			'gmso',
	p_GoBackOnRollOff =				'gbro',
	p_LoopToNextPrevState =			'gslp',
	p_GotoStateName =				'gtsn',
	p_NavigationPointID =			'npid'
};

enum BehaviorsScriptEnumerations 
{
	en_BehaviorEvents		= 'bhev',
	en_MouseUpEvent			= 'muev',
	en_MouseDownEvent		= 'mdev',
	en_MouseEnterEvent		= 'meev',
	en_MouseExitEvent		= 'mxev',
	en_OnFocusEvent			= 'ofev',
	en_OnBlurEvent			= 'obev',
	
	en_PlayOperations		= 'mvop',
	en_AnimationPlayOperations	= 'anop',
	en_MoviePlayOperations	= 'otop',
	en_Play					= 'play',
	en_PlayFromNavigationPoint	= 'plnv',
	en_Stop					= 'stop',
	en_Pause				= 'paus',
	en_Resume				= 'resu',
	en_Reverse				= 'reve',
	en_StopAll				= 'stpa',

	en_GoToZoomOptions		= 'zmop',
	
	en_SubmitFormFormatOptions = 'sffo',
	en_FDF					= 'sfdf',
	
	en_DecimalStyleOptions	= 'bdcs',
	en_CommaPeriod			= 'cmpe',
	en_NothingPeriod		= 'nope',
	en_PeriodComma			= 'pecm',
	en_NothingComma			= 'nocm',
	
	en_NegativeStyleOptions = 'negs',
	en_Minus				= 'minu',
	en_Parenthesized		= 'parn',
	en_RedParenthesized		= 'redp',
	
	en_TimeStyleOptions		= 'tist',
	en_24Hour				= '24  ',
	en_12Hour				= '12  ',
	en_24HourWithSeconds	= '24sc',
	en_12HourWithSeconds	= '12sc',
	
	en_SpecialStyleOptions	= 'spco',
	en_ZipCode				= 'zipc',
	en_ZipCodePlus4			= 'zipp',
	en_PhoneNumber			= 'phon',
	en_SocialSecurityNumber = 'ssn ',

	en_ViewZoomStyleOptions = 'vzst',
	en_ViewZoomFullScreen	= 'vzfs',
	en_ViewZoomReflow		= 'vzrf',
	en_ViewZoomSinglePage	= 'vzsp',
	en_ViewZoomOneColumn	= 'vzoc',
	en_ViewZoomTwoColumns	= 'vztc',
	en_ViewZoomRotateCW		= 'vzrc',
	en_ViewZoomRotateCCW	= 'vzrw'
};

#endif // __BehaviorID_h__
