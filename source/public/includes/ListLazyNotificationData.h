//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ListLazyNotificationData.h $
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

#pragma once
#ifndef __ListLazyNotifsCookie__
#define __ListLazyNotifsCookie__

#include "LazyNotificationData.h"
#include "KeyValuePair.h"
#include <vector>

// The is a templated class so that clients can store data in the way that is
// most fitting for them. Two types of templates have been pre-defined. 
// The first takes a UID and the second takes a ClassID. 
// To add new types you must include the file LazyNotificationData.tpp so that
// the correct templated class can be compiled. Typically this is done in one
// location to avoid having to recompile the same template code over and over
// again. For app wide usage (things that you expect multiple plugins to have
// need of please put your definition in templates_pub.cpp. For plugin specific
// templates you can create a similar file in your plugin and add the definiation
// there. The definition should look like:
// template class ListLazyNotificationData<UID>;

/** This class should be used to indicate to observers which items in a list have 
	changed and how they have actually changed.
*/
template <class ItemType>
class ListLazyNotificationData : public LazyNotificationData
{
public:
	/** Default Constructor */
	ListLazyNotificationData():LazyNotificationData(), fRebuildWholeList(false){};

	/** Use this to add another cookie (of the same type) into this cookie
		All of the appropriate rules for merging cookies will be followed.
		While this method can be called by anybody it was created to allow
		the multiple cookies created from a string of commands to be combined
		into a single cookie for passing to the appropriate observers.
		@param other - The other item to add into this one.
					   NOTE: This method assumes that the two objects can be
					   downcast to the same type of object.
	*/
	virtual void Add (const LazyNotificationData*  other);

	/** This method is used to create a copy of its class which may or may
		not be setup for undo rather than do or redo. The meaning of undo is
		that added items are switched to deleted items and deleted items are
		switched to added. the changed items are not modified.
		While this method can be called by anybody it was created to allow
		cookies to be stored sot hat they can be sent to appropriate 
        observers more than once and with undo information if needed.
		@param undoData - IN kTrue - Swap the adds and deletes
		@return - A new object which looks like this one.
				  Note: the new object is no longer owned by this method
				  so callers need to be sure to clean up pointers that they
				  are no longer in need of.
	*/
	virtual LazyNotificationData*  Clone (bool16 undoData) const;

	/** Indicate that a new item of ItemType was added to the model.
		This method should be called by the command when creating the
		cookie to be passed to ModelChange.
		@param itemID - IN The item that was added.
	*/

	/** Mark the cookie indicating that all needs rebuilding*/
	virtual void MarkShouldRebuildAll ();

	void ItemAdded(ItemType itemID);

	/** Indicate that an item of ItemType was removed from the model.
		This method should be called by the command when creating the
		cookie to be passed to ModelChange.
		@param itemID - IN The item that was deleted.
	*/
	void ItemDeleted(ItemType itemID);

	/** Indicate that an item of ItemType was changed in the model.
		This method should be called by the command when creating the
		cookie to be passed to ModelChange.
		@param itemID - IN The item that was changed.
	*/
	void ItemChanged(ItemType itemID);

	/** Use this method to determine what changes have actually happened
		to the model. Items will be separated into three lists for you.
		This method should be called by the observer in LazyUpdate to
		figure out which items actually changed and how.
		@param addedItems - OPTIONAL IN/OUT will be filled with the list 
				of items which were added. Pass nil to ignore added items
		@param deletedItems - OPTIONAL IN/OUT will be filled with the list 
				of items which were deleted. Pass nil to ignore deleted items
		@param changedItems - OPTIONAL IN/OUT will be filled with the list 
				of items which were changed. Pass nil to ignore changed items
	*/
	void BreakoutChanges(K2Vector<ItemType> *addedItems, K2Vector<ItemType> *deletedItems, K2Vector<ItemType> *changedItems) const;

	/** @see LazyNotificationData::ShouldRebuildAll.
	*/
	bool ShouldRebuildAll() const {return fRebuildWholeList;}

	/** Validate the cookie against the model. This is only really used
		for UIDs. There are some problems with deleting objects twice which
		will cause the cookie to think that an item which never existed 
		actually existed and was deleted. This call will verify that items
		which are currently marked for add (undo of a delete) exist in the
		database.
		NOTE: This call will not do anything in the release build
		@param db - The database that is associated with this cookie
	*/
	virtual void Validate(IDataBase *db);
	

private:

	// Used as an indicator of how a particular item changed (used internally)
	enum ListCookieItemState {
		// Indicates that the item was added
		kAdded, 
		// Indicates that the item was deleted
		kDeleted, 
		// Indicates that the item was changed
		kChanged
	};

	// A typedef to make less typing. Combines an item and state.
	typedef KeyValuePair<ItemType, ListCookieItemState> StoredItemData;
	// A typedef to make less typing. Vector of items and states
	typedef std::vector<StoredItemData> ItemTypeVector;

	// This is the list of items and their changes
	std::vector<StoredItemData> fItemList;

	// This bool indicates whether the entire list should just be rebuilt
	bool fRebuildWholeList;
	/** Used to define the maximum size of the changes list beyond which the cookie is compressed*/
	enum {kMaxSize = 100};
};

#endif