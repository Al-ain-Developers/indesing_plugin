//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/isignalmgr.h $
//  
//  Owner: Roey Horns
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
//  Purpose:	Manage service based responders to a given signal that are interdependent.
//  
//========================================================================================

#pragma once
#ifndef __ISIGNALMGR__
#define __ISIGNALMGR__

#include "IPMUnknown.h"
#include "ShuksanID.h"

/** ISignalMgr is used to send a Signal.

	The Signal/Responder protocol is used particularly for broadcasting model changes,
	but is used anytime the listener doesn't care what object changed, but is intererested
	in finding out about all changes of a certain class. ISignalMgr handles sending the
	message to the responders. 
	
	Responders implement a given ServiceID. The sender (usually a command) gets the  
	signal mgr and sends the message. There is a single default implementation of
	ISignalMgr which is used to actually send the message; usually this is either 
	attached to the command which is sending the message, or on a standalone boss.
	Either way works equally well.
	
	To send a signal, typically you need code that does something like this:
	
	<pre>
	#include "ISignalMgr.h"

	InterfacePtr<ISignalMgr> signalMgr(this, UseDefaultIID());
	signalMgr->Init(kMySignalServiceID);
	signalMgr->SignalAllResponders(kMySignalServiceID);
	</pre>
	
	If you have data you want to pass along in the signal, you can supply it as 
	a data interface if necessary. But if you are signalling on a command, and
	attach the signalmgr to the command, then this is typically not necessary 
	because the responder is passed the signalmgr and can use it to query for the 
	command's data interface directly.
	
	If you need to control the loop yourself, you can do this by iterating the
	responders and terminating the signalmgr yourself. Typically this is not
	necessary.
	
	@see IResponder handles receiving signals.
*/ 
class ISignalMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISIGNALMGR };
	

	/** Initialize the signal mgr (should only get called once)
	
		@param serviceID this tells the SignalMgr what responders to call
	*/
	virtual void Init(ServiceID serviceID) = 0;
	
	/** Call this when you are done with the SignalMgr. The Terminate function
		is used to handle errors. A responder may flag an error by setting the
		global error code. If a responder encounters an error, then iteration
		should be aborted, and Terminate should be called.  Terminate will signal 
		all the responders who have already been called, to let them know that an 
		error occurred.
	*/
	virtual void Terminate() = 0;

	/** Get the ServiceID that this SignalMgr signals on. This is used so that
		client responders may have a single responder capable of handling more
		than one type of signal.
	
		@return ServiceID what service this signal manager is signalling
	*/
	virtual ServiceID GetServiceID() const = 0;
	
	/** Get the number of responders that will be called.
	
		@return int32 the number of responders to signal
	*/
	virtual int32 CountResponders() const = 0;
	
	/** Get the number of responders that are not yet signaled
	
		@return int32 how many responders still need to be signalled
	*/
	virtual int32 CountUnsignaledResponders() const = 0;
	
	/** Send a signal to the next responder. Callers should check the error code,
		and abort iteration in case of error!
		
		@return ErrorCode kSuccess if responder succeeded, the failure code otherwise
	*/
	virtual ErrorCode SignalNextResponder() = 0;
	
	/** Signal a specific responder. The responder may return an error. The error may
		be specific to the responder, but could also be either kUnknownResponderError
		or kResponderIsBusyError.
		
		@return ErrorCode kSuccess if responder succeeded, the failure code otherwise
	*/
	virtual ErrorCode SignalResponder(ClassID actionClassID) = 0;

	/** Signal all responders. This initializes the SignalMgr, iterates through the responders,
		calling each one and aborting in case of error, then calls Terminate. It will optionally
		display a progress indicator.
		
		@return ErrorCode kSuccess if no error, an error code otherwise.
	*/
	virtual ErrorCode SignalAllResponders(ServiceID serviceID, bool16 showProgress = kFalse) = 0;
	
};

#endif // __ISIGNALMGR__

