//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerSubwidgetEH.cpp $
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
//  Implementation of event handler that handles name double clicks
//  to bring up the Layer Options dialog.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActionManager.h"
#include "IApplication.h"
#include "IDocumentLayer.h"
#include "IEvent.h"
#include "ILayerList.h"
#include "IMenuManager.h"
#include "IPanelControlData.h"
#include "ISession.h"

// ----- Utility files -----

#include "EventUtilities.h"
#include "LayerPanelUtils.h"
#include "IPalettePanelUtils.h"

// ----- ID.h files -----

#include "LayerPanelID.h"

#include "DVHostedWidgetEH.h"

class LayerSubwidgetEH : public DVHostedWidgetEH
{
	typedef DVHostedWidgetEH inherited;
	public:
						LayerSubwidgetEH(IPMUnknown *boss);
		virtual 		~LayerSubwidgetEH();
			
		virtual bool16 LButtonDn(IEvent* e); 
		virtual bool16 RButtonDn(IEvent* e);
		virtual bool16 ButtonDblClk(IEvent* e);
		
	private:
		DECLARE_HELPER_METHODS()
};

//========================================================================
// Class LayerSubwidgetEH
//========================================================================
CREATE_PMINTERFACE(LayerSubwidgetEH, kLayerSubwidgetEHImpl)
DEFINE_HELPER_METHODS(LayerSubwidgetEH)

LayerSubwidgetEH::LayerSubwidgetEH(IPMUnknown *boss) :
	inherited(boss),
	HELPER_METHODS_INIT(boss)
{
}

LayerSubwidgetEH::~LayerSubwidgetEH()
{
}
	

//---------------------------------------------------------------
// LayerSubwidgetEH::LButtonDn
//---------------------------------------------------------------

bool16 LayerSubwidgetEH::LButtonDn(IEvent* e) 
{
	bool16 handled = kFalse;

	// Shortcut to select the items on the clicked layer is Option + click
	// Allow shortcut for list focus (Option + Command + click) to pass through.
	if (e->OptionAltKeyDown() && !e->CmdKeyDown())
	{
		handled = kTrue;

		// With shift key down, extend selection, otherwise replace it.
		LayerPanelUtils::DoSelectLayer(this, e->ShiftKeyDown(),e->OptionAltKeyDown());	
	}
	
	e->SetUI_DoEventHandledState(IEvent::kDontCall);  //this allows the event to reach the parent widget (skipping the ui_node's own event handling code)
	return kFalse;
}

//---------------------------------------------------------------
// LayerSubwidgetEH::RButtonDn
//---------------------------------------------------------------

bool16 LayerSubwidgetEH::RButtonDn(IEvent* e)
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
	
	menuMgr->HandlePopupMenu("RtMenuLayerPanelItem", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
	
	return kTrue;
}

//---------------------------------------------------------------
// LayerSubwidgetEH::ButtonDblClk
//---------------------------------------------------------------

bool16 LayerSubwidgetEH::ButtonDblClk(IEvent* ) 
{
	bool16 handled = kTrue;

	// Get the IPanelControlData for the layer panel itself, operate on selected layers
	InterfacePtr<IPanelControlData> layerPanelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kLayerParentWidgetId));
	LayerPanelUtils::InvokeLayerDialog(LayerPanelUtils::kLayerOptionsDialog, LayerPanelUtils::kAboveActive, layerPanelData, nil);

	return handled;
}
