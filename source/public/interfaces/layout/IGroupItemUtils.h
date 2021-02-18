//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGroupItemUtils.h $
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
#ifndef __IGroupItemUtils__
#define __IGroupItemUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"

class UIDList;
class IDocumentLayer;


/** Utilities for answering items can be grouped or ungrouped.
	@ingroup layout_util
*/
class IGroupItemUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGROUPITEMUTILS };

	/**	Check if the give itmes can be grouped on the given document layer or not. 
	    If targetLayer is nil, active layer of front window will be used.
		@param items IN the items to check.
		@param targetLayer IN the document layer.
		@return bool16 kTrue if items can be grouped, otherwise return kFalse.
	*/
	virtual bool16 CanEnableGroup( const UIDList* items, IDocumentLayer* targetLayer = nil ) const = 0;

	/**	Check if the give itmes can be ungrouped or not. 
		@param items IN the given items.
		@return bool16 kTrue if items can be ungrouped, otherwise return kFalse.
	*/
	virtual bool16 CanEnableUngroup( const UIDList* items ) const = 0;

	/**	Iterate through the given items and get the transformed(skew, scale or rotate) group items.
		@param items IN the given items.
		@param transformedGroups OUT the item list contains the transformed group items.
		@return int32 the number of transformed group items.
	*/
	virtual int32 AccumulateTransformedGroups( const UIDList& items, UIDList* transformedGroups) const = 0;

	/**	Check if the give itmes has both locked and unlocked items or not.
		@param items IN the items to check.
		@return bool16 kTrue if there are mixed items, otherwise return kFalse.
	*/
	virtual bool16 HaveBothLockedAndUnLockedItems(const UIDList& itemList) const = 0;

	/**	Check if the give itmes has both overrideable or not overrideable items or not.
		@param items IN the items to check.
		@return bool16 kTrue if there are mixed items, otherwise return kFalse.
	*/
	virtual bool16 HaveBothOverrideableAndNonOverrideableItems(const UIDList& itemList) const = 0;

};


#endif	// __IGroupItemUtils__
