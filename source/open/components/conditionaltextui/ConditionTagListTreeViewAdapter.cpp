//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagListTreeViewAdapter.cpp $
//  
//  Owner: Michele Stutzman
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

// ----- Interfaces -----

#include "IConditionTagList.h"
#include "IDataBase.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IUIDData.h"

// ----- Includes -----

#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "Utils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionTagListTreeViewAdapter : public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	ConditionTagListTreeViewAdapter(IPMUnknown *boss);
	~ConditionTagListTreeViewAdapter();
	
	virtual NodeID_rv	GetRootNode() const;
	virtual NodeID_rv	GetParentNode(const NodeID& node) const;
	virtual int32		GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv	GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32		GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv	GetGenericNodeID() const;
	virtual bool16		ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }
	
private:
	IDataBase*		GetDataBase() const;
};

// =============================================================================
// *** ConditionTagListTreeViewAdapter impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagListTreeViewAdapter, kConditionTagListTreeViewAdapterImpl)

ConditionTagListTreeViewAdapter::ConditionTagListTreeViewAdapter(IPMUnknown *boss) :
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
} // end constructor

ConditionTagListTreeViewAdapter::~ConditionTagListTreeViewAdapter()
{
} // end destructor

// -----------------------------------------------------------------------------

NodeID_rv ConditionTagListTreeViewAdapter::GetRootNode() const
{
	InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(this->GetDataBase()));
	if (tagList)
		return UIDNodeID::Create(::GetUID(tagList));

	return kInvalidNodeID;
} // end GetRootNode()

// -----------------------------------------------------------------------------

NodeID_rv ConditionTagListTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(this->GetDataBase()));
	
	// If the taglist is passed in, the parent is nil. Otherwise, the parent must be the taglist.
	TreeNodePtr<UIDNodeID>	uidNodeID(node);
	if (::GetUID(tagList) == uidNodeID->GetUID())
		return kInvalidNodeID;
		
	return UIDNodeID::Create(::GetUID(tagList));
} // end GetParentNode()

// -----------------------------------------------------------------------------

int32 ConditionTagListTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	IDataBase* db = this->GetDataBase();
	if (!db)
		return 0;

	//ASSERT_MSG(db != nil, "ConditionTagListTreeViewAdapter::GetNumChildren - database is nil!");

	int32 numChildren(0);
	UID uid = TreeNodePtr<UIDNodeID>(node)->GetUID();
	if (node == this->GetRootNode())
	{
		InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
		ASSERT_MSG(tagList != nil, "ConditionTagListTreeViewAdapter::GetNumChildren - no condition tag list?!");
		numChildren = tagList->GetCount();
	}

	return numChildren;
} // end GetNumChildren()

// -----------------------------------------------------------------------------

NodeID_rv ConditionTagListTreeViewAdapter::GetNthChild(const NodeID& node, const int32& nth) const
{
	IDataBase* db = this->GetDataBase();
	ASSERT_MSG(db != nil, "ConditionTagListTreeViewAdapter::GetNthChild - database is nil!");

	UID uid = TreeNodePtr<UIDNodeID>(node)->GetUID();
	UID childUID(kInvalidUID);
	if (node == this->GetRootNode())
	{
		InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
		ASSERT_MSG(tagList != nil, "ConditionTagListTreeViewAdapter::GetNthChild - no condition tag list?!");
		childUID = tagList->GetNthCondition(nth);
	}

	if (childUID != kInvalidUID)
		return UIDNodeID::Create(childUID);

	return kInvalidNodeID;
} // end GetNthChild()

// -----------------------------------------------------------------------------

int32 ConditionTagListTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	IDataBase* db = this->GetDataBase();
	ASSERT_MSG(db != nil, "ConditionTagListTreeViewAdapter::GetChildIndex - database is nil!");

	int32 index(-1);
	UID parentUID = TreeNodePtr<UIDNodeID>(parent)->GetUID();
	UID childUID = TreeNodePtr<UIDNodeID>(child)->GetUID();;
	if (parent == this->GetRootNode())
	{
		InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
		ASSERT_MSG(tagList != nil, "ConditionTagListTreeViewAdapter::GetNthChild - no condition tag list?!");
		for (int32 i = 0; i < tagList->GetCount(); ++i)
		{
			if (tagList->GetNthCondition(i) == childUID)
			{
				index = i;
				break;
			}
		}
	}
	return index;
} // end GetChildIndex()

// -----------------------------------------------------------------------------

NodeID_rv ConditionTagListTreeViewAdapter::GetGenericNodeID() const
{
	return UIDNodeID::Create(kInvalidUID);	
} // end GetGenericNodeID()

// -----------------------------------------------------------------------------

IDataBase* ConditionTagListTreeViewAdapter::GetDataBase() const
{
	InterfacePtr<const IUIDData> data(this, IID_IUIDDATA);
	return data->GetItemDataBase();
} // end GetDataBase()

