//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/aem/AEMUIStartupShutdown.cpp $
//  
//  Owner: Swati Garg
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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

// Interfaces
#include "ICSXSPlugPlugStartupShutdownService.h"
#include "IAEMExtensionEventsWrapper.h"
#include "IAEMLinkUtils.h"

#include "AdobeMenuPositions.h"
#include "IApplication.h"
#include "IActionManager.h"
#include "IMenuManager.h"

class AEMUIStartupShutdown : public CPMUnknown<ICSXSPlugPlugStartupShutdownService>
{
public:
	typedef CPMUnknown<ICSXSPlugPlugStartupShutdownService> inherited;
	AEMUIStartupShutdown(IPMUnknown* boss) ;
	~AEMUIStartupShutdown();
	virtual void Startup();
	virtual void Shutdown();
};

CREATE_PMINTERFACE(AEMUIStartupShutdown, kAEMUIStartupShutdownImpl)

//========================================================================================
// AEMUIStartupShutdown::Constructor
//========================================================================================
AEMUIStartupShutdown::AEMUIStartupShutdown( IPMUnknown* boss ) : inherited( boss )
{
}

//========================================================================================
// AEMUIStartupShutdown::Destructor
//========================================================================================
AEMUIStartupShutdown::~AEMUIStartupShutdown()
{

}

//========================================================================================
// AEMUIStartupShutdown::Startup
//========================================================================================
void AEMUIStartupShutdown::Startup()
{
	InterfacePtr<IAEMExtensionEventsWrapper> aemEventsCommunicator(GetExecutionContextSession(), UseDefaultIID());
	aemEventsCommunicator->AddAEMEventListeners();
    
    bool16 addAALToMenuItem = Utils<IAEMLinkUtils>()->ShouldShowAALRelinkAction();
    
    InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
    InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
    InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
    
    if (addAALToMenuItem)
    {
        // Remove the menu item, if it is already present
        menuMgr->RemoveMenuItem("#LinksUIPanelMenu", kLinksUIRelinkToAALAssetActionID);
        // Then, add it once
        menuMgr->AddMenuItem(kLinksUIRelinkToAALAssetActionID, "#LinksUIPanelMenu", kRelinkAALAssetMenuPosition, kFalse);
    }
    else
    {
        menuMgr->RemoveMenuItem("#LinksUIPanelMenu", kLinksUIRelinkToAALAssetActionID);
    }
}

//========================================================================================
// AEMUIStartupShutdown::Shutdown
//========================================================================================
void AEMUIStartupShutdown::Shutdown()
{
	InterfacePtr<IAEMExtensionEventsWrapper> aemEventsCommunicator(GetExecutionContextSession(), UseDefaultIID());
	aemEventsCommunicator->RemoveAEMEventListeners();
}
