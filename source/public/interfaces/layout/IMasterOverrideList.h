//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMasterOverrideList.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IMasterOverrideList__
#define __IMasterOverrideList__

#include "IPMUnknown.h"
#include "MasterPageID.h"

/** An interface for a page (kPageBoss) which contains a list the master spread items 
	overridden on that page. 

	@ingroup layout_spread
	@see kPageBoss
	@see kMasterPagesBoss
*/
class IMasterOverrideList : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IMASTEROVERRIDELIST };
		
		/** @return count of how many master page items are overridden on this page */
	virtual int32	OverrideCount() = 0;

		/** add an override
			@param masterUID IN the UID of the master page pageitem being overridden,
		 	@param pageUID IN the UID of the replacing pageitem (on this page). if pageUID is kInvalidUID, the local override was a local deletion of the masterUID.
		*/
	virtual void	AddOverride(UID masterUID, UID pageUID) = 0;

		/** add a list of overrides
			@param masterOverrides IN the UID of the master page pageitems and page UIDs being overridden,
		*/
	virtual void	AddOverride(IMasterOverrideList *masterOverrides) = 0;

		/** remove a single previous override. 
			@param masterUID IN master item to remove from this list 
		*/
	virtual void	RemoveOverride(UID masterUID) = 0;

		/** remove all overrides on this page */
	virtual void	RemoveAllOverrides() = 0;

	/** GetNthOverrideIndex and GetOverride are separate because kInvalidUID is a valid value of
		GetOverride - i.e. a master page item could be locally deleted, in which case the 
		local UID is kInvalidUID, but the index is not -1 (so we can decide to not draw the item)
		There could be two routines (IsOverridden(UID) & GetOverride(UID)), but that would require
		an extra PersistUIDList lookup when drawing a local override.

		GetOverrideIndex returns the index of the local override. the value of this index is only
		useful in calls to GetOverride, or to compare against -1, which means it wasn't found (i.e.
		the item isn't overridden)

		@param mpUID IN Master page UID.
		@param nthOverride IN One master page can be overriden more than once (was GetOverrideIndex).
		@return the index of the nth override.
		@see GetOverrideIndexCount
	*/
	virtual int32 GetNthOverrideIndex( UID mpUID, int32 nthOverride ) const = 0;


	/** GetOverrideIndexCount returns the number of overrides for a master page item.
		@param mpUID IN Master page UID.
		@return the index of the nth override.
		@see GetNthOverrideIndex
	*/
	virtual int32 GetOverrideIndexCount(UID mpUID) const = 0;

	/** HasOverrides returns whether a master page item has any overrides.
		@param mpUID IN Master page UID.
		@return kTrue if a master page item has any overrides.
	*/
	virtual bool16 HasOverrides( UID mpUID ) const = 0;

	/** index through all overrides in a given list
		@param index IN index of override
		@param mpUID OUT master page page item UID, overridden on this page
		@param pgUID OUT page item UID on this page (kInvalidUID, if deleted)
	*/
	virtual void	GetOverridePair(int32 index, UID *mpUID, UID *pgUID) = 0;

	/** return the UID of the overriding local page item at the given index. this index is returned
		from GetOverrideIndex. 
		@param idx IN index of overridden page item in this list
		@return UID of the overridden page item on this page
	*/
	virtual UID		GetOverride(int32 idx) = 0;

};

#endif
