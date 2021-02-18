//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookmarkUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IBookmarkUtils__
#define __IBookmarkUtils__


#include "HyperlinkID.h"
#include "IPMUnknown.h"
#include "Utils.h"

class IBookMarkData;
	
#define BOOKMARKUTILS Utils<IBookmarkUtils>()

/** Utilities relating to bookmarks (kBookmarkBoss).
	@ingroup layout_book
	@see kBookmarkBoss 
	@see IBookMarkData
	@ingroup layout_util
*/
class IBookmarkUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBOOKMARKUTILS };

	/**	Given a pointer to an IDataBase and two UIDs of bookmarks in that database this method
		will return an int32 which is the locaiton of the child UID in the parent.
		@param *db - IDataBase of the document that the client is dealing with
		@param parent - UID of the database (if the child is at the root) or the parent of the child
		@param child  - UID of the child whose location you are trying to get
		@return int32 - Location of the child under the parent (-1 if not found)
	 */
	virtual int32 GetChildIndexFromParent(IDataBase *db, const UID parent, const UID child) = 0;

	/**	Given a UIDRef of a bookmark this method will return the number of children under
		the bookmark.
		@param bookmarkRef - The ref which client wants a child count for (This can be a bookmark
		or te document (which will return the count of root level bookmarks)
		@return int32  - The number of children
	 */
	virtual int32 GetBookmarkChildCount(UIDRef bookmarkRef) = 0;

	/**	Given a UIDRef of a bookmark and an index this method will return the Nth child under
		the bookmark
		@param bookmarkRef - The bookmark (or document) to get the Nth child of
		@param index - Which child to return
		@return UIDRef - The child bookmark (gNull if child couldn't be found)
	 */
	virtual UIDRef GetNthBookmarkOfParent(UIDRef bookmarkRef, int32 index) = 0;

	/**	Build a list of ALL bookmarks under a given bookmark.  This list is in reverse order 
		(The lowest bookmarks are first in the list) 
	    NOTE: this method is recursive
		@param *bookmark - The top level bookmark to have in the list
		@param *nestedList - Final list of bookmarks
	 */
	virtual void BuildListOfNestedBookmarks(IBookMarkData *bookmark, UIDList *nestedList) = 0;

	/**	Search up the bookmark tree to determine if given child is already a parent of parent.
	    NOTE: this method is recursive
		@param *db - DataBase we are dealing with
		@param parent - The parent bookmark (may also be a document)
		@param child - The child bookmark (This is the one we are making sure is not already
		a parent of parent
		@return bool16 - kTrue if the parent is 
	 */
	virtual bool16 IsBookmarkAParentOfUID(IDataBase *db, const UID parent, const UID child) = 0;
};


#endif	// __IBookmarkUtils__
