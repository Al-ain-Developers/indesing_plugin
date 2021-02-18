//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHierarchyUtils.h $
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
#ifndef __IHierarchyUtils__
#define __IHierarchyUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "IHierarchy.h"		// for kAtTheEnd

/**
	@ingroup layout_util
*/
class IHierarchyUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHIERARCHYUTILS };

		/** Add an item to the hierarchy. Processes a kAddToHierarchyCmdBoss command.
		@parent db			The database the page item is in (what document)
		@param itemToAdd	The page item we want to add to the hierarchy
		@param parent		itemToAdd's new parent
		@param pos			itemToAdd will appear as the n'th child of parent, or the last if pos is not specified.
        @return 			kSuccess if it worked.
		*/
	virtual ErrorCode AddToHierarchy(IDataBase *db, UID itemToAdd, UID parent, int32 pos = IHierarchy::kAtTheEnd) = 0;

		/** Add an item to the hierarchy. Processes a kAddToHierarchyCmdBoss command.
		@param itemToAdd	The page item we want to add to the hierarchy
		@param parent		itemToAdd's new parent
		@param pos			itemToAdd will appear as the n'th child of parent, or the last if pos is not specified.
        @return 			kSuccess if it worked.
		*/
	virtual ErrorCode AddToHierarchy(const UIDRef& itemToAdd, UID parent, int32 pos = IHierarchy::kAtTheEnd) = 0;

		/** Remove an item from the hierarchy. Processes a kRemoveFromHierarchyCmdBoss command.
		@param itemToRemove	The page item we want to add to the hierarchy
        @return 			kSuccess if it worked.
		*/
	virtual ErrorCode RemoveFromHierarchy(const UIDRef& itemToRemove) = 0;

		/** Filter out items from a list that don't have the same spread UID as the given UID.
			Typically used to remove all items not on a given spread, passing iHierarchy->GetSpreadUID() for keepSpreadUID.
		@param keepSpreadUID	IN, The spread UID to keep items from.
		@param itemList			IN/OUT, The page item list to process.
        @return 				void.
		*/
	virtual void FilterItemsFromOtherSpreads(UID keepSpreadUID, UIDList* itemList) = 0;

		/**	Collapse a list of one or more page UIDs into their parent spread UIDs. May return empty list.
			@param pageUIDList			IN, a UIDList reference containing one or more page UIDs. 
			@param spreadUIDList		IN/OUT, a filled out UIDList of spread UIDs. May be empty depending on bCompleteSpreadsOnly parameter.
			@param bCompleteSpreadsOnly	IN, pass kTrue if you only want spreads with all their pages in pageUIDList, kFalse to get partially represented spreads as well.
		 */
	virtual void CollapsePageUIDsToSpreadUIDs(const UIDList& pageUIDList, UIDList* spreadUIDList, const bool16 bCompleteSpreadsOnly) = 0;

		/**	Expand a list of one or more spread UIDs into their constituent page UIDs. The input spreadUIDList may also
			contain page UIDs, in which case they are simply copied into the pageUIDList.
			@param spreadUIDList	IN, a UIDList reference containing one or more spread UIDs
			@param pageUIDList		IN/OUT, the filled out list of page UIDs belonging to the passed in spreads. 
		 */
	virtual void ExpandSpreadUIDsToPageUIDs(const UIDList& spreadUIDList, UIDList* pageUIDList) = 0;
	
		/** Expand a single page, find it's section, then gather all the pages that fall in this section
			@param pageRef	IN, a UIDRef to a page
			@param bRequireNamedLayout - if kTrue, the pages returned will all be in a named layout. May span several non-named sections.
			@param pageUIDList	IN/OUT, the filled out list of all the pages that are in the same section as pageRef.
		*/
	virtual void ExpandPageUIDToSection(const UIDRef& pageRef, UIDList* pageUIDList, const bool16 bRequireNamedLayout) = 0;

		/** Given a list of pages, divide them into a vector by sections.
			@param pageUIDList IN, a UIDList reference containing one or more page UIDs. 
			@param pagesBySection	IN/OUT, a vector filled out with pages in each entry by section.
			@param bRequireNamedLayout - if kTrue, the pages returned in each vector will all be in a named layout. May span several non-named sections.
		*/
	virtual void CollapsePageUIDsToSections(const UIDList& pageUIDList, K2Vector<UIDList>& pagesBySection, const bool16 bRequireNamedLayout) = 0;

	/** Get the parent of an object taking into account inlines and other cases that don't follow
		the usual hierarchy.
		@param pi	IN, The page item who's parent we would like.
        @return 	the parent object or nil if no parent.
		*/
	virtual IHierarchy * QueryEffectiveHierarchyParent(IHierarchy* pi) const = 0;
};


#endif	// __IHierarchyUtils__
