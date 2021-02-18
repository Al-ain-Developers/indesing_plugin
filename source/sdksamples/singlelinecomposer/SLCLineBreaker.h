//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCLineBreaker.h $
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

#ifndef __SLCLineBreaker_h__
#define __SLCLineBreaker_h__

#include "IParagraphComposer.h"

class IComposeScanner;
class IWaxLine;
class IDrawingStyle;
class SLCTileMeasure;
class SLCTileManager;

/** Positions the line, decides where text should be broken if necessary, and
	creates a wax line(IWaxLine) to represent the text. Positioning and fitting 
	of the glyphs that represent the characters in the line  and the creation 
	of wax runs(IWaxRun) is the role of SLCLineFitter.

	In essence composition proceeds by flowing characters into the line 
	until the width of the characters reaches the maximum width of the line or an end
	of line character is encountered. If the maximum width of the line is reached a 
	character where the line can be broken is sought.

	In reality a couple of things complicate this overview.
	
	Firstly text wrap can affect where in the line text can flow. Frames with
	text wrap settings can intrude into the line creating areas where text should
	not flow. To account for this the composer obtains tiles for the line 
	from a tiler(IParagraphComposer::Tiler). The tiler takes care of the effect of text wrap and 
	irregular frame shapes. Interaction with the tiler is delegated to 
	SLCTileManager. Characters are flowed into each tile within the line.

	Secondly care must be taken not to break text before trailing white space 
	characters. These must be included in the line and may cause the tile width
	to be exceeded initially until they are scaled to fit the width of the tile.

	Flowing of text into tiles is delegated to SLCTileComposer which represents 
	composed text as glyph nodes in SLCGlyphNodeList.

	As output a wax line(IWaxLine) is created and added to the wax strand(IWaxStrand). 
	Note that the wax runs are added to the line by SLCLineFitter which gets called 
	as a result of SLCLineBreaker calling IWaxStrand to apply the composed wax line.

	Note that this implementation does not perform hyphenation. But if hyphenation
	were to be supported it would be added here since it affects where the text
	can be broken across tiles and lines.
	
  	@ingroup singlelinecomposer
	
    @see SLCParagraphComposer
	@see SLCTileManager
	@see SLCTileComposer
	@see SLCGlyphNode
	@see SLCGlyphNodeList
	@see IComposeScanner
	@see IDrawingStyle
	@see IWaxStrand
	@see IWaxLine
*/
class SLCLineBreaker
{
public:
	/** Nothing much is done here. Initialisation is done each time 
		through Recompose.
	*/
	SLCLineBreaker(void) : fComposeScanner(nil), fFirstLine(kFalse), fTextIndex(0), fGridAlignmentMetric(Text::kGANone)
	{
	}

	/** Nothing is done here. Clean up is done each time through Recompose.
	*/
	virtual ~SLCLineBreaker(void)
	{
	}

	/** See SLCParagraphComposer.
	*/
	virtual bool16 Recompose(IParagraphComposer::RecomposeHelper* helper);

private:
	/**	Prepare to compose a line.
	*/
	SLComposerStatusCode Initialise(const IParagraphComposer::RecomposeHelper* helper, ParcelKey parcelKey);

	/**	Tidy up after composing a line.
	*/
	void Finish(void);

	/**	Baseline grid and no alignment are supported.
		@param drawingStyle for the text.
		@return kGABaseline baseline grid alignment, kGANone no alignment.
	*/
	Text::GridAlignmentMetric GetGridAlignmentMetric(IDrawingStyle* drawingStyle);

	/**	Drive FillLine to compose a line. If deeper tiles
		are required (i.e. the height of the text is greater than the
		height of the tile) get them and recompose. If no wax can be
		generated for this line, lead to the next
		line and get tiles until we create some wax. When the
		story is overset (the text cannot be completely displayed) 
		underlying methods will ensure wax is generated.
		@return line with position, height, tiles and the range of text in each (no wax runs added).
	*/
	virtual IWaxLine* ComposeLine(const TextIndex& startingIndex);

	/**	Ask SLCTileManager to make tile measures (SLCTileMeasures)
		for the line.
		kCompSuccess on success, other status otherwise.
	*/
	virtual SLComposerStatusCode GetTiles(void);

	/** Drive FillTile to flow text into each tile.
		@return kCompSuccess or kCompEndOfLine on success, 
				kCompChangeOfHeight if tiles aren't deep enough for the text,
				kCompWillNotFit can't fit any text in the tiles,
				other status otherwise.
		@postcondition return>=kCompSuccess fSLCGlyphNodeList contains glyph nodes for the line.
	*/
	virtual SLComposerStatusCode FillLine(void);

	/**	Flow characters into a tile using SLCTileComposer.
		If the width of the characters in the tile exceeds 
		the width of the tile itself determine where the 
		text can be broken.
		@param tile	IN fXPosition contains position of left edge of tile,
					IN fWidth contains width of tile.
					OUT fTextSpan number of characters in the tile.
		@return kCompSuccess or kCompEndOfLine on success, 
				kCompChangeOfHeight if tiles aren't deep enough for the text,
				other status otherwise.
		@postcondition return>=kCompSuccess glyph nodes for the tile appended to fSLCGlyphNodeList.
	*/
	virtual SLComposerStatusCode FillTile(SLCTileMeasure& tile);

	/**	If the story is not overset this method looks for the 
		point at which the text can be broken if necessary
		and updates the metrics that are being tracked for the line. 
		The method checks the metrics of the tallest text in the
		line against the height of the tiles. If the text is higher
		the new deeper tiles must be obtained and the text recomposed.

		If the story is overset all the text 
		that has been composed is taken without any attempt to identify
		a break point The glyphs will not be displayed since they don't 
		fit inside the frames that display the text.

		@precondition fSLCGlyphNodeList contains glyph nodes to be processed.
		@param fromGlyphNodeIndex of first fSLCGlyphNodeList member to be processed.
		@return kCompSuccess on success, 
				kCompEndOfLine on end of line,
				kCompChangeOfHeight if tiles aren't deep enough for the text,
				other status otherwise.
		@postcondition return>=kCompSuccess fSLCGlyphNodeList contains glyph nodes for the tile.
	*/
	virtual SLComposerStatusCode ProcessGlyphNodes(int32 fromGlyphNodeIndex);

	/**	Looks for the point at which the text can be broken. Searching back from
		the end of the list of glyph nodes, members that contain text that has no
		break point are discarded.
		@precondition fSLCGlyphNodeList contains glyph nodes to be analysed.
		@param fromGlyphNodeIndex of first fSLCGlyphNodeList member to be processed.
		kCompSuccess on success, other status otherwise.
		@return kCompSuccess if break found, kCompFailure otherwise.
		@postcondition return>=kCompSuccess fSLCGlyphNodeList contains glyphs for the tile
						for text up to and including the break point.
	*/
	virtual SLComposerStatusCode FindTextBreak(int32 fromGlyphNodeIndex);

	/**	Note this method does not add wax runs to the line. It just 
		populates the line with properties such as position
		and height based on tile measures, line metrics and other data.
		@return the wax line
	*/
	IWaxLine* CreateWaxLine(void);

	/**	Update metrics being tracked for the line. 
		@param glyphNode to check/update tracked metrics.
		@postcondition fLineMetrics maintained as the maximum metric value on the line is stored.
	*/  
	virtual void UpdateLineHeight(const SLCGlyphNode* glyphNode);

	/** @return kTrue if overset text is being composed, kFalse otherwise.
	*/
	bool16 IsStoryOverset(void) const;

	/** Scanner for story being composed.
	*/
	IComposeScanner* fComposeScanner;

	/** kTrue if the first line of a paragraph is being composed, kFalse otherwise.
	*/
	bool16 fFirstLine;

	/** Metrics tracked during line composition. The maximum values of these
		metrics encountered on the line are maintained during composition so that
		tiles of the correct depth are used.
	*/
	SLCLineMetrics fLineMetrics;

	/** Index into the text model of the character we have composed up to.
	*/
	TextIndex fTextIndex;

	/**	During composition this is the position ofthe top of area text
		is flowing into. Once composition of the line is complete it's 
		the baseline of the text.
	*/
	PMReal fYPosition;

	/** Left edge of line.
	*/          
	PMReal fXPosition;

	/** See GetGridAlignmentMetric.
	*/
	Text::GridAlignmentMetric fGridAlignmentMetric; 

	/** Tile Manager for this SLCLineBreaker instance.
	*/
	SLCTileManager fSLCTileManager;

	/** The collection of composed glyphs.
	*/
	SLCGlyphNodeList fGlyphNodeList;

};

#endif // __SLCLineBreaker_h__

// End, SLCLineBreaker.h

