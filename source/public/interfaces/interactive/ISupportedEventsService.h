//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ISupportedEventsService.h $
//  
//  Owner: Tim Wright
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
//  Comments: ISupportedEventsService says whether a boss (e.g. a form field or action)
//  Supports an IBehaviorEvent.
//  
//========================================================================================

#pragma once
#ifndef __ISupportedEventsService_h__
#define __ISupportedEventsService_h__

#include "IPMUnknown.h"
#include "BehaviorID.h"

class IBehaviorEvent;
class ISupportedEvents;

//========================================================================================
// CLASS IBehaviorEvent
//========================================================================================

/** Interface that declares whether an event is "appropriate" for
	a boss.  This is used by Form Fields and Documents, to declare which events can
	be in the behavior list, and thus have actions attached to them.
	For example, a button does not support calculate or format events (it has no
	value to view or change), but a text field does.
	
	It is also used by behavior bosses, so they can declare what events are appropriate
	for their actions.
	For example, a formula action is only appropriate as a response to a calculate event
	
	This is mostly for the benefit of the UI, so that it can build an appropriate list
	of events and actions when adding behaviors to items (eg form fields).

	If any ISupportedEventsService service reports true for an event/boss pair then that event is considered
	to be supported, this allows for extensibility of events and bosses that support events.

	The Behavior plugin implements one service of this type, kStandardSupportedEventsImpl,
	which queries the IBehaviorEvent SupportsEvent,  SupportsEvent then calls the ISupportedEvents
	interface on inBoss to see if the boss supports the event
	
	This means for all the standard bosses (Form Fields, Documents, Behaviors)
	that support events, we only need to implement ISupportedEvents, but since
	ISupportedEvents is called indirectly, we still allow
	for extensibility of actions, form fields and events...
		
	@see StandardSupportedEvents, ISupportedEvents, IBehaviorEvent
*/
class ISupportedEventsService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISUPPORTEDEVENTSSERVICE };
	
	virtual bool16 IsEventSupported(IBehaviorEvent* inEvent, IPMUnknown* inBoss) const = 0;
};

#endif // __ISupportedEventsService_h__
