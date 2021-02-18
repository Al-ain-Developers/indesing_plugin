//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/resetform/FieldSelectionTreeViewAdptr.cpp $
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

#include "IFieldSelectionTreeViewAdptr.h"
#include "ITreeViewMgr.h"
#include "IFormField.h"
#include "IGraphicStyleDescriptor.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "CPMUnknown.h"
#include "IntNodeID.h"
#include "AttributesUtils.h"

//========================================================================================
// CLASS FieldSelectionTreeViewAdapter
//========================================================================================

class FieldSelectionTreeViewAdapter : public CPMUnknown<IFieldSelectionTreeViewAdapter>
{
public:
	FieldSelectionTreeViewAdapter(IPMUnknown *boss);
	
	enum { kRootNode = -1, kGenericNode = -2 };
		
	virtual NodeID_rv			GetRootNode() const;
	virtual NodeID_rv			GetParentNode(const NodeID& node) const;
	virtual int32				GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv			GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32				GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv			GetGenericNodeID() const;

	virtual void		Set(IDataBase* db, const K2Vector< K2Pair<UID, bool16> >& fields);
	virtual K2Vector< K2Pair<UID, bool16> > Get() const;
	
	virtual IDataBase*			GetDataBase() const { return fDb; }

	virtual PMString GetFieldName(const NodeID& node) const;

	virtual void		SetSelected(const NodeID& node, const bool16& selected);
	virtual bool16 		GetSelected(const NodeID& node) const;

private:
	IDataBase* fDb;
	K2Vector< K2Pair<UID, bool16> > fFields;
};

//========================================================================================
// IMPLEMENTATION FieldSelectionTreeViewAdapter
//========================================================================================

CREATE_PMINTERFACE(FieldSelectionTreeViewAdapter, kFieldSelectionTreeViewAdapterImpl)

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter constructor
//----------------------------------------------------------------------------------------

FieldSelectionTreeViewAdapter::FieldSelectionTreeViewAdapter(IPMUnknown *boss) :
	CPMUnknown<IFieldSelectionTreeViewAdapter>(boss)
{
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::GetRootNode 
//----------------------------------------------------------------------------------------

NodeID_rv FieldSelectionTreeViewAdapter::GetRootNode() const
{
	return IntNodeID::Create(kRootNode);
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::GetParentNode 
//----------------------------------------------------------------------------------------

NodeID_rv FieldSelectionTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	TreeNodePtr<IntNodeID>	intNode(node);
	
	if (intNode->Get() != kRootNode)
		return IntNodeID::Create(kRootNode);
	else
		return NodeID_rv(nil);
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::GetNumChildren 
//----------------------------------------------------------------------------------------

int32 FieldSelectionTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	int32 count = 0;
	TreeNodePtr<IntNodeID> intNode(node);
	
	if (intNode->Get() == kRootNode)
		count = fFields.size();
		
	return count;
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::GetNthChild
//----------------------------------------------------------------------------------------

NodeID_rv FieldSelectionTreeViewAdapter::GetNthChild(const NodeID& node, const int32& nth) const
{
	TreeNodePtr<IntNodeID> intNode(node);
	
	ASSERT(intNode->Get() == kRootNode);
	
	return IntNodeID::Create(nth);
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------

int32 FieldSelectionTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	TreeNodePtr<IntNodeID> parentNode(parent);
	TreeNodePtr<IntNodeID> childNode(child);
	
	ASSERT(parentNode->Get() == kRootNode);
	ASSERT(childNode->Get() != kRootNode);

	return childNode->Get();
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::GetGenericNodeID
//----------------------------------------------------------------------------------------

NodeID_rv FieldSelectionTreeViewAdapter::GetGenericNodeID() const
{
	return IntNodeID::Create(kGenericNode);
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::Set
//----------------------------------------------------------------------------------------

void FieldSelectionTreeViewAdapter::Set(IDataBase* db, const K2Vector< K2Pair<UID, bool16> >& fields)
{
	fDb = db;
	fFields = fields;
	
	InterfacePtr<ITreeViewMgr> treeViewMgr(this, UseDefaultIID());
	treeViewMgr->ChangeRoot();
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::Get
//----------------------------------------------------------------------------------------

K2Vector< K2Pair<UID, bool16> > FieldSelectionTreeViewAdapter::Get() const
{
	return fFields;
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::GetFieldName
//----------------------------------------------------------------------------------------

PMString FieldSelectionTreeViewAdapter::GetFieldName(const NodeID& node) const
{
	TreeNodePtr<IntNodeID> intNode(node);
	
	InterfacePtr<IGraphicStyleDescriptor> styleDesc(fDb, fFields[intNode->Get()].first, ::UseDefaultIID());

	return AttributesUtils::GetStringValue(styleDesc,  kFormNameAttrBoss);
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::SetSelected
//----------------------------------------------------------------------------------------

void FieldSelectionTreeViewAdapter::SetSelected(const NodeID& node, const bool16& selected)
{
	TreeNodePtr<IntNodeID> intNode(node);
	
	K2Pair<UID, bool16> element = fFields[intNode->Get()];
	element.second = selected;
	fFields[intNode->Get()] = element;
}

//----------------------------------------------------------------------------------------
// FieldSelectionTreeViewAdapter::GetSelected
//----------------------------------------------------------------------------------------

bool16 FieldSelectionTreeViewAdapter::GetSelected(const NodeID& node) const
{
	TreeNodePtr<IntNodeID> intNode(node);
	return fFields[intNode->Get()].second;
}
