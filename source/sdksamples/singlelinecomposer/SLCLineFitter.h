//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCLineFitter.h $
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

#ifndef __SLCLineFitter_h__
#define __SLCLineFitter_h__

#include "IParagraphComposer.h"
#include "SLCDiagnostics.h"

class IComposeScanner;
class SLCTileMeasure;
class IWaxLine;
class SLCTileComposer;
class SLCGlyphNodeList;

/** Positions glyphs in the line, adjusts their width if necessary and creates 
	wax runs (IWaxRun) to represent the text. The decision about where text 
	should be broken is made elsewhere, in SLCLineBreaker.

	Note that this implementation does not do paragraph alignment, justification,
	letter spacing, word spacing, kerning, fixed or zero width spaces or other 
	width adjustments. If these are required features they should be added here.

	The range of characters indicated by the line(IWaxLine) is flowed into the
	tiles given by the line. The only width adjustment implemented
	by this composer is the scaling of trailing white space to fit within available
	space in the tile.

	No tiles are obtained from the tiler in this implementation, the
	wax line gives the tiles. A wise fallback might be to attempt recompose the 
	line from scratch  if an unexpected error occurs during fitting. In which case 
	you'd want to use the tiler.

  	@ingroup singlelinecomposer
	
	@see IWaxLine
	@see IWaxRun
	@see SLCGlyphNode
	@see SLCGlyphNodeList
*/
class SLCLineFitter
{
public:
	/** Not much is done here. Set up is done each time 
	through \Ref{RebuildLineToFit}.
	*/
	SLCLineFitter(void) : fComposeScanner(nil), fWaxLine(nil), fTextIndex(0)
	{
	}

	/** Nothing is done here. Clear up is done each time 
	through \Ref{RebuildLineToFit}.
	*/
	virtual ~SLCLineFitter(void)
	{
	}

	/** @see SLCParagraphComposer
	*/
	virtual bool16 RebuildLineToFit(IParagraphComposer::RebuildHelper* helper);

private:
	/**	Fits text into the tiles in the wax line and generates
		wax runs for the line.
		@return kCompSuccess on success, other status otherwise.
		@postcondition wax runs added to fWaxLine.
		@postcondition gLSCGlyphNodeList is used and is cleared on completion.
	*/
	SLComposerStatusCode FitLine(void);

	/**	Drives SLCTileComposer to create glyph nodes (SLCGlyphNode) for 
		the range of text in each tile adjusting glyph width to fit.
		@param tile measures giving area to flow text inside.
		@return kCompSuccess on success, kCompEndOfLine if end of line, other status otherwise.
		@postcondition fSLCGlyphNodeList contains the composed text.
	*/
	SLComposerStatusCode FitTile(const SLCTileMeasure& tile);

	/** Proportionally adjust the width of trailing white space in a tile
		to fit.
		@param tile measures giving area to flow text inside.
		@param fromGlyphNodeIndex into fSLCGlyphNodeList of first node to be considered.
		@param tileComposer to obtain composition metrics from.
		@postcondition fSLCGlyphNodeList width of affected glyphs adjusted.
	*/
	void FitTrailingWhiteSpace(const SLCTileMeasure& tile, 
							   int32 fromGlyphNodeIndex, 
							   const SLCTileComposer& tileComposer);

	/**	Build wax runs for the line.
		@precondition fSLCGlyphNodeList contains nodes that represent the composed text.
		@return kCompSuccess on success, other status otherwise.
		@postcondition wax runs added to fWaxLine.
	*/
	SLComposerStatusCode CreateWax(const SLCDiagnostics & slcDiagnostics);

	/**	Scanner to use to obtain text.
	*/
	IComposeScanner* fComposeScanner;

	/** Wax line being built.
	*/
	const IWaxLine* fWaxLine;

	/**	Index into the text model of the character we have rebuilt up to.
	*/
	TextIndex fTextIndex;

	/**	Left edge of line.
	*/
	PMReal fXPosition;

	/** Used to store collection of glyphs composed on the current line.
	*/
	SLCGlyphNodeList fGlyphNodeList;
};

#endif // __SLCLineFitter_h__

// End, SLCLineFitter.h
