//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IRedlineDataStrand.h $
//  
//  Owner: Eric Menninga
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
#ifndef __IRedlineDataStrand__
#define __IRedlineDataStrand__

#include "IPMUnknown.h"
#include "InCopySharedID.h"
#include "K2Vector.h"
#include "VOSRedline.h"
#include "ICommand.h"

class ITextModel;
class RedlineIterator;

class IRedlineDataStrand : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IREDLINEDATASTRAND };
		
		virtual bool16 DoSyncToStory(UID story) = 0;
		virtual UID GetTextModelUID() const = 0;		
		
		virtual	void ApplyRedlineChange(VOSRedlineChange::RedlineChangeType type, TextIndex position,
		                                const uint64& time, bool16 moved, int32 len, const PMString& user) = 0;
		// Applies a change with the indicated data this redline strand, splits strand object and attaches appropriate record                  				 

		virtual void UndoChange(TextIndex pos, RedlineChangeUndo *undo, int32 changeLen, bool16 inserted, bool16 undoReject) = 0;
		virtual RedlineChangeUndo* DoAcceptChange(TextIndex position, const VOSRedlineChange& change, int32 *changeLen) = 0;
		virtual RedlineChangeUndo* DoRejectChange(TextIndex position, const VOSRedlineChange& change, int32 *changeLen, bool16 *inserted) = 0;
				
		virtual	void DoAcceptRedlineChangeRange(TextIndex position, int32 len) = 0;
		// Accepts just the range from position to position+len, indicates if was necessary to divide at front and/or back of the object
		virtual	void UndoAcceptRedlineChangeFront(TextIndex position, int32 len) = 0;
		virtual	void UndoAcceptRedlineChangeBack(TextIndex position, int32 len) = 0;
		virtual	void UndoAcceptRedlineChangeMiddle(TextIndex position, int32 len) = 0;
		// Undo the accept range

		virtual	void RemoveRedlineChange(TextIndex objPosition, const VOSRedlineChange& changeToRemove) = 0;
		// Removes a change with the indicated data from the redline object at the specified text position.
		virtual	void ClearRedlineChanges(TextIndex objPosition) = 0;
		// Clears all changes from the redline object at the specified text position.

		typedef enum { 

			// phases are used to "tweak" the results of various user actions and commands
			// (including undo/redo) so that the redline strand is kept in good condition
			// it is difficult to tell where the delete/insert originated from so we use
			// this technique to provide the needed information

			kPhase_Normal, 
			kPhase_Storage, 
			kPhase_Rejecting,		// so we don't track deletes as a result of rejecting an insert change
			kPhase_MovingStory,		// to prevent deletions resulting from movestoryrangecmd being put into backing storage
			kPhase_MovingStoryAndPreserve,	// kPhase_MovingStory and indicate preserve track changes data (i.e. place InCopy story vs. text file)
			kPhase_CreatingNote,		// so we can match to tracking state of text receiving the note
			kPhase_XMLDeleteMarker,		// so we avoid tracking delete of xml marker (i.e. during untag or convert to note)
			kPhase_XMLInsertMarker,		// so we avoid tracking insert of xml marker (i.e. during tag or convert to note)
			kPhase_TrackConvertNote,	// so we track text converted from text if changes are being tracked
			kPhase_ConvertingNote,		// so deletion of note is not tracked when converting note to text
			kPhase_SkipTable,			// so deletion of table is not tracked when done via table menu delete - table has been dismantled so not safe to track
			kPhase_IMEInsertResult,		// so we only track the ime insert result not the delete of temp chars
			kPhase_IMEInsertComp		// so we don't track ime temp chars insert and delete
		} RedlinePhase;

		virtual void PushPhase(RedlinePhase phase) = 0;
		virtual void PopPhase() = 0;
		virtual RedlinePhase CurrentPhase() = 0;
		
		/** 
			Iterate track changes in model order. Most code uses this rather than the NewRedlineDisplayOrderIterator() method.
			@param startingAt IN - where to start iteration at
			@param atChange IN a single location may have more than one change, if you know you want to start on a specific change index specify it with this.
			@return iterator that allows traversal of the track changes in the order they appear in the text model
		*/
		virtual RedlineIterator* NewRedlineIterator(TextIndex startingAt = 0, int32 atChange= -1) = 0;
		
		/** 
			Iterate track changes in display order. Used for ui code. There is more overhead for this method than the NewRedlineIterator().
			@param startingAt IN - where to start iteration at
			@param atChange IN a single location may have more than one change, if you know you want to start on a specific change index specify it with this.
			@return iterator that allows traversal of the track changes in the order they appear on the screen in story and galley views.
		*/
		virtual RedlineIterator* NewRedlineDisplayOrderIterator(TextIndex startingAt = 0, int32 atChange= -1) = 0;

		/**
			Check whether the story contains tracked changes which are not in hidden conditional text.

			@return bool16 kTrue if story contains tracked changes. Otherwise return kFalse.
		*/
		virtual bool16 StoryHasChanges() const = 0;

		typedef enum
		{
			kCST_Unknown,	// unknown change, update all
			kCST_Insert,	// a new change is inserted
			kCST_Remove		// an existing change is removed
		} ChangeStateTransition;

		/**
			Updates StoryHasChanges flag if necessary.
		*/
		virtual void UpdateChangeStatus(ChangeStateTransition transition) = 0;
};

#endif
		// __IRedlineDataStrand__

