//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightProcessManager.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPreflightObject.h"
#include "IPreflightProcess.h"

class IdleTimer; // See IIdleTask.h
class IDocument;
class IBook;

/**	The preflight process manager keeps track of the active (and inactive) preflight
	processes. It sits on the session boss, but probably the best way is to get it from
	IPreflightManager or using IPreflightUtils::QueryProcessManager().

	@see IPreflightManager
	@see IPreflightUtils
*/
class IPreflightProcessManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTPROCESSMANAGER };

public:
	/** Called by the preflight manager at application startup; do not call.
	*/
	virtual void Startup() = 0;

	/** Called by the preflight manager at application shutdown; do not call.
	*/
	virtual void Shutdown() = 0;

	/** Called by the preflight manager; you shouldn't call this. Deletes any processes that are
		still active on the document (if not preserved by being part of a book preflight).
	*/
	virtual void OnCloseDocument(IDocument* iDoc) = 0;

	/** Called by the preflight manager; you shouldn't call this. Closes all the processes associated
		with the book preflight.
	*/
	virtual void OnCloseBook(IBook* iBook) = 0;

		/** Get the total number of processes, active and inactive.
		@return Number of processes.
	*/
	virtual int32 GetProcessCount() const = 0;

	/** Get the number of active processes (ie those with something to do).
		@return Number of processes.
	*/
	virtual int32 GetActiveProcessCount() const = 0;

	/** Get a particular process for further inspection.
		@param n The index of the process you're interested in, between 0 and GetProcessCont() - 1.
		@return A refcounted interface to the preflight process.
	*/
	virtual IPreflightProcess* QueryNthProcess(int32 n) const = 0;

	/** Get a particular process for further inspection.
		@param uniqueID The unique ID of the process you're interested in.
		@return A refcounted interface to the preflight process, or nil if the unique ID does not exist.
	*/
	virtual IPreflightProcess* QueryProcessByUniqueID(uint32 uniqueID) const = 0;

	/** Find a process in the list of processes.
		@param iProcess The process you're looking for.
		@return The index of the process in the list, or -1 if not found.
	*/
	virtual int32 FindProcess(IPreflightProcess* iProcess) const = 0;
	
	/** Find a process in the list of processes by its unique ID.
		@param id The ID of the process you're looking for.
		@return The index of the process in the list, or -1 if not found.
	*/
	virtual int32 FindProcess(uint32 uniqueID) const = 0;
	
	/** Find a process in the list of processes by its selector/database pair. These are used to
		'tag' a process as important for a particular reason, such as the current profile for
		continuous preflight for a given document.

		@param selectorID The selector ID of the process you're looking for.
		@param docID The document associated with the process.
		@return The index of the process in the list, or -1 if not found.
	*/
	virtual int32 FindProcess(ClassID selectorID, const PreflightDocumentID& docID) const = 0;
	
	/** Get the indices of the processes that are examining a particular document (if any).
		Can also be used to simply indicate *whether* there are any by passing nil for 'indices.'
		@note "Examining" simply means that there is a task with a root object that comes from
			the document. It doesn't matter what state the task is in.

		@param iDoc IN The document you're interested in.
		@param indices OUT Receives the indices of the processes that are examining the document
			(note that these processes can also be examining other documents, if the tasks are 
			set up that way). If nil, the only check is for the presence of an open process for
			the document (in the return value).
		@return True if there are any processes examining the document.
	*/
	virtual bool GetProcessesForDocument(const IDocument* iDoc, K2Vector<int32>* indices) const = 0;
	
	/** Remove a process from the list. This dereferences the process, so if nobody else
		has a handle on it, it will delete the process. In any case, once the process manager
		doesn't know about the process, it won't get cycles via the master idle callback.

		@param n IN The index of the process you want to remove from the list.
	*/
	virtual void RemoveNthProcess(int32 n) = 0;

	/** Create a new process.
		@param docID IN The document ID the process is bound to (@see IPreflightManager)
		@param iOptions IN The options to use for the process, or nil to leave them at ctor defaults.
		@param iBook IN If not nil, the book this process is associated with.
		@return A new process (with refcount = 2, one for being in the list, one for the caller).
	*/
	virtual IPreflightProcess* CreateProcess() = 0;
	
	/** Provide time for processes to work, normally during the idle callback.
		@param timer IN The timer function that lets the process manager know how much time remains.
					If nil, the process manager works until all tasks are completed, but that's 
					kind of dangerous since no progress feedback is provided at this level.
		@param synchronous IN Set this to true if you are calling this in a tight loop where (for
			example) the text composer will not be given any time to work; otherwise the process
			will never (or only extremely slowly) complete. When true, text composition will
			be forced synchronously prior to preflight expansion and visitation. Set this parameter
			to false if you're calling it from an idle loop where the text composer has a chance
			to operate efficiently.
		@param pNextCallback OUT If not nil, receives the number of milliseconds until the next
			desired callback, based on the priorities and states of all of the processes after
			it has distributed work to the list of processes. 
	*/
	virtual void AdvanceState(IdleTimer* timer, bool synchronous, uint32* pNextCallback = nil) = 0;
	
	/** This method adjusts the idle behavior to establish a "time standoff" window where the idle
		task will simple early-out (ie, exit without doing anything) until the time window is 
		exhausted. This standoff is applied at key points, such as application switch-in (resume),
		new or open document, and invalidation, to avoid preflight being too aggressive. For 
		example if you are nudging a page item or typing we don't want to jump in RIGHTAWAY and 
		start checking again, as this can have a subtle effect on user responsiveness. Thus we 
		wait a short while before resuming preflight.

		Preflight maintains a per-document standoff and a global standoff. These are essentially
		wall-clock times when the "green light" comes on for a given document. A document must
		have its green light *and* the global green light to get preflight cycles.

		Note that this standoff DOES NOT apply to synchronous preflight requests, ie AdvanceState
		when synchronous=true or timer=nil. It only applies to the idle/background preflight slices.

		@param seconds IN The number of seconds of standoff (from this moment) to wait before
			resuming preflight.
		@param iDoc IN The document to apply the standoff to, or nil to apply it globally
			(ie, it affects all documents).
	*/
	virtual void AddTimeStandoff(double seconds, IDocument* iDoc = nil) = 0;

	/** Invalidation (this API will probably need to be more sophisticated eventually).
		This forwards the invalidation request to all applicable processes.

		@param objID The object needing invalidation.
	*/
	virtual void InvalidateObject(const PreflightObjectID& objID) = 0;

	/** Change of settings, either at the app or doc levels. This is forwarded on to each process
		to determine whether that change affects that process.

		@param iInfo The settings change info to respond to.
	*/
	virtual void OnSettingsChange(const IPreflightSettingsChangeInfo* iInfo) = 0;

	/** Obtain a new process unique ID.
	*/
	virtual uint32 NewProcessUniqueID() = 0;

	/** Obtain a new process task unique ID.
	*/
	virtual uint32 NewProcessTaskUniqueID() = 0;
};

