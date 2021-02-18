//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITreeViewHierarchyAdapter.h $
//  
//  Owner: Matt Joss
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
#ifndef __ITreeViewHierarchyAdapter__
#define __ITreeViewHierarchyAdapter__

#include "IPMUnknown.h"
#include "widgetid.h"
#include "NodeID.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class IControlView;

//----------------------------------------------------------------------------------------
// ITreeViewHierarchyAdapter
//----------------------------------------------------------------------------------------

/** Interface that provides the means for navigating through
	a tree model. It is like the adapter pattern in that it provides a way for the TreeView widget
	to navigate a tree-model without requiring the tree-model to conform to any given
	interface.

	Client code wishing to use a tree view widget should implement this interface.
	
	To aid in debugging your ITreeViewHierarchyAdapter implementation, check the test menu item
	Test > UI > Enable TreeView Validation.  This enables more debug only code to check that your hierarchy
	and NodeID implementations are correct.
*/
class ITreeViewHierarchyAdapter : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITREEVIEWHIERARCHYADAPTER };
	
	/** Accessor for the root node of the tree model. 
		Should return an instance of a node that represents the root node, 
		with data allowing it to be uniquely identified as such.
		@return reference to root node
	*/
	virtual NodeID_rv	GetRootNode() const = 0;

	/** Accessor for the parent node of a given node. If the given node is the root node, this should return nil.
	*/
	virtual NodeID_rv	GetParentNode( const NodeID& node ) const = 0;

	/** Accessor for the number of children given a node that is in the tree-model.
		@node specifies the node of interest
		@return number of children of given node
	*/
	virtual int32		GetNumChildren( const NodeID& node ) const = 0;

	/** When building subtrees, this is called so the client can choose to add this particular node or not.
		In most cases, returning true here is what you want.
		@param node specifies the parent node
		@param nth specifies index of child to choose
		@return if the node should be added to the tree or not
	*/
	virtual bool16		ShouldAddNthChild( const NodeID& node, const int32& nth ) const = 0;

	/** Accessor for a child of a given node by index.
		@param node specifies the parent node
		@param nth specifies index of child to choose
		@return reference to the child at the given index
	*/
	virtual NodeID_rv	GetNthChild( const NodeID& node, const int32& nth ) const = 0;

	/** Accessor to determine the index of a given child node in its parent's collection of children.
		@param parent specifies the parent node whose child we are querying about
		@param child specifies child of interest
		@return index of given child in parent's collection, (-1) if not in collection
	*/
	virtual int32		GetChildIndex( const NodeID& parent, const NodeID& child ) const = 0;

	/** Return a dummy node that can be used as a generic node anywhere in the tree. 
		@return reference to a generic node
	*/
	virtual NodeID_rv	GetGenericNodeID() const = 0;

};	

#endif // __ITreeViewMgr__
