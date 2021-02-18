//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyBridgeUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IInCopyBridgeUtils__
#define __IInCopyBridgeUtils__

#include "InCopyBridgeID.h"
#include "IPMUnknown.h"

#include "K2Vector.h"
#include "ICommand.h"

class ICommand;
class UIDRef;
class PMString;
class IDataLink;
class IDocument;

// DEPRECATED. DO NOT USE THIS INTERFACE.
// See method descriptions below for suggested alternative methods to use.

class IInCopyBridgeUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYBRIDGEUTILS };

   /**
			...
    */
	enum ICBridgeError 
	{
		// ARM's _ExpectedErrors, see ARMTypes.h .
		//kSuccess = 0,
		//kCancelled = 1,
		//kUnauthorized,
		//kNoSuchResource,
		//kNoContent,
		//kPermissionDenied,
		//kLockedElsewhere,
		//kLockedByOther,
		//kLockedExclusively,
		//kLockedShared,
		//kLockRevoked,
		//kNoSuchReplica,
		//kWouldClobberLocked,
		//kWouldClobberModified,
		//kWouldClobberCurrent,
		//kNoSuchParent,
		//kNoMountPoint,
		//kCantMountParent,
		//kCantMountChild,
		//kMountPointsDiffer,
		//kNotInARM,
		//kCollectionAlreadyExists,
		//kNonCollectionAlreadyExists,
		//kCantCaptureUnlessCurrent,
		////add lines above here
		//kLastExpectedError = 0x7FFFFFFF,		// force enum to be a 32 bit int

		//// ARM's _UnexpectedErrors, see ARMTypes.h .		
		//kIllegalURL = -6666,		/* a distinctive number, for luck! */
		//kForbidden,
		//kServerBusy,
		//kRedirect,
		//kServerFailure,
		//kDatabaseFailure,
		//kDiskFailure,
		//kMemoryFailure,
		//kNetworkFailure,
		//kConfigurationError,
		//kClientNameError,
		//kRequestError,
		//kFileOpenFailure,
		//kBadParameterPassed,
		//kCantFindMountPointFolder,
		//kFileNotFound,
		//kFolderNotFound,
		//kItemWasNotAFolder,
		//kCantResolveAlias,
		//kCantOpenOptionsFile,
		//kCantCreateAlias,
		//kCantOpenResourceFork,
		//kFileAlreadyExists,
		//kNoMountPointRoot,
		//kIllegalMountName,
		//kNotDAVResource,			// server return shows protocol failure
		//kResourceMissing,			// didn't find a resource we expected
		//kCantCreateFolder,
		//kEncodingError,				// can't map characters
		//kMountPointRootMissing,		// the mount point root was expected but couldn't be found
		//// add lines above here
		//kNonSpecific		= -1,
		//kLastUnexpectedError = 0x7FFFFFFF,		// force enum to be a 32 bit int
		//
		
		// InCopyBridge errors
		kNoError 			= kICBErr_NoError,
		kUnknown 			= kICBErr_Unknown,
		kInvalidParameter	= kICBErr_InvalidParameter,
		kNoDataLink 		= kICBErr_NoDataLink,
		kBrokenLink 		= kICBErr_BrokenLink,
		kLinkIsEmbedded 	= kICBErr_LinkIsEmbedded,
		kNotNormalLink 		= kICBErr_NotNormalLink,
		kCantGetLinkFile 	= kICBErr_CantGetLinkFile,
		kInvalidUserName	= kICBErr_kInvalidUserName,
		kLinkIsMissing 		= kICBErr_kLinkIsMissing,
		kLastInCopyBridgeError = kLinkIsMissing
	};

#ifdef ID_DEPRECATED
   /**
		Sets InCopy user name.
		DEPRECATED - use IUserInfoUtils::SetInCopyUserName instead.
		@param userName IN. User name.
    */
	virtual void SetInCopyUsername( const PMString& userName ) const = 0;

   /**
		Returns InCopy user name.
		DEPRECATED - use IUserInfoUtils::GetInCopyUserName instead.
		@param uiFlags IN, optional. If kFullUI and InCopy user name is empty or "Unknown User Name" the user will be asked for entering a new user name.
		@return InCopy user name.
    */
	virtual PMString GetInCopyUsername( UIFlags uiFlags = kFullUI ) const = 0;


	/**
		Returns the IDataLink interface for a story.
		DEPRECATED - this method is obsolete.
		@param storyRef IN. UIDRef of the story.
		@return IDataLink of story or nil on error.
	*/
	virtual IDataLink *QueryDataLink( const UIDRef& storyRef ) const = 0;


	/**
		Processes kSetItemLockDataCmdBoss command, which changes the story's lock state.
		DEPRECATED - use IWorkgroupStoryFacade::PreventUserEditing or ::AllowUserEditing instead.
		@param storyRef IN. UIDRef of the story.
		@param lockStory IN. Lock or unlock story.
		@param undoabilityFlag IN, optional. Undoability flag for kSetItemLockDataCmdBoss.
		@return kTrue if it changed the model.
	*/
	virtual bool16 LockTextModel( const UIDRef& storyRef, bool16 lockStory, ICommand::Undoability undoabilityFlag = ICommand::kRegularUndo ) const = 0;


	/**
		Processes kSetItemLockDataCmdBoss command, which changes the item's lock state.
		DEPRECATED - use IWorkgroupStoryFacade::PreventUserEditing or ::AllowUserEditing instead.
		@param itemRef IN. UIDRef of the item.
		@param lock IN. Lock or unlock item.
		@param undoabilityFlag IN, optional. Undoability flag for kSetItemLockDataCmdBoss.
		@return kTrue if it changed the model.
	*/
	virtual bool16 LockItem( const UIDRef& itemRef, bool16 lock, ICommand::Undoability undoabilityFlag = ICommand::kRegularUndo ) const = 0;


	/**
		Notifies responders listening to serviceID.
		DEPRECATED - use ISignalMgr instead
		@param icBridgeCommand IN. Command with ISignalMgr interface.
		@param serviceID IN, optional. Used for ISignalMgr::Init().
		@return Returns internal error code from ISignalMgr::SignalNextResponder().
	*/
	virtual ErrorCode NotifyResponders( ICommand *icBridgeCommand, ServiceID serviceID = kLiveEditCmdResponderService ) const = 0;


	/**
		Returns InCopy story file's lockfile.
		DEPRECATED - use IPMLockFile instead.
		@param storySysFile IN. InCopy story file.
		@return Returns InCopy story file's lockfile.
	*/
	virtual bool16 GetInCopyLockFile( const IDFile& storySysFile, IDFile& inCopyLockFile ) const = 0;


	/**
		Calls IsLocked( storyRef ) and synchronizes the result with the story's lock state.
		SyncTextModelLock() is being used by InCopyBridgeDocResponder and InCopyBridgeLinkResponder.
		DEPRECATED - use ILiveEditFacade::SynchronizeLocks instead
		@param storyRef IN. UIDRef of the story.
		@param storyFile OUT. InCopy IDFile.
		@return kTrue if successful.
	*/
	virtual bool16 SyncTextModelLock( const UIDRef& storyRef, IDFile& storyFile, UIFlags uiFlags = kFullUI ) const = 0;

	/**
		Sets the story's lock state based on the state passed in. This is similar to calling SyncTextModelLock, but if you already know the IWorkgroupAccess::LockState, this is much faster.
		DEPRECATED - obsolete
		@param storyRef IN. UIDRef of the story.
		@param state IN. the state of this story. This will be used to decide whether the story should be locked or unlocked.
		@return kTrue if successful.
	*/
	virtual bool16 SetTextModelLock( const UIDRef& storyRef ) const = 0;
	
	/**
		Returns whether storyRef is an InCopy story.
		DEPRECATED - use IStoryUtils::IsAStory() instead.
		@param storyRef IN. UIDRef of the story or graphic frame.
		@return kTrue if storyRef is an InCopy story.
	*/
	virtual bool16 	IsInCopyStory( const UIDRef& storyRef ) const = 0;	


	/**
		Gets the IDFile of a story. This method gets the IDFile using ILinkUtils::GetFileFromLink and, in
		addition, returns FileTypeInfoID and ICBridgeError. The optional parameter, allowSynchronous,
		is obsolete and not used.
		DEPRECATED - use ILinkUtils::GetFileFromLink instead
		@param storyRef IN. UIDRef of the story.
		@param storyFile OUT. InCopy IDFile.
		@param fileTypeInfo OUT. InCopy file type (kInCopyFileTypeInfoID or kInCopyXMLInterchangeFileTypeInfoID).
		@param errorCode OUT, optional. Returns internal error code.
		@param allowSynchronous IN, optional. Obsolete.  Not used.
		@return kTrue if storyFile exists.
	*/
	virtual bool16 GetSysFileOfStory( const UIDRef& storyRef, IDFile& storyFile, FileTypeInfoID& fileTypeInfo, ICBridgeError* errorCode = nil, bool16 allowSynchronous = kTrue ) const = 0;


	/**
		Part of InCopy Story's MetaData information is a GUID, which you can get via IMetaDataAccess::GetInstanceID().
		DEPRECATED - obsolete
		@param storyRef IN. UIDRef of the story.
		@param createGUIDifNecessary IN. Generates new GUID if it hasn't been created.
		@returns MetaData GUID from story or empty string on errors.
	*/
	virtual PMString GetGUIDOfStory( const UIDRef& storyRef, bool16 createGUIDifNecessary = kTrue ) const = 0;
	
	/**
		Determine whether there are any checked out stories in the current pub (InDesign or InCopy).
		DEPRECATED - use IWorkgroupStoryFacade::GetStoryLockState instead
		@param document IN. Pointer to the InDesign document containing InCopy stories.
		@param useCachedValue IN. boolean indicating whether or not it's ok to check our cached value for this.
	*/
	virtual bool16 AreStoriesLocked( const IDocument* document, bool16 useCachedValue = kFalse  ) const = 0;

	/**
		Export an existing incopy story.
		DEPRECATED - use ILiveEditFacade::SaveStories instead
		@param UIDRef of ic story to export
		@param IDFile destination file
		@return kTrue if successfully exported the story
	*/
	virtual bool16 ExportStory( const UIDRef& storyRef, const IDFile& storyFile, const FileTypeInfoID fileTypeID ) const = 0;
	
#endif // ID_DEPRECATED

};


#endif	// __IInCopyBridgeUtils__
