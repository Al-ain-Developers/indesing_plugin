//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IOutlineInfo.h $
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
#ifndef __IOutlineInfo__
#define __IOutlineInfo__
#include "PMReal.h"

/**
 Abstract class passed to callback functions on various interfaces where path 
 information is required. Defines a basic set of operations for paths in the
 Adobe imaging model.
 
 BeginPath is called to start a path, followed by a series of moveto, lineto,
 curveto, and closepath calls for the path's subpaths. EndPath is then called
 to end the path.
 
 Note: This is not a standard interface and is *not* reference counted.
 
 @see IPathGeometry::GetOutlineInfo
 @see IHandleShape::GetControlPointPathOutlineInfo
 @see IPathPageItem::GetOutlineInfo
 @see IRasterPort::GetPathInfo
 @see IOffsetPath::OffsetPath
 @see IPathStorage::GetPathInfo
 */
class IOutlineInfo
{
	public:
		/**
		 Begins a new path. Called before any of the other methods is called.
		 */
		virtual void BeginPath() = 0;
		
		/**
		 Ends a path begun by BeginPath.
		 */
		virtual void EndPath() = 0;
		
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
