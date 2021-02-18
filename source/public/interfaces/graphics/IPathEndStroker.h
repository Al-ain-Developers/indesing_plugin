//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathEndStroker.h $
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
//  Defines the interface for end cap drawing.
//  
//========================================================================================

#pragma once
#ifndef __IPathEndStroker__
#define __IPathEndStroker__

#include "IPMUnknown.h"
#include "GraphicsID.h"
#include "RequestContext.h"

class IGraphicsPort;
class PMRect;
class PMPoint;
class IGraphicStyleDescriptor;
class PMMatrix;
class PMString;
class PMPathPoint;

/** 
 IPathStroker defines the interface to be implemented by installable path end strokers
 (i.e., arrowheads)
 */
class IPathEndStroker : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHENDSTROKER };

	/**
	 This enum describes the location of the end cap(s) to draw 
	 */
	enum PathEndLocation 				
		{
			kPathEndAtNeitherEnd 	= 0, 
			kPathEndAtEnd 			= 1, 
			kPathEndAtStart 		= 2, 
			kPathEndAtBothEnds 		= 3
		}; 

	/** 
	 Strokes the end path for a line.  Assume that the correct rendering object 
	 was setup during the stroking of the line except for the no stroke case.  
	 
	 Note: Won't be called if the item has no stroke.
	 
	 @param styleDescriptor		IN The graphic style descriptor to use
	 @param endLocation			IN The location for the path ends
	 @param startPt				IN The starting point for the line
	 @param endPt				IN The ending point for the line
	 @param gPort				IN The port to draw into
	 @see IGraphicStyleDescriptor
	 @see IGraphicsPort
	 */
	virtual void StrokeLineToPathEnd 
		(
			IGraphicStyleDescriptor*	styleDescriptor, 
			int32 						endLocation,
			const PMPoint&				startPt,
			const PMPoint&				endPt,
			IGraphicsPort*				gPort
		) const = 0;
	
	/**
	 Does the rect intersect the path end for a line? 
	 
	 Note: Won't be called if the item has no stroke.
	 
	 @param styleDescriptor		IN The graphic style descriptor to use
	 @param endLocation			IN The location for the path ends
	 @param startPt				IN The starting point for the path end
	 @param endPt				IN The ending point for the path end
	 @param r					IN The rectangle to test
	 @param gPort				IN The port to draw into
	 @return kTrue if the rect intersects, else kFalse
	 @see IGraphicStyleDescriptor
	 @see IGraphicsPort
	 */
	virtual bool16 InLineToPathEnd
		(
			IGraphicStyleDescriptor*	styleDescriptor, 
			int32						endLocation,
			const PMPoint&				startPt,
			const PMPoint&				endPt,
			const PMRect&				r, 
			IGraphicsPort* 				gPort
		) const = 0;

	/**
	 Returns the bounding box of the path end for a line using the supplied matrix
	 If the item has no stroke, compute the bbox using a stroke weight of 0, i.e. 
	 return the bounds of the path
	 
	 @param styleDescriptor		IN The graphic style descriptor to use
	 @param endLocation			IN The location for the path ends
	 @param startPt				IN The starting point for the path end
	 @param endPt				IN The ending point for the path end
	 @param matrix				IN The matrix to transform the bounding box by
	 @return the bounding box
	 @see IGraphicStyleDescriptor
	 */
	virtual PMRect GetLineToPathEndBBox 
		(
			IGraphicStyleDescriptor*	styleDescriptor, 
			int32						endLocation,
			const PMPoint&				startPt,
			const PMPoint&				endPt,
			const PMMatrix&				matrix
		) const = 0;

	/** 
	 Strokes the end path for a curve.  Assume that the correct rendering object 
	 was setup during the stroking of the curve except for the no stroke case.  

	 Note: Won't be called if the item has no stroke.
	 
	 @param styleDescriptor		IN The graphic style descriptor to use
	 @param endLocation			IN The location for the path ends
	 @param P0					IN The curve's first control point
	 @param P1					IN The curve's second control point
	 @param P2					IN The curve's third control point
	 @param P3					IN The curve's fourth control point
	 @param gPort				IN The port to draw into
	 @see IGraphicStyleDescriptor
	 @see IGraphicsPort
	 */
	virtual void StrokeCurveToPathEnd 
		(
			IGraphicStyleDescriptor*	styleDescriptor, 
			int32 						endLocation,
			const PMPoint&				P0,
			const PMPoint&				P1,
			const PMPoint&				P2,
			const PMPoint&				P3,
			IGraphicsPort*				gPort
		) const = 0;
	

	/**
	 Does the rect intersect the path end for a curve? 
	 
	 Note: Won't be called if the item has no stroke.
	 
	 @param styleDescriptor		IN The graphic style descriptor to use
	 @param endLocation			IN The location for the path ends
	 @param P0					IN The curve's first control point
	 @param P1					IN The curve's second control point
	 @param P2					IN The curve's third control point
	 @param P3					IN The curve's fourth control point
	 @param r					IN The rectangle to test
	 @param gPort				IN The port to draw into
	 @return kTrue if the rect intersects, else kFalse
	 @see IGraphicStyleDescriptor
	 @see IGraphicsPort
	 */
	virtual bool16 InCurveToPathEnd
		(
			IGraphicStyleDescriptor*	styleDescriptor, 
			int32						endLocation,
			const PMPoint&				P0,
			const PMPoint&				P1,
			const PMPoint&				P2,
			const PMPoint&				P3,
			const PMRect&				r, 
			IGraphicsPort* 				gPort
		) const = 0;

	/**
	 Returns the bounding box of the path end for a curve using the supplied matrix
	 If the item has no stroke, compute the bbox using a stroke weight of 0, i.e. 
	 return the bounds of the path
	 
	 @param styleDescriptor		IN The graphic style descriptor to use
	 @param endLocation			IN The location for the path ends
	 @param P0					IN The curve's first control point
	 @param P1					IN The curve's second control point
	 @param P2					IN The curve's third control point
	 @param P3					IN The curve's fourth control point
	 @param matrix				IN The matrix to transform the bounding box by
	 @see IGraphicStyleDescriptor
	 @return the bounding box
	 */
	virtual PMRect GetCurveToPathEndBBox 
		(
			IGraphicStyleDescriptor*	styleDescriptor, 
			int32						endLocation,
			const PMPoint&				P0,
			const PMPoint&				P1,
			const PMPoint&				P2,
			const PMPoint&				P3,
			const PMMatrix&				matrix
		) const = 0;

	/**
	 Gets the adjusted path point for stroking a line
	 
	 @param pt0					IN The line's start point
	 @param pt1					IN The line's end point
	 @param styleDescriptor		IN The graphic style descriptor to use
	 @param endLocation			IN The location for the path ends
	 @return desired ending PathPoint
	 @see IGraphicStyleDescriptor
	 */
	virtual PMPathPoint StrokePathEndAdjust 
		(
			const PMPathPoint& pt0, 
			const PMPathPoint& pt1, 
			IGraphicStyleDescriptor* styleDescriptor, 
			int32 endLocation
		) const = 0;

	/**
	 Fills in the text string that describes this type of end
	 
	 @param pathendName		OUT The name of the path end
	 */
	virtual void GetPathEndName
		(
			PMString* pathendName
		) const = 0;

	/**
	 Stroke the end path for UI purposes. Assume that the correct rendering 
	 object was setup during the stroking of the line except for the no stroke 
	 case.  In the no stroke case StrokePathEnd won't be called.

	 @param endLocation			Which end(s) to stroke
	 @param startPt				Start point for line
	 @param endPt				End point for line
	 @param gPort				Port to stroke to
	 @param strokeWidth			Width of the stroke to use
	 @param arrowHeadScale		Percentage Scaling of the arrowHead
	 @see IGraphicsPort
	 */
	virtual void StrokeLineToPathEndForUI
		(
			int32 						endLocation,
			const PMPoint&				startPt,
			const PMPoint&				endPt,
			IGraphicsPort*				gPort,
			const PMReal&				strokeWidth,
			PMReal						arrowHeadScale
		) const = 0;

	/** 
	 Creates the end path for a line. Typically called at a higher level via StrokeLineToPathEnd, but this
	 function allows path end stroking to be done when no IGraphicStyleDescriptor is available, e.g. in an handle shape adornment.
	 
	 @param endLocation			IN The location for the path ends
	 @param startPt				IN The starting point for the line
	 @param endPt				IN The ending point for the line
	 @param gPort				IN The port to draw into
	 @param strokeWidth			IN Width of the stroke to use
	 @param arrowHeadScale		IN Percentage Scaling of the arrowHead
	 @see IGraphicsPort
	 */
	virtual void CreateLineEndPath
		(
			int32 						endLocation,
			const PMPoint&				startPt,
			const PMPoint&				endPt,
			IGraphicsPort*				gPort,
			const PMReal&               strokeWidth,
			PMReal						arrowHeadScale
		) const = 0;

	/** Returns the ScriptID associated with this path end in the given scripting DOM */
	virtual ScriptID GetScriptID( const ScriptInfo::RequestContext& context ) const = 0;
};

#endif
