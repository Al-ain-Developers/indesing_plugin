//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFootnoteSettings.h $
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

#pragma once
#ifndef __IFootnoteSettings__
#define __IFootnoteSettings__

/** Minimum starting footnote number. */
#define kMinStartingFootnoteNumber		1

/** Maximum starting footnote number. */
#define kMaxStartingFootnoteNumber	100000

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "TextID.h"
#include "CTextEnum.h"
#include "ITextAttrStrokeType.h"

class PMString;

/** This interface is used to set or retrieve the settings associated with footnotes.
	@ingroup text_layout
*/
class IFootnoteSettings : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFOOTNOTESETTINGS };

	/** The different ways to restart numbering of footnotes.
	*/
	typedef enum { kDontRestart, kPageRestart, kSpreadRestart, kSectionRestart, kUnknown } RestartNumberingOptions;

	/** There are two types of footnote rules.  One is applied when a new footnote is the first footnote to appear in the column.
		The second is when a footnote continues from the previous column.  This enum is used to designate which one the caller is interested in.
	*/
	typedef enum { kNew, kContinuing } FootnoteRuleKind;

	/** The different ways to apply prefixes and suffixes to the numbering of footnotes.
	@note: kPrefixSuffixReference refers to the footnote number as it appears in the main text flow
	@note: kPrefixSuffixMarker refers to the footnote number as it appears in the footnote text itself
	*/
	typedef enum { kPrefixSuffixNone, kPrefixSuffixReference, kPrefixSuffixMarker, kPrefixSuffixBoth } SuffixPrefixUsageOptions;

	/** The different ways to apply positioning to the footnote marker.
	@note: kPositionRuby is available in the Japanese Feature Set only.
	*/
	typedef enum { kPositionNormal, kPositionSuperscript, kPositionSubscript, kPositionRuby } MarkerPositionOptions;

	/** Return the option showing when footnotes restart numbering.
	*/
	virtual RestartNumberingOptions GetRestartOption() const = 0;
	/** Set the option showing when footnotes restart numbering.
	*/
	virtual void SetRestartOption(RestartNumberingOptions option) = 0;

	/** Return the number footnotes should start with.
	*/
	virtual int32 GetStartingNumber() const = 0;
	/** Set the number footnotes should start with.
	*/
	virtual void SetStartingNumber(int32 n) = 0;

	/** Return how the footnotes are numbered.  Arabic, roman numerals, etc.
	*/
	virtual ClassID GetNumberingMethod() const = 0;
	/** Set how the footnotes are numbered.  Arabic, roman numerals, etc.
	*/
	virtual void SetNumberingMethod(ClassID whichMethod) = 0;

	/** Return the string to appear before the footnote number
	*/
	virtual const WideString& GetMarkerPrefix() const = 0;
	/** Set the string to appear before the footnote number
	*/
	virtual void SetMarkerPrefix(const WideString& pre) = 0;

	/** Return the string to appear after the footnote number
	*/
	virtual const WideString& GetMarkerSuffix() const = 0;
	/** Set the string to appear after the footnote number
	*/
	virtual void SetMarkerSuffix(const WideString& suf) = 0;

	/** Return where the prefix/suffix strings should occur with regards to footnotes
	*/
	virtual SuffixPrefixUsageOptions GetPrefixSuffixUsage() const = 0;
	/** Set where the prefix/suffix strings should occur with regards to footnotes
	*/
	virtual void SetPrefixSuffixUsage(SuffixPrefixUsageOptions options) = 0;

	/** Return the character style applied to the footnote symbol in the text
		@note: can return kInvalidUID - see GetFootnoteMarkerStyle
	*/
	virtual UID GetFootnoteMarkerStyle() const = 0;
	/** Set the character style applied to the footnote symbol in the text
		@note: The UID can be kInvalidUID which uses the default style for new footnotes, but doesn't change the style of existing footnotes. (All others change the style of existing footnotes to the new style.)
	*/
	virtual void SetFootnoteMarkerStyle(UID s) = 0;

	/** Return the current positioning style for the footnote marker.
	*/
	virtual MarkerPositionOptions GetMarkerPositioning() const = 0;
	/** Set the current positioning style for the footnote marker.
	*/
	virtual void SetMarkerPositioning(MarkerPositionOptions positioning) = 0;

	/** Return the paragraph style applied to the footnotes themselves
	*/
	virtual UID GetFootnoteParagraphStyle() const = 0;
	/** Set the paragraph style applied to the footnotes themselves
	*/
	virtual void SetFootnoteParagraphStyle(UID s) = 0;

	/** Return what text is automatically added between the footnote symbol and the footnote in the footnote.
	*/
	virtual const WideString& GetFootnoteSeparator() const = 0;
	/** Set what text is automatically added between the footnote symbol and the footnote in the footnote.
	*/
	virtual void  SetFootnoteSeparator(const WideString& sep) = 0;

	/**  Return the space between footnote parcels
	*/
	virtual PMReal GetSpaceBetween() const = 0;
	/**  Set the space between footnote parcels
	*/
	virtual void SetSpaceBetween(PMReal g) = 0;

	/** Return the space between the main text and the first footnote
	*/
	virtual PMReal GetSpacerHeight() const = 0;
	/** Set the space between the main text and the first footnote
	*/
	virtual void SetSpacerHeight(PMReal g) = 0;

	/** Return the baseline offset of the first line in the footnote
	*/
	virtual Text::FirstLineOffsetMetric GetFirstLineOffset() const = 0;
	/** Set the baseline offset of the first line in the footnote
	*/
	virtual void SetFirstLineOffset(Text::FirstLineOffsetMetric flo) = 0;

	/** Return the minimum baseline offset of the first line in the footnote
	*/
	virtual PMReal GetMinFirstLineOffset() const = 0;
	/** Set the minimum baseline offset of the first line in the footnote
	*/
	virtual void SetMinFirstLineOffset(PMReal g) = 0;

	/** Return whether the footnote at the end of the story will be placed at the bottom of the column (kFalse) or just below the text (kTrue).
	*/
	virtual bool16 GetEndOfStoryPlacement() const = 0;
	/** Set whether the footnote at the end of the story will be placed at the bottom of the column (kFalse) or just below the text (kTrue).
	*/
	virtual void SetEndOfStoryPlacement(bool16 b) = 0;

	/** Return whether the footnotes that don't fit in the current column can flow into the next column (kFalse) or force the marker to the next column where the entire footnote will fit (kTrue).
	*/
	virtual bool16 GetNoSplitting() const = 0;
	/** Set whether the footnotes that don't fit in the current column can flow into the next column (kFalse) or force the marker to the next column where the entire footnote will fit (kTrue).
	*/
	virtual void SetNoSplitting(bool16 b) = 0;

	/** Return whether straddling is enabled or not.
	*/
	virtual bool16 GetStraddlingInfo() const = 0;
	/** Set whether straddling is enabled or not.
	*/
	virtual void SetStraddlingInfo(bool16 b) = 0;

	/** Return whether we are showing the separator line or not.
	*/
	virtual bool16 GetSeparatorLineOn(FootnoteRuleKind k) const = 0;
	/** Set whether we are showing the separator line or not.
	*/
	virtual void SetSeparatorLineOn(FootnoteRuleKind k, bool16 b) = 0;

	/** Return the weight of the desired line that separates the footnotes from the main text.
	*/
	virtual PMReal GetWeightStroke(FootnoteRuleKind k) const = 0;
	/** Set the weight of the desired line that separates the footnotes from the main text.
	*/
	virtual void SetWeightStroke(FootnoteRuleKind k, PMReal g) = 0;

	/** Return the type/style of the desired line that separates the footnotes from the main text.
		e.g. solid line, dashed line, etc
	*/
	virtual ICompositionStyle::StrokeType GetStrokeType(FootnoteRuleKind k) const = 0;
	/** Set the type/style of the desired line that separates the footnotes from the main text.
		e.g. solid line, dashed line, etc
	*/
	virtual void SetStrokeType(FootnoteRuleKind k, ICompositionStyle::StrokeType s) = 0;

	/** Return the left indent of the desired line that separates the footnotes from the main text.
	*/
	virtual PMReal GetIndentLeft(FootnoteRuleKind k) const = 0;
	/** Set the left indent of the desired line that separates the footnotes from the main text.
	*/
	virtual void SetIndentLeft(FootnoteRuleKind k, PMReal g) = 0;

	/** Return the width of the desired line that separates the footnotes from the main text.
	*/
	virtual PMReal GetWidth(FootnoteRuleKind k) const = 0;
	/** Set the width of the desired line that separates the footnotes from the main text.
	*/
	virtual void SetWidth(FootnoteRuleKind k, PMReal g) = 0;

	/** Return the offset of the desired line that separates the footnotes from the main text.
	*/
	virtual PMReal GetOffset(FootnoteRuleKind k) const = 0;
	/** Set the offset of the desired line that separates the footnotes from the main text.
	*/
	virtual void SetOffset(FootnoteRuleKind k, PMReal g) = 0;

	/** Return the color of the desired line that separates the footnotes from the main text.
	*/
	virtual UID GetColorStroke(FootnoteRuleKind k) const = 0;
	/** Set the color of the desired line that separates the footnotes from the main text.
	*/
	virtual void SetColorStroke(FootnoteRuleKind k, UID s) = 0;

	/** Return the tint of the desired line that separates the footnotes from the main text.
	*/
	virtual PMReal GetTintStroke(FootnoteRuleKind k) const = 0;
	/** Set the tint of the desired line that separates the footnotes from the main text.
	*/
	virtual void SetTintStroke(FootnoteRuleKind k, PMReal g) = 0;

	/** Return whether overprint is on for the desired line that separates the footnotes from the main text.
	*/
	virtual bool16 GetOverprintStroke(FootnoteRuleKind k) const = 0;
	/** Set whether overprint is on for the desired line that separates the footnotes from the main text.
	*/
	virtual void SetOverprintStroke(FootnoteRuleKind k, bool16 b) = 0;

	/** Return the color of the line gap, if any, that separates the footnotes from the main text.
	*/
	virtual UID GetColorGap(FootnoteRuleKind k) const = 0;
	/** Set the color of the line gap, if any, that separates the footnotes from the main text.
	*/
	virtual void SetColorGap(FootnoteRuleKind k, UID s) = 0;

	/** Return the tint of the line gap, if any, that separates the footnotes from the main text.
	*/
	virtual PMReal GetTintGap(FootnoteRuleKind k) const = 0;
	/** Set the tint of the line gap, if any, that separates the footnotes from the main text.
	*/
	virtual void SetTintGap(FootnoteRuleKind k, PMReal g) = 0;

	/** Return whether overprint is on for the line gap, if any, that separates the footnotes from the main text.
	*/
	virtual bool16 GetOverprintGap(FootnoteRuleKind k) const = 0;
	/** Set whether overprint is on for the line gap, if any, that separates the footnotes from the main text.
	*/
	virtual void SetOverprintGap(FootnoteRuleKind k, bool16 b) = 0;
};
#endif	// __ODFRC__

#endif
	// __IFootnoteSettings__

