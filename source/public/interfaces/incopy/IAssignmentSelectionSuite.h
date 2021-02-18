//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAssignmentSelectionSuite.h $
//  
//  Owner: Jon Pugh
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

#pragma once
#ifndef __IAssignmentSelectionSuite__
#define __IAssignmentSelectionSuite__

#include "AssignmentID.h"

#include "IPMUnknown.h"

class IAssignment;

class IAssignmentSelectionSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSIGNMENTSELECTIONSUITE };

	/**
		Determines if the selected object can be assigned
		@return - kTrue if the object can be assigned
	*/
	virtual bool16 CanAssign() = 0;
	
	/**
		Assigns the selected stories to the specified assignment.
		@param assignment - The assignment to add the selected stories to.
		@return - Any error that may have occurred.
	*/
	virtual ErrorCode Assign(IAssignment* assignment) = 0;
};


#endif	// __IAssignmentSelectionSuite__


