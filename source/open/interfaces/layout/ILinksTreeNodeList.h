//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/layout/ILinksTreeNodeList.h $
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

#pragma once
#ifndef __ILinksTreeNodeList__
#define __ILinksTreeNodeList__

#include "IPMUnknown.h"
#include "LinksUIID.h"

class LinkTreeEntry
{
//	typedef object_type data_type;

	public:
		LinkTreeEntry( const UIDRef& linkUIDRef, const UID& linkResourceUID, const LinkTreeEntry *parentEntry);
		virtual ~LinkTreeEntry();
		/** caller should allocate child entries on heap. This class takes ownership and will delete */
		void SetChildEntries(const K2Vector<LinkTreeEntry*> children);
		K2Vector<LinkTreeEntry*> GetChildEntries() const { return fChildren; }
		const LinkTreeEntry* GetParentEntry() const { return fParentEntry; }
		UIDRef GetLinkUIDRef() const
				{ 
					/*
					ASSERT_MSG(fLinkUIDRef.GetUID() == kRootDocumentLinksNodeUID || fLinkUIDRef.GetDataBase()->IsValidUID(fLinkUIDRef.GetUID()),
							   FORMAT_ARGS("LinkTreeEntry::GetLinkUIDRef() can't find the UID %d in the DB 0x%x, did someone delete it?", 
										   fLinkUIDRef.GetUID().Get(), 
										   fLinkUIDRef.GetDataBase()
										   )
							   );
					 */
					return fLinkUIDRef; 
				}
		UID GetLinkResourceUID() const { return fResourceUID; }

	private:
		LinkTreeEntry();
		LinkTreeEntry(const LinkTreeEntry& copy);
		LinkTreeEntry& operator=(const LinkTreeEntry& other);
		bool operator==(const LinkTreeEntry& other) const;

		UID fResourceUID;
		UIDRef fLinkUIDRef;
		const LinkTreeEntry *fParentEntry;
		K2Vector<LinkTreeEntry*> fChildren;
};

/** Interface for storing a list of Link/LinkResource UID values. */
class ILinksTreeNodeList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKSTREENODELIST };

	
	/** Set the value of the list. This object will acquire ownership of the array, and will delete it.
	@param array - the new value of the list
	*/
	virtual void AddEntireTree(LinkTreeEntry* rootNode) = 0;
	virtual const LinkTreeEntry* GetRootLinkEntry() const = 0;
				
	virtual  const LinkTreeEntry* FindEntryForLink(UIDRef linkUIDRef) const = 0;
	
	/** Return a boolean indicating whether or not the current list is flat(no children except of root node)
	*/
	virtual bool IsTreeFlat() const = 0;
	
};

#endif // __ILinksTreeNodeList__
