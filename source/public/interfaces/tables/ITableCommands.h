//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableCommands.h $
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
//========================================================================================

#pragma once
#ifndef __ITableCommands__
#define __ITableCommands__

#include "TablesID.h"
#include "TableTypes.h"
#include "ICellStrokeAttrData.h"
#include "ITableModel.h"

class AttributeBossList;
class TableMementoPiece; // $$$ should not be in the API
class WideString;
class ICommand;

/** Provides command based interface to the table model. Changes made to the table model
	should be made through this interface rather than through ITableAttrModifier or
	ITableModel to support undo capability.
*/
class ITableCommands : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITABLECOMMANDS };


	/**@name  Structure  */
	//@{-----------------------------------------------------------------------------

	/** Method to insert new, unfilled rows in a table. 
		
		Height should be specified in points.  If the given rowHeight is 0.0 then 
		the new row height is determined from 
		the row relative to which the insertion is being made. A non zero value of height will 
		result in all inserted rows having that minimum height.	
		
		The structure and attributes of the row that is the reference for the insertion
		will be propagated to the newly created rows; for instance, if the relative position is 'eAfter' and the
		row above the insertion location has a minimum row
		height of 2 picas and the row height is specified as 0, 
		then the newly created rows will inherit the minimum row 
		size of 2 picas from the rows above the insertion point even if this is not the default for other cells in the table.
		Similarly, if the relative position is 'eBefore', then the attributes and structure of the row below the insertion point
		will be propagated to the newly created rows.
		
		Encapsulates the execution of command that is instance of class kInsertRowsCmdBoss. 
		This command in turn acts on the table model to insert rows.

		@param rows specifies the location as the start of the range, and how many rows to add, as the count
		@param pos eBefore or eAfter to specify whether to insert before or after the current insertion point
		@param height height of the row specified in points; a non-zero value means inserted rows will have that minimum height,
		whereas a zero value will result in a calculated value based as described above
		@param continuation
		@return kSuccess if the command could be executed successully, kFailure otherwise

		@precondition the row range specified has a start within the bounds of the table rows
		@precondition the count of rows to be added in the row-range given  is > 0
		@precondition the minimimum height specified is >= 0.0

	*/
	virtual ErrorCode	InsertRows(const RowRange& rows, const Tables::ERelativePosition pos, const PMReal& height, const Tables::EContinuation continuation = Tables::eStructureAllAttrs) = 0;

	/** Method to move row(s) in a table
		
		@param sourceTable specifies the table within which rows are to be moved
		@param fromArea specifies the grid area which is to be moved
		@param toRow specifies the row where the selected rows are to be moved
		@param pos   specifies the position of moved rows with respect to destination row, i.e. toRow
		@param duplicateFlag  specifies whether the moved rows are to be duplicated or not

		@return kSuccess if the command could be executed successully, kFailure otherwise

	*/
	virtual ErrorCode	MoveRows(ITableModel* sourceTable, GridArea fromArea,  int32 toRow, Tables::ERelativePosition pos, bool16 duplicateFlag) = 0;

	/** Method to move column(s) in a table
		
		@param sourceTable specifies the table within which columns are to be moved
		@param fromArea specifies the grid area which is to be moved
		@param toColumn specifies the column where the selected columns are to be moved
		@param pos specifies the relative position with respect to toColumn
		@param duplicateFlag specifies whether the moved columns are to be duplicated or not

		@return kSuccess if the command could be executed successully, kFailure otherwise

	*/
	virtual ErrorCode	MoveColumns(ITableModel* sourceTable, GridArea fromArea,  int32 toColumn, Tables::ERelativePosition pos, bool16 duplicateFlag) = 0;

	/** Method to insert new, unfilled columns in a table.

		Width for the newly-created columns should be specified in points. 

		If colWidth is 0.0 then the new width is determined from 
		the column relative to which the insertion is being made. A non zero value of 
		width will  result in all inserted columns having that width.

		See the comments on InsertRows for detail on how attributes are propagated from the reference column
		to the newly created columns, mutatis mutandis.
		
		Encapsulates the execution of command that is instance of class kInsertColumnsCmdBoss; 
		this acts on the table model to insert columns.

		@param cols the start of the ColRange specifies the insertion location, and the count of the ColRange
			columns gives the number of columns to add
		@param pos eBefore or eAfter to specify whether to insert before or after the current insertion point
		@param width
		@param continuation
		@return kSuccess if the command could be executed successully, kFailure otherwise
	*/
	virtual ErrorCode 	InsertColumns(const ColRange& cols, const Tables::ERelativePosition pos, const PMReal& width, const Tables::EContinuation continuation = Tables::eStructureAllAttrs) = 0;
	
	/** Method to remove a specified row range from the table model.
		@param rows specifies a range of rows to be removed from the table model
		@return kSuccess if the command executed successfully, kFailure otherwise
		@precondition the start of the range should be within the range of rows in the table
		@precondition the count of rows to be deleted should be greater than 0
		@precondition table.GetTotalRows().Contains(rows)
					(GetTotalRows)
	*/
	virtual ErrorCode 	DeleteRows	 (const RowRange& rows) = 0;

	/** Method that can remove all rows from table model, 
		leaving behind the anchor characters.

	    This method is meant to be called when deleting a table via a text deletion. In this
		case it is undesirable for the table to delete the anchor characters.
	
		@param rows specifies a range of rows to be removed from the table model which should cover
			the whole table
		@return kSuccess if the command executed successfully, kFailure otherwise
		@precondition the start of the range should be within the range of rows in the table
		@precondition table.GetTotalRows() == rows
					(GetTotalRows)
	
	*/
	virtual ErrorCode 	DeleteRowsButNotAnchors(const RowRange& rows) = 0;

	/** Method to remove a specified range of columns from the table. 

		@param cols specifies the range of columns to remove from the table
		@return kSuccess if the command executed successfully, kFailure otherwise
		@precondition the start of the range should be within the range of columns in the table
		@precondition the count of columns to be deleted should be greater than 0
		@precondition table.GetTotalCols().Contains(cols)
					(GetTotalCols)

	*/
	virtual ErrorCode 	DeleteColumns(const ColRange& cols) = 0;

	/** Method to merge the area specified into a single cell covering a GridSpan that is the
		union of all the cells within this area.

		@param cells specifies a grid area that contains the cells to merge
	*/
	virtual ErrorCode 	MergeCells	 (const GridArea& cells) = 0;

	/** Method to unmerge the cells at the specified location, breaking apart the cell into grid 
		elements. These elements will have the trivial or unit GridSpan(1,1).

		@param anchor specifies the location of the cell that is to be unmerged
		@return kSuccess if the command executed successfully, kFailure otherwise
		@precondition the grid address should be valid within the table
		@precondition the address should refer to an anchor (top-left) of a cell			
	*/
	virtual ErrorCode 	UnmergeCell	 (const GridAddress& anchor) = 0;

	/** This method is obsolete. Please use SplitCells.
		Method to split a cell at specified location in given direction.
		@param anchor
		@param splitDirection one of eVerticalSplit, eHorizontalSplit 
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
//	virtual ErrorCode	SplitCell(const GridAddress& anchor, const ITableModel::ESplitDirection splitDirection) = 0;

	/** Method to split cells with anchors in the specified area in given direction.
		@param cells area of cells to split, does not need to contain complete cells
		@param splitDirection one of eVerticalSplit, eHorizontalSplit 
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode	SplitCells	 (const GridArea& cells, const ITableModel::ESplitDirection splitDirection) = 0;

	/* Method to change table direction from LeftToRight to RightToLeft
		@param directionRTL direction to change to
		@return kSuccess command executed successfully
	 */
	virtual ErrorCode 	ChangeTableDirection(Tables::EDirection directionRTL) = 0;

	//@}-----------------------------------------------------------------------------
	
	/**@name  Attributes  */
	//@{-----------------------------------------------------------------------------

	/** Method to apply change in height to rows. 
		
		The result of this method is to set the row-height and
		the minimum row height for the target rows to newHeight. 
		If some cells in target rows have content that extends below this in depth, then
		these cells can become overset.

		This encapsulates executing the command kResizeRowsCmdBoss. 
		This command delegates to the table model's attribute modifier (ITableAttrModifier) to
		change the model attributes. 

		@param rows specifies the range of rows to operate upon
		@param newHeight specifies the new minimum and current row-height to set for the target range of rows
		@return kSuccess if the command executed successfully, kFailure otherwise
		
	*/
	virtual ErrorCode 	ResizeRows	 (const RowRange& rows, const PMReal& newHeight) = 0;

	/** Method to apply change in width to columns. This will set the column width for
		the target column range; this does not affect the minimum column width for the target columns.

		@param cols specifies the target range of columsn for this operation
		@param newWidth specifies the
		@return kSuccess if the command executed successfully, kFailure otherwise		
	*/
	virtual ErrorCode 	ResizeCols	 (const ColRange& cols, const PMReal& newWidth) = 0;

	/** Method to apply attribute-overrides to the given row range.

		
		This encapsulates the execution of a command of class kApplyRowOverridesCmdBoss.
		This command in turn delegates to the table model's attribute modifier (ITableAttrModifier)
		to change the specified overrides. 

		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode	ApplyRowOverrides(const RowRange& rows, const AttributeBossList* attrs) = 0;

	/** Method to apply attribute-overrides to the given column range.

		
		This encapsulates the execution of a command of class kApplyColOverridesCmdBoss.
		This command in turn delegates to the table model's attribute modifier (ITableAttrModifier)
		to change the specified overrides. 

		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode	ApplyColOverrides(const ColRange& cols, const AttributeBossList* attrs) = 0;	

	/** Method to apply stroke-overrides to cells within given area.
		These attributes are represented by boss classes that are distinctively identified by 
		aggregating an ITableAttrReport interface and have a ClassID such as kRowAttr&lt;whatever&gt;Boss.
	
		Encapsulates execution of command of class kModifyCellStrokesCmdBoss. This in turn delegates
		to the table model's attribute modifier (ITableAttrModifier) to clear the strokes specified.
	
		For instance, to apply a stroke-weight to the top of all cells in given area, an ICellStrokeData::Data struct
		would be initialised as follows:
	<pre>
	ICellStrokeAttrData::Data data;
	data.attrs.Set(ICellStrokeAttrData::eWeight);
	data.attrs.Add(ICellStrokeAttrData::eTint);
	data.sides  = Tables::eTopSide;
	data.weight = newWeight; &#47;&#47; a PMReal specifying new weight in points
	data.tintPercent  = newTintPercent; &#47;&#47; a PMReal specifying tint in percent 
	</pre>
	
		@param area the cells within the given GridArea to operate upon
		@param data this is used to specify the sides and/or other attribute(s) for which the stroke-properties should be set. 
		@return kSuccess if the command executed successfully, kFailure otherwise
		@precondition the area should be valid within the table model, i.e. have at least one cell within it
	*/
	virtual ErrorCode	ApplyCellStrokes(const GridArea& area, const ICellStrokeAttrData::Data& data) = 0;

	/** Method to remove stroke-overrides from specified sides of cells in given area.

		Encapsulates execution of command of class kModifyCellStrokesCmdBoss. This in turn delegates
		to the table model's attribute modifier (ITableAttrModifier) to clear the strokes specified.
	
		For instance, to clear all the stroke-weight attributes set on all sides of the cells in the
		area, initialise a ICellStrokeAttrData::Data struct with the following:
	<pre>
	ICellStrokeAttrData::Data data;
	data.sides = Tables::eAllSides; &#47;&#47; or other constant from ESelectionSides
	data.attrs.Set(ICellStrokeAttrData::eWeight);
	</pre>
		
		@param area cells within this area will have the cell stroke overrides removed
		@param data this is used to specify the sides and/or other attribute(s) for which the stroke-properties should be cleared. 
		@return kSuccess if the command executed successfully, kFailure otherwise
		@precondition the area should be valid within the table model, i.e. have at least one cell within it
	*/
	virtual ErrorCode	ClearCellStrokes(const GridArea& area, const ICellStrokeAttrData::Data& data) = 0;
	
	/** @see ClearCellStrokes
		The difference between this command and the one above is that this one checks the GridArea we are applying to and makes
		sure it still exists in the table.  You can run into this problem through the preview dialogs.  If the apply table dimensions
		command is fired before the Clear Cell Attributes command then you end up clearing attributes on a new table structure
		which if using the above command would crash
	*/
	virtual ErrorCode	ClearCellStrokesUISafe(const GridArea& area, const ICellStrokeAttrData::Data& data) = 0;

	/** Method to swap over stroke-fill of the cells in given area. That is, the fill colour, tint and overprint
		will be swapped one-to-one with the stroke colour, tint and overprint.

		This encapsulates execution of a command of class kSwapCellStrokeFillCmdBoss.
		
		@param cells the cells within the given GridArea to operate upon
		@return kSuccess if the command executed successfully, kFailure otherwise
		@precondition the area should be valid within the table model, i.e. have at least one cell within it
	*/
	virtual ErrorCode	SwapCellStrokeFill(const GridArea& cells) = 0;

	/** Method to apply overrides to cells within given area. 
		These attributes are represented by boss classes that are distinctively identified by 
		aggregating an ITableAttrReport interface and have a ClassID such as kCellAttr&lt;whatever&gt;Boss.

		@param cells the cells within the given GridArea to operate upon	
		@param attrs list of boss objects specifying by their ClassID the attribute to override and new values
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	ApplyCellOverrides(const GridArea& cells, const AttributeBossList* attrs) = 0;
	
	/** Removes cell-attribute overrides within specified area.
		These attributes are represented by boss classes that are distinctively identified by 
		aggregating an ITableAttrReport interface and have a ClassID such as kCellAttr&lt;whatever&gt;Boss.

		@param cells the cells within the given GridArea to operate upon	
		@param attrs list of boss objects specifying by their ClassID the override to remove
		
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	ClearCellOverrides(const GridArea& cells, const AttributeBossList* attrs) = 0;
	
	/**	Applies table-level overrides to model.
		These attributes are represented by boss classes that are distinctively identified by 
		aggregating an ITableAttrReport interface and have a ClassID such as kTableAttr&lt;whatever&gt;Boss.

		@param cells the cells within the given GridArea to operate upon	
		@param attrs list of boss objects specifying by their ClassID the attribute to override and new values
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	ApplyTableOverrides(const AttributeBossList* attrs) = 0;
	
	/** Method to associate new table style with table model. Note that InDesign 2.0 does not support
		named table styles, so this is a method for future use.

		@param styleRef reference to the new table-style to associate with this table model
	
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	SetTableStyle(const UIDRef& styleRef) = 0;

	/** Removes cell-border overrides 

		@param edge the side which border we are dealing with	
		@param attrs list of boss objects specifying by their ClassID the override to remove
		
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	ClearBorderOverrides(Tables::ECellEdge edge, const AttributeBossList* attrs) = 0;

	/** Removes cell-attribute overrides within specified area.
		
		These attributes are represented by boss classes that are distinctively identified by 
		aggregating an ITableAttrReport interface and have a ClassID such as kCellAttr&lt;whatever&gt;Boss.

		The difference between this command and the one above is that this one checks the GridArea we are applying to and makes
		sure it still exists in the table.  You can run into this problem through the preview dialogs.  If the apply table dimensions
		command is fired before the Clear Cell Attributes command then you end up clearing attributes on a new table structure
		which if using the above command would crash

		@param cells the cells within the given GridArea to operate upon	
		@param attrs list of boss objects specifying by their ClassID the override to remove
		
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	ClearCellOverridesUISafe(const GridArea& cells, const AttributeBossList* attrs) = 0;

	//@}-----------------------------------------------------------------------------

	// Attributes -- returns a command to be processed
	/**@name  Queries  */
	//@{-----------------------------------------------------------------------------

	/** Method to acquire command that can be processed to apply changes to stroke-properties within given area
		@param area delimits cells that are target of this operation
		@param data
		@return interface ptr that has had reference-count incremented
	*/
	virtual ICommand*	QueryApplyCellStrokesCmd(const GridArea& area, const ICellStrokeAttrData::Data& data) = 0;
	/** Method to acquire command that can be processed to clear stroke-properties within given area
		@param area delimits cells that are target of this operation
		@param data
		@return interface ptr that has had reference-count incremented		
	*/
	virtual ICommand*	QueryClearCellStrokesCmd(const GridArea& area, const ICellStrokeAttrData::Data& data) = 0;
	/** Method to acquire command that can be processed to clear stroke-properties within given area

		The difference between this command and the one above is that this one checks the GridArea we are applying to and makes
		sure it still exists in the table.  You can run into this problem through the preview dialogs.  If the apply table dimensions
		command is fired before the Clear Cell Attributes command then you end up clearing attributes on a new table structure
		which if using the above command would crash

		@param area delimits cells that are target of this operation
		@param data
		@return interface ptr that has had reference-count incremented		
	*/
	virtual ICommand*	QueryClearCellStrokesUISafeCmd(const GridArea& area, const ICellStrokeAttrData::Data& data) = 0;
	/** Method to acquire command that can be processed to apply overrides to cell attributes within given area
		@param cells delimits cells that are target of this operation
		@param attrs
		@return interface ptr that has had reference-count incremented		
	*/
	virtual ICommand* 	QueryApplyCellOverridesCmd(const GridArea& cells, const AttributeBossList* attrs) = 0;	
	//@}-----------------------------------------------------------------------------

	/**@name  Content  */
	//@{-----------------------------------------------------------------------------

	/** Method to set the text contents of cell with given anchor (top-left) location.
		@param cellText specifies text contents for cell
		@param anchor location of top-left of cell that is target for this operation

		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode	SetCellText(const WideString& cellText, const GridAddress& anchor) = 0;	
	
	/** Method to remove the content from cells within given region
		@param cells delimits region within which cell contents are to be cleared
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode	ClearContent(const GridArea& cells) = 0;

	//@}-----------------------------------------------------------------------------

	/**@name  Internal use  */
	//@{-----------------------------------------------------------------------------
	/** Internal use only.
		@param strandRef
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	RegisterStrand(const UIDRef& strandRef) = 0;

	/**	Internal use only. See the documentation on ICellContentMgr for more information.
		@param contentMgrType 
		@param contenMgr
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	RegisterContentMgr(CellType contentMgrType, const UIDRef& contenMgr) = 0;

	//@}-----------------------------------------------------------------------------
	
	/**@name  Create Segments  */
	//@{-----------------------------------------------------------------------------
	/** Method to create a row segment at the distance from the top PMReal specified and
		spanning the cells in the range GridArea.
		@param distanceFromEdge
		@param segment
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	CreateRowSegment(const PMReal& distanceFromEdge, const ColRange& segmentRange) = 0;
	
	/**	Method to create a row segment at the distance from the left PMReal specified and
		spanning the cells in the range GridArea.
		@param distanceFromEdge
		@param segment
		@return kSuccess if the command executed successfully, kFailure otherwise
	*/
	virtual ErrorCode 	CreateColSegment(const PMReal& distanceFromEdge, const RowRange& segmentRange) = 0;	
	//@}-----------------------------------------------------------------------------
	

	/** @name  Convert to header and footer */
	//@{-----------------------------------------------------------------------------

	/**
		@param rows Rows to convert to headers. See ITableModel::ConvertToHeaderRows for more info.
	*/
	virtual ErrorCode ConvertToHeaderRows(const RowRange& rows) = 0;

	/**
		@param rows Rows to convert to footer. See ITableModel::ConvertToFooterRows for more info.
	*/
	virtual ErrorCode ConvertToFooterRows(const RowRange& rows) = 0;

	/**
		@param rows Rows to convert to body. See ITableModel::ConvertToBodyRows for more info.
	*/
	virtual ErrorCode ConvertToBodyRows(const RowRange& rows) = 0;
		
	//@}-----------------------------------------------------------------------------


	/** @name  Convert table to text */
	//@{-----------------------------------------------------------------------------

	/**
		@param colSeparator delimiter for parsing columns
		@param rowSeparator delimiter for parsing rows
	*/
	virtual ErrorCode 	ConvertTableToText(const PMString colSeparator="\t", const PMString rowSeparator="\r") = 0;

	/** Method to acquire command that can be processed to delete an entire table
		@param table model ref
		@return interface ptr that has had reference-count incremented		
	*/
	virtual ICommand*	QueryDeleteTableCmd(const UIDRef& tableRef) = 0;

	/** Method to convert the type of cells

		@param	cells		GridArea of cells to be converted
		@param	destType	cell type to be converted into
		@param	tryToPreserveData	if true, the data is preserved into the cell after conversion, if possible.

	*/
	virtual ErrorCode	ConvertCellsType(const GridArea& cells, CellType destType, bool16 tryToPreserveData = kFalse) = 0;

	/** Method to paste a page item into the graphic cell.

		@param	anchor		GridAddress of destination cell
		@param	pageItemUID	UIDRef of object to be pasted into the cell
		@param	preventCopy	The object would not be copied, just removed from the source and pasted here. This is not cut-paste. 
			It should be used, only if object is already in the scrap database.

	*/
	virtual ErrorCode	PastePageItem(const GridAddress &anchor, UIDRef pageItemUID, bool16 preventCopy = kFalse) = 0;
};

#endif // __ITableCommands__
