//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrFigureStyle.h $
//  
//  Owner: Eric Menninga
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
#ifndef __ITextAttrFigure__
#define __ITextAttrFigure__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "TextAttrID.h"


/**	ITextAttrFigureStyle is a simple data interface that is used to hold the
	desired figure style: oldstyle vs. lining, tabular vs. proportional, or
	the default as specified in the font. Which glyphs are affected by this
	is font dependent, but we only support OpenType fonts, and they usually
	provide the 10 figures (0 - 9) plus sometimes some punctuation (e.g. %$).
	@ingroup text_attr
*/
class ITextAttrFigureStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRFIGURESTYLE };

		/** Enumeration of text attribute figure styles
		*/
		typedef enum {	
						/** consistent width, "tall" figures
						*/
						kFigure_LiningTabular = 0,		// consistent width, "tall" figures.
						/** proportional width, "lowercase" figures
						*/
						kFigure_OldstyleProp = 1,		// proportional width, "lowercase" figures.
						/** proportional width "tall" figures
						*/
						kFigure_LiningProp = 2,			// proportional width "tall" figures.
						/** consistent width "lowercase" figures
						*/
						kFigure_OldstyleTabular = 3,		// consistent width "lowercase" figures.
						/** use whatever the font says is the default
						*/
						kFigure_Default = 4				// use whatever the font says is the default.
						} FigureStyle;

		/** FigureStyle enumeration type
		*/
		typedef ITextAttrFigureStyle::FigureStyle		ValueType;

			/** Get the value.
				@return the desired figure style
			*/
		virtual ValueType Get() const = 0;
			/** Set the value.
				@param val is the desired figure style
			*/
		virtual void Set(ValueType val) = 0;
};

#endif

