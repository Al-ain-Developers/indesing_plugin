//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IStartupShutdownService.h $
//  
//  Owner: David Berggren
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
#ifndef __IStartupShutdownService__
#define __IStartupShutdownService__

#include "IPMUnknown.h"

/** This is an Interface plugins can implement if they'd like to be called during startup and shutdown.
	In order to get your implementation of this interface called at startup/shutdown, you must
	create a new boss.  like so:
	
resource ClassDescription (13)
{
	kXXXStartupShutdownBoss,   
	kInvalidClass,
	{
		IID_IK2SERVICEPROVIDER, kYYYStartupShutdownProviderImpl,
		IID_ISTARTUPSHUTDOWN, kXXXStartupShutdownImpl,
	}
};

	The value of kYYYStartupShutdownProviderImpl should be either kCStartupShutdownProviderImpl or
	kLazyStartupShutdownProviderImpl, depending on whether your Startup method MUST be call during startup 
	or if it is okay to call your Startup method during an idle task immediately after startup.  When possible,
	you should use kLazyStartupShutdownProviderImpl to avoid slowing down launch time.

	Then at startup your XXXStartupShutdown::Startup() method will be called, regardless of the implementation you
	choose for kYYYStartupShutdownProviderImpl above, and you can do whatever you want.

	Similarly your Shutdown() method will be called during app termination.
*/

class IStartupShutdownService : public IPMUnknown
{
public:

	/** The service provider's Startup() method is called just after the Service Registry is set up. 
	*/
	virtual void Startup() = 0;

	/** The Shutdown() method is called just prior to the Service Registry destruction. 
	*/
	virtual void Shutdown() = 0;
};

#endif
