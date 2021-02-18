//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IBehaviorList.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IBehaviorList_h__
#define __IBehaviorList_h__

#include "IPMUnknown.h"
#include "BehaviorID.h"
#include "BehaviorTypes.h"

#include <vector>

/** A list events which in turn have lists of Behavior bosses. These Behavior bosses should have an IBehaviorData interfaces
*/
class IBehaviorList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBEHAVIORLIST };
	
	/** Declare ownership of a behavior. That is, behavior will be deleted by the IBehaviorList's boss.
		@param inEvent The event the inBehavior will belong to
		@param inBehavior A boss UID for the behavior
		@param inPosition Order for inBehavior. -1, the default, puts inBehavior at the end of the list for inEvent,
				otherwise inBehavior is placed at position in list.
	*/
	virtual void				Adopt(const ActionEvent& inEvent, const UID& inBehavior, const int32& inPosition = -1) = 0;

	/** Give up ownership of a behavior.
		@param behavior A boss UID for the behavior
		@return event behavior was attached to.
	*/
	virtual ActionEvent			Relinquish(const UID& inBehavior) = 0;
	
	/** @return A list of all the behavior boss UIDs for the event inForEvent */
	virtual std::vector<UID>							Get(const ActionEvent& inForEvent) const = 0;

	/** @return All event lists containing all the behavior boss UIDs in this IBehaviorList */
	virtual std::vector< std::pair<ActionEvent, UID> >	Get() const = 0;
};

#endif // __IBehaviorList_h__
