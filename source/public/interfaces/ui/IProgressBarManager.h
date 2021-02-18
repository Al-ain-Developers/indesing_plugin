//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IProgressBarManager.h $
//  
//  Owner: Matt Joss
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
#ifndef __IProgressBarManager__
#define __IProgressBarManager__

class PMString;
class IProgressBarControlData;

#include "ShuksanID.h"

enum ProgressBarStyle { eFixedRange = 0, eBarberPole, eDocWindow };
#define kProgressTraceID "ProgressBarTrace"

/**
	This interface is used to manage progress bars.  Although it can be used directly, most client code uses 
	the helper classes RangeProgressBar and TaskProgressBar found in ProgressBar.h
*/
class IProgressBarManager : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPROGRESSBARMANAGER };
		/** Progress bar type */
		enum ProgressType
		{
			kTaskProgress               = 0x01,
			kRangeProgress              = 0x02,
			kFoldupProgress             = 0x04
		};

		/**
			Registers a new task set.  Multiple task sets can be registered at a time.  
			Standard behavior is for second task set to subdivide first task set.
			@param	nType specifies the type of progress bar, kTaskProgress, kRangeProgress or kFoldupProgress
			@param	progressDialogTitle title of the progress bar dialog
			@param	taskStart start value of the task
			@param	taskEnd end value of the task
			@param	showImmediate kTrue to show progress bar immediately, kFalse to put it up after a short delay if the task is not finished
			@param	showCancel kTrue to show cancel button and allow task to be cancelled, kFalse to disallow cancel
			@param	customProgress If you don't want to use the standard progress bar, you can provide your own progress bar widget that contains an IProgressBarControlData interface
			@param	useTwoBars kTrue to use 2 bars when multiple tasks are registered.  kFalse to limit to 1 bar.
			@return	int32 task set identifier
		*/
		virtual int32      RegisterTaskSet(int32                    nType,
			                                const PMString&          progressDialogTitle, 
											int32                    taskStart, 
											int32                    taskEnd, 
											bool8                    showImmediate = kFalse,
											bool8                    showCancel = kTrue, 
											IProgressBarControlData* customProgress = nil, 
											bool32                   useTwoBars = kFalse) = 0;
		/**
			Unregisters the specified task set, or the current task set.
			@param	nBarID if specified, identifies the task set to unregister.  If not specified, current task set is unregistered
		*/
		virtual void		UnregisterTaskSet(int32 nBarID = -1) = 0;

		/**
			Call this before processing a task.  This is usually used to move the progress bar one task at a time, 
			however, you can move more by passing in a value to advanceNtasks. 
			@param	displayText Text for the current task to be displayed in ProgressBar
			@param	advanceNtasks number of tasks to advance.  Default is to advance 1 task
			@param	nBarID identifier of a particular task set
		*/
		virtual void		DoTask(const PMString& displayText, int32 advanceNtasks = 1, int32 nBarID = -1) = 0;

		/**
			Sets the absolute position of the progress bar, as opposed to DoTask, which moves the progress 
			bar forward the specified amount.  Position must be within range specified in the RegisterTaskSet.
			@param	newPosition new value for progress bar
			@param	fParent sets value of previously registered task set instead of the current task set, ignored if nBarID != -1
			@param	nBarID identifier of a particular task set
		*/
		virtual void		SetPosition( int32 newPosition, bool16 fParent = kFalse, int32 nBarID = -1 ) = 0;
		/**
			Gets the absolute position of the progress bar.
			@param	fParent gets value of previously registered task set instead of the current task set, ignored if nBarID != -1
			@param	nBarID identifier of a particular task set
			@return	int32 returns current position for progress bar requested
		*/
		virtual int32       GetPosition( bool16 fParent = kFalse, int32 nBarID = -1 ) = 0;

		/**
			Sets the task text of the progress bar.  
			@param	newText text for task
			@param	forceRedraw kTrue to forceRedraw of text
			@param	nBarID identifier of a particular task set
		*/
		virtual void		SetTaskText( const PMString& newText, bool16 forceRedraw = kTrue, int32 nBarID = -1) = 0;
		
		/**
			Check this to see if the user cancelled the action.
			@param	setGlobalErrorState if kTrue, sets the global error state to kCancel if progress was cancelled
			@return	bool16 kTrue if progress bar was cancelled
		*/
		virtual bool16		WasCancelled(bool8 setGlobalErrorState = kTrue) = 0;

		/**
			Call this anytime during the tasks to immediately terminate the entire progress bar process.  
			Usually called when an  error condition is encountered during one of the sub tasks.  
		*/
		virtual void		Abort() = 0;

		/**
			Returns the number of currently registered task sets
		*/
		virtual int32		GetNumTaskSets() = 0;
		/**
			Get Info about a task set
			@param	taskSetIndex index of the task set in question
			@param	outTaskStart on return, this is filled with the start value for the task set
			@param	outTaskEnd on return, this is filled with the end value for the task set
			@param	outCurrentTask on return, this is filled with the current value for the task set
			@param	outCurrentSubTaskName on return, this is filled with the subtask name for the task set
		*/
		virtual	void		GetTaskSetInfo(int32 taskSetIndex, int32* outTaskStart, int32* outTaskEnd = nil, int32* outCurrentTask = nil, PMString* outCurrentSubTaskName = nil) = 0;
	
		/**
			This is called by the Cancel button and should not be called by users.  Use Abort() instead.		
		*/
		virtual void		Cancel() = 0;

		/**
			Disabling child progress bars will keep any subsequent progress bars from registering, so 
			they cannot subdivide your tasks and they cannot be cancelled.
			@param	disable kTrue to disable child progress bars, kFalse to enable child progress bars
		*/
		virtual void		DisableChildProgressBars(bool16	disable) = 0;

		/**
			Call this to suppress the display of the progress bar.  
			@param	suppressDisplay kTrue to suppress display of progress bar, kFalse to enable display of progress bar
			@return	bool16 kFalse if a progress bar already is shown, since it will not suppress display if the progress bar is already displayed
		*/
		virtual bool16		SuppressProgressBarDisplay(bool16	suppressDisplay) = 0;

		/**
			Call this to see if the progress bar display is currently being suppressed.
		*/
		virtual bool16		IsDisplaySuppressed() = 0;

		/**
			This is basically asking "If I register, will it be successful?"  Register will fail if child progress bars
			are disabled via DisableChildProgressBars(), of if the progress bar is suppressed.
		*/
		virtual bool16		IsRegisterDisabled() = 0;

		/**
			Sets the "status" text line.
			@param	statusText 
			@param	forceRedraw kTrue to force redraw of the status text
			@param	nBarID identifier of a particular task set
		*/
		virtual void        SetTaskStatus(const PMString& statusText, bool16 forceRedraw = kTrue, int32 nBarID = -1) = 0;

		/**
			Sets the task title.
			@param	strTitle 
			@param	forceRedraw kTrue to force redraw of the task title
			@param	nBarID identifier of a particular task set
		*/
		virtual void        SetTaskTitle(const PMString& strTitle, bool16 forceRedraw, int32 nBarID = -1) = 0;

		/** For internal use only */

		virtual bool SkipCheckingForCancel(bool skip) = 0;
};

#endif
