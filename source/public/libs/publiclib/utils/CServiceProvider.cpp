//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/utils/CServiceProvider.cpp $
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

#include "VCPublicHeaders.h"

#include "CServiceProvider.h"
#include "InterfaceInfo.h"
#include "IClassInfo.h"

DEFINE_HELPER_METHODS(CServiceProvider)

CServiceProvider::CServiceProvider(IPMUnknown *boss)
	: HELPER_METHODS_INIT(boss), fThreadingPolicy(IPlugIn::kUnknownThreadingPolicy)
{
	InitThreadingPolicy();
	ASSERT_MSG(fThreadingPolicy != IPlugIn::kUnknownThreadingPolicy, "CServiceProvider - Unknown threading policy!");
}

CServiceProvider::~CServiceProvider()
{
}

bool16 CServiceProvider::HasMultipleIDs() const
{
	return kFalse;
}

void CServiceProvider::GetServiceIDs(K2Vector<ServiceID>& serviceIDs)
{
	// does nothing
}

void  CServiceProvider::GetName(PMString * pName) 
{
}

IK2ServiceProvider::InstancePerX CServiceProvider::GetInstantiationPolicy() 
{ 
	return kInstancePerSession; 
}


bool16 CServiceProvider::IsDefaultServiceProvider() 
{ 
	return kFalse; 
}


IPlugIn::ThreadingPolicy CServiceProvider::GetThreadingPolicy() const
{
	return fThreadingPolicy;
}

void CServiceProvider::InitThreadingPolicy(PMIID whichIID)
{
	InterfacePtr<IControllingUnknown> control( this, UseDefaultIID());
	ASSERT(control);

	// Get the class info for this boss and get the interface info for our PMIID
	InterfacePtr<IClassInfo> clsInfo(GetObjectModelInstance()->QueryClassInfo(control->GetClass()));
	const InterfaceInfo* info = clsInfo->FindInterfaceInfo(whichIID).first;
	ASSERT(info);
	if (info)
	{
		// Store the threading policy
		fThreadingPolicy = info->GetThreadingPolicy();
	}
}
