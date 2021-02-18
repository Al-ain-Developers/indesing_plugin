//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGroupItemSuite.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IGROUPITEMSUITE__
#define __IGROUPITEMSUITE__

// ----- Interface files
#include "IPMUnknown.h"

// ----- ID files
#include "ShuksanID.h"	// for IID_IGROUPSUITE

/** Defines the interface for a group suite to be used in the selection architecture
	@ingroup layout_suite
 */
class IGroupItemSuite : public IPMUnknown
{
	public:
		/** kDefaultIID */
		enum { kDefaultIID = IID_IGROUPITEMSUITE };

		// ----- Abilities

		/** Check if current selected items can be grouped or not.
			
			@return bool16
			kTrue if can, kFalse otherwise.
		*/
		virtual bool16	CanItemsBeGrouped() = 0;

		/** Check if current selected items can be ungrouped or not.

			@return bool16
			kTrue if can, kFalse otherwise.
		*/
		virtual bool16  CanItemsBeUngrouped() = 0;

		/** Check if current selected item has both locked and unlocked items or not.

			@return bool16
			kTrue if we have both locked and unlocked items, kFalse otherwise.
		*/
		virtual bool16  HaveBothLockedAndUnLockedItems() = 0;

		/** Check if current selected item has both  and nonOverrideable items or not.

			@return bool16
			kTrue if we have both overrideable and nonOverrideable items, kFalse otherwise.
		*/
		virtual bool16  HaveBothOverrideableAndNonOverrideableItems() = 0;

		// ----- Actions

		/** Do group the items.
			
			@return ErrorCode as the execution result.
		*/
		virtual ErrorCode GroupItems() = 0;

		/** Do ungroup the items.
			
			@return ErrorCode as the execution result.
		*/
		virtual ErrorCode UngroupItems() = 0;

		/** Do group locked-items.
			
			@return ErrorCode as the execution result.
		*/
		virtual ErrorCode GroupLockedItems() = 0;

		/** Do lock grouped-items.
			
			@return ErrorCode as the execution result.
		*/
		virtual ErrorCode LockGroupedItems() = 0;

		/** Do group overrideable-items.
			
			@return ErrorCode as the execution result.
		*/
		virtual ErrorCode GroupOverrideableItems() = 0;

		/** Make grouped-items nonOverrideable.
			
			@return ErrorCode as the execution result.
		*/
		virtual ErrorCode MakeNonOverrideableGroupedItems() = 0;};

#endif		// __IGROUPITEMSUITE__