//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/suppui/SuppUIQuickApplyFilterProvider.cpp $
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
#include "FindChangeID.h"
#include "CServiceProvider.h"

// Project includes:
#include "SuppUIID.h"
#include "SuppUISuppressedUI.h"

/** Implements the service provider that identifies a quick apply filter service.

	@ingroup suppui
*/
class  SuppUIQuickApplyFilterProvider : public CServiceProvider
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		SuppUIQuickApplyFilterProvider(IPMUnknown *boss) : CServiceProvider(boss)
			{}
		/**
			Initializes the name of the service.
			@param pName OUT Ptr to PMString to receive the name.
		*/
		virtual void GetName(PMString* pName);

		/**
			Returns a single service ID that identifies the service as a quick apply filter.
			@return the service ID (kQuickApplyFilterService)
		*/
		virtual ServiceID GetServiceID();

		/**
			Tells the application this service is not the default service.
			@return kFalse to indicate the service is not the default.
		*/
		virtual bool16 IsDefaultServiceProvider();
		
		/**
			Returns a InstancePerX value to indicate that only one instance per session is needed.
			@return the instantiation policy.
		*/
		virtual InstancePerX GetInstantiationPolicy();
};

CREATE_PMINTERFACE(SuppUIQuickApplyFilterProvider, kSuppUIQuickApplyFilterProviderImpl)

/*
*/
void SuppUIQuickApplyFilterProvider::GetName(PMString *pName)
{
	pName->SetKey("SuppUI Quick Apply Filter Provider");
}

/*
*/
bool16 SuppUIQuickApplyFilterProvider::IsDefaultServiceProvider()
{
	return kFalse;
}

/*
*/
ServiceID SuppUIQuickApplyFilterProvider::GetServiceID()
{
	return kQuickApplyFilterService;
}


/*
*/
IK2ServiceProvider::InstancePerX SuppUIQuickApplyFilterProvider::GetInstantiationPolicy()
{
	return IK2ServiceProvider::kInstancePerSession;
}


