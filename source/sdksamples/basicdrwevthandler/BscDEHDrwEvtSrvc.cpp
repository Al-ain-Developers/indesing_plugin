//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdrwevthandler/BscDEHDrwEvtSrvc.cpp $
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

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "CServiceProvider.h"	// for IK2ServiceProvider
#include "GraphicsID.h"

// Project includes:
#include "BscDEHID.h"


/** BscDEHDrwEvtSrvc
	Registers this plug-in with the application as providing a draw event handling service.

	BscDEHDrwEvtSrvc implements IK2ServiceProvider based on
	the partial implementation CServiceProvider.


	
	@ingroup basicdrwevthandler
*/
class BscDEHDrwEvtSrvc : public CServiceProvider
{
public:
	/**
		Constructor initializes a list of service IDs, one for each file action signal that DocWchResponder will handle.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BscDEHDrwEvtSrvc(IPMUnknown* boss);
	/**
		Destructor.  
	*/
	virtual ~BscDEHDrwEvtSrvc();
	/**
		GetServiceID returns a single service ID.  This is required, even though
		GetServiceIDs() will return the complete list initialized in the constructor.
		This method just returns the first service ID in the list.
	*/
	virtual ServiceID GetServiceID() ; 
	/**
		IsDefaultServiceProvider tells the application this service is not the default service.
	*/
	virtual bool16 IsDefaultServiceProvider() ; 
	/**
		GetInstantiationPolicy returns a InstancePerX value to indicate that only
		one instance per session is needed.
	*/
	virtual InstancePerX GetInstantiationPolicy() ;
	/**
		GetName initializes the name of the service.
		@param pName Ptr to PMString to receive the name.
	*/
	virtual void GetName(PMString* pName);


	virtual IPlugIn::ThreadingPolicy GetThreadingPolicy() const 
		{ return IPlugIn::kMainThreadOnly; }
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscDEHDrwEvtSrvc, kBscDEHDrwEvtSrvcImpl)

/* BscDEHDrwEvtSrvc Constructor
*/
BscDEHDrwEvtSrvc::BscDEHDrwEvtSrvc(IPMUnknown* boss)
	: CServiceProvider(boss) 
{
}

/* BscDEHDrwEvtSrvc Destructor
*/
BscDEHDrwEvtSrvc::~BscDEHDrwEvtSrvc()
{
}

/* GetServiceID
*/
ServiceID BscDEHDrwEvtSrvc::GetServiceID() 
{
	return kDrawEventService;
}

/* IsDefaultServiceProvider
*/
bool16 BscDEHDrwEvtSrvc::IsDefaultServiceProvider() 
{
	return kFalse;
}

/* GetInstantiationPolicy
*/
IK2ServiceProvider::InstancePerX BscDEHDrwEvtSrvc::GetInstantiationPolicy() 
{
	return IK2ServiceProvider::kInstancePerSession;
}

/* GetName
*/
void BscDEHDrwEvtSrvc::GetName(PMString* pName)
{
	pName->SetKey("BscDEHDrwEvtSrvc\0");

}


// End, BscDEHDrwEvtSrvc.cpp.






