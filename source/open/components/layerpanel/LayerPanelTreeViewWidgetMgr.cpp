//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelTreeViewWidgetMgr.cpp $
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

#include "IControlView.h"
#include "IDocument.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IUIDData.h"
#include "IDocumentLayer.h"
#include "IBoolData.h"
#include "ITextControlData.h"
#include "IHierarchy.h"
#include "IInLineEditEditingAttributes.h"
#include "ILayerSuite.h"
#include "ISelectionUtils.h"
#include "IPageItemLockFacade.h"
#include "ILayoutSelectionSuite.h"
#include "ISelectionProxyDrawData.h"
#include "IPNGIconAttributes.h"
#include "IPageItemVisibilityFacade.h"
#include "IPageItemNameFacade.h"
#include "IPageItemTypeUtils.h"
#include "IUIFontSpec.h"
#include "ISpreadLayer.h"
#include "ILayoutUIUtils.h"
#include "IMenuUtils.h"

#include "LayerPanelUtils.h"
#include "LocaleSetting.h"
#include "CTreeViewWidgetMgr.h"
#include "LayerPanelID.h"
#include "CoreResTypes.h"
#include "LayerTreeUIDNodeID.h"
#include "LayerPanelDefs.h"
#include "IconStyleDefs.h"

#include "DVPublicUtilities.h"

#define INHERITED	CTreeViewWidgetMgr

//----------------------------------------------------------------------------------------
// LayerPanelTreeViewWidgetMgr constructor
//----------------------------------------------------------------------------------------
class LayerPanelTreeViewWidgetMgr : public INHERITED
{
public:
	LayerPanelTreeViewWidgetMgr(IPMUnknown *boss);
	~LayerPanelTreeViewWidgetMgr();
	
	virtual	IControlView*		CreateWidgetForNode(const NodeID& node) const;
	virtual	WidgetID			GetWidgetTypeForNode(const NodeID& node) const;
	virtual	bool16			ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 message ) const;
	virtual PMReal				GetNodeWidgetWidth(const NodeID& node) const
	{ 
	#pragma unused(node)
		return 200;
	}
	virtual PMReal				GetNodeWidgetHeight(const NodeID& node) const 
	{ 
	#pragma unused(node)
		InterfacePtr<const IBoolData> rowSizeBool(this, IID_ISMALLPALETTEROWSBOOLDATA);
		return rowSizeBool->GetBool() ? kCC2016PanelTreeNodeSmallRowHeight : kCC2016PanelTreeNodeHeight;
	}

};

CREATE_PMINTERFACE(LayerPanelTreeViewWidgetMgr, kLayerPanelTreeViewWidgetMgrImpl)

//----------------------------------------------------------------------------------------
// LayerPanelTreeViewWidgetMgr constructor
//----------------------------------------------------------------------------------------
LayerPanelTreeViewWidgetMgr::LayerPanelTreeViewWidgetMgr(IPMUnknown *boss) :
	INHERITED(boss)
{
}


//----------------------------------------------------------------------------------------
// LayerPanelTreeViewWidgetMgr::~LayerPanelTreeViewWidgetMgr 
//----------------------------------------------------------------------------------------
LayerPanelTreeViewWidgetMgr::~LayerPanelTreeViewWidgetMgr()
{
}


void SetupLayerWidget(const IDocumentLayer* docLayer,IControlView* widget,bool bSmallRows)
{	
	// set the proper states for layer visibility, lockedness, and proxy
	InterfacePtr<const IPanelControlData> panelData(widget, UseDefaultIID());

	// set up the name widget.
	IControlView* nameWidget = panelData->FindWidget(kLayerListElementNameWidgetID);	
	InterfacePtr<ITextControlData> textData(nameWidget,UseDefaultIID());
	PMString layerName = docLayer->GetName();

	// The string we've gotten from the layer may have an ampersand
	// in it. When this string gets put in a StaticTextControl, this
	// ampersand will be stripped an replaced with an accelerator on
	// Windows. So, we need to turn single ampersands into double-ampersands.
	// Ex: "Units & Increments" in Prefs dialog.
	//
	Utils<IMenuUtils>()->InsertAmpersandForDisplay(&layerName);

	textData->SetString(layerName,kTrue,kFalse); // don't notify
	InterfacePtr<IUIFontSpec> nameFontSpec(nameWidget,UseDefaultIID());
	bool useItalics = (docLayer->IsVisible() && !docLayer->IsPrintable());
	nameFontSpec->SetFontID(useItalics ? kPaletteWindowItalicsFontId : kPaletteWindowSystemScriptFontId);
	nameFontSpec->SetHiliteFontID(useItalics ? kPaletteWindowBoldItalicsFontId : kPaletteWindowSystemScriptHiliteFontId);
	

	IControlView* eyeball = panelData->FindWidget(kLayerListElementEyeballWidgetID);	
	//TRACEFLOW("LayerPanel","SetupLayerWidget for layer %s. Layer visibility is %d\n",docLayer->GetName().GrabCString(),docLayer->IsVisible());
	eyeball->SetRsrcID(docLayer->IsVisible() ? kEyeballIcon : kNoIcon);
	InterfacePtr<IPNGIconAttributes> eyeIconAttrs(eyeball,UseDefaultIID());
	eyeIconAttrs->SetAttributes(kIconCentering, kIconFlushLook,  0);
	
	InterfacePtr<const ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
	bool16 showExpander = layoutData != nil;
	IControlView* expanderView = panelData->FindWidget(kTreeNodeExpanderWidgetID);
	expanderView->ShowView(showExpander);

	IControlView* pencil = panelData->FindWidget(kLayerListElementPencilWidgetID);	
	IControlView* swatchView = panelData->FindWidget(kLayerListElementSwatchWidgetID);

	IControlView* selProxy = panelData->FindWidget(kLayerListElementProxyWidgetID);
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
	{
		pencil->HideView();
		selProxy->HideView();
		IControlView* layerListElementNamePanel = panelData->FindWidget(kLayerListElementNamePanelWidgetID);

		if (LocaleSetting::GetLocale().IsRightToLeftUI())
		{
			swatchView->MoveTo(PMPoint(pencil->GetFrame().Right() - swatchView->GetFrame().Width(),swatchView->GetFrame().Top()));
			layerListElementNamePanel->MoveTo(PMPoint(swatchView->GetFrame().Left() - 1 - layerListElementNamePanel->GetFrame().Width(), layerListElementNamePanel->GetFrame().Top()));
		}
		else
		{
			swatchView->MoveTo(PMPoint(pencil->GetFrame().Left(),swatchView->GetFrame().Top()));
			layerListElementNamePanel->MoveTo(PMPoint(swatchView->GetFrame().Right() + 1, layerListElementNamePanel->GetFrame().Top()));
		}
	}
	else
	{
		pencil->SetRsrcID(docLayer->IsLocked() ? kLayerLockedIcon : kLayerNotLockedIcon);
		InterfacePtr<IPNGIconAttributes> pencilIconAttrs(pencil,UseDefaultIID());
		pencilIconAttrs->SetAttributes(kIconCentering, kIconFlushLook,  0);		
		bool16 found = kFalse;
		InterfacePtr<ILayerSuite>    iLayerSuite(static_cast<ILayerSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ILAYERSUITE)));
		if (iLayerSuite)
		{
			UIDList docLayerList(::GetDataBase(docLayer));
			iLayerSuite->GetSelectedLayers(docLayerList);
			found = (docLayerList.Location(::GetUID(docLayer)) >= 0);
		}

		InterfacePtr<ISelectionProxyDrawData> drawData(selProxy, UseDefaultIID());
		drawData->SetDrawingMode(found ? ISelectionProxyDrawData::kSelected : ISelectionProxyDrawData::kUnselected);
	}
}

bool16 IsOnVisibleLayer(const IHierarchy* itemHier)
{
	InterfacePtr<const ISpreadLayer> spreadLayer(::GetDataBase(itemHier), itemHier->GetLayerUID(), UseDefaultIID());
	return spreadLayer->IsVisible();
}

bool IsAnyChildSelected(UIDRef whichObjRef, const ILayoutSelectionSuite* selSuite)
{
	InterfacePtr<const ILayerSuite>    iLayerSuite (selSuite,UseDefaultIID());
	if (iLayerSuite)
	{
		UIDList selectedItems = iLayerSuite->GetSelectedItemsForLayersPanel();
		for(uint32 i = 0; i < selectedItems.size(); ++i)
		{
			InterfacePtr<const IHierarchy> piHier(selectedItems.GetRef(i),UseDefaultIID());
			UIDList ancestorsOfSelectedItem(whichObjRef.GetDataBase());
			piHier->GetAncestors(&ancestorsOfSelectedItem,IID_IHIERARCHY);
			if(ancestorsOfSelectedItem.Contains(whichObjRef.GetUID()))
				return true;
		}
	}
	return false;
}

void SetupPageItemWidget(const IHierarchy* piHier,IControlView* widget,bool showExpander, int indentLevel, bool bSmallRows)
{	
	InterfacePtr<const IPanelControlData> panelData(widget, UseDefaultIID());
	IControlView* nameWidget = panelData->FindWidget(kLayerPageItemElementTextWidgetID);	
	InterfacePtr<ITextControlData> textData(nameWidget,UseDefaultIID());
	textData->SetString(LayerPanelUtils::GetDefaultPageItemElementName(piHier),kTrue,kFalse); // don't notify

	bool isEditable = Utils<Facade::IPageItemNameFacade>()->IsPageItemNameUserAssignable(::GetUIDRef(piHier));
	InterfacePtr<IInLineEditEditingAttributes> ileEditingAttributes(nameWidget,UseDefaultIID());
	ileEditingAttributes->SetIsEditable(isEditable);
	
	// indent the name, expander, etc.
	IControlView* namePanelWidget = panelData->FindWidget(kLayerPageItemNamePanelWidgetID);	
	PMRect widgetFrame = namePanelWidget->GetFrame();
	const PMReal pageItemXloc = bSmallRows ? PAGEITEM_NAME_PANEL_XLOC(kCC2016PanelTreeNodeContentSmallRowHeight) : PAGEITEM_NAME_PANEL_XLOC(kCC2016PanelTreeNodeContentHeight);
	PMReal adjustment = pageItemXloc + (10 * (indentLevel - 1));
	if (LocaleSetting::GetLocale().IsRightToLeftUI())
		widgetFrame.Right() = widget->GetFrame().Width() - adjustment;
	else
		widgetFrame.Left() = adjustment;
	IControlView* pencil = panelData->FindWidget(kLayerPageItemElementPencilWidgetID);
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
	{
		if (LocaleSetting::GetLocale().IsRightToLeftUI())
			widgetFrame.Right() += pencil->GetFrame().Width();
		else
			widgetFrame.Left() -= pencil->GetFrame().Width();
	}
	namePanelWidget->SetFrame(widgetFrame);


	IControlView* expander = panelData->FindWidget(kTreeNodeExpanderWidgetID);
	expander->ShowView(showExpander);
	
	UIDList itemUIDs(::GetUIDRef(piHier));
	IControlView* eyeball = panelData->FindWidget(kLayerListElementEyeballWidgetID);
	bool visState = Utils<Facade::IPageItemVisibilityFacade>()->GetVisibleState(::GetUIDRef(piHier));
	bool actuallyVisible = !Utils<Facade::IPageItemVisibilityFacade>()->IsHidden(::GetUIDRef(piHier)) && IsOnVisibleLayer(piHier);
	
	if(!visState)
	{
		eyeball->SetRsrcID(kNoIcon);
		eyeball->Enable();
	}
	else if(actuallyVisible)
	{
		eyeball->SetRsrcID(kEyeballIcon);
		eyeball->Enable();
	}
	else
	{
		eyeball->SetRsrcID(kEyeballIcon);
		eyeball->Disable();
	}
	InterfacePtr<IPNGIconAttributes> eyeIconAttrs(eyeball,UseDefaultIID());
	eyeIconAttrs->SetAttributes(kIconCentering, kIconFlushLook,  0);

	// set up the pencil/lock icon
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
	{
		IControlView* swatchView = panelData->FindWidget(kLayerListElementSwatchWidgetID);
		pencil->HideView();	
		if (LocaleSetting::GetLocale().IsRightToLeftUI())
			swatchView->MoveTo(PMPoint(pencil->GetFrame().Right() - swatchView->GetFrame().Width(),swatchView->GetFrame().Top()));
		else
			swatchView->MoveTo(PMPoint(pencil->GetFrame().Left(),swatchView->GetFrame().Top()));
	}
	else
	{
		InterfacePtr<IPNGIconAttributes> pencilIconAttrs(pencil,UseDefaultIID());
		pencilIconAttrs->SetAttributes(kIconCentering, kIconFlushLook,  0);

	//	TRACEFLOW("LayerPanel","SetupPageItemWidget for UID %d. ",::GetUID(piHier).Get());

		if(Utils<Facade::IPageItemLockFacade>()->CanLock(itemUIDs))
		{
			pencil->SetRsrcID(kLayerNotLockedIcon);
			pencil->ShowView();
			pencil->Enable();
		}
		else	if(Utils<Facade::IPageItemLockFacade>()->CanUnlock(itemUIDs))
		{
			pencil->SetRsrcID(kLayerLockedIcon);
			pencil->ShowView();
			pencil->Enable();
		}
		else	if(Utils<Facade::IPageItemLockFacade>()->IsAnyAncestorLocked(itemUIDs.GetRef(0)))
		{
			pencil->SetRsrcID(kLayerLockedIcon);
			pencil->ShowView();
			pencil->Disable();
		}
		else
		{
			//pencil->SetRsrcID(kLayerLockedIcon);
			pencil->HideView();
		}
	}

	//TRACEFLOW("LayerPanel","CanLock %d, CanUnlock %d",Utils<Facade::IPageItemLockFacade>()->CanLock(itemUIDs),Utils<Facade::IPageItemLockFacade>()->CanUnlock(itemUIDs));
	
	IControlView* selProxy = panelData->FindWidget(kPageItemSelectionProxyWidgetID);
	
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
	{
		selProxy->HideView();	
	}
	else
	{
		InterfacePtr<ILayoutSelectionSuite>    layoutSuite ( static_cast<ILayoutSelectionSuite*>(Utils<ISelectionUtils>()->QueryActiveLayoutSelectionSuite()));
		ISelectionProxyDrawData::ProxyDrawType drawType = ISelectionProxyDrawData::kUnselected;
		if (layoutSuite)
		{		
			if(layoutSuite->IsPageItemSelected(::GetUID(piHier)))
				drawType = ISelectionProxyDrawData::kSelected;
			else if(IsAnyChildSelected(::GetUIDRef(piHier),layoutSuite))
				drawType = ISelectionProxyDrawData::kChildSelected;
		}
		InterfacePtr<ISelectionProxyDrawData> drawData(selProxy, UseDefaultIID());
		drawData->SetDrawingMode(drawType);
		
	}
	
}


bool16 LayerPanelTreeViewWidgetMgr::ApplyNodeIDToWidget( const NodeID& node, IControlView* widget, int32 ) const
{	
	TreeNodePtr<const LayerTreeUIDNodeID>	layerNode(node);
	UIDRef itemRef(LayerPanelUtils::GetCurrentLayerPanelDB(this),layerNode->GetUID());
	//TRACEFLOW("LayerPanel","ApplyNodeIDToWidget for node with UID %d\n",layerNode->GetUID().Get());
	
	if (!itemRef.ExistsInDB())
		return kTrue;

	InterfacePtr<const IBoolData> rowSizeBool(this, IID_ISMALLPALETTEROWSBOOLDATA);
	bool bSmallRows = rowSizeBool->GetBool();
	PMReal h = bSmallRows ? kCC2016PanelTreeNodeSmallRowHeight : kCC2016PanelTreeNodeHeight;
	PMRect widgetFrame = widget->GetFrame();
	widgetFrame.Bottom() = widgetFrame.Top() + h;
	widget->SetFrame(widgetFrame);
	
	if(layerNode->IsLayerEntry())
	{
		InterfacePtr<const IDocumentLayer> docLayer(itemRef,UseDefaultIID());
		SetupLayerWidget(docLayer,widget,bSmallRows);
	}
	else
	{
		InterfacePtr<const ITreeViewHierarchyAdapter> treeHier(this,UseDefaultIID());
		
		InterfacePtr<const IHierarchy> piHier(itemRef,UseDefaultIID());
		int indentLevel = 0;
		NodeID tempNode = node;
		while(tempNode !=  treeHier->GetRootNode())
		{
			tempNode = treeHier->GetParentNode(tempNode);
            if(!tempNode.IsValid())
                break;
			++indentLevel;
		}
		
        // Before re-composition of text, inlines are unregistered from the text frame
        // and are added back after composition is complete.
        // Hence, We might not be able to get its parent node, and can not be placed into layers tree.
        // The layer's tree will be again invalidated after re-composition, where it will be again added.
        if(!tempNode.IsValid())
            return kFalse;
		SetupPageItemWidget(piHier,widget,treeHier->GetNumChildren(node)!=0,indentLevel,bSmallRows);
	}

	//Call base class for hilite selection
	INHERITED::ApplyNodeIDToWidget( node, widget );
		
	return kTrue;
}


//----------------------------------------------------------------------------------------
// LayerPanelTreeViewWidgetMgr::CreateWidgetForNode
//----------------------------------------------------------------------------------------
IControlView* LayerPanelTreeViewWidgetMgr::CreateWidgetForNode(const NodeID& node) const
{
//	TRACEFLOW("Layer","LayerPanelTreeViewWidgetMgr::CreateWidgetForNode\n");

	TreeNodePtr<const LayerTreeUIDNodeID>	layerNode(node);

	InterfacePtr<const IBoolData> rowSizeBool(this, IID_ISMALLPALETTEROWSBOOLDATA);
	bool16 bSmallRows = rowSizeBool->GetBool();

	RsrcID treeNodeRsrcID;
	if (layerNode->IsLayerEntry())
		treeNodeRsrcID = bSmallRows ? kLayerElementSmallRowsPanelRsrcID : kLayerElementPanelRsrcID;
	else
		treeNodeRsrcID = bSmallRows ? kLayerPageItemElementSmallRowsPanelRsrcID : kLayerPageItemElementPanelRsrcID;

	IPMUnknown *returnVal = ::CreateObjectNoInit(::GetDataBase(this), RsrcSpec(LocaleSetting::GetLocale(), kLayerPanelPluginID, kViewRsrcType, treeNodeRsrcID), IID_ICONTROLVIEW);
	ASSERT_MSG(returnVal, "Cannot create the appropriate control view.");
	InterfacePtr<IControlView> view(returnVal, UseDefaultIID());
	ASSERT_MSG(view, "Cannot create the appropriate control view.");
	
	// Set the drover theme on the Panel View, since the panel will be added to PanelWrapperWindow at a later stage so add it the panel theme on Panle view
	if(view)
		dv_utils::SetThemeForView(view, dv_utils::kIDPanelTheme);
	
	// Now create the panel hierarchy after the IWindow has been setup at the Panel.
	if (view)
		view->DoPostCreate();
	
	return view;
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeViewWidgetMgr::GetWidgetTypeForNode
//----------------------------------------------------------------------------------------
WidgetID LayerPanelTreeViewWidgetMgr::GetWidgetTypeForNode(const NodeID& node) const
{	
	TreeNodePtr<const LayerTreeUIDNodeID>	layerNode(node);
	
	return layerNode->IsLayerEntry() ? kLayerListParentWidgetId : kLayerPageItemElementWidgetID;
}

