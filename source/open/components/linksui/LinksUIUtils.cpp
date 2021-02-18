//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIUtils.cpp $
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

#include "ILinksUIUtils.h"
#include "IDocument.h"
#include "ILinkFacade.h"
#include "ILinkInfoProvider.h"
#include "ILinksUIPanelPrefs.h"
#include "ILinkManager.h"
#include "IPanelControlData.h"
#include "IWidgetParent.h"
#include "ITreeNodeIDData.h"
#include "IOpenFileDialog.h"
#include "IObserver.h"
#include "IApplication.h"
#include "IPanelMgr.h"
#include "ITreeViewController.h"
#include "ISplitterPanelControlData.h"
#include "ISplitterPanelController.h"
#include "IWidgetUtils.h"
#include "ITextControlData.h"
#include "IBoolData.h"
#include "ITriStateData.h"
#include "ILayoutUIUtils.h"
#include "ILinkObject.h"
#include "ILinkUtils.h"
#include "IOpenFileDialog.h"
#include "IColumnHeaderPanelData.h"
#include "ITreeViewMgr.h"
#include "IIntData.h"
#include "IPanorama.h"
#include "IPersistUIDData.h"
#include "ILinkItemSuite.h"
#include "ISelectionManager.h"
#include "ISelectionUtils.h"
#include "IThumbnailUtils.h"
#include "IImageCache.h"
#include "ILinksTreeNodeList.h"
#include "LinkResourceQuery.h"
#include "IOWLPaletteSizer.h"
#include "IMonitorInfo.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IStringListControlData.h"
#include "IDropDownListController.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"

#include "SysFileList.h"
#include "UIDList.h"
#include "LinksTreeUIDNodeID.h"
#include "Utils.h"
#include "CAlert.h"
#include "LinksUIResDefs.h"
#include "PreferenceUtils.h"
#include "IURIUtils.h"
#include "MetaDataID.h"
#include "PaletteRefUtils.h"
#include "K2Vector.h"
#include "ErrorUtils.h"
#include "LocaleSetting.h"


class LinksUIUtilsImpl : public CPMUnknown<ILinksUIUtils>
{
public:
	LinksUIUtilsImpl(IPMUnknown* boss):CPMUnknown<ILinksUIUtils>(boss){}
	virtual ~LinksUIUtilsImpl() {}
		
	void GetEditOriginalEditorList(AppInfoList& appList, UIDList &resources);
	void EditOriginal(ILink *link, const AppInfo& appInfo = kNullAppInfo);
	UIDRef GetSingleLinkUIDRefSelectedInLayout() const;
	UIDList GetLinkUIDsOfSelectedItems() const;
	UIDList GetResourcesOfLinks(UIDList &links) const;
	void EditAllOriginals(UIDList &links, UIDList &resources, const AppInfo& appInfo = kNullAppInfo) const;
	void GoToSource(ILink *link) const;
	void GoToAllSources(UIDList &links, UIDList &resources) const;

	void SelectLinksInPanel(const UIDList& inLinkUIDsToSelect);
	UIDList GetLinksSelectedInPanel(bool16 inDisplayOrder);
	UIDList GetLinkResourcesSelectedInPanel(bool16 inDisplayOrder);
	UIDList GetLinksForMenuAction(IPMUnknown* widget, bool16 inDisplayOrder) const;
	bool16 SomeCanEdit(UIDList &linkList);
	bool16 SomeCanGoToSource(UIDList &linkList);
	bool IsMenuActionEntirelyOnLinkResourceRows(IPMUnknown* widget);
	
	/* show/hide link info section. If onlyShow bool is true, it will not toggle visible to hidden */
	void ToggleLinkInfoSectionVisibility(bool onlyShow, bool fitSizeToAvailableInfo);
	void	UpdateLinkInfoSectionButtonState();
	const ILinkInfoProvider* QueryLinkInfoProviderFromHeaderWidget(const IPMUnknown* widget);
	void SetPanelSortProvider(const ILinkInfoProvider* newSortProvider);

	virtual bool16 DoUnembedSelectedLinks(const UIDList& targetLinks, bool16 updateLink) const;
	virtual ILinkInfoProvider* QueryInfoProviderFromLinksUIWidget(const IPMUnknown* widget) const;
	virtual ILink* QueryLinkFromLinksUIWidget(const IPMUnknown* widget) const ;
	virtual ILinkResource* QueryLinkResourceFromLinksUIWidget(const IPMUnknown* widget) const ;
	NodeID_rv CreateNodeFromLinkUIDRef(UIDRef linkUIDRef);
	IMetaDataAccess* QueryMetaDataAccessFromLink(const ILink* link) const;
	virtual IImageCache* QueryThumbnailForLink(const ILink * theLink, const ILinkResource * linkResource) const;
	
	virtual void SetupCaptionRowWidget(const IPMUnknown* rowView,const PMString& beforeString, const PMString& providerName,const PMString& afterString) const;
	
};

CREATE_PMINTERFACE(LinksUIUtilsImpl, kLinksUIUtilsImpl)

UIDRef LinksUIUtilsImpl::GetSingleLinkUIDRefSelectedInLayout() const
{
	InterfacePtr<ILinkItemSuite>	iLinkItemSuite (static_cast<ILinkItemSuite*> (Utils<ISelectionUtils> ()->QuerySuite (IID_ILINKITEMSUITE)));
	if (iLinkItemSuite != nil)
	{
		K2::scoped_ptr<UIDList>		dataLinkUIDList (iLinkItemSuite->CreateItemsDataLinkUIDList ());
		if(dataLinkUIDList)
		{			
			if (dataLinkUIDList->Length () == 1)
			{
				return dataLinkUIDList->GetRef(0);
			}
		}
	}
			
	return UIDRef();
}

UIDList LinksUIUtilsImpl::GetLinkUIDsOfSelectedItems() const
{
	InterfacePtr<ILinkItemSuite>	iLinkItemSuite (static_cast<ILinkItemSuite*> (Utils<ISelectionUtils> ()->QuerySuite (IID_ILINKITEMSUITE)));
	if (iLinkItemSuite != nil)
	{
		K2::scoped_ptr<UIDList> dataLinkUIDList(iLinkItemSuite->CreateItemsDataLinkUIDList());
		if(dataLinkUIDList)
		{			
			if (dataLinkUIDList->Length () >= 1)
			{
				return UIDList(*dataLinkUIDList);
			}
		}
	}
			
	return UIDList();
}

UIDList LinksUIUtilsImpl::GetResourcesOfLinks(UIDList &links) const
{
	K2::scoped_ptr<UIDList> resources(new UIDList(links.GetDataBase()));
	for (int32 linkIndex = 0; linkIndex < links.Length(); linkIndex++)
	{
		InterfacePtr<ILink> link(links.GetRef(linkIndex), UseDefaultIID());
		ASSERT(link);
		UID resource = link->GetResource();
		if (resources->Location(resource) == -1)
		{
			resources->Append(resource);
		}
	}
	return UIDList(*resources);
}
	
void LinksUIUtilsImpl::EditAllOriginals(UIDList &links, UIDList &resources, const AppInfo& appInfo) const
{
	// For each resource, edit the first link that refers to it
	for (int32 resourceIndex = 0; resourceIndex < resources.Length(); resourceIndex++)
	{
		InterfacePtr<ILinkResource> resource(resources.GetRef(resourceIndex), UseDefaultIID());
		for (int32 linkIndex = 0; linkIndex < links.Length(); linkIndex++)
		{
			InterfacePtr<ILink> link(links.GetRef(linkIndex), UseDefaultIID());
			ASSERT(link);
			if (link->GetResource() == ::GetUID(resource))
			{
				Utils<ILinksUIUtils>()->EditOriginal(link, appInfo);
				break; // next resource
			}
		}
	}
}

void LinksUIUtilsImpl::GoToAllSources(UIDList &links, UIDList &resources) const
{
	// For each resource, open the first link that refers to it
	for (int32 resourceIndex = 0; resourceIndex < resources.Length(); resourceIndex++)
	{
		InterfacePtr<ILinkResource> resource(resources.GetRef(resourceIndex), UseDefaultIID());
		for (int32 linkIndex = 0; linkIndex < links.Length(); linkIndex++)
		{
			InterfacePtr<ILink> link(links.GetRef(linkIndex), UseDefaultIID());
			ASSERT(link);
			if (link->GetResource() == ::GetUID(resource))
			{
				Utils<ILinksUIUtils>()->GoToSource(link);
				break; // next resource
			}
		}
	}
}

void LinksUIUtilsImpl::GetEditOriginalEditorList(AppInfoList& appList, UIDList &resources)
{
	// the algorithm here is to get the first set of apps to use as a baseline.
	// then this set is compared to all the rest eliminating any that don't appear in the other lists.
	// We do this until we empty the list or run out of others to compare against

	appList.clear();
	
	if (resources.Length() == 0) return;

	Utils<ILinkUtils>()->GetEditorList(resources.GetRef(0),appList,kFalse);

	// look at all the other resources' editor list
	for (int32 resourceIndex = 1; appList.size() > 0 && resourceIndex < resources.Length(); resourceIndex++)
	{
		AppInfoList compareAppList;
		Utils<ILinkUtils>()->GetEditorList(resources.GetRef(resourceIndex),compareAppList,kFalse);
		//See if the items in appList are in the other list, remove them if they aren't
		for (int32 editorIndex = appList.size() - 1; editorIndex >= 0; editorIndex--)
		{
			bool16 bFound = kFalse;
			for (auto compareIter = compareAppList.begin(); !bFound && compareIter != compareAppList.end(); ++compareIter)
			{
				if (appList[editorIndex] == *compareIter)
				{
					bFound = kTrue;
				}
			}
			if (!bFound)
			{
				appList.erase(&appList[editorIndex]);
			}
		}
	}
}



static void _EditOriginalKnownDataLink(ILink *link, const AppInfo& appInfo)
{
	PMString errString;
	if (Utils<Facade::ILinkFacade>()->EditLink(::GetUIDRef(link), appInfo, &errString) != kSuccess)
	{
		if (!errString.IsEmpty())
		{
			ErrorUtils::PMSetGlobalErrorCode(kSuccess);
			CAlert::ErrorAlert(errString);
		}
	}
}

static void EditOriginalKnownDataLink(ILink *link, const AppInfo& appInfo)
{
	_EditOriginalKnownDataLink(link, appInfo);
}

void LinksUIUtilsImpl::EditOriginal(ILink *link, const AppInfo& appInfo)
{
	if (link)
		EditOriginalKnownDataLink(link, appInfo);
//	else
//		EditOriginalCommon(kTrue, appInfo);
}

static void _GoToSourceKnownDataLink(ILink *link)
{
	PMString errString;
	if (Utils<Facade::ILinkFacade>()->GoToSource(::GetUIDRef(link), &errString) != kSuccess)
	{
		if (!errString.IsEmpty())
		{
			ErrorUtils::PMSetGlobalErrorCode(kSuccess);
			CAlert::ErrorAlert(errString);
		}
	}
}

static void GoToSourceKnownDataLink(ILink *link)
{
	_GoToSourceKnownDataLink(link);
}

void LinksUIUtilsImpl::GoToSource(ILink *link) const
{
	if (link)
		GoToSourceKnownDataLink(link);
}

static IControlView* GetLinksUIPanell()
{
	InterfacePtr<const IApplication> theApp (GetExecutionContextSession()->QueryApplication ());
	InterfacePtr<const IPanelMgr> panelMgr( theApp->QueryPanelManager() );
      
	if (panelMgr)
		return panelMgr->GetPanelFromWidgetID(kLinksUIPanelWidgetID);

	return nil;
}

static IControlView* GetLinksUITreeControl()
{
	IControlView* linksPanel = GetLinksUIPanell();
	if(linksPanel)
	{
		InterfacePtr<const IPanelControlData> panelData(linksPanel,UseDefaultIID());
		return panelData->FindWidget(kLinksUIPanelTreeWidgetID);
	}
	return nil;
}

static NodeID_rv GetTreeRowNodeFromChildWidget(const IPMUnknown* widget)
{
	InterfacePtr<const ITreeNodeIDData> nodeData(widget,UseDefaultIID());
	if(nodeData)
		return nodeData->Get();
	else
	{
		InterfacePtr<const IWidgetParent> wp(widget,UseDefaultIID());
		if(wp)
		{
			InterfacePtr<const ITreeNodeIDData> parentNodeData((ITreeNodeIDData*)wp->QueryParentFor(IID_ITREENODEIDDATA));
			if(parentNodeData)
			{
				return parentNodeData->Get();
			}
		}
	}
	NodeID invalidNode;
	return invalidNode;

}

bool LinksUIUtilsImpl::IsMenuActionEntirelyOnLinkResourceRows(IPMUnknown* widget)
{
	InterfacePtr<const ITreeViewController> treeController(GetLinksUITreeControl(),UseDefaultIID());
	if(treeController)
	{
		UID clickedOnResourceRowUID = kInvalidUID;
		NodeID nodeFromWidget = GetTreeRowNodeFromChildWidget(widget);
		if(nodeFromWidget.IsValid())
		{
			TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNodeFromWidget(nodeFromWidget);
			if(linksUIDNodeFromWidget->GetLinkResourceUID() != kInvalidUID && linksUIDNodeFromWidget->GetLinkUIDRef().GetUID() == kInvalidUID)
				clickedOnResourceRowUID = linksUIDNodeFromWidget->GetLinkResourceUID(); // this is a link resource row
		}
		bool foundClickedRowInSelection = false;
		
		NodeIDList selectedItems;
		treeController->GetSelectedItems(selectedItems);
		for(auto iter = selectedItems.rbegin(); iter != selectedItems.rend(); ++iter)
		{
			TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(*iter);
			UID resourceUID = linksUIDNode->GetLinkResourceUID();
			if(linksUIDNode->GetLinkResourceUID() == kInvalidUID || linksUIDNode->GetLinkUIDRef().GetUID() != kInvalidUID)
				return false; // this is not a link resource row
			else if(clickedOnResourceRowUID == linksUIDNode->GetLinkResourceUID())
				foundClickedRowInSelection = true;
		}
		return (!selectedItems.empty()); // we have a selection, and all selected items are link resources.
	}
	return false;
}


NodeID_rv LinksUIUtilsImpl::CreateNodeFromLinkUIDRef(UIDRef linkUIDRef)
{
	InterfacePtr<const ILink> theLink(linkUIDRef,UseDefaultIID());
	if(theLink)
	{
		InterfacePtr<const ILinksTreeNodeList> prebuiltLinksTree(GetLinksUITreeControl(),UseDefaultIID());
		if(prebuiltLinksTree)
		{
			const LinkTreeEntry* linkEntry = prebuiltLinksTree->FindEntryForLink(linkUIDRef);
			if(linkEntry)
				return LinksTreeUIDNodeID::Create(linkEntry); 
			TRACEFLOW("Links:LinksUI","CreateNodeFromLinkUIDRef couldn't find entry for link UID %d (corrupt document? or maybe a DM link in InCopy?)\n",linkUIDRef.GetUID().Get());
		}
	}
	
	NodeID badNode;
	return badNode;
	
}

void LinksUIUtilsImpl::SelectLinksInPanel(const UIDList& inLinkUIDsToSelect)
{	
	TRACEFLOW("Links:LinksUI","SelectLinksInPanel  with %d items in list\n",inLinkUIDsToSelect.Length());
	IControlView *treeView = GetLinksUITreeControl();
	if(treeView && treeView->IsVisible())
	{
		InterfacePtr<ITreeViewController> treeController(treeView,UseDefaultIID());
		if(treeController)
		{
			InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
			if(inLinkUIDsToSelect.GetDataBase() != linksUIPrefs->GetCurrentDocDB())
			{
				// this is a fairly odd case, but can actually happen. See bug 2436976 for one case. If we're asked to select links in a non-front doc, don't bother.
				return;
			}

			InterfacePtr<ITreeViewMgr> treeMgr(treeController,UseDefaultIID());
			
			treeController->DeselectAll(); 		
			IDataBase* linksDB = inLinkUIDsToSelect.GetDataBase();
			if(linksDB)
			{
				InterfacePtr<const ILinkManager> linkMgr(linksDB,linksDB->GetRootUID(),UseDefaultIID());
				InterfacePtr<const IWidgetParent> wp(treeController,UseDefaultIID());
				InterfacePtr<IBoolData> disableDrawingData((IBoolData*)wp->QueryParentFor(IID_LINKSPANELDRAWINGDISABLED));
				if(linkMgr->IsModelChanging() || disableDrawingData->Get())
				{
					// can't scroll or select items in the tree until model is done changing.
					disableDrawingData->Set(kTrue);
					return;

				}
			}

			InterfacePtr<const ITreeViewHierarchyAdapter> treeHier(treeController,UseDefaultIID());
			int32 numLinksToSelect = inLinkUIDsToSelect.Length();
			for(int32 i =  0; i < numLinksToSelect; ++i)
			{				
				NodeID selectedNode = CreateNodeFromLinkUIDRef(inLinkUIDsToSelect.GetRef(i));
				if(selectedNode.IsValid())
				{			
					if(i == 0)
					{
						// want to make sure this node is in view, but only call ScrollToNode if it is not in view, because ScrollToNode also scrolls back to the left, which we don't want.
						bool scrollNode = true;
						InterfacePtr<const IControlView> nodeWidget(treeMgr->QueryWidgetFromNode(selectedNode));
						if(nodeWidget)
						{
							PMRect showingTreeArea = treeMgr->GetViewableArea();
							PMRect widgetFrame = nodeWidget->GetFrame();
							PMRect intersectRect = Intersection(showingTreeArea,widgetFrame);
							const int kMinWidthShowingToPreventScroll = 100;
							const int kMinHeightShowingToPreventScroll = 15;
							if(intersectRect.Width() > kMinWidthShowingToPreventScroll && intersectRect.Height() > kMinHeightShowingToPreventScroll)
								scrollNode = false;
							
						}
						
						if(scrollNode)
						{
							treeView->Invalidate();	// #1879118, tree control doesn't redraw old selection in some cases.
							treeMgr->ScrollToNode(selectedNode,ITreeViewMgr::eScrollIntoView);
						}

					}
					
					// expand parents if they're collapsed. Note we don't bother looking for grandparents because users can't select child links...
					NodeID parentNode = treeHier->GetParentNode(selectedNode);
					if(parentNode.IsValid() && parentNode != treeHier->GetRootNode())
						treeMgr->ExpandNode(parentNode);

					treeController->Select(selectedNode,kTrue);

				}
			}	
		}
	}
}

UIDList LinksUIUtilsImpl::GetLinkResourcesSelectedInPanel(bool16 inDisplayOrder)
{
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	UIDList selectedLinkResources(linksUIPrefs->GetCurrentDocDB());
	if(linksUIPrefs->GetCurrentDocDB())
	{
		InterfacePtr<const ITreeViewController> treeController(GetLinksUITreeControl(),UseDefaultIID());
		if(treeController)
		{
			NodeIDList selectedItems;

			if(inDisplayOrder)
			{
				treeController->GetSelectedItemsDisplayOrder(selectedItems);
			}
			else
			{
				treeController->GetSelectedItems(selectedItems);
			}

			for (auto iter = selectedItems.rbegin(); iter != selectedItems.rend(); ++iter)
			{
				TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(*iter);
				UID resourceUID = linksUIDNode->GetLinkResourceUID();
				if(resourceUID != kInvalidUID)
					selectedLinkResources.push_back(resourceUID);
			}
					
		}
	}
//	TRACEFLOW("Links:LinksUI","LinksUIUtilsImpl::GetLinkResourcesSelectedInPanel returning %d link resources selected in panel\n",selectedLinkResources.size());
	return selectedLinkResources;
}

UIDList LinksUIUtilsImpl::GetLinksSelectedInPanel(bool16 inDisplayOrder)
{
	InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	UIDList selectedLinks(linksUIPrefs->GetCurrentDocDB());
	if(linksUIPrefs->GetCurrentDocDB())
	{
		InterfacePtr<const ILinkManager> linkMgr(linksUIPrefs->GetCurrentDocDB(),linksUIPrefs->GetCurrentDocDB()->GetRootUID(),UseDefaultIID());
		InterfacePtr<const ITreeViewController> treeController(GetLinksUITreeControl(),UseDefaultIID());
		if(treeController)
		{
			NodeIDList selectedItems;

			if(inDisplayOrder)
			{
				treeController->GetSelectedItemsDisplayOrder(selectedItems);
			}
			else
			{
				treeController->GetSelectedItems(selectedItems);
			}
			
			for (auto iter = selectedItems.rbegin(); iter != selectedItems.rend(); ++iter)
			{
				TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(*iter);
				UID linkUID = linksUIDNode->GetLinkUIDRef().GetUID();
				if(linkUID != kInvalidUID && linkUID != kRootDocumentLinksNodeUID)
				{
		//			ASSERT_MSG(linksUIPrefs->GetCurrentDocDB()->IsValidUID(linkUID),"We have an invalid UID, and we think it's a selected link in the links panel.");
					if(selectedLinks.DoesNotContain(linkUID))
						selectedLinks.push_back(linkUID);
				}
				else if(linksUIDNode->GetLinkResourceUID() != kInvalidUID)
				{
					ASSERT_MSG(linksUIPrefs->GetCurrentDocDB()->IsValidUID(linksUIDNode->GetLinkResourceUID()),"We have an invalid UID, and we think it's a selected linkresource in the links panel.");
					K2Vector<LinkTreeEntry*> childElements = linksUIDNode->GetTreeEntry()->GetChildEntries();
					for(K2Vector<LinkTreeEntry*>::const_iterator linkIter = childElements.begin(); linkIter != childElements.end(); ++linkIter)
					{
						if(selectedLinks.DoesNotContain((*linkIter)->GetLinkUIDRef().GetUID()))
							selectedLinks.push_back((*linkIter)->GetLinkUIDRef().GetUID());
					}
				}
			}
					
		}
	}
//	TRACEFLOW("Links:LinksUI","LinksUIUtilsImpl::GetLinksSelectedInPanel returning %d links selected in panel\n",selectedLinks.size());
	return selectedLinks;
}

UIDList LinksUIUtilsImpl::GetLinksForMenuAction(IPMUnknown* widget, bool16 inDisplayOrder) const
{
	InterfacePtr<const ILink> linkFromWidget(Utils<ILinksUIUtils>()->QueryLinkFromLinksUIWidget(widget));
	UIDList selectedLinks = Utils<ILinksUIUtils>()->GetLinksSelectedInPanel(inDisplayOrder);
	if(!linkFromWidget || selectedLinks.Contains(::GetUID(linkFromWidget)))
		return selectedLinks;
	return UIDList(::GetUIDRef(linkFromWidget));
}

bool16 LinksUIUtilsImpl::SomeCanEdit(UIDList &linkList)
{
	Utils<Facade::ILinkFacade> linkFacade;
	ASSERT(linkFacade);
	for(int linkIndex = linkList.Length() - 1; linkIndex >= 0; --linkIndex)
	{
		if (linkFacade->CanEditLink(linkList.GetRef(linkIndex)))
		{
			return kTrue;
		}
	}
	return kFalse;
}

bool16 LinksUIUtilsImpl::SomeCanGoToSource(UIDList &linkList)
{
	Utils<Facade::ILinkFacade> linkFacade;
	ASSERT(linkFacade);
	for(int32 linkIndex = linkList.Length() - 1; linkIndex >= 0; --linkIndex)
	{
		InterfacePtr<ILink> iLink(linkList.GetRef(linkIndex), UseDefaultIID());

		if (linkFacade->CanGoToSource(linkList.GetRef(linkIndex)))
		{
			return kTrue;
		}
	}
	return kFalse;
}

const int kMinHeightForInfoSection = 50;
const int kMinHeightForLinksSection = 75;
const int32 kLinkInfoPaneIndexForSplitter = 1;

#if ID_COCOA_ENABLE
	//FIXME_OWL_COCOA -- see ForceBottomOfPanelOnMonitor
#else
static void ForceBottomOfPanelOnMonitor(IControlView* linksUIPanelView, const PMReal xDim)
{
	// normally we just grow the panel by the amount the link info section is growing, but we don't want to do that if it's going to go off the bottom of the monitor
	SysRect panelBBox = linksUIPanelView->GetBBox();
	SysRect globalPanelBBox = ::ToSys(linksUIPanelView->WindowToGlobal(panelBBox));
	InterfacePtr<const IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<const IMonitorInfo> monInfo(theApp,UseDefaultIID());
	GSysRect monRect = monInfo->GetBestScreenRect(globalPanelBBox);
	if(SysRectBottom(monRect) < SysRectBottom(globalPanelBBox))
	{
		TRACEFLOW("Links:LinksUI:Resize","Panel is off the bottom of the monitor - resizing it shorter\n");
		PMReal amtToShrink = SysRectBottom(globalPanelBBox) - SysRectBottom(monRect) + 2;
		PMPoint newSize(xDim,SysRectHeight(panelBBox) - amtToShrink);
		newSize = linksUIPanelView->ConstrainDimensions(newSize);
		linksUIPanelView->Resize(newSize);
	}			
}
#endif

static void HideInfoAndShrinkPanel(IControlView* linksUIPanelView,ISplitterPanelControlData* splitterControlData)
{
	// hide the info section and shrink the panel
	PMRect panelBounds = linksUIPanelView->GetFrame();
	PMPoint dimensions(panelBounds.Width(),panelBounds.Height());
	
	InterfacePtr<const IControlView> splitterView(splitterControlData,UseDefaultIID());
	int32 infoSectionSize = ::ToInt32(splitterView->GetFrame().Height() - splitterControlData->GetSplitterEdge());
	
	dimensions.Y() -= infoSectionSize;

	splitterControlData->SetPanelVisible(kLinkInfoPaneIndexForSplitter,false);
	
	// we want to try resizing the containing palette. Resizing the panel will work when the palette is floating, but if it's constrained in a dock it may fail.
	InterfacePtr<const IApplication> theApp (GetExecutionContextSession()->QueryApplication ());
	InterfacePtr<const IPanelMgr> panelMgr( theApp->QueryPanelManager() );
	PaletteRef palette = panelMgr->GetPaletteRefContainingPanel(linksUIPanelView);
	ASSERT_MSG(palette.IsValid(),"Got invalid palette - how can I resize?");
	if(PaletteRefUtils::IsPaletteFloating(palette))
	{
		linksUIPanelView->Resize(dimensions);
	}
	else
	{
		// this next bit is a little unusual. Toggling the bottom section changes our min max size, but we only recalculate that during panel resize usually...so we have to force a recalculation of our min/max size by calling UpdateOWLPaletteSizes()
		InterfacePtr<const IWidgetParent> wp(linksUIPanelView,UseDefaultIID());
		InterfacePtr<IOWLPaletteSizer> palSizer((IOWLPaletteSizer*)wp->QueryParentFor(IOWLPaletteSizer::kDefaultIID));
		palSizer->UpdateOWLPaletteSizes();

		SysRect parentBounds = PaletteRefUtils::GetPaletteBounds(palette);
		SysPoint newPalSize;
		SetSysPoint(newPalSize, SysRectWidth(parentBounds), ::ToInt32( SysRectHeight(parentBounds) - infoSectionSize) );
		PaletteRefUtils::SetPaletteSize(palette, newPalSize);
	}
	
	InterfacePtr<const IPanelControlData> linksPanelData(linksUIPanelView,UseDefaultIID());
	InterfacePtr<IIntData> savedInfoSizeData(linksPanelData->FindWidget(kLinkInfoPanelWidgetID),IID_ISAVEDINFOPANESIZE);
	TRACEFLOW("Links:LinksUI","saving infoSectionSize of %d.\n",infoSectionSize);
	savedInfoSizeData->Set(infoSectionSize);
}

static void ShowInfoAndGrowPanel(IControlView* linksUIPanelView, ISplitterPanelControlData* splitterControlData, bool fitSizeToAvailableInfo)
{
	bool wasInfoAlreadyVisible = !splitterControlData->IsSinglePanelVisible();
					
	InterfacePtr<const IPanelControlData> linksPanelData(linksUIPanelView,UseDefaultIID());
	InterfacePtr<const IIntData> savedInfoSizeData(linksPanelData->FindWidget(kLinkInfoPanelWidgetID),IID_ISAVEDINFOPANESIZE);
	int32 newInfoSectionSize = savedInfoSizeData->Get();
	TRACEFLOW("Links:LinksUI:Resize","wasInfoAlreadyVisible %d, retrieved last size @ close of %d.\n",wasInfoAlreadyVisible, newInfoSectionSize);
				
	if(fitSizeToAvailableInfo)
	{
		InterfacePtr<const IPanorama> infoPanelPanorama(savedInfoSizeData,UseDefaultIID());
		if(infoPanelPanorama->GetBounds().Height() != 0) // if height is 0, no link info is showing because there's not a single link selected in the panel.
			newInfoSectionSize = ::ToInt32(infoPanelPanorama->GetBounds().Height());

		TRACEFLOW("Links:LinksUI:Resize","FitLinkInfoSectionToInfo - desiredSize %d\n",newInfoSectionSize);
	}

	// enforce min size for link info section
	if(newInfoSectionSize < splitterControlData->GetSplitterSnapBottom())
		newInfoSectionSize = splitterControlData->GetSplitterSnapBottom();

	// now resize the panel
	PMRect panelBounds = linksUIPanelView->GetFrame();
	PMPoint dimensions(panelBounds.Width(),panelBounds.Height());
	if(wasInfoAlreadyVisible)
	{
		if(fitSizeToAvailableInfo)
		{
			InterfacePtr<const IControlView> splitterView(splitterControlData,UseDefaultIID());
			int32 oldInfoSectionSize = ::ToInt32(splitterView->GetFrame().Height())  - splitterControlData->GetSplitterEdge();
			//dimensions.Y() += (splitterControlData->GetSplitterEdge() + newInfoSectionSize - splitterView->GetFrame().Height() + splitterControlData->GetSplitterSize()); // just resize by the change in size.
			dimensions.Y() +=  newInfoSectionSize - oldInfoSectionSize + splitterControlData->GetSplitterSize(); // just resize by the change in size.
			TRACEFLOW("Links:LinksUI:Resize","Fitting panel to info. Old info pane height %d. New info pane height %d\n",oldInfoSectionSize,newInfoSectionSize);
		}
	}
	else
		dimensions.Y() += newInfoSectionSize ;

	splitterControlData->SetPanelVisible(kLinkInfoPaneIndexForSplitter,true);


	// we want to try resizing the containing palette. Resizing the panel will work when the palette is floating, but if it's constrained in a dock it may fail.
	InterfacePtr<const IApplication> theApp (GetExecutionContextSession()->QueryApplication ());
	InterfacePtr<const IPanelMgr> panelMgr( theApp->QueryPanelManager() );
	PaletteRef palette = panelMgr->GetPaletteRefContainingPanel(linksUIPanelView);
	ASSERT_MSG(palette.IsValid(),"Got invalid palette - how can I resize?");
	if(PaletteRefUtils::IsPaletteFloating(palette))
	{
		TRACEFLOW("Links:LinksUI:Resize","Resizing floating panel to height %d\n",::ToInt32(dimensions.Y()));
		linksUIPanelView->Resize(dimensions);
		int newEdgeValue = ::ToInt32(linksUIPanelView->GetFrame().Height() - newInfoSectionSize ); 
//		TRACEFLOW("Links:LinksUI:Resize","Dimensions.Y() = %d, splitterview height %d, new edge value %d, current edge value %d, newInfoSectionSize %d\n",::ToInt32(dimensions.Y()),::ToInt32(splitterView->GetFrame().Height()),newEdgeValue,splitterControlData->GetSplitterEdge(),newInfoSectionSize);
		if(newEdgeValue != splitterControlData->GetSplitterEdge())
		{
			TRACEFLOW("Links:LinksUI:Resize","setting splitter edge to %d.\n",newEdgeValue);
			InterfacePtr<ISplitterPanelController> splitterController(splitterControlData,UseDefaultIID());
			splitterController->SetSplitterEdge(newEdgeValue);
		}
	#if ID_COCOA_ENABLE
		//FIXME_OWL_COCOA -- see ForceBottomOfPanelOnMonitor
	#else
		ForceBottomOfPanelOnMonitor(linksUIPanelView,dimensions.X());
		// this next bit is a little unusual. We need to resize the panel before we move the splitter, but moving the splitter affects our min/max panel size, and the PanelMgr only recalculates those on Resize...so we have to force a recalculation of our min/max size by calling UpdateOWLPaletteSizes()
		InterfacePtr<const IWidgetParent> wp(linksUIPanelView,UseDefaultIID());
		InterfacePtr<IOWLPaletteSizer> palSizer((IOWLPaletteSizer*)wp->QueryParentFor(IOWLPaletteSizer::kDefaultIID));
		palSizer->UpdateOWLPaletteSizes();
	#endif
	}
	else
	{
		SysRect paletteBounds = PaletteRefUtils::GetPaletteBounds(palette);
		SysPoint newPalSize;
		SetSysPoint(newPalSize,SysRectWidth(paletteBounds),::ToInt32(dimensions.Y()));
		TRACEFLOW("Links:LinksUI:Resize","Panel is not floating. Existing palette height %d, desired palette height %d\n",::ToInt32(SysRectHeight(paletteBounds)),::ToInt32(SysPointV(newPalSize)));
		if(SysPointV(newPalSize) != SysRectHeight(paletteBounds))
		{
			if(!wasInfoAlreadyVisible)
			{
				// open link info section at min size, and try to grow panel, which might not grow at all if the palette is constrained
				InterfacePtr<ISplitterPanelController> splitterController(splitterControlData,UseDefaultIID());
				splitterControlData->SetSplitterEdgeAbsolutePos(::ToInt32(panelBounds.Height()) /*pos*/, true /*updateSplitter*/, false /*shouldassert*/);				
			}
		
			TRACEFLOW("Links:LinksUI:Resize","Set splitter edge to %d. Trying to resize panel to height %d\n",splitterControlData->GetSplitterEdge(),::ToInt32(dimensions.Y()));
			PaletteRefUtils::SetPaletteSize(palette,newPalSize);
		}
	}	
}

void LinksUIUtilsImpl::ToggleLinkInfoSectionVisibility(bool onlyShow, bool fitSizeToAvailableInfo)
{
	IControlView* linksUIPanelView = GetLinksUIPanell();
	if(linksUIPanelView)
	{
		InterfacePtr<const IPanelControlData> linksPanelData(linksUIPanelView,UseDefaultIID());
		InterfacePtr<ISplitterPanelControlData> splitterControlData(linksPanelData->FindWidget(kLinkUISplitterPanelWidgetID),UseDefaultIID());
		if(splitterControlData->IsSinglePanelVisible() || onlyShow)
		{
			ShowInfoAndGrowPanel(linksUIPanelView,splitterControlData,fitSizeToAvailableInfo);
		}
		else
		{
			HideInfoAndShrinkPanel(linksUIPanelView,splitterControlData);
		}
		InterfacePtr<ISplitterPanelController> splitterController(splitterControlData,UseDefaultIID());
		splitterController->SyncPanelsToSplitter(true, false);			
		UpdateLinkInfoSectionButtonState();
	}

}

void	LinksUIUtilsImpl::UpdateLinkInfoSectionButtonState()
{
	InterfacePtr<const IPanelControlData> linksPanelData(GetLinksUIPanell(),UseDefaultIID());
	if(linksPanelData)
	{
		IControlView *buttonView = linksPanelData->FindWidget(kToggleLinkInfoButtonWidgetID);

		InterfacePtr<const ISplitterPanelControlData> splitterControlData((ISplitterPanelControlData*)Utils<IWidgetUtils>()->QueryRelatedWidget(buttonView,kLinkUISplitterPanelWidgetID,IID_ISPLITTERPANELCONTROLDATA));
		if(splitterControlData->IsSinglePanelVisible())
		{
			if (LocaleSetting::GetLocale().IsRightToLeftUI())
				buttonView->SetRsrcID(kTreeBranchCollapsedMERsrcID);
			else
				buttonView->SetRsrcID(kTreeBranchCollapsedRsrcID);
		}
		else
			buttonView->SetRsrcID(kTreeBranchExpandedRsrcID); 
	}
}

const ILinkInfoProvider* LinksUIUtilsImpl::QueryLinkInfoProviderFromHeaderWidget(const IPMUnknown* widget)
{
	InterfacePtr<const IWidgetParent> wp(widget,UseDefaultIID());
	if(wp)
	{
		InterfacePtr<const ITreeNodeIDData> nodeData((ITreeNodeIDData*)wp->QueryParentFor(IID_ITREENODEIDDATA));
		if(!nodeData)
		{
			// this is the header row.Now need to figure out which header was clicked on.
			return QueryInfoProviderFromLinksUIWidget(widget);
		}
	}
	return nil;
}

void LinksUIUtilsImpl::SetPanelSortProvider(const ILinkInfoProvider* newSortProvider)
{
	InterfacePtr<ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
	bool16 ascending = linksUIPrefs->GetSortLinksAscending();
	const ILinkInfoProvider* sortProvider = linksUIPrefs->GetSortInfoProvider();
	if(::GetClass(newSortProvider) == ::GetClass(sortProvider))
		ascending = !ascending;
	else
		sortProvider = newSortProvider;
		
	linksUIPrefs->SetSortInfoProvider(sortProvider);
	linksUIPrefs->SetSortLinksAscending(ascending);
	
}


static IDFile sDefaultUnembedLocation;

static bool GetDirectoryForEmbed(PMString &infoMessage, URI& chosenDirectoryURI)
{
	SysFileList selectedFolder;
	InterfacePtr<IOpenFileDialog> openDlg((IOpenFileDialog*)::CreateObject(kSelectFolderDialogBoss, IID_IOPENFILEDIALOG));
	if (! openDlg)
		return false;
	
	IDFile* defaultDir = nil;
	if ( sDefaultUnembedLocation.HasPath() )
		defaultDir = &sDefaultUnembedLocation;
	
	if(!openDlg->DoDialog(defaultDir, selectedFolder, kFalse, nil, &infoMessage))
		return false; // user cancelled

	IDFile selectedFile = *selectedFolder.GetNthFile(0);
	sDefaultUnembedLocation = selectedFile;

	Utils<IURIUtils>()->IDFileToURI(selectedFile,chosenDirectoryURI);
	return true;
	
}

bool16 LinksUIUtilsImpl::DoUnembedSelectedLinks(const UIDList& targetLinks, bool16 updateLink) const
{
#pragma unused(updateLink)

	PMString alertString("UnembedToOriginal");
	// "Unembed can link to the original files or it can link to files it creates in a folder."
	// "Do you want link to the original files?"

	bool linkToOriginal = false;
	int32 ret = CAlert::ModalAlert(alertString, kYesString, kNoString, kCancelString, 1, CAlert::eWarningIcon);
	if (ret == 1)
		linkToOriginal = true;	// Yes, link to originals.
	else if (ret == 2)
		linkToOriginal = false;  // No, create files in one folder.
	else
		return false;  // user cancelled

	Utils<Facade::ILinkFacade> linkFacade;
	if (linkToOriginal)
		linkFacade->UnembedLinks(targetLinks,kFullUI);
	else
	{
		// Put up the system dialog for selecting a folder to get the directory to use.
		PMString string("#SelectUnembedDir");
		string.Translate();

		URI folderURI;
		if (!GetDirectoryForEmbed(string,folderURI))
			return false;  // user cancelled
		
		linkFacade->UnembedLinks(targetLinks,folderURI,kFullUI);
	}

	return true;
}			
			
ILinkInfoProvider* LinksUIUtilsImpl::QueryInfoProviderFromLinksUIWidget(const IPMUnknown* widget) const
{
//	InterfacePtr<const IWidgetParent> wp(widget,UseDefaultIID());
	InterfacePtr<const IIntData> providerIndexData(widget,IID_LINKINFOPROVIDERINDEX);
	if(providerIndexData && providerIndexData->Get() >= 0)
	{		
		InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
//#ifdef DEBUG
//		{
//			InterfacePtr<const ITextControlData> textDataDebug(widget,UseDefaultIID());
//			PMString debugText;
//			if(textDataDebug)
//				debugText = textDataDebug->GetString();
//			
//			TRACEFLOW("Links:LinksUI","QueryInfoProviderFromLinksUIWidget for widget with current text '%s' returning provider with index %d\n",debugText.GrabCString(),providerIndexData->Get());
//		}
//#endif		
		if(providerIndexData->Get() < linksUIPrefs->GetNumShowingInfoColumns())
			return linksUIPrefs->QueryNthShowingInfoColumn(providerIndexData->Get());
	}
	TRACEFLOW("Links:LinksUI","LinksUIUtilsImpl::QueryInfoProviderFromLinksUIWidget returning nil for this widget\n");
	return nil;
}

ILink* LinksUIUtilsImpl::QueryLinkFromLinksUIWidget(const IPMUnknown* widget) const
{
	NodeID theNode = GetTreeRowNodeFromChildWidget(widget);
	if(theNode.IsValid())
	{
		TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(theNode);
		InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		UID linkUID = linksUIDNode ? linksUIDNode->GetLinkUIDRef().GetUID() : kInvalidUID;
		if(linkUID != kInvalidUID && linksUIPrefs->GetCurrentDocDB() && linksUIDNode->GetLinkUIDRef().GetDataBase()->IsValidUID(linkUID))
		{
			IDataBase* cachedCurrentDocDB = linksUIPrefs->GetCurrentDocDB();
			//IDataBase* cachedLinkDB = linksUIDNode->GetLinkUIDRef().GetDataBase();
			//ASSERT_MSG(cachedCurrentDocDB == cachedLinkDB, "LinksUIUtilsImpl::QueryLinkFromLinksUIWidget cached current document database and cached link database do not match!");
			//ASSERT_MSG(cachedCurrentDocDB->IsValidUID(linkUID), FORMAT_ARGS("LinksUIUtilsImpl::QueryLinkFromLinksUIWidget invalid UID in cached current doc database 0x%x", cachedCurrentDocDB));
			//ASSERT_MSG(cachedLinkDB->IsValidUID(linkUID), FORMAT_ARGS("LinksUIUtilsImpl::QueryLinkFromLinksUIWidget invalid UID in cached link database 0x%x", cachedLinkDB));
			if(cachedCurrentDocDB->IsValidUID(linkUID))
			{
				InterfacePtr<ILink> link(linksUIPrefs->GetCurrentDocDB(),linkUID,UseDefaultIID());
				if(link)
				{
					link->AddRef();
					return link;
				}
			}
		}
	}
	return nil;
}

ILinkResource* LinksUIUtilsImpl::QueryLinkResourceFromLinksUIWidget(const IPMUnknown* widget) const
{
	NodeID theNode = GetTreeRowNodeFromChildWidget(widget);
	if(theNode.IsValid())
	{
		TreeNodePtr<const LinksTreeUIDNodeID>	linksUIDNode(theNode);
		InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		UID linkResourceUID = linksUIDNode ? linksUIDNode->GetLinkResourceUID() : kInvalidUID; 
		if(linkResourceUID != kInvalidUID && linksUIPrefs->GetCurrentDocDB() && linksUIPrefs->GetCurrentDocDB()->IsValidUID(linkResourceUID))
		{
			InterfacePtr<ILinkResource> linkResource(linksUIPrefs->GetCurrentDocDB(),linkResourceUID,UseDefaultIID());
			if(linkResource)
			{
				linkResource->AddRef();
				return linkResource;
			}
		}
	}
	return nil;
}

IMetaDataAccess* LinksUIUtilsImpl::QueryMetaDataAccessFromLink(const ILink* link) const
{
	InterfacePtr<const ILinkObject> linkObj(::GetDataBase(link),link->GetObject(),UseDefaultIID());
	if(linkObj)
	{
		InterfacePtr<const IPersistUIDData> metadataUIDData( linkObj,IID_IMETADATAUIDDATA);
		if(metadataUIDData)
		{
			const UID metaDataUID = metadataUIDData->GetUID();
			if(metaDataUID != kInvalidUID)
			{
				return (IMetaDataAccess*)::GetDataBase(link)->Instantiate(metaDataUID, IID_IMETADATAACCESS );
			}
		}
	}
	return nil;
}


IImageCache* LinksUIUtilsImpl::QueryThumbnailForLink(const ILink * theLink, const ILinkResource * linkResource) const 
{
	InterfacePtr<const ILink> link(theLink,UseDefaultIID());
	IThumbnailUtils* thumbnailUtils = Utils<IThumbnailUtils>();
	if ( thumbnailUtils )
	{
		if(!link)
		{
			if(linkResource)
			{
				IDataBase* docDB = ::GetDataBase(linkResource);
				InterfacePtr<const ILinkManager> linkMgr(docDB,docDB->GetRootUID(),UseDefaultIID());
				ILinkManager::QueryResult listOfLinks;
				linkMgr->QueryLinksByResourceUID(::GetUID(linkResource), false, listOfLinks);
				if(listOfLinks.size() > 0)
				{
					InterfacePtr<const ILink> linkFromResource(docDB,listOfLinks[0],UseDefaultIID());
					link.reset(linkFromResource.forget());
				}
			}
		}
		if(link)
		{
			InterfacePtr<IImageCache> iImageCache;
			InterfacePtr<const ILinkObject> linkObject(::GetDataBase(link),link->GetObject(),UseDefaultIID());
			if(linkObject)
				iImageCache.reset(thumbnailUtils->QueryThumbnail(::GetUIDRef(linkObject)));

			if ( !iImageCache )
				iImageCache.reset(thumbnailUtils->QueryThumbnail(::GetUIDRef(link)));
				
			if(iImageCache)
			{
				iImageCache->AddRef();
				return iImageCache;
			}
					
		}
	}
	return nil;
			
}

static void SelectDropdownItemForProvider(const IStringListControlData* ddStrings, const PMString& providerName)
{
	InterfacePtr<IDropDownListController> ddController(ddStrings,UseDefaultIID());
	if(providerName == "")
	{
		ddController->Select(0);
		return;
	}

	for(int index = 0; index < ddStrings->Length(); ++index)
	{
		PMString ddString = ddStrings->GetString(index);
		if(providerName == ddString)
		{
			ddController->Select(index,kFalse);
			return;
		}
	}
	ASSERT_FAIL("SelectDropdownItemForProvider failed to find correct link info provider in string list");
}

void LinksUIUtilsImpl::SetupCaptionRowWidget(const IPMUnknown* rowView,const PMString& beforeString, const PMString& providerName,const PMString& afterString) const
{
	InterfacePtr<const IPanelControlData> rowPanelData(rowView,UseDefaultIID());
	
	InterfacePtr<IStringListControlData> ddStrings(rowPanelData->FindWidget(kCaptionMetadataDropDownWidgetID),UseDefaultIID());
	if(ddStrings->Length() == 0)
	{
		// populate the strings in the dropdown if we've never filled them out
		InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		const int32 numProviders = linksUIPrefs->GetNumInfoProviders();
		for(int index = 0; index < numProviders; ++index)
		{
			InterfacePtr<const ILinkInfoProvider> linkInfoProvider(linksUIPrefs->QueryNthInfoProvider(index));
			PMString metadataName = linkInfoProvider->GetInfoDescriptionString();
			ddStrings->AddString(metadataName);
		}
	}
	
	// set up the row widgets based on the prefs.
	InterfacePtr<ITextControlData> beforeData(rowPanelData->FindWidget(kCaptionBeforeMetadataEditWidgetID), UseDefaultIID());
	beforeData->SetString(beforeString, kFalse);

	SelectDropdownItemForProvider(ddStrings,providerName);

	InterfacePtr<ITextControlData> afterData(rowPanelData->FindWidget(kCaptionAfterMetadataEditWidgetID), UseDefaultIID());
	afterData->SetString(afterString, kFalse);
}

