//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookMarkData.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IBookMarkData__
#define __IBookMarkData__

#include "IPMUnknown.h"
#include "HyperlinkID.h"

/** Abstract interface to properties associated with bookmarks.
	@ingroup layout_book
	@see kBookmarkBoss 
*/
class IBookMarkData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IBOOKMARKDATA };

	virtual void			operator =(const IBookMarkData *other) = 0;


	/**	Set the name of the bookmark
		@param &bookMark - The new name to use
		@return none 
	 */
	virtual void			SetName(const PMString &bookMark) = 0;

	/**	Get the name of the bookmark (This name will be marked as translated)
		@param none
		@return PMString - The name of the bookmark
	 */
	virtual PMString		GetName() const = 0;
	

	/**	Set the indent level of the bookmark
		@param newIndentLevel - New indent (0 = root)
		@return none
	 */
	virtual void			SetIndentLevel(int32 newIndentLevel) = 0;

	/**	Get the indent level of the bookmark
		@param none
		@return int32 - The indent level of this bookmark
	 */
	virtual int32			GetIndentLevel() const = 0;


	/**	Set the UID of this bookmarks parent
		@param parentBookMark - Parent UID (documents UID indicates that this is at the root level)
		@return none
	 */
	virtual void			SetContainingBookMarkUID(UID parentBookMark) = 0;

	/**	Get the UID of this bookmarks parent
		@param none
		@return Parent UID (documents UID indicates that this is at the root level)
	 */
	virtual UID				GetContainingBookMarkUID() const = 0;


	/**	Add a new child to the end of this bookmark
		@param childBookmark - UID of new child to add
		@return none
	 */
	virtual	void			AddChild(UID childBookmark) = 0;

	/**	Remove a specific child from this bookmarks child list
		@param childBookmark - UID of the child to remove
		@return none
	 */
	virtual	void			RemoveChild(UID childBookmark) = 0;


	/**	Move a child to a new location
		@param child - The UI of the child to move (Must already be in this bookmark's child list)
		@param newIndex - The new lcoation to move the child to (-1 == end of list)
		@return  
	 */
	virtual void			MoveChild(const UID child, int32 newIndex) = 0;


	/**	Get the number of children of this bookmark
		@param none
		@return int32 - Number of chilren in child list
	 */
	virtual int32			GetChildCount() const = 0;


	/**	Get a specific child by index
		@param childIndex - Index of child to get
		@return UID - child at Nth location
	 */
	virtual UID				GetNthChild(int32 childIndex) const = 0;


	/**	Get the index of a specific child by UID
		@param child - UID of the child to get
		@return int32 - Index of the child
	 */
	virtual int32			GetChildWithUID(const UID child) const = 0;
		// Use for locating a specified hyperlink


	/**	Set the destination that this bookmark points to
		@param dest - The appropriate destination
	 */
	virtual void SetDestinationUID(const UID dest) = 0;

	/**	Get the destination that this bookmark points to
		@param none
		@return UID - Destination's UID
	 */
	virtual UID GetDestinationUID() const = 0;


	/**	Show the destination that this bookmark points to
		@param none
	 */
	virtual void GotoDestination() const = 0;


	/**	Ensure that this bookmark is OK (Make sure that parent and children lists
		are valid.  Also make sure that internal data is in a valid state)
		@param none
		@return ErrorCode - Error state of bookmark - kSuccess = Bookmark is OK
	 */
	virtual ErrorCode		ValidateBookmark() = 0;

	/**	Make sure that after methods in this class change things the
		bookmark class is still OK
		@param none
		@return none
	 */
	virtual void			Invariant() const = 0;

	/**	Make this bookmark invalid (Used for conversion from Anna to Dragontail)
		@param none
		@return none
	 */
	virtual void			Invalidate() = 0;

	/**	Add information all at once (used for converting Anna documents to Dragontail)
		@param parentBookMark - The correct parent bookmark
		@param destinationUID - The correct destination UID
		@return  
	 */
	virtual void			AddConversionData(UID parentBookMark, UID destinationUID) = 0;
};

#endif
