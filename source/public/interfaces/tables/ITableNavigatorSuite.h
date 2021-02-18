//========================================================================================
//  
//  $File:$
//  
//  Owner: Danielle Bessette
//  
//  $Author:$
//  
//  $DateTime:$
//  
//  $Revision:$
//  
//  $Change:$
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
#ifndef __ITableNavigatorSuite__
#define __ITableNavigatorSuite__

#include "IPMUnknown.h"
#include "IPMUnknown.h"
#include "TablesUIID.h"
#include "TableTypes.h"
#include "ITableSelectionSuite.h"

class ITableModel;

class ITableNavigatorSuite : public IPMUnknown
{
public:
	enum				{ kDefaultIID = IID_ITABLENAVIGATOR_SUITE	};	

	/**
		Used for navigating around the table
	*/
	enum Direction { kInvalidDirection, kNext, kPrev, kUp, kDown, kLeft, kRight, kStartCol, kEndCol, kFirstFrameRow, kLastFrameRow, kStartRow, kEndRow };
	
	/** Determine what the new table selection <b>would</b> be if you selected given the passed in criteria.
		NOTE: This can only be called if there is an existing selection
		NOTE: this doesn't change any state
		@param	Direction
		@param	SelectAction
	*/
	virtual void		MoveSelection(Direction direction,	ITableSelectionSuite::SelectAction selectionAction) = 0;

	/** Get/Set the last direction in the table we moved in.  
		NOTE: direction is Reset on selection changed
	*/
	virtual Direction	GetLastDirection() = 0;
	virtual void		SetLastDirection(Direction direction) = 0;

	/** Get/Set the anchor of the selection, this is used when navigating to determine where to go next
	*/
	virtual GridAddress	GetAnchor() const = 0;
	virtual void		SetAnchor(const GridAddress anchor) = 0;

	/** Get/Set the anchor text index of the selection, this is used when navigating with a text selection around a cell to
		determine where to go next.
	*/
	virtual TextIndex   GetAnchorTextIndex() const = 0;
	virtual void		SetAnchorTextIndex(const TextIndex anchorIndex) = 0;
	
	/** Get/Set the direction we were moving when the anchor was set 
		NOTE: direction is Reset when we set the anchor cell 
	*/
	virtual Direction	GetInitalDirection() const = 0;
	virtual void		SetInitalDirection(Direction direction) = 0;
};


#endif
