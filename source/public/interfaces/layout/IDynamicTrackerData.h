//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDynamicTrackerData.h $
//  
//  Owner: Richard Rodseth
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
//  Purpose: Notifies document observers during tracking. Used by the Transform Panel
//  to update fields during creation tracking. In some cases, non-dynamic trackers use this
//  interface to notify (e.g. column tracker, zero point tracker, zoom tool tracker, but
//  all these trackers don't affect the selection. For trackers that operate on the selection,
//  (e.g. move, scale, resize, etc), they notify via dynamic commands. 
//  
//========================================================================================

#pragma once
#ifndef __IDynamicTrackerData__
#define __IDynamicTrackerData__

#include "PMPoint.h"

class IDynamicTrackerData : public IPMUnknown
{
public:

	enum TrackingState { kNotTracking, kBeginTracking, kContinueTracking, kEndTracking, kAbortTracking };
	enum TrackingEffect 
	{ 
		kAffectsNone= 0,
		kAffectsX 	= 1,
	 	kAffectsY 	= 2,
	  	kAffectsXY 	= kAffectsX | kAffectsY,
	 	kAffectsW 	= 4,
		kAffectsXW	= kAffectsX | kAffectsW,
	 	kAffectsH	= 8,
		kAffectsYH	= kAffectsY | kAffectsH,
	 	kAffectsXYW	= kAffectsXY | kAffectsW,
	 	kAffectsXYH	= kAffectsXY | kAffectsH,
	 	kAffectsWH  = kAffectsW | kAffectsH,
	 	kAffectsXYWH = kAffectsXY | kAffectsWH,
	 	kAffectsL	= 16,
		kAffectsWHL = kAffectsWH | kAffectsL,	//Bug# 1399913 - for measure tool tracker
		kAffectsXYWHL = kAffectsXY | kAffectsWH | kAffectsL,	// Line tracker broadcasts this
	 	kAffectsD1	= kAffectsL,	// Same as kAffectsL
		kAffectsXYL  = kAffectsXY | kAffectsL,
		kAffectsXYD1  = kAffectsXYL,	// Same as kAffectsXYL
		kAffectsD2	= 32,
		kAffectsXYD2  = kAffectsXY | kAffectsD2,
		kAffectsDeltaX = 64,	// Dragging points in path selection
		kAffectsDeltaY = 128,
		kAffectsDeltaXDeltaY = kAffectsDeltaX | kAffectsDeltaY,
		kAffectsXYDeltaX = kAffectsXY | kAffectsDeltaX,
		kAffectsXYDeltaY = kAffectsXY | kAffectsDeltaY,
		kAffectsXYDeltaXDeltaY = kAffectsXY | kAffectsDeltaX | kAffectsDeltaY,
		kMarqueeSelection = 256,	// Dragging in marquee selection

		kAffectsScaleX = 512,
		kAffectsScaleY = 1024,
		kAffectsSkewAngle = 2048,
		kAffectsRotationAngle = 4096,
		kAffectsTransform = kAffectsScaleX | kAffectsScaleY | kAffectsSkewAngle | kAffectsRotationAngle,
		
		kUnknown = 32768
	};

	virtual void NotifyBeginTracking(const PBPMPoint& startPoint, 
									 const TrackingEffect& effect) = 0;
									 
	virtual void NotifyContinueTracking(const PBPMPoint& startPoint, 
										const PBPMPoint& endPoint, 
										const TrackingEffect& effect) = 0;

	virtual void NotifyContinueTracking(const PBPMPoint& startPoint, 
										const PBPMPoint& middlePoint,
										const PBPMPoint& endPoint, 
										const TrackingEffect& effect) = 0;
										
	virtual void NotifyEndTracking(const PBPMPoint& startPoint,
								   const PBPMPoint& endPoint, const TrackingEffect& effect) = 0;

	virtual PBPMPoint GetStartPoint() const = 0;
	virtual PBPMPoint GetEndPoint() const = 0;	
	virtual PBPMPoint GetMiddlePoint() const = 0;

	virtual TrackingState GetTrackingState() const = 0;
	virtual TrackingEffect GetTrackingEffect() const = 0;

	/** Methods for grid/contact sheet creation when using the creation tools.
	*/
	/** EnableGridMode is called to enable/disable the creation of grids when using tools
		such as the Rectangle tool.
		@param enabled [IN]: true to enable grid mode, false to disable
	*/
	virtual void				EnableGridMode(bool enabled) = 0;
	/** Set the number of rows in the grid.
		@param rows [IN]: the number of rows.
	*/
	virtual void				SetRows(int32 rows) = 0;
	/** Set the number of columns in the grid.
		@param columns [IN]: the number of columns.
	*/
	virtual void				SetColumns(int32 columns) = 0;
	/** Set the Insets. Typically zero.
		@param left [IN]: left inset.
		@param top [IN]: top inset.
		@param right [IN]: right inset.
		@param bottom [IN]: bottom inset.
	*/
	virtual void				SetInsets(const PMReal& left, const PMReal& top, const PMReal& right, const PMReal& bottom) = 0;
	/** Set the amount of horizontal spacing between columns.
		@param horzSpace [IN]: horizontal spacing.
	*/
	virtual void				SetHorizontalSpacing(const PMReal& horzSpace) = 0;
	/** Set the amount of vertical spacing between rows.
		@param horzSpace [IN]: vertical spacing.
	*/
	virtual void				SetVerticalSpacing(const PMReal& vertSpace) = 0;
	virtual void				SetGridBounds(const PMRect& bounds) = 0;

	/** IsGridModeEnabled 
		@return whether or not grid mode is active
	*/
	virtual bool				IsGridModeEnabled() const = 0;
	/** GetRows
		@return the number of rows in the grid.
	*/
	virtual int32				GetRows() const = 0;
	/** GetColumns
		@return the number of columns in the grid.
	*/	
	virtual int32				GetColumns() const = 0;
	/** GetInsets
		@return the left, top, right and bottoms inset values as a rectangle
	*/	
	virtual const PMRect&		GetInsets() const = 0;
	/** GetHorizontalSpacing
		@return horizontal spacing between columns
	*/	
	virtual PMReal				GetHorizontalSpacing() const = 0;
	/** GetVerticalSpacing
		@return vertical spacing between rows
	*/	
	virtual PMReal				GetVerticalSpacing() const = 0;
	/** GetGridBounds
		@return the bounding box of the grid
	*/	
	virtual const PMRect&		GetGridBounds() const = 0;
};

#endif

