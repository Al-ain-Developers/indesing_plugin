//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INotePref.h $
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
#ifndef __INOTEPREF__
#define __INOTEPREF__

#include "IPMUnknown.h"
#include "NotePrefID.h"

/** This session interface presents the inline Notes options : 
	ineline Notes color, inline Notes background color, show Notes tip, 
	find/replace ineline Notes content, and spell check inline Notes content
*/

class INotePref : public IPMUnknown
{
public:	
	/** Which type of background color for Notes to use */
	enum BackgroundColorChoice {kGalleyColorBG, kNoteColorBG};
	
	/** Which type of color for Notes to use */
	enum NoteColorChoice {kUseUserColor, kUseNotePrefColor};


/**	Set the Notes color
	@param colorIndex color index
 */
	virtual void SetColorID(const int32 colorIndex) = 0;

/**	Get the Notes color index
 */
	virtual const int32 GetColorID() const = 0;
				
/**	Show or hide Notes tips containing user info and Notes content
	@param showTips whether to show tips
 */
	virtual void SetShowNoteTips(const bool16 showTips) = 0;

/**	Display Notes tips containing user info and Notes content or not
 */
	virtual const bool16 GetShowNoteTips() const = 0;
	
/**	Set to spell check inline Notes content or not
	@param spellCheck whether to spellcheck
 */
	virtual void SetSpellCheckContent(const bool16 spellCheck) = 0;

/**	Spell check inline Notes content or not
 */
	virtual const bool16 GetSpellCheckContent() const = 0;
				

/**	Set to find/replace inline Notes content or not
	@param findReplace whether to find/replace
 */
	virtual void SetFindReplaceContent(const bool16 findReplace) = 0;

/**	Find/replace inline Notes content or not
 */
	virtual const bool16 GetFindReplaceContent() const = 0;
				
/**	Set the type of inline Notes background color to use
	@param newChoice kGalleyColorBG , kNotesColorBG
 */
	virtual void SetBackgroundColorChoice(const BackgroundColorChoice newChoice) = 0;

/**	Get the type of inline Notes background color to use
	@return const kGalleyColorBG means when display inline Notes, 
						use the galley/story background color(IGalleySettings::GetBackgroundColor()) as inline Notes background color
				  kNotesColorBG means when display inlien Notes, 
						use the user's color if INotePref::GetNoteColorChoice() is INotePref::kUseUserColor, 
						otherwise use INotePref::GetColorID()
 */
	virtual const BackgroundColorChoice GetBackgroundColorChoice() const = 0;
				

/**	Set the type of inline Notes color to use
	@param newChoice kUseUserColor, kUseNotePrefColor
 */
	virtual void SetNoteColorChoice(const NoteColorChoice newChoice) = 0;

/**	Get the type of inline Notes color to use
	@return const kUseUserColor means to display inline Notes using user's color 
				  kUseNotePrefColor means to display inline Notes using INotePref::GetColorID()
 */
	virtual const NoteColorChoice GetNoteColorChoice() const = 0;
};

#endif
