//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicmenu/BscMnuSuiteLayoutCSB.cpp $
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
#include "ILayoutTarget.h"
#include "IBscMnuSuite.h"										// Superclass declaration

// Other headers
#include "CmdUtils.h"

// Project headers

//	CLASS DECLARATIONS

/** 
	Layout concrete selection boss (CSB) IBscMnuSuite implementation.  The suite implementations on the CSBs are 
	responsible for doing all of the model specific work.  The implementation of a CSB suite deals with the 
	model format of its owning boss. The only information that the suite should need is from sibling interfaces 
	on the CSB, primarily the target interface. This interface specifies which items to act upon. For the 
	LayoutCSB, the target interface is ILayoutTarget which wraps a UIDList. So usually you see the methods in
	this CSB will first get an InterfacePtr to a ILayoutTarget, then it gets the UIDList of the selected items
	from the pointer.
	
    Note that the client does not interact with the CSB (which has all the real implementation of the suite) 
    directly, the client interacts with the ASB only.  Also note that the Suite API shouldn't contain model 
    data that is specific to a selection format (layout uidLists, text model/range, etc) so that the client 
    code can be completely decoupled from the underlying CSB.
	 
	@ingroup basicmenu
	
*/
class BscMnuSuiteLayoutCSB : public CPMUnknown<IBscMnuSuite>
{
public:
	/**
		Constructor.
		@param iBoss interface ptr from boss object on which this interface is aggregated.
	*/
	BscMnuSuiteLayoutCSB(IPMUnknown* iBoss);
	
	/** Destructor. */
	virtual					~BscMnuSuiteLayoutCSB(void);

//	Suite Member functions
public:
	/**
		See IBscMnuSuite::CanApplyBscMnu
	*/
	virtual bool16			CanApplyBscMnu(void);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(BscMnuSuiteLayoutCSB, kBscMnuSuiteLayoutCSBImpl)

/* Constructor
*/
BscMnuSuiteLayoutCSB::BscMnuSuiteLayoutCSB(IPMUnknown* iBoss) :
	CPMUnknown<IBscMnuSuite>(iBoss)
{
}

/* Destructor
*/
BscMnuSuiteLayoutCSB::~BscMnuSuiteLayoutCSB(void)
{
}

#pragma mark -
/* CanApplyBscMnu
*/
bool16 BscMnuSuiteLayoutCSB::CanApplyBscMnu(void)
{
	InterfacePtr<ILayoutTarget>		iLayoutTarget(this, UseDefaultIID());
	const UIDList					selectedItems(iLayoutTarget->GetUIDList(kStripStandoffs));

	// if the current selection has at least one drawable page item
	// then we will return true so the client code can apply the data
	if (selectedItems.Length() > 0)
	{
		return (kTrue);
	}
	else
	{
		return (kFalse);
	}
}

