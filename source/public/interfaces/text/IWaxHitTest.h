//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxHitTest.h $
//  
//  Owner: zwilliam
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
#ifndef __IWaxHitTest__
#define __IWaxHitTest__

#include "IPMUnknown.h"
#include "TextID.h"

class PMPoint;
class PMLineSeg;
class PMMatrix;

/** Class providing translation from a text index relative to the waxLine to a point within the waxLine coordinate space or vice versa.
	@ingroup text_wax
*/
class IWaxHitTest : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXHITTEST };

	/** This enum provides exceptional return values for the translation of points to text indices.
	*/
	typedef enum {
		kHitBefore		= -1,
		kHitToTheRight	= 0x7FFFFFFE,
		kHitBelow		= 0x7FFFFFFF
	} HitTestPosition;

	/** Translate a point in this object waxLine to a text index relative to this object.

		@param pt IN A point in Wax coordinate system.

		@param selection OUT A line designating the height of the selection.

		@param charCount OUT An optional return parameter returning the number of chars in this object.

		@return a real number which designates the index of the char hit and includes the fractional distance to
			the next character. designates how far into that char it hit, or one of the following values, as described below:
			kHitBefore, kHitToTheRight, kHitBelow

		@note that this works on characters, not glyphs.  For characters that result in multiple glyphs, the
				group of glyphs is treated as a single glyph.

		Additional information on return values:
		WaxRuns:
			If pt is above or to the left then the call returns kHitBefore.
			If pt is to the right then the call returns kHitToTheRight.
			If pt is below then the call returns kHitBelow.
			Otherwise the run is hit and the call returns the offset of the first glyph that is at or to the right of pt and
				pt is adjusted as follows: (the left of the glyph, selection bottom).

		WaxLines:
			If pt is above or to the left then the call returns zero (0) and pt is adjusted to point to the first glyph on the line.
			If pt is below then the call returns kHitBelow as an indication to try the next line.
			If pt is within the bounds of the line, this call returns the offset of the closest glyph within the line and adjusts pt to
				point to the start of that glyph at the YPosition of the waxLine.
			If pt is within the bounds o the line, but to the right of the last glyph then this call returns the equivalent offset for
				the first glyph on the NEXT waxLine (if this would not be past the story thread boundry), adjusts pt to point to the
				end of the last glyph on the waxLine, and sets the endOfLine flag to kTrue.
	*/
	virtual PMReal HitTestWax(PMPoint pt, PMLineSeg selection, int32* charCount = nil) const = 0;

	/** Translate a text index relative to this object to a point in this object.

		@return kTrue for a valid translation, kFalse otherwise.

		@param offset IN A valid offset in to the wax, or alternatively a value equal to the wax length.

		@param pt OUT If a valid offset, then pt is always adjusted to reflect the Wax X and Y Position, not necessarily
					where and how the glyph is actually drawn in the case of complex transformations (shears, TOP, etc).

			If offset is within the wax then pt is adjusted to reflect the left edge of the appropriate char.
			If offset is equal to the wax length AND this object was hit, then pt is adjusted to reflect the right edge of the last char.

		@note that this works on characters, not glyphs.  For characters that result in multiple glyphs, the
			group of glyphs is treated as a single glyph.

		@param innerPos IN Affects the "lean" of the index.  For instance, if offset is equal to the wax length, then if this is non-zero
						this wax will not be considered to be hit (the next one will).  If innerPos is 0, then this object
						will be hit and the last char will be used to determine the results.

		@param pWaxToGlyphMatrix OUT An optional return parameter which can be used to transform things (such as lines) to
					the actual glyph location.
				@note that anything returned via the wax (e.g. pt) is already transformed and thus applying this matrix
					would be wrong for those items.  It should only be applied to items in the same coordinate space that
					waxLines are in (i.e. parcel coordinates).
	*/
	virtual bool16 GetLocationOf(int32 offset, PMPoint* pt, int32 innerPos, PMMatrix* pWaxToGlyphMatrix = nil) const = 0;
};

#endif
