//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMBezierCurve.h $
//  
//  Owner: jargast
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
#ifndef __PMBezierCurve__
#define __PMBezierCurve__

#include "PMPoint.h"

class IPMStream;
class PMRect;
class PMBezierCurve;
class PMMatrix;
class PMPathPoint;

typedef K2Vector<PMBezierCurve> PMBezierCurveList;

#pragma export on

/**	A C++ class for Bezier curve. The Bezier curve is defined by 4 points.
*/
class PUBLIC_DECL PMBezierCurve
{
public: 
	typedef base_type data_type;
	/**	Constructs an empty Bezier.
	*/
	PMBezierCurve();
	
	/**	Contructs a Bezier from four points.
		@param P0 is the first point.
		@param P1 is the second point.
		@param P2 is the third point.
		@param P3 is the fourth point.
	*/
	PMBezierCurve (const PMPoint& p0, const PMPoint& p1, const PMPoint& p2, const PMPoint& p3);
	
	/**	Constructs a Bezier from two points.  This will make p0 = p1 and p2 = p3
		@param p0p1 the first point.
		@param p2p3 is the second point.
	*/
	PMBezierCurve (const PMPoint& p0p1, const PMPoint& p2p3);
	
	/**	Construct a degenerate curve where p0 = p1 = p2 = p3
		@param p is the point.
	*/
	PMBezierCurve (const PMPoint& p);
	
	// Quick accesors
	/**	@return the first point.
	*/
	const PMPoint& GetP0() const { return fP0; }
	/**	@return the second point.
	*/
	const PMPoint& GetP1() const { return fP1; }
	/**	@return the third point.
	*/
	const PMPoint& GetP2() const { return fP2; }
	/**	@return the fourth point.
	*/
	const PMPoint& GetP3() const { return fP3; }
	
	/**	Return the point at the given index, 0 <= n <= 3
		@param n is the index.
	*/
	const PMPoint& GetNthPoint (int32 n) const;
	
	// Quick ways to set the points. 
	/**	Sets the first point to p.
		@param p specifies the new first point.
	*/
	void SetP0 (const PMPoint& p) { fP0 = p; }
	/**	Sets the second point to p.
		@param p specifies the new second point.
	*/
	void SetP1 (const PMPoint& p) { fP1 = p; }
	/**	Sets the third point to p.
		@param p specifies the new third point.
	*/
	void SetP2 (const PMPoint& p) { fP2 = p; }
	/**	Sets the fourth point to p.
		@param p specifies the new fourth point.
	*/
	void SetP3 (const PMPoint& p) { fP3 = p; }
	
	// Use index
	/**	Sets the nth point to p.
		@param n is the index of the point.
		@param p is the new point.
	*/
	void SetNthPoint (int32 n, const PMPoint& p);
	
	/**	Return the bounding box of the curve including control points.
		If a single point the bbox is empty centered on the point.
		@return the bounding box of the curve.
	*/
	PMRect GetCtrlPtBounds() const;
	
	/**	Returns the bounds of the path. This does not include the control points
		@return the bounding box of the path not including control points.
	*/
	PMRect GetPathBounds() const;
	
	/**	Transform the curve with the given matrix
		@param xForm is the matrix to transform by.
	*/
	void TransformPoints (const PMMatrix& xForm);
		
	/**	Returns whether the point is within hit zone of the curve. If so, it fills
		out the parameter location.
		@param p is the point to check.
		@param hitzone is the hit zone.
		@param retU ?
		@return true if point is within the hit zone of the curve.
	*/
	bool16 FindParameter (const PMPoint& p, const PMReal& hitzone, PMReal* retU) const;
	
	/**	Evaluate the curve at the given parameter.
		@param u is the parameter where 0 <= u <= 1.0
	*/
	PMPoint Evaluate (const PMReal& u) const;
	
	/**	Find the slope at the given u.
		@param u
	*/
	PMPoint EvaluateSlope (const PMReal& u) const;
	
	/**	This is faster than calling Evaluate and EvaluateSlope separately.
	*/
	void EvaluatePointAndSlope (const PMReal& u, PMPoint* outP, PMPoint* outSlope) const;
	
	/**	Returns a step value that when passed into FlattenCurve will result in the given flatness.
		@param flatness is the desired flatness, where 0 < flatness <= 1.0
	*/
	int32 GetStepSize (const PMReal& flatness) const;
	
	/**	Convert the Bezier to (1 << stepSize) + 1 number of points.
		@param pts is the resulting points.
		@param stepSize is the step size.
	*/
	void FlattenCurve (PMPoint* pts, int32 stepSize);
	
	/**	Find the min and max paramesters. 
		Returns the number of paramesters found.  Max is 4.
		FindMinMax does not check param == 0.0 or param == 1.0
		@param uResult contains the resulting parameters.
		@return the number of paramesters.
	*/
	int32 FindMinMax (PMReal* uResult) const;

	/**	Subdivide curve into two other curves at the given parameter.
		@param u is the parameter.
		@param bezLeft is the resulting left bezier.
		@param bezRight is the resulting right bezier.
	*/
	void SubDivide (const PMReal& u, PMBezierCurve* bezLeft, PMBezierCurve* bezRight) const;
	
	/**	Take a segment from begU to endU.
		@param begU
		@param endU
		@param subSegment is the resulting bezier from begU and endU.
	*/
	void SubSegment (const PMReal& begU, const PMReal& endU, PMBezierCurve* subSegment) const;
	
	/**	Divide the curve at u and return the path points representing the curve.
	*/
	void DivideIntoPathPoints 
		(
			const PMReal u,
			PMPathPoint* ptBefore,
			PMPathPoint* ptAt,
			PMPathPoint* ptAfter
		);

	// persistance
	/**	Read/Write bezier from/to given stream.
		@param iPMStream is the stream.
	*/
	void ReadWrite (IPMStream* iPMStream);

	// Math Operators
	friend PUBLIC_DECL PMBezierCurve operator *(const PMReal& c, const PMBezierCurve& pt);
	friend PUBLIC_DECL PMBezierCurve operator /(const PMBezierCurve& numer, const PMReal& denom);

	// Assignment Operators
	void operator *=(const PMReal& a);
	void operator /=(const PMReal& a);
	PMBezierCurve& operator=(const PMBezierCurve& rhs);

	// Comparison Operators
	/**	Compare two PMBezierCurve
		@param a is one beszier curve.
		@param b is the other bezier curve.
		@return true it a and b are equal.
	*/
	friend PUBLIC_DECL bool16 operator ==(const PMBezierCurve& a, const PMBezierCurve& b);
	/**	Compare two PMBezierCurve
		@param a is one beszier curve.
		@param b is the other bezier curve.
		@return true it a and b are not equal.
	*/
	friend PUBLIC_DECL bool16 operator !=(const PMBezierCurve& a, const PMBezierCurve& b);

	// Utility methods
	
	/**	Reduce the Bezier.  The equation for this method is
							P = A*(1-u) + B*u
	*/
	static void Reduce (PMPoint* P, const PMPoint& A, const PMPoint& B, const PMReal& u);

public:
	PMReal PrivateFindParameter 
		(
			const PMReal& startP, 
			const PMReal& endP, 
			const PMReal& coord, 
			bool16 isXCoord, 
			bool16* oneCrossing
		) const ;

	PMReal FindParameterByAverage
		(
			PMReal t0,
			PMReal t1,
			const PMPoint& p
		) const ;

	/**	Returns whether the given rectangle intersects the curve.
		@param r is the rectangle to test.
		@return true if given rectangle intersects the curve.
	*/
	bool16 HitTest( const PMRect& r ) const ;

	/**
	*/
	int16 AdjustToPassThroughPoint( const PMPoint& p, const PMReal& t ) ;
	
	/**	Defines the return values for AdjustThroughPoint
	*/
	enum {	
		kBezierAdjustReflectedp1 =	1,	/**	same slope, but opposite side of p0 */
		kBezierAdjustReflectedp2 =	2,	/**	same slope, but opposite side of p3 */
		kBezierAdjustRotatedp1 =	4,	/**	p0 to p1 has different slope */
		kBezierAdjustRotatedp2 =	8	/**	p3 to p2 has different slope */
	} ;

	/**
	*/
	bool16 PreAdjustCurve(
		const PMReal& t,					// input
		PMPoint& t0, PMPoint& t3,			// output
		PMPoint& c,							// output
		PMPoint& d, PMPoint& e ) const ;	// output
	/**
	*/
	int16 DoAdjustCurve(
		const PMPoint& m,
		const PMReal& t,
		const PMPoint& t0, const PMPoint& t3,
		const PMPoint& c, const PMPoint& d, const PMPoint& e,
		bool16 parallel ) ;

protected:
	PMPoint	fP0;
	PMPoint	fP1;
	PMPoint	fP2;
	PMPoint	fP3;
};


#pragma export off

#endif
