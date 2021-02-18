//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPathSelectionSuite.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IPATHSELECTIONSUITE__
#define __IPATHSELECTIONSUITE__

#include "IPMUnknown.h"

#include "LayoutUIID.h"
#include "PathSelectionList.h"
#include "PMRect.h"

class IGraphicsContext ;

/**
	Suite interface to support selection over paths. Based on IPathSelection, 
	IPathSelectionSuite lives on the selection manager boss. With the 
	exception of drawing, most methods forward to the IPathSelectionTarget on
	the concrete layout selection boss.
	@see IPathSelection
	@see IPathSelectionTarget

	@ingroup layout_suite
*/
class IPathSelectionSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHSELECTION_SUITE } ;

	/** Toggles path selection mode on/off */
	virtual void ActivatePathSelection( bool16 isPathSelection ) = 0 ;
	/** Returns kTrue if the current selection is a path selection */
	virtual bool16 IsPathSelectionActive() const = 0 ;

	/** Selects a path component */
	virtual ErrorCode SelectPageItemPathPoint( const UIDRef& item, const PointSelector& handleID, bool16 drawit = kFalse ) = 0 ;
	/** Selects a set of path components of an item */
	virtual ErrorCode SelectPageItemPathPoints( const UIDRef& item, const PointSelectorList& pts, bool16 drawit = kFalse ) = 0 ;
	/** Selects a list of path components */
	virtual ErrorCode SelectPathPoints( const PathSelectionList& list, bool16 drawit = kFalse ) = 0 ;
	/** Selects all path components of these items */
	virtual ErrorCode SelectEntirePageItem( const UIDList& itemList, bool16 drawit = kFalse ) = 0 ;

	/** Replaces currently selected path components with others */
	virtual ErrorCode ReplacePathSelection( const PathSelectionList& add, bool16 drawit = kFalse ) = 0 ;
	/** Replaces certain path components in the selection with others */
	virtual ErrorCode AlterPathSelection( const PathSelectionList& drop, const PathSelectionList& add, bool16 drawit = kFalse ) = 0 ;
	/** Replaces currently selected path components with all path components of these items */
	virtual ErrorCode Replace_( const UIDList& itemList, bool16 drawit = kFalse ) = 0 ;



	/** Deselects a path component */
	virtual ErrorCode DeselectPageItemPathPoint( const UIDRef& item, const PointSelector& handle, bool16 drawit = kFalse ) = 0 ; //Deselect
	/** Deselects these path components for this item */
	virtual ErrorCode DeselectPageItemPathPoints( const UIDRef& item, const PointSelectorList& pts, bool16 drawit = kFalse ) = 0 ; //Deselect
	/** Deselects these path components */
	virtual ErrorCode DeselectPathPoints( const PathSelectionList& list, bool16 drawit = kFalse ) = 0 ; //Deselect
	/** Deselects all path components of these items */
	virtual ErrorCode DeselectEntirePageItem( const UIDList& itemList, bool16 drawit = kFalse ) = 0 ; //Deselect
	/** Deselects all path components */
	virtual ErrorCode DeselectAllPaths( bool16 drawit = kFalse ) = 0 ; //DeselectAll




	/** Returns kTrue if there are no path components selected */
	virtual bool16 IsPathSelectionEmpty() const = 0 ; //IsEmpty
	/** Returns kTrue if one or more path components on this item are selected */
	virtual bool16 IsAnyPageItemPathPointSelected( const UIDRef& item ) const = 0 ; //IsSelected
	/** Returns kTrue if this path component on this item is selected */
	virtual bool16 IsPageItemPathPointSelected( const UIDRef& item, const PointSelector& handle ) const = 0 ; //IsSelected

	/** Return number of objects with path components selected */
	virtual int32 CountPathSelectedPageItems() const = 0 ; //Length
	/** Retrieves the items with selected path components */
	virtual UIDList GetPathSelectedPageItems() const = 0 ; //GetItemList

	/** Return number of path components selected on object */
	virtual int32 CountPathSelectors( const UIDRef& item ) const = 0 ; //Length
	/** Retrieves the selected path components of an item */
	virtual void GetSelectorList( const UIDRef& item, PointSelectorList& ptsOut ) const = 0 ; //GetComponentList

	/** Get entire selection */
	virtual const PathSelectionList& GetPathSelection() const = 0 ; //GetSelection

	/** Returns kTrue if all points (and thus all segments as well) on the object are selected */
	virtual bool16 IsEntirePageItemSelected( const UIDRef& item ) const = 0 ; //IsEntireObjectSelected
	/** Returns kTrue if all points (and thus all segments as well) on the object's path are selected */
	virtual bool16 IsEntirePathSelected( const UIDRef& item, int32 pathIndex ) const = 0 ; //IsEntirePathSelected


	/** Returns kTrue if only a single anchor point (and one or both contiguous segments) is selected */
	virtual bool16 IsSinglePoint( UIDRef* theItem = nil, PointSelector* thePoint = nil ) const = 0 ;
	/** Returns kTrue if only a single segment is selected */
	virtual bool16 IsSingleSegment( UIDRef* theItem = nil, PointSelector* theSegment = nil ) const = 0 ;
	/** Returns kTrue if two contiguous segments are selected (and nothing else) */
	virtual bool16 IsTwoContiguousSegs( UIDRef* theItem = nil, PointSelector* thePoint = nil ) const = 0 ;
} ;

#endif	// __IPATHSELECTION__
