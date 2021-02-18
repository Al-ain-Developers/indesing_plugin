//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/IMoveColumnsCmdData.h $
//  
//  Owner: sandagra $
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
/*************************************************************************
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2013 Adobe Systems Incorporated
*  All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any.  The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by all applicable intellectual property 
* laws, including trade secret and copyright laws.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/
//  
//  Data interface to specify a column move.
//  
//========================================================================================

#pragma once
#ifndef __IMoveColumnsCmdData__
#define __IMoveColumnsCmdData__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"

class ITableModel;

// ===================================================================================
//	class IMoveColumnsCmdData		
// ===================================================================================
/** Maintains information needed by command to move column within a table
*/
class IMoveColumnsCmdData : public IPMUnknown
{
public:
	
	enum { kDefaultIID = IID_IMOVECOLUMNSCMDDATA };
	
	/**
		Sets the table model, grid area to move, the destination column, relative position and whether to duplicate columns or not
		@param	sourceTable The table whose columns need to be moved
		@param	fromAr The source grid area
		@param  toC   Destination column
		@param  pos   Position of new column(col to be moved) with respect to drop location
		@param  duplicateFlag  Flag is true to indicate that column is to be duplicated
	*/
	virtual void	Set(ITableModel* sourceTable, GridArea fromAr,  int32 toC, Tables::ERelativePosition pos, bool16 duplicateFlag) = 0;
	/**
		Returns the source grid area
		@return	GridArea
	*/
	virtual GridArea	GetFromArea(void) const = 0;
	/**
		Returns the destination column
		@return	int32
	*/
	virtual int32	GetToColumn(void) const = 0;
	/**
		Returns the relative position with respect to destination column
		@return	Tables::ERelativePosition
	*/
	virtual Tables::ERelativePosition GetRelativePos(void) const = 0;
	/**
		Returns if duplication of column is to be done
		@return	bool16
	*/
	virtual bool16 GetDuplicateFlag(void) const = 0;
	/**
		Returns table from which columns are to be moved
		@return	ITableModel*
	*/
	virtual ITableModel* GetSourceTable(void) const = 0;
};

#endif // __IMoveColumnsCmdData__
