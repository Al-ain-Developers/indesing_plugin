//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMLine.h $
//  
//  Owner: Jeff Argast
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
//  Your basic line class.  Encapsulates the equation for a line,
//  solves for x, solves for y, and handles intersection testing.
//  
//========================================================================================

#pragma once
 #ifndef __PMLine__
 #define __PMLine__
 
 class PMPoint;
 
#pragma export on
 
/**	A C++ class for dealing with lines. A PMLine is specified by a slope, x and/or y intercept.
*/
class PUBLIC_DECL PMLine
 {
 public:
	
	/**	The default constructor makes no assumptions about what a default line is.
	*/
	PMLine();
	
	/**	Construct a line from the given slope and y intercept.
		@param slope specifies the slope.
		@param yIntercept is the y intercept.
	*/
	PMLine (const PMReal& slope, const PMReal& yIntercept); 
	
	/**	Construct a line with x intercept. 
		In this case, the line has an infinite slope, i.e. x = some constant.
		@param xIntercept is the x intercept.
	*/
 	PMLine (const PMReal& xIntercept);
	
	/**	Construct a line that passes between the two given points.
		If P1 == P2 the line is undefined.
		@param P1 is the first point.
		@param P2 is the second point.
	*/
	PMLine (const PMPoint& P1, const PMPoint& P2);
	
	/**	Returns true if the solution for Y given X exists. Fills in Y.
		@param X is the given x value.
		@param Y is solution for the given x value.
		@return true if solution for y exists.
	*/
	bool16 SolveForY (const PMReal& X, PMReal* Y) const;
	
	/**	Returns true if the solution for X given Y exists. Fills in X.
		@param Y is the given y value.
		@param X is solution for the given y value.
		@return true if solution for X exists.
	*/
	bool16 SolveForX (const PMReal& Y, PMReal* X) const;
	
	/**	Returns the line that is perpendicular to this line and
		passes through the given point.
		@param P is the point the perpendicular line will pass through.
		@return the perpendicular line.
	*/
	PMLine SolveForPerpendicularLine (const PMPoint& P) const;
	
	/**	Returns whether or not the lines intersect, and if they do,
		fills in the intersect point.  If the two lines are
		equal the following call will return kFalse even though
		the two lines intersect at every point.
		@param otherLine is the line to check for interception.
		@param intersectPt is the resulting intersecting point.
		@return true if lines intersect.
	*/
	bool16 SolveForIntersectPoint (const PMLine& otherLine, PMPoint* intersectPt) const;

	/**	Finds the intersecting point that lies between P1 and P2 if it exists
		Essentially the same as the above method but puts constraints on the answer.
		@param P1 is the first point.
		@param P1 is the second point.
		@param intersectPt is the resulting intersecting point.
		@return true if line defined by P1 and P2 intersect this line between P1 and P2.
	*/
	bool16 SolveForIntersectPoint (const PMPoint& P1, const PMPoint& P2, PMPoint* intersectPt) const;
	
	/**	Return the slope of the line. 
		@param pSlope is the slope of the line.
		@return true if the slope is infinite, otherwise it returns kFalse
	*/
	bool16 GetSlope (PMReal* pSlope) const;

	/**	Find the point on the line that is dist distance away from P0.  Returns true if
		a solution exists.  When there are two solutions (which is most of the time)
		it picks the one farthest away from refPoint.
		@param P0 is the anchor point.
		@param dist specifies the distance from P0.
		@param refPoint is the reference point.
		@param retPt is the point on the line.
		@return true if a solution exists.
	*/
	bool16 FindPointOnLine (const PMPoint& P0, const PMReal& dist, const PMPoint& refPoint, PMPoint* retPt) const;
	
	/**	Returns kTrue if the line contains the given point.
		@param point is the point to check.
		@return true if point is on the line.
	*/
	bool16 ContainsPoint(const PMPoint& point) const;
	
	// Comparison operator
	/**	Return true if two lines are equal.
		@param a is line a.
		@param b is line b.
		@return true if line a and b are equal.
	*/
	friend PUBLIC_DECL bool16 operator ==(const PMLine& a, const PMLine& b);
	/**	Return true if two lines are not equal.
		@param a is line a.
		@param b is line b.
		@return true if line a and b are not equal.
	*/
	friend PUBLIC_DECL bool16 operator !=(const PMLine& a, const PMLine& b);
	
private:
	PMReal	fSlope;
	PMReal	fYIntercept;
	PMReal	fXIntercept;
	bool16	fSlopeIsInfinite;
	bool16	fUndefined; // for those rare cases when the line can't be solved for
};
 
 #pragma export off
 
 #endif
 