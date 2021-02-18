//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMPageSize.h $
//  
//  Owner: sheridan
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
//  Purpose:
//  
//========================================================================================

#pragma once
#ifndef __PageSize__
#define __PageSize__


#include "BaseType.h"
//#include "K2Assert.h"
#include "PMReal.h"
#include "PMRect.h"
#include "K2Pair.h"
#include <cmath>

class IPMStream;

class PUBLIC_DECL PMPageSize
{
public:
	typedef base_type data_type; //K2Vector requirement


	PMPageSize( PMReal width, PMReal height, K2Pair<PMReal, PMReal> scale)
		: fWidth(width), fHeight(height), fWidthScale(scale.first), fHeightScale(scale.second), fEnumerationTag(0)
	{}

	PMPageSize( PMReal width, PMReal height)
		: fWidth(width), fHeight(height), fWidthScale(1.0), fHeightScale(1.0), fEnumerationTag(0)
	{}

	PMPageSize( PMReal width, PMReal height, const PMPoint& square_inch)
		: fWidth(width), fHeight(height), fWidthScale(72.0/square_inch.X()), fHeightScale(72.0/square_inch.Y()), fEnumerationTag(0)
	{}

	explicit PMPageSize( const PMRect& r)
		: fWidth(r.Width()), fHeight(r.Height()), fWidthScale(1.0), fHeightScale(1.0), fEnumerationTag(0)
	{}

	explicit PMPageSize( uint32 tag)
		: fWidth(0.), fHeight(0.), fWidthScale(1.0), fHeightScale(1.0), fEnumerationTag(tag)
	{
		ASSERT(fEnumerationTag > 0); //could just add 1 to the provided tag and skip the assert, but then I'd have to assert the add didn't wrap to zero
	}


//	explicit operator PMRect() const { return PMRect(0., 0., fWidth, fHeight);}




	PMReal OutputWidth() const
	{
		return fWidth;
	}

	PMReal OutputHeight() const
	{
		return fHeight;
	}

	PMPoint OutputDimensions() const
	{
		return PMPoint( OutputWidth(), OutputHeight());
	}




	PMReal DesignWidth() const
	{
		return fWidth*fWidthScale;
	}

	PMReal DesignHeight() const
	{
		return fHeight*fHeightScale;
	}

	PMPoint DesignDimensions() const
	{
		return PMPoint( DesignWidth(), DesignHeight());
	}




	PMReal WidthScale() const
	{
		return fWidthScale;
	}
	
	PMReal HeightScale() const
	{
		return fHeightScale;
	}



	PMReal WidthPPI() const
	{
		return 72.0 / fWidthScale;
	}

	PMReal HeightPPI() const
	{
		return 72.0 / fHeightScale;
	}


	bool16 operator==(const PMPageSize& other) const //careful PMReal fuzz at play
	{
		if( fEnumerationTag || other.fEnumerationTag)
			return fEnumerationTag == other.fEnumerationTag;

		return
		   fWidth == other.fWidth
		&& fHeight == other.fHeight
		&& fWidthScale == other.fWidthScale
		&& fHeightScale == other.fHeightScale;
	}

	bool16 operator!=(const PMPageSize& other) const //careful PMReal fuzz at play
	{
		return !(*this == other);
	}




	PMReal OutputShape() const
	{
		return ShapeMeasure_( fWidth, fHeight);
	}

	bool16 OutputIsWide() const
	{
		return OutputShape() > 1.; //careful PMReal fuzz at play
	}
	
	bool16 OutputIsTall() const
	{
		return OutputShape() < 1.; //careful PMReal fuzz at play
	}
	
	bool16 OutputIsSquare() const
	{
		return OutputShape() == 1.; //careful PMReal fuzz at play
	}

	bool16 OutputIsEmpty() const
	{
		return fWidth*fHeight == 0.; //careful PMReal fuzz at play
	}


	PMReal DesignShape() const
	{
		return ShapeMeasure_( fWidth*fWidthScale, fHeight*fHeightScale);
	}

	bool16 DesignIsWide() const
	{
		return DesignShape() > 1.; //careful PMReal fuzz at play
	}
	
	bool16 DesignIsTall() const
	{
		return DesignShape() <= 1.; //careful PMReal fuzz at play
	}
	
	bool16 DesignIsSquare() const
	{
		return DesignShape() == 1.; //careful PMReal fuzz at play
	}

	bool16 DesignIsEmpty() const
	{
		return fWidth*fWidthScale*fHeight*fHeightScale == 0.; //careful PMReal fuzz at play
	}


	void ReadWrite( IPMStream* iPMStream);




private:

	double ShapeMeasure_( PMReal w, PMReal h) const //hmm what about (0,0)? atan2 return 0.
	{
		return std::atan2( std::fabs(ToDouble(w)), std::fabs(ToDouble(h)))/std::atan(1.); //normalize [0..2] note shape is > 1 for landscape aspect ratios
	}

	PMReal fWidth, fHeight, fWidthScale, fHeightScale;
	uint32 fEnumerationTag;
};



inline PMPageSize TransposedPageSize( const PMPageSize& ps)
{
	return PMPageSize( ps.OutputHeight(), ps.OutputWidth(), K2Pair<PMReal,PMReal>(ps.HeightScale(), ps.WidthScale()));
}

extern PUBLIC_DECL const PMPageSize kPMPageSizeCustom; 
extern PUBLIC_DECL const PMPageSize kPMPageSizeDefine; 
extern PUBLIC_DECL const PMPageSize kPMPageSizeMixed;
extern PUBLIC_DECL const PMPageSize kPMPageSizeEmpty;
extern PUBLIC_DECL const PMPageSize kPMPageSizeNeighbor;
extern PUBLIC_DECL const PMPageSize kPMPageSizeDefault;

#endif
