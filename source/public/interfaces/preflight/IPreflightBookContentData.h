//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightBookContentData.h $
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
#include "PreflightObjectID.h"
#include "PackageAndPreflightID.h"

class IPreflightProcess;
class IPreflightBookData;
class IBook;
class IPreflightAggregatedResults;

/**	This interface maintains the data/status for a particular book preflight operation.
	@see IPreflightBookOptions for the options used for this preflight.
*/
class IPreflightBookContentData: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTBOOKCONTENTDATA };

	enum Status
	{
		/** Preflight has never been requested for this entry. */
		kNoPreflightDone, 

		/** Preflight was done at one point; but the results are no longer valid, so it's back to 
			square one. Still, it's good to know this as opposed to the previous enum value. 
		*/
		kPreflightDoneButNowInvalid, 

		/** Currently preflighting this document. */
		kCurrentlyPreflighting, 

		/** Tried to preflight but couldn't open the document. */
		kCouldNotOpen,

		/** Could open the document but preflight failed for some reason. */
		kCouldNotPreflight,

		/** Preflight has been selected and it's all done. */
		kPreflightSuccessful
	};

public:
	/** Set the parent book data. Needed to get proper notification of changes.
		Should be done once as part of initialization.
		@param iParent IN The parent.
	*/
	virtual void SetParent(IPreflightBookData* iParent) = 0;

	/** Get the parent book data.
		@return Refcounted parent, or nil if no parent.
	*/
	virtual IPreflightBookData* QueryParent() const = 0;

	/** Set the status of this data entry.
		@param newStatus IN The new status.
	*/
	virtual void SetStatus(Status newStatus) = 0;

	/** @return the status of this data entry.
	*/
	virtual Status GetStatus() const = 0;

	/** Attach (or detach) an aggregated results to this content.
		@param iResults IN The new results, or nil to clear the results.
	*/
	virtual void SetAggregatedResults(const IPreflightAggregatedResults* iResults) = 0;

	/** @return a refcounted aggregated results for this content, or nil if there are 
			no results attached.
	*/
	virtual const IPreflightAggregatedResults* QueryAggregatedResults() const = 0;

	/** Set the selection state for this content. This is used to indicate whether the 
		content is still slated for preflight in the current operation. Goes false as 
		soon as the document is opened.
	*/
	virtual void SetSelected(bool selected) = 0;

	/** Get the selection state for this content. This is used to indicate whether the 
		content is still slated for preflight in the current operation. Goes false as 
		soon as the document is opened.
	*/
	virtual bool GetSelected() const = 0;

	/** Set the process ID for this book preflight operation. 
		@param newUniqueID IN The new process unique ID.
	*/
	virtual void SetProcessID(uint32 newUniqueID) = 0;

	/** Get the ID of the process associated with the preflight operation.
		@return The preflight process ID.
		@see IPreflightProcess
		@see IPreflightProcessManager
	*/
	virtual uint32 GetProcessID() const = 0;

	/** Query the process associated with the preflight operation. This is a convenience
		method; it calls IPreflightProcessManager::QueryProcessByUniqueID.
		@return The preflight process. Might be nil depending on what stage the preflight is in.
	*/
	virtual IPreflightProcess* QueryProcess() const = 0;
};

