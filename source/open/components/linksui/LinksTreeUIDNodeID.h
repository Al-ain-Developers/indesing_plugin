//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksTreeUIDNodeID.h $
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

#ifndef __LinksTreeUIDNodeID__
#define __LinksTreeUIDNodeID__


#include "NodeID.h"
#include "LinksUIID.h"

class LinkTreeEntry;
//========================================================================================
// class LinksTreeUIDNodeID 
//========================================================================================
class LinksTreeUIDNodeID : public NodeIDClass
{
public:
	enum { kNodeType = kLinkTreeNodeID }; 
	
	virtual ~LinksTreeUIDNodeID();
	
	virtual	NodeType		GetNodeType() const { return kNodeType; }
	virtual int32			Compare(const NodeIDClass* NodeID) const;
	virtual NodeIDClass*	Clone() const;
	virtual void			Read(IPMStream*	stream);
	virtual void			Write(IPMStream*	stream) const;
	virtual PMString		GetDescription() const;
	
	UIDRef			GetLinkUIDRef() const;
	UID				GetLinkResourceUID() const;
	const LinkTreeEntry* GetTreeEntry() const { return fTreeEntry; }

	static	NodeID_rv		Create(const LinkTreeEntry* treeEntry) { return new LinksTreeUIDNodeID(treeEntry); }
private:
	LinksTreeUIDNodeID(const LinkTreeEntry* treeEntry);
	LinksTreeUIDNodeID();
	LinksTreeUIDNodeID(const LinksTreeUIDNodeID& copy);
	const LinkTreeEntry*	fTreeEntry;
};

struct LinkUIDsStruct
{
	typedef base_type data_type;
	LinkUIDsStruct(UID linkUID, UID linkResourceUID):fLinkUID(linkUID),fLinkResourceUID(linkResourceUID) {}
	UID fLinkUID,fLinkResourceUID;
};


#endif
