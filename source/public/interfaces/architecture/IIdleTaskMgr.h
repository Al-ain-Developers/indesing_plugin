//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IIdleTaskMgr.h $
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
#ifndef __IIdleTaskMgr__
#define __IIdleTaskMgr__

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IIdleTask;

/*
	The IdleTaskMgr maintains a queue of active tasks and a queue of suspended tasks 
	to run when its RunOverdueTasks method is called from the main event loop.  The active
	tasks are prioritized on the time they want to run.

	Idle tasks are a cheap version of threads. They have no stack space of their own, 
	so the memory footprint is very small.

	The only way to check if a task is installed using the IdleTaskMgr directly
	is to remove and re-add it like this:

	<pre>
	uint32 when = RemoveTask(task);
	if( when != IIdleTask::kEndOfTime){
		//was installed so put it back
		AddTask( task, when);
	}else{
		//wasn't currently installed
	}
	</pre>
*/
class IIdleTaskMgr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IIDLETASKMGR };

		/** The state of the application */
		typedef enum ApplicationStateFlags { //these will likely move to the app
			/** */
			kInBackground = 1,
			/** */
			kModalDialogUp = 2,
			/** */
			kMenuUp = 4,
			/** */
			kMouseTracking = 8,
			/** i.e., a real event caused this trip through the event loop as opposed to a sleep timeout */
			kUserActive = 16,
			/** */
			kApplicationMinimized = 32,
			/** a task was enqueued to the main thread queue */
			kMainThreadTaskQueued = 64
		} ApplicationStateFlags;
		/** Set the application state flags */
		virtual void SetApplicationState(uint32 flags) = 0;
		/** Get the application state flags */
		virtual uint32 GetApplicationState() = 0;

		/**
			Add a new task to the list of active tasks.
			Note that it is illegal to add the same task twice.
			@param newTask is the new task
			@param initialMillisecondDelay is the number of milliseconds to wait until the first time this task is run
		*/
		virtual void AddTask(IIdleTask *newTask, uint32 initialMillisecondDelay = 0) = 0;

		/**
			Remove a task from the list of tasks to run. Note that it is significantly 
			more efficient to have a task remove itself when its RunTask method is called.
			@see IIdleTask
			@param taskToRemove is the task to remove
			@return the number of milliseconds before this task was scheduled to run. If it 
			was already overdue, it returns zero. If the task wasn't installed or it is 
			currently running, returns IIdleTask::kEndOfTime. May return IIdleTask::kOnFlagChange
			or IIdleTask::kNextEventCycle if the task to remove was suspended.
		*/
		virtual uint32 RemoveTask(IIdleTask *taskToRemove) = 0;

		/**
			Run the idle tasks. Iterates through the list of 
			idle tasks, calling Run() on each one.
			@param EventsPendingFunction is a function that returns the name of a pending event or nil if none
			@return the delay in milliseconds before RunOverdueTasks should be called again
		*/
		virtual uint32 RunOverdueTasks( const char* (*EventsPendingFunction)()) = 0;
		/**
			Run the idle tasks. Iterates through the list of 
			idle tasks, calling Run() on each one.
			@param EventsPendingFunction is a function that returns the name of a pending event or nil if none
			@return the delay in milliseconds before RunAllTasks should be called again
		*/
		uint32 RunAllTasks( const char* (*EventsPendingFunction)()){ return RunOverdueTasks(EventsPendingFunction);} //name change until clients updated

		/**
			Remove all idle tasks, in preparation for shutdown
		*/
		virtual void Shutdown() = 0;

		/**
			Query the current task for a particular interface
			@param iid is the interface to query on the current task
		*/
		virtual IPMUnknown* QueryRunningTask( PMIID iid ) = 0;
};

#endif // __IIdleTaskMgr__
