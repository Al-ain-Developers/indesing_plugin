//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterSuiteTextCSB.cpp $
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
#include "ITextTarget.h"
#include "ITextModel.h"
#include "IActiveContext.h"
#include "ITextSelectionSuite.h"

// General includes:
#include "CPMUnknown.h"
#include "Utils.h"
#include "K2Vector.tpp"
#include "SelectionExtTemplates.tpp"

// Project includes:
#include "DataUpdaterID.h"
#include "IDataUpdaterSuite.h"
#include "IDataUpdaterFacade.h"

/** From SDK sample

	@ingroup xmldataupdater
*/
class DataUpdaterSuiteTextCSB : public CPMUnknown<IDataUpdaterSuite>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on 
		which this interface is aggregated.
	*/
	DataUpdaterSuiteTextCSB(IPMUnknown* boss);

	/** See IDataUpdaterSuite.
	*/
	virtual bool16 CanInsertData() const;

	/** See IDataUpdaterSuite.
	*/
	virtual ErrorCode InsertData(const WideString& table, const WideString& record, const WideString& field, const WideString& value);

	/**	See IDataUpdaterSuite.
	*/
	virtual ErrorCode InsertAllData(const IDFile& file);

};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(DataUpdaterSuiteTextCSB, kDataUpdaterSuiteTextCSBImpl)

/* Constructor
*/
DataUpdaterSuiteTextCSB::DataUpdaterSuiteTextCSB(IPMUnknown* boss) :
	CPMUnknown<IDataUpdaterSuite>(boss)
{
}



/*
*/
bool16 DataUpdaterSuiteTextCSB::CanInsertData() const
{
	bool16 result = kFalse;

	do
	{
		// Get the story and range of text to target.
		InterfacePtr<ITextTarget> 	textTarget(this, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		if (textModel == nil) {
			break;
		}
		RangeData rangeData = textTarget->GetRange();
		TextIndex textIndex = rangeData.Start(nil);
		int32 length = rangeData.Length();
		result = Utils<IDataUpdaterFacade>()->CanInsertData(textModel, textIndex, length);
	} while(false);

	return result;
}

/*
*/
ErrorCode DataUpdaterSuiteTextCSB::InsertData(const WideString& table, const WideString& record, const WideString& field, const WideString& value )
{
	ErrorCode status = kFailure;
	
	do {
		// Get the story and range of text to target.
		InterfacePtr<ITextTarget> 	textTarget(this, UseDefaultIID());
		ASSERT(textTarget);
		if (textTarget == nil) {
			break;
		}
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		ASSERT(textModel);
		if (textModel == nil) {
			break;
		}
		RangeData rangeData = textTarget->GetRange();
		TextIndex textIndex = rangeData.Start(nil);
		int32 selectionLength = rangeData.Length();

		// Use the facade to do the work.
		status = Utils<IDataUpdaterFacade>()->InsertData(textModel, textIndex, selectionLength, table, record, field, value);

	} while (false);

	return status;

}


/*
*/
ErrorCode DataUpdaterSuiteTextCSB::InsertAllData(const IDFile& file)
{
	ErrorCode status = kFailure;
	
	do
	{	
		// Get the story and TextIndex to target.
		InterfacePtr<ITextTarget> 	textTarget(this, UseDefaultIID());
		ASSERT(textTarget);
		if (textTarget == nil) {
			break;
		}
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		ASSERT(textModel);
		if (textModel == nil) {
			break;
		}
		RangeData rangeData = textTarget->GetRange();
		TextIndex textIndex = rangeData.Start(nil);

		// Use the facade to do the work.
		status = Utils<IDataUpdaterFacade>()->InsertAllData(textModel, textIndex, file);
	
	} while (false);

	return status;
}

// end:	DataUpdaterSuiteTextCSB.cpp
