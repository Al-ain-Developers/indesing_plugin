//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelSuiteLayoutCSB.cpp $
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
#include "ILayoutTarget.h"

// Implementation includes:
// none

// Project includes:
#include "IPrnSelData.h"
#include "PrnSelSuiteCSB.h"
#include "PrnSelID.h"


/** Implements the code necessary to identify and store page UIDs
	and page item UIDs that have a layout selection.
	
	@ingroup printselection
*/
class PrnSelSuiteLayoutCSB : public PrnSelSuiteCSB
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which interface is aggregated.
	*/
	PrnSelSuiteLayoutCSB(IPMUnknown* boss);

	/**	Destructor.
	*/
	virtual ~PrnSelSuiteLayoutCSB(void);
private:
	/**
		Returns the UIDs of items in the layout selection, stand-offs are stripped.
	*/
	virtual UIDList GetItemList(void) const;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class to its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelSuiteLayoutCSB, kPrnSelSuiteLayoutCSBImpl)


/* Constructor
*/
PrnSelSuiteLayoutCSB::PrnSelSuiteLayoutCSB(IPMUnknown* boss) 
: PrnSelSuiteCSB(boss)
{
}

/**	Destructor.
*/
PrnSelSuiteLayoutCSB::~PrnSelSuiteLayoutCSB(void)
{
}


/* GetItemList
*/
UIDList PrnSelSuiteLayoutCSB::GetItemList(void) const
{
	UIDList result;
	do
	{
		InterfacePtr<ILayoutTarget> layoutTarget(this, UseDefaultIID());
		if (layoutTarget == nil)
		{
			ASSERT_FAIL("invalid layoutTarget");
			break;
		}
		result = layoutTarget->GetUIDList(kStripStandoffs);
	} while (false);
	return result;
}

// End,	PrnSelSuiteLayoutCSB.cpp.
