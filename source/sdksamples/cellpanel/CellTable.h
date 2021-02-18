//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/CellTable.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __CELLTABLE_H__
#define __CELLTABLE_H__

#include "WideString.h"

extern const WideString kNullWideString;

/**
	CellData stores the string data for each cell on the table.	
	
	@ingroup cellpanel
	
*/
class CellData {
	public:
		/**
			Constructor.
		*/
		CellData();
		/**
			Destructor.
		*/
		~CellData();
	
		/** Set a string in cell.
			@param str A string data to set up.
		*/
		bool				SetString(const WideString& str);
		/** Getting a string data from a cell.
		*/
		const WideString&		GetString(void);
		
	protected:
	private:
		WideString		string;
};


/** CellTable
	This is a table of cell data class.
	The table has many cell datas, And two access function.
	
	@ingroup cellpanel
	
*/
class CellTable {
	public:
		/**
			Constructor.
			@param numColumn The number of columns for the new table.
			@param numRow The number of rows for the new table.
		*/
		CellTable(int32 numColumn, int32 numRow);
		
		/**
			Destructor.
		*/
		~CellTable();
		
		/** Set a string in cell of the table.
			@param str WideString class data.
			@param column The column number of the cell to set.
			@@param row The row number of the cell to set.
		*/
		bool			SetString(const WideString& str, int32 column, int32 row);
		
		/** Getting a string data from a cell.
			@param column The number of column for getting a string data from a cell.
			@param row The number of row for getting a string data from a cell.
		*/
		const WideString&	GetString(int32 column, int32 row);
				
	private:
		int32 maxColumn, maxRow;
		CellData* table;
		
};

#endif // __CELLTABLE_H__

//End, CellTable.h
