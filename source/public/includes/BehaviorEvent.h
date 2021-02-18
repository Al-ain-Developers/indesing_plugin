//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BehaviorEvent.h $
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
#ifndef __BehaviorEvent_h__
#define __BehaviorEvent_h__

#include "IBehaviorEvent.h"
#include "CPMUnknown.h"

//========================================================================================
// TEMPLATE BehaviorEvent
//========================================================================================

/** Template data interface for an Event that can have attached behaviors
	Examples are MouseDown, MouseUp, ...
	@see IBehaviorEvent
*/
template <int32 Event>
class BehaviorEvent : public CPMUnknown<IBehaviorEvent>
{
public:
	/**	Construct a new BehaviorEvent object
	*/
	BehaviorEvent(IPMUnknown *boss) : 
		CPMUnknown<IBehaviorEvent>(boss) { }
	
	/** Destroy a BehaviorEvent object
	*/
	virtual ~BehaviorEvent() { }
	
	/** Returns a unique enum for the event. Value is in kBehaviorEventIDSpace. e.g. kPageOpenEvt */
	virtual ActionEvent	GetEvent() const
	{
		return Event;
	}
	
	/** Returns a user-readable name for the event e.g. "Mouse Down" */
	virtual PMString GetName() const
	{
		return PMString();
	}
	
	/** Returns a PDF action dictionary key as a PMString for the event e.g. "U" for mouse up,
		used to generate the PDF action dictionary for actions that belong to this event */
	virtual PMString GetDictionaryKey() const
	{
		return PMString();
	}
	
	/** Returns kTrue if this is an event that applies to a page, i.e. does the event belong in
		a page's "AA" dict rather than an annotation's "AA" dict.  */
	virtual bool16 IsPageEvent() const
	{	
		return kFalse;
	}
	
	/** Returns kTrue if IPMUnknown can 'respond' to events. IPMUnknown could be an IBehaviorData
		interface or a IFormField interface, but is not limited to this.
	*/
	virtual bool16 		SupportsEvent(IPMUnknown* inBoss)
	{
		return kFalse;
	}
};

#endif // __BehaviorEvent_h__
