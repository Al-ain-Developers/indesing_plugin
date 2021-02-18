//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableCopyPasteCmdData.h $
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

#ifndef __ITABLECOPYPASTECMDDATA__
#define __ITABLECOPYPASTECMDDATA__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "ITableModel.h"

/** 
	The model, area, and state the copy/paste command is acting on
	@ingroup tables_cmd
*/
class ITableCopyPasteCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITABLECOPYPASTECMDDATA };

	/**
		Sets the source table, source area, destination table and destination area
		@param	fromTable
		@param	fromArea
		@param	toTable
		@param	pasteAt
		@param	what			@see ITableModel::EWhatState
	*/
	virtual void		Set(const UIDRef  fromTable, const GridArea& fromArea, const UIDRef& toTable, const GridAddress& pasteAt, ITableModel::EWhatState what) = 0;

	/**
		Returns the source table
		@return	UIDRef
	*/
	virtual UIDRef					GetFromTable() const = 0;
	/**
		Returns the source area
		@return	GridArea
	*/
	virtual GridArea				GetFromArea() const = 0;
	/**
		Returns the destination table
		@return	UIDRef
	*/
	virtual UIDRef					GetToTable() const = 0;
	/**
		Returns the destination area
		@return	GridArea
	*/
	virtual GridAddress				GetPasteAt() const = 0;
	/**
		Returns what state to paste		@see ITableModel::EWhatState
		@return	ITableModel::EWhatState
	*/
	virtual ITableModel::EWhatState	GetStateToPaste() const = 0;

	/**
		Sets whether to clear redundant rows and columns
		@param	bool16 	
	*/
	virtual void SetShouldClearRedundantRowsAndCols(const bool16 to) = 0;

	/**
		Returns whether to clear redundant rows and columns
		@return	bool16 	
	*/
	virtual bool16 ShouldClearRedundantRowsAndCols() const = 0;

};

#endif	// __ITABLECOPYPASTECMDDATA__

