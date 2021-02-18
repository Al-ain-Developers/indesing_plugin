//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptEvent.h $
//  
//  Owner: Jonathan W. Brown
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#ifndef __IScriptEvent__
#define __IScriptEvent__

#include "IDTime.h"
#include "ScriptingID.h"

class IScript ;
class IScriptEventTarget ;

/**
	An attachable event for scripting.
*/
class IScriptEvent : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTEVENT } ;

	/** Propagation phases of the event.
		Note: kAtTarget == 2 and kBubble == 3 are defined in the W3C standard @see http://www.w3.org/TR/DOM-Level-2-Events/events.html
	*/
	enum EventPhase
	{
		/** Not propagating */
		kNotDispatching		= 0	,
		/** At target phase */
		kAtTarget			= 2	,
		/** Bubbling phase */
		kBubblingPhase		= 3,
		/** Done propagating */
		kDoneDispatching	= -1
	} ;

	/**
		Initialize this ScriptEvent.
		@param eventType the event name
		@param bubbles if kTrue the event is triggered in ancestors of the target object during the bubbling phase
		@param cancelable if kTrue the event can be canceled
	*/
	virtual void		InitEvent( const PMString& eventType, bool16 bubbles, bool16 cancelable ) = 0 ;

	/** The unique id of this event */
	virtual int32		GetID() const = 0 ;

	/** The name of this event */
	virtual PMString	GetEventType() const = 0 ;

	/** The target object where this event occurred */
	virtual IScript*	QueryTarget() const = 0 ;

	/** The target object where the currently executing handler is registered. 
		This could be an ancestor of the target object if the handler is 
		invoked during the bubbling phase. */
	virtual IScript*	QueryCurrentTarget() const = 0 ;

	/** Returns the current event propagation phase */
	virtual EventPhase	GetEventPhase() const = 0 ;

	/** Returns whether this event supports the bubbling phase */
	virtual bool16		GetBubbles() const = 0 ;

	/** Returns whether this event may be canceled */
	virtual bool16		GetCancelable() const = 0 ;

	/** Returns when this event was initiated */
	virtual IDTime		GetTimeStamp() const = 0 ;

	/** Stops event propagation after executing the current handler */
	virtual void		StopPropagation() = 0 ;

	/** Returns whether propagation has been stopped */
	virtual bool16		GetPropagationStopped() const = 0 ;

	/** Cancels the default action of this event, if this event is cancelable */
	virtual void		PreventDefault() = 0 ;

	/** Returns whether this event's default action has been canceled */
	virtual bool16		GetDefaultPrevented() const = 0 ;

	// ----- FOR INTERNAL USE ONLY -----
	/**
		Set the target of this event
		@param target is the target
	*/
	virtual void		SetTarget( IScript* target ) = 0 ;

	/**
		Set the target object where the currently executing handler is registered
		@param target is the current target
	*/
	virtual void		SetCurrentTarget( IScript* target ) = 0 ;

	/**
		Set the current event propagation phase
		@param phase is the current phase
	*/
	virtual void		SetEventPhase( EventPhase phase ) = 0 ;
} ;

typedef K2Vector< InterfacePtr<IScriptEvent> > ScriptEventList ;

#endif
