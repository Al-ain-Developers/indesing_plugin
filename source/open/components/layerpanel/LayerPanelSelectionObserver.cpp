//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelSelectionObserver.cpp $
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
//  Purpose:	Observes the selection for the Layer Panel. Updates the proxy widgets.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IBoolData.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "ILayerList.h"
#include "ILayerSuite.h"
#include "IPanelControlData.h"
#include "IWidgetParent.h"
#include "ITreeViewMgr.h"
#include "IHierarchy.h"
// ----- Includes -----

#include "SelectionObserver.h"
#include "LayerTreeUIDNodeID.h"

// ----- Utility files -----

#include "LayerPanelUtils.h"
#include "IPalettePanelUtils.h"
#include "ISelectionUtils.h"

// ----- ID.h files -----

#include "LayerPanelID.h"

#define INHERITED	ActiveSelectionObserver

//========================================================================================
// class LayerPanelSelectionObserver
//========================================================================================

class LayerPanelSelectionObserver : public INHERITED
{
	public:
		LayerPanelSelectionObserver(IPMUnknown *boss);
		virtual ~LayerPanelSelectionObserver();

		//________________________________________________________________________________________
		//  DESCR:      Everything relating to the selection should update.
		//
		//              Either  (a) there is a new active selection
		//              or      (b) the items in the selection has changed
		//________________________________________________________________________________________
		virtual void    HandleSelectionChanged (const ISelectionMessage*);

		virtual void 	HandleSelectionUpdate (const ClassID& bossClassID, ISubject* subject, const PMIID&, void* message);
	private:
		K2Vector<UID> fPreviousSelectedLayers;
		K2Vector<UID> fPreviousSelectedPageItems;
		
		IDataBase*	fPreviousDB;
};

CREATE_PMINTERFACE(LayerPanelSelectionObserver, kLayerPanelSelectionObserverImpl)

//----------------------------------------------------------------------------------------
// LayerPanelSelectionObserver::LayerPanelSelectionObserver
//----------------------------------------------------------------------------------------

LayerPanelSelectionObserver::LayerPanelSelectionObserver(IPMUnknown *boss) :
	INHERITED(boss, IID_ISELECTIONOBSERVER),fPreviousDB(nil)
{
}

//----------------------------------------------------------------------------------------
// LayerPanelSelectionObserver::~LayerPanelSelectionObserver
//----------------------------------------------------------------------------------------

LayerPanelSelectionObserver::~LayerPanelSelectionObserver()
{
}

//----------------------------------------------------------------------------------------
// LayerPanelSelectionObserver::LayerPanelSelectionObserver
//
// Update the selection proxy widgets at the right side of the layer name(s) to correspond
// with the layers represented in the selection.
//----------------------------------------------------------------------------------------

void LayerPanelSelectionObserver::HandleSelectionChanged(const ISelectionMessage* msg)
{
#if !defined (ENABLE_ALL_TRACES)
	TRACEFLOW("LayerPanel","LayerPanelSelectionObserver::HandleSelectionChanged got msg 0x%x. fPreviousDB is 0x%x. fPreviousSelectedPageItems length %d. fPreviousSelectedLayers length %d\n",
		msg,fPreviousDB,fPreviousSelectedPageItems.size(),fPreviousSelectedLayers.size());
#endif
    
	if(!msg)
	{
		fPreviousSelectedPageItems.clear();
		fPreviousSelectedLayers.clear();
		fPreviousDB = nil;
	//	return;
	}
	
	// inval appropriate items for selection change
	InterfacePtr<ITreeViewMgr> treeViewMgr(this,UseDefaultIID());
	if(fPreviousDB)
	{
		for (uint32 i = 0; i < fPreviousSelectedPageItems.size(); ++i)
		{
			LayerPanelUtils::InvalidateNodeForPageItem(treeViewMgr,fPreviousDB,fPreviousSelectedPageItems[i],false);
		}
	}
	fPreviousSelectedPageItems.clear();

	bool gotLayerSuite = false;
	if (fCurrentSelection && fCurrentSelection->IsInterfaceEnabled (IID_ILAYERSUITE)) 
	{
		InterfacePtr<ILayerSuite>    iLayerSuite ( static_cast<ILayerSuite*>(QueryAbstractSelection(IID_ILAYERSUITE)));
		ASSERT_MSG (iLayerSuite != nil, "LayerPanelSelectionObserver::HandleSelectionChanged, ILayerSuite is nil.");
		
		if (iLayerSuite)
		{
			gotLayerSuite = true;
			UIDList selectedItems = iLayerSuite->GetSelectedItemsForLayersPanel();
								
			// we have to inval all the ancestor nodes of the selected items too, since we show a smaller selection widget for those...					
			for (uint32 i = 0; i < selectedItems.size(); ++i)
			{
				InterfacePtr<const IHierarchy> piHier(selectedItems.GetRef(i),UseDefaultIID());
				UIDList ancestorsOfSelectedItem(selectedItems.GetDataBase());
				piHier->GetAncestors(&ancestorsOfSelectedItem,IID_IHIERARCHY);
				for (uint32 j = 0; j < ancestorsOfSelectedItem.size(); ++j)
				{
					LayerPanelUtils::InvalidateNodeForPageItem(treeViewMgr,fCurrentSelection->GetDataBase(),ancestorsOfSelectedItem[j],false);
					fPreviousSelectedPageItems.push_back(ancestorsOfSelectedItem[j]);
				}
				LayerPanelUtils::InvalidateNodeForPageItem(treeViewMgr,fCurrentSelection->GetDataBase(),selectedItems[i],false);
				fPreviousSelectedPageItems.push_back(selectedItems[i]);
			}

			UIDList docLayerList(fCurrentSelection->GetDataBase());
			iLayerSuite->GetSelectedLayers(docLayerList);
					
			// could add an optimization here to only inval new/old selected layers if their selection state has acutally changed, but that might be more expensive than just doing the inval.
			if(fPreviousDB == fCurrentSelection->GetDataBase())
			{
				for (uint32 i = 0; i < fPreviousSelectedLayers.size(); ++i)
				{
					NodeID layerInOldSelection = LayerTreeUIDNodeID::Create(fPreviousSelectedLayers[i],kTrue);
					treeViewMgr->NodeChanged(layerInOldSelection);
				}
			}
			
			fPreviousSelectedLayers.clear();
			
			for (uint32 i = 0; i < docLayerList.size(); ++i)
			{
#if !defined (ENABLE_ALL_TRACES)
				TRACEFLOW("LayerPanel","LayerPanelSelectionObserver invalling layer UID %d because it's now selected\n",docLayerList[i].Get());
#endif
				NodeID layerInNewSelection = LayerTreeUIDNodeID::Create(docLayerList[i],kTrue);
				treeViewMgr->NodeChanged(layerInNewSelection);
				fPreviousSelectedLayers.push_back(docLayerList[i]);
			}
			fPreviousDB = fCurrentSelection->GetDataBase();
		}
	}
	if(!gotLayerSuite)
	{
		fPreviousSelectedLayers.clear();
		fPreviousDB = nil;
	}
}

//----------------------------------------------------------------------------------------
// LayerPanelSelectionObserver::HandleSelectionUpdate
//	We override this method to get a peek at the message.
//----------------------------------------------------------------------------------------
void LayerPanelSelectionObserver::HandleSelectionUpdate (
		const ClassID& bossClassID, 
		ISubject* subject, 
		const PMIID& protocol, 
		void* message)
{
	// Custom message to initialize panel when first shown.
	if (protocol == IID_IUPDATEPROXYSELECTION)
	{
		HandleSelectionChanged((ISelectionMessage*)message);
	}
	else
	{
		INHERITED::HandleSelectionUpdate(bossClassID, subject, protocol, message);
	}
}


