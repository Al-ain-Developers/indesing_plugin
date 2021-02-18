//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CTreeBasedListBoxController.h $
//  
//  Owner: Tom Taylor
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
#ifndef __CTreeBasedListBoxController__
#define __CTreeBasedListBoxController__

#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.

#include "IPMUnknown.h"
#include "IListBoxController.h"
#include "NodeID.h"
#include "HelperInterface.h"
#include "IEvent.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class WIDGET_DECL CTreeBasedListBoxController : public IListBoxController
{
public:
								CTreeBasedListBoxController(IPMUnknown* boss);
	virtual						~CTreeBasedListBoxController();
								
	// ----- ListBox Use -----
	
	virtual void				SetClickItem(int32 itemNumber);
									// set the item number of the last item clicked on
	virtual int32				GetClickItem() const;
									// return the item number of the last item clicked, or -1 for no item
	virtual int32				Search(const PMString& subString) const;
									// Search first looks through all the items of the list looking for
									// an item that has a name that begins with "subString." If such an
									// item is found, the index of the item is returned. If no item is found,
									// this function then looks for an item that has a name that *contains*
									// "subString." If such an item is found, the index of the item is
									// returned. If no item is found, Search returns -1.
	virtual PMString			GetNthItemString(int32 n) const;
									// Given a list index, return the name of it. Used by Search function for typeahead.
									// By default returns empty string, so typeahead if off by default.

	virtual void				Select(int32 index, bool16 invalidate, bool16 notifyOfChange);
	virtual void				SelectAll(bool16 invalidate, bool16 notifyOfChange);
	virtual void 				Deselect(int32	index, bool16 invalidate, bool16 notifyOfChange); 
	virtual void				DeselectAll(bool16 invalidate, bool16 notifyOfChange);
	virtual bool16				IsSelected(int32 index) const;
	virtual int32				GetSelected() const;
	virtual void				GetSelected(K2Vector<int32>& multipleSelection) const;
	
	virtual void				SetMasterItem(int32 itemNumber);
	virtual int32				GetMasterItem() const;

	// ----- ListBox Use -----
	
	virtual int32				FindRowHit(const PMPoint& clickPoint);
									// Give a point, FindRowHit returns the list row under the point

	virtual eListBoxPart		ClickedWhichPart(const PMPoint& clickPoint);
			
	virtual eScrollDirection	CheckScrollDirection(eScrollDirection direction);
	virtual eScrollDirection	CheckDragScroll(const PMPoint& where);

	virtual void				GetVisibleItemBounds(int32 item, PMRect& newBounds);

	virtual void				ScrollList(const eScrollDirection direction);	
	virtual void				ScrollItemIntoView(int32 itemNumber);
	
	virtual int32				GetFirstVisibleItem() const;
	virtual int32				GetMaximumVisibleItems() const;
	virtual void				SetSelected( const K2Vector<int32>& vecIndices, bool16 bInvalidate = kTrue, bool16 bNotify = kTrue );
	virtual void				ProcessSelectionRules(IEvent* event, int32 index);


protected:
	virtual void				NotifyOfChange(bool16 invalidate, bool16 notifyOfChange, int32 changeMessage);
	virtual bool16				IsMultiselect(void);
	virtual NodeID_rv			GetNodeID(int32 index) const;
	virtual bool16				GetListBoxMetrics(
									PMRect	&bounds, 
									PMRect	&visibleRect,
									int32	&numItems,
									int32	&numVisible,
									bool16	includePartiallyVisible,
									int32	&topIndex,
									int32	&cellWidth,
									int32	&cellHeight
									) const;
private:
	int32						fClickItem;
	int32						fMasterItem;

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif

#endif