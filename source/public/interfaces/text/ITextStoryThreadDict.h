//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextStoryThreadDict.h $
//  
//  Owner: dwaterfa
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
#ifndef __ITextStoryThreadDict__
#define __ITextStoryThreadDict__

#include "IPMUnknown.h"
#include "TextID.h"
#include "PMTextUtils.h"

class ITextStoryThread;
class IFrameList;


/** 
	The ITextStoryThreadDict is responsible for managing one or more
	ITextStoryThreads within a given ITextModel. All the ITextStoryThreads
	managed by a single dictionary are stored contiguously within the
	ITextModel.

	All ITextStoryThreads managed in this way share the same
	dictionar (see ITextStoryThread::GetDictUID()) but are uniquely
	identified within the managing dictionary by a uint32 whose mapping is
	defined only the dictionary.

	The key value is expected to be the same throughout the life of the
	ITextStoryThread. The addition or removal of other ITextStoryThreads in
	the same dictionary must change the keys of the remaining ITextStoryThreads.

	A ITextStoryThreadDict can be anchored or not. Examples of dictionaries
	which are anchored are Notes, Tables and Footnotes. Examples of unanchored
	dictionaries are Text Macros. All unanchored dictionaries should return an
	anchor position of the last carriage return of the primary story thread.

	Every ITextModel boss implements an ITextStoryThreadDict which is
	responsible for managing the primary story thread. This dictionary is
	not anchored with its thread block text range starting at zero and
	ending at the end of the primary story thread. Unlike all other
	unanchored dictionaries, this dictionary returns an anchor position of
	zero.

	The location of the dictionary's thread block is determined by the location
	of the dictionary's anchor relative to other dictionaries in the same
	and other thread blocks. Determining this relative location is the job
	of the ITextStoryThreadDictHier.

	@see ITextStoryThreadDictHier
	@see ITextStoryThread
	@see ITextModel
	@ingroup text_story
*/
class ITextStoryThreadDict : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTSTORYTHREADDICT };

		/**
		Instantiate the ITextStoryThread with the given key.
		@param key Private unique key that identifies which ITextStoryThread to instantiate
		@return Pointer to ITextStoryThread
		*/
		virtual ITextStoryThread*	QueryThread(uint32 key) const = 0;

		/**
		Returns the current StoryRange where the dictionary is anchored into the ITextModel. Implementations that are not anchored should return the TextIndex of the last carriage return in the primary story thread. The ITextModel, which implements the primary story thread, will return an anchor position of zero.
		@param wasAnchored Optional parameter which will be set to kTrue if the dictionary is anchored, kFalse otherwise.
		@return StoryRange where the dictionary is anchored in the ITextModel.
		*/
		virtual Text::StoryRange	GetAnchorTextRange(bool16* wasAnchored = nil) const = 0;

		/**
		Returns the current StoryRange where the dictionary maintains its
		block of ITextStoryThreads.
		Although unusual, a dictionary which does not currently have any
		ITextStoryThreads in the ITextmodel must return
		StoryRange(kInvalidTextIndex, kInvalidTextIndex).
		@return StoryRange of text spanned by the threads of the dictionary
		*/
		virtual Text::StoryRange	GetThreadBlockTextRange() const = 0;

		/**
		When whole ITextStoryThreads are pasted into the ITextModel the
		StoryThread Strand provides a hook to allow these ITextStoryThreads
		to switch owners.
		This occurs, for example, if the
		ITextStoryThreads from one table were deleted and pasted into
		a different table. The assumption is that the manager of
		this operation will ensure that reference conversion occurs
		on the UIDs in the ITextStoryThreads but there is no way to fix
		up the Keys.
		The iteration that is implied by this operation is setup by the
		code managing the copy and the StoryThread Strand will call
		GetFirstKey() on the first ITextStoryThread pasted and then will call
		GetNextKey() repeatedly for each remaining ITextStoryThread copied.
		@return The first key for the converting range.
		*/
		virtual uint32				GetFirstKey() = 0;	

		/**
		Returns the next key during the paste operation.
		@return The first key for the converting range.
		*/
		virtual uint32				GetNextKey() = 0;

};

#endif	// __ITextStoryThreadDict__
