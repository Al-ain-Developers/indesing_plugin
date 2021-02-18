//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TextScriptID.h $
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
//  Contains script info IDs used by the text engine.
//  
//========================================================================================

#ifndef _H_TextScriptID
#define _H_TextScriptID

#include "IDFactory.h"
#include "TextID.h"

START_IDS() //causing problems on windows .fr files

DECLARE_PMID(kScriptInfoIDSpace, kTextSuiteScriptElement,					kTextPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kGaijiOwnedItemObjectScriptElement,			kTextPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kRunInLineStyleObjectScriptElement,			kTextPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kGrepRunInStyleObjectScriptElement,			kTextPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kTextObjectScriptElement,					kTextPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kCharacterObjectScriptElement,				kTextPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kWordObjectScriptElement,					kTextPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kLineObjectScriptElement,					kTextPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kTextColumnObjectScriptElement,				kTextPrefix + 9)

DECLARE_PMID(kScriptInfoIDSpace, kParagraphObjectScriptElement,				kTextPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kTextStyleRangeObjectScriptElement,			kTextPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kInsertionPointObjectScriptElement,			kTextPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameObjectScriptElement,				kTextPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kStoryObjectScriptElement,					kTextPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kParagraphStyleObjectScriptElement,			kTextPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kCharacterStyleObjectScriptElement,			kTextPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kStoryPrefsObjectScriptElement,				kTextPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kTabStopObjectScriptElement,				kTextPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kTextFramePreferencesObjectScriptElement,	kTextPrefix + 19)

DECLARE_PMID(kScriptInfoIDSpace, kTextPreferenceObjectScriptElement,			kTextPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kTextDefaultObjectScriptElement,				kTextPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectSettingsPropertyScriptElement,	kTextPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kRunInStyleObjectScriptElement,				kTextPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kUnderlineColorPropertyScriptElement,			kTextPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kUnderlineGapColorPropertyScriptElement,		kTextPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kUnderlineTintPropertyScriptElement,			kTextPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kUnderlineGapTintPropertyScriptElement,		kTextPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kUnderlineOverprintPropertyScriptElement,		kTextPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kUnderlineGapOverprintPropertyScriptElement,	kTextPrefix + 29)

DECLARE_PMID(kScriptInfoIDSpace, kUnderlineTypePropertyScriptElement,			kTextPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kUnderlineOffsetPropertyScriptElement,		kTextPrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kUnderlineWeightPropertyScriptElement,		kTextPrefix + 32)
DECLARE_PMID(kScriptInfoIDSpace, kStrikeThroughColorPropertyScriptElement,		kTextPrefix + 33)
DECLARE_PMID(kScriptInfoIDSpace, kStrikeThroughGapColorPropertyScriptElement,	kTextPrefix + 34)
DECLARE_PMID(kScriptInfoIDSpace, kStrikeThroughTintPropertyScriptElement,		kTextPrefix + 35)
DECLARE_PMID(kScriptInfoIDSpace, kStrikeThroughGapTintPropertyScriptElement,	kTextPrefix + 36)
DECLARE_PMID(kScriptInfoIDSpace, kStrikeThroughOverprintPropertyScriptElement,	kTextPrefix + 37)
DECLARE_PMID(kScriptInfoIDSpace, kStrikeThroughGapOverprintPropertyScriptElement,kTextPrefix + 38)
DECLARE_PMID(kScriptInfoIDSpace, kStrikeThroughTypePropertyScriptElement,		kTextPrefix + 39)

DECLARE_PMID(kScriptInfoIDSpace, kStrikeThroughOffsetPropertyScriptElement,		kTextPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kStrikeThroughWeightPropertyScriptElement,		kTextPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kStoryTypePropertyScriptElement,				kTextPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kStoryTypeEnumScriptElement,					kTextPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kStoryTextContainersPropertyScriptElement,		kTextPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kStoryDirectionEnumScriptElement,				kTextPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kStoryDirectionPropertyScriptElement,			kTextPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kStylePreviewColorScriptElement,				kTextPrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kApplyParagraphStyleMethodScriptElement,		kTextPrefix + 48)
DECLARE_PMID(kScriptInfoIDSpace, kApplyCharacterStyleMethodScriptElement,		kTextPrefix + 49)

DECLARE_PMID(kScriptInfoIDSpace, kApplyStyleMethodScriptElement,				kTextPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kMoveTextMethodScriptElement,					kTextPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kStoryEditMethodScriptElement,					kTextPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kLoadStyleMethodScriptElement,					kTextPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kRecomposeTextMethodScriptElement,				kTextPrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kScaleTextAttributesMethodScriptElement,		kTextPrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kReleaseAnchoredObjectMethodScriptElement,		kTextPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kConvertToTableMethodScriptElement,			kTextPrefix + 57)
DECLARE_PMID(kScriptInfoIDSpace, kChangeCaseMethodScriptElement,				kTextPrefix + 58)
DECLARE_PMID(kScriptInfoIDSpace, kLoadStylesFormatEnumScriptElement,			kTextPrefix + 59)

DECLARE_PMID(kScriptInfoIDSpace, kSpecialGlyphPropertyScriptElement,			kTextPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kGaijiOwnedItemPropertyScriptElement,			kTextPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kStyleOverriddenPropertyScriptElement,			kTextPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedNestedStylePropertyScriptElement,		kTextPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kCrossFrameHyphenPropertyScriptElement,		kTextPrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kHyphenateLastWordPropertyScriptElement,		kTextPrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kLastLineIndentPropertyScriptElement,			kTextPrefix + 66)
DECLARE_PMID(kScriptInfoIDSpace, kSpecialRunInDelimiterElement,					kTextPrefix + 67)
DECLARE_PMID(kScriptInfoIDSpace, kTextOffsetPropertyScriptElement,				kTextPrefix + 68)
DECLARE_PMID(kScriptInfoIDSpace, kLinkTextFilesPropertyScriptElement,			kTextPrefix + 69)

DECLARE_PMID(kScriptInfoIDSpace, kLengthPropertyScriptElement,					kTextPrefix + 70)
DECLARE_PMID(kScriptInfoIDSpace, kParentStoryPropertyScriptElement,				kTextPrefix + 71)
DECLARE_PMID(kScriptInfoIDSpace, kParentTextFramePropertyScriptElement,			kTextPrefix + 72)
DECLARE_PMID(kScriptInfoIDSpace, kAutoLeadingPropertyScriptElement,				kTextPrefix + 73)
DECLARE_PMID(kScriptInfoIDSpace, kFirstLineIndentPropertyScriptElement,			kTextPrefix + 74)
DECLARE_PMID(kScriptInfoIDSpace, kLeftIndentPropertyScriptElement,				kTextPrefix + 75)
DECLARE_PMID(kScriptInfoIDSpace, kRightIndentPropertyScriptElement,				kTextPrefix + 76)
DECLARE_PMID(kScriptInfoIDSpace, kSpaceBeforePropertyScriptElement,				kTextPrefix + 77)
DECLARE_PMID(kScriptInfoIDSpace, kSpaceAfterPropertyScriptElement,				kTextPrefix + 78)
DECLARE_PMID(kScriptInfoIDSpace, kWordspaceMinPropertyScriptElement,			kTextPrefix + 79)

DECLARE_PMID(kScriptInfoIDSpace, kWordspaceMaxPropertyScriptElement,			kTextPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kWordspaceDesPropertyScriptElement,			kTextPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kLetterspaceMinPropertyScriptElement,			kTextPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kLetterspaceMaxPropertyScriptElement,			kTextPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kLetterspaceDesPropertyScriptElement,			kTextPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kHyphenZonePropertyScriptElement,				kTextPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kGlyphscaleMinPropertyScriptElement,			kTextPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kGlyphscaleMaxPropertyScriptElement,			kTextPrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kGlyphscaleDesPropertyScriptElement,			kTextPrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kPRAOverprintPropertyScriptElement,			kTextPrefix + 89)

DECLARE_PMID(kScriptInfoIDSpace, kPRAStrokePropertyScriptElement,				kTextPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kPRATintPropertyScriptElement,					kTextPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kPRAOffsetPropertyScriptElement,				kTextPrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kPRAIndentLPropertyScriptElement,				kTextPrefix + 93)
DECLARE_PMID(kScriptInfoIDSpace, kPRAIndentRPropertyScriptElement,				kTextPrefix + 94)
DECLARE_PMID(kScriptInfoIDSpace, kRuleAboveWidthPropertyScriptElement,			kTextPrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kRuleAboveColorPropertyScriptElement,			kTextPrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kPRBRuleOnPropertyScriptElement,				kTextPrefix + 97)
DECLARE_PMID(kScriptInfoIDSpace, kPRBOverPrintPropertyScriptElement,			kTextPrefix + 98)
DECLARE_PMID(kScriptInfoIDSpace, kPRBStrokePropertyScriptElement,				kTextPrefix + 99)

DECLARE_PMID(kScriptInfoIDSpace, kPRBTintPropertyScriptElement,					kTextPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kPRBOffsetPropertyScriptElement,				kTextPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kPRBIndentLPropertyScriptElement,				kTextPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kPRBIndentRPropertyScriptElement,				kTextPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kRuleBelowWidthPropertyScriptElement,			kTextPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kRuleBelowColorPropertyScriptElement,			kTextPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kAlignToBaselinePropertyScriptElement,			kTextPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kKeepLinesTogetherPropertyScriptElement,		kTextPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kHyphenateCapitalWordsPropertyScriptElement,	kTextPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kKeepAllLinesTogetherPropertyScriptElement,	kTextPrefix + 109)

DECLARE_PMID(kScriptInfoIDSpace, kHyphenationPropertyScriptElement,				kTextPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kDropCapLinesPropertyScriptElement,			kTextPrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace, kDropCapCharactersPropertyScriptElement,		kTextPrefix + 112)
DECLARE_PMID(kScriptInfoIDSpace, kHyphenateBeforeLastPropertyScriptElement,		kTextPrefix + 113)
DECLARE_PMID(kScriptInfoIDSpace, kHyphenateAfterFirstPropertyScriptElement,		kTextPrefix + 114)
DECLARE_PMID(kScriptInfoIDSpace, kHyphenateWordsLongerThanPropertyScriptElement,kTextPrefix + 115)
DECLARE_PMID(kScriptInfoIDSpace, kHyphenateLadderLimitPropertyScriptElement,	kTextPrefix + 116)
DECLARE_PMID(kScriptInfoIDSpace, kKeepWithNextPropertyScriptElement,			kTextPrefix + 117)
DECLARE_PMID(kScriptInfoIDSpace, kKeepFirstLinesPropertyScriptElement,			kTextPrefix + 118)
DECLARE_PMID(kScriptInfoIDSpace, kKeepLastLinesPropertyScriptElement,			kTextPrefix + 119)

DECLARE_PMID(kScriptInfoIDSpace, kJustificationPropertyScriptElement,			kTextPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kParagraphAlignPropertyScriptElement,			kTextPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kStartParagraphPropertyScriptElement,			kTextPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kComposerPropertyScriptElement,				kTextPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kBalanceRaggedLinesScriptElement,				kTextPrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFillLengthPropertyScriptElement,		kTextPrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFillAnglePropertyScriptElement,		kTextPrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFillStartPropertyScriptElement,		kTextPrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kGradientStrokeStartPropertyScriptElement,		kTextPrefix + 128)
DECLARE_PMID(kScriptInfoIDSpace, kGradientStrokeLengthPropertyScriptElement,	kTextPrefix + 129)

DECLARE_PMID(kScriptInfoIDSpace, kGradientStrokeAnglePropertyScriptElement,		kTextPrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kAscentPropertyScriptElement,					kTextPrefix + 131)
DECLARE_PMID(kScriptInfoIDSpace, kDescentPropertyScriptElement,					kTextPrefix + 132)
DECLARE_PMID(kScriptInfoIDSpace, kHorizontalOffsetPropertyScriptElement,		kTextPrefix + 133)
DECLARE_PMID(kScriptInfoIDSpace, kPRARuleOnPropertyScriptElement,				kTextPrefix + 134)
DECLARE_PMID(kScriptInfoIDSpace, kParagraphStylePropertyScriptElement,			kTextPrefix + 135)
DECLARE_PMID(kScriptInfoIDSpace, kCharacterStylePropertyScriptElement,			kTextPrefix + 136)
DECLARE_PMID(kScriptInfoIDSpace, kBaselinePropertyScriptElement,				kTextPrefix + 137)
DECLARE_PMID(kScriptInfoIDSpace, kStoryPrefsPropertyScriptElement,				kTextPrefix + 138)
DECLARE_PMID(kScriptInfoIDSpace, kOpticalMarginAlignmentPropertyScriptElement,	kTextPrefix + 139)

DECLARE_PMID(kScriptInfoIDSpace, kOpticalMarginBaseSizePropertyScriptElement,	kTextPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kFrameTypeScriptElement,						kTextPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kStoryOrientPropertyScriptElement,				kTextPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kBasedOnStylePropertyScriptElement,			kTextPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kDropCapStylePropertyScriptElement,			kTextPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kNextStylePropertyScriptElement,				kTextPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kAlignmentPropertyScriptElement,				kTextPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kPositionPropertyScriptElement,				kTextPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kAlignCharacterPropertyScriptElement,			kTextPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kLeaderPropertyScriptElement,					kTextPrefix + 149)

DECLARE_PMID(kScriptInfoIDSpace, kTextColumnCountPropertyScriptElement,			kTextPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kTextColumnGutterPropertyScriptElement,		kTextPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kTextColumnFixedWidthPropertyScriptElement,	kTextPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kUseFixedColumnWidthPropertyScriptElement,		kTextPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kInsetSpacingPropertyScriptElement,			kTextPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kFirstBaselineOffsetPropertyScriptElement,		kTextPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kMinimumFirstBaselineOffsetPropertyScriptElement,	kTextPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kVerticalJustificationPropertyScriptElement,	kTextPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kVerticalThresholdPropertyScriptElement,		kTextPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreWrapPropertyScriptElement,				kTextPrefix + 159)

DECLARE_PMID(kScriptInfoIDSpace, kTextFramePreferencesPropertyScriptElement,	kTextPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kStartTextFramePropertyScriptElement,			kTextPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kEndTextFramePropertyScriptElement,			kTextPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kPreviousTextFramePropertyScriptElement,		kTextPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kNextTextFramePropertyScriptElement,			kTextPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameIndexPropertyScriptElement,			kTextPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kOverFlowsPropertyScriptElement,				kTextPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kTextPreferenceObjectPropertyScriptElement,	kTextPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kTypographersQuotesPropertyScriptElement,		kTextPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kHighlightHJViolationsPropertyScriptElement,	kTextPrefix + 169)

DECLARE_PMID(kScriptInfoIDSpace, kHighlightKeepsPropertyScriptElement,			kTextPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kHighlightSubstitutedGlyphsPropertyScriptElement,kTextPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kHighlightCustomSpacingPropertyScriptElement,	kTextPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kHighlightSubstitutedFontsPropertyScriptElement,kTextPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kHighlightKinsokuPropertyScriptElement,		kTextPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kUseOpticalSizePropertyScriptElement,			kTextPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kUseParagraphLeadingPropertyScriptElement,		kTextPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kSuperscriptSizePropertyScriptElement,			kTextPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kSuperscriptPositionPropertyScriptElement,		kTextPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kSubscriptSizePropertyScriptElement,			kTextPrefix + 179)

DECLARE_PMID(kScriptInfoIDSpace, kSubscriptPositionPropertyScriptElement,		kTextPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kSmallCapPropertyScriptElement,				kTextPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kLeadingKeyIncrementPropertyScriptElement,		kTextPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kBaselineShiftKeyIncrementPropertyScriptElement,kTextPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kKerningKeyIncrementPropertyScriptElement,		kTextPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kShowInvisiblesPropertyScriptElement,			kTextPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kJustifyTextWrapsPropertyScriptElement,		kTextPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kScalingAdjustsTextAttributesPropertyScriptElement,kTextPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kPointSizePropertyScriptElement,				kTextPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kBaselineShiftPropertyScriptElement,			kTextPrefix + 189)

DECLARE_PMID(kScriptInfoIDSpace, kLeadingPropertyScriptElement,					kTextPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kHorizontalScalePropertyScriptElement,			kTextPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kVerticalScalePropertyScriptElement,			kTextPrefix + 192)
DECLARE_PMID(kScriptInfoIDSpace, kSkewPropertyScriptElement,					kTextPrefix + 193)
DECLARE_PMID(kScriptInfoIDSpace, kFillTintPropertyScriptElement,				kTextPrefix + 194)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeTintPropertyScriptElement,				kTextPrefix + 195)
DECLARE_PMID(kScriptInfoIDSpace, kTrackingPropertyScriptElement,				kTextPrefix + 196)
DECLARE_PMID(kScriptInfoIDSpace, kKerningValuePropertyScriptElement,			kTextPrefix + 197)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeWeightPropertyScriptElement,			kTextPrefix + 198)
DECLARE_PMID(kScriptInfoIDSpace, kLigaturesPropertyScriptElement,				kTextPrefix + 199)

DECLARE_PMID(kScriptInfoIDSpace, kFigureStylePropertyScriptElement,				kTextPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kStrikeThruPropertyScriptElement,				kTextPrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kNoBreakPropertyScriptElement,					kTextPrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kOverprintStrokePropertyScriptElement,			kTextPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kOverprintFillPropertyScriptElement,			kTextPrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kUnderlinePropertyScriptElement,				kTextPrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kOTFOrdinalPropertyScriptElement,				kTextPrefix + 206)
DECLARE_PMID(kScriptInfoIDSpace, kOTFFractionPropertyScriptElement,				kTextPrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kOTFDiscLigPropertyScriptElement,				kTextPrefix + 208)
DECLARE_PMID(kScriptInfoIDSpace, kOTFTitlingPropertyScriptElement,				kTextPrefix + 209)

DECLARE_PMID(kScriptInfoIDSpace, kOTFContextAltPropertyScriptElement,			kTextPrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kOTFSwashPropertyScriptElement,				kTextPrefix + 211)
DECLARE_PMID(kScriptInfoIDSpace, kOTFStylisticAltPropertyScriptElement,			kTextPrefix + 212)
DECLARE_PMID(kScriptInfoIDSpace, kHyphenWeightPropertyScriptElement,			kTextPrefix + 213)
DECLARE_PMID(kScriptInfoIDSpace, kCapitalizationPropertyScriptElement,			kTextPrefix + 214)
DECLARE_PMID(kScriptInfoIDSpace, kFillColorPropertyScriptElement,				kTextPrefix + 215)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeColorPropertyScriptElement,				kTextPrefix + 216)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedFontPropertyScriptElement,				kTextPrefix + 217)
DECLARE_PMID(kScriptInfoIDSpace, kFontStylePropertyScriptElement,				kTextPrefix + 218)
DECLARE_PMID(kScriptInfoIDSpace, kLanguagePropertyScriptElement,				kTextPrefix + 219)

DECLARE_PMID(kScriptInfoIDSpace, kKerningMethodPropertyScriptElement,			kTextPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kTextPositionPropertyScriptElement,			kTextPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kTriggerExpressionPropertyScriptElement,		kTextPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kTextContentsPropertyScriptElement,			kTextPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameContentsPropertyScriptElement,		kTextPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kPRAGapColorPropertyScriptElement,				kTextPrefix + 225)
DECLARE_PMID(kScriptInfoIDSpace, kPRAGapTintPropertyScriptElement,				kTextPrefix + 226)
DECLARE_PMID(kScriptInfoIDSpace, kPRAGapOverprintPropertyScriptElement,			kTextPrefix + 227)
DECLARE_PMID(kScriptInfoIDSpace, kPRBGapColorPropertyScriptElement,				kTextPrefix + 228)
DECLARE_PMID(kScriptInfoIDSpace, kPRBGapTintPropertyScriptElement,				kTextPrefix + 229)

DECLARE_PMID(kScriptInfoIDSpace, kRuleWidthEnumScriptElement,					kTextPrefix + 230)
DECLARE_PMID(kScriptInfoIDSpace, kJustificationEnumScriptElement,				kTextPrefix + 231)
DECLARE_PMID(kScriptInfoIDSpace, kParagraphAlignEnumScriptElement,				kTextPrefix + 232)
DECLARE_PMID(kScriptInfoIDSpace, kStartParagraphEnumScriptElement,				kTextPrefix + 233)
DECLARE_PMID(kScriptInfoIDSpace, kFrameTypeEnumScriptElement,					kTextPrefix + 234)
DECLARE_PMID(kScriptInfoIDSpace, kHorizontalVerticalEnumScriptElement,			kTextPrefix + 235)
DECLARE_PMID(kScriptInfoIDSpace, kTabStopAlignmentEnumScriptElement,			kTextPrefix + 236)
DECLARE_PMID(kScriptInfoIDSpace, kFirstBaselineEnumScriptElement,				kTextPrefix + 237)
DECLARE_PMID(kScriptInfoIDSpace, kVerticalJustificationEnumScriptElement,		kTextPrefix + 238)
DECLARE_PMID(kScriptInfoIDSpace, kLeadingEnumScriptElement,						kTextPrefix + 239)

DECLARE_PMID(kScriptInfoIDSpace, kFigureStyleEnumScriptElement,					kTextPrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kTextCaseEnumScriptElement,					kTextPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kTextPositionEnumScriptElement,				kTextPrefix + 242)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameContentsEnumScriptElement,			kTextPrefix + 243)
DECLARE_PMID(kScriptInfoIDSpace, kSpecialCharactersEnumScriptElement,			kTextPrefix + 244)
DECLARE_PMID(kScriptInfoIDSpace, kChangeCaseEnumScriptElement,					kTextPrefix + 245)
DECLARE_PMID(kScriptInfoIDSpace, kPRBGapOverPrintPropertyScriptElement,			kTextPrefix + 246)
DECLARE_PMID(kScriptInfoIDSpace, kPRATypePropertyScriptElement,					kTextPrefix + 247)
DECLARE_PMID(kScriptInfoIDSpace, kPRBTypePropertyScriptElement,					kTextPrefix + 248)
DECLARE_PMID(kScriptInfoIDSpace, kTextDefaultObjectPropertyScriptElement,		kTextPrefix + 249)

DECLARE_PMID(kScriptInfoIDSpace, kGalleyIndexPropertyScriptElement,				kTextPrefix + 250)
DECLARE_PMID(kScriptInfoIDSpace, kImportedPropertyScriptElement,				kTextPrefix + 251)
DECLARE_PMID(kScriptInfoIDSpace, kAllTabStopsPropertyScriptElement,				kTextPrefix + 252)
DECLARE_PMID(kScriptInfoIDSpace, kRunInCountPropertyScriptElement,				kTextPrefix + 253)
DECLARE_PMID(kScriptInfoIDSpace, kRunInInclusiveScriptElement,					kTextPrefix + 254)
DECLARE_PMID(kScriptInfoIDSpace, kAllRunInStylesPropertyScriptElement,			kTextPrefix + 255)
//no more!

DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectPositionScriptElement,			kTextPrefix2 + 1)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectPositionEnumScriptElement,		kTextPrefix2 + 2)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectXOffsetScriptElement,			kTextPrefix2 + 3)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectYOffsetScriptElement,			kTextPrefix2 + 4)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectContentScriptElement,			kTextPrefix2 + 5)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectHeightScriptElement,			kTextPrefix2 + 6)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectWidthScriptElement,				kTextPrefix2 + 7)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectStyleScriptElement,				kTextPrefix2 + 8)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectParaStyleScriptElement,			kTextPrefix2 + 9)

DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectHorizontalEnumScriptElement,	kTextPrefix2 + 10)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectHAlignScriptElement,			kTextPrefix2 + 11)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectHRelativeScriptElement,			kTextPrefix2 + 12)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectVerticalEnumScriptElement,		kTextPrefix2 + 13)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectVAlignScriptElement,			kTextPrefix2 + 14)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectRefPointScriptElement,			kTextPrefix2 + 15)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectVRelativeScriptElement,			kTextPrefix2 + 16)
DECLARE_PMID(kScriptInfoIDSpace, kOTFMarkPropertyScriptElement,					kTextPrefix2 + 17)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectDefaultScriptElement,			kTextPrefix2 + 18)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectDefaultPropertyScriptElement,	kTextPrefix2 + 19)

DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectHRefPointEnumScriptElement,		kTextPrefix2 + 20)
DECLARE_PMID(kScriptInfoIDSpace, kBalanceLinesEnumScriptElement,				kTextPrefix2 + 21)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectSpineRelativeScriptElement,		kTextPrefix2 + 22)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectSettingsScriptElement,			kTextPrefix2 + 23)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectVRefPointEnumScriptElement,		kTextPrefix2 + 24)
DECLARE_PMID(kScriptInfoIDSpace, kOTFSlashZeroPropertyScriptElement,			kTextPrefix2 + 25)
DECLARE_PMID(kScriptInfoIDSpace, kOTFHistoricalPropertyScriptElement,			kTextPrefix2 + 26)
DECLARE_PMID(kScriptInfoIDSpace, kOTFStylisticSetsPropertyScriptElement,		kTextPrefix2 + 27)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectSpaceAboveScriptElement,		kTextPrefix2 + 28)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectLockPositionScriptElement,		kTextPrefix2 + 29)

DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectPinPositionScriptElement,		kTextPrefix2 + 30)
DECLARE_PMID(kScriptInfoIDSpace, kOTFLocalePropertyScriptElement,				kTextPrefix2 + 31)
DECLARE_PMID(kScriptInfoIDSpace, kOTPositionalFormEnumScriptElement,			kTextPrefix2 + 32)
DECLARE_PMID(kScriptInfoIDSpace, kDropcapDetailScriptElement,					kTextPrefix2 + 33)
DECLARE_PMID(kScriptInfoIDSpace, kOTPositionalFormScriptElement,				kTextPrefix2 + 34)
DECLARE_PMID(kScriptInfoIDSpace, kRuleAboveKeepInFramePropertyScriptElement,	kTextPrefix2 + 35)
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreEdgeAlignPropertyScriptElement,			kTextPrefix2 + 36)
DECLARE_PMID(kScriptInfoIDSpace, kDuplicateTextMethodScriptElement,				kTextPrefix2 + 37)
DECLARE_PMID(kScriptInfoIDSpace, kEndBaselinePropertyScriptElement,				kTextPrefix2 + 38)
DECLARE_PMID(kScriptInfoIDSpace, kEndHorizontalOffsetPropertyScriptElement,		kTextPrefix2 + 39)

DECLARE_PMID(kScriptInfoIDSpace, kStrokeMiterLimitPropertyScriptElement,		kTextPrefix2 + 40)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeAlignPropertyScriptElement,				kTextPrefix2 + 41)
DECLARE_PMID(kScriptInfoIDSpace, kOutlineJoinPropertyScriptElement,				kTextPrefix2 + 42)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeAlignEnumScriptElement,					kTextPrefix2 + 43)
DECLARE_PMID(kScriptInfoIDSpace, kOutlineJoinEnumScriptElement,					kTextPrefix2 + 44)
DECLARE_PMID(kScriptInfoIDSpace, kEnableStylePreviewPropertyScriptElement,		kTextPrefix2 + 45)
DECLARE_PMID(kScriptInfoIDSpace, kGotoNextXPropertyScriptElement,				kTextPrefix2 + 46)
DECLARE_PMID(kScriptInfoIDSpace, kGotoNextXEnumScriptElement,					kTextPrefix2 + 47)
DECLARE_PMID(kScriptInfoIDSpace, kPageNumberTypePropertyScriptElement,			kTextPrefix2 + 48)
DECLARE_PMID(kScriptInfoIDSpace, kPageNumberTypeEnumScriptElement,				kTextPrefix2 + 49)

DECLARE_PMID(kScriptInfoIDSpace, kRunInLineCountPropertyScriptElement,			kTextPrefix2 + 50)
DECLARE_PMID(kScriptInfoIDSpace, kGrepExpressionPropertyScriptElement,			kTextPrefix2 + 51)
DECLARE_PMID(kScriptInfoIDSpace, kAllLineStylesPropertyScriptElement,			kTextPrefix2 + 52)
DECLARE_PMID(kScriptInfoIDSpace, kAllGrepStylesPropertyScriptElement,			kTextPrefix2 + 53)
DECLARE_PMID(kScriptInfoIDSpace, kRunInLineRepeatPropertyScriptElement,			kTextPrefix2 + 54)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedNestedStylesPropertyScriptElement,		kTextPrefix2 + 55)
DECLARE_PMID(kScriptInfoIDSpace, kAnchoredObjectPositionRefPointScriptElement,	kTextPrefix2 + 56)
//DECLARE_PMID(kScriptInfoIDSpace, kMyFancyNewScriptElement,					kTextPrefix2 + 57)
//DECLARE_PMID(kScriptInfoIDSpace, kMyFancyNewScriptElement,					kTextPrefix2 + 58)
DECLARE_PMID(kScriptInfoIDSpace, kStoryListPropertyScriptElement,				kTextPrefix2 + 59)

DECLARE_PMID(kScriptInfoIDSpace, kBaselineFrameGridObjectScriptElement,			kTextPrefix2 + 60)
DECLARE_PMID(kScriptInfoIDSpace, kBaselineFrameGridPropertyScriptElement,		kTextPrefix2 + 61)
DECLARE_PMID(kScriptInfoIDSpace, kUseCustomBaselineGridPropertyScriptElement,	kTextPrefix2 + 62)
DECLARE_PMID(kScriptInfoIDSpace, kBaselineFrameGridStartingOffsetPropertyScriptElement,		kTextPrefix2 + 63)
DECLARE_PMID(kScriptInfoIDSpace, kBaselineFrameGridRelativeOptionPropertyScriptElement,		kTextPrefix2 + 64)
DECLARE_PMID(kScriptInfoIDSpace, kBaselineFrameGridIncrementPropertyScriptElement,			kTextPrefix2 + 65)
DECLARE_PMID(kScriptInfoIDSpace, kBaselineFrameGridRelativeOptionEnumScriptElement,		kTextPrefix2 + 66)
DECLARE_PMID(kScriptInfoIDSpace, kBaselineFrameGridColorPropertyScriptElement,	kTextPrefix2 + 67)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteFLOEnumScriptElement,					kTextPrefix2 + 68)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteObjectScriptElement, 					kTextPrefix2 + 69)

DECLARE_PMID(kScriptInfoIDSpace, kFootnoteOptionsScriptElement,					kTextPrefix2 + 70)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteOptionsPropertyScriptElement,			kTextPrefix2 + 71)
DECLARE_PMID(kScriptInfoIDSpace, kCreateFootnoteMethodScriptElement,			kTextPrefix2 + 72)
DECLARE_PMID(kScriptInfoIDSpace, kConvertTextToFootnoteMethodScriptElement,		kTextPrefix2 + 73)
DECLARE_PMID(kScriptInfoIDSpace, kConvertFootnoteToTextMethodScriptElement,		kTextPrefix2 + 74)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteRestartEnumScriptElement,				kTextPrefix2 + 75)
DECLARE_PMID(kScriptInfoIDSpace, kFootnotePrefixSuffixEnumScriptElement,		kTextPrefix2 + 76)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNumberingStyleEnumScriptElement,		kTextPrefix2 + 77)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteMarkerStyleEnumScriptElement,			kTextPrefix2 + 78)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteMarkerPositioningEnumScriptElement,	kTextPrefix2 + 79)

DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNumberingStylePropertyScriptElement,	kTextPrefix2 + 80)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteStartAtPropertyScriptElement,			kTextPrefix2 + 81)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteRestartNumberingPropertyScriptElement,kTextPrefix2 + 82)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteShowPrefixSuffixPropertyScriptElement,kTextPrefix2 + 83)
DECLARE_PMID(kScriptInfoIDSpace, kFootnotePrefixPropertyScriptElement, 			kTextPrefix2 + 84)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteSuffixPropertyScriptElement,			kTextPrefix2 + 85)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteApplyParagraphStylePropertyScriptElement,				kTextPrefix2 + 86)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteApplyCharacterStylePropertyScriptElement,				kTextPrefix2 + 87)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteApplyMarkerPositioningPropertyScriptElement,			kTextPrefix2 + 88)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteFLOPropertyScriptElement,				kTextPrefix2 + 89)

DECLARE_PMID(kScriptInfoIDSpace, kFootnoteMinFLOPropertyScriptElement,			kTextPrefix2 + 90)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteSeparatorPropertyScriptElement,		kTextPrefix2 + 91)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteSpaceBetweenPropertyScriptElement,	kTextPrefix2 + 92)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteSpacerPropertyScriptElement,			kTextPrefix2 + 93)
DECLARE_PMID(kScriptInfoIDSpace, kFootnotePlacementPropertyScriptElement,		kTextPrefix2 + 94)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleOnPropertyScriptElement,		kTextPrefix2 + 95)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleTypePropertyScriptElement,		kTextPrefix2 + 96)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleStrokeWeightPropertyScriptElement,				kTextPrefix2 + 97)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleColorPropertyScriptElement,	kTextPrefix2 + 98)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleGapColorPropertyScriptElement,	kTextPrefix2 + 99)

DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleTintPropertyScriptElement,		kTextPrefix2 + 100)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleGapTintPropertyScriptElement,	kTextPrefix2 + 101)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleOverprintPropertyScriptElement,kTextPrefix2 + 102)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleGapOverprintPropertyScriptElement, 			kTextPrefix2 + 103)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleLeftIndentPropertyScriptElement,				kTextPrefix2 + 104)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleWidthPropertyScriptElement,	kTextPrefix2 + 105)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteNewRuleOffsetPropertyScriptElement,	kTextPrefix2 + 106)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleOnPropertyScriptElement,kTextPrefix2 + 107)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleTypePropertyScriptElement,				kTextPrefix2 + 108)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleStrokeWeightPropertyScriptElement,		kTextPrefix2 + 109)

DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleColorPropertyScriptElement,				kTextPrefix2 + 110)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleGapColorPropertyScriptElement,			kTextPrefix2 + 111)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleTintPropertyScriptElement,				kTextPrefix2 + 112)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleGapTintPropertyScriptElement,			kTextPrefix2 + 113)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleOverprintPropertyScriptElement,			kTextPrefix2 + 114)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleGapOverprintPropertyScriptElement,		kTextPrefix2 + 115)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleLeftIndentPropertyScriptElement,		kTextPrefix2 + 116)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleWidthPropertyScriptElement,				kTextPrefix2 + 117)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContinuingRuleOffsetPropertyScriptElement,			kTextPrefix2 + 118)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteStoryOffsetPropertyScriptElement,		kTextPrefix2 + 119)

DECLARE_PMID(kScriptInfoIDSpace, kFootnoteTextFramePropertyScriptElement,		kTextPrefix2 + 120)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteContentsPropertyScriptElement,		kTextPrefix2 + 121)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteSplittingPropertyScriptElement,		kTextPrefix2 + 122)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteStraddlingPropertyScriptElement,      kTextPrefix2 + 123)
//DECLARE_PMID(kScriptInfoIDSpace, kMyFancyNewScriptElement,					kTextPrefix2 + 123)
//DECLARE_PMID(kScriptInfoIDSpace, kMyFancyNewScriptElement,					kTextPrefix2 + 124)
DECLARE_PMID(kScriptInfoIDSpace, kPRBOverprintPropertyScriptElement,			kTextPrefix2 + 125)
DECLARE_PMID(kScriptInfoIDSpace, kPRBGapOverprintPropertyScriptElement,			kTextPrefix2 + 126)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteStyleMethodScriptElement,				kTextPrefix2 + 127)
DECLARE_PMID(kScriptInfoIDSpace, kOverrideTypeEnumScriptElement,				kTextPrefix2 + 128)
DECLARE_PMID(kScriptInfoIDSpace, kClearOverridesMethodScriptElement,			kTextPrefix2 + 129)

DECLARE_PMID(kScriptInfoIDSpace, kClashResolutionStrategyEnumScriptElement,		kTextPrefix2 + 130)
DECLARE_PMID(kScriptInfoIDSpace, kUseNewVerticalScalingPropertyScriptElement,	kTextPrefix2 + 131)
DECLARE_PMID(kScriptInfoIDSpace, kUseCIDMojikumiPropertyScriptElement, 			kTextPrefix2 + 132)
DECLARE_PMID(kScriptInfoIDSpace, kStoryOrientHorizVertEnumScriptElement,		kTextPrefix2 + 133)
DECLARE_PMID(kScriptInfoIDSpace, kTextVariableObjectScriptElement,				kTextPrefix2 + 134)
DECLARE_PMID(kScriptInfoIDSpace, kTextVariableInstanceObjectScriptElement,		kTextPrefix2 + 135)
DECLARE_PMID(kScriptInfoIDSpace, kPageNumberPreferenceObjectScriptElement,		kTextPrefix2 + 136)
DECLARE_PMID(kScriptInfoIDSpace, kChapterNumberPreferenceObjectScriptElement,	kTextPrefix2 + 137)
DECLARE_PMID(kScriptInfoIDSpace, kDatePreferenceObjectScriptElement,			kTextPrefix2 + 138)
DECLARE_PMID(kScriptInfoIDSpace, kFileNamePreferenceObjectScriptElement,		kTextPrefix2 + 139)

DECLARE_PMID(kScriptInfoIDSpace, kMatchCharStylePreferenceObjectScriptElement,	kTextPrefix2 + 140)
DECLARE_PMID(kScriptInfoIDSpace, kMatchParaStylePreferenceObjectScriptElement,	kTextPrefix2 + 141)
DECLARE_PMID(kScriptInfoIDSpace, kCustomTextPreferenceObjectScriptElement,		kTextPrefix2 + 142)
DECLARE_PMID(kScriptInfoIDSpace, kAutoPageInsertScriptElement,					kTextPrefix2 + 143)
DECLARE_PMID(kScriptInfoIDSpace, kAutoPageInsertionEnumScriptElement,			kTextPrefix2 + 144)
DECLARE_PMID(kScriptInfoIDSpace, kCreateTextVariableInstanceMethodScriptElement,kTextPrefix2 + 145)
DECLARE_PMID(kScriptInfoIDSpace, kVariableConvertToTextMethodScriptElement,		kTextPrefix2 + 146)
DECLARE_PMID(kScriptInfoIDSpace, kAutoPageInsertRestrictToMastersScriptElement,	kTextPrefix2 + 147)
DECLARE_PMID(kScriptInfoIDSpace, kEnableDynamicAutoflowScriptElement,			kTextPrefix2 + 148)
DECLARE_PMID(kScriptInfoIDSpace, kDynamicPageDeletionScriptElement,				kTextPrefix2 + 149)

DECLARE_PMID(kScriptInfoIDSpace, kVariableTypeEnumScriptElement,				kTextPrefix2 + 150)
DECLARE_PMID(kScriptInfoIDSpace, kVariableScopeOptionEnumScriptElement,			kTextPrefix2 + 151)
DECLARE_PMID(kScriptInfoIDSpace, kVariableNumberingStyleEnumScriptElement,		kTextPrefix2 + 152)
DECLARE_PMID(kScriptInfoIDSpace, kSearchStrategiesEnumScriptElement,			kTextPrefix2 + 153)
DECLARE_PMID(kScriptInfoIDSpace, kChangeCaseOptionsEnumScriptElement,			kTextPrefix2 + 154)
DECLARE_PMID(kScriptInfoIDSpace, kAutoFlowPreservesRectoVersoScriptElement,		kTextPrefix2 + 155)
DECLARE_PMID(kScriptInfoIDSpace, kVerticalJustBalancePropertyScriptElement,		kTextPrefix2 + 156)
DECLARE_PMID(kScriptInfoIDSpace, kCaptionMetadataProviderPropertyScriptElement,	kTextPrefix2 + 157)
DECLARE_PMID(kScriptInfoIDSpace, kCaptionVariablePreferenceObjectScriptElement,	kTextPrefix2 + 158)
DECLARE_PMID(kScriptInfoIDSpace, kForceDeleteStyleMethodScriptElement,			kTextPrefix2 + 159)

DECLARE_PMID(kScriptInfoIDSpace, kAssociatedInstancesPropertyScriptElement,		kTextPrefix2 + 160)
DECLARE_PMID(kScriptInfoIDSpace, kVariableTypePropertyScriptElement,			kTextPrefix2 + 161)
DECLARE_PMID(kScriptInfoIDSpace, kAssociatedTextVariablePropertyScriptElement,	kTextPrefix2 + 162)
DECLARE_PMID(kScriptInfoIDSpace, kIncludePathPropertyScriptElement,				kTextPrefix2 + 163)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeExtensionPropertyScriptElement,		kTextPrefix2 + 164)
DECLARE_PMID(kScriptInfoIDSpace, kTextBeforePropertyScriptElement,				kTextPrefix2 + 165)
DECLARE_PMID(kScriptInfoIDSpace, kTextAfterPropertyScriptElement,				kTextPrefix2 + 166)
DECLARE_PMID(kScriptInfoIDSpace, kScopePropertyScriptElement,					kTextPrefix2 + 167)
DECLARE_PMID(kScriptInfoIDSpace, kSearchStrategyPropertyScriptElement,			kTextPrefix2 + 168)
//DECLARE_PMID(kScriptInfoIDSpace, kMyFancyNewScriptElement,					kTextPrefix2 + 169)

DECLARE_PMID(kScriptInfoIDSpace, kVariableNumberFormatPropertyScriptElement,	kTextPrefix2 + 170)
DECLARE_PMID(kScriptInfoIDSpace, kVariableOptionsPropertyScriptElement,			kTextPrefix2 + 171)
DECLARE_PMID(kScriptInfoIDSpace, kVariableDateFormatPropertyScriptElement,		kTextPrefix2 + 172)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteEndPunctuationPropertyScriptElement,	kTextPrefix2 + 173)
DECLARE_PMID(kScriptInfoIDSpace, kChangeCasePropertyScriptElement,				kTextPrefix2 + 174)
DECLARE_PMID(kScriptInfoIDSpace, kRootParagraphStyleGroupObjectScriptElement,	kTextPrefix2 + 175)
DECLARE_PMID(kScriptInfoIDSpace, kRootCharacterStyleGroupObjectScriptElement,	kTextPrefix2 + 176)
DECLARE_PMID(kScriptInfoIDSpace, kStyleNamePropertyScriptElement,				kTextPrefix2 + 177)
//DECLARE_PMID(kScriptInfoIDSpace, kMyFancyNewScriptElement,					kTextPrefix2 + 178)
DECLARE_PMID(kScriptInfoIDSpace, kResultTextPropertyScriptElement,				kTextPrefix2 + 179)

DECLARE_PMID(kScriptInfoIDSpace, kCreateStyleExportTagMapMethodScriptElement,	kTextPrefix2 + 180)
DECLARE_PMID(kScriptInfoIDSpace, kStyleExportTagMapObjectScriptElement,			kTextPrefix2 + 181)
DECLARE_PMID(kScriptInfoIDSpace, kExportTypePropertyScriptElement,				kTextPrefix2 + 182)
DECLARE_PMID(kScriptInfoIDSpace, kExportTagDataTagPropertyScriptElement,		kTextPrefix2 + 183)
DECLARE_PMID(kScriptInfoIDSpace, kExportTagDataClassPropertyScriptElement,		kTextPrefix2 + 184)
DECLARE_PMID(kScriptInfoIDSpace, kExportTagDataAttributesPropertyScriptElement,	kTextPrefix2 + 185)
DECLARE_PMID(kScriptInfoIDSpace, kExportBreakHTMLFileInEPUBPropertyScriptElement,kTextPrefix2 + 186)
//DECLARE_PMID(kScriptInfoIDSpace, kMyFancyNewScriptElement,					kTextPrefix2 + 187)

DECLARE_PMID(kScriptInfoIDSpace, kAutoSizeDimensionEnumScriptElement,			kTextPrefix2 + 188)
DECLARE_PMID(kScriptInfoIDSpace, kAutoSizeRefPointEnumScriptElement,			kTextPrefix2 + 189)
DECLARE_PMID(kScriptInfoIDSpace, kAutoSizeDimensionPropertyScriptElement,		kTextPrefix2 + 190)
DECLARE_PMID(kScriptInfoIDSpace, kAutoSizeRefPointPropertyScriptElement,		kTextPrefix2 + 191)
DECLARE_PMID(kScriptInfoIDSpace, kAutoSizeHasMinHeightPropertyScriptElement,	kTextPrefix2 + 192)
DECLARE_PMID(kScriptInfoIDSpace, kAutoSizeMinHeightValuePropertyScriptElement,	kTextPrefix2 + 193)
DECLARE_PMID(kScriptInfoIDSpace, kAutoSizeHasMinWidthPropertyScriptElement,		kTextPrefix2 + 194)
DECLARE_PMID(kScriptInfoIDSpace, kAutoSizeMinWidthValuePropertyScriptElement,	kTextPrefix2 + 195)
DECLARE_PMID(kScriptInfoIDSpace, kAutoSizeNoLineBreakPropertyScriptElement,		kTextPrefix2 + 196)

DECLARE_PMID(kScriptInfoIDSpace, kUseHalfWidthQuotesPropertyScriptElement,		kTextPrefix2 + 197)
DECLARE_PMID(kScriptInfoIDSpace, kUseFlexibleColumnWidthPropertyScriptElement,		kTextPrefix2 + 198)
DECLARE_PMID(kScriptInfoIDSpace, kTextColumnMaxWidthPropertyScriptElement,		kTextPrefix2 + 199)

DECLARE_PMID(kScriptInfoIDSpace, kParagraphStyleSetObjectScriptElement, 		kTextPrefix2 + 200)
DECLARE_PMID(kScriptInfoIDSpace, kCharacterStyleSetObjectScriptElement, 		kTextPrefix2 + 201)
DECLARE_PMID(kScriptInfoIDSpace, kMoveStyleMethodScriptElement, 				kTextPrefix2 + 202)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteStyleSetMethodScriptElement, 			kTextPrefix2 + 203)
DECLARE_PMID(kScriptInfoIDSpace, kAllParagraphStylesPropertyScriptElement, 		kTextPrefix2 + 204)
DECLARE_PMID(kScriptInfoIDSpace, kAllCharacterStylesPropertyScriptElement, 		kTextPrefix2 + 205)
DECLARE_PMID(kScriptInfoIDSpace, kExportStrokeStyleMethodScriptElement,			kTextPrefix2 + 206)
DECLARE_PMID(kScriptInfoIDSpace, kGaijiOwnedItemKeyPropertyScriptElement,		kTextPrefix2 + 207)
DECLARE_PMID(kScriptInfoIDSpace, kTextTextIterObjectScriptElement,				kTextPrefix2 + 208)
DECLARE_PMID(kScriptInfoIDSpace, kParaTextIterObjectScriptElement,				kTextPrefix2 + 209)

DECLARE_PMID(kScriptInfoIDSpace, kParaStyleTextIterObjectScriptElement,			kTextPrefix2 + 210)
DECLARE_PMID(kScriptInfoIDSpace, kCharStyleTextIterObjectScriptElement,			kTextPrefix2 + 211)
DECLARE_PMID(kScriptInfoIDSpace, kObjectTextIterObjectScriptElement,			kTextPrefix2 + 212)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentRangeStartPropertyScriptElement,		kTextPrefix2 + 214)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentRangeEndPropertyScriptElement,			kTextPrefix2 + 215)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentTextPropertyScriptElement,				kTextPrefix2 + 216)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentStyleReferencePropertyScriptElement,	kTextPrefix2 + 217)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentLocalOverridesPropertyScriptElement,	kTextPrefix2 + 218)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentObjectPropertyScriptElement,			kTextPrefix2 + 219)

DECLARE_PMID(kScriptInfoIDSpace, kAdvanceIterMethodScriptElement,				kTextPrefix2 + 220)
DECLARE_PMID(kScriptInfoIDSpace, kAddNothingEnumToCharStylePropsMetadataScriptElement,			kTextPrefix2 + 221)
DECLARE_PMID(kScriptInfoIDSpace, kDontAddToCharStylePropsMetadataScriptElement,	kTextPrefix2 + 222)
DECLARE_PMID(kScriptInfoIDSpace, kCustomTextINXPolicies50MetadataScriptElement,	kTextPrefix2 + 223)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentNumSpecialAnchorCharsScriptElement,	kTextPrefix2 + 224)
DECLARE_PMID(kScriptInfoIDSpace, kParagraphStyleRangeObjectScriptElement,		kTextPrefix2 + 225)
DECLARE_PMID(kScriptInfoIDSpace, kCharacterStyleRangeObjectScriptElement,		kTextPrefix2 + 226)
DECLARE_PMID(kScriptInfoIDSpace, kXMLTextIterObjectScriptElement,				kTextPrefix2 + 227)
DECLARE_PMID(kScriptInfoIDSpace, kTextContentObjectScriptElement,				kTextPrefix2 + 228)
DECLARE_PMID(kScriptInfoIDSpace, kTextBreakObjectScriptElement,					kTextPrefix2 + 229)

DECLARE_PMID(kScriptInfoIDSpace, kShowTextMethodScriptElement,					kTextPrefix2 + 230)

DECLARE_PMID(kScriptInfoIDSpace, kParaAttrKeepWithPrevPropertyScriptElement,					kTextPrefix2 + 231)
DECLARE_PMID(kScriptInfoIDSpace, kParaAttrSpanColumnCountPropertyScriptElement,					kTextPrefix2 + 232)
DECLARE_PMID(kScriptInfoIDSpace, kParaAttrSpanColumnTypeEnumScriptElement,					kTextPrefix2 + 233)
DECLARE_PMID(kScriptInfoIDSpace, kParaAttrSpanColumnTypePropertyScriptElement,					kTextPrefix2 + 234)
DECLARE_PMID(kScriptInfoIDSpace, kParaAttrSplitColumnInsideGutterPropertyScriptElement,					kTextPrefix2 + 235)
DECLARE_PMID(kScriptInfoIDSpace, kParaAttrSplitColumnOutsideGutterPropertyScriptElement,					kTextPrefix2 + 236)
DECLARE_PMID(kScriptInfoIDSpace, kParaAttrSpanColumnCountEnumScriptElement,					kTextPrefix2 + 237)
DECLARE_PMID(kScriptInfoIDSpace, kParaAttrSpanColumnMinSpaceBeforePropertyScriptElement,					kTextPrefix2 + 238)
DECLARE_PMID(kScriptInfoIDSpace, kParaAttrSpanColumnMinSpaceAfterPropertyScriptElement,					kTextPrefix2 + 239)

DECLARE_PMID(kScriptInfoIDSpace, kInsertAnchoredObjectMethodScriptElement,		kTextPrefix2 + 240)
DECLARE_PMID(kScriptInfoIDSpace, kExportEmitCSSForStylePropertyScriptElement,	kTextPrefix2 + 241)

DECLARE_PMID(kScriptInfoIDSpace, kEmptyRunInStylesPropertyScriptElement,		kTextPrefix2 + 242)
DECLARE_PMID(kScriptInfoIDSpace, kEmptyRunInLineStylesPropertyScriptElement,	kTextPrefix2 + 243)
DECLARE_PMID(kScriptInfoIDSpace, kEmptyGrepStylesPropertyScriptElement,			kTextPrefix2 + 244)

DECLARE_PMID(kScriptInfoIDSpace, kPBSOffsetLPropertyScriptElement, kTextPrefix2 + 245)
DECLARE_PMID(kScriptInfoIDSpace, kPBSOffsetRPropertyScriptElement, kTextPrefix2 + 246)
DECLARE_PMID(kScriptInfoIDSpace, kPBSOffsetTPropertyScriptElement, kTextPrefix2 + 247)
DECLARE_PMID(kScriptInfoIDSpace, kPBSOffsetBPropertyScriptElement, kTextPrefix2 + 248)
DECLARE_PMID(kScriptInfoIDSpace, kPBSWidthEnumScriptElement, kTextPrefix2 + 249)
DECLARE_PMID(kScriptInfoIDSpace, kPBSWidthPropertyScriptElement, kTextPrefix2 + 250)
DECLARE_PMID(kScriptInfoIDSpace, kPBSClipToFramePropertyScriptElement, kTextPrefix2 + 251)
DECLARE_PMID(kScriptInfoIDSpace, kPBSSuppressPrintingPropertyScriptElement, kTextPrefix2 + 252)
DECLARE_PMID(kScriptInfoIDSpace, kPBSFillOverprintPropertyScriptElement, kTextPrefix2 + 253)
DECLARE_PMID(kScriptInfoIDSpace, kPBSFillTintPropertyScriptElement, kTextPrefix2 + 254)
DECLARE_PMID(kScriptInfoIDSpace, kPBSFillColorPropertyScriptElement, kTextPrefix2 + 255)
DECLARE_PMID(kScriptInfoIDSpace, kPBSTopOriginPropertyScriptElement, kTextPrefix3 + 1)
DECLARE_PMID(kScriptInfoIDSpace, kPBSBottomOriginPropertyScriptElement, kTextPrefix3 + 2)
DECLARE_PMID(kScriptInfoIDSpace, kPBSFillOnPropertyScriptElement, kTextPrefix3 + 3)
DECLARE_PMID(kScriptInfoIDSpace, kPBSTopOriginEnumScriptElement, kTextPrefix3 + 4)
DECLARE_PMID(kScriptInfoIDSpace, kPBSBottomOriginEnumScriptElement, kTextPrefix3 + 5)

DECLARE_PMID(kScriptInfoIDSpace, kStyleUniqueIDPropertyScriptElement, kTextPrefix3 + 6)

DECLARE_PMID(kScriptInfoIDSpace, kUserTextPropertyScriptElement, kTextPrefix3 + 7)

// Following are obsolete since 13.1. The footnote option properties are being merged into the textFramePreferences object
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameFootnoteOptionsObjectScriptElement, kTextPrefix3 + 8)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameFootnoteOptionsPropertyScriptElement, kTextPrefix3 + 9)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameFootnoteOptionsEnableOverridesPropertyScriptElement, kTextPrefix3 + 10)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameFootnoteOptionsSpanFootnotesAcrossPropertyScriptElement, kTextPrefix3 + 11)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameFootnoteOptionsMinimumSpacingPropertyScriptElement, kTextPrefix3 + 12)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameFootnoteOptionsSpaceBetweenFootnotesPropertyScriptElement, kTextPrefix3 + 13)
// END OBSOLETE FOOTNOTE OPTIONS

DECLARE_PMID(kScriptInfoIDSpace, kCreateEndnoteAnchorMethodScriptElement, kTextPrefix3 + 14)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteObjectScriptElement, kTextPrefix3 + 15)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteOptionsScriptElement, kTextPrefix3 + 16)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteOptionsPropertyScriptElement, kTextPrefix3 + 17)
DECLARE_PMID(kScriptInfoIDSpace, kAppendTextInEndnoteMethodScriptElement, kTextPrefix3 + 18)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteContentsPropertyScriptElement, kTextPrefix3 + 19)
//GAP
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteTitlePropertyScriptElement, kTextPrefix3 + 21)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteApplyTitleParagraphStylePropertyScriptElement, kTextPrefix3 + 22)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteNumberingStyleEnumScriptElement, kTextPrefix3 + 23)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteNumberingStylePropertyScriptElement, kTextPrefix3 + 24)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteStartAtPropertyScriptElement, kTextPrefix3 + 25)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteRestartEnumScriptElement, kTextPrefix3 + 26)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteRestartNumberingPropertyScriptElement, kTextPrefix3 + 27)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteMarkerPositioningEnumScriptElement, kTextPrefix3 + 28)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteApplyMarkerPositioningPropertyScriptElement, kTextPrefix3 + 29)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteApplyMarkerCharacterStylePropertyScriptElement, kTextPrefix3 + 30)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteApplyParagraphStylePropertyScriptElement, kTextPrefix3 + 31)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteSeparatorPropertyScriptElement, kTextPrefix3 + 32)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteScopeEnumScriptElement, kTextPrefix3 + 33)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteScopePropertyScriptElement, kTextPrefix3 + 34)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteFrameCreateEnumScriptElement, kTextPrefix3 + 35)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteFrameCreatePropertyScriptElement, kTextPrefix3 + 36)
//GAP
DECLARE_PMID(kScriptInfoIDSpace, kEndnotePrefixSuffixEnumScriptElement, kTextPrefix3 + 38)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteShowPrefixSuffixPropertyScriptElement, kTextPrefix3 + 39)
DECLARE_PMID(kScriptInfoIDSpace, kEndnotePrefixPropertyScriptElement, kTextPrefix3 + 40)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteSuffixPropertyScriptElement, kTextPrefix3 + 41)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteAnchorObjectScriptElement, kTextPrefix3 + 42)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteRangeObjectScriptElement, kTextPrefix3 + 43)
DECLARE_PMID(kScriptInfoIDSpace, kCreateEndnoteRangeMethodScriptElement, kTextPrefix3 + 44)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteRangeTextPropertyScriptElement, kTextPrefix3 + 45)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteAnchorPropertyScriptElement, kTextPrefix3 + 46)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteRangePropertyScriptElement, kTextPrefix3 + 47)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteStoryPropertyScriptElement, kTextPrefix3 + 48)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteTextFrameObjectScriptElement, kTextPrefix3 + 49)





DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeGapOverprintPropertyScriptElement, kTextPrefix3 + 54)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeGapTintPropertyScriptElement, kTextPrefix3 + 55)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeGapColorPropertyScriptElement, kTextPrefix3 + 56)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeTypePropertyScriptElement, kTextPrefix3 + 57)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeOnPropertyScriptElement, kTextPrefix3 + 59)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeOverprintPropertyScriptElement, kTextPrefix3 + 60)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeTintPropertyScriptElement, kTextPrefix3 + 61)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeColorPropertyScriptElement, kTextPrefix3 + 62)

DECLARE_PMID(kScriptInfoIDSpace, kPBWidthEnumScriptElement, kTextPrefix3 + 63)
DECLARE_PMID(kScriptInfoIDSpace, kPBTopOriginEnumScriptElement, kTextPrefix3 + 64)
DECLARE_PMID(kScriptInfoIDSpace, kPBBottomOriginEnumScriptElement, kTextPrefix3 + 65)
DECLARE_PMID(kScriptInfoIDSpace, kPBTopOriginPropertyScriptElement, kTextPrefix3 + 66)
DECLARE_PMID(kScriptInfoIDSpace, kPBBottomOriginPropertyScriptElement, kTextPrefix3 + 67)

DECLARE_PMID(kScriptInfoIDSpace, kPBOffsetRPropertyScriptElement, kTextPrefix3 + 68)
DECLARE_PMID(kScriptInfoIDSpace, kPBOffsetTPropertyScriptElement, kTextPrefix3 + 69)
DECLARE_PMID(kScriptInfoIDSpace, kPBOffsetBPropertyScriptElement, kTextPrefix3 + 70)
DECLARE_PMID(kScriptInfoIDSpace, kPBOffsetLPropertyScriptElement, kTextPrefix3 + 71)
DECLARE_PMID(kScriptInfoIDSpace, kPBWidthPropertyScriptElement, kTextPrefix3 + 72)
DECLARE_PMID(kScriptInfoIDSpace, kPBStrokeEndJoinPropertyScriptElement, kTextPrefix3 + 73)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeEndCapPropertyScriptElement, kTextPrefix3 + 74)

DECLARE_PMID(kScriptInfoIDSpace, kParaShadeCornerRadiusTopLeftPropertyScriptElement, kTextPrefix3 + 76)
DECLARE_PMID(kScriptInfoIDSpace, kParaShadeCornerOptionsTopLeftPropertyScriptElement, kTextPrefix3 + 77)
DECLARE_PMID(kScriptInfoIDSpace, kParaShadeCornerRadiusTopRightPropertyScriptElement, kTextPrefix3 + 78)
DECLARE_PMID(kScriptInfoIDSpace, kParaShadeCornerOptionsTopRightPropertyScriptElement, kTextPrefix3 + 79)
DECLARE_PMID(kScriptInfoIDSpace, kParaShadeCornerRadiusBottomLeftPropertyScriptElement, kTextPrefix3 + 80)
DECLARE_PMID(kScriptInfoIDSpace, kParaShadeCornerOptionsBottomLeftPropertyScriptElement, kTextPrefix3 + 81)
DECLARE_PMID(kScriptInfoIDSpace, kParaShadeCornerRadiusBottomRightPropertyScriptElement, kTextPrefix3 + 82)
DECLARE_PMID(kScriptInfoIDSpace, kParaShadeCornerOptionsBottomRightPropertyScriptElement, kTextPrefix3 + 83)
DECLARE_PMID(kScriptInfoIDSpace, kParaBorderCornerRadiusTopLeftPropertyScriptElement, kTextPrefix3 + 84)
DECLARE_PMID(kScriptInfoIDSpace, kParaBorderCornerOptionsTopLeftPropertyScriptElement, kTextPrefix3 + 85)
DECLARE_PMID(kScriptInfoIDSpace, kParaBorderCornerRadiusTopRightPropertyScriptElement, kTextPrefix3 + 86)
DECLARE_PMID(kScriptInfoIDSpace, kParaBorderCornerOptionsTopRightPropertyScriptElement, kTextPrefix3 + 87)
DECLARE_PMID(kScriptInfoIDSpace, kParaBorderCornerRadiusBottomLeftPropertyScriptElement, kTextPrefix3 + 88)
DECLARE_PMID(kScriptInfoIDSpace, kParaBorderCornerOptionsBottomLeftPropertyScriptElement, kTextPrefix3 + 89)
DECLARE_PMID(kScriptInfoIDSpace, kParaBorderCornerRadiusBottomRightPropertyScriptElement, kTextPrefix3 + 90)
DECLARE_PMID(kScriptInfoIDSpace, kParaBorderCornerOptionsBottomRightPropertyScriptElement, kTextPrefix3 + 91)

//Some more enteries from scripting side for endnote
DECLARE_PMID(kScriptInfoIDSpace, kCreateEndnoteMethodScriptElement, kTextPrefix3 + 92)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteEndnoteAnchorMethodScriptElement, kTextPrefix3 + 93)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteEndnoteRangeMethodScriptElement, kTextPrefix3 + 94)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteRangeStartIndexPropertyScriptElement, kTextPrefix3 + 95)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteRangeEndIndexPropertyScriptElement, kTextPrefix3 + 96)
DECLARE_PMID(kScriptInfoIDSpace, kIsEndnoteStoryPropertyScriptElement, kTextPrefix3 + 97)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteRangeContentPropertyScriptElement, kTextPrefix3 + 98)
DECLARE_PMID(kScriptInfoIDSpace, kInsertTextInEndnoteMethodScriptElement, kTextPrefix3 + 99)
DECLARE_PMID(kScriptInfoIDSpace, kEndnoteStoryOffsetPropertyScriptElement, kTextPrefix3 + 100)
DECLARE_PMID(kScriptInfoIDSpace, kExportIncludeClassForStylePropertyScriptElement, kTextPrefix3 + 101)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeWeightLeftPropertyScriptElement, kTextPrefix3 + 102)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeWeightTopPropertyScriptElement, kTextPrefix3 + 103)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeWeightRightPropertyScriptElement, kTextPrefix3 + 104)
DECLARE_PMID(kScriptInfoIDSpace, kPBSStrokeWeightBottomPropertyScriptElement, kTextPrefix3 + 105)
DECLARE_PMID(kScriptInfoIDSpace, kTextAttrPBSParagraphFlowScriptElement, kTextPrefix3 + 106)
DECLARE_PMID(kScriptInfoIDSpace, kProviderHyphenationStylePropertyScriptElement, kTextPrefix3 + 107)
DECLARE_PMID(kScriptInfoIDSpace, kProviderHyphenationStyleEnumScriptElement, kTextPrefix3 + 108)

// Entry for Merging Borders -- Target version 13.1 and above.
DECLARE_PMID(kScriptInfoIDSpace, kPBSMergeBordersPropertyScriptElement, kTextPrefix3 + 109)

// New script ids for footnote options being merged into textFramePreferences
DECLARE_PMID(kScriptInfoIDSpace, kTFFootnoteOptionsEnableOverridesPropertyScriptElement, kTextPrefix3 + 110)
DECLARE_PMID(kScriptInfoIDSpace, kTFFootnoteOptionsSpanFootnotesAcrossPropertyScriptElement, kTextPrefix3 + 111)
DECLARE_PMID(kScriptInfoIDSpace, kTFFootnoteOptionsMinimumSpacingPropertyScriptElement, kTextPrefix3 + 112)
DECLARE_PMID(kScriptInfoIDSpace, kTFFootnoteOptionsSpaceBetweenFootnotesPropertyScriptElement, kTextPrefix3 + 113)
DECLARE_PMID(kScriptInfoIDSpace, kSameParaSpacingPropertyScriptElement,         kTextPrefix3 + 114)
DECLARE_PMID(kScriptInfoIDSpace, kSameParaSpacingEnumScriptElement,         kTextPrefix3 + 115)
DECLARE_PMID(kScriptInfoIDSpace, kSynchronousSmartTextReflowScriptElement, kTextPrefix3 + 116)

// Script ids for text frame vertical column rule
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleEnableOverridesPropertyScriptElement, kTextPrefix3 + 117)
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleOffsetPropertyScriptElement, kTextPrefix3 + 118)
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleTopInsetPropertyScriptElement, kTextPrefix3 + 119)
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleInsetChainOverridesPropertyScriptElement, kTextPrefix3 + 120)
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleBottomInsetPropertyScriptElement, kTextPrefix3 + 121)
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleWidthPropertyScriptElement, kTextPrefix3 + 122)
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleStokeColorPropertyScriptElement, kTextPrefix3 + 123)
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleStrokeTypePropertyScriptElement, kTextPrefix3 + 124)
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleTintPropertyScriptElement, kTextPrefix3 + 125)
DECLARE_PMID(kScriptInfoIDSpace, kTFVerticalRuleOverprintOverridesPropertyScriptElement, kTextPrefix3 + 126)
DECLARE_PMID(kScriptInfoIDSpace, kShapeIndicAndLatinWithHarfbuzzScriptElement, kTextPrefix3 + 127)
DECLARE_PMID(kScriptInfoIDSpace, kDesignAxesScriptElement, kTextPrefix3 + 128)
DECLARE_PMID(kScriptInfoIDSpace, kSetNthDesignAxisScriptElement, kTextPrefix3 + 129)
DECLARE_PMID(kScriptInfoIDSpace, kFontSyncPreferenceObjectScriptElement, kTextPrefix3 + 130)
DECLARE_PMID(kScriptInfoIDSpace, kFontSyncPreferencePropertyScriptElement, kTextPrefix3 + 131)
DECLARE_PMID(kScriptInfoIDSpace, kAutoActivateFontPropertyScriptElement, kTextPrefix3 + 132)

END_IDS() //causing problems on windows .fr files


#ifndef RESOURCE_NUMBER	 //avoid errors in TextID.fr

//ScriptIDs
enum TextScriptIDs
{
	// Text Variables
	c_TextVariable				= 'SPtv',
	c_TextVariables				= 'TVc2',
	c_TextVariableInstance		= 'TVc3',
	c_TextVariableInstances		= 'TVc4',
	c_PageNumberPrefs 			= 'TVPl',
	c_ChapterNumberPrefs		= 'TVPn',
	c_DatePrefs 				= 'TVPd',
	c_FileNamePrefs				= 'TVPf',
	c_CaptionMetadataPrefs		= 'TVPm',
	c_MatchCharStylePrefs 		= 'TVCr',
	c_MatchParaStylePrefs 		= 'TVPr',
	c_CustomTextPrefs 			= 'TVPc',

	p_VariableOptions			= 'TVop',
	p_TextBefore				= 'TVtb',
	p_TextAfter					= 'TVta',
	p_VariableType				= 'TVbt',
	p_Scope						= 'TVsc',
	p_SearchStrategy			= 'TVss',
	p_ChangeCase				= 'TVcc',
	p_DeleteEndPunctuation		= 'TVde',
	p_IncludeExtension			= 'TVee',
	p_IncludePath				= 'TVep',
	p_CaptionMetadataProvider	= 'TVmp',
	p_ResultText				= 'TVeq',
	p_AssociatedTextVariable	= 'TVrf',
	p_AssociatedInstances		= 'TVai',

	en_TextVariables = 'TVmt',
		en_StaticText			= 'TVst',
		en_CustomText			= 'TVct',
		en_Filename				= 'TVfn',
		en_CaptionMetadata		= 'TVcm',
		en_LastPageNumber		= 'TVtp',
		en_ChapterNumber		= 'cntp',
		en_OutputDate			= 'TVod',
		en_CreationDate			= 'TVcd',
		en_ModificationDate		= 'TVmd',
		en_MatchCharStyle		= 'TVcS',
		en_MatchParaStyle		= 'TVpS',
		//en_MatchStyle			= 'TVms',
		en_XRefPageNumber		= 'TVxr',
		en_XRefChapterNumber	= 'TVcn',

	en_VariableNumberStyles		= 'TVnf',
		// see Generic number formatters (e.g. en_Arabic, en_RomanLower, etc)

	en_ChangeCaseOptions		= 'TVsf',
    en_SameParaSpacing 			= 'TVCS',

	en_VariableScopes			= 'TVpc',
		en_ScopeDoc				= 'CSdo',
		en_ScopeSection			= 'CSse',

	en_SearchStrategies			= 'TVsS',
		en_SearchFirstOnPage	= 'SAfp',
		en_SearchLastOnPage		= 'SAlp',

	// footnotes
	c_Footnote								= 'FNcl',
	c_Footnotes								= 'FNc2',
	c_FootnoteOptions						= 'FNop',

	//Endnote
	c_Endnote                   = 'ENob',
	c_Endnotes                  = 'ENos',
	c_EndnoteOptions            = 'Enop',
	c_EndnoteAnchor                   = 'ENan',
	c_EndnoteAnchors			= 'ENas',
	c_EndnoteRange              = 'Enrn',
	c_EndnoteRanges				= 'Enrs',

	en_FootnoteRestartEnum					= 'FNrs',
		en_FootnoteDontRestart				= 'Fdrs',
		en_FootnotePageRestart				= 'Fprs',
		en_FootnoteSpreadRestart			= 'Fsrs',
		en_FootnoteSectionRestart			= 'Fers',

	en_FootnotePrefixSuffixEnum				= 'FNps',
		en_FootnotePrefixSuffixNone			= 'Fpsn',
		en_FootnotePrefixSuffixReference	= 'Fpsr',
		en_FootnotePrefixSuffixMarker		= 'Fpst',
		en_FootnotePrefixSuffixBoth			= 'Fpsb',

	en_FootnoteStyle						= 'FNst',
		en_Symbols							= 'Fssy',
	en_FNFirstBaselineEnum					= 'FNFe',

	en_FootnoteMarkerPositioning			= 'FNme',
		en_NormalMarker						= 'Fmnp',
		en_SuperscriptMarker				= 'FmSp',
		en_SubscriptMarker					= 'Fmsp',
		en_RubyMarker						= 'Fmrp',

	en_EndnoteStyle							= 'ENst',

	en_EndnoteRestartEnum					= 'ENrs',
		en_EndnoteContinuous				= 'Edrs',
		en_EndnoteStoryRestart				= 'Esrs',

	en_EndnoteMarkerPositioning				= 'ENme',

	en_EndnoteScopeEnum						= 'ENse',
		en_EndnoteStoryScope				= 'ENss',
		en_EndnoteDocumentScope				= 'ENds',

	en_EndnoteFrameCreateEnum				= 'ENfe',
		en_EndnotePlaceGun					= 'ENpg',
		en_EndnoteNewPage					= 'ENnp',

	en_EndnotePrefixSuffixEnum				= 'ENps',


	en_GotoNextX					= 'egtx',
	en_PageNumberType				= 'epnt',

	// Text (Iterator) Objects
	c_TextIter						= 'titr',
	c_ParaIter						= 'pitr',
	c_ParaStyleIter					= 'pstr',
	c_CharStyleIter					= 'cstr',
	c_ObjectIter					= 'oitr',
	c_XMLIter 						= 'xitr',
	c_TextIters						= 'ttrs',
	c_ParaIters						= 'ptrs',
	c_ParaStyleIters				= 'psrs',
	c_CharStyleIters				= 'csrs',
	c_ObjectIters					= 'otrs',
	c_XMLIters 						= 'xtrs',
	p_CurrentRangeStart				= 'crrs',
	p_CurrentRangeEnd				= 'crre',
	p_CurrentText					= 'crtx',
	p_CurrentStyleReference			= 'crsr',
	p_CurrentLocalOverrides			= 'crlo',
	p_CurrentObject					= 'crob',
	p_CurrentNumSpecialAnchorChars	= 'csac',
	e_AdvanceIter					= 'advi',

	// Text style range objects for use in INX-Alt only
	c_ParagraphStyleRange			= 'psrg',
	c_ParagraphStyleRanges			= 'prgs',
	c_CharacterStyleRange			= 'csrg',
	c_CharacterStyleRanges			= 'crgs',
	c_TextContent					= 'tcnt',
	c_TextBreak						= 'tbrk',

	p_AppliedNestedStyle			= 'apns',
	p_AppliedNestedStyles			= 'apss',

	p_AOPositionRefPoint			= 'AOPr',

	kLastTextScriptID
} ;

//GUIDS
// {180F4549-1934-4f64-B294-DEA5926B156C}
#define kGaijiOwnedItem_CLSID { 0x180f4549, 0x1934, 0x4f64, { 0xb2, 0x94, 0xde, 0xa5, 0x92, 0x6b, 0x15, 0x6c } }
// {72EB2A19-7535-42a0-873C-80C1186CBD39}
#define kGaijiOwnedItems_CLSID { 0x72eb2a19, 0x7535, 0x42a0, { 0x87, 0x3c, 0x80, 0xc1, 0x18, 0x6c, 0xbd, 0x39 } }
// {EE96407D-06C6-11d2-AAC9-00C04FA349C7}
#define kText_CLSID { 0xee96407d, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE96407E-06C6-11d2-AAC9-00C04FA349C7}
#define kTexts_CLSID { 0xee96407e, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964064-06C6-11d2-AAC9-00C04FA349C7}
#define kCharacter_CLSID { 0xee964064, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964076-06C6-11d2-AAC9-00C04FA349C7}
#define kCharacters_CLSID { 0xee964076, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964078-06C6-11d2-AAC9-00C04FA349C7}
#define kWord_CLSID { 0xee964078, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964068-06C6-11d2-AAC9-00C04FA349C7}
#define kWords_CLSID { 0xee964068, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964074-06C6-11d2-AAC9-00C04FA349C7}
#define kTextLine_CLSID { 0xee964074, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE96406A-06C6-11d2-AAC9-00C04FA349C7}
#define kTextLines_CLSID { 0xee96406a, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964072-06C6-11d2-AAC9-00C04FA349C7}
#define kTextColumn_CLSID { 0xee964072, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {77617588-D3DE-11d1-AAA6-00C04FA349C7}
#define kTextColumns_CLSID { 0x77617588, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE96407B-06C6-11d2-AAC9-00C04FA349C7}
#define kParagraph_CLSID { 0xee96407b, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE96407C-06C6-11d2-AAC9-00C04FA349C7}
#define kParagraphs_CLSID { 0xee96407c, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964071-06C6-11d2-AAC9-00C04FA349C7}
#define kInsertPoint_CLSID { 0xee964071, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {496F0BD9-7834-11d2-AAF0-00C04FA37726}
#define kInsertionPoints_CLSID { 0x496f0bd9, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {A3736541-4F5C-11d2-AB07-00C04FA349C7}
#define kTextStyleRange_CLSID { 0xa3736541, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A3736542-4F5C-11d2-AB07-00C04FA349C7}
#define kTextStyleRanges_CLSID { 0xa3736542, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {77617580-D3DE-11d1-AAA6-00C04FA349C7}
#define kTextFrame_CLSID { 0x77617580, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {77617581-D3DE-11d1-AAA6-00C04FA349C7}
#define kTextFrames_CLSID { 0x77617581, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {49734F44-6810-46DB-8FF2-9126F875EFFB}
#define kEndnoteTextFrame_CLSID { 0x49734f44, 0x6810, 0x46db, { 0x8f, 0xf2, 0x91, 0x26, 0xf8, 0x75, 0xef, 0xfb } }
// {FD35DF8D-2EBF-44C4-91A9-602B70AFB89F}
#define kEndnoteTextFrames_CLSID { 0xfd35df8d, 0x2ebf, 0x44c4, { 0x91, 0xa9, 0x60, 0x2b, 0x70, 0xaf, 0xb8, 0x9f } }
// {EE96407F-06C6-11d2-AAC9-00C04FA349C7}
#define kStory_CLSID { 0xee96407f, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A3736540-4F5C-11d2-AB07-00C04FA349C7}
#define kStories_CLSID { 0xa3736540, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {496F0BE5-7834-11d2-AAF0-00C04FA37726}
#define kCharStyle_CLSID { 0x496f0be5, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {496F0BE6-7834-11d2-AAF0-00C04FA37726}
#define kCharStyles_CLSID { 0x496f0be6, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {496F0BE1-7834-11d2-AAF0-00C04FA37726}
#define kParaStyle_CLSID { 0x496f0be1, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {496F0BE2-7834-11d2-AAF0-00C04FA37726}
#define kParaStyles_CLSID { 0x496f0be2, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {A373654C-4F5C-11d2-AB07-00C04FA349C7}
#define kStoryPref_CLSID { 0xa373654c, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {496F0BDA-7834-11d2-AAF0-00C04FA37726}
#define kTabStop_CLSID { 0x496f0bda, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {496F0BDB-7834-11d2-AAF0-00C04FA37726}
#define kTabStops_CLSID { 0x496f0bdb, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {EE96406E-06C6-11d2-AAC9-00C04FA349C7}
#define kTextFramePref_CLSID { 0xee96406e, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964075-06C6-11d2-AAC9-00C04FA349C7}
#define kTextOptPref_CLSID { 0xee964075, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {6FA5985E-2A7A-4f9a-B9B0-077335DB3C58}
#define kTextDefault_CLSID { 0x6fa5985e, 0x2a7a, 0x4f9a, { 0xb9, 0xb0, 0x7, 0x73, 0x35, 0xdb, 0x3c, 0x58 } }
// {B472528A-6948-4644-B7D9-BD09C1C82375}
#define kAnchoredObjectSettings_CLSID { 0xb472528a, 0x6948, 0x4644, { 0xb7, 0xd9, 0xbd, 0x9, 0xc1, 0xc8, 0x23, 0x75 } }
// {EFDEBF5B-01F7-4bde-A228-94D128D984D6}
#define kAnchoredObjectDefault_CLSID { 0xefdebf5b, 0x1f7, 0x4bde, { 0xa2, 0x28, 0x94, 0xd1, 0x28, 0xd9, 0x84, 0xd6  } }

// {9D630202-57E3-4dc6-8400-FA4FF179CA76}
#define kRunInStyle_CLSID { 0x9d630202, 0x57e3, 0x4dc6, { 0x84, 0x0, 0xfa, 0x4f, 0xf1, 0x79, 0xca, 0x76 } }
// {7D9500F2-779A-48ae-8C40-EAA7EA27EEDB}
#define kRunInStyles_CLSID { 0x7d9500f2, 0x779a, 0x48ae, { 0x8c, 0x40, 0xea, 0xa7, 0xea, 0x27, 0xee, 0xdb } }
// {BA2F3F4D-D1B1-4952-8ECD-58D0D15D7A14}
#define kGrepRunInStyle_CLSID	{ 0xba2f3f4d, 0xd1b1, 0x4952, { 0x8e, 0xcd, 0x58, 0xd0, 0xd1, 0x5d, 0x7a, 0x14 } }
// {EDC1C06B-3FB6-4442-807E-7EF63F2609C4}
#define kGrepRunInStyles_CLSID	{ 0xedc1c06b, 0x3fb6, 0x4442, { 0x80, 0x7e, 0x7e, 0xf6, 0x3f, 0x26, 0x9, 0xc4 } }
// {9A25FB37-7D88-4c7b-87AF-C8D86AABBEE0}
#define kRunInLineStyle_CLSID	{ 0x9a25fb37, 0x7d88, 0x4c7b, { 0x87, 0xaf, 0xc8, 0xd8, 0x6a, 0xab, 0xbe, 0xe0 } }
// {2FEC1339-15AC-47d1-8D45-50BB83796104}
#define kRunInLineStyles_CLSID	{ 0x2fec1339, 0x15ac, 0x47d1, { 0x8d, 0x45, 0x50, 0xbb, 0x83, 0x79, 0x61, 0x4 } }

// {807BD7DC-BF95-41f7-92C4-1AC06B6C3BFE}
#define kBaselineFrameGridOption_CLSID { 0x807bd7dc, 0xbf95, 0x41f7, { 0x92, 0xc4, 0x1a, 0xc0, 0x6b, 0x6c, 0x3b, 0xfe } }
// {2ECF958C-6922-4f77-BCDB-F3C1AE676DC7}
#define kFootnote_CLSID { 0x2ecf958c, 0x6922, 0x4f77, { 0xbc, 0xdb, 0xf3, 0xc1, 0xae, 0x67, 0x6d, 0xc7 } }
// {43C9D8FE-AF8F-4bdf-804C-0659B3C83B37}
#define kFootnotes_CLSID { 0x43c9d8fe, 0xaf8f, 0x4bdf, { 0x80, 0x4c, 0x6, 0x59, 0xb3, 0xc8, 0x3b, 0x37 } }
// {370A7F79-B0DD-43ed-9F0A-CB39941F5EBB}
#define kFootnoteOptions_CLSID { 0x370a7f79, 0xb0dd, 0x43ed, { 0x9f, 0xa, 0xcb, 0x39, 0x94, 0x1f, 0x5e, 0xbb } }
// {E5D68C64-EFF3-4FA0-8136-F304FCA1F9FA}

// {800DBA46-96E6-48D7-B069-6C5532CA5EEA}
#define kEndnoteAnchor_CLSID { 0x800dba46, 0x96e6, 0x48d7, { 0xb0, 0x69, 0x6c, 0x55, 0x32, 0xca, 0x5e, 0xea } }

// {8DE517CC-61D5-4770-9042-2917747AB914}
#define kEndnoteAnchors_CLSID { 0x8de517cc, 0x61d5, 0x4770, { 0x90, 0x42, 0x29, 0x17, 0x74, 0x7a, 0xb9, 0x14 } }

//{12EA8B20-F452-457F-B2B6-7F7A2F85E388}
#define kEndnoteOptions_CLSID {0x12ea8b20, 0xf452, 0x457f, { 0xb2, 0xb6, 0x7f, 0x7a, 0x2f, 0x85, 0xe3, 0x88 }}

// {8552D4BA-A469-4B19-8C0B-5BEF43EE3952}
#define kEndnoteRange_CLSID  {0x8552d4ba, 0xa469, 0x4b19, { 0x8c, 0xb, 0x5b, 0xef, 0x43, 0xee, 0x39, 0x52 }}

// {324AE692-6165-44C2-87CB-A90CA36AD4E3}
#define kEndnoteRanges_CLSID {0x324ae692, 0x6165, 0x44c2, {0x87, 0xcb, 0xa9, 0xc, 0xa3, 0x6a, 0xd4, 0xe3}}


#define kTextFrameFootnoteOption_CLSID { 0xe5d68c64, 0xeff3, 0x4fa0, { 0x81, 0x36, 0xf3, 0x4, 0xfc, 0xa1, 0xf9, 0xfa } }
// {EDD2BE26-7D67-4891-A829-F6D366D4F70D}
#define kTextVariable_CLSID { 0xedd2be26, 0x7d67, 0x4891, { 0xa8, 0x29, 0xf6, 0xd3, 0x66, 0xd4, 0xf7, 0xd } }
// {7DB4C304-F694-4bcb-AA87-66E5978A716E}
#define kTextVariables_CLSID { 0x7db4c304, 0xf694, 0x4bcb, { 0xaa, 0x87, 0x66, 0xe5, 0x97, 0x8a, 0x71, 0x6e } }
// {932CE4BA-7FC7-49b9-8733-7535E79B1018}
#define kTextVariableInstance_CLSID { 0x932ce4ba, 0x7fc7, 0x49b9, { 0x87, 0x33, 0x75, 0x35, 0xe7, 0x9b, 0x10, 0x18 } }
// {AF49C28C-40B3-4ece-9D53-0EDB68588E80}
#define kTextVariableInstances_CLSID { 0xaf49c28c, 0x40b3, 0x4ece, { 0x9d, 0x53, 0xe, 0xdb, 0x68, 0x58, 0x8e, 0x80 } }
// {71309121-8428-4d24-8181-2F0EC21F1089}
#define kPageNumberPref_CLSID { 0x71309121, 0x8428, 0x4d24, { 0x81, 0x81, 0x2f, 0xe, 0xc2, 0x1f, 0x10, 0x89 } }
// {53CB57A5-989F-4c3f-B3B9-FA9FF75D6D6A}
#define kChapterNumberPref_CLSID { 0x53cb57a5, 0x989f, 0x4c3f, { 0xb3, 0xb9, 0xfa, 0x9f, 0xf7, 0x5d, 0x6d, 0x6a } }
// {044F34F5-A3EA-44ae-B51F-1317D5D69670}
#define kDatePref_CLSID { 0x44f34f5, 0xa3ea, 0x44ae, { 0xb5, 0x1f, 0x13, 0x17, 0xd5, 0xd6, 0x96, 0x70 } }
// {8F07BFD4-987F-483b-8130-8C273EDA9943}
#define kFileNamePref_CLSID { 0x8f07bfd4, 0x987f, 0x483b, { 0x81, 0x30, 0x8c, 0x27, 0x3e, 0xda, 0x99, 0x43 } }
// {5CB802DD-8683-46a3-917F-5D4F8703841C}
#define kMatchCharStylePref_CLSID { 0x5cb802dd, 0x8683, 0x46a3, { 0x91, 0x7f, 0x5d, 0x4f, 0x87, 0x3, 0x84, 0x1c } }
// {39D3485E-B8E0-4bcd-86EB-9B42612ED9FF}
#define kMatchParaStylePref_CLSID { 0x39d3485e, 0xb8e0, 0x4bcd, { 0x86, 0xeb, 0x9b, 0x42, 0x61, 0x2e, 0xd9, 0xff } }
// {D5959BCB-8E6A-435b-B669-E13B96E9A2F9}
#define kCustomTextPref_CLSID { 0xd5959bcb, 0x8e6a, 0x435b, { 0xb6, 0x69, 0xe1, 0x3b, 0x96, 0xe9, 0xa2, 0xf9 } }
// {168073BC-4076-451a-8B6F-AD7E6AEF2D32}
#define kParagraphStyleGroup_CLSID { 0x168073bc, 0x4076, 0x451a, { 0x8b, 0x6f, 0xad, 0x7e, 0x6a, 0xef, 0x2d, 0x32 } }
// {736A624E-CA83-46c8-A626-4F6DD4CCFBE0}
#define kParagraphStyleGroups_CLSID { 0x736a624e, 0xca83, 0x46c8, { 0xa6, 0x26, 0x4f, 0x6d, 0xd4, 0xcc, 0xfb, 0xe0 } }
// {546328FB-23D6-49bf-9F9A-02E2F8C2F89A}
#define kCharacterStyleGroup_CLSID { 0x546328fb, 0x23d6, 0x49bf, { 0x9f, 0x9a, 0x2, 0xe2, 0xf8, 0xc2, 0xf8, 0x9a } }
// {F278F04A-05F9-4dbd-B5C9-EB6BC2901A3D}
#define kCharacterStyleGroups_CLSID { 0xf278f04a, 0x5f9, 0x4dbd, { 0xb5, 0xc9, 0xeb, 0x6b, 0xc2, 0x90, 0x1a, 0x3d } }
// {8F5CC9A5-BC1B-4ffc-B7E8-E0FCDF69CF6D}
#define kRootParagraphStyleGroup_CLSID { 0x8f5cc9a5, 0xbc1b, 0x4ffc, { 0xb7, 0xe8, 0xe0, 0xfc, 0xdf, 0x69, 0xcf, 0x6d } }
// {119F37D7-5397-42fa-8768-DC4AFB5EB001}
#define kRootCharacterStyleGroup_CLSID { 0x119f37d7, 0x5397, 0x42fa, { 0x87, 0x68, 0xdc, 0x4a, 0xfb, 0x5e, 0xb0, 0x1 } }
// {C13B1CAF-781E-435e-BD19-9B696E015463}
//#define kRootParagraphStyleGroups_CLSID { 0xc13b1caf, 0x781e, 0x435e, { 0xbd, 0x19, 0x9b, 0x69, 0x6e, 0x1, 0x54, 0x63 } }
// {6F20C065-AD9C-4bd9-BA4F-5F303FF8FBE5}
//#define kRootCharacterStyleGroups_CLSID { 0x6f20c065, 0xad9c, 0x4bd9, { 0xba, 0x4f, 0x5f, 0x30, 0x3f, 0xf8, 0xfb, 0xe5 } }
// {8BD87F01-7D2D-4935-8021-6C8B0A2DC776}
#define kTextTextIterObject_CLSID { 0x8bd87f01, 0x7d2d, 0x4935, { 0x80, 0x21, 0x6c, 0x8b, 0xa, 0x2d, 0xc7, 0x76 } }
// {1FA91EE7-89D9-454e-BBBA-7495EAEDAF34}
#define kParaTextIterObject_CLSID { 0x1fa91ee7, 0x89d9, 0x454e, { 0xbb, 0xba, 0x74, 0x95, 0xea, 0xed, 0xaf, 0x34 } }
// {04C21D59-63B8-4f9c-BFC3-325A56FAA4C5}
#define kParaStyleTextIterObject_CLSID { 0x4c21d59, 0x63b8, 0x4f9c, { 0xbf, 0xc3, 0x32, 0x5a, 0x56, 0xfa, 0xa4, 0xc5 } }
// {2E972B44-57AB-4b9e-A997-B56A6B0C758C}
#define kCharStyleTextIterObject_CLSID { 0x2e972b44, 0x57ab, 0x4b9e, { 0xa9, 0x97, 0xb5, 0x6a, 0x6b, 0xc, 0x75, 0x8c } }
// {EB546614-5161-4825-AFAA-71E22E53784B}
#define kObjectTextIterObject_CLSID { 0xeb546614, 0x5161, 0x4825, { 0xaf, 0xaa, 0x71, 0xe2, 0x2e, 0x53, 0x78, 0x4b } }
// {C457C160-D081-4dcf-9412-9660FF64B147}
#define kXMLTextIterObject_CLSID { 0xc457c160, 0xd081, 0x4dcf, { 0x94, 0x12, 0x96, 0x60, 0xff, 0x64, 0xb1, 0x47 } }
// {E7A00ECB-F923-482d-9C99-76255D0D1217}
#define kTextTextItersObject_CLSID { 0xe7a00ecb, 0xf923, 0x482d, { 0x9c, 0x99, 0x76, 0x25, 0x5d, 0xd, 0x12, 0x17 } }
// {2078D500-6A41-4229-896E-0E94F4340BAA}
#define kParaTextItersObject_CLSID { 0x2078d500, 0x6a41, 0x4229, { 0x89, 0x6e, 0xe, 0x94, 0xf4, 0x34, 0xb, 0xaa } }
// {E0700F9F-5B86-42d4-993D-2F1F8855FE96}
#define kParaStyleTextItersObject_CLSID { 0xe0700f9f, 0x5b86, 0x42d4, { 0x99, 0x3d, 0x2f, 0x1f, 0x88, 0x55, 0xfe, 0x96 } }
// {5324C4C7-D40F-4046-980A-95844111E4AC}
#define kCharStyleTextItersObject_CLSID { 0x5324c4c7, 0xd40f, 0x4046, { 0x98, 0xa, 0x95, 0x84, 0x41, 0x11, 0xe4, 0xac } }
// {1843D951-729F-44b0-A355-6E490D6659CA}
#define kObjectTextItersObject_CLSID { 0x1843d951, 0x729f, 0x44b0, { 0xa3, 0x55, 0x6e, 0x49, 0xd, 0x66, 0x59, 0xca } }
// {C6049CF4-1416-48e4-A7C3-948B38515A37}
#define kXMLTextItersObject_CLSID { 0xc6049cf4, 0x1416, 0x48e4, { 0xa7, 0xc3, 0x94, 0x8b, 0x38, 0x51, 0x5a, 0x37 } };
// {F1A2A933-0CF4-4c8d-915C-975E3EF5E623}
#define kParagraphStyleRangeObject_CLSID { 0xf1a2a933, 0xcf4, 0x4c8d, { 0x91, 0x5c, 0x97, 0x5e, 0x3e, 0xf5, 0xe6, 0x23 } }
// {AA2A1300-69C0-48d9-9A67-F64C4553F73E}
#define kCharacterStyleRangeObject_CLSID { 0xaa2a1300, 0x69c0, 0x48d9,{  0x9a, 0x67, 0xf6, 0x4c, 0x45, 0x53, 0xf7, 0x3e} }
// {32DB02E0-955C-421d-BEEF-6D06C3028B10}
#define kParagraphStyleRangesObject_CLSID { 0x32db02e0, 0x955c, 0x421d, { 0xbe, 0xef, 0x6d, 0x6, 0xc3, 0x2, 0x8b, 0x10 } }
// {CD4441A8-A2C5-4b1b-B66D-FC9DBDA0AA26}
#define kCharacterStyleRangesObject_CLSID { 0xcd4441a8, 0xa2c5, 0x4b1b, {  0xb6, 0x6d, 0xfc, 0x9d, 0xbd, 0xa0, 0xaa, 0x26 } }
// {78BB5C69-5ECA-49dc-8215-1FA3F2A9CD43}
#define kTextContentObject_CLSID { 0x78bb5c69, 0x5eca, 0x49dc, {   0x82, 0x15, 0x1f, 0xa3, 0xf2, 0xa9, 0xcd, 0x43 } }
// {D6539452-D0CA-4f41-B21D-9E63E1947D77}
#define kTextBreakObject_CLSID  { 0xa1673a9f, 0x190e, 0x417b, {   0x8d, 0xb5, 0xa, 0x38, 0xe1, 0xe, 0x91, 0x0 } }
// {359ADC39-BACB-452f-B5A7-A1AD7E1D30A9}
#define kCaptionMetadataPref_CLSID { 0x359adc39, 0xbacb, 0x452f, { 0xb5, 0xa7, 0xa1, 0xad, 0x7e, 0x1d, 0x30, 0xa9}}

// {A767BC79-E1BB-4624-8EC7-35885CB7B110}
#define kStyleExportTagMap_CLSID { 0xa767bc79, 0xe1bb, 0x4624, { 0x8e, 0xc7, 0x35, 0x88, 0x5c, 0xb7, 0xb1, 0x10}}
// {2ACA8140-B3D2-4aa3-B711-DE396F19F712}
#define kStyleExportTagMaps_CLSID { 0x2aca8140, 0xb3d2, 0x4aa3, { 0xb7, 0x11, 0xde, 0x39, 0x6f, 0x19, 0xf7, 0x12}}

// {D8246E48-2E41-4502-81D5-483DB99552C4}
#define kFontSyncPrefObject_CLSID { 0xd8246e48, 0x2e41, 0x4502, { 0x81, 0xd5, 0x48, 0x3d, 0xb9, 0x95, 0x52, 0xc4 } }



#endif

#endif /* _H_TextScriptID */
