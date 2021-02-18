//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ICTextNavigationSuite.h $
//  
//  Owner: Ben Park
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
#ifndef __ICTextNavigationSuite__
#define __ICTextNavigationSuite__

#include "IPMUnknown.h"

#include "UIDRef.h"
#include "WritingModeUIID2.h"
#include "WritingModeID2.h"
class RangeData;
/*
		This sucker is used for navigating the Galley Text.  The big table below was copied from
		ITextSelectionNavigator, and it's a list of keyboard shortcuts that can be used.  
		I'll modify it as new stuff is added.  Of course, this can be used w/o keyboard shortcuts 
		(ex. triple click will select a paragraph).
		
		No.	Shortcut						Unit		Direction	Type			Mac OS					Windows
		======================================================================================================
	 	699	Move to the right one character 	kChar	kNext	replace		Right arrow 				Right arrow 
	 	700	Move to the left one character 		kChar	kPrev	replace		Left arrow 				Left arrow
	 	701	Move up one line 				kLine		kPrev	replace		Up arrow 					Up arrow 
	 	702	Move down one line 				kLine		kNext	replace		Down arrow 				Down arrow 
	 	703	Move to the right one word 		kWord	kNext	replace		Cmd + Right Arrow 			Ctrl + Right Arrow 
	 	704	Move to the left one word 			kWord	kPrev	replace		Cmd + Left Arrow 			Ctrl + Left Arrow
	 	705	Move to the start of the line 		kLine		kStart	replace		Home 					Home
	 	706	Move to the end of the line 		kLine		kEnd		replace		End 						End
	 	707	Move to the previous para 		kPara	kPrev	replace		Cmd + Up Arrow 			Ctrl + Up Arrow
	 	708	Move to the next para 			kPara	kNext	replace		Cmd + Down Arrow		 	Ctrl + Down Arrow
	 	709	Move to end of story 			kStory	kEnd		replace		Cmd + End 				Ctrl + End
	 	710	Move to begining of story 			kStory	kStart	replace		Cmd + Home 				Ctrl + Home
	 	712	Select word 					kWord	kAll		replace		Double Click 				Double Click 
	 	713	Select one character to the right 	kChar	kNext	expand		Shift + Right  Arrow 		Shift + Right  Arrow 
	 	714	Select one character to the left 	kChar	kPrev	expand		Shift + Left  Arrow 			Shift + Left  Arrow 
	 	715	Select one word to the right 		kWord	kNext	expand		Cmd + Shift + Right Arrow 	Ctrl + Shift + Right Arrow
	 	716	Select one word to the left 		kWord	kPrev	expand		Cmd + Shift + Left Arrow 		Ctrl + Shift + Left Arrow 
	 	717	Select to the start of the line 		kLine		kStart	expand		Shift + Home 				Shift + Home
	 	718	Select to the end of the line 		kLine		kEnd		expand		Shift + End 				Shift + End
	 	719	Select one line above 			kLine		kPrev	expand		Shift +  Up Arrow 			Shift +  Up Arrow 
	 	720	Select one line below 			kLine		kNext	expand		Shift + Down Arrow 			Shift + Down Arrow 
	 	721	Select one paragraph before		kPara	kPrev	expand		Cmd + Shift + Up Arrow 		Ctrl + Shift + Up Arrow
	 	722	Select one paragraph forward 		kPara	kPrev	expand		Cmd + Shift + Down Arrow 	Ctrl + Shift + Down Arrow
	 	723	Select all chars. in story 			kStory	kAll		expand		Cmd + A 					Ctrl +  A 
	 	724	Select chars. from  insertion point 	kChar	kAll		expand		Shift + Click				Shift + Click 
	 	725	Select to end of story 			kStory	kEnd		expand		Cmd + Shift + End			Ctrl + Shift + End
	 	726	Select to beginning of story 		kStory	kStart	expand		Cmd + Shift + Home			Ctrl + Shift + Home
*/
 
/** Used as a helper classs for ICTextNavigationSuite. Allows more than the TextIndex to be passed to a method as a single parameter indicating a selection */
 class TextSelectionIndex
 {
 
 public:
 	inline			TextSelectionIndex() :
 						fIndex( kInvalidTextIndex ),
 						fEndOfLine( kFalse )
 					{};
 
 
	/** Construct a TextSelectionIndex
		@param nIndex - The selection location
		@param endOfLine - Does the selection extend past the end of the line?
	*/
 	inline			TextSelectionIndex( TextIndex nIndex, bool16 endOfLine /*= kFalse*/) : 
 						fIndex( nIndex ), 
 						fEndOfLine( endOfLine )
 					{ }
 	
	/** Uses the data from another TextSelectionIndex to fill in this one
		@param &rhs - The class to make this equal to
		@return - A reference to this so that you can string operations together.
	*/
 	TextSelectionIndex& operator= (const TextSelectionIndex& rhs)
 	{
 		fIndex = rhs.fIndex;
 		fEndOfLine = rhs.fEndOfLine;
 		
 		return *this;
 	}
 	
	/** The text index to select (or that is selected) */
 	TextIndex		fIndex;

	/** Does the selection extend past the end of the line */
 	bool16			fEndOfLine;
 };
 
 const TextSelectionIndex kInvalidTextSelectionIndex (kInvalidTextIndex, kFalse);
 
 
 
class SelectionExtension;

/** Used to navigate through text in a story */
class ICTextNavigationSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICTEXTNAVIGATIONSUITE };
	
	/** Used to indicate the size to extend/decrease the selection by */
	enum Units { 
		/** No preference */
		kNone,
		/** Extend by a character */
		kChar,
		/** Extend by a word */
		kWord,
		/** Extend by a line */
		kLine,
		/** Extend by a paragraph */
		kParagraph,
		/** Extend by a story */
		kStory,
		/** Extend by a sentence */
		kSentence 
	};

	/** Used to indicate the direction in which to extend/decrease the selection */
	enum Direction {
		/** Go forward */
		kNext,
		/** Go backward */
		kPrev,
		/** Go to the start */
		kStart,
		/** Go to the end */
		kEnd,
		/** No preference */
		kAll  
	}; 

#if 0
	/**
		Method sets and optionally draws and/or scrolls to a galley/story text selection.
		@param nStart Start of new text selection range to set
		@param nEnd End of the new text selection range to set
		@param endUsedLast used for extending selection if true then end of selection was last modified
				default value is kTrue
		@param drawIt Pass kTrue to draw the selection now default is kFalse
		@param autoScroll Pass kTrue to enable autoScroll to the selection position. Only
				scrolls if drawIt is also True. Default value is kTrue.
		@return kTrue if selection was set.
	*/	
#endif

	/** Used to indicate whether or not to scroll to the selection */
	enum ScrollChoice {
		/** Do not scroll the new selection into view */
		kDontScrollSelection,
		/** Scroll the new selection into view */
		kScrollIntoView
	};

	/** Used to indicate whether the start or end of the selection is allowed to move */
	enum LooseEnd { 
		/** The start of the selection can move freely */
		kLooseStart,
		/** The end of the selection can move freely */
		kLooseEnd
	};

	//virtual bool16  SetTextSelection( const RangeData& range, 
	//	bool16 endUsedLast = kTrue, bool16 drawIt = kFalse, bool16 autoScroll = kTrue ) = 0;

	/**
		Method to set a text selection.
		@param range Text range to set a text selection on
		@param endUsedLast used for extending selection
		@param autoScroll should it autoscroll to the newly set selection
		@param extendToUIDPair If want adjacent track changes to be included in the highlight must set the UID of the track change owned item.
					this is mainly an internal implementation detail. May pass in nil or nothing to ignore this value (this is the typical case).
		@return kTrue if selection was set.
	*/	
	virtual bool16	SetTextSelection( const RangeData& range, 
		LooseEnd endUsedLast /*= kLooseEnd*/, ScrollChoice autoScroll /*= kScrollIntoView*/, SelectionExtension *extendToUIDPair = nil) = 0; //draw == true

	/** Select everything 
		@return - kTrue if selection was set
	*/
	virtual bool16	SelectAll() = 0;

	/** Moves the selection to the specified index
		@param nTo - Location to move the selection to
		@param nUnits - If the index is invalid, then the units are used to figure things out.
		@return - kTrue if selection was set
	*/
	virtual bool16	SelectTextAt( TextSelectionIndex nTo, Units nUnits) = 0;

	/** Moves the selection by a specified unit
		@param nUnits - Amount to move the selection
		@param nDirection - Which way to move the selection
		@return - kTrue if selection was set
	*/
	virtual bool16	MoveTextSelection( Units nUnits, Direction nDirection) = 0; //drawit == kTrue

	/** Expands the selection to the specified index
		@param nTo - Location to expand the selection to
		@return - kTrue if selection was set
	*/
	virtual bool16	ExpandTo( TextSelectionIndex nTo) = 0;

	/** Expands the selection by a specified unit
		@param nUnits - Amount to expand the selection
		@param nDirection - Which way to expand the selection
		@return - kTrue if selection was set
	*/
	virtual bool16	ExpandTextSelection ( Units nUnits, Direction nDirection) = 0;

	/** Resets the Up/Down data, anchor data, and end of line data. */
	virtual void	ResetNavigationState () = 0;
	
	// These functins allow outside users to get the relevant Text Nav Data.  The factors tracked here are:
	//		Last up/down position
	//		Anchor point
	//		Start/end indexes end of line data

	/** Returns the location of the anchor point (The end of the selection that is not moving)
		@param *usedEndLast - Is this point the end of the selection (kTrue) or the beginning (kFalse)
		@return - The location of the anchor point
	*/
	virtual RangeData	GetAnchorData ( bool16 *usedEndLast ) = 0;

	/** Does what needs to be done when the user clicks, double-clicks, etc. in text.
		@param clickCount - The number of clicks received
		@param newPosition - The position of the clicks
		@param *pEnd - Filled with the end of the new selection
		@return - The start of the new selection
	*/
	virtual	TextIndex InterpretHitTest( int32 clickCount, TextIndex newPosition, TextSelectionIndex *pEnd) = 0;


	/** Scrolls the text selection into the window so that it can be viewed */
	virtual void	MoveSelectionToVisiblePage() = 0;

};


#endif // __ICTextNavigationSuite__
