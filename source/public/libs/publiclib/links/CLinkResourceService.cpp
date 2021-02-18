//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/links/CLinkResourceService.cpp $
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
//========================================================================================

#include "VCPublicHeaders.h"
#include "CLinkResourceService.h"

#include "LinksID.h"
#include "ShuksanID.h"

// see  .../source/components/utilities/plugin/PublicImpl.cpp
//CREATE_PMINTERFACE(CLinkResourceService, kLinkResourceServiceImpl)


//========================================================================================
//
// CLinkResourceService Public Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
CLinkResourceService::CLinkResourceService(IPMUnknown* boss)
: inherited(boss)
{
}

//========================================================================================
// Destructor
//========================================================================================
CLinkResourceService::~CLinkResourceService()
{
}

//========================================================================================
// CLinkResourceService::GetName
//========================================================================================
void CLinkResourceService::GetName(PMString* pName)
{
	ASSERT_UNIMPLEMENTED();
}

//========================================================================================
// CLinkResourceService::GetServiceID
//========================================================================================
ServiceID CLinkResourceService::GetServiceID()
{
	ASSERT_UNIMPLEMENTED();
	return kInvalidService;
}

//========================================================================================
// CLinkResourceService::IsDefaultServiceProvider
//========================================================================================
bool16 CLinkResourceService::IsDefaultServiceProvider()
{
	return kFalse;
}

//========================================================================================
// CLinkResourceService::GetInstantiationPolicy
//========================================================================================
IK2ServiceProvider::InstancePerX CLinkResourceService::GetInstantiationPolicy()
{
	return kInstancePerSession;
}

//========================================================================================
// CLinkResourceService::HasMultipleIDs
//========================================================================================
bool16 CLinkResourceService::HasMultipleIDs() const
{
	return kTrue;
}

//========================================================================================
// CLinkResourceService::GetServiceIDs
//========================================================================================
void CLinkResourceService::GetServiceIDs(K2Vector<ServiceID>& serviceIDs)
{
	serviceIDs.push_back(kLinkResourceService);
	serviceIDs.push_back(kAsyncWorkProcessorFactoryService);
}

IPlugIn::ThreadingPolicy CLinkResourceService::GetThreadingPolicy() const
{
	/// sbalensi 07-25-2008: Changing this in attempt to enable use of links in background
	//	return IPlugIn::kUnknownThreadingPolicy;
	return IPlugIn::kMultipleThreads;
}
