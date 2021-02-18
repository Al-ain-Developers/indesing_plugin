//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIPanelTreeViewAdapter.cpp $
//  
//  Owner: lance bushore
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

#include "ITreeViewHierarchyAdapter.h"
#include "IDocument.h"
#include "ILayoutUIUtils.h"
#include "ILinkManager.h"
#include "ILinksUIPanelPrefs.h"
#include "IUIDListData.h"
#include "ILinksTreeNodeList.h"

// ----- Includes -----

#include "CPMUnknown.h"
#include "LinksTreeUIDNodeID.h"
#include "LinksUIID.h"
#include "Utils.h"
#include "ILinksUIUtils.h"
#include "PreferenceUtils.h"

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewAdapter constructor
//----------------------------------------------------------------------------------------
class LinksUIPanelTreeViewAdapter : public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	LinksUIPanelTreeViewAdapter(IPMUnknown *boss);
	~LinksUIPanelTreeViewAdapter();
	
	virtual NodeID_rv	GetRootNode() const;
	virtual NodeID_rv	GetParentNode(const NodeID& node) const;
	virtual int32		GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv	GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32		GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv	GetGenericNodeID() const;
	virtual bool16		ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }
};

CREATE_PMINTERFACE(LinksUIPanelTreeViewAdapter, kLinksUIPanelTreeViewAdapterImpl)
//DEFINE_HELPER_METHODS(LinksUIPanelTreeViewAdapter)

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewAdapter constructor
//----------------------------------------------------------------------------------------


LinksUIPanelTreeViewAdapter::LinksUIPanelTreeViewAdapter(IPMUnknown *boss) :
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
}


//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewAdapter::~LinksUIPanelTreeViewAdapter 
//----------------------------------------------------------------------------------------

LinksUIPanelTreeViewAdapter::~LinksUIPanelTreeViewAdapter()
{
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewAdapter::GetRootNode 
//----------------------------------------------------------------------------------------
NodeID_rv LinksUIPanelTreeViewAdapter::GetRootNode() const
{
	InterfacePtr<const ILinksTreeNodeList> prebuiltLinksTree(this,UseDefaultIID());
	return LinksTreeUIDNodeID::Create(prebuiltLinksTree->GetRootLinkEntry());		
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewAdapter::GetParentNode 
//----------------------------------------------------------------------------------------
NodeID_rv LinksUIPanelTreeViewAdapter::GetParentNode(const NodeID& node) const
{
	TreeNodePtr<const LinksTreeUIDNodeID>	linkNode(node);
	if ( kRootDocumentLinksNodeUID == linkNode->GetLinkUIDRef().GetUID() )
		return kInvalidNodeID;
		
	ASSERT_MSG(linkNode->GetLinkUIDRef().GetUID() != kInvalidUID || linkNode->GetLinkResourceUID() != kInvalidUID,"What is this thing? Does it even have a parent?");
	if ( linkNode->GetTreeEntry() != nil )	//#2417495
		return LinksTreeUIDNodeID::Create(linkNode->GetTreeEntry()->GetParentEntry());

	ASSERT_FAIL("We have a bogus tree entry. Not good.");
	return kInvalidNodeID ;
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewAdapter::GetNumChildren 
//----------------------------------------------------------------------------------------
int32 LinksUIPanelTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	TreeNodePtr<const LinksTreeUIDNodeID>	linkNode(node);
	if(linkNode->GetTreeEntry())
		return K2length(linkNode->GetTreeEntry()->GetChildEntries());
	else
		return 0;
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewAdapter::GetNthChild
//----------------------------------------------------------------------------------------
// first element is header row.
// last element is 'link info' group
NodeID_rv LinksUIPanelTreeViewAdapter::GetNthChild(const NodeID& parentTreeNode, const int32& nth) const
{
	TreeNodePtr<const LinksTreeUIDNodeID>	parentLinkNode(parentTreeNode);
	ASSERT_MSG(parentLinkNode->GetTreeEntry() != nil,"We have a bogus tree entry. Not good.");

	K2Vector<LinkTreeEntry*> childEntries = parentLinkNode->GetTreeEntry()->GetChildEntries();
//	TRACEFLOW("Links:LinksUI","LinksUIPanelTreeViewAdapter::GetNthChild(%d) of parent with LinkUID %d, LinkResourceUID %d. Returning child with LinkUID %d, LinkResourceUID %d\n",
//		nth,parentLinkNode->GetTreeEntry()->GetLinkUID(),parentLinkNode->GetTreeEntry()->GetLinkResourceUID(),childEntries[nth]->GetLinkUID(),childEntries[nth]->GetLinkResourceUID());
	return LinksTreeUIDNodeID::Create(childEntries[nth]);		
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------
int32 LinksUIPanelTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	TreeNodePtr<const LinksTreeUIDNodeID>	parentLinkNode(parent);
	TreeNodePtr<const LinksTreeUIDNodeID>	childLinkNode(child);
	ASSERT_MSG(parentLinkNode->GetTreeEntry() != nil,"We have a bogus parent tree entry. Not good.");
	ASSERT_MSG(childLinkNode->GetTreeEntry() != nil,"We have a bogus child tree entry. Not good.");

	K2Vector<LinkTreeEntry*> childEntries = parentLinkNode->GetTreeEntry()->GetChildEntries();
	for(int i = 0; i < K2length(childEntries); ++i)
	{
		if(childEntries[i] == childLinkNode->GetTreeEntry())
			return i;
	}

	TRACEFLOW("Links:LinksUI","LinksUIPanelTreeViewAdapter::GetChildIndex failed to find child(LinkUID: %d, LinkResourceUID: %d) of parent(LinkUID %d, LinkResourceUID %d).\n",
		childLinkNode->GetLinkUIDRef().GetUID().Get(),childLinkNode->GetLinkResourceUID().Get(),parentLinkNode->GetLinkUIDRef().GetUID().Get(),parentLinkNode->GetLinkResourceUID().Get());

	return -1;
}

//----------------------------------------------------------------------------------------
// LinksUIPanelTreeViewAdapter::GetGenericNodeID() const
//----------------------------------------------------------------------------------------
NodeID_rv LinksUIPanelTreeViewAdapter::GetGenericNodeID() const
{
	return LinksTreeUIDNodeID::Create( nil );	
}

