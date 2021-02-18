//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstDocServiceProvider.cpp $
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
#include "PstLstID.h"


/** 
	registers as providing the service of responding to a group of document
	file action signals.  See the constructor code for a list of the
	signals this service responds.

	PstLstDocServiceProvider implements IK2ServiceProvider based on
	the partial implementation CServiceProvider.


	@ingroup persistentlist
	
*/
class PstLstDocServiceProvider : public CServiceProvider
{
	public:

		/**
			Constructor initializes a list of service IDs, one for each file action signal that DocWchResponder will handle.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PstLstDocServiceProvider(IPMUnknown* boss);
		
		/**
			Destructor.  
		*/
		virtual	~PstLstDocServiceProvider();

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
			IsDefaultServiceProvider tells the application this service is not the default service.
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
			@param serviceIDs List of IDs describing the services that PstLstDocServiceProvider registers to handle.
		*/
		virtual void GetServiceIDs(K2Vector<ServiceID>& serviceIDs);

	private:

		K2Vector<ServiceID> fSupportedServiceIDs;
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstDocServiceProvider, kPstLstDocServiceProviderImpl)


/* PstLstDocServiceProvider Constructor
*/
PstLstDocServiceProvider::PstLstDocServiceProvider(IPMUnknown* boss)
	: CServiceProvider(boss)
{
	// Add the service IDs we want the associated responder to handle.
	//  (See DocumentID.h)
	fSupportedServiceIDs.clear();
	
	//	NewDoc
	fSupportedServiceIDs.push_back(kAfterNewDocSignalResponderService);

	//	OpenDoc
	fSupportedServiceIDs.push_back(kDuringOpenDocSignalResponderService);

	//	CloseDoc
	fSupportedServiceIDs.push_back(kBeforeCloseDocSignalResponderService);

	if (fSupportedServiceIDs.size()<=0)
	{
		ASSERT_FAIL("PstLstDocServiceProvider must support at least 1 service ID");
		fSupportedServiceIDs.push_back(kInvalidService);
	}

}

/* PstLstDocServiceProvider Dtor
*/
PstLstDocServiceProvider::~PstLstDocServiceProvider()
{
}

/* PstLstDocServiceProvider::GetName
*/
void PstLstDocServiceProvider::GetName(PMString* pName)
{
	pName->SetKey("PstLst Responder Service");
}

/* PstLstDocServiceProvider::GetServiceID
*/
ServiceID PstLstDocServiceProvider::GetServiceID() 
{
	// Should never be called given that HasMultipleIDs() returns kTrue.
	return fSupportedServiceIDs[0];
}

/* PstLstDocServiceProvider::IsDefaultServiceProvider
*/
bool16 PstLstDocServiceProvider::IsDefaultServiceProvider()
{
	return kFalse;
}

/* PstLstDocServiceProvider::GetInstantiationPolicy
*/
IK2ServiceProvider::InstancePerX PstLstDocServiceProvider::GetInstantiationPolicy()
{
	return IK2ServiceProvider::kInstancePerSession;
}

/* PstLstDocServiceProvider::HasMultipleIDs
*/
bool16 PstLstDocServiceProvider::HasMultipleIDs() const
{
	return kTrue;
}

/* PstLstDocServiceProvider::GetServiceIDs
*/
void PstLstDocServiceProvider::GetServiceIDs(K2Vector<ServiceID>& serviceIDs)
{
	// Append a service IDs for each service provided. 
	for (int32 i = 0; i<fSupportedServiceIDs.size(); i++)
		serviceIDs.push_back(fSupportedServiceIDs[i]);

}


// End, PstLstDocServiceProvider.cpp.



