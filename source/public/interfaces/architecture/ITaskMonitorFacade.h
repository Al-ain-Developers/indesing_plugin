//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ITaskMonitorFacade.h $
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
//  ADOBE CONFIDENTIAL
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
#ifndef __ID_TASK_MONITOR_FACADE__
#define __ID_TASK_MONITOR_FACADE__

#include <vector>
#include "AppFrameworkID.h"
#include "IDictionaryData.h"
#include "TaskInfo.h"

/** 
Interface used to manage background tasks and access their status.
@see TaskInfo
*/ 

namespace Facade
{

	/** This class provides a public facade for getting information about active tasks. This facade
	should closely mirror the task management functions available from scripting.
	*/
	class ITaskMonitorFacade : public IPMUnknown 
	{
	public:
		enum { kDefaultIID = IID_ITASKMONITORFACADE }; 

		typedef std::vector<TaskInfo> TaskInfoArray;
		typedef adobe::name_t TaskPropertyKey;
		typedef adobe::any_regular_t TaskPropertyValue;
		typedef std::pair< const TaskPropertyKey , const TaskPropertyValue > TaskProperty;
		typedef adobe::dictionary_t TaskProperties;

		/** Retrieves the list of the current tasks. Note that the current list of tasks is subject
		to change, but once a task is represented in a TaskInfoArray its TaskInfo will remain
		accessible even if the task completes or is canceled.
		@return TaskInfoArray containing registered tasks at call-time.
		*/
		virtual TaskInfoArray GetCurrentTasks() const = 0;

		/** Gets the TaskInfo for a TaskID
		@return	the TaskInfo or an invalid TaskInfo if no registered task has a matching id
		*/
		virtual TaskInfo GetTaskInfo(TaskInfo::TaskID taskID) const = 0;

		/** Signals all registered tasks to cancel. The tasks may not notice this signal right away,
		so code that depends on all tasks being canceled should call WaitForAllTasks after this call
		returns.
		*/
		virtual void CancelAllTasks() = 0;

		/** Waits for all registered tasks to complete.
		@return TaskInfoArray containing a TaskInfo for each active task at call time.
		*/
		virtual TaskInfoArray WaitForAllTasks() = 0;

		/** Returns the array of active background tasks that contain propertyValue for the key propertyKey
		@return TaskInfoArray containing a TaskInfo for each task with propertyKey, propertyValue pair
		*/
		virtual TaskInfoArray FilterTasks(const TaskPropertyKey& propertyKey , const TaskPropertyValue& propertyValue) const = 0;

		/** Returns the array of active background tasks that satisfy all of the entries in properties
		@return TaskInfoArray containing a TaskInfo for each task that matched all entries in properties
		*/
		virtual TaskInfoArray FilterTasks(const TaskProperties& properties) const = 0;
	};
} /* namespace Facade */

#endif // __ID_TASK_MONITOR_FACADE__
