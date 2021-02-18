//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ILiveEditFacade.h $
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
#ifndef __ILIVEEDITFACADE__
#define __ILIVEEDITFACADE__

#include "InCopyBridgeID.h"
#include "Utils.h"
#include "IPMUnknown.h"


/** The ILiveEditFacade provides methods for performing LiveEdit functions. LiveEdit is a
	simple set of rules for revising InCopy stories:
	
	1.	A story must be checked out before it can be edited. The check out obtains an
		exclusive-use lock on the story asset, which may be in a local file, a server
		or an asset management system, and enables edit to the story page item.
	2.	Due to the exclusive-use lock, a story asset may be edited from only one place
		at a time. An attempt to check out a story that is already checked out results
		in a "lock conflict". Lock conflicts are resolved by allowing the option to
		"embed" the story to enable editing.
	3.  After a story has been revised, it must be checked in. The check in releases
		the exclusive-use lock on the story asset and disables edits to the story
		page item.
	4.  A check out is undone by a "cancel check out" operation. A check out can also
		be undone via the Edit>Undo stack.
*/

class TaskProgressBar;

namespace Facade
	{
	class ILiveEditFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ILIVEEDITFACADE };

		enum LiveEditError 
		{
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
		
		/** Cancels the checked-out state for one or more story page items. Cancelling involves
			(1) reverting changes to the story applied after the story was last checked out;
			(2) releasing the story asset lock;
			(3) preventing further changes to the story page item.
			This method is undoable.
			@param storyList contains UIDRefs of story page items.
			@param updateStoryLink updates the story link when kTrue.
			@param undoabilityFlag applies to all commands that are executed by the implementation of this method.
			@param userName is the same name specified on the the CheckOut() method.
			@param uiFlags controls UI that may be displayed to perform the cancel check out.
			@return a predefined ErrorCode if a failure occurs, a kCancel if the operation was canceled, or
				kSuccess if the method completed without error. 
		*/
		virtual ErrorCode CancelCheckOut( const UIDList& storyList, bool16 updateStoryLink = kTrue, ICommand::Undoability undoabilityFlag = ICommand::kRegularUndo, const PMString *userName = nil, UIFlags uiFlags = kFullUI ) = 0;

		/** CheckInOptions control the subtasks performed by the CheckIn method.
		*/
		enum CheckInOptions
		{
			/** Releases the story lock. */
			enUnlockAsset		= 0x00000001,
			/** Exports the story page item to the story file. */
			enExportStory		= 0x00000002,
			/** Saves a new version to the asset management system; has no affect if the story is not versioned. */	
			enSaveVersion		= 0x00000004,
			/** Does not discard the undo stack. */	
			enKeepUndoStack		= 0x00000008,	
			enLast = 0x7FFFFFFF // Force enum to 32 bits
		};
		
		/** Checks in one or more stories by
			(1) exporting the story page item to disk (optional);
			(2) releasing the story asset lock (optional);
			(3) preventing further changes to the story page item.
			This method is not undoable.
			@param storyList contains UIDRefs of story page items.
			@param opts are CheckInOptions; multiple options are or'd together. For example:
				ILiveEditFacade::CheckInOptions( ILiveEditFacade::enUnlockAsset | ILiveEditFacade::enExportStory ).
			@param comment is a ptr to a PMString containing a user checkin comment; if nil is specified, and
				depending on whether or not the story assets are in an asset management system, a dialog may be
				displayed to allow the user to enter a comment (UI is subject to UIFlags).
			@param userName is the same name specified on the the CheckOut() method.
			@param undoabilityFlag applies to all commands that are executed by the implementation of this method.
			@param uiFlags controls UI that may be displayed to perform the check in.
			@return a predefined ErrorCode if a failure occurs, a kCancel if the operation was canceled, or
				kSuccess if the method completed without error. 		
		*/	
		virtual ErrorCode CheckIn( const UIDList& storyList, ILiveEditFacade::CheckInOptions opts = ILiveEditFacade::enUnlockAsset, const PMString * comment = nil, const PMString *userName = nil, ICommand::Undoability undoabilityFlag = ICommand::kAutoUndo, UIFlags uiFlags = kFullUI ) = 0;
		
		/** Enables editing for one or more stories by checking out the story asset and unlocking the story text frame.
			If at least one story is already locked by another user, the operation is cancelled with a kCancel return
			status. This method has no affect on stories that are already checked out to the current user, or to the
			userName, if specified. This method is undoable.
			@param storyList contains UIDRefs of story page items.
			@param undoabilityFlag applies to all commands that are executed by the implementation of this method.
			@param userName if non-nil, specifies the user name to check the stories out to, and the story text
				frame is not enabled for editing. If nil, the story is checked out to the current user and the story
				text frame is enabled for editing.
			@param displayConflictAlert if kTrue, displays a conflict alert if a story could not be checked out,
				provided that uiFlags allow UI.
			@param uiFlags controls UI that may be displayed to perform the check out. Examples of UI are alerts or
				a dialog requesting a user name if one has not been established.
			@return a predefined ErrorCode if a failure occurs, a kCancel if the operation was canceled, or
				kSuccess if the method completed without error. 		
		*/
		virtual ErrorCode CheckOut( const UIDList& storyList, ICommand::Undoability undoabilityFlag = ICommand::kRegularUndo, const PMString *userName = nil, bool16 displayConflictAlert = kFalse, UIFlags uiFlags = kFullUI ) = 0;
			
		/** Relocks one or more stories. Relocking is used to maintain a lock as in the following situations:
			(1) In InCopy, a "Save Content As", which changes the file path for a checked-out story.
			(2) In InDesign, an operation that changes the UID for a locked story.
			@param storyList contains UIDRefs of story page items.
			@param uiFlags controls UI that may be displayed.
			@return a predefined ErrorCode if a failure occurs, a kCancel if the operation was canceled, or
				kSuccess if the method completed without error. 		
		*/
		virtual ErrorCode RelockStories( const UIDList& storyList, UIFlags uiFlags = kFullUI ) = 0;
		
		/** Saves (exports) content for one or more stories to the respective story files.
			@param storyList contains UIDRefs of story page items.
			@param uiFlags controls UI that may be displayed.
			@return a predefined ErrorCode if a failure occurs, a kCancel if the operation was canceled, or
				kSuccess if the method completed without error. 	
		*/
		virtual ErrorCode SaveStories( const UIDList& storyList, UIFlags uiFlags = kFullUI ) = 0;

		/** Synchronizes the story model lock with the story asset lock so that the two lock states agree.
			That is, if the story asset is checked out, the story model is assured to be unlocked for editing.
			Conversely, if the story asset is not checked out and a story lock is available, the story model is
			locked to prevent editing. This method does not change the story asset lock (the lock on the story file).
			@param storyList contains UIDRefs of story page items.
			@param undoabilityFlag applies to all commands that are executed by the implementation of this method.
			@param progressBar is a valid pointer to an optional progress bar.
			@return a predefined ErrorCode if a failure occurs, kSuccess if the method completed without error, or
				kCancel if a progressBar was specified and the user cancelled the operation.
		*/
		virtual ErrorCode SynchronizeLocks( const UIDList& storyList, ICommand::Undoability undoabilityFlag = ICommand::kRegularUndo, TaskProgressBar * progressBar = nil, UIFlags uiFlags = kFullUI ) = 0;
					
		/** Updates the Link for one or more stories. Updating consists of refreshing the proxy from the
			content file and updating the Link data.
			@param storyList contains UIDRefs of story page items.
			@param undoabilityFlag applies to all commands that are executed by the implementation of this method.
			@param commandName specifies a name for the abortable command sequence used to perform
				the update link operation. If nil, a default command name is used.
			@param uiFlags controls UI that may be displayed
			@return a predefined ErrorCode if a failure occurs, a kCancel if the operation was canceled, or
				kSuccess if the method completed without error. 		
		*/
		virtual ErrorCode UpdateStoryLink( const UIDList& storyList, ICommand::Undoability undoabilityFlag = ICommand::kRegularUndo, PMString * commandName = nil, UIFlags uiFlags = kFullUI ) = 0;
		
	}; // end ILiveEditFacade interface



	/** Tests if the LiveEdit feature is available.
	*/
	inline bool IsLiveEditAvailable()
	{
		return Utils<Facade::ILiveEditFacade>() == nil ? false : true;
	}
} // end namespace Facade

#endif	// __ILIVEEDITFACADE__
