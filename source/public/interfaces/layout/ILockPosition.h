//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILockPosition.h $
//  
//  Owner: Stacy Molitor
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
//  Purpose of Interface:
//  ILockPosition is an interface which specifies whether or not a page item's position is
//  locked.  If it's position is locked it cannot be moved, resized, deleted, etc.
//  
//  All page items should have this interface, though if it's missing the page item is assumed
//  to not be locked.
//  
//========================================================================================

#pragma once
#ifndef __ILockPosition__
#define __ILockPosition__

#include "IPMUnknown.h"
#include "GenericID.h"

/** Page item interface that controls if any item can have its position (or other geometry) changed or not.
*/
class ILockPosition : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILOCKPOSITION };

	typedef enum { kUnlock = 0x00, kLock = 0x01 } LockType;
	
	/**	 Set the lock position flag (kLock or kUnlock). Does not affect IItemLockData lock state. See kSetItemLockCmdBoss for more info.
		@param int32 - must be kLock or kUnlock.
	 */
	virtual void Set(int32 lockFlag) = 0;
	
	/**	 Return the lock position flag. In general, returns kUnlock or kLock based on the setting. However,
		 for managed frames, additional logic comes into play. A content item is considered locked whenever 
		 its parent frame has an insert lock. This means that IItemLockData->GetInsertLock is returns kTrue.
		 Also, for the graphic frame itself, InCopy will always consider the it locked--no frame manipulation allowed in InCopy.
		@return bool16 Returns kUnlock or kLock
	 */
	virtual int32 GetLockPosition() const = 0;
	
	/**	 Return kTrue if the page item's position is considered locked.
		@return bool16 Returns kTrue if GetLockPosition returns kLock, kFalse otherwise.
	 */
	virtual bool16 IsLocked() const = 0;
	
	/**	 Return kTrue if the page item's position is considered unlocked.
		@return bool16 Returns kTrue if GetLockPosition returns kUnlock, kFalse otherwise.
	 */
	virtual bool16 IsUnlocked() const = 0;

	/** Return kTrue if the LockPosition flag is locked. This does not consider managed frames and just 
	    returns the state that was Set. 
		@return int32 kLock or kUnlock 
	*/
	virtual int32 GetLockState() const = 0;

	/** return kTrue if the page item's locked state is set to locked. This does not consider managed frames.
		@return kTrue if lock state is kLock
	*/
	virtual bool16 IsLockStateLocked() const = 0;

	/** return kTrue if the page item is locked. This includes all layout items and groups, but excludes
	    guides.
		@param selecting - if kTrue, it will check and honor the Prevent Selecting Locked Items preference.
		@return kTrue if the item is appropriate and locked. if selecting is true then the preference above must 
		be must also be kTrue before an item will be considered locked.
	*/
	virtual bool16 IsPageItemLocked(bool16 selecting = kFalse) const = 0;

};

#endif //__ILockPosition__
