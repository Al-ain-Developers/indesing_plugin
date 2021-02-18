//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/IDataUpdaterSuite.h $
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

#ifndef __IDataUpdaterSuite_h__
#define __IDataUpdaterSuite_h__

// Interface includes:
#include "IPMUnknown.h"

// Project includes:
#include "DataUpdaterID.h"

/** From SDK sample; Abstract suite interface for XMLDataUpdater data tag manipulation.
  
	@ingroup xmldataupdater
*/
class IDataUpdaterSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATAUPDATERSUITE };


	/** Check if data can be inserted at the position.

		@return kTrue if tag can be inserted, other ErrorCode otherwise.
	*/
	virtual bool16 CanInsertData() const = 0;

	/**
		Insert data.
		@pre IDataUpdaterSuite::CanInsertData returns kTrue
		@param table IN the table name for the data.
		@param record IN the key string (that identifies the record) for the data.
		@param field IN the field name for the data.
		@param value IN the value of the data.
		@return kSuccess if tag inserted, other ErrorCode otherwise.
	*/
	virtual ErrorCode InsertData(const WideString& table, const WideString& record, const WideString& field, const WideString& value ) = 0;

	/** 
		Insert every value in the given CSV file.
		@pre IDataUpdaterSuite::CanInsertData returns kTrue
		@param file
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode InsertAllData(const IDFile& file) = 0;
};

#endif
