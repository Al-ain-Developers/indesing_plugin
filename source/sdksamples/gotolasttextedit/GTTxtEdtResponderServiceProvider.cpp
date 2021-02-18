//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtResponderServiceProvider.cpp $
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

// Implementation includes:
#include "CServiceProvider.h"
#include "K2Vector.h"
#include "DocumentID.h"
#include "GTTxtEdtID.h"

#include "TextID.h"

/** GTTxtEdtServiceProvider
registers as providing the service of responding to a group of document
file action and text story creation/deletion signals.  

See the constructor for the list of signals registered.

GTTxtEdtServiceProvider implements IK2ServiceProvider based on
the partial implementation CServiceProvider.

@ingroup gotolasttextedit
*/
class GTTxtEdtServiceProvider : public CServiceProvider
{
public:

	/**
	Constructor initializes a list of service IDs, one for after open and another for before close.
	@param boss interface ptr from boss object on which interface is aggregated.
	*/
	GTTxtEdtServiceProvider(IPMUnknown* boss);

	/**
	Destructor.  
	*/
	virtual	~GTTxtEdtServiceProvider();

	/**
	GetName initializes the name of the service.
	@param pName Ptr to PMString to receive the name.
	*/
	virtual void GetName(PMString* pName);

	/**
	GetServiceID returns a single service ID.  This is required, even though
	GetServiceIDs() will return the complete list initialized in the constructor.
	This method just returns the first service ID in the list.
	*/
	virtual ServiceID GetServiceID();

	/**
	IsDefaultServiceProvider tells application this service is not the default service.
	*/
	virtual bool16 IsDefaultServiceProvider();

	/**
	GetInstantiationPolicy returns a InstancePerX value to indicate that only
	one instance per session is needed.
	*/
	virtual InstancePerX GetInstantiationPolicy();

	/**
	HasMultipleIDs returns kTrue in order to force a call to GetServiceIDs().
	*/
	virtual bool16 HasMultipleIDs() const;

	/**
	GetServiceIDs returns a list of services provided.
	@param serviceIDs List of IDs describing the services that 
	GTTxtEdtServiceProvider registers to handle.
	*/
	virtual void GetServiceIDs(K2Vector<ServiceID>& serviceIDs);

private:

	K2Vector<ServiceID> fSupportedServiceIDs;
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(GTTxtEdtServiceProvider, kGTTxtEdtServiceProviderImpl)


/* GTTxtEdtServiceProvider Constructor
*/
GTTxtEdtServiceProvider::GTTxtEdtServiceProvider(IPMUnknown* boss)
: CServiceProvider(boss)
{
	// Add the serviceIDs we want the associated responder to handle.
	// (See DocumentID.h)
	fSupportedServiceIDs.clear();
	fSupportedServiceIDs.push_back(kAfterNewDocSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterOpenDocSignalResponderService);
	fSupportedServiceIDs.push_back(kBeforeCloseDocSignalResponderService);
	fSupportedServiceIDs.push_back(kNewStorySignalResponderService);
	fSupportedServiceIDs.push_back(kDeleteStoryRespService);

	if (fSupportedServiceIDs.size()<=0)
	{
		ASSERT_FAIL("GTTxtEdtServiceProvider must support at least 1 service ID");
		fSupportedServiceIDs.push_back(kInvalidService);
	}

}

/* GTTxtEdtServiceProvider Dtor
*/
GTTxtEdtServiceProvider::~GTTxtEdtServiceProvider()
{
}

/* GetName
*/
void GTTxtEdtServiceProvider::GetName(PMString* pName)
{
	pName->SetCString("GTTxtEdt Responder Service");
}

/* GetServiceID
*/
ServiceID GTTxtEdtServiceProvider::GetServiceID() 
{
	// Should never be called given that HasMultipleIDs() returns kTrue.
	ASSERT_FAIL("GTTxtEdtServiceProvider::GetServiceID - should not be called");
	return fSupportedServiceIDs[0];
}

/* IsDefaultServiceProvider
*/
bool16 GTTxtEdtServiceProvider::IsDefaultServiceProvider()
{
	return kFalse;
}

/* GetInstantiationPolicy
*/
IK2ServiceProvider::InstancePerX GTTxtEdtServiceProvider::GetInstantiationPolicy()
{
	return IK2ServiceProvider::kInstancePerSessionNoPurge;
}

/* HasMultipleIDs
*/
bool16 GTTxtEdtServiceProvider::HasMultipleIDs() const
{
	return kTrue;
}

/* GetServiceIDs
*/
void GTTxtEdtServiceProvider::GetServiceIDs(K2Vector<ServiceID>& serviceIDs)
{
	// Append a service IDs for each service provided. 
	for (int32 i = 0; i<fSupportedServiceIDs.size(); i++)
		serviceIDs.push_back(fSupportedServiceIDs[i]);

}


// End, GTTxtEdtServiceProvider.cpp.
