//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartSuiteLayoutCSB.cpp $
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

// Interface includes
#include "ILayoutTarget.h"

// General includes
#include "GenericID.h"

// Project includes
#include "CdlChartID.h"
#include "ICdlChartSuite.h"
#include "CdlChartSuiteCSB.h"

/** ICdlChartSuite implementation for the layout CSB that gets used when a layout
	selection exists; it examines ILayoutTarget and return a UIDList
	of page items (ICdlChartData is an interface added to page items by this plug-in).
	
	The rest of the implementation is provided by CdlChartSuiteCSB.
	 
	@ingroup candlechart
	
	@see Selection fundamentals chapter in Programming Guide
*/
class CdlChartSuiteLayoutCSB : public CdlChartSuiteCSB
{
public:
	/**	Constructor
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CdlChartSuiteLayoutCSB(IPMUnknown* iBoss);

	/** Destructor 
	 */
	virtual ~CdlChartSuiteLayoutCSB(void);

protected:
	/**	@return list of objects in ILayoutTarget with standoffs stripped.
	*/
	virtual UIDList GetTarget(void);
};

/*
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CdlChartSuiteLayoutCSB, kCdlChartSuiteLayoutCSBImpl)


/* Constructor
*/
CdlChartSuiteLayoutCSB::CdlChartSuiteLayoutCSB(IPMUnknown* iBoss) 
	: CdlChartSuiteCSB(iBoss)	
{
}

/* Destructor
*/
CdlChartSuiteLayoutCSB::~CdlChartSuiteLayoutCSB(void)	
{
}

/* GetTarget
*/
UIDList CdlChartSuiteLayoutCSB::GetTarget(void)
{
	UIDList result;
	do
	{
		InterfacePtr<ILayoutTarget> layoutTarget(this, UseDefaultIID());
		ASSERT(layoutTarget);
		if (!layoutTarget)
		{
			break;
		}
		result = layoutTarget->GetUIDList(kStripStandoffs);
	} while (false);
	return result;
}   

// End, CdlChartSuiteLayoutCSB.cpp.
