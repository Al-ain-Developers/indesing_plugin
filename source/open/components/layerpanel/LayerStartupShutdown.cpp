//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerStartupShutdown.cpp $
//  
//  Owner: Paul Sorrick
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
//  Purpose: Attaches/Detaches one LayerSelectionObserver at startup and shutdown. Uses
//  the new selection architecture and avoids having one observer for every
//  layout window.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IApplication.h"
#include "IObserver.h"
#include "IPMUnknown.h"
#include "ISession.h"
#include "IStartupShutdownService.h"

// ----- Includes -----

#include "HelperInterface.h"

// ----- ID.h files -----

#include "LayerPanelID.h"


class LayerStartupShutdown : public IStartupShutdownService
{
public:
	LayerStartupShutdown(IPMUnknown *boss);

	virtual void Startup();
	virtual void Shutdown();

DECLARE_HELPER_METHODS()
};

CREATE_PMINTERFACE(LayerStartupShutdown, kLayerStartupShutdownImpl)
DEFINE_HELPER_METHODS(LayerStartupShutdown)

LayerStartupShutdown::LayerStartupShutdown(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)
{
}

void LayerStartupShutdown::Startup()
{
	InterfacePtr<IObserver> layerObserver(GetExecutionContextSession(), IID_ILAYERSELECTIONOBSERVER);
	if (layerObserver)
		layerObserver->AutoAttach();
}

void LayerStartupShutdown::Shutdown()
{
	InterfacePtr<IObserver> layerObserver(GetExecutionContextSession(), IID_ILAYERSELECTIONOBSERVER);
	if (layerObserver)
		layerObserver->AutoDetach();
}
