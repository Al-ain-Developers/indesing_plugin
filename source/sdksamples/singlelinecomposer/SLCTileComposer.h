//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCTileComposer.h $
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

#ifndef __SLCTileComposer_h__
#define __SLCTileComposer_h__

class IComposeScanner;
class IDrawingStyle;
class SLCTileMeasure;

/** Uses the scanner (IComposeScanner) to flow text into a tile generating a 
	glyph node (SLCGlyphNode) in SLCGlyphNodeList for each run. Also caches 
	additional metrics that describe the flowed text. 

	@ingroup singlelinecomposer
  	
	@see SLCGlyphNode
	@see SLCGlyphNodeList
	@see SLCTileMeasure
	@see IComposeScanner
	@see IDrawingStyle
*/
class SLCTileComposer
{
public:
	/**	Constructor prepares object to flow text.
		@param composeScanner for accessing text (ref count gets bumped). 
		@param xPosition left edge of line containing tile.
		@param startingIndex TextIndex of first character to be flowed into tile.
	*/
	SLCTileComposer(IComposeScanner* composeScanner, 
					const PMReal& xPosition, 
					const TextIndex& startingIndex) : 
		fXPosition(xPosition), 
		fTextIndex(startingIndex), 
		fTextSpan(0),
		fTextWidth(0.0),
		fFitTextSpan(0),
		fFitTextWidth(0.0)
	{
		fComposeScanner = composeScanner; fComposeScanner->AddRef();
	}

	/** Tidies up.
	*/
	virtual ~SLCTileComposer(void)
	{
		if (fComposeScanner != nil)	fComposeScanner->Release();
	}

	/**	Flow characters into the tile creating a glyph node(SLCGlyphNode)
		for each run until the tile width
		is reached or an end of line character is detected.
		If the tile width is reached and trailing white space 
		characters follow the last flowed character add the
		trailing white space into the tile (text should not be 
		broken before trailing white space).
		@param tile left edge and width of area in which to flow text(tile.fXPosition, tile.fWidth).
		@return kCompSuccess or kCompEndOfLine on success, other status otherwise.
		@postcondition SLCGlyphNodeList nodes created for each run of text.
		@postcondition the width of the characters in the tile may exceed the width
		of the tile if there is trailing white space.
		@postcondition GetTextSpan == GetFitTextSpan the characters fit within the tile.
		@postcondition GetTextSpan > GetFitTextSpan the characters don't fit within the tile.
		@postcondition GetTextWidth == GetFitTextWidth the characters fit within the tile.
		@postcondition GetTextWidth > GetFitTextWidth the characters don't fit within the tile.
	*/
	virtual SLComposerStatusCode FlowTextByTileWidth(const SLCTileMeasure& tile, SLCGlyphNodeList & glyphNodeList);

	/**	Flow the range of characters, fTextIndex:fTextIndex+tile.fTextSpan, into 
		the tile.
		@param tile left edge and width of area in which to flow text
		and number of characters to be flowed(tile.fXPosition, tile.fWidth, tile.fTextSpan).
		@return kCompSuccess or kCompEndOfLine on success, other status otherwise.
		@postcondition SLCGlyphNodeList nodes created for each run of text.
		@postcondition the width of the characters in the tile may exceed the width
		of the tile if there is trailing white space.
		@postcondition GetTextSpan == GetFitTextSpan the characters fit within the tile.
		@postcondition GetTextSpan > GetFitTextSpan the characters don't fit within the tile.
		@postcondition GetTextWidth == GetFitTextWidth the characters fit within the tile.
		@postcondition GetTextWidth > GetFitTextWidth the characters don't fit within the tile.
	*/
	virtual SLComposerStatusCode FlowTextByTileTextSpan(const SLCTileMeasure& tile, SLCGlyphNodeList & glyphNodeList);

	/** @return the total number of characters flowed into the tile.
	*/
	inline int32 GetTextSpan(void) const
	{
		return fTextSpan;
	}

	/** @return the total width of characters flowed into the tile.
	*/
	inline PMReal GetTextWidth(void) const
	{
		return fTextWidth;
	}

	/** @return the number of characters that fit within the tile.
				Note this can include trailing white space that fits.
	*/
	inline int32 GetFitTextSpan(void) const
	{
		return fFitTextSpan;
	}

	/** @return the width of the characters that fit within the tile.
				Note this can include the width of trailing white
				space that fits.
	*/
	inline PMReal GetFitTextWidth(void) const
	{
		return fFitTextWidth;
	}

private:
	/** Scanner to access text. 
	*/
	IComposeScanner* fComposeScanner;

	/** Position of left edge of line containing tile. 
	*/
	const PMReal fXPosition;

	/** TextIndex of first character in the tile. 
	*/
	const TextIndex fTextIndex;

	/** @see GetTextSpan 
	*/
	int32 fTextSpan;

	/** @see GetTextWidth 
	*/
	PMReal fTextWidth;

	/** @see GetFitTextSpan 
	*/
	int32 fFitTextSpan;

	/** @see GetFitTextWidth 
	*/
	PMReal fFitTextWidth;
};

#endif // __SLCTileComposer_h__

// End, SLCTileComposer.h

