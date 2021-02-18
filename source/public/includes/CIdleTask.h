//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CIdleTask.h $
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
#ifndef __CIdleTask__
#define __CIdleTask__

#include "IIdleTask.h"
#include "HelperInterface.h"

#pragma export on

/**
	Base implementation of an idle task

	Don't return kEndOfTime from RunTask, instead you would call
	UninstallTask and return any value from RunTask as it will 
	be ignored.
*/
class PUBLIC_DECL CIdleTask : public IIdleTask
{
public:
	/** */
	CIdleTask(IPMUnknown *boss);
	/** */
	~CIdleTask();

	/**
		If you override InstallTask, call this version in your override.
		Otherwise, there is no reason to derive from this class.
	*/
	virtual void InstallTask(uint32 millisecsBeforeFirstRun);

	/**
		If you override UninstallTask, call this version in your override
		Otherwise, there is no reason to derive from this class
	*/
	virtual void UninstallTask();

	/** Get the task name */
	virtual const char* TaskName();

private:
	bool fCurrentlyInstalled;

	DECLARE_HELPER_METHODS()
};

#pragma export off

#endif // __CIdleTask__
