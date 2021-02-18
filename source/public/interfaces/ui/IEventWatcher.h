//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IEventWatcher.h $
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
#ifndef __IEventWatcher__
#define __IEventWatcher__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "IEventDispatcher.h"
class IEvent;

/**	 This interface provides an easy way for snooping at events as they are dispatched
  
  The event dispatcher maintains a list of event watchers. As events are 
  dispatched to the event handlers, they are also passed to the EventWatchers.
  Some example uses of event watchers
  o  drawing the mouse position in the rulers
  o  drawing the mouse position in the transform panel
  o  maintaining the shape of the mouse pointer
  o  implementing tool tips
  Many of these used to be done in the IdleTaskMgr but caused some significant
  performance problems there.
*/
class IEventWatcher : public IPMUnknown	{
public:
	enum { kDefaultIID = IID_IEVENTWATCHER };
	
	/** Called by the EventDispatcher before the event is dispatched. Returns the list of event kinds that are now of interest.
		If the EventList is empty, this IEventWatcher is removed from the EventDispatcher. (StopWatching would not be called)
		@param e the event to watch
		@return new list of events of interest
	*/
	virtual IEventDispatcher::EventTypeList WatchEvent( IEvent* e) = 0;

	/** This is a hook for implementations of register interest in events they want to watch. Typically calls the AddEventWatcher
		 method of the app's only EventDispatcher for each event of interest.
	*/
	virtual void StartWatching() = 0;

	/**	This method is a hook for implmentations to unregister interest in events. Typically calls the RemoveEventWatcher method 
		of the app's only EventDispatcher for each event of interest.
	*/
	virtual void StopWatching() = 0;
};


#endif // __IEventWatcher__
