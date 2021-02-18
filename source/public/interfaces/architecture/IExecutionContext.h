//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IExecutionContext.h $
//  
//  Owner: Florin Trofin 
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
//  Purpose: Provides access to the current thread's execution context.
//  
//  THIS IS NOT A STANDARD BOSS INTERFACE
//  
//========================================================================================

#pragma once
#ifndef __IEXECUTIONCONTEXT__
#define __IEXECUTIONCONTEXT__

#include "IPMUnknown.h" // for the definition of INHERITFROM

class ISession;
class IErrorState;
class IObjectModel;
class IDTask;

/** The execution context wraps together necessary components for the execution of threads.
	All threads in a thread domain share the same execution context (they are not preemptive against each other so they can share an EC).
	
	An IExecutionContext ptr is NOT a reference to a standard boss object. It is a virtual C++ class, but
	does not inherit from IPMUnknown. IExecutionContext member function GetSession() replaces gSession global object.
	This was necessary because of the added support for multi-threading.
*/
class IExecutionContext	INHERITFROM
{
public:
	/** Destructor of the execution context.
	*/
	virtual ~IExecutionContext() {};

	/** Returns a non addref-ed pointer to the ISession instance for the current thread.
	*/
	virtual ISession* GetSession() const = 0;

	/** Retrieves the current error state for the calling thread.
		Each thread keeps its own "global" error code (it is a thread specific variable).
	*/
	virtual IErrorState* GetErrorState() const = 0;

	/** Returns a non addref-ed pointer to the IObjectModel instance for the current thread.
	*/
	virtual IObjectModel* GetObjectModel() const = 0;

	/** Returns the task information for the current task that uses this execution context.
		The pointer is valid only in the current execution context and should not be stored.
	*/
	virtual IDTask* GetCurrentTask() const = 0;

}; // IExecutionContext

/** Main access point to retrieve the current execution context.
*/
PUBLIC_DECL IExecutionContext* GetExecutionContext();


#endif // __IEXECUTIONCONTEXT__
