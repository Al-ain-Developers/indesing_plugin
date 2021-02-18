#ifndef __OpenTypeFontAccess__
#define __OpenTypeFontAccess__

class OpenTypeContext
{
public :
	OpenTypeContext(IWRStrikeBuffer* buffer, WRInt32 start, WRInt32 nStrikes, unsigned short inFlags);
	virtual ~OpenTypeContext();

	bool IsMark(WRInt32 glyphpointIndex)
	{
		return strikes->GetStrike(glyphpointIndex).GetGlyphClass() == IWRStrike::kWRGlyphClassValue_Mark;
	}
	virtual void ReplaceOneByOne(WRInt32 strikeIndex, WRGlyphID32 newGlyphIDs);	
	virtual void ReplaceOneByMany(WRInt32 strikeIndex, const WRGlyphID32* newGlyphIDs, WRInt32 numGlyphIDs);
	virtual void ReplaceRangeByOne (WRInt32 startIndex, WRInt32 limitIndex,	WRGlyphID32 newGlyphID);
	virtual void ReplaceManyByOne (const WRInt32* strikeIndices, WRInt32 indexCount, WRGlyphID32 newGlyphID);
	virtual void AdjustPlacementAndAdvance (WRInt32 strikeIndex, WRFloat xPlacementDelta, WRFloat yPlacementDelta, WRFloat xAdvanceDelta, WRFloat yAdvanceDelta);
	virtual void MergeAnchors (WRInt32 elementIndex1, WRFloat anchor1x, WRFloat anchor1y, WRInt32 elementIndex2, WRFloat anchor2x, WRFloat anchor2y, bool isCursiveAttachment, bool lastOnBaseline);
	
	virtual void DeleteOneInRanges(WRInt32 index) = 0;
	virtual void InsertAfterInRanges(WRInt32 index, WRInt32 count) = 0;
	
	WROTFeatureGSUBProc gsubProc;
	WROTFeatureGPOSProc gposProc;
	void*	clientCtx; 
	
	IWRStrikeBuffer* strikes; /** table of strikes from WRServices contains all strikes , not only those on which OT features are applies **/
	WRInt32 startStrike;/** first strike to be considered in the table **/
	WRInt32 numStrikes;/** number of strikes in the table **/
	
    unsigned short flags;
	WRError fError;
};

#endif
