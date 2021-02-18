//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightAggregatedResults.h $
//  
//  Owner: Matt Phillips
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

#include "IPreflightObject.h"
#include "IPMUnknown.h"
#include "IPreflightResultNodeInfo.h"
#include "PackageAndPreflightID.h"

class IPreflightResultNodeInfo;

/** This is an in-memory database of preflight results AFTER the rules and the engine have finished
	finding any/all problems. Generally speaking the results found in the expansion/visitation phase
	are "raw" and need to be consolidated in different ways depending on the rule and where the
	violations occur. That's the purpose of this secondary structure.

	This interface sits on a boss in memory; it's not persistent. Normally this boss is created
	by the preflight process via IPreflightProcess::CreateAggregatedResults(). However, once built
	the interface is no longer dependent on that process. This is to support user interface, which 
	is where this interface usually matters: presenting the results or dumping them to a file
	somewhere, and you need something that's stable even if the document changes and the process
	dumps its internal database and starts over. Having said that you must be careful when asking
	about nodes whose references may be stable (@see IPreflightResultNodeInfo).

	This interface simply provides the structure of the database. More detailed information 
	about each node is obtained via QueryNodeInfo().
*/

class IPreflightAggregatedResults : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTAGGREGATEDRESULTS };

	typedef uint32 NodeID;
	typedef K2Vector<NodeID> NodeIDVector;

public:
	/** Returns whether a node ID is valid.
		@param node IN The node in which you're interested.
		@return kTrue if valid, kFalse if not.
	*/
	virtual bool IsValidID(NodeID node) const = 0;

	/** Return the root node of the results tree.
		@return The ID of the root or 0 if there is no root.
	*/
	virtual NodeID GetRoot() const = 0;

	/** Clear the database back to it default state, a single root node with no children.
	*/
	virtual void Clear() = 0;

	/** Add a node to the database as a child of an existing node. Note that the child is not
		(generally) appended to the child list; it's added according to 
		IPreflightResultNodeInfo::GetSortValue ordering.

		@param parentNode IN The parent node.
		@param iInfo IN The information to associate with the node (will be refcounted).
		@return The node ID of the newly added node.
	*/
	virtual NodeID AddNode(NodeID parentNode, IPreflightResultNodeInfo* iInfo) = 0;

	/** Delete the specified node. Also deletes all children. The refcount is released on 
		the related IPreflightResultNodeInfo.

		CAUTION: This is a limited-use function as the aggregated results are designed 
		primarily for additions, not modifications. In particular the node ID and memory 
		used by the node are not recovered, just marked as no longer used. This may be 
		improved in future versions.

		@param node IN The ID of the node to delete.
	*/
	virtual void DeleteNode(NodeID node) = 0;

	/** Get the parent of a node, if any.
		@param child IN The node you want the parent of.
		@return The parent node ID, or 0 if there is no parent (ie child is invalid or the root).
	*/
	virtual NodeID GetParent(NodeID child) const = 0;

	/** Get the number of child nodes.
		@param child IN The node you're interested in.
		@return The number of children of the node; 0 if none or error.
	*/
	virtual int32 GetNumChildren(NodeID parent) const = 0;

	/** Get the first child of a node.
		@param node IN The node you want the child of.
		@return The ID of the first child node, or 0 if unsuccessful.
	*/
	virtual NodeID GetFirstChild(NodeID node) const = 0;

	/** Get the next sibling of a node.
		@param node IN The node you want the next sibling of.
		@return The ID of the next sibling node, or 0 if unsuccessful.
	*/
	virtual NodeID GetNextSibling(NodeID node) const = 0;

	/** Given a node ID, return the index of that node in the parent's child list. This is simply 
		a convenience method based on GetParent, GetFirstChild, etc.

		@param parent IN The parent node.
		@param child IN The child node.
		@return The index of the child in the parent, or -1 if the child is not a child of the parent.
	*/
	virtual int32 GetChildIndex(NodeID parent, NodeID child) const = 0;

	/** Get the depth of the hierarchy. The depth of the root is zero; all others are indexed
		from there. This is simply a convenience method based on GetParent().

		@return The depth of the node in the hierarchy.
	*/
	virtual int32 GetHierarchyDepth(NodeID node) const = 0;
	
	/** Given a node, get the preflight result interface for more information about that node.
		@param node IN The ID of the node in which you're interested.
		@return A refcounted information node, or nil if unsuccessful. Not all nodes will have
			information, but in practice the only node that shouldn't is the root node. Note that
			the returned interface won't usually be boss-based but rather a simple structure.
			Nevertheless it still follows IPMUnknown rules for lifecycle management -- that is,
			you MUST dereference it when you're done!
	*/
	virtual IPreflightResultNodeInfo* QueryNodeInfo(NodeID node) const = 0;

	/** General-case method for obtain child/descendent information that saves you the trouble
		of looping over the enumerators above.

		@param parentNode IN The node whose children/descendents you're interested in.
		@param nodeType IN The node type to filter by, or kInvalid to not filter by node type.
		@param recursive IN True to recurse (ie, all descendents) or false to only consider immediate children.
		@param pNodes OUT If not nil, receives the list of matching child nodes.
		@return The number of matching nodes.
	*/
	virtual uint32 GetChildren
		(
			IPreflightAggregatedResults::NodeID parentNode,
			IPreflightResultNodeInfo::NodeType nodeType = IPreflightResultNodeInfo::kInvalid,
			bool recursive = kFalse,
			NodeIDVector* pNodes = nil
		) const = 0;

	/** Copy nodes from another results tree into this one. Note that this does only reference
		counting on the child nodes, not a true data copy.

		@param dstParentNode IN The parent node in THIS tree under which the nodes from the
			source tree should be copied.
		@param iSrcResults IN The tree from which nodes should be copied.
		@param srcRootNode IN The root node at which to start copying.
		@param copyRootNode IN True to copy the root node; false to copy only its children.
		@return The number of nodes actually copied.
	*/
	virtual int32 CopyNodesFrom
		(
			IPreflightAggregatedResults::NodeID dstParentNode,
			const IPreflightAggregatedResults* iSrcResults,
			IPreflightAggregatedResults::NodeID srcRootNode,
			bool copyRootNode
		) = 0;
};

