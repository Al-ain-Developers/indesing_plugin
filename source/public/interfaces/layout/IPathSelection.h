//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPathSelection.h $
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
#ifndef __IPATHSELECTION__
#define __IPATHSELECTION__

#include "IPMUnknown.h"

#include "LayoutUIID.h"
#include "PathSelectionList.h"
#include "PMRect.h"

class IGraphicsContext ;

/**
	A path selection may contain anchor points and/or path segments (collectively
	known as path components).
	An anchor point is indicated by PointSelector::Selector() == kAnchorPt.
	A path segment is indicated by PointSelector::Selector() == kSegment.
*/  
class IPathSelection : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHSELECTION } ;

	/** Toggles path selection mode on/off */
	virtual void ActivatePathSelection_( bool16 isPathSelection ) = 0 ;
	/** Returns kTrue if the current selection is a path selection */
	virtual bool16 IsPathSelectionActive_() const = 0 ;

	/** Selects a list of path components */
	virtual ErrorCode SelectPathPoints_( const PathSelectionList& list) = 0;
	/** Selects all path components of these items */
	virtual ErrorCode SelectEntirePageItem_( const UIDList& itemList) = 0;

	/** Replaces currently selected path components with others */
	virtual ErrorCode ReplacePathSelection_( const PathSelectionList& add) = 0;
	/** Replaces currently selected path components with all path components of these items */
	virtual ErrorCode Replace__( const UIDList& itemList) = 0;

	/** Deselects a path component */
	virtual ErrorCode DeselectPageItemPathPoint_( const UIDRef& item, const PointSelector& handle) = 0;
	/** Deselects these path components for this item */
	virtual ErrorCode DeselectPageItemPathPoints_( const UIDRef& item, const PointSelectorList& pts) = 0;
	/** Deselects these path components */
	virtual ErrorCode DeselectPathPoints_( const PathSelectionList& list) = 0;
	/** Deselects all path components of these items */
	virtual ErrorCode DeselectEntirePageItem_( const UIDList& itemList) = 0;
	/** Deselects all path components */
	virtual ErrorCode DeselectAllPaths_() = 0 ;

	/** Returns kTrue if there are no path components selected */
	virtual bool16 IsPathSelectionEmpty_() const = 0 ;
	/** Returns kTrue if one or more path components on this item are selected */
	virtual bool16 IsAnyPageItemPathPointSelected_( const UIDRef& item ) const = 0 ;
	/** Returns kTrue if this path component on this item is selected */
	virtual bool16 IsPageItemPathPointSelected_( const UIDRef& item, const PointSelector& handle ) const = 0 ;

	/** Return number of objects with path components selected */
	virtual int32 CountPathSelectedPageItems_() const = 0 ;
	/** Retrieves the items with selected path components */
	virtual UIDList GetPathSelectedPageItems_() const = 0 ;

	/** Return number of path components selected on object */
	virtual int32 CountPathSelectors_( const UIDRef& item ) const = 0 ;
	/** Retrieves the selected path components of an item */
	virtual void GetSelectorList_( const UIDRef& item, PointSelectorList& ptsOut ) const = 0 ;

	/** Get entire selection */
	virtual const PathSelectionList& GetPathSelection_() const = 0 ;

	/** Returns kTrue if all points (and thus all segments as well) on the object are selected */
	virtual bool16 IsEntirePageItemSelected_( const UIDRef& item ) const = 0 ;
	/** Returns kTrue if all points (and thus all segments as well) on the object's path are selected */
	virtual bool16 IsEntirePathSelected_( const UIDRef& item, int32 pathIndex ) const = 0 ;

	/** Returns kTrue if only a single anchor point (and one or both contiguous segments) is selected */
	virtual bool16 IsSinglePoint( UIDRef* theItem = nil, PointSelector* thePoint = nil ) const = 0 ;
	/** Returns kTrue if only a single segment is selected */
	virtual bool16 IsSingleSegment( UIDRef* theItem = nil, PointSelector* theSegment = nil ) const = 0 ;
	/** Returns kTrue if two contiguous segments are selected (and nothing else) */
	virtual bool16 IsTwoContiguousSegs( UIDRef* theItem = nil, PointSelector* thePoint = nil ) const = 0 ;

	/** Returns kTrue if the all points/segments on the item are selected */
	virtual bool16 IsFullySelected( const UIDRef& item ) const = 0;
} ;

#endif	// __IPATHSELECTION__
