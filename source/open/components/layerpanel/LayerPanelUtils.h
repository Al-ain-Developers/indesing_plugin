//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelUtils.h $
//  
//  Owner: psorrick
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

#pragma once
#ifndef __LayerPanelUtils__
#define __LayerPanelUtils__

class IDocumentLayer;
class ICommand;
class IPMUnknown;
class UIDList;
class ITreeViewMgr;
class ILayoutControlData;
class IEvent;
class IDragDropController;
class IBoolData;
class IHierarchy;

#include "IColorData.h"
#include "NodeID.h"

namespace LayerPanelUtils
{
	void SetSmallRow(IBoolData* rowData, bool newValue);

	void GetTargetLayers(UIDList& targetList, const IPMUnknown* targetWidget = nil);
	ErrorCode DuplicateSelectedLayers();

	bool16 CanDeleteTargetLayers(IPMUnknown* targetWidget);
	bool16 CanDuplicateTargetLayers(IPMUnknown* targetWidget);

	UIDList GetPageItemsInDrag(const IPMUnknown* somePanelWidget, const IDragDropController *controller);
	UIDList GetPageItemsSelectedInPanel(const IPMUnknown* somePanelWidget, IDataBase* frontDocDB);

	enum LayerLocation { kOnTop, kAboveActive, kBelowActive };
	ICommand* CreateNewLayerCommand(LayerLocation location, IDocumentLayer* targetNewLayer = nil);
	ICommand* CreateShowLockCommand(IPMUnknown* targetWidget, const IDocumentLayer* layerClicked, ActionID id);	// See LayerPanelID.h for ids
	ICommand* CreateDeleteLayersCmd(bool16 checkIsUsed, IPMUnknown* targetWidget);
	ICommand* CreateMergeLayersCmd(IPMUnknown* targetWidget);

	void DoSelectLayer(const IPMUnknown* targetWidget, bool16 extendSelection, bool16 selectAllSelectedLayersIfThisLayerSelected);
	void DoSetActiveLayer(const UIDRef& newActiveLayer, ILayoutControlData* forThisLayout);
	enum LayerDialogType { kNewLayerDialog = 0, kLayerOptionsDialog };

	void InvokeLayerDialog(LayerDialogType dialogType, LayerLocation position, IPMUnknown* targetWidget, IDocumentLayer* targetNewLayer);

	IDocumentLayer* QueryLayerFromPanelWidget(const IPMUnknown* widget);
	void InvalidateNodeForPageItem(ITreeViewMgr* treeViewMgr,IDataBase* db, UID piUID, bool rebuildChildrenToo);
	bool16 SelectAssociatedItemsInLayout(IPMUnknown* widget, bool extendSelection, bool selectChildrenInstead, bool selectAllPanelSelectedItemsIfThisWidgetRowSelected);
	bool16 AreAllOtherPageItemsHidden(IPMUnknown* anyPanelWidget, UID pageItemUID);
	bool16 AreAllOtherPageItemsLocked(IPMUnknown* anyPanelWidget, UID pageItemUID);
	void ShowHideOtherPageItems(IPMUnknown* anyPanelWidget, UID pageItemUID);
	void LockUnlockOtherPageItems(IPMUnknown* anyPanelWidget, UID pageItemUID);
	bool16 CanLockOtherPageItems(IPMUnknown* anyPanelWidget, UID pageItemUID);
	bool16 CanUnlockOtherPageItems(IPMUnknown* anyPanelWidget, UID pageItemUID);

	NodeID_rv GetLayerTreeNodeFromSubwidget(const IPMUnknown* widget);
	ColorArray GetLayerColorForWidget(IPMUnknown* widget);
	bool16 ValidateNewLayerName(IDataBase* docDB, const IDocumentLayer* optionalLayerBeingRenamed, const PMString &newName, PMString& errorString);
	
	IDataBase* GetCurrentLayerPanelDB(const IPMUnknown* anyPanelWidget);
	bool IsItemOrAncestorLockedOrHidden(const UIDRef & someItem);

	bool16 AreThereAnyOthers(IPMUnknown* anyPanelWidget, UID pageItemUID);
	bool IsRowSelectedInTree(IPMUnknown* anyRowWidget);

	PMString GetDefaultPageItemElementName(const IHierarchy* piHier);

}

#endif // __LayerPanelUtils__