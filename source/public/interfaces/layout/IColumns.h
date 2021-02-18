//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IColumns.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __ICOLUMNS__
#define __ICOLUMNS__

/** Minimum width for a column. 1 point. */
#define kMinColumnWidth		1

/** Maximum number of columns on a page. */
#define kMaxNumColumns		216

/** Minimum number of columns on a page. */
#define kMinNumColumns		1

/** Maximum width for a gutter. */
#define kMaxGutter			1440.0

/** Minimum width for a gutter. */
#define kMinGutter			0.0

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "PMReal.h"
#include "PMRect.h"
#include "K2Vector.h"
class IGeometry;

typedef K2Vector<PMReal> PMRealList;

/** Represents columns associated with a page.
	@ingroup layout_column
	@see kPageBoss
*/
class IColumns : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLUMNS };

	enum ColumnOrientation {
		kVerticalColumnOrientation = 0,
		kHorizontalColumnOrientation = 1,
		kRomanColumnOrientation = kVerticalColumnOrientation,
		kTraditionalCJKColumnOrientation = kHorizontalColumnOrientation
		};

	enum MasterColumnRequest { kRequestPerhapsInvalidFirstColumnData = 0, kRequestValidColumnData = 1};


	/**
		Set the column list for the  page. Positions are relative to the
		left edge of the margin. So, first column position is typically 0. For a page
		with vertical columns, positions are from top of page down.

		@param pageCols a list of PMReals for the columns for the page.
		@see GetDirection
		@see kSetPageColumnsCmdBoss
	*/
	virtual void SetColumns(const PMRealList& pageCols) = 0; 

	/**
		Get the column list for the page. column guide positions are relative
		to the left margin for the page. Or to the top of page for vertical columns.

		@param outputColumns OUT list of PMReal column positions. Note that there will be twice as many
		column positions are there are number of columns. A column requires two positions to define it.
		@param wantMaster kTrue to get the column positions for any applied master on the page if valid.
		@see QueryColumns
	 */
	virtual void GetColumns_(PMRealList *outputColumns, MasterColumnRequest wantMaster = kRequestValidColumnData) const= 0;

	/**
		Get the number of columns for the page. 
		@param wantMaster kTrue to get the column positions for any applied master on the page if valid.
		@return the number of columns on the page. Will range from kMinNumColumns to kMaxNumColumns.
	 */
	virtual int32 GetNumberColumns_( MasterColumnRequest wantMaster = kRequestValidColumnData) const = 0;

	/**
		Set the gutter value for the page. Will be the same for all columns on the page.
		@param theGutter. Must range from kMinGutter to kMaxGutter.
	 */
	virtual void SetGutter(const PMReal& theGutter) = 0;

	/**
		Get the gutter value for the page. 
		@param wantMaster kTrue to get the gutter value for any applied master on the page if valid.
	 */
	virtual PMReal GetGutter_( MasterColumnRequest wantMaster = kRequestValidColumnData) const = 0;
	
	/**
		Set the direction/orientation for columns on page. When kFalse, column positions are
		measured from left of page to right, when kTrue, they are measured from top of page down.
		@param direction kFalse is for Roman columns, kTrue for J vertical columns.
	 */
	virtual void SetColumnOrientation_0( ColumnOrientation direction) = 0;
	
	/**
		Get direction/orientation for columns on page. 
		@param wantMaster kTrue to get the direction value for any applied master on the page if valid.
	 */
	virtual ColumnOrientation GetColumnOrientation_0( MasterColumnRequest wantMaster = kRequestValidColumnData) const= 0;

	/**
		Change the column position at the specified index.
		Since every column requires two values to define it, a page with 2 columns 
		would have 4 column positions/indices.
		@param columnIndex IN the column index for the column value to change.
		@param newValue IN the new value for the column position.
		@see kMoveColumnGuideCmdBoss
	 */
	virtual void ChangeColumnAtIndex(int32 columnIndex, const PMReal& newValue) = 0;

	/**
		Return the index of the column at the specified location. Returns the closest column position.
		@param location IN the location value to search for, relative to left margin (or top for J-style columns when GetDirection returns kTrue).
		@see kMoveColumnGuideCmdBoss
	 */
	virtual int32 GetColumnAtLocation_(const PMReal& location) const = 0;

	/**
		Return a bbox in page coordinates for the nth column with the provided marginRect.
		Takes into account if column direction for CJK columns. Used by autoflow.
		Note that this box would need to be transformed by the page's transform to get
		the bounds in spread coordinates.
		@param pageGeom IN the IGeometry* for the desired page.
		@param n IN the column index for the desired column box (0-based).
		@param marginRect IN the PMRect as returned from GetMargins.
		@see GetMargins
	 */
	virtual PMRect GetNthColumnBoundingBox_(IGeometry *pageGeom, const int32 n, const PMRect& marginRect) const = 0;

	/**	Set the custom attribute for columns. Custom columns are not equally spaced.
		@param b IN Pass kTrue to set to custom, kFalse otherwise.
		@see kSetPageColumnsCmdBoss
	 */
	virtual void SetCustom(bool16 b) = 0;

	/**	Reset the columns to equal width based on current margins and gutter. Clears custom setting.
		@param none
		@see ColumnsAreCustom
	 */
	virtual void ResetColumns() = 0;
	
	/**	Returns if the columns on a page are overridden (kTrue) or the applied master page's columns are in use (kFalse).
		@param none
		@return bool16 kTrue if overridden, kFalse if master's columns interface is in use.
	 */
	virtual bool16 ColumnsAreValid_() const = 0;

	/**	Set the columns to be valid or not for a page.
		@param valid IN set to kTrue to override the columns for a page, kFalse to reset to non-overridden 
		(in which case the columns for the master page applied to the page will be used).
		@see kSetPageColumnsValidCmdBoss
	 */
	virtual void SetColumnsAreValid(bool16 valid) = 0;

	/**	Returns whether the columns are evenly spaced, or have been "customized". 
		@param wantMaster IN Pass kTrue to get the custom value for any applied master on the page if valid.
		@return bool16 kTrue if user has modified column widths by dragging in layout, kFalse otherwise.
	 */
	virtual bool16 ColumnsAreCustom_( MasterColumnRequest wantMaster = kRequestValidColumnData) const= 0;
	
	/**	Allows caller to get all the column attributes at once. Faster than calling the individual routines. All parameters are optional.
		@param wantMaster IN Pass kTrue to get the custom value for any applied master on the page if valid.
		@param outputColumns OUT a PMRealList* to contain the list of column positions. May pass nil if not needed. 
		@param gutter OUT a PMReal* to hold the gutter value. Gutter value is always the same for all columns on a page. May pass nil if not needed. 
		@param direction OUT a bool16* to hold the column direction value. May pass nil if not needed. 
		@param custom OUT a bool16* to hold the custom value. May pass nil if not needed. 
		@param valid OUT a bool16* to hold the valid value. May pass nil if not needed. 
		@see GetColumns
		@see GetGutter
		@see GetDirection
		@see ColumnsAreCustom
		@see ColumnsAreValid
	 */
	virtual void GetColumnAttributes_hmm( MasterColumnRequest wantMaster/* = kTrue*/, PMRealList *outputColumns/* = nil*/, PMReal* gutter/* = nil*/, ColumnOrientation* direction/* = nil*/, bool16* custom/* = nil*/, bool16* valid/* = nil*/) const= 0;
	
	/**
		Return a bbox in page coordinates for the columns on the page with the provided marginRect.
		Takes into account if column direction for CJK columns.
		Note that this box would need to be transformed by the page's transform to get
		the bounds in spread coordinates.
		@param pageGeometry IN the IGeometry* for the desired page.
		@param marginRect IN the PMRect as returned from GetMargins.
		@see GetMargins
	*/
	virtual PMRect GetPageBoundingBox_(IGeometry *pageGeometry, const PMRect& marginRect) const = 0;
};
#endif	// __ODFRC__

#endif
