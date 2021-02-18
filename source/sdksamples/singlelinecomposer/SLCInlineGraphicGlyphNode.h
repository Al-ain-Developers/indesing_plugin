//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCInlineGraphicGlyphNode.h $
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

#ifndef __SLCInlineGraphicGlyphNode_h__
#define __SLCInlineGraphicGlyphNode_h__

class IComposeScanner;
class IDrawingStyle;
class IWaxLine;
class IWaxRun;
class IFontInstance;
class PMRect;

#include "SLCGlyphNode.h"

/** Represents an inline and generates its wax run object (kWaxILGRunBoss).
 * 
 * 	This object can only represent a single inline. If there are several consecutive
 * 	inline characters (kTextChar_ObjectReplacementCharacter) in the text a 	
 * 	glyph node is required for each.
 * 	@ingroup singlelinecomposer
 * 	
*/
class SLCInlineGraphicGlyphNode : public SLCGlyphNode
{
public:
	/**	Constructor.
		@param composeScanner 
		@param drawingStyle 
		@param startingIndex 
		@param xOffset
	*/
	SLCInlineGraphicGlyphNode(IComposeScanner* composeScanner, 
							  IDrawingStyle* drawingStyle, 
							  TextIndex startingIndex, 
							  const PMReal& xOffset);

	/** Releases references and memory.
	*/
	virtual ~SLCInlineGraphicGlyphNode(void);

	/** See SLCGlyphNode. 
		@param character must be kTextChar_ObjectReplacementCharacter
		@param glyphID returned as kInvalidGlyphID.
		@param glyphWidth width of the inline.
	*/
	virtual SLComposerStatusCode GetGlyph(const UTF32TextChar& character, 
										  Text::GlyphID& glyphID, 
										  PMReal& glyphWidth);

	/** See SLCGlyphNode. Note this method can only be called once
		only one inline can be stored per instance of this object.
	*/
	virtual SLComposerStatusCode BufferGlyph(const UTF32TextChar& character, 
											 const Text::GlyphID& glyphID, 
											 const PMReal& glyphWidth);

	/** See SLCGlyphNode.
	*/
	virtual PMReal GetWidth(void) const
	{
		return fInlineBoundingBox.Width();
	}

	/**	See SLCGlyphNode.
		@return kCompSuccess since lines can always break after an inline.
	*/
	virtual SLComposerStatusCode FindTextBreak(void)
	{
		return kCompSuccess;
	}

	/** See SLCGlyphNode.
		@return kFalse inline glyph nodes never store trailing white space.
	*/
	virtual bool16 GetTrailingWhiteSpaceWidth(PMReal& width) const
	{
		width = PMReal(0.0); return kFalse;
	}

	/** See SLCGlyphNode.
		@return kFalse inline glyph nodes never store trailing white space.
	*/
	virtual bool16 FitTrailingWhiteSpace(const PMReal& widthScaleFactor)
	{
		return kFalse;
	}

	/** See SLCGlyphNode.
	*/
	virtual SLComposerStatusCode CreateWax(const IWaxLine* waxLine) const;

	/** Adds a kWaxILGRunBoss object to the line.
	*/
	virtual IWaxRun* CreateWaxRun(void) const;

private:
	/** Get the owned item for the inline, save off a UIDRef to it
		find its bounds and return the width.
		@param glyphWidth width of the inline.
		@return kCompSuccess on success, other status otherwise.
	*/
	SLComposerStatusCode GetInlineGraphic(PMReal& glyphWidth);

	/**	Set the various height metrics (leading, ascent etc.) to
		be the given height so that these metrics reflect the
		height of the inline.
	*/
	void SetHeight(const PMReal& height);

	/** Reference to the kInlineBoss object.
	*/
	UIDRef fInlineUIDRef;

	/** Bounds of the inline.
	*/
	PMRect fInlineBoundingBox;
};

#endif // __SLCInlineGraphicGlyphNode_h__

// End, SLCInlineGraphicGlyphNode.h

