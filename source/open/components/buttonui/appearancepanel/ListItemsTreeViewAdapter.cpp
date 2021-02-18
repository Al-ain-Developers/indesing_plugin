//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ListItemsTreeViewAdapter.cpp $
//  
//  Owner: Reena Agrawal
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

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IFormFieldSuite.h"
#include "ITreeViewHierarchyAdapter.h"
#include "FormFieldUIUtils.h"
#include "SelectionUtils.h"

// ----- Implementation Includes -----

#include "FormFieldUIID.h"
#include "NodeID.h"
#include "IntNodeID.h"

//========================================================================================
// CLASS ListItemsTreeViewAdapter
//========================================================================================

class ListItemsTreeViewAdapter : public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	ListItemsTreeViewAdapter(IPMUnknown *boss);

	enum { kRootNode = -1, kGenericNode = -2 };

	virtual NodeID_rv			GetRootNode() const;
	virtual NodeID_rv			GetParentNode(const NodeID& node) const;
	virtual int32				GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv			GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32				GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv			GetGenericNodeID() const;
	virtual bool16				ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }
};

//========================================================================================
// IMPLEMENTATION ListItemsTreeViewAdapter
//========================================================================================

CREATE_PMINTERFACE(ListItemsTreeViewAdapter, kListItemsTreeViewAdapterImpl)

//----------------------------------------------------------------------------------------
// ListItemsTreeViewAdapter constructor
//----------------------------------------------------------------------------------------

ListItemsTreeViewAdapter::ListItemsTreeViewAdapter(IPMUnknown *boss) :
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewAdapter::GetRootNode
//----------------------------------------------------------------------------------------

NodeID_rv ListItemsTreeViewAdapter::GetRootNode() const
{
	return IntNodeID::Create(kRootNode);
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewAdapter::GetParentNode
//----------------------------------------------------------------------------------------

NodeID_rv ListItemsTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	TreeNodePtr<IntNodeID>	intNode(node);
	
	if (intNode->Get() != kRootNode)
		return IntNodeID::Create(kRootNode);
	else
		return NodeID_rv(nil);
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewAdapter::GetNumChildren
//----------------------------------------------------------------------------------------

int32 ListItemsTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	Form::ChoiceList choices;
	if (node == this->GetRootNode())
	{
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());

		// Check if its a combo or a list field
		if (iFormFieldSuite && (iFormFieldSuite->IsFieldSelectionOfType(kComboBoxItemBoss) || iFormFieldSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss) ))
		{			
			iFormFieldSuite->GetChoiceList(choices);
		}
	}
	return choices.size();
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewAdapter::GetNthChild
//----------------------------------------------------------------------------------------

NodeID_rv ListItemsTreeViewAdapter::GetNthChild(const NodeID& node, const int32& nth) const
{
	TreeNodePtr<IntNodeID> intNode(node);
	
	ASSERT(intNode->Get() == kRootNode);
	
	return IntNodeID::Create(nth);
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------

int32 ListItemsTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	TreeNodePtr<IntNodeID> parentNode(parent);
	TreeNodePtr<IntNodeID> childNode(child);
	
	ASSERT(parentNode->Get() == kRootNode);
	ASSERT(childNode->Get() != kRootNode);

	return childNode->Get();
}

//----------------------------------------------------------------------------------------
// ListItemsTreeViewAdapter::GetGenericNodeID() const
//----------------------------------------------------------------------------------------

NodeID_rv ListItemsTreeViewAdapter::GetGenericNodeID() const
{
	return IntNodeID::Create(kGenericNode);
}
