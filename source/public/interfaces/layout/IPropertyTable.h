//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPropertyTable.h $
//  
//  Owner: Hardeep
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IPropertyTable__
#define __IPropertyTable__

#include "IPMUnknown.h"

//Interfaces

//Utils & IDs
#include "LibraryProviderID.h"
#include "PMString.h"

typedef K2Vector<UID> PropUIDList;

/** An interface for storing property instances of a given storage class.  Used for library asset properties.
	@see IProperty
	@see IPropertyMgr
 */
class IPropertyTable : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPROPERTYTABLE };
	
	// ----- Storing Properties -----
	/** Store an instance of a property.
		@param item IN the UID of the item this property is associated with (e.g., library asset)
		@param propertyValue IN an interface pointer on the property being stored
	*/
	virtual void			StoreItemProperty(UID	item, IPMUnknown* propertyValue) = 0;

	/** Query the property of an item.
		@param item IN the UID of the item whose property is being sought
		@return an interface pointer on the property found, or nil if none found
	*/
	virtual IPMUnknown*		QueryItemProperty(UID item) = 0;
	
	/** Delete the property for a given item.
		@param item IN the UID of the item whose property is being deleted
		@return kTrue if deleted, kFalse if not found
	*/
	virtual bool16			DeleteItemProperty(UID	item) = 0;

	// ----- Properties as strings-----

	/** Create a string rendition of the property, if possible
		@param item IN the UID of the item whose property is being deleted
		@return a PMString form of the property, or an empty string
	*/
	virtual PMString		GetItemPropertyAsString(UID item) = 0;

	// ----- Comparing Properties -----
	/** Return the number of comparators supported by the property
		@return the number of comparators the property supports
	*/
	virtual int32			GetPropertyComparatorCount() const = 0;

	/** Get the name of a comparator
		@param compareIndex IN the index of the comparator
		@return the name of this comparator
	*/
	virtual PMString		GetNthPropertyComparatorName(int32 compareIndex) const = 0;

	/** Whether the comparator is negative (e.g., "Not equal")
		@param compareIndex IN the index of the comparator
		@return kTrue for a negative comparator; kFalse otherwise
	*/
	virtual bool16			IsComparatorNegative(int32 compareIndex) const = 0;
	
	/** Delete the property.  This allows the property to delete any UIDs it owns.
	*/
	virtual	void			Delete() = 0;

	// ----- Searching for Properties -----
	/** Get a list of items matching some criteria
		@param items OUT the matching items
		@param whichComparator IN the index of the comparator to use
		@param propertyValue IN an interface to the criteria value to compare against
		@param IN the items to compare (use all existing properties if nil)
	*/
	virtual	void			GetItemsMatchingCriteria( PropUIDList& items, int32 whichComparator, IPMUnknown* propertyValue, PropUIDList* fromList = nil) = 0;
};

#endif
 