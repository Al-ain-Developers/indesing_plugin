//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathStorage.h $
//  
//  Owner: Jack Kirstein
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
#ifndef __IPathStorage__
#define __IPathStorage__

#include "IPMUnknown.h"
#include "GraphicsID.h"
#include "PMReal.h"
class IViewPort;
class IOutlineInfo;

/**
 Interface to be used to store an Adobe imaging model path in an in-memory
 data structure. The basic path API is similar to that exposed by IOutlineInfo.
 
 @see IOutlineInfo
 */
class IPathStorage : public IPMUnknown
{
	public:
		/**
		 Replays the path stored by this object into the specified viewport.
		 Assumes that the viewport has an aggregated IGraphicsPort.
		 
		 @param dstPort		IN The port into which the path is played
		 @see IGraphicsPort
		 */
		virtual void ReplayPath(IViewPort* dstPort) = 0;
		
		/**
		 Captures the path currently stored in the specified viewport. Assumes
		 that the viewport has an aggregated IRasterPort.
		 
		 @param srcPort		IN The port from which the path is captured
		 @see IRasterPort
		 */
		virtual void CapturePath(IViewPort* srcPort) = 0;
		
		/**
		 Clears the path stored by this object.
		 */
		virtual void ClearPath() = 0;
		
		/**
		 Gets the path stored by this object using an IOutlineInfo glue object
		 to capture the path.
		 
		 @param callBack	IN The outline info called back on as the path is gotten
		 */
		virtual void GetPathInfo(IOutlineInfo* callBack) = 0;
		
		/**
		 Returns the number of segments in the path stored by this object
		 
		 @return The number of segments in the stored path
		 */
		virtual int32 GetNumPathSegs() = 0;
		
		/**
		 Starts a new subpath. The current point in user space is set to (x, y).
		 
		 @param x		IN The x-component of the new current point
		 @param y		IN The y-component of the new current point
		 */
		virtual void moveto(const PMReal& x, const PMReal& y) = 0;
		
		/**
		 Adds a line segment to the current subpath. The beginning of the 
		 segment is the current point in user space at the time the call is 
		 made. The end is (x, y). Implicitly sets the current point to (x, y).
		 
		 @param x		IN The x-component for the end point of the new line segment
		 @param y		IN The y-component for the end point of the new line segment
		 */
		virtual void lineto(const PMReal& x, const PMReal& y) = 0;
		
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
		virtual void curveto(const PMReal& x1, const PMReal& y1, const PMReal& x2, const PMReal& y2, const PMReal& x3, const PMReal& y3) = 0;

		/**
		 Closes the current subpath. If the first point in the subpath (defined 
		 by a prior call to moveto) does not correspond to the current point, 
		 this call will implicitly add a line segment from the current point to
		 the first point in the subpath.
		 
		 The current point is undefined after a call to closepath. The caller
		 must call moveto to start a new subpath and establish the current 
		 point before calling either lineto, curveto, or closepath.
		 */
		virtual void closepath() = 0;
};
#endif