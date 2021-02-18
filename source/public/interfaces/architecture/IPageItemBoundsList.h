//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPageItemBoundsList.h $
//  
//  Owner: jargast
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
#ifndef __IPageItemBoundsList__
#define __IPageItemBoundsList__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "PMRect.h"
#include "UIDList.h"
#include "IHierarchy.h"

// Return kTrue to abort the operation, kFalse to continue..
typedef bool8 (*PageItemIntersectCallback)(const UIDRef& uidRef, void *data);

/** This interface stores the bounds of children in the same order as IHierarchy stores
the UIDs of children
*/
class IPageItemBoundsList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMBOUNDSLIST };

	/**	Add the page item to the bounds list.
	@param *iUnknown - The page item to add (specifically needs an ISpread interface)
	@param at - The location (-1 Adds it at the end)
	*/
	virtual void Add (IPMUnknown* iUnknown, int32 at) = 0;
	
	/**	Move the item in the z-order
	@param *iUnknown - The page item to move (specifically needs an ISpread interface)
	@param from - The location to move the item from
	@param to - The location to move the item to (-1 moves it to the end)
	*/
	virtual void Move (IPMUnknown* iUnknown, int32 from, int32 to) = 0;
	
	/**	Remove the page item to the bounds list.
	@param *iUnknown - The page item to remove (specifically needs an ISpread interface)
	@param at - The location of the item to remove (-1 removes it from the end)
	*/
	virtual void Remove (IPMUnknown* iUnknown, int32 at) = 0;
	
	/**	Tell the bounds list that a page item's bounds have changed.
	@param *iUnknown - The page item that has changed (specifically needs an ISpread interface)
	@return kTrue if the item had valid state
	*/
	virtual bool16 Invalidate (IPMUnknown* iUnknown) = 0;
	
	/**	Tell the bounds list that all the items have changed.
	@return kTrue if any of the items had valid state
	*/
	virtual bool16 InvalidateAll () = 0;
	
	/**	Return the number of page items
	@return int32 - The number of items in the list
	*/
	virtual int32 Length() const = 0;
	
	/**	Return the bounds for the nth page item
	@param n - The item whose bounds you want
	@return PMRect - The bounds of the object in the coordinate system of the boss holding this implementation.  Currently that means layer or group coordinates. 
	*/
	virtual PMRect GetNthBounds (int32 n) const = 0;
	
	/**	Returns a list of page items whose bounds intersect with the 
	passed in rectangle.
	@param &rect - The bounds you want to test for intersection with in inner coordinates of the boss holding this implementation.  Currently that means layer or group coordinates.
	@param uidBelowThis - Optional UID of the page item that returned items must be below in the z-order
	@return UIDList - A list of page items that intersect with the PMRect
	*/
	virtual UIDList GetIntersectingItems (const PMRect& rect, UID uidBelowThis = kInvalidUID) const = 0;

	/**	Finds all page items whose bounds intersect with the 
	 passed in rectangle and passes it and the void *data to callback.
	@param &rect - The bounds you want to test for intersection with in inner coordinates of the boss holding this implementation.  Currently that means layer or group coordinates.
	@param callback - The callback method to use (If this method returns kTrue operation will be aborted.
	@param *data - Additional data to pass to the callback
	*/
	virtual void GetIntersectingItems (const PMRect& rect, PageItemIntersectCallback callback, void *data) const = 0;
	
	
	
#if 0
	class iterator
	{
		friend class PageItemBoundsList;
		public:
			bool16 operator==(const iterator& rhs) const { return n == rhs.n;}
			bool16 operator!=(const iterator& rhs) const { return !(*this == rhs);}
				

		private:
			UIDRef operator*() const;
			iterator& operator++();
			InterfacePtr<const IHierarchy> h;
			PageItemBoundsList* p;
			int32 n, length;
			PMRect r;
			
			iterator();
			iterator( PageItemBoundsList* p, const PMRect& r, int32 n, int32 l);
	};

	virtual iterator begin( const PMRect& rect) = 0;
	virtual iterator end( const PMRect& rect) = 0;
//	virtual UIDRef next( iterator& i) = 0;
#endif
};


#endif
