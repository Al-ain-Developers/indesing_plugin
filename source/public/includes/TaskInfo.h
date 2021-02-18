//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TaskInfo.h $
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
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __TASKINFO_H__
#define __TASKINFO_H__

#include <utility>
#include <boost/intrusive_ptr.hpp>
#include <boost/operators.hpp>
#include "AsyncWork.h"
#include "PMString.h"
#include <adobe/move.hpp>


struct AsyncWorkPacketJobSpec;

class IDTask;
class MemXferBytes;
// We need intrusive_ptr instead of shared_ptr because of size constraints (intrusive_ptr has the same size as T*)
typedef boost::intrusive_ptr<IDTask> IDTaskPtr;


//---------------------------------------------------------------------------------------
/** Encapsulates the necessary data so alerts from background tasks can be presented to
	the user.
*/
struct AlertMessage
{
	/** enumeration of the different types of alerts */
	enum AlertType { kGenericMsg,
					 kInformationMsg,
					 kWarningMsg, /**< an alert that needs the users attention */
					 kErrorMsg    /**< an alert representing a failure condition */
					};
	
	/** Default constructor */
	AlertMessage()
	: fAlertType(kGenericMsg)
	{
	}
	
	/** Construct an \c AlertMessage
		@param[in] type AlertType describing the kind of alert message
		@param[in] message A translated message 
	*/
	AlertMessage(AlertType type, PMString const& message)
	: fAlertType(type), fMessage(message)
	{
	}
	
	AlertType	fAlertType; /**< the type of alert */
	PMString	fMessage; /**< the localized message */
};

/** A vector of \c AlertMessage objects */ 
typedef std::vector<AlertMessage> AlertMessageQueue;

//---------------------------------------------------------------------------------------
class IErrorState;

/** Captures the information about the error state as data that can be moved between execution contexts.
 */
struct ErrorStateInfo
{
	/** Default constructor */
	ErrorStateInfo() : fCode(kSuccess), fErrorInfoClass(kInvalidClass)
	{}

	/** Capture the current error state 
		@param[in] errState the global error state to capture.
	*/
	explicit ErrorStateInfo(IErrorState* errState);
	/** Write a persistent Interface as part of the ErrorStateInfo
		@param[in] errorInfo an interface on a persistent boss
	*/
	void WriteErrorInfoToBuffer(IPMUnknown* errorInfo);

	/** Read a persistent Interface that was stored earlier
		@return an IPMUnknown* representing the stored boss
	*/
	IPMUnknown* ReadErrorInfoFromBuffer() const;
	
	ErrorCode	fCode;		/**< the ErrorCode */
	PMString	fString;    /**< the ErrorString */
	PMString	fContext;   /**< the Context */
	boost::shared_ptr<MemXferBytes> fErrorInfoBuffer; /**< raw storage for the stored interface */
	ClassID  fErrorInfoClass; /**< the ClassID of the error info */
};

//---------------------------------------------------------------------------------------

//========================================================================================

/** This class is used to track the progress of background tasks.
 Each top level task registers with the TaskMonitor which will hold a pointer to that task info.
 A client can obtain a TaskInfo from the TaskMonitor, store it and poll it for status and progress information.
 Not all tasks have progress information but all should have a name and should support cancellation. 
 */
class TaskProgressInfo
{
public:
	/** A simple range for position based progress tracking */
	typedef std::pair<uint32, uint32> ProgressRange;
	
	/** A struct that encapsulates the progress data
	*/
	struct ProgressData
	{
		ProgressData() : fRange(0, 0), fPercentage(0.0), fCurrentPosition(0)  
		{}
		
		PMString		fTaskStatusText; 	/**< Status text */
		ProgressRange	fRange;				/**< Range */
		PMReal			fPercentage;		/**< Percentage done */
		uint32			fCurrentPosition;	/**< Current position within range */
	};
	
	// Constructor
	TaskProgressInfo()
	{}
	
	/** Retrieves a snapshot of all progress data.
		 @param[out] data Current data. Only filled when the return value is true.
		 @return [false] if this task doesn't have a progress bar associated with it (its duration is indeterminate)
		 [true] if the task has progress information.
		 If the return value is [false] the \a data parameter is unchanged.
		 \note{ NOTE: a task may return false if called early on startup when the task did not initialize any progress bars
		 but return true later. }
	 */
	PUBLIC_DECL bool GetCurrentData(ProgressData& data) const;
	
	// Convenience accessors
	/** Get the status text
		@return a \c PMString containing the current status text.
	*/
	inline PMString GetTaskStatusText() const
	{
		ProgressData data;
		GetCurrentData(data);
		return data.fTaskStatusText;
	}

	/** Get the current range for progress information
		@return the current \c ProgressRange.
	*/
	inline ProgressRange GetRange() const
	{
		ProgressData data;
		GetCurrentData(data);
		return data.fRange;
	}
	
	/** Get the current position within the active range
		@return the current position.
	*/
	inline uint32 GetCurrentPosition() const
	{
		ProgressData data;
		GetCurrentData(data);
		return data.fCurrentPosition;
	}

	/** Get the current completion percentage.
		@return the completion percentage.
	*/
	inline PMReal GetTaskCompletionPercentage() const
	{
		ProgressData data;
		GetCurrentData(data);
		return data.fPercentage;
	}
	
private:
	friend class IDTaskAccessor;
	
	PUBLIC_DECL void SetRange(ProgressRange range);
	
	/** Sets the current position.
	 */
	PUBLIC_DECL void SetCurrentPosition(uint32 pos);
	
	PUBLIC_DECL void SetTaskCompletionPercentage(PMReal percentage);
	
	ProgressData		fData;		   /**< the progress data */
	IDThreading::spin_mutex	fDataLock; /**< lock that protects the data */
};

//========================================================================================

/** This class encapsulates task status information.
 */
class TaskStatusInfo
{
public:
	
	/** The enumeration of possible states for a task
	*/
	enum TaskState
	{
		kQueued			= 0x0,		/**< Task was initialized and added to the queue but it is not running yet */
		kRunning		= 0x1,		/**< Task is running */
		kFinishing		= 0x2,		/**< Task completed (successfully or not) and it's waiting for the completion callback to execute. */
		kCompleted		= 0x3,		/**< Task is done (this state is set when the task finished regardless if it was successful or not - use GetTaskExitErrorStateInfo() to find out the errorState at exit time*/
		kCancelling		= 0x4,		/**< Task was signaled to cancel, but is still running */
		kCancelled		= 0x5,		/**< Task was cancelled either before it ran or during execution and it is now stopped. */
		kWaiting		= 0x6,		/**< Task is waiting for an event */
		kForceKilled	= 0x7,		/**< Task crashed, used only in background pdf export tasks*/
	};
	
	/** A struct that encapsulates all the status data
	*/
	struct StatusData
	{
		StatusData() : fCurrentState(kQueued), fWasCancelled(false)
		{}
		
		ErrorStateInfo		fExitErrorStateInfo;	/**< Error state info when the task finished */
		AlertMessageQueue	fAlertMessageQueue;		/**< Queue of alert messages generated during the task */
		TaskState			fCurrentState;			/**< Current state of the task */
		bool				fWasCancelled;			/**< Flag set when this task was signalled to cancel. */
	};
	
	/** Constructor
	*/
	TaskStatusInfo()
	{}
	
	/** Retrieves the current state of the task.
	 */
	PUBLIC_DECL TaskState GetCurrentState() const;
	
	/** Global error code state when the task finished.
		\warning{ Should only be called if the TaskState is \c Cancelled or \c Completed. }		
	 */
	PUBLIC_DECL ErrorStateInfo GetTaskExitErrorStateInfo() const;
		
	/** Retrieve the alert messages that were logged during task execution.
	 */
	PUBLIC_DECL AlertMessageQueue GetAlertMessages() const;

	/** for internal use only */ 
	/** Clear the alert messages that were logged during task execution.
	 */
	PUBLIC_DECL void ClearAlertMessages();

	/** Returns true if the task was signalled to cancel, false otherwise.
	 */
	PUBLIC_DECL bool WasCancelled() const;
	
	/** Returns a snapshot of the current status data */
	PUBLIC_DECL StatusData GetCurrentData() const;
	
private:
	friend class IDTaskAccessor;
	
	/* ---------- Called only internally -----------------*/
	
	void SetState(TaskState newState);
	
	void AppendAlert(const AlertMessage& msg);
	
	void SetExitErrorStateInfo(const ErrorStateInfo &info);

	// Sets the internal state to cancelled
	void Cancel();
	
	StatusData			fStatusData;		/**< status data */
	IDThreading::spin_mutex	fDataLock;		/**< Lock that protects access to \f fStatusData */
};



//========================================================================================

/** This class is used to track the status and progress of background tasks.
 Each top level task registers with the TaskMonitor which will hold a pointer to that task info.
 A client can obtain a TaskInfo from the TaskMonitor, store it and poll it for status and progress information.
 Not all tasks have progress information but all should have a name and should support cancellation. 
 */
class PUBLIC_DECL TaskInfo : boost::equality_comparable<TaskInfo, TaskInfo>
{
public:
	
	typedef AsyncWorkPacketID TaskID;
	/** Construct a TaskInfo from a const IDTaskPtr */
	explicit TaskInfo(const IDTaskPtr& myTask);
	/** Construct a TaskInfo from an IDTask reference */
	explicit TaskInfo(IDTask& myTask);
	/*@}*/
	
	/** Default constructor - creates an invalid task */
	TaskInfo();
	/** Destructor */
	~TaskInfo();
	/** Copy constructor - add a reference to the IDTaskPtr in \a other
		@param[in] other TaskInfo representing the task
     */
	TaskInfo(const TaskInfo& other);

	/** Move constructor - moves the content of \a other into this object, leaving \a other in destructible state
		@param[in] other TaskInfo that will be invalid after this method
	 */
	TaskInfo(adobe::move_from<TaskInfo> other);
	
	/** Move-compatible assignment operator.
		@param[in] other TaskInfo that will be invalid after this method
	*/
	TaskInfo& operator=(TaskInfo other);
	
	//@{

	/** Retrieves the unique task identifier for this task.
		@return the unique identifier for this task. If this TaskInfo is invalid this method returns kInvalidAsyncWorkPacketID
	 */
	TaskID GetID() const;

	/** Retrieves a copy of the current task status info.
		Useful when the caller needs all the data in one call, or will be making several status-related
		calls.
		@see TaskStatusInfo::StatusData

		@param[out] data current data. Only filled when the return value is true.
		@return [false] if this TaskInfo is invalid. [true] if the underlying task exists.
		@warning If the return value is [false] the \a data parameter is unchanged.
	 */
	bool GetTaskStatusData(TaskStatusInfo::StatusData& data) const;
	
	/** Retrieves a snapshot of all progress data.
		@see TaskProgressInfo::ProgressData
		@param[out] data current data. Only filled when the return value is true.
		@return [false] if this task doesn't have a progress bar associated with it (its duration is indeterminate)
		[true] if the task has progress information.
		@warning If the return value is [false] the \a data parameter is unchanged.
		@note a task may return false if called early on startup before the task creates a progress bar.
	 */
	bool GetTaskProgressData(TaskProgressInfo::ProgressData& data) const;	
	
	/** Retrieves the job spec for this task 
		@internal
		@return AsyncWorkPacketJobSpec for this task
	*/
	const AsyncWorkPacketJobSpec& GetJobSpec() const;
	
	/** Retrieves the task description
		@return the task description string.
	*/
	PMString GetName() const;

	/** Retrieves the current state of the task
		@see TaskStatusInfo::TaskState
		
		@return state of the task.
	*/
	TaskStatusInfo::TaskState GetCurrentState() const;	

	/** for internal use only */ 
	/** Clear the alert messages for the task.
	 */
	void ClearAlertMessages();

	/** Retrieves the current task completion as a percentage	
		@return task completion percentage.
	*/
	PMReal GetTaskCompletionPercentage() const;

	/** Retrieves any alerts or errors from the task
		@see AlertMessageQueue
		@return an AlertMessageQueue containing alerts or errors from the task
	*/
	AlertMessageQueue GetAlertMessages() const;

	/** Retrieves the ErrorStateInfo at exit of the task.
		@see ErrorStateInfo
		@return error state info at the exit of the task.
	*/
	ErrorStateInfo GetTaskExitErrorStateInfo() const;

	/** Check if the underlying task was previously signaled to cancel
		@return true if the task was cancelled, false otherwise
	*/
	bool WasCancelled() const;

	/** Check if this TaskInfo refers to a valid task
		@return true if this TaskInfo refers to a valid task
	*/
	inline bool IsValid() const
	{
		return fTask != nil;
	}
	//@}
	
	//@{
	
	/** Signal the underlying task to cancel. 
		@warning This method returns immediately, so callers that depend on the task
		being stopped should call \c WaitForTask.	
	*/
	void Cancel();
	
	/** Wait for the underlying task to finish executing and return the state.
		@return TaskStatusInfo::TaskState of the underlying task at completion.
	*/
	TaskStatusInfo::TaskState WaitForTask();
	
	//@}

	// Operators:
	/** swap the contents of two TaskInfo objects */
	friend inline void swap(TaskInfo& left, TaskInfo& right)
	{
		swap(left.fTask, right.fTask);
	}
	
	/** Equality operator */
	friend inline bool operator==(TaskInfo const& left, TaskInfo const& right)
	{
		return left.GetID() == right.GetID();
	}
		
private:
	
	IDTaskPtr		fTask;		/**< A reference to the underlying task */
};

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_0("taskinfo:indesign:adobe",TaskInfo);

#endif // __TASKINFO_H__
