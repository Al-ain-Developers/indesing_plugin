//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/WorldReadyID.h $
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
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#ifndef __WorldReadyID__
#define __WorldReadyID__

#include "GeneralBuildFlags.h"
#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// 2004/07/20 MH: This should be a specific kSessionBoss interface (checking against featureset
#define DEFAULTEDITSIZE_ME	16.0

#define kWorldReadyPrefix			RezLong(0x50F00) //see source/private/Includes/DeveloperPrefix.h
#define kWorldReadyPluginName 		"WorldReady"

//  Shuksan
#define kSemSinaiMajorVersionNumber		RezLong(1)
#define kSemSinaiMinorVersionNumber		RezLong(5)

// Anna
#define kInitialSemFormat					kAnnaInitialMinorFormatNumber + 0
#define kSemMEAttributesFormatChg			kAnnaInitialMinorFormatNumber + 1

#define kSemLastAnnaFormatChange			kSemMEAttributesFormatChg

// Cobalt
#define kSemLastCobaltFormatChange			kCobaltInitialMinorFormatNumber

// Basil
#define kRemoveStoryOptionMEImplChange	kBasilInitialMinorFormatNumber
#define kRemoveRLTImplFromFrameChange	kBasilInitialMinorFormatNumber+1
#define kTextAttrComposerIDImplChange	kBasilInitialMinorFormatNumber+2
#define kKashidaAttrImplChange			kBasilInitialMinorFormatNumber+3

#define kWorldReadyLastBasilFormatChange	kKashidaAttrImplChange


#define kWorldReadyLastMajorFormatChange			kBasilMajorFormatNumber
#define kWorldReadyLastMinorFormatChange			kWorldReadyLastBasilFormatChange

DECLARE_PMID(kPlugInIDSpace, kWorldReadyPluginID, kWorldReadyPrefix + 1)

//---------------------------------------------------------------
// <Class ID>
//---------------------------------------------------------------
//gap

//DECLARE_PMID(kClassIDSpace, kMEToolBoss,				kWorldReadyPrefix + 2)
////DECLARE_PMID(kClassIDSpace, kMEToolRegisterBoss,		kWorldReadyPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kMEToolTrackerBoss,			kWorldReadyPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kMEToolTrackerRegisterBoss,	kWorldReadyPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kMEFrameItemBoss,			kWorldReadyPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kMEFrameTrackerBoss,		kWorldReadyPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kMEFrameToolBoss,			kWorldReadyPrefix + 8)
////DECLARE_PMID(kClassIDSpace, kNewMEFrameCmdBoss,			kWorldReadyPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSetRToLFrameCmdBoss,		kWorldReadyPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss,	kWorldReadyPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kMETextTrackerBoss,			kWorldReadyPrefix + 12)
////gap
//DECLARE_PMID(kClassIDSpace, kTOPMEToolBoss,				kWorldReadyPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kTOPMEToolTrackerBoss,		kWorldReadyPrefix + 15)
//gap
DECLARE_PMID(kClassIDSpace, kDigitsAttrBoss,			kWorldReadyPrefix + 17)
//gap
//gap
//gap
DECLARE_PMID(kClassIDSpace, kKashidaAttrBoss,			kWorldReadyPrefix + 21)
//gap
DECLARE_PMID(kClassIDSpace, kDiacVPosAttrBoss,			kWorldReadyPrefix + 24)
//gap
//gap
//gap
//gap
//gap
//gap
DECLARE_PMID(kClassIDSpace, kDirOverrideAttrBoss,		kWorldReadyPrefix + 31)
//gap
DECLARE_PMID(kClassIDSpace, kParagraphDirAttrBoss,		kWorldReadyPrefix + 41)
DECLARE_PMID(kClassIDSpace, kJustifMethodAttrBoss,		kWorldReadyPrefix + 42)
DECLARE_PMID(kClassIDSpace, kKashidaWidthAttrBoss,		kWorldReadyPrefix + 43)
//gap
DECLARE_PMID(kClassIDSpace, kDiacXOffsetAttrBoss,		kWorldReadyPrefix + 47)
DECLARE_PMID(kClassIDSpace, kDiacYOffsetAttrBoss,		kWorldReadyPrefix + 48)
//gap
//gap
//gap
DECLARE_PMID(kClassIDSpace, kSemOpenDocResponderBoss,	kWorldReadyPrefix + 54)
//DECLARE_PMID(kClassIDSpace, kSemSchemaBasedConversionBoss,	kWorldReadyPrefix + 55)
DECLARE_PMID(kClassIDSpace, kSemConversionProviderBoss,	kWorldReadyPrefix + 56)
DECLARE_PMID(kClassIDSpace, kSemPhase2ConversionResponderBoss,	kWorldReadyPrefix + 57)


// Tables R2L
DECLARE_PMID(kClassIDSpace, kChangeTableDirCmdBoss,	kWorldReadyPrefix + 58)
//DECLARE_PMID(kClassIDSpace, kTablesUIChangeTableDirCmdBoss, kWorldReadyPrefix + 59)
DECLARE_PMID(kClassIDSpace, kSemOTFOverlapBoss,	kWorldReadyPrefix + 60)
DECLARE_PMID(kClassIDSpace, kSemOTFStylisticAlternatesBoss,	kWorldReadyPrefix + 61)
DECLARE_PMID(kClassIDSpace, kSemOTFJustificationAlternatesBoss,	kWorldReadyPrefix + 62)
DECLARE_PMID(kClassIDSpace, kSemOTFStretchAlternatesBoss,	kWorldReadyPrefix + 63)

//Keyboard direction
DECLARE_PMID(kClassIDSpace, kKeyboardDirAttrBoss,        kWorldReadyPrefix + 64)
DECLARE_PMID(kClassIDSpace, kSetMEInputPreferencesCmdBoss, kWorldReadyPrefix + 65)
DECLARE_PMID(kClassIDSpace, kSetArabicSpellingModePrefsCmdBoss, kWorldReadyPrefix + 66)

// Footnotes numbering
DECLARE_PMID(kClassIDSpace, kArabicAlifBaTahFootnoteNumberingBoss,	kWorldReadyPrefix + 70)
DECLARE_PMID(kClassIDSpace, kArabicAbjadFootnoteNumberingBoss,	kWorldReadyPrefix + 71)
DECLARE_PMID(kClassIDSpace, kHebrewBiblicalFootnoteNumberingBoss,	kWorldReadyPrefix + 72)
DECLARE_PMID(kClassIDSpace, kHebrewNonStandardFootnoteNumberingBoss,	kWorldReadyPrefix + 73)

// Attribute Accessor
DECLARE_PMID(kClassIDSpace, kSemAttributeAccessorBoss,			kWorldReadyPrefix + 74)

// Numbering
// New numbering style bosses. Please do not change these IDs, since they form part of
// persistent data in a document.
DECLARE_PMID(kClassIDSpace, kArabicAlifBaTahParaNumberingStyleServiceBoss,	kWorldReadyPrefix + 75)
DECLARE_PMID(kClassIDSpace, kArabicAbjadParaNumberingStyleServiceBoss,	kWorldReadyPrefix + 76)
DECLARE_PMID(kClassIDSpace, kHebrewBiblicalParaNumberingStyleServiceBoss,	kWorldReadyPrefix + 77)
DECLARE_PMID(kClassIDSpace, kHebrewNonStandardParaNumberingStyleServiceBoss,	kWorldReadyPrefix + 78)
DECLARE_PMID(kClassIDSpace, kHindiParaNumberingStyleServiceBoss,	kWorldReadyPrefix + 79)
DECLARE_PMID(kClassIDSpace, kFarsiParaNumberingStyleServiceBoss,	kWorldReadyPrefix + 80)
//
// Sections
// New page numbering style bosses. Do not change the Ids, since these are persisted in the document.
DECLARE_PMID(kClassIDSpace, kArabicAlifBaTahPageNumberingStyleServiceBoss, kWorldReadyPrefix + 81)
DECLARE_PMID(kClassIDSpace, kArabicAbjadPageNumberingStyleServiceBoss, kWorldReadyPrefix + 82)
DECLARE_PMID(kClassIDSpace, kHebrewBiblicalPageNumberingStyleServiceBoss, kWorldReadyPrefix + 83)
DECLARE_PMID(kClassIDSpace, kHebrewNonStandardPageNumberingStyleServiceBoss, kWorldReadyPrefix + 84)
DECLARE_PMID(kClassIDSpace, kDiacriticsCmdBoss, kWorldReadyPrefix + 85)
DECLARE_PMID(kClassIDSpace, kKashidasCmdBoss, kWorldReadyPrefix + 86)

DECLARE_PMID(kClassIDSpace, kWorldReadyConversionProviderBoss, kWorldReadyPrefix + 87)

//Apply Middle Eastern Composer
DECLARE_PMID(kClassIDSpace, kApplyMEComposersCmdBoss, kWorldReadyPrefix + 88)
DECLARE_PMID(kClassIDSpace, kSemScriptProviderBoss, kWorldReadyPrefix + 89)
//Reverse Layout
DECLARE_PMID(kClassIDSpace, kSetInvertPubCmdBoss, kWorldReadyPrefix + 90)
DECLARE_PMID(kClassIDSpace, kInvertItemCmdBoss, kWorldReadyPrefix + 91)

//
//
//// classid messages 100, protocol is IID_ITABRULERDATA
//DECLARE_PMID(kMessageIDSpace, kLTRParaMessage, kWorldReadyPrefix + 100	/* changedBy is a TabStop. TabAlignObserver (TabPanel button) -> TabRulerObserver. */)
//DECLARE_PMID(kMessageIDSpace, kRTLParaMessage, kWorldReadyPrefix + 101	/* changedBy is a TabStop. TabAlignObserver (TabPanel button) -> TabRulerObserver. */)
//---------------------------------------------------------------
// <Implementation ID>
//---------------------------------------------------------------

//1 not used anymore
DECLARE_PMID(kImplementationIDSpace, kDigitsAttrImpl,				kWorldReadyPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDigitsReportImpl,				kWorldReadyPrefix + 3)
////gap
DECLARE_PMID(kImplementationIDSpace, kSetRToLFrameCmdImpl,			kWorldReadyPrefix + 13)
////gap
////gap
////gap
DECLARE_PMID(kImplementationIDSpace, kMultiColTextFrameMEImpl_Obsolete,		kWorldReadyPrefix + 18)	//kMultiColTextFrameMEImpl (CS3-5.0) replace kTextFrameMEImpl (CS2-4.0)
DECLARE_PMID(kImplementationIDSpace, kStoryOptionsMEImpl_Obsolete,	kWorldReadyPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kTOPMEToolImpl,				kWorldReadyPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kKashidaObserverImpl,			kWorldReadyPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kTOPMEToolCursorProviderImpl,	kWorldReadyPrefix + 22)
//gap
//gap
//gap
//gap
DECLARE_PMID(kImplementationIDSpace, kKashidaAttrImpl,				kWorldReadyPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kKashidaReportImpl,			kWorldReadyPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kDiacVPosAttrImpl,				kWorldReadyPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kDiacVPosReportImpl,			kWorldReadyPrefix + 30)
////gap
////DECLARE_PMID(kImplementationIDSpace, kMERulerSettingsImpl,			kWorldReadyPrefix + 32)
//DECLARE_PMID(kImplementationIDSpace, kTabRulerDataMEImpl,			kWorldReadyPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kMEEyeCharAttrFilterImpl,			kWorldReadyPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kMEEyeParaAttrFilterImpl,			kWorldReadyPrefix + 35)
//gap
//gap
DECLARE_PMID(kImplementationIDSpace, kSemOpenDocResponderImpl, kWorldReadyPrefix + 38)
//gap
// Object styles - Story Options ME
DECLARE_PMID(kImplementationIDSpace, kObjectStylesStoryOptionsMEImpl, kWorldReadyPrefix + 40)
//DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesMESuiteDefCSBImpl, kWorldReadyPrefix + 41)
//DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesMESuiteDefCSBSelectionExtImpl, kWorldReadyPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesScriptUtilsMEImpl, kWorldReadyPrefix + 43)
////gap
DECLARE_PMID(kImplementationIDSpace, kSetMEFrameCmdDataImpl,		kWorldReadyPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDirOverrideAttrImpl,			kWorldReadyPrefix + 46)
//DECLARE_PMID(kImplementationIDSpace, kDefaultDirObserverImpl,		kWorldReadyPrefix + 47)
//DECLARE_PMID(kImplementationIDSpace, kRTLDirObserverImpl,			kWorldReadyPrefix + 48)
//DECLARE_PMID(kImplementationIDSpace, kLTRDirObserverImpl,			kWorldReadyPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kDirOverrideReportImpl,		kWorldReadyPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kALColumnRuleableMEImpl,		kWorldReadyPrefix + 55)
//DECLARE_PMID(kImplementationIDSpace, kSemKBSCImpl,					kWorldReadyPrefix + 56)
//DECLARE_PMID(kImplementationIDSpace, kSemActionComponentImpl,		kWorldReadyPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kWaxGlyphsMEImpl,				kWorldReadyPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesMESuiteASBImpl,kWorldReadyPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kWaxRunHitTestMEImpl,			kWorldReadyPrefix +  60)
//DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesMESuiteLayoutCSBImpl, kWorldReadyPrefix + 61)
//DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesMESuiteTextCSBImpl, kWorldReadyPrefix + 62)
////DECLARE_PMID(kImplementationIDSpace, kCharacterPropertiesImpl,		kWorldReadyPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kFontUtilsMEImpl,				kWorldReadyPrefix + 64)
//DECLARE_PMID(kImplementationIDSpace, kWaxLineMEImpl,				kWorldReadyPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kParagraphDirAttrImpl,			kWorldReadyPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kParagraphDirReportImpl,		kWorldReadyPrefix + 67)
//DECLARE_PMID(kImplementationIDSpace, kTextTilerMEImpl,				kWorldReadyPrefix + 68)
//DECLARE_PMID(kImplementationIDSpace, kDefaultDigitsObserverImpl,	kWorldReadyPrefix + 69)
//DECLARE_PMID(kImplementationIDSpace, kArabicDigitsObserverImpl,		kWorldReadyPrefix + 70)
//DECLARE_PMID(kImplementationIDSpace, kHindiDigitsObserverImpl,		kWorldReadyPrefix + 71)
//DECLARE_PMID(kImplementationIDSpace, kFarsiDigitsObserverImpl,		kWorldReadyPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kJustifMethodAttrImpl,			kWorldReadyPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kJustifMethodReportImpl,		kWorldReadyPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kDiacXOffsetReportImpl,		kWorldReadyPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kDiacYOffsetReportImpl,		kWorldReadyPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kWaxLineHiliteMEImpl,			kWorldReadyPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kWaxRunShapeMEImpl_Obsolete,	kWorldReadyPrefix + 78)
//DECLARE_PMID(kImplementationIDSpace, kMELangInstallationImpl,		kWorldReadyPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kKashidaWidthReportImpl,		kWorldReadyPrefix + 80)
//gap
DECLARE_PMID(kImplementationIDSpace, kSemConversionProviderImpl,	kWorldReadyPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kSemPhase2ConversionImpl,	kWorldReadyPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kFindChangeOptionsMEImpl,	kWorldReadyPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kGraphicsUtilsMEImpl_Obsolete,	kWorldReadyPrefix + 85)
//
//// Attribute Accessor
DECLARE_PMID(kImplementationIDSpace, kSemAttributeAccessorImpl,			kWorldReadyPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kSemAttributeAccessorServiceImpl,	kWorldReadyPrefix + 87)

// Numbering
DECLARE_PMID(kImplementationIDSpace, kArabicAlifBaTahNumberConverterImpl,	kWorldReadyPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kArabicAbjadNumberConverterImpl,		kWorldReadyPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kHebrewBiblicalNumberConverterImpl,	kWorldReadyPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kHebrewNonStandardNumberConverterImpl, kWorldReadyPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kHindiNumberConverterImpl,				kWorldReadyPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kFarsiNumberConverterImpl,				kWorldReadyPrefix + 93)

// Tables R2L
DECLARE_PMID(kImplementationIDSpace, kChangeTableDirCmdImpl, 		kWorldReadyPrefix +  96)
DECLARE_PMID(kImplementationIDSpace, kChangeTableDirectionDataImpl, kWorldReadyPrefix +  97)
//DECLARE_PMID(kImplementationIDSpace, kTablesUIChangeTableDirCmdImpl,kWorldReadyPrefix + 98)
//gap
DECLARE_PMID(kImplementationIDSpace, kTableModelMEImpl, 			kWorldReadyPrefix + 101)

// Parcels R2L
DECLARE_PMID(kImplementationIDSpace, kTextParcelListMEImpl_Obsolete, 		kWorldReadyPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kFrameListTextPLDataMEImpl_Obsolete, 	kWorldReadyPrefix + 110)

// ME Attributes
DECLARE_PMID(kImplementationIDSpace, kAttributesMEImpl, 			kWorldReadyPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kSemOTFOverlapReportImpl,			kWorldReadyPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kSemOTFStylisticAlternatesReportImpl,			kWorldReadyPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kSemOTFJustificationAlternatesReportImpl,			kWorldReadyPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kSemOTFStretchAlternatesReportImpl,			kWorldReadyPrefix + 115)

// ME Symetrize
//DECLARE_PMID(kImplementationIDSpace, kMESymetrizeImpl,				kWorldReadyPrefix + 116)
//gap
//gap
// Baseless tags in story editor
DECLARE_PMID(kImplementationIDSpace, kBaselessTagRunImpl,			kWorldReadyPrefix + 119)

// StoryService ME
DECLARE_PMID(kImplementationIDSpace, kStoryServiceMEImpl_Obsolete,			kWorldReadyPrefix + 120)

// TextLinesME ME
DECLARE_PMID(kImplementationIDSpace, kTextLinesMEImpl,			kWorldReadyPrefix + 121)

// CompositionStyleME and DrawingStyleME
DECLARE_PMID(kImplementationIDSpace, kCompositionStyleMEImpl_Obsolete, kWorldReadyPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kDrawingStyleMEImpl, kWorldReadyPrefix + 123)

DECLARE_PMID(kImplementationIDSpace, kArabicSpellingModePrefsImpl, kWorldReadyPrefix +  128)
//FindChange cmds
DECLARE_PMID(kImplementationIDSpace, kDiacriticsCmdImpl, kWorldReadyPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kKashidasCmdImpl, kWorldReadyPrefix + 130)

//Tagged text
DECLARE_PMID(kImplementationIDSpace, kTextAttrHindiDigitsBossImpExpImpl, kWorldReadyPrefix + 131 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrDirOverrideBossImpExpImpl, kWorldReadyPrefix + 132 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrKashidaBossImpExpImpl, kWorldReadyPrefix + 133 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrDiacVPosBossImpExpImpl, kWorldReadyPrefix + 134 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrDiacXOffsetBossImpExpImpl, kWorldReadyPrefix + 135 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrDiacYOffsetBossImpExpImpl, kWorldReadyPrefix + 136 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrParaDirBossImpExpImpl, kWorldReadyPrefix + 137 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrOTFOverlapSwashBossImpExpImpl, kWorldReadyPrefix + 138 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrOTFStyAltBossImpExpImpl, kWorldReadyPrefix + 139 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrOTFJustifAltBossImpExpImpl, kWorldReadyPrefix + 140 )
DECLARE_PMID(kImplementationIDSpace, kTextAttrKbdDirOverrideBossImpExpImpl, kWorldReadyPrefix + 141 )

//TOCME
DECLARE_PMID(kImplementationIDSpace, kTOCCmdDataMEImpl,				kWorldReadyPrefix + 142)

//Keyboard Direction
DECLARE_PMID(kImplementationIDSpace, kKeyboardDirReportImpl,        kWorldReadyPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kMEInputPreferencesImpl,        kWorldReadyPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kSetMEInputPreferencesCmdImpl,     kWorldReadyPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kMEInputPreferencesCmdDataImpl,     kWorldReadyPrefix + 146)

//SemUtils
DECLARE_PMID(kImplementationIDSpace, kSemUtilsImpl,					kWorldReadyPrefix + 147)

//Tagged text
DECLARE_PMID(kImplementationIDSpace, kTextAttrJustifMethodBossImpExpImpl, kWorldReadyPrefix + 148 )

//Arabic spelling
DECLARE_PMID(kImplementationIDSpace, kSetArabicSpellingModePrefsCmdImpl,     kWorldReadyPrefix + 149)

DECLARE_PMID(kImplementationIDSpace, kRightToLeftImpl, kWorldReadyPrefix + 150)

//Apply ME composers
DECLARE_PMID(kImplementationIDSpace, kApplyMEComposersCmdImpl, kWorldReadyPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kSemScriptProviderImpl, kWorldReadyPrefix + 152)

//Reverse Layout
DECLARE_PMID (kImplementationIDSpace, kSetInvertPubCmdImpl, kWorldReadyPrefix + 153)
DECLARE_PMID (kImplementationIDSpace, kSetInvertPrefsCmdDataImpl, kWorldReadyPrefix + 154)
DECLARE_PMID (kImplementationIDSpace, kInvertOptionsImpl, kWorldReadyPrefix + 155)
DECLARE_PMID (kImplementationIDSpace, kInvertOptionsCmdDataImpl, kWorldReadyPrefix + 156)
DECLARE_PMID (kImplementationIDSpace, kInvertItemsCmdImpl, kWorldReadyPrefix + 157)
DECLARE_PMID (kImplementationIDSpace, kInvertItemsCmdDataImpl, kWorldReadyPrefix + 158)

//F/C Saved Query
DECLARE_PMID (kImplementationIDSpace, kFCAttrImpExpKashidaImpl, kWorldReadyPrefix + 159)
DECLARE_PMID (kImplementationIDSpace, kFCAttrImpExpDigitsImpl, kWorldReadyPrefix + 160)
DECLARE_PMID (kImplementationIDSpace, kFCAttrImpExpParaDirImpl, kWorldReadyPrefix + 161)
DECLARE_PMID (kImplementationIDSpace, kFCAttrImpExpJustifMethodImpl, kWorldReadyPrefix + 162)
DECLARE_PMID (kImplementationIDSpace, kFCAttrImpExpDiacVPosImpl, kWorldReadyPrefix + 163)
DECLARE_PMID (kImplementationIDSpace, kFCAttrImpExpDirOverrideImpl, kWorldReadyPrefix + 164)


//---------------------------------------------------------------
// <Interface ID>
//---------------------------------------------------------------
//
DECLARE_PMID(kInterfaceIDSpace, IID_IDIGITSATTR, kWorldReadyPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IWAXGLYPHSME, kWorldReadyPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIACVPOSATTR, kWorldReadyPrefix + 3)
////DECLARE_PMID(kInterfaceIDSpace, IID_ICHARACTERPROPERTIES, kWorldReadyPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWAXLINEME, kWorldReadyPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_IMEFRAME, kWorldReadyPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYOPTIONSME_OBSOLETE, kWorldReadyPrefix + 7)		//IID_IMETEXTFRAME (3.0) replaced by IID_ISTORYOPTIONSME
DECLARE_PMID(kInterfaceIDSpace, IID_IPARAGRAPHDIRATTR, kWorldReadyPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IKASHIDAATTR, kWorldReadyPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IWAXHITTESTME_OBSOLETE, kWorldReadyPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDIACXOFFSET, kWorldReadyPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDIACYOFFSET, kWorldReadyPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IWAXLINEHILITEME_OBSOLETE, kWorldReadyPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IWAXRUNSHAPEME, kWorldReadyPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETMEFRAMECMDDATA, kWorldReadyPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIROVERRIDEATTR, kWorldReadyPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IJUSTIFMETHODATTR, kWorldReadyPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLMEFRAME, kWorldReadyPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IRULEABLEME, kWorldReadyPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IMERULERSETTINGS, kWorldReadyPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_IMELANGUAGESTABLE, kWorldReadyPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYPROPERTIESMESUITE, kWorldReadyPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTUTILSME, kWorldReadyPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTTILERME, kWorldReadyPrefix + 25)
//DECLARE_PMID(kInterfaceIDSpace, IID_IMELANGINSTALLATION, kWorldReadyPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IISRIGHTTOLEFT, kWorldReadyPrefix + 27)


// Tables R2L
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEDIRATTR, kWorldReadyPrefix + 28)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDIRINTDATA, kWorldReadyPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEMODELME, kWorldReadyPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEUTILSME, kWorldReadyPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWTABLECMDDATAME, kWorldReadyPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLE_IMESUITE, kWorldReadyPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLECOMMANDSME, kWorldReadyPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLCONTENTMGRME, kWorldReadyPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLFOCUSME, kWorldReadyPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLFOCUSMGRME, kWorldReadyPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_ICELLFOCUSCACHEME, kWorldReadyPrefix + 38)
// Parcel R2L
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTPARCELLISTME_OBSOLETE, kWorldReadyPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTPARCELLISTDATAME_OBSOLETE, kWorldReadyPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IFINDCHANGEOPTIONSME, kWorldReadyPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSUTILSME_OBSOLETE, kWorldReadyPrefix + 42)

// ME Attributes
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTESME, kWorldReadyPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_ILANGUAGEIDDATAME, kWorldReadyPrefix + 44)
//
//// ME Symetrize
//DECLARE_PMID(kInterfaceIDSpace, IID_IMESYMETRIZE, kWorldReadyPrefix + 45)

// PlaceHolderText ME
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTMISCELLANYSUITEME, kWorldReadyPrefix + 46)

// Eye Dropper
DECLARE_PMID(kInterfaceIDSpace, IID_IMEEYECHARATTRFILTER, kWorldReadyPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEEYEPARAATTRFILTER, kWorldReadyPrefix + 48)
//
// For Story Editor
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOLDATAME, kWorldReadyPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IBASELESSTAGRUN, kWorldReadyPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYSERVICEME_OBSOLETE, kWorldReadyPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTLINESME, kWorldReadyPrefix + 52)
//
//RTL Direction
//DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTFRAMEME, kWorldReadyPrefix + 53)
//DECLARE_PMID(kInterfaceIDSpace, IID_IMULTICOLUMNTEXTFRAMEME_OBSOLETE, kWorldReadyPrefix + 53)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYOPTIONSME, kWorldReadyPrefix + 54)

// CompositionStyleME and DrawingStyleME
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMPOSITIONSTYLEME_OBSOLETE, kWorldReadyPrefix + 55 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWINGSTYLEME, kWorldReadyPrefix + 56 )
DECLARE_PMID(kInterfaceIDSpace, IID_IWRATTRIBUTEACCESSOR, kWorldReadyPrefix + 57 )

// Object styles - Story Options ME
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLESSTORYOPTIONSME, kWorldReadyPrefix + 58 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLESSCRIPTUTILSME, kWorldReadyPrefix + 59 )

DECLARE_PMID(kInterfaceIDSpace, IID_IARABICSPELLINGMODEPREFS, kWorldReadyPrefix + 60)
//gap

//TOCME
DECLARE_PMID(kInterfaceIDSpace, IID_ITOCCMDDATAME, kWorldReadyPrefix + 62)

//Keyboard direction
DECLARE_PMID(kInterfaceIDSpace, IID_IMEINPUTPREFERENCES,     kWorldReadyPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEINPUTPREFSCMDDATA,    kWorldReadyPrefix + 64)

//SemUtils
DECLARE_PMID(kInterfaceIDSpace, IID_ISEMUTILS,				 kWorldReadyPrefix + 65)

//WordBreaker
DECLARE_PMID(kInterfaceIDSpace, IID_IWRLINGUISTICWORDBREAKER, kWorldReadyPrefix + 67 )

//Reverse Layout
DECLARE_PMID (kInterfaceIDSpace, IID_IINVERTOPTIONS, kWorldReadyPrefix + 68)
DECLARE_PMID (kInterfaceIDSpace, IID_IINVERTPREFSCMDDATA, kWorldReadyPrefix + 69)
DECLARE_PMID (kInterfaceIDSpace, IID_IINVERTOPTIONSCMDDATA, kWorldReadyPrefix + 70)
DECLARE_PMID (kInterfaceIDSpace, IID_IINVERTITEMCMDDATA, kWorldReadyPrefix + 72)

////---------------------------------------------------------------
//// <Widget ID>
////---------------------------------------------------------------
//
//DECLARE_PMID(kWidgetIDSpace, kMEToolWidgetId, kWorldReadyPrefix + 1)
//DECLARE_PMID(kWidgetIDSpace, kDiacOffsetPanelWidgetID, kWorldReadyPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace, kDiacXOffsetLabelWidgetID, kWorldReadyPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kDiacXOffsetEditWidgetID, kWorldReadyPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kDiacXOffsetNudgeWidgetID, kWorldReadyPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kDiacYOffsetLabelWidgetID, kWorldReadyPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kDiacYOffsetEditWidgetID, kWorldReadyPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kDiacYOffsetNudgeWidgetID, kWorldReadyPrefix + 8)
//
//// Tables R2L
//DECLARE_PMID(kWidgetIDSpace, kTableDirGroupWidgetID, kWorldReadyPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kTableDirBorderWidgetID, kWorldReadyPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kDirStaticTextWidgetID, kWorldReadyPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kTablesDirDropdownWidgetID, kWorldReadyPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kTableSetUpDirGroupWidgetID, kWorldReadyPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kTableSetUpDirBorderWidgetID, kWorldReadyPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kTableDirStaticTextWidgetID, kWorldReadyPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kTableSetUpDirDropdownWidgetID, kWorldReadyPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kDirectionSelectGroupWidgetID, kWorldReadyPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kIconTableLTRDirWidgetId, kWorldReadyPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kIconTableRTLDirWidgetId, kWorldReadyPrefix + 19)
//
//DECLARE_PMID(kWidgetIDSpace, kDiacOffsetTitleWidgetID, kWorldReadyPrefix + 20)
//
//DECLARE_PMID(kWidgetIDSpace, kMEEyeDirOverrideWidgetId, kWorldReadyPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kMEEyeDigitsWidgetId, kWorldReadyPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kMEEyeKashidaWidgetId, kWorldReadyPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kMEEyeDiacVPosWidgetId, kWorldReadyPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kMEEyeDiacOffsetWidgetId, kWorldReadyPrefix + 25)
//DECLARE_PMID(kWidgetIDSpace, kMEEyeOpenTypeWidgetId, kWorldReadyPrefix + 26)
//DECLARE_PMID(kWidgetIDSpace, kMEEyeParagraphDirWidgetId, kWorldReadyPrefix + 27)
//DECLARE_PMID(kWidgetIDSpace, kMEEyeJustifMethodWidgetId, kWorldReadyPrefix + 28)
//
//// Object styles - Story Options ME
//DECLARE_PMID(kWidgetIDSpace, kObjStylesMEGenericWidgetID, kWorldReadyPrefix + 29)
//
////BN right indent
//DECLARE_PMID(kWidgetIDSpace, kBNRightIndentLabelWidgetId, kWorldReadyPrefix + 30)
//DECLARE_PMID(kWidgetIDSpace, kBNRightIndentEBWidgetId, kWorldReadyPrefix + 31)
//DECLARE_PMID(kWidgetIDSpace, kBNRightIndentNudgeWidgetId, kWorldReadyPrefix + 32)
//
////---------------------------------------------------------------
//// <Action ID>
////---------------------------------------------------------------
//
//DECLARE_PMID(kActionIDSpace, kSemDigitsActionID,	kWorldReadyPrefix +1)
//DECLARE_PMID(kActionIDSpace, kSemKashidaActionID,		kWorldReadyPrefix +2)
//
//DECLARE_PMID(kActionIDSpace, kSemDefaultDirActionID, kWorldReadyPrefix +7)
//DECLARE_PMID(kActionIDSpace, kSemLTRDirActionID, kWorldReadyPrefix +8)
//DECLARE_PMID(kActionIDSpace, kSemRTLDirActionID, kWorldReadyPrefix +9)
//DECLARE_PMID(kActionIDSpace, kSemPopupSepActionID, kWorldReadyPrefix +10)
//
//DECLARE_PMID(kActionIDSpace, kSemInsertLTRMarkActionID, kWorldReadyPrefix +11)
//DECLARE_PMID(kActionIDSpace, kSemInsertRTLMarkActionID, kWorldReadyPrefix +12)
//DECLARE_PMID(kActionIDSpace, kSemInsertZWNonJoinerActionID, kWorldReadyPrefix +13)
//DECLARE_PMID(kActionIDSpace, kSemInsertZWJoinerActionID, kWorldReadyPrefix +14)
//DECLARE_PMID(kActionIDSpace, kSemInsertGereshActionID, kWorldReadyPrefix +15)
//DECLARE_PMID(kActionIDSpace, kSemInsertGershayimActionID, kWorldReadyPrefix +16)
//DECLARE_PMID(kActionIDSpace, kSemInsertMaqafActionID, kWorldReadyPrefix +17)
//DECLARE_PMID(kActionIDSpace, kSemInsertKashidaActionID, kWorldReadyPrefix +18)
//DECLARE_PMID(kActionIDSpace, kMEToolActionID, kWorldReadyPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kTOPMEToolActionID, kWorldReadyPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kDiacOffsetActionID,   kWorldReadyPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kSemInsertR2LDashActionID,		kWorldReadyPrefix +22)
//DECLARE_PMID(kActionIDSpace, kSemInsertL2RDashActionID,		kWorldReadyPrefix +23)
//
//DECLARE_PMID(kActionIDSpace, kSemDefaultDigitsActionID,	kWorldReadyPrefix +24)
//DECLARE_PMID(kActionIDSpace, kSemArabicDigitsActionID, kWorldReadyPrefix +25)
//DECLARE_PMID(kActionIDSpace, kSemHindiDigitsActionID, kWorldReadyPrefix +26)
//DECLARE_PMID(kActionIDSpace, kSemFarsiDigitsActionID, kWorldReadyPrefix +27)
//
//DECLARE_PMID(kActionIDSpace, kSemInsertNarrowHardSpaceActionID, kWorldReadyPrefix +50)
//DECLARE_PMID(kActionIDSpace, kSemOTFOverlapActionID, kWorldReadyPrefix +54)
//DECLARE_PMID(kActionIDSpace, kSemOTFStylisticAlternatesActionID, kWorldReadyPrefix +55)
//DECLARE_PMID(kActionIDSpace, kSemOTFJustificationAlternatesActionID, kWorldReadyPrefix +56)
//DECLARE_PMID(kActionIDSpace, kSemOTFStretchAlternatesActionID, kWorldReadyPrefix +57)
//
//#define kTypeMenuInsertSpecialCharacterMEActionArea    "KBSCE Type menu:Insert Special ME Character"
//#define kTypographyOpenTypeActionArea    "KBSCE Typography:OpenType variants"
//#define kTypographyDigitsActionArea    "KBSCE Typography:Digits"
//#define kTypographyDirOverrideActionArea    "KBSCE Typography:Character Direction"
//#define kTypographyParaDirActionArea    "KBSCE Typography:Paragraph Direction"

//---------------------------------------------------------------
// <Service ID>
//---------------------------------------------------------------
DECLARE_PMID(kServiceIDSpace, kWRAttributeAccessorService,	kWorldReadyPrefix +1)

//WordBreaker
DECLARE_PMID(kServiceIDSpace, kWRLinguisticWordBreakerService,	kWorldReadyPrefix +2)

#endif
