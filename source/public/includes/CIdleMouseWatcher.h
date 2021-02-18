//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CIdleMouseWatcher.h $
//  
//  Owner: Shawn Sheridan
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
#ifndef __CIdleMouseWatcher__
#define __CIdleMouseWatcher__

//#include "IIdleTask.h"
#include "IEventWatcher.h"
#include "IPMUnknownData.h"
#include "HelperInterface.h"
#ifdef MACINTOSH
#	include <CoreServices/CoreServices.h>
#endif

class MouseWatcherIdleTask;
#pragma export on

/**	An implementation of IEventWatcher that watches the mouse location--but
	not EVERY move.  It works by first installing an idle task that checks the mouse
	location periodically.  If the mouse ever stays put between idle calls,
	the idle task is removed and an event watcher is installed.  As soon as the
	mouse moves again, the idletask is reinstalled and the event watcher uninstalled
	and so on.  You might use this if you want to watch the mouse, but getting every
	mouse movement when the mouse is moving quickly would be overkill--perhaps because
	the user can't consume the information that rapidly or perhaps it would be too
	expensive to call your code on every mouse moved event.  For example, the transform
	palette tracks the mouse location when no page items are selected.  However, a
	person can't read and interpret the displayed values as fast as the mouse-moved
	events are generated.  So this event watcher could be used with an update
	interval of say 250ms.  Likewise, the tool tips need not be instantly up-to-date.
	In fact if they are too lively, it's a little disconcerting.  Moreover, checking
	the needs of tool tips can be expensive on every mouse move.

	Note that this event watcher differs from the usual mouse-event watcher in that
	it won't notice every mouse move (strictly speaking the OS never gives you pixel
	by pixel mouse-moved events anyway).  In that way it may be called far less often
	when the mouse is on the move.  And unlike an idle task that periodically
	gets the global mouse location--when the mouse has come to a stop, nothing
	gets called at all.  Note also that you couldn't just throttle your expensive
	code in an event watcher by waiting until sufficient time has elapsed, because
	you may decide not to call your expensive code yet at the moment the mouse has
	stopped.  Your event watcher won't get called again and your state will be 
	incorrect until the mouse starts moving again.
	An idle task alone can periodically check the mouse location but only by 
	constantly getting called even when the mouse is not moving.

	Note further that the presence of the idle task is opaque to users of this
	class.  You simply use the event watcher API
	
	Clients of this code typically have a custom implementation which is a subclass of CIdleMouseWatcher.
	This subclass usually just needs to override MouseMoved() to do whatever is appropriate.
*/
class PUBLIC_DECL CIdleMouseWatcher : public IEventWatcher
{
public:
	CIdleMouseWatcher(IPMUnknown *boss);
	~CIdleMouseWatcher();
	
	IEventDispatcher::EventTypeList WatchEvent( IEvent* e);		
	
	/**	CIdleMouseWatcher implements this to watch the mouse events appropriately. Subclasses don't need to
		override unless there are additional events they want to register for.
	*/
	void StartWatching();
	
	/**	CIdleMouseWatcher implements this to stop watching the mouse events appropriately. Subclasses don't need to
		override unless there are additional events they need to unregister for.
	*/
	void StopWatching();
	
	enum { kEndOfTime = ~(uint32)0};
	
	/**	Subclasses must override this to do whatever is appropriate when the mouse has moved.
		Return sleep time in milliseconds before being called again. Returning kEndOfTime will, in effect, calls CIdleMouseWatcher::StopWatching--i.e., not the derived class' StopWatching.
	*/
	virtual uint32 MouseMoved(GSysPoint) = 0;
	
	/**	StartingMousePoint is called by StartWatching--override to tell the watcher where you think the mouse is now.
		The inherited version returns (0,0) which will almost ensure one call to MouseMoved before the mouse actually moves
		*/
	virtual GSysPoint StartingMousePoint();
private:
	friend class MouseWatcherIdleTask; //needs private access to fMouseMoving
	IPMUnknownData* fAccomplice;
	enum { kNoOneWatching, kIdleTaskWatching, kEventWatcherWatching} fWhoIsWatching;  //an optimization so I don't have to ask the IdleTaskMgr or EventDispatcher which is active
	void Farewell();
	bool16	fbInWatchEvent, fStopWhileInMouseMoved;
	DECLARE_HELPER_METHODS()
};

#pragma export off

#endif // __CIdleMouseWatcher__
