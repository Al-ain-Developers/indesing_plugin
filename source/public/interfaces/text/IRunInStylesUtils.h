//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IRunInStylesUtils.h $
//  
//  Owner: Eric Menninga
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
#ifndef __IRunInStylesUtils__
#define __IRunInStylesUtils__

#include "IPMUnknown.h"

#include "K2Vector.h"
#include "TextID.h"


class ITextModel;
class ICompositionStyle;
class WideString;
class PMString;


class RunInStyleResult
{
	public:
		typedef K2Vector<UID>	CharStyleList;

		RunInStyleResult() : fLength(0), fLineRuleIndex(-1), fLinesCount(0)
			{ }
		RunInStyleResult(UID cs, int32 len) : fLength(len), fLineRuleIndex(-1), fLinesCount(0)
			{ fCharStyles.push_back(cs);  }
		RunInStyleResult(UID cs, int32 len, int32 ndx, int32 lc) : fLength(len), fLineRuleIndex(ndx), fLinesCount(lc)
			{ fCharStyles.push_back(cs); }
		RunInStyleResult(const CharStyleList& cs, int32 len, int32 ndx, int32 lc) : fLength(len), fLineRuleIndex(ndx), fLinesCount(lc)
			{ fCharStyles = cs; }

		UID CharStyle(uint32 i) const
			{ return (i < fCharStyles.size()) ? fCharStyles[i] : kInvalidUID; }
		CharStyleList& CharStyles()
			{ return fCharStyles; }
		const CharStyleList& CharStyles() const
			{ return fCharStyles; }

		int32 Length() const
			{ return fLength; }
		int32& Length()
			{ return fLength; }

		int32 LineRuleIndex() const
			{ return fLineRuleIndex; }
		int16& LineRuleIndex()
			{ return fLineRuleIndex; }

		int32 LinesCount() const
			{ return fLinesCount; }
		int16& LinesCount()
			{ return fLinesCount; }

	   	typedef object_type data_type;
	private:
		CharStyleList	fCharStyles;
		int32	fLength;
		int16	fLineRuleIndex;
		int16	fLinesCount;
};

/** This list will contain the results of applying the specified run-in styles
	to a paragraph. The data in the list consists of the UID of the character style
	and an int32 which is the number of characters that the character style applies to.
	@see IRunInStylesUtils::ParseParagraphForRunInStyles()
	@ingroup text_style
	*/
class RunInStyleResults : public K2Vector<RunInStyleResult>
{
public:
	void Append(UID cs, int32 len, int32 lineRule, int32 linesCount)
		{
		if (empty() ||  back().LineRuleIndex() != lineRule)
			push_back(RunInStyleResult(cs, len, lineRule, linesCount));
		else
			{
			const RunInStyleResult::CharStyleList& list = back().CharStyles();
			if (list.empty() || list.size() > 1 || list[0] != cs)
				push_back(RunInStyleResult(cs, len, lineRule, linesCount));
			else
				back().Length() += len;
			}
		}

	void Append(UID cs, int32 len)
		{
		if (empty() || back().LineRuleIndex() >= 0)
			push_back(RunInStyleResult(cs, len));
		else
			{
			const RunInStyleResult::CharStyleList& list = back().CharStyles();
			if (list.empty() || list.size() > 1 || list[0] != cs)
				push_back(RunInStyleResult(cs, len));
			else
				back().Length() += len;
			}
		}

	void RemoveFirst()
		{ erase(begin(), begin() + 1); }
};


/** Some utility functions to aid in processing run-in styles
	@ingroup text_util
	@ingroup text_style
*/
class IRunInStylesUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IRUNINSTYLESUTILS };

			/** Calculate the Run-In style transition points for the given paragraph
				@param model the text model of the story being examined
				@param position usually the starting index of the paragraph being examined
				@param paragraphStyle the paragraph attributes for the paragraph.
						If the paragraphStyle is nil, then everything is fine and the position can be arbitrary.
						If the paragraphStyle is NOT file, then it position should be == to paragraph start.
				@param results a list of run-in styles for this paragraph specified as an ordered
								list of <character style UID, number of characters> pairs
				@param ignoreUnsetLines specifies whether to ignore "lines" nested styles or to set that style over the
								entire remaining paragraph. In already-composed paragraphs, this parameter is
								ignored, but in uncomposed paragraphs, the choice exists. Generally, they are ignored
								except by composition itself.
				@param pParagraphLengthLeft should be SET to the paragraph length if the paragraphStyle was passed in,
						otherwise, it's for occasional callers who need to know the rest of the paragraph's length too.
				@param moveBackwards specifies the direction in which rest of the paragraph's length is to be reported.
						The value is kTrue for backwards direction and kFalse for forward direction.
				@return kTrue if the paragraph at the position has runins (results could be empty if position past the affected range) */
//		enum HandleUncomposedNestedLines { kIgnoreNestedLines, kRestOfParagraphNestedLines };
		virtual bool16 ParseParagraphForRunInStyles(const ITextModel *model, TextIndex position,
						const ICompositionStyle *paragraphStyle, RunInStyleResults& results, //HandleUncomposedNestedLines lines = kIgnoreNestedLines,
						int32 *pParagraphLengthLeft = nil, bool16 moveBackwards = kFalse) = 0;

			/** map the attribute's expression string into a PMString for readibility. The
				attribute is split into the characters to match and the count.
				@param expression the attribute's value describing the rule
				@param pOutput the string that should contain a readable version of the rule
				@param pCount the number of TIMES that the expression should be found before switching styles
				@param pInclusive will be return whether the style INCLUDES the final trigger
				@see RunInStyleRule */
		virtual void MapExpressionToPMString(const WideString& expression, PMString *pOutput, int32 *pCount, bool16 *pInclusive) = 0;

			/** map a user description of a rule PLUS a count into an attribute's expression string
				@param nicePhrase a PMString version of the rule
				@param count the number of time the rule should be satisfied
				@param pExpression the attribute's rule string the describes the input.
				@param inclusive declares whether the style INCLUDES the final trigger
				@see RunInStyleRule */
		virtual void MapPMStringToExpression(const PMString& nicePhrase, int32 count, bool16 inclusive, WideString *pExpression) = 0;

			/** toggle whether the rule include the character that triggers the switch or not
				@param original the original expression from the run-in style list
				@param pToggled the new expression, with the inclusion toggled
				@return some expressions are not toggle-able and if original == *pToggled this will return kFalse
				@see RunInStyleRule */
		virtual bool16 ToggleExpressionInclusion(const WideString& original, WideString *pToggled) = 0;

			/** calculate actual number of char that dropcap need to be applied (adjusted for hidden character at the beginning of paragraph)
				@param beginPosition beginning position for dropcap evaluation (usually beginning position of paragraph)
				@param baseCharCount number of dropcap char specified by user
				@param dcText actual text string used for dropcap
				@return actual number of char dropcap will be applied starting beginning position
				@see RunInStyleRule */
		virtual int32 CalculateDropCapCount(const TextIterator& beginPosition, int16 baseCharCount, WideString * dcText) = 0;
};


#endif	// __IRunInStylesUtils__
