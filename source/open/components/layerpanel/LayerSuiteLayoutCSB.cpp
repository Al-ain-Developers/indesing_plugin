//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerSuiteLayoutCSB.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "ICmdCollection.h"
#include "IControlView.h"
#include "ICopyCmdData.h"
#include "IDocumentBroadcastMsg.h"
#include "IDocumentLayer.h"
#include "IGeometry.h"
#include "IHierarchy.h"
#include "ILayerSuite.h"
#include "ILayoutControlData.h"
#include "ILayoutSelectionSuite.h"
#include "ILayoutTarget.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "ILayerFacade.h"

// ----- Includes -----

#include "CPMUnknown.h"
#include "HelperInterface.h"
#include "SelectionExtTemplates.tpp"

// ----- Utility files -----

#include "CmdUtils.h"
#include "ILayerUtils.h"
#include "ILayoutUtils.h"
#include "IPageItemTypeUtils.h"
#include "ISelectionUtils.h"

// ----- ID.h files -----

#include "LayerPanelID.h"


class LayerSuiteLayoutCSB : public CPMUnknown<ILayerSuite>
{
public:
    LayerSuiteLayoutCSB(IPMUnknown *boss);
    ~LayerSuiteLayoutCSB();

	virtual void		GetSelectedLayers(UIDList& docLayerUIDList);
	virtual bool16		AreAllItemsOnLayerSelected(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
	virtual void		DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly);
	virtual void		DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr);
	virtual void		SelectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly, Selection::Action replaceOrAdd);
	virtual ErrorCode	MoveToLayer(IDocumentLayer* sourceLayer, IDocumentLayer* targetLayer, IControlView* view, Selection::Action replaceOrAdd, bool16 bDuplicate);
	virtual UIDList GetSelectedItemsForLayersPanel() const;

	// Selection Extension methods
	virtual void                SelectionChanged(SuiteBroadcastData*, const PMIID&, void*) {}
	virtual void                SelectionAttributeChanged(SuiteBroadcastData*, const PMIID&, void*);
	virtual ProtocolCollection* CreateObserverProtocolCollection(void);
	virtual void                Startup(void) {}
	virtual void                Shutdown(void) {}
	virtual void                HandleIntegratorSuiteMessage (void*, const ClassID&, ISubject*, const PMIID&, void*) {}


};

CREATE_PMINTERFACE(LayerSuiteLayoutCSB, kLayerSuiteLayoutCSBImpl )
CREATE_PMINTERFACE(SelectionExt<LayerSuiteLayoutCSB>, kLayerSuiteLayoutCSBExtImpl)

LayerSuiteLayoutCSB::LayerSuiteLayoutCSB(IPMUnknown *boss) :
    CPMUnknown<ILayerSuite>(boss)
{
}


LayerSuiteLayoutCSB::~LayerSuiteLayoutCSB()
{
}

UIDList LayerSuiteLayoutCSB::GetSelectedItemsForLayersPanel() const
{
	InterfacePtr<ILayoutTarget> iNewSelectionTarget (this, UseDefaultIID ());
	if (iNewSelectionTarget)
	{
		// Get list of selected items from Layout Selection
		UIDList selectedItems = iNewSelectionTarget->GetUIDList (kDontStripStandoffs);
		// should probably do some filtering here - LayerPanelUtils::InvalidateNodeForPageItem has some criteria for what gets filtered out.
		return selectedItems;
	}
	return UIDList();
		
}

// Look through the page items in the layout selection and
// create a list of document layers that all the items are on.
void LayerSuiteLayoutCSB::GetSelectedLayers(UIDList& docLayerUIDList)
{
	InterfacePtr<ILayoutTarget> iNewSelectionTarget (this, UseDefaultIID ());
	if (iNewSelectionTarget)
	{
		// Get list of selected items from Layout Selection
		UIDList selectedItems = iNewSelectionTarget->GetUIDList (kDontStripStandoffs);

		// Figure out what document layer each item is on, store in docLayerUIDList
		int32 numItems = selectedItems.Length();
		for (int32 i = 0; i < numItems; i++)
		{
			InterfacePtr<IHierarchy> hierItem(selectedItems.GetRef(i), IID_IHIERARCHY);
			if (hierItem != nil && !Utils<IPageItemTypeUtils>()->IsStandOff(hierItem))	
			{
				UID spreadLayerUID = Utils<ILayerUtils>()->GetLayerUID(hierItem);
				if (spreadLayerUID != kInvalidUID)
				{
					InterfacePtr<ISpreadLayer> spreadLayer(::GetDataBase(hierItem), spreadLayerUID, IID_ISPREADLAYER);
					UID docLayerUID = spreadLayer->GetDocLayerUID();

					if (docLayerUIDList.Location(docLayerUID) == -1)
						docLayerUIDList.Append(docLayerUID);
				}
			}
		}
	}
}

bool16 LayerSuiteLayoutCSB::AreAllItemsOnLayerSelected(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly)
{
	InterfacePtr<ILayoutControlData> layoutData(view, IID_ILAYOUTCONTROLDATA);
	ASSERT_MSG(layoutData != nil, "CLayoutLayerListObserver::DeselectItems - layoutData != nil");
	if (layoutData)
	{
		InterfacePtr<ISpread> spread(layoutData->GetSpreadRef(), IID_ISPREAD);
		InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(documentLayer, nil, guideLayerOnly));	// Regular spread layer or guide layer
		InterfacePtr<IHierarchy> layerHierarchy(spreadLayer, IID_IHIERARCHY);

		if (layerHierarchy)
		{
			UIDList itemsOnLayer(GetDataBase(spread));

			// Put all the items on this layer into a list.
			if (spreadLayer->IsVisible() && !spreadLayer->IsLocked())
			{
				int32 numItems = layerHierarchy->GetChildCount();
				for (int32 j = 0; j < numItems; j++)
					itemsOnLayer.Append(layerHierarchy->GetChildUID(j));
			}

			if (itemsOnLayer.Length() == 0)
				return kFalse;

			InterfacePtr<ILayoutTarget> layoutTarget(this, UseDefaultIID());
			UIDList selectedList = layoutTarget->GetUIDList (kDontStripStandoffs);
			if (itemsOnLayer.Length() >  selectedList.Length())
				return kFalse;

			for (int32 i = itemsOnLayer.Length() - 1; i >= 0; i--)
			{
				bool found = false;
				for (int32 j = selectedList.Length() - 1; j >= 0; j--)
				{
					if(itemsOnLayer[i] == selectedList[j])
					{
						found = true;
						break;
					}
				}
				if(!found)
					return kFalse;
			}
			return kTrue;
		}		
		else
		{
			ASSERT_FAIL("LayerSuiteLayoutCSB::SelectAllItemsOnLayer, No hierarchy found!");
		}
	}
	return kFalse;
}

void LayerSuiteLayoutCSB::DeselectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly)
{
	InterfacePtr<ILayoutControlData> layoutData(view, IID_ILAYOUTCONTROLDATA);
	ASSERT_MSG(layoutData != nil, "LayerSuiteLayoutCSB::DeselectAllItemsOnLayer - layoutData != nil");
	if (layoutData)
	{
		InterfacePtr<ISpread> spread(layoutData->GetSpreadRef(), IID_ISPREAD);
		InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(documentLayer, nil, guideLayerOnly));	// Regular spread layer or guide layer
		InterfacePtr<IHierarchy> layerHierarchy(spreadLayer, IID_IHIERARCHY);

		InterfacePtr<ILayoutTarget> layoutTarget(this, UseDefaultIID());
		UIDList selectedList = layoutTarget->GetUIDList (kDontStripStandoffs);

		if (!selectedList.IsEmpty())
		{
			// Remove items that aren't the layer being hidden/locked so they won't be deselected.
			for (int32 i = selectedList.Length() - 1; i >= 0; i--)
			{
				InterfacePtr<IHierarchy> pageItemHier(::GetDataBase(layerHierarchy), (selectedList)[i], IID_IHIERARCHY);
				if (pageItemHier && layerHierarchy && pageItemHier->GetLayerUID() != layerHierarchy->GetLayerUID())
					selectedList.Remove(i);
			}
		}

		// Now deselect the items.
		if (selectedList.Length() > 0)
		{
			InterfacePtr<ISelectionManager> 	iSelectionManager ( Utils<ISelectionUtils>()->QueryViewSelectionManager(view));
			InterfacePtr<ILayoutSelectionSuite>	iLayoutSelectionSuite (Utils<ISelectionUtils>()->QueryLayoutSelectionSuite (iSelectionManager));	
			
			iLayoutSelectionSuite->DeselectPageItems (selectedList);
		}
	}
}

void LayerSuiteLayoutCSB::DeselectAllItemsInList(UIDList& list, ISelectionManager* selectionMgr)
{
	// Now deselect the items.
	if (list.Length() > 0)
	{
		InterfacePtr<ILayoutSelectionSuite>	iLayoutSelectionSuite (Utils<ISelectionUtils>()->QueryLayoutSelectionSuite (selectionMgr));	
		
		iLayoutSelectionSuite->DeselectPageItems (list);
	}
}

void LayerSuiteLayoutCSB::SelectAllItemsOnLayer(IDocumentLayer* documentLayer, IControlView* view, bool16 guideLayerOnly, Selection::Action replaceOrAdd)
{
	InterfacePtr<ILayoutControlData> layoutData(view, IID_ILAYOUTCONTROLDATA);
	ASSERT_MSG(layoutData != nil, "CLayoutLayerListObserver::DeselectItems - layoutData != nil");
	if (layoutData)
	{
		InterfacePtr<ISpread> spread(layoutData->GetSpreadRef(), IID_ISPREAD);
		InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(documentLayer, nil, guideLayerOnly));	// Regular spread layer or guide layer
		InterfacePtr<IHierarchy> layerHierarchy(spreadLayer, IID_IHIERARCHY);

		if (layerHierarchy)
		{
			UIDList selectedList(GetDataBase(spread));

			// Put all the items on this layer into a list.
			if (spreadLayer->IsVisible() && !spreadLayer->IsLocked())
			{
				int32 numItems = layerHierarchy->GetChildCount();
				for (int32 j = 0; j < numItems; j++)
					selectedList.Append(layerHierarchy->GetChildUID(j));
			}

			if (selectedList.Length() > 0)
			{
				InterfacePtr<ISelectionManager> 	iSelectionManager ( Utils<ISelectionUtils>()->QueryViewSelectionManager(view));
				InterfacePtr<ILayoutSelectionSuite>	iLayoutSelectionSuite (Utils<ISelectionUtils>()->QueryLayoutSelectionSuite (iSelectionManager));	
				
				iLayoutSelectionSuite->SelectPageItems (selectedList, replaceOrAdd, Selection::kDontScrollLayoutSelection);
			}
		}
		else
		{
			ASSERT_FAIL("LayerSuiteLayoutCSB::SelectAllItemsOnLayer, No hierarchy found!");
		}
	}
}

ErrorCode LayerSuiteLayoutCSB::MoveToLayer(IDocumentLayer* sourceLayer, IDocumentLayer* targetLayer, IControlView* view, Selection::Action replaceOrAdd, bool16 bDuplicate)
{
	ErrorCode err = kSuccess;

	InterfacePtr<ILayoutTarget> layoutTarget( this, UseDefaultIID() ); 
	UIDList selectedItems = layoutTarget->GetUIDList( kStripStandoffs ); 
	IDataBase* db = selectedItems.GetDataBase();
		
	if (!(view == nil || selectedItems.Length() == 0 || sourceLayer == targetLayer))
	{
		InterfacePtr<ILayoutControlData> layoutData(view, UseDefaultIID());

		// Create a pipeline sequence command to hold a set of commands.
		InterfacePtr<ICommand> command(CmdUtils::CreateCommand(kPipelineSequenceCmdBoss));
		InterfacePtr<ICmdCollection> cmdList(command, IID_ICMDCOLLECTION);
		command->SetName(bDuplicate ? "Copy To Layer" : "Move To Layer");
	
		// Make the current selection list, which may contain items from many layers.
		// Then remove all but those from the source layer.
		for (int32 i = 0; i < selectedItems.Length(); )
		{
			InterfacePtr<IHierarchy> itemHierarchy(selectedItems.GetRef(i), IID_IHIERARCHY);
			UID spreadLayerUID = Utils<ILayerUtils>()->GetLayerUID(itemHierarchy);
			InterfacePtr<ISpreadLayer> spreadLayer(db, spreadLayerUID, IID_ISPREADLAYER);
			if (spreadLayer->GetDocLayerUID() != ::GetUID(sourceLayer))
				selectedItems.Remove(i);
			else
				i++;
		}
		
		UIDList originalSelectedItems(selectedItems);
		err = Utils<Facade::ILayerFacade>()->MoveToLayer(selectedItems,targetLayer,bDuplicate);
		
		if (err == kSuccess)
		{
			InterfacePtr<ISelectionManager> iSelectionManager (Utils<ISelectionUtils>()->QueryViewSelectionManager (view));
			InterfacePtr<ILayoutSelectionSuite>	iLayoutSelectionSuite (Utils<ISelectionUtils>()->QueryLayoutSelectionSuite (iSelectionManager));	

			// Select/Deselect the items on the new target layer. Normally we select, but 
			// if target layer was hidden and/or locked, deselect the items.
			// User can make this happen when command key is pressed as an override gesture.
			// The item list for this SelectPageItems command gets its input via pipeline command.
			if (targetLayer)
			{
				if (targetLayer->IsVisible() && !targetLayer->IsLocked())
				{
					iLayoutSelectionSuite->SelectPageItems (selectedItems, replaceOrAdd, Selection::kDontScrollLayoutSelection);			
				}
				else
				{
					iLayoutSelectionSuite->DeselectPageItems (selectedItems);			
				}
			}
			
			// Deselect the original items that were duplicated. Make this a compound command
			// so that the pipeline command above doesn't mess up the item list.
			if (bDuplicate)
			{
				iLayoutSelectionSuite->DeselectPageItems (originalSelectedItems);
			}
		}

	}

	return err;
}

//----------------------------------------------------------------------------------------
// LayerSuiteLayoutCSB::SelectionAttributeChanged
//----------------------------------------------------------------------------------------
void LayerSuiteLayoutCSB::SelectionAttributeChanged(SuiteBroadcastData* broadcastData, const PMIID& messageID, void* data)
{
	ASSERT_MSG(broadcastData, "LayerSuiteLayoutCSB::SelectionAttributeChanged. broadcastData is nil");
	
	if (messageID == IID_IDOCUMENT_BROADCAST)
	{
		IDocumentBroadcastMsg*  layoutMessage = static_cast<IDocumentBroadcastMsg*>(data);
		const PMIID protocol = layoutMessage->GetPMIID();
		const ClassID theChange = layoutMessage->GetClassID();

		if ((protocol == IID_ILAYERLIST) && (theChange == kMoveToLayerCmdBoss) &&
			FindLocationInSorted(*broadcastData, static_cast<PMIID>(IID_ILAYERSUITE)) < 0)
		{
			InsertKeyValueInSorted(*broadcastData, static_cast<PMIID>(IID_ILAYERSUITE),
								 boost::shared_ptr<SelectionSuiteData>());
		}
	}
}

//----------------------------------------------------------------------------------------
// LayerSuiteLayoutCSB::CreateObserverProtocolCollection
//----------------------------------------------------------------------------------------
ProtocolCollection* LayerSuiteLayoutCSB::CreateObserverProtocolCollection()
{
    ProtocolCollection* protocolList = new ProtocolCollection ();
    protocolList->push_back(IID_ILAYERLIST);      // For e.g. kMoveToLayerCmdBoss
    return protocolList;
}
