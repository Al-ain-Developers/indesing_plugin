//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelMenuComponent.cpp $
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

#include "IActionStateList.h"
#include "IBoolData.h"
#include "ICmdCollection.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "ILayerList.h"
#include "ILayerPrefs.h"
#include "ILayerPrefsCmdData.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "ISession.h"
#include "IActiveContext.h"
#include "IWidgetParent.h"
#include "IBoolData.h"
#include "ITreeNodeIDData.h"
#include "IShowPageItemUtils.h"
#include "ISelectionUtils.h"
#include "IPageItemNameFacade.h"

// ----- Includes -----

#include "CActionComponent.h"
#include "LayerPanelDefs.h"
#include "UIDList.h"
#include "CAlert.h"
#include "K2Vector.tpp"

// ----- Utility files -----

#include "CmdUtils.h"
#include "EventUtilities.h"
#include "ILayoutUIUtils.h"
#include "ILayerUtils.h"
#include "ILayerUIUtils.h"
#include "IMenuUtils.h"
#include "LayerPanelUtils.h"
#include "IPalettePanelUtils.h"
#include "PreferenceUtils.h"
#include "StringUtils.h"
#include "ILayoutSelectionSuite.h"
#include "LayerTreeUIDNodeID.h"
#include "ITreeViewController.h"
#include "IPageItemScrapFacade.h"

// ----- ID.h files -----

#include "LayerID.h"
#include "LayerPanelID.h"
#include "LayoutUIID.h"
#include "widgetid.h"
#include "GenericID.h"

//========================================================================================
// CLASS LayerPanelMenuComponent
//========================================================================================

class LayerPanelMenuComponent : public CActionComponent
{
public:
	LayerPanelMenuComponent(IPMUnknown *boss);
	
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

private:
		virtual IDocumentLayer* QueryTargetLayer(IActiveContext* ac, IPMUnknown* widget);
};

CREATE_PMINTERFACE(LayerPanelMenuComponent, kLayerPanelMenuComponentImpl)

//========================================================================================
// CLASS LayerPanelMenuComponent
//========================================================================================

LayerPanelMenuComponent::LayerPanelMenuComponent(IPMUnknown *boss) :
	CActionComponent(boss)
{
}

UIDList GetPageItemUIDsSelectedInTree(IPMUnknown * widget, IPMUnknown* tree)
{
	IDataBase* frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(widget);

	UID uidAssociatedWithWidget = kInvalidUID;

	InterfacePtr<ITreeNodeIDData> nodeData((ITreeNodeIDData*)Utils<ILayoutUIUtils>()->QueryWidgetParentFor(widget, IID_ITREENODEIDDATA));
	if(nodeData)
	{
		TreeNodePtr<const LayerTreeUIDNodeID>	treeNode(nodeData->Get());
		if(!treeNode->IsLayerEntry())
			uidAssociatedWithWidget = treeNode->GetUID();
	}
	
	UIDList nodesSelectedInTree(frontDocDB);
	bool widgetIsSelected = false;
	InterfacePtr<const ITreeViewController> treeController(tree,UseDefaultIID());
	if (treeController)
	{
		NodeIDList selectedItems;
		treeController->GetSelectedItems(selectedItems);
		for(auto iter = selectedItems.rbegin(); iter != selectedItems.rend(); ++iter)
		{
			TreeNodePtr<const LayerTreeUIDNodeID>	treeNode(*iter);
			if(!treeNode->IsLayerEntry())
			{
				if(treeNode->GetUID() == uidAssociatedWithWidget)
					widgetIsSelected = true;
				nodesSelectedInTree.push_back(treeNode->GetUID());
			}
		}
	}
	
	// if they right click on a wiget, and that widget is one of the selected widgets, return all the selected widgets, but if they right click on a widget that is not selected, return just that one.
	if(widgetIsSelected || uidAssociatedWithWidget == kInvalidUID)
		return nodesSelectedInTree;
	else if(uidAssociatedWithWidget != kInvalidUID)
		return UIDList(frontDocDB, uidAssociatedWithWidget);
	else
		return UIDList();
		
}


void LayerPanelMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint /*mousePoint*/, IPMUnknown* widget)
{
	int32 count = listToUpdate->Length();
	IDocument* frontDoc = ac->GetContextDocument();
	InterfacePtr<ILayerPrefs> iLayerPrefs((ILayerPrefs*)::QuerySessionPreferences(IID_ILAYERPREFERENCES));
	InterfacePtr<IBoolData> iLayerUngroupPrefs((IBoolData*)::QuerySessionPreferences(IID_ILAYERUNGROUPPREFERENCES));

	bool16 bSmallPaletteRows = kFalse;
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kLayerParentWidgetId));
	if(!panelData)
		return;

	IControlView* treeView = panelData->FindWidget(kLayerPanelTreeWidgetID);
	InterfacePtr<const IBoolData> rowSizeBool(treeView, IID_ISMALLPALETTEROWSBOOLDATA);
	bSmallPaletteRows =  rowSizeBool->GetBool();

	if (!frontDoc)
	{
		// Most items are disabled in no pub state
		for(int i = 0; i < count; i++)
		{
			ActionID action = listToUpdate->GetNthAction(i);
			if (action == kPasteRemembersLayersActionID) 
			{
				if(iLayerPrefs->GetPasteRemembersLayers())
					listToUpdate->SetNthActionState(i,kEnabledAction|kSelectedAction);
				else
					listToUpdate->SetNthActionState(i,kEnabledAction);
			}
			else if (action == kUngroupRemembersLayersActionID)
			{
				if(iLayerUngroupPrefs->Get())
					listToUpdate->SetNthActionState(i,kEnabledAction|kSelectedAction);
				else
					listToUpdate->SetNthActionState(i,kEnabledAction);
			}
			else if (action == kSmallPaletteRowsActionID && panelData)
			{
				if(bSmallPaletteRows)
					listToUpdate->SetNthActionState(i,kEnabledAction|kSelectedAction);
				else
					listToUpdate->SetNthActionState(i,kEnabledAction);
			}
			else
			{
				ASSERT_FAIL("I shouldn't be called for this item(in no doc state)");
			}
		}
	}
	else
	{

		// Get a list of target layers
		UIDList targetUIDList(::GetDataBase(frontDoc));
		LayerPanelUtils::GetTargetLayers(targetUIDList, widget);
		
		int32 numSelected = targetUIDList.Length();

//		ASSERT_MSG(numSelected >= 1, "There should always be at least one selected layer!");
//		There may be no selected layer(s) if an XML structure window is forward.  In this case,
//		only PasteRemembersLayers and SmallPaletteRows are being asked to update in this function,
//		as the other are all already disabled due to kDisableIfNoFrontLayoutView flag in Menu.fr file.
		bool16 optionKeyDown = ::IsOptionAltKeyPressed();
		bool16 commandKeyDown = ::IsCommandKeyPressed();
		bool16 shiftKeyDown = ::IsShiftKeyPressed();

		int32 numLayers = 0;
		InterfacePtr<ILayerList> layerList(frontDoc,UseDefaultIID());
		numLayers = Utils<ILayerUtils>()->CountUILayers(layerList);

		// Get the name of the current active layer, or the layer that was clicked (used for context menus)
		InterfacePtr<IDocumentLayer> targetLayer(this->QueryTargetLayer(ac, widget));

		PMString targetLayerName, ampersandedTargetLayerName;
		if (targetLayer)
		{
			targetLayer->GetName(&targetLayerName);

			// Convert & to && if user-entered layer name contains &.
			// Prevents it from being interpreted as an accelerator.
			ampersandedTargetLayerName = targetLayerName;
			Utils<IMenuUtils>()->InsertAmpersandForDisplay(&ampersandedTargetLayerName);
		}
		
		UIDList pageItemsSelectedInTree = GetPageItemUIDsSelectedInTree(widget,treeView);
		PMString ampersandedPageItemName;
		if(pageItemsSelectedInTree.size() == 1)
		{
			ampersandedPageItemName = Utils<Facade::IPageItemNameFacade>()->GetUserAssignedPageItemName(pageItemsSelectedInTree.GetRef(0));
			if(ampersandedPageItemName.IsEmpty())
				ampersandedPageItemName = Utils<Facade::IPageItemNameFacade>()->GetDefaultPageItemName(pageItemsSelectedInTree.GetRef(0));
			ampersandedPageItemName.Translate();
			Utils<IMenuUtils>()->InsertAmpersandForDisplay(&ampersandedPageItemName);

		}
				
		PMString menuItemString;
		while (count--)
		{
			ActionID action = listToUpdate->GetNthAction(count);
			
			switch (action.Get())
			{
				case kNewLayerActionID:
				case kNewLayerContextActionID:
					{
					listToUpdate->SetNthActionState(count,kEnabledAction);
					
					// Specify that the new layer goes just above the active layer, CS5 change instead of always creating at top of list.
					// This matches Photoshop logic as well. 
					// Shortcuts are command key for layer below active layer and command + shift for top
					LayerPanelUtils::LayerLocation location = LayerPanelUtils::kAboveActive;	
					if (commandKeyDown)
						location = shiftKeyDown ? LayerPanelUtils::kOnTop : LayerPanelUtils::kBelowActive;

					if (location == LayerPanelUtils::kAboveActive)	// Specify that the new layer goes just above the active layer, CS5 change instead of always creating at top of list.
						menuItemString = "New Layer...";
					else if (location == LayerPanelUtils::kBelowActive)
						menuItemString = "New Layer Below \"^1\"...";
					else
						menuItemString = "New Top Layer...";
					
					menuItemString.Translate();
					if (location == LayerPanelUtils::kBelowActive)
						::ReplaceStringParameters(&menuItemString, ampersandedTargetLayerName);
					else
						menuItemString.SetTranslatable(kFalse);

					listToUpdate->SetNthActionName(count,menuItemString);
					break;
					}

				case kDuplicateLayerOrPageItemActionID:
				case kDuplicateLayerContextActionID:
				{
					if(pageItemsSelectedInTree.size())
					{
						if(Utils<Facade::IPageItemScrapFacade>()->CanDuplicatePageItems(pageItemsSelectedInTree))
							listToUpdate->SetNthActionState(count,kEnabledAction);
						if (pageItemsSelectedInTree.size() == 1 && !ampersandedPageItemName.IsEmpty())
						{
							menuItemString = "#DuplicatePI ^1 Menu";
							menuItemString.Translate();
							::ReplaceStringParameters(&menuItemString, ampersandedPageItemName);
						}
						else
							menuItemString = "#DuplicatePIMenu";
					}
					else
					{
						if(LayerPanelUtils::CanDuplicateTargetLayers(widget))
							listToUpdate->SetNthActionState(count,kEnabledAction);
						if (numSelected == 1)
						{
							menuItemString = "#Duplicate ^1 Menu";
							menuItemString.Translate();
							::ReplaceStringParameters(&menuItemString, ampersandedTargetLayerName);
						}
						else
							menuItemString = "#Duplicate LayersMenu";
					}
					listToUpdate->SetNthActionName(count,menuItemString);
					break;
				}
				
				case kDeleteLayerOrPageItemActionID:
				case kDeleteLayerContextActionID:
				{
					if(pageItemsSelectedInTree.size())
					{
						if(Utils<Facade::IPageItemScrapFacade>()->CanDeletePageItems(pageItemsSelectedInTree))
							listToUpdate->SetNthActionState(count,kEnabledAction);
						if (pageItemsSelectedInTree.size() == 1 && !ampersandedPageItemName.IsEmpty())
						{
							menuItemString = "#DeletePageItem \"^1\"";
							menuItemString.Translate();
							::ReplaceStringParameters(&menuItemString, ampersandedPageItemName);
						}
						else
							menuItemString = "#DeletePageItemsMenu";
					}
					else
					{
						if(LayerPanelUtils::CanDeleteTargetLayers(action.Get() == kDeleteLayerOrPageItemActionID ? panelData : widget))
							listToUpdate->SetNthActionState(count,kEnabledAction);
						if (numSelected == 1)
						{
							menuItemString = "Delete \"^1\"";
							menuItemString.Translate();
							::ReplaceStringParameters(&menuItemString, ampersandedTargetLayerName);
						}
						else
							menuItemString = "Delete Layers";
					}

					listToUpdate->SetNthActionName(count,menuItemString);
					break;
				}
				
				case kLayerOptionsActionID:
				case kLayerOptionsContextActionID:
					listToUpdate->SetNthActionState(count,kEnabledAction);
					if (numSelected == 1 && !ampersandedTargetLayerName.IsEmpty())
					{
						menuItemString = "Layer Options for \"^1\"...";
						menuItemString.Translate();
						::ReplaceStringParameters(&menuItemString, ampersandedTargetLayerName);
					}
					else
						menuItemString = "Layer Options...";

					listToUpdate->SetNthActionName(count,menuItemString);
					break;
				
				case kShowHideLayersActionID:
				{
					if(pageItemsSelectedInTree.size() && widget)
					{
						if(pageItemsSelectedInTree.size() == 1 && LayerPanelUtils::AreThereAnyOthers(widget,pageItemsSelectedInTree[0]))
						{
							listToUpdate->SetNthActionState(count,kEnabledAction);
						
							if (LayerPanelUtils::AreAllOtherPageItemsHidden(widget,pageItemsSelectedInTree[0]))
								menuItemString = "#ShowOthers";
							else
								menuItemString = "Hide Others";
						}
					}
					else
					{
						if(numLayers > 0 && LayerPanelUtils::GetCurrentLayerPanelDB(widget))
							listToUpdate->SetNthActionState(count,kEnabledAction);
						int32 numHidden = 0;
						if (Utils<ILayerUtils>()->AnyLayersHidden(frontDoc, &numHidden))
							menuItemString = "Show All Layers";
						else if (numHidden == 0 && numLayers == numSelected)
							menuItemString = "Hide All Layers";
						else
							menuItemString = "Hide Others";
					}
					//menuItemString.Translate();
					listToUpdate->SetNthActionName(count,menuItemString);
					break;
				}
				case kLockUnlockLayersActionID:
				{
					if(pageItemsSelectedInTree.size() && widget)
					{
						if(pageItemsSelectedInTree.size() == 1 && LayerPanelUtils::AreThereAnyOthers(widget,pageItemsSelectedInTree[0]))
						{
							if (LayerPanelUtils::AreAllOtherPageItemsLocked(widget,pageItemsSelectedInTree[0]))
							{	
								if(LayerPanelUtils::CanUnlockOtherPageItems(widget, pageItemsSelectedInTree[0]))
									listToUpdate->SetNthActionState(count,kEnabledAction);
								menuItemString = "#UnlockOthers";
							}
							else
							{
								if(LayerPanelUtils::CanLockOtherPageItems(widget, pageItemsSelectedInTree[0]))
									listToUpdate->SetNthActionState(count,kEnabledAction);
								menuItemString = "Lock Others";
							}
						}
					}
					else
					{
						if(numLayers > 0 && LayerPanelUtils::GetCurrentLayerPanelDB(widget))
							listToUpdate->SetNthActionState(count,kEnabledAction);
						int32 numLocked = 0;
						if (Utils<ILayerUtils>()->AnyLayersLocked(frontDoc, &numLocked))
							menuItemString = "Unlock All Layers";
						else if (numLocked == 0 && numLayers == numSelected)
							menuItemString = "Lock All Layers";
						else
							menuItemString = "Lock Others";
					}
					//menuItemString.Translate();
					listToUpdate->SetNthActionName(count,menuItemString);
					break;
				}
				case kPasteRemembersLayersActionID:
					if(iLayerPrefs->GetPasteRemembersLayers())
						listToUpdate->SetNthActionState(count,kEnabledAction|kSelectedAction);
					else
						listToUpdate->SetNthActionState(count,kEnabledAction);
					break;
				
				case kUngroupRemembersLayersActionID:
					if(iLayerUngroupPrefs->Get())
						listToUpdate->SetNthActionState(count,kEnabledAction|kSelectedAction);
					else
						listToUpdate->SetNthActionState(count,kEnabledAction);
					break;

				case kMergeLayersActionID:
				case kMergeLayersContextActionID:
					if(numSelected > 1)
						listToUpdate->SetNthActionState(count,kEnabledAction);
					break;
				
				case kDeleteUnusedLayersActionID:
					if(numLayers > 1)
						listToUpdate->SetNthActionState(count,kEnabledAction);
					break;

				case kSelectLayerContextActionID:
					if (targetLayer && targetLayer->IsVisible() && !targetLayer->IsLocked()  && !ampersandedTargetLayerName.IsEmpty())
					{
						listToUpdate->SetNthActionState(count,kEnabledAction);
						menuItemString = "Select Item(s) on \"^1\"";
						menuItemString.Translate();
						::ReplaceStringParameters(&menuItemString, ampersandedTargetLayerName);

						listToUpdate->SetNthActionName(count,menuItemString);
					}
					break;
				case kSelectZoomLayerPageItemActionID:
					{
						// if there's one page item selected in the tree, enable this menu item.
						if(pageItemsSelectedInTree.size() == 1)
						{
							listToUpdate->SetNthActionState(count,kEnabledAction);

							bool canSelect = !LayerPanelUtils::IsItemOrAncestorLockedOrHidden(pageItemsSelectedInTree.GetRef(0));
							if(canSelect)
								listToUpdate->SetNthActionName(count,"#SelectZoomLayerPageItemMenu");
							else
								listToUpdate->SetNthActionName(count,"#ZoomLockedPageItemMenu");
						}

					}
					break;
				case kSelectLayerPageItemActionID:
					{
						// if there's any unlocked page item selected in the tree, enable this menu item.
						if(pageItemsSelectedInTree.size())
						{
							if (pageItemsSelectedInTree.GetDataBase() == nil)
							{
								// nothing is selected, so exit.
								break;
							}
							bool canSelect = true;
							for(uint32 i = 0; i < pageItemsSelectedInTree.size(); ++i)
							{
								if(LayerPanelUtils::IsItemOrAncestorLockedOrHidden(pageItemsSelectedInTree.GetRef(i)))
								{
									canSelect = false;
									break;
								}
							}
							if(canSelect)
								listToUpdate->SetNthActionState(count,kEnabledAction);
						}

					}
					break;

				case kSmallPaletteRowsActionID:
					if(bSmallPaletteRows)
						listToUpdate->SetNthActionState(count,kEnabledAction|kSelectedAction);
					else
						listToUpdate->SetNthActionState(count,kEnabledAction);
					break;
			}
		}
	}
}


void LayerPanelMenuComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint /*mousePoint*/, IPMUnknown* widget)
{
	IDocument* frontDoc = ac->GetContextDocument();
	if (!frontDoc && actionID != kPasteRemembersLayersActionID && actionID != kSmallPaletteRowsActionID && actionID != kUngroupRemembersLayersActionID)
		return ;
	
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kLayerParentWidgetId));
	InterfacePtr<IDocumentLayer> targetLayer(this->QueryTargetLayer(ac, widget));

	bool16 optionKeyDown = ::IsOptionAltKeyPressed();
	bool16 commandKeyDown = ::IsCommandKeyPressed();
	bool16 shiftKeyDown = ::IsShiftKeyPressed();

	switch (actionID.Get())
	{
		case kDuplicateLayerOrPageItemActionID:
		case kDuplicateLayerContextActionID:
			{
				IControlView* treeView = panelData->FindWidget(kLayerPanelTreeWidgetID);
				UIDList pageItemsSelectedInTree = GetPageItemUIDsSelectedInTree(widget,treeView);
				if(pageItemsSelectedInTree.size())
					Utils<Facade::IPageItemScrapFacade>()->DuplicatePageItems(pageItemsSelectedInTree);
				else
					LayerPanelUtils::DuplicateSelectedLayers();
			}
			break;
		case kNewLayerActionID:
		case kLayerOptionsActionID:
		case kNewLayerContextActionID:
		case kLayerOptionsContextActionID:
		{
			// Determine the layer location (used for New Layer). 
			LayerPanelUtils::LayerLocation location = LayerPanelUtils::kAboveActive;	
			if (commandKeyDown)
				location = shiftKeyDown ? LayerPanelUtils::kOnTop : LayerPanelUtils::kBelowActive;

			// Operate on selected layers or context menu/right click layers
			IDocumentLayer* targetNewLayer = nil;
			LayerPanelUtils::LayerDialogType dialogType = LayerPanelUtils::kNewLayerDialog;
			if (actionID.Get() == kNewLayerActionID || actionID.Get() == kNewLayerContextActionID)
			{
				dialogType = LayerPanelUtils::kNewLayerDialog;
				targetNewLayer = targetLayer;
			}
			else if (actionID.Get() == kLayerOptionsActionID || actionID.Get() == kLayerOptionsContextActionID)
			{
				dialogType = LayerPanelUtils::kLayerOptionsDialog;
			}			
			InvokeLayerDialog(dialogType, location, widget, targetNewLayer);
			break;
		}
						
		case kDeleteLayerOrPageItemActionID:
		case kDeleteLayerContextActionID:
		{
			IControlView* treeView = panelData->FindWidget(kLayerPanelTreeWidgetID);
			UIDList pageItemsSelectedInTree = GetPageItemUIDsSelectedInTree(widget,treeView);
			if(pageItemsSelectedInTree.size())
				Utils<Facade::IPageItemScrapFacade>()->DeletePageItems(pageItemsSelectedInTree);
			else
			{
				InterfacePtr<ICommand> cmd(LayerPanelUtils::CreateDeleteLayersCmd(!optionKeyDown, actionID.Get() == kDeleteLayerOrPageItemActionID ? panelData : widget));
				if (cmd)
					CmdUtils::ProcessCommand(cmd);
			}
			break;
		}
			
		case kShowHideLayersActionID:
		case kLockUnlockLayersActionID:
		{
			IControlView* treeView = panelData->FindWidget(kLayerPanelTreeWidgetID);
			UIDList pageItemsSelectedInTree = GetPageItemUIDsSelectedInTree(widget,treeView);

			if(pageItemsSelectedInTree.size())
			{
				ASSERT_MSG(pageItemsSelectedInTree.size() == 1,"These menu items should not be enabled with more than one page item selected in the panel!");
				NodeID selectedPINode = LayerTreeUIDNodeID::Create(pageItemsSelectedInTree[0],kFalse);						
				TreeNodePtr<const LayerTreeUIDNodeID>	layerTreeNode(selectedPINode);
				if(actionID == kShowHideLayersActionID)
				{
					LayerPanelUtils::ShowHideOtherPageItems(widget,pageItemsSelectedInTree[0]);
				}
				else
				{
					LayerPanelUtils::LockUnlockOtherPageItems(widget,pageItemsSelectedInTree[0]);
				}
			}
			else
			{
				// Get a list of target layers
				UIDList targetUIDList(::GetDataBase(frontDoc));
				LayerPanelUtils::GetTargetLayers(targetUIDList, widget);
				
				int32 numSelected = targetUIDList.Length();
				ASSERT_MSG(numSelected >= 1, "There should always be at least one selected layer!");

				int32 numLayers = 0;
				InterfacePtr<ILayerList> layerList(frontDoc, IID_ILAYERLIST);
				numLayers = Utils<ILayerUtils>()->CountUILayers(layerList);

				ActionID menuID;
				if (actionID == kShowHideLayersActionID)
				{
					int32 numHidden;
					if (Utils<ILayerUtils>()->AnyLayersHidden(frontDoc, &numHidden))
						menuID = kShowAllLayersActionID;
					else if (numHidden == 0 && numLayers == numSelected)
						menuID = kHideAllLayersActionID;
					else
						menuID = kHideOtherLayersActionID;
				}
				else
				{
					int32 numLocked = 0;
					if (Utils<ILayerUtils>()->AnyLayersLocked(frontDoc, &numLocked))
						menuID = kUnlockAllLayersActionID;
					else if (numLocked == 0 && numLayers == numSelected)
						menuID = kLockAllLayersActionID;
					else
						menuID = kLockOtherLayersActionID;
				}

				InterfacePtr<ICommand> cmd (LayerPanelUtils::CreateShowLockCommand(widget,targetLayer, menuID));
				CmdUtils::ProcessCommand(cmd);
			}
			break;
		}
		case kPasteRemembersLayersActionID:
		{
			InterfacePtr<ILayerPrefs> iLayerPrefs((ILayerPrefs*)::QuerySessionPreferences(IID_ILAYERPREFERENCES));
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetLayerPrefsCmdBoss));
			InterfacePtr<ILayerPrefsCmdData> data(cmd, IID_ILAYERPREFSCMDDATA);
			data->Set(!iLayerPrefs->GetPasteRemembersLayers());
			CmdUtils::ProcessCommand(cmd);
			break;
		}

		case kUngroupRemembersLayersActionID:
		{
			InterfacePtr<IBoolData> iLayerUngroupPrefs((IBoolData*)::QuerySessionPreferences(IID_ILAYERUNGROUPPREFERENCES));
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetLayerUngroupPrefsCmdBoss));
			InterfacePtr<IBoolData> data(cmd, IID_ILAYERUNGROUPPREFSCMDDATA);
			data->Set(!iLayerUngroupPrefs->Get());
			CmdUtils::ProcessCommand(cmd);
			break;
		}

		case kMergeLayersActionID:
		case kMergeLayersContextActionID:
		{
			InterfacePtr<ICommand> cmd(LayerPanelUtils::CreateMergeLayersCmd(actionID.Get() == kMergeLayersActionID ? panelData : widget));
			if (cmd)
				CmdUtils::ProcessCommand(cmd);
			break;
		}
		case kDeleteUnusedLayersActionID:
		{	
			// See what document layers in pub are unused.
			// Make sure we don't removed them all.
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kCompoundSequenceCmdBoss));
			InterfacePtr<ICmdCollection> cmdList(cmd, IID_ICMDCOLLECTION);
			InterfacePtr<ILayerList> layerList(frontDoc, IID_ILAYERLIST);
			int32 numPossible = Utils<ILayerUtils>()->CountExpendableUILayers(layerList);
			int32 numLayers = layerList->GetCount();
			int32 numRemoved = 0;
			for (int32 i = 0; i < numLayers && numRemoved + 1 < numPossible; i++)
			{
				InterfacePtr<IDocumentLayer> docLayer(layerList->QueryLayer(i));
				if (docLayer->IsUILayer() && docLayer->IsExpendableLayer() && (Utils<ILayerUtils>()->IsLayerUsed(docLayer) == ILayerUtils::kLayerNotUsed))
				{
					ICommand* deleteCmd = CmdUtils::CreateCommand(kDeleteLayerCmdBoss);
					deleteCmd->SetItemList(  UIDList(docLayer));
					cmdList->Append(deleteCmd);
					numRemoved++;
				}
			}

			// If any layers were unused, delete them
			if (cmdList->Length())
			{
				cmd->SetName("Delete Unused Layers");
				CmdUtils::ProcessCommand(cmd);
			}
			break;
		}
		case kSelectLayerContextActionID:
		{
			LayerPanelUtils::DoSelectLayer(widget, ::IsShiftKeyPressed(),::IsOptionAltKeyPressed());
			break;
		}
		case kSelectLayerPageItemActionID:
		case kSelectZoomLayerPageItemActionID:
			{
				IControlView* treeView = panelData->FindWidget(kLayerPanelTreeWidgetID);
				UIDList pageItemsSelectedInTree = GetPageItemUIDsSelectedInTree(widget,treeView);
				ASSERT_MSG(pageItemsSelectedInTree.size() > 0,"These require a page item to be enabled!");

				bool canSelect = !LayerPanelUtils::IsItemOrAncestorLockedOrHidden(pageItemsSelectedInTree.GetRef(0));
			
				if(canSelect)
				{
					InterfacePtr<ILayoutSelectionSuite>    layoutSuite ( static_cast<ILayoutSelectionSuite*>(Utils<ISelectionUtils>()->QueryActiveLayoutSelectionSuite()));
					if (layoutSuite)
					{
						if (frontDoc)
						{
							// first make sure we blow away any non-layout selection, if one exists.
							InterfacePtr<const ISelectionManager> selectionManager ( Utils<ISelectionUtils>()->QueryActiveSelection());
							if(!selectionManager->SelectionExists(kNewLayoutSelectionBoss, ISelectionManager::kUniqueSelection))
							{
								selectionManager->DeselectAll (nil);
							}
							 
							layoutSuite->SelectPageItems(pageItemsSelectedInTree,::IsShiftKeyPressed() ? Selection::kAddTo : Selection::kReplace,Selection::kDontScrollLayoutSelection);
						}
					}
				}
				if(actionID == kSelectZoomLayerPageItemActionID)
					Utils<IShowPageItemUtils>()->Show(pageItemsSelectedInTree.GetDataBase(),pageItemsSelectedInTree[0]);
			}
			break;
		case kSmallPaletteRowsActionID:
		{
			IControlView* treeView = panelData->FindWidget(kLayerPanelTreeWidgetID);
			InterfacePtr<IBoolData> rowSizeBool(treeView, IID_ISMALLPALETTEROWSBOOLDATA);
			LayerPanelUtils::SetSmallRow(rowSizeBool, !rowSizeBool->GetBool());
			break;
		}
	}
}

IDocumentLayer* LayerPanelMenuComponent::QueryTargetLayer(IActiveContext* ac, IPMUnknown* widget)
{
	InterfacePtr<IDocumentLayer> targetLayer(Utils<ILayerUIUtils>()->QueryContextActiveLayer(ac));

	// "widget" passed into this function will hold element clicked on. Could have been initiated
	// via a context click. If so, use this layer instead of active layer.
	InterfacePtr<IWidgetParent> parentHolder(widget, UseDefaultIID());
	if (parentHolder)
	{
		InterfacePtr<IDocumentLayer> layerClicked(LayerPanelUtils::QueryLayerFromPanelWidget(widget));
		if (layerClicked)
		{
			targetLayer.reset(layerClicked.forget());
		}
	}

	if (targetLayer)
		targetLayer->AddRef();

	return targetLayer;
}




	
