//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableSelectionSuite.h $
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
//========================================================================================

#pragma once
#ifndef __ITableSelectionSuite__
#define __ITableSelectionSuite__

#include "ITableTarget.h"
#include "TablesUIID.h"
#include "TableTypes.h"

class ITableModel;


/** 
	Interface to manipulate the table selection.
*/
class ITableSelectionSuite : public IPMUnknown
{
public:
	enum				{ kDefaultIID = IID_ITABLESELECTION_SUITE	};	
	/** 
		kReplace recents the anchor pt to the top left of the new area and sets the selection to the new area.
		
		kAddTo gives the behavior that the anchorPt is the center of the selection and all selections are made around it.
		
		kExtend ignores the anchor pt and adds to the selection -- sets the anchor pt to the top left or the extended selection.

	*/
	enum SelectAction	{ kReplace, kAddTo, kExtend };

//----- Setters -----
	/** 
		Sets the table selection according to the selection action and the scrolls the view
		@param tableModel	model of selection
		@param cells		 the new selection
		@param selectionAction	what selection action are we doing
		@param autoScroll 	scroll selection
	*/
	virtual void 		Select(const ITableModel* table, const GridArea& cells, const SelectAction selectionAction, const bool16 autoScroll) = 0;

	/** 
		Sets the table selection according to the selection action and the scrolls the view
	*/
	virtual void 		Select(IPMUnknown* targetingBoss, const SelectAction selectionAction, const bool16 autoScroll) = 0;

	/** Method to select an entire table. 
	*/
	virtual void 		SelectAll(void) = 0;
	/** Method to select an entire table.
		@precondition table model is not nil
		@param model table model
	*/
	virtual void		SelectAll(const ITableModel *model) = 0;

	/** Method to unselect entire table targeted by selection
	*/
	virtual void 		DeselectAll(void) = 0;

	/** Sets a new selection at the given row.  Shrinks the selection so it is equal to
		how it appears to the user.  
		@precondition table model is not nil
		@precondition the row range specified by the RowRange(startRowNum,rowsToSelect) is valid, i.e. within table
		@param startRowNum	begin selection from this row
		@param rowsToSelect specifies count of rows to select
		@param model refers to table model in which to select (One version of this function tables a model and the other uses the existing on in the selection)
		@param useTopRowAsAnchor when kTrue sets the anchor to the left cell in the top row, and when false sets the anchor to the left cell in the bottom row
		@param autoScroll kTrue if view should scroll 
	*/
	virtual void		SelectRows(const int32 startRowNum, const int32 rowsToSelect, const ITableModel *model, 
								   const bool16 useTopRowAsAnchor, const bool16 autoScroll) = 0;
	/**
		Differs from the above function because this one doesn't take a model as a parameter and it uses the exisiting on in the selection
		@see SelectRows
	 */
	virtual void		SelectRows(const int32 startRowNum, const int32 rowsToSelect, const bool16 useTopRowAsAnchor, 
								   const bool16 autoScroll) = 0;
	/**
		Sets a new selection at the given column.  Shrinks the selection so it is equal to
		how it appears to the user.  
		
		For example if the last row is merged and the second
		column is selected it will shrink the selection to not include the last cell in that column.
		@precondition table model is not nil
		@precondition the column range specified by the ColRange(startColNum,colssToSelect) is valid, i.e. within table
		@param startColNum begin selection from this column
		@param colsToSelect count of columns to select
		@param model refers to table model in which to select (One version of this function tables a model and the other uses the existing on in the selection)
		@param useLeftColumnAsAnchor when kTrue sets the anchor to the top cell in the left column, and when false sets the anchor to the top cell in the right column
		@param autoScroll kTrue if view should scroll
	*/
	virtual void		SelectColumns(const int32 startColNum, const int32 colsToSelect, const ITableModel *model, 
								      const bool16 useLeftColumnAsAnchor, const bool16 autoScroll) = 0;
	/**
		Differs from the above function because this one doesn't take a model as a parameter and it uses the exisiting on in the selection
		@see SelectColumns
	 */
	virtual void		SelectColumns(const int32 startColNum, const int32 colsToSelect,
								      const bool16 useLeftColumnAsAnchor, const bool16 autoScroll) = 0;

	/**
		Selects all the cells which intersect with the given column and the body area of the table 
		@param startColNum	the first column in selection
		@param colsToSelect	the number of columns in the selection
		@param model		the model of the selection
		@param useLeftColumnAsAnchor use the left most column as the anchor
		@param autoScroll	scroll to selection
	 */
	virtual void		SelectBodyColumns(const int32 startColNum, const int32 colsToSelect, const ITableModel *model, 
								      const bool16 useLeftColumnAsAnchor, const bool16 autoScroll) = 0;

	/**
		Selects all of the body rows in the table
		@param tableModel	 model of selection
		@param autoScroll	 scroll selection
	 */
	 virtual void	SelectAllBodyRows(const ITableModel *tableModel, const bool16 autoScroll = kTrue) = 0;
	/**
		Selects all of the header rows in the table
	 @param tableModel	  model of selection
	 @param autoScroll	  scroll selection
	 */
	 virtual void	SelectAllHeaderRows(const ITableModel *tableModel, const bool16 autoScroll = kTrue) = 0;
	
	/**
		Selects all of the footer rows in the table
	 @param tableModel	  model of selection
	 @param autoScroll	  scroll selection
	 */
	 virtual void	SelectAllFooterRows(const ITableModel *tableModel, const bool16 autoScroll = kTrue) = 0;


	/** Used when moving around in the table
		@param index specifies text index to cache
	*/
	virtual void		SetSavedIndex(TextIndex index) = 0;

//----- Getters -----
	/** Accessor for the area selected in table that is target of the selection. 
		
		For instance, there is a text selection in the table, 
		would expect this to be area to span one cell for InDesign 2.0. 
		If there are cells selected, this can span more than one cell.

		@return return the dimension of the area selected in the table targeted by the selection
	*/
	virtual GridArea 	GetSelection() const = 0;

	/** Accessor for the extent of table selected. If none selected GridSpan(0, 0) would be returned.
		@return a GridSpan object representing the span of table selected. 
	*/
	virtual GridSpan 	GetTableSpan() const = 0;
	
	/** Accessor for the saved TextIndex.
		@return the saved index
	*/
	virtual TextIndex	GetSavedIndex() const = 0;

	/**  Accessor for the top-left of the area selected.
		@return the location represented by a GridAddress
	*/
	virtual GridAddress GetAnchor() const = 0;

	/** Determine what the new table selection <b>would</b> be if you selected given the passed in criteria.
		NOTE: this doesn't change any state, if you are calling it you have to know that kExtend
		and kReplace change the anchor to the top left of the selection returned
		@param tableModel	model of selection
		@param newSelection	the new selection
		@param anchorAddr	anchor of the selection
		@param selectionAction	what selection action are we doing
		@param GridArea		the new selection
	*/
	virtual GridArea GetNewTableSelection(const ITableModel *tableModel, const GridArea newSelection, const GridAddress anchorAddr, const SelectAction selectionAction = kReplace) = 0;

		
//----- Scrolling -----
	/**
		Scrolls the view to the given selection.
		Passes in a table model so that you can scroll the view even if the selection is not 
		set like in the case of tracking.

		@param model specifies table to work with
		@param newSelection specifies an area within this table to scroll into view
		@precondition model not nil
		@precondition newSelection not kZeroGridArea
	*/
	virtual void	ScrollViewToSelection(const ITableModel *model, const GridArea newSelection) = 0;

	/**
		Same as above, but it doesn't take an ITableModel
		This is the first step to deprecating the above function
		@param newSelection specifies an area within this table to scroll into view
	*/
	virtual void	ScrollViewToSelection(const GridArea newSelection) = 0;

	/** Sets the current selection to be in the centre of view. 
	
		For instance a sequence of method calls
		on this interface to GetSelection() and ScrollViewToSelection() with resulting 
		GridArea would have same net effect as this method.
	*/
	virtual void	CenterViewToSelection() = 0;

//------  For Internal Use ONLY --------

	/**
		USED ONLY BY THE TRACKER CODE
		Figures out if we are in the same table mode and can there for extend the selection
	*/
	virtual bool16 	CanShiftExtendSelection(const ITableModel* trackerFramesTableModel) const = 0;

	/**
		USED ONLY BY THE TABLES CODE
		return the table model of current selection
	*/
	virtual ITableModel* 		QuerySelectedTableModel(void) const = 0;
};


#endif //__ITableSelectionSuite__
