//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ChangeTree.h $
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
#ifndef __ChangeTree__
#define __ChangeTree__

#include "TreeNode.h"
#include <map>
#ifdef DEBUG
// #define VALIDATE_TREE
#endif
#ifdef VALIDATE_TREE
#include <queue>
#include <boost/bind.hpp>
#endif

/** Used to hold information about changes nodes in a tree.
	NOTE: This tree does NOT sort the child nodes in any 
	order. They are simply inserted into the tree in the
	location that we decide. Because of this you cannot
	expect to walk the children looking for more meaning-
	ful information than just the parent-child relation-
	ships.
*/
template<class ItemType>
class ChangeTree
{
public:
	/** Just a simpler thing to type for clients */
	typedef TreeNode<ItemType> Node;
	
	/** Default constructor */
	ChangeTree() : fRoot(nil) {}

	/** Copy constructor 
		@param o - The object to copy
	*/
	ChangeTree(const ChangeTree &o);

	/** Destructor */
	~ChangeTree()
	{
		if (fRoot != nil)
			Remove(fRoot);
	}

	/** Assignment Operator 
		@param o - The object to copy
		@return - A pointer to this object
	*/
	ChangeTree &operator=(const ChangeTree &o);

	/** Use this to swap the contents of this object with the
		contents of another object.
		@param ChangeTree - The object with which you want to swap data
	*/
	void swap(ChangeTree &o);

	/** Use this to get the size of the tree
	*/
	int size() const;

	/** Use this to clone a branch of the tree.
		New nodes will be created that match the
		nodes in the other branch.
		@param myStart - The node under which to add the new branch.
						 If this is a nil pointer the branch will be
						 added as root
		@param otherStart - The beginning of the other branch
	*/
	void CloneBranch(Node *myStart, const Node *otherStart);

	/** Insert a new node into the tree. 
		NOTE: Once you insert a node into this tree
		the tree owns it. You can ask for a node to
		get information but the tree will handle 
		deletion of the node
		@param node - the new node to be inserted
		@param parent - the parent of this node
	*/
	void Insert(Node *node, Node *parent);

	/** Remove a node and its children from this tree.
		@param node - the node to be removed
	*/
	void Remove(Node *node);

	/** This method will look up a node given a unique
		identifier.
		@param item - the item you are looking up
		@return Node - The node that corresponds to the item
	*/
	Node *find(ItemType item);

	/** Get the root node of the tree
		@return Node - the node at the root of the tree
	*/
	Node *GetRoot();

private:

	/** The root node of the tree */
	Node *fRoot;

	/** A map for quick lookup between an item and a node */
	typedef std::map<ItemType, Node *> NodeMap;
	NodeMap fLookup;

public:
#ifdef VALIDATE_TREE 
		// Validator for fLookup map -- check for fRoot's tree and fLookup being out of sync 
		template<class SameItemType>
		class ChangeTreeValidator : public std::unary_function<SameItemType, void>
		{
		public:
			ChangeTreeValidator(NodeMap lookup, Node *root) : fMyLookup(lookup),fMyRoot(root)
			{
				//ASSERT(fMyRoot != nil);
			}
			void operator()()
			{
				typename NodeMap::iterator iter;
				for (iter = fMyLookup.begin(); iter != fMyLookup.end(); ++iter)
				{
					// Check fMyRoot and its descendants for a match on current iter
					std::queue<Node*> treeQueue;
					treeQueue.push(fMyRoot);
					Node* targetNode = iter->second;
					bool16 bFound = kFalse;
					while (!treeQueue.empty())
					{
						// Get the current node
						Node *curNode = treeQueue.front();
						treeQueue.pop();
						
						if (curNode->fItem == targetNode->fItem)
						{
							bFound = kTrue;
							break;	// Found map item in tree... this is good
						}
						// Add its direct descendents to the queue
						std::for_each(curNode->fChildren.begin(), curNode->fChildren.end(), boost::bind(&std::queue<Node*>::push, &treeQueue, _1));
					}
					ASSERT_MSG(bFound, "ChangeTree out of sync -- some fLookup node not found in fRoot's tree!");
				}
			}
			
	//		void operator()(ItemType const& item);
		private:
			Node *fMyRoot;
			NodeMap fMyLookup;
		};
#endif

};
#endif