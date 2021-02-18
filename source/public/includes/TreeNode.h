//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TreeNode.h $
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
#ifndef __TreeNode__
#define __TreeNode__

#include <vector>
#include <boost/noncopyable.hpp>

/** Used in conjunction with a tree to store information about each node */
template<class ItemType>
struct TreeNode : boost::noncopyable
{
	/** Used to indicate what type of tree change happened */
	enum ChangeState {
		/** No change */
		kEmpty = 0, 
		/** This node was added to the tree */
		kInsert, 
		/** This node was deleted from the tree */
		kDelete,
		/** This node was changed */
		kChange,
		/** This node and its children need to be rebuilt */
		kRebuild};

	/** Used to construct a tree node */
	TreeNode(ItemType item, ChangeState state) 
		:fItem(item)
		,fChangeState(state)
		,fParent(nil)
		,fNewNode(fChangeState == kInsert || fChangeState == kRebuild)
	{}


	/** Holds a specific item that changed */
	ItemType fItem;

	/** Stores the change that actually happened */
	ChangeState fChangeState;

	/** Used to indicate that that this node didn't exist in the model before these changes */
	bool fNewNode;

	/** Holds this node's children */
	std::vector<TreeNode *> fChildren;

	/** Hold this node's parent (nil if this node has no parent) */
	TreeNode *fParent;
};

#endif
