//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/IMoveRowsCmdData.h $
//  
//  Owner: sandagra 
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
//  Data interface to specify a row move.
//  
//========================================================================================

#pragma once
#ifndef __IMoveRowsCmdData__
#define __IMoveRowsCmdData__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"

class ITableModel;


// ===================================================================================
//	class IMoveRowsCmdData		
// ===================================================================================
/** Maintains information needed by command to move row within a table
*/
class IMoveRowsCmdData : public IPMUnknown
{
public:
	
	enum { kDefaultIID = IID_IMOVEROWSCMDDATA };
	
	/**
		Sets the table model, grid area to move, the destination row, relative position and whether to duplicate rows or not
		@param	sourceTable The table whose rows need to be moved
		@param	fromArea The source grid area
		@param  toR   Destination row
		@param ERelativePosition Position of moved area with respect to destination row
		@param  duplicateFlag  Flag is true to indicate that row is to be duplicated
	*/
	virtual void	Set(ITableModel* sourceTable, GridArea fromArea,  int32 toR, Tables::ERelativePosition, bool16 duplicateFlag) = 0;
	/**
		Returns the source grid area
		@return	GridArea
	*/
	virtual GridArea	GetFromArea(void) const = 0;
	/**
		Returns the destination row
		@return	int32
	*/
	virtual int32	GetToRow(void) const = 0;
	/**
		Returns the relative position with respect to destination row
		@return	Tables::ERelativePosition
	*/
	virtual Tables::ERelativePosition GetRelativePos(void) const = 0;
	/**
		Returns whether duplication of row is to be done
		@return	bool16
	*/
	virtual bool16 GetDuplicateFlag(void) const = 0;
	/*
		Return table from which rows are to be moved
		@return	tablemodel from which rows are to be moved
	*/
	virtual ITableModel* GetSourceTable(void) const = 0;
};

#endif // __IMoveRowsCmdData__
