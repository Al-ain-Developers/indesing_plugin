//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PathSelectionList.h $
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
#ifndef __PathSelectionList__
#define __PathSelectionList__

#include "K2Vector.h"
#include "KeyValuePair.h"
#include "PathTypes.h"
#include "UIDList.h"

#pragma export on

/**
	A path point selection may contain anchor points and/or path segments (collectively
	known as path components).
	An anchor point is indicated by PointSelector::Selector() == kAnchorPt.
	A path segment is indicated by PointSelector::Selector() == kSegment.
*/  
class PUBLIC_DECL PathSelectionList
{
public:
	/** Constructs empty list */
	PathSelectionList( IDataBase* db = nil ) ;

	/** Set the database */
	ErrorCode SetDataBase( IDataBase* db ) ;
	/** Get the database */
	IDataBase* GetDataBase() const { return fDB ; }

	/** Adds path component to selection */
	ErrorCode Add( const UIDRef& item, const PointSelector& handle ) ;
	/** Adds path components to selection */
	ErrorCode Add( const UIDRef& item, const PointSelectorList& pts ) ;
	/** Appends another path selection list onto this one */

	ErrorCode Add( const PathSelectionList& list ) ;

	/** Clears all path components */
	ErrorCode Clear() ;
	/** Clears all path components for this item */
	ErrorCode Clear( const UIDRef& item ) ;
	/** Clears this path component for this item */
	ErrorCode Clear( const UIDRef& item, const PointSelector& handle ) ;
	/** Clears these path components for this item */
	ErrorCode Clear( const UIDRef& item, const PointSelectorList& pts ) ;
	/** Clears these path components */
	ErrorCode Clear( const PathSelectionList& list ) ;

	/** Returns kTrue if there are no path components selected */
	bool16 IsEmpty() const ;
	/** Returns kTrue if one or more path components on this item are selected */
	bool16 IsSelected( const UIDRef& item ) const ;

	/** Returns kTrue if this path component on this item is selected */
	bool16 IsSelected( const UIDRef& item, const PointSelector& handle ) const ;


	/** Return number of objects with path components selected */
	int32 Length() const ;
	/** Return list of objects with path components selected */
	UIDList GetItemList() const ;

	/** Return number of path components selected on object */
	int32 Length( const UIDRef& item ) const ;
	/** Return list of path components selected on object */
	void GetComponentList( const UIDRef& item, PointSelectorList& ptsOut ) const ;

	/** */
	void ReadWrite (IPMStream* s, IDataBase* db);

	//Comparison operators
	/** */
	bool16 operator==( const PathSelectionList& other ) const ;
	/** */
	bool16 operator!=( const PathSelectionList& other ) const ;

private:
	IDataBase* fDB ;
	K2Vector<KeyValuePair< UID, PointSelectorList > > fSelection ;
} ;

#pragma export off

#endif
