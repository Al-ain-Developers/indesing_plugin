//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tablebasics/TblBscSuiteASB.cpp $
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
#include "ISelectionManager.h" // required by selection templates.
#include "ICommandSequence.h"

// General includes:
#include "CPMUnknown.h"
#include "SelectionASBTemplates.tpp"
#include "WideString.h"
#include "CmdUtils.h"

// Project includes:
#include "TblBscID.h"
#include "ITblBscSuite.h"

/**	Integrator ITblBscSuite implementation. Uses templates
	provided by the API to delegate calls to ITblBscSuite
	implementations on underlying concrete selection boss
	classes.

	The SDK provides SelectionASBTemplates.tpp to cut down on boilerplate code
	which you may often need to write for abstract selection boss implementations.
	See <sdk dir>/source/public/includes/SelectionASBTemplates.tpp for
	info on how this ASB (abstract selection boss) implementation delegates to functions
	with the same name and same parameters on existing CSBs (concrete selection bosses).
	
	@see ITblBscSuite
	@ingroup tablebasics
*/
class TblBscSuiteASB : public CPMUnknown<ITblBscSuite>
{
public:
	/** Constructor.
		@param boss refers to boss class on which this is aggregated.
	*/
	TblBscSuiteASB (IPMUnknown *boss);

	/** Destructor.
	*/
	virtual ~TblBscSuiteASB (void);

public:
	/**	See ITblBscSuite::CanInsertTable.
	*/
	virtual bool16 CanInsertTable() const;
	
	/**	See ITblBscSuite::InsertTable.
	*/
	virtual ErrorCode InsertTable(int32 numRows, int32 numCols);

	/**	See ITblBscSuite::CanSetCellText.
	*/
	virtual bool16 CanSetCellText(int32 row, int32 col) const;

	/**	See ITblBscSuite::SetCellText.
	*/
	virtual ErrorCode SetCellText(int32 row, int32 col, const WideString& text);

	/**	See ITblBscSuite::CanGetCellText.
	*/
	virtual bool16 CanGetCellText(int32 row, int32 col) const;

	/**	See ITblBscSuite::GetCellText.
	*/
	virtual void GetCellText(int32 row, int32 col, WideString& text) const;

};

/*  Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(TblBscSuiteASB, kTblBscSuiteASBImpl)


/*
*/
TblBscSuiteASB::TblBscSuiteASB(IPMUnknown* boss) :
	CPMUnknown<ITblBscSuite>(boss)
{
}

/*
*/
TblBscSuiteASB::~TblBscSuiteASB(void)
{
}

/*
*/
bool16 TblBscSuiteASB::CanInsertTable() const
{
	return (AnyCSBSupports(make_functor(&ITblBscSuite::CanInsertTable), this));
}

/*
*/
ErrorCode TblBscSuiteASB::InsertTable(int32 numRows, int32 numCols)
{
	return (Process(make_functor(&ITblBscSuite::InsertTable, numRows, numCols), this));
}

/*
*/
bool16 TblBscSuiteASB::CanSetCellText(int32 row, int32 col) const
{
	return (AnyCSBSupports(make_functor(&ITblBscSuite::CanSetCellText, row, col), this));
}

/*
*/
ErrorCode TblBscSuiteASB::SetCellText(int32 row, int32 col, const WideString& text)
{
	return (Process(make_functor(&ITblBscSuite::SetCellText, row, col, text), this));
}

/*
*/
bool16 TblBscSuiteASB::CanGetCellText(int32 row, int32 col) const
{
	return (AnyCSBSupports(make_functor(&ITblBscSuite::CanGetCellText, row, col), this));
}

/*
*/
void TblBscSuiteASB::GetCellText(int32 row, int32 col, WideString& text) const
{
	CallEach(make_functor(&ITblBscSuite::GetCellText, row, col, text), this);
}

// End, TblBscSuiteASB.cpp.



