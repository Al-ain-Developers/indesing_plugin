//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontMetricsTable.h $
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
#ifndef __IFontMetricsTable__
#define __IFontMetricsTable__

#include "IPMUnknown.h"
#include "FontMgrID.h"
#include "CTextEnum.h"

class PMMatrix;
class PMReal;

/**	In the Japanese version of InDesign a feature called "Tsume" is available.
	This feature removes a percentage of the whitespace from either side of a glyph.
	It works by getting the exact ink bounding box of a particular glyph and comparing that
	with the pen-advance. Because this data is completely unavailable when the font
	is missing, we store the values, as they are used, in this table. Each font that has been
	used with Tsume has its own table. These tables are available from the IFontMetricTableList.
	@see IFontMetricsTableList
	@ingroup text_font
*/
class IFontMetricsTable : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IFONTMETRICSTABLE };

		/** For a glyphID at a particular size, get the amount of white space before & after the
			actual ink bounds in the horizontal direction.
			@param matrix specifies the character matrix being considered. Only the 2x2 matrix is used.
			@param glyph is the glyphID of requested.
			@param before RETURNS the amount of whitespace before the glyph. Can be nil.
			@param after RETURNS the amount of whitespace after the glyph. Can be nil.
			@return kFalse if the font was missing or the glyph was unavailable in some way.
		*/
		virtual bool16 GetTsumeHorizontal(const PMMatrix& matrix, Text::GlyphID glyph, PMReal *before, PMReal *after) = 0;

		/** For a glyphID at a particular size, get the amount of white space above & below the
			actual ink bounds in the vertical direction.
			@param matrix specifies the character matrix being considered. Only the 2x2 matrix is used.
			@param glyph is the glyphID of requested.
			@param above RETURNS the amount of whitespace above the glyph. Can be nil.
			@param below RETURNS the amount of whitespace below the glyph. Can be nil.
			@return kFalse if the font was missing or the glyph was unavailable in some way.
		*/
		virtual bool16 GetTsumeVertical(const PMMatrix& matrix, Text::GlyphID glyph, PMReal *above, PMReal *below) = 0;

		/** Clear the table of saved side-bearings for this font. This function is generally only called
			by IFontMetricsTableList::ClearFontMetricsTable which is called by the composite font system.
		*/
		virtual void ClearTable() = 0;
};


#endif
		// __IFontMetricsTableList__
