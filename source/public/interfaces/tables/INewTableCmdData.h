//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/INewTableCmdData.h $
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
//  Data interface for new table commands.
//  
//========================================================================================

#pragma once
#ifndef __INewTableCmdData__
#define __INewTableCmdData__

#include "IPMUnknown.h"
#include "PMReal.h"
#include "TablesID.h"
#include "TableTypes.h"

class IDataBase;

/**	Is a holder class for specifications for a new table, used when call ITableUtils::InsertTable.
	@author jshankar
	@see ITableUtils.h
*/
class INewTableCmdData : public IPMUnknown
{
public:
	
	enum { kDefaultIID = IID_INEWTABLECMDDATA };
	
	/**
	Set data in this holder class.
	@param db Target story's database.
	@param textModelUID TextModel in which to make the new table.
	@param insertionPoint Text insertion point at which to make the new table.
	@param numBodyRows Number of body rows in new table.
	@param numColumns Number of columns in new table.
	@param tableWidth New table width in points.
	@param tableHeight New table height in points.
	@param cellType Type of cell (no content, text, etc.).
	@param useExistingAnchor optional parameter that allows the Table to inherit the first anchor character that already exist at the insertion point.
	*/
	virtual void Set(IDataBase* db,
					UID textModelUID,
					TextIndex insertionPoint,
					int32 numBodyRows,
					int32 numColumns,
					const PMReal& tableWidth,
					const PMReal& tableHeight,
					CellType cellType,
					bool16 useExistingAnchor = kFalse) = 0;

	/**
	Set data in this holder class.
	@param db Target story's database.
	@param textModelUID TextModel in which to make the new table.
	@param insertionPoint Text insertion point at which to make the new table.
	@param numHeaderRows Number of header rows in new table.
	@param numBodyRows Number of body rows in new table.
	@param numFooterRows Number of footer rows in new table.
	@param numColumns Number of columns in new table.
	@param tableWidth New table width in points.
	@param tableHeight New table height in points.
	@param cellType Type of cell (no content, text, etc.).
	@param useExistingAnchor optional parameter that allows the Table to inherit the first anchor character that already exist at the insertion point.
	*/
	virtual void Set(IDataBase* db,
					UID textModelUID,
					TextIndex insertionPoint,
					int32 numHeaderRows,
					int32 numBodyRows,
					int32 numFooterRows,
					int32 numColumns,
					const PMReal& tableWidth,
					const PMReal& tableHeight,
					CellType cellType,
					bool16 useExistingAnchor = kFalse) = 0;

	/**
	Get data from this holder class.
	@param numHeaderRows Number of header rows in new table.
	@param numBodyRows Number of body rows in new table.
	@param numFooterRows Number of footer rows in new table.
	@param numColumns Number of columns in new table.
	@param tableWidth New table width in points.
	@param tableHeight New table height in points.
	@param cellType Type of cell (no content, text, etc.).
	*/
	virtual void Get(int32&	 numHeaderRows,
					 int32&  numBodyRows,
					 int32&  numFooterRows,
					 int32&  numColumns,
					 PMReal& tableWidth,
					 PMReal& tableHeight,
					 CellType& cellType) const = 0;
	
	/**
	Get DataBase from this holder class.
	@return IDatabase* Target story's database.
	*/
	virtual IDataBase*	GetDataBase(void) const = 0;

	/**
	Get TextModel UID from this holder class.
	@return UID TextModel of the new table.
	*/
	virtual UID			GetTextModelUID() const = 0;

	/**
	Get TextIndex from this holder class.
	@return TextIndex Text insertion point of the new table's table character.
	*/
	virtual TextIndex	GetTextIndex() const = 0;

	/**
	Get use existing anchor from this holder class.
	@return bool16 no anchors
	*/
	virtual bool16		GetUseExistingAnchor() const = 0;

	/**
	Set the direction for this holder class.
	@return EDirection direction
	*/
	virtual void		SetDirection(Tables::EDirection direction) = 0;

	/**
	Get use direction from this holder class.
	@return EDirection direction
	*/
	virtual Tables::EDirection		GetDirection() const = 0;

};

#endif // __INewTableCmdData__
