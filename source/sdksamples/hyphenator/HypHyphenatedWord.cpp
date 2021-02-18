//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypHyphenatedWord.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IHyphenatedWord.h"

// General includes:
#include "TextCharBuffer.h"
#include "WideString.h"
#include "PMString.h"
#include "LinguisticID.h"
#include "Trace.h"
#include "KeyValuePair.h"
#include "K2Vector.tpp"

// Project includes:	
#include "HypHyphenatedWord.h"
#include "HypDiagnostic.h"
#include "HypPerformanceData.h"
#include "Hyp.h"

/*
 */
HypHyphenatedWord::HypHyphenatedWord(const TextCharBuffer& originalWord, const uint16 nMinTail, const uint16 nMinHead, const Hyp::HyphenationPoints& hyphenationPoints) 
: fOriginalWord(originalWord), fnMinTail(nMinTail), fnMinHead(nMinHead)
{
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::HypHyphenatedWord()-->In\n");
	
	uint64 numHyphsThisWord = 0;
	
	// update the Hyphenation Total metric 
	HypPerformanceData::IncrementHypTotal();
	
	// Construct a hyphenated word.
	int32 wordLength = fOriginalWord.CharCount();
	for (Hyp::HyphenationPoints::const_iterator iter = hyphenationPoints.begin(); iter < hyphenationPoints.end(); iter++) {
		Hyp::HyphenIndex hyphenIndex = iter->Key();
		ASSERT_MSG(hyphenIndex > 0 && hyphenIndex < wordLength, FORMAT_ARGS("Can't have a hyphen before the start or after the end of the word hyphenIndex=%d", hyphenIndex));
		if (hyphenIndex <= 0 || hyphenIndex >= wordLength) {
			// Skip this invalid hyphenation point.
			continue;
		}
		if (hyphenIndex < fnMinHead || wordLength - hyphenIndex < fnMinTail) {
			// Skip hyphenation points outside the range of valid hyphen indexes.
			TRACEFLOW("Hyphenator HypHyphenatedWord", "Igoring hyphenation outside valid hyphenIndex range=%d", hyphenIndex);
			continue;
		}
		Hyp::HyphenationPoints::const_iterator findIter = K2find(fHyphenationPoints.begin(), fHyphenationPoints.end(), hyphenIndex);
		if (findIter != fHyphenationPoints.end()) {
			// Word already hyphenated at this point, skip it.
			TRACEFLOW("Hyphenator HypHyphenatedWord", "Ignoring duplicate hyphenation point hyphenIndex=%d", hyphenIndex);
			continue;
		}
		fHyphenationPoints.push_back(*iter);
		
		// update the Hyphenation Max metric 
		numHyphsThisWord++;	
		if(numHyphsThisWord > HypPerformanceData::GetHypMax())
		{
			HypPerformanceData::SetHypMax(numHyphsThisWord);
		}		
	}
	std::sort(fHyphenationPoints.begin(), fHyphenationPoints.end());
	
	// Trace the hyphenated word.
	HypDiagnostic diagnostic("Hyphenator");
	diagnostic.TraceHyphenatedWord(*this);
	
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::HypHyphenatedWord()-->Out\n");
}

/*
 */
HypHyphenatedWord::~HypHyphenatedWord( )
{
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::~HypHyphenatedWord()\n");
}

/*
 */
int32 HypHyphenatedWord::GetPointCount( ) const
{
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::ValidatePointRanges()-->In result=%d\n", fHyphenationPoints.size());
	return(fHyphenationPoints.size());
}

/*
 */
int32 HypHyphenatedWord::GetIndexOfPoint(int32 nNthPoint) const
{
	Hyp::HyphenIndex result = kInvalidHyphenPoint;
	ASSERT_MSG(nNthPoint >= 0 && nNthPoint < fHyphenationPoints.size(), FORMAT_ARGS("nNthPoint=%d contains an invalid index", nNthPoint));
	if (nNthPoint >= 0 && nNthPoint < fHyphenationPoints.size()) {
		result = fHyphenationPoints [nNthPoint].Key();
	}
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::GetIndexOfPoint(%d) result=%d\n", nNthPoint, result);
	return result;
}

/*
 */
int32 HypHyphenatedWord::GetQualityOfPoint(int32 nNthPoint) const
{
	Hyp::HyphenQuality result = kInvalidHyphenPoint;
	ASSERT_MSG(nNthPoint >= 0 && nNthPoint < fHyphenationPoints.size(), FORMAT_ARGS("nNthPoint=%d contains an invalid index", nNthPoint));
	if (nNthPoint >= 0 && nNthPoint < fHyphenationPoints.size()) {
		result = fHyphenationPoints [nNthPoint].Value();
	}
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::GetQualityOfPoint(%d) result=%d\n", nNthPoint, result);
	return result;
}

/*
 */
WideString HypHyphenatedWord::GetWord() const
{
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::GetWord()\n");
	WideString word(fOriginalWord.begin_raw(), fOriginalWord.end_raw() - fOriginalWord.begin_raw(), fOriginalWord.CharCount());
	TRACEFLOW("Hyphenator HypHyphenatedWord", " fOriginalWord=\"%s\"\n", PMString(word).GetUTF8String().c_str());
	return word;
}

/*
 */
void HypHyphenatedWord::GetPartsOfPoint(int32 nNthPoint, WideString* pFirstPart, WideString* pLastPart) const
{
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::GetFirstPartOfPoint(%d)-->In\n", nNthPoint);
	this->GetFirstPartOfPoint(nNthPoint, pFirstPart);
	this->GetLastPartOfPoint(nNthPoint, pLastPart);
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::GetFirstPartOfPoint(%d)-->Out\n", nNthPoint);
}

/*
 */
void HypHyphenatedWord::GetFirstPartOfPoint(int32 nNthPoint, WideString* pPart) const
{
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::GetFirstPartOfPoint(%d)-->In\n", nNthPoint);
	do {
		ASSERT(pPart != nil);
		if (pPart == nil) {
			break;
		}
		ASSERT_MSG(nNthPoint >= 0 && nNthPoint < fHyphenationPoints.size(), FORMAT_ARGS("nNthPoint=%d contains an invalid index", nNthPoint));
		if (nNthPoint < 0 || nNthPoint >= fHyphenationPoints.size()) {
			break;
		}
		Hyp::HyphenIndex hyphenIndex = fHyphenationPoints[nNthPoint].Key();
		
		WideString tempWord(fOriginalWord.begin_raw(), fOriginalWord.end_raw()-fOriginalWord.begin_raw(), fOriginalWord.CharCount());
		*pPart = WideString(tempWord.begin(), hyphenIndex);
		PMString	partString(WideString(pPart->begin(), pPart->CharCount()));
		TRACEFLOW("Hyphenator HypHyphenatedWord", " pPart=\"%s\"\n", partString.GetUTF8String().c_str());
	} while(false);
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::GetFirstPartOfPoint(%d)-->Out\n", nNthPoint);
}

/*
 */
void HypHyphenatedWord::GetLastPartOfPoint(int32 nNthPoint, WideString* pPart) const
{
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::GetLastPartOfPoint(%d)-->In\n", nNthPoint);
	do {
		ASSERT(pPart != nil);
		if (pPart == nil) {
			break;
		}
		ASSERT_MSG(nNthPoint >= 0 && nNthPoint < fHyphenationPoints.size(), FORMAT_ARGS("nNthPoint=%d contains an invalid index", nNthPoint));
		if (nNthPoint < 0 || nNthPoint >= fHyphenationPoints.size()) {
			break;
		}
		Hyp::HyphenIndex hyphenIndex = fHyphenationPoints[nNthPoint].Key();
		WideString tempWord(fOriginalWord.begin_raw(), fOriginalWord.end_raw()-fOriginalWord.begin_raw(), fOriginalWord.CharCount());
		*pPart = WideString(tempWord.begin()+hyphenIndex, fOriginalWord.CharCount()-hyphenIndex);
		PMString	partString(*pPart);
		TRACEFLOW("Hyphenator HypHyphenatedWord", " pPart=\"%s\"\n", partString.GetUTF8String().c_str());
	} while(false);
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::GetLastPartOfPoint(%d)-->Out\n", nNthPoint);
}

/*
 */
void HypHyphenatedWord::Merge(const IHyphenatedWord* pToMergeWith)
{
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::Merge()-->In\n");
	
	do {
		// Validate parameters.
		ASSERT(pToMergeWith != nil);
		if (pToMergeWith == nil) {
			break;
		}
		
		// The word to be merged should be the same as this word.
		WideString mergeWord = pToMergeWith->GetWord();
		WideString thisWord(fOriginalWord.begin_raw(), fOriginalWord.end_raw()-fOriginalWord.begin_raw(), fOriginalWord.CharCount());
		ASSERT_MSG(mergeWord == thisWord, "Cannot merge hyphenation points for a different word");
		if (mergeWord != thisWord) {
			break;
		}
		
		// Trace the word to be merged.
		TRACEFLOW("Hyphenator HypHyphenatedWord", " word to be merged:\n");
		HypDiagnostic diagnostic("Hyphenator");
		diagnostic.TraceHyphenatedWord(*pToMergeWith);
		
		// Trace this word.
		TRACEFLOW("Hyphenator HypHyphenatedWord", " this word:\n");
		diagnostic.TraceHyphenatedWord(*this);
		
		// Loop through the merge word's hyphenation points.
		int32 insertCount = 0;
		int32 thisWordLength = thisWord.CharCount();
		for (int32 i = 0; i < pToMergeWith->GetPointCount(); i++)
		{
			// Get the merge word's next hyphenation point.
			Hyp::HyphenIndex hyphenIndex = pToMergeWith->GetIndexOfPoint(i);
			ASSERT_MSG(hyphenIndex > 0 && hyphenIndex < thisWordLength, FORMAT_ARGS("Can't have a hyphen before the start or after the end of the word hyphenIndex=%d", hyphenIndex));
			if (hyphenIndex <= 0 || hyphenIndex >= thisWordLength) {
				// Invalid hyphenation point for this word, skip it.
				continue;
			}
			
			// Look for the hyphenation point in this word.
			Hyp::HyphenationPoints::const_iterator iter = K2find(fHyphenationPoints.begin(), fHyphenationPoints.end(), hyphenIndex);
			if (iter != fHyphenationPoints.end()) {
				// Word already hyphenated at this point, skip it.
				continue;
			}
			
			if (hyphenIndex < fnMinHead || thisWordLength - hyphenIndex < fnMinTail) {
				// Skip hyphenation points outside the valid hyphen index range.
				continue;
			}
			
			// Add the hyphenation point to this word.
			Hyp::HyphenQuality hyphenQuality = pToMergeWith->GetQualityOfPoint(i);
			fHyphenationPoints.push_back(Hyp::HyphenationPoint(hyphenIndex, hyphenQuality));
			
			// Bump the inserted count.
			insertCount++;
		}
		
		// If any hyphenation points are inserted re-sort the vector.
		if (insertCount > 0) {
			std::sort(fHyphenationPoints.begin(), fHyphenationPoints.end());
		}
		
		// Trace the updated word.
		TRACEFLOW("Hyphenator HypHyphenatedWord", " sorted, updated word:\n");
		diagnostic.TraceHyphenatedWord(*this);
		
	} while(false);
	
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::Merge()-->Out\n");
}

/*
 */
void HypHyphenatedWord::ValidatePointRanges()
{
	TRACEFLOW("Hyphenator HypHyphenatedWord", "HypHyphenatedWord::ValidatePointRanges()\n");
}

// End, HypHyphenatatedWord.cpp
