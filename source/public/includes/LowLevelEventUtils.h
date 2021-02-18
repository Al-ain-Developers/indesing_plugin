//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/LowLevelEventUtils.h $
//
//  Owner: Dave Burnard
//
//  $Author: pmbuilder $
//
//  $DateTime: 2020/11/06 13:08:29 $
//
//  $Revision: #2 $
//
//  $Change: 1088580 $
//
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or
//  distribution of it requires the prior written permission of Adobe.
//
//========================================================================================

#pragma once
#ifndef __LowLevelEventUtils__
#define __LowLevelEventUtils__

#pragma export on

namespace LowLevelEventUtils
{
#if MACINTOSH
	
	/** Checks the main event queue for any pending events.
	 */
	PUBLIC_DECL bool CheckEventQueueForPendingEvents();
	
	/** Checks the event queue for an user-cancel event. 	 */
	PUBLIC_DECL bool CheckEventQueueForUserCancel();
	
	
	/**	Posts an event to wake up the main event queue, it posts an empty event but that is enough.
	 */
	enum { idleTaskWakeupEventSubtype = 1337 }; //needs to be semi-unique
	enum { eventLoopWakeupEventSubtype = 1338 }; //needs to be semi-unique
	PUBLIC_DECL void PostEventToWakeUpMainEventQueue(short eventSubType = idleTaskWakeupEventSubtype, bool postToFrontofQueue = false);
	
#endif // MACINTOSH
	
#if WINDOWS
#endif // WINDOWS
	
}; // namespace LowLevelEventUtilities

#endif // __LowLevelEventUtils__
