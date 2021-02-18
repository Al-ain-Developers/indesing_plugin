//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPathSelectionList.h $
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
#ifndef __IPathSelectionList__
#define __IPathSelectionList__

#include "PathSelectionList.h"
#include "LayoutID.h"

/**
	A path point selection may contain anchor points and/or path segments (collectively
	known as path components).
	An anchor point is indicated by PointSelector::Selector() == kAnchorPt.
	A path segment is indicated by PointSelector::Selector() == kSegment.
*/  
class IPathSelectionList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHSELECTIONLIST };
	/** Set the database */
//	virtual ErrorCode SetDataBase( IDataBase* db ) = 0 ;
	/** Get the database */
	virtual IDataBase* GetDataBase() const = 0 ;

	/** Set the entire selection */
	virtual ErrorCode SetSelection( const PathSelectionList& list ) = 0 ;
	/** Get the entire selection */
	virtual const PathSelectionList& GetSelection() const = 0 ;

	/** Adds path component to selection */
	virtual ErrorCode Add( const UIDRef& item, const PointSelector& handle ) = 0 ;
	/** Adds path components to selection */
	virtual ErrorCode Add( const UIDRef& item, const PointSelectorList& pts ) = 0 ;
	/** Appends another path selection list onto this one */
	virtual ErrorCode Add( const PathSelectionList& list ) = 0 ;

	/** Clears all path components */
	virtual ErrorCode Clear() = 0 ;
	/** Clears all path components for this item */
	virtual ErrorCode Clear( const UIDRef& item ) = 0 ;
	/** Clears this path component for this item */
	virtual ErrorCode Clear( const UIDRef& item, const PointSelector& handle ) = 0 ;
	/** Clears these path components for this item */
	virtual ErrorCode Clear( const UIDRef& item, const PointSelectorList& pts ) = 0 ;
	/** Clears these path components */
	virtual ErrorCode Clear( const PathSelectionList& list ) = 0 ;

	/** Returns kTrue if there are no path components selected */
	virtual bool16 IsEmpty() const = 0 ;
	/** Returns kTrue if one or more path components on this item are selected */
	virtual bool16 IsSelected( const UIDRef& item ) const = 0 ;
	/** Returns kTrue if this path component on this item is selected */
	virtual bool16 IsSelected( const UIDRef& item, const PointSelector& handle ) const = 0 ;

	/** Return number of objects with path components selected */
	virtual int32 Length() const = 0 ;
	/** Return list of objects with path components selected */
	virtual UIDList GetItemList() const = 0 ;

	/** Return number of path components selected on object */
	virtual int32 Length( const UIDRef& item ) const = 0 ;
	/** Return list of path components selected on object */
	virtual void GetComponentList( const UIDRef& item, PointSelectorList& ptsOut ) const = 0 ;
} ;

#endif
