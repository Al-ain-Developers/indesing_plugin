//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITrackerTimer.h $
//  
//  Owner: robin briggs
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
#ifndef __ITrackerTimer__
#define __ITrackerTimer__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "IIdleTask.h"

class ITracker;


const uint32 kDefaultMouseMoveDelay = 250;
const uint32 kDefaultMouseSteadyDelay = 50;

/** Defines an interface used to start a timer during tracking. 
	Typically a timer is started in BeginTracking and stopped in EndTracking.

	@see ITracker.h
	@see IIdleTask.h
*/
class ITrackerTimer : public IIdleTask
{
	public:

		/**	Start a timer that will be run periodically during tracking after a certain amount of time elapses.
			Used internally by some tracker to start up patient user mode.
			@param callBack [IN] ITracker* object to initiate timer with (you can use to store the object for use by by timer. e.g. callback to ITracker->TimerMessage).
			@param milliSeconds [IN] how frequently in milliseconds before first RunTask is called.
			@param mouseMoveDelay [IN] how frequently in milliseconds RunTask is called while mouse is moving.
			@param mouseSteadyDelay [IN] how frequently in milliseconds RunTask is called while mouse is not moving.
			@see IIdleTask.h
			@see kPatientUserBoss
		 */
		virtual void StartTimer(ITracker *callBack, uint32 milliSeconds, uint32 mouseMoveDelay = kDefaultMouseMoveDelay, uint32 mouseSteadyDelay = kDefaultMouseSteadyDelay) = 0;

		/**	Stop the timer
		 */
		virtual void StopTimer() = 0;
};
		
#endif // __ITrackerTimer__
