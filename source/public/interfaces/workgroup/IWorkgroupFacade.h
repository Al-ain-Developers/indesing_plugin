//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IWorkgroupFacade.h $
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
#ifndef __IWORKGROUPFACADE__
#define __IWORKGROUPFACADE__

#include "workgroupid.h"
#include "IPMUnknown.h"
#include "IAMLockable.h"
#include "IAMServiceProvider.h"
#include "IDatalink.h"
#include "IManageableAsset.h"
#include "IOpenFileCmdData.h"
#include "Utils.h"

class IDFile;
class SysFileList;
class URIList;

/** The IWorkgroupFacade provides high-level access to the public AMSP interfaces. Suggested usage:

		Utils<Facade::IWorkgroupFacade>()->method( params,... );
*/
namespace Facade
	{
	class IWorkgroupFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IWORKGROUPFACADE };

		typedef std::vector<IDFile> FileList;
		
		/** Predefined ForceSave options for resolving version conflicts during CheckIn. */
		enum ForceSave
		{
			/** OK to checkin even though a newer version exists */
			enForceSaveYes,
			/** Do not checkin if a newer version exists */
			enForceSaveNo,
			/** Undecided; display UI for user assistance */
			enForceSaveUnspecified
		};

		/** This method adds an assetRef to the list to be restored (reinitialized) as part of an ICommand
			Undo/Redo checkout operation for LiveEdit.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param objectUID is the UID of the document model object linked to the asset.
		*/
		virtual void AddRestoreCheckedOutCandidate( UIDRef assetRef, UID objectUID = kInvalidUID ) = 0;
		
		/** This method adds an assetRef to the list to be restored (reinitialized) as part of an ICommand
			Undo/Redo operation.
			@param assetRef is a UIDRef for an IManageableAsset.
		*/
		virtual void AddRestoreLinkCandidate( UIDRef assetRef ) = 0;

		/** todo: add doc++ comments
		*/
		virtual void AddRestoreLockStateCandidate( UIDRef assetRef, int32 assetServiceID, UID objectUID = kInvalidUID, const PMString *userName = nil ) = 0;
				
		/** This method adds an IAMStatusListener to an IManagedStatus instance.
			@param listenerRef is the UIDRef of an IAMStatusListener.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return ErrorCode if there was an error; otherwise returns kSuccess. 
		*/
		virtual ErrorCode AddStatusListener( UIDRef listenerRef, UIDRef assetRef ) = 0;
		
		/** This method tests if a managed asset has been moved or renamed.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if the asset has been moved or renamed; kFalse otherwise.
		*/
		virtual bool16 AssetHasMoved( UIDRef assetRef ) = 0;
		
		/** This method cancels the checkout of an asset, provided that the local working copy has not 
			been modified. Services executed (in order):
				IAMServiceProvider::enCancelCheckOut,
				IAMServiceProvider::enAfterCancelCheckOut.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param uiFlags specifies the UI permitted during the method execution.
			@param checkOutToUserName optional parameter that identifies the user that has the asset checked out (default is current user).
			@param objectUID is the UID of the model object (e.g., page item) associated with the asset.
			@return kSuccess if the cancel succeeded; otherwise returns an ErrorCode.
		*/
		virtual ErrorCode CancelCheckOut( UIDRef assetRef, UIFlags uiFlags = kFullUI, const PMString *checkOutToUserName = nil, UID objectUID = kInvalidUID ) = 0;

		/** This method tests if a CheckIn is permitted.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param objectUID is the UID of the document model object linked to the asset.
			@return kTrue if it is OK to CheckIn; kFalse otherwise.
		*/
		virtual bool16 CanCheckIn( UIDRef assetRef, UID objectUID = kInvalidUID ) = 0;

		/** This method tests if a CheckOut is permitted.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param objectUID is the UID of the document model object linked to the asset.
			@return kTrue if it is OK to CheckOut; kFalse otherwise.
		*/	
		virtual bool16 CanCheckOut( UIDRef assetRef, UID objectUID = kInvalidUID ) = 0;
				
		/** This method tests if an asset's locally-saved changes can be reverted to the current version.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param objectUID is the UID of the document model object linked to the asset.
			@return kTrue if it is OK to revert; kFalse otherwise.
		*/
		virtual bool16 CanRevert( UIDRef assetRef, UID objectUID = kInvalidUID ) = 0;
		
		/** This method tests if changes to an asset can be saved (written) to its source file (the file
			it was created from).
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if it is OK to write to source file; kFalse otherwise.
		*/
		virtual bool16 CanSaveToSource( UIDRef assetRef ) = 0;

		/** This method tests if asset management for an asset can be terminated. Normally it is OK to
			terminate, but this method may return kFalse if the asset status in currently being processed.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if OK to terminate; kFalse otherwise.
		*/
		virtual bool16 CanTerminateAssetManagement( UIDRef assetRef ) = 0;

		/** This method saves asset changes to the asset management system as a new version of the asset.
			Services executed (in order):
				IAMServiceProvider::enCheckIn,
				IAMServiceProvider::enAfterCheckIn.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param doSaveChanges applies to file-based assets. Specifying kTrue writes (saves) unsaved
				model changes to the local asset replica file. Specify kFalse to skip the save.
			@param versionComment is a valid pointer to a PMString populated with the version (checkin)
				comments. This PMString is typically obtained from the UI.
			@param uiFlags specifies the UI permitted during the method execution.
			@param checkedOutToUserName specifies the userName that the asset is checked out to. This must
				be the same user name specified for the IWorkgroupFacade::CheckOut() method.
			@param doSaveVersion if kTrue, tells the asset management system to save a new version of the
				asset. Ignored if the asset management system does not support historical versioning.
			@param objectUID is the UID of the model object (e.g., page item) associated with the asset. The database of the
				model object must be the same as asset's. The value is converted to a UIDRef and passed to the enCheckOut
				service as an IAMService::enModelObject.					
			@return kSuccess if the CheckIn succeeded; otherwise returns an ErrorCode.
		*/	
		virtual ErrorCode CheckIn( UIDRef assetRef, bool16 doSaveChanges, const PMString * versionComment = nil, UIFlags uiFlags = kFullUI, bool16 doSaveVersion = kTrue, const PMString *checkedOutToUserName = nil, UID objectUID = kInvalidUID ) = 0;
		
		/** This method saves the local contents of a file as a new version. Use this method to save a
			version when model changes have already been saved to a file. Service executed:
			IAMServiceProvider::enCheckIn.
				
			@param assetfile is the IDFile to which the latest changes have been written.
			@param versionComment is a valid pointer to a PMString populated with the version (checkin)
				comments. This PMString is typically obtained from the UI.
			@param forceSave specifies the ForceSave option in the event of a version conflict.
			@return kSuccess if the CheckIn succeeded; otherwise returns an ErrorCode. 		
		*/	
		virtual ErrorCode CheckIn( const IDFile& assetFile, const PMString * versionComment = nil, const IWorkgroupFacade::ForceSave& forceSave = IWorkgroupFacade::enForceSaveUnspecified  ) = 0;
			
		/** This method checks in a list of files. Files that are not managed are skipped without generating
			an error. Service executed:
				IAMServiceProvider::enBatchCheckIn if available, otherwise
				IAMServiceProvider::enCheckIn.
			@param inIDFileList contains the list of IDFiles to check in.
			@param inComment is a valid pointer to a PMString populated with the version (checkin) comments.
				This PMString is typically obtained from the UI. The same comment is applied to each file
				that is checked in.	
			@return kSuccess if the CheckIn succeeded; otherwise returns an ErrorCode.	
		*/
		virtual ErrorCode CheckIn( const IWorkgroupFacade::FileList & inIDFileList, const PMString & inComment ) = 0;

		/** This method checks in a list of ILinkResources. ILinkResources that are not managed are skipped without generating
			an error. Service executed:
				IAMServiceProvider::enBatchCheckIn if available, otherwise
				IAMServiceProvider::enCheckIn.
			@param inLinkResources contains the list of ILinkResource UIDs to check in.
			@return kSuccess if the CheckIn succeeded; otherwise returns an ErrorCode.	
		*/
		virtual ErrorCode CheckIn( const UIDList & inLinkResources, UIFlags uiFlags = kFullUI ) = 0;
						
		/** This method checks out an asset to a user for editing. Services executed (in order):
				IAMServiceProvider::enBeforeCheckOut,
				IAMServiceProvider::enCheckOut.
			@param assetRef is a UIDRef for an IManageableAsset to check out.
			@param uiFlags specifies the UI permitted during the method execution.
			@param checkOutToUserName optional parameter to specify who to check out the asset to (default is current user).
			@param objectUID is the UID of the model object (e.g., page item) associated with the asset. The database of the
				model object must be the same as asset's. The value is converted to a UIDRef and passed to the enCheckOut
				service as an IAMService::enModelObject.
			@return kSuccess if it worked otherwise an error code.
		*/	
		virtual ErrorCode CheckOut( UIDRef assetRef, UIFlags uiFlags = kFullUI, const PMString *checkOutToUserName = nil, UID objectUID = kInvalidUID ) = 0;
				
		/** This method ensures that an IDFile represents the latest version of a versioned asset. This method
			returns kSuccess and has no effect if the file is not a versioned asset. Service executed:
			IAMServiceProvider::enEnsureLatestVersion.
			@param file is an IDFile with a valid path.
			@return kSuccess if file is the latest version or is otherwise OK to use as is; returns an ErrorCode
				if the operation failed (e.g., lost communication with the asset management system).
		*/
		virtual ErrorCode EnsureLatestVersion( const IDFile & file ) = 0; 
		
		/** DEPRECATED; use alternate method with the same name.
			This method ensures that the content referenced by an IDataLink is the latest version. This method
			returns kSuccess and has no effect if the IDataLink is not to a versioned asset. Service executed:
			IAMServiceProvider::enEnsureLatestVersion.
			@param dl is a valid pointer to an IDataLink instance.
			@return kSuccess if the method succeeded; otherwise returns a failure ErrorCode.
		*/
		virtual ErrorCode EnsureLatestVersion( IDataLink * dl ) = 0;

		/** This method ensures that the external asset associated with an IManageableAsset is the latest version.
			Returns kSuccess and has no effect if the IManageableAsset is not versioned. Service executed:
			IAMServiceProvider::enEnsureLatestVersion.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kSuccess if the method succeeded; otherwise returns a failure ErrorCode.
		*/
		virtual ErrorCode EnsureLatestVersion( UIDRef assetRef ) = 0;
		
		/** This method retrieves the IManagedStatus::enCurrentUser for an IManageableAsset.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param outCurrentUserName is populated with the IManagedStatus::enCurrentUser.
			@see IManagedStatus.
		*/
		virtual void GetCurrentUserName( UIDRef assetRef, PMString & outCurrentUserName ) = 0;

		/** This method retrieves the IManagedStatus::EditingState for an IManageableAsset.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return the IManagedStatus::EditingState.
			@see IManagedStatus.
		*/
		virtual IManagedStatus::EditingState GetEditingState( UIDRef assetRef ) = 0;
		
		/** This method retrieves the IAMLockable::LockState for an IManageableAsset.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param doVerification setting this to kTrue will contact the asset management system for the current
				lock state. If kFalse, retrieves the cached status. Use this flag judiciously: setting to kTrue
				could, depending on the AMSP, hit the network or result in file I/O.
			@param uiFlags specifies the UI permitted during the method execution.
			@param objectUID is the UID of the model object (e.g., page item) associated with the asset.
			@return the IAMLockable::LockState.
			@see IAMLockable.
		*/
		virtual IAMLockable::LockState GetLockState( UIDRef assetRef, bool16 doVerification = kFalse, UIFlags uiFlags = kFullUI, UID objectUID = kInvalidUID ) = 0;
				
		/** This method retrieves a display status string for a IManagedStatus::WGStatusType.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param wgStatusID is the IManagedStatus::WGStatusType or otherwise unique identifier.
			@param outStatusStr is populated with the status text if it was found.
			@see IManagedStatus.
		*/
		virtual void GetStatusString( UIDRef assetRef, int32 wgStatusID, PMString & outStatusStr ) = 0;
		
		/** This method obtains a unique managed asset location based on a proposed path. If a file already exists
			at the proposed path, the filename is munged to obtain a new path.
			@param inProposedFile the suggested unique path.
			@param outUniqueFile the unique valid path that is guaranteed to not already exist. This may
				be the same as inProposedFile.
			@return kSuccess if outUniqueFile is set to the unique path; otherwise it returns failure ErrorCode.
		*/
		virtual ErrorCode GetUniqueAssetLocation( const IDFile & inProposedFile, IDFile & outUniqueFile ) = 0;

		/** This method retrieves the currently stored user interaction level.
			@return UIFlags for permissible UI.
		*/
		virtual UIFlags GetUserInteractionLevel() = 0;
		
		/** This method retrieves the IManagedStatus::VersionState for an IManageableAsset.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return the IManagedStatus::VersionState.
			@see IManagedStatus.
		*/
		virtual IManagedStatus::VersionState GetVersionState( UIDRef assetRef ) = 0;
			
		/** This method tests if an IManageableAsset is associated with versioned content either directly or via
			a link. For AssetType::enDocument, this method is identical to IWorkgroupFacade::IsVersioned (defined
			below).
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if the asset is versioned; kFalse otherwise.
		*/
		virtual bool16 HasVersionedContent( UIDRef assetRef ) = 0;

		/** This method prepares an IManageableAsset for servicing and monitoring as a document (IManageableAsset::
			enDocument) by calling the IAMSPManager::BindAsset() method and an initializer service if available. This
			method may be called for the same assetRef any number of times. Each time it is called, any previous
			IManagedStatus data is discarded. Service executed: IAMServiceProvider::enInitialize. If you call this
			method for an IManageableAsset, you must also call the IWorkgroupFacade::TerminateAssetManagement() method.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param file specified an IDFile with a valid absolute path.
			@return kSuccess if the initialization completed without error; otherwise, it returns a failure ErrorCode. 
			@see TerminateAssetManagement.
		*/
		virtual ErrorCode InitDocumentAssetManagement( UIDRef assetRef, const IDFile & file = IDFile() ) = 0;
		
		/** This method prepares an IManagableAsset for servicing and monitoring as a link (IManageableAsset::enLinked)
			by calling the IAMSPManager::BindAsset() method and an initializer service if available. This method may be
			called for the same assetRef any number of times. Each time it is called, any previous IManagedStatus data
			is discarded. Service executed: IAMServiceProvider::enInitialize. If you call this method for an IManageableAsset,
			you must also call the IWorkgroupFacade::TerminateAssetManagement() method.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param useStoredAssetManagementData if kTrue, the IManageableAsset will be initialized from stored (persistent)
				asset reference data, if available. If kFalse, clears any peristent asset reference data and initializes
				from the ILink location.
			@return kSuccess if the initialization completed without error; otherwise, it returns a failure ErrorCode.
			@see TerminateAssetManagement.	
		*/
		virtual ErrorCode InitLinkAssetManagement( UIDRef assetRef, bool16 useStoredAssetManagementData = kFalse ) = 0;
		
		/** This method initializes an IManageableAsset without asset management capability. This is useful when a boss
			has an IManageableAsset interface, but is not otherwise associated with a managed asset. For example, a
			standalone InCopy kDocBoss is initialized without asset management, since the kDocBoss is an internal container
			not associated with an external ID document file.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kSuccess if the initialization completed without error; otherwise, it returns a failure ErrorCode.
		*/
		virtual ErrorCode InitWithoutAssetManagement( UIDRef assetRef ) = 0;
		
		/** DEPRECATED; use alternate method with the same name.
			This method invalidates the proxy version number associated with an IDataLink so that the link state is reported as
			IDataLink::kLinkOutOfDate (via IWorkgroupFacade::OverrideLinkState). The proxy version number is the version number
			of the asset that the proxy (InDesign document model object) was created from. This method should be called for an
			IDataLink when it is pointed to a different asset. Service executed: IAMServiceProvider::enInvalidateProxyVersionNumber.
			@param dl is a valid pointer to an IDataLink instance.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/	
		virtual ErrorCode InvalidateProxyVersionNumber( IDataLink * dl ) = 0;

		/** This method invalidates the proxy version number associated with an ILink. The proxy version number is the version number
			of the asset that the proxy (InDesign document model object) was created from. This method should be called for an
			ILink when it is pointed to a different asset. Service executed: IAMServiceProvider::enInvalidateProxyVersionNumber.
			@param assetRef is a UIDRef for an IManageableAsset of type IManageableAsset::enLinked.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/	
		virtual ErrorCode InvalidateProxyVersionNumber( UIDRef assetRef ) = 0;
				
		/** This method tests if an IManageableAsset has been initialized via one of the asset management initialization methods.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if initialized; kFalse otherwise.
		*/
		virtual bool16 IsAssetManagementInitialized( UIDRef assetRef ) = 0;
		
		/** This method tests if an asset is checked out.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param objectUID is the UID of the model object associated with the lock.
			@return kTrue if checked out; kFalse if not.
			@see IAMLockable.
		*/
		virtual bool16 IsCheckedOut( UIDRef assetRef, UID objectUID = kInvalidUID ) = 0;
		
		/** This method tests if a newer version of an asset exists in the asset management system.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if a newer version is available; kFalse if the IManageableAsset represents the current version.
		*/
		virtual bool16 IsLatestVersion( UIDRef assetRef ) = 0;

		/** This method tests if an IManageableAsset can be locked (it must have an IAMLockable instance).
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if the asset can be locked; kFalse if not.
		*/
		virtual bool16 IsLockable( UIDRef assetRef ) = 0;
			
		/** This method tests if a newer version of a versioned asset is available. This method is similar to IsLatestVersion(),
			except that it verifies that the asset management system is online for the purpose of downloading the latest version.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if a newer version can be downloaded; kFalse otherwise.
		*/	
		virtual bool16 IsNewerVersionAvailable( UIDRef assetRef ) = 0;
		
		/** This method tests if a server-based asset is accessible.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if online or asset is not managed; kFalse if no server connection.
		*/
		virtual bool16 IsOnline( UIDRef assetRef ) = 0;
		
		/** This method test if a file is a temporary file created from an older version of an asset. A temporary file is opened
			strictly for viewing (read-only).
			@param file is an IDFile with a path to an existing file.
			@return kTrue if file is a temporary version; kFalse otherwise.
		*/
		virtual bool16 IsTemporaryVersion( const IDFile & file ) = 0;
		
		/** This method tests if an IManageableAsset is versioned. For IManageableAsset AssetType::enLinked, this method will
			always return kFalse, regardless of whether or not the link is to a versioned asset (use the IWorkgroupFacade::
			HasVersionedContent() method instead).
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if versioned and AssetType::enDocument; kFalse otherwise.
		*/
		virtual bool16 IsVersioned( UIDRef assetRef ) = 0;
		
		/** This method tests if a file represents a versioned asset.
			@param file is an IDFile with a path to an existing file.
			@return kTrue if file is a versioned asset; kFalse otherwise.
		*/
		virtual bool16 IsVersioned( const IDFile & file ) = 0;
		
		/** This method tests if an IManageableAsset can be written. By default, assets of type AssetType::enDocument can written,
			but enLinked assets, with the exception of stories, can not.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if writeable; kFalse if not.
		*/	
		virtual bool16 IsWriteable( UIDRef assetRef ) = 0;
		
		/** DEPRECATED; no longer functional.
			This method overrides the IDataLink state with the corrected state based on the asset management state information.
			For example, the IDataLink::StateType may be kLinkMissing because the cached asset file is missing, when in fact the
			correct state may be kLinkNormal and the asset file simply needs to be downloaded from the asset management system.
			@param assetRef is a UIDRef for an AssetType::enLinked IManageableAsset.
			@param localState is the IDataLink state with respect to the local linked file.
			@return the corrected IDataLink::StateType (may be the same as localState).
		*/
		virtual IDataLink::StateType OverrideLinkState( UIDRef assetRef, IDataLink::StateType localState ) = 0;

		/** This method overrides the open flags that are used to control how a document file is opened. The underlying AMSP
			implementation is responsible for assuring that the open flags will open a managed document file in
			the right way. For example, a temporary version indd file supplied by Version Cue must be opened as a
			new, unsaved file, rather than as a normal document file.
			@param file is an IDFile with a path to an existing file.
			@param inOpenFlags are the presumed IOpenFileCmdData::OpenFlags.
			@return the corrected IOpenFileCmdData::OpenFlags.
		*/
		virtual IOpenFileCmdData::OpenFlags OverrideOpenFlags( const IDFile & file, IOpenFileCmdData::OpenFlags inOpenFlags ) = 0;

		/** This method removes a status listener from an asset's managed status boss.
			@param listenerRef is the UIDRef of an IAMStatusListener.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return ErrorCode if there was an error; otherwise returns kSuccess.
			@see IAMStatusListener. 
		*/
		virtual ErrorCode RemoveStatusListener( UIDRef listenerRef, UIDRef assetRef ) = 0;

		/** This method restores the previously saved user interaction level.
		*/
		virtual void RestoreUserInteractionLevel() = 0;
		
		/** This method retrieves a stored checkin comment. After this method returns, the comment is no longer in the store.
			@param file is an IDFile with a path to an existing file.
			@param outComment is populated with the text of the comment.
			@return kTrue if a comment was available (outComment may be empty if comment was blank); kFalse if not available.
			@see IWorkgroupFacade::StoreCheckInComment.
		*/
		virtual bool16 RetrieveCheckInComment( const IDFile & file, PMString & outComment ) = 0;

		/** This method retrieves the force save option. The option is no longer in the store after this
			call.
			@param file is an IDFile with a path to an existing file.
			@return IWorkgroupFacade::ForceSave option.
		 */
		virtual ForceSave RetrieveForceSaveOption( const IDFile& file ) = 0;
			
		/** This method reverts a modified local asset by replacing it with the current version of the asset. Service executed:
			IAMServiceProvider::enRevert.
			@param assetRef is a UIDRef for an IManageableAsset. 
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/
		virtual ErrorCode Revert( UIDRef assetRef ) = 0;
		
		/** This method starts monitoring an IManageableAsset for status changes. The IManageableAsset must be initialized via
			IWorkgroupFacade::InitDocumentAssetManagement() or InitLinkAssetManagement() before calling this method. This method
			has no affect if the asset is already being monitored.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
			@see IWorkgroupFacade::StopMonitoring
		*/
		virtual ErrorCode StartMonitoring( UIDRef assetRef ) = 0;
		
		/** This method stops monitoring an IManageableAsset for status changes. This method has no affect if StartMonitoring()
			was not called beforehand. Once monitoring has stopped, it may be resumed by calling StartMonitoring().
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
			@see IWorkgroupFacade::StartMonitoring
		*/
		virtual ErrorCode StopMonitoring( UIDRef assetRef ) = 0;

		/** This method stores a checkin comment for later retrieval. The comment remains in the store until it
			is retrieved.
			@param inComment is a PMString with the comment; an empty string denotes a valid blank comment.
			@param file is an IDFile with a path to an existing file. This is the file that will be checked in.
			@see IWorkgroupFacade::RetrieveCheckInComment.
		*/
		virtual void StoreCheckInComment( const PMString & inComment, const IDFile & file ) = 0;

		/** This method stores the force save option for later retrieval. The option remains in the store until it
			is retrieved.
			@param file is an IDFile with a path to an existing file.
			@param forceSave is the ForceSave option to store with the file.
		 */
		virtual void StoreForceSaveOption( const IDFile& file, const ForceSave& forceSave ) = 0;

		/** This method stores the user interaction level for later retrieval. The previously stored interaction
			level is saved and can be restored using IWorkgroupFacade::RestoreUserInteractionLevel().
			@param uiFlags the new user interaction level.
		*/
		virtual void StoreUserInteractionLevel(const UIFlags& uiFlags) = 0;
		
		/** This method terminates asset management capability associated with an IManageableAsset. Service executed:
			IAMServiceProvider::enTerminate.
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kSuccess if the termination succeeded; otherwise, it returns a failure ErrorCode.
		*/		
		virtual ErrorCode TerminateAssetManagement( UIDRef assetRef ) = 0;
		
		/** DEPRECATED; use alternate method with the same name.
			This method executes an IAMServiceProvider::enUpdateLinkLocation service for an IDataLink instance.
			@param dl is a valid pointer to an IDataLink instance.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/
		virtual ErrorCode UpdateLinkLocation( IDataLink * dl ) = 0;

		/** This method executes an IAMServiceProvider::enUpdateLinkLocation service for an ILink instance.
			@param assetRef is a UIDRef for an IManageableAsset of type IManageableAsset::enLinked.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/
		virtual ErrorCode UpdateLinkLocation( UIDRef assetRef ) = 0;
				
		/** DEPRECATED; use alternate method with the same name.
			This method updates the proxy version number associated with an IDataLink. This method should be
			called for an IDataLink whenever the proxy is created from the asset. This method returns kSuccess
			and has no affect unless the link is to a versioned asset. Service executed:
			IAMServiceProvider::enUpdateProxyVersionNumber.
			@param dl is a valid pointer to an IDataLink instance.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/ 
		virtual ErrorCode UpdateProxyVersionNumber( IDataLink * dl ) = 0;
		
		/** This method updates the proxy version number associated with an ILink. This method should be
			called for an ILink whenever the proxy is created from the asset. This method returns kSuccess
			and has no affect if the ILink is not for a versioned asset. Service executed:
			IAMServiceProvider::enUpdateProxyVersionNumber.
			@param assetRef is a UIDRef for an IManageableAsset of type IManageableAsset::enLinked.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/ 		
		virtual ErrorCode UpdateProxyVersionNumber( UIDRef assetRef ) = 0;
		
		/** This method calls the IAMServiceProvider::UpdateScriptedAssetData method for an IManageableAsset.
			@param assetRef is a UIDRef for an IManageableAsset.
			@param scriptString is the IScriptRequestData converted to a PMString.
			@param scriptID is the script data item's ScriptID.
			@see IAMServiceProvider::UpdateScriptedAssetData.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/
		virtual ErrorCode UpdateScriptedAssetData( UIDRef assetRef, const PMString & scriptString, int32 scriptID  ) = 0;
		
		/** DEPRECATED; use alternate method with the same name.
			This method uses IAMServiceProvider::enUpdateStoredAssetReference service to update AMSP-specific
			asset reference data that is persisted (stored) with a linked asset.
			@param dl is a valid pointer to an IDataLink instance.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/
		virtual ErrorCode UpdateStoredAssetReference( IDataLink * dl ) = 0;

		/** This method uses IAMServiceProvider::enUpdateStoredAssetReference service to update AMSP-specific
			asset reference data that is persisted (stored) with a linked asset.
			@param assetRef is a UIDRef for an IManageableAsset of type IManageableAsset::enLinked.
			@return kSuccess if the method completed without error; otherwise, it returns a failure ErrorCode.
		*/
		virtual ErrorCode UpdateStoredAssetReference( UIDRef assetRef ) = 0;
		
		/** This method tests if an asset is currently being monitored for IManagedStatus changes. 
			@param assetRef is a UIDRef for an IManageableAsset.
			@return kTrue if an IAssetMonitor instance is currently monitoring the asset; kFalse otherwise.
			@see IWorkgroupFacade::StartMonitoring
			@see IWorkgroupFacade::StopMonitoring
			@see IAssetMonitor
			@see IManagedStatus
		*/
		virtual bool16 IsMonitoring( UIDRef assetRef ) = 0;

	}; // end IWorkgroupFacade interface
}

#endif	// __IWORKGROUPFACADE__
