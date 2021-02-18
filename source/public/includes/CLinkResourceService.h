//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CLinkResourceService.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  All link resource K2 service providers should use or inherit from this class.
//  
//========================================================================================

#pragma once
#ifndef __CLinkResourceService__
#define __CLinkResourceService__

// ----- Includes -----
#include "CPMUnknown.h"
#include "IK2ServiceProvider.h"


/**
 Implementation of IK2ServiceProvider for a multi-service link resource service provider. 
 This class can be utilized as the implementation of the IID_IK2SERVICEPROVIDER entry for
 all link resource service provider bosses.
 @see IK2ServiceProvider
 */
class PUBLIC_DECL CLinkResourceService : public CPMUnknown<IK2ServiceProvider>
{
public:
    typedef CPMUnknown<IK2ServiceProvider> inherited;

	CLinkResourceService(IPMUnknown* boss);
	virtual ~CLinkResourceService();

	/**
	 Returns the optional name of the service provider.\\
	 The service registry does not use this name in any way.
	 @param pName [OUT] Name of the service provider.
	 */ 
	virtual void GetName(PMString* pName);

	/**
	 Returns the service ID that the service provider implements.
	 @return kInvalidService by default.
	 */ 
	virtual ServiceID GetServiceID();

	/**
	 Returns whether the service is the default service provider.
	 @return kFalse by default.
	 */ 
	virtual bool16 IsDefaultServiceProvider();

	/**
	 Returns the instantiation policy used by the service.
	 @return kInstancePerSession by default.
	 */ 
	virtual InstancePerX GetInstantiationPolicy();

	/**
	 Returns whether the service provider supports multiple services.
	 @return kTrue by default.
	 */ 
	virtual bool16 HasMultipleIDs() const;

	/**
	 Returns the IDs of all the services suppported by the provider.
	 @param serviceIDs [OUT] IDs of all the services suppported by the provider.\\
							 By default, this provider supports the kLinkResourceService
							 and kAsyncWorkProcessorFactoryService services.
	 */ 
	virtual void GetServiceIDs(K2Vector<ServiceID>& serviceIDs);

	virtual IPlugIn::ThreadingPolicy GetThreadingPolicy() const;
};

#endif // __CLinkResourceService__
