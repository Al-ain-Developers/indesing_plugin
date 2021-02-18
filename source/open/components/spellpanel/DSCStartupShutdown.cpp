//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/DSCStartupShutdown.cpp $
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

#include "VCPlugInHeaders.h"		

#include "IObserver.h"
#include "IStartupShutdownService.h"

#include "HelperInterface.h"
#include "SpellPanelID.h"

#include "Trace.h"


class DynamicSpellCheckStartupShutdown : public IStartupShutdownService
{
public:
					DynamicSpellCheckStartupShutdown(IPMUnknown *boss);
					~DynamicSpellCheckStartupShutdown();
					
	virtual void 	Startup();
	virtual void 	Shutdown();

private:

	DECLARE_HELPER_METHODS()
};

CREATE_PMINTERFACE(DynamicSpellCheckStartupShutdown, kDynamicSpellCheckStartupShutdownImpl)
DEFINE_HELPER_METHODS(DynamicSpellCheckStartupShutdown)


DynamicSpellCheckStartupShutdown::DynamicSpellCheckStartupShutdown(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)

{
}


DynamicSpellCheckStartupShutdown::~DynamicSpellCheckStartupShutdown()
{
}

void DynamicSpellCheckStartupShutdown::Startup()
{
	InterfacePtr<IObserver> dscObserver(this, IID_IOBSERVER);
	if (dscObserver)
		dscObserver->AutoAttach();
}

void DynamicSpellCheckStartupShutdown::Shutdown()
{
	InterfacePtr<IObserver> dscObserver(this, IID_IOBSERVER);
	if (dscObserver)
		dscObserver->AutoDetach();
}
