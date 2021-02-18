//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksTreeUIDNodeID.cpp $
//  
//  Owner: Matt Joss
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

#include "LinksTreeUIDNodeID.h"
#include "IPMStream.h"
#include "widgetid.h"
#include "LinksUIID.h"
#include "ILinksTreeNodeList.h"

LinksTreeUIDNodeID::LinksTreeUIDNodeID(const LinkTreeEntry* treeEntry) : 
fTreeEntry(treeEntry)
{
//	ASSERT_MSG(fLinkResourceUID != kRootDocumentLinksNodeUID,"This is not a legal value for linkresource uid.");
//	ASSERT_MSG(fLinkUID == kInvalidUID || fLinkResourceUID == kInvalidUID || fLinkUID != fLinkResourceUID,"These should not be equal.");
//	ASSERT_MSG(fLinkUID == kInvalidUID || fLinkUID == kRootDocumentLinksNodeUID || fParentNode.IsValid(),"If Link UID is valid, parent UID should be as well");

//	TRACEFLOW("Links:LinksUI","LinksTreeUIDNodeID created(this = 0x%x) - fLinkUID %d, fLinkResourceUID %d, fParentNode 0x%x\n",this,fLinkUID, fLinkResourceUID, fParentNode.Get());
}

LinksTreeUIDNodeID::~LinksTreeUIDNodeID()
{
//	TRACEFLOW("Links:LinksUI","LinksTreeUIDNodeID destroyed(this = 0x%x)\n",this);

}
	
UIDRef LinksTreeUIDNodeID::GetLinkUIDRef() const
{
	if(fTreeEntry)
		return fTreeEntry->GetLinkUIDRef();
	return kInvalidUIDRef;
}

UID LinksTreeUIDNodeID::GetLinkResourceUID() const
{
	if(fTreeEntry)
		return fTreeEntry->GetLinkResourceUID();
	return kInvalidUID;
}


//----------------------------------------------------------------------------------------
// LinksTreeUIDNodeID::Compare
//----------------------------------------------------------------------------------------
int32 LinksTreeUIDNodeID::Compare(const NodeIDClass* otherNode) const
{
	const LinksTreeUIDNodeID* otherLinkNode = static_cast<const LinksTreeUIDNodeID*>(otherNode);
	const LinkTreeEntry* myEntry = GetTreeEntry();
	const LinkTreeEntry* otherEntry = otherLinkNode->GetTreeEntry();
	if(myEntry == otherEntry)
		return 0;
	else if (myEntry > otherEntry)
		return 1;
	else
		return -1;
}

NodeIDClass* LinksTreeUIDNodeID::Clone() const
{
	return new LinksTreeUIDNodeID(GetTreeEntry());
}


void LinksTreeUIDNodeID::Read(IPMStream*	stream)
{
 LinksTreeUIDNodeID::Write(stream);
}

void LinksTreeUIDNodeID::Write(IPMStream*	stream) const
{
// THIS NEEDS WORK!

	// also called for read.
	uintptr_t temp = reinterpret_cast<uintptr_t>(fTreeEntry);
	stream->XferPointer(temp);
	((LinksTreeUIDNodeID*)this)->fTreeEntry = reinterpret_cast<LinkTreeEntry*>(temp);
}

PMString LinksTreeUIDNodeID::GetDescription() const 
{ 
	PMString desc("Link UID:");
	desc.AppendNumber(GetLinkUIDRef().GetUID().Get());
	desc.Append(" LinkResource UID:");
	desc.AppendNumber(GetLinkResourceUID().Get());
	return desc; 
}
