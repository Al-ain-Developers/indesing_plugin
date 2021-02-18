//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtServiceProvider.cpp $
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

// General includes:
#include "CServiceProvider.h"
#include "K2Vector.h"
#include "DocumentID.h"
#include "PDFID.h"
#include "DocFrameworkID.h"

// Project includes:
#include "CusCondTxtID.h"

class CusCondTxtServiceProvider : public CServiceProvider
{
	public:

		/**
			Constructor initializes a list of service IDs, one for each file action 
			signal that CusCondTxtResponder will handle.
			@param boss interface ptr from boss object on which interface is aggregated.
		*/
		CusCondTxtServiceProvider(IPMUnknown* boss);
		
		/**
			Destructor.  
		*/
		virtual	~CusCondTxtServiceProvider();

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
			CusCondTxtServiceProvider registers to handle.
		*/
		virtual void GetServiceIDs(K2Vector<ServiceID>& serviceIDs);

	private:

		K2Vector<ServiceID> fSupportedServiceIDs;
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusCondTxtServiceProvider, kCusCondTxtServiceProviderImpl)


/* CusCondTxtServiceProvider Constructor
*/
CusCondTxtServiceProvider::CusCondTxtServiceProvider(IPMUnknown* boss)
	: CServiceProvider(boss)
{
	// Add the serviceIDs we want the associated responder to handle.
	fSupportedServiceIDs.clear();
	fSupportedServiceIDs.push_back(kBeforeExportSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterExportSignalResponderService);
	fSupportedServiceIDs.push_back(kFailedExportSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterNewDocSignalResponderService);
}

/* CusCondTxtServiceProvider Dtor
*/
CusCondTxtServiceProvider::~CusCondTxtServiceProvider()
{
}

/* GetName
*/
void CusCondTxtServiceProvider::GetName(PMString* pName)
{
	pName->SetKey("CustomConditionalText Responder Service");
}

/* GetServiceID
*/
ServiceID CusCondTxtServiceProvider::GetServiceID() 
{
	// Should never be called given that HasMultipleIDs() returns kTrue.
	return fSupportedServiceIDs[0];
}

/* IsDefaultServiceProvider
*/
bool16 CusCondTxtServiceProvider::IsDefaultServiceProvider()
{
	return kFalse;
}

/* GetInstantiationPolicy
*/
IK2ServiceProvider::InstancePerX CusCondTxtServiceProvider::GetInstantiationPolicy()
{
	return IK2ServiceProvider::kInstancePerSession;
}

/* HasMultipleIDs
*/
bool16 CusCondTxtServiceProvider::HasMultipleIDs() const
{
	return kTrue;
}

/* GetServiceIDs
*/
void CusCondTxtServiceProvider::GetServiceIDs(K2Vector<ServiceID>& serviceIDs)
{
	// Append a service IDs for each service provided.
	std::copy(fSupportedServiceIDs.begin(), fSupportedServiceIDs.end(), std::back_inserter(serviceIDs));
}


// End, CusCondTxtServiceProvider.cpp.



