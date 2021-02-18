//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IRefPointShape.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IRefPointShape__
#define __IRefPointShape__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "PMPolygon4.h"

#include "UIDRef.h"

class UIDList;
class IGraphicsPort;
class IGraphicsContext;

/**  Interface class that handles drawing the actual reference point shape on the screen.
	 In general, these methods are only used internally since the management of the reference
	 point is handled via higher-level calls.

	 @see IRefPointUIUtils.h
*/
class IRefPointShape : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IREFPOINTSHAPE };

	/** Enum that controls the size of the reference point (in pixels). */
	enum
	{
		/** Bounds of the reference point shape. */
		kSize = 13
	};

	/**	Method that does the actual drawing of the reference point shape.
		@param gPort [IN] the port to draw into. 
		@param center [IN] the point in pasteboard coordinates to center the reference point drawing on.
	 */
	virtual void Path(IGraphicsPort* gPort, const PBPMPoint& center) = 0;

	/**	Description
		@param gc [IN] IGraphicsContext pointer for drawing.
		@param center [IN] the point in pasteboard coordinates to center the reference point drawing on.
	 */
	virtual void Draw(IGraphicsContext* gc, const PMPoint& center) = 0;

	/**	Invalidate the area of the screen where the reference point shape is.
		@param gc [IN] IGraphicsContext pointer for drawing.
		@param center [IN] the point in pasteboard coordinates to center the reference point invalidation on.
		@param forceInval, kTrue to force the invalidation even if the reference point is hidden, kFalse to only invalidate when shown. 
	 */
	virtual void Invalidate(IGraphicsContext* gc, const PMPoint& center, bool16 forceInval = kFalse) = 0;

	/**	Return the bounds of the reference point shape.
		@param gc [IN] IGraphicsContext pointer for drawing.
		@param center [IN] the point in pasteboard coordinates of the middle of reference point shape.
		@return PMRect the bounds of the reference point shape in pasteboard coordinates
	 */
	virtual PMRect GetBounds(IGraphicsContext* gc, const PMPoint& center) = 0;
};

/** PMPolygon4Extras namespace */
namespace PMPolygon4Extras
{
	inline PMPoint TopLeft(const PMPolygon4& bounds4);
	inline PMPoint TopCenter(const PMPolygon4& bounds4);
	inline PMPoint TopRight(const PMPolygon4& bounds4);
	inline PMPoint LeftCenter(const PMPolygon4& bounds4);
	inline PMPoint Center(const PMPolygon4& bounds4);
	inline PMPoint RightCenter(const PMPolygon4& bounds4);
	inline PMPoint BottomLeft(const PMPolygon4& bounds4);
	inline PMPoint BottomCenter(const PMPolygon4& bounds4);
	inline PMPoint BottomRight(const PMPolygon4& bounds4);
	
	inline PMReal Left(const PMPolygon4& bounds4);
	inline PMReal Top(const PMPolygon4& bounds4);
	inline PMReal Right(const PMPolygon4& bounds4);
	inline PMReal Bottom(const PMPolygon4& bounds4);
	
	inline PMPoint GetPoint(const PMPolygon4& bounds4, PMRect::PointIndex whichPoint);	
	inline PMPoint GetOppositePoint(const PMPolygon4& bounds4, PMRect::PointIndex whichPoint);
}

inline PMPoint PMPolygon4Extras::TopLeft(const PMPolygon4& bounds4)
{
	return bounds4[0];
}
inline PMPoint PMPolygon4Extras::TopCenter(const PMPolygon4& bounds4)
{
	return (bounds4[0] + bounds4[1]) / 2;
}
inline PMPoint PMPolygon4Extras::TopRight(const PMPolygon4& bounds4)
{
	return bounds4[1];
}
inline PMPoint PMPolygon4Extras::LeftCenter(const PMPolygon4& bounds4)
{
	return (bounds4[0] + bounds4[3]) / 2;
}
inline PMPoint PMPolygon4Extras::Center(const PMPolygon4& bounds4)
{
	return (bounds4[0] + bounds4[2]) / 2;
}
inline PMPoint PMPolygon4Extras::RightCenter(const PMPolygon4& bounds4)
{
	return (bounds4[1] + bounds4[2]) / 2;
}
inline PMPoint PMPolygon4Extras::BottomLeft(const PMPolygon4& bounds4)
{
	return bounds4[3];
}
inline PMPoint PMPolygon4Extras::BottomCenter(const PMPolygon4& bounds4)
{
	return (bounds4[3] + bounds4[2]) / 2;
}
inline PMPoint PMPolygon4Extras::BottomRight(const PMPolygon4& bounds4)
{
	return bounds4[2];
}

inline PMReal PMPolygon4Extras::Left(const PMPolygon4& bounds4)
{
	return bounds4[0].X();
}
inline PMReal PMPolygon4Extras::Top(const PMPolygon4& bounds4)
{
	return bounds4[0].Y();
}
inline PMReal PMPolygon4Extras::Right(const PMPolygon4& bounds4)
{
	return bounds4[2].X();
}
inline PMReal PMPolygon4Extras::Bottom(const PMPolygon4& bounds4)
{
	return bounds4[2].Y();
}

inline PMPoint PMPolygon4Extras::GetPoint(const PMPolygon4& bounds4, PMRect::PointIndex whichPoint)
{
	PMPoint thePoint;
	
	switch (whichPoint)
	{
		case PMRect::kMiddleTop:
			thePoint = PMPolygon4Extras::TopCenter(bounds4);
			break;
		case PMRect::kLeftMiddle:
			thePoint = PMPolygon4Extras::LeftCenter(bounds4);
			break;
		case PMRect::kMiddleBottom:
			thePoint = PMPolygon4Extras::BottomCenter(bounds4);
			break;
		case PMRect::kRightMiddle:
			thePoint = PMPolygon4Extras::RightCenter(bounds4);
			break;
		case PMRect::kLeftTop:
			thePoint = PMPolygon4Extras::TopLeft(bounds4);
			break;
		case PMRect::kRightTop:
			thePoint = PMPolygon4Extras::TopRight(bounds4);
			break;
		case PMRect::kRightBottom:
			thePoint = PMPolygon4Extras::BottomRight(bounds4);
			break;
		case PMRect::kLeftBottom:
			thePoint = PMPolygon4Extras::BottomLeft(bounds4);
			break;
		case PMRect::kCenter:
			thePoint = PMPolygon4Extras::Center(bounds4);
			break;
		default:
			ASSERT_FAIL("Invalid PointIndex in PMPolygon4Extras::GetPoint");
		}
	return thePoint;
}

inline PMPoint PMPolygon4Extras::GetOppositePoint(const PMPolygon4& bounds4, PMRect::PointIndex whichPoint)
{
	return GetPoint(bounds4, kEmptyRect.GetOppositePointIndex(whichPoint));
}

#endif	// __IRefPointShape__
