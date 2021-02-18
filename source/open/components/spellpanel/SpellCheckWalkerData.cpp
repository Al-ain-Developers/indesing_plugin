//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellCheckWalkerData.cpp $
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

#include "VCPlugInHeaders.h"

#include "IAttrReport.h"
#include "IComposeScanner.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IDrawingStyle.h"
#include "IHyphenationExceptions.h"
#include "IHyphenationStyle.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILinguisticMgr.h"
#include "ISession.h"
#include "ISpellCheckWalkerData.h"
#include "ISpellingService.h"
#include "ISpellingUtils.h"
#include "ITextAttrUID.h"
#include "ITextModel.h"
#include "ITrackChangesSettings.h"
#include "IUserDictService.h"
#include "IWorkspace.h"

#include "K2SmartPtr.h"
#include "CharacterClass.h"
#include "HelperInterface.h"
#include "PreferenceUtils.h"
#include "TextChar.h"
#include "Trace.h"
#include "UnicodeClass.h"
#include "Utils.h"
#include "WideString.h"
#include "LocaleSetting.h"


#include "INoteData.h"
#include "INotePref.h"
#include "INoteUtils.h"
#include "NoteID.h"

#include "IItemStrand.h"
#include "IOwnedItem.h"
#include "ITextStoryThread.h"
#include "InCopySharedID.h"

#include "HyphenExceptions.h"

//===============================================================
// CLASS SpellCheckWalkerData
//===============================================================

class SpellCheckWalkerData : public ISpellCheckWalkerData
{
public:
						SpellCheckWalkerData(IPMUnknown * boss);
						~SpellCheckWalkerData();

	virtual	void							Reset();
	virtual	ISpellingService::SpellResult		CheckText( const WideString &rText, const ILanguage *pLanguage, bool16 bCheckGrammar );
	virtual void							SetDirection(const bool16 direction) { fSearchBackwards = direction; return; };
	virtual bool16							GetDirection() const { return fSearchBackwards; };
	virtual	const WideString &				GetText() const {return fText;}
	virtual	const WideString &				Get_Unnormalized_ModelText() const {return fUnnormalizedModelText;}
	virtual	ISpellingService::SpellResult		GetSpellResult() const {return fResult;}
	virtual	const WideStringList &			GetAlternatives() const {return fAlternatives;}
	virtual bool16							IsCorrect() const {return fResult == ISpellingService::kCorrect;}
	virtual void							SetWordFilter(const FuncIsWordChar func);
	virtual FuncIsWordChar					GetWordFilter(void) const {return fWordFunc;}

	virtual	void SetSpellResult(const ISpellingService::SpellResult result);

	virtual	ISpellingService::SpellResult	FindNextError( ITextModel *pModel, TextIndex searchStart, TextIndex searchEnd,
		TextIndex *pErrorStart, TextIndex *pErrorEnd );

private:

	WideString 					fText;
	bool16						fSearchBackwards;
	WideString 					fUnnormalizedModelText;
	ISpellingService::SpellResult		fResult;
	WideStringList				fAlternatives;
	FuncIsWordChar 				fWordFunc;
	ILinguisticMgr *			fLinguMgr;
	IHyphenationExceptions *	fHyphenationExceptions;

	ISpellingService::SpellResult		IsCorrect( const WideString &rWord, const ILanguage *pLanguage, WideStringList *pAlternatives, bool16* bEndsWithPeriod );
	ILanguage* 					QueryLanguageAt( IComposeScanner *pScanner, TextIndex nAt );
	ISpellingService*			QuerySpellingService( const ILanguage *pLanguage );
	bool16						GetGrammarAlternatives( const WideString &rWord, WideStringList *pAlternatives, const ILanguage *pLanguage ) const;

DECLARE_HELPER_METHODS()
};




//=====================================================
// CLASS SpellCheckWalkerData
//=====================================================

CREATE_PMINTERFACE(SpellCheckWalkerData, kSpellCheckWalkerDataImpl )
DEFINE_HELPER_METHODS(SpellCheckWalkerData)

//---------------------------------------------------------------
// SpellCheckWalkerData constructor
//---------------------------------------------------------------

SpellCheckWalkerData::SpellCheckWalkerData( IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
		fSearchBackwards(kFalse),
		fResult(ISpellingService::kCorrect),
		fLinguMgr(nil),
		fHyphenationExceptions(nil),
		fWordFunc(PMCharFilters::SpellingIsWordChar)
{
	this->Reset();

	InterfacePtr<IK2ServiceRegistry> pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	InterfacePtr<IK2ServiceProvider> pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	if( !pLinguMgrService )
	{
		return;
	}
	fLinguMgr = (ILinguisticMgr*)pLinguMgrService->QueryInterface( IID_ILINGUISTICMGR );
}

//---------------------------------------------------------------
// SpellCheckWalkerData destructor
//---------------------------------------------------------------

SpellCheckWalkerData::~SpellCheckWalkerData()
{
	if( fLinguMgr )
	{
		fLinguMgr->Release();
	}
	if (fHyphenationExceptions)
	{
		fHyphenationExceptions->Release();
	}
}

//---------------------------------------------------------------
// SpellCheckWalkerData::Reset
//---------------------------------------------------------------

void SpellCheckWalkerData::Reset()
{
	fText.Clear();
	fUnnormalizedModelText.Clear();
	fResult = ISpellingService::kCorrect;
	fAlternatives.clear();
}

// The entries in the dictionary all go through the user interface, which doesn't
// distinguish between right and left double or single quotations.  When comparing
// against those entries, we need to turn typographer's quotes into standard
// (ANSI) quotes
void NormalizeWordForPunctuation(WideString &tempText);
void NormalizeWordForPunctuation(WideString &tempText)
{
	int32 numberOfCharacters = tempText.CharCount();
	for (int32 i = 0 ; i < numberOfCharacters; i++)
	{
		UTF32TextChar thisCharacter = tempText[i];
		if (thisCharacter == kTextChar_RightSingleQuotationMark ||
			thisCharacter == kTextChar_LeftSingleQuotationMark)
		{
			tempText.SetChar(i, kTextChar_Apostrophe);
		}
		else if (thisCharacter == kTextChar_LeftDoubleQuotationMark ||
			thisCharacter == kTextChar_RightDoubleQuotationMark)
		{
			tempText.SetChar(i,  kTextChar_QuotationMark);
		}
	}
}

//---------------------------------------------------------------
// SpellCheckWalkerData::CheckText
//---------------------------------------------------------------

ISpellingService::SpellResult SpellCheckWalkerData::CheckText( const WideString &rText, const ILanguage *pLanguage, bool16 bCheckGrammar )
{
	// Init: clear all except fUnnormalizedModelText

	fText.Clear();
	fResult = ISpellingService::kCorrect;
	fAlternatives.clear();
	fText = rText;

	const int32 nWordLength = fText.Length();
	if( nWordLength == 0 || !pLanguage )
	{
		return fResult;
	}

	InterfacePtr<ILanguage>pWalkLanguage( this, IID_ILANGUAGE );
	if( pWalkLanguage )
	{
		 pWalkLanguage->CopyFrom( pLanguage );
	}

	bool16 bEndsWithPeriod = kFalse;

	// (1) Correct Word ?
	fResult = this->IsCorrect( fText, pLanguage, &fAlternatives, &bEndsWithPeriod );
	if( fResult != ISpellingService::kCorrect )
	{
		return fResult;
	}

	// (2) Correct Grammar?
	// BP 6/11/97: check for grammar (repeated and uncapitalized sentences on Proximity).
	// see SpellAlternativesObserver, GetAlternatives()

	if( bCheckGrammar )
	{
		InterfacePtr<ISpellingService>pDict( this->QuerySpellingService( pLanguage ) );
		if( pDict )
		{
			// includes carriage return, except for the last paragraph, if no return was typed in.
			if (fText.Length() > 0)
			{
				if( fText[fText.Length() - 1] == kTextChar_CR )
				{
					fText.Truncate(1);
				}

				TextIndex nGrammarStart = 0;
				TextIndex nGrammarLength = fText.Length();

				fResult = pDict->FindError( fText, 0, &nGrammarStart, &nGrammarLength, nil  );
				if( fResult > ISpellingService::kGrammarError )
				{
					this->GetGrammarAlternatives( fText, &fAlternatives, pLanguage );
					return fResult;
				}
			}
		}
	}

	return fResult;
}

//---------------------------------------------------------------
// SpellCheckWalkerData::IsCorrect
//---------------------------------------------------------------
// BP 4/4/97:	return kTrue if there is no ISpellingService because of:
//	#203290 	Spell checking text set to No Language flags every word in the selection.

ISpellingService::SpellResult SpellCheckWalkerData::IsCorrect(const WideString &rWord, const ILanguage *pLanguage, WideStringList *pAlternatives, bool16* bEndsWithPeriod)
{
	return Utils<ISpellingUtils>()->IsWordCorrect(rWord, pLanguage, pAlternatives, fLinguMgr, fHyphenationExceptions, bEndsWithPeriod);
}

//---------------------------------------------------------------
// SpellCheckWalkerData::QueryLanguageAt
//---------------------------------------------------------------

ILanguage *SpellCheckWalkerData::QueryLanguageAt( IComposeScanner *pScanner, TextIndex nAt )
{
	ILanguage *pLanguage = nil;
	IDrawingStyle *pStyle = pScanner->GetCompleteStyleAt( nAt );
	if( pStyle )
	{
		InterfacePtr<IHyphenationStyle>pHyphStyle( pStyle, IID_IHYPHENATIONSTYLE );
		pLanguage = pHyphStyle->QueryLanguage();
	}

	return pLanguage;
}


//---------------------------------------------------------------
// SpellCheckWalkerData::QuerySpellingService()
//---------------------------------------------------------------

ISpellingService *SpellCheckWalkerData::QuerySpellingService( const ILanguage *pLanguage )
{
	if( !fLinguMgr )
	{
		return nil;
	}

	return fLinguMgr->QuerySpellingService( pLanguage );
}

//---------------------------------------------------------------
// SpellCheckWalkerData::GetGrammarAlternatives
//---------------------------------------------------------------

bool16	 SpellCheckWalkerData::GetGrammarAlternatives( const WideString &rWord, WideStringList *pAlternatives, const ILanguage *pLanguage ) const
{
	pAlternatives->clear();

	if( fResult == ISpellingService::kCorrect )
	{
		return kFalse;
	}

	WideString aText( rWord );
	if( fResult == ISpellingService::kUncapitalizedStartOfSentence || fResult == ISpellingService::kUncapitalizedWord )
	{
		const UTF32TextChar cFirst = UnicodeClass::ToUpper( aText[0] );
		aText.SetChar(0, cFirst.GetValue());
	}
	else if( fResult == ISpellingService::kRepeatedWord )
	{
		// The alternative to "the the" is "the".
		const int32 nMax = aText.Length();
		for( int32 i = 0; i < nMax; ++i )
		{
			if (UnicodeClass::IsWhiteSpace(aText[i]))
			{
				aText.Remove( i, nMax - i );
				i = nMax;
			}
		}
	}
	if( !aText.Length() )
	{
		return kFalse;
	}

	pAlternatives->push_back( aText );

	return kTrue;
}

void SpellCheckWalkerData::SetSpellResult(const ISpellingService::SpellResult result)
{
	if (result != fResult)
	{
		fResult = result;
	}
}

void SpellCheckWalkerData::SetWordFilter(const FuncIsWordChar func)
{
	if (func != fWordFunc)
	{
		fWordFunc = func;
	}
}


ISpellingService::SpellResult SpellCheckWalkerData::FindNextError( ITextModel *pModel, TextIndex searchStart, TextIndex searchEnd,
		TextIndex *pErrorStart, TextIndex *pErrorEnd )
{
	InterfacePtr<IComposeScanner>pScanner( pModel, IID_ICOMPOSESCANNER );
	ASSERT_MSG( pScanner != 0, "SpellCheckWalkerClient - missing IID_ICOMPOSESCANNER" );

	// Init
	this->Reset();

	// check if the current index is note, then skip this index
	InterfacePtr<INoteData> noteData;
	if (fSearchBackwards)
	{
		noteData.reset(Utils<INoteUtils>() ? Utils<INoteUtils>()->QueryNoteData(pModel, searchEnd) : 0);
	}
	else
	{
		noteData.reset(Utils<INoteUtils>() ? Utils<INoteUtils>()->QueryNoteData(pModel, searchStart) : 0);
	}
	if (noteData)
	{
		if (fSearchBackwards)
		{
			*pErrorStart = searchEnd - 1;
		}
		else
		{
			*pErrorStart = searchStart + 1;
		}
		*pErrorEnd = *pErrorStart;
		return ISpellingService::kNoteAnchor;
	}

	// Don't cross language changes!
	int32 langAttrLength;
	int32 endLanguagePostition = 0;
	InterfacePtr<const IAttrReport> textAttrLangReport;
	if (fSearchBackwards)
	{
		textAttrLangReport.reset(pScanner->QueryAttributeAt(searchStart, searchEnd, kTextAttrLanguageBoss, &langAttrLength, kTrue));// Query attribute in reverse direction.
		endLanguagePostition = searchEnd - langAttrLength;
	}
	else
	{
		textAttrLangReport.reset(pScanner->QueryAttributeAt(searchStart, searchEnd, kTextAttrLanguageBoss, &langAttrLength));
		endLanguagePostition = searchStart + langAttrLength;
	}
	InterfacePtr<const ITextAttrUID> textAttrLangUID(textAttrLangReport, UseDefaultIID());
	UID langUID = (textAttrLangUID) ? textAttrLangUID->GetUIDData() : kInvalidUID;

	InterfacePtr<const ILanguage>pLanguage( ::GetDataBase(pModel), langUID, UseDefaultIID() );
	InterfacePtr<ILanguage>pWalkLanguage( this, IID_ILANGUAGE );
	if( pWalkLanguage )
	{
		 pWalkLanguage->CopyFrom( pLanguage );
	}

	WideString aParagraph;
	int32 nParaErrorStart, nErrorHighlightLength;
	TextIndex nParaStart;
	// includes carriage return, except for the last paragraph, if no return was typed in.
	// Don't spell check across a langauge boundry
	if (fSearchBackwards) 
	{
		nParaStart = nParaErrorStart = pScanner->FindSurroundingParagraph(searchEnd, &nErrorHighlightLength);
		if ( endLanguagePostition > nParaStart)
		{
			//searchEnd (and therefore endLanguagePosition) might be in the middle of a word. Need to go to start of word.
			UID nLanguageUID = kInvalidUID;
			WideString aWord;
			TextIndex wordStart = pScanner->CopySurroundingWord(endLanguagePostition, &aWord, &nLanguageUID, PMCharFilters::SpellingIsWordChar);

			if ((wordStart != kInvalidTextIndex) && (wordStart < endLanguagePostition)
				&& ((wordStart + aWord.Length()) > endLanguagePostition))
			{
				endLanguagePostition = wordStart;// Changes due to language change will be taken care of after finding the error. ***
			}				
		}
	}
	else
	{
		nParaStart = nParaErrorStart = pScanner->FindSurroundingParagraph(searchStart, &nErrorHighlightLength);		
		// trunc paragraph at language change. We send in the start of the paragrpah even if its a different
		// language so we know the context. We need to know if previous is end of sentence or not.
		// interesting side effect of this is if two of the same word are next to each other but in different
		// languages it shows repeated word even if the first is misspelled. Might wan't to address that.
		if ((nErrorHighlightLength + nParaStart) > endLanguagePostition)
		{
			nErrorHighlightLength = endLanguagePostition - nParaStart;

			//searchEnd (and therefore endLanguagePosition) might be in the middle of a word. Need to go to end of word.
			UID nLanguageUID = kInvalidUID;
			WideString aWord;
			TextIndex wordStart = pScanner->CopySurroundingWord(endLanguagePostition, &aWord, &nLanguageUID, PMCharFilters::SpellingIsWordChar);

			if ((wordStart != kInvalidTextIndex) && (wordStart < endLanguagePostition)
				&& ((wordStart + aWord.Length()) > endLanguagePostition))
				nErrorHighlightLength = wordStart + aWord.Length() - nParaStart;
		}
	}

	pScanner->CopyText(nParaErrorStart, nErrorHighlightLength, &aParagraph);
	
	//move to previous paragraph unless there is an error.
	if (fSearchBackwards)
	{
		*pErrorStart = nParaStart -1; 
		if (*pErrorStart < searchStart)
		{
			*pErrorStart = searchStart;
		}
		ASSERT(*pErrorStart < searchEnd);
	}
	else
	{
		*pErrorEnd = nParaStart + nErrorHighlightLength; 
		ASSERT(*pErrorEnd > searchStart);
	}
	
	

	//strip the paragraph char
	if( aParagraph[aParagraph.Length() - 1] == kTextChar_CR )
	{
		aParagraph.Truncate(1);
		nErrorHighlightLength--;
	}

	if( aParagraph.empty())
		return ISpellingService::kCorrect;
	InterfacePtr<ISpellingService>pDict( this->QuerySpellingService( pLanguage ) );
	if( !pDict)
		return ISpellingService::kCorrect;

	InterfacePtr<ILanguage> pAllLanguage(fLinguMgr->QueryLanguage("Neutral"));
	IUserDict *documentAllLangDict = Utils<ISpellingUtils>()->AddDocumentDictionariesToDictService(pModel, pAllLanguage);
	IUserDict *documentCurLangDict = Utils<ISpellingUtils>()->AddDocumentDictionariesToDictService(pModel, pLanguage);

	if (fSearchBackwards)
	{
		fResult = pDict->FindError(aParagraph, searchEnd - nParaStart, &nParaErrorStart, &nErrorHighlightLength,&fAlternatives, fSearchBackwards);
	}
	else
	{
		fResult = pDict->FindError(aParagraph, searchStart - nParaStart, &nParaErrorStart, &nErrorHighlightLength,
			&fAlternatives, fSearchBackwards);
	}
	
	//need to remove document dictionaries
	if (documentAllLangDict)
	{
		InterfacePtr<IUserDictService> pAllDictService(fLinguMgr->QueryUserDictService( pAllLanguage ));
		pAllDictService->RemoveUserDictFromSearchPath(documentAllLangDict);
	}
	if (documentCurLangDict)
	{
		InterfacePtr<IUserDictService> pDictService(fLinguMgr->QueryUserDictService( pLanguage ));
		pDictService->RemoveUserDictFromSearchPath(documentCurLangDict);
	}

	if( fResult == ISpellingService::kCorrect )
		return fResult;

	// ***Checking Language boundary in case of searchbackwards.
	if (fSearchBackwards && nParaStart + nParaErrorStart < endLanguagePostition)
	{
		*pErrorStart = endLanguagePostition-1;
		fResult = ISpellingService::kCorrect;
		return fResult;
	}


	// If error is outside range we are checking then return kCorrect. Same condition for both forward and backward.
	if( (nParaStart + nParaErrorStart + nErrorHighlightLength < searchStart) || (nParaStart + nParaErrorStart > searchEnd) )
	{
		fResult = ISpellingService::kCorrect;
		return fResult;
	}

	//setup error position and return error
	K2::scoped_ptr<WideString>pSubString( aParagraph.Substring( nParaErrorStart, nErrorHighlightLength ) );

	*pErrorStart = nParaStart + nParaErrorStart;
	*pErrorEnd = *pErrorStart + nErrorHighlightLength;
	// Set pErrorEnd passed zero space chars.
	int32 indexToCheck = nParaErrorStart + (*pErrorEnd - *pErrorStart);
	while (indexToCheck < aParagraph.CharCount() && 
		UnicodeClass::IsIgnoredCharacter(aParagraph.GetChar(indexToCheck)))
	{
		(*pErrorEnd)++;
		++indexToCheck;
	}

	if (pSubString)	/* HH 3/7/00 this could be nil */
	{
		fText = *pSubString;
		fUnnormalizedModelText = *pSubString;
	}
	else
	{
		fAlternatives.clear();
		fText.clear();
		fUnnormalizedModelText.Clear();
	}

	return fResult;
}
