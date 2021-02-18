//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptEventListener.h $
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
#ifndef __IScriptEventListener__
#define __IScriptEventListener__

#include "ScriptingID.h"
#include "ScriptData.h"

/**
	Represents an event handler for scripting events.
*/
class IScriptEventListener : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTEVENTLISTENER } ;

	/**
		Initialize this ScriptEventListener.
		@param eventType the event name
		@param handler is the script to execute in response to an event
	*/
	virtual void				Init( const PMString& eventType, const ScriptData& handler ) = 0 ;

	/** The unique id of this event listener */
	virtual int32				GetID() const = 0 ;

	/** The name of the event to handle */
	virtual const PMString&		GetEventType() const = 0 ;

	/** The handler for the event */
	virtual const ScriptData&	GetHandler() const = 0 ;

	/** State of a listener */
	enum State
	{
		/** Listener exists but is not yet active */
		kNew,
		/** Listener exists and should be called */
		kAlive,
		/** Listener exists but is no longer active */
		kDead
	} ;

	/** The current state of the listener */
	virtual State				GetState() const = 0 ;

	// ----- FOR INTERNAL USE ONLY -----
	/** Set the state of the listener */
	virtual void				SetState( State state ) = 0 ;
} ;

typedef K2Vector< InterfacePtr<IScriptEventListener> > ScriptEventListenerList ;

#endif
