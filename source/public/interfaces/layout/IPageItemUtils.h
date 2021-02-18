//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemUtils.h $
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
#ifndef __IPageItemUtils__
#define __IPageItemUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"

class ICommand;
class IControlView;
class IDataBase;
class IDocumentLayer;
class IGeometry;
class IGraphicFrameData;
class IHandleShape;
class IHierarchy;
class IItemContext;
class IPathGeometry;
class IScrapItem;
class ISpread;
class ISubject;
class IDocument;
class PMUnknownRefList;
class UIDList;
class LazyNotificationData;

// Includes
#include "PMRect.h"
#include "PMLine.h"
#include "IGeometry.h"
#include "PathSelectionList.h"
#include "PMPathPoint.h"
#include "K2Vector.h"

/**	
	Utilities for page items.
	Please use the IPageItemUtils directly via the Utils boss if possible:
		<pre> Utils<IPageItemUtils>()->GetPathInfo( ... ) ;</pre>
	@see Utils.h
	@ingroup layout_util
	@ingroup layout_pgitem
 */
class IPageItemUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMUTILS };

	/** Types of cache invalidation. */
	enum InvalidateCacheType
	{	
		/** The entire cache */
		kInvalidateAll,
		/** Guides only */
		kInvalidateGuides,
		/** Everything but guides */
		kInvalidateNonGuides
	};


	
	/** Invalidates the entire page item bounds cache for a document.
		@param doc [IN]The document whose cache to invalidate.
		@param type [IN] What to invalidate.
	*/
	virtual void InvalidatePageItemCache(IDocument * doc, InvalidateCacheType type = kInvalidateAll) const = 0;

	/** Invalidates the page item bounds cache for one spread.
		@param spread [IN] The spread whose cache to invalidate.
		@param type [IN] What to invalidate.
	*/
	virtual void InvalidatePageItemCacheForSpread(ISpread *spread, InvalidateCacheType type = kInvalidateAll) const = 0;


	/**
	Notify observers attached to the document's ISubject that the document has been changed.
	@param theChange is the actual change, often times the classID of a command.
	@param interestedIn specifies the interface of the object that was modified.
	@param changedBy is a generic pointer to the object that caused the change.  
	@param data is a cookie passed to observers, data could be nil. 
	This is usually a pointer to a command object
	*/
	virtual void NotifyDocumentObservers(IDataBase* iDataBase, ClassID theChange, const PMIID& interestedIn, void* changedBy, LazyNotificationData* data = nil) const = 0;

	/**
	Notify observers attached to the document's ISubject that the document has been changed.
	The difference between this method and the other NotifyDocumentObservers method is that the
	original Subject is passed along to the observers as the object that was changed,
	not the object this subject is part of.
	@param originalSubject is the original subject of the object that was changed
	@param theChange is the actual change, often times the classID of a command.
	@param interestedIn specifies the interface of the object that was modified.
	@param changedBy is a generic pointer to the object that caused the change.  
	@param data is a cookie passed to observers, data could be nil. 
	This is usually a pointer to a command object
	@see ISubject
	*/
	virtual void NotifyDocumentObservers(ISubject* originalSubject, IDataBase* iDataBase, ClassID theChange, const PMIID& interestedIn, void* changedBy, LazyNotificationData* data = nil) const = 0;
	
	/** Calculate the in-port and out-port positions for the textframe
		@param shape [IN] an IHandleShape pointer for the textframe page item
		@param point1 [IN/OUT] pointer to the location of the in-port for the textframe
		@param point2 [IN/OUT] pointer to the location of the out-port for the textframe
	*/
	virtual void GetTextFrameHandlePositions(IHandleShape* shape, PMPoint *point1, PMPoint *point2) const = 0;


	/** Sort a list of page items in drawing order.
		Assumes that all items in the
		list share the same ultimate root, but may have different parents.
		@param items [IN/OUT] A pointer to a UIDList of the items.
	*/
	virtual void SortDisplayList(UIDList *items) = 0;

	/** Finds the top-level pageitem parent of an inline (handles nested inlines).
		@param itemHierarchy [IN] the IHierarchy interface for an inline item.
		@return An IHierarchy interface for the pageitem which is the highest ancestor of the inline, or
		nil if itemHierarchy is not an inline (or if inline is overset). The reference count is incremented; caller is responsible 
		for calling Release().
	*/
	virtual IHierarchy *QueryInlineParentPageItem(IHierarchy *itemHierarchy) const = 0;

	/**
		Get the first page item UID associated with the passed in item.
		For non-text items it just returns the given UID.  For text items it returns 
		the UID of the first frame that contains the text.
		@param IDataBase *db: The document containing the page item and data link.
		@param UID pageitem: The page item of the associated data link.
		@return UID: Return kInvalidUID on failure. 
	*/
	virtual UID GetFirstPageItemUID(IDataBase *db, UID pageItemUID) const= 0;

	/** Strips items from the list if their parent is locked.  Does not strip if item is outermost
		item and is locked.
		@param items [IN/OUT] a UIDList of the pageitems
		@return a pointer the UIDList of the pageitems.
	*/
	virtual UIDList* StripIfParentIsLocked(UIDList* items) = 0;

	/** Finds the top-level pageitem parent of an placed item (which either is inline or image inside table cell).
		@param itemHierarchy [IN] the IHierarchy interface for an placed item.
		@return An IHierarchy interface for the pageitem which is the highest ancestor of the placed item, or
		nil if itemHierarchy is not an  placed item. The reference count is incremented; caller is responsible 
		for calling Release().
	*/
	virtual IHierarchy* QueryPlacedItemParentPageItem(IHierarchy *itemHierarchy) const = 0;

	/** Finds the immediate text frame pageitem parent of an inline (handles nested inlines).
		@param itemHierarchy [IN] the IHierarchy interface for an inline item.
		@return An IHierarchy interface for the text frame which is the immediate ancestor of the inline, or
		nil if itemHierarchy is not an inline (or if inline is overset). The reference count is incremented; caller is responsible 
		for calling Release().
	*/
	virtual IHierarchy *QueryInlineImmediateParentPageItem(IHierarchy *itemHierarchy) const = 0;
};

#endif	// __IPageItemUtils__
