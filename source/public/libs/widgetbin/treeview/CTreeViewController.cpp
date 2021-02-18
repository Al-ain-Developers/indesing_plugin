//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/treeview/CTreeViewController.cpp $
//  
//  Owner: Matt Joss
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

#include "DV_VCWidgetHeaders.h"

#include "CTreeViewController.h"

// ----- Interface Includes -----
#include "IControlView.h"
#include "ITreeAttributes.h"
#include "ISubject.h"
#include "IPMStream.h"
#include "ITreeViewMgr.h"
#include "ITreeNodeIDData.h"
#include "IWidgetParent.h"
#include "IPanelControlData.h"
#include "ITreeViewHierarchyAdapter.h"

// ----- Implementation Includes -----

#include "widgetid.h"
#include "HelperInterface.h"
#include "k2VectorStreaming.h"
#include "CTreeViewMgr.h"
#include "TreeNodeTraverser.h"

//----------------------------------------------------------------------------------------
// CTreeViewController
//----------------------------------------------------------------------------------------
// BP 04/17/01: moved to  .../source/components/WidgetBin/WidgetBinImpl.cpp
// CREATE_PERSIST_PMINTERFACE(CTreeViewController, kCTreeViewControllerImpl)
DEFINE_HELPER_METHODS(CTreeViewController)

CTreeViewController::CTreeViewController(IPMUnknown *boss)
	: HELPER_METHODS_INIT(boss), fNumSelectableItems( eAllowSingleSelection ), fAllowDiscontiguousSelection( kFalse ), 
	fAllowMultipleParents( kFalse ), fFirstSelected(nil)
{
}

CTreeViewController::~CTreeViewController()
{
}

//----------------------------------------------------------------------------------------
// CTreeViewController::ProcessSelectionRules
//----------------------------------------------------------------------------------------
void CTreeViewController::ProcessSelectionRules(IEvent* event, UID nodeWidgetUID, bool16 notifyOfChange)
{
	// we currently only handle LButtonDown or RButtonDown events for selection
	if( (event->GetType() != IEvent::kLButtonDn) &&
		(event->GetType() != IEvent::kRButtonDn) )
		return;	
	
	//if we don't support selection, we don't need to do anything
	if (fNumSelectableItems == eAllowNoSelection)
		return;

	InterfacePtr<IControlView>	nodeView( ::GetDataBase(this), nodeWidgetUID, UseDefaultIID());
	InterfacePtr<ITreeNodeIDData>	data( nodeView, UseDefaultIID() );
	NodeID node =  data->Get();
	bool16 nodeIsSelected = IsSelected(node);
	
	NodeIDList nodes;
	GetSelectedItems(nodes);
	ASSERT_MSG( fNumSelectableItems == eAllowMultipleSelection || nodes.size() < 2, "We have a multiple selection, but we're in single selection mode");
	if (fNumSelectableItems != eAllowMultipleSelection || (!event->CmdKeyDown() && !event->ShiftKeyDown()))
	{
		//Single selection
		//if it is already selected and we want to ignore it, just do nothing
		//By default, this is already return kTrue. Currently only object style dialog 
		//return kFalse since it has to deal with enable/disable panels. See bug #1053706.
		if (nodeIsSelected && this->IgnoreIfNodeIsSelected())
			return;
		
		if (!nodes.empty())
			DeselectAll( kFalse, kTrue );
			
		Select( node, notifyOfChange );
	} else
	{
		//Multiple Selection
		//if it's already selected, check the Cmd/Cntl key
		// if the Cmd/Cntl key is down, deselect, else
		if (nodeIsSelected && event->CmdKeyDown())
		{
			Deselect( node, notifyOfChange );
			return;
		}
		
		//it isn't selected, but shift is being held down
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
	
}

//----------------------------------------------------------------------------------------
// CTreeViewController::Select
//----------------------------------------------------------------------------------------
ITreeViewController::SelectCode CTreeViewController::Select( const NodeID&	itemToSelect, bool16 notifyOfChange, bool16 changeHilite )
{
	if (this->IsSelected(itemToSelect)) // If item in question is selected, just return
		return eSuccess;

	//if we don't support selection, we don't need to do anything
	if (fNumSelectableItems == eAllowNoSelection)
		return eNoSelectionAllowed;

	InterfacePtr<ITreeAttributes> attributes(this, UseDefaultIID());
	InterfacePtr<ITreeViewHierarchyAdapter>	adapter(this, UseDefaultIID());
	if ( adapter->GetRootNode() == itemToSelect && attributes->IsRootNodeDisplayed() == kFalse)
		return eCantSelectHiddenRootNode;
	
	NodeIDList nodes;
	GetSelectedItems(nodes);
	if (fNumSelectableItems != eAllowMultipleSelection && !nodes.empty())
		return eSingleItemAlreadySelected;
	
	//Are we limited to selecting things with the same parent?  if so, check existing selection for a parent match
	//We should only have to match the parent with 1 in the list, since they should all be the same
	if (!fAllowMultipleParents && !nodes.empty())
	{
		if ( adapter->GetParentNode( itemToSelect ) !=  adapter->GetParentNode( nodes[0] ) )
			return eSingleParentOnly;		
	}

	if (!fAllowDiscontiguousSelection && !nodes.empty())
	{
		int32 aboveOrBelow = CTreeViewMgr::AboveOrBelow( adapter, fFirstSelected, itemToSelect );
		
		//Move up or down the tree selecting nodes between the current node and the last selected node
		InterfacePtr<ITreeViewMgr>	treeMgr(this, UseDefaultIID());
		TreeNodeTraverser	traverse(fFirstSelected, treeMgr, kTrue, aboveOrBelow < 0 ? TreeNodeTraverser::eForward : TreeNodeTraverser::eReverse);
		NodeID	next = traverse.Next();
		while (!traverse.Completed() && next != itemToSelect)
		{
			if ( !next.IsValid() || this->IsSelected( next ) == kFalse)
				return eDiscontiguousNotAllowed;
			next = traverse.Next();			
		}
	}
	
	UpdateSelection(itemToSelect, kTrue);
	
	//Change the hilite if needed
	if (changeHilite)
		ChangeHilite( itemToSelect, kTrue );		
	
	//Tell the world about it
	NotifyOfChange( notifyOfChange, kListSelectionChangedMessage );
	
	return eSuccess;
}

//----------------------------------------------------------------------------------------
// CTreeViewController::Deselect
//----------------------------------------------------------------------------------------
void CTreeViewController::Deselect( const NodeID&	itemToDeselect, bool16 notifyOfChange, bool16 changeHilite )
{
	if (!this->IsSelected(itemToDeselect)) // If item in question is not selected, just return
		return;

	UpdateSelection(itemToDeselect, kFalse);
	
	//Change the hilite if needed
	if (changeHilite)
		ChangeHilite( itemToDeselect, kFalse );
		
	//Tell the world about it
	NotifyOfChange( notifyOfChange, kListSelectionChangedMessage);
}

//----------------------------------------------------------------------------------------
// CTreeViewController::DeselectAll
//----------------------------------------------------------------------------------------
void CTreeViewController::DeselectAll( bool16 notifyOfChange, bool16 changeHilite )
{
	ClearSelection(notifyOfChange);
	
	//Change the hilite if needed, passing in a non-valid NodeID will cause all items to be unhilited
	if (changeHilite)
		ChangeHilite( NodeID(nil), kFalse );
		
	NotifyOfChange( notifyOfChange, kListSelectionChangedMessage);
}

//----------------------------------------------------------------------------------------
// CTreeViewController::IsSelected
//----------------------------------------------------------------------------------------
bool16 CTreeViewController::IsSelected(const NodeID&	item ) const
{
	if (FindLocationInSorted(fSelectedNodes, item ) < 0)
		return kFalse;
	
	return kTrue;
}

//----------------------------------------------------------------------------------------
// CTreeViewController::GetSelectedItemsDisplayOrder
//----------------------------------------------------------------------------------------
void CTreeViewController::GetSelectedItemsDisplayOrder( NodeIDList&  selectedItems) const
{
	InterfacePtr<ITreeViewHierarchyAdapter>	adapter(this, UseDefaultIID());
	InterfacePtr<ITreeViewMgr>	treeMgr(this, UseDefaultIID());
	TreeNodeTraverser	traverse(adapter->GetRootNode(), treeMgr, kTrue, TreeNodeTraverser::eForward);

	selectedItems.clear();

	NodeID	next;
	while (!traverse.Completed())
	{
		next = traverse.Next();
		if ( next.IsValid() && IsSelected(next) )
		{
			selectedItems.push_back(next);
		}
	}

	// make sure we have the right number of selected nodes.
	ASSERT(selectedItems.size() == fSelectedNodes.size());
}

//----------------------------------------------------------------------------------------
// CTreeViewController::GetSelectedItems
//----------------------------------------------------------------------------------------
void CTreeViewController::GetSelectedItems( NodeIDList&  selectedItems) const
{
	selectedItems = fSelectedNodes;
}

//----------------------------------------------------------------------------------------
// CTreeViewController::NotifyOfChange
//----------------------------------------------------------------------------------------
void CTreeViewController::NotifyOfChange(bool16 notifyOfChange, int32 changeMessage)
{
	if (notifyOfChange) 
	{
		InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
		if( subject ) 
		{
			subject->Change(changeMessage, IID_ITREEVIEWCONTROLLER);
		}
	}
}

//----------------------------------------------------------------------------------------
// CTreeViewController::ChangeHilite
// Passing in 'nodeToHilite' that is invalid will cause all items to be hilited according to 'hilite'
//----------------------------------------------------------------------------------------
void CTreeViewController::ChangeHilite( const NodeID& nodeToHilite, bool16 hilite )
{
	if (nodeToHilite.IsValid())
	{
		InterfacePtr<ITreeViewMgr>	treeMgr(this, UseDefaultIID());
		InterfacePtr<IControlView>	view( treeMgr->QueryWidgetFromNode(nodeToHilite) );
		if (view)
		{
			if (view->IsHilited() != hilite)
			{
				view->Hilite( hilite );
				view->Invalidate();
			}
		}
	} else
	{	
		//The only way to do this is to go thru the widgets in the PanelControlData looking for this widget and changing the hilite
		InterfacePtr<IPanelControlData>	myWidgets(this, UseDefaultIID());
		InterfacePtr<IPanelControlData>	scrollersWidgets( myWidgets->FindWidget(kTreeScrollerWidgetID), UseDefaultIID());
		ASSERT_MSG(scrollersWidgets != nil, "Could not find Scroller widget in TreeViewWidget!");
		if (scrollersWidgets)
		{
			for (int32 i = 0; i < scrollersWidgets->Length(); i++)
			{
				if ( scrollersWidgets->GetWidget( i )->IsHilited( ) != hilite )
				{
					scrollersWidgets->GetWidget( i )->Hilite( hilite );
					scrollersWidgets->GetWidget( i )->Invalidate();
				}
			}
			
		}
	}
}

//----------------------------------------------------------------------------------------
// CTreeViewController::ReadWrite 
//----------------------------------------------------------------------------------------
void CTreeViewController::ReadWrite(IPMStream *s, ImplementationID prop)
{
	s->XferInt16(fNumSelectableItems);
	s->XferBool(fAllowMultipleParents);
	s->XferBool(fAllowDiscontiguousSelection);
	
	if (s->IsReading())
	{
		InterfacePtr<ITreeViewHierarchyAdapter>	adapter( this, UseDefaultIID());
		NodeID genericID = adapter->GetGenericNodeID();	
		NodeID::SetNodeIDTemplate( genericID );
	}
	
	// Read/Write the Selection table
	K2ReadWrite(s, fSelectedNodes);		

	NodeID::ClearNodeIDTemplate();

}

//----------------------------------------------------------------------------------------
// CTreeViewController::UpdateSelection 
//----------------------------------------------------------------------------------------
void CTreeViewController::UpdateSelection(const NodeID& itemToSelect, bool16 select)
{
	if(select)	//	Add this node to the selection
	{	
		if (fSelectedNodes.empty())
			fFirstSelected = itemToSelect;
		
		//Now, add it to the selection
		if (FindLocationInSorted(fSelectedNodes, itemToSelect) < 0)
		{
			PreDirty ();
			InsertInSorted(fSelectedNodes, itemToSelect);
			
		}
	}
	else	//	Remove this node from the selection
	{
		int32 loc = FindLocationInSorted(fSelectedNodes, itemToSelect);
		if (loc >= 0)
		{
			PreDirty ();
			fSelectedNodes.erase(fSelectedNodes.begin() + loc);
		}
		
		if (fFirstSelected == itemToSelect)
		{
			fFirstSelected.MakeInvalid();
			if(fSelectedNodes.size() == 1)
				fFirstSelected = fSelectedNodes[0];
		}
	}
}

//----------------------------------------------------------------------------------------
// CTreeViewController::ClearSelection 
//----------------------------------------------------------------------------------------
void CTreeViewController::ClearSelection(bool8 notifyOfSelectionChange)
{
	if (fSelectedNodes.empty()) // Check to see if nothing is selected
		return;

	PreDirty();
	fFirstSelected.MakeInvalid();
	if (fSelectedNodes.empty())
		return;
		
	fSelectedNodes.clear();
}

//----------------------------------------------------------------------------------------
// CTreeViewController::AllowsSelection 
//----------------------------------------------------------------------------------------
bool16 	CTreeViewController::AllowsSelection( ) const
{
	return fNumSelectableItems != eAllowNoSelection;
}
