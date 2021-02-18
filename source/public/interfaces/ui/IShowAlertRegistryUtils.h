//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IShowAlertRegistryUtils.h $
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
#ifndef __IShowAlertRegistryUtils__
#define __IShowAlertRegistryUtils__

#include "AppUIID.h"

#pragma export on

/**
	Utilities for querying and modifying the "don't-show" registry, which controls which
	alerts are shown and which are not, based on the user's previous checking of "don't
	show this alert again" checkbox in many alerts, as well as the "show all alerts again"
	option in preferences, which brings them all back to life.

	@see IShowAlertRegistry
*/

class IShowAlertRegistryUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISHOWALERTREGISTRYUTILS };

	/** Returns whether the specified alertID should be shown.
		@param alertID The alert ID you're interested in.
		@return kTrue to show the alert; kFalse not to.
	*/
	virtual bool32 GetShouldShow(int32 alertID) = 0; 

	/** Processes a command to set the should-show state for the specified alert.
		@param alertID The alert to show/not-show.
		@param shouldShow kTrue to show (enable) the alert; kFalse to not-show (disable) the alert.
		@return The command error code.
	*/
	virtual ErrorCode DoSetShouldShowCmd(int32 alertID, bool32 shouldShow) = 0; 

	/** Processes a command to set the should-show state to show/enable for all alerts.
		@return The command error code.
	*/
	virtual ErrorCode DoClearAllCmd() = 0;
};
#pragma export off

#endif // __IShowAlertRegistryUtils__