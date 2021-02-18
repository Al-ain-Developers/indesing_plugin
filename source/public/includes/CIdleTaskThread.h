//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CIdleTaskThread.h $
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
#ifndef __IdleTaskThread__
#define __IdleTaskThread__

#include "IIdleTaskThread.h"
#include "HelperInterface.h"
#ifdef MACINTOSH
#	include <CoreServices/CoreServices.h>
#endif

// forward declares
class IExecutionContext;

#pragma export on

/**
	An implementation of IIdleTask that uses cooperative threads to 
	perform its task.  You would use this if your idle task might
	take a long time to execute and you want to be able to yield
	back to the event loop without "losing your place", (i.e., you
	keep track of how far along your task is by using the stack and the
	program counter).  You must override TaskName() and RunThread().
	You do your work in RunThread(), periodically calling YieldToEventLoop().
	At calls to YieldToEventLoop, if the IdleTaskMgr thinks you've had enough
	time because the user has generated an event or another IdleTask is ready to
	run, your RunThread() method will be suspended and scheduled to run again as
	soon as possible.  At that time, the call to YieldToEventLoop() will unblock
	exactly where it left off.  When you return from your RunThread() method,
	the thread will be destroyed and this IdleTask will be removed from the 
	IdleTaskMgr's queue.  Calling InstallTask() again will create a new
	thread and reinstall this IdleTask in the IdleTaskMgr's queue to be
	run as soon as possible.
	
	Note that this class provides no facility for checking to see if the
	user wants to interrupt this task or if the task should end early
	for some other reason.  You would have to do that by some other facility,
	perhaps by setting some state in response to a user event and checking
	that state the next time your thread wakes from the YieldToEventLoop()
	call.  Simply returning anyplace from RunThread will then cause the
	thread to be destroyed and the IdleTask to be removed from the IdleTaskMgr.

	<pre>
	include "CIdleTaskThread.h"
	
	class MyIdleTask : public CIdleTaskThread
	
	public:
	MyIdleTask(IPMUnknown * boss) : CIdleTaskThread(boss){}
	void RunThread();
	const char* TaskName();
	
	CREATE_PMINTERFACE(MyIdleTask, kMyIdleTaskImpl)
	
	void MyIdleTask::RunThread()
	
	uint32 flags;
	work,work,work
	flags = YieldToEventLoop(0);
	work,work,work
	flags = YieldToEventLoop(1000); //rest for 1 second
	work,work,work
	flags = YieldToEventLoop(0);
	if( flags & kMouseTracking)
	YieldToEventLoop(kOnFlagChange); //sleep til user stops tracking
	work,work,work

	if ( flags & kCITT_Shutdown )
		return;
	
	const char* MyIdleTask::TaskName()
	
	return "MyIdleTask";
	</pre>
*/

namespace idt_syncprimitives{
class CIdleTaskThreadSyncPrimitives;
}
class PUBLIC_DECL CIdleTaskThread : public IIdleTaskThread
{
public:
	/** */
	CIdleTaskThread(IPMUnknown *boss);
	/** */
	~CIdleTaskThread();

	/*
	YieldToEventLoop() will OR in this flag to the returned appflags when it
	needs the Thread to return from its RunThread() method. This can be useful
	for those Threads that normally never return and simply yield within an
	endless loop. When the Thread is forcibly Uninstalled() the CIdleTaskThread
	will call RunTask() one more time and expects the Thread to return.
	*/
	const static uint32 kCITT_Shutdown = 0x80000000;

	/** Do not override RunTask, override RunThread instead */
	virtual uint32 RunTask( uint32 schedulerFlags, IdleTimer* timeCheck);

	/** If you override InstallTask, you must call this version in your override */
	virtual void InstallTask(uint32 millisecsBeforeFirstRun);

	/** If you override UninstallTask, you must call this version in your override */
	virtual void UninstallTask();

	/** A friendly reminder that all IIdleTasks need a name */
	virtual const char* TaskName() = 0;

	/** Call YieldToEventLoop periodically in your RunThread method */
	uint32 YieldToEventLoop(uint32 millisecSleep = 0);

	/**
		Allows the overriding implementation to detect when the CIdleTaskThread
		is being shutown. This is needed because an implementation may be in
		the middle of a YieldToEventLoop() in one part of code and may not have
		a convenient method to return state to the RunThread().
		@return kTrue if the Thread is being shutdown, kFalse otherwise.
	*/
	virtual bool16 IsShuttingDown() const
		{ return ((fFlags & kCITT_Shutdown) != 0); }

	/** INTERNAL USE ONLY! Should be used only by the architecture team!
		Invokes the specified task in the main application thread.
		If the call is happening in another thread, this IdleTaskThread will switch to the main thread, execute the task and come right back.
		If the context is already the main thread, the task will simply be executed.
		It will NOT go through the event loop.
		This is useful when a component is really tied to the main execution thread (like UI) and it needs to be executed only in that context.
	*/
	void ExecuteTaskInMainThread(IIdleTaskThread::Task& task);

private:
	/**
		You must override RunThread but can't call it yourself--this is called by RunTask
		CodeWarrior doesn't seem to care that this is declared private and lets subclasses
		call it--DONT DO THIS!
	*/
	virtual void RunThread(uint32 flags) = 0;

	/**
		Override StackSize() if you need an unusual stack size. StackSize() 
		should return the stack size in bytes required by RunThread().
	*/
	virtual uint32 StackSize();

private:
#if MACINTOSH
	typedef ThreadID ThreadHandle;
	ThreadEntryUPP entryPoint;
#elif WINDOWS
	typedef LPVOID ThreadHandle;
#else
#	error CIdleTaskThread unimplemented
#endif
	static const ThreadHandle kInvalidThreadHandle;
	ThreadHandle fThisThread;
	K2Vector<ThreadHandle> fParentThread; //can I use stack<ThreadHandle, K2Vector<ThreadHandle> > here?

	uint32 fSleep; //when this becomes kEndOfTime thread is done
	uint32 fFlags; //set every time RunTask is called, i.e. every time YieldToEventLoop returns
	IdleTimer* fTimeCheck;
	//fState is for sanity checking--could make kFinished == kConstructed call it say kUninstalled
	//hmm is kInstalled the same as kYielding?  Not yet, see UninstallTask
	enum { kConstructed, kInstalled, kRunning, kYielding, kFinished, kDestroyed, kProcessingMainThreadTasks} fState;
	
	IIdleTaskThread::Task fMainThreadTask;
	
	void SwitchToChildThread();
	void SwitchToParentThread();

	static void private_FiberFunction( CIdleTaskThread* theTask);
#ifdef MACINTOSH
	static DEFINE_API(void *) FiberEntryPoint( void * cookie);
#else
	static VOID CALLBACK CIdleTaskThread::FiberEntryPoint( PVOID cookie);
#endif
	
    // For private use only.
    void FiberEntryPointNoReturn(void* cookie);
    
    idt_syncprimitives::CIdleTaskThreadSyncPrimitives* fSyncPrimitives;
	DECLARE_HELPER_METHODS()
};

#pragma export off

#endif // __IdleTaskThread__
