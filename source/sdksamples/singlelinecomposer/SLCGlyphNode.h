//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCGlyphNode.h $
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

#ifndef __SLCGlyphNode_h__
#define __SLCGlyphNode_h__

class IComposeScanner;
class IDrawingStyle;
class IWaxLine;
class IWaxRun;
class IFontInstance;
class PMRect;


/** Base class for a glyph node, the intermediate representation of a run of 
	text used by this implementation during composition. The role of a glyph 
	node is to maintain the information required to compose and ultimately 
	generate a wax run(IWaxRun). 

	This class is specialised and completed to handle text(SLCTextGlyphNode)
	or inline graphics(SLCInlineGraphicGlyphNode) each of which have a 
	distinct wax run boss class. A full composer implementation might have 
	further sub-classes capable of creating other types of wax run(see IWaxRun).

	
  	@ingroup singlelinecomposer
	@see IWaxRun
	@see SLCTextGlyphNode
	@see SLCInlineGraphicGlyphNode
*/
class SLCGlyphNode
{
public:

	/** Each sub-class should add an enum to identify the type
		wax run it represents.
	*/
	enum GlyphNodeType
	{
		kGNTText = 0,
		kGNTInlineGraphic
	};

	/** Initialises the common state required to compose the any text.
		@param composeScanner IN for the story.
		@param drawingStyle IN for the run of text.
		@param startingIndex IN into the text model of the first character in the run.
		@param xOffset IN relative to the left edge of the wax line.
		@param glyphNodeType IN
		@postcondition check for successful construction by calling GetStatus.
	*/
	SLCGlyphNode(   IComposeScanner* composeScanner, 
					IDrawingStyle* drawingStyle, 
					TextIndex startingIndex, 
					const PMReal& xOffset,
					GlyphNodeType glyphNodeType);

	/** Get status of object (should be called after object construction).
		@return kCompSuccess means object was successfully constructed, kCompFailure otherwise.
	*/
	virtual SLComposerStatusCode GetStatus() const
	{
		return fStatus;
	};

	/** Tidies up.
	*/
	virtual ~SLCGlyphNode();

	/** Get glyph information for the given character.
		@param character for which glyph info is desired.
		@param glyphID the character maps to in the font or kInvalidGlyphID if not in the font.
		@param glyphWidth of the glyph in the style that applies to this run.
		@return kCompSuccess on success,
		kCompIncompatibleCharacter if this node can't handle the character,
		other status otherwise.
	*/
	virtual SLComposerStatusCode GetGlyph(const UTF32TextChar& character, 
										  Text::GlyphID& glyphID, 
										  PMReal& glyphWidth) = 0;

	/**	Store glyph information for this character.
		@param character 
		@param glyphID 
		@param glyphWidth 
		@return kCompSuccess on success, 
		kCompEndOfLine if character is line end or soft line,
		kCompIncompatibleCharacter if this node can't handle the character.
		kCompOutOfMemory if there's no memory available,
		other status otherwise.
	*/
	virtual SLComposerStatusCode BufferGlyph(const UTF32TextChar& character, const Text::GlyphID& glyphID, const PMReal& glyphWidth) = 0;

	/** @return the overall width of the glyphs buffered in this object.
	*/
	virtual PMReal GetWidth() const = 0;

	/** Determine a point where the text in this object can be broken.
		@return kCompSuccess if valid break point found, other status otherwise.
		@postcondition glyphs that lie after the break point are removed.
	*/
	virtual SLComposerStatusCode FindTextBreak() = 0;

	/** Get the width of trailing white space in the node.
		@return kTrue node contains only trailing white space, kFalse otherwise.
	*/
	virtual bool16 GetTrailingWhiteSpaceWidth(PMReal& width) const = 0;


	/** Adjust the width of any trailing white space in the node by
		the given scale factor.
		@param widthScaleFactor IN Scaling factor of trailing white space. 
	  		Must be between 0.0 and 1.0, non-inclusive.
		@return kTrue node contains only trailing white space, kFalse otherwise.
	*/
	virtual bool16 FitTrailingWhiteSpace(const PMReal& widthScaleFactor) = 0;

	/** Create a wax run and add it to the given line.
		@param waxLine to which run should be added.
		@return kCompSuccess on success, other status otherwise.
	*/
	virtual SLComposerStatusCode CreateWax(const IWaxLine* waxLine) const = 0;

	/** Create a wax run from the buffered glyph and style information.
		@return wax run interface pointer, the caller must release the reference.
	*/
	virtual IWaxRun* CreateWaxRun() const = 0;  

	/** @return the drawing style the glyphs are associated with.
	*/
	virtual IDrawingStyle* GetDrawingStyle() const
	{
		return fDrawingStyle;
	}

	/** @return the number of glyphs buffered in this object.
	*/
	virtual const int32& GetTextSpan() const
	{
		return fTextSpan;
	};

	/** @return the leading of the text in this object.
	*/
	inline const PMReal& GetLeading() const
	{
		return fLeading;
	}

	/** @return the ascent of the text in this object.
	*/
	inline const PMReal& GetAscent() const
	{
		return fAscent;
	}

	/** @return the cap height of the text in this object.
	*/
	inline const PMReal& GetCapHeight() const
	{
		return fCapHeight;
	}

	/** @return the x height of the text in this object (the height
		of a lowercase x in the IFontInstance of this object).
	*/
	inline const PMReal& GetXHeight() const
	{
		return fXHeight;
	}

	/** @return the index into the text model of the first character 
		in this object.
	*/
	inline const TextIndex& GetTextIndex() const
	{
		return fTextIndex;
	};    

	/** Determines if the character is a trailing white space character.
	 * 	@param character IN Text char to test.
	 * 	@return kTrue if character is a trailing white space character, kFalse otherwise.
	*/
	bool16 IsTrailingWhiteSpace(const UTF32TextChar& character) const;

	/** Dump diagnostic info to Trace.
	*/
	virtual void Dump(const char* msg) const;

	/** Set the number of glyphs in this object.
		@param count
	*/
	void SetTextSpan(int32 count)
	{
		fTextSpan = count;
	};

protected:
	/** Object status, kCompSuccess means object successfully constructed.
	*/
	SLComposerStatusCode fStatus;   

	/** Scanner for the story.
	*/
	IComposeScanner* fComposeScanner;

	/** Drawing style for the glyphs in the run.
	*/
	IDrawingStyle* fDrawingStyle;   

	/** x offset from left edge of the line to edge of first glyph.
	*/
	PMReal fXOffset;

	/** Index into the text model of the first character in the run.
	*/
	TextIndex fTextIndex;

	/* Cached metrics for the font.
	*/  
	PMReal fLeading;                    
	PMReal fAscent;
	PMReal fCapHeight;
	PMReal fXHeight;

	/** Number of glyphs in the node.
	*/
	int32 fTextSpan;    

	/**
	*/
	const GlyphNodeType fGlyphNodeType;
};

#endif // __SLCGlyphNode_h__

// End, SLCGlyphNode.h

