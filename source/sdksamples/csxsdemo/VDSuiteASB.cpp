//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/csxsdemo/VDSuiteASB.cpp $
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
#include "K2Vector.h"

// Project includes:
#include "VDID.h"
#include "IVDSuite.h"

class VDSuiteASB : public CPMUnknown<IVDSuite>
{
	public:
		VDSuiteASB(IPMUnknown* boss);
		virtual ~VDSuiteASB();	
		virtual ErrorCode GetTextFromSelectedFrame(const UIDRef &frameUIDRef, PMString &result);
};

CREATE_PMINTERFACE(VDSuiteASB, kVDSuiteASBImpl)

VDSuiteASB::VDSuiteASB(IPMUnknown* boss) : CPMUnknown<IVDSuite>(boss)
{
}

VDSuiteASB::~VDSuiteASB()
{
}

ErrorCode VDSuiteASB::GetTextFromSelectedFrame(const UIDRef &frameUIDRef, PMString &result)
{
	return (Process(make_functor(&IVDSuite::GetTextFromSelectedFrame, frameUIDRef, result), this));
}