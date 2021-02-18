//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/treeview/ListTreeViewAdapter.cpp $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#include "VCWidgetHeaders.h"

// ----- Interfaces -----

#include "ListTreeViewAdapter.h"
#include "NodeID.h"

// ----- Includes -----

#include "HelperInterface.h"
#include "ListIndexNodeID.h"

DEFINE_HELPER_METHODS(ListTreeViewAdapter)

//----------------------------------------------------------------------------------------
// ListTreeViewAdapter constructor
//----------------------------------------------------------------------------------------

ListTreeViewAdapter::ListTreeViewAdapter(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)
{
}


//----------------------------------------------------------------------------------------
// ListTreeViewAdapter::~ListTreeViewAdapter 
//----------------------------------------------------------------------------------------

ListTreeViewAdapter::~ListTreeViewAdapter()
{
}

//----------------------------------------------------------------------------------------
// ListTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------
int32 ListTreeViewAdapter::GetNumListItems() const
{
	return 10;
}

//----------------------------------------------------------------------------------------
// ListTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------
NodeID_rv ListTreeViewAdapter::GetNthListItem(const int32& nth) const
{
	return ListIndexNodeID::Create(nth);
}

//----------------------------------------------------------------------------------------
// ListTreeViewAdapter::GetRootNode 
//----------------------------------------------------------------------------------------
NodeID_rv ListTreeViewAdapter::GetRootNode() const
{
	return ListIndexNodeID::RootNodeID();	
}

//----------------------------------------------------------------------------------------
// ListTreeViewAdapter::GetParentNode 
//----------------------------------------------------------------------------------------
NodeID_rv ListTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	NodeID root = this->GetRootNode();
	if ( node == root )
		return kInvalidNodeID;
		
	return root;
}

//----------------------------------------------------------------------------------------
// ListTreeViewAdapter::GetNumChildren 
//----------------------------------------------------------------------------------------
int32 ListTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	// In a list, only the root node has children
	if (node == this->GetRootNode())
		return this->GetNumListItems();
	
	return 0;
}

//----------------------------------------------------------------------------------------
// ListTreeViewAdapter::GetNthChild
//----------------------------------------------------------------------------------------
NodeID_rv ListTreeViewAdapter::GetNthChild(const NodeID& node, const int32& nth) const
{
	ASSERT_MSG(node == this->GetRootNode(), "ListTreeViewAdapter::GetNthChild - This should only be called for root node");

	return this->GetNthListItem(nth);
}

//----------------------------------------------------------------------------------------
// ListTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------
int32 ListTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	int32 count = this->GetNumListItems();		
	for (int32 i = 0; i < count; i++)
	{
		if ( this->GetNthListItem(i) == child)	
			return i;
	}
	return -1;
}

//----------------------------------------------------------------------------------------
// GetGenericNodeID() const
//----------------------------------------------------------------------------------------
NodeID_rv ListTreeViewAdapter::GetGenericNodeID() const
{
	return GetRootNode();	
}


