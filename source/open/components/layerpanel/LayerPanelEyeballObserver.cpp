//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelEyeballObserver.cpp $
//  
//  Owner: Brendan O'Shea
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

#include "CObserver.h"

#include "ISubject.h"
#include "InterfacePtr.h"
#include "ITriStateControlData.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IControlView.h"
#include "ILayerList.h"
#include "IBoolData.h"
#include "IDocumentLayer.h"
#include "LayerPanelUtils.h"
#include "IPanelControlData.h"
#include "IPageItemVisibilityFacade.h"
#include "IWidgetParent.h"
#include "ITreeNodeIDData.h"

#include "CmdUtils.h"
#include "LayerPanelID.h"
#include "LayoutUIID.h"
#include "LayerID.h"
#include "LayerPanelDefs.h"
#include "UIDList.h"
#include "widgetid.h"
#include "LayerTreeUIDNodeID.h"
#include "Utils.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class LayerPanelEyeballObserver
//----------------------------------------------------------------------------------------

class LayerPanelEyeballObserver : public CObserver
{
	public:
		LayerPanelEyeballObserver(IPMUnknown *boss);
		virtual ~LayerPanelEyeballObserver();
		
		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);


};


//========================================================================================
// CLASS LayerPanelEyeballObserver
//========================================================================================

CREATE_PMINTERFACE(LayerPanelEyeballObserver, kLayerPanelEyeballObserverImpl)

//----------------------------------------------------------------------------------------
// LayerPanelEyeballObserver constructor 
//----------------------------------------------------------------------------------------

LayerPanelEyeballObserver::LayerPanelEyeballObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// LayerPanelEyeballObserver::~LayerPanelEyeballObserver: 
//----------------------------------------------------------------------------------------

LayerPanelEyeballObserver::~LayerPanelEyeballObserver()
{
}


//----------------------------------------------------------------------------------------
// LayerPanelEyeballObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void LayerPanelEyeballObserver::AutoAttach()
{
//	TRACEFLOW("LayerPanel","LayerPanelEyeballObserver::AutoAttach for UID %d\n",::GetUID(this));
	// watch for changes in this buttons state (i.e. respond when clicked on)
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// LayerPanelEyeballObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void LayerPanelEyeballObserver::AutoDetach()
{
//	TRACEFLOW("LayerPanel","LayerPanelEyeballObserver::AutoDetach for UID %d\n",::GetUID(this));
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// LayerPanelEyeballObserver::Update: 
//----------------------------------------------------------------------------------------

void LayerPanelEyeballObserver::Update(const ClassID& theChange, ISubject* , const PMIID& , void* )
{
	// ==> Please update GetObserverInfo()  <==

	if (theChange == kTrueStateMessage || theChange == kFalseStateMessage)
	{
		InterfacePtr<ITriStateControlData> data(this, IID_ITRISTATECONTROLDATA);
		if (data)
		{
			NodeID treeNode(LayerPanelUtils::GetLayerTreeNodeFromSubwidget(this)); // this looks like it could be combined with the next line, but doing so creates a memory leak.
			TreeNodePtr<const LayerTreeUIDNodeID>	layerTreeNode(treeNode);

			UIDRef clickedItem(LayerPanelUtils::GetCurrentLayerPanelDB(this),layerTreeNode->GetUID());
			if(layerTreeNode->IsLayerEntry())
			{
				InterfacePtr<const IDocumentLayer> layerClicked(clickedItem,UseDefaultIID());
				if(layerClicked)
				{
					bool16 visible = layerClicked->IsVisible();

					InterfacePtr<ICommand> cmd (CmdUtils::CreateCommand(kShowLayerCmdBoss));
					cmd->SetItemList(  UIDList(layerClicked));
					InterfacePtr<IBoolData> cmdData(cmd, IID_IBOOLDATA);
					cmdData->Set(!visible);
					CmdUtils::ProcessCommand(cmd);
				}
			}
			else
			{

				if(Utils<Facade::IPageItemVisibilityFacade>()->CanHide(clickedItem))
				{
					bool16 hidden = !Utils<Facade::IPageItemVisibilityFacade>()->GetVisibleState(clickedItem);

					if(hidden)
						Utils<Facade::IPageItemVisibilityFacade>()->Show(clickedItem);
					else
						Utils<Facade::IPageItemVisibilityFacade>()->Hide(clickedItem);
				}
			}
		}
	}
}

