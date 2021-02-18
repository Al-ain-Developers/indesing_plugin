//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITrackerRegister.h $
//  
//  Owner: robin briggs
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
#ifndef __ITrackerRegister__
#define __ITrackerRegister__

#include "IPMUnknown.h"

class ITrackerFactory;

/** Defines an interface used for registering trackers. When the app
	starts up with no saved data, it will query all objects that 
	implement ITrackerRegister and request them to register their 
	trackers. This is similar to how services, menus, and palettes are 
	registered. Typical implementation of a tracker register interface
	will use the factory interface to call InstallTracker. Will typically
	be installed on a boss that also has an IID_IK2SERVICEPROVIDER service
	provider with kCTrackerRegisterProviderImpl implementation.

	@see ITrackerFactory.h
	@see ITracker.h
*/
class ITrackerRegister : public IPMUnknown
{
public:

	/**	Called at startup in order to register a particular tracker.
		@param *factory the ITrackerFactory interface to register your tracker in.
	 */
	virtual void Register(ITrackerFactory *factory) = 0;
};


#endif // __ITrackerRegister__