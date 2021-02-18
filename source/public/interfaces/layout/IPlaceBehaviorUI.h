//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPlaceBehaviorUI.h $
//  
//  Owner: Lonnie Millett
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
//  
//  Return the cursor to use during a place operation and a content dropper operation.  
//	This was moved from IPlaceBehavior.
//  
//========================================================================================

#pragma once
#ifndef __IPlaceBehaviorUI__
#define __IPlaceBehaviorUI__

#include "IPMUnknown.h"
#include "ICursorMgr.h"
#include "GenericID.h"

class IHierarchy;
class ISpread;
class IPlaceBehavior;

/** Interface that lives on a pageitem and is used to determine the 
		cursor feedback and place behavior for a particular location on the screen (within a potential place target).
*/
class IPlaceBehaviorUI : public IPMUnknown {
public:	
	enum { kDefaultIID = IID_IPLACEBEHAVIORUI};

	/** Get the place feedback cursor appropriate at a given location.

		@param globalLocation IN location of the cursor
		@param modifiers IN keyboard modifier state
		@return the appropriate cursor
	*/
	virtual CursorSpec	GetCursor(SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const = 0;

	/** Query for the place behavior interface appropriate at a given location.

		@param point IN location in question
		@return the place behavior
	*/
	virtual IPlaceBehavior* QueryPlaceBehaviorAt(const PMPoint& point) const = 0;

	/** Get the drop feedback cursor appropriate at a given location.

		@param globalLocation IN location of the cursor
		@param modifiers IN keyboard modifier state
		@return the appropriate cursor
	*/
	virtual CursorSpec	GetDropCursor(SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const = 0;
};

#endif

