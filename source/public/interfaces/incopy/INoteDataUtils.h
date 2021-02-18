//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INoteDataUtils.h $
//  
//  Owner: Wai Cheuk
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
#ifndef __INOTEDATAUTILS__
#define __INOTEDATAUTILS__

#include "NoteID.h"
#include "INoteDataUtils.h"
#include "IPMUnknown.h"
#include "UIDList.h"
#include "RangeData.h"
#include "ITextModel.h"
//#include "INoteMarkerRange.h"

//-----------------------------------
//	Forward References
//
class INoteChangePrefs;
class WideString;
class IDocument;
class IControlView;
class ITextLines;
class ITextRuns;

/** Notes related utility interface. 
*/
class INoteDataUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INOTEDATAUTILS };
	/** The type of Note found*/
	enum Note_Type { kBookEnd, kNoteContent, kHitTestStoryText, kHitDeletedText };
	
/**	Get page number and page string based on the param anchorPos
	@param anchorPos The main storythread text index where the Note is at
	@param textModel The story
	@param pageString return the page number string with a given text index in the story.
	@return int32 The physical page number with a given text index in the story.
 */
	virtual int32 GetPageNumberOfTextIndex(TextIndex anchorPos, ITextModel* textModel, PMString * pageString = nil) = 0;
				
	/**	With a given Note (param noteDataUID), get the nth number Notes in the param storyRef
		@param storyRef 
		@param noteDataUID 
		@param currentNoteNumber Return nth number Notes
	 */
	virtual void GetNoteNumber(UIDRef storyRef, UID noteDataUID, int32& currentNoteNumber) const = 0;
	

	/**	Get the total Notes count in param storyRef
		@param storyRef 
		@param totalStoryNoteCount 
		@return int32 
	 */
	virtual int32 GetStoryNoteCount(UIDRef storyRef, int32& totalStoryNoteCount) const = 0;
	
	/**	Count the words in a note
		@param textModel reference to the text model the note is contained by
		@param begin text index of start of note
		@param end text index of end of note
		@param charCount optional may get the number of characters if you pass a pointer to charCount (it's a filtered char count)
		@return the number of word in the range specified for the note
	*/	
	virtual int32 CountWords(ITextModel* textModel, TextIndex begin, TextIndex end, int32 *charCount = nil) = 0;
	

	/**	Returns kTrue if the character we're looking at is a word break character.
		Used by CountWords.
		@param currChar 
		@return bool16 
	 */
	virtual bool16 IsWordBreak(const UTF32TextChar& currChar) = 0;
	
	/** Returns kTrue if the character we're looking at is a punctuation that can be in the middle of a word
		Used by CountWords.
		@param currChar
		@return
	*/
	virtual	bool16 IsPunctuation(const UTF32TextChar& currChar) = 0;

	/**
		Create a new note at createAt location in a given story
		and document.  No note will be created if createAt is
		outside the main story thread.
		@param createAt The text index the Note to be added to
		@param storyRef
		@param docRef
		@return UIDRef Return the newly added Note UIDRef
	*/
	virtual	UIDRef NewNote(TextIndex createAt, UIDRef storyRef, UIDRef docRef) = 0;

	/** Given the Note's author, find out the color index from user color list
		It uses IInCopyDocUserList to do the conversion.
		@param docRef 
		@param userName 
		@return int32 
	 */
	virtual int32 GetNoteColorIndex(UIDRef docRef, const WideString& userName) const = 0;

/**	Return the note color index with the given user name;
	It uses IInCopyDocUserList to do the conversion.
	@param docDataBase 
	@param userName 
	@return int32 
 */
	virtual int32 GetNoteColorIndex(IDataBase* docDataBase, const WideString& userName) const = 0;


/**	Return the inline note background color index with the given user name;
	@param docRef 
	@param userName 
	@return int32 
 */
	virtual int32 GetNoteBGColorIndex(UIDRef docRef, const WideString& userName) const = 0;

/**	Return the inline note background color index with the given user name;
	It uses IInCopyDocUserList to do the conversion.
	@param docDataBase 
	@param userName 
	@return int32 
 */
	virtual int32 GetNoteBGColorIndex(IDataBase* docDataBase, const WideString& userName) const = 0;

/**	Can be used by any UI element to detect if inline note exists over the
	SysPoint globalPoint with the given writing view.  This method returns
	the note collapsed state in bIsCollapsed, the Note_Type in typeFound, 
	the line index where the note data is in pLineIndex, and finally,
	the character offset in that line in pOffsetIntoLine.

	@param writingView Galley control view 
	@param globalPoint 
	@param bIsCollapsed 
	@param typeFound 
	@param originalStoryIndex 
	@param activeStoryIndex 
	@param pLineIndex 
	@param pOffsetIntoLine 
	@return bool16 
 */
	virtual bool16 DetectInlineNoteData(IControlView* writingView, const SysPoint globalPoint, 
										bool16* bIsCollapsed, int16* typeFound, 
										int32* originalStoryIndex, int32* activeStoryIndex,
										int32* pLineIndex = 0, int32* pOffsetIntoLine = 0) const = 0;

/**	Check if this is a Note by given the object's ClassID
	@param id 
	@return bool16 
 */
	virtual bool16 IsNoteOwnedItem(ClassID id) = 0;
	
/**	Setup Note owned item information
	@param textModelRef 
	@param textIndex 
	@param ownedItemClass 
	@param ownedItemUID 
 */
	virtual void SetupOwnedItemInfo(UIDRef textModelRef, TextIndex textIndex, ClassID ownedItemClass, UID ownedItemUID) = 0;
};

#endif // __INOTEDATAUTILS__
