//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TreeLazyNotificationData.h $
//  
//  Owner: Habib Khalfallah
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
#ifndef __LazyTreeMsgCookie__
#define __LazyTreeMsgCookie__

#include "LazyNotificationData.h"
#include "KeyValuePair.h"
#include "ChangeTree.h"

class ITreeViewMgr;

/** This class is used to identify changes that
	happened to objects which are tree based.
	For list based objects please use
	@see ListLazyNotificationData
*/
template<class ItemType>
class TreeLazyNotificationData : public LazyNotificationData
{
	/** Internal typedef to make code easier to read */
	typedef typename ChangeTree<ItemType>::Node TreeNode; 
public:
	/** Default constructor */
	TreeLazyNotificationData():LazyNotificationData(), fMustRebuildChangeRecords (false)
	{
	}

	/** Default destructor */
	virtual ~TreeLazyNotificationData()
	{
	}
	
	/** Use this to add another cookie into this one
		This method will ensure that items added that
		already exist in this tree will get set to a 
		"combined" state.
		@param other - The tree to add
	*/
	virtual void Add (const LazyNotificationData*  other);

	/** Use this to copy this tree and its state. You
		can ask the copy to be an exact copy or to have
		the proper state for undo (Adds and Deletes are
		swapped)
		@param undoData - Whether to swap adds and deletes
		@return - A copy of this class
	*/
	virtual LazyNotificationData*  Clone (bool16 undoData) const;

	/** Validate the cookie against the model. This is only really used
		for UIDs. There are some problems with deleting objects twice which
		will cause the cookie to think that an item which never existed 
		actually existed and was deleted. This call will verify that items
		which are currently marked for add (undo of a delete) exist in the
		database.
		NOTE: This call will not do anything in the release build
		@param db - The database that is associated with this cookie
	*/
	virtual void Validate(IDataBase *)
	{}


	/** Compress the tree to one root node that has kRebuild*/
	virtual void MarkShouldRebuildAll();

	/** @see LazyNotificationData::ShouldRebuildAll.
	*/
	virtual bool ShouldRebuildAll() const;

	/** Notify the tree that an item was added in the model
		@param item - The item that was added.
	*/
	void ItemAdded(const ItemType &item);
	
	/** Notify the tree that an item was deleted in the model
		@param item - The item that was deleted.
	*/
	void ItemDeleted(const ItemType &item);
	
	/** Notify the tree that an item was changed in the model
		@param item - The item that was changed.
	*/
	void ItemChanged(const ItemType &item);
	
	/** Notify the tree that an item was rebuilt in the model
		When you mark an item as rebuilt it means that it and
		each of its descendants will be reconstructed
		@param item - The item that needs rebuilt.
	*/
	void ItemRebuilt(const ItemType &item);

	/** This method allows the client to handel adds, deletes,
		changes, and rebuilds of given nodes. These operations
		are handled via callbacks. To use this simply create
		your required function objects. Objects must take an
		item of ItemType.
		@see IgnoreItem
		@param Added - The method to be called when an item is added
		@param Deleted - The method to call when an item is deleted
		@param Changed - The method to call when an item is changed
		@param Rebuilt - The method to call when an item and its children need rebuilt
	*/
	template<typename TAdded, typename TDeleted, typename TChanged, typename TBuild>
	void ProcessChanges(TAdded Added, 
						TDeleted Deleted, 
						TChanged Changed, 
						TBuild Rebuilt);

	/** This function object can be used by clients to easily ignore
		a particular node state. For instance if you want to ignore
		cases where a node was added you simply pass this as the first
		parameter to ProcessChanges
		@see ProcessChanges
		@param item - The item that should be ignored
	*/
	struct IgnoreItem : std::unary_function<const ItemType &,void>
	{
		void operator () (const ItemType &) const {}
	};

#ifdef DEBUG
	/** This debug code ill write out the tree to verify its contents
		@param stream - The stream to write the tree to
	*/
	virtual void WriteTree(std::ofstream *file);
#endif

	/*
	/ ** Used to indicate to external clients what type of change 
		happened to a given item
	* /
	enum ChangeType
	{
		/ ** Item was added * /
		kAdd,
		/ ** Item was deleted * /
		kDelete,
		/ ** Item was changed * /
		kChange,
		/ ** Item and its children need to be rebuilt * /
		kRebuild
	};

	/ ** Each item in the iterator will be a ChangeRecord * /
	typedef std::pair<ChangeType,ItemType> ChangeRecord;
	/ ** Used as a typedef simply to make less typing and easier reading * /
	typedef std::vector<ChangeRecord> ChangeRecordsContainer;
	/ ** Used as a typedef simply to make less typing and easier reading * /
	typedef typename ChangeRecordsContainer::const_iterator change_records_iterator;

	/ ** This method can be used to ask for an iterator
		which starts at the beginning of the changes.
		NOTE: When using this iterator it is highly 
		recommended that you handle each item change
		in the order that you iterate them, rather than
		skip some and try to handle them later.
		@return - A const iterator for looking at the changes
	* /
	change_records_iterator begin_change_records ();

	/ ** The end of the list of changes. Use this in
		conjuction with begin_change_records
		@return - The end of the changes.
	* /
	change_records_iterator end_change_records ();
	*/

protected:
	/** This method must be overridden by derived classes
		so that this class can clone itself without having
		to have knowledge about the actual class in question
		@return - A new object that is derived from this
	*/
	virtual TreeLazyNotificationData *CreateNewCookie() const = 0;

	/** Get the parent of a given item. This method should
		be overridden by classes that derive from this class
		and the implementation should look at the model to 
		determine what the appropriate parent is.
		@param item - The item for which we want the parent
		@param parent - Will be filled in with a parent (unless there is none)
		@return - kFalse if no valid parent was found - kTrue if a parent was found
	*/
	virtual bool16 GetParent(const ItemType &item, ItemType &parent) const  = 0;
	
#ifdef DEBUG
		virtual PMString GetNodeName(const ItemType &item) const
		{ 
			#pragma unused(item)
			return ""; 
		}
#endif

private:
	/** This method adds a given change to the stored change
		tree. The method will find the path from this node
		to the lowest node that is already in the tree. Then
		it will add all required nodes into the tree.
		@param item - the item to be marked with a change
		@param nodeChange - The change to be used. Only the item 
		will actually get marked with this change. Other nodes that
		are required to build the tree will get marked with empty
		changes.
	*/
	void AddChange(const ItemType &item, typename TreeNode::ChangeState nodeChange);

	/** Merge the children of two nodes together. The nodes may be
		the root of two trees but this is not required. This method
		will also make sure that if the same node (item) exists in
		both trees that the ChangeState gets updated correctly based
		on the combination of the two states
		NOTE: The whole and part nodes must point to the same ItemType
		@param whole - The node we are adding into
		@param part - The node we are mergin in
	*/
	void MergeChildren(typename ChangeTree<ItemType>::Node *whole, const TreeNode *part);

	/** Insert the 'otherStart' node and its children into 'myStart' as a subtree. 
		The 'otherStart' node can have descendants that exist in the 'self' tree. 
		In that case, we have to do some consolidating.
	*/
	void InsertSubBranch(TreeNode *myStart, const TreeNode *otherStart);

	/** this method will merge two change states so that the final 
		outcome will behave as expected. For instance if a node is
		marked for change and you then mark it as delete you want
		it to be marked as delete but if it is marked as delete and
		you try to mark it as changed you don't want that change to
		succeed because you can't change something that has been 
		deleted.
		@param node - The node that you are trying to update
		@param newState - The state you want to integrate
	*/
	void ChangeNode(TreeNode *node, typename ChangeTree<ItemType>::Node::ChangeState newState);

	/** This method can be used to swap the adds to deletes and the 
		deletes to adds. It is used by the clone method when the
		undo flag is turned on.
		@param item - The item to swap values for
	*/	
	void SwapAddAndDelete (const ItemType item);

	/** Used to store a tree of appropriate changes */
	ChangeTree<ItemType> fTree;

	/** Used to indicate whether the change records are up to date */
	bool fMustRebuildChangeRecords;

	/** Used to define the maximum size of the tree beyond which the tree is compressed*/
	enum {kMaxSize = 200};
};

#pragma export off

#endif