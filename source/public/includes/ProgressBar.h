//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ProgressBar.h $
//  
//  Owner: Dave Burnard (was Matt Joss)
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
#ifndef __ProgressBar__
#define __ProgressBar__

#include "IProgressBarManager.h"
#include "IProgressBarControlData.h"

class PMString;				// foward decl
class IDrawMgr;
class IDocWindowProgressBar;


#pragma export on

/** Abstract baseclass for stack based Progress bar objects.
*/
class PUBLIC_DECL CProgressBar
{
public:
	CProgressBar();
	virtual ~CProgressBar() {}

	/** Check this to see if the user cancelled the action. */
	virtual bool16	WasCancelled(bool8 setGlobalErrorState = kTrue) = 0;

	/** Call this anytime during the tasks to immediately terminate
			the entire progress bar process.  Usually called when an 
			error condition is encountered during one of the sub tasks. 
	*/
	virtual void	Abort() = 0;

	/** Call this passing kTrue to keep any subsequent progress bars from subdividing your progress bar. */
	virtual void	DisableChildProgressBars(bool16 disable) = 0;

	/** Was the registration of this progress bar was successful. Not usually necessary to call this. 
			Reasons for failure include another progress bar calling DisableChildProgressBars().
	*/
	virtual bool16	WasRegisterSuccessful() = 0;

	/** Call this to set the position of the progressbar to a location within the specified range. */
	virtual void	SetPosition(int32 newPosition);

private:
	int32 nVTTest;
};

/** Concrete/generic progress bar - used as a starting point for various types of progress bars.
		Intended to be used as a stack based object, the lifetime of the progress bar corresponding to the scope of the object.
*/
class PUBLIC_DECL BaseProgressBar: public CProgressBar
{
protected:
	/**	Constructor
	
		@param nType IN the progress bar type
		@param progressDialogTitle IN dialog title
		@param taskStart IN value corresponding to the start of the bar
		@param taskEnd IN value corresponding to the end of the bar
		@param showImmediate IN show the progress bar dialog immediately
		@param showCancel IN	make the cancel button visible
		@param customProgress IN custom progress bar control data
		@param useTwoBars IN one bar or two (for subtasks)
	*/
	BaseProgressBar( int32                             nType,
		             const PMString&                   progressDialogTitle, 
		             int32                             taskStart, 
					 int32                             taskEnd, 
					 bool8                             showImmediate,
					 bool8                             showCancel, 
					 IProgressBarControlData*          customProgress, 
					 bool32                            useTwoBars);

public:
	virtual ~BaseProgressBar();

	/** Check this to see if the user cancelled the action. */
	bool16	WasCancelled(bool8 setGlobalErrorState = kTrue);

	/** Call this anytime during the tasks to immediately terminate
			the entire progress bar process.  Usually called when an 
			error condition is encountered during one of the sub tasks. 
	*/
	void	Abort();

	/** Call this passing kTrue to keep any subsequent progress bars from subdividing your progress bar. */
	void	DisableChildProgressBars(bool16 disable);

	/** Was the registration of this progress bar was successful. Not usually necessary to call this. 
			Reasons for failure include another progress bar calling DisableChildProgressBars().
	*/
	bool16	WasRegisterSuccessful();

	/** Call this to set the position of the progressbar to a location within the specified range. */
	void	SetPosition(int32 newPosition);

protected:
	IProgressBarManager*	fProgressMgr;
	int32                   fnBarID;
};

/** Progress bar within a document window.
		Intended to be used as a stack based object, the lifetime of the progress bar corresponding to the scope of the object.
*/
class PUBLIC_DECL DocWindowProgressBar: public CProgressBar
{
public:
	/**	Constructor
	
		@param taskStart IN value corresponding to the start of the bar
		@param taskEnd IN value corresponding to the end of the bar
		@param strText IN text label
		@param pMgr IN draw manager to use
		@param bAllowCancel IN	allow the operation to be cancelled
		@param bShowImmediate IN show the progress bar dialog immediately
	*/
	DocWindowProgressBar( int32 nStart, int32 nEnd, const PMString& strText, IDrawMgr* pMgr, bool32 bAllowCancel = kTrue, bool32 bShowImmediate = kFalse);
	~DocWindowProgressBar();

	/** Check this to see if the user cancelled the action. */
	virtual bool16	WasCancelled(bool8 setGlobalErrorState = kTrue);

	/** Call this anytime during the tasks to immediately terminate
			the entire progress bar process.  Usually called when an 
			error condition is encountered during one of the sub tasks. 
	*/
	virtual void	Abort();

	/** Call this passing kTrue to keep any subsequent progress bars from subdividing your progress bar. */
	virtual void	DisableChildProgressBars(bool16 disable);

	/** Was the registration of this progress bar was successful. Not usually necessary to call this. 
			Reasons for failure include another progress bar calling DisableChildProgressBars().
	*/
	virtual bool16	WasRegisterSuccessful();

	/** Call this to set the position of the progressbar to a location within the specified range. */
	virtual void	SetPosition(int32 newPosition);

private:
	IDocWindowProgressBar*	fProgressBarImpl;
};

/** Task Progress bar (one that manages a series of smaller tasks).
		Intended to be used as a stack based object, the lifetime of the progress bar corresponding to the scope of the object.
*/
class PUBLIC_DECL TaskProgressBar: public BaseProgressBar
{
public:
	/**	Constructor
	
		@param title IN dialog title
		@param numTasks IN number of tasks managed by this progress bar
		@param showImmediate IN show the progress bar dialog immediately
		@param showCancel IN	make the cancel button visible
		@param customProgress IN custom progress bar control data
		@param useTwoBars IN one bar or two (for subtasks)
	*/
	TaskProgressBar(const PMString& title, int32 numTasks, bool8 showImmediate = kFalse, 
				bool8 showCancel = kTrue, IProgressBarControlData* customProgress = nil, bool32 useTwoBars = kFalse);
	virtual ~TaskProgressBar();

	/** Call this before processing a task.  Calling this will move the progress bar for any previously called tasks */
	void	DoTask(const PMString& displayText = "", int32 advanceNtasks = 1);

	/** set line of status text */
	void SetTaskStatus(const PMString& displayText = "");
};

/** Range Progress bar.
		Intended to be used as a stack based object, the lifetime of the progress bar corresponding to the scope of the object.
*/
class PUBLIC_DECL RangeProgressBar: public BaseProgressBar
{
public:
	/**	Constructor
	
		@param title IN dialog title
		@param startRange IN value corresponding to the start of the bar
		@param endRange IN value corresponding to the end of the bar
		@param showImmediate IN show the progress bar dialog immediately
		@param showCancel IN	make the cancel button visible
		@param customProgress IN custom progress bar control data
		@param useTwoBars IN one bar or two (for subtasks)
	*/
	RangeProgressBar(const PMString& title, int32 startRange, int32 endRange, bool8 showImmediate = kFalse, 
				bool8 showCancel = kTrue, IProgressBarControlData* customProgress = nil, bool32 useTwoBars = kFalse);
	virtual ~RangeProgressBar();
	
	/** Set the task text for the current task. */
	void	SetTaskText(const PMString& text, bool16 forceRedraw = kTrue);
};

/** Sub task progress bar.
		This progress bar variant is only useful if you have already declared on of the other progress bars above
		you on the stack.  
		
		It doesn't display anything by itself.  Instead, it:
		
			1. Causes the next progress bar up to move through its current task smoothly as this progress bar goes to completion

			2. Usually cause its text to be appended to the text that is currently displayed in the next progress bar up

			3. Moves the next progress bar up one step forward when it reaches completion.

		Intended to be used as a stack based object, the lifetime of the progress bar corresponding to the scope of the object.
*/
class PUBLIC_DECL SubTaskFoldupProgressBar: public BaseProgressBar
{
public:
	/**	Constructor
	
		@param title IN dialog title
		@param startRange IN value corresponding to the start of the bar
		@param endRange IN value corresponding to the end of the bar
	*/
	SubTaskFoldupProgressBar(const PMString&       strText,
		                     int32                 startRange, 
						     int32                 endRange);
	virtual ~SubTaskFoldupProgressBar();

public:
	/** Set the task text for the current task. */
	void SetTaskText(const PMString& strText, bool16 forceRedraw = kTrue);
};

/** Stack based class to suppress subsequent progress bars.
		If you want to suppress the progress bar from showing, create this class on the stack.  All progress bars "below" you
		will not display.  If somebody "above" you has already created a progress bar, your suppression will be ignored.

		Intended to be used as a stack based object, the lifetime of the suppression corresponding to the scope of the object.
*/
class PUBLIC_DECL SuppressProgressBarDisplay
{
	public:
		/** Constructor */
		SuppressProgressBarDisplay(bool16	suppressDisplay = kTrue);
		virtual ~SuppressProgressBarDisplay();

		/** Have progress bars been suppressed? */
		static	bool16	IsSuppressed();
	
	protected:
		IProgressBarManager*	fProgressMgr;

};

#pragma export off

#endif
