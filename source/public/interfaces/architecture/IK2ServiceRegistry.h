//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IK2ServiceRegistry.h $
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
//  
//  Purpose:
//  The IK2ServiceRegistry interface lives on the session boss.  The 
//  service registry provides a globally accessible container where 
//  non-persistent bosses can be registered as providing a "service".  
//  A ServiceID (a long integer in K2's ID space) is used to categorize 
//  a set of non-persistent boss objects that support the same set of 
//  interfaces.
//  
//  To provide a service, a boss object only needs to aggregate an 
//  IK2ServiceProvider interface.  The remainder of the interfaces of the 
//  boss can be whatever the developer needs to a specific task.  The 
//  service registry will automatically find and register the boss as a 
//  service during startup.
//  
//  Examples of services include: import filters, export filters, open 
//  converters, text composers, dialog panels, actions to run when creating 
//  a new document, actions to run at application startup/shutdown, image data
//  manipulators, hyphenation systems,  spelling systems, measurement systems, etc.  
//  
//========================================================================================

#pragma once
#ifndef __IK2ServiceRegistry__
#define __IK2ServiceRegistry__

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IK2ServiceProvider;

/** The service registry manages all the services in all the plug-ins. It maintains an
	internal list, sorted by the service's ServiceID.
	A service is a generic concept, identified by a ServiceID. For instance, 
	kScriptProviderServiceID is the service used by objects that want to add new functionality
	to scripting. There may be many different script providers, each one sharing the same
	kScriptProviderServiceID.
	@see IK2ServiceProvider.
*/
class IK2ServiceRegistry : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IK2SERVICEREGISTRY };

		/** Provides access to a specific service.  In many cases a service is provided 
			by a single instance of a boss object that is used by multiple callers.  
			This method returns the existing instance of a service, if one has already 
			been created.
			@param serviceID what service to look in
			@param providerClass the classID of the service provider
		*/
	virtual IK2ServiceProvider * QueryServiceProviderByClassID(ServiceID serviceID, ClassID providerClassID) const= 0;

		/** Returns the default service provider, or if no default has been set the 
			first service provider found for the given ServiceID.
			@param serviceID what service
			@return IK2ServiceProvider the default provider
		*/
	virtual IK2ServiceProvider * QueryDefaultServiceProvider(ServiceID serviceID) const= 0;

		/**	Returns the ClassID of the default service provider, or if no default has 
			been set the ClassID of the first service provider found for the given 
			ServiceID. 
			@param serviceID what service
			@return ClassID the class of the default provider
		*/
	virtual ClassID GetDefaultServiceProviderID(ServiceID serviceID) const = 0;
		
		/** Sets the given classID as the default service provider for the given ServiceID.
			@param serviceID what service
			@param providerClass the classID of the service provider
		*/
	virtual void SetDefaultServiceProviderID(ServiceID serviceID, ClassID classID) = 0;
	

	/**@name  Functions for iterating a particular serviceID  */
	//@{-----------------------------------------------------------------------------


		/** Get the number of providers for the service.
			@param serviceID the service we're interested in
			Return the number of providers for a specific service.
		*/
	virtual int32 GetServiceProviderCount(ServiceID serviceID) const= 0;
		
		/** Return the n'th provider for the service.
			@param serviceID the service we're interested in
			@param n the index of the provider
			@return IK2ServiceProvider* the n'th service provider
		*/
	virtual IK2ServiceProvider * QueryNthServiceProvider(ServiceID serviceID, int32 n) const= 0;

		/** Return the classID of the n'th provider for the service.
			@param serviceID the service we're interested in
			@param n the index of the provider
			@return ClassID of the n'th service provider
		*/
	virtual ClassID GetNthServiceProviderID(ServiceID serviceID, int32 n) const= 0;

		/** Given a service provider, return its index.
			@param serviceID the service we're interested in
			@param serviceProviderID the provider we're interested in
			@return int32 the index of the provider
		*/
	virtual int32 GetServiceProviderIndex(ServiceID serviceID, ClassID serviceProviderID) const= 0;

		/** Given a service provider, return its index.
			@param IK2ServiceProvider* the service provider we're interested in
			@return int32 the index where the provider is found
		*/
	virtual int32 GetServiceProviderIndex(const IK2ServiceProvider * serviceProvider) const= 0;

	//@}-----------------------------------------------------------------------------


	/**@name  For Internal Use Only  */
	//@{-----------------------------------------------------------------------------


		/** Called by the application during application startup.
			Every boss class description that includes an IK2ServiceProvider
			interface is registered as a service provider.
		*/
	virtual void Startup() = 0;

		/** Called by the application during application shutdown.
			The IStartupShutdownService::Shutdown() method of all service
			providers that support the kStartupShutdownServiceID is called.
		*/
	virtual void Shutdown() = 0;
	
		/** Releases all cached service providers, thus freeing up memory.
			This is only called by the memory management code.
		*/
	virtual void ReleaseCachedServiceProviders() = 0;
		
		/** This method of registration is only for use in very obscure cases (like
			the error string table service, where we need the service provider to be available
			before all the plug-ins are installed into the object model, and therefore
			before Startup() has been called).
		*/
	virtual void RegisterServiceProvider(ClassID classID) = 0;

		/** The IStartupShutdownService::Startup() method of all service
			providers that support the kStartupShutdownServiceID is called.
		*/
	virtual void PerformStartupServices() = 0;

		/** Retrieves a list of all the registered service IDs with this instance of service registry.
		*/
	virtual void GetRegisteredServiceIDs(K2Vector<ServiceID>& services) const= 0;

	//@}-----------------------------------------------------------------------------

};

#endif
