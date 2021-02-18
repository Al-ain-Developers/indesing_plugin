//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPageItemPencilEH.cpp $
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
//  Implementation of event handler that detects drag operations
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActionManager.h"
#include "IApplication.h"
#include "ITriStateControlData.h"
#include "IDragDropSource.h"
#include "IEvent.h"
#include "IDragDropController.h"
#include "IMenuManager.h"
#include "IPageItemLockFacade.h"

#include "CPMUnknown.h"
#include "EventUtilities.h"
#include "LayerPanelUtils.h"
#include "LayerTreeUIDNodeID.h"
#include "UIDList.h"
#include "LayerPanelID.h"
#include "Utils.h"

#include "DVControlEventHandler.h"

class LayerPageItemPencilEH : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;
	public:
						LayerPageItemPencilEH(IPMUnknown *boss);
		virtual 		~LayerPageItemPencilEH();
			
		virtual bool16 	LButtonDn(IEvent* e); 
		virtual bool16	RButtonDn(IEvent* e);
};

//========================================================================
// Class LayerPageItemPencilEH
//========================================================================
CREATE_PMINTERFACE(LayerPageItemPencilEH, kLayerPageItemPencilEHImpl)

LayerPageItemPencilEH::LayerPageItemPencilEH(IPMUnknown *boss) :
	DVControlEventHandler(boss)
{
}

LayerPageItemPencilEH::~LayerPageItemPencilEH()
{
}
	

//--------------------------------------------------------------------------------------
// LButtonDn
//--------------------------------------------------------------------------------------
bool16 LayerPageItemPencilEH::LButtonDn(IEvent* e)
{
	InterfacePtr<IDragDropSource> dragSource(this, UseDefaultIID());
	if (dragSource && dragSource->WillDrag(e))
	{
		// Check to see if user is trying to start a drag
		bool16 isPatientUser;
		if (::IsUserStartingDrag(e, isPatientUser))
		{
			InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), UseDefaultIID());
			if (ddController)
			{
				ddController->StartDrag(dragSource, e);	
				return kTrue; // Make up for the fact that StartDrag will swallow the mouse up
			}
		}
	}
	
	NodeID treeNode(LayerPanelUtils::GetLayerTreeNodeFromSubwidget(this)); // this looks like it could be combined with the next line, but doing so creates a memory leak.
	TreeNodePtr<const LayerTreeUIDNodeID>	layerTreeNode(treeNode);

	if(e->OptionAltKeyDown() && !e->CmdKeyDown())
	{
		LayerPanelUtils::LockUnlockOtherPageItems(this,layerTreeNode->GetUID());
	}
	else
	{
		UIDList selectedPI = LayerPanelUtils::GetPageItemsSelectedInPanel(this,LayerPanelUtils::GetCurrentLayerPanelDB(this));
		if(e->CmdKeyDown() && selectedPI.Contains(layerTreeNode->GetUID()))
		{			
			// lock/unlock all the panel selected items
			if(Utils<Facade::IPageItemLockFacade>()->CanLock(selectedPI))
			{
				Utils<Facade::IPageItemLockFacade>()->LockPageItems(selectedPI);
			}
			else if(Utils<Facade::IPageItemLockFacade>()->CanUnlock(selectedPI))
			{
				Utils<Facade::IPageItemLockFacade>()->UnlockPageItems(selectedPI);
			}
		}
		else
		{	
			// just lock/unlock this one item.
			InterfacePtr<ITriStateControlData> triControlData(this, UseDefaultIID());
			if(!triControlData->IsSelected())
				triControlData->Select();
			else
				triControlData->Deselect();
		}
	}
	return kTrue;
}

bool16 LayerPageItemPencilEH::RButtonDn(IEvent* e)
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
	
	menuMgr->HandlePopupMenu("RtMenuLayerPanelLock", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
	
	return kTrue;
}

