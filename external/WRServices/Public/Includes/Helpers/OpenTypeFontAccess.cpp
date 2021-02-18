#ifndef __OpenTypeFontAccess_cpp__
#define __OpenTypeFontAccess_cpp__


OpenTypeContext::OpenTypeContext(IWRStrikeBuffer* buffer, WRInt32 start, WRInt32 nStrikes,unsigned short inFlags) : 
	gsubProc(NULL), gposProc(NULL), clientCtx(NULL),
	strikes(buffer), startStrike(start), numStrikes(nStrikes), flags(inFlags)
{
}

OpenTypeContext::~OpenTypeContext()
{
}


void OpenTypeContext::ReplaceOneByMany(WRInt32 strikeIndex, const WRGlyphID32* newGlyphIDs, WRInt32 numGlyphIDs)
{
	WRInt32 added = numGlyphIDs - 1;
	strikes->ReplaceOneByMany(startStrike + strikeIndex, newGlyphIDs, numGlyphIDs);
	
	InsertAfterInRanges((WRInt32)strikeIndex,(WRInt32)added);

	numStrikes += added;

	if (gsubProc)
		(*(gsubProc))(clientCtx, (WRInt32) (startStrike + strikeIndex), (WRInt32) kWROTMultiSubstitute, (WRInt32) numGlyphIDs, 0);
}

void OpenTypeContext::ReplaceOneByOne (WRInt32 strikeIndex, WRGlyphID32 newGlyphID)
{
	strikes->ReplaceOneByOne(startStrike + strikeIndex, newGlyphID);
	if (gsubProc)
		(*(gsubProc))(clientCtx, (WRInt32) (strikeIndex + startStrike), (WRInt32) kWROTSingleSubstitute, (WRInt32) 1, 0); 
}

void OpenTypeContext::ReplaceRangeByOne (WRInt32 startIndex, WRInt32 limitIndex,	WRGlyphID32 newGlyphID)
{
	WRInt32 idx=0;
	WRInt32 termDiacCount = 0;
	WRInt32 deleted = limitIndex - startIndex - 1;
			
	strikes->ReplaceRangeByOne(startStrike + startIndex, newGlyphID, limitIndex - startIndex, termDiacCount);
	
	// Update ranges
	WRInt32 nDeletedIndex;
	//WRInt32 nStartIndex = static_cast<WRInt32>(startIndex);
	for (nDeletedIndex = static_cast<WRInt32>(limitIndex-1) ; nDeletedIndex > static_cast<WRInt32>(startIndex) ; nDeletedIndex--)
		DeleteOneInRanges(nDeletedIndex);
		
	//Update strike count
	numStrikes -= deleted;
	
	if (gsubProc)
	{
		(*(gsubProc))(clientCtx, (WRInt32) (startIndex + startStrike), (WRInt32) kWROTLigature, (WRInt32) (limitIndex - startIndex),(WRInt32) termDiacCount);
		for (idx = startIndex+1 ; idx < limitIndex - 1 ; idx++)
			(*(gsubProc))(clientCtx, (WRInt32) (idx + startStrike), (WRInt32) kWROTDeleted, (WRInt32) 0, (WRInt32) 0);
		
		(*(gsubProc))(clientCtx, (WRInt32) (limitIndex - 1 + startStrike), (WRInt32) kWROTDeleted, (WRInt32) (limitIndex - startIndex),(WRInt32) termDiacCount);
	}
}

void OpenTypeContext::ReplaceManyByOne (const WRInt32* strikeIndices, WRInt32 indexCount, WRGlyphID32 newGlyphID)
{
	WRInt32 termDiacCount = 0;
	strikes->ReplaceManyByOne(startStrike, strikeIndices, newGlyphID, indexCount, termDiacCount);

	// Update first glyph to the new value
	WRInt32 startIndex = strikeIndices[0];
	if (gsubProc)
		(*(gsubProc))(clientCtx, (WRInt32) (startIndex + startStrike), (WRInt32) kWROTLigature, (WRInt32) indexCount,(WRInt32) termDiacCount);

	// Remove other glyphs
	WRInt32 index = 0;
	for (index = 1 ; index < indexCount ; index++)
	{
		if (gsubProc)
			(*(gsubProc))(clientCtx, 
							static_cast<WRInt32>(strikeIndices[index] + startStrike), 
							static_cast<WRInt32>(kWROTDeleted), 
							static_cast<WRInt32>((index == indexCount - 1) ? indexCount : 0),(WRInt32) termDiacCount);
	}

	for (index = indexCount-1 ; index > 0 ; index--)
		DeleteOneInRanges((WRInt32)(strikeIndices[index]));

	//Update strike count
	numStrikes -= indexCount -1;

}

void OpenTypeContext::AdjustPlacementAndAdvance (WRInt32 strikeIndex, WRFloat xPlacementDelta, WRFloat yPlacementDelta, WRFloat xAdvanceDelta, WRFloat yAdvanceDelta)
{
	// pass either startStrike+numStrikes if propagation is handled by the client or strikes->Size() 
	strikes->AdjustPlacementAndAdvance(strikeIndex + startStrike, strikes->Size(), xPlacementDelta, yPlacementDelta, xAdvanceDelta, yAdvanceDelta, (flags & kWRRtl) != 0, IsMark(startStrike + strikeIndex));
}

void OpenTypeContext::MergeAnchors (WRInt32 elementIndex1, WRFloat anchor1x, WRFloat anchor1y, WRInt32 elementIndex2, WRFloat anchor2x, WRFloat anchor2y, bool isCursiveAttachment, bool lastOnBaseline)
{
	strikes->MergeAnchors(elementIndex1 + startStrike, anchor1x, anchor1y, IsMark(startStrike + elementIndex1), elementIndex2 + startStrike, anchor2x, anchor2y, isCursiveAttachment != 0, lastOnBaseline != 0);
}

#endif
