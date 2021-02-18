//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdaterui/DataUpdaterUITVHierarchyAdapter.cpp $
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
#include "ITreeViewHierarchyAdapter.h"
#include "IWorkspace.h"
#include "IDataUpdaterUIDataModel.h"
// General includes:
#include "CPMUnknown.h"
#include "CAlert.h"

// Project includes:
#include "DataUpdaterConst.h"
#include "DataUpdaterUIID.h"
#include "DataUpdaterUINodeID.h"

/** Implementation of ITreeViewHierarchyAdapter, adapts our tree model to the needs of the 
	tree-view widget. Implements an adapter for the tree hierarchy; this is where the hierarchy 
	is accessed by the application core - you'll find that this is the only implementation 
	you provide with methods like GetNumChildren or GetParent.

	For further reading on ITreeViewHiearchyAdapter interface, see the Widgets chapter
	of the User Interface technote.

	
	@ingroup xmldataupdaterui

*/

class DataUpdaterUITVHierarchyAdapter : 
	public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	/** Constructor
	*/	
	DataUpdaterUITVHierarchyAdapter(IPMUnknown* boss);

	/** Destructor
	*/	
	virtual ~DataUpdaterUITVHierarchyAdapter();
	

	/** 
		Acquire reference to root node of our tree. 
		@return reference to root node
	*/	
	virtual NodeID_rv GetRootNode() const;

	/** Acquire a reference to the parent of the given node.
		GetParentNode() should always return kInvalidNodeID for the root.
		@param node (in) specifies node of interest
		@return reference to parent of given node
	*/	
	virtual NodeID_rv GetParentNode(const NodeID& node) const;

	/** 
		Determine the number of child nodes that the given node has.
		@param node (in) specifies node of interest
		@return count of children for given node
	*/	
	virtual int32 GetNumChildren(const NodeID& node) const;

	/**
		Acquire a reference to the nth child. Note: the indexing is from 0 to (numChildren-1).
		@param node (in) identifies the parent node for which we're seeking the nth child
		@param nth (in) get the child at this index in the list of children of the specified node
		@return reference to the nth child
	*/	
	virtual NodeID_rv GetNthChild(
		const NodeID& node, const int32& nth) const;

	/** Determines the index of given child in the parent's list of children.
		Given the parent and an instance of a child, indicate what the index of
		the given child node should be in the list of children of the parent, if any.
	
		@param parent (in) reference to the parent node
		@param child (in) reference to the child node, whose index we're seeking
		@return index of child in parent's kids, or (-1) if the child doesn't belong to this parent
	*/	
	virtual int32 GetChildIndex(
		const NodeID& parent, const NodeID& child) const;

	/** Acquire reference to a general-purpose node.
		This should return an instance of a node that can be used anywhere in the hierarchy.
		@return reference to general purpose node
	*/	
	virtual NodeID_rv GetGenericNodeID() const;

	virtual bool16  ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }

};	

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(DataUpdaterUITVHierarchyAdapter, kDataUpdaterUITVHierarchyAdapterImpl)

/* Constructor
*/
DataUpdaterUITVHierarchyAdapter::DataUpdaterUITVHierarchyAdapter(IPMUnknown* boss) : 
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
}


/* Destructor
*/
DataUpdaterUITVHierarchyAdapter::~DataUpdaterUITVHierarchyAdapter()
{
}


/* GetRootNode
*/
NodeID_rv DataUpdaterUITVHierarchyAdapter::GetRootNode() const
{
	// When we call ITreeViewMgr::ChangeRoot, then this is the first
	// method that gets called
	InterfacePtr<IDataUpdaterUIDataModel> model(this, UseDefaultIID());
	ASSERT(model);
	if (model->HasInitialized())
		return DataUpdaterUINodeID::Create(kDataUpdaterTableTag, 0, model->GetTable());
	else
		return kInvalidNodeID;
}


/* GetParentNode
*/
NodeID_rv DataUpdaterUITVHierarchyAdapter::GetParentNode(const NodeID& node) const
{
	// The root has no parent: this will be a general result	
	do
	{
		TreeNodePtr<DataUpdaterUINodeID> nodeID(node);
		if (nodeID == nil)
		{
			break; 
		}

		PMString type = nodeID->GetType();
		PMString value = nodeID->GetValue();
		InterfacePtr<IDataUpdaterUIDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		if(type ==  kDataUpdaterTableTag || value == model->GetTable())
		{ //If it is the root
			break;
		}

		if ( type ==  kDataUpdaterKeyTag)
		{ // if it is a record, then its parent is the root (table)
			return DataUpdaterUINodeID::Create(kDataUpdaterTableTag, 0, model->GetTable());
		}

		if ( type ==  kDataUpdaterFieldTag)
		{ //its parent is a record
			int32 index = nodeID->GetIndex(); // this index is nth record  nth field
			int32 recIndex = index / model->GetFieldCount();
			PMString key = model->GetNthValue(recIndex, 0);
			return DataUpdaterUINodeID::Create(kDataUpdaterKeyTag, recIndex, key);
		}
		
		// If we get here, it must be our leaf node, its index is value index
		{
			int32 index = nodeID->GetIndex(); // this is also a value index
			int32 fieldCount = model->GetFieldCount();
			int32 nthRec = index / fieldCount;
			PMString field = model->GetNthField(index - fieldCount*nthRec);
			return DataUpdaterUINodeID::Create(kDataUpdaterFieldTag, index, field);
		}

	} while(kFalse);

	return kInvalidNodeID;	
}


/*
*/
int32 DataUpdaterUITVHierarchyAdapter::GetNumChildren(const NodeID& node) const
{
	int32 retval=0;
	do
	{
		TreeNodePtr<DataUpdaterUINodeID> nodeID(node);
		if (nodeID == nil)
		{
			break;
		}
		InterfacePtr<IDataUpdaterUIDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		PMString type = nodeID->GetType();
		if (type == kDataUpdaterTableTag)
			return  model->GetRecordCount();

		if (type == kDataUpdaterKeyTag) // a record node
			return  model->GetFieldCount();
 
		if (type ==  kDataUpdaterFieldTag) // a field node
			return   1; // only a leaf node of value

		if (type ==  kDataUpdaterValueTag)		 //a leaf node of value
			return  0; // no child 

	} while(kFalse);
	
	return retval;
}

/* GetNthChild
*/
NodeID_rv DataUpdaterUITVHierarchyAdapter::GetNthChild(
	const NodeID& node, const int32& nth) const
{
	do
	{
		TreeNodePtr<DataUpdaterUINodeID> nodeID(node);
		if (nodeID == nil)
		{
			break;
		}
		InterfacePtr<IDataUpdaterUIDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		PMString type = nodeID->GetType();
		int32 index = nodeID->GetIndex(); 
		PMString childType, childValue;
		int32 childIndex;

		if (type == kDataUpdaterTableTag) //table node
		{
			childType = kDataUpdaterKeyTag;
			childIndex = nth;
			childValue = model->GetNthValue(nth, 0); //first field of the record
		}
		else if (type == kDataUpdaterKeyTag) // a record node
		{
			childType = kDataUpdaterFieldTag;
			childIndex = index * model->GetFieldCount() + nth;
			childValue = model->GetNthField(nth);
		}
		else if (type ==  kDataUpdaterFieldTag) // a field node
		{
			childType = kDataUpdaterValueTag;
			childIndex = index;
			int32 nthRec = index / model->GetFieldCount();
			childValue = model->GetNthValue(nthRec, index - nthRec * model->GetFieldCount()); 
		}
		else //kDataUpdaterValueTag, a leaf node of value 
		{
			childIndex = -1; // no child 
			ASSERT_MSG(kFalse, "Ask leaf node for children");
		}
		return DataUpdaterUINodeID::Create(childType, childIndex, childValue);
		
	} while(kFalse);
	return kInvalidNodeID;
}


/* GetChildIndex
*/
int32 DataUpdaterUITVHierarchyAdapter::GetChildIndex(
	const NodeID& parent, const NodeID& child) const
{
	int32 retval = -1;
	do
	{
		TreeNodePtr<DataUpdaterUINodeID> parentNodeID(parent);
		ASSERT(parentNodeID);
		if(parentNodeID==nil)
		{
			break;
		}
		TreeNodePtr<DataUpdaterUINodeID> childNodeID(child);
		ASSERT(childNodeID);
		if(childNodeID==nil)
		{
			break;
		}
		InterfacePtr<IDataUpdaterUIDataModel> model(this, UseDefaultIID());
		ASSERT(model);	

		PMString parentType = parentNodeID->GetType();
		int32 parentIndex = parentNodeID->GetIndex();
		PMString childType = childNodeID->GetType();
		int32 childIndex = childNodeID->GetIndex();
		PMString childValue = childNodeID->GetValue();
		if(parentType ==  kDataUpdaterTableTag && childType == kDataUpdaterKeyTag)
		{ //If it is the root and record
			retval = childIndex;
			break;
		}

		if(parentType ==  kDataUpdaterKeyTag && childType == kDataUpdaterFieldTag)
		{ //If it is the record and field
			retval = model->GetFieldIndex(childValue);
			break;
		}

		if(parentType ==  kDataUpdaterFieldTag && childType == kDataUpdaterValueTag)
		{ //If it is the field and value
			retval = 0; //only one, always the first
			break;
		}
		
		ASSERT_MSG(kFalse, "Unexpected combination of parent and child");	

	} while(kFalse);

	return (retval);
}


/* GetGenericNodeID
*/
NodeID_rv DataUpdaterUITVHierarchyAdapter::GetGenericNodeID() const
{
	return DataUpdaterUINodeID::Create();
}


//	end, File: DataUpdaterUITVHierarchyAdapter.cpp
