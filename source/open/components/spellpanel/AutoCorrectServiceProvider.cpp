//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectServiceProvider.cpp $
//  
//  Owner: Heath Horton
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
//  
//  Proj:	Spelling Panel.µ
//  
//========================================================================================

#include "VCPlugInHeaders.h"		// must be the first header file to include

#include "IObserver.h"

#include "CServiceProvider.h"
#include "SpellPanelID.h"
#include "ILayoutUIUtils.h"
#include "Trace.h"

//----------------------------------------------------------------------------------------
// Class AutoCorrectServiceProvider
//----------------------------------------------------------------------------------------
class AutoCorrectServiceProvider : public CServiceProvider
{
public:
    AutoCorrectServiceProvider(IPMUnknown * boss);

	virtual	void 		GetName(PMString * pName);
    virtual	ServiceID 	GetServiceID();
	virtual	bool16 		IsDefaultServiceProvider();
	virtual	IK2ServiceProvider::InstancePerX GetInstantiationPolicy();
};

CREATE_PMINTERFACE(AutoCorrectServiceProvider, kAutoCorrectServiceProviderImpl)


AutoCorrectServiceProvider::AutoCorrectServiceProvider(IPMUnknown *boss) :
   CServiceProvider(boss)
{}

IK2ServiceProvider::InstancePerX AutoCorrectServiceProvider::GetInstantiationPolicy()
{
   return IK2ServiceProvider::kInstancePerSessionPreload;
}

bool16 AutoCorrectServiceProvider::IsDefaultServiceProvider()
{
   return kFalse;
}

void AutoCorrectServiceProvider::GetName(PMString* pName)
{
   pName->SetKey("AutoCorrectStartupShutdownService");
}

ServiceID AutoCorrectServiceProvider::GetServiceID()
{
   return kAppLazyStartupShutdownService;
}

