//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPISuiteASB.cpp $
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

// General includes:
#include "CmdUtils.h"
#include "SelectionASBTemplates.tpp"

// Project includes:
#include "BPIID.h"
#include "IBPISuite.h"							// Superclass declaration

/** Integrator IBPISuite implementation on the abstract selection boss (ASB) that
	forwards client calls to CSB suite(s) that have a selection.
	
	The purpose of this integrator suite is
	to determine how to forward the client request on to the CSB suite(s).  Note that the client does not
	interact with the CSB (which has all the real implementation of the suite) directly, the client interacts 
	with the ASB only.  Also note that the suite API shouldn't contain model data that is specific to a 
	selection format (layout uidLists, text model/range, etc) so that the client code can be completely 
	decoupled from the underlying CSB.

	@ingroup basicpersistinterface
	
	@see Selection fundamentals chapter in Programming Guide
*/
class BPISuiteASB : public CPMUnknown<IBPISuite>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BPISuiteASB (IPMUnknown* boss);
	
	/** Destructor. 
	 */
	virtual ~BPISuiteASB (void);

	/**
		@return kTrue if any CSB suites on active CSBs allow adding IBPIData, kFalse otherwise.
		@see IBPISuite::CanApplyBPIData
	*/
	virtual bool16			CanApplyBPIData (void);

	/**
		Create or join a command sequence and call CSB suites on active CSBs to process it's commands.
		@see IBPISuite::ApplyBPIData
	*/
	virtual ErrorCode		ApplyBPIData(const WideString& value);

	/**
		@return kTrue if any of the CSB suites on active CSBs allow getting of IBPIData, kFalse otherwise.
		@see IBPISuite::CanGetBPIData
	*/
	virtual bool16			CanGetBPIData (void);

	/**
		Call CSB suites on active CSB's to GetBPIData
		@param values OUT vector of the IBPIData values of the selected objects.
		@see IBPISuite::GetBPIData
	*/
	virtual void			GetBPIData(K2Vector<WideString>& values);
};

/* CREATE_PMINTERFACE
 	Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE (BPISuiteASB, kBPISuiteASBImpl)

/* BPISuiteASB Constructor
*/
BPISuiteASB::BPISuiteASB(IPMUnknown* iBoss) :
	CPMUnknown<IBPISuite>(iBoss)
{
}

/* BPISuiteASB Destructor
*/
BPISuiteASB::~BPISuiteASB(void)
{
}

/*
*/
bool16 BPISuiteASB::CanApplyBPIData(void)
{
	return (AnyCSBSupports (make_functor(&IBPISuite::CanApplyBPIData), this));
}

/*
*/
ErrorCode BPISuiteASB::ApplyBPIData(const WideString&	value)
{
	return (Process (make_functor(&IBPISuite::ApplyBPIData, value), this, IBPISuite::kDefaultIID));
}

/*
*/
bool16 BPISuiteASB::CanGetBPIData(void)
{
	return (AnyCSBSupports (make_functor(&IBPISuite::CanGetBPIData), this));
}

/*
*/
void BPISuiteASB::GetBPIData(K2Vector<WideString>& values)
{
	CallEach(make_functor(&IBPISuite::GetBPIData, values), this);
}

// End, BPISuiteASB.cpp.



