//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IK2ServiceMgr.h $
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
#ifndef __IK2ServiceMgr__
#define __IK2ServiceMgr__

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IK2ServiceProvider;

/**	Service manager interface. This interface maintains a list of providers for one kind of service(one ServiceID). The Service Registry maintains a list of service managers, one
	for each service it knows about. 
	@see IK2ServiceRegistry
	@see IK2ServiceProvider
	@ingroup arch_db
*/
class IK2ServiceMgr : public IPMUnknown
{
public:
	/** 	Called when the Service Registry is shutdown, to force all service providers to be released. Not done in ~ServiceMgr because the call to the destructor is delayed until the database
		is deleted because ServiceMgr is persistent and goes to the instance cache.
	*/
	virtual void Shutdown() = 0;
	
	/**	Instantiation enum. Determines how long this service manager will hold on to it's service provider bosses. Really only important if the service provider has state that you care about preserving from
		one access to the next. */
	typedef enum 
	{ 
		/** kInstancePerSession - one instance per session. The first time (per application run) a service provider boss is requested, it will be constructed. After that it is cached and the cached boss is returned. */
		kInstancePerSession, 
		/** kInstancePerUse - one instance per use. Every time a service provider boss is requested, it will be constructed. */
		kInstancePerUse, 
		/** kInstancePerSessionPreload - one instance per session. A startup time, the service provider bosses will be constructed. After that they are cached and the cached boss is returned. */
		kInstancePerSessionPreload
	 } InstancePerX;
	 
	 /** 	Internal use only. The service registry registers services that belong to this service manager. Just implement an IK2ServiceProvider and add it to your boss.
	 */
	virtual void RegisterServiceProvider(IK2ServiceProvider *provider, ClassID classID, InstancePerX instancePerX = kInstancePerSession, bool16 dontPurge = kFalse) = 0;

	/** Internal use only. true means ok to purge this. false means serviceMgr couldn't purge everything, so don't purge it.
	*/
	virtual bool16 ReleaseCachedServiceProviders() = 0; 

	/** Set the default service provider for this service
		@param classID The ClassID of the default service provider boss.
	*/
	virtual void SetDefaultServiceProvider(ClassID classID) = 0;

	/** Query for the default service provider. Caller must Release the returned pointer
	*/
	virtual IK2ServiceProvider * QueryDefaultServiceProvider() = 0;
	
	/** Get the ClassID of the default service provider boss
	*/
	virtual ClassID GetDefaultServiceProviderID() = 0;
	
	/**	Query the service provider with the requested ClassID. Caller must Release the returned pointer
	*/
	virtual IK2ServiceProvider * QueryServiceProviderByClassID(ClassID classID) = 0;
	
	/** Count service providers for this service
	*/
	virtual int32 GetServiceProviderCount() = 0;
	
	/**	Query the nth service provider for this service. Caller must Release the returned pointer
	*/
	virtual IK2ServiceProvider * QueryNthServiceProvider(int32 n) = 0;

	/** Get the ClassID of the nth service provider boss
	*/
	virtual ClassID GetNthServiceProviderID(int32 n) = 0;
	
	/** Get the index of the passed in service provider in the service provider list
		@param serviceProvider Pointer to the service provider you'd like the index of.
		@return index of service provider in list, or -1 if not found
	*/
	virtual int32 GetServiceProviderIndex(IK2ServiceProvider * serviceProvider) = 0;

	/** Get the index of the passed in service provider ClassID in the service provider list
		@param serviceProviderID The ClassID of the service provider boss you'd like the index of.
		@return index of service provider in list, or -1 if not found
	*/
	virtual int32 GetServiceProviderIndex(ClassID serviceProviderID) = 0;
};

#endif
