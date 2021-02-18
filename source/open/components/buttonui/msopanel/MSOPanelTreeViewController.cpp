//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelTreeViewController.cpp $
//  
//  Owner: SusanCL
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

#include "IControlView.h"
#include "ITreeViewMgr.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewHierarchyAdapter.h"

// ----- Includes -----

#include "CActionComponent.h"
#include "CTreeViewController.h"
#include "K2Vector.tpp"
#include "TreeNodeTraverser.h"
#include "TreeViewEventHandler.h"

// ----- Utility files -----

#include "EventUtilities.h"
#include "IPalettePanelUtils.h"
#include "UserInterfaceUtils.h"

// ----- ID.h files -----

#include "widgetid.h"
#include "FormFieldUIID.h"


class MSOPanelTreeViewController : public CTreeViewController
{
public:
    MSOPanelTreeViewController(IPMUnknown *boss) : CTreeViewController(boss) {}
	virtual ~MSOPanelTreeViewController() {}

	virtual void ProcessSelectionRules(IEvent* event, UID nodeWidgetUID, bool16 notifyOfChange);
	virtual void DeselectAll(bool16 notifyOfChange = kTrue, bool16 changeHilite = kTrue);
};

// =============================================================================
// *** MSOPanelTreeViewController impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE (MSOPanelTreeViewController, kMSOPanelTreeViewControllerImpl)

// -----------------------------------------------------------------------------
//	Note: This is basically the same as the CTreeViewController, except that it ensure
//	at least one is selected at all time.

void MSOPanelTreeViewController::ProcessSelectionRules(IEvent* event, UID nodeWidgetUID, bool16 notifyOfChange)
{
	// we currently only handle LButtonDown or RButtonDown events for selection
	if( (event->GetType() != IEvent::kLButtonDn) &&
		(event->GetType() != IEvent::kRButtonDn) )
		return;	
	
	//if we don't support selection, we don't need to do anything
	if (fNumSelectableItems == eAllowNoSelection)
		return;

	InterfacePtr<IControlView>		nodeView (::GetDataBase(this), nodeWidgetUID, UseDefaultIID());
	InterfacePtr<ITreeNodeIDData>	data( nodeView, UseDefaultIID() );
	NodeID node =  data->Get();
	bool16 nodeIsSelected = IsSelected(node);
	
	NodeIDList nodes;
	GetSelectedItems (nodes);
	ASSERT_MSG( fNumSelectableItems == eAllowMultipleSelection || nodes.size() < 2, "We have a multiple selection, but we're in single selection mode");
	if (fNumSelectableItems != eAllowMultipleSelection || (!event->CmdKeyDown() && !event->ShiftKeyDown()))
	{
		//Single selection
		//if it is already selected and we want to ignore it, just do nothing
		//By default, this is already return kTrue. Currently only object style dialog 
		//return kFalse since it has to deal with enable/disable panels. See bug #1053706.
		//If this node is disable, do nothing, i.e. don't allow DeselectAll to happen.
		if (nodeIsSelected && this->IgnoreIfNodeIsSelected())
			return;
		
		//	If node clicked is disabled, don't deselect all.
		//	NOTE that this is different from the base class.
		InterfacePtr<ITreeViewMgr>	iTreeMgr (this, UseDefaultIID ());
		InterfacePtr<IControlView>	iNodeView (iTreeMgr->QueryWidgetFromNode (node));
		if (iNodeView->IsEnabled ())
		{
			if (!nodes.empty())
				DeselectAll( kFalse, kTrue );
				
			Select( node, notifyOfChange );
		}
	}
	else
	{
		//	Multiple Selection
		//	if it's already selected, check the Cmd/Cntl key
		//	if the Cmd/Cntl key is down, deselect, else
		//	if only one is currently selected, don't deselect.
		//	NOTE that this is different from the base class.
		if (nodeIsSelected && event->CmdKeyDown())
		{
			if (nodes.size () > 1) Deselect( node, kTrue );
			return;
		}
		
		//	it isn't selected, but shift is being held down
		if (event->ShiftKeyDown())
		{
			NodeID originalSelection( fFirstSelected );
			DeselectAll( notifyOfChange, kTrue );

			if (originalSelection.IsValid())
			{
				Select( originalSelection, notifyOfChange );
				if(originalSelection != node)
				{
					InterfacePtr<ITreeViewHierarchyAdapter>	adapter(this, UseDefaultIID());
					int32 aboveOrBelow = CTreeViewMgr::AboveOrBelow( adapter, fFirstSelected, node );
					
					//Move up or down the tree selecting nodes between the current node and the last selected node
					InterfacePtr<ITreeViewMgr>	treeMgr(this, UseDefaultIID());
					TreeNodeTraverser	traverse(originalSelection, treeMgr, kTrue, aboveOrBelow < 0 ? TreeNodeTraverser::eForward : TreeNodeTraverser::eReverse);
					NodeID	next;
					while (!traverse.Completed() && next != node)
					{
						next = traverse.Next();
						if ( next.IsValid() )
							Select( next, notifyOfChange );
					}
				}
			} else //Select the new node only
				Select( node, notifyOfChange );
			
		}
		
		//it isn't selected, but Command is being held down
		if (event->CmdKeyDown())		
			Select( node, notifyOfChange );
		
	}
} // end ProcessSelectionRules()

void MSOPanelTreeViewController::DeselectAll(bool16 notifyOfChange, bool16 changeHilite)
{
	NodeIDList nodes;
	GetSelectedItems (nodes);

	if (!nodes.empty())
	{
		// Mark the selected nodes changed before deselect so the node gets updated.
		// In particular the state selection icon (if visible) needs to hide.
		InterfacePtr<ITreeViewMgr>	iTreeMgr (this, UseDefaultIID ());
		for (int32 i = 0; i < nodes.size(); ++i)
			iTreeMgr->NodeChanged(nodes[i]);
	}

	CTreeViewController::DeselectAll(notifyOfChange, changeHilite);
}
