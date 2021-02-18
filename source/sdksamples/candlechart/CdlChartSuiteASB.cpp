//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartSuiteASB.cpp $
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
// none.

// General includes:
#include "CmdUtils.h"
#include "CPMUnknown.h"
#include "SelectionASBTemplates.tpp"

// Project includes:
#include "CdlChartID.h"
#include "ICdlChartSuite.h" // Superclass declaration
#include "ICdlChartData.h"

/** Integrator ICdlChartSuite implementation on the abstract selection boss (ASB) that
	forwards client calls to CSB suite(s) that have a selection.
	
	The purpose of this integrator suite is
	to determine how to forward the client request on to the CSB suite(s).  Note that the client does not
	interact with the CSB (which has all the real implementation of the suite) directly, the client interacts 
	with the ASB only.  Also note that the suite API shouldn't contain model data that is specific to a 
	selection format (layout uidLists, text model/range, etc) so that the client code can be completely 
	decoupled from the underlying CSB.

	@ingroup candlechart
	
	@see Selection fundamentals chapter in Programming Guide
*/
class CdlChartSuiteASB : public CPMUnknown<ICdlChartSuite>
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CdlChartSuiteASB(IPMUnknown* iBoss);

	/** Destructor
	 */
	virtual ~CdlChartSuiteASB();

	/**	Check if it is capable of giving the name of the chart.
		@return kTrue if any CSB suites on active CSBs allow adding IBPIData, kFalse otherwise.
	*/
	virtual bool16 CanGetChartName();

	/** Get the name of the chart.
		@param outChartName string where the name of the chart will be given.
	*/
	virtual ErrorCode GetChartName(WideString& outChartName);

};

/* CREATE_PMINTERFACE
	Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE (CdlChartSuiteASB, kCdlChartSuiteASBImpl)

/* Constructor
*/
CdlChartSuiteASB::CdlChartSuiteASB(IPMUnknown* iBoss) 
	: CPMUnknown<ICdlChartSuite>(iBoss)
{
}

/* Destructor
*/
CdlChartSuiteASB::~CdlChartSuiteASB()	
{
}

/* CanGetChartName
*/
bool16 CdlChartSuiteASB::CanGetChartName()
{
	return(AnyCSBSupports (make_functor(&ICdlChartSuite::CanGetChartName), this));
}

/* GetChartName
*/
ErrorCode CdlChartSuiteASB::GetChartName(WideString& outChartName)
{
	return(Process(make_functor(&ICdlChartSuite::GetChartName, outChartName),
				   this, ICdlChartSuite::kDefaultIID));
}

// End, CdlChartSuiteASB.cpp.



