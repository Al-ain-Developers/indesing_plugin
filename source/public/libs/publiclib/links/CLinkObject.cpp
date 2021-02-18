//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/links/CLinkObject.cpp $
//  
//  Owner: Michael Easter
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

#include "VCPublicHeaders.h"
#include "CLinkObject.h"

#include "IDataBase.h"
#include "ILinkManager.h"
#include "ILinkResource.h"
#include "IPMStream.h"


//========================================================================================
//
// CLinkObject Public Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
CLinkObject::CLinkObject(IPMUnknown* boss)
: inherited(boss),
  fLinkRefs(::GetDataBase(boss))
{
}

//========================================================================================
// Destructor
//========================================================================================
CLinkObject::~CLinkObject()
{
}

//========================================================================================
// CLinkObject::QueryLinkedObject
//========================================================================================
IPMUnknown* CLinkObject::QueryLinkedObject(const PMIID& interfaceId) const
{
	return InterfacePtr<IPMUnknown>(this, interfaceId).forget();
}

//========================================================================================
// CLinkObject::MarkLinksModified
//========================================================================================
void CLinkObject::MarkLinksModified() const
{
	SetLinksObjectModificationState(ILink::kObjectModified);
}

//========================================================================================
// CLinkObject::ClearLinksModified
//========================================================================================
void CLinkObject::ClearLinksModified() const
{
	SetLinksObjectModificationState(ILink::kObjectUnmodified);
}

//========================================================================================
// CLinkObject::ReadWrite
//========================================================================================
void CLinkObject::ReadWrite(IPMStream* s, ImplementationID prop)
{
	s->XferID(fClientId);
	fLinkRefs.ReadWriteXferReference(s);
}


//========================================================================================
//
// CLinkObject Private Implementation
//
//========================================================================================

//========================================================================================
// CLinkObject::AddLinkRef
//========================================================================================
void CLinkObject::AddLinkRef(UID linkUID)
{
	ASSERT_MSG(linkUID.IsValid(), "CLinkObject::AddLink() - Link UID is invalid!");

	PreDirty();
	fLinkRefs.Insert(linkUID);
}

//========================================================================================
// CLinkObject::RemoveLinkRef
//========================================================================================
void CLinkObject::RemoveLinkRef(UID linkUID)
{
	ASSERT_MSG(linkUID.IsValid(), "CLinkObject::RemoveLink() - Link UID is invalid!");

	int32 idx = fLinkRefs.Location(linkUID);
	if (idx == -1) {
		ASSERT_FAIL("CLinkObject::RemoveLink() - Link UID not found!");
		return;
	}

	PreDirty();
	fLinkRefs.Remove(idx);
}

//========================================================================================
// CLinkObject::SetLinksObjectModificationState
//========================================================================================
void CLinkObject::SetLinksObjectModificationState(ILink::ObjectModificationState modState) const
{
	IDataBase* db = fLinkRefs.GetDataBase();
	InterfacePtr<ILinkManager> iLinkMgr(db, db->GetRootUID(), UseDefaultIID());
	if (!iLinkMgr) {
		ASSERT_FAIL("CLinkObject::SetLinksObjectModificationState() - ILinkManager is nil!");
		return;
	}

	UIDList::const_iterator iterEnd(fLinkRefs.end());
	for (UIDList::const_iterator iter(fLinkRefs.begin()); iter != iterEnd; ++iter) {
		InterfacePtr<ILink> iLink(iLinkMgr->QueryLinkByUID(*iter));
		ASSERT_MSG(iLink, "CLinkObject::SetLinksObjectModificationState() - ILink is nil!");

		if (iLink) {
			iLink->SetObjectModificationState(modState);
		}
	}
}
