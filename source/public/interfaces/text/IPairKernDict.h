//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IPairKernDict.h $
//  
//  Owner: EricK
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
#ifndef __IPairKernDict__
#define __IPairKernDict__

#include "IPMUnknown.h"
#include "CTextEnum.h"
#include "TextID.h"

class IDrawingStyle;
class WideStringConstUTF32Iter;
class PMRealGlyphPoint;

/**
	IPairKernDict is the interface used by text composition to calculate kern pairs.

	@ingroup text_kern
*/
class IPairKernDict: public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPAIRKERNDICT };
		enum { kDefaultServiceID = kPairKerningService };

			/** Calculate kern pairs for a buffer of glyphs.
			@param vertical is the text vertical?
			@param style are the attributes applied. Get the font, pointsize, etc from here.
			@param glyphs is a buffer of glyphs.
			@param xKerns is a buffer that will be filled with the kern pair metrics. For example,
					if the first 2 glyphs are the glyphs for 'W' 'A' then xKerns[0] will be kern pair value.
			@param yKerns is a buffer that will be filled with the kern pair adjustments for vertical text.
			@param bufSize is the number of elements in the 3 buffers.
			@param kernChars is an iterator may point to the characters used to produce the glyphs.
					Mostly, the glyphs are sufficient for kerning. Other glyph substitutions (ligatures, fractions)
					may have already occured
			@param scriptTag specifies the OpenType script tag. Nil -> font's default script.
			@param langTag specifies the OpenType language tag. Nil -> font's default language.
			*/
		virtual bool16 SingleStyleKerns(bool16 vertical, const IDrawingStyle *style,
			const Text::GlyphID *glyphs, PMReal *xkerns, PMReal *yKerns, int32 bufSize,
			const WideStringConstUTF32Iter *kernChars = nil,
			const char* scriptTag = nil, const char* langTag = nil) const = 0;

			/** Calculate a kern pair for a pair of glyphs.
			@param vertical is the text vertical?
			@param style are the attributes applied. Get the font, pointsize, etc from here.
			@param g1 is the first glyph.
			@param g2 is the second glyph.
			@param xk should be set the the fixed point kerning value in the horizontal axis.
			@param yk should be set the the fixed point kerning value in the vertical axis.
			@param kernChars is an iterator may point to the characters used to produce the glyphs.
					Mostly, the glyphs are sufficient for kerning. Other glyph substitutions (ligatures, fractions)
					may have already occured
			@param scriptTag specifies the OpenType script tag. Nil -> font's default script.
			@param langTag specifies the OpenType language tag. Nil -> font's default language.
			*/
		virtual bool16 SingleStyleKern(bool16 vertical, const IDrawingStyle *style,
			Text::GlyphID g1, Text::GlyphID g2, PMReal *xk, PMReal *yk,
			const WideStringConstUTF32Iter *kernChars = nil,
			const char* scriptTag = nil, const char* langTag = nil) const = 0;

			/** Calculate kern pairs for a pair of glyphs using different text attributes.
			@param vertical is the text vertical?
			@param style are the attributes applied to the first character. Get the font, pointsize, etc from here.
					The method CanSimpleKernWith() may be used to determine if the 2 glyphs are compatible for kerning.
			@param g1 is the first glyph.
			@param style2 are the attributes applied to the second character. Get the font, pointsize, etc from here.
					The method CanSimpleKernWith() may be used to determine if the 2 glyphs are compatible for kerning.
			@param g2 is the second glyph.
			@param xk should be set the the fixed point kerning value in the horizontal axis.
			@param yk should be set the the fixed point kerning value in the vertical axis.
			@param kernChars is an iterator may point to the characters used to produce the glyphs.
					Mostly, the glyphs are sufficient for kerning. Other glyph substitutions (ligatures, fractions)
					may have already occured
			@param paraStyle should be set (if possible) to the root paragraph attributes for this text. This
					can allow kerning services to tune kerns of mixed sizes to favor the paragraph's overall color.
			@param scriptTag specifies the OpenType script tag. Nil -> font's default script.
			@param langTag specifies the OpenType language tag. Nil -> font's default language.
			*/
		virtual bool16 MultiStyleKern(bool16 vertical, const IDrawingStyle *style1,
			Text::GlyphID g1, const IDrawingStyle *style2, Text::GlyphID g2, PMReal *xk, PMReal *yk,
			const WideStringConstUTF32Iter *kernChars = nil, const IDrawingStyle *paraStyle = nil,
			const char* scriptTag = nil, const char* langTag = nil) const = 0;

			/** Calculate kern pairs for a buffer of PMRealGlyphPoints.
			@param vertical is the text vertical?
			@param style are the attributes applied. Get the font, pointsize, etc from here.
			@param strike is a buffer of PMRealGlyphPoints. Adjust the xPosition and yPosition fields directly.
			@param number is the number of glyph points used in the buffer.
			@param bufSize is the number of elements in the 3 buffers.
			@param kernChars is an iterator may point to the characters used to produce the glyphs.
					Mostly, the glyphs are sufficient for kerning. Other glyph substitutions (ligatures, fractions)
					may have already occured
			@param scriptTag specifies the OpenType script tag. Nil -> font's default script.
			@param langTag specifies the OpenType language tag. Nil -> font's default language.
			*/
		virtual bool16 SingleStyleKerns(bool16 vertical, const IDrawingStyle *style,
			PMRealGlyphPoint *strike, int32 number, const WideStringConstUTF32Iter *kernChars = nil,
			const char* scriptTag = nil, const char* langTag = nil) const = 0;
};


#endif
		// __IPairKernDict__
