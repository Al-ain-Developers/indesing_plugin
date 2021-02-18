//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ChangeTree.tpp $
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

#include "ChangeTree.h"

#include <queue>
#include <boost/bind.hpp>

template<class ItemType>
ChangeTree<ItemType>::ChangeTree(const ChangeTree &o) : fRoot(nil)
{
	if (o.fRoot != nil)
		CloneBranch(fRoot, o.fRoot);
}

template<class ItemType>
ChangeTree<ItemType> &ChangeTree<ItemType>::operator=(const ChangeTree &o)
{
	ChangeTree<ItemType> temp(o);
	this->swap(temp);
	return *this;
}

template<class ItemType>
void ChangeTree<ItemType>::swap(ChangeTree &o)
{
	std::swap(fRoot, o.fRoot);
	fLookup.swap(o.fLookup);
}

template<class ItemType>
int ChangeTree<ItemType>::size() const
{
	return (int)fLookup.size();
}

template<class ItemType>
void ChangeTree<ItemType>::Insert(Node *node, Node *parent)
{
	// First make sure the node is valid
	ASSERT(node != nil);

#ifdef VALIDATE_TREE 
	// Validate that our internal lists are in sync
	ChangeTreeValidator<ItemType> validator(fLookup, fRoot);
	validator();
#endif
	// If parent is nill we should treat this
	// as the root node. First make sure that
	// this list is empty
	ASSERT(parent != nil || fRoot == nil);

	// Now make sure this node isn't already in the ChangeTree
	ASSERT_MSG(fLookup.find(node->fItem) == fLookup.end(), "ChangeTree<ItemType>::Insert - This item is already in the lookup");

	// Now insert the node into the ChangeTree
	if (parent)
		parent->fChildren.push_back(node);
	else
	{
		// If parent is nil this should be 
		// stored as the root node
		fRoot = node;
	}
	
	// Set this node's parent
	node->fParent = parent;

	// Add the node into the lookup
	fLookup[node->fItem] = node;
#ifdef VALIDATE_TREE 
	// Validate that our internal lists are in sync
	ChangeTreeValidator<ItemType> validator2(fLookup, fRoot);
	validator2();
#endif
}


template<class ItemType>
void ChangeTree<ItemType>::Remove(Node *node)
{
	// make sure the node is valid
	ASSERT(node != nil);

#ifdef VALIDATE_TREE 
	// Validate that our internal lists are in sync
	ChangeTreeValidator<ItemType> validator(fLookup, fRoot);
	validator();
#endif
	// If this node is the root node we should clear fRoot
	// NOTE: We are not deleting fRoot just setting it to
	// nil. That is because we will be deleting all of the
	// nodes to be removed at one time.
	if (node == fRoot)
		fRoot = nil;
	else
	{
		// Make sure the parent of this node doesn't
		// point to this node because it is about to be deleted
		ASSERT (node->fParent != nil);
		node->fParent->fChildren.erase(std::find(node->fParent->fChildren.begin(), node->fParent->fChildren.end(), node));
	}

	// Delete this node and all of its children. In order
	// to keep performance up we will do this using a queue
	// rather than recursively. The reason is that this ChangeTree
	// can have any depth and we want to avoid a large stack
		
	std::queue<Node*> treeQueue;
	treeQueue.push(node);

	while (!treeQueue.empty())
	{
		// Get the current node
		Node *curNode = treeQueue.front();
		treeQueue.pop();
		
		// Add its direct descendents to the queue
		void (std::queue<Node*>::*ptr) (const typename std::queue<Node*>::value_type&) = &std::queue<Node*>::push;
		std::for_each(curNode->fChildren.begin(), curNode->fChildren.end(), boost::bind(ptr, &treeQueue, _1));

		// Remove the node from the lookup
		fLookup.erase(curNode->fItem);

		// Now I can delete this node
		delete curNode;
	}
#ifdef VALIDATE_TREE 
	// Validate that our internal lists are in sync
	ChangeTreeValidator<ItemType> validator2(fLookup, fRoot);
	validator2();
#endif
}


template<class ItemType>
typename ChangeTree<ItemType>::Node *ChangeTree<ItemType>::find(ItemType item)
{
	// Look for the item in our lookup
	typename NodeMap::iterator iter(fLookup.find(item)); 

	// If the item wasn't found return nil
	if (iter == fLookup.end())
		return nil;

	// Otherwise return the item
	return iter->second;
}


template<class ItemType>
typename ChangeTree<ItemType>::Node *ChangeTree<ItemType>::GetRoot()
{
	return fRoot;
}

template<class ItemType>
void ChangeTree<ItemType>::CloneBranch(Node *myStart, const Node *otherStart)
{
#ifdef VALIDATE_TREE 
	// Validate that our internal lists are in sync
	ChangeTreeValidator<ItemType> validator(fLookup, fRoot);
	validator();
#endif
	typedef std::pair<Node*, Node*> NodePair;
	typename std::vector<Node*>::const_iterator iter;

	// This queue holds the new parent node (first)
	// and the node to be copied into it (second)
	std::queue<NodePair> treeQueue;
	
	if (myStart != nil)
	{
		// We have a node to place into
		treeQueue.push(NodePair(myStart, const_cast<Node*>(otherStart)));
	}
	else
	{
		// This must be the root so create a new node and add it as fRoot.
		ASSERT(fRoot == nil);
		Insert (new Node(otherStart->fItem, otherStart->fChangeState), nil);

		// now add each of the children to the queue so that they
		// get inserted properly
		for (iter = otherStart->fChildren.begin(); iter != otherStart->fChildren.end(); ++iter)
		{
			treeQueue.push(NodePair(fRoot, *iter));
		}
	}

	// Go through every item in the list and add new nodes to my ChangeTree.
	while (!treeQueue.empty())
	{
		// Get the current nodes
		Node *curParent = treeQueue.front().first;
		Node *oldChild = treeQueue.front().second;
		treeQueue.pop();

		// Create the new node that we will be inserting
		Node *newChild = new Node(oldChild->fItem, oldChild->fChangeState);

		// Insert the new node
		Insert(newChild, curParent);

		// Push each of the node's children into the queue so
		// they will be added before we are done.
		for (iter = oldChild->fChildren.begin(); iter != oldChild->fChildren.end(); ++iter)
		{
			treeQueue.push(NodePair(newChild, *iter));
		}
	}
}