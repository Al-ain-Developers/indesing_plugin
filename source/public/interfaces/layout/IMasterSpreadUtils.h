//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMasterSpreadUtils.h $
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
#ifndef __IMasterSpreadUtils__
#define __IMasterSpreadUtils__

#include "MasterPageID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "ICommand.h"
#include "UIDList.h"
#include "IShape.h"
#include "PMMatrix.h"
							  
class IStringListControlData;
class IMasterSpreadList;
class IDocument;
class ICallback;
class IMasterPage;


/** Utility interface to manipulate master spreads; please use the IMasterSpreadUtils via kUtilsBoss (see Utils.h).
	<pre>Utils<MasterSpreadUtils>()->IsFrontViewAMaster( ... ) ;</pre>

	@ingroup layout_spread 
	@ingroup layout_util
	@see kUtilsBoss
	@see kMasterPagesBoss
*/
class IMasterSpreadUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMASTERSPREADUTILS };
	
	/** @returns kFalse - obsolete, do not use */
	virtual bool16 _IsFrontViewAMaster() = 0;

	/** build a string list of master spread names.
		@param stringData IN an empty IStringListControlData OUT a list of master names
		@param masterUIDs IN an empty UIDList created with a valid database OUT a list of UIDs, parallel to stringData (i.e. the n'th UID corresponds to the n'th master name)
		@param bIncludeNone IN kTrue means include the string 'None'
		@param excludeUID IN if valid, skip this UID
	*/
	virtual void BuildMasterSpreadList(IStringListControlData *stringData, UIDList *masterUIDs, bool16 bIncludeNone, UID excludeUID) = 0;

	/** Return kTrue if masterA is an ancestor of masterB (i.e. if one of the pages of
		B has masterA applied to it, or if one of master B's masters has masterA applied to it, and so on recursively)
		@param masterList IN list of masters (containing masterA and masterB
		@param masterA IN potential ancestor master spread
		@parma masterB IN master being queried about
		@return kTrue if masterA is an ancestor of masterB; kFalse otherwise
	*/
	virtual bool16	IsAnAncestorOf(IMasterSpreadList *masterList, UID masterA, UID masterB) = 0;

	/** build a list of all masters applied to a given master or its ancestors
		@param masterSpreadList IN list of masters for a given document
		@param masterUID IN master spread whose ancestors are being requested
		@param ancestors OUT list of all masters applied to the specified master, or to those masters
	*/
	virtual void GetAncestorsOf(IMasterSpreadList *masterSpreadList, UID masterUID, UIDList *ancestors) = 0;
	
	/** sort the specified IMasterSpreadList such that masters with other masters applied to them are later in the list than the
		masters they derive from (e.g. if 'B-Master' has 'C-Master' applied, and 'A-Master' and 'C-Master' have 'None' applied, the
		sorted order would be 'A-Master', 'C-Master', 'B-Master'.). Useful for duplicating a master spread list to a new document.
		
		Warning: I think the above comment is wrong. It seems that TopoSortMasterSpread sorts all the masters so
		that a given master in the list depends only on masters appearing later in the list. That is the root masters
		are sorted to the end of the list and the most dependent masters are sorted to the beginning.
		
		@param masterSpreadList IN list of master spreads for a given document
		@param sortedList OUT sorted list of masters, base masters first, derived masters later.
	*/
	virtual void TopoSortMasterSpread(IMasterSpreadList *masterSpreadList, UIDList* sortedList) = 0;
	
	/** Returns kTrue if the specified master is applied to the specified page, or to one of its ancestors
		@param masterUID IN master being queried about
		@param page IN page being queried about
		@return	kTrue if page has masterUID applied to it (recursively)
	*/
	virtual bool16	IsMasterAppliedToPage(UID masterUID, IPMUnknown* page) const = 0;

	/** build a UID list of master spreads that are not applied to pages.
		@param doc IN The database to search.
		@return a UIDList of unused master spread UIDs
	*/
	virtual UIDList GetUnusedMasterUIDs(IDocument *doc) = 0;

	/** count the number of pages in the document that have one of the specified
		masters applied to it. optionally look at the masters also.
		@param masterUIDs IN list of masters being queried about
		@param mastersWithMaster OUT if not NIL, returns the count of master spreads with the specified masters applied
		@param pageUIDs OUT if not NIL, returns an array of page UIDs with the specified masters applied
	*/
	virtual int32 CountPagesWithMaster(UIDList *masterUIDs, int32 *mastersWithMaster = nil, UIDList *pageUIDs = nil) = 0;


	/** Given a master item and a layout page which has that master item drawing on it, override the master
		item and return the item corresponding to the passed in item. This may be different than the item
		which was overridden - in the case of a sub-item of a group, the returned item is the item corresponding
		to the passed in item, not the group (which was overridden). The undoability argument is for uses where the
		returned item is immediately modified, so the 'Override master item' doesn't need to show up in the Undo stack.
		
		Return value is kTrue if everything is OK, kFalse if the item wasn't overridden (which can happen if the
		specified master item wasn't drawing on the specified page, or if the item was already overridden)

		@param masterItem IN master item to override
		@param pageToOverrideOn IN page to override the item on
		@param undoability IN how should the override command be undone? default : ICommand::kAutoUndo
		@param overriddenItem OUT new page item corresponding to masterItem
		@return kTrue if success, kFalse otherwise
	 */	 
	virtual	bool16 OverrideMasterPageItem(const UIDRef masterItem, 
												const UIDRef pageToOverrideOn,
												ICommand::Undoability undoability = ICommand::kAutoUndo,
												UIDRef *overriddenItem = nil) = 0;	

	/**	determine if the given master page item is already overridden on the given page (may be a crossover
		and therefore overridden on a page other than the specified one)
		@param masterItem IN master page page item being queried about
		@param startPageUIDRef IN page being queried about
		@return kTrue if the given master page page item is overridden on the given page
	*/
	virtual	bool16	IsMasterItemOverriddenOnPage(const UIDRef masterItem, const UIDRef startPageUIDRef) = 0;

	/** Creates a OverrideMasterPageItemsCmd and feeds it with items based on the UIDList that is being passed in.
		@param spreadsOrPages. UIDList of spreads or pages.
		@param masterItemCollector OPTIONAL. Call back object being used for collecting master page items..
		@param drwMgrFlags OPTIONAL. Draw flags being used for collecting master page items..
		@return an executable command (kOverrideMasterPageItemCmdBoss).
	*/
	virtual ICommand *CreateOverrideMasterPageItemsCmd( const UIDList& spreadsOrPages, ICallback* masterItemCollector = nil, int32 drwMgrFlags = IShape::kSkipChildren + IShape::kSkipHiddenAndLockedLayers ) const = 0;


	/**	Creates a list of master page items, pages, and offsets for the master items that
		are drawn on the given spread and page bounds.
		@param db the database for the document to operate on
		@param theSpread the UID of the spread to collect the items from
		@param onThesePages the UIDs of the pages within this spread
		@param pageBounds the bounds of the pages (in spread coordinates). May be enlarged by bleed, slug, etc.
		@param masterItems OUT the returned list of items drawn on the spread
		@param pages OUT the page UID for the master page item (parallel list with masterItems)
		@param offsets OUT the offset of each master page item (parallel list with masterItems)
		@param masterItemCollector OPTIONAL. Call back object being used for collecting master page items.
		@param drwMgrFlags OPTIONAL. Draw flags to use for collecting master page items.
		@see ILayoutUtils::EnlargePagesRectBySlug
	 */
	virtual void AppendMasterPageItems(IDataBase * db, UID theSpread, 
						   const UIDList & onThesePages, 
						   const PMRectCollection & pageBounds,
						   UIDList & masterItems, 
						   UIDList &  pages, 
						   PMMatrixCollection & offsets,
						   ICallback* masterItemCollector = nil, 
						   int32 drwMgrFlags = IShape::kSkipChildren + IShape::kSkipHiddenAndLockedLayers) const = 0;


	virtual PMMatrix CalculateMasterSpreadToDrawingSpreadMatrix( const IMasterPage* drawingPage, UIDRef masterPage = kInvalidUIDRef /*if already known*/) const = 0;

};


#endif	// __IMasterSpreadUtils__
