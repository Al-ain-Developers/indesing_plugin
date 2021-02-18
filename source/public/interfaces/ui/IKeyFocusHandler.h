//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IKeyFocusHandler.h $
//  
//  Owner: Tom Taylor
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
#ifndef __IKeyFocusHandler__
#define __IKeyFocusHandler__

#include "IPMUnknown.h"

class IControlView;
class IEventHandler;


/**
	This interface is associated with a window boss to handle keyboard focus function on 
	this particular window.
*/
class IKeyFocusHandler : public IPMUnknown
{
public:	
	/**
		Return the first control's event handler in the dialog that can be the keyboard target.

		@return	keyboard target or nil if no target
	*/
	virtual IEventHandler*	GetFirstTargetEventHandler() = 0;
	
	/**
		Return the next control's event handler in the dialog that can be the keyboard target. 
		Pass in false to get the previous control.  If there's only a single control, the 
		current control's event handler will be returned.

		@param forward search direction. kTrue search forward and kFalse search backward
		@return	keyboard target or nil if no target
	*/
	virtual IEventHandler*	GetNextTargetEventHandler(bool16 forward) = 0;
	
	/**
		Return the current event handler that is the keyboard target.

		@return	keyboard target or nil if no target
	*/
	virtual IEventHandler*	GetCurrentTargetEventHandler() = 0;
	
	/**
		Set the event handler that will be the keyboard target. Returns kFalse if the function 
		wasn't able to set the event handler as the target. This might happen when the current 
		target won't let go of the keyboard. If you pass kFalse for the "validate" parameter, 
		then validation won't occur for the event handler that currently has the focus.

		@param handler IEventHandler we try to set as keyboard target.
		@param validate kTrue validate current key focus target.
		@return	boolean kTrue if the function was able to set the event handler as the target. kFalse otherwise
	*/
	virtual bool16 SetCurrentTargetEventHandler(IEventHandler * handler, bool16 validate = kTrue) = 0;

	// ----- Internal Functions -----
	/**
		For internal use only. Use should call SetCurrentTargetEventHandler instead.
	*/
	virtual void SetTargetEventHandler(IEventHandler* view) = 0;
};

#pragma export on

/**
	Utility function for getting the KeyFocusHandler from an event handler
*/
WIDGET_DECL IKeyFocusHandler* QueryKeyFocusHandler(IEventHandler* eventHandler);

#pragma export off

#endif
