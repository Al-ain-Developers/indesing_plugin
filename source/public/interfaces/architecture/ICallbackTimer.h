//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICallbackTimer.h $
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
#ifndef __ICallbackTimer__
#define __ICallbackTimer__

#include "IPMUnknown.h"
#include "IIdleTask.h"
#include "ShuksanID.h"

// Danger! Danger! Danger! Danger! Danger! Danger! 
// The callback function is an unreferenced pointer. So the plug-in that supplies it
// MUST NOT be unloaded while the function pointer is in the timer.

typedef uint32 (*TimerCallback)(void *refPtr);

class ICallbackTimer : public IIdleTask
{
	public:
	
		// register a one time only callback in msecs milliseconds
		virtual void StartTimer(TimerCallback callback, uint32 msecs, void *refPtr = nil) = 0;
		virtual void StopTimer() = 0;
};


#endif // __ICallbackTimer__
