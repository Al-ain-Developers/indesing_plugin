//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerPanelTreeObserver.cpp $
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
#include "IDocument.h"
#include "ISubject.h"
#include "ITreeViewMgr.h"
#include "ILayoutControlData.h"
#include "IControlView.h"
#include "ITextControlData.h"
#include "IWidgetUtils.h"
#include "ILayerUtils.h"
#include "ILayerList.h"
#include "ITreeViewController.h"
#include "IDocumentLayer.h"
#include "ILayoutCmdData.h"
#include "ILayoutUtils.h"
#include "ISpreadLayer.h"
#include "IHierarchy.h"
#include "IWidgetParent.h"
#include "IUIDData.h"
#include "IPageList.h"
#include "ISpread.h"

// ----- Includes -----

#include "CObserver.h"
#include "LayerPanelID.h"
#include "LayerID.h"
#include "ILayoutUIUtils.h"

#include "ListLazyNotificationData.h"
#include "LayerTreeUIDNodeID.h"
#include "StringUtils.h"
#include "K2Vector.tpp"
#include "GenericID.h"
#include "LocaleSetting.h"
#include "LayerPanelUtils.h"

//========================================================================================
// CLASS LayerPanelTreeObserver
//========================================================================================
class LayerPanelTreeObserver : public CObserver
{
	public:
		LayerPanelTreeObserver(IPMUnknown *boss);
		virtual ~LayerPanelTreeObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);
		
		virtual void AutoAttach();
			// If the observer knows who to attach itself to, it'll do so with this call
			
		virtual void AutoDetach();
			// If the observer knows who to detach itself from, it'll do so with this call

	private:
		void ActiveDocChange();
		void AttachToNewFrontDoc(const IDocument* newFrontDoc);
		void DetachFromDoc();
		void RebuildTree(bool eliminateTreeSelection, bool updateFromLayoutSelection) const;
		void ActiveLayoutChange();
		void DetachFromLayout();
		void AttachToLayout(const IControlView *layout);
		void UpdateStatusWidget() const;
		void UpdateActiveLayer(UID newActiveLayer) const;
		
		const IDocument*	fCurrentDocument;
		const IControlView*	fCurrentLayout;
		mutable UID		fCachedActiveLayer;
		mutable int32		fCachedNumLayers;
};


CREATE_PMINTERFACE(LayerPanelTreeObserver, kLayerPanelTreeObserverImpl)

//----------------------------------------------------------------------------------------
// LayerPanelTreeObserver constructor 
//----------------------------------------------------------------------------------------

LayerPanelTreeObserver::LayerPanelTreeObserver(IPMUnknown *boss) :
	CObserver(boss),fCurrentDocument(nil),fCurrentLayout(nil),fCachedActiveLayer(kInvalidUID),fCachedNumLayers(-1)
{
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeObserver::~LayerPanelTreeObserver: 
//----------------------------------------------------------------------------------------

LayerPanelTreeObserver::~LayerPanelTreeObserver()
{
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeObserver::AutoAttach: 
//----------------------------------------------------------------------------------------
void LayerPanelTreeObserver::AutoAttach()
{
	// attach to the active context, so we can see changes to the active document and active layout
	ActiveDocChange();
	
	RebuildTree(true,true);

	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());

		if (contextSubject)
		{
			contextSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER);
		}
		
		IControlView* activeView = context->GetContextView();
		InterfacePtr<ILayoutControlData> isLayoutView( activeView, UseDefaultIID());
		
		if (isLayoutView && (activeView != fCurrentLayout))
		{
			AttachToLayout(activeView);
			UpdateStatusWidget();
		}

	}
		
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeObserver::AutoDetach: 
//----------------------------------------------------------------------------------------
void LayerPanelTreeObserver::AutoDetach()
{
	CObserver::AutoDetach();
	
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, UseDefaultIID());

		if (contextSubject)
		{
			if (contextSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER))
			{
				contextSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IACTIVECONTEXT,IID_IOBSERVER);
			}
		}
	}

	DetachFromDoc();
	DetachFromLayout();
	

}

//----------------------------------------------------------------------------------------
// LayerPanelTreeObserver::Update: 
//----------------------------------------------------------------------------------------
void LayerPanelTreeObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
#ifdef DEBUG				
	DebugClassUtilsBuffer buf1;
	TRACEFLOW("LayerPanel","LayerPanelTreeObserver::Update got message IID %s\n",DebugClassUtils::GetIDName(&buf1,protocol));
#endif		


	#pragma unused(theChange,theSubject)
	if (protocol == IID_IACTIVECONTEXT)  //this protocol sends IID instead of cmdID
	{
		const PMIID& what = *((const PMIID*)changedBy);

		if( what == IID_IDOCUMENT )
		{
			ActiveDocChange();
			//TRACEFLOW("Layer","LayerPanelTreeObserver::Update forcing tree to rebuild for active document change\n");
			RebuildTree(true,false);
		}
		else if (what == IID_ICONTROLVIEW)	
		{
			ActiveLayoutChange();
		}
	}
}


void LayerPanelTreeObserver::RebuildTree(bool eliminateTreeSelection, bool updateFromLayoutSelection) const
{
#if !defined (ENABLE_ALL_TRACES)
	TRACEFLOW("Layer","LayerPanelTreeObserver forcing tree to rebuild for some change\n");
#endif
	InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());
	treeViewMgr->ChangeRoot();
	
	
	if(eliminateTreeSelection)
	{
		InterfacePtr<ITreeViewController> treeController(this,UseDefaultIID());
		treeController->DeselectAll();
	}
	// kick the selection observer to update the proxy selection.
	if(updateFromLayoutSelection)
	{
		InterfacePtr<IObserver> selectionObserver(this,IID_ISELECTIONOBSERVER);
		selectionObserver->Update(kInvalidClass, nil, IID_IUPDATEPROXYSELECTION, nil);
	}
	fCachedActiveLayer = kInvalidUID;

	UpdateStatusWidget();
}

void LayerPanelTreeObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
#ifdef DEBUG				
	DebugClassUtilsBuffer buf1;
	TRACEFLOW("LayerPanel","LayerPanelTreeObserver::LazyUpdate got message IID %s\n",DebugClassUtils::GetIDName(&buf1,protocol));
#endif				
	#pragma unused(data,theSubject)
	switch(protocol.Get())
	{
		case IID_IACTIVESPREAD:
		{
			RebuildTree(true,true);
			break;
		}
		case IID_ISPREADLIST:
		{
			UpdateStatusWidget();
			break;
		}
		
		case IID_IVISIBLE:
		case IID_IPAGEITEMNAME:
		case IID_ILAYERLIST:
		case IID_IACTIVELAYER:
		case IID_ILOCKPOSITION:
		case IID_ISPREADLAYERHIERARCHYCHANGED:
		{
			K2Vector<UID> addedItems, updatedItems, deletedItems;
			const ListLazyNotificationData<UID> *listData = static_cast<const ListLazyNotificationData<UID> *>(data);
			if (listData && !listData->ShouldRebuildAll())
				listData->BreakoutChanges(&addedItems, &deletedItems, &updatedItems);
			else
			{
				RebuildTree(false,true);
				return;
			}

			if(protocol ==  IID_IACTIVELAYER)
			{
				ASSERT_MSG(addedItems.empty() && deletedItems.empty() && updatedItems.size() > 0,"Unexpected data for IID_IACTIVELAYER change");
				InterfacePtr<ILayoutControlData> layoutData(fCurrentLayout, UseDefaultIID());
				if (layoutData)
				{
					UpdateActiveLayer(layoutData->GetActiveDocLayerUID());
				}
			}
			else if(!addedItems.empty() || !deletedItems.empty())
			{
				RebuildTree(false,true);
			}
			else if(!updatedItems.empty())
			{
				InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());
				if(protocol == IID_ISPREADLAYERHIERARCHYCHANGED)
				{
					// this notification is spread layers
					IDataBase *db = ::GetDataBase(fCurrentDocument);
					for(K2Vector<UID>::const_iterator i = updatedItems.begin(); i != updatedItems.end(); ++i)
					{
						if(db->IsValidUID(*i))  // combination of lazy notifications and undo might mean we get notified about a layer that no longer exists
						{
							InterfacePtr<const ISpreadLayer> spreadLayer(db,*i,UseDefaultIID());
							
							UID docLayerUID = spreadLayer->GetDocLayerUID();
							NodeID changedNode = LayerTreeUIDNodeID::Create(docLayerUID,kTrue);						
#if !defined (ENABLE_ALL_TRACES)
							TRACEFLOW("LayerPanel","Invalidating node for layer UID %d for IID_ISPREADLAYERHIERARCHYCHANGED\n",docLayerUID);
#endif
							treeViewMgr->RefreshSubTree(changedNode);
						}
					}
//					// kick the selection observer, since we potentially just changed some nodes which might be showing selection proxies,
//					InterfacePtr<IObserver> selectionObserver(this,IID_ISELECTIONOBSERVER);
//					selectionObserver->Update(kInvalidClass, nil, IID_IUPDATEPROXYSELECTION, nil);
					
				}
				else if(protocol ==  IID_ILAYERLIST)
				{
					for(K2Vector<UID>::const_iterator i = updatedItems.begin(); i != updatedItems.end(); ++i)
					{
						NodeID changedNode = LayerTreeUIDNodeID::Create(*i,kTrue);						
						treeViewMgr->RefreshSubTree(changedNode); // change could affect children, for example layer color change.
					}
				}
				else
				{
					ASSERT_MSG(protocol == IID_ILOCKPOSITION || protocol == IID_IPAGEITEMNAME || protocol == IID_IVISIBLE,"unexpected protocol notification");
					if(fCurrentLayout)
					{
						IDataBase *db = ::GetDataBase(fCurrentDocument);
						for(K2Vector<UID>::const_iterator i = updatedItems.begin(); i != updatedItems.end(); ++i)
						{
							LayerPanelUtils::InvalidateNodeForPageItem(treeViewMgr,db,*i, protocol == IID_IVISIBLE ? true : false);
						}
					}
				}
			}
			break;
		}
	}
	

}

//----------------------------------------------------------------------------------------
// LayerPanelTreeObserver::AttachToNewFrontDoc 
//----------------------------------------------------------------------------------------
void LayerPanelTreeObserver::AttachToNewFrontDoc(const IDocument* newFrontDoc)
{
	if( newFrontDoc )
	{		
		InterfacePtr<ISubject>	docSubject( newFrontDoc, UseDefaultIID() );
		docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ILAYERLIST, IID_IOBSERVER);
		docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER);
		docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ILOCKPOSITION, IID_IOBSERVER);
		docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IVISIBLE, IID_IOBSERVER);
		docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IPAGEITEMNAME, IID_IOBSERVER);
		docSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ISPREADLAYERHIERARCHYCHANGED, IID_IOBSERVER);
		fCurrentDocument = newFrontDoc;
		
		InterfacePtr<const IWidgetParent> wp(this,UseDefaultIID());
		InterfacePtr<IUIDData> curDocData((IUIDData*)wp->QueryParentFor(IID_ILAYERPANELDOCUMENTDATA));
		curDocData->Set(newFrontDoc);
	}
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeObserver::DetachFromDoc 
//----------------------------------------------------------------------------------------
void LayerPanelTreeObserver::DetachFromDoc()
{
	
	InterfacePtr<ISubject> oldSubject(fCurrentDocument, IID_ISUBJECT);
	if (oldSubject)
	{
		oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ILAYERLIST, IID_IOBSERVER);
		oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ISPREADLIST, IID_IOBSERVER);
		oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ILOCKPOSITION, IID_IOBSERVER);
		oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_IVISIBLE, IID_IOBSERVER);
		oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_IPAGEITEMNAME, IID_IOBSERVER);
		oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ISPREADLAYERHIERARCHYCHANGED, IID_IOBSERVER);
		fCurrentDocument = nil;
	}

	InterfacePtr<const IWidgetParent> wp(this,UseDefaultIID());
		InterfacePtr<IUIDData> curDocData((IUIDData*)wp->QueryParentFor(IID_ILAYERPANELDOCUMENTDATA));
	curDocData->Set(nil);
}

//----------------------------------------------------------------------------------------
// LayerPanelTreeObserver::ActiveDocChange: 
//----------------------------------------------------------------------------------------
void LayerPanelTreeObserver::ActiveDocChange()
{
	DetachFromDoc();
	AttachToNewFrontDoc(Utils<ILayoutUIUtils>()->GetFrontDocument());

}


void LayerPanelTreeObserver::ActiveLayoutChange()
{
	InterfacePtr<const ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
	if(layoutData)
	{		
		InterfacePtr<const IControlView> currentView(layoutData,UseDefaultIID());
		if (fCurrentLayout != currentView)
		{
			// if we are already attached to a  different LayoutControlData, detach from that
			this->DetachFromLayout();  
			
			this->AttachToLayout(currentView);
			
			RebuildTree(true,false);

		}
	}
	else if (fCurrentLayout)
	{
		this->DetachFromLayout();

		RebuildTree(true,true);
	}
}

void LayerPanelTreeObserver::DetachFromLayout()
{ 	
	if (fCurrentLayout)
	{
		InterfacePtr<ISubject> subject(fCurrentLayout, UseDefaultIID());
		
		if (subject)
		{
			subject->DetachObserver(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER);
			subject->DetachObserver(ISubject::kLazyAttachment,this, IID_IACTIVELAYER, IID_IOBSERVER);
		}
	}
	fCachedActiveLayer = kInvalidUID;
	fCurrentLayout = nil;
}

void LayerPanelTreeObserver::AttachToLayout(const IControlView *layout)
{
	if (fCurrentLayout != layout)
	{
		InterfacePtr<ISubject> subject(layout, UseDefaultIID());
		
		if (subject)
		{
			subject->AttachObserver(ISubject::kLazyAttachment,this, IID_IACTIVESPREAD, IID_IOBSERVER);
			subject->AttachObserver(ISubject::kLazyAttachment,this, IID_IACTIVELAYER, IID_IOBSERVER);
		}
		
		fCurrentLayout = layout;
		
		InterfacePtr<ILayoutControlData> layoutData(fCurrentLayout, UseDefaultIID());
		
		if (layoutData)
		{
			UpdateActiveLayer(layoutData->GetActiveDocLayerUID());
		}
	}
}

void LayerPanelTreeObserver::UpdateStatusWidget() const
{
	InterfacePtr<ITextControlData> textData((ITextControlData*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLayerStatusWidgetID,IID_ITEXTCONTROLDATA));

	if(textData)
	{

		int32 layerCount = -1;
		if (fCurrentDocument)
		{
			InterfacePtr<const ILayerList> layerList(fCurrentDocument, UseDefaultIID());
			layerCount = Utils<ILayerUtils>()->CountUILayers(layerList);
		}
		fCachedNumLayers = layerCount;

		PMString statusString;
		if (layerCount != -1)
		{
		
			PMString pageString;
			InterfacePtr<const ILayoutControlData> layoutData(fCurrentLayout, UseDefaultIID());
			if (layoutData)
			{
				UIDRef activeSpreadRef = layoutData->GetSpreadRef();
				InterfacePtr<const ISpread> activeSpread(activeSpreadRef,UseDefaultIID());
				
				UIDList listOfPages(activeSpreadRef.GetDataBase());
				int32 numPages = activeSpread->GetNumPages();
				for(int32 i = 0; i < numPages; ++i)
					listOfPages.push_back(activeSpread->GetNthPageUID(i));
				
				if(numPages == 1)
					pageString = "#Page:^1,";
				else
					pageString = "#Pages:^1,";
				pageString.Translate();
																								
				InterfacePtr<const IPageList> pageList(activeSpreadRef.GetDataBase(),activeSpreadRef.GetDataBase()->GetRootUID(), UseDefaultIID());
				
				PMString pageRangeString;
				pageList->GetPageRangeString(listOfPages,&pageRangeString);	
				::ReplaceStringParameters(&pageString, pageRangeString);
			}
		
			PMString layerString;
			if (layerCount == 1)
				layerString = "^1 Layer";
			else
				layerString = "^1 Layers";
			layerString.Translate();
			
			PMString	layerCountString;
			layerCountString.AsNumber(layerCount);
			::ReplaceStringParameters(&layerString, layerCountString);

		
			statusString = pageString;
			statusString.Append(layerString);
			statusString.SetTranslated();
		}

		textData->SetString(statusString);	// so it reads "4 Layers" or whatever
	}

}

void LayerPanelTreeObserver::UpdateActiveLayer(UID newActiveLayer) const
{
#if !defined (ENABLE_ALL_TRACES)
	TRACEFLOW("LayerPanel","UpdateActiveLayer for UID %d\n",newActiveLayer.Get());
#endif
    
	InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());
	if(fCachedActiveLayer != kInvalidUID && fCurrentDocument && ::GetDataBase(fCurrentDocument)->IsValidUID(fCachedActiveLayer))
	{
		NodeID oldActiveNode = LayerTreeUIDNodeID::Create(fCachedActiveLayer,kTrue);
		treeViewMgr->NodeChanged(oldActiveNode);
	}

	if(fCurrentDocument && ::GetDataBase(fCurrentDocument)->IsValidUID(newActiveLayer)) 
	{
		InterfacePtr<const ILayerList> layerList(fCurrentDocument, UseDefaultIID());
		if(fCachedNumLayers == Utils<ILayerUtils>()->CountUILayers(layerList)) // sometimes we get active layer changes while waiting for layer deletes to come thru. Don't update in this case.
		{
			NodeID newActiveNode = LayerTreeUIDNodeID::Create(newActiveLayer,kTrue);
			treeViewMgr->NodeChanged(newActiveNode);
			if(fCachedActiveLayer != newActiveLayer)
			{
				InterfacePtr<ITreeViewController> treeController(this,UseDefaultIID());
				NodeIDList selectedItems;
				treeController->GetSelectedItems(selectedItems);
				bool activeLayerIsSelectedInPanel = false;
				for (auto iter = selectedItems.rbegin(); iter != selectedItems.rend(); ++iter)
				{
					TreeNodePtr<const LayerTreeUIDNodeID>	layerNode(*iter);
					if(layerNode->GetUID() == newActiveLayer)
					{
						activeLayerIsSelectedInPanel = true;
						break;
					}
				}
				if(!activeLayerIsSelectedInPanel)
				{
					treeController->DeselectAll();
					treeController->Select(newActiveNode);
				}
				fCachedActiveLayer = newActiveLayer;
			}
		}
	}
}

