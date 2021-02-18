//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IkfStyle.h $
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
#ifndef __IkfStyle__
#define __IkfStyle__


#include "GRRefCountedObj.h"
#include "PMTypes.h"
#include "IDrawingStyle.h"

class kfCharacter; 
class OKLStyle;

/** This  holds all style specific information for kf "kerning on the fly" to store and calculate kerning values 
	@ingroup text_kern
*/
class IkfStyle : public grRefCountedObj
{
	public:
		IkfStyle()
			{}

		virtual bool16 Kern(Text::GlyphID gl, Text::GlyphID gr, PMReal *kw,
							int32 kernUnities, void *fSqrLT) = 0;		   
		virtual PMReal LeftSideKern(Text::GlyphID g, void *marginSpNorm, PMReal bodySize, int32 kwil,
								   int32 kernUnities, void *fSqrLT) = 0;
		virtual PMReal RightSideKern(Text::GlyphID g, void *marginSpNorm, PMReal bodySize, int32 kwir,
									int32 kernUnities, void *fSqrLT) = 0;
		
		virtual Text::GlyphID	hyphenGlyph() = 0;
		virtual PMReal fontSize() = 0;
		virtual	double fontSizeDouble() = 0;
		virtual int32 capHeight() = 0;
		virtual Text::GlyphID	marginGlyph() = 0;
  		virtual void *GetClasses() = 0;
  		virtual void *GetSpnorm() = 0;
  		virtual void *GetkfRaster() = 0;
		virtual Text::GlyphID *GetQDtoGlyph() = 0;
		virtual kfCharacter **kfCharcaters() = 0;
		virtual void SetkfStyleID(int32 kfstyleID) = 0;
		virtual int32 GetkfStyleID() = 0;
		virtual bool16 IsValid() = 0;
		virtual bool16 IsStyle(double ptSize, char* fontNameString,
							   double widthFactor, double heightFactor,
							   int16 designVNumAxes, const Fixed *designV,
							   IDrawingStyle::CapitalizeMode capitalizeMode) = 0;
		virtual IPMFont *GetFont() = 0;
		virtual void setFontName(CString fontNameString) = 0;
		
  		virtual void makekfChar(Text::GlyphID ch, Bool16 forMarginAlignment) = 0;
		virtual int16 kfInitStylistics( int32 numScanLines) = 0;	
		virtual int16 SetStyle(double ptSize, char *fontNameString,
							   double widthFactor, double heightFactor,
							   int16 designVNumAxes, const Fixed *designV,
							   IDrawingStyle::CapitalizeMode capitalizeMode,
							   void *SqrtLT) = 0;		


		/**	Does the style passed in match this style
			@param *drawStyle - style to compare
			@return bool16 - kTrue if same style. kFalse if different
		 */
		virtual bool16 IsStyle(const IDrawingStyle *drawStyle) = 0;

		/**	Set style based on drawStyle.
			@param *drawStyle - style to set to
			@return int16 - noError if style is set
		 */
		virtual int16 SetStyle(const IDrawingStyle *drawStyle) = 0;

		/**	Kern mixed style
			@param *style1 
			@param g1 
			@param *style2 
			@param g2 
			@return double 
		 */
		virtual PMReal MultiStyleHKern(IkfStyle *style1, Text::GlyphID g1, IkfStyle *style2,
							Text::GlyphID g2) = 0;

		/**	For Internal use only.
			@return OKLStyleObj *
		 */
  		virtual OKLStyle& GetStyleObject() = 0;

};


#endif		// __IkfStyle__
