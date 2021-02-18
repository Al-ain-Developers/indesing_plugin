//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ListLazyNotificationData.tpp $
//  
//  Owner: Ryan Gano
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

#ifndef __ListLazyNotificationDataTPP__
#define __ListLazyNotificationDataTPP__


#include "ListLazyNotificationData.h"
#include <vector>
#include <algorithm>
#include <iterator>

template <class ItemType>
void ListLazyNotificationData<ItemType>::Add (const LazyNotificationData*  other)
{
	ASSERT(other);

	// now I can copy the data from the other cookie into this one
	// only copy the data if this object is not marked for a full
	// rebuild.
	if (other && !fRebuildWholeList)
	{
		const ListLazyNotificationData *realOther = static_cast<const ListLazyNotificationData *>(other);

		// If the other cookie is marked for a full rebuild
		// we should use that setting for ourselves as well
		if (realOther->fRebuildWholeList || fItemList.size() + realOther->fItemList.size() > kMaxSize)
		{
			fItemList.clear();
			fRebuildWholeList = true;
			return;
		}

		// These optimizations allows us to not have to walk
		// through the two lists if one of them is empty
		// If the incoming list is empty we are done. If the
		// existing list is empty we just need to copy the
		// incoming list over it and no further changes need
		// to be made. - Ryan Gano
		if (realOther->fItemList.empty())
			return;
			
		if (fItemList.empty())
		{
			fItemList = realOther->fItemList;
			return;
		}
		
		// We repopulate fItemList from scratch.
		// We first save a copy of fItemList and then clear fItemList.
		// Because fItemList is an std::vector,
		// duplicating fItemList would require less copying
		// than operating the changes directly on fItemList, as long as
		// list has more than one item.

		ItemTypeVector newList;
		newList.reserve (fItemList.size() + realOther->fItemList.size());
		
		// Now walk originalThisList and realOther->fItemList together, in order, and populate
		// fItemList.
		typename ItemTypeVector::const_iterator toAddListIter = realOther->fItemList.begin(),
									thisListIter = fItemList.begin();
		while(toAddListIter != realOther->fItemList.end()
			&& thisListIter != fItemList.end())
		{
			if (*toAddListIter < *thisListIter)
			{
				InsertKeyValue(newList,toAddListIter->Key(), toAddListIter->Value() );
				++toAddListIter;
			}
			else if (*toAddListIter > *thisListIter)
			{
				InsertKeyValue(newList, thisListIter->Key(), thisListIter->Value());
				++thisListIter;
			}
			else
			{
				if 	(thisListIter->Value() == toAddListIter->Value())
					InsertKeyValue(newList, thisListIter->Key(), thisListIter->Value());
				else
				{
					switch(thisListIter->Value())
					{
						case kAdded:
							if (toAddListIter->Value() != kDeleted)
								InsertKeyValue(newList, thisListIter->Key(), thisListIter->Value());
							break;
						case kDeleted:

							if (toAddListIter->Value() == kAdded)
								InsertKeyValue(newList, thisListIter->Key(), kChanged);
							else
							{
								ASSERT_FAIL("This item has already been deleted. You cannot change it.");
								InsertKeyValue(newList, thisListIter->Key(), thisListIter->Value());
							}
							break;
						case kChanged:
								if (toAddListIter->Value() == kAdded)
								{
									InsertKeyValue(newList, thisListIter->Key(), thisListIter->Value());
								}
								else
									InsertKeyValue(newList, toAddListIter->Key(), toAddListIter->Value());
							break;
					}
				}
				++thisListIter;
				++toAddListIter;
			}
		}

		ASSERT(thisListIter == fItemList.end() ||
				toAddListIter == realOther->fItemList.end());

		while( thisListIter != fItemList.end())
		{
			InsertKeyValue(newList, thisListIter->Key(), thisListIter->Value());
			++thisListIter;
		}
		while (toAddListIter != realOther->fItemList.end())
		{
			InsertKeyValue(newList,toAddListIter->Key(), toAddListIter->Value());
			++toAddListIter;
		}
		
		fItemList.swap (newList);
	}
}

template <class ItemType>
LazyNotificationData*  ListLazyNotificationData<ItemType>::Clone (bool16 undoData) const
{
	// NOTE: This method must return a new list.
	// First, because of the requirement that this method return a new
	// list it will make a copy of the internal list to be returned.
	// The calling method will own this new list because it does us no
	// good to store it.
	// if undoData is true we need to reverse the meaning of the Added and 
	// Removed List. That means that all it really needs to do is walk
	// the vector and if the value of an item is kAdded change it to
	// kDeleted. The inverse is also true. If it starts as kDeleted we
	// change it to kAdded. kChanged or kDestroyed do not matter for this
	// method.
	ListLazyNotificationData *listUndoList = new ListLazyNotificationData<ItemType>;
	
	listUndoList->fItemList = this->fItemList;
	listUndoList->fRebuildWholeList = this->fRebuildWholeList;

	ASSERT(!listUndoList->fRebuildWholeList || (listUndoList->fRebuildWholeList && (listUndoList->fItemList.begin() == listUndoList->fItemList.end())));

	// Only switch the added and deleted flags if the client wants the undo information.
	if (undoData == kTrue)
	{
		typename ItemTypeVector::iterator iter;
		for (iter = listUndoList->fItemList.begin(); iter != listUndoList->fItemList.end(); ++iter)
		{
			switch (iter->Value())
			{
			case kAdded:
				iter->Value() = kDeleted;
				break;
			case kDeleted:
				iter->Value() = kAdded;
				break;
			case kChanged:
				break; // nothing to do
			}
		}
	}
	return listUndoList;
}

template <class ItemType>
void ListLazyNotificationData<ItemType>::MarkShouldRebuildAll ()
{
	fItemList.clear();
	fRebuildWholeList = true;
}

template <class ItemType>
void ListLazyNotificationData<ItemType>::ItemAdded(ItemType itemID)
{
	if (fRebuildWholeList)
		return;

	if (fItemList.size() >= kMaxSize)
	{
		this->MarkShouldRebuildAll();
		return;
	}
	
	// If the item doesn't exist in the list already we can simply add it.
	// If the item exists we need change the kItemState to match the true 
	// state of the object. The rules are:
	// Old State	: New State	: Reason
	// kAdded		: No-op		: We shouldn't be adding items that are already there
	// kDeleted		: kChanged	: In essence the item was not deleted and added but simply changed
	// kChanged		: Assert	: We shouldn't be adding items that are already there
	
	// find the original item if it exists
	typename ItemTypeVector::iterator pos(std::lower_bound(fItemList.begin(), fItemList.end(), itemID));

	// change to correct value
	if (pos != fItemList.end() && pos->Key() == itemID)
	{
		switch(pos->Value())
		{
		case kAdded:
			break;
		case kDeleted:
			pos->Value() = kChanged;
			break;
		case kChanged:
			ASSERT_FAIL("ListLazyNotificationData::ItemAdded - This item has already been marked for change. You cannot add it.");
			break;
		}

		return;
	}

	// or add the item the list
	fItemList.insert(pos, StoredItemData(itemID, kAdded));
}

template <class ItemType>
void ListLazyNotificationData<ItemType>::ItemDeleted(ItemType itemID)
{
	if (fRebuildWholeList)
		return;

	if (fItemList.size() >= kMaxSize)
	{
		this->MarkShouldRebuildAll();
		return;
	}

	// If the item doesn't exist in the list already we can simply add it.
	// If the item exists we need change the kItemState to match the true 
	// state of the object. The rules are:
	// Old State	: New State	: Reason
	// kAdded		: Remove	: This item never really existed. We just need to take it out of the list
	// kDeleted		: No-op		: We shouldn't be deleting items that are already gone
	// kChanged		: kDeleted	: The item can be deleted normally

	// find the original item if it exists
	typename ItemTypeVector::iterator pos(std::lower_bound(fItemList.begin(), fItemList.end(), itemID));

	// change to correct value
	if (pos != fItemList.end() && pos->Key() == itemID)
	{
		switch(pos->Value())
		{
		case kAdded:
			fItemList.erase(pos);
			break;
		case kDeleted:
			break;
		case kChanged:
			pos->Value() = kDeleted;
			break;
		}

		return;
	}

	// or add the item the list
	fItemList.insert(pos, StoredItemData(itemID, kDeleted));
}

template <class ItemType>
void ListLazyNotificationData<ItemType>::ItemChanged(ItemType itemID)
{
	if (fRebuildWholeList)
		return;

	if (fItemList.size() >= kMaxSize)
	{
		this->MarkShouldRebuildAll();
		return;
	}

	// If the item doesn't exist in the list already we can simply add it.
	// If the item exists we need change the kItemState to match the true 
	// state of the object. The rules are:
	// Old State	: New State	: Reason
	// kAdded		: kAdded	: This item doesn't exist yet so we have to add it
	// kDeleted		: Assert	: You can't change something that doesn't exist
	// kChanged		: kChanged	: Just changed multiple times

	// find the original item if it exists
	typename ItemTypeVector::iterator pos(std::lower_bound(fItemList.begin(), fItemList.end(), itemID));

	// change to correct value
	if (pos != fItemList.end() &&  pos->Key() == itemID)
	{
		switch(pos->Value())
		{
		case kAdded:
			break;
		case kDeleted:
			ASSERT_FAIL("ListLazyNotificationData::ItemChanged - You can't change a deleted item.");
			break;
		case kChanged:
			break;
		}

		return;
	}

	// or add the item the list
	fItemList.insert(pos, StoredItemData(itemID, kChanged));
}

template <class ItemType>
void ListLazyNotificationData<ItemType>::BreakoutChanges(K2Vector<ItemType> *addedItems, K2Vector<ItemType> *deletedItems, K2Vector<ItemType> *changedItems) const
{
	ASSERT_MSG(!fRebuildWholeList, "Broken assumption: If this is an observer that is calling this function it should have gotten nil cookie!");

	// Step through the list and put the ItemIDs in the appropriate
	// list based on whether they were added, deleted, or changed.
	// items that were destroyed can be ignored
	typename ItemTypeVector::const_iterator iter;

	for (iter = fItemList.begin(); iter != fItemList.end(); ++iter)
	{
		switch (iter->Value())
		{
		case kAdded:
			if (addedItems)
				addedItems->push_back(iter->Key());
			break;
		case kDeleted:
			if (deletedItems)
				deletedItems->push_back(iter->Key());
			break;
		case kChanged:
			if (changedItems)
				changedItems->push_back(iter->Key());
			break;
		}
	}
}
template <class ItemType>
void ListLazyNotificationData<ItemType>::Validate(IDataBase * /* db */)
{
}

#if 0
template<> void ListLazyNotificationData<UID>::Validate(IDataBase *db)
{
#ifdef DEBUG
	// Step through every UID that is marked for add and make
	// sure that it is valid.
	ListLazyNotificationData<UID>::ItemTypeVector::const_iterator iter;
	for (iter = fItemList.begin(); iter != fItemList.end(); ++iter)
	{
		if (iter->Value() == kAdded)
		{
			// It is a bad thing to have a cookie that says you are adding
			// a UID when that UID doesn't exist in the data base. A common
			// reason for this problem is a delete performing a pre and post
			// notify. The pre notify can make the item leave the list (in 
			// the case of add + delete and then the post notify adds it back
			// to the list as a delete. This is not good.
			ASSERT_MSG(db->GetClass(iter->Key()) != kInvalidClass, "ListLazyNotificationData<UID>::Validate - You are trying to add an item that isn't in the database. (possibly this is an undo of an extra delete?). Is the cookie add during a pre- and post-notify? Check for GetCommandState() == kDone before passing along a cookie.");
		}
	}
#endif
}
#endif
#endif
