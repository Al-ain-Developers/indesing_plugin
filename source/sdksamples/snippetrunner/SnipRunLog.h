//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunLog.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef _SnipRunLog_
#define _SnipRunLog_

// Interface includes:

// Forward declarations:
class PMString;
class ITextControlData;
class ICounterControlData;
class IPMStream;

/**
	Log that records messages in a multi line text widget on a panel.

	This is a singleton instance. The lifetime extends from the first use of the log, until the SnipRunManager instance is destroyed.
	This allows the log to be used when snippets are executed through alternative mechansisms (scripting or quick apply) when the snippet
	runner panel might be hidden.
	@ingroup snippetrunner
	
*/
class SnipRunLog
{
	friend class SnipRunPanelWidgetObserver;
protected:
	/**
		Constructor is protected because this is a singleton class.
		@param logPanelWidgetID IN of panel containing the text widget that will display log.
		@param logWidgetID IN of text widget that will display messages.
		@param scrollBarWidgetID IN of log scroll bar.
	*/
	SnipRunLog(const WidgetID& logPanelWidgetID, const WidgetID& logWidgetID, const WidgetID& scrollBarWidgetID);

public:
	/**
		Returns the global instance of this singleton class.
		@return the global instance of this singleton class.
	*/
	static SnipRunLog* Instance();

	/**
		Destroys the single global instance of this singleton class. If there is no instance in existance, just returns.
	*/
	static void DeleteInstance();

	/** Destructor
	*/
	virtual ~SnipRunLog();

	/**
		Records the given message on a new line in the log, call like this SnipRunLog::Instance()->Log("Hiya"),
		@param message to be logged.
	*/
	void Log(const PMString& message);

	/**
		Clears the log of messages.
	*/
	void Clear();

	/**
		UpdateTextControl that displays the log.
	*/
	void UpdateTextControl();

	/**
		SaveLog
		@param stream IN log data to be saved into.
	*/
	void SaveLog(InterfacePtr<IPMStream> stream);

	/**
		GetTrace
	*/
	bool16 GetTrace() const {return fTrace;}

	
	/** Controls whether log messages are echoed to TRACE.
		@param traceState kTrue to enable echo of log calls to TRACE
	*/
	void SetTrace(bool16 traceState) {fTrace = traceState;}
	
	/** Let's client code see if the log has been instantiaed.
		Used to workaround a problem that happens when the log UI
		(a panel) gets resized (see SnipRunControlView::Resize).
		@return pointer to the log object if instantiated, nil otherwise.
	*/
	static SnipRunLog* PeekAtSnipRunLog() {return fSnipRunLog;}

	/** The user is resizing the log panel that displays the log. 
		The content of the log is saved for later restoration and
		then the log is cleared for the duration of the resize.
		Resize runs much faster if there is no data in the 
		multi line text widget. This method schedules a command
		kSnipRunRestoreLogCmdBoss that will get processed 
		when the user finishes dragging the resize handle and
		the command calls SnipRunLog::ResizeComplete.
	 */
	void Resize();

	/** Restores the saved contents of the log into the multi-line
		text widget.
	 */
	void ResizeComplete();

private:
	void ScrollToTop();
	void ScrollToBottom();
	// return false if the view cannot be initialised (say the panel is hidden)
	bool16 InitPanelView();
	void DetachPanelView();
	static SnipRunLog* fSnipRunLog;
	InterfacePtr<ITextControlData> fLogTextControlData;
	InterfacePtr<ICounterControlData> fScrollBarCounterData;
	PMString fLog;
	bool16 fTrace;
	WidgetID fLogWidgetID;
	WidgetID fLogPanelWidgetID;
	WidgetID fScrollBarWidgetID;

	bool16 fPanelInit;
	bool16 fResizeInProgress;
	PMString fSavedLog;
};

/**
	Records printf style formatted string with variable argument list to the log.
*/
extern void SNIPLOG(const char* str, ...);

/**
	Records printf style formatted string with variable argument list to the log
	and throws an ASSERT_FAIL message.
*/
extern void SNIPLOG_ASSERT_FAIL(const char* str, ...);

#endif // _SnipRunLog_


