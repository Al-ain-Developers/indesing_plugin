//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellFocusManager.h $
//  
//  Owner: Joe Shankar
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
//  Purpose: Interface that to keep cell focuses up-to-date and handling notification
//  from the table model.
//  
//========================================================================================

#pragma once
#ifndef __ICellFocusManager__
#define __ICellFocusManager__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"

class ICellFocus;
class RowRange;
class ColRange;
class GridArea;

/**
	Manages cell focuses -- it is notified by the model when model events occur and it sends out the 
	messages to the appropriate cell focuses.
	@see ICellFocus
*/
class ICellFocusManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICELLFOCUSMANAGER };

	//----- Focus registration management.
	/**
		Adds a focus to its list to manage
		@param focus
	*/
	virtual void	AddFocus(ICellFocus* focus) = 0;
	/**
		Removes a focus to its list to manage
		@param focus
	*/
	virtual void	RemoveFocus(ICellFocus* focus) = 0;

	//---- Internal API for notification of table structure & attributes changes.
	/**
		Notified by the model when rows are inserted into the table
		@param rows The range of rows inserted
	*/
	virtual void	RowsInserted(const RowRange& rows) const = 0;
	/**
		Notified by the model when columns are inserted into the table
		@param cols The range of columns inserted
	*/
	virtual void	ColsInserted(const ColRange& cols) const = 0;
	/**
		Notified by the model when rows are deleted into the table
		@param rows The range of rows deleted
	*/
	virtual void	RowsDeleted (const RowRange& rows) const = 0;
	/**
		Notified by the model when columns are deleted into the table
		@param cols The range of columns deleted
	*/
	virtual void	ColsDeleted (const ColRange& cols) const = 0;
	/**
		Notified by the model when cells are merged in the table
		@param cells	The GridArea of the cells merged
	*/
	virtual void	CellsMerged	 (const GridArea& cells) const = 0;
	/**
		Notified by the model when cells are unmerged in the table
		@param cells	The GridArea of the cells unmerged
	*/
	virtual void	CellsUnmerged(const GridArea& cells) const = 0;
	/**
		Notified by the model when rows are coverted in the model (from header to body or footer to body or vise versa)
		@param rows The range of rows converted
	*/
	virtual void	RowsConverted(const RowRange& rows) const = 0;

	/**
		Notified by the model when row attributes are changed
		@param rows The range of rows whose attributes changed
	*/
	virtual void	RowAttributesChanged(const RowRange& rows) const = 0;
	/**
		Notified by the model when column attributes are changed
		@param cols The range of columns whose attributes changed
	*/
	virtual void	ColAttributesChanged(const ColRange& cols) const = 0;
	/**
		Notified by the model when cell attributes are changed
		@param cells	The GridArea of the cells whose attributes changed
	*/
	virtual void	CellAttributesChanged(const GridArea& cells)  const = 0;

	/**
		Notification when the whole table is deleted
	*/
	virtual void	TableBeingDeleted(void) const = 0;

	/**
		Notified by the model when table direction is changed
		@param directionRTL	Direction changed
	*/
	virtual void	TableDirChange(Tables::EDirection directionRTL) const = 0;

	/**
		Notified by the model when the content of cells are changed
		@param cells	The GridArea of the cells whose type changed
	*/
	virtual void	CellContentChanged(const GridArea& cells) const = 0;

	/**
		Notified by the model when the content of cells are deleted
		@param cells	The GridArea of the cells whose type changed
	*/
	virtual void	CellContentDeleted(const GridArea& cells) const = 0;
};

#endif
