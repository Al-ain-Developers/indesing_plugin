//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelSuiteASB.cpp $
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
#include "IDataBase.h"
#include "IDocument.h"

// Implementation includes:
#include "CPMUnknown.h"
#include "SelectionASBTemplates.tpp"

// Project includes:
#include "IPrnSelData.h"
#include "IPrnSelSuite.h"
#include "PrnSelID.h"


/** Integrator IPrnSelSuite implementation. Uses templates
	provided by the API to delegate calls to IPrnSelSuite
	implementations on underlying concrete selection boss
	classes.

	@ingroup printselection
*/
class PrnSelSuiteASB : public CPMUnknown<IPrnSelSuite>
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PrnSelSuiteASB(IPMUnknown* boss);

	/**	Destructor.
	*/
	virtual ~PrnSelSuiteASB(void);

	/** Creates a list of UIDs of selected items.
	*/
	virtual void StoreSelectionData(void);

	/** Can the print selection flag be retrieved? 
	 * 	@see IPrnSelSuite::CanGetPrintSelectionFlag
	 */
	virtual bool16 CanGetPrintSelectionFlag(void);

	/** Get the print selection flag. 
	 * 	@see IPrnSelSuite::GetPrintSelectionFlag
	 */
	virtual bool16 GetPrintSelectionFlag(void);

	/** Can the print selection flag be set? 
	 * 	@see IPrnSelSuite::CanSetPrintSelectionFlag
	 */
	virtual bool16 CanSetPrintSelectionFlag(void);

	/** Set the print selection flag. 
	 * 	@see IPrnSelSuite::SetPrintSelectionFlag
	 */
	virtual ErrorCode SetPrintSelectionFlag(const bool16 printSelection);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class to its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelSuiteASB, kPrnSelSuiteASBImpl)


/* Constructor
*/
PrnSelSuiteASB::PrnSelSuiteASB(IPMUnknown* boss) 
: CPMUnknown<IPrnSelSuite>(boss)
{
}

/* Destructor
*/
PrnSelSuiteASB::~PrnSelSuiteASB(void) 
{
}


/* StoreSelectionData
*/
void PrnSelSuiteASB::StoreSelectionData(void)
{
	CallEach(make_functor(&IPrnSelSuite::StoreSelectionData), this, IPrnSelSuite::kDefaultIID);
}

/* CanGetPrintSelectionFlag
*/
bool16 PrnSelSuiteASB::CanGetPrintSelectionFlag(void)
{
	return (AnyCSBSupports(make_functor(&IPrnSelSuite::CanSetPrintSelectionFlag), this));
}

/* GetPrintSelectionFlag
*/
bool16 PrnSelSuiteASB::GetPrintSelectionFlag(void)
{
	return (Process(make_functor(&IPrnSelSuite::GetPrintSelectionFlag), this, IPrnSelSuite::kDefaultIID));
}

/* CanSetPrintSelectionFlag
*/
bool16 PrnSelSuiteASB::CanSetPrintSelectionFlag(void)
{
	return (AnyCSBSupports(make_functor(&IPrnSelSuite::CanSetPrintSelectionFlag), this));
}

/* SetPrintSelectionFlag
*/
ErrorCode PrnSelSuiteASB::SetPrintSelectionFlag(const bool16 printSelection)
{
	return (Process(make_functor(&IPrnSelSuite::SetPrintSelectionFlag, printSelection), this, IPrnSelSuite::kDefaultIID));
}

// End,	PrnSelSuiteASB.cpp

