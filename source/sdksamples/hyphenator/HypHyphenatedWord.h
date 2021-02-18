//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypHyphenatedWord.h $
//
//  Owner: Adobe Developer Technologies
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

#ifndef __HypHyphenatedWord__
#define __HypHyphenatedWord__

#include "Hyp.h"

// Forward declarations:
class WideString;
class PMString;
class HypHyphenationPair;
class IHyphenatedWord;
class TextCharBuffer;

/** The word with its hyphenation points used by the application to
	find the index and the quality of each hyphen and the text
	that surrounds it.

	@ingroup hyphenator

 */
class HypHyphenatedWord : public IHyphenatedWord
{
	public:
		/**	Constructor. Hyphenation points that are outside the range given
			by nMinHead..wordLength-nMinTail are discarded. Duplicate hyphenation
			points are discarded.
			@param originalWord passed when IHyphenationService::Hyphenate was called.
			@param nMinTail the minimum number of characters at the end of a word after a hyphen break.
			@param nMinHead the minimum number of characters at the start of a word before a hyphen break.
			@param hyphenationPoints giving index and quality of each hyphenation point.
		 */
							HypHyphenatedWord(const TextCharBuffer& originalWord, const uint16 nMinTail, const uint16 nMinHead, const Hyp::HyphenationPoints& hyphenationPoints);

		/** Destructor.
		 */
		virtual				~HypHyphenatedWord();

	public:
		/** @return the total number of hyphenation points.
		 */
		virtual	int32		GetPointCount() const;

		/** @param nNthPoint The Nth hyphenation point.
			@return the index in the word of the Nth hyphenation point.
			The index is the position before the hyphen: i.e. ser-vice returns 2.
		 */
		virtual	int32		GetIndexOfPoint(int32 nNthPoint) const;

		/** @param nNthPoint The Nth hyphenation point.
			@return the quality value of the Nth hyphenation point e.g. kRegularHyphenPoint.
		 */
		virtual	int32		GetQualityOfPoint(int32 nNthPoint) const;

		/** @return the characters of the word.
		 */
		virtual	WideString	GetWord() const;

		/**	Get strings with text before/after the Nth hyphen point.
			@param nNthPoint
			@param pFirstPart of the word before the Nth hyphen e.g. ser for ser-vice.
			@param pLastPart of the word after the Nth hyphen e.g. vice for ser-vice.
		 */
		virtual	void		GetPartsOfPoint(int32 nNthPoint, WideString* pFirstPart, WideString* pLastPart) const;

		/**	Get string with text before the Nth hyphen point.
			@param nNthPoint
			@param pPart of the word before the Nth hyphen e.g. ser for ser-vice.
		 */
		virtual	void		GetFirstPartOfPoint(int32 nNthPoint, WideString* pPart) const;

		/**	Get string with text after the Nth hyphen point.
			@param nNthPoint
			@param pPart of the word before the Nth hyphen e.g. vice for ser-vice.
		 */
		virtual	void		GetLastPartOfPoint(int32 nNthPoint, WideString* pPart) const;

		/** Add the hyphenation points in pToMergeWith to this word.
			@param pToMergeWith The hyphenated word to merge with.
		 */
		virtual	void		Merge(const IHyphenatedWord* pToMergeWith);

		/** Empty implementation. All hyphenation points are checked
			to be in a valid range before being accepted. See
			nMinTail and nMinHead description in HypAdapter.
		 */
		virtual void		ValidatePointRanges();

	private:
		const TextCharBuffer	fOriginalWord;
		const uint16			fnMinTail;
		const uint16			fnMinHead;
		Hyp::HyphenationPoints	fHyphenationPoints;
};

#endif // __HypHyphenatedWord__
