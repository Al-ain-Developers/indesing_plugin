//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IBridgeTalkUtils.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IBridgeTalkUtils__
#define __IBridgeTalkUtils__

#include "IPMUnknown.h"
#include "Utils.h"

#include "JavaScriptID.h"

/** Utilities related to BridgeTalk scripting.
*/
class IBridgeTalkUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBRIDGETALKUTILS };

	/**
		Execute a script via the script runner that supports BridgeTalk. For information on how to 
		write a script that sends a message via BridgeTalk, consult a BridgeTalk JavaScript guide.
		@param msg is a text script
		@result the error code returned by the script
	*/
	virtual ErrorCode PostMessageToBridgeTalk( const PMString& msg ) const = 0 ;

	/**
		Checks for pending incoming BridgeTalk messages. Code that might raise a modal dialog
		during startup should call this method to determine whether the application was
		launched via a BridgeTalk request (in which case putting up a modal dialog is discouraged).
		Note: Most clients also test Utils<IStartupUtils>()->WillFilesBeOpenedAtStartup() == kFalse
		before putting up a modal dialog on startup.
		@return whether there is a BridgeTalk request pending
	*/
	virtual bool16 CheckForIncomingBridgeTalkTraffic() const = 0 ;
	
	/**
		This is a convenience method to determine if a CS app is installed or not.
		@param appSpec is a character string for the BridgeTalk app specifier (e.g. "bridge-4", "photoshop-11", etc).
		@return true if the app is installed, false otherwise
	 */
	virtual bool16 IsAppInstalled( const char* appSpec ) const = 0 ;
};

#endif	// __IBridgeTalkUtils__
