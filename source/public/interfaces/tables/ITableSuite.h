//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableSuite.h $
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
//  Purpose: Interface to manipulate the table selection.
//  
//========================================================================================

#pragma once
#ifndef __ITableSuite__
#define __ITableSuite__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"
#include "ICellStrokeAttrData.h"

class AttributeBossList;
class ITextFrameColumn;
class ITableModel;

/**
	Manipulates the table selection.

	@see ISelectionUtils
	@ingroup table_ui
*/
class ITableSuite : public IPMUnknown
{
public:
	enum	{ kDefaultIID = IID_ITABLE_ISUITE };

	/**
		Directions in which a cell can be split.
	*/
	enum ESplitDirection { eVerticalSplit, eHorizontalSplit };

	/**
		User information about the row
	*/
	class UserRowNumber
	{
	public:
		enum RowType {eHeader, eBody, eFooter};

		UserRowNumber() : rowType(eBody), rowNumber(-1) {};
		RowType 	rowType;
		int32 		rowNumber;
	};


//---------------------------------------------------------------------------------------------------------------------------------------------
//
// Functions which preform actions on the selection	or the table containing the selection
//

	//----- Table structure
	/**
		Returns kTrue if InsertRows() can be called, kFalse otherwise.
		@param pos insert before or after the rows in the selection.
	*/
	virtual bool16	CanInsertRows	(Tables::ERelativePosition pos) const = 0;

	/**
		Returns kTrue if InsertColumns() can be called, kFalse otherwise.
		@param pos insert before or after the columns in the selection.
	*/
	virtual bool16	CanInsertColumns(Tables::ERelativePosition pos) const = 0;

	/**
		Returns kTrue if DeleteRows() can be called, kFalse otherwise.
	*/
	virtual bool16	CanDeleteRows	(void) const = 0;

	/**
		Returns kTrue if DeleteColumns() can be called, kFalse otherwise.
	*/
	virtual bool16	CanDeleteColumns(void) const = 0;

	/**
		Returns kTrue if MergeCells() can be called, kFalse otherwise.
	*/
	virtual bool16	CanMergeCells(void) const = 0;

	/**
		Returns kTrue if UnmergeCell() can be called, kFalse otherwise.
	*/
	virtual bool16	CanUnmergeCell(void) const = 0;

	/**
		This method is obsolete. Please use CanSplitCells().
		Returns kTrue if SplitCell() can be called, kFalse otherwise.
		@param direction of split, vertical or horizontal.
	*/
//	virtual bool16	CanSplitCell(ESplitDirection direction) const = 0;

	/**
		Returns kTrue if SplitCells() can be called, kFalse otherwise.
		@param direction of split, vertical or horizontal.
	*/
	virtual bool16	CanSplitCells(ESplitDirection direction) const = 0;

	/**
		Returns kTrue if you can edit the table, this is for InCopy because you can lock text
	*/
	virtual bool16	CanEditTable(void) const = 0;

	/**
		Returns kTrue if ConvertTableToText() can be called, kFalse otherwise.
	*/
	virtual bool16 	CanConvertTableToText() const = 0;

	/**
		Returns kTrue if DeleteTable() can be called, kFalse otherwise.
	*/
	virtual bool16 	CanDeleteTable() const = 0;

	/**
		Insert rows before or after the rows in the selection.
		The rowHeight is in points. If rowHeight is zero then the row height is
		determined by the auto-grow and minimum row height attribute of the row
		relative to which the insertion is being made. A non zero rowHeight value
		will result in all inserted rows having that minimum height.
		@param howMany number of rows to insert.
		@param pos before or after the rows in the selection.
		@param continuation
		@param rowHeight height of rows in points or zero to determine automatically.
		@precondition CanInsertRows() == kTrue.
	*/
	virtual void	InsertRows   (int32 howMany, Tables::ERelativePosition pos, const PMReal& rowHeight, Tables::EContinuation continuation = Tables::eStructureAllAttrs) = 0;

	/**
		Insert columns before or after the columns in the selection.
		Width is in points. If colWidth is zero then the new width is determined from
		the column relative to which the insertion is being made. A non zero colWidth value
		will  result in all inserted columns having that width.
		@param howMany number of columns to insert.
		@param pos before or after the columns in the selection.
		@param colWidth width of columns or zero to determine automatically.
		@param continuation
		@precondition CanInsertColumns() == kTrue.
	*/

	virtual void	InsertColumns(int32 howMany, Tables::ERelativePosition pos, const PMReal&  colWidth, Tables::EContinuation continuation = Tables::eStructureAllAttrs) = 0;

	/**
		Delete selected rows.
		@precondition CanDeleteRows() == kTrue.
	*/
	virtual void	DeleteRows   (void) = 0;

	/**
		Delete selected columns.
		@precondition CanDeleteColumns() == kTrue.
	*/
	virtual void	DeleteColumns(void) = 0;

	/**
		Merge selected cells.
		@precondition CanMergeCells() == kTrue.
	*/
	virtual void	MergeCells(void) = 0;

	/**
		Unmerge selected cell.
		@precondition CanUnmergeCell() == kTrue.
	*/
	virtual void	UnmergeCell(void) = 0;

	/**
		This method is obsolete. Please use SplitCells().
		Split selected cell in the given direction.
		@param direction of split, vertical or horizontal.
		@precondition CanSplitCell(direction) == kTrue.
	*/
//	virtual void 	SplitCell(ESplitDirection direction) = 0;

	/**
		Split selected cells in the given direction.
		@param direction of split, vertical or horizontal.
		@precondition CanSplitCells(direction) == kTrue.
	*/
	virtual void 	SplitCells(ESplitDirection direction) = 0;

	/**
		Convert selected table to text.
		@precondition CanConvertTableToText() == kTrue.
	*/
	virtual void 	ConvertTableToText(const PMString colSeparator="\t", const PMString rowSeparator="\r") = 0;

	/**
		Delete selected table.
		@precondition CanDeleteTable() == kTrue.
	*/
	virtual void 	DeleteTable() = 0;

	/**
		Returns kTrue if ClearAllTableOverrides() can be called, kFalse otherwise.
	*/
	virtual bool16	CanClearAllTableOverrides() const = 0;

	/**
		Returns kTrue if ClearSelectionOverrides() can be called, kFalse otherwise.
	*/
	virtual bool16	CanClearSelectionOverrides() const = 0;

	/**
		Clear the given table attribute overides for the selected table.
		Table attribute boss classes have one of the following prefixes
		in their name:
		<UL>
		<LI>kTableAttr
		<LI>kCellAttr
		<LI>kRowAttr
		<LI>kColAttr
		</UL>
		@param attrs list of table attributes to be cleared.
		@precondition CanClearAllTableOverrides() == kTrue.
	*/
	virtual void	ClearAllTableOverrides(AttributeBossList &attrs) const = 0;

	/**
		Clear the given table attribute overides for the selected cells.
		@param attrs gives the table attributes to be cleared.
		@param data gives the cell stroke attributes to be cleared.
		@precondition CanClearSelectionOverrides() == kTrue.
	*/
	virtual void	ClearSelectionOverrides(AttributeBossList &attrs, ICellStrokeAttrData::Data &data) const = 0;

	//---- Row and column size.
	/**
		Returns kTrue if ResizeRows() can be called, kFalse otherwise.
	*/
	virtual bool16	CanResizeRows(void) const = 0;

	/**
		Returns kTrue if ResizeColumns() can be called, kFalse otherwise.
	*/
	virtual bool16	CanResizeColumns(void) const = 0;

	/**
		Change the height of rows in the underlying grid of the table.
		@param height.
		@precondition CanResizeRows() == kTrue.
		@see GridAddress
	*/
	virtual void	ResizeRows(const PMReal& height) = 0;

	/**
		Change the width of columns in the underlying grid of the table.
		@param width.
		@precondition CanResizeColumns() == kTrue.
		@see GridAddress
	*/
	virtual void	ResizeColumns(const PMReal& width) = 0;
	/**
		Returns kTrue if ResizeCellHeight() can be called, kFalse otherwise.
	*/
	virtual bool16	CanResizeCellHeight(void) const = 0;

	/**
		Returns kTrue if ResizeCellWidth() can be called, kFalse otherwise.
	*/
	virtual bool16	CanResizeCellWidth(void) const = 0;

	/**
		Change the height of selected cells.
		@param height.
		@precondition CanResizeCellHeight() == kTrue.
	*/
	virtual void	ResizeCellHeight(const PMReal& height) = 0;

	/**
		Change the width of selected cells.
		@param width.
		@precondition CanResizeCellWidth() == kTrue.
	*/
	virtual void	ResizeCellWidth(const PMReal& width) = 0;

	/**
		Returns kTrue if RedistributeRows() can be called, kFalse otherwise.
	*/
	virtual bool16	CanRedistributeRows(void) const = 0;

	/**
		Returns kTrue if RedistributeColumns() can be called, kFalse otherwise.
	*/
	virtual bool16	CanRedistributeColumns(void) const = 0;

	/**
		Redistribute the height of rows across the space between
		the top of the first selected row and the bottom of the
		last selected row to give evenly sized rows.
		@precondition CanRedistributeRows() == kTrue.
	*/
	virtual void	RedistributeRows(void)= 0;

	/**
		Redistribute the width of columns across the space between
		the left of the first selected column and the right of the
		last selected column to give evenly sized columns.
		@precondition CanRedistributeColumns() == kTrue.
	*/
	virtual void	RedistributeColumns(void) = 0;

	/**
		Returns kTrue if SwapCellStrokeFill() can be called, kFalse otherwise.
	*/
	virtual bool16	CanSwapCellStrokeFill(void) const = 0;

	/**
		Swap the stroke and fill rendering attibutes for the selected cells.
		@precondition CanSwapCellStrokeFill() == kTrue.
	*/
	virtual void	SwapCellStrokeFill(void) = 0;

	/**
		Increase or decrease the number of body rows in the selected table to match the specified dimension.
		@param newRowDim total number of body rows the table will have.
		@precondition CanChangeTableDimensions() == kTrue.
	*/
	virtual void	ChangeBodyRowDimensionTo(int32 newRowDim) const = 0;

	/**
		Increase or decrease the number of columns in the selected table to match the specified dimension.
		@param newColDim total number of columns the table will have.
		@precondition CanChangeTableDimensions() == kTrue.
	*/
	virtual void	ChangeColumnDimensionTo(int32 newColDim) const = 0;

	/**
		Increase or decrease the number of header rows in the selected table to match the specified dimension.
		@param newRowDim total number of header rows the table will have.
		@precondition CanChangeTableDimensions() == kTrue.
	*/
	virtual void	ChangeHeaderRowDimensionTo(int32 newRowDim) const = 0;

	/**
		Increase or decrease the number of footer rows in the selected table to match the specified dimension.
		@param newRowDim total number of footer rows the table will have.
		@precondition CanChangeTableDimensions() == kTrue.
	*/
	virtual void	ChangeFooterRowDimensionTo(int32 newRowDim) const = 0;

	/**
		Returns kTrue if ChangeBodyRowDimensionTo(), ChangeColumnDimensionTo(), ChangeHeaderRowDimensionTo() or ChangeFooterRowDimensionTo() can be called, kFalse otherwise.
	*/
	virtual bool16	CanChangeTableDimensions(void) const = 0;

	/**
		Returns kTrue if Can Convert the selection To Header Rows
		@return 	bool16
	*/
	virtual bool16	CanConvertToHeaderRows(void) const   = 0;
	/**
		Converts the selection To Header Rows
	*/
	virtual void	ConvertToHeaderRows(void) = 0;
	/**
		Returns kTrue if Can Convert the selection To Footer Rows
		@return 	bool16
	*/
	virtual bool16	CanConvertToFooterRows(void) const  = 0;
	/**
		Converts the selection To Footer Rows
	*/
	virtual void	ConvertToFooterRows(void) = 0;

	/**
		Returns kTrue if Can Convert the selection To Body Rows
		@return 	bool16
	*/
	virtual bool16	CanConvertToBodyRows(void) const   = 0;
	/**
		Converts the selection To Body Rows
		*/
	virtual void	ConvertToBodyRows(void) = 0;

	/**
		INTERNAL USE ONLY, UNTESTED!
	*/
	virtual bool16	CanCreateTableStyleFromSelection(void) const = 0;
	/**
		INTERNAL USE ONLY, UNTESTED!
	*/
	virtual void	CreateTableStyleFromSelection(void) = 0;
	/**
		INTERNAL USE ONLY, UNTESTED!
	*/
	virtual bool16	CanApplyTableStyle(int32 nthStyle)    const = 0;
	/**
		INTERNAL USE ONLY, UNTESTED!
	*/
	virtual void	ApplyTableStyle(int32 nthStyle) = 0;

	/**
	 	Freezes or unfreezes the stroke tick depending on the bool parameter
	 	While the tick is frozen all strokes applied will have the same priority

	 	@return	FreezeTickHolder -- this object was created to hold the reference to the table attribute modifier
	 								the frozen tick value is not persisited and therefore this is neccessary
	 								The FreezeTickHolder freezes the tick on creation and unfreezes it on release
	 								place the FreezeTickHolder obj in an auto_ptr
	 */
	 class FreezeTickHolder
	 {
	 public:
		 virtual ~FreezeTickHolder() {}
	 };
	 virtual bool16	CanFreezeTick() const = 0;
	 virtual FreezeTickHolder*	FreezeTick() = 0;

//---------------------------------------------------------------------------------------------------------------------------------------------
//
// Functions which answer questions about cell attributes in the selection
//

	/**
		Returns kTrue if selected rows have the same height and GetRowSize() can be called, kFalse otherwise.
	*/
	virtual bool16	CanGetRowSize(void) const = 0;

	/**
		Returns kTrue if selected columns have the same width and GetColumnSize() can be called, kFalse otherwise.
	*/
	virtual bool16	CanGetColumnSize(void) const = 0;

	/**
		Get height of rows in the underlying grid of the table.
		@precondition CanGetRowSize() == kTrue.
		@return row height.
		@see GridAddress
	*/
	virtual PMReal	GetRowSize(void) const = 0;

	/**
		Get width of columns in the underlying grid of the table.
		@precondition CanGetColumnSize() == kTrue
		@return column width.
		@see GridAddress
	*/
	virtual PMReal	GetColumnSize(void) const = 0;

	/**
		Returns kTrue if GetCellWidth() can be called, kFalse otherwise.
	*/
	virtual bool16	CanGetCellWidth(void) const = 0;

	/**
		Returns kTrue if GetCellHeight() can be called, kFalse otherwise.
	*/
	virtual bool16	CanGetCellHeight(void) const = 0;

	/**
		Get visible width of cell, for example if one cell is merged with another
		the overall width of both is returned.
		@precondition CanGetCellWidth() == kTrue
		@return cell width.
		@see GridAddress
	*/
	virtual PMReal	GetCellWidth(void) const = 0;

	/**
		Get visible height of cell, note if one cell is merged with another
		the overall height of both cells is returned.
		@precondition CanGetCellHeight() == kTrue
		@return cell height.
		@see GridAddress
	*/
	virtual PMReal	GetCellHeight(void) const = 0;

	//----- Table attributes
	/**
		Returns kTrue if ApplyTableOverrides() can be called, kFalse otherwise.
	*/
	virtual bool16	CanApplyTableOverrides() const = 0;

	/**
		Override the given table attributes.
		@param attrs list of attributes to be overridden.
		@precondition CanApplyTableOverrides() == kTrue.
	*/
	virtual void	ApplyTableOverrides(const AttributeBossList* attrs) = 0;

	/**
		Acquire the IPMUnknown interface pointer of the given table attribute
		for the selection.
		Other interfaces that exist on the boss object can be queried from this.
		@param whichAttr identifies the table attribute boss class wanted, kTableAttrColStrokeWeightBoss for example.
		@return IPMUnknown interface pointer of the given table attribute for the selection.
		@postcondition caller is responsible for releasing the returned interface pointer.
	*/
	virtual const IPMUnknown*	QueryTableAttribute(ClassID whichAttr) const = 0;


	//----- Cell attributes
	/**
		Override the given cell attributes.
		@param attrs list of attributes to be overridden.
		@precondition CanApplyCellOverrides() == kTrue.
	*/
	virtual void	ApplyCellOverrides(const AttributeBossList* attrs) = 0;

	/**
		Returns kTrue if ApplyCellOverrides() can be called, kFalse otherwise.
	*/
	virtual bool16	CanApplyCellOverrides(void) const = 0;

	/**
		Returns kTrue if the value of the given attribute is the same for all
		selected cells and QueryCellAttribute() can be called, kFalse otherwise.
		@param whichAttr identifies the attribute to be checked, kCellAttrBottomInsetBoss for example.
	*/
	virtual bool16	CanGetCellAttribute(ClassID whichAttr) const = 0;

	/**
		Acquire the IPMUnknown interface pointer of the given cell attribute
		for the selection. Using this pointer a data interface can be queried
		on the boss object to find the attribute value.
		@param whichAttr identifies the table attribute boss class wanted, kCellAttrBottomInsetBoss for example.
		@return IPMUnknown interface pointer of the given cell attribute for the selection.
		@precondition CanGetCellAttribute() == kTrue.
		@postcondition caller is responsible for releasing the returned interface pointer.
	*/
	virtual const IPMUnknown*	QueryCellAttribute(ClassID whichAttr) const = 0;

	/**
		Returns kTrue if ApplyCellStrokes() can be called to change the cell
		stroke attributes indicated in data, kFalse otherwise.
		@param data identifies the cell stroke attributes to be changed.
	*/
	virtual bool16 	CanApplyCellStrokes(const ICellStrokeAttrData::Data& data) const = 0;

	/**
		Change the cell stroke attributes to the values given by data.
		The attributes to be changed and their new values are identified
		by the data interface which allows them to be set
		in a single call.
		@param data identifyies cell stroke attributes to be changed and their new values.
		@precondition CanApplyCellStrokes() == kTrue.
	*/
	virtual void	ApplyCellStrokes(const ICellStrokeAttrData::Data& data) = 0;

	/**
		Returns kTrue if GetCellStrokes() can be called to get the value of the attributes indicated by data, kFalse otherwise.
		@param data identifies the cell stroke attributes to be obtained.
	*/
	virtual bool16	CanGetCellStrokes(const ICellStrokeAttrData::Data& data) const = 0;

	/**
		Get the value of the attributes indicated by data. Use of data allows the values
		of several attributes (stroke weight, color etc.) to be retrieved in a single call
		rather than individually.
		@param data identifies the cell stroke attributes to be obtained on input and contains their values on return.
		@precondition CanGetCellStrokes()
	*/
	virtual void	GetCellStrokes(ICellStrokeAttrData::Data& data) const = 0;

					// stroke operations given the use of the Stroke Data on the kTableSuiteBoss
	/**
		Returns kTrue if GetCellStrokesBySelection() or ApplyCellStrokesBySelection()
		can be called, kFalse otherwise.
	*/
	virtual bool16				CanGetApplyCellStrokesBySelection(void) const = 0;

	/**
		Change cell stroke attributes using the selection's cell stroke data.
		@param interface pointer to data boss class
	*/
	virtual void				ApplyCellStrokesBySelection(const IPMUnknown* attr) = 0;

	/**
		Acquire an interface pointer to the selection's cell stroke data.
		The IPMUnknown returned can be used to query an ICellStrokeAttrData
		interface that carries the cell stroke data.
		@precondition CanGetApplyCellStrokesBySelection() == kTrue.
		@return IPMUnkown interface pointer to data boss object.
		@postcondition caller is responsible for releasing the returned interface pointer.
	*/
	virtual const IPMUnknown*   GetCellStrokesBySelection() const = 0;


	//----- Row attributes
	/**
		Override the given row attributes associated with the selection.
		@precondition CanApplyRowOverrides() == kTrue.
		@param attrs list of attributes to be overridden.
	*/
	virtual void	ApplyRowOverrides(const AttributeBossList* attrs) = 0;

	/**
		Returns kTrue if ApplyRowOverrides() can be called, kFalse otherwise.
	*/
	virtual bool16	CanApplyRowOverrides(void) const = 0;

	/**
		Returns kTrue if you can apply keeps/start on attributes to this row
	*/
	virtual bool16	CanApplyRowKeeps(void) const = 0;

	/**
		Returns kTrue if all rows in the selection have the same value for whichAttr
		and QueryRowAttribute() can be called, kFalse otherwise.
		@param whichAttr identifies the attribute to be checked, kRowAttrHeightBoss for example.
	*/
	virtual bool16	CanGetRowAttribute(ClassID whichAttr) const = 0;

	/**
		Acquire an IPMUnkown interface pointer for whichAttr.
		@param whichAttr identifies the attribute wanted, kRowAttrHeightBoss for example.
		@precondition self.CanGetRowAttribute(whichAttr) == kTrue.
		@return IPMUnkown interface pointer for whichAttr.
		@postcondition caller is responsible for releasing the returned interface pointer.
	*/
	virtual const IPMUnknown*	QueryRowAttribute(ClassID whichAttr) const = 0;

	/**
		Returns kTrue if all cols in the selection have the same value for whichAttr
		and QueryColAttribute() can be called, kFalse otherwise.
		@param whichAttr identifies the attribute to be checked, kColAttrWidthBoss for example.
	*/
	virtual bool16	CanGetColAttribute(ClassID whichAttr) const = 0;

	/**
		Acquire an IPMUnkown interface pointer for whichAttr.
		@param whichAttr identifies the attribute wanted, kColAttrWidthBoss for example.
		@precondition self.CanGetColAttribute(whichAttr) == kTrue.
		@return IPMUnkown interface pointer for whichAttr.
		@postcondition caller is responsible for releasing the returned interface pointer.
	*/
	virtual const IPMUnknown*	QueryColAttribute(ClassID whichAttr) const = 0;

	/**
		Returns kTrue if GetOverridesInTable() can be called, kFalse otherwise.
	*/
	virtual bool16	CanGetOverridesInTable() const = 0;

	/**
		Attribute override state information returned by GetOverridesInTable().
	*/
	struct OverrideState
	{
		typedef base_type data_type;
		/** */
		ClassID		classID;
		/** */
		bool16		valueSameAsFind;
	};

	/**
		Collection of override state information returned by GetOverridesInTable().
	*/
	typedef K2Vector<OverrideState> OverrideStateVector;

	/**
		INTERNAL USE ONLY
		Note: This function is called when using the table alternating pattern UI, there is no use otherwise
		Collects the overrides in the table based on the pattern passed
		in, findAttrsFirst and findAttrsSecond.
		findAttrsFirst  maybe nil only if firstPatterCount   = 0
		findAttrsSecond maybe nil only if secondPatternCount = 0

		For each attribute in the findAttrs (first or second) that is overriden,
		an entry is  made in the corresponding result OverrideStateVector.
		If the value of all override  is the same as that of the attribute in the findAttrs
		then the OverrideState entry.valueSameAsFind is set to kTrue. A value of kFalse
		indicates the presence of override(s) but the value being different from that in
		findAttrs. If no entry is made in resultFirst || resultSecond for the corresponding
		attribute then there are no overrides.

		@param patternType			column or row
		@param firstPatternCount		count in first set 
		@param secondPatternCount		count in second set
		@param skipFirst				number from top skipped
		@param skipLast				number from bottom skipped
		@param findAttrsFirst IN		attributes in first set to look for
		@param findAttrsSecond IN		attributes in first set to look for
		@param resultFirst OUT			the overrides on the first set
		@param resultSecond OUT		the overrides on the second set
		@postcondition delete resultFirst and resultSecond before they go out of scope.
	*/
	virtual void	GetOverridesInTable
						(Tables::ERowColumn patternType,
						 int32 firstPatternCount, int32 secondPatternCount,
						 int32 skipFirst, int32 skipLast,
						 const AttributeBossList* findAttrsFirst,
						 const AttributeBossList* findAttrsSecond,
						 OverrideStateVector* resultFirst,
						 OverrideStateVector* resultSecond) const = 0;



	/**
		INTERNAL USE ONLY
	 	The following function clears the FILL overrides which intersect with alternating row or column FILL pattern
		Note: This function is called when using the table alternating pattern UI, there is no use otherwise
		@param firstOverrideAttrs  		the overrides on the first set
		@param secondOverrideAttrs	the overrides on the first set
		@param pattern1				count in first set 
		@param pattern2				count in second set
		@param skipFirst				number from top skipped
		@param skipLast				number from bottom skipped
	*/
	virtual void ClearRowPatternFillOverrides(const AttributeBossList *firstOverrideAttrs, const AttributeBossList *secondOverrideAttrs,
 									  const int32 pattern1, const int32 pattern2, const int32 skipFirst, const int32 skipLast) = 0;
	/**
		INTERNAL USE ONLY
	 	The following function clears the FILL overrides which intersect with alternating row or column FILL pattern
		Note: This function is called when using the table alternating pattern UI, there is no use otherwise
		@param firstOverrideAttrs  		the overrides on the first set
		@param secondOverrideAttrs	the overrides on the first set
		@param pattern1				count in first set 
		@param pattern2				count in second set
		@param skipFirst				number from top skipped
		@param skipLast				number from bottom skipped
	*/
	virtual void ClearColumnPatternFillOverrides(const AttributeBossList *firstOverrideAttrs, const AttributeBossList *secondOverrideAttrs,
 									  const int32 pattern1, const int32 pattern2, const int32 skipFirst, const int32 skipLast) = 0;



	/**
		INTERNAL USE ONLY
		Collects the overrides in the table based on the pattern passed
		in, findAttrsFirst and findAttrsSecond.
		findAttrsFirst  maybe nil only if firstPatterCount   = 0
		findAttrsSecond maybe nil only if secondPatternCount = 0

		For each attribute in the findAttrs (first or second) that is overriden,
		an entry is  made in the corresponding result ICellStrokeAttrData::Data.
		If the value of all override  is the same as that of the attribute in the findAttrs
		then the ICellStrokeAttrData::Data entry is set. No value indicates the presence
		of override(s) but the value being different from that in
		findAttrs. If no entry is made in resultFirst || resultSecond for the corresponding
		attribute then there are no overrides.

		@param patternType			column or row
		@param firstPatternCount		count in first set 
		@param secondPatternCount		count in second set
		@param skipFirst				number from top skipped
		@param skipLast				number from bottom skipped
		@param findAttrsFirst IN		attributes in first set to look for
		@param findAttrsSecond IN		attributes in first set to look for
		@param resultFirst OUT			the overrides on the first set
		@param resultSecond OUT		the overrides on the second set
		@postcondition delete resultFirst and resultSecond before they go out of scope.
	*/

	virtual void	GetStrokeOverridesInTable(Tables::ERowColumn patternType,
						 int32 firstPatternCount, int32 secondPatternCount,
						 int32 skipFirst, int32 skipLast,
						 const ICellStrokeAttrData::Data& firstData,
						 const ICellStrokeAttrData::Data& secontData,
						 ICellStrokeAttrData::Data& resultFirst,
						 ICellStrokeAttrData::Data& resultSecond) const = 0;

	/**
		INTERNAL USE ONLY
	 	The following function clears the STROKE overrides which intersect with alternating row or column STROKE pattern
		Note: This function is called when using the table alternating pattern UI, there is no use otherwise
		@param firstOverrideAttrs  		the overrides on the first set
		@param secondOverrideAttrs	the overrides on the first set
		@param pattern1				count in first set 
		@param pattern2				count in second set
		@param skipFirst				number from top skipped
		@param skipLast				number from bottom skipped
	*/
	virtual void ClearRowPatternStrokeOverrides(const ICellStrokeAttrData::Data& firstOverrideAttrs,
											   const ICellStrokeAttrData::Data& secondOverrideAttrs,
 											   const int32 pattern1, const int32 pattern2,
 											   const int32 skipFirst, const int32 skipLast) = 0;
	/**
		INTERNAL USE ONLY
	 	The following function clears the STROKE overrides which intersect with alternating row or column STROKE pattern
		Note: This function is called when using the table alternating pattern UI, there is no use otherwise
		@param firstOverrideAttrs  		the overrides on the first set
		@param secondOverrideAttrs	the overrides on the first set
		@param pattern1				count in first set 
		@param pattern2				count in second set
		@param skipFirst				number from top skipped
		@param skipLast				number from bottom skipped
	*/
	virtual void ClearColumnPatternStrokeOverrides(const ICellStrokeAttrData::Data& firstOverrideAttrs,
												  const ICellStrokeAttrData::Data& secondOverrideAttrs,
												  const int32 pattern1, const int32 pattern2,
												  const int32 skipFirst, const int32 skipLast) = 0;
	/**
		Collects the overrides in the table that intersect the table border
		Finds the attributes in findAttrs
		Returns in results

		@param findAttrs
		@param results
	*/
	virtual void	GetBorderOverridesInTable
						(const AttributeBossList* findAttrs, OverrideStateVector* results) const = 0;

	/**
		Clears the overrides which intersect the table border
		@params	The attributes to clear for each side

		Note: This function is called when using the table border UI, there is no need to call it otherwise
	*/
	virtual void	ClearOverridesIntersectingBorder(const AttributeBossList* leftSideAttrs, const AttributeBossList* topSideAttrs,
										   			 const AttributeBossList* rightSideAttrs, const AttributeBossList* bottomSideAttrs) = 0;

//---------------------------------------------------------------------------------------------------------------------------------------------
//
// Functions which answer specific questions about the selection
//
	/**
	 	Returns kTrue if IsWritingDirectionHorizontal() can be called, kFalse otherwise.
	 */
	virtual bool16	CanGetWritingDirection(void) const = 0;

	/**
	 	Returns kTrue if the Writing direction of the story the table is in is horizontal
	 */
	virtual bool16	IsWritingDirectionHorizontal(void) const = 0;

	//----- Table Dimensions
	/**
		Returns the number of the row in which the selection lies as seen by the user.
		For example if two rows are merged together they are seen as one row by the user.
		@return the current row as seen by the user (1 >= result <= GetUserNumRowsInTable()).
		@see GridAddress
	*/
	virtual UserRowNumber	GetUserCurrentRowNumber(void) const = 0;

	/**
		Returns the number the column in which the selection lies as seen by the user.
		For example if two columns are merged together they are seen as one column to the user.
		@return the current column as seen by the user (1 >= result <= GetUserNumColsInTable()).
		@see GridAddress
	*/
	virtual int32	GetUserCurrentColNumber(void) const = 0;
	/**
		Returns kTrue if GetTextFramesSpannedBySelection() can be called, kFalse otherwise.
	*/
	virtual bool16					CanGetTextFramesSpannedBySelection() const = 0;
	/**
		Returns a collection of ITextFrameColumn interface pointers to each
		text frame touched by the selection.
		@return a collection of ITextFrameColumn interface pointers to each
		text frame touched by the selection.
		@postcondition delete the returned K2Vector pointer before it goes out of scope.
	*/
	virtual K2Vector<ITextFrameColumn*>*	GetTextFramesSpannedBySelection() const = 0;

	/**
		The following functions are used to find the span of the smallest/largest merged cell in the selection
		should only be used by the ui when calculating the min and max values for a edit box
	*/
	virtual bool16 	CanGetSpanInformationFromSelection() const = 0;
	virtual int32 	GetHSpanSmallestHorizMergedCellInSelection() const = 0;
	virtual int32 	GetHSpanLargestHorizMergedCellInSelection() const = 0;
	virtual int32 	GetVSpanSmallestVertMergedCellInSelection() const = 0;
	virtual int32 	GetVSpanLargestVertMergedCellInSelection() const = 0;

	/** Returns the model row number that corresponds with the row number and row type as the user see it.
		USED ONLY BY THE GOTOROW DIALOG

		@param	int32 row number as the user sees it (1-based)
		@param  ITableSuite::UserRowNumber::RowType (eHeader, eFooter, eBody)

		@precondition rowNum > currentSelectionModel.TotalRows.start && rowNum  <= currentSelectionModel.TotalRows.End
		@postcondition result >= currentSelectionModel.TotalRows.start && result < currentSelectionModel.TotalRows.End
	*/
	virtual bool16 CanGetUserRowSelection(int32 rowNum) const = 0;
	virtual int32 GetUserRowSelection(const int32 rowNum, const ITableSuite::UserRowNumber::RowType rowType) const = 0;

	/** Returns true if this selection is in the header set
		Note:  Will return false if the selection spans all three sets (ie is a whole table selection)
	*/
	virtual bool16 IsHeaderSelection() const = 0;

	/** Returns true if this selection is in the footer set
		Note:  Will return false if the selection spans all three sets (ie is a whole table selection)
	*/
	virtual bool16 IsFooterSelection() const = 0;

	/** Returns true if this selection is the whole table
		Note:  IsHeaderSelection and IsFooterSelection will return false if this is true
	*/
	virtual bool16 isWholeTableSelected() const = 0;

	/**
		Returns true if you can get the max/min row size of the selecton
		@return bool16 true if you can get the max/min row size of the selecton
	 */
	virtual bool16 CanGetMaxMinRowSizeOfSelection() const = 0;

	/**
		Finds the row in the selection with the maximum row size
		@return PMReal the maximum row size
	 */
	virtual PMReal GetMaxRowSizeOfSelection() const = 0;

	/**
		Finds the row in the selection with the minumun row size
		@return PMReal the minumun row size
	 */
	virtual PMReal GetMinRowSizeOfSelection() const = 0;

	/**
		Returns the sides of the cells which are active in the selection (sides can be set using the stroke proxy)
		@return sides selected
	*/
	virtual bool16 CanGetSelectionActiveStrokes(void) const = 0;
	virtual Tables::ESelectionSides GetSelectionActiveStrokes(void) = 0;


//---------------------------------------------------------------------------------------------------------------------------------------------
//
// Functions which answer questions about table structure
//

	/**
		Returns true if you can get the properties of the table
		@return bool16 true if you can get the properties of the table
	 */
	virtual bool16	CanGetTableProperties(void)const = 0;
	/**
		Returns true if you there is a header in the table and you can make a selection in it
		@return bool16 true if you there is a header in the table and you can make a selection in it
	 */
	virtual bool16	CanGetHeader(void)const = 0;
	/**
		Returns true if you there is a footer in the table and you can make a selection in it
		@return bool16 true if you there is a footer in the table and you can make a selection in it
	 */
	virtual bool16	CanGetFooter(void)const = 0;

	/**
		Returns the number of rows in the underlying grid of the selected table.
		For example if a table was created with 5 rows then two of
		the rows were merged together the user would see 4 rows
		but the number of rows in the underlying grid would still be 5.
		@return the number of rows in the underlying grid of the selected table.
		@see GridAddress
	*/
	virtual int32	GetNumRowsInTable(void)const = 0;

	/**
		Returns the number of columns in the underlying grid of the selected table.
		For example if a table was created with 5 columns then two of
		the columns were merged together the user would see 4 columns
		but the number of columns in the underlying grid would still be 5.
		@return the number of columns in the underlying grid of the selected table.
		@see GridAddress
	*/
	virtual int32	GetNumColsInTable(void)const = 0;

	/**
		Returns the number of header rows in this table
		@return	int32	the number of header rows in the table
	*/
	virtual int32	GetNumHeaderRowsInTable(void)const = 0;

	/**
		Returns the number of footer rows in this table
		@return	int32	the number of footer rows in the table
	*/
	virtual int32	GetNumFooterRowsInTable(void)const = 0;

	/**
		Returns the number of rows in the selected table as seen by the user.
		If two rows are merged together they count as one row to the user.
		@return the number of rows in the selected table as seen by the user.
		@see GridAddress
	*/
	virtual int32	GetUserNumRowsInTable(void)const = 0;

	/**
		Returns the number of columns in the selected table as seen by the user.
		If two columns are merged together they count as one column to the user.
		@return the number of columns in the selected table as seen by the user.
		@see GridAddress
	*/
	virtual int32	GetUserNumColsInTable(void)const = 0;

	/**
		Returns true if table which the selection is in has any Header rows.
		@return bool16 	true if the table contains headers
	*/
	virtual bool16	TableContainsHeaders(void)const = 0;

	/**
		Returns true if table which the selection is in has any Footer rows.
		@return bool16 	true if the table contains footers
	*/
	virtual bool16	TableContainsFooters(void)const = 0;


//---------------------------------------------------------------------------------------------------------------------------------------------
//
// Actions to create a table.  Done only from a text selection
//
	/**
	 	Returns true if you can insert a new table
	 	@return bool16	 true if you can insert a table
	 */
	 virtual bool16 CanInsertTable() const = 0;

	/**
	 	Inserts a new table at the current text selection location

		@param numRows number of rows
		@param numCols number of columns
		@param headerRows number of header rows
		@param footerRows number of footer rows
        @param [IN] tableStyleUID optional, the table style for the new table,
        if this is not provided, the default table style is used
        @param direction the direction for the new table
	 */
	 virtual void InsertTable(const int32 numRows, const int32 numCols, const int32 headerRows, const int32 footerRows,
                              const UID& tableStyleUID = kInvalidUID, const Tables::EDirection direction = Tables::eLTR) = 0;

//---------------------------------------------------------------------------------------------------------------------------------------------
//
// Actions to convert text to table.  Done only from a text selection
//
	/**
	 	Returns true if you can convert the selected text to a table
		 @return	  bool16  true if can convert text to a table
	 */
	 virtual bool16 CanConvertTextToTable() const = 0;

	/**
	 	Converts the current text selection to a table at the selection's location

		@param colSeparator column separator to delimit end of column
		@param rowSeparator row separator to delimit end of row
		@param userNumCols number of columns specified by user, used if rowSeparator==colSeparator
		@param tableStyleUID [IN] optional, the table style for the new table, if
		this is <code>kInvalidUID</code>, the root table style is used  
		@return UIDRef the UIDRef of the table created
	 */
	 virtual UIDRef ConvertTextToTable(const PMString colSeparator="\t", const PMString rowSeparator="\r", 
                                       const int32 userNumCols=1,
									   const UID& tableStyleUID = kInvalidUID) const = 0;
	/**
	 	Same as above except parameters 1 and 2 are lists instead of single strings

		@param colSeparator list of column separators to delimit end of column
		@param rowSeparator list of row separators to delimit end of row
		@param userNumCols number of columns specified by user, used if rowSeparator==colSeparator 
		@param tableStyleUID [IN] optional, the table style for the new table, if
		this is <code>kInvalidUID</code>, the root table style is used  
		@return UIDRef the UIDRef of the table created
	 */
	 virtual UIDRef ConvertTextToTable(const K2Vector<PMString>& colSeparators, const K2Vector<PMString>& rowSeparators, 
                                       const int32 userNumCols=1,
									   const UID& tableStyleUID = kInvalidUID) const = 0;

	/**
	 	Returns true if any footnotes were found in the selection
		 @return	  bool16  true if any footnotes were found in the selection
	 */
	 virtual bool16 AnyFootnotesInSelection() const = 0;


 	/**
	 	Returns true if you can get the table direction
	 	@return bool16	 true if you can get direction
	 */
   virtual bool16    CanGetTableDirection(void) const = 0;

	/**
	 	Get direction of table

        @return EDirection the direction of the table
	 */
    virtual Tables::EDirection    GetTableDirection(void) const = 0;

	/**
	 	Returns true if you can change the table direction
	 	@return bool16	 true if you can change the table direction
	 */
    virtual bool16    CanChangeTableDirection(void) const = 0;

	/**
	 	Change direction of table

        @param NewDirection the direction for the new table
	 */
    virtual void    ChangeTableDirection(Tables::EDirection NewDirection) const = 0;

	
	/**
		Returns kTrue if rows can be moved to destination row, kFalse otherwise.
		
		@param toRow  The destination row

		@return bool16 return kTrue if rows can be moved to destination row, kFalse otherwise

	*/
	virtual bool16	CanMoveRows	(int32 toRow) const = 0;

	/** Method to move row(s) in a table
		
		@param sourceTable specifies the table within which rows are to be moved
		@param fromArea specifies the grid area which is to be moved
		@param toRow specifies the row where the selected rows are to be moved
		@param pos specifies the relative position with respect to toRow
		@param duplicateFlag specifies whether rows need to be duplicated or not

	*/
	virtual void	MoveRows	(ITableModel* sourceTable, GridArea fromArea,  int32 toRow, Tables::ERelativePosition, bool16 duplicateFlag) = 0;

	/**
		Returns kTrue if columns can be moved to destination column, kFalse otherwise.
		
		@param toColumn  The destination column

		@return bool16 return kTrue if columns can be moved to destination column, kFalse otherwise

	*/
	virtual bool16	CanMoveColumns	(int32 toColumn) const = 0;

	/** Method to move column(s) in a table
		
		@param sourceTable specifies the table within which columns are to be moved
		@param fromArea specifies the grid area which is to be moved
		@param toColumn specifies the column where the selected columns are to be moved
		@param pos specifies the relative position with respect to toColumn
		@param duplicateFlag specifies whether columns need to be duplicated or not

	*/
	virtual void	MoveColumns	(ITableModel* sourceTable, GridArea fromArea,  int32 toColumn, Tables::ERelativePosition pos, bool16 duplicateFlag) = 0;

	/** Returns kTrue if row(s) can be pasted after/before the selected area in the table, kFalse otherwise.

		@param isPasteAfter specifies whether the row is to be pasted after the selected area or before the selected area

		@return bool16 return kTrue if row(s) can be pasted

	*/
	virtual bool16  CanPasteRows(bool16 isPasteAfter) const = 0; 
	
	/** Returns kTrue if ConvertCellsType() can be called on selected cells, kFalse otherwise.
		@param	destType	cell type to be converted into
	*/
	virtual bool16	CanConvertCellsType(CellType destType) const = 0;

	/** Method to convert the type of cells in sellection
		@param	destType	cell type to be converted into
		@param	tryToPreserveData	if true, the data is preserved into the cell after converion, if possible.
	*/
	virtual void	ConvertCellsType(CellType destType, bool16 tryToPreserveData) = 0;

	/** Returns kTrue if column(s) can be pasted after/before the selected area in the table, kFalse otherwise.

		@param isPasteAfter specifies whether the column is to be pasted after the selected area or before the selected area

		@return bool16 return kTrue if column(s) can be pasted

	*/
	virtual bool16  CanPasteColumns(bool16 isPasteAfter) const = 0;

	/** Returns the grid area of selected region inside table

		@return GridArea

	*/
	virtual GridArea GetFocussedArea() const = 0;

	/** Returns kTrue if the grid area of selected region is valid area, kFalse otherwise.

		@return bool16 return kTrue if a valid grid area can be returned

	*/
	virtual bool16 CanGetFocussedArea() const = 0;

	/** Returns kTrue if we can paste page item into the grid area of selected region, kFalse otherwise.

	@return bool16 return kTrue if we can paste page item into the grid area of selected region

	*/
	virtual bool16	CanPastePageItem() const = 0;

	/** Method to paste a page item into a graphic cell. Call CanPastePageItem before this operation

		@param	anchor		GridAddress of destination cell
		@param	pageItemUID	UID of object to be pasted into the cell
		@param	preventCopy	The object would not be copied, just removed from the source and pasted here. This is not cut-paste.
		It should be used, only if object is already in the scrap database.

	*/
	virtual void PastePageItem(const GridAddress &anchor, UIDRef pageItemUID, bool16 preventCopy) = 0;

	/** Returns kTrue if there is any text cell in the grid area of selected region, kFalse otherwise
	
		@return bool16	Returns kTrue if there is any text cell in the grid area of selected region
	
	*/
	virtual bool16		IsAnyTextCellSelected() const = 0;

	/** Returns kTrue if there is any graphic cell in the grid area of selected region, kFalse otherwise

	@return bool16	Returns kTrue if there is any graphic cell in the grid area of selected region

	*/
	virtual bool16		IsAnyGraphicCellSelected() const = 0;
};

#endif //__ITableSuite__

