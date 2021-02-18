//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelTreeViewAdapter.cpp $
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

#include "IAppearanceSuite.h"
#include "IFormFieldSuite.h"
#include "ITreeViewHierarchyAdapter.h"

// ----- Includes -----

#include "MSOStateNodeID.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelTreeViewAdapter : public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	MSOPanelTreeViewAdapter(IPMUnknown *boss);
	~MSOPanelTreeViewAdapter();
	
	virtual NodeID_rv	GetRootNode() const;
	virtual NodeID_rv	GetParentNode(const NodeID& node) const;
	virtual int32		GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv	GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32		GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv	GetGenericNodeID() const;
	virtual bool16		ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }
};

// =============================================================================
// *** MSOPanelTreeViewAdapter impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelTreeViewAdapter, kMSOPanelTreeViewAdapterImpl)

MSOPanelTreeViewAdapter::MSOPanelTreeViewAdapter(IPMUnknown *boss) :
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
} // end constructor

MSOPanelTreeViewAdapter::~MSOPanelTreeViewAdapter()
{
} // end destructor

// -----------------------------------------------------------------------------

NodeID_rv MSOPanelTreeViewAdapter::GetRootNode() const
{
	return MSOStateNodeID::Create(Form::kStateInvalid);
} // end GetRootNode()
	
// -----------------------------------------------------------------------------

NodeID_rv MSOPanelTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	if (node == this->GetRootNode())
		return kInvalidNodeID;
	else
		return this->GetRootNode();
} // end GetParentNode()

// -----------------------------------------------------------------------------

int32 MSOPanelTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	if (node == GetRootNode())
	{
		InterfacePtr<IFormFieldSuite> formFieldSuite(FormFieldUIUtils::QueryFormSuite());
		InterfacePtr<IAppearanceSuite> appearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
		if (formFieldSuite && formFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss) && appearanceSuite)
			return appearanceSuite->NumStates();
	}
	return 0;
} // end GetNumChildren()

// -----------------------------------------------------------------------------

NodeID_rv MSOPanelTreeViewAdapter::GetNthChild(const NodeID& parentTreeNode, const int32& nth) const
{
	if (parentTreeNode == this->GetRootNode())
	{
		InterfacePtr<IAppearanceSuite> appearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
		if (appearanceSuite)
			return MSOStateNodeID::Create(appearanceSuite->GetNthState(nth));
	}

	return MSOStateNodeID::Create(Form::kStateInvalid);
} // end GetNthChild()

// -----------------------------------------------------------------------------

int32 MSOPanelTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	if (parent == this->GetRootNode())
	{
		InterfacePtr<IAppearanceSuite> appearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
		if (appearanceSuite)
		{
			TreeNodePtr<const MSOStateNodeID> childStateNode(child);

			int32 numStates = appearanceSuite->NumStates();
			for (int32 i=0; i < numStates; ++i)
			{
				if (appearanceSuite->GetNthState(i) == childStateNode->GetAppearance())
					return i;
			}
		}
	}

	return -1;
} // end GetChildIndex()

// -----------------------------------------------------------------------------

NodeID_rv MSOPanelTreeViewAdapter::GetGenericNodeID() const
{
	return MSOStateNodeID::Create(Form::kStateInvalid);	
} // end GetGenericNodeID()

