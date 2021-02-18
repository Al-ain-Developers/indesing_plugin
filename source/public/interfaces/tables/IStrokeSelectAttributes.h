//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/IStrokeSelectAttributes.h $
//  
//  Owner:
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
//  ADOBE CONFIDENTIAL
//  
//  Code modeled after PoxyWidget in the Transform Panel
//  
//========================================================================================

#pragma once
#ifndef __IStrokeSelectAttributes__
#define __IStrokeSelectAttributes__

class PMLine;

#include "IReferencePointData.h"
#include "widgetid.h"

/**
	Abstract interface that defines API of cell-stroke widget for stroke-selection.
	This is an application UI-related interface and not likely to be relevant to client code directly.
*/
class IStrokeSelectAttributes : public IPMUnknown
{

public:
	enum	{ kDefaultIID = IID_ISTROKESELECTATTRIBUTES };

	/**
		Enumerates the possible configurations for selecting sides on a cell or pair of cells
	*/
	enum RectLines {
		/**  */
		kNone = 0,
		/**  */
		kLeft = 1,
		/**  */
		kRight = 2,
		/**  */
		kTop = 4,
		/**  */
		kBottom = 8,
		/**  */
		kOuterEdges = 15,
		/**  */
		kHorizontalMiddle = 16,
		/**  */
		kVerticalMiddle = 32,
		/** */
		kInnerEdges = 48,
		/** */
		kAllSides = 63,

		/** */
		kTopRight = 9,
		/** */
		kTopLeft = 5,
		/** */
		kBottomRight = 10,
		/** */
		kBottomLeft = 6,
		/** */
		kTopMiddle = 17,
		/** */
		kBottomMiddle = 18,
		/** */
		kLeftMiddle = 36,
		/** */
		kRightMiddle = 40
	};

	/**
		Returns true if the value passed in is selected
		@param kTrue if the specified configuration is selected
	*/
	virtual const bool IsSelected(const IStrokeSelectAttributes::RectLines& position) const = 0;

	/**
		Gets the selected value
		@return selected value
	*/
	virtual const int32 GetSelected() const = 0;

	/**
		Used when the user selects the value.  Sends out a broadcast
		@param position one of the RectLines values
	*/
	virtual void SetSelected(const IStrokeSelectAttributes::RectLines& position) = 0;

	/**
		Used when setting the value when we don't want a broadcast
		@param position one of the RectLines values
	*/
	virtual void SetSelectedValue(const IStrokeSelectAttributes::RectLines& position) = 0;

	/**
		No broadcast -- sets the values back to 0  (calls SetSelectedValue)
	*/
	virtual void ResetSelected() = 0;

	/**
		No broadcast -- sets the values back to 63  (calls SetSelectedValue)
	*/
	virtual void SelectAll() = 0;

	/** Determine most recent selection.
		@return the selection that was most recently selected

	*/
	virtual int32 GetMostRecentSelection() const = 0;

	/**
		Returns true if table is vertical
	*/
	virtual bool16 DrawVertical() const = 0;

	/**
		Returns true if table is Bidirectional
	*/
	virtual bool16 DrawBiDi() const = 0;

	/**
		Returns true if the position is being drawn
		@param position one of the RectLines values
	*/
	virtual bool16 IsDrawn(const IStrokeSelectAttributes::RectLines& position) = 0;

	/**
		Sets the positions that will be drawn in the widget (one cell, two vertical cells.
		two horizontal cells, four cells)
		@param position one of the RectLines values
	*/
	virtual void SetDrawnPosition(const IStrokeSelectAttributes::RectLines& position, bool16 drawVertical, bool16 drawBiDi = kFalse) = 0;

	/**
		Returns the cell drawing information (see comment one above)
	*/
	virtual const int32 GetDrawnPositions() const = 0;

	/**
		Draws a single cell
		@param drawVertical	true if we are in a vertical table -- this way the sides draw correctly
	*/
	virtual void DrawSingle(bool16 drawVertical, bool16 drawBiDi = kFalse) = 0;

	/**
		Draws two cells vertically
		@param drawVertical true if we are in a vertical table -- this way the sides draw correctly
	*/
	virtual void DrawDoubleVertical(bool16 drawVertical, bool16 drawBiDi = kFalse) = 0;

	/**
		Draws two cells horizontally
		@param drawVertical true if we are in a vertical table -- this way the sides draw correctly
	*/
	virtual void DrawDoubleHorizontal(bool16 drawVertical, bool16 drawBiDi = kFalse) = 0;

	/**
		Draws all four cells
		@param drawVertical true if we are in a vertical table -- this way the sides draw correctly
	*/
	virtual void DrawAll(bool16 drawVertical, bool16 drawBiDi = kFalse) = 0;

	/**
		Resets drawn to 0
	*/
	virtual void ResetDrawn(bool16 drawVertical, bool16 drawBiDi = kFalse) = 0;

	/**
		Gets the neighbors that are selected (returns 00, 01, 10, 11)
		@param line
		@return
	*/
	virtual const int32 GetSelectedNeighbors(const RectLines& line) const = 0;

	/*
		False if you do not want to store the sides selected with the selection
		Ex: Cell Fill Pane
	*/
	virtual void SetStoreSidesWithSelection(bool16) = 0;

};

#endif  //define __IStrokeSelectAttributes__

