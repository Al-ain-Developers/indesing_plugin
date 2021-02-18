//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelUtils.cpp $
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

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IApplication.h"
#include "IBoolData.h"
#include "ICmdCollection.h"
#include "IDialogController.h"
#include "ITreeViewController.h"
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IGuideDataSuite.h"
#include "IGuidePrefs.h"
#include "IHierarchy.h"
#include "IIntData.h"
#include "ILayerList.h"
#include "ILayerSuite.h"
#include "ILayoutCmdData.h"
#include "ILayoutControlData.h"
#include "IMasterSpreadList.h"
#include "IMemoryManager.h"
#include "INewLayerCmdData.h"
#include "IPanelControlData.h"
#include "IPanelMgr.h"
#include "IPMUnknownData.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "ISpreadList.h"
#include "ITextFocus.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "IWindow.h"
#include "IWorkspace.h"
#include "ITreeNodeIDData.h"
#include "ILayoutUtils.h"
#include "ITreeViewMgr.h"
#include "IPageItemTypeUtils.h"
#include "ILayerFacade.h"
#include "ILayoutSelectionSuite.h"
#include "IPageItemAdapter.h"
#include "ITextFrameColumn.h"
#include "ITreeViewHierarchyAdapter.h"
#include "iuicolorutils.h"
#include "IWidgetUtils.h"
#include "IPageItemVisibilityFacade.h"
#include "IPageItemLockFacade.h"
#include "IPageItemScrapFacade.h"
#include "IDragDropController.h"
#include "ITreeViewMgr.h"
#include "IOWLPaletteSizer.h"
#include "ITreeViewWidgetMgr.h"
#include "ITreeAttributes.h"
#include "IPageItemNameFacade.h"

// ----- Includes -----

#include "CAlert.h"
#include "CoreResTypes.h"
#include "LayerPanelDefs.h"
#include "LocaleSetting.h"
#include "LayerTreeUIDNodeID.h"
#include "RsrcSpec.h"
#include "UIDList.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "ILayerUtils.h"
#include "ILayerUIUtils.h"
#include "LayerPanelUtils.h"
#include "ILayoutUIUtils.h"
#include "IPalettePanelUtils.h"
#include "PreferenceUtils.h"
#include "ISelectionUtils.h"
#include "StringUtils.h"
#include "UIDListUtils.h"
#include "K2Vector.tpp"

// ----- ID.h files -----

#include "LayerID.h"
#include "LayerPanelID.h"
#include "LayoutUIID.h"
#include "MasterPageID.h"
#include "SpreadID.h"
#include "TextID.h"
#include "FormFieldID.h"

// Helper function to return the indices of target items in this list and their document layer UIDs.
// Target items may either be the items selected in the tree, or can be the widget the user clicked
// on in the case of a context menu hit. Use the targetWidget parameter to find target layer(s).
// Use the Widget parent interface of the panel to find the list box and then the selected items.
// Items are in list index order.
void LayerPanelUtils::GetTargetLayers(UIDList& targetUIDList, const IPMUnknown* targetWidget)
{
	targetUIDList.Clear();
	InterfacePtr<const IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<const IPanelMgr> panelMgr(app->QueryPanelManager());

	if (panelMgr->IsPanelWithWidgetIDShown(kLayerParentWidgetId))
	{
		IControlView* panelControlView = panelMgr->GetVisiblePanel(kLayerParentWidgetId);
		if (panelControlView)
		{
			InterfacePtr<const IPanelControlData> panelData(panelControlView, IID_IPANELCONTROLDATA);
			
			InterfacePtr<const ITreeViewController> treeController(panelData->FindWidget(kLayerPanelTreeWidgetID), ITreeViewController::kDefaultIID);
			if (treeController)
			{

				NodeIDList selectedItems;
				treeController->GetSelectedItems(selectedItems);
				for (auto iter = selectedItems.rbegin(); iter != selectedItems.rend(); ++iter)
				{
					TreeNodePtr<const LayerTreeUIDNodeID>	layerNode(*iter);
					if(layerNode->IsLayerEntry())
						targetUIDList.Append(layerNode->GetUID());
				}

				// A "widget" passed into this function will hold element clicked on. Could have been initiated
				// via a context click. If so, consider this layer as a possible target. If the target layer
				// is already in the list of selected layers, just return the selected layers. This lets user
				// right click on a selected layer and operate on all of the selected layers (e.g. Merge).
				// If it isn't in the list, put target layer only in the list. User clicked on a blank layer.
				InterfacePtr<const IWidgetParent> parentHolder(targetWidget, UseDefaultIID());
				if (parentHolder)
				{
					InterfacePtr<const ITreeNodeIDData>	nodeData((ITreeNodeIDData*)parentHolder->QueryParentFor(IID_ITREENODEIDDATA));
					if (nodeData)
					{
						TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
						if(uidNode->IsLayerEntry())
						{
							UID targetUID = uidNode->GetUID();
							if (targetUIDList.Location(targetUID) == -1)
							{
								targetUIDList.Clear();
								targetUIDList.Append(targetUID);
							}
						}
					}
				}

	//			ASSERT_MSG(targetUIDList.Length() >= 1, "Why are no layers selected in panel?!?");
			}
		}
	}

	// Default to active document layer if no target layer can be found.
	if (targetUIDList.Length() == 0)
	{
		IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
		InterfacePtr<IDocumentLayer> activeLayer(Utils<ILayerUIUtils>()->QueryContextActiveLayer(context));
		if (activeLayer)
			targetUIDList.Append(::GetUID(activeLayer));
	}
}

// Are there expendable layers selected?
bool16 LayerPanelUtils::CanDeleteTargetLayers(IPMUnknown* targetWidget)
{
	InterfacePtr<IMemoryManager> memMgr(GetExecutionContextSession(), IID_IMEMORYMANAGER);
	if(memMgr->MemoryIsLow())
		return kFalse;
		
	bool16 canDelete = kTrue;
	IDataBase * docDB = LayerPanelUtils::GetCurrentLayerPanelDB(targetWidget);
	if (docDB != nil)
	{
		// Get a list of target layers
		UIDList targetUIDList(docDB);
		LayerPanelUtils::GetTargetLayers(targetUIDList, targetWidget);

		InterfacePtr<ILayerList> layerList(docDB,docDB->GetRootUID(),UseDefaultIID());
		int32 numLayers = Utils<ILayerUtils>()->CountUILayers(layerList);
		int32 numSelected = targetUIDList.Length();
		
		if (numLayers == numSelected || numSelected == 0)
		{
			canDelete = kFalse;
		}
		else
		{
//			InterfacePtr<IPlaceGun> placeGun(Utils<ILayoutUIUtils>()->GetFrontDocument(), UseDefaultIID());
			for (int32 i = 0; i < numSelected && canDelete; i++)
			{
				InterfacePtr<IDocumentLayer> docLayer(targetUIDList.GetRef(i), IID_IDOCUMENTLAYER);
                ASSERT_MSG(docLayer, "Are we trying to delete a layer that is already deleted?");
				if (!docLayer || !docLayer->IsExpendableLayer())
					canDelete = kFalse;
//				Don't do this check -- let it remain enabled so we can put up an alert for this edge case
//				else if (placeGun->OwnsAnyPageItemsOnLayer(targetUIDList[i]))
//					canDelete = kFalse;
			}
		}
	}
	else
	{
		canDelete = kFalse;
	}
	return canDelete;
}

//static bool TargetWidgetImpliesLayer(IPMUnknown* targetWidget)
//{
//	IDataBase * docDB = LayerPanelUtils::GetCurrentLayerPanelDB(targetWidget);
//	if (docDB != nil)
//	{
//		// Get a list of target layers
//		UIDList targetUIDList(docDB);
//		LayerPanelUtils::GetTargetLayers(targetUIDList, targetWidget);
//		if(!targetUIDList.IsEmpty())
//			return true;
//	}
//	return false;
//}
//
//static bool CanDeleteTargetPageItem(IPMUnknown* targetWidget)
//{
//	InterfacePtr<const IWidgetParent>	widgetParent(targetWidget, UseDefaultIID());
//	InterfacePtr<const ITreeNodeIDData>	nodeData((ITreeNodeIDData*)widgetParent->QueryParentFor(IID_ITREENODEIDDATA));
//	if(nodeData)
//	{
//		TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
//		ASSERT_MSG(!uidNode->IsLayerEntry(),"Shouldn't be layer!");
//		UIDList targetUIDList(LayerPanelUtils::GetCurrentLayerPanelDB(targetWidget),uidNode->GetUID());
//		return Utils<Facade::IPageItemScrapFacade>()->CanDeletePageItems(targetUIDList);
//	}
//	return false;
//}
//
//bool16 LayerPanelUtils::CanDeleteTargetLayers(IPMUnknown* targetWidget)
//{
//	if(TargetWidgetImpliesLayer(targetWidget))
//		return CanDeleteTargetLayers(targetWidget);
//	else
//		return CanDeleteTargetPageItem(targetWidget);
//}


ErrorCode LayerPanelUtils::DuplicateSelectedLayers()
{
	ErrorCode errorCode = kFailure;

	InterfacePtr<ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
	if (layoutData)
	{
		ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		cmdSeq->SetName("#DuplicatLayersCmd");
		UIDList targetUIDList(::GetDataBase(layoutData->GetDocument()));
		LayerPanelUtils::GetTargetLayers(targetUIDList);
		bool activateDuplicatedLayer = false;
		if(targetUIDList.Length() == 1)
		{
			if(targetUIDList[0] ==  layoutData->GetActiveDocLayerUID())
				activateDuplicatedLayer =  true;
		}
		for(int32 uidIndex = 0; uidIndex < targetUIDList.Length(); ++uidIndex)
		{
			UIDList listOfOne(targetUIDList.GetRef(uidIndex));

			InterfacePtr<const ILayerList> layerList(layoutData->GetDocument(), UseDefaultIID());
			int32 layerIndex = Utils<ILayerUIUtils>()->GetUILayerIndex(layerList,targetUIDList[uidIndex]);
			
			UIDRef layerToBeBelow;
			if(layerIndex >= 1)
			{
				InterfacePtr<const IDocumentLayer> layerAbove(Utils<ILayerUIUtils>()->QueryNthUILayer(layerList,layerIndex - 1));
				layerToBeBelow = ::GetUIDRef(layerAbove);
			}
			errorCode = Utils<Facade::ILayerFacade>()->MoveLayers(listOfOne,layerToBeBelow,kTrue);
		}
		if(errorCode == kSuccess && activateDuplicatedLayer)
		{
			LayerPanelUtils::DoSetActiveLayer(targetUIDList.GetRef(0),layoutData);
		}
		CmdUtils::EndCommandSequence(cmdSeq);
	}
		
	return errorCode;
}

void LayerPanelUtils::DoSetActiveLayer(const UIDRef& newActiveLayer, ILayoutControlData* forThisLayout)
{
	InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetActiveLayerCmdBoss));
	cmd->SetItemList(UIDList(newActiveLayer));
	InterfacePtr<ILayoutCmdData> data(cmd, IID_ILAYOUTCMDDATA);
	data->Set(UIDRef(newActiveLayer.GetDataBase(),newActiveLayer.GetDataBase()->GetRootUID()), forThisLayout);
	CmdUtils::ProcessCommand(cmd);
}

// This function returns a pipeline command made up of
// a new layer command, a set active layer command, and
// potentially a move layer command depending on the desired
// layer location.
ICommand* LayerPanelUtils::CreateNewLayerCommand(LayerLocation location, IDocumentLayer* targetNewLayer)
{
	IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
	IDocument* frontDocument = context->GetContextDocument();

	ICommand* cmd = nil;
	if (frontDocument)
	{
		cmd = CmdUtils::CreateCommand(kPipelineSequenceCmdBoss);
		InterfacePtr<ICmdCollection> cmdList(cmd, IID_ICMDCOLLECTION);

		// Create a new layer in the frontmost document
		ICommand * newLayerCmd = CmdUtils::CreateCommand(kNewLayerCmdBoss);
		InterfacePtr<INewLayerCmdData> layerData(newLayerCmd, IID_INEWLAYERCMDDATA);
		layerData->Set(::GetUIDRef(frontDocument));

		// Specify that the new layer is created above the active layer
		InterfacePtr<ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
		if (location == kAboveActive)
		{
			InterfacePtr<IDocumentLayer> activeLayer(Utils<ILayerUIUtils>()->QueryContextActiveLayer(context));
			InterfacePtr<IUIDData> uidLayerData(newLayerCmd, UseDefaultIID());
			uidLayerData->Set(activeLayer);
		}

		cmdList->Append(newLayerCmd);

		// The new layer will be the active layer for the frontmost view
		ICommand *setActiveLayer = CmdUtils::CreateCommand(kSetActiveLayerCmdBoss);
		InterfacePtr<ILayoutCmdData> activeLayerData(setActiveLayer, IID_ILAYOUTCMDDATA);
		activeLayerData->Set(::GetUIDRef(frontDocument), layoutData);
		cmdList->Append(setActiveLayer);
		
		// Now move the layer to the desired location. If location == kOnTop,
		// no need to move layer because the default is on top of all the layers.
		// Likewise for kAboveActive, that case is handle above as well.
		if (location == kBelowActive)
		{
			ICommand *moveLayer = CmdUtils::CreateCommand(kMoveLayerCmdBoss);
			InterfacePtr<IUIDData> uidData(moveLayer, IID_IUIDDATA);
			
			InterfacePtr<ILayerList> layerList(frontDocument, UseDefaultIID());
			
			// Use the provided target layer for above/below if non nil
			// Otherwise use document's active layer as basis for new layer location.
			InterfacePtr<IDocumentLayer> activeLayer(Utils<ILayerUIUtils>()->QueryContextActiveLayer(context));

			if (location == kBelowActive)
			{
				uidData->Set(targetNewLayer == nil ? activeLayer : targetNewLayer);
			}
			else
			{
				int32 targetPos = layerList->GetLayerIndex(targetNewLayer == nil ? activeLayer : targetNewLayer);
				int32 numLayers = layerList->GetCount();
				for (int32 i = targetPos + 1; i < numLayers; i++)
				{
					InterfacePtr<IDocumentLayer> nextLayer(layerList->QueryLayer(i));
					if (nextLayer->IsUILayer())
					{
						uidData->Set(nextLayer);
						break;
					}
				}

				if (targetPos >= numLayers)
				{
					moveLayer->Release();
					moveLayer = nil;
				}
			}

			// If layer is going to be put at top of layer list, no need to move it.
			if (uidData->GetItemUID() == kInvalidUID)
				moveLayer->Release();
			else
				cmdList->Append(moveLayer);
		}
	}
	
	return cmd;
}

// Can the target layers be duplicated?
bool16 LayerPanelUtils::CanDuplicateTargetLayers(IPMUnknown* widget)
{
	InterfacePtr<IMemoryManager> memMgr(GetExecutionContextSession(), IID_IMEMORYMANAGER);
	if(memMgr->MemoryIsLow())
		return kFalse;
		
	if (LayerPanelUtils::GetCurrentLayerPanelDB(widget) != nil)
	{
		return kTrue;
	}
	else
	{
		return kFalse;
	}

}


// This function returns a compound command made up of either
// Show/Hide layer commands or Lock/Unlock layer command based
// on where the user clicked, and based on whether there are 
// any layers hidden or locked when the click happened.
ICommand* LayerPanelUtils::CreateShowLockCommand(IPMUnknown* widget, const IDocumentLayer* layerClicked, ActionID id)
{
	ICommand *cmd = CmdUtils::CreateCommand(kCompoundSequenceCmdBoss);
	InterfacePtr<ICmdCollection> cmdList(cmd, IID_ICMDCOLLECTION);

	IDataBase * docDB = LayerPanelUtils::GetCurrentLayerPanelDB(widget);
	InterfacePtr<ILayerList> layerList(docDB,docDB->GetRootUID(),UseDefaultIID());
	int32 numLayers = layerList->GetCount();
	for (int32 i = 0; i < numLayers; i++)
	{
		InterfacePtr<IDocumentLayer> docLayer(layerList->QueryLayer(i));
		if (docLayer->IsUILayer())
		{
			switch(id.Get())
			{
				case kShowAllLayersActionID:
				case kHideAllLayersActionID:
				{
					if ((id == kShowAllLayersActionID && !docLayer->IsVisible()) ||
						(id == kHideAllLayersActionID && docLayer->IsVisible()) )
					{
						ICommand *showCmd = CmdUtils::CreateCommand(kShowLayerCmdBoss);
						showCmd->SetItemList(UIDList(docLayer));
						InterfacePtr<IBoolData> data(showCmd, IID_IBOOLDATA);
						data->Set(id == kShowAllLayersActionID ? kTrue : kFalse);
						cmdList->Append(showCmd);
					}
					break;
				}
				case kHideOtherLayersActionID:
				{
					if ((docLayer == layerClicked && !docLayer->IsVisible()) || 
						(docLayer != layerClicked && docLayer->IsVisible()))
					{
						ICommand *showCmd = CmdUtils::CreateCommand(kShowLayerCmdBoss);
						showCmd->SetItemList(  UIDList(docLayer));
						InterfacePtr<IBoolData> data(showCmd, IID_IBOOLDATA);
						data->Set(!docLayer->IsVisible());
						cmdList->Append(showCmd);
					}
					break;
				}
				case kUnlockAllLayersActionID:
				case kLockAllLayersActionID:
				{
					if ((id == kUnlockAllLayersActionID && docLayer->IsLocked()) ||
						(id == kLockAllLayersActionID && !docLayer->IsLocked()) )
					{
						ICommand *lockCmd = CmdUtils::CreateCommand(kLockLayerCmdBoss);
						lockCmd->SetItemList(  UIDList(docLayer));
						InterfacePtr<IBoolData> data(lockCmd, IID_IBOOLDATA);
						data->Set(id == kUnlockAllLayersActionID ? kFalse : kTrue);
						cmdList->Append(lockCmd);
					}
					break;
				}
				case kLockOtherLayersActionID:
				{
					if ((docLayer == layerClicked && docLayer->IsLocked()) || 
						(docLayer != layerClicked && !docLayer->IsLocked()))
					{
						ICommand *lockCmd = CmdUtils::CreateCommand(kLockLayerCmdBoss);
						lockCmd->SetItemList(  UIDList(docLayer));
						InterfacePtr<IBoolData> data(lockCmd, IID_IBOOLDATA);
						data->Set(!docLayer->IsLocked());
						cmdList->Append(lockCmd);
					}
					break;
				}
			}
		}
	}
	
	if (id == kShowAllLayersActionID)
		cmd->SetName("Show All"); 
	else if (id == kHideOtherLayersActionID)
		cmd->SetName("Hide Others"); 
	else if (id == kUnlockAllLayersActionID)
		cmd->SetName("Unlock All"); 
	else if (id == kLockOtherLayersActionID)
		cmd->SetName("Lock Others"); 
	else if (id == kHideAllLayersActionID)
		cmd->SetName("Hide All"); 
	else if (id == kLockAllLayersActionID)
		cmd->SetName("Lock All"); 
	
	return cmd;
}

// This function returns a compound command made up of delete layer
// commands delete all the selected layers. The boolean determines whether
// to check and see if the layer(s) are used in the pub or not. If we
// check, and there are used layers, put up an alert and ask the user if
// they really want to delete the layers.
ICommand* LayerPanelUtils::CreateDeleteLayersCmd(bool16 checkIsUsed, IPMUnknown* targetWidget)
{
	ICommand *cmd = nil;
	PMString layerName;
	int32 numInUse = 0;
	LayerFlags howUsed = ILayerUtils::kLayerNotUsed;
	
	// Get a list of target layers
	IDataBase * docDB = LayerPanelUtils::GetCurrentLayerPanelDB(targetWidget);
	InterfacePtr<ILayerList> layerList(docDB,docDB->GetRootUID(),UseDefaultIID());
	UIDList targetUIDList(docDB);
	LayerPanelUtils::GetTargetLayers(targetUIDList, targetWidget);

	int32 numLayers = targetUIDList.Length();
	int32 numUILayers = Utils<ILayerUtils>()->CountExpendableUILayers(layerList);

	if (numLayers && numLayers != numUILayers)
	{
		cmd = CmdUtils::CreateCommand(kCompoundSequenceCmdBoss);
		InterfacePtr<ICmdCollection> cmdList(cmd, IID_ICMDCOLLECTION);

		// Delete all the selected layers
		for (int32 i = 0; i < numLayers; i++)
		{
			InterfacePtr<IDocumentLayer> docLayer(targetUIDList.GetRef(i), IID_IDOCUMENTLAYER);
			
			if (docLayer->IsExpendableLayer())
			{
				ICommand *deleteCmd = CmdUtils::CreateCommand(kDeleteLayerCmdBoss);
				deleteCmd->SetItemList(  UIDList(docLayer));
				cmdList->Append(deleteCmd);
				
				// Check if requested if this layer is used in the document
				if (checkIsUsed && !(howUsed == ILayerUtils::kLayerContainsBoth && numInUse > 1))
				{
					LayerFlags how = ILayerUtils::kLayerNotUsed;
					how |= Utils<ILayerUtils>()->IsLayerUsed(docLayer);
					if (how != ILayerUtils::kLayerNotUsed)
					{
						numInUse++;
						howUsed |= how;
						if (numInUse == 1)
							docLayer->GetName(&layerName);
					}
				}
			}
		}
		
		int32 numToDelete = cmdList->Length();		
		if (numToDelete)
		{
			// Ask user if requested and if there are actually some used layers
			if (checkIsUsed && numInUse)
			{
				PMString alertString;
		
				if (howUsed & ILayerUtils::kLayerHasPlaceGunOwnedItem)
				{
					alertString = "DeletingPlaceGunUsedLayer";
					alertString.Translate();
					CAlert::ModalAlert(alertString, 
						kOKString, 
						kNullString,  
						kNullString,  
						1, CAlert::eWarningIcon);
					cmd->Release();
					cmd = nil;
				}
				else 
				{
					if (numInUse == 1)
					{
						if (howUsed == ILayerUtils::kLayerContainsGuides)
							alertString = "DeleteOneGuideLayer";
						else
							alertString = "DeleteOneLayer";
						alertString.Translate();

						::ReplaceStringParameters(&alertString, layerName);
					}
					else
					{
						if (howUsed == ILayerUtils::kLayerContainsGuides)
							alertString = "DeleteGuideLayers";
						else
							alertString = "DeleteMultiLayers";
						alertString.Translate();
					}
					
					if (CAlert::ModalAlert(alertString, 
						kOKString, 
						kCancelString,  
						kNullString,  
						1, CAlert::eWarningIcon) != 1)
					{
						cmd->Release();
						cmd = nil;
					}
				}
			}

			if (cmd)
			{
				cmd->SetName("Layer Deletion"); 
			}
		}
		else
		{
			cmd->Release();
			cmd = nil;
		}
	}
	
	return cmd;
}

// This function returns a compound command made up of merge layer
// commands to combine the items from multiple document layers, followed
// by delete layer commands to delete all but the "merge to" layer.
// The "merge to" layer is the active layer.
ICommand* LayerPanelUtils::CreateMergeLayersCmd(IPMUnknown* targetWidget)
{
	ICommand *cmd = nil;
	
	// Get a list of target layers
	IDataBase * docDB = LayerPanelUtils::GetCurrentLayerPanelDB(targetWidget);
	UIDList targetUIDList(docDB);
	GetTargetLayers(targetUIDList, targetWidget);
	InterfacePtr<ILayerList> layerList(docDB,docDB->GetRootUID(),UseDefaultIID());

	int32 numSelectedLayers = targetUIDList.Length();
	if (numSelectedLayers > 1)
	{
		cmd = CmdUtils::CreateCommand(kCompoundSequenceCmdBoss);
		InterfacePtr<ICmdCollection> cmdList(cmd, IID_ICMDCOLLECTION);

		IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
		InterfacePtr<IDocumentLayer> activeLayer(Utils<ILayerUIUtils>()->QueryContextActiveLayer(context));

		// Merge all the layers onto the active layer
		UID activeLayerUID = ::GetUID(activeLayer);
		int32 activeIndex = layerList->GetLayerIndex(activeLayerUID);
		int32 layerIndex = -1;

		for (int32 i = 0; i < numSelectedLayers; i++)
		{
			UID layerUID = targetUIDList[i];
			layerIndex = layerList->GetLayerIndex(layerUID);
			if (layerIndex != activeIndex)
			{
				InterfacePtr<IDocumentLayer> docLayer(targetUIDList.GetRef(i), IID_IDOCUMENTLAYER);
				if (docLayer != activeLayer)
				{
					ICommand *mergeCmd = CmdUtils::CreateCommand(kMergeLayersCmdBoss);
					UIDList* mergeList = new UIDList(LayerPanelUtils::GetCurrentLayerPanelDB(targetWidget));
					mergeList->Append(activeLayerUID);	// Active layer goes in the list first
					mergeList->Append(::GetUID(docLayer));

					UIDListUtils::SetItemList_Deprecated(mergeCmd,mergeList);
					if (layerIndex > activeIndex)
						cmdList->Prepend(mergeCmd);
					else
						cmdList->Append(mergeCmd);
				}
			}
		}
		
		// Now delete all the selected layers except the active layer
		int32 curIndex = 0;
		int32 numToDelete = numSelectedLayers - 1;
		while (numToDelete)
		{
			InterfacePtr<IDocumentLayer> docLayer(targetUIDList.GetRef(curIndex), IID_IDOCUMENTLAYER);
			if (docLayer->IsExpendableLayer())
			{
				if (docLayer != activeLayer)
				{
					ICommand *deleteCmd = CmdUtils::CreateCommand(kDeleteLayerCmdBoss);
					deleteCmd->SetItemList(  UIDList(docLayer));
					cmdList->Append(deleteCmd);
					numToDelete--;
				}
			}
			else
			{
				numToDelete--;
			}
			curIndex++;
		}
		
		cmd->SetName("Merge Layers"); 
	}
	
	return cmd;
}

// Select the items on a layer. AddTo or Replace.
void LayerPanelUtils::DoSelectLayer(const IPMUnknown* widget, bool16 extendSelection, bool16 selectAllSelectedLayersIfThisLayerSelected)
{
	InterfacePtr<IDocumentLayer> layerClicked(LayerPanelUtils::QueryLayerFromPanelWidget(widget));

	// if the user holds down the cmd key while clicking on the selection proxy,
	// and the row they're clicking in is already selected, we want to select all the page items for all the selected rows.
	// we have to put the item from the clicked row in the list first so that we match the select or deselect behavior to the clicked item.
	UIDList layersToSelect(::GetDataBase(layerClicked));
	LayerPanelUtils::GetTargetLayers(layersToSelect, widget);
	if(!selectAllSelectedLayersIfThisLayerSelected || !layersToSelect.Contains(::GetUID(layerClicked)))
	{
		// just do the one layer clicked on.
		layersToSelect.erase(layersToSelect.begin(),layersToSelect.end());
		layersToSelect.push_back(::GetUID(layerClicked));
	}
	
	IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
	IControlView* frontView = context->GetContextView();
	InterfacePtr<ISelectionManager> selectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<ILayerSuite> iLayerSuite (selectionMgr, UseDefaultIID());
	InterfacePtr<ILayoutControlData> layoutData(frontView, UseDefaultIID());

	if(iLayerSuite && layoutData)
	{
		InterfacePtr<ISpread> spread(layoutData->GetSpreadRef(), UseDefaultIID());
		InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(layerClicked, nil, kFalse));
		InterfacePtr<IHierarchy> layerHierarchy(spreadLayer, UseDefaultIID());
		
		// If layer has no regular page item content, then try guide layer.
		// Also, if guides are selected, favor selecting guides.
		InterfacePtr<IGuideDataSuite> iGuideSuite(selectionMgr, UseDefaultIID());
		bool16 bGuidesSelected = iGuideSuite && iGuideSuite->AreGuidesSelected();

		bool16 bGuideLayerOnly = kFalse;
		if (layerHierarchy && !layerHierarchy->GetChildCount())
			bGuideLayerOnly = kTrue;

		if(extendSelection && iLayerSuite->AreAllItemsOnLayerSelected(layerClicked, frontView, bGuideLayerOnly || bGuidesSelected))
		{
			for(int32 i = 0; i<layersToSelect.Length(); ++i)
			{
				InterfacePtr<IDocumentLayer> layerToSelect(layersToSelect.GetRef(i),UseDefaultIID());
				iLayerSuite->DeselectAllItemsOnLayer(layerToSelect, frontView, bGuideLayerOnly || bGuidesSelected);
			}
		}
		else
		{
			for(int32 i = 0; i<layersToSelect.Length(); ++i)
			{
				InterfacePtr<IDocumentLayer> layerToSelect(layersToSelect.GetRef(i),UseDefaultIID());
				iLayerSuite->SelectAllItemsOnLayer(layerToSelect, frontView, bGuideLayerOnly || bGuidesSelected, (extendSelection || i > 0) ? Selection::kAddTo : Selection::kReplace);
			}
		}
	}
}

// Invoke the Layer Options or New Layer dialog based on the options parameter.
// kTrue for the Layer Options dialog, kFalse for New Layer dialog. List of target
// layers is obtained from targetWidget that invoked the dialog.
void LayerPanelUtils::InvokeLayerDialog(LayerDialogType dialogType, LayerLocation location, IPMUnknown* targetWidget, IDocumentLayer* targetNewLayer)
{
	if (!LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
	{
		RsrcID dialogID = kLayerOptionsDialogRsrcID;
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IDialogMgr> dialogMgr(app, IID_IDIALOGMGR);	
		IDialog* dialog = dialogMgr->CreateNewDialog(RsrcSpec(LocaleSetting::GetLocale(), kLayerPanelPluginID, kViewRsrcType, dialogID),
													IDialog::kMovableModal);
		IControlView* dialogView = dialog->GetDialogPanel();
		InterfacePtr<IDialogController> dialogController(dialogView, IID_IDIALOGCONTROLLER);

		// Set the dialog mode
		// IDType ISSUE: It would be nice to change this IIntData
		// to IActionIDData, but too risky right now.
		InterfacePtr<IIntData> dialogTypeData(dialogController, IID_IDIALOGTYPEDATA);
		dialogTypeData->Set(dialogType);

		// Set the layer location, used for New Layer
		InterfacePtr<IIntData> intData(dialogController, IID_IINTDATA);
		intData->Set(location);

		// Set the layer location, used for New Layer. Reference released in LayerOptionsDlgController::ClosingDialog
		InterfacePtr<IPMUnknownData> targetNewLayerData(dialogController, IID_ITARGETNEWLAYER);
		targetNewLayerData->SetPMUnknown(targetNewLayer);

		// Set the target widget for list of layers for Layer Options/Duplicate Layer to operate on
		InterfacePtr<IPMUnknownData> targetData(dialogController, UseDefaultIID());
		targetData->SetPMUnknown(targetWidget);

		// Set appropriate window title based on mode
		InterfacePtr<IWindow> window(dialog, IID_IWINDOW);
		switch (dialogType)
		{
			case kLayerOptionsDialog:
				window->SetTitle("Layer Options"); break;
			case kNewLayerDialog:
				window->SetTitle("New Layer"); break;
			default:
				ASSERT_FAIL("Unknown Dialog type");
		}

		dialog->SetDialogFocusingAlgorithm(IDialog::kNoAutoFocus); // prevent focus from starting in color drop down.
		dialog->Open();
	}
}

IDocumentLayer* LayerPanelUtils::QueryLayerFromPanelWidget(const IPMUnknown* widget)
{
	IDataBase * frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(widget);
	if (frontDocDB)
	{
		InterfacePtr<const IWidgetParent>	widgetParent(widget, UseDefaultIID());
		InterfacePtr<const ITreeNodeIDData>	nodeData((ITreeNodeIDData*)widgetParent->QueryParentFor(IID_ITREENODEIDDATA));
		if(nodeData)
		{
			TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
			if(uidNode->IsLayerEntry())
			{
				InterfacePtr<const ILayerList> layerList(frontDocDB,frontDocDB->GetRootUID(), UseDefaultIID());
				UID	layerUID = uidNode->GetUID();
				int32	layerIndex	= layerList->GetLayerIndex(layerUID);
				return layerList->QueryLayer(layerIndex);
			}
		}
	}
	return nil;
}

static const IHierarchy* QueryUppermostAncestorSupportingAppearanceList(const IHierarchy* piHier)
{
	IHierarchy* upperMostHierSupportingAppearanceList = nil;
	InterfacePtr<IHierarchy> parentHier(piHier->QueryParent());
	while(parentHier)
	{
		InterfacePtr<IPMUnknown> appearanceList(parentHier,IID_IAPPEARANCELIST);
		if(appearanceList)
		{
			if(upperMostHierSupportingAppearanceList)
				upperMostHierSupportingAppearanceList->Release();
			
			upperMostHierSupportingAppearanceList = parentHier;
			upperMostHierSupportingAppearanceList->AddRef();
			
		}
		parentHier.reset(parentHier->QueryParent());
	}
		
	return upperMostHierSupportingAppearanceList;
}

// walks up the hierarchy to find the top most item supporting IID_IAPPEARANCELIST, then checks if this thing is among the visible descendents of this MSO or Button
static bool IsItemHiddenInHierarchy(const IHierarchy* piHier)
{
	InterfacePtr<const IHierarchy> ancestorHier(QueryUppermostAncestorSupportingAppearanceList(piHier));
	if(ancestorHier)
	{
		UIDList descendents(::GetDataBase(ancestorHier));
		ancestorHier->GetDescendents(&descendents,IID_IHIERARCHY);
		if(descendents.Contains(::GetUID(piHier)))
			return false;
		else
			return true;
	}
	return false;
}


// In various places, we're notified about things changing which we aren't displaying in our Tree.
// This function will only inval nodes which should really be in our tree.
void LayerPanelUtils::InvalidateNodeForPageItem(ITreeViewMgr* treeViewMgr,IDataBase* db, UID piUID, bool rebuildChildrenToo)
{
	// There are a number of situations where we get notifications for UIDs which aren't in our tree(yet or anymore).
	// Undo of creation, or creation of guides, or selection changes after item creation/deletion/hierachy changes.
	// The easiest thing to do here would be to call ITreeViewMgr->Search() to determine if the node is actually in our tree, but that potentially walks the entire tree, which can be very expensive.
	// instead we've just hard coded a bunch of checks to see if this thing should be in our tree still or not.
	if(db->IsValidUID(piUID)) 
	{
		// Also have to check if this thing is filtered out of our tree. Guides are part of the hierarchy, and can be locked, but aren't shown in our tree.
		InterfacePtr<const IHierarchy> piHier(db,piUID,UseDefaultIID());
		if(piHier)
		{
			InterfacePtr<const ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
			if(!layoutData)
				return; // if no active spread, we're not showing any page items in the layers panel.
				
			// media(movies,sounds), images are not shown in the panel
			if(Utils<IPageItemTypeUtils>()->IsMedia(piHier))
				return;
			InterfacePtr<const IPageItemAdapter> iPageItemAdapter(piHier,UseDefaultIID());
			if(iPageItemAdapter)
				return; // we don't show the inline wrapper boss
			
			if(IsItemHiddenInHierarchy(piHier))
				return; // filter out inactive button/MSO states
				
			if(Utils<IPageItemTypeUtils>()->IsPlacedInsideText(piHier) && !Utils<IPageItemTypeUtils>()->IsGraphic(piHier))
			{
				InterfacePtr<const IHierarchy> parentHier(piHier->QueryRoot());
				InterfacePtr<const IPageItemAdapter> parentInlineData(parentHier,UseDefaultIID());
				ASSERT_MSG(parentInlineData,"How can we be in an inline hierarchy, and not be able to get IPageItemAdapter?");
				InterfacePtr<const ITextFrameColumn> textCol(parentInlineData->QueryTextFrame());	
				if(!textCol)
					return; // we don't show inlines unless they're in a text frame.
			}
			else if(Utils<IPageItemTypeUtils>()->IsGraphic(piHier))
				return;
					
			InterfacePtr<const ISpreadLayer> itemsSpreadLayer((ISpreadLayer *) Utils<ILayoutUtils>()->QueryParentFor(piHier, ISpreadLayer::kDefaultIID));
			if(layoutData->GetSpreadRef().GetUID() != piHier->GetSpreadUID())
				return; // we've gotten some notification for something not on the current spread. Ignore it.
			
			if(!Utils<IPageItemTypeUtils>()->IsPlacedInsideText(piHier) && (!itemsSpreadLayer || itemsSpreadLayer->GetIsGuideLayer()))
				return;
			else
			{
#ifdef DEBUG				
				DebugClassUtilsBuffer classBuf;
				TRACEFLOW("LayerPanel","InvalidateNodeForPageItem invalidating node for UID %d, which is of class %s\n",piUID.Get(),DebugClassUtils::GetIDName(&classBuf,db->GetClass(piUID)));
#endif				
				NodeID changedNode = LayerTreeUIDNodeID::Create(piUID,kFalse);
				if(rebuildChildrenToo)
					treeViewMgr->RefreshSubTree(changedNode);
				else
					treeViewMgr->NodeChanged(changedNode);
			}
		}
	}
}

bool16 LayerPanelUtils::SelectAssociatedItemsInLayout(IPMUnknown* widget, bool extendSelection, bool selectChildrenInstead, bool selectAllSelectedInPanel)
{
	InterfacePtr<const IWidgetParent>	widgetParent(widget, UseDefaultIID());
	InterfacePtr<const ITreeNodeIDData>	nodeData((ITreeNodeIDData*)widgetParent->QueryParentFor(IID_ITREENODEIDDATA));
	if(nodeData)
	{
		TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(nodeData->Get());
		if(uidNode->IsLayerEntry())
		{
			// With shift key down, extend selection, otherwise replace it.

			LayerPanelUtils::DoSelectLayer(widget, extendSelection,selectAllSelectedInPanel);	
			return kTrue;
		}
		else
		{
			// not a layer - this is some sort of page item. Click on proxy area should select item in layout.
			InterfacePtr<ILayoutSelectionSuite>    layoutSuite ( static_cast<ILayoutSelectionSuite*>(Utils<ISelectionUtils>()->QueryActiveLayoutSelectionSuite()));
			if (layoutSuite)
			{
				IDataBase * frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(widget);
				if (frontDocDB)
				{
					UIDList piToSelect(frontDocDB);
					bool selectedChildren = false;
					if(selectChildrenInstead) // if option key is down, select the hierarchy children of this item.
					{
						InterfacePtr<const IHierarchy> hier(frontDocDB,uidNode->GetUID(),UseDefaultIID());
						if(Utils<IPageItemTypeUtils>()->IsGroup(hier) || Utils<IPageItemTypeUtils>()->IsGraphicFrame(hier) )
						{
							for(int32 i = hier->GetChildCount() - 1; i >=0; --i)
							{
								UIDRef oneChildRef(frontDocDB,hier->GetChildUID(i));
								if(!IsItemOrAncestorLockedOrHidden(oneChildRef))
									piToSelect.push_back(oneChildRef.GetUID());
							}
						}
					}
					else if(selectAllSelectedInPanel)
					{	
						// if the user holds down the cmd key while clicking on the selection proxy,
						// and the row they're clicking in is already selected, we want to select all the page items for all the selected rows.
						// we have to put the item from the clicked row in the list first so that we match the select or deselect behavior to the clicked item.
						UIDList piSelectedInPanel = GetPageItemsSelectedInPanel(widget, frontDocDB);
						if(piSelectedInPanel.Contains(uidNode->GetUID()))
						{
							piToSelect.push_back(uidNode->GetUID());
							for(int32 i = 0; i<piSelectedInPanel.Length(); ++i)
							{
								if(piSelectedInPanel[i] != uidNode->GetUID())
									piToSelect.push_back(piSelectedInPanel[i]);
							}
						}

					}	
					
					if(piToSelect.size() == 0)
					{
						UIDRef piRef(frontDocDB,uidNode->GetUID());
						if(!IsItemOrAncestorLockedOrHidden(piRef))
							piToSelect.push_back(piRef.GetUID());
					}
						
					if(piToSelect.size() == 0)
						return kFalse;
						
					if(extendSelection && layoutSuite->IsPageItemSelected(piToSelect[0]))
					{
						layoutSuite->DeselectPageItems(piToSelect);
					}
					else
					{
						// first make sure we blow away any non-layout selection, if one exists.
						InterfacePtr<const ISelectionManager> selectionManager ( Utils<ISelectionUtils>()->QueryActiveSelection());
						if(!selectionManager->SelectionExists(kNewLayoutSelectionBoss, ISelectionManager::kUniqueSelection))
						{
							selectionManager->DeselectAll (nil);
						}
						 
						layoutSuite->SelectPageItems(piToSelect,extendSelection ? Selection::kAddTo : Selection::kReplace,Selection::kScrollIntoViewIfNecessary);
					}
					return kTrue;
				}
			}
			
		}
	}
	return kFalse;
}

NodeID_rv LayerPanelUtils::GetLayerTreeNodeFromSubwidget(const IPMUnknown* widget)
{
	InterfacePtr<const ITreeNodeIDData>	nodeData(widget,UseDefaultIID());
	if(nodeData)
		return nodeData->Get();
	InterfacePtr<const IWidgetParent>	widgetParent(widget, UseDefaultIID());
	InterfacePtr<const ITreeNodeIDData>	parentNodeData((ITreeNodeIDData*)widgetParent->QueryParentFor(IID_ITREENODEIDDATA));
	return parentNodeData->Get();
}

ColorArray LayerPanelUtils::GetLayerColorForWidget(IPMUnknown* widget)
{
	IDataBase * frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(widget);
	if (frontDocDB)
	{
		InterfacePtr<const IWidgetParent>	widgetParent(widget, UseDefaultIID());
		InterfacePtr<const ITreeNodeIDData>	nodeData((ITreeNodeIDData*)widgetParent->QueryParentFor(IID_ITREENODEIDDATA));
		if(nodeData)
		{
			NodeID treeNode = nodeData->Get();
			TreeNodePtr<const LayerTreeUIDNodeID>	uidNode(treeNode);
			UID layerUID = kInvalidUID;
			InterfacePtr<const ITreeViewHierarchyAdapter> treeAdapter((ITreeViewHierarchyAdapter*)widgetParent->QueryParentFor(ITreeViewHierarchyAdapter::kDefaultIID));
			while(uidNode && !uidNode->IsLayerEntry())
			{
				treeNode = treeAdapter->GetParentNode(treeNode);
				TreeNodePtr<const LayerTreeUIDNodeID>	layerTreeNode(treeNode);
				uidNode = layerTreeNode;
			}
			if (uidNode)
				layerUID = uidNode->GetUID();
				
			UIDRef layerRef(frontDocDB, layerUID);
			if(layerUID != kInvalidUID && layerRef.ExistsInDB())
			{
				InterfacePtr<const IDocumentLayer> docLayer(frontDocDB,layerUID,UseDefaultIID());
				if(docLayer)
					return Utils<IUIColorUtils>()->GetRGBColorValue(frontDocDB, docLayer->GetColorUID() );
			}
		}
	}

	ColorArray	color;
	color.push_back(0.0);
	color.push_back(0.0);
	color.push_back(0.0);
	return color;
}

static UIDList GetListOfOtherPageItems(IPMUnknown* anyPanelWidget, UID pageItemUID)
{
	UIDList otherPIList(LayerPanelUtils::GetCurrentLayerPanelDB(anyPanelWidget));
	InterfacePtr<const ITreeViewHierarchyAdapter> treeAdapter((ITreeViewHierarchyAdapter*)Utils<IWidgetUtils>()->QueryRelatedWidget(anyPanelWidget,kLayerPanelTreeWidgetID,ITreeViewHierarchyAdapter::kDefaultIID));

	NodeID piNode = LayerTreeUIDNodeID::Create(pageItemUID,kFalse);
	NodeID parentTreeNode = treeAdapter->GetParentNode(piNode);

	uint32 numChildNodes = treeAdapter->GetNumChildren(parentTreeNode);
	for(uint32 i = 0; i < numChildNodes; ++i)
	{
		NodeID childNode = treeAdapter->GetNthChild(parentTreeNode,i);
		TreeNodePtr<const LayerTreeUIDNodeID>	childPINode(childNode);
		if(childPINode->GetUID() != pageItemUID)
			otherPIList.push_back(childPINode->GetUID());
	}
	return otherPIList;
}


bool16 LayerPanelUtils::AreAllOtherPageItemsHidden(IPMUnknown* anyPanelWidget, UID pageItemUID)
{
	UIDList otherPIList = GetListOfOtherPageItems(anyPanelWidget,pageItemUID);
	
	// figure out if we're showing or hiding others.
	bool othersAllHidden = true;
	for(int32 i = otherPIList.Length() - 1; i >= 0; --i)
	{
		if(Utils<Facade::IPageItemVisibilityFacade>()->GetVisibleState(otherPIList.GetRef(i)))
		{
			othersAllHidden = false;
			break;
		}
	}
	return othersAllHidden;
}

void LayerPanelUtils::ShowHideOtherPageItems(IPMUnknown* anyPanelWidget, UID pageItemUID)
{	
	// figure out if we're showing or hiding others.
	bool othersAllHidden = AreAllOtherPageItemsHidden(anyPanelWidget,pageItemUID);

	// now do it
	UIDList otherPIList =GetListOfOtherPageItems(anyPanelWidget,pageItemUID);
	for(int32 i = otherPIList.Length() - 1; i >= 0; --i)
	{
		if(othersAllHidden)
			Utils<Facade::IPageItemVisibilityFacade>()->Show(otherPIList.GetRef(i));
		else
			Utils<Facade::IPageItemVisibilityFacade>()->Hide(otherPIList.GetRef(i));
		
	}
}

bool16 LayerPanelUtils::AreAllOtherPageItemsLocked(IPMUnknown* anyPanelWidget, UID pageItemUID)
{
	UIDList otherPIList = GetListOfOtherPageItems(anyPanelWidget,pageItemUID);

	// figure out if we're showing or hiding others.
	return Utils<Facade::IPageItemLockFacade>()->AreItemsAllLocked(otherPIList);
}

void LayerPanelUtils::LockUnlockOtherPageItems(IPMUnknown* anyPanelWidget, UID pageItemUID)
{
	UIDList otherPIList = GetListOfOtherPageItems(anyPanelWidget,pageItemUID);

	if (otherPIList.Length() > 0)
	{
		// figure out if we're showing or hiding others.
		bool othersAllLocked = Utils<Facade::IPageItemLockFacade>()->AreItemsAllLocked(otherPIList); // could call AreAllOtherPageItemsLocked, but this will be faster...

		// now do it
		CmdUtils::SequencePtr seq;
		if(othersAllLocked)
		{
			seq->SetName("kUnlockOthersSequence");
			Utils<Facade::IPageItemLockFacade>()->UnlockPageItems(otherPIList);
		}
		else
		{
			seq->SetName("kLockOthersSequence");
			Utils<Facade::IPageItemLockFacade>()->LockPageItems(otherPIList);
		}
	}
}

bool16 LayerPanelUtils::AreThereAnyOthers(IPMUnknown* anyPanelWidget, UID pageItemUID)
{
	UIDList otherPIList = GetListOfOtherPageItems(anyPanelWidget,pageItemUID);
	return (otherPIList.Length() > 0);

}


bool16 LayerPanelUtils::ValidateNewLayerName(IDataBase* docDB, const IDocumentLayer* optionalLayerBeingRenamed, const PMString &newName, PMString& errorString)
{
	if (newName.IsNull())
	{
		// Do not allow an empty layer name string or a name with all spaces.
		errorString = "EmptyLayerName";
		return kFalse;
	}
	else
	{
		InterfacePtr<const ILayerList> layerList(docDB,docDB->GetRootUID(),UseDefaultIID());
		PMString layerName;

		if (layerList)
		{
			int32 numLayers = layerList->GetCount();
			for (int32 i = 0; i < numLayers; i++)
			{
				// For each existing layer, get the name and compare it
				// against the newly entered name, looking for duplicates.
				// No need to check the layer we may be editing (thus the
				//  check against optionalLayerBeingRenamed).
				InterfacePtr<const IDocumentLayer> layer(layerList->QueryLayer(i));
				if (layer && layer != optionalLayerBeingRenamed)
				{
					layer->GetName(&layerName);
					if (newName == layerName)
					{
						errorString = "DuplicateLayer";

						return kFalse;
					}
				}
			}
		}
	}
	return kTrue;
}

IDataBase* LayerPanelUtils::GetCurrentLayerPanelDB(const IPMUnknown* anyPanelWidget)
{
	if(anyPanelWidget)
	{
		InterfacePtr<const IUIDData> layerPanelDocData(anyPanelWidget,IID_ILAYERPANELDOCUMENTDATA);
		if(layerPanelDocData)
			return layerPanelDocData->GetItemDataBase();

		InterfacePtr<const IWidgetParent> wp(anyPanelWidget,UseDefaultIID());
		if(wp)
		{
			InterfacePtr<const IUIDData> parentWidgetLayerPanelDocData((IUIDData*)wp->QueryParentFor(IID_ILAYERPANELDOCUMENTDATA));
			return parentWidgetLayerPanelDocData->GetItemDataBase();
		}
	}
	else
	{
		InterfacePtr<const IApplication> app(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<const IPanelMgr> panelMgr(app->QueryPanelManager());

		IControlView* layerPanel = panelMgr->GetVisiblePanel(kLayerParentWidgetId);
		InterfacePtr<const IUIDData> layerPanelDocData(layerPanel,IID_ILAYERPANELDOCUMENTDATA);
		if(layerPanelDocData)
			return layerPanelDocData->GetItemDataBase();
	}
	return nil;
}

bool LayerPanelUtils::IsItemOrAncestorLockedOrHidden(const UIDRef & someItem)
{
	UIDList targetItemList(someItem);
	if(Utils<Facade::IPageItemLockFacade>()->IsLockedAndNotSelectable(targetItemList))
		return true;
	if(Utils<Facade::IPageItemVisibilityFacade>()->IsHidden(someItem)) // does not include layer
		return true;
	if(Utils<Facade::IPageItemLockFacade>()->IsAnyAncestorLocked(someItem)) // includes layer
		return true;
		
	InterfacePtr<const IHierarchy> itemHier(someItem, UseDefaultIID());
	InterfacePtr<const ISpreadLayer> spreadLayer(someItem.GetDataBase(), itemHier->GetLayerUID(), UseDefaultIID());
	return !spreadLayer->IsVisible();
}

UIDList LayerPanelUtils::GetPageItemsSelectedInPanel(const IPMUnknown* somePanelWidget, IDataBase* frontDocDB)
{

	if(frontDocDB == nil)
		frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(somePanelWidget);
	UIDList listOfPageItems(frontDocDB);
			
	InterfacePtr<const ITreeViewController> treeController((ITreeViewController*)Utils<IWidgetUtils>()->QueryRelatedWidget(somePanelWidget,kLayerPanelTreeWidgetID,ITreeViewController::kDefaultIID));
	if (treeController)
	{
		NodeIDList selectedItems;
		treeController->GetSelectedItems(selectedItems);
		for (auto iter = selectedItems.rbegin(); iter != selectedItems.rend(); ++iter)
		{
			TreeNodePtr<const LayerTreeUIDNodeID>	piNode(*iter);
			if(!piNode->IsLayerEntry())
			{
				listOfPageItems.Append(piNode->GetUID());
			}
		}
	}
	return listOfPageItems;
}

UIDList LayerPanelUtils::GetPageItemsInDrag(const IPMUnknown* somePanelWidget, const IDragDropController* controller)
{	
	IDataBase * frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(somePanelWidget);
	UIDList listOfPageItems(GetPageItemsSelectedInPanel(somePanelWidget,frontDocDB));

	// figure out which page items we're moving. If the source for the drag is a selected page item, then we'll move all the selected page items. If not, we'll just move that one page item.
	InterfacePtr<const IDataExchangeHandler> handler(controller->QuerySourceHandler());
	InterfacePtr<const IUIDData> uidData(handler,UseDefaultIID());
	UID dragSourceUID = uidData->GetItemUID();
	
	bool foundSourceInSelection = false;
	for (int32 i = listOfPageItems.Length() - 1; i >= 0; --i)
	{
		if(listOfPageItems[i] == dragSourceUID)
		{
			foundSourceInSelection = true;
			break;
		}
	}
	if(!foundSourceInSelection)
	{
		listOfPageItems.Clear();
		listOfPageItems.push_back(dragSourceUID);
	}
	
	return listOfPageItems;

}

void LayerPanelUtils::SetSmallRow(IBoolData* rowSizeBool, bool newValue)
{
	if(rowSizeBool->GetBool() != (bool16)newValue)
	{
		rowSizeBool->Set((bool16)newValue);
		
		InterfacePtr<ITreeViewMgr>	treeViewMgr(rowSizeBool, UseDefaultIID());
		treeViewMgr->ChangeRoot();
		
		// fix up the thumb scroll size.
		InterfacePtr<const ITreeViewWidgetMgr> treeWidgetMgr(rowSizeBool, UseDefaultIID());
		InterfacePtr<ITreeAttributes> treeAttr(treeWidgetMgr, UseDefaultIID());
		PMReal h = treeWidgetMgr->GetNodeWidgetHeight(kInvalidNodeID);
		int32 height = ToInt32(h);
		treeAttr->SetScrollAmount(ITreeAttributes::kVerticalScrollBar, height, height);  // this will call ChangeRoot()

								
		// this next bit is a little unusual. Toggling the row size changes our min max size, but we only recalculate that during panel resize usually...so we have to force a recalculation of our min/max size by calling UpdateOWLPaletteSizes()
		InterfacePtr<const IWidgetParent> wp(rowSizeBool,UseDefaultIID());
		InterfacePtr<IOWLPaletteSizer> palSizer((IOWLPaletteSizer*)wp->QueryParentFor(IOWLPaletteSizer::kDefaultIID));
		palSizer->UpdateOWLPaletteSizes();
	}
}

PMString LayerPanelUtils::GetDefaultPageItemElementName(const IHierarchy* piHier)
{
	Utils<Facade::IPageItemNameFacade> pinFacade;
	PMString itemName;
	UIDRef piRef = ::GetUIDRef(piHier);
	bool usedDefaultName = false;
	
	itemName.SetString(pinFacade->GetUserAssignedPageItemName(piRef));
	if(itemName.IsEmpty())
	{
		itemName = pinFacade->GetDefaultPageItemName(piRef);
		usedDefaultName = true;
	}
	
	if(!pinFacade->IsPageItemNameUserAssignable(piRef))
	{
		itemName.Translate();
		itemName.Insert("[");
		itemName.Append("]");
	} 
	else if(usedDefaultName)
	{
		itemName.Translate();
		itemName.Insert("<");
		itemName.Append(">");
	}
	
	return itemName;
}

bool16 LayerPanelUtils::CanLockOtherPageItems(IPMUnknown* anyPanelWidget, UID pageItemUID)
{
	UIDList others = GetListOfOtherPageItems(anyPanelWidget, pageItemUID);
	if(others.IsEmpty())
		return kFalse;

	return Utils<Facade::IPageItemLockFacade>()->CanLock(others);
}

bool16 LayerPanelUtils::CanUnlockOtherPageItems(IPMUnknown* anyPanelWidget, UID pageItemUID)
{
	UIDList others = GetListOfOtherPageItems(anyPanelWidget, pageItemUID);
	if(others.IsEmpty())
		return kFalse;

	return Utils<Facade::IPageItemLockFacade>()->CanUnlock(others);
}

