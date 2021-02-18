//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableAttrAccessor.h $
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
#ifndef __ITableAttrAccessor__
#define __ITableAttrAccessor__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"
#include "ITableLineType.h"
#include "PMRect.h"
#include "DataWrapper.h"
#include "ICellStrokeAttrData.h"
#include <map>

//----- Forward declarations
class AttributeBossList;
class ITableAttrRealNumber;
class ITableAttributes;


typedef std::pair<PMReal, ITableLineType::SType> TableAttrStrokeWeightAndType;
DECLARE_BASE_TYPE(TableAttrStrokeWeightAndType);
typedef K2Vector<TableAttrStrokeWeightAndType>	TableAttrStrokeWeightAndTypeList;

//===================================================================================
/** Interface to access attributes in the table model.

	@author 	Joe Shankar
 */
//===================================================================================
class ITableAttrAccessor : public IPMUnknown
{
public:
		/// kDefaultIID 
		enum { kDefaultIID = IID_ITABLEATTRACCESSOR };

		//-------------------------------------------------------------------------------
		/**@name	Cell Styles. */
		//@{-----------------------------------------------------------------------------
		/**
		 * Gets the attributes for a given cell that are from the cell style
		 * applied to the cell.  Its not sufficient to simply get the attributes
		 * of the cell style to determine which attributes are actually being
		 * shown because for a given cell its cell strokes may come from the
		 * cell style applied to the cell, or its neighbor.  The attributes 
		 * returned by this function are not necessarily the attributes used
		 * in the cell.  To get what is actually used you can call
		 * <code>GetAttributesFromRegionalCellStyle</code>, this function,
		 * and <code>QueryCellOverrides</code> to get all the cell attributes
		 * applied to a single cell.
		 *
		 * @param element [IN] the address of the cell to get the cell style
		 * attributes from
		 * @param runArea [OUT] optional, the run area for the cell style 
		 * attributes
		 * @return a list containing the cell style attributes for the given 
		 * cell, with its stroke attributes resolved with the stroke attributes
		 * of cell styles from adjacent cells.
		 */
		virtual const AttributeBossList* GetAttributesFromCellStyle(const GridAddress& element, GridArea* runArea = nil) const = 0;
		
		/**
		 * Gets the attributes for a given cell that are from the regional cell 
		 * style that is applied through the table style.  Its not sufficient to
		 * simply get the attributes of the regional cell style to determine 
		 * which attributes are actually being shown because for a given cell 
		 * its cell strokes may come from the regional cell style applied to the
		 * cell, or its neighbor.  The attributes returned by this function are 
		 * not necessarily the attributes used in the cell.  To get what is 
		 * actually used you can call this function, 
		 * <code>GetAttributesFromCellStyle</code>, and 
		 * <code>QueryCellOverrides</code> to get all the cell attributes
		 * applied to a single cell.
		 *
		 * @param element [IN] the address of the cell to get the regional cell
		 * style attributes from
		 * @param runArea [OUT] optional, the run area for the regional cell 
		 * style attributes
		 * @return a list containing the regional cell style attributes for the 
		 * given  cell, with its stroke attributes resolved with the stroke 
		 * attributes of regional cell styles from adjacent cells.
		 */
		virtual const AttributeBossList* GetAttributesFromRegionalCellStyle(const GridAddress& element, GridArea* runArea = nil) const = 0;
		
		/**
		 * Gets the cell style for the given <code>GridAddress</code>.  Because
		 * cells do not necessarily have a style, this function can
		 * return <code>kInvalidUID</code>, which is treated the same as the
		 * root cell style.
		 *
		 * @param element [IN] the <code>GridAddress</code> of the
		 * cell to retrieve the style from, this should be a valid
		 * grid address of the table
		 * @param priority [OUT] optional, the cell style priority
		 * @param runArea [OUT] optional, the run area
		 * @return the <code>UID</code> of the applied cell style,
		 * may be <code>kInvalidUID</code>
		 */
		virtual UID GetCellStyle(const GridAddress& element, int32* priority = nil, GridArea* runArea = nil) const = 0;
		
		/**
		 * Gets the regional cell style for the given <code>GridAddress</code>.
		 *
		 * @param element [IN] the address of the cell
		 * @param runArea [OUT] optional, the regional style's area
		 * @return the regional cell style for the given cell
		 */
		virtual UID GetRegionalCellStyle(const GridAddress& element, GridArea* runArea = nil) const = 0;
		
		/**
		 * Queries the cell style and regional cell style for a particular attribute.
		 * The attriubte returned by this function may not be the attribute that
		 * is visible, an override may be applied to the cell.
		 *
		 * @param [IN] the cell to get the attribute for
		 * @param whichAttr [IN] the cell attribute to retrieve
		 * @param iid [IN] the attribute's <code>PMIID</code>
		 * @param surroundingRun [IN] optional, the surrounding run
		 * @return the attribute for the cell after resolving the cell and regional cell style
		 * hierarchies, may be nil if the attribute is not defined
		 */
		virtual const IPMUnknown* QueryCellStyleForAttr(const GridAddress& element, const ClassID& whichAttr, const PMIID& iid, GridArea* surroundingRun = nil) const = 0;
		//@}-----------------------------------------------------------------------------
		
		//-------------------------------------------------------------------------------
		/**@name	Row attributes. */
		//@{-----------------------------------------------------------------------------
		/** Returns row attribute fully resolving inheritance of table 
			style, table attribute overrides and rules.

			@param row 		Row for which attribute is to be returned.
			@param whicAttr ClassID of the attribute boss of interest
			@param iid		Interface ID of interface on attribute boss to be returned. 
							The result may be cast to the 'type' identified by iid.													

		*/
		virtual const IPMUnknown* QueryRowAttribute(int32 row, ClassID whichAttr, PMIID iid) const = 0;

		/** Query for a row override WITHOUT any inheritance resolution. 
			Returns interface ptr that has reference count incremented.

			@param row 		row for which attribute is to be returned.
			@param whicAttr ClassID of the attribute boss.
			@param iid		Interface ID of interface on attribute boss to be returned. 
							The result may be cast to the 'type' identified by iid.
		*/
		virtual const IPMUnknown* QueryRowOverride(int32 row, ClassID whichAttr, PMIID id) const = 0;

		/** Returns all row overrides WITHOUT any inheritance resolution.

			@param row 			Row for which attribute is to be returned.
			@param runLength	Value will be returned if non nil. Return value is the count
								of the rows starting with 'row' that have the same attribute.
								This can be used for optimizations.
		*/
		virtual DataWrapper<AttributeBossList> QueryRowOverrides(int32 row, int32* runLength = nil) const = 0;
		//@}-----------------------------------------------------------------------------

		//-------------------------------------------------------------------------------
		/**@name	Column attributes. */
		//@{-----------------------------------------------------------------------------
		/** Query for column attribute, fully resolving inheritance of table 
			style, table attribute overrides and rules. 	
			Returns interface ptr that has reference count incremented.


			@param col 		Column for which attribute is to be returned.
			@param whicAttr ClassID of the attribute boss of interest
			@param iid		Interface ID of interface on attribute boss to be returned. 
							The result may be cast to the 'type' identified by iid.
		*/
		virtual const IPMUnknown* QueryColAttribute(int32 col, ClassID whichAttr, PMIID id) const = 0;

		/** Query for a column override WITHOUT any inheritance resolution. 
			Returns interface ptr that has reference count incremented 

			@param col 		Column for which attribute is to be returned.
			@param whicAttr ClassID of the attribute boss.
			@param iid		Interface ID of interface on attribute boss to be returned. 
							The result may be cast to the 'type' identified by iid.
		*/
		virtual const IPMUnknown* QueryColOverride(int32 col, ClassID whichAttr, PMIID id) const = 0;

		/** Returns all column overrides WITHOUT any inheritance resolution.

			@param col 			Column for which attribute is to be returned.
			@param runLength	Value will be returned if non nil. Return value is the count
								of the columns starting with 'col' that have the same attribute.
								This can be used for optimizations.
			@return				collection of attribute boss ClassIDs
		*/
		virtual DataWrapper<AttributeBossList> QueryColOverrides(int32 col, int32* runLength = nil) const = 0;
		//@}-----------------------------------------------------------------------------

		//-------------------------------------------------------------------------------
		/**@name	Cell attributes. */
		//@{-----------------------------------------------------------------------------
		/**	Returns cell attribute fully resolving inheritance of table 
			style, table attribute overrides.

			@param element				Grid element  for which attribute is to be returned.
			@param whicAttr 			ClassID of the attribute boss.
			@param iid					Interface ID of interface on attribute boss to be returned. 
										The result may be cast to the 'type' identified by iid.
			@param surroundingRun		Value will be returned if non nil. Return value is the absolute value
										of the run  that the element is in. All elements in this range have the same
										value for whichAttr. This can be used for optimizations.
			@param isPreserveOverride	Preserve local overrides ON or OFF. This is used to govern
										whether cell overrides are to be taken into consideration or not
										(required in EPUB/HTML export.)
		*/
		virtual const IPMUnknown* QueryCellAttribute(const GridAddress& element, ClassID whichAttr, PMIID iid , GridArea* surroundingRun = nil, bool16 isPreserveOverride = kTrue) const = 0;

		/**	Returns cell override WITHOUT any inheritance resolution. Returns nil if 
			the attribute is not overriden.

			@param element			Grid element for which attribute is to be returned.
			@param whicAttr 		ClassID of the attribute boss.
			@param iid				Interface ID of interface on attribute boss to be returned. 
									The result may be cast to the 'type' identified by iid.
			@param surroundingRun	Will be set if non nil. Is the absolute value of the run 
									that the element is in. All elements in this range have the same
									value for whichAttr. This can be used for optimizations.
		*/		
		virtual const IPMUnknown* QueryCellOverride(const GridAddress& element, ClassID whichAttr, PMIID iid, GridArea* surroundingRun = nil) const = 0;

		/** Returns all cell overrides WITHOUT any inheritance resolution. 

			@param element			Grid element for which attribute is to be returned.
			@param surroundingRun	Value will be returned if non nil. Return value is the absolute value
									of the run  that the element is in. All elements in this range have the same
									value for whichAttr. This can be used for optimizations.
		*/		
		virtual DataWrapper<AttributeBossList> QueryCellOverrides(const GridAddress& element, GridArea* surroundingRun = nil) const = 0;

			/** Nested call-back class for visiting cell override runs via IterateCellOverrides(). 
			*/
			class CellOverridesCallback
			{
			public:
				/** 
						@param runArea		Absolute GridArea of current run.
						@param overrides	Cell overrides of runArea
						
						@return				Returning kFalse will stop iteration.
											Return kTrue to continue processing runs.
				 */
				virtual bool16 VisitRun(const GridArea& runArea, const AttributeBossList* overrides) = 0;
			};
		
		/**
			Function to walk all cell overrides efficiently.
			@param callBack		Callback for iterating cell overrides. callBack.VisitRun is 
								called for each run area See CellOverridesCallback for
								more info.				
		 */
		virtual void IterateCellOverrides(CellOverridesCallback& callBack) const = 0;

			/** Nested call-back class for visiting cell stroke override runs via IterateCellOverrides(). 
			*/
			class CellStrokeOverridesCallback
			{
			public:
				/** 
						@param runArea		Absolute GridArea of current run.
						@param overrides	Cell stroke overrides of runArea 
						
						@return				Returning kFalse will stop iteration.
											Return kTrue to continue processing runs.
				 */
				virtual bool16 VisitRun(const GridArea& runArea, const ICellStrokeAttrData::Data& overrides) = 0;
			};

		/**
			Function to walk all cell stroke overrides efficiently.
			@param patternType	Whether we are searching or a row or a column override
			@param callBack		Callback for iterating cell overrides. callBack.VisitRun is 
								called for each run area See CellOverridesCallback for
								more info.				
		 */
		virtual void IterateCellStrokeOverrides(Tables::ERowColumn patternType, CellStrokeOverridesCallback& callBack) const = 0;

		//@}-----------------------------------------------------------------------------

		 //-------------------------------------------------------------------------------
		/**@name	Table attributes. */
		//@{-----------------------------------------------------------------------------
		/** Returns the table style of this table */
		virtual	UID							GetTableStyle(void) const = 0;

		/** Query for table attribute fully resolving inheritance of table 
			style and table attribute overrides. 
			Get back interface ptr which has reference count incremented.

			@param whicAttr ClassID of the attribute boss.
			@param iid		Interface ID of interface on attribute boss to be returned. 
							The result may be cast to the 'type' identified by iid.
			@return reference-count incremented interface ptr
		*/
		virtual const IPMUnknown* 			QueryTableAttribute(ClassID whichAttr, PMIID iid) const = 0;

		/** Acquire the list of table attributes after resolving table style and overrides. 
			Caller does <b>not</b> own the storage here and should not attempt to release
			as this is not a reference-bumped ptr that would be returned from a query.
			@return reference to list of table attributes fully resolved.
		*/
		virtual const AttributeBossList*	GetTableAttributesResolved(void) const = 0;

		/** Query for the list of table attribute overrides. Caller should call release.
			@return reference-count incremented pointer.
		*/
		virtual const ITableAttributes*		QueryTableOverrides(void) const = 0;		
		//@}-----------------------------------------------------------------------------

		//-------------------------------------------------------------------------------
		/**@name	Stroke & fill attributes. */
		//@{-----------------------------------------------------------------------------
		/** Determine the stroke weight at a given location for specified edge.
			@param	element specifies location within underlying grid 
			@param	edge  specifies whether  left, top right or bottom
			@param	OUT: isOverride	whether result is an override attribute
			@param	OUT: Only Valid is isOverride is true, it is the runArea area over the attribute if it is an override
		*/
		virtual PMReal					GetElementStrokeWeight(const GridAddress& element, Tables::ECellEdge edge, bool16 *isOverride = nil, GridArea *runArea = nil) const = 0;		
								
		/** Determine the stroke type associated with specified element and given edge.
			@param	element specifies location within underlying grid 
			@param	edge specifies whether left, top right or bottom
			@return line type as one of enumerated values on ITableLineType interface
			@param	OUT: isOverride	whether result is an override attribute
			@param	OUT: Only Valid is isOverride is true, it is the runArea area over the attribute if it is an override
		*/
		virtual ITableLineType::SType	GetElementStrokeType(const GridAddress& element, Tables::ECellEdge edge, bool16 *isOverride = nil, GridArea *runArea = nil) const = 0;

		/** Determine the stroke color for the specified element on the given edge.
			@param element specifies a location within underlying grid
			@return stroke color as a UID for given edge
			@param	OUT: isOverride	whether result is an override attribute
			@param	OUT: Only Valid is isOverride is true, it is the runArea area over the attribute if it is an override
		*/
		virtual UID						GetElementStrokeColor(const GridAddress& element, Tables::ECellEdge edge, bool16 *isOverride = nil, GridArea *runArea = nil) const = 0;

		/** Determine for stroke tint associated with a grid-element.
			This will use inheritance resolution to take account of any overrides applied.
			@param	element specifies a location within underlying grid
			@param	edge  specifies whether  left, top right or bottom
			@return the stroke-tint as  real-numbered value
			@param	OUT: isOverride	whether result is an override attribute
			@param	OUT: Only Valid is isOverride is true, it is the runArea area over the attribute if it is an override
		*/
		virtual PMReal					GetElementStrokeTint(const GridAddress& element, Tables::ECellEdge edge, bool16 *isOverride = nil, GridArea *runArea = nil) const = 0;

		/** Determine whether the grid-element at the given address has an associated stroke overprint.
			This will use inheritance resolution to take account of any overrides applied.
			@param	element co-ordinate of cell of interest
			@param edge specifies which edge of the cell are to be considered
			@return kTrue if the stroke associated with given location has overprint, kFalse otherwise
			@param	OUT: isOverride	whether result is an override attribute
			@param	OUT: Only Valid is isOverride is true, it is the runArea area over the attribute if it is an override
		 */
		virtual bool16					GetElementStrokeOverprint(const GridAddress& element, Tables::ECellEdge edge, bool16 *isOverride = nil, GridArea *runArea = nil) const = 0;

		/** Determine the stroke gap color for the specified element on the given edge.
			@param element specifies a location within underlying grid
			@return stroke gap color as a UID for given edge
			@param	OUT: isOverride	whether result is an override attribute
			@param	OUT: Only Valid is isOverride is true, it is the runArea area over the attribute if it is an override
		*/
		virtual UID						GetElementStrokeGapColor(const GridAddress& element, Tables::ECellEdge edge, bool16 *isOverride = nil, GridArea *runArea = nil) const = 0;

		/** Determine for stroke gap tint associated with a grid-element.
			This will use inheritance resolution to take account of any overrides applied.
			@param	element specifies a location within underlying grid
			@param	edge specifies whether left, top right or bottom
			@return the stroke-gap-tint as  real-numbered value
			@param	OUT: isOverride	whether result is an override attribute
			@param	OUT: Only Valid is isOverride is true, it is the runArea area over the attribute if it is an override
		*/
		virtual PMReal					GetElementStrokeGapTint(const GridAddress& element, Tables::ECellEdge edge, bool16 *isOverride = nil, GridArea *runArea = nil) const = 0;

		/** Determine whether the grid-element at the given address has an associated stroke gap overprint.
			This will use inheritance resolution to take account of any overrides applied.
			@param	element co-ordinate of cell of interest
			@param edge specifies which edge of the cell are to be considered
			@return kTrue if the stroke associated with given location has gap overprint, kFalse otherwise
			@param	OUT: isOverride	whether result is an override attribute
			@param	OUT: Only Valid is isOverride is true, it is the runArea area over the attribute if it is an override
		 */
		virtual bool16					GetElementStrokeGapOverprint(const GridAddress& element, Tables::ECellEdge edge, bool16 *isOverride = nil, GridArea *runArea = nil) const = 0;

		enum { kLowestPriority = 0 };
		/**
			Returns the stroke draw priority. Larger number draws on top of smaller ones.
			@return stroke-draw priority.
		*/
		virtual int32					GetElementStrokePriority(const GridAddress& element, Tables::ECellEdge edge) const = 0;

		/** Determine the max *effective* stroke weight for a cell's specified
			edge. For an edge to have an effective stroke it must have a
			non-zero stroke weight and a valid stroke type.
			@param	anchor, anchor location of the anchor (top-left of cell) in underlying table grid.
					see GridAddress for more information on anchors versus elements.
			@param 	edge,  specifies whether left, top right or bottom edge.
			@return max stroke weight for edge of cell.
		*/
		virtual PMReal					GetCellMaxStrokeWeight(const GridAddress& anchor, Tables::ECellEdge edge) const = 0;

		/** Fills in the swtList with *effective* stroke weight and line type
			for all elements along the specified edge of the cell. For an
			edge to have an effective stroke it must have a non-zero stroke
			weight and a valid stroke type.
			@param	anchor, anchor location of the anchor (top-left of cell) in underlying table grid.
					see GridAddress for more information on anchors versus elements.
			@param 	edge,  specifies whether left, top right or bottom edge.
			@param	swtList, the list to be filled in with Stroke Weight and LineType.
		*/
		virtual void					GetCellStrokeWeightAndType(const GridAddress& anchor, Tables::ECellEdge edge, TableAttrStrokeWeightAndTypeList* swtList) const = 0;
		
		/** Determine the max *effective* stroke weight for the left edge of
			the table. For an edge to have an effective stroke it must
			have a non-zero stroke weight and a valid stroke type.
			@return maximum stroke weight for the left edge of the first column
		*/		
		virtual PMReal					GetFirstColMaxLeftStrokeWeight() const = 0;

		/** Determine the max *effective* stroke weight for the right edge of
			the table. For an edge to have an effective stroke it must
			have a non-zero stroke weight and a valid stroke type.
			@return maximum stroke weight for the right edge of the last column
		*/		
		virtual PMReal					GetLastColMaxRightStrokeWeight() const = 0;

		/**  Determine the fill of the given anchor; see GridAddress for more information
			on anchors versus elements.
			@param	anchor location of the anchor (top-left of cell) in underlying table grid
			@return fill color as UID

		*/
		virtual UID					GetFillColor(const GridAddress& anchor) const = 0;

			/** Returns the tint of the fill for anchor.
			@param	anchor location of the anchor (top-left of cell) in underlying table grid
			@return fill-tint as real-valued number
		*/
		virtual PMReal				GetFillTint(const GridAddress& anchor) const = 0;

		/** Returns the overprint of the fill for anchor.

			@param anchor location of the anchor (top-left of cell) within the underlying grid
			@return kTrue if there is an overprint associated with the fill at the given location, kFalse otherwise
		*/
		virtual bool16				GetFillOverprint(const GridAddress& anchor) const = 0;	
		//@}-----------------------------------------------------------------------------

		//-------------------------------------------------------------------------------
		/**@name	Cell content type attributes. */
		//@{-----------------------------------------------------------------------------
		/** Might be removed.
			Returns the CellType associated with anchor.

			@param anchor		Cell whose type is to be returned.
		*/
		virtual CellType	GetCellType(const GridAddress& anchor) const = 0;

		/** Query to determine what the default cell-type
        @return 	default type of new cells that are created in this table. 
		*/
		virtual CellType 	GetDefaultCellType(void) const = 0;
		//@} -----------------------------------------------------------------------------	
		
		//-------------------------------------------------------------------------------
		/**@name	Caches. */
		//@{-----------------------------------------------------------------------------
		/**  For internal use by table model.
			@param	cols
		*/	
		virtual void ClearCaches(void) = 0;

	
		/**  For internal use by table model.
		*/	
		virtual void FirstColLeftStrokeChanged() = 0;
		virtual void LastColRightStrokeChanged() = 0;
		//@} -----------------------------------------------------------------------------		

};

#endif		// __ITableAttrAccessor__

