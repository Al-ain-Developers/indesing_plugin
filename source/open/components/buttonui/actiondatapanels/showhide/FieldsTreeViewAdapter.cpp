//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/showhide/FieldsTreeViewAdapter.cpp $
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

#include "IFieldsTreeViewAdapter.h"
#include "IFormField.h"
#include "IGraphicStyleDescriptor.h"
#include "ITreeViewMgr.h"

// ----- Implementation Includes -----
#include "CPMUnknown.h"
#include "K2Vector.tpp"

#include "AttributesUtils.h"

#include "BehaviorUIID.h"
#include "IntNodeID.h"

//========================================================================================
// CLASS FieldsTreeViewAdapter
//========================================================================================

class FieldsTreeViewAdapter : public CPMUnknown<IFieldsTreeViewAdapter>
{
public:
	FieldsTreeViewAdapter(IPMUnknown *boss);
	
	enum { kRootNode = -1, kGenericNode = -2 };
		
	virtual NodeID_rv			GetRootNode() const;
	virtual NodeID_rv			GetParentNode(const NodeID& node) const;
	virtual int32				GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv			GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32				GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv			GetGenericNodeID() const;
	virtual bool16				ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }

	virtual void		Set(IDataBase* db, const K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> >& fields);
	virtual K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> > Get() const;
	
	virtual IDataBase*			GetDataBase() const { return fDb; }

	virtual PMString GetFieldName(const NodeID& node) const;

	virtual void		SetAction(const NodeID& node, const IShowHideFieldActionData::Action& action);
	virtual IShowHideFieldActionData::Action GetAction(const NodeID& node) const;

private:
	IDataBase* fDb;
	K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> > fFields;
};

//========================================================================================
// IMPLEMENTATION FieldsTreeViewAdapter
//========================================================================================

CREATE_PMINTERFACE(FieldsTreeViewAdapter, kFieldsTreeViewAdapterImpl)

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter constructor
//----------------------------------------------------------------------------------------

FieldsTreeViewAdapter::FieldsTreeViewAdapter(IPMUnknown *boss) :
	CPMUnknown<IFieldsTreeViewAdapter>(boss),fDb(nil)
{
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::GetRootNode 
//----------------------------------------------------------------------------------------

NodeID_rv FieldsTreeViewAdapter::GetRootNode() const
{
	return IntNodeID::Create(kRootNode);
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::GetParentNode 
//----------------------------------------------------------------------------------------

NodeID_rv FieldsTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	TreeNodePtr<IntNodeID>	intNode(node);
	
	if (intNode->Get() != kRootNode)
		return IntNodeID::Create(kRootNode);
	else
		return NodeID_rv(nil);
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::GetNumChildren 
//----------------------------------------------------------------------------------------

int32 FieldsTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	int32 count = 0;
	TreeNodePtr<IntNodeID> intNode(node);
	
	if (intNode->Get() == kRootNode)
		count = fFields.size();
		
	return count;
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::GetNthChild
//----------------------------------------------------------------------------------------

NodeID_rv FieldsTreeViewAdapter::GetNthChild(const NodeID& node, const int32& nth) const
{
	TreeNodePtr<IntNodeID> intNode(node);
	
	ASSERT(intNode->Get() == kRootNode);
	
	return IntNodeID::Create(nth);
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------

int32 FieldsTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	TreeNodePtr<IntNodeID> parentNode(parent);
	TreeNodePtr<IntNodeID> childNode(child);
	
	ASSERT(parentNode->Get() == kRootNode);
	ASSERT(childNode->Get() != kRootNode);

	return childNode->Get();
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::GetGenericNodeID
//----------------------------------------------------------------------------------------

NodeID_rv FieldsTreeViewAdapter::GetGenericNodeID() const
{
	return IntNodeID::Create(kGenericNode);
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::Set
//----------------------------------------------------------------------------------------

void FieldsTreeViewAdapter::Set(IDataBase* db, const K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> >& fields)
{
	fDb = db;
	fFields = fields;
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::Get
//----------------------------------------------------------------------------------------

K2Vector< K2Pair<UID, IShowHideFieldActionData::Action> > FieldsTreeViewAdapter::Get() const
{
	return fFields;
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::GetFieldName
//----------------------------------------------------------------------------------------

PMString FieldsTreeViewAdapter::GetFieldName(const NodeID& node) const
{
	TreeNodePtr<IntNodeID> intNode(node);

	if (!fDb->IsValidUID(fFields[intNode->Get()].first))
		return PMString();

	InterfacePtr<IGraphicStyleDescriptor> styleDesc(fDb, fFields[intNode->Get()].first, ::UseDefaultIID());
	return AttributesUtils::GetStringValue(styleDesc,  kFormNameAttrBoss);
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::SetAction
//----------------------------------------------------------------------------------------

void FieldsTreeViewAdapter::SetAction(const NodeID& node, const IShowHideFieldActionData::Action& action)
{
	TreeNodePtr<IntNodeID> intNode(node);
	
	K2Pair<UID, IShowHideFieldActionData::Action> element = fFields[intNode->Get()];
	element.second = action;
	fFields[intNode->Get()] = element;
}

//----------------------------------------------------------------------------------------
// FieldsTreeViewAdapter::GetAction
//----------------------------------------------------------------------------------------

IShowHideFieldActionData::Action FieldsTreeViewAdapter::GetAction(const NodeID& node) const
{
	TreeNodePtr<IntNodeID> intNode(node);
	return fFields[intNode->Get()].second;
}
