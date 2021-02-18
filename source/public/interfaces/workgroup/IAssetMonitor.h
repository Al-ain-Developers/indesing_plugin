//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IAssetMonitor.h $
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
#ifndef __IAssetMonitor_h__
#define __IAssetMonitor_h__

#include "IPMUnknown.h"
#include "workgroupid.h"


class IManageableAsset;
class IManagedStatus;
class ICommand;


/** The IAssetMonitor interface is responsible for monitoring status changes for assets. An asset
	monitor is enabled simply by returning its instance on the IAMSystemProvider::GetAssetMonitor()
	method. Each asset monitor is automatically called by the AssetMonitorIdleTask, which has a loop
	that calls two IAssetMonitor methods. The first call, to IAssetMonitor::GetHandleChangesCommand(),
	gets an ICommand to schedule for processing status changes. A command rather than a direct call
	is used in the event that a modal dialog is necessary for informing the end user of a status change
	(the idle loop should never be interrupted with a modal dialog). The second call, which is made to
	IAssetMonitor::DoBackgroundTasks(), gives the IAssetMonitor implementation time to perform non-UI
	status processing or other tasks.
	
	Developer hint: the design details of the HandleChangesCommand is left up to the implementation;
	however, the command should have a processing loop that calls IAssetMonitor::GetNextPendingStatus()
	for the next IManagedStatus that needs processing. This is the technique used to process Version Cue
	status changes.
	
	@see IAMSystemProvider.
	@see IManagedStatus.
*/
class IAssetMonitor : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSETMONITOR };

	/** This method tests if an asset has moved or has been renamed.
		@param asset is a valid pointer to a bound IManageableAsset instance.
		@return kTrue if the asset has been moved or rename; kFalse otherwise.
	*/
	virtual bool16 AssetHasMoved( IManageableAsset * asset ) = 0;
	
	/** This method does any initialization needed before monitoring begins. This method is called
		once during app startup.
		@return kTrue if the asset monitor is OK for use; kFalse if it may not be used.
	*/
	virtual bool16 StartUp() = 0;
	
	/** This method performs any termination needed after monitoring ends. This method is called once
		during app shutdown.
		@return kTrue if shutdown succeeded; kFalse if there was an error.
	*/
	virtual bool16 ShutDown() = 0;
	
	/** This method tests if the asset monitor is able to monitor a file for status changes.
		@param file is an IDFile with a path to an existing file.
		@return kTrue if the file can be monitored; kFalse otherwise.
	*/
	virtual bool16 CanMonitor( const IDFile & file ) = 0;
	
	/** This method tests if the asset monitor is able to monitor an IManageableAsset for status changes.
		@param asset is a valid pointer to an IManageableAsset instance.
		@return kTrue if the asset can be monitored; kFalse otherwise.
	*/	
	virtual bool16 CanMonitor( IManageableAsset * asset ) = 0;
	
	/** This method provides an ICommand that can be scheduled to process asset status changes. May return
		nil if there are no pending changes to process. An ICommand should be used to process status changes
		if the status processing displays modal dialogs (such as for alerts).
		@return a valid pointer to an ICommand object or nil if there are no changes to process.
	*/
	virtual ICommand * GetHandleChangesCommand() = 0;
	
	/** This method retrieves the next pending IManagedStatus instance to process.
		@return a valid pointer to an IManagedStatus instance or nil if there are no remaining instances
			to process.
	*/
	virtual IManagedStatus * GetNextPendingStatus() = 0;
	
	/** This method tests if an asset has a pending status that has not yet been processed. The StartWatching()
		method must be called for the asset before this method is called.
		@param asset is an IManageableAsset that is being monitored.
		@return kTrue if the asset has unprocessed status pending; kFalse otherwise. 
	*/
	virtual bool16 IsStatusPending( IManageableAsset * asset ) = 0;	
	
	/** This method is called from the idle task in order to give the asset monitor implementation processing
		time. This method should not display UI or otherwise interrupt the idle loop processing.
		@return the callback interval (for future use).
		@see IIdleTask::RunTask.
	*/
	virtual uint32 DoBackgroundTasks() = 0;
		
	/** This method starts monitoring for status changes for an asset. Changes to IManagedStatus
		and IAMLockable states are typically monitored.
		@param assetRef is the UIDRef of a bound IManageableAsset.
		@return kSuccess if monitoring the asset has started; otherwise returns a failure ErrorCode.
	*/
	virtual ErrorCode StartMonitoring( UIDRef assetRef ) = 0;

	/** This method stops monitoring for status changes for an asset.
		@param assetRef is the UIDRef of a bound IManageableAsset.
		@return kSuccess if monitoring the asset has stopped; otherwise returns a failure ErrorCode.
	*/
	virtual ErrorCode StopMonitoring( UIDRef assetRef ) = 0;
	
	/** This method tests if an asset is currently being monitored for status changes.
		@param assetRef is the UIDRef of a bound IManageableAsset.
		@return kTrue if the asset is being monitored; kFalse otherwise.
	*/
	virtual bool16 IsMonitoring( UIDRef assetRef ) = 0;	
	
}; // end IAssetMonitor interface

#endif // __IAssetMonitor_h__
