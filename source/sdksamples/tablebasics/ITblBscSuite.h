//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tablebasics/ITblBscSuite.h $
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

#ifndef _ITblBscSuite_
#define _ITblBscSuite_

// Interface includes:
#include "IPMUnknown.h"

// Forward declarations:
class WideString;

/** From SDK sample;  abstract suite interface for table creation and table cell text content manipulation.
	ITableSuite now provides a method to insert a table but no suites are provided that
	set and get the text in a table cell. So this custom suite is still required to fully
	manipulate table content.

	
	@ingroup tablebasics
*/
class ITblBscSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITBLBSCSUITE };

public:
	/** Return kTrue if ITblBscSuite::InsertTable can be called, kFalse otherwise.
		@return kTrue if ITblBscSuite::InsertTable can be called, kFalse otherwise.
	*/
	virtual bool16 CanInsertTable() const = 0;

	/** Insert table at the current selection location.
		@precondition ITblBscSuite::CanInsertTable == kTrue.
		@param numRows IN number of rows in the table.
		@param numCols IN number of columns in the table.
		@return kSuccess on success, otherwise failure
	*/
	virtual ErrorCode InsertTable(int32 numRows, int32 numCols) = 0;

	/**	Return kTrue if the text for the given cell in the table in which the
		selection lies can be changed, kFalse otherwise.
		@param row IN number of the cell you want to set the text for.
		@param col IN column number of the cell you want to set the text for.
		@return kTrue if text can be set, kFalse otherwise.
	*/
	virtual bool16 CanSetCellText(int32 row, int32 col) const = 0;

	/**	Change the text for the given cell in the table in which the
		selection lies.
		@precondition ITblBscSuite::CanSetCellText == kTrue.
		@param row IN number of the cell you want to set the text for.
		@param col IN column number of the cell you want to set the text for.
		@param text IN the string the cell should contain.
		@return kSuccess if the text was set successfully.
	*/
	virtual ErrorCode SetCellText(int32 row, int32 col, const WideString& text) = 0;

	/**	Return kTrue if the text for the given cell in the table in which the 
		selection lies can be read.
		@param row IN number of the cell you want to get the text for.
		@param col IN column number of the cell you want to get the text for.
		@return kTrue if the text can be read, kFalse otherwise.
	*/
	virtual bool16 CanGetCellText(int32 row, int32 col) const = 0;

	/** Get the text for the given cell in the table in which the
		selection lies.
		@precondition ITblBscSuite::CanGetCellText == kTrue.
		@param row IN number of the cell you want to get the text for.
		@param col IN column number of the cell you want to get the text for.
		@param text OUT the text extracted from the cell.
	*/
	virtual void GetCellText(int32 row, int32 col, WideString& text) const = 0;
};

#endif // _ITblBscSuite_


