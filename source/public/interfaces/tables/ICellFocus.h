//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellFocus.h $
//  
//  Owner: Mat Marcus
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
//  This interface describes a Table selection. It describes the range
//  and the table selected. 
//  In the planned implementation, the TableModel will have a TableFocusManager
//  that maintains the foci positions through editing.
//  
//========================================================================================

#pragma once
#ifndef __ICellFocus__
#define __ICellFocus__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"

class ITableModel;
class UIDRef;

/** 
	Represents a rectangular area of the table
	@see ICellFocusManager
*/
class ICellFocus : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ICELLFOCUS };

		/**
			Returns the ITableModel this focus is in
			@return ITableModel
		*/
		virtual ITableModel*	QueryModel() const = 0;

		/**
			Returns the UID of the ITableModel this focus is in
			@return UIDRef
		*/
		virtual UIDRef			GetModel() const = 0;

		/**
			Sets the rectangular area of the table this focus is in
			@param area	the range
		*/
		virtual void			SetRange(const GridArea &area) = 0;

		/**
			Returns the rectangular area of the table this focus is in
			@return GridArea
		*/
		virtual GridArea		GetRange() const = 0;

		/**
			Notification when rows are inserted into the table
			@param rows	The range of rows inserted
		*/
		virtual void			RowsInserted(const RowRange& rows) = 0;
		/**
			Notification when columns are inserted into the table
			@param cols	The range of columns inserted
		*/
		virtual void			ColsInserted(const ColRange& cols) = 0;
		/**
			Notification when rows are deleted into the table
			@param rows	The range of rows deleted
		*/
		virtual void			RowsDeleted (const RowRange& rows) = 0;
		/**
			Notification when columns are deleted into the table
			@param cols	The range of columns deleted
		*/
		virtual void			ColsDeleted (const ColRange& cols) = 0;
		/**
			Notification when rows are coverted in the model (from header to body or footer to body or vise versa)
			@param rows	The range of rows converted
		*/
		virtual void			RowsConverted (const RowRange& rows) = 0;
		/**
			Notification when cells are merged in the table
			@param cells	The GridArea of the cells merged
		*/
		virtual void			CellsMerged(const GridArea& cells) = 0;
		/**
			Notification when cells are unmerged in the table
			@param cells	The GridArea of the cells unmerged
		*/
		virtual void			CellsUnmerged(const GridArea& cells) = 0;
		/**
			Notification when the whole table is deleted
		*/
		virtual void			TableModelDeleted() = 0;

		/**
			DeRegisters with the model the focus is of so it doesn't recieve notification events
			@see ICellFocusManager
		*/
		virtual void			DeRegisterFromModel() = 0;
		/**
			Registers with the model the focus is of that it wants to recieve notification of model events
			@see ICellFocusManager
		*/
		virtual void			RegisterWithModel(const UIDRef& tableRef) = 0;

		/**
			Notification when the content of cells are modified
			@see ICellFocusManager
		*/
		virtual void			CellContentChanged(const GridArea& cells) = 0;

		/**
			Notification when the content of cells are deleted
			@see ICellFocusManager
		*/
		virtual void			CellContentDeleted(const GridArea& cells) = 0;
};


#endif //__ICellFocus__
