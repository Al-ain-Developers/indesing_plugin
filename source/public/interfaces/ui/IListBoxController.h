//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IListBoxController.h $
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
#ifndef __IListBoxController__
#define __IListBoxController__


// WARNING: listboxes are DEPRECATED and will disappear from a future version of InDesign. Please use TreeViews instead.

#include "IPMUnknown.h"
#include "IControlView.h"
#include "widgetid.h"
#include "IEvent.h"

// Some List Constants

const int16 kTopAutoScrollSlop	= 4;	// area below top of list that we autoscroll the list in while dragging
const int16 kScrollBarWidth		= 15;

/** Interface to access/set list-box selection and other state. There may be cases where
	you want to override this to provide a custom search; see the Search() method on this interface for
	more detail.
*/
class IListBoxController : public IPMUnknown
{
public:
	enum { kNoSelection = -1 };
	enum { kDefaultIID = IID_ILISTBOXCONTROLLER };
	
	/**@name Item selection */
	//@{

	/** Select the element at the given position in the list.
		@param index specifies position of item to select
		@param invalidate whether control should be invalidated
		@param notifyOfChange specify whether registered observers should be notified of this change
	*/
	virtual void				Select(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
									 
	/** Select all elements of the list.
		@param invalidate whether control should be invalidated
		@param notifyOfChange specify whether registered observers should be notified of this change
	*/
	virtual void				SelectAll(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
									 
	/** Deselect the element at the given position in the list.
		@param index position of item to unselect
		@param invalidate whether control should be invalidated
		@param notifyOfChange specify whether registered observers should be notified of this change
	*/
	virtual void 				Deselect(int32 index = -1, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
									 
	/** Deselect all elements.
		@param invalidate whether control should be invalidated
		@param notifyOfChange specify whether registered observers should be notified of this change
	*/
	virtual void				DeselectAll(bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;
									 
	/** Return true if the item with index is selected.
		@return kTrue if item at given position is selected, kFalse otherwise
	*/
	virtual bool16				IsSelected(int32 index) const = 0;
									 
	/** Get index of the currently selected element.
		@return index of currently selected element
	*/
	virtual int32				GetSelected() const = 0;
									 
	/** Fills in collection with indexes of selected elements.
		The elements are in the order the user selected the items.
		@param multipleSelection OUT parameter, holds indices of selected elements
	*/
	virtual void				GetSelected(K2Vector<int32>& multipleSelection) const = 0;
								 
	/** Item can never be deselected, -1 for no item
		@param itemNumber specifies an item that is always to be selected
	*/
	virtual void				SetMasterItem(int32 itemNumber) = 0;
									 
	/** Determine the index of master item in the listbox, if it exists
		@return index of master item or -1 if there's no master item	
	*/
	virtual int32				GetMasterItem() const = 0;
	//@}								

	/**@name ListBox Use */
	//@{

	/** Set the item number of the last item clicked on
	*/
	virtual void				SetClickItem(int32 itemNumber) = 0;
								 
									
	/** Return the item number of the last item clicked, or -1 for no item
	*/
	virtual int32				GetClickItem() const = 0;
									 
							
	/** Given a point, FindRowHit returns the list row under the point
	*/
	virtual int32				FindRowHit(const PMPoint& clickPoint) = 0;
									
	/** Identify part of list box clicked */
	enum eListBoxPart {
		/** no part of the list was clicked */ 
		kInNothing = 0,				
		/** the scrollbar was clicked */ 
		kInScrollbar,				 
		/** a listitem was clicked */ 
		kInList,					
		/** the user clicked in the empty area in the list but below any list items */ 
		kInListBelowItems,			
		/** the user clicked in a small area at the top of the list (part of the first visible item) */
		kInTopAutoScrollArea		
	};
	
	/** Given a point, ClickedWhichPart will tell you what part of the list
		was clicked on.
	*/
	virtual eListBoxPart		ClickedWhichPart(const PMPoint& clickPoint) = 0;
									 
	/** Identify scrolling state */
	enum eScrollDirection {
		/** */ kNoScroll = 0,
		/** */ kScrollUp,
		/** */ kScrollUpSlow,
		/** */ kScrollDown,
		/** */ kScrollDownSlow,
		/** */ kScrollLeft,
		/** */ kScrollLeftSlow,
		/** */ kScrollRight,
		/** */ kScrollRightSlow,
		/** */ kInsideDoNothing
	};
	
	/** depending upon "direction", the list is scrolled one way or the other
	*/
	virtual void				ScrollList(const eScrollDirection direction) = 0;
									
	
	/** automatically scroll the list so that item "itemNumber" is visible
	*/
	virtual void				ScrollItemIntoView(int32 itemNumber) = 0;
									
									
	/**  returns the zero based index of the first visible item at the top of the list box
	*/
	virtual int32				GetFirstVisibleItem() const = 0;
									
									
	/** returns the numbers of "slots" completely visible in the list box
	*/
	virtual int32				GetMaximumVisibleItems() const = 0;
									
	
	/** Used when a listbox has focus and user types:
		Search first looks through all the items of the list looking for
		an item that has a name that begins with "subString." 
		
		If such an
		item is found, the index of the item is returned. If no item is found,
		this function then looks for an item that has a name that *contains*
		"subString." If such an item is found, the index of the item is
		returned. If no item is found, Search returns -1. 
		
		Typically, subclassers
		will override GetNthItemString because only they know how to interpret
		their list control data or widget hierarchy stored in the list. But
		Search can also be overridden if default search algorithm described
		above doesn't meet your needs. 
		
		By default, this function always returns -1
		unless the GetNthItemString function is provided.
	*/
	virtual int32				Search(const PMString& subString) const = 0;
									

	/** Given a list index, return the name of it. Used by Search() function for typeahead.
		By default returns empty string, so typeahead if off by default.
	*/
	virtual PMString			GetNthItemString(int32 n) const = 0;
	

	// These function are typically for internal use
	/** Internal use.
	*/
	virtual void				GetVisibleItemBounds(int32 item, PMRect& newBounds) = 0;

	/** Internal use.
	*/
	virtual eScrollDirection	CheckScrollDirection(eScrollDirection direction) = 0;

	/** Internal use.
	*/
	virtual eScrollDirection	CheckDragScroll(const PMPoint& where) = 0;
	
	/**
	 * Select the set of indices in the specified vector.  Generally faster than writing the
	 * loop yourself for reasonably large selections (>25).
	 */

	virtual void SetSelected( const K2Vector<int32>& vecIndices, bool16 bInvalidate = kTrue, bool16 bNotify = kTrue) = 0;

	/**
	 * Let the underlying tree control process the selection rules for a mouse event. This is only supported in
	 * list controls that are based on the tree control.
	 */
	virtual void ProcessSelectionRules(IEvent* event, int32 index) = 0;
	
	//@}


};

#endif
