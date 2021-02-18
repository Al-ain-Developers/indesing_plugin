//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IOverrideMasterPageItemData.h $
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
//  
//  Data interface for overriding master page items.
//  
//========================================================================================

#pragma once
#ifndef __IOverrideMasterPageItemData__
#define __IOverrideMasterPageItemData__

#include "IPMUnknown.h"
#include "MasterPageID.h"
#include "UIDRef.h" 
#include "PMReal.h"
#include "UIDList.h"
#include "PMMatrix.h"

/**	This class is used to pass data to the OverrideMasterPageItemCmdBoss and 
	retrieve data after the command has finished.

*/
class IOverrideMasterPageItemData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOVERRIDEMASTERPAGEITEMDATA };

		/** Initialization routine
			@param mpPageItemUIDs IN page item UIDs from the master pages 
			@param pageUIDs IN pages on which to override the master page items - must be same length as mpPageItemUIDs
			@param itemShifts IN horizontal shift for the master page items to correctly align on the page - must be same length as mpPageItemUIDs
		*/
	virtual void	SetOverrideMasterPageItemData(const UIDList &mpPageItemUIDs, const UIDList &pageUIDs, const PMMatrixCollection &itemShifts) = 0;
	
		/** @return how many page items were overridden */
	virtual int32	GetOverrideCount() = 0;		

		/**	return the triplet that identifies the 'whichItem' override. 
			(original item, page it is overridden on, new page item id)
			if the override was to delete the item or if the command hasn't
			finished yet, the newPageItemUID will be kInvalidUID.
			@param whichItem IN index of item
			@param overriddenMasterPagePageItem OUT UIDRef of the master page item which was overridden
			@param pageOverriddenOn OUT UIDRef of the page the new override belongs to
			@param newPageItemUID OUT UIDRef of the new page item (the override)
			@param itemShift OUT horizontal distance the overridden item was shifted to appear in the correct location (e.g. a item overridden from a single page master in a facing pages spread will have a shift of +/- (1/2 page width) )
		*/
	virtual bool16	GetNthOverride(	int32	whichItem,
									UIDRef *overriddenMasterPagePageItem,  
									UIDRef *pageOverriddenOn,
									UIDRef *newPageItemUID,
									PMMatrix	*itemShift) = 0;
		
		
		/**	Set the n'th override to the specified triplet. Used 
			internally by the command to set return data. 
			@param whichItem IN index of item to set values for
			@param overriddenMasterPagePageItem IN master page page item being overridden
			@param pageOverriddenOn IN page owning the overridden page item
			@param newPageItemUID IN overridden page item UID
			@param itemShift IN horizontal shift of master page item to page item
		*/
	virtual bool16	SetNthOverride(	int32	whichItem,
									UIDRef *overriddenMasterPagePageItem,  
									UIDRef *pageOverriddenOn,
									UIDRef *newPageItemUID,
									PMMatrix	itemShift) = 0;
									
		/** Get the list of master page items being overridden
			@return UIDList with master page items being overridden
		*/
	virtual const UIDList &GetMPItems() = 0;

		/** Get the list of pages where the overridden page items will be
			@return list of pages
		*/
	virtual const UIDList &GetPagesHit() = 0;

		/** Get the list of item shifts - horizontal shifts to align the master page item to the correct location
			@return list of page item shifts
		*/
	virtual const PMMatrixCollection &GetItemShifts() = 0;
};



#endif // __IOverrideMasterPageItemData__
