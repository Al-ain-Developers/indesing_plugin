//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IIdleTaskThread.h $
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
//  
//  Purpose:
//  
//  Review Date:
//  
//========================================================================================

#pragma once
#ifndef __IIdleTaskThread__
#define __IIdleTaskThread__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "IIdleTask.h"
#include <boost/function.hpp>


/** An implementation of IIdleTask that uses cooperative threads to
	perform its task.  You would use this if your idle task might
	take a long time to execute and you want to be able to yield
	back to the event loop without "losing your place", (i.e., you
	keep track of how far along your task is by using the stack and the
	program counter).
*/
class IIdleTaskThread : public IIdleTask
{
	public:
		enum { kDefaultIID = IID_IIDLETASKTHREAD };

		/** Causes this thread to yield itself to the event loop rather than allowing it to hog all of the processor time
			@param millisecSleep - The number of milliseconds this thread should sleep before reawakening.
			@return - The current App Flags will get returned to the client.
		*/
		virtual uint32 YieldToEventLoop( uint32 millisecSleep = 0) = 0;
	
		/** Generic task definition.
		*/
		typedef boost::function<void ()> Task;

		/** INTERNAL USE ONLY! Should be used only by the architecture team!
			Invokes the specified task in the main application thread.
			If the call is happening in another thread, this IdleTaskThread will switch to the main thread, execute the task and come right back.
			If the context is already the main thread, the task will simply be executed.
			It will NOT go through the event loop.
			This is useful when a component is really tied to the main execution thread (like UI) and it needs to be executed only in that context.
		*/
		virtual void ExecuteTaskInMainThread(Task& task) = 0;
};


#endif // __IIdleTaskThread__
