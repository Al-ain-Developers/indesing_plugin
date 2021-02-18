//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/CJKID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __CJKID__
#define __CJKID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


// Double check kCJKPrefix with DeveloperPrefix.h
#define kCJKPrefix	 RezLong(0x4200)

// <Start IDC>
// PluginID
#define kCJKPluginName "CJKText Attributes"
DECLARE_PMID(kPlugInIDSpace, kCJKPluginID, kCJKPrefix + 1)


// <Class ID>
// class ids
DECLARE_PMID(kClassIDSpace, kCJKServiceBoss, kCJKPrefix + 1)
DECLARE_PMID(kClassIDSpace, kCJKCharacterPropsScriptProviderBoss, kCJKPrefix + 2)		//jwb 4/30/02 moved from ScriptingID.h

DECLARE_PMID(kClassIDSpace, kMojikumiStyleBoss, kCJKPrefix + 3)
DECLARE_PMID(kClassIDSpace, kKinsokuStyleBoss, kCJKPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTsumeStyleBoss, kCJKPrefix + 5)

DECLARE_PMID(kClassIDSpace, kHardcodedMojikumiStyleBoss, kCJKPrefix + 6)
DECLARE_PMID(kClassIDSpace, kHardcodedTsumeBoss, kCJKPrefix + 7)
DECLARE_PMID(kClassIDSpace, kHardcodedTsumeNoneBoss, kCJKPrefix + 8)
DECLARE_PMID(kClassIDSpace, kHardcodedKinsokuHardBoss, kCJKPrefix + 9)
DECLARE_PMID(kClassIDSpace, kHardcodedKinsokuSoftBoss, kCJKPrefix + 10)
DECLARE_PMID(kClassIDSpace, kHardcodedKinsokuNoneBoss, kCJKPrefix + 11)

DECLARE_PMID(kClassIDSpace, kRubyAttrStrandBoss, kCJKPrefix + 12)
DECLARE_PMID(kClassIDSpace, kVOSRubyAttrObjectBoss, kCJKPrefix + 13)
DECLARE_PMID(kClassIDSpace, kApplyRubyCmdBoss, kCJKPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kWaxRubyRunBoss, kCJKPrefix + 15)		OBSOLETE in Anna

DECLARE_PMID(kClassIDSpace, kMojikumiConverterBoss, kCJKPrefix + 16)
DECLARE_PMID(kClassIDSpace, kCopyMojikumiCmdBoss, kCJKPrefix + 17)

DECLARE_PMID(kClassIDSpace, kCJKNewDocResponderBoss, kCJKPrefix + 18)
DECLARE_PMID(kClassIDSpace, kCJKNewWSResponderBoss, kCJKPrefix + 19)
DECLARE_PMID(kClassIDSpace, kCJKNewStoryResponderBoss, kCJKPrefix + 20)

DECLARE_PMID(kClassIDSpace, kUseInputWindowCmdBoss, kCJKPrefix + 21)
DECLARE_PMID(kClassIDSpace, kCJKIMEHintsAdornmentBoss, kCJKPrefix + 22)

DECLARE_PMID(kClassIDSpace, kMojikumiClassListStyleBoss, kCJKPrefix + 23)
DECLARE_PMID(kClassIDSpace, kDefaultMojikumiCharacterClassListBoss, kCJKPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kMojikumiCharacterClassBoss, kCJKPrefix + 25)
DECLARE_PMID(kClassIDSpace, kCJKOpenDocResponderBoss, kCJKPrefix + 26)

DECLARE_PMID(kClassIDSpace, kCJKConversionProviderBoss, kCJKPrefix + 27)

// Text attribute data

// Tsume
DECLARE_PMID(kClassIDSpace, kTATsumeBoss, kCJKPrefix + 29)

DECLARE_PMID(kClassIDSpace, kTextAttrRubyAlignBoss, kCJKPrefix + 30)
DECLARE_PMID(kClassIDSpace, kTextAttrRubyOverhangBoss, kCJKPrefix + 31)
DECLARE_PMID(kClassIDSpace, kTextAttrRubyAdjustParentBoss, kCJKPrefix + 32)

// Text attribute report boss
// Mojikumi
DECLARE_PMID(kClassIDSpace, kTAMojikumiTableBoss, kCJKPrefix + 33)
DECLARE_PMID(kClassIDSpace, kTAMojikumiForceBeforeSpacingBoss, kCJKPrefix + 34)
DECLARE_PMID(kClassIDSpace, kTAMojikumiForceAfterSpacingBoss, kCJKPrefix + 35)

// Kinsoku
DECLARE_PMID(kClassIDSpace, kTAKinsokuTableBoss, kCJKPrefix + 36)
DECLARE_PMID(kClassIDSpace, kTAKinsokuTypeBoss, kCJKPrefix + 37)
DECLARE_PMID(kClassIDSpace, kTACJKHangingBoss, kCJKPrefix + 38)
DECLARE_PMID(kClassIDSpace, kTABunriKinshiBoss, kCJKPrefix + 39)
// Tsume
DECLARE_PMID(kClassIDSpace, kTATsumeTableBoss, kCJKPrefix + 40)
DECLARE_PMID(kClassIDSpace, kTATsumeKindBoss_obsolete, kCJKPrefix + 41)
// Moved to CJKPanelID.h 26.Jan.2000 %brycem%
DECLARE_PMID(kClassIDSpace, kTATsumeRatioBoss_obsolete, kCJKPrefix + 42)
DECLARE_PMID(kClassIDSpace, kTATsumeYakumonoRatioBoss_obsolete, kCJKPrefix + 43)
// this id is being reused by kTARubyOTProBoss DECLARE_PMID(kClassIDSpace, kTAUseFontMetricsBoss_obsolete, kCJKPrefix + 44)

// Ruby
DECLARE_PMID(kClassIDSpace, kTARubyOTProBoss, kCJKPrefix + 44)
DECLARE_PMID(kClassIDSpace, kTARubyAttrBoss, kCJKPrefix + 45)
DECLARE_PMID(kClassIDSpace, kTARubyStringBoss, kCJKPrefix + 46)
DECLARE_PMID(kClassIDSpace, kTARubyPointSizeBoss, kCJKPrefix + 47)
DECLARE_PMID(kClassIDSpace, kTARubyRelativeSizeBoss, kCJKPrefix + 48)
DECLARE_PMID(kClassIDSpace, kTARubyAlignmentBoss, kCJKPrefix + 49)
DECLARE_PMID(kClassIDSpace, kTAMojiRubyBoss, kCJKPrefix + 50)
DECLARE_PMID(kClassIDSpace, kTARubyFontUIDBoss, kCJKPrefix + 51)
DECLARE_PMID(kClassIDSpace, kTARubyFontStyleBoss, kCJKPrefix + 52)
DECLARE_PMID(kClassIDSpace, kTARubyAdjustParentBoss, kCJKPrefix + 53)
DECLARE_PMID(kClassIDSpace, kTARubyXScaleBoss, kCJKPrefix + 54)
DECLARE_PMID(kClassIDSpace, kTARubyYScaleBoss, kCJKPrefix + 55)
DECLARE_PMID(kClassIDSpace, kTARubyXOffsetBoss, kCJKPrefix + 56)
DECLARE_PMID(kClassIDSpace, kTARubyYOffsetBoss, kCJKPrefix + 57)
DECLARE_PMID(kClassIDSpace, kTARubyPositionBoss, kCJKPrefix + 58)
DECLARE_PMID(kClassIDSpace, kTARubyEdgeSpaceBoss, kCJKPrefix + 59)
DECLARE_PMID(kClassIDSpace, kTARubyOverhangBoss, kCJKPrefix + 60)
DECLARE_PMID(kClassIDSpace, kTARubyOverhangFlagBoss, kCJKPrefix + 61)
DECLARE_PMID(kClassIDSpace, kTARubyAutoScalingBoss, kCJKPrefix + 62)
DECLARE_PMID(kClassIDSpace, kTARubyAutoScaleMinBoss, kCJKPrefix + 63)

DECLARE_PMID(kClassIDSpace, kTARubyColorBoss, kCJKPrefix + 64)
DECLARE_PMID(kClassIDSpace, kTARubyTintBoss, kCJKPrefix + 65)
DECLARE_PMID(kClassIDSpace, kTARubyOverprintBoss, kCJKPrefix + 66)
DECLARE_PMID(kClassIDSpace, kTARubyStrokeColorBoss, kCJKPrefix + 67)
DECLARE_PMID(kClassIDSpace, kTARubyStrokeTintBoss, kCJKPrefix + 68)
DECLARE_PMID(kClassIDSpace, kTARubyStrokeOverprintBoss, kCJKPrefix + 69)
DECLARE_PMID(kClassIDSpace, kTARubyOutlineBoss, kCJKPrefix + 70)

// Kenten
DECLARE_PMID(kClassIDSpace, kTAKentenKindBoss, kCJKPrefix + 71)
DECLARE_PMID(kClassIDSpace, kTAKentenSizeBoss, kCJKPrefix + 72)
DECLARE_PMID(kClassIDSpace, kTAKentenRelatedSizeBoss, kCJKPrefix + 73)
DECLARE_PMID(kClassIDSpace, kTAKentenFontFamilyBoss, kCJKPrefix + 74)
DECLARE_PMID(kClassIDSpace, kTAKentenFontStyleBoss, kCJKPrefix + 75)
DECLARE_PMID(kClassIDSpace, kTAKentenXScaleBoss, kCJKPrefix + 76)
DECLARE_PMID(kClassIDSpace, kTAKentenYScaleBoss, kCJKPrefix + 77)
// 15.Mar.2000 %brycem% removed, per Heath Horton
DECLARE_PMID(kClassIDSpace, kTAKentenXOffsetBoss_obsolete, kCJKPrefix + 78)
DECLARE_PMID(kClassIDSpace, kTAKentenYOffsetBoss, kCJKPrefix + 79)
DECLARE_PMID(kClassIDSpace, kTAKentenAlignmentBoss, kCJKPrefix + 80)
DECLARE_PMID(kClassIDSpace, kTAKentenPositionBoss, kCJKPrefix + 81)
DECLARE_PMID(kClassIDSpace, kTAKentenCharacterBoss, kCJKPrefix + 82)
DECLARE_PMID(kClassIDSpace, kTAKentenCharacterSetBoss, kCJKPrefix + 83)

// Don't know what these were, but I want constants for 'em
// so I can remove 'em with a converter.
// Steve Pellegrin -- May 20, 2000
DECLARE_PMID(kClassIDSpace, k84_obsolete, kCJKPrefix + 84)
DECLARE_PMID(kClassIDSpace, k85_obsolete, kCJKPrefix + 85)
DECLARE_PMID(kClassIDSpace, k86_obsolete, kCJKPrefix + 86)

DECLARE_PMID(kClassIDSpace, kTAKentenColorBoss, kCJKPrefix + 87)
DECLARE_PMID(kClassIDSpace, kTAKentenTintBoss, kCJKPrefix + 88)
DECLARE_PMID(kClassIDSpace, kTAKentenOverprintBoss, kCJKPrefix + 89)
DECLARE_PMID(kClassIDSpace, kTAKentenStrokeColorBoss, kCJKPrefix + 90)
DECLARE_PMID(kClassIDSpace, kTAKentenStrokeTintBoss, kCJKPrefix + 91)
DECLARE_PMID(kClassIDSpace, kTAKentenStrokeOverprintBoss, kCJKPrefix + 92)
DECLARE_PMID(kClassIDSpace, kTAKentenOutlineBoss, kCJKPrefix + 93)



//Tatechuyoko
DECLARE_PMID(kClassIDSpace, kTATatechuyokoAttrBoss, kCJKPrefix + 94)
DECLARE_PMID(kClassIDSpace, kTATatechuyokoXOffsetBoss, kCJKPrefix + 95)
DECLARE_PMID(kClassIDSpace, kTATatechuyokoYOffsetBoss, kCJKPrefix + 96)
// Kumi number
DECLARE_PMID(kClassIDSpace, kTAKumiNumberReportBoss, kCJKPrefix + 97)
DECLARE_PMID(kClassIDSpace, kTAKumiNumberWithRomanReportBoss, kCJKPrefix + 98)

// Grid related attribute
DECLARE_PMID(kClassIDSpace, kTAGridJidoriReportBoss, kCJKPrefix + 99)
DECLARE_PMID(kClassIDSpace, kTAGridGyoudoriReportBoss, kCJKPrefix + 100)
DECLARE_PMID(kClassIDSpace, kTAGridAlignOnlyFirstLineReportBoss, kCJKPrefix + 101)
DECLARE_PMID(kClassIDSpace, kTextAttrGridAlignmentBoss, kCJKPrefix + 102)

// Character rotate
DECLARE_PMID(kClassIDSpace, kTACharRotateAngleReportBoss, kCJKPrefix + 103)
DECLARE_PMID(kClassIDSpace, kTARotateRomanBoss, kCJKPrefix + 104)

// Mojikumi options
DECLARE_PMID(kClassIDSpace, kTAMojikumiRomanWidthBoss, kCJKPrefix + 105)
DECLARE_PMID(kClassIDSpace, kTAMojikumiFullAdjustBoss, kCJKPrefix + 106)
DECLARE_PMID(kClassIDSpace, kTAMojikumiAdjustPeriodBoss, kCJKPrefix + 107)
DECLARE_PMID(kClassIDSpace, kTAMojikumiRensuujiBoss, kCJKPrefix + 108)

// Tsume options
// Moved to CJKPanelID.h 26.Jan.2000 %brycem%
DECLARE_PMID(kClassIDSpace, kTATsumeKindYakumonoBoss_obsolete, kCJKPrefix + 109)
DECLARE_PMID(kClassIDSpace, kTATsumeKindHiraganaBoss_obsolete, kCJKPrefix + 110)
DECLARE_PMID(kClassIDSpace, kTATsumeKindKatakanaBoss_obsolete, kCJKPrefix + 111)
DECLARE_PMID(kClassIDSpace, kTATsumeKindRomanBoss_obsolete, kCJKPrefix + 112)
DECLARE_PMID(kClassIDSpace, kTATsumeKindNumericBoss_obsolete, kCJKPrefix + 113)
DECLARE_PMID(kClassIDSpace, kTATsumeKindSymbolBoss_obsolete, kCJKPrefix + 114)
DECLARE_PMID(kClassIDSpace, kTATsumeKindKanjiBoss_obsolete, kCJKPrefix + 115)
DECLARE_PMID(kClassIDSpace, kTAEMBodyMarginBoss_obsolete, kCJKPrefix + 116)

// Linguistic
DECLARE_PMID(kClassIDSpace, kCJKLinguisticBoss, kCJKPrefix + 117)
//DECLARE_PMID(kClassIDSpace, kCJKTextPreProcessorBoss, kCJKPrefix + 118)
//DECLARE_PMID(kClassIDSpace, kCJKTextPostProcessorBoss, kCJKPrefix + 119)

// Shatai
DECLARE_PMID(kClassIDSpace, kTAShataiMagnificationBoss, kCJKPrefix + 120)
DECLARE_PMID(kClassIDSpace, kTAShataiAngleBoss, kCJKPrefix + 121)
DECLARE_PMID(kClassIDSpace, kTAShataiAdjustTsumeBoss, kCJKPrefix + 122)
DECLARE_PMID(kClassIDSpace, kTAShataiAdjustRotationBoss, kCJKPrefix + 123)

// Warichu
DECLARE_PMID(kClassIDSpace, kTAWarichuAttrBoss, kCJKPrefix + 125)
DECLARE_PMID(kClassIDSpace, kTAWarichuNumOfLineBoss, kCJKPrefix + 126)
DECLARE_PMID(kClassIDSpace, kTAWarichuRelativeSizeBoss, kCJKPrefix + 127)
DECLARE_PMID(kClassIDSpace, kTAWarichuLineSpacingBoss, kCJKPrefix + 128)
DECLARE_PMID(kClassIDSpace, kTAWarichuAlignmentBoss, kCJKPrefix + 129)


// Alternate glyph (OTF font characteristics)
DECLARE_PMID(kClassIDSpace, kAltGlyphAttrBoss_obsolete, kCJKPrefix + 130) // needed for conversion

// Mojikumi Command
DECLARE_PMID(kClassIDSpace, kCreateMojikumiTableCmdBoss, kCJKPrefix + 131)
DECLARE_PMID(kClassIDSpace, kDeleteMojikumiTableCmdBoss, kCJKPrefix + 132)
// Kinsoku Command
DECLARE_PMID(kClassIDSpace, kCreateKinsokuTableCmdBoss, kCJKPrefix + 133)
DECLARE_PMID(kClassIDSpace, kDeleteKinsokuTableCmdBoss, kCJKPrefix + 134)

DECLARE_PMID(kClassIDSpace, kCJKUserEditCmdResponderBoss, kCJKPrefix + 135)

DECLARE_PMID(kClassIDSpace, kAltGlyphStyleAttrBoss_obsolete, kCJKPrefix + 136)	// added 8/14/00 brycem, now obsolete
																		// but needed for conversion

DECLARE_PMID(kClassIDSpace, kCJKTextAttrIteratorRegBoss, kCJKPrefix + 137)

DECLARE_PMID(kClassIDSpace, kMojikumiStyleSyncBoss, kCJKPrefix + 138)	
DECLARE_PMID(kClassIDSpace, kTsumeStyleSyncBoss,	kCJKPrefix + 139)
DECLARE_PMID(kClassIDSpace, kCompositeFontStyleSyncBoss, kCJKPrefix + 140)
DECLARE_PMID(kClassIDSpace, kKinsokuStyleSyncBoss, kCJKPrefix + 141)

DECLARE_PMID(kClassIDSpace, kTAWarichuMinCharsBeforeBreakBoss, kCJKPrefix + 142)
DECLARE_PMID(kClassIDSpace, kTAWarichuMinCharsAfterBreakBoss, kCJKPrefix + 143)
DECLARE_PMID(kClassIDSpace, kTAWarichuAutoResizeParenBoss, kCJKPrefix + 144)

//DECLARE_PMID(kClassIDSpace, kTAUseCenterLeadingModelBoss, kCJKPrefix + 145)	// replaced by leadingmodelboss
DECLARE_PMID(kClassIDSpace, kCJKTextAttrSchemaConversionBoss, kCJKPrefix + 146)
DECLARE_PMID(kClassIDSpace, kCJKTraditionalConversionProviderBoss, kCJKPrefix + 147)

DECLARE_PMID(kClassIDSpace, kTAOTFHVKanaBoss, kCJKPrefix + 148)
DECLARE_PMID(kClassIDSpace, kTAOTFProportionalBoss, kCJKPrefix + 149)
DECLARE_PMID(kClassIDSpace, kTAOTFRomanItalicsBoss, kCJKPrefix + 150)
DECLARE_PMID(kClassIDSpace, kTALeadingModelBoss, kCJKPrefix + 151)
DECLARE_PMID(kClassIDSpace, kConventionalCJKConversionProviderBoss, kCJKPrefix + 152)

DECLARE_PMID(kClassIDSpace, kLoadMojikumiTableCmdBoss, kCJKPrefix + 153)
DECLARE_PMID(kClassIDSpace, kCreateTsumeTableCmdBoss, kCJKPrefix + 154)
DECLARE_PMID(kClassIDSpace, kDeleteTsumeTableCmdBoss, kCJKPrefix + 155)

DECLARE_PMID(kClassIDSpace, kReplaceTsumeTableCmdBoss, kCJKPrefix + 156)
DECLARE_PMID(kClassIDSpace, kReplaceKinsokuTableCmdBoss, kCJKPrefix + 157)
DECLARE_PMID(kClassIDSpace, kReplaceMojikumiTableCmdBoss, kCJKPrefix + 158)

DECLARE_PMID(kClassIDSpace, kTAIMECompModeBoss, kCJKPrefix + 159)
DECLARE_PMID(kClassIDSpace, kCJKTextAttrPhase2ConversionBoss, kCJKPrefix + 160)
DECLARE_PMID(kClassIDSpace, kCJKNewScrapDocResponderBoss, kCJKPrefix + 161)
DECLARE_PMID(kClassIDSpace, kRubyStrandPastePieceBoss, kCJKPrefix + 162) 

// New for 3.0
DECLARE_PMID(kClassIDSpace, kTAScaleAffectsLineHeightBoss, kCJKPrefix + 163) 
DECLARE_PMID(kClassIDSpace, kTAParaGyoudoriBoss, kCJKPrefix + 164)
DECLARE_PMID(kClassIDSpace, kCJKParagraphPropsScriptProviderBoss, kCJKPrefix + 165)
DECLARE_PMID(kClassIDSpace, kTACJKGridTrackingBoss, kCJKPrefix + 166)
//gap
DECLARE_PMID(kClassIDSpace, kKinsokuScriptProviderBoss, kCJKPrefix + 168)
DECLARE_PMID(kClassIDSpace, kMojikumiScriptProviderBoss, kCJKPrefix + 169)
DECLARE_PMID(kClassIDSpace, kEditMojikumiTableCmdBoss, kCJKPrefix + 170)
DECLARE_PMID(kClassIDSpace, kMojikumiUIOptionsBoss, kCJKPrefix + 171)
DECLARE_PMID(kClassIDSpace, kMojikumiSetDispPrefCmdBoss, kCJKPrefix + 172)
DECLARE_PMID(kClassIDSpace, kTextAttrGlyphFormBoss, kCJKPrefix + 173)
DECLARE_PMID(kClassIDSpace, kTextAttrOTFeatureListBoss, kCJKPrefix + 174)
DECLARE_PMID(kClassIDSpace, kMojikumiUIPrefsScriptProviderBoss, kCJKPrefix + 175)
DECLARE_PMID(kClassIDSpace, kCJKTextErrorStringServiceBoss, kCJKPrefix + 176)

// New for 4.0
DECLARE_PMID(kClassIDSpace, kTARubyAutoTCYNumDigitsBoss, kCJKPrefix + 177)
DECLARE_PMID(kClassIDSpace, kTARubyAutoTCYIncludeRomanBoss, kCJKPrefix + 178)
DECLARE_PMID(kClassIDSpace, kTARubyAutoTCYAutoScaleBoss, kCJKPrefix + 179)

DECLARE_PMID(kClassIDSpace, kHardcodedKinsokuKoreanBoss, kCJKPrefix + 180)
DECLARE_PMID(kClassIDSpace, kHardcodedKinsokuSCBoss, kCJKPrefix + 181)
DECLARE_PMID(kClassIDSpace, kHardcodedKinsokuTCBoss, kCJKPrefix + 182)

#ifdef DEBUG
DECLARE_PMID(kClassIDSpace, kCJKTestMenuBoss, kCJKPrefix + 184)
#endif

DECLARE_PMID(kClassIDSpace, kRubyStrandDiskPageBoss, kCJKPrefix + 185)

// New for 5.0
DECLARE_PMID(kClassIDSpace, kKinsokuBaseBoss, kCJKPrefix + 186)
DECLARE_PMID(kClassIDSpace, kMojikumiBaseBoss, kCJKPrefix + 187)
DECLARE_PMID(kClassIDSpace, kJBXMojikumiResTypeBoss, kCJKPrefix + 188)	
DECLARE_PMID(kClassIDSpace, kJBXKinsokuResTypeBoss, kCJKPrefix + 189)

DECLARE_PMID(kClassIDSpace, kSetFontLockingPrefsCmdBoss, kCJKPrefix + 190)
DECLARE_PMID(kClassIDSpace, kFontLockingPrefsScriptProviderBoss, kCJKPrefix + 191)

// New for 6.0
DECLARE_PMID(kClassIDSpace, kTAIdeoSpaceBehaviorBoss, kCJKPrefix + 192)
DECLARE_PMID(kClassIDSpace, kTAWordWrapOffBoss, kCJKPrefix + 193)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKDATA, kCJKPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKATTRSTYLE, kCJKPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRKINSOKUMODE, kCJKPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOJIKUMINAMETABLE, kCJKPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOJIKUMITABLE, kCJKPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IKINSOKUTABLE, kCJKPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IKINSOKUNAMETABLE, kCJKPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ITSUMETABLE, kCJKPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ITSUMENAMETABLE, kCJKPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ICJKTEXTOPTIONS, kCJKPrefix + 10)

DECLARE_PMID(kInterfaceIDSpace, IID_IRUBYATTRSTRAND, kCJKPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_IRUBYSTRAND, kCJKPrefix + 11)

DECLARE_PMID(kInterfaceIDSpace, IID_IMOJIKUMISTYLE, kCJKPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IVERTICALTEXTSTYLE, kCJKPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRIDRELATEDSTYLE, kCJKPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IKENTENSTYLE, kCJKPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IVERTICALRELATEDSTYLE, kCJKPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IWARICHUSTYLE, kCJKPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IRUBYSTYLE, kCJKPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMEATTRSTYLE, kCJKPrefix + 19)


DECLARE_PMID(kInterfaceIDSpace, IID_IKINSOKUTYPE, kCJKPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRRUBYALIGN, kCJKPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRRUBYOVERHANG, kCJKPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRRUBYADJUSTPARENT, kCJKPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRGRIDALIGNMENT, kCJKPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOJIKUMIDOCUMENTOBSERVER, kCJKPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOJIKUMICHARCLASSLISTNAMETABLE, kCJKPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOJIKUMICHARCLASSLIST, kCJKPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IALTGLYPHATTR_OBSOLETE, kCJKPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IENCODINGUTILS, kCJKPrefix + 29)

//DECLARE_PMID(kInterfaceIDSpace, IID_IALTGLYPHSTYLEATTR_obsolete, kCJKPrefix + 30)	// Added 8/14/00 brycem

DECLARE_PMID(kInterfaceIDSpace, IID_IKINSOKUHANGTYPE, kCJKPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ILEADINGMODEL, kCJKPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRCOMPMODE, kCJKPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRREPORT_ALTGLYPH_OBSOLETE, kCJKPrefix + 34)  // Keeps boss out of defaults!
DECLARE_PMID(kInterfaceIDSpace, IID_IRUBYUTILS, kCJKPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IEDITMOJIKUMITABLECMDDATA, kCJKPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOJIKUMIUIOPTIONS, kCJKPrefix + 36)

DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTRGLYPHFORM, kCJKPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTATTROTFEATURELIST, kCJKPrefix + 38)

DECLARE_PMID(kInterfaceIDSpace, IID_IFONTLOCKINGPREFS, kCJKPrefix + 39);
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTLOCKINGPREFSCMDDATA, kCJKPrefix + 40);

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kCJKLowMemoryImpl, kCJKPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCJKCharacterPropsScriptProviderImpl, kCJKPrefix + 2)		//jwb 4/30/02 moved from ScriptingID.h
DECLARE_PMID(kImplementationIDSpace, kCJKPluginFileImpl, kCJKPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCJKServiceDataImpl, kCJKPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCJKServiceProviderImpl, kCJKPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCJKInputEngineImpl, kCJKPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kTAKinsokuReportImpl, kCJKPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kTextAttrKinsokuModeImpl, kCJKPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kMojikumiNameTableImpl, kCJKPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kMojikumiTableImpl, kCJKPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kMojikumiCharacterClassImpl, kCJKPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kMojikumiCharacterClassListImpl, kCJKPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTextAttrMojikumiRefImpl, kCJKPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTATextAttrKinsokuRefImpl, kCJKPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kTextAttrTsumeRefImpl, kCJKPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kTsumeTableImpl, kCJKPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kTsumeNameTableImpl, kCJKPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kKinsokuNameTableImpl, kCJKPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kKinsokuTableImpl, kCJKPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kTextAttrKinsokuRefImpl, kCJKPrefix + 21)

DECLARE_PMID(kImplementationIDSpace, kRubyStrandImpl, kCJKPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kRubyAttrStrandImpl, kCJKPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kDefaultMojikumiCharacterClassListImpl, kCJKPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kHardcodedKinsokuTableImpl, kCJKPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kHardcodedKinsokuTableSoftImpl, kCJKPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kHardcodedKinsokuTableNoneImpl, kCJKPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kHardcodedTsumeTableImpl, kCJKPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kHardcodedTsumeTableNoneImpl, kCJKPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kHardcodedMojikumiTableImpl, kCJKPrefix + 30)

DECLARE_PMID(kImplementationIDSpace, kMojikumiConverterImpl, kCJKPrefix + 31)

DECLARE_PMID(kImplementationIDSpace, kCopyMojikumiCmdImpl, kCJKPrefix + 32)
//DECLARE_PMID(kImplementationIDSpace, kCJKTextOptions, kCJKPrefix + 33)
//DECLARE_PMID(kImplementationIDSpace, kUseInputWindowCmd, kCJKPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kIMEAttrStyleImpl, kCJKPrefix + 35)

DECLARE_PMID(kImplementationIDSpace, kCJKNewDocResponderImpl, kCJKPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kCJKNewWSResponderImpl, kCJKPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kCJKNewStoryResponderImpl, kCJKPrefix + 38)

DECLARE_PMID(kImplementationIDSpace, kCJKIMEHintsAdornmentImpl, kCJKPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kIMENewDocResponderImpl, kCJKPrefix + 40)

// Text style
DECLARE_PMID(kImplementationIDSpace, kMojikumiStyleImpl, kCJKPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kRubyStyleImpl, kCJKPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kVerticalRelatedStyleImpl, kCJKPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kGridRelatedStyleImpl, kCJKPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kWarichuStyleImpl, kCJKPrefix + 45)

DECLARE_PMID(kImplementationIDSpace, kCJKAttrStyleImpl, kCJKPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kCJKConversionProviderImpl, kCJKPrefix + 47)

// Text attribute data
DECLARE_PMID(kImplementationIDSpace, kTextAttrKinsokuTypeImpl, kCJKPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kTextAttrRubyAlignImpl, kCJKPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kTextAttrRubyOverhangImpl, kCJKPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kTextAttrRubyAdjustParentImpl, kCJKPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kTextAttrGridAlignmentImpl, kCJKPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kTextAttrAlignAutoImpl, kCJKPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kTextAttrKentenAlignImpl, kCJKPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kTextAttrRubyAutoScaleMinImpl, kCJKPrefix + 57)

// Text attribute report
// Mojikumi
DECLARE_PMID(kImplementationIDSpace, kTAMojikumiTableReportImpl, kCJKPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kTAMojikumiForceBeforeSpacingReportImpl, kCJKPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kTAMojikumiForceAfterSpacingReportImpl, kCJKPrefix + 62)
// Kinsoku
//DECLARE_PMID(kImplementationIDSpace, kTAKinsokuFlagReportImpl, kCJKPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kTAKinsokuTableReportImpl, kCJKPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kTAKinsokuTypeReportImpl, kCJKPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kTACJKHangingReportImpl, kCJKPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kTABunriKinshiReportImpl, kCJKPrefix + 68)
// Tsume
DECLARE_PMID(kImplementationIDSpace, kTATsumeReportImpl, kCJKPrefix + 69)

DECLARE_PMID(kImplementationIDSpace, kTAExternalTsumeReportImpl, kCJKPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kTATsumeKindReportImpl_obsolete, kCJKPrefix + 71)
// Moved to CJKPanel.r 3.Feb.2000 %brycem%
//DECLARE_PMID(kImplementationIDSpace, kTATsumeRatioReportImpl, kCJKPrefix + 72)

//Ruby
DECLARE_PMID(kImplementationIDSpace, kRubyStrandAttrImpl, kCJKPrefix + 73)

DECLARE_PMID(kImplementationIDSpace, kTARubyOTProReportImpl, kCJKPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kTARubyReportImpl, kCJKPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kTARubySizeReportImpl, kCJKPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kTARubyRelativeSizeReportImpl, kCJKPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kTARubyFontUIDReportImpl, kCJKPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kTARubyFontStyleReportImpl, kCJKPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kTARubyAdjustParentReportImpl, kCJKPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kTARubyXScaleReportImpl, kCJKPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kTARubyYScaleReportImpl, kCJKPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kTARubyXOffsetReportImpl, kCJKPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kTARubyYOffsetReportImpl, kCJKPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kTARubyAlignReportImpl, kCJKPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kTARubyStringReportImpl, kCJKPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kTAMojiRubyReportImpl, kCJKPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kTARubyPositionReportImpl, kCJKPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kTARubyEdgeSpaceReportImpl, kCJKPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kTARubyOverhangReportImpl, kCJKPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kTARubyOverhangFlagReportImpl, kCJKPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kTARubyAutoScalingReportImpl, kCJKPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kTARubyAutoScaleMinReportImpl, kCJKPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kTARubyColorReportImpl, kCJKPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kTARubyTintReportImpl, kCJKPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kTARubyOverprintReportImpl, kCJKPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kTARubyStrokeColorReportImpl, kCJKPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kTARubyStrokeTintReportImpl, kCJKPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kTARubyStrokeOverprintReportImpl, kCJKPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kTARubyOutlineReportImpl, kCJKPrefix + 100)

// Kenten (Bouten)
DECLARE_PMID(kImplementationIDSpace, kKentenStyleImpl, kCJKPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kTAKentenKindReportImpl, kCJKPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kTAKentenSizeReportImpl, kCJKPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kTAKentenRelatedSizeReportImpl, kCJKPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kTAKentenFontFamilyReportImpl, kCJKPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kTAKentenFontStyleReportImpl, kCJKPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kTAKentenXScaleReportImpl, kCJKPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kTAKentenYScaleReportImpl, kCJKPrefix + 108)
// 15.Mar.2000 %brycem% removed, per Heath Horton
//DECLARE_PMID(kImplementationIDSpace, kTAKentenXOffsetReportImpl, kCJKPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kTAKentenYOffsetReportImpl, kCJKPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kTAKentenAlignmentReportImpl, kCJKPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kTAKentenPositionReportImpl, kCJKPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kTAKentenCharacterReportImpl, kCJKPrefix + 113)

DECLARE_PMID(kImplementationIDSpace, kTAKentenColorReportImpl, kCJKPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kTAKentenTintReportImpl, kCJKPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kTAKentenOverprintReportImpl, kCJKPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kTAKentenStrokeColorReportImpl, kCJKPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kTAKentenStrokeTintReportImpl, kCJKPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kTAKentenStrokeOverprintReportImpl, kCJKPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kTAKentenOutlineReportImpl, kCJKPrefix + 121)

// Tatechuyoko
DECLARE_PMID(kImplementationIDSpace, kTATatechuyokoReportImpl, kCJKPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kTATatechuyokoXOffsetReportImpl, kCJKPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kTATatechuyokoYOffsetReportImpl, kCJKPrefix + 124)
// Kumi number
DECLARE_PMID(kImplementationIDSpace, kTAKumiNumberReportImpl, kCJKPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kTAKumiNumberWithRomanReportImpl, kCJKPrefix + 126)

// Grid related attribute
DECLARE_PMID(kImplementationIDSpace, kTAGridJidoriReportImpl, kCJKPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kTAGridGyoudoriReportImpl, kCJKPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kTAGridAlignOnlyFirstLineReportImpl, kCJKPrefix + 129)

// Baseline
DECLARE_PMID(kImplementationIDSpace, kTAGridAlignmentReportImpl, kCJKPrefix + 133)

// Character rotate
DECLARE_PMID(kImplementationIDSpace, kTACharRotateAngleReportImpl, kCJKPrefix + 134)

// Rotate Roman in vertical text
DECLARE_PMID(kImplementationIDSpace, kTARotateRomanReportImpl, kCJKPrefix + 135)

// Mojikumi options
DECLARE_PMID(kImplementationIDSpace, kTAMojikumiRomanWithReportImpl, kCJKPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kTAMojikumiFullAdjustReportImpl, kCJKPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kTAMojikumiAdjustPeriodPosReportImpl, kCJKPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kTAMojikumiRensuujiReportImpl, kCJKPrefix + 139)

DECLARE_PMID(kImplementationIDSpace, kJBXMojikumiResTypeImpl, kCJKPrefix + 140) 
DECLARE_PMID(kImplementationIDSpace, kJBXKinsokuResTypeImpl, kCJKPrefix + 141)

// Tsume options
// Moved to CJKPanel.r 3.Feb.2000 %brycem%
//DECLARE_PMID(kImplementationIDSpace, kTATsumeKindYakumonoReportImpl, kCJKPrefix + 140)
//DECLARE_PMID(kImplementationIDSpace, kTATsumeKindHiraganaReportImpl, kCJKPrefix + 141)
//DECLARE_PMID(kImplementationIDSpace, kTATsumeKindKatakanaReportImpl, kCJKPrefix + 142)
//DECLARE_PMID(kImplementationIDSpace, kTATsumeKindRomanReportImpl, kCJKPrefix + 143)
//DECLARE_PMID(kImplementationIDSpace, kTATsumeKindNumericReportImpl, kCJKPrefix + 144)
//DECLARE_PMID(kImplementationIDSpace, kTATsumeKindSymbolReportImpl, kCJKPrefix + 145)
//DECLARE_PMID(kImplementationIDSpace, kTATsumeKindKanjiReportImpl, kCJKPrefix + 146)
//DECLARE_PMID(kImplementationIDSpace, kTAEMBodyMarginReportImpl, kCJKPrefix + 147)

DECLARE_PMID(kImplementationIDSpace, kMojiClassListNameTableTableImpl, kCJKPrefix + 148)

// Warichu
DECLARE_PMID(kImplementationIDSpace, kTAWarichuReportImpl, kCJKPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kTAWarichuNumOfLineReportImpl, kCJKPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kTAWarichuRelativeSizeReportImpl, kCJKPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kTAWarichuLineSpacingReportImpl, kCJKPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kTAWarichuAlignmentReportImpl, kCJKPrefix + 153)

#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kCJKTestMenuImpl, kCJKPrefix + 154)
#endif

DECLARE_PMID(kImplementationIDSpace, kEncodingUtilsImpl, kCJKPrefix + 155) 

DECLARE_PMID(kImplementationIDSpace, kCJKLinguisticProviderImpl, kCJKPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kCJKSpellingMgrImpl, kCJKPrefix + 157)

//DECLARE_PMID(kImplementationIDSpace, kCJKTextPreProcessorImpl, kCJKPrefix + 158)
//DECLARE_PMID(kImplementationIDSpace, kCJKTextPostProcessorImpl, kCJKPrefix + 159)

// Shatai
DECLARE_PMID(kImplementationIDSpace, kTAShataiMagnificationReportImpl, kCJKPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kTAShataiAngleReportImpl, kCJKPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kTAShataiAdjustTsumeReportImpl, kCJKPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kTAShataiAdjustRotationReportImpl, kCJKPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kTextAttrShataiMagnificationImpl, kCJKPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kTextAttrShataiAngleImpl, kCJKPrefix + 165)


// Alternate Glyphs
DECLARE_PMID(kImplementationIDSpace, kAltGlyphAttrImpl, kCJKPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kAltGlyphReportImpl, kCJKPrefix + 167)

DECLARE_PMID(kImplementationIDSpace, kTAKentenCharacterSetReportImpl, kCJKPrefix + 170)

// Mojikumi Command
DECLARE_PMID(kImplementationIDSpace, kCreateMojikumiTableCmdImpl, kCJKPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kDeleteMojikumiTableCmdImpl, kCJKPrefix + 172)
// Kinsoku Command
DECLARE_PMID(kImplementationIDSpace, kCreateKinsokuTableCmdImpl, kCJKPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kDeleteKinsokuTableCmdImpl, kCJKPrefix + 174)

DECLARE_PMID(kImplementationIDSpace, kMojikumiDocumentObserverImpl, kCJKPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kCJKOpenDocResponderImpl, kCJKPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kCJKUserEditCmdRespImpl, kCJKPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kAltGlyphStyleAttrImpl_obsolete, kCJKPrefix + 178)
// obsolete DECLARE_PMID(kImplementationIDSpace, kAltGlyphStyleReportImpl_obsolete, kCJKPrefix + 179)

DECLARE_PMID(kImplementationIDSpace, kCJKTextAttrIteratorRegImpl, kCJKPrefix + 180)

DECLARE_PMID(kImplementationIDSpace, kMojikumiStyleSyncServiceImpl,	kCJKPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kTsumeStyleSyncServiceImpl,	kCJKPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kCompFontStyleSyncServiceImpl,	kCJKPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kKinsokuStyleSyncServiceImpl,  kCJKPrefix + 184)

DECLARE_PMID(kImplementationIDSpace, kTAWarichuMinCharsBeforeBreakReportImpl, kCJKPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kTAWarichuMinCharsAfterBreakReportImpl, kCJKPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kTAWarichuAutoResizeParenReportImpl, kCJKPrefix + 187)

//DECLARE_PMID(kImplementationIDSpace, kTAUseCenterLeadingModelReportImpl, kCJKPrefix + 188)	// replaced by LeadingModel

DECLARE_PMID(kImplementationIDSpace, kTAOTFHVKanaReportImpl, kCJKPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kTAOTFProportionalReportImpl, kCJKPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kTAOTFRomanItalicsReportImpl, kCJKPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kTextAttrKinsokuHangTypeImpl, kCJKPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kTALeadingModelReportImpl, kCJKPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kTextAttrLeadingModelImpl, kCJKPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kLoadMojikumiTableCmdImpl, kCJKPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kCreateTsumeTableCmdImpl, kCJKPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kDeleteTsumeTableCmdImpl, kCJKPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kReplaceTsumeTableCmdImpl, kCJKPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kReplaceKinsokuTableCmdImpl, kCJKPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kReplaceMojikumiTableCmdImpl, kCJKPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kTAIMECompModeImpl, kCJKPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kTAIMECompReportImpl, kCJKPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kCJKTextAttrPhase2ConversionImpl, kCJKPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kCJKNewScrapDocResponderImpl, kCJKPrefix + 204)
//DECLARE_PMID(kImplementationIDSpace, kInvalidImpl, kCJKPrefix + 205) 
DECLARE_PMID(kImplementationIDSpace, kRubyStrandPastePieceImpl, kCJKPrefix + 206) 
//DECLARE_PMID(kImplementationIDSpace, kMyFancyImpl, kCJKPrefix + 207) 

// New for 3.0
DECLARE_PMID(kImplementationIDSpace, kTAParaGyoudoriReportImpl, kCJKPrefix + 208) 
DECLARE_PMID(kImplementationIDSpace, kCJKParagraphPropsScriptProviderImpl, kCJKPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kTAScaleAffectsLineHeightReportImpl, kCJKPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kTACJKGridTrackingReportImpl, kCJKPrefix + 211)
//gap
DECLARE_PMID(kImplementationIDSpace, kKinsokuScriptProviderImpl, kCJKPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kMojikumiScriptProviderImpl, kCJKPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kMojikumiScriptImpl, kCJKPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kKinsokuScriptImpl, kCJKPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kEditMojikumiTableCmdImpl, kCJKPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kEditMojikumiTableCmdDataImpl, kCJKPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kMojikumiUIOptionsImpl, kCJKPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kMojikumiSetDispPrefCmdImpl, kCJKPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kTextAttrGlyphFormImpl, kCJKPrefix + 221) 
DECLARE_PMID(kImplementationIDSpace, kTextAttrGlyphFormReportImpl, kCJKPrefix + 222) 
DECLARE_PMID(kImplementationIDSpace, kTextAttrOTFeatureListImpl, kCJKPrefix + 223) 
DECLARE_PMID(kImplementationIDSpace, kTextAttrOTFeatureListReportImpl, kCJKPrefix + 224) 
DECLARE_PMID(kImplementationIDSpace, kMojikumiUIPrefsScriptProviderImpl, kCJKPrefix + 225) 
DECLARE_PMID(kImplementationIDSpace, kCJKTextErrorStringServiceImpl, kCJKPrefix + 226) 

// New for 4.0
DECLARE_PMID(kImplementationIDSpace, kTARubyAutoTCYNumDigitsReportImpl, kCJKPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kTARubyAutoTCYIncludeRomanReportImpl, kCJKPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kTARubyAutoTCYAutoScaleReportImpl, kCJKPrefix + 229)

DECLARE_PMID(kImplementationIDSpace, kHardcodedKinsokuTableKoreanImpl, kCJKPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kHardcodedKinsokuTableSCImpl, kCJKPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kHardcodedKinsokuTableTCImpl, kCJKPrefix + 232)

// New for 5.0
DECLARE_PMID(kImplementationIDSpace, kFontLockingPrefsImpl, kCJKPrefix + 233)			// addin to workspace
DECLARE_PMID(kImplementationIDSpace, kSetFontLockingPrefsCmdImpl, kCJKPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kFontLockingPrefsCmdDataImpl, kCJKPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kFontLockingPrefsScriptProviderImpl, kCJKPrefix + 236)

// New for 6.0
DECLARE_PMID(kImplementationIDSpace, kTAIdeoSpaceBehaviorReportImpl, kCJKPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, kTAWordWrapOffReportImpl, kCJKPrefix + 238)


// For DontShowAgain warning alerts
DECLARE_PMID(kWidgetIDSpace, kFontLockingWarningWidgetId,	kCJKPrefix + 1)

// Error Codes
DECLARE_PMID(kErrorIDSpace, kDefaultMojikumiReadOnlyError,	kCJKPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kDefaultKinsokuReadOnlyError,	kCJKPrefix + 2)
//DECLARE_PMID(kErrorIDSpace, ,	kCJKPrefix + 2)

//
//ScriptElementIDs
//

// Objects
DECLARE_PMID(kScriptInfoIDSpace, kKinsokuTableObjectScriptElement,				kCJKPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kMojikumiTableObjectScriptElement,				kCJKPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kMojikumiUIPrefsObjectScriptElement,			kCJKPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kFontLockingPrefsObjectScriptElement,			kCJKPrefix + 13)

// Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateKinsokuTableMethodScriptElement,			kCJKPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kCreateMojikumiTableMethodScriptElement,		kCJKPrefix + 31)

// Data type
DECLARE_PMID(kScriptInfoIDSpace, kOverrideMojikumiAkiTypeDefScriptElement,		kCJKPrefix + 40)

// Properties
DECLARE_PMID(kScriptInfoIDSpace, kMojikumiUIPrefsPropertyScriptElement, 		kCJKPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kMojikumiUISettingsPropertyScriptElement, 		kCJKPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kFontLockingPrefsPropertyScriptElement, 		kCJKPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kFontInputLockingPrefPropertyScriptElement, 	kCJKPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kFontChangeLockingPrefPropertyScriptElement, 	kCJKPrefix + 54)

//gap
DECLARE_PMID(kScriptInfoIDSpace, kCharacterAlignmentPropertyScriptElement, 		kCJKPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kTsumePropertyScriptElement, 					kCJKPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kLeadingAkiPropertyScriptElement,  			kCJKPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kTrailingAkiPropertyScriptElement,  			kCJKPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kCharacterRotationPropertyScriptElement,  		kCJKPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kJidoriPropertyScriptElement,  				kCJKPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kGlyphFormPropertyScriptElement,  				kCJKPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kShataiMagnificationPropertyScriptElement,  	kCJKPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kShataiDegreeAnglePropertyScriptElement,  		kCJKPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kShataiAdjustRotationPropertyScriptElement,  	kCJKPrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kShataiAdjustTsumePropertyScriptElement,  		kCJKPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kTatechuyokoXOffsetPropertyScriptElement,  	kCJKPrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace, kTatechuyokoYOffsetPropertyScriptElement,  	kCJKPrefix + 112)
DECLARE_PMID(kScriptInfoIDSpace, kKentenFillColorPropertyScriptElement,  		kCJKPrefix + 113)
DECLARE_PMID(kScriptInfoIDSpace, kKentenStrokeColorPropertyScriptElement,  		kCJKPrefix + 114)
DECLARE_PMID(kScriptInfoIDSpace, kKentenTintPropertyScriptElement,  			kCJKPrefix + 115)
DECLARE_PMID(kScriptInfoIDSpace, kKentenStrokeTintPropertyScriptElement,  		kCJKPrefix + 116)
DECLARE_PMID(kScriptInfoIDSpace, kKentenWeightPropertyScriptElement,  			kCJKPrefix + 117)
DECLARE_PMID(kScriptInfoIDSpace, kKentenOverprintFillPropertyScriptElement,  	kCJKPrefix + 118)
DECLARE_PMID(kScriptInfoIDSpace, kKentenOverprintStrokePropertyScriptElement,  	kCJKPrefix + 119)
DECLARE_PMID(kScriptInfoIDSpace, kKentenKindPropertyScriptElement,  			kCJKPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kKentenPlacementPropertyScriptElement,  		kCJKPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kKentenPositionPropertyScriptElement,  		kCJKPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kKentenFontPropertyScriptElement,  			kCJKPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kKentenFontStylePropertyScriptElement,  		kCJKPrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kKentenFontSizePropertyScriptElement,  		kCJKPrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kKentenXScalePropertyScriptElement,  			kCJKPrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kKentenYScalePropertyScriptElement,  			kCJKPrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kKentenCustomCharacterPropertyScriptElement,  	kCJKPrefix + 128)
DECLARE_PMID(kScriptInfoIDSpace, kKentenCharacterSetPropertyScriptElement,  	kCJKPrefix + 129)
DECLARE_PMID(kScriptInfoIDSpace, kRubyFlagPropertyScriptElement,  				kCJKPrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kRubyStringPropertyScriptElement,  			kCJKPrefix + 131)
DECLARE_PMID(kScriptInfoIDSpace, kRubyFillPropertyScriptElement,  				kCJKPrefix + 132)
DECLARE_PMID(kScriptInfoIDSpace, kRubyStrokePropertyScriptElement,  			kCJKPrefix + 133)
DECLARE_PMID(kScriptInfoIDSpace, kRubyTintPropertyScriptElement,  				kCJKPrefix + 134)
DECLARE_PMID(kScriptInfoIDSpace, kRubyWeightPropertyScriptElement,  			kCJKPrefix + 135)
DECLARE_PMID(kScriptInfoIDSpace, kRubyOverprintFillPropertyScriptElement,  		kCJKPrefix + 136)
DECLARE_PMID(kScriptInfoIDSpace, kRubyOverprintStrokePropertyScriptElement,  	kCJKPrefix + 137)
DECLARE_PMID(kScriptInfoIDSpace, kRubyStrokeTintPropertyScriptElement,  		kCJKPrefix + 138)
DECLARE_PMID(kScriptInfoIDSpace, kRubyFontPropertyScriptElement,  				kCJKPrefix + 139)
DECLARE_PMID(kScriptInfoIDSpace, kRubyFontStylePropertyScriptElement,  			kCJKPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kRubyFontSizePropertyScriptElement,  			kCJKPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kRubyXScalePropertyScriptElement,  			kCJKPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kRubyYScalePropertyScriptElement,  			kCJKPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kRubyTypePropertyScriptElement,  				kCJKPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kRubyAlignmentPropertyScriptElement,  			kCJKPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kRubyPositionPropertyScriptElement,  			kCJKPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kRubyXOffsetPropertyScriptElement,  			kCJKPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kRubyYOffsetPropertyScriptElement,  			kCJKPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kRubyParentSpacingPropertyScriptElement,  		kCJKPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kRubyAutoAlignPropertyScriptElement,  			kCJKPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kRubyOverhangPropertyScriptElement,  			kCJKPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kRubyAutoScalingPropertyScriptElement,  		kCJKPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kRubyParentScalingPercentPropertyScriptElement,kCJKPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kRubyParentOverhangAmountPropertyScriptElement,kCJKPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kWarichuPropertyScriptElement,  				kCJKPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kWarichuSizePropertyScriptElement,  			kCJKPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kWarichuLinesPropertyScriptElement,  			kCJKPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kWarichuLineSpacingPropertyScriptElement,  	kCJKPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kWarichuAlignmentPropertyScriptElement,  		kCJKPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kWarichuCharsAfterBreakPropertyScriptElement,  kCJKPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kWarichuCharsBeforeBreakPropertyScriptElement, kCJKPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kOTFProportionalMetricsPropertyScriptElement,  kCJKPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kOTFHVKanaPropertyScriptElement,  				kCJKPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kOTFRomanItalicsPropertyScriptElement,  		kCJKPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kGridAlignmentPropertyScriptElement,   		kCJKPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kGridAlignFirstLineOnlyPropertyScriptElement,	kCJKPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kParaGyoudoriPropertyScriptElement,  			kCJKPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kGridGyoudoriPropertyScriptElement,  			kCJKPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kKinsokuSetPropertyScriptElement,  			kCJKPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kKinsokuTypePropertyScriptElement,  			kCJKPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kKinsokuHangTypePropertyScriptElement,  		kCJKPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kBunriKinshiPropertyScriptElement,  			kCJKPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kMojikumiPropertyScriptElement,  				kCJKPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kRensuujiPropertyScriptElement,  				kCJKPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kRotateSingleByteCharsPropertyScriptElement,	kCJKPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kLeadingModelPropertyScriptElement,  			kCJKPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kTatechuyokoPropertyScriptElement, 	 		kCJKPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kAutoTCYPropertyScriptElement,			  		kCJKPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kAutoTCYInclRomanPropertyScriptElement,  		kCJKPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kScaleAffectsLineHeightPropertyScriptElement,	kCJKPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kCJKGridTrackingPropertyScriptElement,			kCJKPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kCantBeginLineCharsPropertyScriptElement,		kCJKPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kCantEndLineCharsPropertyScriptElement,		kCJKPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kHangingPunctuationCharsPropertyScriptElement,	kCJKPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kCantBeSeparatedCharsPropertyScriptElement,	kCJKPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kBasedOnMojikumiPropertyScriptElement,			kCJKPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kOverrideAkiListPropertyScriptElement,			kCJKPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kKentenAlignmentPropertyScriptElement,			kCJKPrefix + 188)	//missing from 2.0
DECLARE_PMID(kScriptInfoIDSpace, kRubyOTProPropertyScriptElement,				kCJKPrefix + 189)	//missing from 2.0
DECLARE_PMID(kScriptInfoIDSpace, kOTFeatureListPropertyScriptElement,  			kCJKPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kRubyAutoTCYNumDigitsPropertyScriptElement,	kCJKPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kRubyAutoTCYIncludeRomanPropertyScriptElement,	kCJKPrefix + 192)
DECLARE_PMID(kScriptInfoIDSpace, kRubyAutoTCYAutoScalePropertyScriptElement,	kCJKPrefix + 193)
DECLARE_PMID(kScriptInfoIDSpace, kIdeoSpaceBehaviorPropertyScriptElement, 		kCJKPrefix + 194)
DECLARE_PMID(kScriptInfoIDSpace, kWordWrapOffPropertyScriptElement,				kCJKPrefix + 195)

// Enums
DECLARE_PMID(kScriptInfoIDSpace, kCharacterAlignmentEnumScriptElement,  		kCJKPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kGlyphFormEnumScriptElement,  					kCJKPrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kAdornmentOverprintEnumScriptElement,  		kCJKPrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kKentenCharacterEnumScriptElement,  			kCJKPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kRubyKentenPositionEnumScriptElement,  		kCJKPrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kKentenCharacterSetEnumScriptElement,  		kCJKPrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kRubyTypeEnumScriptElement,  					kCJKPrefix + 206)
DECLARE_PMID(kScriptInfoIDSpace, kRubyAlignmentEnumScriptElement,  				kCJKPrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kRubyParentSpacingEnumScriptElement,  			kCJKPrefix + 208)
DECLARE_PMID(kScriptInfoIDSpace, kRubyOverhangEnumScriptElement,  				kCJKPrefix + 209)
DECLARE_PMID(kScriptInfoIDSpace, kWarichuAlignmentEnumScriptElement,  			kCJKPrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kKinsokuTypeEnumScriptElement,  				kCJKPrefix + 211)
DECLARE_PMID(kScriptInfoIDSpace, kKinsokuHangTypeEnumScriptElement,  			kCJKPrefix + 212)
DECLARE_PMID(kScriptInfoIDSpace, kLeadingModelEnumScriptElement,  				kCJKPrefix + 213)
DECLARE_PMID(kScriptInfoIDSpace, kKinsokuSetEnumScriptElement,  				kCJKPrefix + 214)
DECLARE_PMID(kScriptInfoIDSpace, kMojikumiTableEnumScriptElement,  				kCJKPrefix + 215)
DECLARE_PMID(kScriptInfoIDSpace, kGridAlignmentEnumScriptElement,  				kCJKPrefix + 216)
DECLARE_PMID(kScriptInfoIDSpace, kKentenAlignmentEnumScriptElement,  			kCJKPrefix + 217)	//missing from 2.0

// More props
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl1PropertyScriptElement,  	kCJKPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl2PropertyScriptElement,  	kCJKPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl3PropertyScriptElement,  	kCJKPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl4PropertyScriptElement,  	kCJKPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl5PropertyScriptElement,  	kCJKPrefix + 225)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl6PropertyScriptElement,  	kCJKPrefix + 226)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl7PropertyScriptElement,  	kCJKPrefix + 227)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl8PropertyScriptElement,  	kCJKPrefix + 228)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl9PropertyScriptElement,  	kCJKPrefix + 229)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl10PropertyScriptElement,  	kCJKPrefix + 230)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl11PropertyScriptElement,  	kCJKPrefix + 231)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl12PropertyScriptElement,  	kCJKPrefix + 232)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl13PropertyScriptElement,  	kCJKPrefix + 233)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl14PropertyScriptElement,  	kCJKPrefix + 234)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl15PropertyScriptElement,  	kCJKPrefix + 235)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultMojikumiTbl16PropertyScriptElement,  	kCJKPrefix + 236)

//GUIDS
// {61273251-CCFF-4985-8C95-017C7FCFECFE}
#define kKinsokuTable_CLSID { 0x61273251, 0xccff, 0x4985, { 0x8c, 0x95, 0x1, 0x7c, 0x7f, 0xcf, 0xec, 0xfe } }
// {004AEAD1-3C3F-438f-B22F-316000307E4D}
#define kKinsokuTables_CLSID { 0x4aead1, 0x3c3f, 0x438f, { 0xb2, 0x2f, 0x31, 0x60, 0x0, 0x30, 0x7e, 0x4d } }
// {7C361EA2-B609-4c38-AEC6-F6C0AFF7D70C}
#define kMojikumiTable_CLSID { 0x7c361ea2, 0xb609, 0x4c38, { 0xae, 0xc6, 0xf6, 0xc0, 0xaf, 0xf7, 0xd7, 0xc } }
// {96FD14D4-164E-49f9-9BAC-227B1529B06A}
#define kMojikumiTables_CLSID { 0x96fd14d4, 0x164e, 0x49f9, { 0x9b, 0xac, 0x22, 0x7b, 0x15, 0x29, 0xb0, 0x6a } }
// {E4324EF1-13EE-4e95-9C8C-50653F5F87BB}
#define kMojikumiUIPref_CLSID { 0xe4324ef1, 0x13ee, 0x4e95, { 0x9c, 0x8c, 0x50, 0x65, 0x3f, 0x5f, 0x87, 0xbb } }
// {4D163B2E-D758-4309-9B2F-9EEAFFA3C448}
#define kFontLockingPrefs_CLSID { 0x4d163b2e, 0xd758, 0x4309, { 0x9b, 0x2f, 0x9e, 0xea, 0xff, 0xa3, 0xc4, 0x48 } }

enum CJKScriptIDs
{
	t_OverrideMojikumiAkiType		= 'OMKT'
};

#endif

