//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextWalkerScope.h $
//  
//  Owner: Habib Khalfallah	
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
#ifndef __ITextWalkerScope__
#define __ITextWalkerScope__
#include "TextWalkerServiceProviderID.h"
#include "ITextModel.h"
#include "ITextFocus.h"
#include "PMTextUtils.h"

/** 
	@ingroup text_find
*/
class ITextWalkerScope : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTWALKERSCOPE};

	/** scope state lock type */
	enum LockType {kLockForRead /** read lock */, kLockForWrite /** write lock */};

	/** 
		Sets scope lock state to the specified lock type.

		@param lockType 	lock type for scope lock state to set to.

		@return bool16	kTrue if successfully set the lock state.
	*/
	virtual bool16 		LockScope(LockType lockType) const = 0;

	/** 
		Releases scope lock.

		@return bool16	kTrue if successfully released the lock state.
	*/
	virtual bool16 		UnlockScope() const = 0;

	/** 
		Checks if scope is lock.

		@return bool16	kTrue if the scope is unlocked, kFalse if otherwise.
	*/
	virtual bool16		IsLocked() const = 0;

	/** 
		Checks if doc list is empty.

		@return bool16	kTrue if the doc list is empty, kFalse if otherwise.
	*/
	virtual bool16		IsEmpty() const = 0;

	/** 
		Adds the specified document to the doc list.

		@param doc	Document to be added.
	*/
	virtual void 		SetNextDoc(const UIDRef& doc) = 0;

	/** 
		Adds the specified story to the document last added.

		@param story		Story to be added.
	*/
	virtual void 		SetNextStory(UID story) = 0;

	/** 
		Adds the specified story ranges to the document last added.

		@param list	list of story ranges to be added.
	*/
	virtual void 		SetNextRange(const Text::StoryRangeList* list) = 0;

	/** 
		Removes the specified document from the doc list.

		@param doc	Document to be removed.

		@return bool16	kTrue if successfully removed the document.
	*/
	virtual bool16 		RemoveDoc(const UIDRef& doc) = 0;

	/** 
		Removes the specified story from the specified document in the doc list.

		@param doc	Document from which the story to be removed.
		@param story	Story to be removed.

		@return bool16	kTrue if successfully removed the story. 
	*/
	virtual bool16 		RemoveStory(const UIDRef& doc, UID story) = 0;

	/** 
		Gets the total character count in all the doc list documents .

		@return int32	Total character count. 
	*/
	virtual int32		GetCharTotal() const = 0;

	/** 
		Gets document in doc list for the specified token.

		@param token		token used to retrieve document.
		
		@return UIDRef& 	document retrieved for the token.
	*/
	virtual const UIDRef&		GetCursorDoc(void *token) const = 0;
	
	/** 
		Gets story of a document in doc list for the specified token.

		@param token		token used to retrieve story.
		
		@return UID 	story retrieved for the token.
	*/
	virtual UID			GetCursorStory(void *token) const = 0;

	/** 
		Gets cursor range for the specified token.

		@param token			token used to retrieve cursor range.
		@param pAdjustable	[OUT] returns whether the range is adjustable or not when it's not nil. 
							one can only adjust when the cursor is the first of a 
							multi-focus range. In addition, the start of the first range 
							must equal the last of the last range.
		@param pCharOffset	[OUT] when non-nil, contains total character count before the range.
		@param searchBackwards	Direction for the current search. Value is kTrue if searching backwards.
		
		@return ITextFocus* 	cursor range for the specified token.
	*/
	virtual ITextFocus* GetCursorRange(void *token, bool16 *pAdjustable = nil,
										int32* pCharOffset = nil, bool16 searchBackwards=kFalse) const = 0;

	/** 
		Resets cursor range to start of the story.

		@param token			Token for the cursor range.
		@param delta			Distance to advance for the range.
		
		@return bool16	 	kTrue if range was adjusted successfully.
	*/
	virtual bool16		AdjustRangeToStoryStart(void *token, int32 delta) = 0;

	/** 
		Resets cursor range to end of the story.

		@param token			Token for the cursor range.
		@param delta			Distance to recede for the range.
		
		@return bool16	 	kTrue if range was adjusted successfully.
	*/
	virtual bool16		AdjustRangeToStoryEnd(void *token, int32 delta) = 0;

	/** 
		This method is called when we are a full story scope and we wish to
		limit the walk to the end of the story. In this regard we are really
		trying to interrupt the full walk and stop at the bottom.
		If we already have passed the end and are wrapping around then this does
		nothing.
		
		@param token			token for the cursor range.
		
		@return bool16	 	kTrue if range was extended successfully.
	*/
	virtual bool16		ExtendRangeToEndOfStory(void *token) = 0;

	/** 
		This method is called when we are a partial (end-of-story) scope and we
		wish to limit the walk to the end of the story. Although we expect to
		only be called with end-of-story scope, this algorithm will extend any
		scope to the full story.		
		
		@param token			token for the cursor range.
		
		@return bool16	 	kTrue if range was extended successfully.
	*/
	virtual bool16		ExtendRangeToStory(void *token) = 0;

	/** 
		Moves doc cursor to next document in the doc list.
		
		@param token			token for current cursor.
		
		@return bool16	 	kTrue if successfully moved cursor to next document.
	*/
	virtual bool16 		MoveToNextDoc(void *token) const = 0;

	/** 
		Moves story cursor to next story in the doc list.
		
		@param token			token for current cursor.
		
		@return bool16	 	kTrue if successfully moved cursor to next story.
	*/
	virtual bool16 		MoveToNextStory(void *token) const = 0;

	/** 
		Moves range cursor to next range in the doc list.
		
		@param token			token for current cursor.
		
		@return bool16	 	kTrue if successfully moved cursor to next range.
	*/
	virtual bool16 		MoveToNextRange(void *token) const = 0;	
	
	/** 
		Gets a new cursor based on the token if provided.
		
		@param basedOn		token to be based on for getting the new cursor.
		
		@return void*	 	token for the new cursor.
	*/
	virtual void*		GetNewCursor(void * basedOn = nil) const = 0;

	/** 
		Releases the cursor for the specified token.
		
		@param token		token for the cursor to be released.
		
		@return bool16	 	kTrue if cursor was released successfully.
	*/
	virtual bool16		ReleaseCursor(void * token) const = 0;

	/** 
		Sets the focus position for the specified cursor.
		
		@param token		token for the cursor to be set.
		@param nPosition 	text index to set focus to.
	*/
	virtual void		SetPosition(void *token, TextIndex nPosition) = 0;

	/** 
		Gets the focus position for the specified cursor.
		
		@param token		token for the cursor to get focus from.
		
		@return TextIndex 	text index of the focus position.
	*/
	virtual TextIndex	GetPosition(void *token) const = 0;

	/** 
		Sets the client focus for the specified token.
		
		@param token		token for the cursor to set focus.
		@param nStart	start text index to set focus to.
		@param nLength	length of the text to set focus to.
	*/
	virtual void		SetClientSelection(void *token,  TextIndex nStart, int32 nLength) = 0;

	/** 
		Gets the client focus for the specified token.
		
		@param token		token for the cursor to get focus.
		@param start		[OUT] start text index of retrieved focus.
		@param length	[OUT] length of the text of retrieved focus.

		@return ITextFocus*	Client focus for the specified token.
	*/
	virtual ITextFocus*	GetClientSelection(void *token, TextIndex& start, int32& length) const = 0;

	/** 
		Specified whether to allow the client focus to set range.
		
		@param token		token for the client focus.
		@param bAllow	kTrue if allows to set range, kFalse otherwise.
	*/
	virtual void		AllowClientSelectionSetRange(void *token, bool16 bAllow) = 0;

	/** 
		Clears client focus for the specified token.
		
		@param token		token for the client focus.
	*/
	virtual void		ClearClientSelection(void *token)  = 0;
};

#endif
