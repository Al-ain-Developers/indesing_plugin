//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITreeViewMgr.h $
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
#ifndef __ITreeViewMgr__
#define __ITreeViewMgr__

#include "IPMUnknown.h"
#include "widgetid.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class IControlView;
class NodeID;
class NodeID_rv;
//----------------------------------------------------------------------------------------
// ITreeViewMgr
//----------------------------------------------------------------------------------------

/** Interface to keep the tree-view synchronised with changes to
	the tree-model. 

	Client code should call methods in this interface to let the tree know when
	changes to the tree have occurred. For instance, client code should call ChangeRoot() to initialize the treeview
	control. 
*/
class INTERFACE_DECL ITreeViewMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITREEVIEWMGR };
	
	/**
		Call this method to initialize the tree, using the ITreeViewHierarchyAdapter.
		Call this if you want the tree to repopulate it's widgets.  Node expansion will be preserved 
		unless the root node is different.  If you don't want node expansion preserved, you must call ClearTree(kTrue)
		before calling ChangeRoot()
	
		Debug version of ChangeRoot() which had a test parameter has been removed.  To get the Tree validation, use
		the test menu item Test > UI > Enable TreeView Validation to turn on TreeView debugging code.  Enabling this will
		help you find bugs in your NodeID and ITreeViewHierarchyAdapter implementations.

		@param widgetHeightIsConstant if all of the widgets that will be created in your tree will have the same height,
		set widgetHeightIsConstant to kTrue to improve performance
	*/
	virtual void		ChangeRoot( bool16 widgetHeightIsConstant = kFalse ) = 0;		

	/** This should be called after the node has been added
		@param nodeAdded
	*/
	virtual void		NodeAdded( const NodeID& nodeAdded ) = 0;
	
	/** This should be called after a collection of nodes have been added
		@param nodesAdded
	*/
	virtual void		NodesAdded( const K2Vector<NodeID>&	nodesAdded ) = 0;		

	/** This must be called before the object is actually deleted, so we can get it's size
		@param nodeDeleted
	*/
	virtual void		BeforeNodeDeleted( const NodeID& nodeDeleted ) = 0;	
	
	/** Call this method before a collection of nodes are to be removed from the tree. 
		This method has a K2Vector parameter that is non-const, because the nodes in this collection
		will be sorted after use	

		@param nodesDeleted nodes about to be deleted, 
		@postcondition the nodesDeleted vector will be sorted 
	*/
	virtual void		BeforeNodesDeleted( K2Vector<NodeID>& nodesDeleted ) = 0;	


	/** This should be called when a node has moved to a new location.  
		Do not call this if the height of the widget may have
		also changed.  In that case, you'll have to use BeforeNodeDeleted and NodeAdded

		@param nodeMoved
		@param oldParent
	*/
	virtual void		NodeMoved( const NodeID& nodeMoved, const NodeID& oldParent ) = 0;		

	//
	/** This should only be called for a node whose height will not change.  If the height could change
		call delete and then add

		@param nodeChanged
		@param childrenChangedAlso
		@param message
	*/
	virtual void		NodeChanged( const NodeID& nodeChanged, bool16 childrenChangedAlso = kFalse, int32 message = 0 ) = 0;		

	typedef enum { eScrollToTop, eScrollToMiddle, eScrollIntoView, eScrollToShowChildren } ScrollWhere;

	/** This allows a certain node to be scrolled into view, ancestors will be expanded to make node visible
		@param scrollToNode
		@param whereToScroll
	*/
	virtual void		ScrollToNode( const NodeID& scrollToNode, ScrollWhere	whereToScroll ) = 0;		

	/** Determine if given node is expanded.
		@param nodeInQuestion node of interest
		@return kTrue if node is expanded, kFalse otherwise
	*/
	virtual bool16		IsNodeExpanded( const NodeID& nodeInQuestion ) const = 0;	
	
	/** Determine if given node is expanded.
		@param widget the corresponding widget that is responsible for rendering a node
		@return kTrue if node is expanded, kFalse otherwise
	*/
	virtual bool16		IsNodeExpanded(IControlView* widget) const = 0;	
	/** Method to expand node and optionally all its descendants.

		@param nodeToExpand specifies node that is to be expanded
		@param expandAllDescendants kTrue if all descendants are to be expanded also, 
		kFalse to restrict expansion to immediate children
	*/
	virtual void		ExpandNode( const NodeID& nodeToExpand, bool16 expandAllDescendants = kFalse ) = 0;	
	/** Method to collapse given node and optionally collapse all the descendants

		@param nodeToCollapse specifies node that is to be collapsed
		@param collapseAllDescendants kFalse if only immediate children to be collapsed, kTrue if all descendants to be collapsed
	*/
	virtual void		CollapseNode( const NodeID& nodeToCollapse, bool16 collapseAllDescendants = kFalse  ) = 0;	

	/** This is typically only called by the scroll bar event handler/ resize widget
	*/
	virtual void		HandleScroll( int32 amount, bool16 up ) = 0;

	/** This is typically only called by the scroll bar event handler/ resize widget
	*/
	virtual	void		HandleResize() = 0;

	/** Would scroll up as if you had clicked in the scroll bar between the thumb and end buttons.
	*/
	virtual	void		ScrollUp() = 0;

	/** Would scroll down as if you had clicked in the scroll bar between the thumb and end buttons.
	*/
	virtual	void		ScrollDown() = 0;

	/** This method is used with typeahead to search for the first node in the tree that begins with  
		'partialNodeName'.  TreeView must have ITreeViewTypeAhead interface for this to do anything useful
		@param search the tree for a node whose text representation starts with 'partialNodeName'
		@return first node in the tree that begins with 'partialNodeName', or kInvalidNodeID if no match is found
	*/
	virtual	NodeID_rv	Search( const PMString& partialNodeName ) const = 0;
	
	/** This method is used to determine if a node has been loaded in the tree widget.
		@param nodeToSearch search the tree for a node with this ID
		@return the node, or kInvalidNodeID if no match is found
	*/
	virtual	NodeID_rv	Search( const NodeID& nodeToSearch ) const = 0;
	
	/** Call this to remove all the widgets.  This is the same as calling ChangeRoot() when the TreeViewHierarchy
		will return nil for QueryRootNode().  It makes the tree empty and breaks the connection between the tree and it's root
		You need to call ChangeRoot() again for a new connection to be established.  
		By default, the list of expanded nodes will not be cleared.  To clear the list of expanded nodes, 
		set clearExpandedNodeList	to kTrue.  
	*/
	virtual	void		ClearTree( bool16 clearExpandedNodeList = kFalse ) = 0;

	//
	/** Utility function to get the widget for a particular node.  There is no guarantee that a widget will exist though.  This call is rarely what you want.
		It will return nil in cases where the node in question is not visible in the tree, or when the tree has changed and the widgets have
		not yet been rearranged.  Call NodeChanged() if you want to update data in a node.  Typically, this is only called in response to mouse
		events.
	*/
	virtual IControlView* QueryWidgetFromNode( const NodeID& node ) const = 0;	

	/**
	*/
	virtual	void		Purge(int32 level) = 0;

	/** When a subtree has changed significantly or when you aren't sure of the nodes added/removed,
		you can call this method to regenerate the tree below the specified node
		@param the node at the top of the subtree you want refreshed
		@param false will only fix up the imediate children ignoring all grandchildren
	*/
	virtual	void		RefreshSubTree(const NodeID& subTreeRoot, bool16 includeEntireHier = kTrue) = 0;

	// These methods are for the other TreeMgr interfaces and shouldn't be called by client code
	virtual	void		ArrangeWidgets() = 0;

	/**
	// Returns a rectangle in scroller coordinates that represents the viewable area on the scrollable
	// canvas.
	*/
	virtual PMRect		GetViewableArea() = 0;

	/**
	// Returns a rectangle that specify the size needed for whole tree to draw without scrollbar
	*/
	virtual PMPoint		GetSizeNeededWihtoutScrollbar() = 0;

    /**
       Scroll the tree view widget vertically with a specified amount in pixels
     */
	virtual void		ScrollVerticalAbsoluteAmount(int32 amount, bool16 forceRedraw = kTrue) = 0;
};	





#endif // __ITreeViewMgr__
