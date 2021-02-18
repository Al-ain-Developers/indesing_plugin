//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IMergeStoriesSignalData.h $
//  
//  Owner: Matt Joss
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
#ifndef __IMergeStoriesSignalData__
#define __IMergeStoriesSignalData__

#include "IPMUnknown.h"
#include "TextID.h"

/** 
	A receiver of a kMergeStoriesSignalService can look at this interface to find out which two stories have been merged,
	whether this is pre or post merge or if there was an error doing the merge. Note this signal will only happen on the
	Do() of the command. This interface cannot be used to change the behavior of the command it is for information only.
**/
class IMergeStoriesSignalData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMERGESTORIESSIGNALDATA };
		
		/** State enum that can be retrieved by with the GetState() method.
		*/
		typedef enum { 
		/** Before merge has been done */
		kBeforeDoMerge, 
		/** After merge is done */
		kAfterDoMerge, 
		/** No merge was done error occurred */
		kMergeError } State;
		
		/** Set the data for this interface, when the two stories merge, the source story will be appended to the destination story. 
			Source story will be appended to the destination story. INTERNAL USE ONLY
			@param targetStory same as destination story this story will contain the text of the source and destination story when command is complete.
			@param appendingStory story to be appended to the destination (targetStory).
			@param destIndex indicates the index in the destination story where the source story will begin.  It is the last index in the original destStory.  
			@param length refers to the length of the source story before the merge.
			@param useAppendingStoryOptions (J feature) if true then the frame grid of the source story will be used for the merged stories.
			@return void
		*/
		virtual void		Set(const UIDRef& targetStory, const UIDRef& appendingStory, TextIndex destIndex, int32 length, bool16 useAppendingStoryOptions) = 0;
		
		/** Used to set the state that the command was in when this signal was sent. INTERNAL USE ONLY
			@param state see comments on the State enum.
			@return void
		*/		
		virtual void		SetState( State state ) = 0;
		
		/** This story will have the data from the other story (AppendingStory) append to it when the command is complete.
			@return UIDRef reference of the target story.
		*/		
		virtual	UIDRef 		GetTargetStory() const = 0;
		
		/** Get reference of the story to be appended to the target story.
			@return UIDRef reference of the story to be appended to the target story.
		*/		
		virtual	UIDRef 		GetAppendingStory() const = 0;
		
		/** Indicates the index in the target story where the appending story will begin. Last original primary story index of the original target story.
			@return text index where the appending story begins in the target story.
		*/		
		virtual	TextIndex 	GetDestinationTextIndex() const = 0;
		
		/** Refers to the length of the appending story.
			@return number of primary story characters in the appended story
		*/		
		virtual	int32		GetAppendingStoryLength() const = 0;
		
		/** Use the frame grid of the appending story will be used for the merged story result
			@return if true the target storise frame grid will be used instead of the target stories.
		*/
		virtual	bool16		UseAppendingStoryOptions() const = 0;
		
		/** What is the state of the command (i.e. before or after completion).
			@return State enum which describes current state of command doing the merge.
		*/
		virtual	State		GetState() const = 0;
		
};


#endif
		// __IMergeStoriesSignalData__
