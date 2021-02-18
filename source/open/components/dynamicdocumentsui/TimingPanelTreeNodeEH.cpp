//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelTreeNodeEH.cpp $
//  
//  Owner: Yeming Liu
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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

#include "IWidgetParent.h"
#include "IWindow.h"
#include "ISubject.h"
#include "ILayoutSelectionSuite.h"
#include "ISelectionManager.h"
#include "ITreeNodeIDData.h"
#include "ITreeAttributes.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IControlView.h"
#include "IDynamicEventTimingSuite.h"
#include "IDynamicEventTimingFacade.h"
#include "IDynamicTargetsFacade.h"
#include "ILayerUtils.h"
#include "ISelectionUtils.h"

// ----- Include files -----

#include "TreeNodeEventHandler.h"
#include "TimingPanelTreeNodeID.h"
#include "DynamicDocumentsUIUtils.h"
#include "CTreeViewMgr.h"
#include "TreeNodeTraverser.h"
#include "K2Vector.tpp"

// ----- Utility files -----

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

class TimingPanelTreeNodeEH : public TreeNodeEventHandler
{
	public:
		TimingPanelTreeNodeEH(IPMUnknown *boss) : TreeNodeEventHandler(boss) { }
		virtual ~TimingPanelTreeNodeEH() { }

        virtual bool16 LButtonDn(IEvent *e); 
		virtual bool16 ButtonDblClk(IEvent* e);

private:

		void ProcessSelectionRulesButDontSelect (ITreeViewController* iTVController, IEvent* event, UID nodeWidgetUID, NodeIDList& newNodes);
};

CREATE_PMINTERFACE(TimingPanelTreeNodeEH, kTimingPanelTreeNodeEHImpl)

//_________________________________________________________________________________________ 
//	LButtonDn
//	Note:	This is essentially the same as TreeNodeEventHandler except that 
//			we want to cache a list of selected nodes before next selection changes.
//			We also suppress notification until we are done with ProcessSelectionRules so that
//			we only get one kListSelectionChangedMessage instead of multiple ones.
//
//	Tried calling ITreeViewController::ProcessSelectionRules after the current edit values
//	are validated and applied. This caused the widgets in the list to get recreated so that
//	when ProcessSelectionRules is called, this widget UID is no longer valid.
//	
//	Instead, ProcessSelectionRulesButDontSelect process the selections using similar algorithm.
//	But, we don't select or hilite the new selection until the current edit value is validated.
//_________________________________________________________________________________________ 
bool16 TimingPanelTreeNodeEH::LButtonDn(IEvent *e) 
{ 
	if (HandleLButtonDnBeforeSelectionProcessing(e))
		return kTrue;
		
	InterfacePtr<IWidgetParent>	iWidgetParent (this, UseDefaultIID());
	InterfacePtr<ITreeAttributes> iTreeAttrs ((ITreeAttributes*)iWidgetParent->QueryParentFor(IID_ITREEATTRIBUTES));
	InterfacePtr<ITreeViewController> iTVController (iTreeAttrs, UseDefaultIID());
	
	//	Get the list of currently selected node.
	//	Uncommited changes from the edit boxes get applied to this list before the node selection changes.
	//	NOTE: tried to force the keyfocus to this node so that the edit box will go through giving up focus and
	//	hopefully commit the changes. But this caused unforseen crashes when trying to process the selection rules.
	NodeIDList currentNodes;
	iTVController->GetSelectedItems(currentNodes);

	//	Process the selection but don't notify or hilite.
	//	Reselect to hilite and notify at the end when all's OK.
	NodeIDList newNodes;
	this->ProcessSelectionRulesButDontSelect (iTVController, e, ::GetUID(this), newNodes);


	bool canUpdate = true;
	WidgetID invalidWidgetID = kDefaultWidgetId;
	if (!currentNodes.empty ())
	{
		//	Apply uncomitted changes if necessary.
		//	Uncommited changes could be delay or number of group plays.
		invalidWidgetID = ddui_utils::UpdateTimingItemsIfNecessary (this, currentNodes);
		canUpdate = invalidWidgetID == kDefaultWidgetId;
	}

	if (canUpdate)
	{
		//	Select new and deselect old nodes
		NodeIDList::iterator n1 = newNodes.begin ();
		NodeIDList::iterator n0 = currentNodes.begin ();
		for (; n0 != currentNodes.end (); ++n0)
		{
			NodeIDList::iterator foundNode = std::find (newNodes.begin (), newNodes.end (), *n0);
			if (foundNode == newNodes.end ()) iTVController->Deselect (*n0, kFalse, kTrue);
		}
		for (; n1 != newNodes.end (); ++n1)
		{
			NodeIDList::iterator foundNode = std::find (currentNodes.begin (), currentNodes.end (), *n1);
			if (foundNode == currentNodes.end ()) iTVController->Select (*n1, kFalse, kTrue);
		}
		

		//	Notify once.
		InterfacePtr<ISubject> subject (iTVController, IID_ISUBJECT);
		if (newNodes != currentNodes && subject) 
		{
			subject->Change (kListSelectionChangedMessage, IID_ITREEVIEWCONTROLLER);
		}

		//	For some reasons, if we actually applied uncommitted changes from the delay edit box,
		//	we ended up with a nil parent pointer in widget parent.
		InterfacePtr<IWindow> iWindow ((IWindow*)iWidgetParent->QueryParentFor(IID_IWINDOW));
		if (iWindow != nil && this->HandleTreeNodeDragDrop(e))
			return kTrue;

	}
	
	return HandleLButtonDnAfterSelectionProcessing(e);
} 

//---------------------------------------------------------------
// TimingPanelTreeNodeEH::ButtonDblClk
//---------------------------------------------------------------
bool16 TimingPanelTreeNodeEH::ButtonDblClk(IEvent* e)
{
	//
	// Get the UID of the selected items.
	//
	InterfacePtr<ITreeNodeIDData> holderData(this, UseDefaultIID());
	NodeID nodeIDHolder = holderData->Get();	
	TreeNodePtr<TimingPanelTreeNodeID> nodeItem(nodeIDHolder);
	UID itemUID = nodeItem->GetUID();

	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection()); 

	IDataBase* db = iSelectionMgr->GetDataBase();
	UIDRef targetRef (db, itemUID);
	UIDRef pageItemRef = Utils<Facade::IDynamicTargetsFacade> ()->GetTargetPageItemRef (targetRef);
	ASSERT (pageItemRef.GetUID () != kInvalidUID);

	UIDList selectItems(pageItemRef);

	//
	// Select the item in the layout view.
	//
	if (Utils<ILayerUtils> ()->AreLayersUnlockedAndVisible (&selectItems))
	{
		InterfacePtr<ILayoutSelectionSuite> iLayoutSelectionSuite(static_cast<ILayoutSelectionSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ILAYOUTSELECTION_ISUITE, iSelectionMgr)));
		iLayoutSelectionSuite->SelectPageItems(selectItems, Selection::kReplace, Selection::kScrollIntoViewIfNecessary); 
	}

	return kTrue;
}

//_________________________________________________________________________________________ 
//	ProcessSelectionRulesButDontSelect
//
//	Note:	This basic rule is the same as ITreeViewController::ProcessSelectionRules.
//			However, we do it here so that we determined what the new nodes without
//			selecting them unless the potential edit value entered for the currently selected
//			nodes is "legal". In that case, the caller will select, hilite new nodes and
//			notify changes once.
//			If there's an error in the edit values, we put back the last good values and return
//			key focus to the edit box. The selection is not changed.
//
//	We also assumed that timing panel allows multiple selections!
//_________________________________________________________________________________________ 
void TimingPanelTreeNodeEH::ProcessSelectionRulesButDontSelect(ITreeViewController* iTVController, IEvent* event, UID nodeWidgetUID, NodeIDList& newNodes)
{
	// we currently only handle LButtonDown events for selection 
	if(event->GetType() != IEvent::kLButtonDn)
		return;     
     
	//if we don't support selection, we don't need to do anything 
	if (!iTVController->AllowsSelection ()) 
		return; 

	InterfacePtr<IControlView> nodeView( ::GetDataBase(this), nodeWidgetUID, UseDefaultIID()); 
	InterfacePtr<ITreeNodeIDData> data( nodeView, UseDefaultIID() ); 
	NodeID node = data->Get(); 
	bool16 nodeIsSelected = iTVController->IsSelected(node); 
     
	NodeIDList nodes; 
	iTVController->GetSelectedItems(nodes); 

	if (!event->CmdKeyDown() && !event->ShiftKeyDown())
	{
		//	Do nothing if this node already selected.
		if (nodeIsSelected)
			newNodes = nodes;
		else
			newNodes.push_back (node);
	}
	else
	{ 
		//Multiple Selection 
		// if it's already selected, check the Cmd/Cntl key 
		// if the Cmd/Cntl key is down, remove from selected list.
		if (nodeIsSelected && event->CmdKeyDown()) 
		{ 
			// Remove this one
			newNodes = nodes;
			NodeIDList::iterator n = std::find (newNodes.begin (), newNodes.end (), node);
			newNodes.erase (n);
			return; 
		} 
         
		//it isn't selected, but shift is being held down 
		if (event->ShiftKeyDown()) 
		{ 
			NodeID originalSelection (iTVController->GetMasterItem ()); 

			if (originalSelection.IsValid()) 
			{ 
				newNodes.push_back (originalSelection);
				if(originalSelection != node) 
				{
					NodeID firstNode = iTVController->GetMasterItem ();
					InterfacePtr<ITreeViewHierarchyAdapter>    adapter(iTVController, UseDefaultIID()); 
					int32 aboveOrBelow = CTreeViewMgr::AboveOrBelow( adapter, firstNode, node); 
                     
					//Move up or down the tree selecting nodes between the current node and the last selected node 
					InterfacePtr<ITreeViewMgr>    treeMgr(iTVController, UseDefaultIID()); 
					TreeNodeTraverser    traverse(originalSelection, treeMgr, kTrue, aboveOrBelow < 0 ? TreeNodeTraverser::eForward : TreeNodeTraverser::eReverse); 
					NodeID    next; 
					while (!traverse.Completed() && next != node) 
					{ 
						next = traverse.Next(); 
						if ( next.IsValid() ) 
							newNodes.push_back (next);
					} 
				} 
			} else // add the new node only 
				newNodes.push_back (node);
		} 
         
		//it isn't selected, but Command is being held down 
		if (event->CmdKeyDown())
		{
			newNodes = nodes;
 			newNodes.push_back (node);
		} 
	} 
}