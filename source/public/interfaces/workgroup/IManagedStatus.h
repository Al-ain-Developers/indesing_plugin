//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IManagedStatus.h $
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
#ifndef __IMANAGEDSTATUS__
#define __IMANAGEDSTATUS__

#include "IPMUnknown.h"
#include "workgroupid.h"

#include <map>
#include <vector>

class IAMStatusListener;
class IManageableAsset;

/** The IManagedStatus interface represents asset management status information for a managed asset.
	Each IManageableAsset instance should have its own IManagedStatus instance. The IManagedStatus
	instance is normally created during the IAMServiceProvider::enInitialize service and set by calling
	the IManageableAsset::SetStatus method. Custom implementations of this interface are allowed; however,
	most applications will find it convenient to define a custom status boss by subclassing kManagedStatusBoss,
	which uses the kManagedStatusImpl for this interface.
	@see IManageableAsset.
	@see IAMServiceProvider. 
*/
class IManagedStatus : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMANAGEDSTATUS };
	
	typedef std::vector<UIDRef> UIDRefList;
	typedef std::map<int32, PMString> StatusStringTable;
	typedef std::map<int32, PMRsrcID> StatusIconTable;
	typedef std::vector<IAMStatusListener*>	ListenerList;
	
	/** Predefined asset editing states */
	enum EditingState
	{
		/** default state */
		enUnknownEditingState	= 0,
		/** asset is not currently being edited */
		enNotEditing			= 1,
		/** this instance is being edited (edited here) */
		enEditingLocally		= 2,
		/** being edited elsewhere */
		enEditingRemotely		= 3,
		/** editing here and elsewhere at the same time */
		enEditingConflict		= 4
	};

	/** Prefined asset version states (for versioned asset) */
	enum VersionState
	{
		/** default state */
		enUnknownVersionState	= 0,
		/** local cache identical to latest version */
		enUpToDate				= 1,
		/** local cache has changes not checked in */
		enLocalIsNewer			= 2,
		/** local cache is older than latest version */
		enLocalIsOutOfDate		= 3,
		/** local cache has changes while newer version exists */
		enVersionConflict		= 4
	};

	/** Predefined status identifiers for status icons and strings. */
	enum WGStatusType
	{
		/** default status type */
		enInvalidWGStatus		= 0,
		/** general display status */
		enGeneralStatus			= kWorkgroupPrefix + 1,
		/** version status */
		enContent				= kWorkgroupPrefix + 2,
		/** editing status */
		enEditing				= kWorkgroupPrefix + 3,
		/** tooltip display status */
		enToolTip				= kWorkgroupPrefix + 4,
		
		//NOT USED				= kWorkgroupPrefix + 5,
		
		/** Current IAMLockable lock owner name */
		enLockOwner				= kWorkgroupPrefix + 6,
		/** Current LiveEdit user name */
		enCurrentUser			= kWorkgroupPrefix + 7,
		/** Current lock client name */
		enLockClient			= kWorkgroupPrefix + 8,
		/** Current client name */
		enCurrentClient			= kWorkgroupPrefix + 9,
		/** User name (for LiveEdit) */
		enCheckedOutBy			= kWorkgroupPrefix + 10,
		/** Application name (for LiveEdit */
		enCheckedOutApp			= kWorkgroupPrefix + 11,
		/** Document name (for LiveEdit */
		enCheckedOutDoc			= kWorkgroupPrefix + 12
	};

	
	/** This method adds an IAMStatusListener to the list for status notifications.
		@param listenerRef is a UIDRef of a boss with an IAMStatusListener interface.
		@see IAMStatusListener.
	*/						 
	virtual void AddListener( UIDRef listenerRef ) = 0;

	/** Adds a pointer to a non-persistent IAMStatusListener to the list for status notifications.
			Note that persistent IAMStatusListeners may be added via the AddListener method.
		@param listener is a valid pointer to a non-persistent IAMStatusListener instance.
	*/
	virtual void AddNonPersistentListener( IAMStatusListener * listener ) = 0;
		
	/** Gets the UIDRef of the IManageableAsset boss associated with this status instance.
		@return a valid UIDRef unless not properly set.
		@see IManageableAsset.
	*/
	virtual UIDRef GetAsset() = 0;
	
	/** Retrieves the current EditingState for the asset.
		@return IManagedStatus::EditingState.
	*/	
	virtual IManagedStatus::EditingState GetEditingState() = 0;
	
	/** Retrieves a display icon ID.
		@param iconType is a predefined WGStatusType or other unique identifier.
		@return a valid RsrcID or 0.
	*/
	virtual RsrcID GetIconID( int32 iconType ) = 0;

	/** Retrieves the list of IAMStatusListeners added via the AddListener method.
		@param listeners is populated with the UIDRef of the IAMStatusListeners.
		@return the number of UIDRefs put in the list.
		@see IAMStatusListener.
	*/
	virtual int32 GetListeners( IManagedStatus::UIDRefList & listeners ) = 0;

	/** Retrieves the list of non-persistent IAMStatusListener pointers. This list contains
			only those IAMStatusListeners added via the AddNonPersistentListener method.
		@param listeners is populated with IAMStatusListener pointers.
		@return the number of IAMStatusListener pointers in the list.
	*/
	virtual int32 GetNonPersistentListeners( IManagedStatus::ListenerList & listeners ) = 0;
		
	/** Retrieves a display status string.
		@param stringType is a predefined WGStatusType or other unique identifier.
		@param outString is set to the corresponding display text or empty if no status string is
			available.
	*/
	virtual bool16 GetStatusString( int32 stringType, PMString & outString ) = 0;
	
	/** Retrieves the current VersionState.
		@return IManagedStatus::VersionState.
	*/
	virtual IManagedStatus::VersionState GetVersionState() = 0;
	
	/** This method imports the IAMStatusListeners from another IManagedStatus instance. This method
		is useful when a new IManagedStatus boss must be created to replace an old one.
		@param sourceStatus is a valid pointer to another IManagedStatus instance.
		@see IAMStatusListener.
	*/ 
	virtual void ImportListeners( IManagedStatus * sourceStatus ) = 0;
	
	/** This method tests if this instance can communicate with the asset management system. For server
		base asset management systems, this tests if the client side has a connection with the server.
		@return kTrue if a connection exists; kFalse otherwise.
	*/
	virtual bool16 IsOnline() = 0;
	
	/** This method removes an IAMStatusListener from the status notification list.
		@param listenerRef is a UIDRef of a boss with an IAMStatusListener interface.
		@see IAMStatusListener.	
	*/
	virtual void RemoveListener( UIDRef listenerRef ) = 0;

	/** Removes an IAMStatusListener pointer for a non-persistent listener from the
			status notification list.
		@param listener is a valid pointer to an IAMStatusListener previously added
			via the AddNonPersistentListener method.
	*/
	virtual void RemoveNonPersistentListener( IAMStatusListener * listener ) = 0;
	
	/** This method sets the UIDRef of the IManageableAsset boss associated with this status. This method
		is typically set by the IAMServiceProvider::enInitialize service.
		@param assetRef is the UIDRef of an IManageableAsset.
		@see IManageableAsset.
		@see IAMServiceProvider.
	*/
	virtual void SetAsset( UIDRef assetRef ) = 0;
	
	/** This method updates status data then calls NotifyListeners() if an status data has changed.
		@param isOnline is the current online status for the asset.
		@param editingState is the current editing state for the asset.
		@param versionState is the current version state for the asset.
		@param inStatusStrings is the current StatusStringTable for displaying status.
		@param inStatusIcons is the current StatusIconTable for displaying status.
		@return kTrue if any status data has changed; kFalse otherwise.
	*/
	virtual bool16 Update( bool16 isOnline,
						   IManagedStatus::EditingState editingState,	
						   IManagedStatus::VersionState versionState,
						   const IManagedStatus::StatusStringTable & inStatusStrings,
						   const IManagedStatus::StatusIconTable & inStatusIcons
						  ) = 0;
	
	/** This method retrieves display status data.
		@param outStatusStrings is populated with the current StatusStringTable.
		@param outStatusIcons is populated with the current StatusIconTable.
	*/
	virtual void GetDisplayStatusData( IManagedStatus::StatusStringTable & outStatusStrings, IManagedStatus::StatusIconTable & outStatusIcons ) = 0;
						  
	/** This method updates only the display status data.
		@param inStatusStrings is the current StatusStringTable for displaying status.
		@param inStatusIcons is the current StatusIconTable for displaying status.	
		@return kTrue if the display status has changed; kFalse otherwise.
	*/
	virtual bool16 Update( const IManagedStatus::StatusStringTable & inStatusStrings, const IManagedStatus::StatusIconTable & inStatusIcons ) = 0;				 						 

	/** Retrieves a display icon PMRsrcID.
		@param iconType is a predefined WGStatusType or other unique identifier.
		@return a valid PMRsrcID or PMRsrcID(kInvalidRsrcID,kInvalidPlugin).
	*/
	virtual PMRsrcID GetIconPMRsrcID( int32 iconType ) = 0;

protected:	

	/** This method notifies listeners that the latest status update is available by calling the
		IAMStatusListener::Update() method for each IAMStatusListener.
		@see IAMStatusListener.
	*/
	virtual void NotifyListeners() = 0;
	
}; // end IManagedStatus interface

#endif // __IMANAGEDSTATUS__
