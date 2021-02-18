//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicmenu/BscMnuSuiteASB.cpp $
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

//===========================
//  INCLUDES
//===========================

#include "VCPlugInHeaders.h"								// For MSVC

// Interface headers
#include "IBscMnuSuite.h"							// Superclass declaration

// API includes:
#include "CmdUtils.h"
#include "SelectionASBTemplates.tpp"

/** 
	Abstract selection boss (ASB) IBscMnuSuite implementation.  The purpose of this integrator suite is
	to determine how to forward the client request on to the CSB suite(s).  Note that the client does not
	interact with the CSB (which has all the real implementation of the suite) directly, the client interacts 
	with the ASB only.  Also note that the Suite API shouldn't contain model data that is specific to a 
	selection format (layout uidLists, text model/range, etc) so that the client code can be completely 
	decoupled from the underlying CSB.

	@ingroup basicmenu
	
*/
class BscMnuSuiteASB : public CPMUnknown<IBscMnuSuite>
{
public:
	/**
		Constructor.
		@param iBoss interface ptr from boss object on which this interface is aggregated.
	*/
	BscMnuSuiteASB(IPMUnknown *iBoss);
	
	/** Destructor. */
	virtual ~BscMnuSuiteASB(void);

	/**
		See IBscMnuSuite::CanApplyBscMnu
	*/
	virtual bool16			CanApplyBscMnu(void);
};

/* CREATE_PMINTERFACE
 	Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(BscMnuSuiteASB, kBscMnuSuiteASBImpl)

/* BscMnuSuiteASB Constructor
*/
BscMnuSuiteASB::BscMnuSuiteASB(IPMUnknown* iBoss) :
	CPMUnknown<IBscMnuSuite>(iBoss)
{
}

/* BscMnuSuiteASB Destructor
*/
BscMnuSuiteASB::~BscMnuSuiteASB(void)
{
}

#pragma mark-
/* CanApplyBscMnuData
*/
bool16 BscMnuSuiteASB::CanApplyBscMnu(void)
{
	return (AnyCSBSupports (make_functor(&IBscMnuSuite::CanApplyBscMnu), this));
}

// End, BscMnuSuiteASB.cpp.

