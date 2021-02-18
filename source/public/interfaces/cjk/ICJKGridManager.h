//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICJKGridManager.h $
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
//  
//  Purpose: Geometric grid calculations.
//  
//========================================================================================

#pragma once
#ifndef __ICJKGridManager__
#define __ICJKGridManager__

#include "PMMatrix.h"
#include "PMRect.h"

#include "IPMUnknown.h"
#include "IDrawCJKGrid.h"

typedef K2Vector<int32> Int32List;

/** ICJKGridManager is the interface used to manage a frame or layout grid.  It provides geometric information like
	the scaled cell size, the number of characters, the number of lines, etc.  It also contains methods for moving
	points to closest grid left, top, right, or bottom.
*/
class ICJKGridManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICJKGRIDMANAGER };

	/** Calculates and caches cell counts, grid data, scaled size, and more.
		@param dynamicBounds IN Optional argument specifying the bounds of the grid during dynamic resize.
	*/
	virtual void RecalcGrid()  = 0;

	/**
	Returns the calculated state of the grid. Note that this might lag the
	value returned from the controlling ICJKGrid (such as the Story) because
	the manager of the layout (such as the MultiColumnTextFrame) has not caught
	up with the change.
	@return kTrue if the grid has been recalculated and found active, kFalse otherwise
	*/
	virtual bool16 IsActive() const = 0;

	/**
		@return kTrue if this is a vertical grid.  Otherwise kFalse.
	*/
	virtual bool16 IsGridVertical() const = 0;

	/**
		@return kTrue if this is a rectangular grid.  Otherwise kFalse.
	*/
	virtual bool16 IsGridRectangular() const = 0;

	/**  Fills in the PMRect at & rect with the bounds of the grid.
		@param rect OUT The bounds of the grid.
		@precondition rect must be a valid addresss.
	*/
	virtual void GetGridBounds(PMRect & rect) const = 0;

	/**
		@return a list of int32s that contain the characters per line for each column the grid manager controls.
		This will only contain one entry in the case of a multi-column text frame, because each column has
		its own grid manager.  For the case of a multi-column page it will contain one entry for each column.
	*/
	virtual const Int32List& GetCharsPerLine() const = 0;

	/**
		@return The number of lines in the grid.
	*/
	virtual int32 GetNumOfLines() const = 0;

	/**
		@return The number of cells in this grid managers control.
	*/
	virtual int32 GetRectCount() const = 0;

	/**
		@param cellNumber IN which cell do we want the bounds of.
		@return The rect of the Nth EmBox.
	*/
	virtual PMRect GetNthEmBoxRect(const int32 cellNumber) const = 0;

	/**
		@param cellNumber IN which cell do we want the bounds of.
		@return The rect of the Nth ICFBox.
	*/
	virtual PMRect GetNthICFBoxRect(const int32 cellNumber) const = 0;


	/**
		@return the horizontally scaled size of the grid cell
	*/
	virtual PMReal GetHCellSize() const = 0;

	/**
		@return the vertically scaled size of the grid cell
	*/
	virtual PMReal GetVCellSize() const = 0;


	/**  Draws all visible EmBox rects for the current grid.
		@param drawCJKGrid IN The IDrawCJKGrid to draw with.
		@param viewRect IN The visible rect.  If nil, the parent's rect will be used.
		@return kTrue if the grid did draw.  Otherwise kFalse.
	*/

	virtual bool16 DrawVisibleEmBoxRects( const IDrawCJKGrid * drawCJKGrid,const PMRect * viewRect = nil) const = 0;
	/**  Draws all visible ICF Box rects for the current grid.
		@param drawCJKGrid IN The IDrawCJKGrid to draw with.
		@param viewRect IN The visible rect.  If nil, the parent's rect will be used.
		@return kTrue if the grid did draw.  Otherwise kFalse.
	*/
	virtual bool16 DrawVisibleICFBoxRects( const IDrawCJKGrid * drawCJKGrid,const PMRect * viewRect = nil) const = 0;

	/**  Provides the x and y distances between the em and icf box.
		@param xAdjustment OUT The x distance between the left of the em and icf box.
		@param yAdjustment OUT The y distance between the bottom of the em and icf box.
		@precondition xAdjustment and yAdjustment must be valid addresses.
	*/
	virtual void GetICFAdjustments(PMReal & xAdjustment, PMReal & yAdjustment) const = 0;

	/**  Moves thePoint to the closest em box left then adds extra to the x value of thePoint, then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest left.
		@return
	*/
	virtual bool16 MoveToClosestEmBoxLeft(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;

	/**  Moves thePoint to the closest em box top, then adds extra to the x value of thePoint, and then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest top.
		@return
	*/
	virtual bool16 MoveToClosestEmBoxTop(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;

	/**  Moves thePoint to the closest em box right, then adds extra to the x value of thePoint, and then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest right.
		@return
	*/
	virtual bool16 MoveToClosestEmBoxRight(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;

	/**  Moves thePoint to the closest em box bottom, then adds extra to the x value of thePoint, and then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest bottom.
		@return
	*/
	virtual bool16 MoveToClosestEmBoxBottom(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;

	/**  MoveToClosestICFBoxLeft moves thePoint to the closest icf box left then adds extra to the x value of thePoint, then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest left.
		@return
	*/
	virtual bool16 MoveToClosestICFBoxLeft(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;

	/**  Moves thePoint to the closest icf box top, then adds extra to the x value of thePoint, and then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest top.
		@return
	*/
	virtual bool16 MoveToClosestICFBoxTop(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;

	/**  Moves thePoint to the closest icf box right, then adds extra to the x value of thePoint, and then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest right.
		@return
	*/
	virtual bool16 MoveToClosestICFBoxRight(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;

	/**  Moves thePoint to the closest icf box bottom, then adds extra to the x value of thePoint, and then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest bottom.
		@return
	*/
	virtual bool16 MoveToClosestICFBoxBottom(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;


	/**  Moves thePoint to the closest baseline, then adds extra to the y value of thePoint, and then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest bottom.
		@return
	*/
	virtual bool16 MoveToClosestBaseline(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;

	/**  Moves thePoint to the closest center, then adds extra to the x value of thePoint, and then transforms.
		@param thePoint INOUT the point to adjust.
		@param transform IN The transform apply before moving the point.
		@param extra IN The extra distance to add after finding the closest bottom.
		@return
	*/
	virtual bool16 MoveToClosestCenter(PMPoint & thePoint, const PMMatrix * transform = nil, const PMReal& extra = PMReal(0.0)) const = 0;

};

#endif
