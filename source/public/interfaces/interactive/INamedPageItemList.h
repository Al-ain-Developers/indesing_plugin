//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/INamedPageItemList.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __INamedPageItemList_h__
#define __INamedPageItemList_h__

#include "IPMUnknown.h"
#include "BehaviorID.h"
#include "K2Vector.h"

//========================================================================================
// CLASS INamedPageItemList
//========================================================================================

/** Add-in interface on a document that contains annotations added to the document
	There are 3 implementations of this on the document, one for movies, one for sounds,
	and one for form fields.  This is used by behavior ui to present lists of movies or
	form fields when adding/editing a behavior that uses these items as parameters
	Examples are play movie, submit form, reset form, show/hide fields.  This interface
	provides a convenient way of getting a UID list of all the form fields or movies that
	currently exist in a document.
*/
class INamedPageItemList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INAMEDPAGEITEMLIST };
	
	/** Add a page item to the list. This is done automatically by a document responder,
		so there is no other reason why this should  be  called */
	virtual void			Add(const UID& pageItem) = 0;

	/** Remove a page item from the list. This is done automatically by a document responder,
		so there is no other reason why this should  be  called */
	virtual void			Remove(const UID& pageItem) = 0;
	
	/** Test an item for presence in the list.
		@return kTrue if the item is in the named page item list*/
	virtual bool16			ItemIsInList(const UID& pageItem) const = 0;

	/** Test a list of items for presence in the list.
		@return kTrue if any of the items are in the named page item list*/
	virtual bool16			AnyItemIsInList(const UIDList& pageItems) const = 0;

	/** Test a list of items for presence in the list.
		@return kTrue if all of the items are in the named page item list*/
	virtual bool16			AllItemsAreInList(const UIDList& pageItems) const = 0;
	
	/** Get the entire list of page item UIDs */
	virtual K2Vector<UID>	Get() const = 0;
};

#endif // __INamedPageItemList_h__
