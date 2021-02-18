//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableTextSelection.h $
//  
//  Owner: Danielle Bessette
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
#ifndef __ITABLETEXTSELECTION__
#define __ITABLETEXTSELECTION__

#include "IPMUnknown.h"
#include "TablesUIID.h"
#include "TableTypes.h"

class ITableModel;

/**
	Abstract interface for accessing and manipulating text-selection in a table.

	@see kTextSuiteBoss
	@see kTextSelectionBoss
*/
class ITableTextSelection : public IPMUnknown
{
public:
	enum				{ kDefaultIID = IID_ITABLETEXTSELECTION	};	

	/** Enumerated type defining how to perform selection of text within table cell */
	enum WhatToSelect	{ 
							/** sets selection to the beginning of the cell */ 
							kStart, 
							/** sets the selection to the end of the cell */
							kEnd, 
							/** sets the selection to all the text in the cell */
							kAll, 
							/** sets the selection to a given index + start index of the cell */
							kIndex, 
							/** sets the selection from start to the given index + start index of the cell */
							kToIndex,
							/**  sets the selection from the given index + start index of the cell to the end */
							kFromIndex };

	/** Selects text in the cell passed in.  Assumes an existing selection in a table
		Selection is based on the choices in WhatToSelect.

		@param tableModel		the table model the cell is in
		@param cell				cell specifies the cell in which to select the text
		@param whatToSelect		one of the enumerated type defined in WhatToSelect
		@param index			the index used for kIndex, kToIndex, and kFromIndex; 
			this parameter will be used in the manner indicated by the whatToSelect parameter
			
	*/
	virtual void 		SelectTextInCell(const ITableModel *tableModel, const GridAddress& cell, WhatToSelect whatToSelect = kStart, int32 index = -1) = 0;
	
	/** Checks and sees if the text selection is in a table
		@return kTrue if the text selection is within a table, kFalse otherwise
	*/
	virtual bool16 		IsTableSelection() const = 0;
	
	/** Accessor for the GridArea where the text selection is located.
		Can be used to get the grid id of the cell the 
		text selection is in by using e.g.ITableModel::GetGridID
		@return 	the GridArea the text insertion point is in
	*/
	virtual GridArea	GetSelection() const = 0;

	/** Determine the the text index of the last position in the cell
		@return the text index of last position in the cell
	*/
	virtual TextIndex	GetIndexOfLastCharInCell() const = 0;
	 
	/** Determine the the text index of the first position in the cell
		@return the the text index of the first character in cell
	*/
	virtual TextIndex	GetIndexOfFirstCharInCell() const = 0;
	 
	/** Determine the text index of the character at the first position in the text selection
		@return text index of the first character in the text selection
	*/
	virtual TextIndex	GetFirstSelectedTextIndex(void) const = 0;

	/** Determine the text index of the character in last position in the text selection
		@return text index of the last character in the text selection
	*/
	virtual TextIndex	GetLastSelectedTextIndex(void) const = 0;
};


#endif //__ITABLETEXTSELECTION__
