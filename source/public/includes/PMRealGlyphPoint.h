//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMRealGlyphPoint.h $
//  
//  Owner: mvogel
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
#ifndef __PMRealGlyphPoint__
#define __PMRealGlyphPoint__


#include "CTextEnum.h"            // for Text::GlyphID


/** A glyph ID and its x/y coordinates
*/
#pragma export on


struct CTRealGlyphPointx {
	/**  */
	int32	glyphID;	// CTGlyphID = BRVInt32
	/**  */
	float		xPosition;	// BRVRealCoord
	/**  */
	float		yPosition;	// BRVRealCoord
};

class PMRealGlyphPoint
{
public:
	PMRealGlyphPoint()
		{ Set(kInvalidGlyphID, 0.0, 0.0); }
	explicit PMRealGlyphPoint(Text::GlyphID glyphID, float x = 0.0, float y = 0.0)
		{ Set(glyphID, x, y); }

	void Set(Text::GlyphID glyphID, float x = 0.0, float y = 0.0)
		{ fPoint.glyphID = glyphID; fPoint.xPosition = x; fPoint.yPosition = y; }

	void SetX(float x)
		{ fPoint.xPosition = x; }
	void SetY(float y)
		{ fPoint.yPosition = y; }
	void SetX(PMReal x)
		{ fPoint.xPosition = ::ToFloat(x); }
	void SetY(PMReal y)
		{ fPoint.yPosition = ::ToFloat(y); }

	Text::GlyphID GetGlyphID() const
		{ return fPoint.glyphID; }
	Text::GlyphID& GlyphID()
		{ return fPoint.glyphID; }

	float GetXPosition() const
		{ return fPoint.xPosition; }
	float GetYPosition() const
		{ return fPoint.yPosition; }

	float& GetXPosition()
		{ return fPoint.xPosition; }
	float& GetYPosition()
		{ return fPoint.yPosition; }

	PMRealGlyphPoint& operator+=(const PMRealGlyphPoint& other)
		{ fPoint.yPosition += other.fPoint.yPosition;
		  fPoint.xPosition += other.fPoint.xPosition;
		  return *this;
		}

private:
	CTRealGlyphPointx	fPoint;
};

#pragma export off

DECLARE_BASE_TYPE(PMRealGlyphPoint);


#endif

