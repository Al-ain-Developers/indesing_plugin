//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterSuiteASB.cpp $
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

// Interface includes:
#include "IIntegratorTarget.h"

// Implementation includes:
#include "CPMUnknown.h"
#include "SelectionASBTemplates.tpp"

// Project includes:
#include "IDataUpdaterSuite.h"
#include "DataUpdaterID.h"


/** From SDK sample; IDataUpdaterSuite implementation for the abstract integrator suite. 
	Uses templates provided by the API to delegate calls to IDataUpdaterSuite
	implementations on underlying concrete selection boss
	classes.

	@ingroup xmldataupdater
*/
class DataUpdaterSuiteASB : public CPMUnknown<IDataUpdaterSuite>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on 
		which this interface is aggregated.
	*/
	DataUpdaterSuiteASB(IPMUnknown* boss);

	/** See IDataUpdaterSuite
	*/
	virtual bool16 CanInsertData() const;

	/** See IDataUpdaterSuite
	*/
	virtual ErrorCode InsertData(const WideString& table, const WideString& record, const WideString& field, const WideString& value );

	/** See IDataUpdaterSuite
	*/
	virtual ErrorCode InsertAllData(const IDFile& file);

};

/*	Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(DataUpdaterSuiteASB, kDataUpdaterSuiteASBImpl)


/* Constructor
*/
DataUpdaterSuiteASB::DataUpdaterSuiteASB(IPMUnknown* boss) :
	CPMUnknown<IDataUpdaterSuite>(boss)
{
}


/*
*/
bool16 DataUpdaterSuiteASB::CanInsertData() const
{
    return (AnyCSBSupports(make_functor(&IDataUpdaterSuite::CanInsertData), this, IID_IDATAUPDATERSUITE));
}

/* 
*/
ErrorCode DataUpdaterSuiteASB::InsertData(const WideString& table, const WideString& key, const WideString& field, const WideString& value )
{
    return (Process (make_functor(&IDataUpdaterSuite::InsertData, table, key, field, value), this, IID_IDATAUPDATERSUITE));
}


/*
*/
ErrorCode DataUpdaterSuiteASB::InsertAllData(const IDFile& file)
{
    return (Process (make_functor(&IDataUpdaterSuite::InsertAllData, file), this, IID_IDATAUPDATERSUITE));
}


// end:	PrnSelSuiteASB.cpp

