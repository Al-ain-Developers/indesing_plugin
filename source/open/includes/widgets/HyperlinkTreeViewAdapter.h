//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/HyperlinkTreeViewAdapter.h $
//  
//  Owner: Kaustubh Bansal
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  Copyright 2016 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================
#pragma once

#ifndef __HYPERLINKTREEVIEWADAPTER__
#define __HYPERLINKTREEVIEWADAPTER__

class HyperlinkTreeViewAdapter : public ITreeViewHierarchyAdapter
{
public:
	HyperlinkTreeViewAdapter(IPMUnknown *boss);
	~HyperlinkTreeViewAdapter();

	virtual NodeID_rv    GetRootNode() const;
	virtual NodeID_rv    GetParentNode(const NodeID& node) const;
	virtual int32        GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv    GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32        GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv    GetGenericNodeID() const;
	virtual bool16       ShouldAddNthChild(const NodeID& node, const int32& nth) const { return kTrue; }

	// Adding this function to clear internal state when the tree is otherwise cleared on closing the panel
	// Since it is not a part of ITreeViewHierarchyAdapter, to call this the interface pointer will have to be dynamically cast.
	void ClearTreeVector();

private:
	IDataBase*			GetDataBase() const;

	mutable PanelUIDs fTreeVector;

	PanelUIDs GetVector() const;

	DECLARE_HELPER_METHODS()
};

#endif // __HYPERLINKTREEVIEWADAPTER__