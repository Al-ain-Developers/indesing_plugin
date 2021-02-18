//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITipRegister.h $
//  
//  Owner: lance bushore
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
//  Purpose of interface:
//  provide a standard hook for plugins to register tips. Allows plugin to add any 
//  number of widget tips to the current tip manager. Note that this could be called multiple 
//  times in a session for different locales, and it is possible to register different
//  tips for different locales.
//  
//========================================================================================

#pragma once
#ifndef __ITipRegister__
#define __ITipRegister__

#include "PMLocaleId.h"
#include "TipsID.h"

/** Interface responsible for registering tip strings during startup
*/
class ITipRegister : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITIPREGISTER };

	/**  add appropriate tips to the tipmanager. This is only called at the first startup. We call this on bosses that support kTipRegisterService
		@param localeId which locale we're registering for
	*/
	virtual bool16 Startup(const PMLocaleId& localeId) = 0;
};


#endif


