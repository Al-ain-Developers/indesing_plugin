//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IEdgeAlignDict.h $
//  
//  Owner: Eric_Menninga
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
#ifndef __IEdgeAlignDict__
#define __IEdgeAlignDict__

#include "IPMUnknown.h"
#include "CTextEnum.h"
#include "TextID.h"

class IDrawingStyle;



/** This interface is used to find an edge adjustment for a particular
	style/glyph based on optical considerations.
	@ingroup text_other
*/
class IEdgeAlignDict: public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IEDGEALIGNMENTDICT };
		enum { kDefaultServiceID = kEdgeAlignmentService };

			// if an engine can't do what is requested, correct type to match
		virtual PMReal LeftEdgeAdjustment(const IDrawingStyle *style, const PMReal& bodySize, Text::GlyphID g) const = 0;
		virtual PMReal RightEdgeAdjustment(const IDrawingStyle *style, const PMReal& bodySize, Text::GlyphID g) const = 0;
};


#endif		// __IEdgeAlignDict__
