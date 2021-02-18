//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/PackageAndPreflightID.h $
//  
//  Owner: Matt Phillips
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

#pragma once
#ifndef __PackageAndPreflightID__
#define __PackageAndPreflightID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPackageAndPreflightPlugIn_obsolete		RezLong(0x40C80)
#define kPackageAndPreflightPrefix		RezLong(0x13A00)

// PluginID
#define kPackageAndPreflightPlugInName			"Package and Preflight"
#define kPackageAndPreflightPlugInID_obsolete	kPackageAndPreflightPlugIn_obsolete + 1
#define kPackageAndPreflightPlugInID			kPackageAndPreflightPrefix + 1


//------------------------------------------------------------------------------------------------
//
// NOTE ON LEGACY VS CS4, PREFLIGHT VS INVENTORY TERMINOLOGY
//
// The IDs below represent both legacy package implementation and the new preflight implementation
// introduced in CS4. The legacy package behavior consisted of something called "preflight" which
// was a somewhat accurate term; what it really was, was "inventory" with a few specific checks
// added in. In CS4 we now call this "inventory" in the UI, but in the ID files we left the
// "preflight" term in place mainly to avoid making changes for change's sake. We have marked the
// specific IDs below that may be confusing with extra comments referring to this explanation.
//
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
// ClassIDs  (bosses)
//DECLARE_PMID(kClassIDSpace, kS4SPControlTestMenuBoss, kPackageAndPreflightPrefix + 1)	// moved to package and preflight_
DECLARE_PMID(kClassIDSpace, kS4SPControlBoss,							kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kClassIDSpace, kFontDescBoss_Obsolete,						kPackageAndPreflightPrefix + 3)
DECLARE_PMID(kClassIDSpace, kICCProfileDescBoss,						kPackageAndPreflightPrefix + 4)
DECLARE_PMID(kClassIDSpace, kInkDescBoss,								kPackageAndPreflightPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPrintSettingsDescBoss,						kPackageAndPreflightPrefix + 6)
DECLARE_PMID(kClassIDSpace, kLinkDescBoss,								kPackageAndPreflightPrefix + 7)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kClassIDSpace, kPreflightAPIBoss,							kPackageAndPreflightPrefix + 8)
DECLARE_PMID(kClassIDSpace, kPackageAPIBoss,							kPackageAndPreflightPrefix + 9)
DECLARE_PMID(kClassIDSpace, kJobTicketBoss_Obsolete,					kPackageAndPreflightPrefix + 10)
DECLARE_PMID(kClassIDSpace, kS4SPPackageReportBoss,						kPackageAndPreflightPrefix + 11)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kClassIDSpace, kS4SPPreflightReportBoss,					kPackageAndPreflightPrefix + 12)
//gap
DECLARE_PMID(kClassIDSpace, kS4SPConversionProviderBoss_obsolete,		kPackageAndPreflightPrefix + 14)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kClassIDSpace, kPreflightBookAPIBoss,						kPackageAndPreflightPrefix + 15)
DECLARE_PMID(kClassIDSpace, kPackageBookAPIBoss,						kPackageAndPreflightPrefix + 16)
DECLARE_PMID(kClassIDSpace, kPackageConversionProviderBoss,				kPackageAndPreflightPrefix + 17)
DECLARE_PMID(kClassIDSpace, kDocAddOnScriptBoss,						kPackageAndPreflightPrefix + 18)

// Basil Preflighting classes
DECLARE_PMID(kClassIDSpace, kPreflightNativeRuleBoss,					kPackageAndPreflightPrefix + 19)
DECLARE_PMID(kClassIDSpace, kPreflightProfileBoss,						kPackageAndPreflightPrefix + 20)
DECLARE_PMID(kClassIDSpace, kPreflightProcessBoss,						kPackageAndPreflightPrefix + 21)
DECLARE_PMID(kClassIDSpace, kPreflightRuleBaseBoss,						kPackageAndPreflightPrefix + 22)
DECLARE_PMID(kClassIDSpace, kPreflightNativeRuleSPBoss,					kPackageAndPreflightPrefix + 24)
DECLARE_PMID(kClassIDSpace, kPreflightObjectModelSPBoss,				kPackageAndPreflightPrefix + 25)
DECLARE_PMID(kClassIDSpace, kPreflightScriptBasedRuleSPBoss,			kPackageAndPreflightPrefix + 26)
DECLARE_PMID(kClassIDSpace, kPreflightProfileScriptProviderBoss,		kPackageAndPreflightPrefix + 27)
DECLARE_PMID(kClassIDSpace, kPreflightStartupServiceBoss,				kPackageAndPreflightPrefix + 28)

//	Basil script-based rule and scripting related classes
DECLARE_PMID(kClassIDSpace, kPreflightScriptRuleSPBoss,					kPackageAndPreflightPrefix + 30)
DECLARE_PMID(kClassIDSpace, kPreflightRuleScriptObjectBoss,				kPackageAndPreflightPrefix + 31)
DECLARE_PMID(kClassIDSpace, kPreflightScriptRuleInstanceObjectBoss,		kPackageAndPreflightPrefix + 32)
DECLARE_PMID(kClassIDSpace, kPreflightRuleScriptProviderBoss,			kPackageAndPreflightPrefix + 33)
DECLARE_PMID(kClassIDSpace, kPreflightRuleInstanceScriptProviderBoss,	kPackageAndPreflightPrefix + 34)
DECLARE_PMID(kClassIDSpace, kPreflightRuleDataScriptObjectBoss,			kPackageAndPreflightPrefix + 35)

DECLARE_PMID(kClassIDSpace, kPreflightProcessScriptProviderBoss,		kPackageAndPreflightPrefix + 36)
//OBSOLETE: DECLARE_PMID(kClassIDSpace, kPreflightProcessTaskBoss,					kPackageAndPreflightPrefix + 37)
//OBSOLETE: DECLARE_PMID(kClassIDSpace, kPreflightProcessTaskScriptProviderBoss,	kPackageAndPreflightPrefix + 38)
DECLARE_PMID(kClassIDSpace, kPreflightRuleDataScriptProviderBoss,		kPackageAndPreflightPrefix + 39)
DECLARE_PMID(kClassIDSpace, kPreflightRuleResultScriptBoss,				kPackageAndPreflightPrefix + 40)
DECLARE_PMID(kClassIDSpace, kPreflightRuleResultScriptProviderBoss,		kPackageAndPreflightPrefix + 41)

DECLARE_PMID(kClassIDSpace, kNewPreflightProfileCmdBoss,				kPackageAndPreflightPrefix + 42)
DECLARE_PMID(kClassIDSpace, kAddProfileRuleCmdBoss,						kPackageAndPreflightPrefix + 43)
DECLARE_PMID(kClassIDSpace, kRemoveProfileRuleCmdBoss,					kPackageAndPreflightPrefix + 44)
DECLARE_PMID(kClassIDSpace, kChangeProfileRuleDataCmdBoss,				kPackageAndPreflightPrefix + 45)
//OBSOLETE (use kUpdatePreflightProfileCmdBoss) DECLARE_PMID(kClassIDSpace, kSetPreflightProfileNameCmdBoss,			kPackageAndPreflightPrefix + 46)
DECLARE_PMID(kClassIDSpace, kDeletePreflightProfileCmdBoss,				kPackageAndPreflightPrefix + 47)
DECLARE_PMID(kClassIDSpace, kChangeProfileRuleInfoCmdBoss,				kPackageAndPreflightPrefix + 48)
DECLARE_PMID(kClassIDSpace, kPreflightViewPortBoss,						kPackageAndPreflightPrefix + 49)
DECLARE_PMID(kClassIDSpace, kPreflightApplicationScriptProviderBoss,	kPackageAndPreflightPrefix + 50)
DECLARE_PMID(kClassIDSpace, kPreflightAGMObjectModelSPBoss,				kPackageAndPreflightPrefix + 51)
DECLARE_PMID(kClassIDSpace, kPreflightAGMDrwEvtServiceBoss,				kPackageAndPreflightPrefix + 52)
DECLARE_PMID(kClassIDSpace, kPreflightNewDocResponderBoss,				kPackageAndPreflightPrefix + 53)
DECLARE_PMID(kClassIDSpace, kPreflightProcessProxyScriptBoss,			kPackageAndPreflightPrefix + 54)
//OBSOLETE: DECLARE_PMID(kClassIDSpace, kPreflightProcessTaskProxyScriptBoss,		kPackageAndPreflightPrefix + 55)
DECLARE_PMID(kClassIDSpace, kDuplicatePreflightProfileCmdBoss,			kPackageAndPreflightPrefix + 56)
DECLARE_PMID(kClassIDSpace, kUpdatePreflightProfileCmdBoss,				kPackageAndPreflightPrefix + 57)
DECLARE_PMID(kClassIDSpace, kEmbedPreflightProfileCmdBoss,				kPackageAndPreflightPrefix + 58)
DECLARE_PMID(kClassIDSpace, kPreflightErrorStringServiceBoss,			kPackageAndPreflightPrefix + 59)
DECLARE_PMID(kClassIDSpace, kSetPreflightOptionsCmdBoss,				kPackageAndPreflightPrefix + 60)
DECLARE_PMID(kClassIDSpace, kPreflightOptionsScriptProviderBoss,		kPackageAndPreflightPrefix + 61)
DECLARE_PMID(kClassIDSpace, kUpdatePreflightProfileAllRulesDataCmdBoss,	kPackageAndPreflightPrefix + 62)
DECLARE_PMID(kClassIDSpace, kPreflightAggregatedResultsBoss,			kPackageAndPreflightPrefix + 63)
DECLARE_PMID(kClassIDSpace, kPreflightNonPrintDrwEvtServiceBoss,		kPackageAndPreflightPrefix + 64)
DECLARE_PMID(kClassIDSpace, kPreflightNewWSResponderBoss,				kPackageAndPreflightPrefix + 65)
DECLARE_PMID(kClassIDSpace, kPreflightBookBoss,							kPackageAndPreflightPrefix + 66)
DECLARE_PMID(kClassIDSpace, kPreflightBookContentBoss,					kPackageAndPreflightPrefix + 67)
DECLARE_PMID(kClassIDSpace, kSetPreflightBookOptionsCmdBoss,			kPackageAndPreflightPrefix + 68)
DECLARE_PMID(kClassIDSpace, kPreflightOptionsTempBoss,					kPackageAndPreflightPrefix + 69)
DECLARE_PMID(kClassIDSpace, kPreflightBookOptionsTempBoss,				kPackageAndPreflightPrefix + 70)
DECLARE_PMID(kClassIDSpace, kPreflightOpenDocResponderBoss,				kPackageAndPreflightPrefix + 71)
DECLARE_PMID(kClassIDSpace, kUpdateActivePreflightOptionsCmdBoss,		kPackageAndPreflightPrefix + 72)
DECLARE_PMID(kClassIDSpace, kPreflightProfileExportPolicyBoss,			kPackageAndPreflightPrefix + 73)
DECLARE_PMID(kClassIDSpace, kPreflightProfileImportPolicyBoss,			kPackageAndPreflightPrefix + 74)
DECLARE_PMID(kClassIDSpace, kPreflightProfileImportValidationBoss,		kPackageAndPreflightPrefix + 75)
DECLARE_PMID(kClassIDSpace, kPreflightProfileTempBoss,					kPackageAndPreflightPrefix + 76)
DECLARE_PMID(kClassIDSpace, kDuplicatePreflightProfileCmd_PreNotify,	kPackageAndPreflightPrefix + 77)
DECLARE_PMID(kClassIDSpace, kDeletePreflightProfileCmd_PostNotify,		kPackageAndPreflightPrefix + 78)
DECLARE_PMID(kClassIDSpace, kNewPreflightProfileCmd_PreNotify,			kPackageAndPreflightPrefix + 79)
DECLARE_PMID(kClassIDSpace, kPreflightArtworkMarkBoss,					kPackageAndPreflightPrefix + 80)
DECLARE_PMID(kClassIDSpace, kPreflightArtworkGroupBoss,					kPackageAndPreflightPrefix + 81)
DECLARE_PMID(kClassIDSpace, kPreflightArtworkContextBoss,				kPackageAndPreflightPrefix + 82)
DECLARE_PMID(kClassIDSpace, kPreflightArtworkPaintInfoBoss,				kPackageAndPreflightPrefix + 83)
DECLARE_PMID(kClassIDSpace, kPreflightArtworkCSInfoBoss,				kPackageAndPreflightPrefix + 84)
DECLARE_PMID(kClassIDSpace, kPreflightArtworkImageBoss,					kPackageAndPreflightPrefix + 85)
DECLARE_PMID(kClassIDSpace, kPreflightObjectBoss,						kPackageAndPreflightPrefix + 86)
DECLARE_PMID(kClassIDSpace, kPreflightTextRangeBoss,					kPackageAndPreflightPrefix + 87)
DECLARE_PMID(kClassIDSpace, kPreflightWaxInfoBoss,						kPackageAndPreflightPrefix + 88)
DECLARE_PMID(kClassIDSpace, kPreflightTableCellBoss,					kPackageAndPreflightPrefix + 89)
// DECLARE_PMID(kClassIDSpace, kPreflightTextParcelBoss,					kPackageAndPreflightPrefix + 90)
DECLARE_PMID(kClassIDSpace, kPreflightResultRecordBoss,					kPackageAndPreflightPrefix + 91)
DECLARE_PMID(kClassIDSpace, kPreflightResultRecordTableBoss,			kPackageAndPreflightPrefix + 92)
DECLARE_PMID(kClassIDSpace, kPreflightResultNodeBoss,					kPackageAndPreflightPrefix + 93)
DECLARE_PMID(kClassIDSpace, kPreflightSaveDocResponderBoss,				kPackageAndPreflightPrefix + 94)
DECLARE_PMID(kClassIDSpace, kPreflightSaveAsDocResponderBoss,			kPackageAndPreflightPrefix + 95)
DECLARE_PMID(kClassIDSpace, kPreflightPhase2ConversionBoss,				kPackageAndPreflightPrefix + 96)
DECLARE_PMID(kClassIDSpace, kPreflightAfterNewDocResponderBoss,			kPackageAndPreflightPrefix + 97)
DECLARE_PMID(kClassIDSpace, kPreflightAfterCloseDocResponderBoss,		kPackageAndPreflightPrefix + 99)

// Rule bosses
DECLARE_PMID(kClassIDSpace, kImageResolutionRuleBoss,					kPackageAndPreflightPrefix + 100)
DECLARE_PMID(kClassIDSpace, kWhiteOverprintRuleBoss,					kPackageAndPreflightPrefix + 101)
DECLARE_PMID(kClassIDSpace, kOversetTextRuleBoss,						kPackageAndPreflightPrefix + 102)
DECLARE_PMID(kClassIDSpace, kMissingModifiedGraphicsRuleBoss,			kPackageAndPreflightPrefix + 103)
DECLARE_PMID(kClassIDSpace, kStrokeRequirementsRuleBoss,				kPackageAndPreflightPrefix + 104)
DECLARE_PMID(kClassIDSpace, kSmallTextRuleBoss,							kPackageAndPreflightPrefix + 105)
DECLARE_PMID(kClassIDSpace, kTestingHelperRuleBoss_Unimplemented,		kPackageAndPreflightPrefix + 106)
DECLARE_PMID(kClassIDSpace, kBleedSlugRuleBoss,							kPackageAndPreflightPrefix + 107)
DECLARE_PMID(kClassIDSpace, kPageSizeOrientationRuleBoss,				kPackageAndPreflightPrefix + 108)
DECLARE_PMID(kClassIDSpace, kPageCountRuleBoss,							kPackageAndPreflightPrefix + 109)
DECLARE_PMID(kClassIDSpace, kColorspaceRuleBoss,						kPackageAndPreflightPrefix + 110)
DECLARE_PMID(kClassIDSpace, kSpotColorSetupRuleBoss,					kPackageAndPreflightPrefix + 111)
DECLARE_PMID(kClassIDSpace, kFontUsageRuleBoss,							kPackageAndPreflightPrefix + 112)
DECLARE_PMID(kClassIDSpace, kTextAndTransparencyRuleBoss_Unimplemented,	kPackageAndPreflightPrefix + 113)
DECLARE_PMID(kClassIDSpace, kScaledTypeRuleBoss,						kPackageAndPreflightPrefix + 114)
DECLARE_PMID(kClassIDSpace, kTransparencyUsageRuleBoss,					kPackageAndPreflightPrefix + 115)
DECLARE_PMID(kClassIDSpace, kImageColorManagementRuleBoss,				kPackageAndPreflightPrefix + 116)
DECLARE_PMID(kClassIDSpace, kImageCompressionRuleBoss_Unimplemented,	kPackageAndPreflightPrefix + 117)
DECLARE_PMID(kClassIDSpace, kOPIRuleBoss,								kPackageAndPreflightPrefix + 118)
DECLARE_PMID(kClassIDSpace, kInteractiveContentRuleBoss,				kPackageAndPreflightPrefix + 119)
DECLARE_PMID(kClassIDSpace, kPlacedPDFRuleBoss_Unimplemented,			kPackageAndPreflightPrefix + 120)
DECLARE_PMID(kClassIDSpace, kPlacedEPSRuleBoss_Unimplemented,			kPackageAndPreflightPrefix + 121)
DECLARE_PMID(kClassIDSpace, kRichBlackRuleBoss_Unimplemented,			kPackageAndPreflightPrefix + 122)
DECLARE_PMID(kClassIDSpace, kCMYPlatesRuleBoss,							kPackageAndPreflightPrefix + 123)
DECLARE_PMID(kClassIDSpace, kPlacedContentSpotRuleBoss_Unimplemented,	kPackageAndPreflightPrefix + 124)
DECLARE_PMID(kClassIDSpace, kDPOERuleBoss_Unimplemented,				kPackageAndPreflightPrefix + 125)
DECLARE_PMID(kClassIDSpace, kTransparencyBlendingRuleBoss,				kPackageAndPreflightPrefix + 126)
DECLARE_PMID(kClassIDSpace, kBlankPagesRuleBoss,						kPackageAndPreflightPrefix + 127)
DECLARE_PMID(kClassIDSpace, kMissingFontsRuleBoss,						kPackageAndPreflightPrefix + 128)
DECLARE_PMID(kClassIDSpace, kUnusedColorsRuleBoss_Unimplemented,		kPackageAndPreflightPrefix + 129)
DECLARE_PMID(kClassIDSpace, kBleedTrimHazardRuleBoss,					kPackageAndPreflightPrefix + 130)
DECLARE_PMID(kClassIDSpace, kConditionIndicatorsRuleBoss,				kPackageAndPreflightPrefix + 131)
DECLARE_PMID(kClassIDSpace, kTextOverridesRuleBoss,						kPackageAndPreflightPrefix + 132)
DECLARE_PMID(kClassIDSpace, kCrossReferencesRuleBoss,					kPackageAndPreflightPrefix + 133)
DECLARE_PMID(kClassIDSpace, kOverprintRuleBoss,							kPackageAndPreflightPrefix + 134)
DECLARE_PMID(kClassIDSpace, kRegistrationRuleBoss,						kPackageAndPreflightPrefix + 135)
DECLARE_PMID(kClassIDSpace, kLayerVisibilityRuleBoss,					kPackageAndPreflightPrefix + 136)
DECLARE_PMID(kClassIDSpace, kCompositionViolationsRuleBoss_Unimplemented,kPackageAndPreflightPrefix + 137)
DECLARE_PMID(kClassIDSpace, kMissingGlyphRuleBoss,						kPackageAndPreflightPrefix + 138)
DECLARE_PMID(kClassIDSpace, kScaledGraphicsRuleBoss,					kPackageAndPreflightPrefix + 139)
DECLARE_PMID(kClassIDSpace, kSpellCheckRuleBoss,						kPackageAndPreflightPrefix + 140)
DECLARE_PMID(kClassIDSpace, kHiddenPageItemRuleBoss,				    kPackageAndPreflightPrefix + 141)
DECLARE_PMID(kClassIDSpace, kTrackedChangeRuleBoss,				    kPackageAndPreflightPrefix + 142)
DECLARE_PMID(kClassIDSpace, kInaccessibleUrlLinkRuleBoss,				    kPackageAndPreflightPrefix + 143)
DECLARE_PMID(kClassIDSpace, kUnresolvedCaptionVariableRuleBoss,			kPackageAndPreflightPrefix + 144)
DECLARE_PMID(kClassIDSpace, kMultiPageSizesRuleBoss,				    kPackageAndPreflightPrefix + 145)
DECLARE_PMID(kClassIDSpace, kSpanColumnsRuleBoss,				    kPackageAndPreflightPrefix + 146)

// a few more to come, probably

// Boss class IDs continue here..
DECLARE_PMID(kClassIDSpace, kEmbedPreflightProfileCmd_PreNotify,		kPackageAndPreflightPrefix + 170)


// Messages (these are not bosses; they're used for subjects in nonpersistent changes).
// See IPreflightUtils to obtain the necessary subjects to observe.

// Meaning: A process timestamp was updated.
// Broadcast on: IPreflightUtils::QueryAppMessageSubject, IID_IPREFLIGHTPROCESSMANAGER
// changedBy: the IPreflightProcess being updated
DECLARE_PMID(kClassIDSpace, kPreflightProcessUpdateMsg,				kPackageAndPreflightPrefix + 210)

// Meaning: The list of processes was updated (additions/deletions)
// Broadcast on: IPreflightUtils::QueryAppMessageSubject, IID_IPREFLIGHTPROCESSMANAGER
// changedBy: nil
DECLARE_PMID(kClassIDSpace, kPreflightProcessListChangedMsg,		kPackageAndPreflightPrefix + 211)

// Meaning: Preflight was initiated/changed on a book.
// Broadcast on: book->ISubject, IID_IPREFLIGHTBOOKREF
// changedBy: nil
DECLARE_PMID(kClassIDSpace, kPreflightBookRefChangedMsg,			kPackageAndPreflightPrefix + 212)

// Meaning: The data in the book changed (status changes, new chapter shadows, deletions, etc).
// Broadcast on: IPreflightBookUtils::QueryActivePreflight->ISubject, IID_IPREFLIGHTBOOKDATA
// changedBy: nil
DECLARE_PMID(kClassIDSpace, kPreflightBookDataChangedMsg,			kPackageAndPreflightPrefix + 213)

// Meaning: The process changed from complete to incomplete or vice-versa.
// Broadcast on: IPreflightUtils::QueryAppMessageSubject, IID_IPREFLIGHTPROCESSMANAGER
// changedBy: the IPreflightProcess (in its new state)
DECLARE_PMID(kClassIDSpace, kPreflightProcessCompletionChangeMsg,	kPackageAndPreflightPrefix + 214)

// Meaning: The InvalHandler-backed observer saw a change and is rebroadcasting it. The message ID
//		indicates whether this is a first-time do, an undo, or a redo.
// Broadcast on: IPreflightUtils::QueryDocumentSubject, IID_IPREFLIGHTSETTINGSCHANGEINFO
// changedBy: IPreflightSettingsChangeInfo
DECLARE_PMID(kClassIDSpace, kPreflightSettingsChangeInfo_Do_Msg,	kPackageAndPreflightPrefix + 215)
DECLARE_PMID(kClassIDSpace, kPreflightSettingsChangeInfo_Undo_Msg,	kPackageAndPreflightPrefix + 216)
DECLARE_PMID(kClassIDSpace, kPreflightSettingsChangeInfo_Redo_Msg,	kPackageAndPreflightPrefix + 217)

// Meaning: The application has switched back in (ie has regained focus).
// Broadcast on: IPreflightUtils::QueryAppMessageSubject, IID_IPREFLIGHTEVENTWATCHER
// changedBy: nil
DECLARE_PMID(kClassIDSpace, kPreflightEventAppResumeMsg,			kPackageAndPreflightPrefix + 218)

DECLARE_PMID(kClassIDSpace, kPreflightFrameDamageMsg,				kPackageAndPreflightPrefix + 219)

// Selectors (CassIDs but not really; just unique IDs)
DECLARE_PMID(kClassIDSpace, kPreflightContinuousProcessSelectorID,	kPackageAndPreflightPrefix + 220)
DECLARE_PMID(kClassIDSpace, kPreflightBookProcessSelectorID,		kPackageAndPreflightPrefix + 221)

DECLARE_PMID(kClassIDSpace, kPreflightStartupSignalBoss,			kPackageAndPreflightPrefix + 222)

//------------------------------------------------------------------------------------------------
// InterfaceIDs

DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPREFS,						kPackageAndPreflightPrefix + 1 )
DECLARE_PMID(kInterfaceIDSpace,	IID_IFONTDESC,						kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,	IID_IICCPROFILEDESC,				kPackageAndPreflightPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,	IID_IINKDESC,						kPackageAndPreflightPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,	IID_IJOBTICKET,   	   				kPackageAndPreflightPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILINKDESC,   					kPackageAndPreflightPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace,	IID_IPRINTSETTINGSDESC,				kPackageAndPreflightPrefix + 7)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPREFLIGHTAPI,				kPackageAndPreflightPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPACKAGEAPI,				kPackageAndPreflightPrefix + 9)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPREFLIGHTDATA,				kPackageAndPreflightPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPACKAGEDATA,				kPackageAndPreflightPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPACKAGEREPORT,				kPackageAndPreflightPrefix + 12)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPREFLIGHTREPORT,			kPackageAndPreflightPrefix + 13)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPREFLIGHTBOOKDATA,			kPackageAndPreflightPrefix + 14)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPREFLIGHTBOOKAPI,			kPackageAndPreflightPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPACKAGEBOOKDATA,			kPackageAndPreflightPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPPACKAGEBOOKAPI,			kPackageAndPreflightPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace,	IID_IS4SPUTILS,						kPackageAndPreflightPrefix + 18)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kInterfaceIDSpace,	IID_IPREFLIGHTSRCDATA,				kPackageAndPreflightPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace,	IID_IENTIREBOOKEXPORT,				kPackageAndPreflightPrefix + 20)

//___________________________________________________________________________________
// Basil Preflighting IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRULEINFO,					kPackageAndPreflightPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRULEVISITOR,				kPackageAndPreflightPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTOPTIONS,					kPackageAndPreflightPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTPROFILE,					kPackageAndPreflightPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTPROFILERULES,				kPackageAndPreflightPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTMANAGER,					kPackageAndPreflightPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTPROFILELIST,				kPackageAndPreflightPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTPROCESS,					kPackageAndPreflightPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRULESERVICE,				kPackageAndPreflightPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTOBJECTMODELSERVICE,		kPackageAndPreflightPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTOBJECT,					kPackageAndPreflightPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRULEUTILITIES,			kPackageAndPreflightPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTPROFILEMANAGER,			kPackageAndPreflightPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTOBJECTMODEL,				kPackageAndPreflightPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTSCRIPTRULEUTILS,			kPackageAndPreflightPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTSCRIPTRULEINFO,			kPackageAndPreflightPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTSCRIPTRULEMANAGER,		kPackageAndPreflightPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRULEDATA,					kPackageAndPreflightPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRULERESULTDATA,			kPackageAndPreflightPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTPROCESSMANAGER,			kPackageAndPreflightPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTIDLETASK,					kPackageAndPreflightPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTPROFILEUTILS,				kPackageAndPreflightPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRULEMANAGER,				kPackageAndPreflightPrefix + 49)
// DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTNATIVERULEHANDLER,		kPackageAndPreflightPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTSCRIPTRULERESULTINFO,		kPackageAndPreflightPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTUTILS,					kPackageAndPreflightPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKGROUPINFO,			kPackageAndPreflightPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKMARKINFO,			kPackageAndPreflightPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTGLOBALOBSERVER,			kPackageAndPreflightPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTCONTENTOBSERVER,			kPackageAndPreflightPrefix + 56)
// DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTTEXTPARCELINFO,			kPackageAndPreflightPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTWAXINFO,					kPackageAndPreflightPrefix + 58)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTTABLECELLINFO,			kPackageAndPreflightPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTFACADE,					kPackageAndPreflightPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKSHAPECONTEXT,		kPackageAndPreflightPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKPAINTINFO,			kPackageAndPreflightPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKOPICONTEXT,		kPackageAndPreflightPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKCSINFO,			kPackageAndPreflightPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKTEXTCONTEXT,		kPackageAndPreflightPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKTABLECONTEXT,		kPackageAndPreflightPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTAGGREGATEDRESULTS,		kPackageAndPreflightPrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRESULTNODEINFO,			kPackageAndPreflightPrefix + 69)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTAGGREGATEDRESULTSEXPORT,	kPackageAndPreflightPrefix + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTBOOKOPTIONS,				kPackageAndPreflightPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTBOOKREF,					kPackageAndPreflightPrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTBOOKDATA,					kPackageAndPreflightPrefix + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTBOOKCONTENTDATA,			kPackageAndPreflightPrefix + 74)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTBOOKCONTROLLER,			kPackageAndPreflightPrefix + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTBOOKUTILS,				kPackageAndPreflightPrefix + 76)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATEPREFLIGHTPROFILECMDDATA,		kPackageAndPreflightPrefix + 77)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTSETTINGSCHANGEINFO,		kPackageAndPreflightPrefix + 78) // Note: Only used as a protocol for subject
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTAPPSETTINGSOBSERVER,		kPackageAndPreflightPrefix + 79)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTDOCSETTINGSOBSERVER,		kPackageAndPreflightPrefix + 80)
DECLARE_PMID(kInterfaceIDSpace, IID_IEMBEDPREFLIGHTPROFILECMDDATA,		kPackageAndPreflightPrefix + 81)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTDOCOBSERVER,				kPackageAndPreflightPrefix + 82)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEPREFLIGHTPROFILECMDDATA,		kPackageAndPreflightPrefix + 83)
DECLARE_PMID(kInterfaceIDSpace, IID_IDUPLICATEPREFLIGHTPROFILECMDDATA,	kPackageAndPreflightPrefix + 84)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWPREFLIGHTPROFILECMDDATA,		kPackageAndPreflightPrefix + 85)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTEVENTWATCHER,				kPackageAndPreflightPrefix + 86)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTAGGREGATEDRESULTSUTILS,	kPackageAndPreflightPrefix + 87)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRESULTRECORD,				kPackageAndPreflightPrefix + 88)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRESULTRECORDTABLE,		kPackageAndPreflightPrefix + 89)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTRESULTNODEDATA,			kPackageAndPreflightPrefix + 90)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTTEXTRANGEINFO,			kPackageAndPreflightPrefix + 91)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTOBJECTMODELUTILS,			kPackageAndPreflightPrefix + 92)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKNODEINFO,			kPackageAndPreflightPrefix + 93)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKIMAGE,				kPackageAndPreflightPrefix + 94)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKCONTEXT,			kPackageAndPreflightPrefix + 95)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTARTWORKTEXTINFO,			kPackageAndPreflightPrefix + 96)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTFRAMEDAMAGEMSG,			kPackageAndPreflightPrefix + 97) // Note: Only used as a protocol for subject
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTSPELLWATCHIDLETASK,		kPackageAndPreflightPrefix + 98)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTSPELLSTATE,				kPackageAndPreflightPrefix + 99)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREFLIGHTWAXADORNMENTINFO,			kPackageAndPreflightPrefix + 100)

//_______________________________________________________________________________________________
//	Message ID for non-persistent changes
//_______________________________________________________________________________________________
DECLARE_PMID(kMessageIDSpace, kDocumentActiveProfileChangedMessage,		kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kDocumentPreflightOnOffChangedMessage,	kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kMessageIDSpace, kDocumentPreflightScopeChangedMessage,	kPackageAndPreflightPrefix + 3)

//------------------------------------------------------------------------------------------------
// ImplementationIDs
//DECLARE_PMID(kImplementationIDSpace, kS4SPControlTestMenu,						kPackageAndPreflightPrefix + 1) 	// moved to package and preflight_
DECLARE_PMID(kImplementationIDSpace, kS4SPPrefs,									kPackageAndPreflightPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kFontDesc,            		kPackageAndPreflightPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kICCProfileDesc,   	     	kPackageAndPreflightPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kInkDesc,            		kPackageAndPreflightPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kJobTicket,   		     kPackageAndPreflightPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kLinkDesc,   	   	     	kPackageAndPreflightPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPrintSettingsDesc,         		kPackageAndPreflightPrefix + 8)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightAPI,         		kPackageAndPreflightPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageAPI,   	      		kPackageAndPreflightPrefix + 10)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightData,         		kPackageAndPreflightPrefix + 11 )
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageData,      kPackageAndPreflightPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kS4SPChangeObserver,         		kPackageAndPreflightPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageReport,   				kPackageAndPreflightPrefix + 14)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightReport,   			kPackageAndPreflightPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kDocAddOnScriptProvider,		kPackageAndPreflightPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kS4SPConversionProviderImpl_obsolete,   	kPackageAndPreflightPrefix + 17)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightBookData,         kPackageAndPreflightPrefix + 18 )
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightBookAPI,         kPackageAndPreflightPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageBookData,           		kPackageAndPreflightPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageBookAPI,   	      		kPackageAndPreflightPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kS4SPUtilsImpl,   	      		kPackageAndPreflightPrefix + 22)
// Note: This "preflight" ID is LEGACY preflight, aka Inventory; see note at top of file.
DECLARE_PMID(kImplementationIDSpace, kPreflightSrcDataImpl, 		kPackageAndPreflightPrefix + 23)

//______________________________________________________________________________________________
// Basil Preflighting implementations
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleInfoImpl,					kPackageAndPreflightPrefix + 24)
// DECLARE_PMID(kImplementationIDSpace, kPreflightNativeRuleVisitorImpl,			kPackageAndPreflightPrefix + 25)
//DECLARE_PMID(kImplementationIDSpace, kPreflightNativeRuleUIImpl,				kPackageAndPreflightPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileImpl,						kPackageAndPreflightPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileRulesImpl,				kPackageAndPreflightPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kPreflightManagerImpl,						kPackageAndPreflightPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileListImpl,					kPackageAndPreflightPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kPreflightProcessImpl,						kPackageAndPreflightPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleSPImpl,						kPackageAndPreflightPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kPreflightNativeRuleServiceImpl,			kPackageAndPreflightPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kPreflightObjectModelSPImpl,				kPackageAndPreflightPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kPreflightNativeObjectModelServiceImpl,	kPackageAndPreflightPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleUtilitiesImpl,				kPackageAndPreflightPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileManagerImpl,				kPackageAndPreflightPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kPreflightScriptBasedRuleServiceImpl,		kPackageAndPreflightPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPreflightErrorStringServiceImpl,			kPackageAndPreflightPrefix + 41)

DECLARE_PMID(kImplementationIDSpace, kPreflightObjectModelImpl,					kPackageAndPreflightPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleScriptUtilsImpl,				kPackageAndPreflightPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleScriptObjectImpl,			kPackageAndPreflightPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kPreflightScriptRuleInfoImpl,				kPackageAndPreflightPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kPreflightScriptRuleVisitorImpl,			kPackageAndPreflightPrefix + 47)
//DECLARE_PMID(kImplementationIDSpace, kPreflightScriptRuleUIImpl,				kPackageAndPreflightPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleScriptProviderImpl,			kPackageAndPreflightPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kPreflightScriptRuleManagerImpl,			kPackageAndPreflightPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleInstanceScriptObjectImpl,	kPackageAndPreflightPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleDataScriptImpl,				kPackageAndPreflightPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleDataScriptProviderImpl,		kPackageAndPreflightPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleInstanceScriptProviderImpl,	kPackageAndPreflightPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileScriptProviderImpl,		kPackageAndPreflightPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kPreflightProcessManagerImpl,				kPackageAndPreflightPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kPreflightIdleTaskImpl,					kPackageAndPreflightPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kPreflightStartupServiceImpl,				kPackageAndPreflightPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kPreflightStartupShutdownImpl,				kPackageAndPreflightPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileUtilsImpl,				kPackageAndPreflightPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kPreflightProcessScriptImpl,				kPackageAndPreflightPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kPreflightProcessScriptProviderImpl,		kPackageAndPreflightPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleManagerImpl,					kPackageAndPreflightPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileScriptImpl,				kPackageAndPreflightPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kMemoryPreflightProfileScriptImpl,			kPackageAndPreflightPrefix + 69)

DECLARE_PMID(kImplementationIDSpace, kPreflightRuleDataImpl,					kPackageAndPreflightPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleResultScriptImpl,			kPackageAndPreflightPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleResultScriptProviderImpl,	kPackageAndPreflightPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kPreflightScriptRuleResultInfoImpl,		kPackageAndPreflightPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kPreflightScriptRuleUtilitiesImpl,			kPackageAndPreflightPrefix + 74)

DECLARE_PMID(kImplementationIDSpace, kNewPreflightProfileCmdImpl,				kPackageAndPreflightPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kAddProfileRuleCmdImpl,					kPackageAndPreflightPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kRemoveProfileRuleCmdImpl,					kPackageAndPreflightPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kChangeProfileRuleDataCmdImpl,				kPackageAndPreflightPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kSetPreflightProfileNameCmdImpl,			kPackageAndPreflightPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kDeletePreflightProfileCmdImpl,			kPackageAndPreflightPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kChangeProfileRuleInfoCmdImpl,				kPackageAndPreflightPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kPreflightUtilsImpl,						kPackageAndPreflightPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kPreflightApplicationScriptProviderImpl,	kPackageAndPreflightPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kPreflightAGMObjectModelServiceImpl,		kPackageAndPreflightPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kPreflightAGMDrwEvtServiceImpl,			kPackageAndPreflightPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kPreflightAGMDrwEvtHandlerImpl,			kPackageAndPreflightPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kPreflightDocResponderImpl,				kPackageAndPreflightPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kPreflightGlobalObserverImpl,				kPackageAndPreflightPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kPreflightContentObserverImpl,				kPackageAndPreflightPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kDuplicatePreflightProfileCmdImpl,			kPackageAndPreflightPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kUpdatePreflightProfileCmdImpl,			kPackageAndPreflightPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kEmbedPreflightProfileCmdImpl,				kPackageAndPreflightPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kPreflightFacadeImpl,						kPackageAndPreflightPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkShapeContextImpl,			kPackageAndPreflightPrefix + 99)

// Rule implementations (keep these in a separate range for now)
DECLARE_PMID(kImplementationIDSpace, kImageResolutionRuleImpl,					kPackageAndPreflightPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kWhiteOverprintRuleImpl,					kPackageAndPreflightPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kOversetTextRuleImpl,						kPackageAndPreflightPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kMissingModifiedGraphicsRuleImpl,			kPackageAndPreflightPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kStrokeRequirementsRuleImpl,				kPackageAndPreflightPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kSmallTextRuleImpl,						kPackageAndPreflightPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kTestingHelperRuleImpl,					kPackageAndPreflightPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kBleedSlugRuleImpl,						kPackageAndPreflightPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kPageSizeOrientationRuleImpl,				kPackageAndPreflightPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kPageCountRuleImpl,						kPackageAndPreflightPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kColorspaceRuleImpl,						kPackageAndPreflightPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kSpotColorSetupRuleImpl,					kPackageAndPreflightPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kFontUsageRuleImpl,						kPackageAndPreflightPrefix + 112)
//DECLARE_PMID(kImplementationIDSpace, kTextAndTransparencyRuleImpl,			kPackageAndPreflightPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kScaledTypeRuleImpl,						kPackageAndPreflightPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kTransparencyUsageRuleImpl,				kPackageAndPreflightPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kImageColorManagementRuleImpl,				kPackageAndPreflightPrefix + 116)
//DECLARE_PMID(kImplementationIDSpace, kImageCompressionRuleImpl,				kPackageAndPreflightPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kOPIRuleImpl,								kPackageAndPreflightPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kInteractiveContentRuleImpl,				kPackageAndPreflightPrefix + 119)
//DECLARE_PMID(kImplementationIDSpace, kPlacedPDFRuleImpl,						kPackageAndPreflightPrefix + 120)
//DECLARE_PMID(kImplementationIDSpace, kPlacedEPSRuleImpl,						kPackageAndPreflightPrefix + 121)
//DECLARE_PMID(kImplementationIDSpace, kRichBlackRuleImpl,						kPackageAndPreflightPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kCMYPlatesRuleImpl,						kPackageAndPreflightPrefix + 123)
//DECLARE_PMID(kImplementationIDSpace, kPlacedContentSpotRuleImpl,				kPackageAndPreflightPrefix + 124)
//DECLARE_PMID(kImplementationIDSpace, kDPOERuleImpl,								kPackageAndPreflightPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kTransparencyBlendingRuleImpl,				kPackageAndPreflightPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kBlankPagesRuleImpl,						kPackageAndPreflightPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kMissingFontsRuleImpl,						kPackageAndPreflightPrefix + 128)
//DECLARE_PMID(kImplementationIDSpace, kUnusedColorsRuleImpl,						kPackageAndPreflightPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kBleedTrimHazardRuleImpl,					kPackageAndPreflightPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kConditionIndicatorsRuleImpl,				kPackageAndPreflightPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kTextOverridesRuleImpl,					kPackageAndPreflightPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kCrossReferencesRuleImpl,					kPackageAndPreflightPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kOverprintRuleImpl,						kPackageAndPreflightPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kRegistrationRuleImpl,						kPackageAndPreflightPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kLayerVisibilityRuleImpl,					kPackageAndPreflightPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kTrackedChangeRuleImpl,					kPackageAndPreflightPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kMissingGlyphRuleImpl,						kPackageAndPreflightPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kScaledGraphicsRuleImpl,					kPackageAndPreflightPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kSpellCheckRuleImpl,						kPackageAndPreflightPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kHiddenPageItemRuleImpl,					kPackageAndPreflightPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kInaccessibleUrlLinkRuleImpl,				kPackageAndPreflightPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kUnresolvedCaptionVariableRuleImpl,			kPackageAndPreflightPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kMultiPageSizesRuleImpl,					kPackageAndPreflightPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kSpanColumnsRuleImpl,					kPackageAndPreflightPrefix + 145)

// a few more to come, probably, so leave a nice gap here please

DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkOPIContextImpl,			kPackageAndPreflightPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kPreflightOptionsImpl,						kPackageAndPreflightPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kSetPreflightOptionsCmdImpl,				kPackageAndPreflightPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kPreflightOptionsScriptProviderImpl,		kPackageAndPreflightPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kUpdatePreflightProfileAllRulesDataCmdImpl,kPackageAndPreflightPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kPreflightAggregatedResultsImpl,			kPackageAndPreflightPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kPreflightAggregatedResultsExportImpl,		kPackageAndPreflightPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookOptionsImpl,					kPackageAndPreflightPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kPreflightNonPrintDrwEvtHandlerImpl,		kPackageAndPreflightPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kPreflightNonPrintDrwEvtServiceImpl,		kPackageAndPreflightPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kPreflightNewWSResponderImpl,				kPackageAndPreflightPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookRefImpl,						kPackageAndPreflightPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookDataImpl,					kPackageAndPreflightPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookContentDataImpl,				kPackageAndPreflightPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookControllerImpl,				kPackageAndPreflightPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kSetPreflightBookOptionsCmdImpl,			kPackageAndPreflightPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kDocPreflightOptionsImpl,					kPackageAndPreflightPrefix + 186)
//	Do not use ID 187. This was an implementation that was removed.
//	Will generate implemenation removed but no persist data if this is use for anything.
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileExportPolicyImpl,			kPackageAndPreflightPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileImportPolicyImpl,			kPackageAndPreflightPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kPreflightProfileImportValidationImpl,		kPackageAndPreflightPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookObserverImpl,				kPackageAndPreflightPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kPreflightBookUtilsImpl,					kPackageAndPreflightPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kUpdatePreflightProfileCmdDataImpl,		kPackageAndPreflightPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kPreflightAppSettingsObserverImpl,			kPackageAndPreflightPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kPreflightDocSettingsObserverImpl,			kPackageAndPreflightPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kEmbedPreflightProfileCmdDataImpl,			kPackageAndPreflightPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kPreflightDocObserverImpl,					kPackageAndPreflightPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kDeletePreflightProfileCmdDataImpl,		kPackageAndPreflightPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kDuplicatePreflightProfileCmdDataImpl,		kPackageAndPreflightPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kNewPreflightProfileCmdDataImpl,			kPackageAndPreflightPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kPreflightEventWatcherImpl,				kPackageAndPreflightPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kPreflightAggregatedResultsUtilsImpl,		kPackageAndPreflightPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kPreflightDynamicDocsContextImpl,			kPackageAndPreflightPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kPreflightObjectModelUtilsImpl,			kPackageAndPreflightPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkGroupInfoImpl,			kPackageAndPreflightPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkMarkInfoImpl,				kPackageAndPreflightPrefix + 206)
// DECLARE_PMID(kImplementationIDSpace, kPreflightTextParcelInfoImpl,				kPackageAndPreflightPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kPreflightWaxInfoImpl,						kPackageAndPreflightPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kPreflightTableCellInfoImpl,				kPackageAndPreflightPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkShapecontextImpl,			kPackageAndPreflightPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkPaintInfoImpl,			kPackageAndPreflightPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkCSInfoImpl,				kPackageAndPreflightPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkTextContextImpl,			kPackageAndPreflightPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkTableContextImpl,			kPackageAndPreflightPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kPreflightResultNodeInfoImpl,				kPackageAndPreflightPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kPreflightResultRecordImpl,				kPackageAndPreflightPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kPreflightResultRecordTableImpl,			kPackageAndPreflightPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kPreflightResultNodeDataImpl,				kPackageAndPreflightPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kPreflightTextRangeInfoImpl,				kPackageAndPreflightPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkNodeInfoImpl,				kPackageAndPreflightPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kPreflightObjectImpl,						kPackageAndPreflightPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkImageImpl,				kPackageAndPreflightPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkContextImpl,				kPackageAndPreflightPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kPreflightArtworkTextInfoImpl,				kPackageAndPreflightPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kPreflightPhase2ConversionImpl,			kPackageAndPreflightPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kPreflightSpellWatchIdleTaskImpl,			kPackageAndPreflightPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kPreflightSpellStateImpl,					kPackageAndPreflightPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kPreflightWaxAdornmentInfoImpl,			kPackageAndPreflightPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kBeforePackageDocSignalRespServiceImpl,	kPackageAndPreflightPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kAfterPackageDocSignalRespServiceImpl,		kPackageAndPreflightPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kBeforePackageBookSignalRespServiceImpl,	kPackageAndPreflightPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kAfterPackageBookSignalRespServiceImpl,	kPackageAndPreflightPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kBeforePackageBookDocSignalRespServiceImpl,kPackageAndPreflightPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kAfterPackageBookDocSignalRespServiceImpl, kPackageAndPreflightPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kPreflightStartupSignalRespServiceImpl,	kPackageAndPreflightPrefix + 236)

//------------------------------------------------------------------------------------------------
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kProgressBarUserPreflight,							kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kProgressBarUserNone,								kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kProgressBarUserPackage,							kPackageAndPreflightPrefix + 3)


//------------------------------------------------------------------------------------------------
// Service IDs
DECLARE_PMID(kServiceIDSpace, kBeforePackageDocSignalRespService,				kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kAfterPackageDocSignalRespService,				kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kBeforePackageBookSignalRespService,				kPackageAndPreflightPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kAfterPackageBookSignalRespService, 				kPackageAndPreflightPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kBeforeGeneratePackageReportDocSignalRespService,	kPackageAndPreflightPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kAfterGeneratePackageReportDocSignalRespService,	kPackageAndPreflightPrefix + 6)
DECLARE_PMID(kServiceIDSpace, kBeforeGeneratePackageReportBookSignalRespService,kPackageAndPreflightPrefix + 7)
DECLARE_PMID(kServiceIDSpace, kAfterGeneratePackageReportBookSignalRespService,	kPackageAndPreflightPrefix + 8)

// Basil Preflighting Service IDs
DECLARE_PMID(kServiceIDSpace, kPreflightRuleService,							kPackageAndPreflightPrefix + 9)
DECLARE_PMID(kServiceIDSpace, kPreflightObjectModelService,						kPackageAndPreflightPrefix + 10)

// New signals at the document level when packaging a book
DECLARE_PMID(kServiceIDSpace, kBeforePackageBookDocSignalRespService,			kPackageAndPreflightPrefix + 11)
DECLARE_PMID(kServiceIDSpace, kAfterPackageBookDocSignalRespService, 			kPackageAndPreflightPrefix + 12)

// Signal after preflight manager has finished startup up (including all other preflight managers)
DECLARE_PMID(kServiceIDSpace, kPreflightStartupSignalService,					kPackageAndPreflightPrefix + 13)

//__________________________________________________________________________________________________
//	Obsolete ClassIDs
//__________________________________________________________________________________________________
//DECLARE_PMID(kClassIDSpace, kS4SPControlTestMenuBoss_obsolete, kPackageAndPreflightPlugIn_obsolete + 1)
DECLARE_PMID(kClassIDSpace, kS4SPControlBoss_obsolete,							kPackageAndPreflightPlugIn_obsolete + 2)
DECLARE_PMID(kClassIDSpace, kFontDescBoss_obsolete,								kPackageAndPreflightPlugIn_obsolete + 3)
DECLARE_PMID(kClassIDSpace, kICCProfileDescBoss_obsolete,						kPackageAndPreflightPlugIn_obsolete + 4)
DECLARE_PMID(kClassIDSpace, kInkDescBoss_obsolete,								kPackageAndPreflightPlugIn_obsolete + 5)
DECLARE_PMID(kClassIDSpace, kPrintSettingsDescBoss_obsolete,					kPackageAndPreflightPlugIn_obsolete + 6)
DECLARE_PMID(kClassIDSpace, kLinkDescBoss_obsolete,								kPackageAndPreflightPlugIn_obsolete + 7)
DECLARE_PMID(kClassIDSpace, kPreflightAPIBoss_obsolete,							kPackageAndPreflightPlugIn_obsolete + 8)
DECLARE_PMID(kClassIDSpace, kPackageAPIBoss_obsolete,							kPackageAndPreflightPlugIn_obsolete + 9)
DECLARE_PMID(kClassIDSpace, kJobTicketBoss_obsolete,							kPackageAndPreflightPlugIn_obsolete + 10)
DECLARE_PMID(kClassIDSpace, kS4SPPackageReportBoss_obsolete,					kPackageAndPreflightPlugIn_obsolete + 11)
DECLARE_PMID(kClassIDSpace, kS4SPPreflightReportBoss_obsolete,					kPackageAndPreflightPlugIn_obsolete + 12)
//gap
DECLARE_PMID(kClassIDSpace, kPreflightBookAPIBoss_obsolete,						kPackageAndPreflightPlugIn_obsolete + 15)
DECLARE_PMID(kClassIDSpace, kPackageBookAPIBoss_obsolete,						kPackageAndPreflightPlugIn_obsolete + 16)
DECLARE_PMID(kClassIDSpace, kPackageConversionProviderBoss_obsolete,			kPackageAndPreflightPlugIn_obsolete + 17)


// Obsolete ImplementationIDs
//DECLARE_PMID(kImplementationIDSpace, kS4SPControlTestMenu_obsolete,			kPackageAndPreflightPlugIn_obsolete + 1)
DECLARE_PMID(kImplementationIDSpace, kS4SPPrefs_obsolete,						kPackageAndPreflightPlugIn_obsolete + 2 )
DECLARE_PMID(kImplementationIDSpace, kFontDesc_obsolete,            			kPackageAndPreflightPlugIn_obsolete + 3)
DECLARE_PMID(kImplementationIDSpace, kICCProfileDesc_obsolete,   	     		kPackageAndPreflightPlugIn_obsolete + 4)
DECLARE_PMID(kImplementationIDSpace, kInkDesc_obsolete,            				kPackageAndPreflightPlugIn_obsolete + 5)
DECLARE_PMID(kImplementationIDSpace, kJobTicket_obsolete,   					kPackageAndPreflightPlugIn_obsolete + 6)
DECLARE_PMID(kImplementationIDSpace, kLinkDesc_obsolete,   	   	     			kPackageAndPreflightPlugIn_obsolete + 7)
DECLARE_PMID(kImplementationIDSpace, kPrintSettingsDesc_obsolete,         		kPackageAndPreflightPlugIn_obsolete + 8)
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightAPI_obsolete,         		kPackageAndPreflightPlugIn_obsolete + 9)
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageAPI_obsolete,   	      		kPackageAndPreflightPlugIn_obsolete + 10)
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightData_obsolete,         		kPackageAndPreflightPlugIn_obsolete + 11 )
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageData_obsolete,					kPackageAndPreflightPlugIn_obsolete + 12)
DECLARE_PMID(kImplementationIDSpace, kS4SPChangeObserver_obsolete,         		kPackageAndPreflightPlugIn_obsolete + 13)
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageReport_obsolete,   			kPackageAndPreflightPlugIn_obsolete + 14)
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightReport_obsolete,   			kPackageAndPreflightPlugIn_obsolete + 15)
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightBookData_obsolete,			kPackageAndPreflightPlugIn_obsolete + 18 )
DECLARE_PMID(kImplementationIDSpace, kS4SPPreflightBookAPI_obsolete,			kPackageAndPreflightPlugIn_obsolete + 19)
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageBookData_obsolete,           	kPackageAndPreflightPlugIn_obsolete + 20)
DECLARE_PMID(kImplementationIDSpace, kS4SPPackageBookAPI_obsolete,   	      	kPackageAndPreflightPlugIn_obsolete + 21)
//__________________________________________________________________________________________________
//	End Obsolete definitions
//__________________________________________________________________________________________________

//_________________________________________________________________________
//	<Error ID>
//_________________________________________________________________________
// Error Codes
DECLARE_PMID(kErrorIDSpace, kCannotCreatePreflightProfileError,					kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kCannotCreatePreflightRuleError,					kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kPreflightRuleAlreadyExistInProfileError,			kPackageAndPreflightPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kPreflightRuleDoesnotExistInProfileError,			kPackageAndPreflightPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kProfileNameAlreadyExistsError,						kPackageAndPreflightPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kProfileNameBlankError,								kPackageAndPreflightPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kProfileNameInvalidError,							kPackageAndPreflightPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kDeletePresetProfileError,							kPackageAndPreflightPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kCannotEmbedProfileError,							kPackageAndPreflightPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kLoadProfileOpenDocError,							kPackageAndPreflightPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kLoadProfileActiveDocError,							kPackageAndPreflightPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kLoadProfileFailedError,							kPackageAndPreflightPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kLoadProfileNoEmbeddedProfileError,					kPackageAndPreflightPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kRenamePresetProfileError,							kPackageAndPreflightPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kAggregatedResultIsNotAvailableError,				kPackageAndPreflightPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kPreflightingIsOffForDocumentError,					kPackageAndPreflightPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kCannotEmbedDefaultProfileError,					kPackageAndPreflightPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kCannotEditDefaultProfileError,						kPackageAndPreflightPrefix + 18)


// Resource IDs
#define kPackageAndPreflightStringsID					230
#define kPackageAndPreflightStringsNoTransRsrcID		330
#define kPackageAndPreflightErrorStringTableRsrcID		340

//	Basil Preflight Script Element definitions
//	Script Element IDs
//

DECLARE_PMID(kScriptInfoIDSpace, kPreflightSuiteScriptElement,							kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleObjectScriptElement,						kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kScriptPreflightRuleObjectScriptElement,				kPackageAndPreflightPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleDataObjectScriptElement,					kPackageAndPreflightPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kCreateScriptPreflightRuleMethodScriptElement,			kPackageAndPreflightPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleIDPropertyScriptElement,					kPackageAndPreflightPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleObjectTypePropertyScriptElement,			kPackageAndPreflightPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleObjectTypeEnumScriptElement,				kPackageAndPreflightPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleAlertStatusPropertyScriptElement,		kPackageAndPreflightPrefix + 9)
//DECLARE_PMID(kScriptInfoIDSpace, gap,			kPackageAndPreflightPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleFullFeaturePropertyScriptElement,		kPackageAndPreflightPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightScriptRuleCheckFuncPropertyScriptElement,	kPackageAndPreflightPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightScriptRuleFixupFuncPropertyScriptElement,	kPackageAndPreflightPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightScriptRuleUIFuncPropertyScriptElement,		kPackageAndPreflightPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleAlertStatusEnumScriptElement,			kPackageAndPreflightPrefix + 15)
//DECLARE_PMID(kScriptInfoIDSpace, gap,		kPackageAndPreflightPrefix + 16)

DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleInstanceObjectScriptElement,				kPackageAndPreflightPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightScriptRuleInstanceObjectScriptElement,		kPackageAndPreflightPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kCreatePreflightRuleInstanceObjectMethodScriptElement,	kPackageAndPreflightPrefix + 19)
//DECLARE_PMID(kScriptInfoIDSpace, gap,			kPackageAndPreflightPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleResultPropertyScriptElement,				kPackageAndPreflightPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleResultCodePropertyScriptElement,			kPackageAndPreflightPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleVisitResultEnumScriptElement,			kPackageAndPreflightPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleResultDescriptionPropertyScriptElement,	kPackageAndPreflightPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightProfileObjectScriptElement,					kPackageAndPreflightPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kCreatePreflightProfileObjectMethodScriptElement,		kPackageAndPreflightPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightProcessScriptElement,						kPackageAndPreflightPrefix + 27)
//OBSOLETE: DECLARE_PMID(kScriptInfoIDSpace, kPreflightProcessTaskScriptElement,					kPackageAndPreflightPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kAddPreflightRuleMethodScriptElement,					kPackageAndPreflightPrefix + 29)
//DECLARE_PMID(kScriptInfoIDSpace, gap,			kPackageAndPreflightPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightProfileRuleObjectScriptElement,				kPackageAndPreflightPrefix + 31)

DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleDataTypeEnumScriptElement,				kPackageAndPreflightPrefix + 32)
DECLARE_PMID(kScriptInfoIDSpace, kRuleDataTypePropertyScriptElement,					kPackageAndPreflightPrefix + 33)
DECLARE_PMID(kScriptInfoIDSpace, kRuleDataValuePropertyScriptElement,					kPackageAndPreflightPrefix + 34)
DECLARE_PMID(kScriptInfoIDSpace, kAddPreflightRuleDataMethodScriptElement,				kPackageAndPreflightPrefix + 35)
DECLARE_PMID(kScriptInfoIDSpace, kMemoryPreflightProfileScriptElement,					kPackageAndPreflightPrefix + 36)
DECLARE_PMID(kScriptInfoIDSpace, kAddPreflightProcessMethodScriptElement,				kPackageAndPreflightPrefix + 37)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleResultScriptElement,						kPackageAndPreflightPrefix + 38)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightProcessTargetPropertyScriptElement,			kPackageAndPreflightPrefix + 39)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightProcessProfilePropertyScriptElement,			kPackageAndPreflightPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightAllClassesPropertySE,						kPackageAndPreflightPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightAllRuleCategoriesPropertySE,					kPackageAndPreflightPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightWaitForProcessEventSE,						kPackageAndPreflightPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightProcessResultsPropertySE,					kPackageAndPreflightPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightProcessInventoryPropertySE,					kPackageAndPreflightPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightAllRuleIDsPropertySE,						kPackageAndPreflightPrefix + 46)

DECLARE_PMID(kScriptInfoIDSpace, kPFOPreflightOptionsScriptElement,						kPackageAndPreflightPrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kPFOPreflightOptionsPropertyScriptElement,				kPackageAndPreflightPrefix + 48)
DECLARE_PMID(kScriptInfoIDSpace, kPFOScopeOptionsEnumScriptElement,						kPackageAndPreflightPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kPFOScopePropertyScriptElement,						kPackageAndPreflightPrefix + 49)
DECLARE_PMID(kScriptInfoIDSpace, kPFOScopePageRangeScriptElement,						kPackageAndPreflightPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kPFOIncludeLayerEnumScriptElement,						kPackageAndPreflightPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kPFOIncludeLayerPropertyScriptElement,					kPackageAndPreflightPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kPFOIncludeObjsOnPBPropertyScriptElement,				kPackageAndPreflightPrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kPFOIncludeNonPrintPropertyScriptElement,				kPackageAndPreflightPrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kPFOPreflightOffPropertyScriptElement,					kPackageAndPreflightPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kPFOProfilePolicyEnumScriptElement,					kPackageAndPreflightPrefix + 57)
DECLARE_PMID(kScriptInfoIDSpace, kPFOProfilePolicyPropertyScriptElement,				kPackageAndPreflightPrefix + 58)
DECLARE_PMID(kScriptInfoIDSpace, kPFOProfilePolicyProfilePropertyScriptElement,			kPackageAndPreflightPrefix + 59)

DECLARE_PMID(kScriptInfoIDSpace, kPreflightEmbedProfileMethodScriptElement,				kPackageAndPreflightPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightUnembedProfileMethodScriptElement,			kPackageAndPreflightPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightUpdateProfileMethodScriptElement,				kPackageAndPreflightPrefix + 62)

DECLARE_PMID(kScriptInfoIDSpace, kPFOProfileEmbedInNewDocumentPropertyScriptElement,	kPackageAndPreflightPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kPFOProfilePolicyWorkingProfilePropertyScriptElement,	kPackageAndPreflightPrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kLoadPreflightProfileMethodScriptElement,				kPackageAndPreflightPrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kSavePreflightProfileMethodScriptElement,				kPackageAndPreflightPrefix + 66)

DECLARE_PMID(kScriptInfoIDSpace, kPFOPreflightBookOptionsScriptElement,					kPackageAndPreflightPrefix + 67)
DECLARE_PMID(kScriptInfoIDSpace, kPFOPreflightBookOptionsPropertyScriptElement,			kPackageAndPreflightPrefix + 68)

DECLARE_PMID(kScriptInfoIDSpace, kDocumentActiveProcessPropertySE,						kPackageAndPreflightPrefix + 69)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightErrorNodeTypeDefScriptElement,				kPackageAndPreflightPrefix + 70)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightResultsTypeDefScriptElement,					kPackageAndPreflightPrefix + 71)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightProcessAggregatedResultPropertySE,			kPackageAndPreflightPrefix + 72)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightErrorInfoTypeDefScriptElement,				kPackageAndPreflightPrefix + 73)
DECLARE_PMID(kScriptInfoIDSpace, kSavePreflightReportMethodScriptElement,				kPackageAndPreflightPrefix + 74)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightBookMethodScriptElement,						kPackageAndPreflightPrefix + 75)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightBookContentMethodScriptElement,				kPackageAndPreflightPrefix + 76)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleDataIDPropertyScriptElement,				kPackageAndPreflightPrefix + 77)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleDataListBaseTypeDefScriptElement,		kPackageAndPreflightPrefix + 78)
DECLARE_PMID(kScriptInfoIDSpace, kPreflightRuleDataListTypeDefScriptElement,			kPackageAndPreflightPrefix + 79)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kPackageMethodScriptElement,							kPackageAndPreflightPrefix + 80)

#ifdef DEBUG
DECLARE_PMID(kScriptInfoIDSpace, kDebugOnlyVisitPreflightRuleMethodScriptElement,		kPackageAndPreflightPrefix + 255)
#endif

// Viewport attributes
DECLARE_PMID(kViewPortAttrIDSpace, kIsPreflightAGMCapturePortVPAttr,	kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kViewPortAttrIDSpace, kPreflightIssuePortGroupsVPAttr,		kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kViewPortAttrIDSpace, kPreflightSuppressNonprintingVPAttr,	kPackageAndPreflightPrefix + 3)
DECLARE_PMID(kViewPortAttrIDSpace, kIsPreflightIteratorPortVPAttr,		kPackageAndPreflightPrefix + 4)

// Inval handlers
DECLARE_PMID(kInvalHandlerIDSpace, kPreflightContentInvalHandlerID,			kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kInvalHandlerIDSpace, kPreflightSettingsInvalHandlerID,		kPackageAndPreflightPrefix + 2)

// Object Model Class IDs
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Book,					kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Document,				kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Spread,				kPackageAndPreflightPrefix + 3)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Page,					kPackageAndPreflightPrefix + 4)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_DocumentLayer,			kPackageAndPreflightPrefix + 5)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_PageItem,				kPackageAndPreflightPrefix + 6)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Graphic,				kPackageAndPreflightPrefix + 7)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Image,					kPackageAndPreflightPrefix + 8)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_PDF,					kPackageAndPreflightPrefix + 9)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_EPS,					kPackageAndPreflightPrefix + 10)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_INDD,					kPackageAndPreflightPrefix + 11)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextFrame,				kPackageAndPreflightPrefix + 12)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextColumn,			kPackageAndPreflightPrefix + 13)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Group,					kPackageAndPreflightPrefix + 14)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Story,					kPackageAndPreflightPrefix + 15)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_SpreadLayer,			kPackageAndPreflightPrefix + 16)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_GraphicFrame,			kPackageAndPreflightPrefix + 17)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextContent,			kPackageAndPreflightPrefix + 18)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Swatch,				kPackageAndPreflightPrefix + 19)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_CharStyle,				kPackageAndPreflightPrefix + 20)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_ParaStyle,				kPackageAndPreflightPrefix + 21)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_ObjectStyle,			kPackageAndPreflightPrefix + 22)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_WaxLine,				kPackageAndPreflightPrefix + 23)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_WaxRun,				kPackageAndPreflightPrefix + 24)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextParcel,			kPackageAndPreflightPrefix + 25)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextTable,				kPackageAndPreflightPrefix + 26)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_ArtworkMark,			kPackageAndPreflightPrefix + 27)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_ArtworkGroup,			kPackageAndPreflightPrefix + 28)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableModel,			kPackageAndPreflightPrefix + 29)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableFrame,			kPackageAndPreflightPrefix + 30)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableCell,				kPackageAndPreflightPrefix + 31)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextFootnote,			kPackageAndPreflightPrefix + 32)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextNote,				kPackageAndPreflightPrefix + 33)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextOtherWaxOwner,		kPackageAndPreflightPrefix + 34)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextInline,			kPackageAndPreflightPrefix + 35)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableStyle,			kPackageAndPreflightPrefix + 36)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableCellStyle,		kPackageAndPreflightPrefix + 37)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Font,					kPackageAndPreflightPrefix + 38)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableFrameCell,		kPackageAndPreflightPrefix + 39)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TOPFrame,				kPackageAndPreflightPrefix + 40)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_ArtworkContext,		kPackageAndPreflightPrefix + 41)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextRange,				kPackageAndPreflightPrefix + 42)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_XRefInText,			kPackageAndPreflightPrefix + 43)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableArea,				kPackageAndPreflightPrefix + 44)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableFrameArea,		kPackageAndPreflightPrefix + 45)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextCharacter,			kPackageAndPreflightPrefix + 46)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_SpellCheckState,		kPackageAndPreflightPrefix + 47)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TextFrameWithLink,		kPackageAndPreflightPrefix + 48)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_StoryList,				kPackageAndPreflightPrefix + 49)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_SwatchList,			kPackageAndPreflightPrefix + 50)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_CharStyleList,			kPackageAndPreflightPrefix + 51)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_ParaStyleList,			kPackageAndPreflightPrefix + 52)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_ObjectStyleList,		kPackageAndPreflightPrefix + 53)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableStyleList,		kPackageAndPreflightPrefix + 54)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TableCellStyleList,	kPackageAndPreflightPrefix + 55)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_WaxRunAdornment,		kPackageAndPreflightPrefix + 56)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_TrackedChange,			kPackageAndPreflightPrefix + 57)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_Media,					kPackageAndPreflightPrefix + 58)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_PageItemWithLink,		kPackageAndPreflightPrefix + 59)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_EPSTextItem,			kPackageAndPreflightPrefix + 60)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_XMLElement,			kPackageAndPreflightPrefix + 61)
DECLARE_PMID(kPreflightObjClassIDSpace, kPreflightOM_SVG,					kPackageAndPreflightPrefix + 62)

// Object subpart IDs
// Note: kPreflightOSP_None means "no subpart; the whole thing."
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_None,				kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_NativeStroke,		kPackageAndPreflightPrefix + 2)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_NativeFill,		kPackageAndPreflightPrefix + 3)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_Effect,			kPackageAndPreflightPrefix + 4)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_EffectStroke,		kPackageAndPreflightPrefix + 5)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_EffectFill,		kPackageAndPreflightPrefix + 6)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_Stroke,			kPackageAndPreflightPrefix + 7)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_Fill,				kPackageAndPreflightPrefix + 8)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_ContentMark,		kPackageAndPreflightPrefix + 9)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_RuleAbove,		kPackageAndPreflightPrefix + 10)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_RuleBelow,		kPackageAndPreflightPrefix + 11)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_GraphicProxy,		kPackageAndPreflightPrefix + 12)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_TextArtwork,		kPackageAndPreflightPrefix + 13)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_Underline,		kPackageAndPreflightPrefix + 14)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_Strikethrough,	kPackageAndPreflightPrefix + 15)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_LeftBorder,		kPackageAndPreflightPrefix + 16)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_TopBorder,		kPackageAndPreflightPrefix + 17)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_RightBorder,		kPackageAndPreflightPrefix + 18)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_BottomBorder,		kPackageAndPreflightPrefix + 19)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_Diagonal,			kPackageAndPreflightPrefix + 20)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_InnerRow,			kPackageAndPreflightPrefix + 21)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_InnerCol,			kPackageAndPreflightPrefix + 22)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_Border,			kPackageAndPreflightPrefix + 23)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_BulletsNumbering,	kPackageAndPreflightPrefix + 24)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_Kenten,			kPackageAndPreflightPrefix + 25)
DECLARE_PMID(kPreflightObjSubpartIDSpace,	kPreflightOSP_Ruby,				kPackageAndPreflightPrefix + 26)

// Criteria IDs
// kPrelightRC_Default is available for any rule that doesn't require multiple criteria.
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_Default,						kPackageAndPreflightPrefix + 1)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ColorspaceNotAllowed,			kPackageAndPreflightPrefix + 4)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_GraphicProxy,					kPackageAndPreflightPrefix + 5)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_CMYNotAllowed,					kPackageAndPreflightPrefix + 6)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_BleedTooSmall,					kPackageAndPreflightPrefix + 7)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_BleedTooLarge,					kPackageAndPreflightPrefix + 8)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_SlugTooSmall,					kPackageAndPreflightPrefix + 9)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_SlugTooLarge,					kPackageAndPreflightPrefix + 10)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_OrientationMismatch,			kPackageAndPreflightPrefix + 11)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_SizeMismatch,					kPackageAndPreflightPrefix + 12)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_SizeAndOrientationMismatch,	kPackageAndPreflightPrefix + 13)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_EmbeddedProfileOverridden,		kPackageAndPreflightPrefix + 14)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_CMYKUsingProfile,				kPackageAndPreflightPrefix + 15)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_VectorNotIgnoringCMYK,			kPackageAndPreflightPrefix + 16)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ImageResColorMin,				kPackageAndPreflightPrefix + 17)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ImageResColorMax,				kPackageAndPreflightPrefix + 18)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ImageResGrayMin,				kPackageAndPreflightPrefix + 19)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ImageResGrayMax,				kPackageAndPreflightPrefix + 20)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ImageResBWMin,					kPackageAndPreflightPrefix + 21)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ImageResBWMax,					kPackageAndPreflightPrefix + 22)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_InteractiveButton,				kPackageAndPreflightPrefix + 23)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_InteractiveMedia,				kPackageAndPreflightPrefix + 24)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_OverrideParaAndCharStyles,		kPackageAndPreflightPrefix + 25)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_OverrideParaStyle,				kPackageAndPreflightPrefix + 26)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_OverrideCharStyle,				kPackageAndPreflightPrefix + 27)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_MissingGraphic,				kPackageAndPreflightPrefix + 28)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ModifiedGraphic,				kPackageAndPreflightPrefix + 29)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ChildGraphic_Missing,			kPackageAndPreflightPrefix + 30)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_OversetTextFrame,				kPackageAndPreflightPrefix + 31)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_OversetFootnote,				kPackageAndPreflightPrefix + 32)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_OversetTableCell,				kPackageAndPreflightPrefix + 33)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_LABSpotsSetting,				kPackageAndPreflightPrefix + 34)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_WrongNumberOfSpots,			kPackageAndPreflightPrefix + 35)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_XRefsOutOfDate,				kPackageAndPreflightPrefix + 36)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_XRefsUnresolved,				kPackageAndPreflightPrefix + 37)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_BadFontType,					kPackageAndPreflightPrefix + 38)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ProtectedFont,					kPackageAndPreflightPrefix + 39)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_MultipleMasterFont,			kPackageAndPreflightPrefix + 40)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ChildGraphic_Modified,			kPackageAndPreflightPrefix + 41)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_SpellCheckingOff,				kPackageAndPreflightPrefix + 42)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_SpellingErrors,				kPackageAndPreflightPrefix + 43)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_ChildLink_Inaccessible,		kPackageAndPreflightPrefix + 44)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_Link_Inaccessible,				kPackageAndPreflightPrefix + 45)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_InteractiveAnimated,			kPackageAndPreflightPrefix + 46)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_InteractiveMSO,				kPackageAndPreflightPrefix + 47)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_InteractiveLegacyAudio,		kPackageAndPreflightPrefix + 48)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_InteractiveLegacyVideo,		kPackageAndPreflightPrefix + 49)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_SpanColumnsViolation,		kPackageAndPreflightPrefix + 50)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_SplitColumnsViolation,		kPackageAndPreflightPrefix + 51)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_CaptionNoLink,					kPackageAndPreflightPrefix + 52)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_CaptionNoData,					kPackageAndPreflightPrefix + 53)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_CaptionMultipleLinks,			kPackageAndPreflightPrefix + 54)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_CaptionObscureProblem,			kPackageAndPreflightPrefix + 55)
DECLARE_PMID(kPreflightCriteriaIDSpace,	kPreflightRC_InteractiveFormField,				kPackageAndPreflightPrefix + 56)

//CLSIDs

// {AB351BD0-F382-4be3-AA6D-2E14317C2319}
#define kPreflightRule_CLSID { 0xab351bd0, 0xf382, 0x4be3, { 0xaa, 0x6d, 0x2e, 0x14, 0x31, 0x7c, 0x23, 0x19 }}
// {D9E7B47C-A830-4ea5-812A-7D79E0322552}
#define kPreflightRules_CLSID { 0xd9e7b47c, 0xa830, 0x4ea5, { 0x81, 0x2a, 0x7d, 0x79, 0xe0, 0x32, 0x25, 0x52 }}
// {AEA2AA36-D3E8-46c1-9D44-4633885E893E}
#define kScriptPreflightRule_CLSID { 0xaea2aa36, 0xd3e8, 0x46c1, {0x9d, 0x44, 0x46, 0x33, 0x88, 0x5e, 0x89, 0x3e }}
// {34CB369E-6144-4658-AD14-428D449AE3A9}
#define kScriptPreflightRules_CLSID { 0x34cb369e, 0x6144, 0x4658, { 0xad, 0x14, 0x42, 0x8d, 0x44, 0x9a, 0xe3, 0xa9 }}
// {99405403-996F-421f-BE71-180862DB3DFA}
#define kPreflightProfileRule_CLSID { 0x99405403, 0x996f, 0x421f, { 0xbe, 0x71, 0x18, 0x8, 0x62, 0xdb, 0x3d, 0xfa }}
// {4C49C78D-BE71-44ec-ADC9-1885D2F74C9E}
#define kPreflightProfileRules_CLSID { 0x4c49c78d, 0xbe71, 0x44ec, { 0xad, 0xc9, 0x18, 0x85, 0xd2, 0xf7, 0x4c, 0x9e }}
// {B8B56D43-A12A-46ed-8973-41FB78399AE1}
#define kPreflightRuleInstance_CLSID { 0xb8b56d43, 0xa12a, 0x46ed, {0x89, 0x73, 0x41, 0xfb, 0x78, 0x39, 0x9a, 0xe1}}
// {5E0D82A8-0A3F-4421-B8C8-2CE48F6642C2}
#define kPreflightRuleInstances_CLSID { 0x5e0d82a8, 0xa3f, 0x4421, {0xb8, 0xc8, 0x2c, 0xe4, 0x8f, 0x66, 0x42, 0xc2}}
// {9D7C5DB4-163A-45de-9E92-BEC82D080145}
#define kPreflightScriptRuleInstance_CLSID { 0x9d7c5db4, 0x163a, 0x45de, {0x9e, 0x92, 0xbe, 0xc8, 0x2d, 0x8, 0x1, 0x45}}
// {386C3076-5C26-41ca-864A-4B26F25419F1}
#define kPreflightScriptRuleInstances_CLSID { 0x386c3076, 0x5c26, 0x41ca, {0x86, 0x4a, 0x4b, 0x26, 0xf2, 0x54, 0x19, 0xf1}}
// {6A61125E-F75F-4b40-A987-846C18D82DB4}
#define kPreflightProfile_CLSID { 0x6a61125e, 0xf75f, 0x4b40, {0xa9, 0x87, 0x84, 0x6c, 0x18, 0xd8, 0x2d, 0xb4}}
// {D70FBB1B-B7E4-4ed8-982E-DBA0FCA64E22}
#define kPreflightProfiles_CLSID { 0xd70fbb1b, 0xb7e4, 0x4ed8, {0x98, 0x2e, 0xdb, 0xa0, 0xfc, 0xa6, 0x4e, 0x22}}
// {FED458F5-51C2-4046-B14F-924967F8ABE0}
#define kPreflightProcess_CLSID		{ 0xFED458F5, 0x51C2, 0x4046, {0xB1, 0x4F, 0x92, 0x49, 0x67, 0xF8, 0xAB, 0xE0 }}
// {9DF9D22D-42BD-44b5-ADCC-C42FD947E769}
#define kPreflightProcesses_CLSID	{ 0x9DF9D22D, 0x42BD, 0x44b5, {0xAD, 0xCC, 0xC4, 0x2F, 0xD9, 0x47, 0xE7, 0x69 }}
// {0A09280F-E204-4b28-AACE-7194DD98E57D}
#define kPreflightRuleDataObject_CLSID { 0x0A09280F, 0xE204, 0x4b28, {0xAA, 0xCE, 0x71, 0x94, 0xDD, 0x98, 0xE5, 0x7D}}
// {A11D6C83-0371-4a1c-A4B9-AB188846E15C}
#define kPreflightRuleDataObjects_CLSID { 0xA11D6C83, 0x0371, 0x4a1c, {0xA4, 0xB9, 0xAB, 0x18, 0x88, 0x46, 0xE1, 0x5C}}
// {9B035563-FAA5-4dd8-9A26-BB44FBA27599}
#define kPreflightRuleResultObject_CLSID { 0x9B035563, 0xFAA5, 0x4dd8, {0x9A, 0x26, 0xBB, 0x44, 0xFB, 0xA2, 0x75, 0x99}}
// {DA059773-68F3-4d85-AE97-5590A3821E34}
#define kPreflightOptions_CLSID { 0xDA059773, 0x68F3, 0x4d85, {0xAE, 0x97, 0x55, 0x90, 0xA3, 0x82, 0x1E, 0x34}}
// {6E47BA45-8E01-4877-81D8-1ED9A1585F25}
#define kPreflightBookOptions_CLSID { 0x6E47BA45, 0x8E01, 0x4877, {0x81, 0xD8, 0x1E, 0xD9, 0xA1, 0x58, 0x5F, 0x25}}

// More GUIDs pre-formatted via macros for later.. help yourself..
// {C9638E9F-C982-469d-8BA0-8B137C801328}
// #define kXXXXX_CLSID { 0xC9638E9F, 0xC982, 0x469d, {0x8B, 0xA0, 0x8B, 0x13, 0x7C, 0x80, 0x13, 0x28}}
// {BAD1F38B-3ABF-4c2d-81E0-62B5DB3C8024}
// #define kXXXXX_CLSID { 0xBAD1F38B, 0x3ABF, 0x4c2d, {0x81, 0xE0, 0x62, 0xB5, 0xDB, 0x3C, 0x80, 0x24}}
// {0AED5639-3433-494d-9E14-69A0DEF4B96F}
// #define kXXXXX_CLSID { 0x0AED5639, 0x3433, 0x494d, {0x9E, 0x14, 0x69, 0xA0, 0xDE, 0xF4, 0xB9, 0x6F}}
// {E1918EFA-95CB-46a1-AD3B-D4D92F0B8C01}
// #define kXXXXX_CLSID { 0xE1918EFA, 0x95CB, 0x46a1, {0xAD, 0x3B, 0xD4, 0xD9, 0x2F, 0x0B, 0x8C, 0x01}}
// {DBFA9FEF-A06B-4eb0-8905-64EBDBC78AD0}
// #define kXXXXX_CLSID { 0xDBFA9FEF, 0xA06B, 0x4eb0, {0x89, 0x05, 0x64, 0xEB, 0xDB, 0xC7, 0x8A, 0xD0}}
// {E51803BD-FFA8-4da0-BFCF-0F45298452FF}
// #define kXXXXX_CLSID { 0xE51803BD, 0xFFA8, 0x4da0, {0xBF, 0xCF, 0x0F, 0x45, 0x29, 0x84, 0x52, 0xFF}}
// {CE08CC81-8ABC-4e5f-8C02-BEAFFD691004}
// #define kXXXXX_CLSID { 0xCE08CC81, 0x8ABC, 0x4e5f, {0x8C, 0x02, 0xBE, 0xAF, 0xFD, 0x69, 0x10, 0x04}}
// {DA2E6783-B40A-4b66-89DE-B99F4334E66A}
// #define kXXXXX_CLSID { 0xDA2E6783, 0xB40A, 0x4b66, {0x89, 0xDE, 0xB9, 0x9F, 0x43, 0x34, 0xE6, 0x6A}}
// {8D22F697-C7D0-4379-9015-7D7768999BBF}
// #define kXXXXX_CLSID { 0x8D22F697, 0xC7D0, 0x4379, {0x90, 0x15, 0x7D, 0x77, 0x68, 0x99, 0x9B, 0xBF}}
// {5904761F-AB39-4982-AA25-9883E13E29E2}
// #define kXXXXX_CLSID { 0x5904761F, 0xAB39, 0x4982, {0xAA, 0x25, 0x98, 0x83, 0xE1, 0x3E, 0x29, 0xE2}}
// {6851F321-3A86-49ee-8E21-6FDD2C5B4B78}
// #define kXXXXX_CLSID { 0x6851F321, 0x3A86, 0x49ee, {0x8E, 0x21, 0x6F, 0xDD, 0x2C, 0x5B, 0x4B, 0x78}}
// {A9441188-0D19-4a2d-9223-8ED597814527}
// #define kXXXXX_CLSID { 0xA9441188, 0x0D19, 0x4a2d, {0x92, 0x23, 0x8E, 0xD5, 0x97, 0x81, 0x45, 0x27}}

#endif // __PackageAndPreflightID__
