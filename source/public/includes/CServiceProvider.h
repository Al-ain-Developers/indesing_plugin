//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CServiceProvider.h $
//  
//  Owner: Tom Taylor
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
#ifndef __CServiceProvider__
#define __CServiceProvider__

#include "IK2ServiceProvider.h"
#include "HelperInterface.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/** Base class for service providers.
*/
class PUBLIC_DECL CServiceProvider : public IK2ServiceProvider
{
public:
	// ----- Initialization -----
	
						CServiceProvider(IPMUnknown *boss);
	virtual				~CServiceProvider();
	
	virtual void GetName(PMString * pName);
	
	virtual InstancePerX GetInstantiationPolicy();
	virtual bool16 IsDefaultServiceProvider();

	// Support for multiple Service ID's
	virtual bool16		HasMultipleIDs() const;
	virtual void		GetServiceIDs(K2Vector<ServiceID>& serviceIDs);

	/** By default the base class will return the threading policy of the plugin where the service provider is defined.
		Service providers can override this if they reside in a model plugin but want to operate only in the main thread.
	*/
	virtual IPlugIn::ThreadingPolicy GetThreadingPolicy() const;

protected:
	/** Helper function that initializes fThreadingPolicy with the threading policy of the specified interface
		(by default IID_IK2SERVICEPROVIDER but responders and other special providers can use the IIDs of their specific service)
	*/
	void InitThreadingPolicy(PMIID whichIID = IID_IK2SERVICEPROVIDER);

	IPlugIn::ThreadingPolicy	fThreadingPolicy;

DECLARE_HELPER_METHODS()
};

#ifdef PUBLIC_BUILD
#pragma export off
#endif

#endif
