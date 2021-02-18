//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAMLockable.h $
//  
//  Owner: Bill Tislar
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
#ifndef __IAMLOCKABLE__
#define __IAMLOCKABLE__

#include "IPMUnknown.h"
#include "workgroupid.h"

#include <map>

/** The IAMLockable interface represents the lock for an asset. Implementations are responsible
	for determining the correct lock state and for interacting with the underlying asset management
	system to change the lock state as needed.
*/

class IAMLockable : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAMLOCKABLE };
	

	/** Possible IAMLockable lock states for an asset. These states are mutually exclusive.	
	*/	
	enum LockState
	{
		enUndefined = 0,	/** Default before object initialization or if locking is not supported. */
		enUnavailable,		/** Cannot be locked at this time; e.g., new asset not yet saved. */
		enAvailable,		/** Can be locked (currently unlocked). */
		enLocked,			/** Asset is locked other than here. */
		enCheckedOut		/** Locked here (note that all other instances of IAMLockable will report enLocked). */
	};

	/** Tests if the asset is locked anywhere. Call VerifyState (see below) before calling this method.
		@return kTrue if the LockState is either enLocked or enCheckedOut; kFalse otherwise.
	*/
	virtual bool16 IsLocked() = 0;
	
	/** Tests if the asset has the lock (is locked here).
		@param objectUID is the UID of the model object associated with the lock.
		@return kTrue if the LockState is enCheckedOut; kFalse otherwise.
	*/
	virtual bool16 HasLock( UID objectUID = kInvalidUID ) = 0;
	
	/** Retrieves the cached LockState. To get the latest LockState, call IAMLockable::VerifyState().
		@param objectUID is the UID of the model object associated with the lock. 
		@return cached LockState (not guaranteed to be current unless this method is called immediately
			after calling IAMLockable::VerifyState(). If the implementation of this interface supports
			locking at the individual page item level, then this method returns the IAMLockable::enCheckedOut
			state only if the lock is held for the specified objectUID.
	*/
	virtual IAMLockable::LockState GetLockState( UID objectUID = kInvalidUID ) = 0;
	
	/** Retrieves the UID of the model object associated with the lock.
		@return UID of a model object, or kInvalidUID.
	*/
	virtual UID GetLockObjectUID() = 0;
	
	/** Retrieves the cached lock status data as PMStrings. To get the latest status, call
		IAMLockable::VerifyState before calling this method.
		@param stringTable to be populated by the lock status <key/value> pairs. A <key/value> pair
			consists of the IManagedStatus::WGStatusType and the corresponding PMString value. If possible,
			implementations for story locks should provide at least the following status data:
		
				IManagedStatus::enCheckedOutBy
				IManagedStatus::enCheckedOutApp
				IManagedStatus::enCheckedOutDoc
		
			Omitting status data is not considered an error; however, UI alerts and status messages may be
			incomplete. Similarly, callers of this interface may safely ignore any unneeded data that an
			implementation provides.	
		@see IManagedStatus.
	*/
	virtual void GetLockStatusStrings( std::map<int32, PMString> & stringTable ) = 0;
	
	/**	Sets the lock by changing the LockState from enAvailable to enCheckedOut (or enLocked if userName
		that is passed in that is not equal to currentUser). This method fails if the current LockState is
		not enAvailable.
	    @param uiFlags standard flags for specifying permissible UI in performing this method.
	    @param allowOverride when kTrue, allows changing of lock state even if the state is not currently
			IAMLockable::enAvailable.
	    @param userName the user owning the lock file. If nil then the currentUser will be used.
	    @param objectUID is the UID of the model object associated with the lock.
		@return kTrue if the lock was successful; kFalse otherwise.
	*/	
	virtual bool16 Lock( UIFlags uiFlags = kFullUI, bool16 allowOverride = kFalse, const PMString *userName = nil, UID objectUID = kInvalidUID ) = 0;
	
	/** Relocks the lock for the same lock owner by updating any lock data as necessary. Note that this
		method will not override a lock; to override, use IAMLockable::Lock() instead.
		@param uiFlags standard flags for specifying permissible UI in performing this method.
		@param allowOverride allow relock of asset not owned by current user. May not be supported by all
			implementations of IAMLockable.
		@param objectUID is the UID of the model object to be associated with the lock, for those implementations
			of this interface that support locking at the individual page item level.	
		@return kFalse if the relock operation failed or if the current lock state is not enCheckedOut.
			Implementations that do not require updating lock data should return kTrue. 
	*/
	virtual bool16 Relock( UIFlags uiFlags = kFullUI, bool16 allowOverride = kFalse, UID objectUID = kInvalidUID ) = 0;
	
	/**	Unlocks the lock by changing the LockState from enCheckedOut to enAvailable.
	    @param uiFlags standard flags for specifying whether to show ui related to this operation or not
		@param allowOverride allow unlock of asset not owned by current user. May not be supported by all
			implementations of IAMLockable.
		@param objectUID is the UID of the model object associated with the lock.
		@return kTrue if the unlock was successful; kFalse otherwise.
	*/
	virtual bool16 Unlock( UIFlags uiFlags = kFullUI, bool16 allowOverride = kFalse, UID objectUID = kInvalidUID ) = 0;
	
	/** Retrieves the actual (current) LockState by checking the lock token (or underlying asset management
		system). Depending on the implementation, calling this method could result in a significant time
		delay. Avoid calling this method during routine UI refreshes.
		@param uiFlags controls UI that may be displayed in determining the LockState. For example, progress
			notification (if necessary) may be displayed for kFullUI, by not for kSuppressUI.
		@param objectUID is the UID of the model object associated with the lock.	
		@return the current LockState.
	*/
	virtual IAMLockable::LockState VerifyState( UIFlags uiFlags = kFullUI, UID objectUID = kInvalidUID ) = 0;

	/** Tests if a specified user name has the lock.
		@param userName is the test user name.
		@return kTrue if locked for userName; kFalse otherwise.
	*/
	virtual bool16 IsLocked( const PMString & userName ) = 0;
}; // end IAMLockable interface

#endif // __IAMLOCKABLE__
