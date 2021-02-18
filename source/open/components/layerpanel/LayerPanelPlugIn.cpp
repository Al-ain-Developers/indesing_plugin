//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelPlugIn.cpp $
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
//  Plug-in code for Layers Panel.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "PlugIn.h"
#include "DebuggingLayers.h"


static PlugIn gPlugIn;


// This is the main entry point from the application to the plug-in.
// The application calls this function when the plug-in is installed 
// or loaded. This function is called by name, so it must be called 
// GetPlugIn, and defined as C linkage.
IPlugIn *GetPlugIn()
{
	return &gPlugIn;
}

//////////////////////////////////////////////////////////////////
//				Test Menu
//////////////////////////////////////////////////////////////////

#ifdef DEBUG
#include "TestMenuComponent.h"
#include "LayerPanelID.h"

class LayerTestMenu : public TestMenuComponent {
public:
	LayerTestMenu(IPMUnknown *boss);
};


CREATE_PERSIST_PMINTERFACE(LayerTestMenu, kLayerTestMenuImpl)

LayerTestMenu::LayerTestMenu(IPMUnknown *boss) :
	TestMenuComponent(boss)
{
	AddTestMenu("Layers", "Iterate Page Items", IteratePageItems, kAlwaysEnabled,kFalse/* not obsolete */);
	AddTestMenu("Layers", "Iterate Spread", IterateSpread, kAlwaysEnabled,kFalse/* not obsolete */);
	AddTestMenu("Layers", "Create Non-UI Layer", CreateNonUILayer, kAlwaysEnabled,kFalse/* not obsolete */);
	AddTestMenu("Layers", "Create Non-Expendable Layer", CreateNonExpendableLayer, kAlwaysEnabled,kFalse/* not obsolete */);
	AddTestMenu("Layers", "Create Non-UI Non-Expendable Layer", CreateNonUINonExpendableLayer, kAlwaysEnabled,kFalse/* not obsolete */);
	AddTestMenu("Layers", "Trace Layer List", TraceLayerList, kAlwaysEnabled,kFalse/* not obsolete */);
}

#endif




