//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGridListController.h $
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
#ifndef __IGridListController__
#define __IGridListController__

#include "IPMUnknown.h"
#include "IControlView.h"

// Some List Constants

const int16 kGridListTopAutoScrollSlop	= 4;	// area below top of list that we autoscroll the list in while dragging

class IGridListController : public IPMUnknown
{
public:
	// ----- Item selection -----

	
	virtual void				SetClickItem(int32 itemNumber) = 0;
									// Set the item number of the last item clicked on
									
	virtual int32				GetClickItem() const = 0;
									// Return the item number of the last item clicked, or -1 for no item
							
	virtual int32				FindItemHit(const PMPoint& clickPoint, bool16& hitOnLeft) = 0;
									// Given a point, FindItemHit returns the item index under the point,
									// Also hitOnLeft returns kTrue if hit on left side.
									// Otherwise if hit on right, it returns kFalse.
									
	virtual void				ScrollItemIntoView(int32 itemNumber) = 0;
									// automatically scroll the list so that item "itemNumber" is visible
									
	virtual int32				GetFirstVisibleItem() const = 0;
									// returns the zero based index of the first visible item at the top of the list box
									
	virtual int32				GetMaximumVisibleItems() const = 0;
									// returns the numbers of "slots" completely visible in the list box
	
	virtual int32 				FindFirstContinousSelectionBlock(int32& firstIndex) = 0;
									// Find the first contiguous selection block. firstIndex returns the first
									// index in the selection block. The method returns the last index in this
									// selection block. If only one item is selected, then last index == firstIndex.
	
	virtual int32				Search(const PMString& subString) const = 0;
									// Search first looks through all the items of the list looking for
									// an item that has a name that begins with "subString." If such an
									// item is found, the index of the item is returned. If no item is found,
									// this function then looks for an item that has a name that *contains*
									// "subString." If such an item is found, the index of the item is
									// returned. If no item is found, Search returns -1. Typically, subclassers
									// much override this function because only they know how to interpret
									// their list control data or widget hierarchy stored in the list. By
									// default, this function always returns -1.

	virtual PMString			GetNthItemString(int32 n) const = 0;


};

#endif
