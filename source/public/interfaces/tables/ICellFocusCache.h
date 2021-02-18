//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellFocusCache.h $
//  
//  Owner: Joe Shankar
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
//  
//  Purpose: To cache cell attributes for all cells in a cell focus.
//  The cache, once built, is time stamped so that the system can tell
//  if the cache has changed.
//  
//========================================================================================

#pragma once
#ifndef __ICellFocusCache__
#define __ICellFocusCache__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "TableTypes.h"

class AttributeBossList;

/**
	Cache of attribute stores based on an associated CellFocus
	@see ICellFocus
	@see ICellFocusManager
*/
class ICellFocusCache : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICELLFOCUSCACHE };
	
	// How many values for a particular attribute, and it's value
	/**
		Returns the number of unique values the selection contains given a attribute's classID
		@param which	The classID of the attribute we are asking about
		@return int32	The count of unique values
	*/
	virtual int32				CountAttributes(ClassID which) const = 0;
	/**
		Returns the nth attribute of the given classID
		@param n		The nth entry in that attribute's list
		@param which	The classID of the attribute we are querying for
		@param iid		The interface id we are querying for
		@return IPMUnknown	The specific attribute
	*/
	virtual const IPMUnknown*	QueryAttributeN(int32 n, ClassID which, const PMIID iid) const = 0;

	// Notification for cache maintenance
	/**
		Notification when rows are inserted into the table, updates the cache appropriately
		@param rows The range of rows inserted
	*/
	virtual void	RowsInserted (const RowRange& rows ) = 0;
	/**
		Notification when columns are inserted into the table, updates the cache appropriately
		@param cols The range of columns inserted
	*/
	virtual void	ColsInserted (const ColRange& cols ) = 0;
	/**
		Notification when rows are deleted into the table, updates the cache appropriately
		@param rows The range of rows deleted
	*/
	virtual void	RowsDeleted  (const RowRange& rows ) = 0;
	/**
		Notification when columns are deleted into the table, updates the cache appropriately
		@param cols The range of columns deleted
	*/
	virtual void	ColsDeleted  (const ColRange& cols ) = 0;
	/**
		Notification when cells are merged in the table, updates the cache appropriately
		@param cells	The GridArea of the cells merged
	*/
	virtual void	CellsMerged	 (const GridArea& cells) = 0;
	/**
		Notification when cells are unmerged in the table, updates the cache appropriately
		@param cells	The GridArea of the cells unmerged
	*/
	virtual void	CellsUnmerged(const GridArea& cells) = 0;

	/**
		Notification when the whole table is deleted, updates the cache appropriately
	*/
	virtual void	TableDeleted() = 0;
	/**
		Notification when the attriubtes in the cell focus change, updates the cache appropriately
	*/
	virtual void	AttributesChanged(void) = 0;
	/**
		Clears the existing cache
	*/
	virtual void 	ClearCache(void) = 0;
	

	 /**
	 	Let's you check if the cache needs building.
	 	@return bool16  true if the cache needs rebuilding
	 */
	virtual bool16	CacheIsBuilt(void) const = 0;

	/**
		What is the time stamp, may build the cache if not already built.
		@return uint32	time stamp of last cache build
	*/
	virtual uint32	GetTimeStamp(void) const = 0;

	/**
		Copies the attributes into list. If an attribute is mixed it is put into mixedList.
		@param attrList	  The attriubte list to copy into the current one
		@param mixedList  Returns a list of attriubtes that are mixed (contain more then one attribute with different values) between the existing list and the one we just added
	*/
	virtual void	CopyToAttributeLists(AttributeBossList *attrList, AttributeBossList* mixedList = nil) = 0;

	/**
		Notification when table direction changes, updates the cache appropriately
		@param directionRTL new direction
	*/
    virtual void    TableDirChange(Tables::EDirection directionRTL) = 0;
};


#endif		// __ICellFocusCache__

