//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagLoggerServiceProvider.cpp $
//  
//  Owner: Brendan O'Shea
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CServiceProvider.h"	

#include "DiagnosticLogID.h"

class DiagLoggerServiceProvider : public CServiceProvider
{
public:
	DiagLoggerServiceProvider(IPMUnknown *boss);
	virtual void GetName(PMString * pName) ; 
	virtual ServiceID GetServiceID() ; 
	virtual bool16 IsDefaultServiceProvider() ; 
	virtual InstancePerX GetInstantiationPolicy() ; 
	virtual IPlugIn::ThreadingPolicy GetThreadingPolicy() const 
			{ return IPlugIn::kMultipleThreads; }
};

CREATE_PMINTERFACE(DiagLoggerServiceProvider, kDiagLoggerServiceProviderImpl)

DiagLoggerServiceProvider::DiagLoggerServiceProvider(IPMUnknown *boss)
	: CServiceProvider(boss) 
{}

void DiagLoggerServiceProvider::GetName(PMString * pName) 
{
	pName->SetCString("");
}

ServiceID DiagLoggerServiceProvider::GetServiceID() 
{
	return kDiagnosticLoggerService;
}

bool16 DiagLoggerServiceProvider::IsDefaultServiceProvider() 
{
	return kFalse;
}

IK2ServiceProvider::InstancePerX DiagLoggerServiceProvider::GetInstantiationPolicy() 
{
	return IK2ServiceProvider::kInstancePerSession;
}
