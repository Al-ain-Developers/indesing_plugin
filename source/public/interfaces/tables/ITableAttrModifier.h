//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableAttrModifier.h $
//  
//  Owner: ???
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
#ifndef __ITableAttrModifier__
#define __ITableAttrModifier__

#include "TablesID.h"
#include "TableTypes.h"

#include "ICellStrokeAttrData.h"

class AttributeBossList;

/** Abstract interface to manipulate table attributes directly. 
	In practice client code would use ITableCommands to provide 
	for undo-able change to the table model. There should be counterparts 
	on ITableCommands of the significant  methods on this interface.
*/
class ITableAttrModifier : public IPMUnknown {

public:
	///	kDefaultIID
	enum  { kDefaultIID = IID_ITABLEATTRMODIFIER };
	
	//-------------------------------------------------------------------------------
	/**@name	Row attribute modifiers.  */
	//@{-----------------------------------------------------------------------------
	
	/** Applies overrides to rows from rows.start to 
		rows.start + rows.count  

		@param rows identifies range of rows to apply row-attribute overrides to
		@param these collection of boss objects specifying (by their ClassID) row attribute-overrides to be applied
		@precondition rows should be a valid range within the table model
	*/
	virtual void		ApplyRowOverrides(const RowRange& rows, const AttributeBossList* these) = 0;
						
	/** Clears overrides in to rows from rows.start to 
		rows.start + rows.count  

		@param rows identifies range of rows for which row-overrides should be removed
		@param these collection of boss objects specifying (by their ClassID) row attribute-overrides to remove
		@precondition rows should be a valid range within the table model
	*/
	virtual void		ClearRowOverrides(const RowRange& rows, const AttributeBossList* these) = 0;

	/** Sets the rows heights of rows from rows.start to 
		rows.start + rows.count to newHeight 

		@param rows identifies range of rows for size change
		@param newHeight specifies the new height and minimum height for the given rows
		@precondition rows should be a valid range within the table model
		@precondition newHeight should be &gte; 0
	*/
	virtual void		ResizeRows(const RowRange& rows, const PMReal& newHeight) = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name	Columns attribute modifiers.  */
	//@{-----------------------------------------------------------------------------

	/** Applies overrides to columns from cols.start to cols.start + cols.count 
	
	  @param cols identifies range of columns to apply column-attribute overrides to
	  @param these collection of boss objects specifying (by their ClassID) attribute-overrides to be applied
	*/
	virtual void		ApplyColOverrides(const ColRange& cols, const AttributeBossList* these) = 0;

	/** Clears overrides in columns from cols.start to cols.start + cols.count  
	  @param cols specifies range of columns on which to remove column-attribute overrides
	  @param these collection of boss objects specifying (by their ClassID) attributes for which the override is to be cleared
	*/
	virtual void		ClearColOverrides(const ColRange& cols, const AttributeBossList* these) = 0;

	/** Sets the column widths of columns from  cols.start to cols.start + cols.count to newWidth 
	  @param cols specifies range of columns for change in size
	  @param newWidth specifies the new width setting for this column range
	*/
	virtual void		ResizeCols	 (const ColRange& cols, const PMReal& newWidth) = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name	Cell attribute modifiers.  */
	//@{-----------------------------------------------------------------------------

	/** Applies overrides to cells in given area.
		@param cells an area that delimits the target cells: method operates upon the cells contained wholly within this grid area
		@param these list of boss objects, specifying (by their ClassID) attributes to be applied to target cells
		@param clearRedundantOverrides whether to clear overrides in the attribute boss list that are redundant with the applied
		cell style.

	*/
	virtual void		ApplyCellOverrides(const GridArea& cells, const AttributeBossList* these,bool16 clearRedundantOverrides = kTrue) = 0;

	/** Clears overrides applied to cells .
		@param cells an area that delimits the target cells: method operates upon the cells contained wholly within this grid area
		@param these  list of boss objects, specifying (by their ClassID) attributes to remove 
	*/
	virtual void		ClearCellOverrides(const GridArea& cells, const AttributeBossList* these) = 0;
						
	/** Applies strokes to cells. 
		@param area an area that delimits the target cells: cells contained wholly within this grid area are target for operation
		@param data used to specify sides and other properties of the stroke that are to be applied. For more detail consult the
			documentation on ITableCommands.
		@param clearRedundantOverrides whether to clear overrides in the attribute boss list that are redundant with 
			the applied cell style.  
	*/
	virtual void		ApplyCellStrokes(const GridArea& area, const ICellStrokeAttrData::Data& data,bool16 clearRedundantOverrides = kTrue) = 0;

	/** Clears cell strokes.
		@param area an area that delimits the target cells: cells contained wholly within this grid area are target for operation
		@param data used to specify sides and other properties of the stroke that are to be cleared. 
	*/
	virtual void		ClearCellStrokes(const GridArea& area, const ICellStrokeAttrData::Data& data) = 0;

	/** Used by cell strokes apply code for draw priority of stroke overrides. 
	*/
	virtual int32		GetStrokesApplyTick(void) const = 0;

	/** For internal use only.
		Used by cell strokes UI apply code to ensure that multiple applies have the same
		draw priority. If freeze is kTrue then the stroke apply tick is incremented
		and frozen until it is unfrozen with a freeze value of kFalse. The frozen state
		is not persistent. So it is essential to hold a reference to this interface for
		the scope of the freeze.
	*/
	virtual	void		FreezeStrokesApplyTick(bool16 freeze) = 0;
	
	/**
	 * Applies the cell style to the given <code>GridArea</code>.  If the style
	 * priority is -1, then a new priority value will be calculated that is 
	 * greater than any priority of all cells that are adjacent to <code>areaToSet</code>.
	 *
	 * @param cellStyle [IN] the <code>UID</code> of the cell style to
	 * apply, this style should live on the same database as the
	 * table
	 * @param areaToSet [IN] the <code>GridArea</code> to apply the cell
	 * style to
	 * @param priority [IN] optional, the style priority
	 */
	virtual void ApplyCellStyle(const UID& cellStyle, const GridArea& areaToSet, int32 priority = -1) = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name	Table attribute modifiers. */
	//@{
	//-------------------------------------------------------------------------------

	/** Applies table attributes
		@param these list of boss objects, specifying (by their ClassID) attributes to apply
	*/
	virtual	void		ApplyTableOverrides(const AttributeBossList* these) = 0;

	/** Clears specified attribute-overrides 
		@param these list of boss objects, specifying (by their ClassID) attributes to remove overrides from
	*/
	virtual	void		ClearTableOverrides(const AttributeBossList* these) = 0;

	/** Method to remove (releasing) all the attributes in the underlying boss list holding table-level attributes. 
	*/
	virtual	void		ClearAllTableOverrides() = 0;

	/** Sets this tables style. 
	*/
	virtual	void		SetTableStyle(UID tableStyle) = 0;

	/** Returns the table style of this table 
	*/
	virtual	UID			GetTableStyle(void) const = 0;
	//@}-----------------------------------------------------------------------------

	/** Scales attributes.
	*/
	virtual void		Scale(const PMReal& xScale, const PMReal& yScale) = 0;
};

#endif // __ITableAttrModifier__
