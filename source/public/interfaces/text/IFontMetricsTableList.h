//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontMetricsTableList.h $
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
#ifndef __IFontMetricsTableList__
#define __IFontMetricsTableList__

#include "IPMUnknown.h"
#include "FontMgrID.h"


class IFontMetricsTable;
class IPMFont;

/**	In the Japanese version of InDesign a feature called "Tsume" is available.
	This feature removes a percentage of the whitespace from either side of a glyph.
	It works by getting the exact ink bounding box of a particular glyph and comparing that
	with the pen-advance. Because this data is completely unavailable when the font
	is missing, we store the values, as they are used, in this table. Each font that has been
	used with Tsume has its own table. These tables are available from the IFontMetricTableList.
	@see IFontMetricsTable
	@ingroup text_font
*/
class IFontMetricsTableList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IFONTMETRICSTABLELIST };

		/** return a IFontMetricsTable for a particular font.
			@param font specifies which font you want to get side-bearings for.
			@param createIfNew specifies if you want "nil" returned if the table doesn't already exist.
					otherwise, it will create an empty table.
			@return a AddRef'd IFontMetricsTable interface for the font.
		*/
		virtual IFontMetricsTable* QueryFontMetricsTable(const IPMFont *font, bool16 createIfNew) = 0;

		/** Clear the table for a particular font. Only called by the Composite Font Manager at this time.
			@param font is the font whose table is to be cleared.
		*/
		virtual void ClearFontMetricsTable(const IPMFont *font) = 0;
};


#endif
		// __IFontMetricsTableList__
