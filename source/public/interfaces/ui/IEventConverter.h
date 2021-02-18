//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IEventConverter.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __IEVENTCONVERTER__
#define __IEVENTCONVERTER__

#include "IPMUnknown.h"
#include "AppFrameworkID.h"		// IID_IEVENTCONVERTER

class IEvent;
class IEventHandler;

/**	The event converter takes a platform event and changes it into a Shuksan IEvent. Usually this is called from our main event loop. We fetch an OS event, stuff it into a PlatformEvent,
	then we call this interface to fully populate the IEvent with required information, including the event type. After that, the IEvent is usually sent out via a call to IEventDispatcher.
*/
class IEventConverter : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEVENTCONVERTER };
	
	/** 	Takes an IEvent which merely contains a platform event, and converts  it into a real core IEvent. */
	virtual void ConvertIEvent(IEvent& coreEvent) = 0;
	
	/** Called after events are processed to stamp event with end time. */
	virtual void StampWithEndTime(IEvent& theEvent) = 0;

	/** 	During mouse tracking (i.e. between the mouse down, mouse drag, and mouse up) don't accept other events that could terminate the drag.  */
 	virtual void TrackingMouse(bool16 isTracking) = 0;
			
	/** returns whether currently tracking the mouse or not */
	virtual bool16 IsTrackingMouse() const = 0;
		
};


#endif // __IEVENTCONVERTER__
