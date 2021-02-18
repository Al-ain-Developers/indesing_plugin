//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IIdleTask.h $
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
//  Idle task mgr (alternative to real threads)
//  
//  Purpose:
//  An IIdleTask is an element of the IIdleTaskMgr's priority queue of tasks
//  that have an opportunity to run each pass through the main event loop.
//  
//  Review Date:
//  
//========================================================================================

#pragma once
#ifndef __IIdleTask__
#define __IIdleTask__

#include "IPMUnknown.h"
#include "ShuksanID.h"

/*
	#include "HelperInterface.h"
	#include "IIdleTask.h"
	#include "ShuksanID.h"
	#include "IIdleTaskMgr.h"
	#include "ISession.h"

	class MyIdleTask : public IIdleTask
	{
		public:
			MyIdleTask(IPMUnknown *boss);
			~MyIdleTask();
			uint32 RunTask( uint32 schedulerFlags, uint32 (*timeCheck)());
			void InstallTask(uint32 millisecsBeforeFirstRun);
			void UninstallTask();
			const char* TaskName();
		private:
			bool InappropriateState(uint32 flags);
			//...

		DECLARE_HELPER_METHODS()
	};

	DEFINE_HELPER_METHODS(MyIdleTask)
	CREATE_PMINTERFACE(MyIdleTask, kMyIdleTaskImpl)

	MyIdleTask::MyIdleTask(IPMUnknown *boss) : HELPER_METHODS_INIT(boss)
	{
	}

	const char* MyIdleTask::TaskName()
	{
		return "MyIdleTask: used to do cool things";
	}

	void MyIdleTask::InstallTask(uint32 millisecsBeforeFirstRun)
	{
		//perhaps other chores
		InterfacePtr<IIdleTaskMgr> idleTaskMgr(GetExecutionContextSession(), UseDefaultIID());
		if(idleTaskMgr) idleTaskMgr->AddTask(this, millisecsBeforeFirstRun);
	}


//one time task
	uint32 RunTask( uint32 schedulerFlags, uint32 (*timeCheck)())
	{
		if( InappropriateState(schedulerFlags))
			return kOnFlagChange;
		DoOneTimeThing();
		//Clean up as UninstallTask won't be called
		return kEndOfTime;
	}

//periodic task
//Note this is not drift free.  You would have to
//keep track of the time yourself and adjust the
//return value downward to make up for the fact
//that RunTask calls are always overdue.
	uint32 RunTask( uint32 schedulerFlags, uint32 (*timeCheck)())
	{
		if( InappropriateState(schedulerFlags))
			return kOnFlagChange;
		DoPeriodicThing();
		return 1000; //Call me again in 1 second.
	}

//lengthy interruptable one time task: Substitute a sleep
//value for kEndOfTime for a lengthy interruptable periodic task
	uint32 RunTask( uint32 schedulerFlags, uint32 (*timeCheck)())
	{
		if( InappropriateState(schedulerFlags))
			return kOnFlagChange;

		do{
			DoSomething( fThingsLeftToDo);
		}while( --fThingsLeftToDo && timeCheck() > 0);
		
		return fThingsLeftToDo ? 0 : kEndOfTime;
	}

//adjustable period, periodic task
	uint32 RunTask( uint32 schedulerFlags, uint32 (*timeCheck)())
	{
		if( InappropriateState(schedulerFlags))
			return kOnFlagChange;
		DoPeriodicThing();
		return schedulerFlags & kBackground ? 5000 : 1000;
	}



	void MyIdleTask::UninstallTask()
	{
		//perhaps other chores
		InterfacePtr<IIdleTaskMgr> idleTaskMgr(GetExecutionContextSession(), UseDefaultIID());
		if(idleTaskMgr) idleTaskMgr->RemoveTask(this);
	}
	
*/

/*	@ashishja
	This enumerator is used in order to check whether idle task needs to be stopped 
	due to a specific reason. More values can be added here as per the need evolves.
	All these types may not be supported for IdleTimer derived impls. So the derived impls
	need to handle the unsupported types as per their requirement gracefully .
*/
enum IdleTimerCompletionType
{
	kTimeout,		/* checks whether only timout has occured */
	kEventPending,	/* checks whether some event is pending */
	kDefault		/* checks for all possible reasons to stop the idle task */
};

/** Used as a callback for long tasks so that they 
	can pause and return control if they need to.
*/
class IdleTimer{
	public:
	/** Method to be called which will determine if the idle task needs to stop.
		@param  completionType (optional parameter) - checks whether the idle task
				needs to stop because of a specific reason type 
				(check IdleTimerCompletionType above for various types.)
				In case this optional parameter passed is not supported , it will 
				fallback to Default value and implementation.
				Default value checks for all possible reasons to stop the idle task.
		@return - The amound of time left (0 means the itdle task should stop)
	*/
	virtual uint32 operator()(IdleTimerCompletionType completionType = IdleTimerCompletionType::kDefault) = 0;

	/** String indicating why the task is out of time. */
	virtual void LogString( const char*) = 0;
};

/** An IIdleTask is an element of the IIdleTaskMgr's priority queue of tasks
	that have an opportunity to run each pass through the main event loop.
*/
class IIdleTask : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IIDLETASK };

		enum { 
				/** Task should be removed imediately from the IdleTaskMgr */
				kEndOfTime = ~(uint32)0, 
				/** Don't call again until the app state has changed */
				kOnFlagChange = ~(uint32)1, 
				/** Yield for at least one cycle of the event loop which allows the cmd queue to be flushed */
				kNextEventCycle = ~(uint32)2};

		/** Will perform its task and then relinquish control until it is called again.
			See CIdleTaskThread.h if this API is inconvenient for the task at hand.
			@param appFlags - Informs this method of the current state of the app see 
			IIdleTaskMgr::ApplicationStateFlags
			@param timeCheck - A callback method that should be called periodically 
			during long tasks to see whether RunTask has run out of time and needs to return.
			@return - The number of milliseconds to sleep before running again.

			  o  Returning kEndOfTime means that this task will be removed
			     from the IdleTaskMgr--without calling its UninstallTask method.
			     Hence, you should do whatever other chores you do in UninstallTask 
			     before returning this value.

			  o  If this task's UninstallTask method is called before RunTask
			     returns, then the return value for RunTask will be ignored.

			  o  Returning kOnFlagChange suspends this task until appFlags
			     changes.  At which point it will be called again ASAP.  RunTask
			     can continue to return kOnFlagChange as long as it doesn't like
			     the current appFlags.
			@see IdleTaskMgr
			@see CIdleTaskThread
			@see IIdleTaskMgr::ApplicationStateFlags
		*/
		virtual uint32 RunTask( uint32 appFlags, IdleTimer* timeCheck) = 0;
		//virtual uint32 RunTask( uint32 appFlags, uint32 (*timeCheck)()) = 0;
		
		/**
			InstallTask would be called by whatever code wants to get this
			task started.  Such code may look like this:
			
				InterfacePtr<IIdleTask> myTask(...);
				myTask->InstallTask(100);
			
			You should call the IdleTaskMgr's AddTask method in addition to
			other startup chores for this task.
			@param millisecsBeforeFirstRun - The number of milliseconds to wait before running this task the first time.
			@see IdleTaskMgr
		*/
		virtual void InstallTask(uint32 millisecsBeforeFirstRun) = 0;

		/**
			Uninstall would be called by companion code to that which installs
			the task.  Such code may look like this:
			
				InterfacePtr<IIdleTask> myTask(...);
				myTask->UninstallTask();
			
			You should call the IdleTaskMgr's RemoveTask method in addition to
			other cleanup chores for this task.  Note that the IdleTaskMgr does
			NOT call UninstallTask when you return kEndOfTime from your RunTask
			method--it simply internally removes the task from its queues.
			However IdleTaskMgr DOES call UninstallTask for any tasks
			that were not yet removed when its Shutdown method is called.  In
			this situation your UninstallTask must call IIdleTaskMgr::RemoveTask()
			directly or indirectly or you will hit an assert.
			
			@see IdleTaskMgr
		*/
		// Should UninstallTask return RemoveTask's return value?
		virtual void UninstallTask() = 0;

		enum { kMaxTaskNameLength = 1023}; //1024 if you include the trailing '\0'
		
		/**
			A task's name is simply a C string that is used internally by
			the IdleTaskMgr.  It is used for debugging and logging purposes
			and need not be unique among tasks although this would certainly
			be more helpful.  
			NOTE: Eventually this will probably be a parameter passed to IdleTaskMgr::AddTask.
			@return - The string returned is immediately copied.
			@see IdleTaskMgr
		*/
		virtual const char* TaskName() = 0;
};


#endif // __IIdleTask__
