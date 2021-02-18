//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/ISpellingUtils.h $
//  
//  Owner: mvogel
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
#ifndef _H_ISpellingUtils
#define _H_ISpellingUtils

#include "LinguisticID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "ISpellingService.h"

class UndoInfo;
class ILinguisticMgr;
class IHyphenationExceptions;
class ILanguage;
class IComposeScanner;
class IControlView;
class IUserDict;

class ISpellingUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPELLINGUTILS };

	virtual ISpellingService::SpellResult IsTextIndexCorrect(TextIndex clickedIndex,
																IComposeScanner* scanner,
																WideStringList* wList,
																int32 &errorStart,
																int32 &errorLength) = 0;

	virtual ISpellingService::SpellResult IsWordCorrect(	const WideString& 			word,
														const ILanguage* 		lang,
														WideStringList* 		alternatives,
														ILinguisticMgr*			lingMgr,
														IHyphenationExceptions* 	he,
														bool16* 					endPeriod) = 0;

	/**
		Calls ISpelling::IsCorrectGrammer then checks and doesn't give a uncap start of sentence
		error if footnote or note.

		@param  sentence	text to check
		@param  wordStartIndex	index in text to start reporting errors
		@param  pLanguage		language of text to check
		@param  lingMgr			linguitic manager
		@param  textModel		text model of text to check
		@param  errorStart		OUT start of error
		@param  errorLength		OUT length of error

		@return  ISpellingService::SpellResult spell result
	*/
	virtual ISpellingService::SpellResult IsGrammarCorrect(	WideString&			sentence,
															int32			wordStartIndex,
															const ILanguage*	pLanguage,
															ILinguisticMgr*	lingMgr,
															ITextModel*		textModel,
															int32			&errorStart,
															int32			&errorLength) = 0;

	virtual void StripLeadingAndTrailingPunctuation(	const WideString &inWord,
													WideString &outWord,
													int32& numLeadingStripped,
													int32& numTrailingStripped,
													bool16 stripLastPeriod = kFalse) = 0;

	virtual bool16 StripIgnorablesForSpelling(WideString& word) = 0;

	/**
		Adds user dictionaries from document to dictionary service. Caller is responsible for
		deleting returned IUserDict. This is usually done using IUserDictService::RemoveUserDictFromSearchPath

		@param  pModel		text model with dictionaries to add
		@param  pLanguage	language to add dictionaries to

		@return  IUserDict	user dictionary for language in model that was added 
	*/
	virtual IUserDict* AddDocumentDictionariesToDictService(ITextModel *pModel, const ILanguage *pLanguage) = 0;


	#ifdef DEBUG
	virtual bool16 VerifyStoryIsSpellChecked(ITextModel* model) = 0;

	virtual bool16 VerifyStoryIsSpellCheckedUpToTextIndex(ITextModel* textModel, TextIndex damageStart) = 0;

	virtual bool16 ValidateSpellingStrandLengths(ITextModel * textModel) = 0;
	#endif
};

#endif /* _H_SpellingUtils */

