//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPencilDragDropSourceEH.cpp $
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
//  Implementation of event handler that detects drag operations
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActionManager.h"
#include "IApplication.h"
#include "IBoolData.h"
#include "IDocumentLayer.h"
#include "IDragDropController.h"
#include "IDragDropSource.h"
#include "IEvent.h"
#include "ILayerList.h"
#include "IMenuManager.h"
#include "ISession.h"
#include "ITriStateControlData.h"
#include "ILayerUIUtils.h"

// ----- Includes -----

#include "CAlert.h"
#include "UIDList.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "EventUtilities.h"
#include "ILayerUtils.h"
#include "LayerPanelUtils.h"
#include "LayerTreeUIDNodeID.h"

// ----- ID.h files -----

#include "DragDropID.h"
#include "LayerPanelID.h"
#include "widgetid.h"

#include "DVControlEventHandler.h"

class LayerPencilDragDropSourceEH : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;
	public:
						LayerPencilDragDropSourceEH(IPMUnknown *boss);
		virtual 		~LayerPencilDragDropSourceEH();
			
		virtual bool16 	LButtonDn(IEvent* e); 
		virtual bool16 	LButtonUp(IEvent* e); 
		virtual bool16	RButtonDn(IEvent* e);
		
	private:
		DECLARE_HELPER_METHODS()
};

//========================================================================
// Class LayerPencilDragDropSourceEH
//========================================================================
CREATE_PMINTERFACE(LayerPencilDragDropSourceEH, kLayerPencilDragDropSourceEHImpl)
DEFINE_HELPER_METHODS(LayerPencilDragDropSourceEH)

LayerPencilDragDropSourceEH::LayerPencilDragDropSourceEH(IPMUnknown *boss) :
	inherited(boss),
	HELPER_METHODS_INIT(boss)
{
}

LayerPencilDragDropSourceEH::~LayerPencilDragDropSourceEH()
{
}
	

bool16 LayerPencilDragDropSourceEH::LButtonUp(IEvent* )
{
	return kTrue; // so it doesn't get handled as activating the layer
}

bool16 LayerPencilDragDropSourceEH::LButtonDn(IEvent* e)
{
	bool16 optionKeyDown = e->OptionAltKeyDown();
	bool16 cmdKeyDown = e->CmdKeyDown();

	InterfacePtr<IDragDropSource> dragSource(this, IID_IDRAGDROPSOURCE);
	if (dragSource && dragSource->WillDrag(e))
	{
		// Check to see if user is trying to start a drag
		bool16 isPatientUser;
		if (::IsUserStartingDrag(e, isPatientUser))
		{
			InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), IID_IDRAGDROPCONTROLLER);
			if (ddController)
			{
				ddController->StartDrag(dragSource, e);	
				return kTrue; // Make up for the fact that StartDrag will swallow the mouse up
			}
		}
		else if (!(optionKeyDown && cmdKeyDown))	// Allow shortcut for list focus (Option + Command + click) to pass through.
		{
			// Option + click is shortcut for Unlock All/Lock Others
			NodeID treeNode(LayerPanelUtils::GetLayerTreeNodeFromSubwidget(this));
			TreeNodePtr<const LayerTreeUIDNodeID>	layerTreeNode(treeNode);
			ASSERT_MSG(layerTreeNode->IsLayerEntry(),"Expected this to be a layer");
			IDataBase *db = LayerPanelUtils::GetCurrentLayerPanelDB(this);
			UIDList targetLayers(db);
			LayerPanelUtils::GetTargetLayers(targetLayers,this);
			InterfacePtr<const IDocumentLayer> clickedDocLayer(LayerPanelUtils::QueryLayerFromPanelWidget(this));

			if (optionKeyDown)
			{
				// Don't lock a layer holding a placegun-owned item (like a snippet)
				InterfacePtr<const ILayerList> layerList(::GetDataBase(clickedDocLayer),::GetDataBase(clickedDocLayer)->GetRootUID(),UseDefaultIID());
				int32 numLocked = Utils<ILayerUtils>()->CountLockedUILayers(layerList);
				int32 numLayers = Utils<ILayerUtils>()->CountUILayers(layerList);
				InterfacePtr<ICommand> cmd(LayerPanelUtils::CreateShowLockCommand(this, clickedDocLayer,
					(numLocked == numLayers - 1) ? (ActionID)kUnlockAllLayersActionID : (ActionID)kLockOtherLayersActionID));
				if (cmd)
					CmdUtils::ProcessCommand(cmd); 
				
			}
			else if(cmdKeyDown && targetLayers.Contains(layerTreeNode->GetUID())) // cmd+click in layer pencil means lock/unlock all layers selected in panel
			{
				bool16 originalLayerLockState = clickedDocLayer->IsLocked();
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
			//	cmdSeq->SetName("#LockLayersCmd");
				for (int32 i = 0; i<targetLayers.Length(); i++)
				{
					InterfacePtr<const IDocumentLayer> someLayer(targetLayers.GetRef(i),UseDefaultIID());
					if(someLayer->IsLocked() == originalLayerLockState)
					{
						InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kLockLayerCmdBoss));
						cmd->SetItemList(targetLayers.GetRef(i));
						InterfacePtr<IBoolData> cmdData(cmd, IID_IBOOLDATA);
						cmdData->Set(!originalLayerLockState);
						CmdUtils::ProcessCommand(cmd);
					}
				}
				CmdUtils::EndCommandSequence(cmdSeq);
			}
			else
			// Just  Lock/Unlock a single layer
			{
				InterfacePtr<ITriStateControlData> triControlData(this, IID_ITRISTATECONTROLDATA);
				if(!triControlData->IsSelected())
					triControlData->Select();
				else
					triControlData->Deselect();
			}
			return kTrue;
		}
	}

	// Don't pass event to underlying widget, was derived from CEventHandler
	e->SetUI_DoEventHandledState(IEvent::kDontCall);
	return kFalse;
}

bool16 LayerPencilDragDropSourceEH::RButtonDn(IEvent* e)
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
	
	menuMgr->HandlePopupMenu("RtMenuLayerPanelLock", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
	
	return kTrue;
}

