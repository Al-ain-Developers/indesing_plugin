//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMLineSeg.h $
//  
//  Owner: Ric Kamicar
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
//  Simple class to hold two points. The line is vertically directional, meaning that top <= bottom.
//  The line is primarily vertical, so the object is optimized for that.
//  Also, UNLIKE PMReal, this class asserts if the object is ill-formed (PMRect silently normalizes).
//  
//========================================================================================

#pragma once
#ifndef __PMLineSeg__
#define __PMLineSeg__

#include "PMPoint.h"

#pragma export on

/**	A C++ class for line segment. This line segment is defined by two points.
*/
class PUBLIC_DECL PMLineSeg
{
public:
	/**	The default constructor makes no assumptions about what a default line is.
	*/
	PMLineSeg()
		{ }

	/**	Creates a line given two points.
		(Current) usage is such that, usually P1 is "less than" P2, resulting in DeltaY being positive.
		We assert the fact that P1.Y() < P2.Y().  The x-dimension can be arbitrary.
		Therefore it is assumed that P1 is the top point and P2 the bottom.
		@param P1 is the first point.
		@param P2 is the second point.
	*/
	PMLineSeg(const PMPoint& P1, const PMPoint& P2) :
			fTop(P1), fBottom(P2)
		{
			if (fTop.Y() > fBottom.Y()) {
				fTop = P2;
				fBottom = P1;
				}
			ASSERT(fTop.Y() <= fBottom.Y());
		}

	/**	Creates a line given a point and x and y distances.
		It is assumed that P1 is the top point and P2 the bottom
		@param P1 is the point.
		@param xDistance is the distance to the y-axis (P2).
		@param yDistance is the distance to the x-axis (P2).
	*/
	PMLineSeg(const PMPoint& P1, const PMReal& xDistance, const PMReal& yDistance) :
			fTop(P1)
		{
			ASSERT(yDistance >= 0);
			fBottom = PMPoint(fTop.X() + xDistance, fTop.Y() + yDistance);
		}

	/**	Cosntruct a line given two points as x and y each.
		It is assumed that P1 is the top point and P2 the bottom
		@param p1x is the x position of the first point (P1).
		@param p1y is the y position of the first point (P1).
		@param p1x is the x position of the second point (P2).
		@param p1y is the y position of the second point (P2).
	*/
	PMLineSeg(const PMReal& p1x, const PMReal& p1y, const PMReal& p2x, const PMReal& p2y)
		{
			ASSERT(p1y <= p2y);
			fTop = PMPoint(p1x, p1y);
			fBottom = PMPoint(p2x, p2y);
		}

	/**	@return true if line is a horizontal line.
	*/
	bool16 IsHorizontal() const
		{
			return fBottom.Y() == fTop.Y();
		}

	/**	@return true if line is a vertical line.
	*/
	bool16 IsVertical() const
		{
			return fBottom.X() == fTop.X();
		}

	/**	@return the difference in the x coordinates.
	*/
	PMReal DeltaX() const
		{
			return fBottom.X() - fTop.X();
		}

	/**	@return the difference in the y coordinates.
	*/
	PMReal DeltaY() const
		{
			return fBottom.Y() - fTop.Y();
		}

	// Accessor Methods
	/**	@reutrn the top point.
	*/
	const PMPoint& TopPoint() const
		{
			return fTop;
		}

	/**	@reutrn the bottom point.
	*/
	const PMPoint& BottomPoint() const
		{
			return fBottom;
		}

#if ZERO
	PMPoint& TopPoint()
		{
			return fTop;
		}
	void TopPoint(const PMPoint& newP1)
		{
			fTop = newP1;
		}

	PMPoint& BottomPoint()
		{
			return fBottom;
		}
	void BottomPoint(const PMPoint& newP2)
		{
			fBottom = newP2;
		}
#endif

	/**	@reutrn the top point y value.
	*/
	const PMReal& Top() const
		{
			return fTop.Y();
		}

	/**	Return the top point y value.
		Caution when using this method - you should ASSERT(fTop.Y() <= fBottom.Y());
		@reutrn the top point y value.
	*/
	PMReal& Top()
		{
			return fTop.Y();
		}

	/**	Set the top point y value.
		@param newP1y is the new y value for top point.
	*/
	void Top(const PMReal& newP1y)
		{
			fTop.Y(newP1y);
			ASSERT(fTop.Y() <= fBottom.Y());
		}

	/**	@reutrn the bottom point y value.
	*/
	const PMReal& Bottom() const
		{
			return fBottom.Y();
		}
	/**	Return the bottom point y value.
		Caution when using this method - you should ASSERT(fTop.Y() <= fBottom.Y());
		@reutrn the bottom point y value.
	*/
	PMReal& Bottom() 
		{
			return fBottom.Y();
		}
	/**	Set the bottom point y value.
		@param newP2y is the new y value for bottom point.
	*/
	void Bottom(const PMReal& newP2y)
		{
			fBottom.Y(newP2y);
			ASSERT(fTop.Y() <= fBottom.Y());
		}

	/**	@return the left point.
	*/
	const PMReal& Left() const
		{
			return fTop.X() > fBottom.X() ? fBottom.X() : fTop.X();
		}
	/**	@return the left point.
	*/
	PMReal& Left()
		{
			return fTop.X() > fBottom.X() ? fBottom.X() : fTop.X();
		}
	/**	Set the new left value
		@param newLeft specifies the new left value.
	*/
	void Left(const PMReal& newLeft)
		{
			if (fTop.X() > fBottom.X())
			{
				// The left point was also the bottom point.  Will it still be?
				ASSERT_MSG(fTop.X() >= newLeft, "Swapping left and right points. Is this really what you want?");
				fBottom.X(newLeft);
			}
			else
			{
				ASSERT_MSG(newLeft <= fBottom.X(), "Swapping left and right points. Is this really what you want?");
				fTop.X(newLeft);
			}
		}

	/**	@return the right point.
	*/
	const PMReal& Right() const
		{
			return fTop.X() > fBottom.X() ? fTop.X() : fBottom.X();
		}
	/**	@return the right point.
	*/
	PMReal& Right()
		{
			return fTop.X() > fBottom.X() ? fTop.X() : fBottom.X();
		}
	/**	Set the new right value
		@param newRight specifies the new right value.
	*/
	void Right(const PMReal& newRight)
		{
			if (fTop.X() > fBottom.X())
			{
				// The right point was also the top point.  Will it still be?
				ASSERT_MSG(newRight >= fBottom.X(), "Swapping left and right points. Is this really what you want?");
				fTop.X(newRight);
			}
			else
			{
				ASSERT_MSG(fTop.X() <= newRight, "Swapping left and right points. Is this really what you want?");
				fBottom.X(newRight);
			}
		}

	/**	Set the new x values for top and bottom points.
		@param x1 is the x value for the top point.
		@param x2 is the x value for the bottom point.
	*/
	void SetX(const PMReal& x1, const PMReal& x2)
		{
			fTop.X(x1);
			fBottom.X(x2);
		}

	/**	Set the new top and bottom value for the points.
		@param y1 is the new top value for the top point.
		@param y2 is the new bottom value for the bottom point.
	*/
	void SetY(const PMReal& y1, const PMReal& y2)
		{
			ASSERT(y1 <= y2);

			fTop.Y(y1);
			fBottom.Y(y2);
		}

	/**	Turn the line segment to a horizontal line that passes through x1 and x2.
		@param x1 is the new left value for the horizontal line.
		@param x2 is the new right value for the horizontal line.
	*/
	void SetHorizontal(const PMReal& x1, const PMReal& x2)
		{
			fTop.X(x1);
			fBottom.X(x2);
			fTop.Y(0.);
			fBottom.Y(0.);
		}

	/**	Turn the line segment to a vertical line that passes through y1 and y2.
		@param y1 is the new top value for the vertical line.
		@param y2 is the new bottom value for the vertical line.
	*/
	void SetVertical(const PMReal& y1, const PMReal& y2)
		{
			ASSERT(y1 <= y2);

			fTop.X(0.);
			fBottom.X(0.);
			fTop.Y(y1);
			fBottom.Y(y2);
		}

	/**	Move the line segmenet by delta amount in both x and y direction.
		@param dx the amount in x position to move.
		@param dy is the amount in y position to move.
		@return the new line segment.
	*/
	PMLineSeg& MoveRel(const PMReal& dx, const PMReal& dy)
	{
		if (dx != 0.)
		{
			fTop.X() += dx;
			fBottom.X() += dx;
		}
		if (dy != 0.)
		{
			fTop.Y() += dy;
			fBottom.Y() += dy;
		}
		return *this;
	}

	/**	Move the line segmenet by delta amount in both x and y direction specified by point.
		@param point the amount to move.
		@return the new line segment.
	*/
	PMLineSeg& MoveRel(const PMPoint& point)
	{
		MoveRel(point.X(), point.Y());
		return *this;
	}

	// Comparison operator
	/**	Return true if two PMLineSeg are equal.
		@param a is first line segment.
		@param b is second line segment.
		@return true if a and b are equal.
	*/
	friend PUBLIC_DECL bool16 operator ==(const PMLineSeg& a, const PMLineSeg& b);
	/**	Return true if two PMLineSeg are not equal.
		@param a is first line segment.
		@param b is second line segment.
		@return true if a and b are not equal.
	*/
	friend PUBLIC_DECL bool16 operator !=(const PMLineSeg& a, const PMLineSeg& b);

private:
	PMPoint		fTop;
	PMPoint		fBottom;
};

#pragma export off

//----------------------------------------------------------------------------------------
// Inlines:
//----------------------------------------------------------------------------------------

inline bool16 operator ==(const PMLineSeg& a, const PMLineSeg& b)
{
	return a.TopPoint() == b.TopPoint() && a.BottomPoint() == b.BottomPoint();
}

inline bool16 operator !=(const PMLineSeg& a, const PMLineSeg& b)
{
	return a.TopPoint() != b.TopPoint() || a.BottomPoint() != b.BottomPoint();
}

#endif
 
