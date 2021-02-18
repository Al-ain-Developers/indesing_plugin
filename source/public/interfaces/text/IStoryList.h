//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStoryList.h $
//  
//  Owner: EricK
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
#ifndef __ISTORYLIST__
#define __ISTORYLIST__

#include "IPMUnknown.h"
#include "TextID.h"
#include "textstoryaccesstypes.h"

class UIDList;

/** This interface encapsulates a list of stories- each story being a UID.
	The stories are NOT created or deleted here, only managed. Use "NewStoryCmd" and "DeleteStoryCmd"
	for that.

	User accessibility is used across the interface to identify if a story
	was created by the user or whether it was created for internal use. 
	Internal stories are not subject to search through find change, 
	spell checking, and other activities that make sense only for user 
	created stories.
	@ingroup text_story
*/
class IStoryList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTORYLIST }; 

		/** Add an already created story to the list.
			@param story IN story uid to add.
			@param access IN whether the story is user accessible.
		*/
		virtual void AddNewStory(UID story, TextStory_StoryAccess access ) = 0;

		/* Same as AddNewStory except we do it in a command.
		*/
		virtual void ProcessAddNewStory(UID story, TextStory_StoryAccess access) = 0; 
		
		/** Remove a story from the list -- doesn't affect the story itself in any way.
			@param story IN removed story UID.
		*/
		virtual void RemoveStory(UID story) = 0;
		
		/** 
		 @return number of user accessible stories in the document.
		 Use this function when iterating over user accessible stories. 
		*/
		virtual int32 GetUserAccessibleStoryCount() const = 0;

		/** 
			@return number of all stories in the document (both user accessible and not).
			Use this function when iterating over all stories. 
		*/
		virtual int32 GetAllTextModelCount() const = 0;
		
		/** 
			@return UIDRef to Nth user accessible story. Use this function when
			iterating over user accessible stories.
			@param storyIndex IN index in the list of user accessible stories. 
		*/
		virtual UIDRef GetNthUserAccessibleStoryUID(int32 storyIndex) const = 0;

		/** 
			@return UIDRef to Nth story. Use this function when
			iterating over all stories. 
			@param storyIndex IN index in the list of all stories. 
		 */
		virtual UIDRef GetNthTextModelUID(int32 storyIndex) const = 0;
		
		/** 
			@return user accessibility of a particular story. Use this function when
			iterating over all stories. 
			@param storyIndex IN index in the list of all stories. 
		 */
		virtual TextStory_StoryAccess GetNthTextModelAccess(int32 storyIndex) const = 0;
		
		/** 
			@return  index of a particular story in the list of user accessible stories.
			-1 is returned when the story is not in user accessible story list. 
			@param story IN story UID. 
		*/
		virtual int32 GetUserAccessibleStoryIndex(UID story) const = 0;

		/** 
			@return index of a particular story in the list of all stories.
			-1 is returned when the story is not in story list. 
			@param story IN story UID. 
		*/
		virtual int32 GetTextModelIndex(UID model) const = 0;
		
		/** Mark a story as needs composing.
			@param story IN story UID. 
		*/
		virtual void MarkStoryDamaged(UID story) = 0;

		/** Mark story as composed.		
			@param story IN story UID. 
		*/
		virtual void MarkStoryComposed(UID story) = 0;

		/** 
			@return last story marked as need composing.
		*/
		virtual UIDRef GetLastDamagedStory() const = 0;

		/** 
			@return number of marked need composing stories.
			Use when iterating over the need composing stories.
		*/
		virtual int32 CountDamagedStories() const = 0;

		/** 
			@return  Nth damaged story UID.
			Use when iterating over need composing stories.
			@param n IN index in damaged story list.
		*/
		virtual UID GetNthDamagedTextModelUID(int32 n) const = 0;

		virtual bool16 ModifiedStory (UID Story) = 0;

		/** reorder the list of story UIDs to match the parameter.
			can NOT change user accessible stories to be after non-accessible 
			stories.
		*/
		virtual void ReorderStories(const UIDList& desiredOrder) = 0;
};

DECLARE_OBJECT_TYPE (TextStory_StoryAccess);
#endif // __ISTORYLIST__

