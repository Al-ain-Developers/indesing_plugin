//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IK2ServiceProvider.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __IK2ServiceProvider__
#define __IK2ServiceProvider__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "K2Vector.h"
#include "IPlugIn.h"

/** The IK2ServiceProvider interface is aggregated by any boss object that wishes to register that it supports a specific service with the IK2ServiceRegistry.

At application startup the service registry finds all boss objects with an IK2ServiceProvider interface and gathers the information about what ServiceID 
they support, etc.  This mechanism is automatic, so all a boss needs to do to be a service is aggregate an implementation of this interface.

Any object that provides a service must implement this interface. A service is a generic way for a plug-in to declare that it provides a service for 
use by the application. Services are used throughout InDesign. Some examples include scripting, composition, signal/responder, etc.
*/

class IK2ServiceProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IK2SERVICEPROVIDER };

		/** A service may optionally have a name.  The service registry
			does not use this name in any way.
		*/
	virtual void GetName(PMString * pName) = 0;
		
		/**	Each type of service is identified by a ServiceID. This function returns
			the ServiceID that this service implements.
		*/
	virtual ServiceID GetServiceID() = 0;
		
		/** For the majority of service providers this method should return kFalse.
			However, if a specific service provider should always be the default
			for its service this can be set to kTrue.
		*/
	virtual bool16 IsDefaultServiceProvider() = 0;
	
		/** A service provider can choose to have once instance that is shared by
			all requests for that service providers (this is the most common case - 
			kInstancePerSession), or a service provider may choose to have a unique 
			instance created on each request for the service provider (kInstancePerUse).
			"Instance Per Session" service providers are created when first requested
			and cached by the service registry as long as available memory allows.
			kInstancePerSessionNoPurge is similar, but will not be purged or unloaded
			until shutdown (such as "state" data that is expensive or difficult to regenerate). 
			Think carefully before choosing to create a "nopurge" service.
			kInstancePerSessionPreload will cause a service provider to be constructed
			and cached at application startup.  Furthermore, a "preload" service
			provider will not be unloaded until application shutdown.
			Note:  Since "preload" service providers are never unloaded, they incur
			the memory overhead for the service.  Therefore "preload" service providers should
			be avoided, when possible.  If you need to be called at startup and/or
			shutdown, use a kStartupShutdownServiceID.
		*/
	typedef enum { kInstancePerSession, kInstancePerUse, kInstancePerSessionPreload, kInstancePerSessionNoPurge } InstancePerX;
	
		/** Get the instantiation policy used for this service. @see IK2ServiceMgr
			@return InstancePerX the instantiation policy
		*/
	virtual InstancePerX GetInstantiationPolicy() = 0;
	
		/** Support for multiple Service ID's
			A single service provider may support multiple service IDs.  This is
			a most frequently used for dialog panels that appear in multiple dialogs.
			If a service does support multiple service ID's and is instance per session,
			one instance is created per service ID.
			@return kTrue if this service supports multiple ServiceIDs
		*/
	virtual bool16 HasMultipleIDs() const = 0;
	
		/** If the service supports more than on ServiceID, return a list of 
			services supported.
			@return K2Vector<ServiceID> all supported services
		*/
	virtual void GetServiceIDs(K2Vector<ServiceID>& serviceIDs) = 0;

		/** A service provider can choose if it wants to be instantiated and used by other
			threads than the main thread. By default the threading policy returned by the base class
			CServiceProvider is kUnknownThreadingPolicy which means that the service provider
			will NOT be used by other threads besides the main thread.
			If a service is designed to be only used exclusively by the main thread it should return kMainThreadOnly.
			All UI service providers will fall in this category.
			If a service provider returns kMultipleThreads, it will be instantiated
			in each worker thread according to its instantiation policy
			(kInstancePerSession in this case will mean one instance in each thread session).
		*/
	
		/** Get the threading policy used for this service.
			@return the threading policy
		*/
	virtual IPlugIn::ThreadingPolicy GetThreadingPolicy() const = 0;
};

#endif
