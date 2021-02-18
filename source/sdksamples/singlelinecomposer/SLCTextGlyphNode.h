//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCTextGlyphNode.h $
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

#ifndef __SLCTextGlyphNode_h__
#define __SLCTextGlyphNode_h__

class IComposeScanner;
class IDrawingStyle;
class IWaxLine;
class IWaxRun;
class IFontInstance;

#include "SLCGlyphNode.h"

/** Represents a run of styled text and generates its wax run object(kWaxTextRunBoss). 

	This class uses the style and font 
	APIs (IDrawingStyle, IPMFont and IFontInstance) to discover essential 
	metrics such as leading, ascent etc. It maps a character code into its 
	corresponding GlyphID and stores it in a buffer along with its width.
	It understands how to locate points where Roman text can be broken
	across lines or tile. 
 
	@ingroup singlelinecomposer
	 
*/
class SLCTextGlyphNode : public SLCGlyphNode
{
public:
	/** Caches the font and font metrics for the text.
	*/
	SLCTextGlyphNode(IComposeScanner* composeScanner, 
					 IDrawingStyle* drawingStyle, 
					 TextIndex startingIndex, 
					 const PMReal& xOffset);

	/** Releases references and memory.
	*/
	virtual ~SLCTextGlyphNode(void);

	/** See SLCGlyphNode.
	*/
	virtual SLComposerStatusCode GetGlyph(const UTF32TextChar& character, Text::GlyphID& glyphID, PMReal& glyphWidth);

	/** See SLCGlyphNode.
	*/
	virtual SLComposerStatusCode BufferGlyph(const UTF32TextChar& character, const Text::GlyphID& glyphID, const PMReal& glyphWidth);

	/**  See SLCGlyphNode.
	*/
	virtual PMReal GetWidth(void) const;

	/**	 See SLCGlyphNode.
	*/
	virtual SLComposerStatusCode FindTextBreak(void);

	/** See SLCGlyphNode.
	*/
	virtual bool16 GetTrailingWhiteSpaceWidth(PMReal& width) const;

	/**  See SLCGlyphNode.
	*/
	virtual bool16 FitTrailingWhiteSpace(const PMReal& widthScaleFactor);

	/** See SLCGlyphNode.
	*/
	virtual SLComposerStatusCode CreateWax(const IWaxLine* waxLine) const;

	/** Creates a kWaxTextRunBoss object (see SLCGlyphNode for other info).
	*/
	virtual IWaxRun* CreateWaxRun(void) const;  

protected:
	/** @return the point size of the text in this object.
	*/
	inline const PMReal& GetPointSize(void) const
	{
		return fPointSize;
	}

	/** Check if the dynamic buffers in this object can take
		another glyph and grow them if necessary.
		@return kCompSuccess on success, kCompOutOfMemory otherwise.
	*/
	SLComposerStatusCode GrowBuffers(void);

	/** Calculate the width rounding error introduced by fixed-point math 
		for an em-dash character in the current IFontInstance.

		This rounding error is used to compensate for the fact 
		that fixed-point math in AGM is only fully accurate to the 4th 
		decimal place.

		The internal units used by composition is Points. The measure
		used in Roman fonts is points so rounding error is not significant
		for Roman composition. However other measures such as Japanese Q 
		units need more accuracy to round trip to the internal measure.

		In AGM a fixed-point number is 32 bits long. The low-order 
		16 bits contain the fractional part of the number and the 
		high-order 16 bits contain the integer part of the number.
		Note 1/32767 ~ 0.0000305. 

		The adjustment calculated here for an em-dash is
		applied proportionally to each fixed-point glyph width.
		@postcondition GetFixedToPMRealEmDashWidthRoundingError can be called.
		@see DetermineGlyphWidth
	*/
	void CalculateFixedToPMRealEmDashWidthRoundingError(void);

	/** @return the width rounding error for an em-dash character.
	*/
	inline const PMReal& GetFixedToPMRealEmDashWidthRoundingError(void) const
	{
		return fFixedToPMRealEmDashWidthRoundingError;
	}

	/** @return the width of an em-dash character in fixed point.
	*/
	inline const PMReal& GetEmDashWidth(void) const
	{
		return fEmDashWidth;
	}

	/** Determine the GlyphID for a given character from the
		IFontInstance for this run. Handles kTextChar_SpecialGlyph
		character used to describe glyphs that have no corresponding 
		Unicode character code. Such characters have text attribute
		kTextAttrSpecialGlyphBoss applied which is used to map in the
		desired GlyphID from the font. The mapping is obtained
		via a method on IDrawingStyle.
		@param character
		@return GlyphID associated with the given character.
	*/
	virtual Text::GlyphID DetermineGlyphID(const UTF32TextChar& character) const;

	/** Determine the width of the given glyph.
		@param glyphID
		@return width in points.
	*/
	virtual PMReal DetermineGlyphWidth(const Text::GlyphID& glyphID) const; 

	/** @return a pointer to the array of GlyphID's buffered in this object.
	*/
	virtual K2Vector<Text::GlyphID> GetGlyphIDs(void)
	{
		return fGlyphIDs;
	};

	/** @return a pointer to the array of glyph widths that
		correspond to the GlyphID's returned by \Ref{GetGlyphIDs}.
	*/
	virtual K2Vector<PMReal> GetGlyphWidths(void)
	{
		return fGlyphWidths;
	};  

	/** Applies rules to find where Roman text can be broken.
		@return kCompSuccess if the text in this buffer can be broken.
	*/
	virtual SLComposerStatusCode ApplyTextBreakRules(void);

	/** Get the character code corresponding to the glyph at the given index 
		in this object.
		@param glyphNodeIndex 
		@param character at the given index
		@return kCompSuccess on success, other status otherwise.
	*/
	virtual SLComposerStatusCode GetCharacter(int32 glyphNodeIndex, UTF32TextChar& character) const;

	/** Remove the last glyph in this object from the buffer.
		@param lastCharacter OUT the character associated with what
		is now the last glyph in this object.
		@return kCompSuccess on success, other status otherwide.
	*/
	virtual SLComposerStatusCode PushOut(UTF32TextChar& lastCharacter);

private:    

	/* Font instance for the glyphs that is used to get GlyphIDs and metrics.
	*/
	IFontInstance* fFontInstance;       

	/* Current dynamic buffer size.
	*/
	int32 fBufferSize;

	/* Buffers storing GlyphIDs and corresponding widths (allocated on the heap).
	*/
#if 0
	Text::GlyphID* fGlyphIDs;
	PMReal* fGlyphWidths;
	#define USING_PTRS_FOR_MEMBERS
#else
	K2Vector<Text::GlyphID> fGlyphIDs;           
	K2Vector<PMReal> fGlyphWidths;               
#endif
	
	/* Cached metrics for the font.
	*/
	PMReal fPointSize;      

	/* Adjustment to compensate for AGM fixed-point math rounding error.
	*/
	PMReal fFixedToPMRealEmDashWidthRoundingError;

	/* Width of an em-dash in AGM fixed-point.
	*/
	PMReal fEmDashWidth;                     
};

#endif // __SLCTextGlyphNode_h__

// End, SLCTextGlyphNode.h

