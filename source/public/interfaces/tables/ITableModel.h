//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableModel.h $
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
#ifndef __ITableModel__
#define __ITableModel__

#include "TableTypes.h"
#include "TablesID.h"
#include "PMReal.h"
#include "CellIterator.h"
#include "K2SmartPtr.h"
#include "IScaleObject.h"

//---- Forward declarations.
class IParcelList;
class ICellContent;
class ITextModel;
class ICellContentMgr;

class AttributeBossList;
class TableMemento;
class TableMementoPiece;
class ContentBossAccessor;

//===================================================================================
/** Public interface exposing the table model.

	The table model allows content to be arranged into rows and columns of cells.
 	The rows and columns in the table form a grid which is used for addressing.
 	Each element in the grid is addressed by a GridAddress(row, column).

	For instance, a GridAddress (1, 2) refers to the grid element in row 1, column 2.
	A table has a set of header, body and footer rows. The rows in a table are grouped
	in this order. Header rows, then body rows followed by footer rows. There should be
	at least one body rows. Header and footer rows may have a count of zero.
    Valid row values are in the row range represented by GetTotalRows.
    Valid column values are in the column range represented by GetTotalCols.

 	One or more elements can  be grouped together to  form a "cell".  Cells have content
 	and may span multiple rows and columns, i.e. multiple elements in the grid.
    The extent of a cell is represented by its GridSpan.

    A  "trivial cell" has a (row, column) span of (1, 1). Every element in the grid maps
 	to at most one cell. The topLeft element of a cell is called an anchor. A cell is
 	addressed by the GridAddress of it's anchor.

	Also see ITableAttrModifier and ITableAttrAccessor.

	@author 	Joe Shankar
 */
//===================================================================================

class ITableModel : public IPMUnknown {

public:
	///	kDefaultIID
	enum  { kDefaultIID = IID_ITABLEMODEL };

	//-------------------------------------------------------------------------------
	/**@name 	Table Dimensions	*/
	//@{-----------------------------------------------------------------------------
						/** Accessor for the range of header rows in the underlying table structure.
							@return the header rows in a RowRange object
						*/
	virtual RowRange 	GetHeaderRows() const = 0;

						/** Accessor for the area covered by the header rows.
							@returns the area of header rows in a GridArea object. 
						*/
	virtual GridArea 	GetHeaderArea() const = 0;

						/** Accessor for the range of body rows in the underlying table structure.
							@return the body rows in a RowRange object
						*/
	virtual RowRange 	GetBodyRows() const = 0;

						/** Accessor for the area covered by the body rows.
							@returns the area of body rows in a GridArea object. 
						*/
	virtual GridArea 	GetBodyArea() const = 0;

						/** Accessor for the range of footer rows in the underlying table structure.
							@return the footer rows in a RowRange object
						*/
	virtual RowRange 	GetFooterRows() const = 0;

						/** Accessor for the area covered by the footer rows.
							@returns the area of footer rows in a GridArea object. 
						*/
	virtual GridArea 	GetFooterArea() const = 0;

						/** Accessor for the total rows including headers, body and footers 
							in the underlying table structure.
							@returns total rows in a RowRange object
						*/	
	virtual RowRange 	GetTotalRows() const = 0;

						/** Accessor for the total columns in the underlying table structure.
							@return total columns in a ColRange object
						*/
	virtual ColRange 	GetTotalCols() const = 0;

						/** Accessor for the area covered by the whole table model.
							@return the whole table area in a GridArea object.
						*/
	virtual GridArea 	GetTotalArea() const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name  Cell spans  */
	//@{-----------------------------------------------------------------------------
						/** Accessor to determine if a given location is an anchor cell.
                            @param element Identifies the grid element to be tested.
                            @return kTrue if gridRef is the top-left element in a cell.
						*/
	virtual bool16 		IsAnchor(const GridAddress& element) const = 0;

						/** Accessor to determine the number of elements the cell consists of, i.e. the
						    number of rows and columns the cell spans.
                            @param anchor specifies the location for the cell this query is about
                            @return a GridSpan object that represents the cell-span (height,width) of the cell.
						*/
	virtual GridSpan	GetCellSpan(const GridAddress& anchor) const = 0;

						/** Returns the absolute location of the elements the cell consists of.
							i.e. <pre>GridArea(anchor, this->GetCellSpan()) </pre>
							@param anchor specifies the location for the cell query is about
						*/
	virtual GridArea	GetCellArea(const GridAddress& anchor) const = 0;

						/** Returns the anchor (top-left location) of the cell this element is in.
							@param element specifies the grid-element for this query
							@return the location of the anchor (top-left) for the given grid-element*/
	virtual GridAddress FindCellAnchor(const GridAddress& element) const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name	Validators  */
	//@{-----------------------------------------------------------------------------
						/** Determine if element at the given location is within the range of elements in
							the underlying table grid.
							@postcondition result = self.GetTableArea().Contains(element)
							@return kTrue if the location is within the table bounds, kFalse otherwise
						*/
	virtual bool16		IsValid(const GridAddress& element) const = 0;

						/** Determine if a given row lies within the range of rows spanned by this table.
							@return kTrue if row is within the table models range of rows */
	virtual bool16		IsValidRow(int32 row) const = 0;

						/** Determine if given column lies within columns spanned by this table.
							@return kTrue if col is within the table models range of rows
						*/
	virtual bool16		IsValidColumn(int32 col) const = 0;

						/** Determine if the specified area can be decomposed into a set of complete cells.
							The cells will be complete iff all the grid-elements that compose a cell are contained
							within the area. See the documentation for GridAddress for more material on
							distinction between grid-elements and cells.
							@return kTrue if cells are a complete rectangular, selectable area, kFalse otherwise
						*/
	virtual bool16 		ContainsCompleteCells(const GridArea& cells) const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name	GridID to GridAddress conversion
				Every element in a table has a unique GridID associated with it that does not
			change for the lifetime of the table.
	  */
	//@{-----------------------------------------------------------------------------
					    /** Accessor to find the GridID for a particular location. This

							@precondition location should be within the table
							@return the persistent GridID that identifies element,
					        or kInvalidGridID if the element is invalid.
						*/
	virtual	GridID	 	GetGridID (const GridAddress& element) const = 0;

					 	 /** The gridID should have been obtained by a previous call
					 	 	 to GetGridID.
							 @return the GridAddress represented by the gridID.
					 	 	 */
	virtual GridAddress  GetGridAddress(GridID gridID) const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name	Grid and span modifiers.  */
	//@{-----------------------------------------------------------------------------
					/** Inserts rows&#46;count rows  before or after rows&#46;start depending on pos.

						Height is in points. If rowHeight is 0.0 then the row height is
						determined by the auto-grow and minimum row height attribute of the row
						relative to which the insertion is being made. A non zero value of height will
						result in all inserted rows having that minimum height.

						[Documentation note for height semantics:
						Update ITableSuite.h & ITableCommands.h and ITableUtils.h to reflect changes.]

						@param rows	specifies the range of rows within table for the insertion, if this is
								not an empty range then the rows will be replaced
						@param pos	Specifies the relative position, before or after the given range in the table
						@param height desired row height in points
						@param continuation one of enumerated constants specifying how existing table properties should apply to these new rows
					  */
	virtual void	InsertRows(const RowRange& rows, const Tables::ERelativePosition pos, const PMReal& height, const Tables::EContinuation continuation = Tables::eStructureAllAttrs) = 0;

					/** Inserts rows&#46;count rows  before or after rows&#46;start depending on pos.

						This is meant to be called when we already have anchors for the rows we are
						adding, such as the case where we are coping a text frame containing part of a table

						@param rows	specifies the range of rows within table for the insertion, if this is
								not an empty range then the rows will be replaced
						@param pos	Specifies the relative position, before or after the given range in the table
						@param height desired row height in points
						@param continuation one of enumerated constants specifying how existing table properties should apply to these new rows
					  */

	virtual void	InsertRowsButNotAnchors(const RowRange& rows, const Tables::ERelativePosition pos, const PMReal& height, const Tables::EContinuation continuation = Tables::eStructureAllAttrs) = 0;

					/** Inserts cols&#46;count columns before or after cols&#46;start depending on pos.

						Width is in points. If colWidth is 0.0 then the new width is determined from
						the column relative to which the insertion is being made. A non zero value of
						width will  result in all inserted columns having that width.

						[Documentation note for width semantics:
						 Update ITableSuite.h & ITableCommands.h to reflect changes.]

						@precondition EContinuation should include attributes if width = 0
						@param cols	specifies the range of columns within the table for the insertion, if this is
								not an empty range then the rows will be replaced
						@param pos	Specifies the relative position, before or after the given range in the table
						@param height desired column height in points
						@param continuation one of enumerated constants specifying how existing table properties should apply to these new rows

					*/
	virtual void	InsertColumns(const ColRange& cols, const Tables::ERelativePosition pos, const PMReal& width, const Tables::EContinuation continuation = Tables::eStructureAllAttrs) = 0;

					/** Delete the number (rows&#46;count) rows starting from the position (rows&#46;start).
						@param rows specifies the range of rows to remove from this table
					*/
	virtual void	DeleteRows(const RowRange& rows) = 0;

					/** Delete the number (rows&#46;count) rows starting from the row given by (rows&#46;start),
						leaving the anchor characters behind.

						This is meant to be called when deleting a table via a text deletion. In this
						case it is undesirable for the table to delete the anchor characters.

						@param rows specifies the range of rows to remove from the table
					  */
	virtual void	DeleteRowsButNotAnchors(const RowRange& rows) = 0;

					/** Delete  (cols&#46;count) columns starting from the column at (cols&#46;start).
						@param cols gives range of columns to remove from table
					  */
	virtual void	DeleteColumns(const ColRange& cols) = 0;

					/**	Merges the elements specified by area. 	This function makes the anchor identified by (area.TopLeft) span
						all elements in 'area'.

						@param area Specifies a rectangle of elements in the grid to
						 be merged.
						@precondition self.CanMergeCells(area) = kTrue
					 */
	virtual void	MergeCells   (const GridArea& area) = 0;

					/** Determine if the given area is appropriate for a merge-cells operation.
						@param area specifies dimension of area containing cells of interest
						@return kTrue if area can be passed to the MergeCells call
					*/
	virtual bool16	CanMergeCells(const GridArea& area) const = 0;

					/** Anchor specifies a non-trivial cell to be unmerged. This function will
						make all elements spanned by the anchor trivial cells.
					  */
	virtual void	UnmergeCell(const GridAddress& anchor) = 0;

	enum 			ESplitDirection { eVerticalSplit, eHorizontalSplit };

					/** This method is obsolete. Please use SplitCells.
						Split the cell in half vertically or horizontally.
						@precondition self.CanSplitCell
					  */
//	virtual void	SplitCell(const GridAddress& anchor, ESplitDirection direction) = 0;

					/** Split the cells with anchors in the area in half vertically or horizontally.
						@precondition self.CanSplitCells
					  */
	virtual void	SplitCells(const GridArea& cells, ESplitDirection direction) = 0;

					/** This method is obsolete. Please use CanSplitCells.
						Determine whether a particular cell can be split.
						@precondition direction ==  eVerticalSplit or direction == eHorizontalSplit
						@param anchor location of the cell
						@param direction specify whether vertical or horizontal split of interest
						@return kTrue if the cell with specified
							anchor can be split in given direction,
							kFalse if this can't be done, or if the location does not represent the
							anchor point of a cell
					 */
//	virtual bool16	CanSplitCell(const GridAddress& anchor, ESplitDirection direction) const = 0;

					/** Determine whether cells with anchors in a particular area can be split.
						@precondition direction ==  eVerticalSplit or direction == eHorizontalSplit
						@param cells area of cells to split, does not need to contain complete cells
						@param direction specify whether vertical or horizontal split of interest
						@return kTrue if all of the cells can be split in given direction,
							kFalse if this can't be done, or if the area does not contain any anchors
					 */
	virtual bool16	CanSplitCells(const GridArea& cells, ESplitDirection direction) const = 0;

	/** Used to specify different states relating to table deletion.
	*/
	enum 			EDeleteState { eNotDeleting, eTableInitiatedDelete, eTextInitiatedDelete };

					/** Find out if who intitiated the delete of the table. Might be in states such as: not-deleting, text-deleting or table-deletnig.
						@return the current state relating to the ongoing deletion
					*/
	virtual EDeleteState	DeleteState() const = 0;

	/** Used to specify different states relating to table insertion.
	*/
	enum 			EInsertState { eNotInserting, eTableInitiatedInsert, eTextInitiatedInsert };

					/** Whether we should insert anchors with these rows or not
						@return the current state relating to the ongoing deletion
					*/
	virtual EInsertState	InsertState() const = 0;

	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name	Cell Content */
	//@{-----------------------------------------------------------------------------

					/** Efficient access to content bosses. Typical usage:
						<pre>
	boost::shared_ptr&lt;ContentBossAccessor&gt; cbAccessor(table->CreateContentBossAccessor());
	cbAccessor->QueryCellContentBoss(anchor);
						</pre>
						The returned ContentBossAccessor cannot be used across structure
						changes specifically row and column insertion or deletion.
						The following sequence would be illegal.
						<ol>
							<li> cb = table.CreateContentBossAccessor
							<li> table.insert/delete rows/columnns.
							<li>cb.QueryCellContentBoss
						</ol>
					 */
	virtual boost::shared_ptr<ContentBossAccessor> CreateContentBossAccessor(void) const = 0;

					/** Use ContentBossAccessor for accessing a range of cells.
						QueryCellContentBoss is not as efficient as the ContentBossAccessor.
						@param anchor refers to location of cell for which content boss object is sought
					*/
	virtual ICellContent*		QueryCellContentBoss(const GridAddress& anchor) const = 0;

					/**  Access to content managers.
						@param type The type of cell you wish the manager for
						@return a reference-incremented ptr to the cell content manager for the specified cell type
					*/
	virtual ICellContentMgr*	QueryContentMgr(CellType type) const = 0;
	//@}-----------------------------------------------------------------------------

	 //-------------------------------------------------------------------------------
	/**@name	Iteration  */
	//@{-----------------------------------------------------------------------------
							/** Used to traverse through the GridAddress locations
								within a table model */
	typedef CellIterator<ITableModel>		 const_iterator;
							/** Used to traverse through the GridAddress locations
								within a table model */
	typedef CellIterator<ITableModel>		 iterator;
							/** Used to traverse (in reverse direction) through the GridAddress locations
								within a table model */
	typedef ReverseCellIterator<ITableModel> reverse_iterator;
							/** Used to traverse (in reverse direction) through the GridAddress locations
								within a table model */
	typedef ReverseCellIterator<ITableModel> const_reverse_iterator;

							/** Use to acquire  an iterator that refers to the cell at the start of the table structure, i.e. GridAddress(0,0).
							*/
	virtual const_iterator				begin() const = 0;

							/** Use to acquire  an iterator that refers to cell at the start of the GridArea specified.
								@param area specifies dimension of grid-elements covered of interest
							*/
	virtual const_iterator				begin(const GridArea& area) const = 0;

							/** Use to acquire  an iterator that refers to cell just off the end of the whole table. Use this when
								the iteration should end at the last cell.
							*/
	virtual const_iterator				end() const = 0;

							/** Use to acquire an iterator that refers to the last cell for traversal through
								specified GridArea.
								@param area specifies dimension of grid-elements covered of interest
								@return iterator that refers to the specified location.
							*/
	virtual const_iterator				end(const GridArea& area) const = 0;


							/** Acquire a forward iterator.
								@return iterator referring to the given GridAddress
							*/
	virtual const_iterator				make_iterator(const GridAddress& gridRef) const = 0;

							/** Acquire a (reverse) iterator that can be used for a traversal of cells in reverse order via ++ starting
								at the specified location.
								@return (reverse) iterator referring to given location
							*/
	virtual const_reverse_iterator		rbegin() const = 0;

							/** Acquire a (reverse) iterator for delimiting end of traversal of cells in reverse order (via ++).
								This will normally be the beginning of the collection.
								@return (reverse) iterator that will mark end of iteration
							*/
	virtual const_reverse_iterator		rbegin(const GridArea& area) const = 0;

							/** Acquire a (reverse) iterator for delimiting end of traversal of cells in reverse order (via ++).
								This will normally be the beginning of the collection.
								@return (reverse) iterator that will mark end of iteration
							*/
	virtual const_reverse_iterator		rend() const = 0;

							/** Acquire a (reverse) iterator for delimiting the end of an iteration that ends at the given location.
								@return (reverse) iterator to refer to mark the given location in the collection
							*/
	virtual const_reverse_iterator		rend(const GridArea& area) const = 0;

							/** Acquire a (reverse) iterator.
								@return (reverse) iterator referring to the given GridAddress
							*/
	virtual const_reverse_iterator		rmake_iterator(const GridAddress& gridRef) const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name 	Copy-paste	 */
	//@{-----------------------------------------------------------------------------

							/** Determine if a given area within the table can be copied.

								@precondition self.GetTableArea().Contains(cells)
								@param cells specifies the dimension of the area containing cells of interest
								@return kTrue if it is valid to call self.Copy(cells), kFalse otherwise
							 */
	virtual bool16			CanCopy(const GridArea& cells) const = 0;

							/** Returns a TableMemento representing the internal state of the cells.

								This may be restored with a corresponding Paste call. Caller is responsible
								for deleting storage of the returned memento.

								@precondition CanCopy() == kTrue
								@param cells specifies the dimension of the area containing cells to copy
								@return a memento that can be used in subsequent paste operations

							 */
	virtual TableMemento*	Copy(const GridArea& cells) const = 0;


							/** Precondition for self.Clear

								@param	cells
							 */
	virtual bool16 			CanClear(const GridArea& cells) const = 0;

							/** Clears the content in cells.

  								@precondition self.CanClear
								@param	cells
							 */
	virtual void			Clear	(const GridArea& cells) = 0;

							/** Specifies what aspect to Paste
								These are the various aspects of a table that may be affected by Paste.
								Only eAll & eCells is currently supported.
							*/
							enum EWhatState
							{
								// Table attributes and style.
								 eTableAttrsStyle	=  0x01,

								// Row attributes.
								eRowAttrs			=  0x02,

								// Column attributes.
								eColAttrs			=  0x04,

								// Cell attributes.
								eCellAttrs			=  0x08,

								// Cell content.
								eCellContent		=  0x10,


								/** cell attributes and content */
								eCells				=  0x18,

								/** table, row, column, cell attr and content */
								eAll				=  0x1f

							};

							/** Accepts the TableMemento created by a previous call to
								Copy and applies into the model at atAnchor.

								Ownership of storage is transferred from the caller to the
								implementation of Paste.

								@param atAnchor location at which to paste
								@param what specifies what properties to transfer
								@param toAdopt
								@precondition self.GetTableArea().Contains(GridArea(atAnchor, memento.GetSpan())
							  */
	virtual void		   	Paste(const GridAddress& atAnchor, EWhatState what, TableMemento* toAdopt) = 0;
	virtual void		   	Paste(const GridAddress& atAnchor, EWhatState what, TableMemento* toAdopt, bool16 clearRedundantRows) = 0;

							/** Determine if a memento of mementoSpan can be pasted location specified by atAnchor.
								@param atAnchor specifies location of interest
								@param mementoSpan gives the dimension (height,width) of cell to be pasted
								@param memento give the structure to ensure complete cells in sets to paste into
								@return kTrue if a memento of mementoSpan can be pasted at location atAnchor
							*/
	virtual bool16			CanPaste(const GridAddress& atAnchor, const GridSpan& mementoSpan, const ITableModel* sourceTable, const GridAddress& fromAnchor) const = 0;

	//-------------------------------------------------------------------------------
	/**@name	Debug functions  */
	//@{-----------------------------------------------------------------------------
	#ifdef DEBUG
						/** Returns previous lock state of model.
							@param lock specifies new state for the lock on model
							@return previous state of the lock, kTrue if was locked, kFalse otherwise
						*/
	virtual	bool16	LockModel(bool16 lock) = 0;

						/** Accessor for lock state of model.
							@return current state of lock, kTrue if locked, kFalse otherwise
						*/
	virtual	bool16	IsModelLocked(void) const = 0;

						/** Traces out the current table structure using html tags */
	virtual void	TraceStructureAsHtml(void) const = 0;

						/** @return kTrue if there are any headers or footers in this table. */
	virtual bool16	IsHeaderOrFooterPresent(void) const = 0;
	#endif
	//@} -----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name	Create segments  */
	//@{-----------------------------------------------------------------------------
					/** Creates row segment.
						@param distanceFromTableTopEdge specifies segment pos, relative to top edge of the table
						@param segmentCols specifies the range of columns within the table for the new segment
					*/
	virtual void	CreateRowSegment(const PMReal& distanceFromTableTopEdge, const ColRange& segmentCols) = 0;

					/** Creates row segment.
						@param distanceFromTableTopEdge specifies segment pos, relative to top edge of the table
						@param segmentCols specifies the vector of the range of columns within the table for the new segment(s)
					*/
	virtual void	CreateRowSegment(const PMReal& distanceFromTableTopEdge, const K2Vector<ColRange>& segmentCols) = 0;

					/** Creates col segment.
						@param distanceFromTableLeftEdge specifies segment pos, relative to left edge of the table
						@param segmentRows specifies the range of rows within the table for the new segment
					*/
	virtual void	CreateColSegment(const PMReal& distanceFromTableLeftEdge, const RowRange& segmentRows) = 0;
	//@} -----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name	Convert to header & footer */
	//@{-----------------------------------------------------------------------------
				/** Converts body rows to header rows.
					@param	rows to be converted to headers.
					@pre	self.CanConvertToHeaderRows()
					@post	let preHeaderRows = self.GetHeaderRows()
					@post	self.GetHeaderRows == RowRange(preHeaderRows.start, preHeaderRows.count + rows.count)
				*/
	virtual void ConvertToHeaderRows(const RowRange& rows) = 0;

				/** Determine if the given rows can be converted to header rows.
				 	All header rows are maintained in a contiguous range before all body rows.
					@param rows specifies the body rows to be converted to header rows.
					@return kTrue if rows can be passed to ConvertToHeaderRows or ConvertToHeaderRowsButNoAnchors.
				 */
	virtual bool16 CanConvertToHeaderRows(const RowRange& rows) const = 0;

				/** Converts body rows to footer rows.
					@pre	self.CanConvertToFooterRows()
					@post	let preFooterRows = self.GetFooterRows()
					@post	self.GetFooterRows == RowRange(rows.start, preFooterRows.count + rows.count)
				*/
	virtual void ConvertToFooterRows(const RowRange& rows) = 0;

					/** Determine if the given rows can be converted to footer rows.					
					 	All footer rows are maintained in a contiguous range after all body rows.
						@param rows specifies the body rows to be converted to footer rows.
						@return kTrue if rows can be passed to ConvertToFooterRows or ConvertToFooterRowsButNoAnchors.
					*/
	virtual bool16 CanConvertToFooterRows(const RowRange& rows) const = 0;

				/** Converts header or footer rows to body rows.
					@param	rows to convert to body rows.					
					@pre	self.CanConvertToBodyRows(rows)					
					@post	self.GetBodyRows.Contains(rows)
					@post	self.GetHeaderRows().Contains(rows) == false
					@post	self.GetFooterRows().Contains(rows) == false
				*/
	virtual void ConvertToBodyRows(const RowRange& rows) = 0;

					/** Determine if the given rows can be converted to body rows.
						All body rows are maintained in one contiguous range after all header rows and 
						before all footer rows.
						@param	rows specifies the header or footer rows to be converted to  body rows. 				
						@pre	self.GetTotalRows().Contains(rows)
						@return kTrue if rows can be passed to CanConvertToBodyRows if self.GetHeaderRows().Contains(rows) or 
								self.GetFooterRows().Contains(rows)
					*/
	virtual bool16 CanConvertToBodyRows(const RowRange& rows) const = 0;


				/** For Internal use. */
	virtual void ConvertToHeaderRowsButNoAnchors(const RowRange& rows) = 0;
				/** For Internal use. */
	virtual void ConvertToFooterRowsButNoAnchors(const RowRange& rows) = 0;

	/** Accessor for the table direction.

		@returns the direction of the table. 
	*/
	virtual	Tables::EDirection GetTableDirection() const = 0;

	/** Changes the table direction.

		@param directionRTL Direction to change table.
	*/
	virtual void	ChangeTableDirection   (const Tables::EDirection directionRTL) = 0;

	/** Method to convert the type of cells
		@param	cells		GridArea of cells to be converted
		@param	destType	cell type to be converted into
		@param	tryToPreserveData	if true, the data is preserved into the cell after converion, if possible.
	*/
	virtual	void	ConvertCellsType(const GridArea& cells, const CellType destType, bool16 tryToPreserveData = kFalse) = 0;

	/** Returns kTrue if ConvertCellsType() can be called, kFalse otherwise.
		@param	cells		GridArea of cells to be converted
		@param	destType	cell type to be converted into
	*/
	virtual	bool16	CanConvertCellsType(const GridArea& cells, const CellType destType) const = 0;

	/** Get the type of cell (kTextContentType, kPageItemContentType etc.)
		@param	cells		GridArea of cells to be converted
	*/
	virtual CellType	GetCellType(const GridAddress& cell) const = 0;
};

/** 
Used to "or" EWhatState passed in to ITableModel::Paste
*/
inline ITableModel::EWhatState operator|(ITableModel::EWhatState first, ITableModel::EWhatState second)
{
	ASSERT(first  > 0 && first  <= ITableModel::eAll );
	ASSERT(second > 0 && second <= ITableModel::eAll );

	ITableModel::EWhatState result = (ITableModel::EWhatState)((uint32)first | (uint32)second);

	ASSERT(result > 0 && result <= ITableModel::eAll);
	return result;
};

/**
Well known CellContentTypes.
*/
const CellType kTextContentType	= kTextCellContentMgrBoss;
const CellType kPageItemContentType = kPageItemCellContentMgrBoss;

#endif // __ITableModel__
