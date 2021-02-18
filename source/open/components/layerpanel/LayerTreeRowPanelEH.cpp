//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerTreeRowPanelEH.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

//interface includes
#include "IApplication.h"
#include "IEvent.h"
#include "IDragDropSource.h"
#include "IDragDropController.h"
#include "ITreeNodeIDData.h"
#include "LayerTreeUIDNodeID.h"
#include "ILayoutUIUtils.h"
#include "IDocument.h"
#include "IWidgetParent.h"
#include "ITreeViewController.h"
#include "IMenuManager.h"
#include "IActionManager.h"
#include "IPanelControlData.h"

//includes
#include "TreeNodeEventHandler.h"
#include "LayerPanelUtils.h"
#include "LayerPanelID.h"
#include "EventUtilities.h"
#include "Utils.h"
#include "IEventUtils.h"

class  LayerTreeRowPanelEH : public TreeNodeEventHandler
{
public:
	typedef TreeNodeEventHandler Inherited;

	LayerTreeRowPanelEH(IPMUnknown* boss) : Inherited(boss)
		{}
	virtual ~LayerTreeRowPanelEH()
		{}
	
	virtual bool16 LButtonDn(IEvent* e);
	virtual bool16 LButtonUp(IEvent* e);
	virtual bool16 RButtonDn(IEvent* e);
};


CREATE_PMINTERFACE(LayerTreeRowPanelEH, kLayerTreeRowPanelEHImpl)


bool16 LayerTreeRowPanelEH::LButtonDn(IEvent* e)
{
	bool16 result = TreeNodeEventHandler::LButtonDn(e);
	if(!result)
	{
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
					e->SetSystemHandledState(IEvent::kDontCall);
					return kTrue; // Make up for the fact that StartDrag will swallow the mouse up
				}
			}
		}
	}
	return result;
}

bool16 LayerTreeRowPanelEH::LButtonUp(IEvent* e)
{
	bool16 result = TreeNodeEventHandler::LButtonUp(e);

	if(!result && !e->ShiftKeyDown() && !e->CmdKeyDown())
	{
		InterfacePtr<const ITreeNodeIDData>	nodeData(this,UseDefaultIID());
		NodeID treeNode = nodeData->Get();
		TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(treeNode);
		if(uidNode->IsLayerEntry())
		{
			InterfacePtr<const IWidgetParent> wp(this,UseDefaultIID());
			InterfacePtr<const ITreeViewController> treeController((ITreeViewController*)wp->QueryParentFor(ITreeViewController::kDefaultIID));
			if(uidNode->IsLayerEntry() && treeController->IsSelected(treeNode))
			{
				UID	layerUID = uidNode->GetUID();
				InterfacePtr<ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
				UIDRef docLayerRef(LayerPanelUtils::GetCurrentLayerPanelDB(this),layerUID);
				LayerPanelUtils::DoSetActiveLayer(docLayerRef,layoutData);
			}
		}
	}

	return result;
}

bool16 LayerTreeRowPanelEH::RButtonDn(IEvent* e)
{
	InterfacePtr<IControlView>	myView(this, UseDefaultIID());
	InterfacePtr<IPanelControlData> widgetsChildren(this, UseDefaultIID());
	if (widgetsChildren)
	{
		SysPoint pt = e->GlobalWhere();
		SysPoint localWhere = ::ToSys(myView->GlobalToWindow(pt));
		IControlView* hitWidget = widgetsChildren->FindWidget(localWhere);

		if (hitWidget && (hitWidget->GetWidgetID() == kTreeNodeExpanderWidgetID || 
						hitWidget->GetWidgetID() == kLayerPageItemElementWidgetID ||
						hitWidget->GetWidgetID() == kLayerPageItemNamePanelWidgetID)	// Actual hit on name will return kInLineEditStaticTextWidgetID, this is for blank area at left
			)
		{
			InterfacePtr<const IApplication> theApp(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<const IActionManager> actionMgr(theApp->QueryActionManager());
			InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
			
			InterfacePtr<const ITreeNodeIDData>	nodeData(this,UseDefaultIID());
			NodeID treeNode = nodeData->Get();
			TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(treeNode);
			if(uidNode->IsLayerEntry())
				menuMgr->HandlePopupMenu("RtMenuLayerPanelItem", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
			else
				menuMgr->HandlePopupMenu("RtMenuLayerPanelPageItem", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);
			
			return kTrue;
		}
	}

	return TreeNodeEventHandler::RButtonDn(e);
}




