//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AutoBusyCursor.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __AutoBusyCursor__
#define __AutoBusyCursor__

#include "CmdUtils.h"

/**
	A stack-based approach to enabling/enabling busy cursor support during command and sequence processing.
	Typically used to turn off busy cursor in command processor during tracking, then restore after tracking
	is finished. Base class CTracker does this automatically in BeginTracking and EndTracking, which covers most, 
	if not all, tracker clients. Trackers can then freely manipulate cursor, even during open command sequences.
	@see CmdUtils.h
	@see CTracker.h
*/
class AutoBusyCursor
{
public:
	/**
		Stack-based object constructor to manage busy cursor during command/sequence processing.
		Typically managed automatically, but this object allows finer control. Restores previous state
		in destructor. 
		@param bEnabled is the desired state of the busy cursor
	*/
	AutoBusyCursor(bool16 bEnabled)
		{
			fSavedBusyCursorState = CmdUtils::IsBusyCursorEnabled();
			CmdUtils::EnableBusyCursor(bEnabled);
		}

	/**
		Restore busy cursor to previous state.
	*/
	~AutoBusyCursor()
		{
			CmdUtils::EnableBusyCursor(fSavedBusyCursorState);
		}

private:
	bool16 fSavedBusyCursorState;
};

#endif //__AutoBusyCursor__
