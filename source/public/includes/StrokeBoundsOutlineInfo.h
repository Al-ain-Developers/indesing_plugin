//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/StrokeBoundsOutlineInfo.h $
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
#ifndef __StrokeBoundsOutlineInfo__
#define __StrokeBoundsOutlineInfo__

#include "IOutlineInfo.h"
#include "PMPoint.h"
#include "PMRect.h"
#include "PMMatrix.h"
#include "PMBezierCurve.h"

const int32 kSegmentWindow = 3;

class IPathEndStroker;

#pragma export on

/**
 Concrete implementation of IOutlineInfo. Intended to be used as a glue class
 for calculating a path's bounding box using information from IPathGeometry and 
 other interfaces that use IOutlineInfo.
 
 Similar to PathBoundsOutlineInfo, but takes into account stroke parameters 
 when calculating bounds, so that returned bounds reflect the bounds that would
 be marked if the path were stroked.
 
 @see IOutlineInfo
 @see PathBoundsOutlineInfo
 */
class PUBLIC_DECL StrokeBoundsOutlineInfo : public IOutlineInfo
{
public:
	/**
	 Constructs a StrokeBoundsOutlineInfo with the specified stroke parameters
	 and a matrix that will used to define the coordinate system for the input 
	 points and the scaling applied to the stroke weight.
	 
	 @param strokeWeight		IN The stroke's weight
	 @param miterLimit			IN The stroke's miter limit
	 @param joinType			IN The stroke's join type
	 @param lineCap				IN The stroke's line cap
	 @param xForm				IN The matrix defining the coordinate system for the input points
	 @param styleDescriptor		IN Style descriptor defining additional relevant stroke parameters (not currently used). Not AddRef'd
	 */
	StrokeBoundsOutlineInfo
	(
		const PMReal&				strokeWeight,
		const PMReal&				miterLimit,
		int32						joinType,
		int32						lineCap,
		const PMMatrix&				xForm,
		IGraphicStyleDescriptor*	styleDescriptor
	);

	/**
	 Returns the computed bounds
	 
	 @return the computed bounds
	 */
	PMRect GetBoundingBox();

	/**
	 Begins a new path. Called before any of the other methods is called.
	 */
	virtual void BeginPath();

	/**
	 Ends a path begun by BeginPath.
	 */
	virtual void EndPath();

	/**
	 Starts a new subpath. The current point in user space is set to (x, y).
		 
	 @param x		IN The x-component of the new current point
	 @param y		IN The y-component of the new current point
	 */
	virtual void moveto(const PMReal& x, const PMReal& y);

	/**
	 Adds a line segment to the current subpath. The beginning of the 
	 segment is the current point in user space at the time the call is 
	 made. The end is (x, y). Implicitly sets the current point to (x, y).
	 
	 @param x		IN The x-component for the end point of the new line segment
	 @param y		IN The y-component for the end point of the new line segment
	 */
	virtual void lineto(const PMReal& x, const PMReal& y);

	/**
	 Adds a new bezier curve segment to the current subpath, using four 
	 control points. The current point in user space at the time the call
	 is made is used as the starting point for the curve. (x1, y1) and
	 (x2, y2) are used as control points defining the degree of curvature 
	 and magnitude of the curve, and (x3, y3) defines the end point. The
	 current point is implicitly set to (x3, y3).
	 
	 @param x1		IN The x-component for the first control point of the new bezier segment
	 @param y1		IN The y-component for the first control point of the new bezier segment
	 @param x2		IN The x-component for the second control point of the new bezier segment
	 @param y2		IN The y-component for the second control point of the new bezier segment
	 @param x3		IN The x-component for the end point of the new bezier segment
	 @param y3		IN The y-component for the end point of the new bezier segment
	 */		 
	virtual void curveto(const PMReal& x1, const PMReal& y1, const PMReal& x2, const PMReal& y2, const PMReal& x3, const PMReal& y3);

	/**
	 Closes the current subpath. If the first point in the subpath (defined 
	 by a prior call to moveto) does not correspond to the current point, 
	 this call will implicitly add a line segment from the current point to
	 the first point in the subpath.
	 
	 The current point is undefined after a call to closepath. The caller
	 must call moveto to start a new subpath and establish the current 
	 point before calling either lineto, curveto, or closepath.
	 */
	virtual void closepath();
		
private:
	StrokeBoundsOutlineInfo(); 

private:
	// Compute the bounds of the one and only segment
	void ComputeSingleSegmentBoundsWithEnds();
	
	// Compute the first segment bounds and include an end calculation
	// at the beginning
	void ComputeFirstSegmentBoundsWithEnd();
	
	// Compute the last segment bounds and include an end calculation
	// at the end.  This assumes the segment to miter with is
	// fNumSegments - 1
	void ComputeLastSegmentBoundsWithEnd();
	
	// Compute the given segment bounds.  Will use whichsegment - 1 as the segment
	// to miter to
	void ComputeSegmentBounds (int32 whichSegment);
	
	// Compute a single closed segment bounds.  There is only one segment in this
	// case and no end calculations
	void ComputeSingleSegmentBounds();
	
	// Compute the first segment bounds assuming the path is closed.  Use the last segment
	// to miter with
	void ComputeFirstSegmentBounds();
	
	// Compute the bounds of the Bezier
	void ComputeBezierBounds(PMPoint* ptList);
	
	// Compute the bounds of the line
	void ComputeLineBounds(const PMPoint& P0, const PMPoint& P1);
	
	// Compute the miter point
	void ComputeMiterBounds 
		(
			PMPoint* B,
			int32 segmentType,
			int32 previousSegment
		);
	
	// Compute the miter point
	void ComputeRoundJoinBounds 
		(
			PMPoint* B,
			int32 segmentType,
			int32 previousSegment
		);
	
	// Compute the bbox for the starting path end
	void ComputeStartPathEnd (PMPoint* ptList, int32 segType);
	
	// Compute the bbox for the ending path end
	void ComputeEndPathEnd (PMPoint* ptList, int32 segType);
	
	// Single method that both of the above call.  Passes in start pt and end pt	
	void ComputePathEnd (const PMPoint& Pfrom, const PMPoint& Pto);
	
	// Compute bounds at the given param location
	void ComputeCurveBounds (const PMBezierCurve& bezCurve, const PMReal& u);
	
private:
	IGraphicStyleDescriptor*	fStyleDescriptor;

	PMPoint fFirstSegmentStorage[4];
	int32   fFirstSegmentType;
	
	PMPoint fSegmentStorage[kSegmentWindow][4]; // Three segments, each having up to 4 points
	int32 	fSegmentType[kSegmentWindow];
	
	int32	fNumSegments;
	
	PMReal	fLastX, fLastY;
	PMReal	fFirstX, fFirstY;
	
	// The following values comprise the bounds
	PMRect	fBounds;
	
	bool16	fBoundsSet;

	bool16	fStartedWithMoveTo;
	bool16	fComputeBoundsForFirstSegment;
	bool16	fComputeBoundsForLastSegment;
	
	PMMatrix	fXform;
	PMMatrix	fStrokeMat;
	bool16		fIsMatrixIdentity;
	
	int32	fJoinType;
	int32	fLineCap;
	PMReal	fMiterLimit;
	
	PMReal	fStrokeWeight;
	PMReal	fHalfStrokeWeight;
	PMReal	fXStrokeWeight;
	PMReal	fYStrokeWeight;
	
	// temp storage for line methods
	PMPoint	fP0, fP1, fP2, fP3;
	
	// temp storage for curve methods
	PMBezierCurve fCurve1, fCurve2;
};

#pragma export off

#endif

