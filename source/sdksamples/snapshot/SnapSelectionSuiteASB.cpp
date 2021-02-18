//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapSelectionSuiteASB.cpp $
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

#include "CPMUnknown.h"

// ----- Interfaces files
#include "IIntegratorTarget.h"
#include "SnapshotUtilsEx.h"

// ----- ID files
#include "SnapID.h"
#include "ISnapSelectionSuite.h"
#include "SelectionASBTemplates.tpp"	// for make_functor

/**
	Abstract selection class implementation of ISnapSelectionSuite.

	@ingroup snapshot
	

*/
class SnapSelectionSuiteASB : public CPMUnknown<ISnapSelectionSuite>
{
	public:
		/** Constructor
		*/
		SnapSelectionSuiteASB (IPMUnknown* boss);
		  

		/**	Destructor
		 */
		virtual ~SnapSelectionSuiteASB ();


		/**	See ISnapSelectionSuite::CreateSnapshot
		 */
		virtual SnapshotUtilsEx* CreateSnapshot(ISpread* spread);

		/**	See ISnapSelectionSuite::SelectionIsEmpty
		 */
		virtual bool16 SelectionIsEmpty();


};

CREATE_PMINTERFACE (SnapSelectionSuiteASB, kSnapSelectionSuiteASBImpl)


SnapSelectionSuiteASB::SnapSelectionSuiteASB(IPMUnknown* boss) :
		CPMUnknown<ISnapSelectionSuite>(boss)
{
}

SnapSelectionSuiteASB::~SnapSelectionSuiteASB()
{
}

SnapshotUtilsEx* SnapSelectionSuiteASB::CreateSnapshot(ISpread* spread)
{
	ASSERT(spread);
	InterfacePtr<IIntegratorTarget>	iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> snapSuites (iIntegratorTarget->GetTarget ( IID_ISNAPSELECTIONSUITE));
	ASSERT(snapSuites->size() <=1);

	if (snapSuites->size() == 1)
	{
		ISnapSelectionSuite* selectionSuites = (ISnapSelectionSuite*) ((*snapSuites)[0].get());
		return selectionSuites->CreateSnapshot(spread);
	} else
	{
		return nil;
	}
}


bool16 SnapSelectionSuiteASB::SelectionIsEmpty()	
{
	return (AnyCSBSupports (make_functor(&ISnapSelectionSuite::SelectionIsEmpty), this, IID_ISNAPSELECTIONSUITE));
}

