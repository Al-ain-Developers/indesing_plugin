//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/IWorkgroupStoryFacade.h $
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
#ifndef __IWORKGROUPSTORYFACADE__
#define __IWORKGROUPSTORYFACADE__

#include "workgroupid.h"
#include "Utils.h"
#include "IPMUnknown.h"

#include "IAMLockable.h"

/** The IWorkgroupStoryFacade provides high-level access to the public AMSP interfaces for LiveEdit
	stories. Suggested usage:

		Utils<Facade::IWorkgroupStoryFacade>()->method( params,... );

	Note that "storyRef" in method definitions refers to the UIDRef of the story page item, not to
	the UIDRef of the corresponding link boss.		
		
*/
namespace Facade
{
	class IWorkgroupStoryFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IWORKGROUPSTORYFACADE };
		
		/** Allows user to edit the story model.
			IMPORTANT: This method should only be called within an abortable command sequence.
		*/
		virtual ErrorCode AllowUserEditing( const UIDRef & storyRef, ICommand::Undoability undoabilityFlag = ICommand::kRegularUndo ) = 0;
	
		/** This method retrieves the UIDRef of the boss that has the IManageableAsset interface from the
			UIDRef of a story page item.
			@param storyRef is the UIDRef of the story page item.
			@return UIDRef of the IManageableAsset if storyRef is valid; otherwise UIDRef::gNull.
		*/
		virtual UIDRef GetAssetUIDRef( UIDRef storyRef ) = 0;

		/** Retrieves the user name that a story is checked out to.
			@param storyRef the UIDRef of a story page item.
			@param outCheckedOutToName a PMString reference to receive the user name.
			@return kTrue if the story is currently locked (checked out by anyone) and outCheckedOutToName
				is populated with the user name; otherwise returns kFalse and outCheckedOutToName is not
				affected.
		*/
		virtual bool16 GetCheckedOutToName( const UIDRef& storyRef, PMString & outCheckedOutToName ) = 0;

#ifdef ID_DEPRECATED
		/** Retrieves the IDFile for a story. DEPRECATED. Use Utils<ILinkUtils>->GetFileFromLink( storyRef, file ).
			@param storyRef the UIDRef of a story page item.
			@param outStoryFile is set to the file path for the story, if available.
			@return kTrue if the file was set; kFalse otherwise.
		*/
		virtual bool16 GetStoryFile( const UIDRef& storyRef, IDFile& outStoryFile ) = 0;
#endif // ID_DEPRECATED
				
		/** This method retrieves the UIDRef of the first story page item found to be associated with the
			specified assetRef. 
			@param assetRef is a UIDRef for an IManageableAsset.
			@return UIDRef of the story page item if assetRef is associated with an existing story page item;
				otherwise UIDRef::gNull.
		*/
		virtual UIDRef GetStoryUIDRef( UIDRef assetRef ) = 0;
		
		/** This method retrieves the story lock status names.
			@param storyRef is the UIDRef of the story page item.
			@param outUserName is populated with the IManagedStatus::enCheckedOutBy name.
			@param outDocName is populated with the IManagedStatus::enCheckedOutDoc name.
			@param outAppName is populated with the IManagedStatus::enCheckedOutApp name.
			@return kTrue if the names were found (one or more PMStrings may be empty signifying a blank);
				otherwise, returns kFalse.
		*/
		virtual bool16 GetStoryLockNames( UIDRef storyRef, PMString & outUserName, PMString & outDocName, PMString & outAppName ) = 0;

		/** This method retrieves the story lock status names for a storyFile. This method will succeed only
			if the story asset is locked.
			@param storyFile has a valid path to an existing file-based story asset.
			@param outUserName is populated with the IManagedStatus::enCheckedOutBy name.
			@param outDocName is populated with the IManagedStatus::enCheckedOutDoc name.
			@param outAppName is populated with the IManagedStatus::enCheckedOutApp name.
			@param uiFlags controls UI that may be displayed to get the user name.
			@return kTrue if the names were found (one or more PMStrings may be empty signifying a blank);
				otherwise, returns kFalse.
		*/
		virtual bool16 GetStoryLockNames( const IDFile & storyFile, PMString & outUserName, PMString & outDocName, PMString & outAppName, UIFlags uiFlags = kFullUI ) = 0;
				
		/** This method retrieves the LockState for a story asset.
			@param storyRef is the UIDRef of the story page item.
			@param doVerification (see description in IWorkgroupFacade::GetLockState).
			@return the IAMLockable::LockState.
		*/
		virtual IAMLockable::LockState GetStoryLockState( UIDRef storyRef, bool16 doVerification = kFalse, UIFlags uiFlags = kFullUI ) = 0;

#ifdef ID_DEPRECATED
		/** Tests if the specified UIDRef refers to a story page item.
			This method will be removed in a future release. Please use IStoryUtils::IsAStory.
			@param testRef is a UIDRef to test.
			@return kTrue if the UIDRef refers to a story page item; kFalse otherwise.
		*/
		virtual bool16 IsAStory( UIDRef testRef ) = 0;
#endif // ID_DEPRECATED

#ifdef ID_DEPRECATED	
		/** Tests if a story's content is embedded in an InDesign document.
			@param storyRef is the UIDRef of the story page item.
			@return kTrue if the story content is embedded; kFalse otherwise.
		*/
		virtual bool16 IsEmbedded( UIDRef storyRef ) = 0;
#endif // ID_DEPRECATED
		
		/** This method tests if a story is a versioned asset.
			@param storyRef is the UIDRef of the story page item.
			@return kTrue if versioned; kFalse if not.
		*/
		virtual bool16 IsVersioned( UIDRef storyRef ) = 0;

		/** This method uses IAMServiceProvider::IsWriteable to test if a story file may be overwritten
			(exported to).
			@param storyFile has a valid path to file-based story asset.
			@return kTrue if it is currently legal to export to the storyFile; kFalse otherwise.
		*/
		virtual bool16 IsWriteable( const IDFile & storyFile ) = 0;

		/** This method displays a LiveEdit lock conflict alert for a story.
			@param storyRef is the UIDRef of the story page item affected by the lock conflict.
			@param storyFile is a valid IDFile if the story asset is file-based; specify an IDFile with an
			empty path for a story asset that is not file-based.
			@param checkedOutBy is the name of the user that owns the lock.
			@param checkedOutApp is the name of the application that owns the lock.
			@param checkedOutDoc is the name of the document that owns the lock.
			@param warnText is the text to display.
			@return one of the LiveEdit alert choices (see kInCopyAlertChoiceYes, et al. in InCopyBridgeUIID.h).
		*/
		virtual PMString LiveEditConflictAlert( UIDRef storyRef, const IDFile& storyFile, const PMString& checkedOutBy, const PMString& checkedOutApp, const PMString& checkedOutDoc, const PMString& warnText ) = 0;

		/** Prevents changes to a story page item by locking the page item for further updates. When this
			method returns successfully, the content of a story page item may not be changed until the
			ILiveEditUtils::AllowUserEditing() method is called.
			IMPORTANT: This method should only be called within an abortable command sequence.
		*/
		virtual ErrorCode PreventUserEditing( const UIDRef & storyRef, ICommand::Undoability undoabilityFlag = ICommand::kRegularUndo ) = 0;
					
		/** This method retrieves the story UIDRef from a standalone InCopy document.
			@param docRef is the UIDRef of an InDesign document.
			@return UIDRef of the story.
		*/
		virtual UIDRef QueryStandaloneStoryRef( UIDRef docRef ) = 0;

#ifdef ID_DEPRECATED		
		/** This method assures that editing access to a story page item agrees with the corresponding story
			asset's lock state. The page item is editable only if the asset is checked out or embedded.
			This method will be removed in a future release. Please use ILiveEditFacade::SynchronizeLocks() instead.
			@param storyRef the UIDRef of a story page item.
			@return kSuccess if the sync was successful (or no change was needed); returns kFailure if the
				method was unable to sync or to determine that synchronization was needed.
		*/
		virtual ErrorCode SyncStoryPIAccessToStoryLock( UIDRef storyRef ) = 0;
#endif // ID_DEPRECATED	
	
		/** This method changes the data link information for an existing story page item.
			@param storyRef is the UIDRef of the story page item.
			@param uiFlags controls UI that may be displayed to perform the relink.
			@return kSuccess if the relink succeeded; otherwise returns an ErrorCode value.
		*/
		virtual ErrorCode Relink( UIDRef storyRef, UIFlags uiFlags = kMinimalUI ) = 0;

#ifdef ID_DEPRECATED		
		/** This method exports embedded story content to an external story location.
			@param storyRef is the UIDRef of the embedded story page item.
			@param uiFlags specifies the permissable UI to use for the unembed process.
			@param undoabilityFlag specifies the permissable ICommand::Undoability for any commands that may
			be executed as part of the unembed process.
			@return kSuccess if the unembed succeeded; otherwise returns an ErrorCode value.
		*/
		virtual ErrorCode Unembed( UIDRef storyRef, UIFlags uiFlags = kFullUI, ICommand::Undoability undoabilityFlag = ICommand::kRegularUndo ) = 0;
#endif // ID_DEPRECATED

		/** This method updates the IAMLockable implementation for a story asset lock. Note that this
			method does not affect the story text frame lock.
			@param storyRef is the UIDRef of the story page item associated with the story asset to relock.
			@return kSuccess if the relock operation succeeded; otherwise returns an ErrorCode value.
		*/
		virtual ErrorCode Relock( UIDRef storyRef ) = 0;
		
		/** Writes story model changes to the corresponding story asset using the asset's ISaveAssetContent
			implementation.
			@param storyRef is the UIDRef of a story item.
			@return kSuccess if the save operation succeeded; otherwise returns an ErrorCode value.
		*/
		virtual ErrorCode SaveModelChanges( UIDRef storyRef ) = 0;
		
		/** Tests if a story model can be edited.
			@param storyRef is the UIDRef of a story model.
			@return true if the story model can be edited; false otherwise.
		*/
		virtual bool IsEditingAllowed( UIDRef storyRef ) = 0;
		
	}; // end IWorkgroupStoryFacade interface
}

#endif	// __IWORKGROUPSTORYFACADE__
