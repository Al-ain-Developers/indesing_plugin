//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxGlyphsME.h $
//  
//  Owner: prubini
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
//  
//  ADOBE CONFIDENTIAL
//  
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#ifndef __IWaxGlyphsMEData__
#define __IWaxGlyphsMEData__

#include "WorldReadyID.h"
#include "IPMUnknown.h"

class TEInputOutputMapping;

/** Interface for working with complex-script specific glyph data.
	This information is provided only for text composed with a
	complex-script composer. It provides additional layout information that
	is critical for the correct placement of marks & diacritics, especially
	in right-to-left writing scripts.

	@see IWaxGlyphs
	@ingroup text_wax
*/
class IWaxGlyphsME : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IWAXGLYPHSME };

		/** provide the complex layout metrics for this run of glyphs
		@param num is the number of glyphs
		@param xOffsets
		@param yOffsets
		@param width
		@param lineGlyphOffset
		@param lineTextOffset
		*/
		virtual void			AddGlyphMEData(int32 num, const float* xOffsets, const float* yOffsets,
												const float * width, int32 lineGlyphOffset = -1, int32 lineTextOffset = -1) = 0;

		/** get xoffset for an index.
		@param glyphIndex
		@return x offset for the glyph */
		virtual float			GetXOffsetAt(int32 glyphIndex) const = 0;
		/** set xoffset for an index.
		@param glyphIndex
		@param xOffset for the glyph */
		virtual void			SetXOffsetAt(int32 glyphIndex, float xOffset) = 0;

		/** get yoffset for an index.
		@param glyphIndex
		@return y offset for the glyph */
		virtual float			GetYOffsetAt(int32 glyphIndex) const = 0;
		/** set yoffset for an index.
		@param glyphIndex
		@param yOffset for the glyph */
		virtual void			SetYOffsetAt(int32 glyphIndex, float yOffset) = 0;

		/** get left offset for an index.
		@param glyphIndex
		@return left offset for the glyph */
		virtual float			GetLeftOffsetAt(int32 glyphIndex) const = 0;
		/** set left offset for an index.
		@param glyphIndex
		@param offset is the left offset for the glyph */
		virtual void			SetLeftOffsetAt(int32 glyphIndex,float offset) = 0;

		/** get the diacritical marks x-offset buffer.
		@ return the x-offset buffer.
		*/
		virtual const float*		PeekDiacXOffsetArray() const = 0;
		/** get the diacritical marks y-offset buffer.
		@ return the y-offset buffer.
		*/
		virtual const float*		PeekDiacYOffsetArray() const = 0;
		/** get the diacritical marks left-offset buffer.
		@ return the left-offset buffer.
		*/
		virtual const float*		PeekLeftOffsetArray() const = 0;

		/** get the difference between this run's first glyph and the line's first glyph.
		@return line glyph offset.
		*/
		virtual int32			GetLineGlyphOffset() const = 0;
		/** get the difference between this run's first character and the line's first character.
		@return line text offset.
		*/
		virtual int32			GetLineTextOffset() const = 0;

		/** GetLog().
		@return the character - glyph mapping.
		*/
		virtual const TEInputOutputMapping*	GetLog() const = 0;

		/** GetIsTabLeaderRun.
		@return if this run is a tab leader run.
		*/
		virtual bool			GetIsTabLeaderRun() const = 0;
		/** SetIsTabLeaderRun. Not to be called outside of composition.
		@param tabLeaderRun specifies if this run is a tab leader run.
		*/
		virtual void			SetIsTabLeaderRun(bool tabLeaderRun) = 0;

		/**
			Split this set of glyphs into two, the first sub-set (up, not including charOffsetInRun) remains in this object,
			the latter in the given object.
		 */
		virtual bool16			SplitInto(IWaxGlyphsME* other, int32 glyphOffsetInRun) = 0;
};

#endif

