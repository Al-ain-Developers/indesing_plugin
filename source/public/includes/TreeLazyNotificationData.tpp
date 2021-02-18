//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TreeLazyNotificationData.tpp $
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

#include "TreeLazyNotificationData.h"
#include "ChangeTree.tpp"

// ----- Includes -----
#include <queue>
#include <boost/bind.hpp>

// this is needed in VC & CW, but not in GCC?
#ifdef __MWERKS__
template<class ItemType>
typename TreeLazyNotificationData<ItemType>::TreeLazyNotificationData* TreeLazyNotificationData<ItemType>::CreateNewCookie() const { return nil; }
#endif

template<class ItemType>
bool16 TreeLazyNotificationData<ItemType>::GetParent(const ItemType &item, ItemType &parent) const 
{ 
	#pragma unused(item,parent)
	return kFalse; 
}

template<class ItemType>
void TreeLazyNotificationData<ItemType>::Add (const LazyNotificationData*  other)
{
	fMustRebuildChangeRecords = true;
	// Add a the other list into this list to build one large master list
	// We must add using the same methods we use to add items to the list
	// so that we can ensure that the correct rules are followed if the
	// item already exists in this list

	// now I can copy the data from the other cookie into this one
	if (other)
	{
		TreeLazyNotificationData *realOther = static_cast<TreeLazyNotificationData *>(const_cast<LazyNotificationData *>(other));

		if (realOther->fTree.GetRoot() != nil)
		{
			this->MergeChildren(fTree.GetRoot(), realOther->fTree.GetRoot()); // [][] note that we may copy everything only to delete it later
		}
	}
	if (fTree.size() > kMaxSize)
		this->MarkShouldRebuildAll();
}

template<class ItemType>
void TreeLazyNotificationData<ItemType>::SwapAddAndDelete (const ItemType item)
{
	typename ChangeTree<ItemType>::Node *node = fTree.find(item);
	node->fChangeState = node->fChangeState == TreeNode::kInsert ? TreeNode::kDelete : TreeNode::kInsert;
}

template<class ItemType>
LazyNotificationData*  TreeLazyNotificationData<ItemType>::Clone (bool16 undoData) const
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
	// change it to kAdded. kChanged or kRebuild do not matter for this
	// method.
	TreeLazyNotificationData *treeClonedList = this->CreateNewCookie();

	treeClonedList->Add(this);

	// Only switch the added and deleted flags if the client wants the undo information.
	if (undoData == kTrue && treeClonedList->fTree.GetRoot() != nil)
	{
		// We will do this by calling ProcessChanges and only passing
		// methods for kDelete and kInsert that will swap their values
		treeClonedList->ProcessChanges(::boost::bind(&TreeLazyNotificationData::SwapAddAndDelete, treeClonedList, _1), 
									   ::boost::bind(&TreeLazyNotificationData::SwapAddAndDelete, treeClonedList, _1), 
									   IgnoreItem(), 
									   IgnoreItem());
	}

	return treeClonedList;
}

template<class ItemType>
void TreeLazyNotificationData<ItemType>::MarkShouldRebuildAll()
{
	TreeNode *rootNode = fTree.GetRoot();
	
	if (!rootNode)
		return;
		
	ChangeNode(rootNode, TreeNode::kRebuild);

	// Delete all of the children nodes of rootNode
	typename std::vector<TreeNode *>::reverse_iterator iter;
		
	while ((iter = rootNode->fChildren.rbegin()) != rootNode->fChildren.rend())
		fTree.Remove(*iter);
}

template<class ItemType>
bool TreeLazyNotificationData<ItemType>::ShouldRebuildAll() const
{
	const TreeNode *rootNode = const_cast<TreeLazyNotificationData<ItemType>*>(this)->fTree.GetRoot();
	return !rootNode || rootNode->fChangeState == TreeNode::kRebuild;
}


template<class ItemType>
void TreeLazyNotificationData<ItemType>::ItemAdded(const ItemType &item)
{
	this->AddChange(item, TreeNode::kInsert);
}

template<class ItemType>
void TreeLazyNotificationData<ItemType>::ItemDeleted(const ItemType &item)
{
	this->AddChange(item, TreeNode::kDelete);
}

template<class ItemType>
void TreeLazyNotificationData<ItemType>::ItemChanged(const ItemType &item)
{
	this->AddChange(item, TreeNode::kChange);
}

template<class ItemType>
void TreeLazyNotificationData<ItemType>::ItemRebuilt(const ItemType &item)
{
	this->AddChange(item, TreeNode::kRebuild);
}

template<class ItemType>
void TreeLazyNotificationData<ItemType>::AddChange(const ItemType &item, typename TreeLazyNotificationData<ItemType>::TreeNode::ChangeState nodeChange)
{
	fMustRebuildChangeRecords = true;
	TreeNode *insertionNode = nil;
	
	// Check to see if this node is already in the tree.
	// If it is we don't need to worry about adding it 
	// again, we just need to update the data that is there.
	insertionNode = fTree.find(item);

	if (insertionNode != nil)
	{
		// We found the item so we don't need to build the rest
		// of the tree. Just add the change so that it gets
		// incorporated
		ChangeNode(insertionNode, nodeChange);

		// If the node is being set to rebuild we need
		// to delete all of the child nodes
		if (nodeChange == TreeNode::kRebuild)
		{
			typename std::vector<TreeNode *>::reverse_iterator iter;
			
			while ((iter = insertionNode->fChildren.rbegin()) != insertionNode->fChildren.rend())
				fTree.Remove(*iter);
		}
		return;
	}
	
	// Build a list of nodes to add to the tree.
	// We will build the list front to back (bottom up) 
	// but when we insert items we will add them from the 
	// back to the front. This allows for quick tree walking
	// but also allows us to add nodes to the vector quickly.
	std::vector<TreeNode *> nodesPath;
	TreeNode *newNode = new TreeNode(item, nodeChange);
	nodesPath.push_back(newNode);
	
	ItemType curItem(item);
	bool16 bStillLookingInsertionNode(kTrue);

	do
	{
		// Get the item's parent. If 
		bStillLookingInsertionNode = GetParent(curItem, curItem);
		if(bStillLookingInsertionNode)
		{
			// We found a valid parent so we are not at the top of the tree yet
			// Only add nodes until we find a given node in the tree
			insertionNode = fTree.find(curItem);
			if (insertionNode == nil)
			{
				newNode = new TreeNode(curItem, TreeNode::kEmpty);
				nodesPath.push_back(newNode);
			}
			else
				bStillLookingInsertionNode = kFalse;
		}
	} while (bStillLookingInsertionNode);

	// Now we may have a specific node that we need to insert this tree into,
	// if so we will insert it here.
	if (insertionNode && insertionNode->fChangeState == TreeNode::kRebuild)
	{
		// Delete any new nodes that were created to avoid leaks
		typename std::vector<TreeNode *>::iterator iter;
		for (iter = nodesPath.begin(); iter != nodesPath.end(); ++iter)
			delete *iter;
		if (fTree.size() > kMaxSize)
			this->MarkShouldRebuildAll();
		return;
	}

	// Insert the nodes into the tree in reverse order.
	typename std::vector<TreeNode *>::reverse_iterator iter;
	for (iter = nodesPath.rbegin(); iter != nodesPath.rend(); ++iter)
	{
		fTree.Insert(*iter, insertionNode);
		insertionNode = *iter;
	}
	if (fTree.size() > kMaxSize)
		this->MarkShouldRebuildAll();
}

template<class ItemType>
template<typename TAdded, typename TDeleted, typename TChanged, typename TBuild>
void TreeLazyNotificationData<ItemType>::ProcessChanges(TAdded Added, 
												 TDeleted Deleted, 
												 TChanged Changed, 
												 TBuild Rebuild)
{
	// Walk the tree and call the appropriate callback function;
	TreeNode *curNode = fTree.GetRoot();

	// Update the tree based on our currently list of known dirties
	if (curNode != nil)
	{
		std::queue<TreeNode*> treeQueue;
		treeQueue.push(curNode);

		while (!treeQueue.empty())
		{
			// Get the current node and add its direct descendents to the queue
			curNode = treeQueue.front();
			treeQueue.pop();

			// Don't go farther down for when we come to an item that is marked
			// for rebuild
			ASSERT(curNode->fChangeState != TreeNode::kRebuild || curNode->fChildren.size() == 0);
			//if (curNode->fChangeState != TreeNode::kRebuild)
			std::for_each(curNode->fChildren.begin(), curNode->fChildren.end(), boost::bind(static_cast<void (std::queue<TreeNode*>::*) (const typename std::queue<TreeNode*>::value_type&)>(&std::queue<TreeNode*>::push), &treeQueue, _1));

			// Now I can determine whether or not I actually need to do anything with this
			// node based on its current values.
			switch (curNode->fChangeState)
			{
			case TreeNode::kChange:
				Changed(curNode->fItem);
				break;
			case TreeNode::kInsert:
				Added(curNode->fItem);
				break;
			case TreeNode::kDelete:
				Deleted(curNode->fItem);
				break;
			case TreeNode::kRebuild:
				// 6/3/05 - rgano
				// We will possibly need to watch out for the case of trying to rebuild a node
				// tat never existed. It is possible that the tree manager doesn't handle that
				// case well. If not a possible solution is to call add and then rebuild. An issue
				// with that would be that there may be some clients doing someting with the tree
				// rather than just passing the information on to the tree. Clone() is good example
				// If we make this add and then rebuild it will break our very own clone method.
				Rebuild(curNode->fItem);
				break;
			default:
				// Do nothing for the empty case
				break;
			}
		}
	}
}
	
template<class ItemType>
void TreeLazyNotificationData<ItemType>::MergeChildren(typename ChangeTree<ItemType>::Node *self, const typename ChangeTree<ItemType>::Node *other)
{
	if (!other) return;

	// If we don't have anything yet just clone the branch into this 
	// tree
	if (!self)
	{
		fTree.CloneBranch(self, other);
		return;
	}

	if (self->fItem != other->fItem)
	{
		// If the "root" nodes don't match, then adopt as rebuild the other root node
		TreeNode *selfParent = self->fParent;
		fTree.Remove (self);
		fTree.Insert (new TreeNode (other->fItem, TreeNode::kRebuild), selfParent);
		return;
	}

	typedef std::pair<TreeNode*, TreeNode*> NodePair;

	// This queue holds the pairs of self,other to process
	std::queue<NodePair> treeQueue;
	treeQueue.push (NodePair (self, const_cast<TreeNode *>(other)));

	while (!treeQueue.empty ())
	{
		self = treeQueue.front().first;
		other = treeQueue.front().second;
		treeQueue.pop ();

		// These iterators are used for walking the children of the other tree node
		typename std::vector<TreeNode *>::const_iterator otherIter;
		typename std::vector<TreeNode *>::const_iterator otherEnd(other->fChildren.end());

		// Process the "root" node
		ChangeNode(self, other->fChangeState);

		// If This node is marked for rebuild delete all of its children
		if (self->fChangeState == TreeNode::kRebuild)
		{
			typename std::vector<TreeNode *>::reverse_iterator iter;
			while ((iter = self->fChildren.rbegin()) != self->fChildren.rend())
				fTree.Remove(*iter);
		}
		else if (self->fChangeState == TreeNode::kDelete)
		{
			if (self->fNewNode == true)
			{
				// If the node was new and it is now marked delete we just remove it and
				// all of its children
				fTree.Remove(self);
			}
			else
			{
				// If this node is marked for delete, just delete all of its children.
				typename std::vector<TreeNode *>::reverse_iterator iter;
				while ((iter = self->fChildren.rbegin()) != self->fChildren.rend())
					fTree.Remove(*iter);
			}
		}
		else
		{
			// Only merge other into self if this is not a rebuild node already
			
			// For each child of the other
			for (otherIter = other->fChildren.begin(); otherIter != otherEnd; ++otherIter)
			{
				TreeNode *findInSelf = fTree.find ((*otherIter)->fItem);

				if (findInSelf)
				{
					if (findInSelf->fParent == self)
					{
						treeQueue.push (NodePair (findInSelf, *otherIter));
					}
					else
					{
						bool16 bRemovedNode(kFalse);
						TreeNode *oldParent = findInSelf->fParent;

						ChangeNode (self, TreeNode::kRebuild);
						
						typename std::vector<TreeNode *>::reverse_iterator iter;
						while ((iter = self->fChildren.rbegin()) != self->fChildren.rend())
						{
							if (*iter == oldParent)
								bRemovedNode = kTrue;
							fTree.Remove(*iter);
						}

						if (!bRemovedNode)
						{
							ChangeNode (findInSelf->fParent, TreeNode::kRebuild);
							while ((iter = oldParent->fChildren.rbegin()) != oldParent->fChildren.rend())
								fTree.Remove(*iter);
						}
					}
				}
				else
				{
					InsertSubBranch(self, (*otherIter));
				}
			}
		}
	}
}

template<class ItemType>
void TreeLazyNotificationData<ItemType>::InsertSubBranch(TreeNode *myStart, const TreeNode *otherStart)
{
	typedef std::pair<TreeNode*, TreeNode*> NodePair;
	typename std::vector<TreeNode*>::const_iterator treeIter;

	// This queue holds the new parent node (first)
	// and the node to be copied into it (second)
	std::queue<NodePair> treeQueue;
	
	ASSERT(myStart);
	if (myStart != nil)
	{
		// We have a node to place into
		treeQueue.push(NodePair(myStart, const_cast<TreeNode*>(otherStart)));
	}

	// Go through every item in the list and add new nodes to my ChangeTree.
	while (!treeQueue.empty())
	{
		// Get the current nodes
		TreeNode *curParent = treeQueue.front().first;
		TreeNode *oldChild = treeQueue.front().second;
		treeQueue.pop();

		TreeNode *findInSelf = fTree.find (oldChild->fItem);
		if (findInSelf)
		{
			TreeNode *oldParent = findInSelf->fParent;
			ChangeNode (curParent, TreeNode::kRebuild);
			
			typename std::vector<TreeNode *>::reverse_iterator iter;
			while ((iter = curParent->fChildren.rbegin()) != curParent->fChildren.rend())
			{
				fTree.Remove(*iter);
			}

			TreeNode *findOldParent = fTree.find (oldParent->fItem);
			if (findOldParent )
			{
				ChangeNode (oldParent, TreeNode::kRebuild);
				while ((iter = oldParent->fChildren.rbegin()) != oldParent->fChildren.rend())
					fTree.Remove(*iter);
			}
		}
		else
		{
			// Create the new node that we will be inserting
			TreeNode *newChild = new TreeNode(oldChild->fItem, oldChild->fChangeState);

			// Insert the new node
			fTree.Insert(newChild, curParent);

			// Push each of the node's children into the queue so
			// they will be added before we are done.
			for (treeIter = oldChild->fChildren.begin(); treeIter != oldChild->fChildren.end(); ++treeIter)
			{
				treeQueue.push(NodePair(newChild, *treeIter));
			}
		}
	}
}
/*
template<class ItemType>
void TreeLazyNotificationData<ItemType>::AppendChangeRecord (typename TreeLazyNotificationData<ItemType>::ChangeType x, 
												      ItemType y)
{
	fChangeRecords.push_back (ChangeRecord (x, y));
}

template<class ItemType>
void TreeLazyNotificationData<ItemType>::EnsureChangeRecordsUpToDate ()
{
	if (fMustRebuildChangeRecords)
	{
		fMustRebuildChangeRecords = false;
		fChangeRecords.clear ();

		ProcessChanges (
			boost::bind (&TreeLazyNotificationData<ItemType>::AppendChangeRecord, this, kAdd, _1),
			boost::bind (&TreeLazyNotificationData<ItemType>::AppendChangeRecord, this, kDelete, _1),
			boost::bind (&TreeLazyNotificationData<ItemType>::AppendChangeRecord, this, kChange, _1),
			boost::bind (&TreeLazyNotificationData<ItemType>::AppendChangeRecord, this, kRebuild, _1));
	}
}

template<class ItemType>
typename TreeLazyNotificationData<ItemType>::change_records_iterator TreeLazyNotificationData<ItemType>::begin_change_records ()
{
	EnsureChangeRecordsUpToDate ();
	return fChangeRecords.begin ();
}

template<class ItemType>
typename TreeLazyNotificationData<ItemType>::change_records_iterator TreeLazyNotificationData<ItemType>::end_change_records ()
{
	EnsureChangeRecordsUpToDate ();
	return fChangeRecords.end ();
}
*/

template<class ItemType>
void TreeLazyNotificationData<ItemType>::ChangeNode(TreeNode *node, typename ChangeTree<ItemType>::Node::ChangeState newState)
{
	// This method has to have some smarts about how to modify nodes.
	// The reason for this is that in some cases you cannot just change
	// a state from one state to another. Imaging trying to go from 
	// deleted to changed. How can you change something that has been
	// deleted.

	// If my state is empty (no change) then there is no problem 
	// with setting them to whatever state we are trying to set
	// them to.
	if (node->fChangeState == TreeNode::kEmpty)
	{
		node->fChangeState = newState;

		if (newState == TreeNode::kInsert || newState == TreeNode::kRebuild)
			node->fNewNode = true;
	}
	else if (node->fChangeState != newState)
	{
		// Now if the original state wasn't kEmpty AND it doesn't
		// already match the state being passed in we want to use
		// our rules for changing the state so that it gets changed
		// correctly
		switch (node->fChangeState)
		{
			case TreeNode::kEmpty:
			break;
			
			case TreeNode::kInsert:
			// Original state was Insert. 
			if (newState == TreeNode::kDelete || newState == TreeNode::kRebuild)
				// If the new state is Delete we delete the node
				// and all of its children from the tree.
				// If we are rebuilding a new node we need to mark
				// it as rebuilt but keep its new state around
				node->fChangeState = newState;
			break;
		case TreeNode::kDelete:
			// Original state was Delete
			if (newState == TreeNode::kInsert)
				// If the new state is kInsert we will mark the
				// node as changed because it was taken out and 
				// added back but probably changed in the mean-
				// time.
				node->fChangeState = TreeNode::kChange;
			// You cannot change or rebuild a deleted node
			ASSERT_MSG(newState != TreeNode::kChange, "Cannot change an item that has been deleted");
			// Deleting an linked element will mark the element as deleted. 
			// When later the content is deleted, XMLUnplaceElementCmd sends a rebuild notification on the same element.
			//ASSERT_MSG(newState != TreeNode::kRebuild, "Cannot rebuild an item that has been deleted");
			break;
		case TreeNode::kChange:
			// Original state was Change
			if (newState == TreeNode::kDelete || newState == TreeNode::kRebuild)
				// If the new state is delete or rebuild we just
				// set it to the new state because those both
				// take precidence over a change state.
				node->fChangeState = newState;
			// We cannot insert a node that is already marked for change.
			ASSERT_MSG(newState != TreeNode::kInsert, "Why are you trying to insert an item that already exists?");
			break;
		case TreeNode::kRebuild:
			// Original state was Rebuild
			if (newState == TreeNode::kDelete)
				// Mark the node for delete. Later we may actually
				// remove this node and all of its children from the tree. 
				// that decision is based on whether the node was new or not.
				node->fChangeState = newState;

			// We cannot insert a node that is already marked for rebuild.
			break;
		}
	}
}

#ifdef DEBUG
#include <fstream>

template<class ItemType>
void TreeLazyNotificationData<ItemType>::WriteTree(std::ofstream *file)
{
	// Walk the tree and call the appropriate callback function;
	TreeNode *curNode = fTree.GetRoot();

	// Update the tree based on our currently list of known dirties
	if (curNode != nil)
	{
		std::queue<TreeNode*> treeQueue;
		treeQueue.push(curNode);

		while (!treeQueue.empty())
		{
			// Get the current node and add its direct descendents to the queue
			curNode = treeQueue.front();
			treeQueue.pop();
			
			std::for_each(curNode->fChildren.begin(), curNode->fChildren.end(), boost::bind(static_cast<void (std::queue<TreeNode*>::*) (const typename std::queue<TreeNode*>::value_type&)>(&std::queue<TreeNode*>::push), &treeQueue, _1));

			(*file) << this->GetNodeName(curNode->fItem).GetUTF8String().c_str();
			
			//PMString type;
			switch (curNode->fChangeState)
			{
			case TreeNode::kEmpty:
				(*file) << ":Empty - ";
				break;
			case TreeNode::kInsert:
				(*file) << ":Insert - ";
				break;
			case TreeNode::kDelete:
				(*file) << ":Delete - ";
				break;
			case TreeNode::kChange:
				(*file) << ":Change - ";
				break;
			case TreeNode::kRebuild:
				(*file) << ":Rebuild - ";
				break;
			}
			
			if (curNode->fParent != nil)
				(*file) << this->GetNodeName(curNode->fParent->fItem).GetUTF8String().c_str();
			else
				(*file) << "[none]";

			(*file) << std::endl;
		}
	}
}
#endif