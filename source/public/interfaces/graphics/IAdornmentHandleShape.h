//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAdornmentHandleShape.h $
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
//  Purpose:
//  This is the handle shape interface for page item adornments.  This interface can
//  return trackers just like a normal handle shape.  Keep in mind, however, that
//  it is the page item which is in the selection, not the adornment.  
//  
//========================================================================================

#pragma once
#ifndef __IAdornmentHandleShape__
#define __IAdornmentHandleShape__

#include "IPMUnknown.h"
#include "GraphicsData.h"
#include "IHandleShape.h"

class ITip;

class IAdornmentHandleShape : public IPMUnknown
{
//XFIssue this api called only in:
//	source/public/pageitems/basicinterfaces/CHandleShape.cpp
//	source/components/pageitems/generic/PageItemAdornmentList.cpp
// as of May 2006
public:
	
	enum AdornmentDrawOrder
	{
		// These values represent when the adornment is to be drawn.
		// Upon calling AddAdornment, the adornment is inserted into
		// the list based when it is to be drawn.  If more the one of
		// the flags are & together, the adornment is put on the list
		// in all specified locations.
		/** Before shape adornments */
		kBeforeShape = 1,
		/** After shape adornments */
		kAfterShape = 2,
		/** All the adornments */
		kAllAdornmentFlags = 3
	};

	enum AdornmentDrawNumber
	{
		kNumberOfAdornments = 2
	};

	enum AdornmentDrawMode
	{
		// These values represent when the adornment is to be drawn.
		
		kNonTouchDrawMode = 0,	// draw in non touch mode
		kTouchDrawMode,			// draw only in touch mode		
		kBothDrawMode			// draw in both modes
	};

	/**
	Retrieve the draw order flags

	@return AdornmentDrawOrder flags.	
	*/
	virtual AdornmentDrawOrder GetDrawOrderBits() = 0;

	/**
    Draw the adorment handle shape. It is up to the adornment to save and restore the graphic state. 
	
	@param iHandleShape[IN] the owning page item.
	@param adornmentDrawOrder[IN] the draw order of the adornment, in case this adornment is used more than once.
	@param gd[IN] the graphics context used for drawing.
	@param concretSelection[IN] the selection boss.
	@param flags[IN] default as kNoFlags and serves as a drawing flag. 
	*/
	virtual void DrawAdornmentHandleShape
		(
			IHandleShape* 		iHandleShape, 		// The owning page item
			AdornmentDrawOrder	adornmentDrawOrder,	// In case this adornment is used more than once
			GraphicsData* 		gd,
			IConcreteSelection* concreteSelection,
			int32 				flags = 0
		) = 0;
	
	/**
    Draw the path based on item's control points.

	@param iHandleShape[IN] the owning page item.
	@param adornmentDrawOrder[IN] the draw order of the adornment, in case this adornment is used more than once.
	@param gd[IN] the graphics context used for drawing.
	@param flags[IN] default as kNoFlags and serves as a drawing flag.
	*/
	virtual void DrawControlPointPath
		(
			IHandleShape* 		iHandleShape, 		// The owning page item
			AdornmentDrawOrder	adornmentDrawOrder,	// In case this adornment is used more than once
			GraphicsData* 		gd, 
			int32 				flags = 0
		) = 0;

	/**
    Check if a particular adornment handle of the item has been hit or not within the specified area.

	@param iHandleShape[IN] the owning page item.
	@param adornmentDrawOrder[IN] the draw order of the adornment, in case this adornment is used more than once.
	@param gd[IN] the graphics context used for hit testing.
	@param r[IN] the area for checking hit test.
	@param handleIndex[IN] the index of adornment handle.
	@param bDragging[IN] the flag which indicates whether dragging is on or not.
	@return bool16 kTrue if it hits, otherwise kFalse.
	*/
	virtual bool16 HitTest
		(
			IHandleShape* 		iHandleShape, 		// The owning page item
			AdornmentDrawOrder	adornmentDrawOrder,	// In case this adornment is used more than once
			GraphicsData* 		gd, 
			const PMRect&		r, 
			PointSelector* 		handleIndex,
			bool16				bDragging = kFalse
		) = 0;
	
	/**
    Check if the control point path has been hit or not.

	@param iHandleShape[IN] the owning page item.
	@param adornmentDrawOrder[IN] the draw order of the adornment, in case this adornment is used more than once.
	@param gd[IN] the graphics context used for hit testing.
	@param r[IN] the area for checking hit test.
	@return bool16 kTrue if it hits, otherwise kFalse.
	*/
	virtual bool16 HitTestControlPointPath
		(
			IHandleShape* 		iHandleShape, 		// The owning page item
			AdornmentDrawOrder	adornmentDrawOrder,	// In case this adornment is used more than once
			GraphicsData* 		gd, 
			const PMRect&		r
		) = 0;

	/**
    Returns the bounding box by computing it in pasteboard coords and then transforming it by inner to view.

	@param iHandleShape[IN] the owning page item.
	@param adornmentDrawOrder[IN] the draw order of the adornment, in case this adornment is used more than once.
	@param itemBounds[IN] the painted bounds of the page item.
	@param innertoview[IN] inner to view matrix. 
	@return PMRect the bounds for painting(redrawing).
	*/
	virtual PMRect GetPaintedAdornmentHandleBounds
		(
			IHandleShape* 		iHandleShape, 		// The owning page item
			AdornmentDrawOrder	adornmentDrawOrder,	// In case this adornment is used more than once
			const PMRect&		itemBounds,			// This is the painted bounds of the page item
			const PMMatrix& 	innertoview			// NOTE: this is inner to view, not pb to view
		) = 0;
	
	/**
	Query the tracker based on the given mouse position, hit test mode and adornment handle index.

	@param iHandleShape[IN] the owning page item.
	@param adornmentDrawOrder[IN] the draw order of the adornment, in case this adornment is used more than once.
	@param layView[IN] the active layout view where mouse is on.
	@param where[IN] the mouse position based on pasteboard coordinate.
	@param selectionMode[IN] the hit test flags.
	@param index[IN] specifies the index of adornment handle.
	@return ITracker* the result tracker and caller should deference it. 
	*/
	virtual ITracker* QueryTracker
		(
			IHandleShape* 		iHandleShape, 		// The owning page item
			AdornmentDrawOrder	adornmentDrawOrder,	// In case this adornment is used more than once
			IControlView*		layView, 
			const PBPMPoint& 	where, 
			int32 				selectionMode, 
			const PointSelector& index
		) = 0;

	/**
	Query for any tip implemented on the Adornment. If there is any tip on the Adornment then the ITip interface Ptr 
	will be returned else nil is returned in the default implementation.

	@param handleIndex[IN] the index of the handle for the adornment.
	@return ITip* the result tip interface  and caller should deference it.
	*/
	virtual ITip* QueryTip
		(
		   const PointSelector*       handleIndex
		) = 0;

	/**
	Obtain the adornment draw mode
	kNonTouchDrawMode - Draw only in non touch mode
	kTouchDrawMode - Draw only in touch mode
	kBothDrawMode - Draw in both modes
	*/
	virtual AdornmentDrawMode GetAdornmentDrawMode() = 0;

protected:

	/**
	Draw the adorment handle shape. It is up to the adornment to save and restore the graphic state.
	@param iHandleShape[IN] the owning page item.
	@param adornmentDrawOrder[IN] the draw order of the adornment, in case this adornment is used more than once.
	@param gd[IN] the graphics context used for drawing.
	@param concretSelection[IN] the selection boss.
	@param flags[IN] default as kNoFlags and serves as a drawing flag.
	*/
	virtual void DrawAdornmentHandleShapeModeChecked
		(
		IHandleShape* 		iHandleShape, 		// The owning page item
		AdornmentDrawOrder	adornmentDrawOrder,	// In case this adornment is used more than once
		GraphicsData* 		gd,
		IConcreteSelection* concreteSelection,
		int32 				flags = 0
		) = 0;
};

#endif
