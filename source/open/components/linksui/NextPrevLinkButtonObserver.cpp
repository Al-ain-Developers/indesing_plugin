//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/NextPrevLinkButtonObserver.cpp $
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
#include "ISubject.h"
#include "IControlView.h"
#include "ILinksUIPanelPrefs.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewController.h"

// ----- Includes -----

#include "CObserver.h"
#include "LinksTreeUIDNodeID.h"
#include "TreeNodeTraverser.h"
#include "UIDList.h"

// ----- Utility files -----

#include "ILinksUIUtils.h"
#include "IWidgetUtils.h"
#include "Utils.h"
#include "PreferenceUtils.h"

// ----- ID.h files -----

#include "LinksUIID.h"

class NextPrevLinkButtonObserver : public CObserver
{
	public:
		NextPrevLinkButtonObserver(IPMUnknown *boss);
		virtual ~NextPrevLinkButtonObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();
		virtual void AutoDetach();
	private:
		void UpdateButtonState();
};


CREATE_PMINTERFACE(NextPrevLinkButtonObserver, kNextPrevLinkButtonObserverImpl)

//----------------------------------------------------------------------------------------
// NextPrevLinkButtonObserver constructor 
//----------------------------------------------------------------------------------------

NextPrevLinkButtonObserver::NextPrevLinkButtonObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}

//----------------------------------------------------------------------------------------
// NextPrevLinkButtonObserver::~NextPrevLinkButtonObserver: 
//----------------------------------------------------------------------------------------

NextPrevLinkButtonObserver::~NextPrevLinkButtonObserver()
{
}

//----------------------------------------------------------------------------------------
// NextPrevLinkButtonObserver::AutoAttach: 
//----------------------------------------------------------------------------------------
void NextPrevLinkButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget( this, kLinksUIPanelTreeWidgetID,IID_ISUBJECT ));
	treeSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
	
	UpdateButtonState();
}

//----------------------------------------------------------------------------------------
// NextPrevLinkButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------
void NextPrevLinkButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
	
	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ISUBJECT));
	treeSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
}

static NodeID_rv GetNextPrevNode(const ITreeViewHierarchyAdapter* treeAdapter, const NodeID& node, bool isNextButton)
{
	ASSERT_MSG(treeAdapter->GetNumChildren( treeAdapter->GetRootNode()) > 0,"Button should be disabled!");

	InterfacePtr<const ITreeViewMgr> treeMgr(treeAdapter,UseDefaultIID());
	TreeNodeTraverser	traverse(node, treeMgr, kTrue, isNextButton  ? TreeNodeTraverser::eForward : TreeNodeTraverser::eReverse);	
	NodeID nodeToSelect =  traverse.Next();
	if(!nodeToSelect.IsValid() || nodeToSelect == treeAdapter->GetRootNode())
	{
		if(isNextButton)
			nodeToSelect = treeAdapter->GetNthChild(treeAdapter->GetRootNode(),0); // select first
		else
			nodeToSelect = treeAdapter->GetNthChild(treeAdapter->GetRootNode(),treeAdapter->GetNumChildren(treeAdapter->GetRootNode()) - 1); // select last
	}
	return nodeToSelect;

//	NodeID parentNode = treeAdapter->GetParentNode(node);
//	int32 oldSelectedChildIndex = treeAdapter->GetChildIndex(parentNode,node);
//
//	if(isNextButton)
//	{
//		if(treeAdapter->GetNumChildren(parentNode)  - 1 > oldSelectedChildIndex)
//			return treeAdapter->GetNthChild(parentNode,oldSelectedChildIndex + 1);
//		else
//			return GetNextPrevNode(treeAdapter,parentNode,isNextButton);
//	}
//	else
//	{
//		if(oldSelectedChildIndex > 0)
//			return treeAdapter->GetNthChild(parentNode,oldSelectedChildIndex - 1);
//		else
//			return GetNextPrevNode(treeAdapter,parentNode,isNextButton);
//	}
}
void NextPrevLinkButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	#pragma unused(changedBy)
	if (protocol == IID_ITRISTATECONTROLDATA && theChange == kTrueStateMessage)
	{
		InterfacePtr<const IControlView> buttonView(theSubject,UseDefaultIID());
		ASSERT_MSG(buttonView->GetWidgetID() == kSelectNextLinkButtonWidgetID || buttonView->GetWidgetID() == kSelectPrevLinkButtonWidgetID,"Unexpected widget notification");
		bool isNextButton = (buttonView->GetWidgetID() == kSelectNextLinkButtonWidgetID);

		InterfacePtr<ITreeViewController> treeController((ITreeViewController*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ITREEVIEWCONTROLLER));
		NodeIDList selectedItems;
		treeController->GetSelectedItemsDisplayOrder(selectedItems);
		
		InterfacePtr<const ITreeViewHierarchyAdapter> treeAdapter(treeController,UseDefaultIID());
		
		NodeID nodeToSelect;
		
		if(selectedItems.size() == 0)
		{
			// nothing is selected. Select either the first or last item, depending on which button was clicked.
			NodeID rootNode = treeAdapter->GetRootNode();
			nodeToSelect = GetNextPrevNode(treeAdapter,rootNode,isNextButton);
		}
		else // something is selected. Select relative to the first item in the list
		{
			NodeID oldSelectedNode = selectedItems[0];
			nodeToSelect = GetNextPrevNode(treeAdapter,oldSelectedNode,isNextButton);
		}
		if(nodeToSelect.IsValid())
		{
			TreeNodePtr<const LinksTreeUIDNodeID>  linksUIDNode(nodeToSelect);
			if (linksUIDNode)
			{
				InterfacePtr<const ILinksUIPanelPrefs> linksUIPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
				IDataBase* db = linksUIPrefs->GetCurrentDocDB();

				UIDRef linkUIDRef = linksUIDNode->GetLinkUIDRef();
				if (linkUIDRef.GetUID() != kInvalidUID)	// Could be a parent node with no link UID
				{
					UIDList links(db, linkUIDRef.GetUID());
					Utils<ILinksUIUtils>()->SelectLinksInPanel(links);
				}
				else
				{
					treeController->DeselectAll();
					treeController->Select(nodeToSelect);
				}
			}
		}
	}
	else if(protocol == IID_ITREEVIEWCONTROLLER)
	{
		UpdateButtonState();
	}
}

void NextPrevLinkButtonObserver::UpdateButtonState()
{	
	InterfacePtr<const ITreeViewHierarchyAdapter> treeAdapter((ITreeViewHierarchyAdapter*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ITREEVIEWHIERARCHYADAPTER));

	NodeID rootNode = treeAdapter->GetRootNode();
	
	InterfacePtr<IControlView> view(this,UseDefaultIID());
	
	bool enableButtons = false;
	if(treeAdapter->GetNumChildren(rootNode) > 1)
		enableButtons = true;
	else if(treeAdapter->GetNumChildren(rootNode) == 1)
	{
		NodeID onlyChild = treeAdapter->GetNthChild(rootNode,0);
		InterfacePtr<const ITreeViewMgr> treeViewMgr(treeAdapter,UseDefaultIID());
		if(treeAdapter->GetNumChildren(onlyChild) > 1 && treeViewMgr->IsNodeExpanded(onlyChild))
			enableButtons = true;
	}
	
	
	if(enableButtons)
		view->Enable();
	else
		view->Disable();
}
