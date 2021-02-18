//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMPathPoint.h $
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
//  
//  A Generic class that describes a line point or a Bezier knot
//  
//========================================================================================

#pragma once
#ifndef __PMPathPoint__
#define __PMPathPoint__

#include "PMPoint.h"
#include "PathTypes.h"

class IPMStream;
class PMRect;
class PMPathPoint;
class PMMatrix;

typedef PMPathPoint PBPMPathPoint ;	// path point in "Pasteboard" PMRealinates
typedef K2Vector<PMPathPoint> PMPathPointList;

#pragma export on

/**	Data class for a InDesign path point.
*/
class PUBLIC_DECL PMPathPoint
{
public: 
   typedef base_type data_type;

	/**	Constructs a line path point at 0,0.
	*/
    constexpr PMPathPoint() noexcept : fAnchorType(kL), fLeftDirPt(0,0), fRightDirPt(0,0), fAnchorPt(0,0)
    {}
	
	/**	Construct a path point of type PMPathPointType fromt a list of points.  
		If pointType is kL, ptList.Length() == 1.
		If pointType is kCS or kCK ptList.Length() == 3.  For both kCS and kCK the first
		point is the left dir pt, the second point is the anchor point, and the third
		point is the right dir pt.
		@param pointType specifies the path point type. @see PathTypes.h
		@param ptList is the list of points.
	*/
	PMPathPoint (PMPathPointType pointType, const PMPointList& ptList);
	
	/**	Construct a path point of type PMPathPointType.
		If pointType is kL, only leftDirPt needs to be specified.
		For both kCS and kCK, three points are required.
		@param pointType specifies the path point type. @see PathTypes.h
		@param leftDirPt is the first point.
		@param anchorPt is the second point.
		@param rightDirPt is the third point.
	*/
	PMPathPoint (PMPathPointType pointType, const PMPoint& leftDirPt, const PMPoint& anchorPt, const PMPoint& rightDirPt);

	/**	Construct a path point heuristically.  If the length of ptList is 1 then create
		a line (kL) path point.  If the length of ptList is 3 then create a kCS if the
		direction points are on the same line, or create a kCK if the direction points
		are discontinuous.  If length is 3 the order is leftDirPt, anchorPt, rightDirPt.
		@param ptList is the list of at least one point or at most three points.
	*/
	PMPathPoint (const PMPointList& ptList);

	/**	Construct a line path point
	*/
	PMPathPoint (const PMPoint& linePt) noexcept;
	
	/**	Construct a curve pt, determining kCK or kCS from the direction points
	*/
	PMPathPoint (const PMPoint& leftDirPt, const PMPoint& anchorPt, const PMPoint& rightDirPt);
	
	/**	@return the point at the given index.
	*/
	const PMPoint& GetPoint (PathPointIndex ptIndex) const;
	
	/**	@return the left direciton point.
	*/
	const PMPoint& GetLeftDirPoint () const noexcept;
	/** @return the anchor point.
	*/
	const PMPoint& GetAnchorPoint () const noexcept;
	/**	@return the right direction point.
	*/
	const PMPoint& GetRightDirPoint () const noexcept;
	
	/**	Returns the anchor type. This should be one of kL, kCS, or kCK.
		@see PathTypes.h
	*/
	PMPathPointType GetAnchorType() const noexcept;
	
	/**	Modify the point. The point is modified so that the entire path point
		fits inside the constrain rectangle. bMirrorPt is ignored if the ptIndex
		points to an anchor point. 
		If ptIndex points to a direction point and the anchor point is kCS then
		the other direction point is mirrored.
		if ptIndex points to a direction point, bMirrorPt is false, and the
		anchor point is kCS, them the other direction point is projected onto
		the tangent line.
		@param ptIndex is the path point index to modify.
		@param newPoint is the new point to set to.
		@param bMirrorPt is ignored if ptIndex points to an anchor point.
		@param constrainRect is the constraining rectangle.
	*/
	void ModifyPoint 
		(
			PathPointIndex ptIndex,
			const PMPoint& newPoint,
			bool16 bMirrorPt = kFalse,
			PMRect* constrainRect = nil
		);

	/**	Generally you will want to use ModifyPoint to get the expected behavior for the UI,
		but sometimes you just want to directly set the point.
	*/

	/**	Sets the point index with the new point.
		@param ptIndex is the point index to set.
		@param newPoint is the new point to set to.
	*/
	void SetPoint( PathPointIndex ptIndex, const PMPoint& newPoint );
	/**	Sets the left direction point with the specified new point.
		@param newPoint is the new point to set to.
	*/
	void SetLeftDirPoint( const PMPoint& newPoint ) noexcept;
	/**	Sets the anchor point with the specified new point.
		@param newPoint is the new point to set to.
	*/
	void SetAnchorPoint( const PMPoint& newPoint ) noexcept;
	/**	Sets the right direction point with the specified new point.
		@param newPoint is the new point to set to.
	*/
	void SetRightDirPoint( const PMPoint& newPoint ) noexcept;

	/**	Set right direction point to location of left direciont pt and vice versa
	*/
	void Flip();
	
	/**	Change the type of the anchor point.  If changing to a kL, it removes the extra
		direction points, if changing to a kCS or kCK from kL it creates the direction
		points equal to the anchor point.
		@param newType is the type of anchor point to change to.
	*/
	void ModifyAnchorType (PMPathPointType newType);
	
	/**	Returns the bounding box of the point.  If a single point the bbox is
		empty centered on the point.
		@return the bounding box of the point.
	*/
	PMRect GetBoundingBox() const;
	 
	/**	Transform the points with the given matrix.
		@param xForm is the matrix to transform with.
	*/
	void TransformPoints (const PMMatrix& xForm);
	
	/**	Return the point that falls inside of hitRect. The anchor point is checked first before direction handles.
		@param hitRect is the rectangle to test.
		@param whichPt is the index of the path point to test.
		@param handleSize is the optional parameter inciating the size of the relevant handles.
		@return kTrue if point falls inside of hitRect. Otherwise returns kFalse.
	*/
	bool16 HitTest( const PMRect& hitRect, PathPointIndex& whichPt, const PMReal& handleSize = 0.0 ) const ;
	
	/**	Read/Write to the specified stream.
		@param iPMStream is the stream to read from or write to.
	*/
	void ReadWrite (IPMStream* iPMStream);

	// Math Operators
	/**	
	*/
	friend PUBLIC_DECL PMPathPoint operator *(const PMReal& c, const PMPathPoint& pt);
	/**
	*/
	friend PUBLIC_DECL PMPathPoint operator *(const PMPathPoint& pt, const PMReal& c);
	/**
	*/
	friend PUBLIC_DECL PMPathPoint operator /(const PMPathPoint& numer, const PMReal& denom);

	// Assignment Operators
	/**
	*/
	void operator *=(const PMReal& a);
	/**
	*/
	void operator /=(const PMReal& a);
	/**
	*/
    PMPathPoint(const PMPathPoint& rhs) noexcept = default;
    PMPathPoint(PMPathPoint&& rhs) noexcept = default;
	PMPathPoint& operator=(const PMPathPoint& rhs) noexcept = default;
    PMPathPoint& operator=(PMPathPoint&& rhs) noexcept = default;

	// Comparison Operators
	/**	Compare two PMPathPoint.
		@return true if two PMPathPoint are equal.
	*/
	friend PUBLIC_DECL bool16 operator ==(const PMPathPoint& a, const PMPathPoint& b) noexcept;
	/**	Compare two PMPathPoint.
		@return true if two PMPathPoint are not equal.
	*/
	friend PUBLIC_DECL bool16 operator !=(const PMPathPoint& a, const PMPathPoint& b) noexcept;
	
private:
	PMPathPointType	fAnchorType;
	PMPoint			fLeftDirPt;	
	PMPoint			fAnchorPt;	
	PMPoint			fRightDirPt;	
};

inline bool16 operator ==(const PMPathPoint& a, const PMPathPoint& b) noexcept
{
    return ( a.fAnchorType == b.fAnchorType &&
            a.fLeftDirPt  == b.fLeftDirPt &&
            a.fAnchorPt   == b.fAnchorPt &&
            a.fRightDirPt == b.fRightDirPt );
}

inline bool16 operator !=(const PMPathPoint& a, const PMPathPoint& b) noexcept
{
    return !(a == b);
}


#pragma export off

#endif
