//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagListTreeController.cpp $
//  
//  Owner: Michele Stutzman
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

// ----- Interfaces -----


// ----- Includes -----

#include "CTreeViewController.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class  ConditionTagListTreeController : public CTreeViewController
{
public:
	ConditionTagListTreeController(IPMUnknown *boss);
	~ConditionTagListTreeController();

protected:
	virtual void ProcessSelectionRules(IEvent* event, UID nodeWidgetUID, bool16 notifyOfChange);
};

// =============================================================================
// *** ConditionTagListTreeController impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(ConditionTagListTreeController, kConditionTagListTreeControllerImpl)

ConditionTagListTreeController::ConditionTagListTreeController(IPMUnknown *boss)
	: CTreeViewController(boss)
{
} // end constructor

ConditionTagListTreeController::~ConditionTagListTreeController()
{
} // end destructor

// -----------------------------------------------------------------------------

void ConditionTagListTreeController::ProcessSelectionRules(IEvent* event, UID nodeWidgetUID, bool16 notifyOfChange)
{
	// TODO - borrow from StyleTVController.cpp or SwatchesTreeViewController do
	// condition doesn't apply when drag and drop to trash.

	return CTreeViewController::ProcessSelectionRules(event, nodeWidgetUID,notifyOfChange);
} // end ProcessSelectionChanges()