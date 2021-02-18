//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TextEditorActionID.h $
//  
//  Owner: ???
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

#ifndef __TextEditorActionID__
#define __TextEditorActionID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTextEditorPrefix		RezLong(0x1d300)		// these are also in TextEditorID.h
#define kTextEditorPrefix2		RezLong(0xb800)
#define kTextEditorPrefix3		RezLong(0x20000)

#define kTextEditorActionResID 							2000
#define kTextEditorMenuResID							2100
// See also: TextEditorDefs.h

// <Action ID>
//---------------------------------------------------------------
// Action IDs
//---------------------------------------------------------------
DECLARE_PMID(kActionIDSpace, kViewShowInvisiblesActionID, kTextEditorPrefix + 1)
DECLARE_PMID(kActionIDSpace, kShowInvisiblesRtMouseNothingTextActionID, kTextEditorPrefix + 2)
DECLARE_PMID(kActionIDSpace, kShowInvisiblesRtMouseTextActionID, kTextEditorPrefix + 3)
DECLARE_PMID(kActionIDSpace, kMoveToRightOneCharActionID, kTextEditorPrefix + 4)
DECLARE_PMID(kActionIDSpace, kMoveToLeftOneCharActionID, kTextEditorPrefix + 5)
DECLARE_PMID(kActionIDSpace, kMoveUpOneLineActionID, kTextEditorPrefix + 6)
DECLARE_PMID(kActionIDSpace, kMoveDownOneLineActionID, kTextEditorPrefix + 7)
DECLARE_PMID(kActionIDSpace, kMoveToRightOneWordActionID, kTextEditorPrefix + 8)
DECLARE_PMID(kActionIDSpace, kMoveToLeftOneWordActionID, kTextEditorPrefix + 9)
DECLARE_PMID(kActionIDSpace, kMoveToStartOfLineActionID, kTextEditorPrefix + 10)

DECLARE_PMID(kActionIDSpace, kMoveToEndOfLineActionID, kTextEditorPrefix + 11)
DECLARE_PMID(kActionIDSpace, kMoveToPrevParaActionID, kTextEditorPrefix + 12)
DECLARE_PMID(kActionIDSpace, kMoveToNextParaActionID, kTextEditorPrefix + 13)
DECLARE_PMID(kActionIDSpace, kMoveToEndOfStoryActionID, kTextEditorPrefix + 14)
DECLARE_PMID(kActionIDSpace, kMoveToStartOfStoryActionID, kTextEditorPrefix + 15)
DECLARE_PMID(kActionIDSpace, kSelectToRightOneCharActionID, kTextEditorPrefix + 16)
DECLARE_PMID(kActionIDSpace, kSelectToLeftOneCharActionID, kTextEditorPrefix + 17)
DECLARE_PMID(kActionIDSpace, kSelectToRightOneWordActionID, kTextEditorPrefix + 18)
DECLARE_PMID(kActionIDSpace, kSelectToLeftOneWordActionID, kTextEditorPrefix + 19)
DECLARE_PMID(kActionIDSpace, kSelectToStartOfLineActionID, kTextEditorPrefix + 20)

DECLARE_PMID(kActionIDSpace, kSelectToEndOfLineActionID, kTextEditorPrefix + 21)
DECLARE_PMID(kActionIDSpace, kSelectUpOneLineActionID, kTextEditorPrefix + 22)
DECLARE_PMID(kActionIDSpace, kSelectDownOneLineActionID, kTextEditorPrefix + 23)
DECLARE_PMID(kActionIDSpace, kSelectToPrevParaActionID, kTextEditorPrefix + 24)
DECLARE_PMID(kActionIDSpace, kSelectToNextParaActionID, kTextEditorPrefix + 25)
DECLARE_PMID(kActionIDSpace, kSelectAllInStoryActionID, kTextEditorPrefix + 26)
DECLARE_PMID(kActionIDSpace, kSelectToEndOfStoryActionID, kTextEditorPrefix + 27)
DECLARE_PMID(kActionIDSpace, kSelectToStartOfStoryActionID, kTextEditorPrefix + 28)
DECLARE_PMID(kActionIDSpace, kDeleteOneCharToRightActionID, kTextEditorPrefix + 29)
DECLARE_PMID(kActionIDSpace, kDeleteOneCharToLeftActionID, kTextEditorPrefix + 30)

DECLARE_PMID(kActionIDSpace, kDiscHyphenActionID, kTextEditorPrefix + 31)
DECLARE_PMID(kActionIDSpace, kSoftReturnActionID, kTextEditorPrefix + 32)
DECLARE_PMID(kActionIDSpace, kPageNumberActionID, kTextEditorPrefix + 33)
DECLARE_PMID(kActionIDSpace, kTESectionNameActionID, kTextEditorPrefix + 34)
DECLARE_PMID(kActionIDSpace, kNoBreakHyphenActionID, kTextEditorPrefix + 35)
DECLARE_PMID(kActionIDSpace, kFlushSpaceActionID, kTextEditorPrefix + 36)
DECLARE_PMID(kActionIDSpace, kThinSpaceActionID, kTextEditorPrefix + 37)
DECLARE_PMID(kActionIDSpace, kFigureSpaceActionID, kTextEditorPrefix + 38)
DECLARE_PMID(kActionIDSpace, kEmSpaceActionID, kTextEditorPrefix + 39)
DECLARE_PMID(kActionIDSpace, kEnSpaceActionID, kTextEditorPrefix + 40)

DECLARE_PMID(kActionIDSpace, kHairSpaceActionID, kTextEditorPrefix + 41)
DECLARE_PMID(kActionIDSpace, kHardSpaceActionID, kTextEditorPrefix + 42)
DECLARE_PMID(kActionIDSpace, kBulletActionID, kTextEditorPrefix + 43)
DECLARE_PMID(kActionIDSpace, kCopyrightMarkActionID, kTextEditorPrefix + 44)
DECLARE_PMID(kActionIDSpace, kRegistrationMarkActionID, kTextEditorPrefix + 45)
DECLARE_PMID(kActionIDSpace, kPilcrowActionID, kTextEditorPrefix + 46)
DECLARE_PMID(kActionIDSpace, kSectionMarkActionID, kTextEditorPrefix + 47)
DECLARE_PMID(kActionIDSpace, kDblOpenQuoteActionID, kTextEditorPrefix + 48)		// Does "smart" version of quote
DECLARE_PMID(kActionIDSpace, kDblCloseQuoteActionID, kTextEditorPrefix + 49)	// Does "smart" version of quote
DECLARE_PMID(kActionIDSpace, kSngOpenQuoteActionID, kTextEditorPrefix + 50)		// Does "smart" version of quote

DECLARE_PMID(kActionIDSpace, kSngCloseQuoteActionID, kTextEditorPrefix + 51)	// Does "smart" version of quote
DECLARE_PMID(kActionIDSpace, kEllipseActionID, kTextEditorPrefix + 52)
DECLARE_PMID(kActionIDSpace, kEnDashActionID, kTextEditorPrefix + 53)
DECLARE_PMID(kActionIDSpace, kEmDashActionID, kTextEditorPrefix + 54)
DECLARE_PMID(kActionIDSpace, kPunctuationSpaceActionID, kTextEditorPrefix + 55)
DECLARE_PMID(kActionIDSpace, kTrademarkActionID, kTextEditorPrefix + 56)
DECLARE_PMID(kActionIDSpace, kTypeStyleNormalActionID, kTextEditorPrefix + 57)
DECLARE_PMID(kActionIDSpace, kTypeStyleBoldActionID, kTextEditorPrefix + 58)
DECLARE_PMID(kActionIDSpace, kTypeStyleItalicActionID, kTextEditorPrefix + 59)
DECLARE_PMID(kActionIDSpace, kTypeStyleUnderlineActionID, kTextEditorPrefix + 60)

DECLARE_PMID(kActionIDSpace, kChangeCaseMenuSepActionID, kTextEditorPrefix + 61)
DECLARE_PMID(kActionIDSpace, kTypeStyleSmallCapsActionID, kTextEditorPrefix + 62)
DECLARE_PMID(kActionIDSpace, kTypeStyleAllCapsActionID, kTextEditorPrefix + 63)
DECLARE_PMID(kActionIDSpace, kTypeStyleSuperscriptActionID, kTextEditorPrefix + 64)
DECLARE_PMID(kActionIDSpace, kTypeStyleSubscriptActionID, kTextEditorPrefix + 65)
DECLARE_PMID(kActionIDSpace, kTypeStyleStrikethruActionID, kTextEditorPrefix + 66)
DECLARE_PMID(kActionIDSpace, kTypeStyleNobreakActionID, kTextEditorPrefix + 67)
DECLARE_PMID(kActionIDSpace, kTypeStyleLigaturesActionID, kTextEditorPrefix + 68)
DECLARE_PMID(kActionIDSpace, kTypeStyleOldStylePropActionID, kTextEditorPrefix + 69)
DECLARE_PMID(kActionIDSpace, kAlignLeftActionID, kTextEditorPrefix + 70)

DECLARE_PMID(kActionIDSpace, kAlignCenterActionID, kTextEditorPrefix + 71)
DECLARE_PMID(kActionIDSpace, kAlignRightActionID, kTextEditorPrefix + 72)
DECLARE_PMID(kActionIDSpace, kAlignJustifyActionID, kTextEditorPrefix + 73)
DECLARE_PMID(kActionIDSpace, kAlignForceActionID, kTextEditorPrefix + 74)
DECLARE_PMID(kActionIDSpace, kAlignToGridActionID, kTextEditorPrefix + 75)
DECLARE_PMID(kActionIDSpace, kApplyStyleShortcutActionID, kTextEditorPrefix + 76)
DECLARE_PMID(kActionIDSpace, kGoToNextFrameActionID, kTextEditorPrefix + 77)
DECLARE_PMID(kActionIDSpace, kGoToPrevFrameActionID, kTextEditorPrefix + 78)
DECLARE_PMID(kActionIDSpace, kGoToFirstFrameActionID, kTextEditorPrefix + 79)
DECLARE_PMID(kActionIDSpace, kGoToLastFrameActionID, kTextEditorPrefix + 80)

DECLARE_PMID(kActionIDSpace, kIncreasePointSizeActionID, kTextEditorPrefix + 81)
DECLARE_PMID(kActionIDSpace, kDecreasePointSizeActionID, kTextEditorPrefix + 82)
DECLARE_PMID(kActionIDSpace, kIncreaseLeadingActionID, kTextEditorPrefix + 83)
DECLARE_PMID(kActionIDSpace, kDecreaseLeadingActionID, kTextEditorPrefix + 84)
DECLARE_PMID(kActionIDSpace, kIncreaseTrackingActionID, kTextEditorPrefix + 85)
DECLARE_PMID(kActionIDSpace, kDecreaseTrackingActionID, kTextEditorPrefix + 86)
DECLARE_PMID(kActionIDSpace, kIncreaseTrackingTimes5ActionID, kTextEditorPrefix + 87)
DECLARE_PMID(kActionIDSpace, kDecreaseTrackingTimes5ActionID, kTextEditorPrefix + 88)
DECLARE_PMID(kActionIDSpace, kIncreaseBLShiftActionID, kTextEditorPrefix + 89)
DECLARE_PMID(kActionIDSpace, kDecreaseBLShiftActionID, kTextEditorPrefix + 90)

DECLARE_PMID(kActionIDSpace, kIncreaseBLShiftTimes5ActionID, kTextEditorPrefix + 91)
DECLARE_PMID(kActionIDSpace, kDecreaseBLShiftTimes5ActionID, kTextEditorPrefix + 92)
DECLARE_PMID(kActionIDSpace, kIncreasePointSizeTimes5ActionID, kTextEditorPrefix + 93)
DECLARE_PMID(kActionIDSpace, kDecreasePointSizeTimes5ActionID, kTextEditorPrefix + 94)
DECLARE_PMID(kActionIDSpace, kIncreaseLeadingTimes5ActionID, kTextEditorPrefix + 95)
DECLARE_PMID(kActionIDSpace, kDecreaseLeadingTimes5ActionID, kTextEditorPrefix + 96)
DECLARE_PMID(kActionIDSpace, kNormalHorScaleActionID, kTextEditorPrefix + 97)
DECLARE_PMID(kActionIDSpace, kNormalVerScaleActionID, kTextEditorPrefix + 98)
DECLARE_PMID(kActionIDSpace, kAutoLeadingActionID, kTextEditorPrefix + 99)
DECLARE_PMID(kActionIDSpace, kRecomposeAllStoriesActionID, kTextEditorPrefix + 100)

DECLARE_PMID(kActionIDSpace, kRefreshMissingFontsActionID, kTextEditorPrefix + 101)
DECLARE_PMID(kActionIDSpace, kCreateAnchoredTextFrameActionID, kTextEditorPrefix + 102)
DECLARE_PMID(kActionIDSpace, kShowHiddenSepActionID, kTextEditorPrefix + 103)
DECLARE_PMID(kActionIDSpace, kInsertColumnBreakActionID, kTextEditorPrefix + 104)
DECLARE_PMID(kActionIDSpace, kInsertFrameBreakActionID, kTextEditorPrefix + 105)
DECLARE_PMID(kActionIDSpace, kInsertPageBreakActionID, kTextEditorPrefix + 106)
DECLARE_PMID(kActionIDSpace, kInsertOddPageBreakActionID, kTextEditorPrefix + 107)
DECLARE_PMID(kActionIDSpace, kInsertEvenPageBreakActionID, kTextEditorPrefix + 108)
DECLARE_PMID(kActionIDSpace, kSelectLineActionID, kTextEditorPrefix + 109)
DECLARE_PMID(kActionIDSpace, kIdeographicSpaceActionID, kTextEditorPrefix + 110)

DECLARE_PMID(kActionIDSpace, kTextBreakSepActionID, kTextEditorPrefix + 111)
DECLARE_PMID(kActionIDSpace, kIncreaseWordSpaceActionID, kTextEditorPrefix + 112)
DECLARE_PMID(kActionIDSpace, kIncreaseWordSpaceTimes5ActionID, kTextEditorPrefix + 113)
DECLARE_PMID(kActionIDSpace, kDecreaseWordSpaceActionID, kTextEditorPrefix + 114)
DECLARE_PMID(kActionIDSpace, kDecreaseWordSpaceTimes5ActionID, kTextEditorPrefix + 115)
DECLARE_PMID(kActionIDSpace, kColumnBreakActionID, kTextEditorPrefix + 116)
DECLARE_PMID(kActionIDSpace, kFrameBreakActionID, kTextEditorPrefix + 117)
DECLARE_PMID(kActionIDSpace, kPageBreakActionID, kTextEditorPrefix + 118)
DECLARE_PMID(kActionIDSpace, kOddPageBreakActionID, kTextEditorPrefix + 119)
DECLARE_PMID(kActionIDSpace, kEvenPageBreakActionID, kTextEditorPrefix + 120)

DECLARE_PMID(kActionIDSpace, kRightEdgeTabActionID, kTextEditorPrefix + 121)
DECLARE_PMID(kActionIDSpace, kIndentToHereActionID, kTextEditorPrefix + 122)
DECLARE_PMID(kActionIDSpace, kPrevPageNumActionID, kTextEditorPrefix + 123)
DECLARE_PMID(kActionIDSpace, kNextPageNumActionID, kTextEditorPrefix + 124)
DECLARE_PMID(kActionIDSpace, kChangeCaseUpperActionID, kTextEditorPrefix + 125)
DECLARE_PMID(kActionIDSpace, kChangeCaseLowerActionID, kTextEditorPrefix + 126)
DECLARE_PMID(kActionIDSpace, kChangeCaseTitleActionID, kTextEditorPrefix + 127)
DECLARE_PMID(kActionIDSpace, kChangeCaseSentenceActionID, kTextEditorPrefix + 128)
DECLARE_PMID(kActionIDSpace, kFillFrameActionID, kTextEditorPrefix + 129)
DECLARE_PMID(kActionIDSpace, kIBeamToolActionID, kTextEditorPrefix + 130)

DECLARE_PMID(kActionIDSpace, kVerticalTextToolActionID, kTextEditorPrefix + 131)
DECLARE_PMID(kActionIDSpace, kInsertTextSepActionID, kTextEditorPrefix + 132)
DECLARE_PMID(kActionIDSpace, kDamageAllStoriesActionID, kTextEditorPrefix + 133)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFSuperiorActionID, kTextEditorPrefix + 134)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFInferiorActionID, kTextEditorPrefix + 135)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFOrdinalActionID, kTextEditorPrefix + 136)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFSwashActionID, kTextEditorPrefix + 137)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFFractionActionID, kTextEditorPrefix + 138)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFDiscLigActionID, kTextEditorPrefix + 139)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFTitlingActionID, kTextEditorPrefix + 140)

DECLARE_PMID(kActionIDSpace, kTypeStyleOTFNumeratorActionID, kTextEditorPrefix + 141)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFDenominatorActionID, kTextEditorPrefix + 142)
DECLARE_PMID(kActionIDSpace, kTypeStyleOldStyleTabularActionID, kTextEditorPrefix + 143)
DECLARE_PMID(kActionIDSpace, kTypeStyleLiningPropActionID, kTextEditorPrefix + 144)
DECLARE_PMID(kActionIDSpace, kTypeStyleLiningTabularActionID, kTextEditorPrefix + 145)
DECLARE_PMID(kActionIDSpace, kInsertTabActionID, kTextEditorPrefix + 146 )
DECLARE_PMID(kActionIDSpace, kInsertFootnoteActionID, kTextEditorPrefix + 147 )
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFContextualActionID, kTextEditorPrefix + 148 )
DECLARE_PMID(kActionIDSpace, kCJKCharHangICFTopActionID, kTextEditorPrefix + 149)
DECLARE_PMID(kActionIDSpace, kCJKCharHangICFBottomActionID, kTextEditorPrefix + 150)

DECLARE_PMID(kActionIDSpace, kCJKCharHangEmTopActionID, kTextEditorPrefix + 151)
DECLARE_PMID(kActionIDSpace, kCJKCharHangEmCenterActionID, kTextEditorPrefix + 152)
DECLARE_PMID(kActionIDSpace, kCJKCharHangEmBottomActionID, kTextEditorPrefix + 153)
DECLARE_PMID(kActionIDSpace, kCJKCharHangBaselineActionID, kTextEditorPrefix + 154)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFHVKanaActionID, kTextEditorPrefix + 155)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFProportionalActionID, kTextEditorPrefix + 156)
DECLARE_PMID(kActionIDSpace, kTypeStyleOTFRomanItalicsActionID, kTextEditorPrefix + 157)
DECLARE_PMID(kActionIDSpace, kCJKKinsokuPushInFirstActionID, kTextEditorPrefix + 158)
DECLARE_PMID(kActionIDSpace, kCJKKinsokuPushOutFirstActionID, kTextEditorPrefix + 159)
DECLARE_PMID(kActionIDSpace, kCJKKinsokuPushOutOnlyActionID, kTextEditorPrefix + 160)

DECLARE_PMID(kActionIDSpace, kTypeStyleOTFStyleAltActionID, kTextEditorPrefix + 161 )
DECLARE_PMID(kActionIDSpace, kTypeStyleCapToSmallCapActionID, kTextEditorPrefix + 162 )
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep1ActionID, kTextEditorPrefix + 163 )
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep2ActionID, kTextEditorPrefix + 164 )
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep3ActionID, kTextEditorPrefix + 165 )
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep4ActionID, kTextEditorPrefix + 166 )
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep5ActionID, kTextEditorPrefix + 167 )
DECLARE_PMID(kActionIDSpace, kCJKHangingNoneActionID, kTextEditorPrefix + 168)
DECLARE_PMID(kActionIDSpace, kCJKHangingRegularActionID, kTextEditorPrefix + 169)
DECLARE_PMID(kActionIDSpace, kCJKHangingForceActionID, kTextEditorPrefix + 170)

DECLARE_PMID(kActionIDSpace, kCJKRomanRotateActionID, kTextEditorPrefix + 171)
DECLARE_PMID(kActionIDSpace, kCJKGridAlignmentNoneActionID, kTextEditorPrefix + 172)
DECLARE_PMID(kActionIDSpace, kCJKGridAlignmentBaselineActionID, kTextEditorPrefix + 173)
DECLARE_PMID(kActionIDSpace, kCJKGridAlignmentTopActionID, kTextEditorPrefix + 174)
DECLARE_PMID(kActionIDSpace, kCJKGridAlignmentCenterActionID, kTextEditorPrefix + 175)
DECLARE_PMID(kActionIDSpace, kCJKGridAlignmentBottomActionID, kTextEditorPrefix + 176)
DECLARE_PMID(kActionIDSpace, kCJKGridAlignmentICFTopActionID, kTextEditorPrefix + 177)
DECLARE_PMID(kActionIDSpace, kCJKGridAlignmentICFBottomActionID, kTextEditorPrefix + 178)
DECLARE_PMID(kActionIDSpace, kCJKGridAlignOnlyFirstLineActionID, kTextEditorPrefix + 179)

DECLARE_PMID(kActionIDSpace, kCJKLeadingModelCenterActionID, kTextEditorPrefix + 180)
DECLARE_PMID(kActionIDSpace, kCJKLeadingModelAkiBelowActionID, kTextEditorPrefix + 181)
DECLARE_PMID(kActionIDSpace, kCJKLeadingModelAkiAboveActionID, kTextEditorPrefix + 182)
DECLARE_PMID(kActionIDSpace, kCJKLeadingModelRomanActionID, kTextEditorPrefix + 183)
DECLARE_PMID(kActionIDSpace, kContextFrameOptionsSepActionID, kTextEditorPrefix + 184 )
DECLARE_PMID(kActionIDSpace, kCJKContextSepActionID, kTextEditorPrefix + 185 )
DECLARE_PMID(kActionIDSpace, kRubyDialogActionID, kTextEditorPrefix + 186 )
DECLARE_PMID(kActionIDSpace, kKentenDialogActionID, kTextEditorPrefix + 187 )
DECLARE_PMID(kActionIDSpace, kShataiDialogActionID, kTextEditorPrefix + 188 )
DECLARE_PMID(kActionIDSpace, kCJKCharTatechuyokoActionID, kTextEditorPrefix + 189 )
DECLARE_PMID(kActionIDSpace, kCJKCharWarichuActionID, kTextEditorPrefix + 190 )

DECLARE_PMID(kActionIDSpace, kParagraphReturnActionID, kTextEditorPrefix + 191 )
DECLARE_PMID(kActionIDSpace, kTypeStyleFontDefaultActionID, kTextEditorPrefix + 192 )
DECLARE_PMID(kActionIDSpace, kCJKRubySetting_2ActionID, kTextEditorPrefix + 193 )
DECLARE_PMID(kActionIDSpace, kCJKRubySetting_3ActionID, kTextEditorPrefix + 194 )
DECLARE_PMID(kActionIDSpace, kCJKRubySetting_4ActionID, kTextEditorPrefix + 195 )
DECLARE_PMID(kActionIDSpace, kBalanceLinesActionID, kTextEditorPrefix + 196 )
DECLARE_PMID(kActionIDSpace, kBreakRunInStyleActionID, kTextEditorPrefix + 197 )
DECLARE_PMID(kActionIDSpace, kCJKGridTrackingActionID, kTextEditorPrefix + 198)
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep6ActionID, kTextEditorPrefix + 199 )

DECLARE_PMID(kActionIDSpace, kInsertSpellingSuggestionActionID, kTextEditorPrefix + 200 )
// 200 - 232 reserved for dynamic spell check suggestions!!!

DECLARE_PMID(kActionIDSpace, kDashActionID, kTextEditorPrefix + 233 )
DECLARE_PMID(kActionIDSpace, kAddWordToDictionaryActionID, kTextEditorPrefix + 234 )
DECLARE_PMID(kActionIDSpace, kInsertFootnoteNumberActionID, kTextEditorPrefix + 235)
DECLARE_PMID(kActionIDSpace, kCJKKinsokuPushInAlwaysActionID, kTextEditorPrefix + 236)
DECLARE_PMID(kActionIDSpace, kScaleAffectsLineHeightActionID, kTextEditorPrefix + 237 )
DECLARE_PMID(kActionIDSpace, kCJKParaGyoudoriActionID, kTextEditorPrefix + 238)
DECLARE_PMID(kActionIDSpace, kSpellingIgnoreAllActionID, kTextEditorPrefix + 239 )

DECLARE_PMID(kActionIDSpace, kInsertCapitalizedSuggestionActionID, kTextEditorPrefix + 240 )
DECLARE_PMID(kActionIDSpace, kOpenStoryEditorActionID, kTextEditorPrefix + 241 )
DECLARE_PMID(kActionIDSpace, kIgnoreEdgeAlignActionID, kTextEditorPrefix + 242)
DECLARE_PMID(kActionIDSpace, kIncreaseHorzScaleActionID, kTextEditorPrefix + 243)
DECLARE_PMID(kActionIDSpace, kDecreaseHorzScaleActionID, kTextEditorPrefix + 244)
DECLARE_PMID(kActionIDSpace, kIncreaseHorzScaleTimes5ActionID, kTextEditorPrefix + 245)
DECLARE_PMID(kActionIDSpace, kDecreaseHorzScaleTimes5ActionID, kTextEditorPrefix + 246)
DECLARE_PMID(kActionIDSpace, kSlashedZeroOTFActionID, kTextEditorPrefix + 247 )
DECLARE_PMID(kActionIDSpace, kHistoricalOTFActionID, kTextEditorPrefix + 248 )
DECLARE_PMID(kActionIDSpace, kDeleteRepeatedWordActionID, kTextEditorPrefix + 249 )

DECLARE_PMID(kActionIDSpace, kDeleteOneWordToRightActionID, kTextEditorPrefix + 250 )
DECLARE_PMID(kActionIDSpace, kDeleteOneWordToLeftActionID, kTextEditorPrefix + 251 )
DECLARE_PMID(kActionIDSpace, kMoveToPrevSentenceActionID, kTextEditorPrefix + 252 )
DECLARE_PMID(kActionIDSpace, kMoveToNextSentenceActionID, kTextEditorPrefix + 253 )
DECLARE_PMID(kActionIDSpace, kSelectToPrevSentenceActionID, kTextEditorPrefix + 254 )
DECLARE_PMID(kActionIDSpace, kSelectToNextSentenceActionID, kTextEditorPrefix + 255 )

// This space is full: don't go over 255, use the next prefix

DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF1Action, kTextEditorPrefix2 + 0 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF2Action, kTextEditorPrefix2 + 1 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF3Action, kTextEditorPrefix2 + 2 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF4Action, kTextEditorPrefix2 + 3 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF5Action, kTextEditorPrefix2 + 4 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF6Action, kTextEditorPrefix2 + 5)
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF7Action, kTextEditorPrefix2 + 6 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF8Action, kTextEditorPrefix2 + 7 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF9Action, kTextEditorPrefix2 + 8 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF10Action, kTextEditorPrefix2 + 9 )

DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF11Action, kTextEditorPrefix2 + 10 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF12Action, kTextEditorPrefix2 + 11 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF13Action, kTextEditorPrefix2 + 12 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF14Action, kTextEditorPrefix2 + 13 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF15Action, kTextEditorPrefix2 + 14 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF16Action, kTextEditorPrefix2 + 15 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF17Action, kTextEditorPrefix2 + 16 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF18Action, kTextEditorPrefix2 + 17 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF19Action, kTextEditorPrefix2 + 18 )
DECLARE_PMID(kActionIDSpace, kStylisticSetsOTF20Action, kTextEditorPrefix2 + 19 )

DECLARE_PMID(kActionIDSpace, kJBulletActionID, kTextEditorPrefix2 + 20)
DECLARE_PMID(kActionIDSpace, kAlignTowardsSpineActionID, kTextEditorPrefix2 + 21)
DECLARE_PMID(kActionIDSpace, kAlignAwaySpineActionID, kTextEditorPrefix2 + 22)
DECLARE_PMID(kActionIDSpace, kToFootnoteTextActionID, kTextEditorPrefix2 + 23)
DECLARE_PMID(kActionIDSpace, kClearAllOverridesActionID, kTextEditorPrefix2 + 24)
DECLARE_PMID(kActionIDSpace, kClearCharacterOverridesActionID, kTextEditorPrefix2 + 25)
DECLARE_PMID(kActionIDSpace, kClearParagraphOverridesActionID, kTextEditorPrefix2 + 26)
DECLARE_PMID(kActionIDSpace, kThirdSpaceActionID, kTextEditorPrefix2 + 27)
DECLARE_PMID(kActionIDSpace, kQuarterSpaceActionID, kTextEditorPrefix2 + 28)
DECLARE_PMID(kActionIDSpace, kSixthSpaceActionID, kTextEditorPrefix2 + 29)

DECLARE_PMID(kActionIDSpace, kInsertFootnoteOrGotoActionID, kTextEditorPrefix2 + 30 )
DECLARE_PMID(kActionIDSpace, kNarrowNoBreakSpaceActionID, kTextEditorPrefix2 + 31 )
DECLARE_PMID(kActionIDSpace, kTextWhiteSep1ActionID, kTextEditorPrefix2 + 32 )
DECLARE_PMID(kActionIDSpace, kTextWhiteSep2ActionID, kTextEditorPrefix2 + 33 )
DECLARE_PMID(kActionIDSpace, kPositionFormsOffActionID, kTextEditorPrefix2 + 34)
DECLARE_PMID(kActionIDSpace, kPositionFormsAutoActionID, kTextEditorPrefix2 + 35)
DECLARE_PMID(kActionIDSpace, kPositionFormsInitialActionID, kTextEditorPrefix2 + 36)
DECLARE_PMID(kActionIDSpace, kPositionFormsMedialActionID, kTextEditorPrefix2 + 37)
DECLARE_PMID(kActionIDSpace, kPositionFormsFinalActionID, kTextEditorPrefix2 + 38)
DECLARE_PMID(kActionIDSpace, kPositionFormsIsolatedActionID, kTextEditorPrefix2 + 39)

DECLARE_PMID(kActionIDSpace, kVariableInsertActionID, kTextEditorPrefix2 + 40)
DECLARE_PMID(kActionIDSpace, kVariableConvertToTextActionID, kTextEditorPrefix2 + 41)
DECLARE_PMID(kActionIDSpace, kVariablesActionID, kTextEditorPrefix2 + 42)
DECLARE_PMID(kActionIDSpace, kIncreaseVertScaleActionID, kTextEditorPrefix2 + 43)
DECLARE_PMID(kActionIDSpace, kDecreaseVertScaleActionID, kTextEditorPrefix2 + 44)
DECLARE_PMID(kActionIDSpace, kIncreaseVertScaleTimes5ActionID, kTextEditorPrefix2 + 45)
DECLARE_PMID(kActionIDSpace, kDecreaseVertScaleTimes5ActionID, kTextEditorPrefix2 + 46)
DECLARE_PMID(kActionIDSpace, kTVSepAActionID, kTextEditorPrefix2 + 47)
DECLARE_PMID(kActionIDSpace, kTVSepBActionID, kTextEditorPrefix2 + 48)
DECLARE_PMID(kActionIDSpace, kTVSepCActionID, kTextEditorPrefix2 + 49)

DECLARE_PMID(kActionIDSpace, kDiscLineBreakActionID, kTextEditorPrefix2 + 50)
DECLARE_PMID(kActionIDSpace, kZeroWidthNonJoinerActionID, kTextEditorPrefix2 + 51)
DECLARE_PMID(kActionIDSpace, kTVUnused52, kTextEditorPrefix2 + 52)
DECLARE_PMID(kActionIDSpace, kTVUnused53, kTextEditorPrefix2 + 53)
DECLARE_PMID(kActionIDSpace, kTVBulletActionID, kTextEditorPrefix2 + 55)
DECLARE_PMID(kActionIDSpace, kTVCopyrightMarkActionID, kTextEditorPrefix2 + 56)
DECLARE_PMID(kActionIDSpace, kTVEllipseActionID, kTextEditorPrefix2 + 57)
DECLARE_PMID(kActionIDSpace, kTVParagraphReturnActionID, kTextEditorPrefix2 + 58)
DECLARE_PMID(kActionIDSpace, kTVRegistrationMarkActionID, kTextEditorPrefix2 + 59)

DECLARE_PMID(kActionIDSpace, kTVSectionMarkActionID, kTextEditorPrefix2 + 60)
DECLARE_PMID(kActionIDSpace, kTVTrademarkActionID, kTextEditorPrefix2 + 61)
DECLARE_PMID(kActionIDSpace, kVariablesSepDActionID, kTextEditorPrefix2 + 62)				// -------
DECLARE_PMID(kActionIDSpace, kTVEmDashActionID, kTextEditorPrefix2 + 63)
DECLARE_PMID(kActionIDSpace, kTVEnDashActionID, kTextEditorPrefix2 + 64)
DECLARE_PMID(kActionIDSpace, kVariablesSepEActionID, kTextEditorPrefix2 + 65)				// -------
DECLARE_PMID(kActionIDSpace, kTVEmSpaceActionID, kTextEditorPrefix2 + 66)
DECLARE_PMID(kActionIDSpace, kTVEnSpaceActionID, kTextEditorPrefix2 + 67)
DECLARE_PMID(kActionIDSpace, kTVFlushSpaceActionID, kTextEditorPrefix2 + 68)
DECLARE_PMID(kActionIDSpace, kTVHairSpaceActionID, kTextEditorPrefix2 + 69)

DECLARE_PMID(kActionIDSpace, kTVThinSpaceActionID, kTextEditorPrefix2 + 70)
DECLARE_PMID(kActionIDSpace, kTVFigureSpaceActionID, kTextEditorPrefix2 + 71)
DECLARE_PMID(kActionIDSpace, kTVPunctuationSpaceActionID, kTextEditorPrefix2 + 72)
DECLARE_PMID(kActionIDSpace, kVariablesSepFActionID, kTextEditorPrefix2 + 73)				// -------
DECLARE_PMID(kActionIDSpace, kTVDblOpenQuoteActionID, kTextEditorPrefix2 + 74)
DECLARE_PMID(kActionIDSpace, kTVDblCloseQuoteActionID, kTextEditorPrefix2 + 75)
DECLARE_PMID(kActionIDSpace, kTVSngOpenQuoteActionID, kTextEditorPrefix2 + 76)
DECLARE_PMID(kActionIDSpace, kTVSngCloseQuoteActionID, kTextEditorPrefix2 + 77)
DECLARE_PMID(kActionIDSpace, kTVDateTimeZoneLongActionID, kTextEditorPrefix2 + 78)
DECLARE_PMID(kActionIDSpace, kTVJBulletActionID, kTextEditorPrefix2 + 79)

DECLARE_PMID(kActionIDSpace, kTVIdeographicSpaceActionID, kTextEditorPrefix2 + 80)
DECLARE_PMID(kActionIDSpace, kTVThirdSpaceActionID, kTextEditorPrefix2 + 81)
DECLARE_PMID(kActionIDSpace, kTVQuarterSpaceActionID, kTextEditorPrefix2 + 82)
DECLARE_PMID(kActionIDSpace, kTVSixthSpaceActionID, kTextEditorPrefix2 + 83)
DECLARE_PMID(kActionIDSpace, kDblQuoteActionID, kTextEditorPrefix2 + 84)		// Does "straight" version of quote (")
DECLARE_PMID(kActionIDSpace, kSngQuoteActionID, kTextEditorPrefix2 + 85)		// Does "straight" version of quote/apostrophe (')
DECLARE_PMID(kActionIDSpace, kMacSpotlightTextSearchActionID, kTextEditorPrefix2 + 86)
DECLARE_PMID(kActionIDSpace, kTVCMenuDynamicActionID, kTextEditorPrefix2 + 87)
DECLARE_PMID(kActionIDSpace, kTVMenuDynamicActionID, kTextEditorPrefix2 + 88)
DECLARE_PMID(kActionIDSpace, kEuclideanSpaceActionID, kTextEditorPrefix2 + 89)

DECLARE_PMID(kActionIDSpace, kSpecialSep4ActionID, kTextEditorPrefix2 + 90)
DECLARE_PMID(kActionIDSpace, kDashActionID1, kTextEditorPrefix2 + 91)
DECLARE_PMID(kActionIDSpace, kDashActionID2, kTextEditorPrefix2 + 92)
DECLARE_PMID(kActionIDSpace, kCJKIdeoSpaceBehaviorActionID, kTextEditorPrefix2 + 93)
DECLARE_PMID(kActionIDSpace, kCJKWordWrapOffActionID, kTextEditorPrefix2 + 94)

// gap IDS 95-138 ARE available (they used to be reserved for variables)
// Date popout Menu (Variables)
DECLARE_PMID(kActionIDSpace, kTVDateTimeActionID, kTextEditorPrefix2 + 139)

DECLARE_PMID(kActionIDSpace, kTVDateDayActionID, kTextEditorPrefix2 + 140)
DECLARE_PMID(kActionIDSpace, kTVDateMonthActionID, kTextEditorPrefix2 + 141)
DECLARE_PMID(kActionIDSpace, kTVDateYearActionID, kTextEditorPrefix2 + 142)
DECLARE_PMID(kActionIDSpace, kTVDateTimeHourActionID, kTextEditorPrefix2 + 143)
DECLARE_PMID(kActionIDSpace, kTVDateTimeHour01ActionID, kTextEditorPrefix2 + 144)
DECLARE_PMID(kActionIDSpace, kTVDateTimeHour24ActionID, kTextEditorPrefix2 + 145)
DECLARE_PMID(kActionIDSpace, kTVDateTimeHour024ActionID, kTextEditorPrefix2 + 146)
DECLARE_PMID(kActionIDSpace, kTVDateTimeMinuteActionID, kTextEditorPrefix2 + 147)
DECLARE_PMID(kActionIDSpace, kTVDateTimeMinute00ActionID, kTextEditorPrefix2 + 148)
DECLARE_PMID(kActionIDSpace, kTVDateTimeSecondActionID, kTextEditorPrefix2 + 149)

DECLARE_PMID(kActionIDSpace, kTVDateTimeSecond00ActionID, kTextEditorPrefix2 + 150)
DECLARE_PMID(kActionIDSpace, kTVDateTimeampmShortActionID, kTextEditorPrefix2 + 151)
DECLARE_PMID(kActionIDSpace, kTVDateTimeampmActionID, kTextEditorPrefix2 + 152)
DECLARE_PMID(kActionIDSpace, kTVDateTimeAMPMShortActionID, kTextEditorPrefix2 + 153)
DECLARE_PMID(kActionIDSpace, kTVDateTimeAMPMActionID, kTextEditorPrefix2 + 154)
DECLARE_PMID(kActionIDSpace, kTVDateDayNumberActionID, kTextEditorPrefix2 + 155)
DECLARE_PMID(kActionIDSpace, kTVDateDayNumber01ActionID, kTextEditorPrefix2 + 156)
DECLARE_PMID(kActionIDSpace, kTVDateDayNumberRomanLowerActionID, kTextEditorPrefix2 + 157)
DECLARE_PMID(kActionIDSpace, kTVDateDayNumberRomanUpperActionID, kTextEditorPrefix2 + 158)
DECLARE_PMID(kActionIDSpace, kTVDateDayNameActionID, kTextEditorPrefix2 + 159)

DECLARE_PMID(kActionIDSpace, kTVDateDayNameShortActionID, kTextEditorPrefix2 + 160)
DECLARE_PMID(kActionIDSpace, kTVDateMonthNumberActionID, kTextEditorPrefix2 + 161)
DECLARE_PMID(kActionIDSpace, kTVDateMonthNumber01ActionID, kTextEditorPrefix2 + 162)
DECLARE_PMID(kActionIDSpace, kTVDateMonthNameActionID, kTextEditorPrefix2 + 163)
DECLARE_PMID(kActionIDSpace, kTVDateMonthNameShortActionID, kTextEditorPrefix2 + 164)
DECLARE_PMID(kActionIDSpace, kTVDateYearLongActionID, kTextEditorPrefix2 + 165)
DECLARE_PMID(kActionIDSpace, kTVDateYearShortActionID, kTextEditorPrefix2 + 166)
DECLARE_PMID(kActionIDSpace, kTVDateYearTeenyActionID, kTextEditorPrefix2 + 167)
DECLARE_PMID(kActionIDSpace, kTVDateYearRomanUpperActionID, kTextEditorPrefix2 + 168)
DECLARE_PMID(kActionIDSpace, kTVDateYearRomanLowerActionID, kTextEditorPrefix2 + 169)

DECLARE_PMID(kActionIDSpace, kTVDateTimeZoneShortActionID, kTextEditorPrefix2 + 170)
DECLARE_PMID(kActionIDSpace, kTVDateYearEraShortActionID, kTextEditorPrefix2 + 171)
DECLARE_PMID(kActionIDSpace, kQuickApplyVariablesPrefActionID, kTextEditorPrefix2 + 172)
DECLARE_PMID(kActionIDSpace, kInsertTextSep2ActionID, kTextEditorPrefix2 + 173)

// Endnote
DECLARE_PMID(kActionIDSpace, kInsertEndnoteActionID, kTextEditorPrefix2 + 174)
DECLARE_PMID(kActionIDSpace, kInsertEndnoteOrGotoActionID, kTextEditorPrefix2 + 175)
DECLARE_PMID(kActionIDSpace, kToEndnoteTextActionID, kTextEditorPrefix2 + 176)

DECLARE_PMID(kActionIDSpace, kOpenFastEditorActionID, kTextEditorPrefix2 + 177)
DECLARE_PMID(kActionIDSpace, kCopyEditorFeedackActionID, kTextEditorPrefix2 + 178)
DECLARE_PMID(kActionIDSpace, kTextEditorDynamicActionID, kTextEditorPrefix2 + 179)
DECLARE_PMID(kActionIDSpace, kCopyEditorFeedbackDynamicActionID, kTextEditorPrefix2 + 180)
// gap

DECLARE_PMID(kActionIDSpace, kTVFirstDynamicActionID, kTextEditorPrefix3 +1				/* First variable item */)
// DONT USE THE IDS 1-151 they are reserved for variables (dynamic menu)						150..
DECLARE_PMID(kActionIDSpace, kTVLastDynamicActionID, kTextEditorPrefix3 +151			/* Last variable item */)
#endif
// __TextEditorActionID__
