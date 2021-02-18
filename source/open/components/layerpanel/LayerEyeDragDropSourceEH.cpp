//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerEyeDragDropSourceEH.cpp $
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
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IDragDropController.h"
#include "IDragDropSource.h"
#include "IEvent.h"
#include "ILayerList.h"
#include "IMenuManager.h"
#include "ISession.h"
#include "ITriStateControlData.h"
#include "IWidgetParent.h"
#include "IPageItemVisibilityFacade.h"

// ----- Includes -----

#include "LayerTreeUIDNodeID.h"
#include "UIDList.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "EventUtilities.h"
#include "ILayerUtils.h"
#include "LayerPanelUtils.h"

// ----- ID.h files -----

#include "DragDropID.h"
#include "LayerPanelID.h"
#include "widgetid.h"

#include "DVControlEventHandler.h"

class LayerEyeDragDropSourceEH : public DVControlEventHandler
{		
	typedef DVControlEventHandler inherited;
	public:
						LayerEyeDragDropSourceEH(IPMUnknown *boss);
		virtual 		~LayerEyeDragDropSourceEH();
			
		virtual bool16 	LButtonDn(IEvent* e); 
		virtual bool16 	LButtonUp(IEvent* e); 
		virtual bool16	RButtonDn(IEvent* e);
		
	private:
		DECLARE_HELPER_METHODS()
};

//========================================================================
// Class LayerEyeDragDropSourceEH
//========================================================================
CREATE_PMINTERFACE(LayerEyeDragDropSourceEH, kLayerEyeDragDropSourceEHImpl)
DEFINE_HELPER_METHODS(LayerEyeDragDropSourceEH)

LayerEyeDragDropSourceEH::LayerEyeDragDropSourceEH(IPMUnknown *boss) :
	inherited(boss),
	HELPER_METHODS_INIT(boss)
{
}

LayerEyeDragDropSourceEH::~LayerEyeDragDropSourceEH()
{
}
	
bool16 LayerEyeDragDropSourceEH::LButtonUp(IEvent* )
{
	return kTrue; // so it doesn't get handled as activating the layer
}


UIDList GetItemsSelectedInTree(IPMUnknown* widget,const LayerTreeUIDNodeID* layerTreeNode)
{
	if(layerTreeNode->IsLayerEntry())
	{
		UIDList selectedLayers(LayerPanelUtils::GetCurrentLayerPanelDB(widget));
		LayerPanelUtils::GetTargetLayers(selectedLayers,widget);
		return selectedLayers;
	}
	return LayerPanelUtils::GetPageItemsSelectedInPanel(widget,LayerPanelUtils::GetCurrentLayerPanelDB(widget));
}

bool16 LayerEyeDragDropSourceEH::LButtonDn(IEvent* e)
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
			// Option + click is shortcut for Show All/Hide Others
			NodeID treeNode(LayerPanelUtils::GetLayerTreeNodeFromSubwidget(this)); // this looks like it could be combined with the next line, but doing so creates a memory leak.
			TreeNodePtr<const LayerTreeUIDNodeID>	layerTreeNode(treeNode);
			UIDList treeItemsSelected = GetItemsSelectedInTree(this,layerTreeNode);
			if (optionKeyDown)
			{
				if(layerTreeNode->IsLayerEntry())
				{
					InterfacePtr<IDocumentLayer> docLayer(LayerPanelUtils::QueryLayerFromPanelWidget(this));
					InterfacePtr<ILayerList> layerList(::GetDataBase(docLayer),::GetDataBase(docLayer)->GetRootUID(),UseDefaultIID());
					int32 numShown = Utils<ILayerUtils>()->CountVisibleUILayers(layerList);
					InterfacePtr<ICommand> cmd(LayerPanelUtils::CreateShowLockCommand(this, docLayer, 
						(numShown == 1 && docLayer->IsVisible()) ? (ActionID)kShowAllLayersActionID : (ActionID)kHideOtherLayersActionID));
					if (cmd)
						CmdUtils::ProcessCommand(cmd); 
				}
				else
				{
					LayerPanelUtils::ShowHideOtherPageItems(this,layerTreeNode->GetUID());
				}
			}
			else if(cmdKeyDown && treeItemsSelected.Contains(layerTreeNode->GetUID()))
			{
				// if cmd+click on selected eye, all the selected layers/page items should toggle visibility
				if(layerTreeNode->IsLayerEntry())
				{
					InterfacePtr<IDocumentLayer> clickedDocLayer(LayerPanelUtils::QueryLayerFromPanelWidget(this));
					bool16 originalVisible = clickedDocLayer->IsVisible();
					ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
					for(int i = 0; i < treeItemsSelected.Length(); ++i)
					{
						InterfacePtr<const IDocumentLayer> oneLayer(treeItemsSelected.GetRef(i),UseDefaultIID());
						if(oneLayer && oneLayer->IsVisible() == originalVisible)
						{
							InterfacePtr<ICommand> cmd (CmdUtils::CreateCommand(kShowLayerCmdBoss));
							cmd->SetItemList(  UIDList(oneLayer));
							InterfacePtr<IBoolData> cmdData(cmd, IID_IBOOLDATA);
							cmdData->Set(!originalVisible);
							CmdUtils::ProcessCommand(cmd);
						}
					}
					CmdUtils::EndCommandSequence(cmdSeq);
				}
				else
				{
					UIDRef clickedItem(treeItemsSelected.GetDataBase(),layerTreeNode->GetUID());
					if(Utils<Facade::IPageItemVisibilityFacade>()->CanHide(clickedItem))
					{
						bool16 hidden = !Utils<Facade::IPageItemVisibilityFacade>()->GetVisibleState(clickedItem);
						
						if(hidden)
							Utils<Facade::IPageItemVisibilityFacade>()->Show(treeItemsSelected);
						else
							Utils<Facade::IPageItemVisibilityFacade>()->Hide(treeItemsSelected);
					}
				}
			}
			else
			// Just Show/Hide a single layer
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

bool16 LayerEyeDragDropSourceEH::RButtonDn(IEvent* e)
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> actionMgr(theApp->QueryActionManager());
	InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
	
	menuMgr->HandlePopupMenu("RtMenuLayerPanelEye", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
	
	return kTrue;
}

