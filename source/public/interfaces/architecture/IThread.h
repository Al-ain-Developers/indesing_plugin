//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IThread.h $
//  
//  Owner: ???
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

#error IThread is no longer supported and will soon be remmoved

#pragma once
#ifndef __ITHREAD__
#define __ITHREAD__

#include "IPMUnknown.h"
#include "ShuksanID.h"

#ifdef MACINTOSH
#include <Threads.h>
#endif

#ifdef Yield
#undef Yield
#endif

class IThread : public IPMUnknown
{
	public:
			// The main entry point for a thread.  A thread is automatically terminated
			// when Run is exited.
		virtual void *Run() = 0;
			
			// Suspend execution of this thread.  By default threads are created in a
			// suspended state.
		virtual void Suspend() = 0;
			 
			// Resume executing a suspended thread.  Newly create threads must be resumed
			// before they begin execution.
		virtual void Resume() = 0;
			
			// Sleep for the specified number of milliseconds
		virtual void Sleep(uint32 milliseconds) = 0;
			
			// Yield execution time to any other thread determined by the thread scheduler
		virtual void Yield() = 0;
			
			// True if the thread has completed running.
		virtual bool16 Completed() = 0;
			
			// Terminate this thread's execution.
		virtual void Terminate() = 0;

			// A thread can specify when it is run based on whether the application is currently
			// in the foreground or backround. An application is considered to be in the backround
			// if modal dialogs are up.
		typedef enum SchedulerFlags { 
			kRunForeground = 1,
			kRunBackround = 2,
			kRunWhileDialogUp = 4,
			kRunWhileTracking = 8,
			kModifiesModel = 16,
			kModifiesDocument = 32,
			kRunAlways = 15,												// kRunForeground | kRunBackround | kRunWhileDialogUp | kRunWhileTracking
			kRunDefault = kRunForeground						// kRunForeground | kRunBackround | kRunWhileDialogUp | kRunWhileTracking
			} SchedulerFlags;
		virtual uint32 GetSchedulerFlags() = 0;

			// A thread can specify how often it should be run.
		typedef enum Priority { 
			kFirstPriority = 0,
			kVeryFrequent = 0,			
			kFrequent = 1,
			kLessFrequent = 2,
			kSeldom = 3,
			kLastPriority = 3
			} Priority;

		virtual Priority GetPriority() = 0;
};
	/*
const uint32 kRunAlways = kRunForeground | kRunBackround | kRunWhileDialogUp | kRunWhileTracking;
const uint32 kRunDefault = kRunForeground; */

#endif