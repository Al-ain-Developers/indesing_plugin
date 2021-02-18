//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ui/IBehaviorDragDropData.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __IBehaviorDragDropData_h__
#define __IBehaviorDragDropData_h__

#include "IPMUnknown.h"
#include "BehaviorUIID.h"
#include "BehaviorTypes.h"
#include <vector>

//========================================================================================
// CLASS IBehaviorDragDropData
//========================================================================================

/** Interface on kEventDragDropDEHandlerBoss, kPageItemDDTargetBehaviorHelperBoss
	to specify data of a behavior or event drag
*/
class IBehaviorDragDropData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBEHAVIORDRAGDROPDATA };

	/** Remove all events/behaviors from the drag data */
	virtual void Clear() = 0;

	/** @return if there are any events/behaviors in the drag data */
	virtual bool16 IsEmpty() const = 0;
	
	/** Populate the drag data with events and behaviors.
		@param db source database of the behaviors
		@param behaviors A list of pairs of events and behavior UIDs */
	virtual void Set(IDataBase* db, const std::vector< std::pair<ActionEvent, UID> >& behaviors) = 0;
	
	/** @return the database of the behaviors */
	virtual IDataBase* GetDataBase() const = 0;

	/** @return A list of pairs of events and behavior UIDs in the drag */
	virtual std::vector< std::pair<ActionEvent, UID> > Get() const = 0;
};

#endif // __IBehaviorDragDropData_h__
