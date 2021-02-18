//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltextui/CusCondTreeViewAdapter.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Interface includes:
#include "IActiveContext.h"
#include "IWorkspace.h"
#include "IUIDData.h"
#include "IConditionalTextFacade.h"
#include "IConditionTagList.h"

// General includes
#include "ListTreeViewAdapter.h"
#include "Utils.h"
#include "UIDNodeID.h"

// Project includes:
#include "CusCondTxtNodeID.h"
#include "CusCondTxtUIID.h"

/**
 *  TreeViewAdapter.
	@ingroup customconditionaltext
 */
class  CusCondTxtTreeViewAdapter: public ListTreeViewAdapter
{
public:
	CusCondTxtTreeViewAdapter(IPMUnknown* boss);
	
	virtual ~CusCondTxtTreeViewAdapter()
	{}
	virtual NodeID_rv	GetRootNode() const;
	virtual NodeID_rv	GetParentNode(const NodeID& node) const;
	virtual int32		GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv	GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32		GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv	GetGenericNodeID() const;
private:
	IDataBase* GetDataBase() const;

};

CREATE_PMINTERFACE(CusCondTxtTreeViewAdapter, kCusCondTxtUITreeViewHierarchyAdapterImpl)

/* Constructor
*/
CusCondTxtTreeViewAdapter::CusCondTxtTreeViewAdapter(IPMUnknown* boss) : ListTreeViewAdapter(boss)
{
}

/*GetRootNode
*/
NodeID_rv CusCondTxtTreeViewAdapter::GetRootNode() const
{
	do{
		IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
		if (context == nil)
		{
			ASSERT_FAIL("IActiveContext is invalid");
			break;
		}
		
		IWorkspace *ws = context->GetContextWorkspace();
		if (ws == nil)
		{
			ASSERT_FAIL("IWorkspace is invalid");
			break;
		}

		InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(::GetDataBase(ws)));
		if (tagList)
			return UIDNodeID::Create(::GetUID(tagList));
	} while(false);

	return kInvalidNodeID;
} 

/*GetParentNode
*/
NodeID_rv CusCondTxtTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	do{
		IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
		if (context == nil)
		{
			ASSERT_FAIL("IActiveContext is invalid");
			break;
		}
		IWorkspace *ws = context->GetContextWorkspace();
		if (ws == nil)
		{
			ASSERT_FAIL("IWorkspace is invalid");
			break;
		}
		InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(::GetDataBase(ws)));
		
		// If the taglist is passed in, the parent is nil. Otherwise, the parent must be the taglist.
		TreeNodePtr<UIDNodeID>	uidNodeID(node);
		if (::GetUID(tagList) == uidNodeID->GetUID())
			return kInvalidNodeID;

		return UIDNodeID::Create(::GetUID(tagList));

	} while(false);
		
	return kInvalidNodeID;
} 

/*GetNumChildren
*/
int32 CusCondTxtTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	int32 numChildren(0);
	do{

		IDataBase* db = GetDataBase();
		if (db == nil)
		{
			ASSERT_FAIL("IDataBase is invalid");
			break;
		}
		
		UID uid = TreeNodePtr<UIDNodeID>(node)->GetUID();
		if (node == this->GetRootNode())
		{
			InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
			if (tagList == nil)
			{
				ASSERT_FAIL("IConditionTagList is invalid");
				break;
			}
			numChildren = tagList->GetCount();
		}

	} while(false);

	return numChildren;
} // end GetNumChildren()

/*GetNthChild
*/
NodeID_rv CusCondTxtTreeViewAdapter::GetNthChild(const NodeID& node, const int32& nth) const
{
	do{

		IDataBase* db = GetDataBase();
		if (db == nil)
		{
			ASSERT_FAIL("IDataBase is invalid");
			break;
		}

		UID uid = TreeNodePtr<UIDNodeID>(node)->GetUID();
		UID childUID(kInvalidUID);
		if (node == this->GetRootNode())
		{
			InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
			if (tagList == nil)
			{
				ASSERT_FAIL("IConditionTagList is invalid");
				break;
			}
			childUID = tagList->GetNthCondition(nth);
		}

		if (childUID != kInvalidUID)
			return UIDNodeID::Create(childUID);

	} while(false);

	return kInvalidNodeID;
} // end GetNthChild()

/*GetChildIndex
*/
int32 CusCondTxtTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	int32 index(-1);
	do {

		IDataBase* db = GetDataBase();
		if (db == nil)
		{
			ASSERT_FAIL("IDataBase is invalid");
			break;
		}
		
		UID parentUID = TreeNodePtr<UIDNodeID>(parent)->GetUID();
		UID childUID = TreeNodePtr<UIDNodeID>(child)->GetUID();;
		if (parent == this->GetRootNode())
		{
			InterfacePtr<const IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
			if (tagList == nil)
			{
				ASSERT_FAIL("IConditionTagList is invalid");
				break;
			}
			for (int32 i = 0; i < tagList->GetCount(); ++i)
			{
				if (tagList->GetNthCondition(i) == childUID)
				{
					index = i;
					break;
				}
			}
		}
	} while(false);	

	return index;
} 

/*GetGenericNodeID
*/
NodeID_rv CusCondTxtTreeViewAdapter::GetGenericNodeID() const
{
	return UIDNodeID::Create(kInvalidUID);	
}

/*GetDataBase
*/
IDataBase*  CusCondTxtTreeViewAdapter::GetDataBase() const
{
	IDataBase* db = nil;
	do {
		IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
		if (context == nil)
		{
			ASSERT_FAIL("IActiveContext is invalid");
			break;
		}

		IWorkspace *ws = context->GetContextWorkspace();
		if (ws == nil)
		{
			ASSERT_FAIL("IWorkspace is invalid");
			break;
		}
		
		db = ::GetDataBase(ws);
		if (db == nil)
		{
			ASSERT_FAIL("IDataBase is invalid");
			break;
		}	

	} while(false);

	return db;
}