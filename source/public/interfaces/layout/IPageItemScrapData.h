//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemScrapData.h $
//  
//  Owner: Dave Burnard
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
#ifndef __IPAGEITEMSCRAPDATA__
#define __IPAGEITEMSCRAPDATA__

#include "IPMUnknown.h"
#include "PageItemScrapID.h"

//========================================================================================
// Forward declarations
//========================================================================================

class UIDList;
class PMPoint;

//========================================================================================
// CLASS IPageItemScrapData
//========================================================================================

/**
	@ingroup arch_scrap 
*/
/** IPageItemScrapData interface, is used to represent pageitems in a scrap database by the data exchange framework.
		This interface can be found on the PageItemScrapHandler boss as well as several other handler bosses that also
		store page item data. The class PageItemScrapData provides the necessary implementation.  
		
		Note that the pageitems are not required to live in the same database	as this interface does. The pageitems can
		either exist in the scrap database (as is the case for the clipboard) in another document (typical when dragging from ne document to another),
		etc.
 */
class IPageItemScrapData : public IPMUnknown
{
// ----- Constants
public:
	enum { kScrapType = 'PMLY' };
	enum { kDefaultIID = IID_IPAGEITEMSCRAPDATA };

// ----- Constructors/destructors
public:

// ----- Manipulators
public:
	/** Specify the pageitems to be remembered. 
			Note that you MUST call Replace first to establish which database the items exist in. 
			You can then optionally call Append to add other items.

		@param newList IN list of pageitems
		@postcondition this establishes which database the items exist in.
	*/
	virtual void		Replace(const UIDList& newList) = 0;
	
	/** Append an item to the scrap data

		@param newItem INOUT DESCRIPTION
		@precondition you MUST call Replace first to establish which database the items exist in.
	*/
	virtual void		Append(UID newItem) = 0;
	
	/** Append a list of items to the scrap data

		@param newList IN items to add to the list (should be in the same database as those items already there)
		@precondition you MUST call Replace first to establish which database the items exist in.
	*/
	virtual void		Append(const UIDList& newList) = 0;
	
	/** Remove all of the page items (release references or delete actual page items)
	*/
	virtual void		Clear() = 0;
	
// ----- Accessors
public:
	/** Are there any pageitems in the scrap data
	*/
	virtual bool16		IsEmpty() const = 0;
	
	/** Get a copy of the list of items on the scrap. 

		@return list of pageitems
		@postcondition Caller is responsible for deleting the list.
	*/
	virtual UIDList*	CreateUIDList() const = 0;

	/** Get the parent to be used when adding items to the scrap
	*/
	virtual UIDRef 		GetRootNode() const = 0;

	/** Set the parent to be used when adding page items to the scrap.
		Used when copying or otherwise creating pageitems that reside in the scrap database.

		@param newRoot IN the root node
		@precondition it is necessary for the root node to live in the same database
			as the handler boss containing the IPageItemScrapData
	*/
	virtual void 		SetRootNode(const UIDRef& newRoot) = 0;

	/** Does the scrap contain guides rather than pageitems?
	*/
	virtual bool16      GetIsGuide() const = 0;
	/** Set the flag that records whether the items in the scrap are guides rather than pageitems.
	*/
	virtual void		SetIsGuide(bool16 isGuide) = 0;
	
	/** When pasting, should the pageitems be centered on the page
	*/
	virtual bool16     GetCenterItemOnPaste() const = 0;
	/** Set whether the should the pageitems be centered on the page, when pasting.
	*/
	virtual void		SetCenterItemOnPaste(bool16 centerItem) = 0;

	/** For Paste Inside: Get the offset, saved at copy time of the item within it's parent.  
	*/
	virtual PMPoint		GetPasteInsideOffset(void) const = 0;
	
	/** For Paste Inside: Set the offset at copy time of the top left of the item we are copying to the top left of its parent.  
			The Offset calculation should be done in the coordinate space of the parent.  At PasteInside time, this Offset will
			be transformed into PasteBoard coordinates using the transform of the
			frame we are pasting into in order to calculate an offset in PasteBoard coordinates
			which can be used to move the pasted item such that it maintains the same offset
			with respect to its new frame as when originally copied.
	
		@param offset IN the offset
	*/
	virtual void		SetPasteInsideOffset(const PMPoint& offset) = 0;

	/** For Paste Inside: Get the transform set at copy time of the item(s) parent.  
	*/
	virtual PMMatrix	GetPasteInsideRelativeTransform(void) const = 0;

	/** For Paste Inside: Set the transform at copy time of the item(s) parent.  
	*/
	virtual void		SetPasteInsideRelativeTransform(const PMMatrix& transform) = 0;
};

#endif
