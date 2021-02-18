//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/CellTable.cpp $
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

#include "VCPlugInHeaders.h"

#include "CellTable.h"

const WideString kNullWideString("");

/* CellData
*/
CellData::CellData()
{
}

/* ~CellData
*/
CellData::~CellData()
{
}

/* SetString
*/
bool CellData::SetString(const WideString& str)
{
	string = str;
	return true;
}

/* GetString
*/
const WideString& CellData::GetString(void)
{
	return string;
}

/* CellTable
*/
CellTable::CellTable(int32 numColumn, int32 numRow)
{
	table = new CellData[numColumn*numRow];
	maxColumn = numColumn;
	maxRow = numRow;
}

/* ~CellTable
*/
CellTable::~CellTable()
{
	delete[] table;
}

/* SetString
*/
bool CellTable::SetString(const WideString& str, int32 column, int32 row)
{
	if((0 <= column) || (0 <= row)){
		if((column <= maxColumn) || (row <= maxRow)){
			table[row * maxColumn + column ].SetString(str);
			return true;
		}
	}
	
	return false;
}
 
 /* GetString
 */
const WideString& CellTable::GetString(int32 column, int32 row)
{
	if((0 <= column) || (0 <= row)){
		if((column <= maxColumn) || (row <= maxRow)){
			return table[row * maxColumn + column ].GetString();
		}
	}
	
	return kNullWideString;
}	

// End, CellTable.cpp.
