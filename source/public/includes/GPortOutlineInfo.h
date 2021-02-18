//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GPortOutlineInfo.h $
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
//========================================================================================

#pragma once
#ifndef __GPortOutlineInfo__
#define __GPortOutlineInfo__
 
#include "IOutlineInfo.h"

class IGraphicsPort;
 
#pragma export on

/**
 Concrete implementation of IOutlineInfo. Intended to be used as a glue class
 for converting information from IPathGeometry and other interfaces that use
 IOutlineInfo into calls on an IGraphicsPort.
 
 @see IOutlineInfo
 @see IGraphicsPort
 @see IPathGeometry
 */
class PUBLIC_DECL GPortOutlineInfo : public IOutlineInfo
{
public:
	/**
	 Constructs a GPortOutlineInfo on the specified IGraphicsPort.
	 
	 Note: Calls AddRef on the IGraphicsPort
	 
	 @param gPort		IN The graphics port on which path operations are made
	 */
	GPortOutlineInfo(IGraphicsPort* gPort);
	
	/**
	 Destructs this GPortOutlineInfo.
	 
	 Note: Calls Release on its IGraphicsPort
	 */
	~GPortOutlineInfo();
	
	/**
	 Begins a new path. Called before any of the other methods is called.
	 */
	virtual void 		BeginPath();
	
	/**
	 Ends a path begun by BeginPath.
	 */
	virtual void		EndPath();
	
	/**
	 Starts a new subpath. The current point in user space is set to (x, y).
		 
	 @param x		IN The x-component of the new current point
	 @param y		IN The y-component of the new current point
	 */
	virtual void 		moveto(const PMReal& x, const PMReal& y);

	/**
	 Adds a line segment to the current subpath. The beginning of the 
	 segment is the current point in user space at the time the call is 
	 made. The end is (x, y). Implicitly sets the current point to (x, y).
	 
	 @param x		IN The x-component for the end point of the new line segment
	 @param y		IN The y-component for the end point of the new line segment
	 */
	virtual void 		lineto(const PMReal& x, const PMReal& y);

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
	virtual void 		curveto(const PMReal& x1, const PMReal& y1, const PMReal& x2, const PMReal& y2, const PMReal& x3, const PMReal& y3);

	/**
	 Closes the current subpath. If the first point in the subpath (defined 
	 by a prior call to moveto) does not correspond to the current point, 
	 this call will implicitly add a line segment from the current point to
	 the first point in the subpath.
	 
	 The current point is undefined after a call to closepath. The caller
	 must call moveto to start a new subpath and establish the current 
	 point before calling either lineto, curveto, or closepath.
	 */
	virtual void 		closepath();
	
private:
	IGraphicsPort *		fPort;
	bool16				fBeginPathCalled;
};

#pragma export off

#endif

