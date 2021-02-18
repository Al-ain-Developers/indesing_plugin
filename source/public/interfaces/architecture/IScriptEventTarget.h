//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptEventTarget.h $
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
#ifndef __IScriptEventTarget__
#define __IScriptEventTarget__

#include "IPMUnknown.h"

#include "IScriptEventListener.h"

class IScriptEvent ;

/**
	Any object that can be the target of attachable events in scripting
	should aggregate this interface to the same boss as its IID_ISCRIPT.
*/
class IScriptEventTarget : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTEVENTTARGET };

	/**
		Some events have additional properties that must be initialized prior to dispatch,
		or used to update the object model after the event finishes propagation. In this
		case, pass an InitEventCallback function to DispatchScriptEvent. The IScriptEvent
		interface on the initialized event will be passed to this function before and after
		propagation.

		A good example of this is a MutationEvent. See @IScriptMutationData.h.
	*/
	typedef enum { kPreDispatch, kPostDispatch } InitCallbackType ; 
	typedef void (*InitEventCallback)( IScriptEvent* e, InitCallbackType t, void* privateData ) ;
	/**
		Dispatch an attachable event
		@param eventID - ID of the event
		@param initCallback - function to call before and after the event is dispatched
		@param privateData - private data to pass to the InitEventCallback function
		@return - none, but if default action is canceled by an event handler, 
			sets the global error code to kCancel
	*/
	virtual void DispatchScriptEvent( ScriptElementID eventID, InitEventCallback initCallback = nil, void* privateData = nil ) = 0 ;

	//------------------------------------------------------------------------------------------------------
	//	EventListeners
	//------------------------------------------------------------------------------------------------------

	/**
		Checks whether an event listener is registered with this event target object or 
		any of its ancestors for the specified event type.
		@param eventType is the event type IN
		@param bubbles pass kTrue if the event bubbles and you want to check for event 
			listeners on this target's ancestors
	*/
	virtual bool16 WillTriggerEventListeners( const PMString& eventType, bool16 bubbles ) const = 0 ;

	/**
		Get the number of event listeners registered on this target
	*/
	virtual int32 GetNumEventListeners() const = 0 ;

	/**
		Get the number of event listeners registered on this target for a particular event type
		@param eventType is the event type IN
	*/
	virtual int32 GetNumEventListeners( const PMString& eventType ) const = 0 ;

	/**
		Return the nth event listener registered on this target. The order of event listeners is arbitrary.
		@param n is the index of the desired listener IN
		@return the nth listener or nil if none
	*/
	virtual IScriptEventListener* QueryNthEventListener( int32 n ) const = 0 ;

	/**
		Return the nth event listener registered on this target for a particular event type. The order of event listeners is arbitrary.
		@param n is the index of the desired listener IN
		@param eventType is the event type IN
		@return the nth listener or nil if none
	*/
	virtual IScriptEventListener* QueryNthEventListener( int32 n, const PMString& eventType ) const = 0 ;

	/**
		Return every event listener registered on this target. The order of event listeners is arbitrary.
		@param eventListeners is the array of listeners OUT
	*/
	virtual void GetEventListeners( ScriptEventListenerList& eventListeners ) const = 0 ;

	/**
		Return every event listener registered on this target for a particular event type. The order of event listeners is arbitrary.
		@param eventListeners is the array of listeners OUT
		@param eventType is the event type IN
	*/
	virtual void GetEventListeners( ScriptEventListenerList& eventListeners, const PMString& eventType ) const = 0 ;

	/**
		Register an event listener on this target, unless one already exists with the same parameters on this target.
		@param eventListener is the listener to add IN
		@return whether the event listener was added
	*/
	virtual bool16 AddEventListener( IScriptEventListener* eventListener ) = 0 ;

	/**
		Remove an event listener from this target, if one exists with the same parameters on this target.
		@param eventListener is the listener to remove IN
		@return whether the event listener was removed
	*/
	virtual bool16 RemoveEventListener( IScriptEventListener* eventListener ) = 0 ;

	/**
		Find a matching event listener, if one exists with the same parameters on this target.
		@param eventType is the event type for which the listener is registered IN
		@param handler is the registered callback IN
		@return the matching event listener, or nil if none
	*/
	virtual IScriptEventListener* QueryMatchingEventListener( const PMString& eventType, const ScriptData& handler ) const = 0 ;

	/**	For INTERNAL USE ONLY by implementations of IScriptEventTarget::DispatchScriptEvent().
		Increment/decrement the busy count for event listeners of a given type on this target.
		@param eventType is the event type that is busy IN
		@param bBusy is kTrue to increment, kFalse to decrement IN
	*/
	virtual void SetBusy( const PMString& eventType, bool16 bBusy ) = 0 ;

	/**
		Is this object the target of a propagating event
		@return kTrue if so, kFalse if not
	*/
	virtual bool16 IsBusy() const = 0 ;

	//------------------------------------------------------------------------------------------------------
	//	Events
	//------------------------------------------------------------------------------------------------------

	/**
		Get the number of active events on this target of a particular event type
		@param type of events (to get all events, pass c_Event) IN
		@param context is the script request context IN
		@return the number of events
	*/
	virtual int32 GetNumEvents( const ScriptID& type, const RequestContext& context ) const = 0 ;

	/**
		Return the nth active event on this target of a particular event type
		@param n is the index of the desired event IN
		@param type of events (to get all events, pass c_Event) IN
		@param context is the script request context IN
		@return the nth event
	*/
	virtual IScriptEvent* QueryNthEvent( int32 n, const ScriptID& type, const RequestContext& context ) const = 0 ;

	/**	For INTERNAL USE ONLY by implementations of IScriptEventTarget::DispatchScriptEvent().
		Add an event to this target.
		@param the event IN
	*/
	virtual void PushEvent( IScriptEvent* e ) = 0 ;

	/**	For INTERNAL USE ONLY by implementations of IScriptEventTarget::DispatchScriptEvent().
		Remove an event from this target.
		@return the event
	*/
	virtual IScriptEvent* PopEvent() = 0 ;
};

#endif
