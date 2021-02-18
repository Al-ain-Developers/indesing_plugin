//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BookmarkLazyNotificationData.h $
//  
//  Owner: Ryan Gano
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
#ifndef __BookmarkLazyNotificationData__
#define __BookmarkLazyNotificationData__

#include "TreeLazyNotificationData.h"
#include "IBookMarkData.h"

/** Used to notify UI panels of changes to the bookmarks structure in the document. 
	Because of the hierarchical nature of bookmarks, BookmarkLazyNotificationData derives
	from TreeLazyNotificationData.
*/

class BookmarkLazyNotificationData : public TreeLazyNotificationData<UID>
{
public:
	/** Constructor
	@param db : database that the bookmarks belong to.
	*/
	BookmarkLazyNotificationData(IDataBase *db) : TreeLazyNotificationData<UID>(), fDB(db)
	{
	}

	/** Destructor
	*/
	virtual ~BookmarkLazyNotificationData()
	{
	}

private:
	virtual TreeLazyNotificationData<UID> *CreateNewCookie() const
	{ return new BookmarkLazyNotificationData(fDB); }

	virtual bool16 GetParent(const UID &bookmarkUID, UID &parentBookmarkUID) const
	{
		bool16 bFoundParent(kFalse);

		if (bookmarkUID != kInvalidUID)
		{
			InterfacePtr<IBookMarkData> bookmark(fDB, bookmarkUID, UseDefaultIID());
			if (bookmark)
			{
				parentBookmarkUID = bookmark->GetContainingBookMarkUID();

				if (parentBookmarkUID != kInvalidUID)
					bFoundParent = kTrue;
			}
		}
		else
		{
			parentBookmarkUID = kInvalidUID;
			ASSERT_FAIL("Why am I getting passed an invalid UID? This will probably hang in release.");
		}

		return bFoundParent;
	}

private:
	IDataBase *fDB;
};

#endif