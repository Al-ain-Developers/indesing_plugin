//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUITVHierarchyAdapter.cpp $
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


// General includes:
#include "CPMUnknown.h"
#include "CAlert.h"

// Project includes:
#include "CusDtLnkUIID.h"
#include "CusDtLnkUIFileNodeID.h"
#include "ICusDtLnkUITreeDataModel.h"
//#include "ICusDtLnkUITreeOptions.h"

/** Implementation of ITreeViewHierarchyAdapter, adapts our tree model to the needs of the 
	tree-view widget. Implements an adapter for the tree hierarchy; this is where the hierarchy 
	is accessed by the application core - you'll find that this is the only implementation 
	you provide with methods like GetNumChildren or GetParent.

	For further reading on ITreeViewHiearchyAdapter interface, see the Widgets chapter
	of the User Interface technote.

	
	@ingroup customdatalinkui

*/

class CusDtLnkUITreeTVHierarchyAdapter : 
	public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	/** Constructor
	*/	
	CusDtLnkUITreeTVHierarchyAdapter(IPMUnknown* boss);

	/** Destructor
	*/	
	virtual ~CusDtLnkUITreeTVHierarchyAdapter();
	

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

	virtual bool16	ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }

protected:
	PMString getTargetPath() const;

private:
	// We want to be violate the 'const'-ness of the GetRootNode method
	// to change the root path when the options change.
	// So if we add mutable, it is OK to call mutators on this instance variable
	// from within a const method.
	//mutable CusDtLnkUITreeDataModel model->;

};	

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusDtLnkUITreeTVHierarchyAdapter, kCusDtLnkUITVHierarchyAdapterImpl)

/* Constructor
*/
CusDtLnkUITreeTVHierarchyAdapter::CusDtLnkUITreeTVHierarchyAdapter(IPMUnknown* boss) : 
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
}


/* Destructor
*/
CusDtLnkUITreeTVHierarchyAdapter::~CusDtLnkUITreeTVHierarchyAdapter()
{
}


/* GetRootNode
*/
NodeID_rv CusDtLnkUITreeTVHierarchyAdapter::GetRootNode() const
{
	TRACEFLOW(kCusDtLnkUIPluginName, "CusDtLnkUITreeTVHierarchyAdapter::GetRootNode() : About to rebuild model\n");
	// When we call ITreeViewMgr::ChangeRoot, then this is the first
	// method that gets called
	/*PMString targetPath = this->getTargetPath();	
	if(targetPath != model->GetRootNodeUniqueKey())
	{
		// Looks like the root has changed, so update our model
		model->SetRootPath(targetPath);
	}*/
	// TODO optimize PMString rootPath = model->GetRootNodeUniqueKey();
	// TODO optimize if(rootPath.empty()) {
	//	model->Rebuild();
	// TODO optimize }
	InterfacePtr<ICusDtLnkUITreeDataModel> model(this, UseDefaultIID());
	ASSERT(model);
	return CusDtLnkUIFileNodeID::Create(model->GetRootNodeUniqueKey());
}


/* GetParentNode
*/
NodeID_rv CusDtLnkUITreeTVHierarchyAdapter::GetParentNode(const NodeID& node) const
{
	// The root has no parent: this will be a general result	
	do
	{
		TreeNodePtr<CusDtLnkUIFileNodeID> nodeID(node);
		if (nodeID == nil)
		{
			break; 
		}

		PMString pkey = nodeID->GetUniqueKey();
		InterfacePtr<ICusDtLnkUITreeDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		if(pkey == model->GetRootNodeUniqueKey()) {
			break;
		}
		PMString parentUKey(model->GetParentPath(pkey));
		return CusDtLnkUIFileNodeID::Create(parentUKey);

	} while(kFalse);

	return kInvalidNodeID;	
}


/*
*/
int32 CusDtLnkUITreeTVHierarchyAdapter::GetNumChildren(const NodeID& node) const
{
	int32 retval=0;
	do
	{
		TreeNodePtr<CusDtLnkUIFileNodeID> nodeID(node);
		if (nodeID == nil)
		{
			break;
		}
		InterfacePtr<ICusDtLnkUITreeDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		retval = model->GetChildCount(nodeID->GetUniqueKey());
	} while(kFalse);
	
	return retval;
}

/* GetNthChild
*/
NodeID_rv CusDtLnkUITreeTVHierarchyAdapter::GetNthChild(
	const NodeID& node, const int32& nth) const
{
	do
	{
		TreeNodePtr<CusDtLnkUIFileNodeID> nodeID(node);
		if (nodeID == nil)
		{
			break;
		}
		InterfacePtr<ICusDtLnkUITreeDataModel> model(this, UseDefaultIID());
		ASSERT(model);
		PMString childKey = model->GetNthChildPath(nodeID->GetUniqueKey(), nth);	
		return CusDtLnkUIFileNodeID::Create(childKey);
		
	} while(kFalse);
	return kInvalidNodeID;
}


/* GetChildIndex
*/
int32 CusDtLnkUITreeTVHierarchyAdapter::GetChildIndex(
	const NodeID& parent, const NodeID& child) const
{
	do
	{
		TreeNodePtr<CusDtLnkUIFileNodeID> parentFileNodeID(parent);
		ASSERT(parentFileNodeID);
		if(parentFileNodeID==nil)
		{
			break;
		}
		TreeNodePtr<CusDtLnkUIFileNodeID> childFileNodeID(child);
		ASSERT(childFileNodeID);
		if(childFileNodeID==nil)
		{
			break;
		}
		InterfacePtr<ICusDtLnkUITreeDataModel> model(this, UseDefaultIID());
		ASSERT(model);				
		return model->GetChildIndexFor(parentFileNodeID->GetUniqueKey(), childFileNodeID->GetUniqueKey());			
	} while(kFalse);

	return (-1);
}


/* GetGenericNodeID
*/
NodeID_rv CusDtLnkUITreeTVHierarchyAdapter::GetGenericNodeID() const
{
	return CusDtLnkUIFileNodeID::Create();
}


/* getTargetPath

PMString CusDtLnkUITreeTVHierarchyAdapter::getTargetPath() const
{
	PMString retval="";
	do
	{
		// TODO ip 
		InterfacePtr<IWorkspace> 
			iSessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(iSessionWorkspace);
		if(iSessionWorkspace == nil)
		{
			break;
		}
		InterfacePtr<ICusDtLnkUITreeOptions>
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
//	end, File: CusDtLnkUITreeTVHierarchyAdapter.cpp
