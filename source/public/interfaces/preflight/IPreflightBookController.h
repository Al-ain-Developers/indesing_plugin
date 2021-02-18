//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightBookController.h $
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

/**	This interface provides a state machine based preflighting controller. It uses and modifies
	the IPreflightBookData and IPreflightBookContentData interfaces on the same boss.

	Typical usage is a something like this:

		InterfacePtr<IPreflightBookRef> iBookRef(iBook, UseDefaultIID());
		InterfacePtr<IPreflightBookData> iBookData(iBookRef->CreateActivePreflight());
		InterfacePtr<IPreflightBookController> iController(iBookData, UseDefaultIID());
		iController->BeginPreflight(chapters);
		while(!iController->AdvanceState(duration)) 
		{ 
			MyUpdateProgress(iController->GetCurrentStatus(...));
		}
		iController->EndPreflight();

		InterfacePtr<IPreflightAggregatedResults> iBookResults(iBookData->CreateAggregatedResults());
*/
class IPreflightBookController : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTBOOKCONTROLLER };

public:
	/** Begin a preflight operation. This initializes all of the chapter mappings as appropriate
		given the passed-in selection. Note that it's dangerous to make any changes to the documents
		that are open, or to the book, or any settings, while the preflight is in operation; it is
		divided into methods like this in order to allow the caller flexibility in reporting progress.

		@param contentSelection IN The content (chapters) you want to preflight.
	*/
	virtual void BeginPreflight(const UIDList& contentSelection) = 0;

	/** Advance the preflight state by providing a certain amount of time.

		@param duration IN The number of seconds to provide to the method before returning.
			Note that in some cases (eg when opening a document) we aren't able to guarantee
			this amount of time. Also, we may return early, for example when preflight is complete.
		@return kTrue if the preflight is done; kFalse otherwise.
	*/
	virtual bool AdvanceState(const PMReal& duration) = 0;

	/** Get the current status as a percentage and as a string. Useful for updating a progress bar.
		@param percentage OUT Receives the (approximate) percentage between 0 and 1.
		@param description OUT Receives the status (current operation) as a string.
		@return kTrue if the preflight is complete (status will also be 1); kFalse if not.
	*/
	virtual bool GetCurrentStatus(PMReal& percentage, PMString& description) const = 0;

	/** @return whether the operation has been cancelled.
	*/
	virtual bool WasCancelled() const = 0;

	/** Cancel preflight. Note that this *might* take a few cycles (eg closing documents) so
		you should continue to AdvanceState until it returns true, then call EndPreflight().
	*/
	virtual void Cancel() = 0;

	/** End a preflight operation.
	*/
	virtual void EndPreflight() = 0;
};

