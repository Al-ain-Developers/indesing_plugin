//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypServiceProvider.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"    

// Interface includes:
#include "ILinguisticServiceData.h"

// General includes:
#include "CServiceProvider.h"
#include "PMString.h"
#include "Trace.h"

// Project includes:
#include "HypID.h"
#include "HypAdapter.h"

/** Identifies the linguistic hyphenation service this plug-in
	provides to the application.

	@ingroup hyphenator
 */
class HypServiceProvider : public CServiceProvider
{
	public:
		/** Constructor.
		 */
		HypServiceProvider(IPMUnknown* boss);

		/** Destructor
		*/
		virtual ~HypServiceProvider();

		/** Gets the service provider's name, if there is one. 
		*/
		virtual void GetName(PMString* pName);

		/** Gets the service provider's ID.
		*/
		virtual ServiceID GetServiceID();

		/** Returns kTrue if this is the default service provider, otherwise kFalse. 
		*/
		virtual bool16 IsDefaultServiceProvider();

		/** A service provider can choose to have one instance that is shared by
		 all requests for that service providers (this is the most common case - kInstancePerSession),
		 or a service provider may choose to have a unique instance created on
		 each request for the service provider (kInstancePerUse).
		 kInstancePerSessionPreload will cause a service provider to be constructed
		 and cached at application startup.  Furthermore, a "preload" service
		 provider will not be unloaded until application shutdown.
		 Note:  Since "preload" service providers are never unloaded, the incur
		 the memory overhead for the service and cause the plug-in that contains
		 the service to not be unloaded.  Therefore "preload" service providers should
		 be avoided, when possible. 

		 See IK2ServiceProvider for more details.
		*/
		virtual InstancePerX GetInstantiationPolicy();

		virtual IPlugIn::ThreadingPolicy GetThreadingPolicy() const
			{return IPlugIn::kMultipleThreads;}
	private:
		virtual void setServiceName();
		virtual void setDictionaryFolderPath();
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(HypServiceProvider, kHypServiceProviderImpl)

/*
*/
HypServiceProvider::HypServiceProvider(IPMUnknown* boss) :
	CServiceProvider(boss)
{
	TRACEFLOW("Hyphenator", "HypServiceProvider::HypServiceProvider()-->In\n");
	this->setServiceName();
	this->setDictionaryFolderPath();
	TRACEFLOW("Hyphenator", "HypServiceProvider::HypServiceProvider()-->Out\n");
}

/*
*/
HypServiceProvider::~HypServiceProvider()
{
	TRACEFLOW("Hyphenator", "HypServiceProvider::~HypServiceProvider()\n");
}

/*
*/
void HypServiceProvider::GetName(PMString* pName)
{
	TRACEFLOW("Hyphenator", "HypServiceProvider::GetName()\n");
	do {
		ASSERT(pName != nil);
		if (pName == nil) {
			break;
		}
		InterfacePtr<ILinguisticServiceData> linguisticServiceData(this, UseDefaultIID());
		ASSERT(linguisticServiceData != nil);
		if (linguisticServiceData == nil) {
			break;

		}
		*pName = linguisticServiceData->GetServiceName();
	} while(false);
}

/*
*/
ServiceID HypServiceProvider::GetServiceID()
{
	TRACEFLOW("Hyphenator", "HypServiceProvider::GetServiceID()\n");
	return(kLinguisticService);
}

/*
*/
bool16 HypServiceProvider::IsDefaultServiceProvider()
{
	TRACEFLOW("Hyphenator", "HypServiceProvider::IsDefaultServiceProvider()\n");
	// Not the default
	return(kFalse);
}

/*
*/
IK2ServiceProvider::InstancePerX HypServiceProvider::GetInstantiationPolicy()
{
	TRACEFLOW("Hyphenator", "HypServiceProvider::GetInstantiationPolicy()\n");
	return(IK2ServiceProvider::kInstancePerSession);
}

/*
*/
void HypServiceProvider::setServiceName()
{
	const PMString serviceName(kHypLinguisticServiceName);
	InterfacePtr<ILinguisticServiceData> linguisticServiceData(this, UseDefaultIID());
	ASSERT(linguisticServiceData != nil);
	if (linguisticServiceData != nil) {
		linguisticServiceData->SetServiceName(serviceName);
	}
	TRACEFLOW("Hyphenator", "HypServiceProvider::setServiceName()=\"%s\"\n", serviceName.GetUTF8String().c_str());
}

/*
*/
void HypServiceProvider::setDictionaryFolderPath()
{
	// The path supplied by your adapter is kept by this hyphenation service
	// on the ILinguisticServiceData interface in the service registry.
	HypAdapter hypAdapter;
	const PMString dictionaryFolderPath = hypAdapter.GetDictionaryFolderPath();
	InterfacePtr<ILinguisticServiceData> linguisticServiceData(this, UseDefaultIID());
	ASSERT(linguisticServiceData != nil);
	if (linguisticServiceData != nil) {
		linguisticServiceData->SetPath(dictionaryFolderPath);
	}
	TRACEFLOW("Hyphenator", "HypServiceProvider::setDictionaryFolderPath()=\"%s\"\n", dictionaryFolderPath.GetUTF8String().c_str());
}

// End, HypServiceProvider.cpp