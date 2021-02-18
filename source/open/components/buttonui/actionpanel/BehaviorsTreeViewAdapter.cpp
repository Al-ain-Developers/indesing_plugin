//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorsTreeViewAdapter.cpp $
//  
//  Owner: Michael Burbidge
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

#include "IBehaviorSuite.h"
#include "IFormFieldSuite.h"
#include "ISelectionDataSuite.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewMgr.h"

#include "FormFieldUIUtils.h"
#include "SelectionUtils.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "FormFieldUIID.h"
#include "CPMUnknown.h"
#include "NodeID.h"
#include "UIDNodeID.h"


//========================================================================================
// CLASS BehaviorsTreeViewAdapter
//========================================================================================

class BehaviorsTreeViewAdapter : public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	BehaviorsTreeViewAdapter(IPMUnknown *boss);

	virtual NodeID_rv			GetRootNode() const;
	virtual NodeID_rv			GetParentNode(const NodeID& node) const;
	virtual int32				GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv			GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32				GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv			GetGenericNodeID() const;
	virtual bool16				ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }
};

//========================================================================================
// IMPLEMENTATION BehaviorsTreeViewAdapter
//========================================================================================

CREATE_PMINTERFACE(BehaviorsTreeViewAdapter, kBehaviorsTreeViewAdapterImpl)

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewAdapter constructor
//----------------------------------------------------------------------------------------

BehaviorsTreeViewAdapter::BehaviorsTreeViewAdapter(IPMUnknown *boss) :
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewAdapter::GetRootNode
//----------------------------------------------------------------------------------------

NodeID_rv BehaviorsTreeViewAdapter::GetRootNode() const
{
	return UIDNodeID::Create(kInvalidUID);
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewAdapter::GetParentNode
//----------------------------------------------------------------------------------------

NodeID_rv BehaviorsTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	NodeID root =  this->GetRootNode();
	if (node == root)
		return kInvalidNodeID;

	return root;
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewAdapter::GetNumChildren
//----------------------------------------------------------------------------------------

int32 BehaviorsTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	int32 count = 0;

	if (node == this->GetRootNode())
	{
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		InterfacePtr<ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISELECTIONDATASUITE)));
		bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;

		if (isSingleSelection && iFormFieldSuite && iFormFieldSuite->IsFieldSelection() && !iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss) )
		{
			InterfacePtr<IBehaviorSuite> behaviorSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
			if (behaviorSuite)
			{
				IDataBase* db;
				std::vector<UID> behaviors;	

				ActionEvent currentEvent = FormFieldUIUtils::GetSelectedEvent(this);
				behaviorSuite->GetActions(currentEvent, db, behaviors);
				count = static_cast<int32>(behaviors.size());
			}
		}
	}

	return count;
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewAdapter::GetNthChild
//----------------------------------------------------------------------------------------

NodeID_rv BehaviorsTreeViewAdapter::GetNthChild(const NodeID& node, const int32& nth) const
{
	ASSERT_MSG(node == this->GetRootNode(), "BehaviorsTreeViewAdapter::GetNthChild - This should only be called for root node.");

	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
	InterfacePtr<ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISELECTIONDATASUITE)));
	bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;

	if (isSingleSelection && iFormFieldSuite && iFormFieldSuite->IsFieldSelection() && !iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss) )
	{
		InterfacePtr<IBehaviorSuite> behaviorSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
		if (behaviorSuite)
		{
			IDataBase* db;
			std::vector<UID> behaviors;	

			ActionEvent currentEvent = FormFieldUIUtils::GetSelectedEvent(this);
			behaviorSuite->GetActions(currentEvent, db, behaviors);

			if (behaviors.size() > 0)
			{
				ASSERT(nth <= behaviors.size());

				return UIDNodeID::Create(behaviors[nth]);
			}
		}
	}
	return NodeID_rv(nil);
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------

int32 BehaviorsTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	TreeNodePtr<UIDNodeID>	behaviorNode(child);

	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
	InterfacePtr<ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISELECTIONDATASUITE)));
	bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;

	if (isSingleSelection && iFormFieldSuite && iFormFieldSuite->IsFieldSelection() && !iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss))
	{
		InterfacePtr<IBehaviorSuite> behaviorSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
		if (behaviorSuite)
		{
			IDataBase* db;
			std::vector<UID> behaviors;	

			ActionEvent currentEvent = FormFieldUIUtils::GetSelectedEvent(this);
			behaviorSuite->GetActions(currentEvent, db, behaviors);
			for (int32 i = 0; i < behaviors.size(); ++i)
			{
				if (behaviorNode->GetUID() == behaviors[i])
					return i;
			}
		}
	}
	return -1;
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeViewAdapter::GetGenericNodeID() const
//----------------------------------------------------------------------------------------

NodeID_rv BehaviorsTreeViewAdapter::GetGenericNodeID() const
{
	return UIDNodeID::Create(kInvalidUID);
}
