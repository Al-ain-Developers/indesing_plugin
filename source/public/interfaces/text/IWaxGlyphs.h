//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxGlyphs.h $
//  
//  Owner: ?
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

#pragma once
#ifndef __IWaxGlyphs__
#define __IWaxGlyphs__

#include "IPMUnknown.h"
#include "CTextEnum.h"
#include "TextID.h"
#include "PMRect.h"
#include "IWaxRun.h"

class PMMatrix;
class PMRealGlyphPoint;

/** Interface for working with glyphs that will be drawn onto the page.

	Text is converted into a set of glyphIDs and data specifying how and where to draw that glyph. Within this object, glyphs are
	placed relative to the start of this object (which is also the start of the corresponding waxRun).  Multiple glyphs can represent
	one char of text, or vice versa. Glyphs are placed out in increasing x-positions, but have various adjustments made to them to
	correctly place them on the line (i.e. shifting or matrix-transformations).

	GlyphIDs are accompanied by a width and an optional x-Offset value. The latter is difference between the drawing position
		and selection position on the glyph and is typically not needed for roman based text. Also, a matrix can accompany the glyphs,
		but again, isn't typically used for roman text.  For convenience, a single matrix can be specified that works on each glyph
		in turn.

	@note For InDesign 3.0, IWaxGlyphs has been changed to support NON one-to-one mapping between chars and glyphs.
	This means, for instance, that a tab with leaders is supported (where 1 tab char results in N glyphs drawn).

	AS A CONSEQUENCE, ALL USERS OF WAX ARE REQUIRED TO MAP BETWEEN TEXT INDICES AND GLYPH INDICES and vice versa.
	New methods have been added to access the char equivalent information (e.g. GetCharCount or GetCharWidthAt)
	as well as methods to map between chars and glyphs.

	@note NOTEs on glyph widths and glyph positions:
	<pre>
	You have two choices for getting width or position related values:
		1) get the widths for glyph placement or
		2) get the widths for selecting.
	</pre>
	This is due to leading space (Aki) added to each glyph for J text. (Thus for roman text, there is no difference).
	Selection includes the leading Aki for that glyph in that glyph's width, whereas drawing does not.  Thus the selection of a glyph is from
		the beginning of the leading Aki through the end of the trailing Aki.<br>
	Glyph Placement includes the leading Aki for a glyph in the PREVIOUS glyph's width (lumped together as trailing Aki).
		This makes the width of a particular glyph look wider than it actually is, but the GLYPH'S X-POSITION IS
		UNCHANGED (the ink appears where it should).  Thus when we draw the glyph, the glyphs are placed at their correct
		x-position and the width from one glyph to the other is correct.

	<pre>
	Since the draw code is the special case, most of these methods will return the selection width/position.
	--------------------------------------------------------------------------------------------------------------------
	Only the QueryDrawWidthsArray() and GetInitialGlyphOffset() methods (and the methods for adding or
	replacing glyphs) will return/deal-with the glyph-placement-oriented widths/positions.
	IN SHORT - FOR MOST USES, THIS INTERFACE DEALS WITH THE SELECTION WIDTHS.
	--------------------------------------------------------------------------------------------------------------------
	</pre>

	When adding glyphs, the glyphOffset is the offset from the beginning of the preAki to the glyph.
	This is the position at which the glyph should draw.
	Again for roman text, glyphOffset is always zero and so there is no difference.

	@ingroup text_wax
*/
class IWaxGlyphs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXGLYPHS };

	/**
		Return the number of glyphs in this set.

		@note there is not a 1-1 mapping between chars and glyphs. You must convert glyph indices to char indices
				(and vice versa) using the utility methods Map{Chars,Glyphs}To{Glyphs,Chars}
	 */
	virtual int32 GetGlyphCount() const = 0;
	/**
		Return the number of chars in this set.

		@note there is not a 1-1 mapping between chars and glyphs. You must convert glyph indices to char indices
				(and vice versa) using the utility methods Map{Chars,Glyphs}To{Glyphs,Chars}
	 */
	virtual int32 GetCharCount() const = 0;

	/**
		Return whether or not there is a mapping.  In other words, if !IsMapped(), then the ratio is 1-1.

		@note do not use this unless the wax is fully built!  (basically, it's ok except for the composer).
	 */
	virtual bool16 IsMapped() const = 0;

	/** Return either the number of chars or glyph represented by this wax.
		If using World Ready composer the span is number of glyphs. Otherwise
		it is the number of characters.

		@note GetWaxSpan <= GetGlyphCount -- always
	 */
	virtual int32 GetWaxSpan() const = 0;

	/**
		Return the width of this set of glyphs.

		The returned width is relative to the waxRun (i.e. GetXPosition() is the origin)

		@param ignoreAllTrailing - if kTrue the width will not include the width of trailing white space or non selectable glyphs.
	 */
	virtual PMReal GetWidth(bool16 ignoreAllTrailing = kFalse) const = 0;
	/**
		Get the width of the characters that this object represents (e.g. the sum of the widths of the glyphs).

		Typically only GetWidth should be used.  GetCharWidth is used mainly to build the wax.
	 */
	virtual PMReal GetCharWidth() const = 0;

	/**
		Get the (Embox) height of this set of glyphs.

		The returned height is relative to the waxRun (i.e. GetYPosition() is the origin)
	 */
	virtual PMReal GetHeight() const = 0;
	/**
		Set the (Embox) height of this set of glyphs.
	 */
	virtual void SetHeight(const PMReal& height) = 0;

	// ***************************************************************************
	// Conversion methods.

	/**
		Return which glyph is at the given coordinate.

		@return the index and, as the fractional part, the distance within the glyph as a percentage.
	 */
	virtual PMReal GetGlyphIndexFor(PMReal position) const = 0;

	/**
		Map char index (or range) to glyph index (or range).
	 */
	virtual void MapCharsToGlyphs(int32 offset, int32 length, int32* pRangeStart, int32* pRangeLength) const = 0;

	/**
		Map glyph index (or range) to char index (or range).
	 */
	virtual void MapGlyphsToChars(int32 rangeStart, int32 rangeLength, int32* pOffset, int32* pLength) const = 0;

	// ***************************************************************************
	// Access to particular glyph data.

	/**
		Return the glyphID for the given glyph index.
	 */
	virtual Text::GlyphID GetGlyphAt(int32 glyphIndex) const = 0;

	/**
		Return the width of the given glyph index.
	 */
	virtual PMReal GetWidthAt(int32 glyphIndex) const = 0;
	/**
		Return the distance from the start of this set THROUGH the given glyph index.
	 */
	virtual PMReal GetEscapementAt(int32 glyphIndex) const = 0;

	/**
		Return the width of the (set of) glyphs corresponding to the given char index.
	 */
	virtual PMReal GetCharWidthAt(int32 charIndex) const = 0;
	/**
		Return the distance from the start of this set THROUGH the end of the set of glyphs for the given char index.
	 */
	virtual PMReal GetCharEscapementAt(int32 charIndex) const = 0;

	// ***************************************************************************
	// Access to various set data.

	/**
		Return a const pointer to the internal array of glyphIDs.

		@note This method is intended only for low level drawing code - you very very likely shouldn't be using PeekGlyphArray.
	 */
	virtual const Text::GlyphID* PeekGlyphArray() const = 0;
	/**
		Return a const pointer to the internal array of glyph widths.

		@note This method is intended only for low level drawing code - you very very likely shouldn't be using PeekWidthsArray.
	 */
	virtual const float* PeekWidthsArray() const = 0;

	// ***************************************************************************

	/**
		Return an array representing the widths of the glyphs as they will ultimately be drawn.

		Caller must deallocate the returned array, if non-nil.

		@note This method is intended only for low level drawing code - you very very likely shouldn't be using QueryDrawWidthsArray.
	 */
	virtual float* QueryDrawWidthsArray(float& initialGlyphXOffset) const = 0;
	/**
		Returns the glyph's X offset: This is the difference between the drawing position and selection position on the glyph.

		The glyphOffset is the offset from the beginning of the preAki to the glyph.
	 */
	virtual float GetXOffsetAt(int32 glyphIndex) const = 0;

	// ***************************************************************************
	// Add or replace the set of glyphs

	/**
		Add a single glyph, width and xOffset to this object.
	 */
	virtual void AddGlyph(Text::GlyphID glyph, float width, float glyphXOffset = 0) = 0;
	/**
		Replace the glyph that will be drawn by another.

		@note This only replaces the glyph, it does not change the width or placement of that glyph.
	 */
	virtual void ReplaceGlyphAt(int32 glyphIndex, Text::GlyphID glyph) = 0;

	/**
		Add this set of glyphs, widths and xOffsets to this object.
	 */
	virtual void AddGlyphs(const Text::GlyphID* glyphs, const float* widths, int32 count, const float* glyphXOffsets = nil) = 0;

	/**
		Add this set of glyphs, widths and xOffsets to this object.
	 */
	virtual void AddGlyphs(const PMRealGlyphPoint *points, int32 count, const float* glyphXOffsets = nil) = 0;

	/**
		This is essentially the same as AddGlyph - it adds another char and its width (e.g. a tab and its end point) to the run.
		This width is returned via the GetCharWidth() method.
	 */
	virtual void AddMappingWidth(const PMReal& width) = 0;

	// ***************************************************************************
	// These provide a mapping between this char (& width) and the glyphs that will fill it (e.g. associates the leader glyphs to the tab char).

	/**
		These provide a mapping between this char (& width) and the glyphs that will fill it (e.g. associates the leader glyphs to the tab char).
	 */
	virtual void AddMappingRange(int32 offset, int32 rangeStart, int32 rangeLength) = 0;

	/**
		Adjust the particular glyph's width (and optionally its xOffset).
	 */
	virtual void AdjustWidthAt(int32 glyphIndex, float deltaWidth, float glyphOffset = 0) = 0;

	// ***************************************************************************
	// Transform related methods.

	/**
		Return the stroke bounding box for this object.

		@param pMatrix default: nil. Thematrix will be used to transform the result before returning.
			This can be used to, for instance, to convert to pasteboard coordinates.
			i.e. if you want a PasteBoardBBox, pass in an InnerToPasteboard Matrix
		If the matrix pointer is nil, no transformations are done. BBox returned is in inner coordinates
	 */
	virtual PMRect GetStrokeBoundingBox(const PMMatrix* pMatrix = nil) const = 0;

	/**
		Returns a modified matrix and penCorrection for the given glyph.

		<pre>
		UPDATEs the given matrix (and point) to represent the requested glyph in this run.
		This matrix is the sum of all transformations of the glyph (it incorporates all matrices and the position of the glyph in the run),
		Returns the left bottom corner of the glyph (waxGlyphs relative).
		Return value is kTrue if the glyph was found.
		This matrix should be concat'ed onto scaled font matrix for all glyphs in the array.
		</pre>
	 */
	virtual bool16 GetGlyphMatrix(int32 glyphIndex, PMMatrix* glyphMatrix, PMPoint* penCorrection) const = 0;

	/**
		Calculate and return a matrix that can be used to determine the position at which the given glyph will ultimately draw.
	*/
	virtual PMMatrix GetGlyphDrawPosition(int32 glyphIndex) const = 0;

	/**
		Will a matrix be applied to any or all glyphs?
	 */
	virtual bool16 HasGlyphMatrix() const = 0;

	/**
		Get the per-glyph matrix and pen correction for the requested glyph. Does not include AllGlyphsMatrix.
		penCorrection for the matrix is _added_ to the PMPoint passed in.
	 */
	virtual PMMatrix GetPerGlyphMatrix(int32 glyphIndex, PMPoint * penCorrection) const = 0;
	/**
		Update the per-glyph's matrix to this - it is an independent modification of the AllGlyphsMatrix.
	 */
	virtual void SetPerGlyphMatrix( int32 glyphIndex, const PMMatrix& glyphMatrix, const PMPoint& penCorrection ) = 0 ;
	/**
		Return whether or not this object has a per-glyph matrix or not.
	 */
	virtual bool16 HasPerGlyphMatrix() const = 0;

	/**
		Get the matrix that will be applied to all glyphs within this object.  Also returns the penCorrection to be used.

		This matrix should be concat'ed onto scaled font matrix for all glyphs in the array.
		It usually includes skew, rotation, shatai, vertical rotation.
	 */
	virtual PMMatrix GetAllGlyphsMatrix(PMPoint * penCorrection) const = 0;
	/**
		Set the matrix that will be applied to all glyphs within this object.  Also returns the penCorrection to be used.

		This matrix will be concat'ed onto scaled font matrix for all glyphs in the array.
		It usually includes skew, rotation, shatai, vertical rotation.
	 */
	virtual void SetAllGlyphsMatrix( const PMMatrix& matrix, const PMPoint& penCorrection ) = 0 ;

	/**
		Split this set of glyphs into two, the first sub-set (up, not including charOffsetInRun) remains in this object,
		the latter in the given object.
	 */
	virtual bool16 SplitInto(IWaxGlyphs* other, int32 charOffsetInRun) = 0;
};

#endif
