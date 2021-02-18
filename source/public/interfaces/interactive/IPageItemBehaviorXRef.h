//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IPageItemBehaviorXRef.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IPageItemBehaviorXRef_h__
#define __IPageItemBehaviorXRef_h__

#include "IPMUnknown.h"
#include "IBehaviorList.h"
#include "BehaviorID.h"
#include <vector>
#include <map>

/** A mapping of behavior UIDs and the page item UIDs they reference.
	When a behavior is created that references page items (Examples are
	play movie action, reset form action, show/hide fields) is created,
	it adds its referenced page items to this interface, using the Add method.
	When the behavior is deleted, the behavior is removed from the table using
	the Remove method.
	
	The purpose of this table, is to enable notification of a behavior when any of
	it's referenced page items are deleted.  The behavior then can be modified
	so that it doesn't reference the deleted page items any more.
	
	An implementation of IDeleteCleanup (kBehaviorDeleteCleanupImpl) will check
	this interface whenever a page item is deleted, and for each behavior that
	references the page item being deleted, will return commands that cleanup the
	behavior, obtained from the behavior's IDeleteCleanup interface.

	@see IDeleteCleanup
*/
class IPageItemBehaviorXRef : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_PAGEITEMBEHAVIORXREF };
	
	/** Add a referenced page item to a behavior.
		Should be done in the command that creates or edits the behavior
		@param pageItemUID a referenced page item
		@param behaviorUID a behavior that references the page item */
	virtual void Add(const UID& pageItemUID, const UID& behaviorUID) = 0;

	/** Remove a referenced page item from a behavior.
		Should be done in the command that deletes or edits the behavior
		@param pageItemUID a referenced page item
		@param behaviorUID a behavior that references the page item */
	virtual void Remove(const UID& pageItemUID, const UID& behaviorUID) = 0;
	
	/** Get a list of behaviors that currently reference a specified page item.
		@param a pageItemUID that may be referenced by a behavior
		@return a list of behaviors, specified by UID that reference pageItemUID */
	virtual std::vector<UID> Get(const UID& pageItemUID) const = 0;

	/** Get a list of pageitems that are currently referenced by the list of behaviors.
		@param a behaviorList that may refer pageItems
		@return a list of pageItems, referred by  behaviors passed(if any) */
	virtual std::vector<UID> Get(const IBehaviorList* behaviorList) const = 0;
};

#endif // __IPageItemBehaviorXRef_h__
