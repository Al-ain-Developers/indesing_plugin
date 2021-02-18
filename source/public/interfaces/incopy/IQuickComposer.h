//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IQuickComposer.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IQuickComposer__
#define __IQuickComposer__

#include "IPMUnknown.h"

#include "WritingModeUIID2.h"
#include "LineDescription.h"

class IdleTimer;

/**
	Methods to compose text in story and galley views.
**/
class IQuickComposer : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IQUICKCOMPOSER };
	
		/**
			Compose a range of text for a story view.
			@param textModelRef reference of the text model to use.
			@param startLineIndex line where composition should start.
			@param textStartPosition text index where composition should start can be display index or text model index value of isGalleyDisplayStartPosition tells which.
			@param numCharsAdded number of characters added or deleted from the model (negative if deleted).
			@param clearLines used when initializing the view, tells the composer to remove all existing text lines before starting.
			@param isGalleyDisplayStartPosition tell composer whether the textStartPosition is a text model index or a galley display index.
			@param startNewStory used internally pass false
			@param startRunTypeClue can be used the help the composer figure out what type of run the textStartPosition starts in.
			@return none
		**/
		virtual void Compose(const UIDRef& textModelRef, int32 startLineIndex, TextIndex textStartPosition, int32 numCharsAdded,
							bool16 clearLines, bool16 isGalleyDisplayStartPosition = kFalse, bool16 startNewStory = kFalse,
							RunDescription::RunType startRunTypeClue = RunDescription::regularText) = 0;

		/**
			When a story is first created or you want to destroy all lines and recreate all or part of them again call this. Will trigger background
			composition if only some of the story is composed
			@param textModelRef reference of the text model to use.
			@param textStartPosition text model index to start composing at.
			@param textEndPosition text model index to start composing at.
			@return none
		**/
		virtual bool16 InitializeRange(const UIDRef &textModelRef, TextIndex textStartPosition, TextIndex textEndPosition) = 0;

		/**
			Used to create a range of lines to compose in the background to speed up opening a new story editor window. Psuedo lines are
			lines that are not composed but are a placeholder for later replacement with actual true composed TextLines. The ranges to create
			psuedo lines for are more of a guide the actual psuedo lines will begin and end only at paragraph boundaries.
			@param textModelRef reference of the text model to use.
			@param startIndex text model index to start creating psuedo lines for.
			@param length how many characters to create psuedolines for.
			@return none
		**/
		virtual void CreatePsuedoRange(const UIDRef &textModelRef, TextIndex startIndex, int32 length) = 0;

		/**
			Given the location of a psuedoline created by CreatePsuedoRange convert the psuedo line to a truly composed line.
			@param textModelRef reference of the text model to use.
			@param startLineIndex text model index of the start of the psuedo line.
			@param timeCheck can pass a time limit (used when called from idle task) to limit the amount of time this routine is allowed to perform its task.
			@return kTrue if success
		**/
		virtual bool16 UnPsuedoLine(const UIDRef &textModelRef, int32 startLineIndex, IdleTimer* timeCheck) = 0;
	
		/** When you know you need to compose through a range of text call this. Useful, when composing attribute changes or similar type things.
		    Returns the last character it composed through
			@param textModelRef reference of the text model to use.
			@param startLineIndex index of line to start composing at
			@param textStartPosition text model index to start composing at
			@param textEndPosition text model index to stop composing at (or that it may stop composing at the routine may decide to compose further)
			@param numCharsAdded how many characters have been added or deleted from the model.
			@param ownedItemDamage true if the notes or other owned item type things caused the compose
			@return textindex where composition stopped.
		**/
		virtual TextIndex ComposeRange(const UIDRef &textModelRef, int32 startLineIndex, TextIndex textStartPosition, 
									TextIndex textEndPosition, int32 numCharsAdded, bool16 ownedItemDamage = kFalse) = 0;

		/** Compose a specific textline for Story View normally called from Compose().
			@param textModelRef reference of the text model to use.
			@param at index of line to compose
			@param textStartPosition text model index to start composing at
			@param numCharsAdded number of characters that the change that caused this compose added or deleted
			@param isGalleyDisplayStartPosition if the textStartPosition is a galleyDisplayIndex pass kTrue for this
			@param startNewStory internal use pass kFalse or let auto initialization take care of it
			@param ownedItemDamage internal use 
			@return textindex where composition stopped.
		**/		
		virtual bool16 ComposeLine(const UIDRef& textModelRef, int32 at, TextIndex textStartPosition, int32 numCharsAdded, 
							bool16 isGalleyDisplayStartPosition = kFalse, bool16 startNewStory = kFalse, bool16 ownedItemDamage = kFalse) = 0;
				
		/** Compose a Galley View overset line (ALE = accurate line endings). This routine is really a failsafe normally overset lines are composed
			by normal means because a extra frame is added so to the layout composer there is no difference between overset and normal text while in
			InCopy. However, some text cannot be composed into a overset frame because it is too big etc. That's where this routine will get called
			to compose something reasonable for the overset text so that it can be displayed in the galley view. (INCOPY ONLY)
			@param textModelRef reference of the text model to use.
			@param startLineIndex of line to compose
			@param textStartPosition text model index to start composing at
			@param numCharsAdded number of characters that the change that caused this compose added or deleted
			@param startLineNumber line number to display in info column
			@return textindex where composition stopped.
		**/				
		virtual void ComposeOversetAle(const UIDRef& textModelRef, int32 startLineIndex, TextIndex textStartPosition, int32 numCharsAdded, int32 startLineNumber) = 0;
		
		/** Used to compose ale lines to window after layout composition creates the line ends for us.
			@param textModelRef reference of the text model to use.
			@param at startLineIndex of line to compose
			@param description initial line description created from data in the waxline
			@param layoutLineIsHyphenated true if the associated waxline is ends in a hyphen
			@return textindex where composition stopped.
		**/				
		virtual int32 ComposeAleLine(const UIDRef &textModelRef, int32 at, LineDescription &description, bool16 layoutLineIsHyphenated = kFalse) = 0;
				
		/** 
			Internal use only
		**/			
		virtual void SetInstantDraw(bool16 instantDraw) = 0;
		
		/** If composition is temporarily suppressed this will return false.
			@return none
		**/				
		virtual bool16 CompositionEnabled() = 0;
				
};


#endif 		// __IQuickComposer__
