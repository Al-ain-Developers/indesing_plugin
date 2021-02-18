//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvTVHierarchyAdapter.cpp $
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
#include "ISession.h"
#include "IPnlTrvDataModel.h"
// General includes:
#include "CPMUnknown.h"
#include "CAlert.h"

// Project includes:
#include "PnlTrvID.h"
#include "PnlTrvFileNodeID.h"
#include "IPnlTrvOptions.h"

/** Implementation of ITreeViewHierarchyAdapter, adapts our tree model to the needs of the 
	tree-view widget. Implements an adapter for the tree hierarchy; this is where the hierarchy 
	is accessed by the application core - you'll find that this is the only implementation 
	you provide with methods like GetNumChildren or GetParent.

	For further reading on ITreeViewHiearchyAdapter interface, see the Widgets chapter
	of the User Interface technote.

	
	@ingroup paneltreeview

*/

class PnlTrvTVHierarchyAdapter : 
	public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	/** Constructor
	*/	
	PnlTrvTVHierarchyAdapter(IPMUnknown* boss);

	/** Destructor
	*/	
	virtual ~PnlTrvTVHierarchyAdapter();
	

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
CREATE_PMINTERFACE(PnlTrvTVHierarchyAdapter, kPnlTrvTVHierarchyAdapterImpl)

/* Constructor
*/
PnlTrvTVHierarchyAdapter::PnlTrvTVHierarchyAdapter(IPMUnknown* boss) : 
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
}


/* Destructor
*/
PnlTrvTVHierarchyAdapter::~PnlTrvTVHierarchyAdapter()
{
}


/* GetRootNode
*/
NodeID_rv PnlTrvTVHierarchyAdapter::GetRootNode() const
{
	// When we call ITreeViewMgr::ChangeRoot, then this is the first
	// method that gets called
	InterfacePtr<IPnlTrvDataModel> model(this, UseDefaultIID());
	ASSERT(model);
	return PnlTrvFileNodeID::Create(model->GetRootPath());
}


/* GetParentNode
*/
NodeID_rv PnlTrvTVHierarchyAdapter::GetParentNode(const NodeID& node) const
{
	// The root has no parent: this will be a general result	
	do
	{
		TreeNodePtr<PnlTrvFileNodeID> nodeID(node);
		if (nodeID == nil)
		{
			break; 
		}

		PMString path = nodeID->GetPath();
		InterfacePtr<IPnlTrvDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		if(path == model->GetRootPath())
		{
			break;
		}
		PMString parentPath(model->GetParentPath(path));
		return PnlTrvFileNodeID::Create(parentPath);

	} while(kFalse);

	return kInvalidNodeID;	
}


/*
*/
int32 PnlTrvTVHierarchyAdapter::GetNumChildren(const NodeID& node) const
{
	int32 retval=0;
	do
	{
		TreeNodePtr<PnlTrvFileNodeID> nodeID(node);
		if (nodeID == nil)
		{
			break;
		}
		InterfacePtr<IPnlTrvDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		retval = model->GetChildCount(nodeID->GetPath());
	} while(kFalse);
	
	return retval;
}

/* GetNthChild
*/
NodeID_rv PnlTrvTVHierarchyAdapter::GetNthChild(
	const NodeID& node, const int32& nth) const
{
	do
	{
		TreeNodePtr<PnlTrvFileNodeID> nodeID(node);
		if (nodeID == nil)
		{
			break;
		}
		InterfacePtr<IPnlTrvDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		PMString childPath = model->GetNthChildPath(nodeID->GetPath(), nth);	
		return PnlTrvFileNodeID::Create(childPath);
		
	} while(kFalse);
	return kInvalidNodeID;
}


/* GetChildIndex
*/
int32 PnlTrvTVHierarchyAdapter::GetChildIndex(
	const NodeID& parent, const NodeID& child) const
{
	do
	{
		TreeNodePtr<PnlTrvFileNodeID> parentFileNodeID(parent);
		ASSERT(parentFileNodeID);
		if(parentFileNodeID==nil)
		{
			break;
		}
		TreeNodePtr<PnlTrvFileNodeID> childFileNodeID(child);
		ASSERT(childFileNodeID);
		if(childFileNodeID==nil)
		{
			break;
		}
		InterfacePtr<IPnlTrvDataModel> model(this, UseDefaultIID());
		ASSERT(model);				
		return model->GetChildIndexFor(parentFileNodeID->GetPath(), childFileNodeID->GetPath());			
	} while(kFalse);

	return (-1);
}


/* GetGenericNodeID
*/
NodeID_rv PnlTrvTVHierarchyAdapter::GetGenericNodeID() const
{
	return PnlTrvFileNodeID::Create();
}


/* getTargetPath

PMString PnlTrvTVHierarchyAdapter::getTargetPath() const
{
	PMString retval="";
	do
	{
		InterfacePtr<IWorkspace> 
			iSessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(iSessionWorkspace);
		if(iSessionWorkspace == nil)
		{
			break;
		}
		InterfacePtr<IPnlTrvOptions>
			iOptions(iSessionWorkspace, UseDefaultIID());
		ASSERT(iOptions);
		if(!iOptions)
		{
			break;
		}
		retval = iOptions->GetNthOption(0);
		
	} while(kFalse);
	return retval;
}
*/

//	end, File: PnlTrvTVHierarchyAdapter.cpp
