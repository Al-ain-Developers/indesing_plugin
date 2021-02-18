//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightResultRecordTable.h $
//  
//  Owner: Matt Phillips
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

#include "IPreflightObject.h"
#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPreflightResultRecord.h"

class PreflightXferStream;

/** This interface manages an array/vector of IPreflightResultRecord references. It's used
	extensively by the preflight aggregated results utilities and preflight rules.

	@see IPreflightResultRecord
	@see IPreflightAggregatedResultsUtils

	This interface sits on its own boss by itself, typically. You can create an empty one of
	these via IPreflightAggregatedResultsUtils::CreatePreflightResultRecordTable, but more
	typically you use IPreflightAggregatedResultsUtils::CreateTableFromNodes and various
	other create-table-via-filter methods in that interface.
*/

class IPreflightResultRecordTable : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRESULTRECORDTABLE };

public:
	/** @return the number of records in the table.
	*/
	virtual int32 GetRecordCount() const = 0;

	/** Get a record.
		@param n IN The index of the record.
		@return a refcounted interface, or nil if error.
	*/
	virtual const IPreflightResultRecord* QueryNthRecord(int32 n) const = 0;

	/** Adds a record to the table. This isn't terribly common in rules because most of
		the time they're simply grouping existing results and those generated via
		IPreflightAggregatedResultsUtils::ApplyAllStandardAggregations (et al). But 
		there's no reason you can't build a table exactly the way you like with this API.
		
		@param iRec IN The record to add. It's appended to the end of the table.
	*/
	virtual void AddRecord(const IPreflightResultRecord* iRec) = 0;
	
	/** Appends an entire table. Note that there's no attempt to merge, ie identify
		like entries; it's simply appended.
		
		@param iOther IN The other table whose records you want to add.
	*/
	virtual void AppendTable(const IPreflightResultRecordTable* iOther) = 0;

	/** Internal use only. Used to serialize from a blob in the database. */
	virtual void ReadData(PreflightXferStream& s) = 0;

	/** Internal use only. Used to serialize to a blob in the database. */
	virtual void WriteData(PreflightXferStream& s) const = 0;
};

