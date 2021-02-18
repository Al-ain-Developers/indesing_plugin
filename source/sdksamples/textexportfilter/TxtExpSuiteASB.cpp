//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/TxtExpSuiteASB.cpp $
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
#include "ISelectionManager.h"

// General includes:
#include "CmdUtils.h"
#include "SelectionASBTemplates.tpp"
#include "CPMUnknown.h"

// Project includes:
#include "TxtExpID.h"
#include "ITxtExpSuite.h"	
#include "ITxtExpFileWriter.h"

/** 
	ITxtExpSuite implementation for the abstract selection boss (ASB) that
	forwards the client request on to the CSB suite implementations. 

	This integrator implementation enforces	an ANY policy, which states that if 
	any enabled concrete selection boss CSB supports the functionality the suite 
	client code should enable the feature to the user. In this case the functionality
	is the manipulation of text inset.

	@ingroup textexportfilter
	
	@see ITxtExpSuite
*/
class TxtExpSuiteASB : public CPMUnknown<ITxtExpSuite>
{
public:
	/** Constructor
	*/
	TxtExpSuiteASB (IPMUnknown *iBoss);
	
	/** Destructor
	*/
	virtual ~TxtExpSuiteASB(void);

	/** see ITxtExpSuite::CanExportText
	*/
	virtual bool16 CanExportText(const PMString& formatName);
	
	/** see ITxtExpSuite::DoExportText
	*/
	virtual ErrorCode DoExportText(IPMStream *fileStreamWrites, ITxtExpFileWriter::Encoding encoding);
};

/* CREATE_PMINTERFACE
 	Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE (TxtExpSuiteASB, kTxtExpSuiteASBImpl)



/* TxtExpSuiteASB Constructor
*/
TxtExpSuiteASB::TxtExpSuiteASB(IPMUnknown* boss) :
	CPMUnknown<ITxtExpSuite>(boss)
{
}

/* TxtExpSuiteASB Destructor
*/
TxtExpSuiteASB::~TxtExpSuiteASB(void)
{
}

/* 
*/
bool16 TxtExpSuiteASB::CanExportText(const PMString& formatName)
{
	return (AnyCSBSupports (make_functor(&ITxtExpSuite::CanExportText, formatName), this));
}

/* 
*/
ErrorCode TxtExpSuiteASB::DoExportText(IPMStream *fileStreamWrites, ITxtExpFileWriter::Encoding encoding)
{
	return (Process (make_functor(&ITxtExpSuite::DoExportText ,fileStreamWrites, encoding), this, ITxtExpSuite::kDefaultIID));
}

// End, TxtExpSuiteASB.cpp.



