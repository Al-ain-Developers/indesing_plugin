//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/docwatch/DocWchServiceProvider.cpp $
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
#include "DocWchID.h"


/** DocWchServiceProvider
	registers as providing the service of responding to a group of document
	file action signals.  See the constructor code for a list of the
	signals this service responds to.

	DocWchServiceProvider implements IK2ServiceProvider based on
	the partial implementation CServiceProvider.


	@ingroup docwatch
	
*/
class DocWchServiceProvider : public CServiceProvider
{
	public:

		/**
			Constructor initializes a list of service IDs, one for each file action 
			signal that DocWchResponder will handle.
			@param boss interface ptr from boss object on which interface is aggregated.
		*/
		DocWchServiceProvider(IPMUnknown* boss);
		
		/**
			Destructor.  
		*/
		virtual	~DocWchServiceProvider();

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
			DocWchServiceProvider registers to handle.
		*/
		virtual void GetServiceIDs(K2Vector<ServiceID>& serviceIDs);

	private:

		K2Vector<ServiceID> fSupportedServiceIDs;
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(DocWchServiceProvider, kDocWchServiceProviderImpl)


/* DocWchActionComponent Constructor
*/
DocWchServiceProvider::DocWchServiceProvider(IPMUnknown* boss)
	: CServiceProvider(boss)
{
	// Add the serviceIDs we want the associated responder to handle.
	// (See DocumentID.h)
	fSupportedServiceIDs.clear();
	
	//	NewDoc
	fSupportedServiceIDs.push_back(kBeforeNewDocSignalResponderService);
	fSupportedServiceIDs.push_back(kDuringNewDocSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterNewDocSignalResponderService);

	//	OpenDoc
	fSupportedServiceIDs.push_back(kBeforeOpenDocSignalResponderService);
	fSupportedServiceIDs.push_back(kDuringOpenDocSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterOpenDocSignalResponderService);

	//	SaveDoc
	fSupportedServiceIDs.push_back(kBeforeSaveDocSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterSaveDocSignalResponderService);

	//	SaveAsDoc
	fSupportedServiceIDs.push_back(kBeforeSaveAsDocSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterSaveAsDocSignalResponderService);

	//	SaveACopyDoc
	fSupportedServiceIDs.push_back(kBeforeSaveACopyDocSignalResponderService);
	fSupportedServiceIDs.push_back(kDuringSaveACopyDocSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterSaveACopyDocSignalResponderService);

	//	RevertDoc
	fSupportedServiceIDs.push_back(kBeforeRevertDocSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterRevertDocSignalResponderService);

	//	CloseDoc
	fSupportedServiceIDs.push_back(kBeforeCloseDocSignalResponderService);
	fSupportedServiceIDs.push_back(kAfterCloseDocSignalResponderService);

	if (fSupportedServiceIDs.size()<=0)
	{
		ASSERT_FAIL("DocWchServiceProvider must support at least 1 service ID");
		fSupportedServiceIDs.push_back(kInvalidService);
	}

}

/* DocWchActionComponent Dtor
*/
DocWchServiceProvider::~DocWchServiceProvider()
{
}

/* GetName
*/
void DocWchServiceProvider::GetName(PMString* pName)
{
	pName->SetKey("DocWatch Responder Service");
}

/* GetServiceID
*/
ServiceID DocWchServiceProvider::GetServiceID() 
{
	// Should never be called given that HasMultipleIDs() returns kTrue.
	return fSupportedServiceIDs[0];
}

/* IsDefaultServiceProvider
*/
bool16 DocWchServiceProvider::IsDefaultServiceProvider()
{
	return kFalse;
}

/* GetInstantiationPolicy
*/
IK2ServiceProvider::InstancePerX DocWchServiceProvider::GetInstantiationPolicy()
{
	return IK2ServiceProvider::kInstancePerSession;
}

/* HasMultipleIDs
*/
bool16 DocWchServiceProvider::HasMultipleIDs() const
{
	return kTrue;
}

/* GetServiceIDs
*/
void DocWchServiceProvider::GetServiceIDs(K2Vector<ServiceID>& serviceIDs)
{
	// Append a service IDs for each service provided. 
	for (int32 i = 0; i<fSupportedServiceIDs.size(); i++)
		serviceIDs.push_back(fSupportedServiceIDs[i]);

}


// End, DocWchServiceProvider.cpp.



