//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IGalleyTextNavigationSuite.h $
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
#ifndef __IGalleyTextNavigationSuite__
#define __IGalleyTextNavigationSuite__

#include "IPMUnknown.h"
#include "ICTextNavigationSuite.h" // For TextSelectionIndex

#include "UIDRef.h"
#include "WritingModeUIID2.h"

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

/** Used to navigate through text in a galley story */
class IGalleyTextNavigationSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGALLEYTEXTNAVIGATIONSUITE };
	
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
		kStory
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

	/**
		Method to set a text selection.
		@param nStart - The beginning of the text range to select
		@param nEnd - The end of the text range to select
		@param endUsedLast - used for extending selection
		@param drawIt - Should the selection be drawn.
		@return kTrue if selection was set.
	*/	
	virtual bool16	SetTextSelection( TextSelectionIndex nStart, TextSelectionIndex nEnd, bool16 endUsedLast = kTrue, bool16 drawIt = kFalse ) = 0;

	/** Select everything 
		@return - kTrue if selection was set
	*/
	virtual bool16	SelectAll ( bool16 drawIt = kFalse) = 0;

	/** Moves the selection to the specified index
		@param nTo - Location to move the selection to
		@param drawIt - should the selection be drawn
		@param nUnits - If the index is invalid, then the units are used to figure things out.
		@param nDirection - Which way to move the selection
		@return - kTrue if selection was set
	*/
	virtual bool16	MoveTextSelection ( TextSelectionIndex nTo = kInvalidTextSelectionIndex, bool16 drawIt = kFalse, Units nUnits = kNone, Direction nDirection = kNext ) = 0;

	/** Expands the selection to the specified index
		@param nTo - Location to expand the selection to
		@param drawIt - Should the selection be drawn
		@param nUnits - Amount to expand the selection
		@param nDirection - Which way to expand the selection
		@return - kTrue if selection was set
	*/
	virtual bool16	ExpandTextSelection ( TextSelectionIndex nTo = kInvalidTextSelectionIndex, bool16 drawIt = kFalse, Units nUnits = kNone, Direction nDirection = kNext  ) = 0;

	/** Scrolls the view to the selection
		@param nStart - Start of the selection
		@param nEnd - End of the selection
		@return - Could the operation be completed
	*/
	virtual bool16	ScrollViewToSelection ( TextSelectionIndex nStart, TextSelectionIndex nEnd ) = 0;

	/** Resets the Up/Down data, anchor data, and end of line data */
	virtual void	Reset () = 0;
	
	// These functins allow outside users to get the relevant Text Nav Data.  The factors tracked here are:
	//		Last up/down position
	//		Anchor point
	//		Start/end indexes end of line data
	
	/** Returns the location of the anchor point (The end of the selection that is not moving)
		@param *anchorIndex - Index of the anchor point
		@param *usedEndLast - Is this point the end of the selection (kTrue) or the beginning (kFalse)
	*/
	virtual void	GetAnchorData ( TextSelectionIndex *anchorIndex, bool16 *usedEndLast ) = 0;
//	virtual void	GetEndOfLineData ( bool16 *startAtEndOfLine, bool16 *endAdEndOfLine ) = 0;

	
};


#endif // __IGalleyTextNavigationSuite__
