//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPISuiteLayoutCSB.cpp $
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
#include "K2Vector.tpp"
#include "SelectionExtTemplates.tpp"
#include "GenericID.h"

// Project includes
#include "BPIID.h"
#include "IBPISuite.h"
#include "BPISuiteCSB.h"		// Superclass declaration

/** IBPISuite implementation for the layout CSB that gets used when a layout
	selection exists; it examines ILayoutTarget and return a UIDList
	of page items (IBPIData is an interface added to page items by this plug-in).
	
	The rest of the implementation is provided by BPISuiteCSB.
	 
	@ingroup basicpersistinterface
	
	@see Selection fundamentals chapter in Programming Guide
*/
class BPISuiteLayoutCSB : public BPISuiteCSB
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BPISuiteLayoutCSB (IPMUnknown* boss);
	
	/** Destructor. */
	virtual					~BPISuiteLayoutCSB (void);

protected:
	/** @return list of objects in ILayoutTarget with standoffs stripped.
	*/
	virtual UIDList GetTarget(void);						
};

/*
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE (BPISuiteLayoutCSB, kBPISuiteLayoutCSBImpl)

/*
	Binds the suite onto its selection extension making the 
	selection extension member functions in the suite
	callable by the selection subsystem.
	The parameter to the template is the suite implementation class.
*/
template class SelectionExt<BPISuiteLayoutCSB>;
CREATE_PMINTERFACE (SelectionExt<BPISuiteLayoutCSB>, kBPISuiteLayoutSelectionExtImpl)

/* Constructor
*/
BPISuiteLayoutCSB::BPISuiteLayoutCSB(IPMUnknown* iBoss) :
	BPISuiteCSB(iBoss)
{
}

/* Destructor
*/
BPISuiteLayoutCSB::~BPISuiteLayoutCSB(void)
{
}

/*
*/
UIDList BPISuiteLayoutCSB::GetTarget(void)
{
	UIDList result;
	do {
		InterfacePtr<ILayoutTarget> layoutTarget(this, UseDefaultIID());
		ASSERT(layoutTarget);
		if (!layoutTarget) {
			break;
		}
		result = layoutTarget->GetUIDList(kStripStandoffs);
	} while(false);
	return result;
}	


