//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IDrawCJKGrid.h $
//  
//  Owner: Heath Lynn
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
#ifndef __IDrawCJKGrid__
#define __IDrawCJKGrid__

#include "IPMUnknown.h"
#include "ICJKGridData.h"
#include "IShape.h"
#include "IAdornmentShape.h"

class GraphicsData;
class PMRect;
class ICJKGridManager;

/** IDrawCJKGrid allows for custom CJK grid drawing.
*/
class IDrawCJKGrid : public IPMUnknown
{

public:

	/**  Draw will be called to draw the grid. 

		The drawing of grid cells is optimized by calling
		DrawVisibleICFBoxRects and DrawVisibleEmBoxRects on the ICJKGridManager.
		This will in turn call your DrawOpenCell(), DrawFilledCell(), and
		EndDraw().  If you wish to use optimized grid drawing, you will need to save the 
		GraphicsData from this Draw call and use it in your DrawOpenCell(), DrawFilledCell(),
		and EndDraw() methods.  You will also need to call DrawVisibleEmBoxRects
		or DrawVisibleICFBoxRects on the ICJKGridManager for this object.
		
		@param shape IN The shape the grid is drawing on.
		@param gridData IN The grids ICJKGridData.
		@param gridManager The grids ICJKGridManager.
		@param lineWidth IN The linewidth that should be used to draw this grid.
		@param gd IN The GraphicsData you are drawing into.
		@param flags IN The drawing flags this shape is drawing with.
	*/
	virtual void Draw(	const IPMUnknown * shape,
						const ICJKGridData* gridData, 
						const ICJKGridManager* gridManager, 
						const PMReal & lineWidth,
						const GraphicsData* gd, 
						const int32 flags ) = 0;
	
	/**  GetPaintedBBox returns the rect of the grid in view coordinates.  This most likely is just itemBounds, but
		in the event you wish the grid to extend beyond itemBounds, you need to return the extra area.
		@param iShape IN The shape the grid is drawing on.
		@param itemBounds IN The items current bounds in view coordinates.
		@param innertoview IN InnerToView transform matrix.
	*/
	virtual PMRect GetPaintedBBox(	const IShape* iShape, const PMRect& itemBounds, const PMMatrix& innertoview) const = 0;


	
	/** Inval, like it's namesake on IAdornmentShape is provided for completeness.
	When the owning shape is invalidated it includes the adornment in it's bounding box.   
	Under most circumstances the implemenation needs to do nothing in its inval method.
	There are times, however, when specific page items will get a specific reasonFoInval,
	and your implementation may want to know about that inval.  This provides a mechanism
	to respond to such an event.
		@param iShape IN The shape the grid is drawing on.
		@param gd IN The GraphicsData you are drawing into.
		@param reasonForInval IN Why we are invalidating.
		@param flags IN The drawing flags this shape is drawing with.
	*/
	virtual void Inval( IShape*				iShape,
						const GraphicsData*		gd, 
						const ClassID 			reasonForInval, 
						const int32 				flags ) const = 0;

	/**  DrawOpenCell is called by the grid manager's optimized grid drawing code.
		Your implementation can draw one open cell any way you like it.  It's best not
		to stroke the graphics port everytime.  It however, may be useful to stroke
		every 1000 cells in case you are drawing a massive grid.  Otherwise
		you should call stroke in EndDraw.
		@param rect IN The rectangle bounds of the cell.
		@param  position IN The cell number.
	*/
	virtual void DrawOpenCell(const PMRect & rect, int32 & position ) const = 0;
	
	/**  DrawFilledCell is called by the grid manager's optimized grid drawing code on filled cells.
		Your implementation can draw one filled cell any way you like it.  It's best not
		to stroke the graphics port everytime.  It however, may be useful to stroke
		every 1000 cells in case you are drawing a massive grid.  Otherwise
		you should call stroke in EndDraw.
		@param rect IN The rectangle bounds of the cell.
		@param  position IN The cell number.
	*/
	virtual void DrawFilledCell(const PMRect & rect, int32 & position ) const = 0;
	
	/**  EndDraw is called after the last call to DrawOpenCell or DrawFilledCell.
		@param  position IN The last cell drawn.
		@precondition You probably need to call stroke if position is > 0.
	*/
	virtual void EndDraw( int32 & position ) const = 0;


};

#endif
