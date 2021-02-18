//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IKerningOnTheFly.h $
//  
//  Owner: Margret_Albrecht
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
#ifndef __IKerningOnTheFly__
#define __IKerningOnTheFly__

#include "IPMUnknown.h"
#include "CTextEnum.h"

class IkfStyle;
class IDrawingStyle;
class PMRealGlyphPoint;


/** This  holds all general information for kf "kerning on the fly" to store and calculate kerning values
	@ingroup text_kern
*/
class IKerningOnTheFly: public IPMUnknown
{
	public:

		/**	Gets kerning value for the left side of a glyph.
			@param *style		style for kerning
			@param bodySize		was int32 in InDesign 2.01.
			@param g			Glyph to get kerning value for
			@return PMReal		Kerning value
		 */
		virtual PMReal LeftSideKerning(IkfStyle *style, const PMReal& bodySize, Text::GlyphID g) = 0;

		/**	Gets kerning value for the right side of a glyph.
			@param *style		style for kerning
			@param bodySize		was int32 in InDesign 2.01.
			@param g			Glyph to get kerning value for
			@return PMReal		Kerning value
		 */
		virtual PMReal RightSideKerning(IkfStyle *style, const PMReal& bodySize, Text::GlyphID g) = 0;

		virtual bool16 SingleStyleKerns(IkfStyle *style, const Text::GlyphID *glyphs,
								PMReal *xkerns, PMReal *yKerns, int32 bufSize) = 0;
		virtual bool16 SingleStyleKerns(IkfStyle *style, PMRealGlyphPoint *strikes, int32 bufSize, double xScale = 1.0) = 0;
		virtual bool16 SingleStyleKern(IkfStyle *style, Text::GlyphID g1,
								Text::GlyphID g2, PMReal *xk, PMReal *yk) = 0;
		virtual bool16 MultiStyleKern(IkfStyle *style1, Text::GlyphID g1,
								IkfStyle *style2, Text::GlyphID g2,  PMReal *xk, PMReal *yk) = 0;

		virtual PMReal  GetParStyleSize() = 0;
		virtual void SetParStyle(const IDrawingStyle * parStyle) = 0;
		virtual IkfStyle*  GetkfStyle(const IDrawingStyle *style) = 0;
		virtual void EmptyCache() = 0;
};


#endif		// __IKerningOnTheFly__
