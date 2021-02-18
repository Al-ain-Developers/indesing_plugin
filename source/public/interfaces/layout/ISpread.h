//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISpread.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __ISPREAD__
#define __ISPREAD__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "PMRect.h"
#include "TransformTypes.h"

class IDocumentLayer;
class ISpreadLayer;
class IHierarchy;
class IGeometry;
class UIDList;
class IColumns;

/** Helper class for iterating spreads.
	@ingroup layout_spread
	@see ISpread
	@see kSpreadBoss
*/
class ItemManipulator
{
public:
	/**
		ManipulateItem - Called once for each item iterated over by ISpread::ForEachItem.
			Note:  ForEachItem iterates in drawing order and includes all
			layers (including non-printing, hidden, etc.) unless a LayerMask
			is provided.  Iteration stops if false is returned.
	
		@param	itemHier
		@return	bool16 - true == continue; false == stop iteration
	*/
	virtual bool16 ManipulateItem(IHierarchy * itemHier) = 0;
};

/** Helper class for controlling iteration over spreads.
	@ingroup layout_spread
	@see ISpread
	@see kSpreadBoss
*/
class LayerMask
{
public:
	/**
		MaskOutLayer - Return true to prevent ISpread::ForEachItem from iterating
			over the items in the given layer. Useful for skipping guide layers or the pages layer.
	
		@param	layerHier
		@return	bool16 - true == skip this layer; false == don't skip this layer
	*/
	virtual bool16 MaskOutLayer(IHierarchy * layerHier) = 0;
};

/** 
	Abstract interface that represents a spread, a container for pages (kPageBoss) and page items. 
	The list of spreads (kSpreadBoss) is kept in the ISpreadList off the document (kDocBoss). A spread (kSpreadBoss)
	is the root of all drawable page item's IHierarchies (except for inlines) - pages are just elements in one layer
	of the spread's hierarchy, pages are not parents of other page items.

	@see kSpreadBoss
	@see ISpreadList
	@see kDocBoss
	@see kPageBoss
	@ingroup layout_spread
 */
class ISpread : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPREAD };

	typedef enum	{ kDefaultBinding = -1, kBindingAtBeginning = 0, kBindingAtEnd = -2} BindingLocation;
	typedef enum	{ kDefaultBindingSide = -1, kLeftSideOfBinding = 0, kRightSideOfBinding = -2} BindingSide;
	typedef enum	{ kFollowMasterColorUID = 1 } PageColorLabel;

	/**
		QueryLayer - Return the spread layer associated with the given document layer; adds a ref count to the interface

	
		@param IN	docLayer - document layer whose corresponding SpreadLayer you want
		@param OUT	pPos - returned position of the spread layer within the spread (may be nil)
		@param IN 	wantGuideLayer - kTrue == return the corresponding spread guide layer; kFalse == return the normal spread layer (default = kFalse)
		@return	ISpreadLayer* - spread layer corresponding to the supplied document layer
	*/
	virtual ISpreadLayer * QueryLayer(const IDocumentLayer * docLayer, int32 * pPos = nil, bool16 wantGuideLayer = kFalse) const = 0;

	/**
		QueryPagesLayer	- return the special "Pages" layer - the non-editable, non-UI layer containing the page shapes
	
		@return	IHierarchy*	of the pages layer
	*/
	virtual IHierarchy * QueryPagesLayer() const = 0;
	
	enum { kAtTheEnd = -1 };

	/**
		GetItemsOnPage - return a list of all items in this spread's hierarchy that are "owned" by the given page. An item that
			overlaps more than one page is "owned" by the one its spread aligned bounding box intersects the most with by area (or the one with
			the smallest page index in case of a tie).
			This is used to decide what page items should be moved when a page is moved to another sppread. Note this does *not* include
			master items (because they aren't in the same hierarchy), and it may contain the page shape itself, if bIncludePage is kTrue.
	
		@param	IN pgPos - zero based index, which page in the spread
		@param	OUT items - UIDList of items owned by the given page
		@param	IN bIncludePage - kTrue == include the page shape itself; kFalse == don't
		@param	IN bIncludePasteboard  - kTrue == include items that are owned by the pasteboard in the returned list also
		@param	IN bIncludeBleedAndSlug  - kTrue == include items that are within the bleed/slug area for this page.
	*/
	virtual void GetItemsOnPage(int32 pgPos, UIDList * items, bool16 bIncludePage = kTrue, bool16 bIncludePasteboard = kFalse, bool16 bIncludeBleedAndSlug = kTrue) const  = 0;

	/**
		PartitionPageItems - returns lists of all the items on this spread's layers that are "owned" by each page. An item that
			overlaps more than one page is "owned" by the one that its item-aligned bounding box intersects the most with by area 
			(or the one with the smallest page index in case of a tie).
			This is used to decide what page items should be moved when a page is moved to another sppread. Note this does *not* include
			master items (because they aren't in the same hierarchy), and it may contain the page shape itself, if bIncludePage is kTrue.
			The partition parameter is a C array of (numPages + 1) pointers to UIDLists that the caller must allocate.  The last UIDList is
			for returning items that are not owned by any page but are completely in the pasteboard margins.  Individual pointers themselves
			may be nil if you are not interested in items on certain pages. Or individual pointers may be equal if you want to pile together
			items on more than one page into a single list maintaining their z-order.  For example, you may make every UIDList* before a page
			index (say i) point to one UIDList, the UIDList* at index i paoint to a second UIDList, and every UIDList* after i point to a 
			third UIDList. If pasteboardIndex >= 0 or less than numPages, the pasteboard items will be added to that page's UIDList in
			addition to adding them to partition[numPages].  (Note passing numPages for pasteboardIndex does not mean add pasteboard items
			to the last UIDList twice, it means don't add pasteboard items to any other UIDList other than the last.)
			Note that every item on every layer is logically added to exactly one of the UIDLists in partition[].  If some UIDList* pointers
			are nil, or if pasteboardIndex >= 0 and < numPages, or if bIncludePage is false, this won't be strictly true in the
			obvious ways.
			
			Note that PartitionPageItems is a generalization of GetItemsOnPage and is more efficient, more convenient, and more
			informative than calling GetItemsOnPage several times.  PartitionPageItems is no less efficient than GetItemsOnPage
			even if you require only a one UIDList answer.
	
		@param	OUT partition - an array of numPages + 1 pointers to UIDLists that the caller must allocate
		@param	IN bIncludePage - kTrue == include the page shape itself; kFalse == don't
		@param	IN pasteboardIndex  - 0-based index into partition for which UIDList to add pasteboard items to in addition to adding them to *partion[numPages]
		@param	IN bIncludeBleedAndSlug  - kTrue == include items that are within the bleed/slug area of each page.
	*/
	virtual void PartitionPageItems( UIDList* partition[], bool16 bIncludePage, int32 pasteboardIndex, bool16 bIncludeBleedAndSlug) const = 0;

	virtual void PartitionPageItems( const K2Vector<PMRect>& rects, const K2Vector<PMMatrix>& rect2SpreadTransforms, UIDList* partition_[], int32 pasteboardIndex) const = 0;

	/**
		GetNumPages - return the number of pages in this spread
	
		@return	int32 - the number of pages in this spread
	*/
	virtual int32 GetNumPages() const = 0;

	/**
		QueryNthPage - return the IGeometry of the n'th page. Adds a reference to the returned interface.
	
		@param	n - zero based page index
		@return	IGeometry* - n'th page's IGeometry
	*/
	virtual IGeometry * QueryNthPage(int32 n) const = 0;

	/**
		GetNthPageUID - return the UID of the indexed page (kInvalidUID if out of range)
	
		@param	n - zero based page index
		@return	UID - the UID of the indexed page (kInvalidUID if out of range)
	*/
	virtual UID GetNthPageUID(int32 n) const  = 0;

	/**
		QueryNearestPage - return the IGeometry of the nearest page to the given point in Pasteboard coordinates. Adds a reference to the returned interface.
	
		@param	pt - [IN] - pt in Pasteboard coordinates
		@param	pageIndex - [OUT] - page index of nearest page
		@return	IGeometry* - n'th page's IGeometry
	*/
	virtual IGeometry * QueryNearestPage(const PBPMPoint& pt, int32 * pageIndex) const  = 0;

	/**
		GetPageIndex - return the index of the page corresponding to the passed UID (or -1 if not in this spread)
			this is the inverse of GetNthPageUID
	
		@param	pageID - UID of page
		@return	int32 - index of page with UID pageUID
	*/
	virtual int32 GetPageIndex(UID pageID) const  = 0;

	/**
		ForEachItem - Iterates over all items in the spread.  The "manipulator" is called for each item.  Groups
			are not traversed into.  All layers are transversed (including hidden, non-printing, etc.),
			unless a LayerMask is provided.  

	
		@param	IN manipulator - the object called back with each item on the spread
		@param	IN layerMask - a filter call back (see LayerMask)
		@return	bool16 - Returns kFalse, if iteration was terminated due to the
			manipulator returning kFalse.  Returns kTrue if all items on all layers satisfying the
			LayerMask were traversed.
	*/
	virtual bool16 ForEachItem(ItemManipulator * manipulator, LayerMask * layerMask = nil) const  = 0;

	/**
		GetPagesBounds - Returns the bounding box that tightly encloses
				all the pages on the spread in the given coordinate system.

		@param	IN coordinateSpace - either Transform::PasteboardCoordinates() or Transform::SpreadCoordinates()
		@return	PMRect - bounding box that tightly encloses all the pages on the spread.
	*/
	virtual PMRect GetPagesBounds( const Transform::CoordinateSpace& coordinateSpace) const  = 0;

	/**
		GetPagesAndItemsBounds - Returns a bounding box that tightly encloses (in the given coordinate system)
				all the pages on the spread plus any page items sitting on the pasteboard.
	
		@param	IN coordinateSpace - either Transform::PasteboardCoordinates() or Transform::SpreadCoordinates()
		@param	includeGuides - kTrue == include enough space vertically to include horizontal guides and enough space 
			horizontally to include vertical guides; kFalse = ignore guides
		@return	PMRect
	*/
	virtual PMRect GetPagesAndItemsBounds( const Transform::CoordinateSpace& coordinateSpace, bool16 includeGuides = kFalse) const  = 0;


	/**
		GetSpreadZeroPoint - Returns the zero point for this spread by getting zero point pref
			for the pub and calculating where that spread-relative point falls
			on this spread.
	
		@return	PMPoint
	*/
	virtual PMPoint GetSpreadZeroPoint() const  = 0;
	
	/**
		QueryNearestColumnBounds - Used to locate the column nearest a point.
			In calculating the ColumnBounds we take into account 
			whether we are interested in a horizontal or vertical perspective
			For example, a vertical text frame in a horizontal column layout
			will be interested in aligning the right edge if pColumnBounds
			to pt.X(), while a horizontal text frame will want to align top
			with pt.Y().
	
		@param	IN pt - point in question
		@param	bIsVertical
		@param	OUT pColumnBounds - rectangle in spread coordinates for the size of the column
		@param	OUT pPageIndex - the index of the page containing the columns
		@param	OUT pColumnIndex - the column index
		@return	IColumns* - the column interface for the columns; adds a reference to this interface
	*/
	virtual IColumns * QueryNearestColumnBounds(const PBPMPoint& pt, bool16 bIsVertical, PMRect * pColumnBounds = nil,
									int32 * pPageIndex = nil, int32 * pColumnIndex = nil) const  = 0;
};

#endif
