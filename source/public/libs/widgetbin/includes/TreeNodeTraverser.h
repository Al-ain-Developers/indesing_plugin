//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/TreeNodeTraverser.h $
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
#ifndef __TreeNodeTraverser__
#define __TreeNodeTraverser__

#include "ITreeViewMgr.h"
#include "K2Stack.h"
#include "K2Vector.h"
#include "NodeID.h"

class ITreeViewMgr;

// This is a help class used by the TreeNodeTraverser class.  It really has no use on its own.
class TreeNodeHelper
{
	public:
		typedef base_type data_type;
		TreeNodeHelper(const ITreeViewMgr* treeMgr, const NodeID&	node, bool16 expandedNodesOnly, bool16 reverse = kFalse, int32 index = -1);
		~TreeNodeHelper();
				
		NodeID			GetNextNode(const ITreeViewMgr* treeMgr);
		const NodeID&		GetNode() const;
		
	private:
		NodeID	fNode;
		int32			fIndex;
		bool16			fReverse;
		bool16			fExpandedOnly;
};


//========================================================================================
// CLASS TreeNodeTraverser
//========================================================================================
#pragma export on

/** TreeNodeTraverser is a class that helps a client walk thru the tree hierarchy of a TreeView Widget.
	It uses the ITreeViewHierarchyAdapter on the kTreeViewWidgetBoss to traverse the tree from a given
	node in the tree.  You choose a node in the tree and then can go from that node to the next node
	in the tree, either going up or down the tree hierarchy.  You can also decide whether to go into unexpanded
	nodes or to just visit the "visible" nodes.

	An example usage is shown below...

<pre>
	TreeNodeTraverser	traverse(startNode, treeMgr, kTrue, TreeNodeTraverser::eForward );
	NodeID	next;
	while (!traverse.Completed())
	{
		next = traverse.Next();

		// Do your stuff here
	}
</pre>

	*/
class DV_WIDGET_DECL TreeNodeTraverser 
{
// ----- Constructors/desctructors
public:
    enum Direction { eForward, eReverse };

	/** 
		Create a TreeNodeTraverser for traversing the nodes in the specified tree
		@param from which node in th etree you would like to start your traversal from.  You can start from any node in the tree
		@param treeMgr the ITreeViewMgr interface of the TreeView widget you are traversing
		@param expandedNodesOnly if kTrue, only visible nodes are returned.  if kFalse, all nodes in the tree are returned, even those not visible because their parent is closed
		@param direction eForward will go forward(or down) the tree hierarchy.  eReverse will go backwards(or up) the hierarchy
	*/
	TreeNodeTraverser(const NodeID& from, const ITreeViewMgr* treeMgr, bool16 expandedNodesOnly, Direction direction = eForward);	
	/** 
		Destructor.  Nothing special to note
	*/
	virtual ~TreeNodeTraverser();

	/** 
		Move to the next node in the tree.  Calling this the first time will move from the start node to the next node above or below
		the start node.  i.e. If you had a root element called 'Root' and 3 child elements, 'A', 'B', and 'C' and you were starting with 'A', 
		calling Next() would return 'B' if going forward and it would return 'Root' if going backward.
		@return NodeID of the next node
	*/
	virtual NodeID		Next();

	/** 
		Determine whether or not the traversal has reached the last node in the tree.  For a reverse traversal, last node would be the root node.
		This is typically used in a loop, for example...
		
		while (!traverse.Completed()) { // your code here }

		@return kTrue if traversal has completed, kFalse if there are mmore nodes to traverse
	*/
	virtual bool16				Completed() const;

	private:
		void			ClearStack();
		
		NodeID	fCurrentNode;
		bool16			fExpandedNodesOnly;
		Direction		fDirection;
		K2Vector<TreeNodeHelper*>	fStack;
		const ITreeViewMgr*	fTreeMgr;
};

#pragma export off

#endif
