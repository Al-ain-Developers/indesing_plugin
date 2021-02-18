//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ISupportedEvents.h $
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
//  
//  Comments: ISupportedEvents says whether an event type is supported.
//  
//========================================================================================

#pragma once
#ifndef __ISupportedEvents_h__
#define __ISupportedEvents_h__

#include "IPMUnknown.h"
#include "BehaviorID.h"

class IBehaviorEvent;

//========================================================================================
// CLASS IBehaviorEvent
//========================================================================================

/** Interface that declares whether a class of events is appropriate for
	a boss.  This is used by Form Fields and Documents, to declare which events can
	be in the behavior list, and thus have actions attached to them.
	For example, a button does not support calculate or format events (it has no
	value to view or change), but a text field does.
	
	It is also used by behavior bosses, so they can declare what events are appropriate
	for their actions.
	For example, a formula action is only appropriate as a response for a calculate event
	
	This is mostly for the benefit of the UI, so that it can build an appropriate list
	of events and actions when adding behaviors to items (eg form fields).
	
	To ensure 3-way extensibility of form fields, events and actions,
	This interface is only to be called indirectly by a SupportedEventsService. This
	service has one method, IsEventSupported, that takes an event and a boss.
	If any service reports true for an event/boss pair then that event is considered
	to be supported.
		
	@see ISupportedEventsService
*/
class ISupportedEvents : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISUPPORTEDEVENTS };
	
	/** Supports Mouse Up/Down/Enter/Over */
	virtual bool16 SupportsMouseEvents() const = 0;
	/** Supports OnFocus/OnBlur */
	virtual bool16 SupportsFocusEvents() const = 0; //focus/blur
	/** Supports PageOpen/Close.  Note these are allowed on buttons, since we
	    don't have a way to attach events,actions to pages. */
	virtual bool16 SupportsPageEvents() const = 0;
	
	/* Supports Format */
	virtual bool16 SupportsFormatEvents() const = 0;
	/* Supports KeyDown */
	virtual bool16 SupportsKeystrokeEvents() const = 0;
	/* Supports Validate */
	virtual bool16 SupportsValidateEvents() const = 0;
	/* Supports Calculate */
	virtual bool16 SupportsCalculateEvents() const = 0;
	/* Supports SignedEvents */
	virtual bool16 SupportsSignedEvents() const = 0;
	/* Supports SelectionChanged */
	virtual bool16 SupportsSelectionChangedEvents() const = 0; //selection changed
	/* Supports DocumentOpen (Document-Wide JavaScript), DocumentWill/Did Close/Save/Print */
	virtual bool16 SupportsDocumentEvents() const = 0;
};

#endif // __IBehaviorEvent_h__
