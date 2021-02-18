//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/text/ISpellCheckWalkerData.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __ISpellCheckWalkerData__
#define __ISpellCheckWalkerData__

#include "IPMUnknown.h"
#include "SpellPanelID.h"
#include "ISpellingService.h"
#include "PMTextUtils.h"

class ITextModel;
class ILanguage;
class WideString;

//----------------------------------------------------------------------------------------
// Interface ISpellCheckWalkerData
//----------------------------------------------------------------------------------------

class ISpellCheckWalkerData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPELLCHECKWALKERDATA };


	virtual	void							Reset() = 0;
	virtual void							SetDirection(const bool16 direction) = 0;
	virtual bool16							GetDirection() const = 0;
	virtual	ISpellingService::SpellResult	CheckText( const WideString &rText, const ILanguage *pLanguage, bool16 bCheckGrammar = kTrue ) = 0;
	virtual	const WideString &				GetText() const = 0;
	virtual	const WideString &				Get_Unnormalized_ModelText() const = 0;
	virtual ISpellingService::SpellResult	GetSpellResult() const = 0;
	virtual	const WideStringList &			GetAlternatives() const = 0;
	virtual bool16							IsCorrect() const = 0;
	virtual void							SetWordFilter(const FuncIsWordChar wordCharFunc) = 0;
	virtual FuncIsWordChar					GetWordFilter(void) const = 0;

	virtual	void SetSpellResult(const ISpellingService::SpellResult result) = 0;

    /**
		Finds next linguistic error in model. 

        @param	pModel		model to search for error
        @param	searchStart	position to start reporting error (actually starts search at beginning of paragraph to get context)
		@param	searchEnd	position to stop reporting errors for
		@param	pErrorStart	start position of text with error
		@param	pErrorEnd	end position of text with error

		@return	SpellResult	Result of find.
    */
	virtual	ISpellingService::SpellResult	FindNextError( ITextModel *pModel, TextIndex searchStart, TextIndex searchEnd,
		TextIndex *pErrorStart, TextIndex *pErrorEnd ) = 0;
};


/*
Check() returns whether the text at pPosition is correct. If it's not it can be: an incrorrect word
	or a grammar error. If GetGrammarError() returns kNoError the word is incorrect.
	The pPosition parameter gets the position where Check() found the text that you get via GetText().
	If Check() returned kTrue pPosition contains the start of the word and GetText() returns the 
	word of IComposeScanner::CopySurroundingWord().
	If Check() returned kFalse pPosition contains the start of the problematic text (word or more)
	and GetText() the text itself. SpellCheckWalker calculated the next position by adding start to
	GetText().Length().
*/

#endif
