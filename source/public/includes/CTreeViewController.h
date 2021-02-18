//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTreeViewController.h $
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

#pragma once
#ifndef __CTreeViewController__
#define __CTreeViewController__

#include "ITreeViewController.h"
#include "HelperInterface.h"
#include "K2Vector.h"
#include "PMPoint.h"
#include "CTreeViewMgr.h"
#include "NodeID.h"

//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------
#pragma export on

//----------------------------------------------------------------------------------------
// Class CTreeViewController
//----------------------------------------------------------------------------------------
class DV_WIDGET_DECL CTreeViewController : public ITreeViewController
{
public:
	CTreeViewController(IPMUnknown *boss);
	~CTreeViewController();

    enum { eAllowNoSelection = 0, eAllowSingleSelection = 1, eAllowMultipleSelection  };

	// ----- Item selection -----
	virtual void				ProcessSelectionRules(IEvent* event, UID node,bool16 notifyOfChange);
									// Handles a click on the given node to determine how it affects the selection

	virtual void				DeselectAll( bool16 notifyOfChange = kTrue, bool16 changeHilite = kTrue );
									// Deselect all elements.

	virtual	SelectCode			Select( const NodeID&	node, bool16 notifyOfChange = kTrue, bool16 changeHilite = kTrue );
									// Select the element at the given position in the list.
	virtual void 				Deselect( const NodeID&	node, bool16 notifyOfChange = kTrue, bool16 changeHilite = kTrue );
									// Deselect the element at the given position in the list.

	virtual bool16 				AllowsSelection( ) const;
									// returns kTrue if this tree allows nodes to be selected
									// returns kFalse if no nodes are selectable

	virtual NodeID				GetMasterItem() const { return fFirstSelected; }

			void 				ReadWrite(IPMStream *s, ImplementationID prop);
protected:
	virtual	void				NotifyOfChange(bool16 notifyOfChange, int32 changeMessage);
	virtual	void				ChangeHilite( const NodeID& nodeToHilite, bool16 hilite );
	


	//	Override these functions if you hold the selection in something other than 
	//	fSelectedNodes and fFirstSelected.  XMLStructureTVController is an example of this.
	
	//							This will add or remove the given node from the selection
	virtual void 				UpdateSelection(const NodeID&, bool16 select);
	
	//							This will deselect all
	virtual void				ClearSelection(bool8 notifyOfSelectionChange = true);
	virtual bool16				IsSelected( const NodeID&	item ) const;
									// Return true if the item with index is selected.
									// selectedItems is sorted
	virtual	void				GetSelectedItems( NodeIDList&  selectedItems) const;

	virtual	void				GetSelectedItemsDisplayOrder( NodeIDList&  selectedItems) const;

	virtual bool16              IgnoreIfNodeIsSelected() const { return kTrue; }

	
protected:	
	NodeIDList			fSelectedNodes;			// sorted list by NodeID
	NodeID							fFirstSelected;
	int16							fNumSelectableItems;
	bool16							fAllowMultipleParents;
	bool16							fAllowDiscontiguousSelection;

DECLARE_HELPER_METHODS()

};
#pragma export off

#endif //__CTreeViewController__
