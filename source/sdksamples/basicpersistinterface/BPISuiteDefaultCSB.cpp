//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPISuiteDefaultCSB.cpp $
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
								
// General includes
#include "K2Vector.tpp"
#include "SelectionExtTemplates.tpp"
#include "GenericID.h"
#include "UIDList.h"

// Project includes
#include "BPIID.h"
#include "IBPIData.h"
#include "IBPISuite.h"
#include "BPISuiteCSB.h"

/** IBPISuite implementation for application and document defaults. 

	This implementation is aggregated
	on kDocumentDefaultSuiteBoss and kApplicationDefaultSuiteBoss allowing
	the IBPIData that is aggregated on kDocWorkspaceBoss and kWorkspaceBoss
	respectively to be manipulated by selection.

	When a document is open but nothing is selected the selection
	targets document defaults.

	When no documents are open the selection targets application defaults.

	@ingroup basicpersistinterface
	
	@see Selection fundamentals chapter in Programming Guide
*/
class BPISuiteDefaultCSB : public BPISuiteCSB
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BPISuiteDefaultCSB (IPMUnknown* boss);
	
	/** Destructor. */
	virtual					~BPISuiteDefaultCSB (void);

protected:
	/**
		Return the UIDs of page items in the layout selection.
	*/
	virtual UIDList GetTarget(void);						
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE (BPISuiteDefaultCSB, kBPISuiteDefaultCSBImpl)

/*
	Instatiate the selection extension template and create an InDesign interface.
	The parameter to the template is the suite implementation class.
*/
template class SelectionExt<BPISuiteDefaultCSB>;
CREATE_PMINTERFACE (SelectionExt<BPISuiteDefaultCSB>, kBPISuiteDefaultSelectionExtImpl)

/* Constructor
*/
BPISuiteDefaultCSB::BPISuiteDefaultCSB(IPMUnknown* iBoss) :
	BPISuiteCSB(iBoss)
{
}

/* Destructor
*/
BPISuiteDefaultCSB::~BPISuiteDefaultCSB(void)
{
}

/*
*/
UIDList BPISuiteDefaultCSB::GetTarget(void)
{
	UIDRef defaultsRef = ::GetUIDRef(this);
	ASSERT(defaultsRef != UIDRef::gNull);
	return UIDList(defaultsRef);
}	
