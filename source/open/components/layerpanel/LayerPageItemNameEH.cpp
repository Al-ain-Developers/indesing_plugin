//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPageItemNameEH.cpp $
//  
//  Owner: lance bushore
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
#include "IEvent.h"
#include "IApplication.h"
#include "IMenuManager.h"
#include "IActionManager.h"

// ----- Includes -----

#include "InLineEditClickPauseClickEH.h"
#include "LayerPanelUtils.h"

// ----- ID.h files -----

#include "LayerPanelID.h"


#define INHERITED InLineEditClickPauseClickEH

class LayerPageItemNameEH : public InLineEditClickPauseClickEH
{			
	public:
						LayerPageItemNameEH(IPMUnknown *boss);
		virtual 		~LayerPageItemNameEH();
			
		virtual bool16 LButtonDn(IEvent* e); 
		virtual bool16 RButtonDn(IEvent* e); 
		
	private:
		DECLARE_HELPER_METHODS()
};

//========================================================================
// Class LayerPageItemNameEH
//========================================================================
CREATE_PMINTERFACE(LayerPageItemNameEH, kLayerPageItemNameEHImpl)
DEFINE_HELPER_METHODS(LayerPageItemNameEH)

LayerPageItemNameEH::LayerPageItemNameEH(IPMUnknown *boss) :
	INHERITED(boss),
	HELPER_METHODS_INIT(boss)
{
}

LayerPageItemNameEH::~LayerPageItemNameEH()
{
}
	

//---------------------------------------------------------------
// LayerPageItemNameEH::LButtonDn
//---------------------------------------------------------------

bool16 LayerPageItemNameEH::LButtonDn(IEvent* e) 
{
	// Shortcut to select the items on the clicked layer is Option + click
	// Allow shortcut for list focus (Option + Command + click) to pass through.
	if (e->OptionAltKeyDown() && !e->CmdKeyDown())
	{
		if(LayerPanelUtils::SelectAssociatedItemsInLayout(this,e->ShiftKeyDown(),false,e->CmdKeyDown()))
			return kTrue;
	}
	return INHERITED::LButtonDn(e);
}

bool16 LayerPageItemNameEH::RButtonDn(IEvent* e)
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
	
	menuMgr->HandlePopupMenu("RtMenuLayerPanelPageItem", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
	
	return kTrue;
}


