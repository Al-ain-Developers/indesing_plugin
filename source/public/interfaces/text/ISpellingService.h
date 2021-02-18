//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ISpellingService.h $
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
#ifndef __ISpellingService__
#define __ISpellingService__

#include "IPMUnknown.h"
#include "K2Vector.h"

//----------------------------------------------------------------------------------------
// Interface ISpellingService
//----------------------------------------------------------------------------------------

class WideString;
typedef K2Vector<WideString> WideStringList;

/** 
	@ingroup text_dict
*/
class ISpellingService : public IPMUnknown
{
public:
	/** Spelling results.
		Items after kSpellError are spelling errors. Items after kGrammarError are grammar errors.
	*/
	enum SpellResult {
		/** Word is spelled correctly or no grammar error. */
		kCorrect = 0, 
		/** Denotes beginning of spelling errors. Not valid return value. */
		kSpellError,
		/** Word is spelled incorrectly. */
		kIncorrectWord,
		/** Word is not correctly capitalized. */
		kUncapitalizedWord, 
		/** Denotes beginning of grammar errors. Not valid return value. */
		kGrammarError,
		/** Word is repeated. */
		kRepeatedWord,
		/** Sentence is not correctly capitalized. */
		kUncapitalizedStartOfSentence,

		/** used to indicate that current index is a note. not returned by any routines in ISpellingService. Spelling walker is using */
		kNoteAnchor,
		/** used to indicate that current index is deleted text. not currently returned by any routines in ISpellingService. Spelling walker is using */
		kDeletedText
	} ;

	/**
		Checks whether the word is spelled correctly.

		@param rWord			IN to be checked word for spelling.
		@param bEndsWithPeriod	OUT if the word ends with period (ex. Mr. would return kFalse).
									If kTrue the calling code will attempt to remove the trailing period.

		@return					kTrue if the word spelling is correct.
	*/
	virtual	SpellResult			IsCorrect( const WideString &rWord, bool16 *bEndsWithPeriod ) = 0;

	/**
		Look for alternate spellings for word.

		@param rWord			IN to be checked word for alternative word.
		@param pAlternatives	OUT the list of alternative words for this word.

		@return					kTrue if there is at least one alternative word found.
	*/
	virtual	bool16				FindAlternatives( const WideString &rWord, WideStringList *pAlternatives ) = 0;

	/**
		Spell checking the word.
	 
		@param rWord			IN to be checked word for spelling.
		@param pAlternatives	OUT the list of alternative words for this word.
		@param bEndsWithPeriod	OUT if the word ends with period.

		@return					kCorrect if the word spelling is correct; otherwise,
									it will find all the alternative words for this word.
	*/
	virtual	SpellResult			Spell( const WideString &rWord,  WideStringList *pAlternatives, bool16 *bEndsWithPeriod ) = 0;

	/**
		IsCorrectGrammar() assumes that rParagraph is a paragraph that has
		to start with a capital.
		Notice that  IsCorrectGrammar() does not check the word at the
		position, use IsCorrect() and Spell() instead.
	 
		@param rParagraph	IN the paragraph to check its grammar.
		@param pWordStart	OUT the position where the word start.
		@param pWordLength	OUT the length of the word.
		@param StartAt		IN the starting position for the paragraph.

		@return				kCorrect if the paragraph grammar is correct,
							    otherwise returns one of the grammar errors.
	*/
	virtual	SpellResult			IsCorrectGrammar( const WideString &rParagraph, int32 *pWordStart, int32 *pWordLength, int32 startAt = 0 ) = 0;

	/**
		Set up the spelling service.

		@param rCoreFileName IN the core file name.
		@param rLexFileName IN the lex file name.
		@param rPhonFileName IN the phon file name.
		@param rBaseLangLexFileName IN the base language lex file name.
		@return Returns kTrue if success.
	*/
	virtual	bool16 				Set( const PMString &rCoreFileName, const PMString &rLexFileName, const PMString &rPhonFileName, const PMString &rBaseLangLexFileName ) = 0;

	/**
		Spelling service supports case sensitive.

		@return					kTrue if spelling service supports case sensitive
	*/
	virtual	bool16				SupportsCaseSensitive() = 0;


	/**
		FindError() finds first error in rParagraph starting at startAt.
		assumes that rParagraph is a paragraph that has to start with a capital.
	 
		@param rParagraph		IN the paragraph to check.
		@param startAt			IN the starting position for where to start 
									reporting errors in the paragraph.
		@param pErrorStart		OUT the position where the error starts.
		@param pErrorLength		OUT the length of the error.
		@param pAlternatives	OUT the alternatives for this error. Can be nil.
		@param searchBackwards	IN the direction of spell check. Spell check works in reverse direction if this bool is true.

		@return					kCorrect if the paragraph is correct,
								    otherwise returns one of the spelling error.
	*/
	virtual SpellResult			FindError( const WideString &rParagraph, int32 startAt, int32 *pErrorStart, int32 *pErrorLength, WideStringList* pAlternatives, bool searchBackwards=false) = 0;

	/** Used by FindAllErrors to return error information  */
	class SpellingError
	{
	public:
		/** 0 based index indicating start of error */
		int32 errorStart;
		/** Length of error. For repeated word this included the two words and space between */
		int32 errorLength;
		/** Kind of spelling error. */
		SpellResult spellingErrorType;
	};
	/**
		FindAllErrors() assumes that rParagraph is a paragraph that has
		to start with a capital.
	 
		@param rParagraph		IN the paragraph to check.
		@param startAt			IN the starting position for where to start 
									reporting errors in the paragraph.
		@param pSpellingErrors	OUT errors. vector is empty if no errors.
	*/
	virtual void			FindAllErrors( const WideString &rParagraph, int32 startAt, std::vector<SpellingError> *pSpellingErrors ) = 0;

};

#endif
