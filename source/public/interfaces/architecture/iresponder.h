//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/iresponder.h $
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
//  Purpose:	Interface for signal responders.
//  
//========================================================================================

#pragma once
#ifndef __IRESPONDER__
#define __IRESPONDER__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "IPlugIn.h"

class ISignalMgr;

/** IResponder is used to recieve a Signal.

	The Signal/Responder protocol is used particularly for broadcasting model changes,
	but is used anytime the listener doesn't care what object changed, but is intererested
	in finding out about all changes of a certain class. IResponder is implemented in
	order to receive a message. The IReponder implementation can be added to any boss,
	but since the SignalMgr uses the ServiceID to locate the responder, the responder's 
	boss will have to also have an @see IK2ServiceProvider implementation that uses the serviceID
	of the message type. Typically a responder that handles a single type of message can
	use kResponderServiceProviderImpl for the IK2ServiceProvider.
	Note that the threading policy for a responder is dictated by the
	threading policy of the service provider it is associated with (@see IK2ServiceProvider::GetThreadingPolicy comments).
	All implementations of IResponder should inherit from CResponder.
	
	@see CResponder
	@see ISignalMgr
*/
class IResponder : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IRESPONDER };
		
	/** Returns the ServiceID that this responder should get notified on. This is used to allow
		the default responder to service to work. If you have a responder that handles multiple 
		message types, leave this returning kInvalidService, but supply your own implementation
		of IK2ServiceProvider that can handle the multiple services.
		
		@return ServiceID identifies what type of message the responder is interested in
	*/
	virtual ServiceID GetResponderService() = 0;


	/** Respond to the signal. If there's an error, set the global error state to
		cancel the associated action. If you have one responder that depends on 
		another responder having already been signalled, use the SignalMgr::SignalResponder 
		to signal the other responder. The SignalMgr will call the other responder 
		immediately, and will know later on that that responder has already been called.
		The responder may find it handy to query the signalMgr for a data interface
		that contains more information about the action.
		
		@param signalMgr the signalMgr that sent the signal
	*/
	virtual void Respond(ISignalMgr* signalMgr) = 0;

	/** Handle errors that come up during signalling. If the action has been cancelled, 
		and the reponder has already been called, the SignalMgr will call the reponder 
		again, to let it know that the action is cancelled. For instance, suppose that 
		there are 14 observers, and 10 have been called when the eleventh sets the error 
		state. Then the remaining three are not called, and the first 10's SignalError 
		get called. If the responder has attached observers, these should be detached here.
		
		@param signalMgr the signalMgr that sent the signal
	*/
	virtual void SignalFailed(ISignalMgr *signalMgr) = 0;
};

#endif // __IRESPONDER__

