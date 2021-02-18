//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLSpelling.cpp $
//  
//  Owner: Adobe Developer Technologies
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

//Interface includes:
#include "IPMStream.h"		
#include "ISpellingService.h"
#include "IUserDictService.h"
#include "IUserDictIterator.h"

// General includes:
#include "CPMUnknown.h"
#include "LinguisticID.h"
#include "TextChar.h"
#include "StringUtils.h"
#include "UnicodeClass.h"
#include "UserDictWordList.h"

// Project includes:
#include "CHLID.h"
#include "CHLUtils.h"

/** This sample spelling service was extracted from the Proximity plug-in's implementation.
	Vendors should replace this implementation with their own.

	This simple implementation checks words against a text file dictionary containing one
	word per line. The word being checked is looked up via a sequential search of the text 
	file.

	User dictionaries and the provision of a list of alternative words
	is not implemented but placeholders are indicated in the code where 
	these facilities would typically be added.
	
	kCHLSpellingImpl implements the spelling service for a single language. The
	Set method is used to pass paths to supporting data files (dictionaries etc.).
	IsCorrect(), FindAlternatives(), Spell(), IsCorrectGrammar()
	methods are called to spell check words when your spelling service has been
	selected as the active one to check the language.
	
	 / Mitsutoshi Kikuta
	@ingroup chlinguistic
*/
class CHLSpelling : public CPMUnknown<ISpellingService>
{
	public:
		/**	Constructor.
		 * 	@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		CHLSpelling(IPMUnknown* boss);
		
		/** Destructor.
		*/
		~CHLSpelling();

		/** Setting the spelling service.
		 * 
		 * 	@param rCoreFileName IN the core file name.
		 *  @param rLexFileName IN the lex file name, not used in this sample.
		 *  @param rPhonFileName IN the phon file name, not used in this sample.
		 *  @param rBaseLangLexFileName IN the base language lex file name, not used in this sample.
		 *  @return Returns kTrue if success.
		*/
		virtual	bool16 			Set(const PMString& rCoreFileName, const PMString& rLexFileName, const PMString& rPhonFileName, const PMString& rBaseLangLexFileName);
		
		/**	Confirms whether the word is a correct spelling.
		 * 
		 * 	@param rWord IN to be checked word for spelling.
		 * 	@param bEndsWithPeriod OUT if the word ends with period.
		 * 	@return Returns kTrue if the word spelling is correct.
		*/
		virtual	SpellResult		IsCorrect(const WideString& rWord, bool16* bEndsWithPeriod);
		
		/** Look for an alternative word.
		 * 
		 * 	@param rWord IN to be checked word for alternative word.
		 *  @param pAlternatives OUT the list of alternative words for this word.
		 *  @return Returns kTrue if there is at least one alternative word found.
		*/
		virtual	bool16	FindAlternatives(const WideString& rWord, WideStringList* pAlternatives);
		
		/**	Spell checking the word.
		 * 
		 *  @param rWord IN to be checked word for spelling.
		 *  @param pAlternatives OUT the list of alternative words for this word.
		 *  @param bEndsWithPeriod OUT if the word ends with period. 
		 *  @return Returns kCorrect if the word spelling is correct; otherwise, 
		 * 			it will find all the alternative words for this word.
		*/
		virtual	SpellResult		Spell(const WideString& rWord,  WideStringList* pAlternatives, bool16* bEndsWithPeriod);
		
		/**	IsCorrectGrammar() assumes that rParagraph is a paragraph that has
		 * 	to start with a capital.
		 * 	Notice that  IsCorrectGrammar() does not check the word at the 
		 * 	position, use IsCorrect() and Spell() instead.
		 * 
		 *  @param rParagraph IN the paragraph to check its grammar.
		 *  @param pWordStart OUT the position where the word start.
		 * 	@param pWordLength OUT the length of the word.
		 * 	@param StartAt IN the starting position for the paragraph .
		 * 	@return Returns kCorrect if the paragraph grammar is correct, 
		 * 			otherwise returns kGrammarError.
		*/
		virtual	SpellResult		IsCorrectGrammar(const WideString& rParagraph, int32* pWordStart, int32* pWordLength, int32 StartAt);
				
		/**
			Spelling service supports case sensitive.

			@return					kTrue if spelling service supports case sensitive
		*/
		virtual	bool16			SupportsCaseSensitive() {return kTrue; }


		/**
			FindError() assumes that rParagraph is a paragraph that has
			to start with a capital.
		 
			@param rParagraph	IN the paragraph to check.
			@param pErrorStart	OUT the position where the error starts.
			@param pErrorLength	OUT the length of the error.
			@param StartAt		IN the starting position for the paragraph.

			@return				kCorrect if the paragraph is correct,
									otherwise returns one of the spelling error.
		*/
		virtual ISpellingService::SpellResult	FindError( const WideString &rParagraph, int32 startAt, int32 *pErrorStart, int32 *pErrorLength, WideStringList* pAlternatives , bool dir=kFalse );

		/**
			FindAllErrors() assumes that rParagraph is a paragraph that has
			to start with a capital.
		 
			@param rParagraph		IN the paragraph to check.
			@param startAt			IN the starting position for where to start 
										reporting errors in the paragraph.
			@param pSpellingErrors	OUT errors. vector is empty if no errors.
		*/
		virtual void			FindAllErrors( const WideString &rParagraph, int32 startAt, std::vector<SpellingError> *pSpellingErrors );

	private:
		/** We only spell check letters. Vendors may want to change this 
		 * 	to allow other characters to pass through.
		 * 	Also as we filter we convert to lower case.
		 *  
		 * 	@param rWord IN the word.
		 *  @param word OUT the output word after through the filter .
		*/
		void Filter(const WideString& rWord, WideString& word);
		
		/**	This routine searches file fCoreFileName for the given word.
		 *  It assumes the file is a simple text file with one word per
		 * 	line and just searches sequentially for a match.
		 * 
		 *  @param rWord IN to be checked word to see if it is in the core file stream.
		 *  @param endsWithPeriod OUT returns whether or not the word has an end period.
		 *  @return Returns the spelling or grammar error.
		*/
		ISpellingService::SpellResult IsWord(const WideString& rWord, bool16& endsWithPeriod);

		virtual ISpellingService::SpellResult	FindIncorrectSpaceError( const WideString &rParagraph, int32 startAt, int32 *pErrorStart, int32 *pErrorLength, WideStringList* pAlternatives  );

		PMString fCoreFileName;
		IPMStream* fCoreStream;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(CHLSpelling, kCHLSpellingServiceImpl)

/* CHLSpelling constructor 
*/
CHLSpelling::CHLSpelling(IPMUnknown* boss) : CPMUnknown<ISpellingService>(boss) , fCoreStream(nil)
{
}


/* CHLSpelling destructor 
*/
CHLSpelling::~CHLSpelling()
{
	if (fCoreStream != nil)
	{
		fCoreStream->Close();
		fCoreStream->Release();
	}
}


/* CHLSpelling::Set()
*/
bool16 CHLSpelling::Set(const PMString& rCoreFileName, 
						const PMString& rLexFileName, 
						const PMString& rPhonFileName, 
						const PMString& rBaseLangLexFileName)
{
	fCoreFileName = rCoreFileName;
	return kTrue;
}


/* CHLSpelling::IsCorrect
*/
ISpellingService::SpellResult CHLSpelling::IsCorrect(const WideString& inWord, bool16* bEndsWithPeriod)
{
	long rWordLength = inWord.Length();
	// Empty pub, & Spell panel open could cause crash.
	if (rWordLength == 0)
		return kCorrect;
	else if (rWordLength > 255)	
		return kIncorrectWord;
	
	// Filter unwanted characters from the word we are passed.
	WideString rWord;
	this->Filter(inWord, rWord);

	if (rWord.Length() <= 0)
	{
		return kCorrect;
	}

	// OK we're ready to spell check the word.
	// First we need some flags.
	ISpellingService::SpellResult nResult = kCorrect;
	bool16 endsWithPeriod = kFalse;

	// Consult the core dictionary.
	nResult = this->IsWord(rWord, endsWithPeriod);

	// Consult the user dictionary here for additions or overrides.
	InterfacePtr<IUserDictService> userDictService(this, IID_IUSERDICTSERVICE);
	if (userDictService != nil)
	{
		// Placeholder for vendor code....

		// Normally a spelling 'system' would integrate the user dictionary with the speller
		// For our sample we will simply walk the word list of each user dictionary
		if (nResult != ISpellingService::kCorrect)
		{
			K2Vector<IUserDict*> userDictList;
			bool16 bOpenFiles = kTrue;

			int32 numUserDicts = userDictService->QueryAllUserDictsInSearchPath(userDictList, bOpenFiles);

			for (int32 i = 0; i < numUserDicts; i++)
			{
				InterfacePtr<IUserDict> userDict(userDictList[i], UseDefaultIID());
				if (userDict)
				{
					InterfacePtr<IUserDictIterator> userDictIterator(userDictService, IID_IUSERDICTITERATOR);

					/* convenience method in UserDictWordList */
					UserDictWordList udWordList;
					udWordList.InsertUserDict(userDictService, userDict, userDictIterator, IUserDictService::kIsAWord);

					if (udWordList.Location(rWord) > -1)
					{
						/* we found the word in our user dictionary */
						return kCorrect;
					}
				}
			}
		}
	}

	// Return results.
	if (bEndsWithPeriod != nil)
		*bEndsWithPeriod = endsWithPeriod;

	return nResult;
}


/* CHLSpelling::FindAlternatives
*/
bool16	CHLSpelling::FindAlternatives(const WideString& inWord, WideStringList* pAlternatives)
{
	// Empty pub, & Spell panel open could cause crash.
	if (inWord.Length() == 0)
		return kTrue;

	// Clear the list of alternatives.
	pAlternatives->clear();

	// Filter unwanted characters from the word we are passed.
	WideString rWord;
	this->Filter(inWord, rWord);

	// Build list of alternatives here...
	{
		// Placeholder for vendor code...
	}

	if (pAlternatives->size() > 0)
		return kTrue;
	else
		return kFalse;
}


/* CHLSpelling::Spell
*/
ISpellingService::SpellResult CHLSpelling::Spell(const WideString& rWord,  WideStringList* pAlternatives, bool16* bEndsWithPeriod)
{
	// Empty pub, & Spell panel open could cause crash.
	if (rWord.Length() == 0)
		return kCorrect;

	const ISpellingService::SpellResult nResult = this->IsCorrect(rWord, bEndsWithPeriod);
	if (nResult != kCorrect && pAlternatives != nil)
	{
		this->FindAlternatives(rWord, pAlternatives);
	}

	return nResult;
}


/* CHLSpelling::IsCorrectGrammar
*/
ISpellingService::SpellResult CHLSpelling::IsCorrectGrammar(const WideString& rParagraph, int32* pWordStart, int32* pWordLength, int32 StartAt)
{
	// Empty pub, & Spell panel open could cause crash.
	if (rParagraph.Length() == 0)
		return ISpellingService::kCorrect;

	ISpellingService::SpellResult nResult = ISpellingService::kCorrect;

	// Grammar Check
	{
		// Placeholder for vendor code...
	}

	return nResult;
}


/* CHLSpelling::Filter
// We only spell check letters. Vendors may want to change this
// to allow other characters to pass through. Also as we filter
// we convert to lower case.
*/
void CHLSpelling::Filter(const WideString& inWord, WideString& rWord)
{
	rWord = WideString("");

	for (int32 i = 0; i < inWord.Length(); i++)
	{
		const UTF32TextChar& workChar = inWord [i];

		// We only check letters.
		if (UnicodeClass::IsLetter(workChar) == kFalse)
			continue;

		// In lower case.
		if (UnicodeClass::IsUpper(workChar) == kTrue)
			rWord.Append(UnicodeClass::ToLower(workChar));
		else
			rWord.Append(workChar);
	}

	// You should be aware that it is possible to filter
	// special characters inserted by the text model
	// (discretionary hyphens and the like). To do this
	// you can use the method below:
	//  Utils<ITextUtils>()->ConvertTextModelText(inWord, &rWord, kFalse, kTrue, kTrue);
	// See PMTextUtils.h for more details.

}


/* CHLSpelling::IsWord
// This routine searches file fCoreFileName for the given word.
// It assumes the file is a simple text file with one word per
// line and just searches sequentially for a match.
*/
ISpellingService::SpellResult CHLSpelling::IsWord(const WideString& rWord, bool16& endsWithPeriod)
{
	ISpellingService::SpellResult nResult = kCorrect;

	do
	{
		// Open the dictionary text file if necessary.
		if (fCoreStream == nil)
		{
			fCoreStream = CHLUtils::CreateFileStreamRead(fCoreFileName);
		}

		if (fCoreStream == nil)
		{
			ASSERT_FAIL("CHLSpelling::IsWord() fCoreStream invalid");
			break;
		}


		// File control characters
		const uchar kuchar_Separator = ',';

		// Loop control variables.
		uchar oneChar(0);
		WideString dictionaryWord;
		bool16 found = kFalse;
		bool16 dictionaryWordEndsWithPeriod = kFalse;

		// Trace
		{
			TRACEFLOW(kCHLPluginName, "CHLSpelling::IsWord(): Looking for word...\n");
			for (int32 i = 0; i < rWord.Length(); i++)
			{
				//PMString str(rWord);
				WideString* wsChar = rWord.Substring(i);
				std::string str;
				StringUtils::ConvertWideStringToUTF8(*wsChar, str);
				TRACEFLOW(kCHLPluginName, "%s, %x, %d\n", str.c_str(), rWord[i].GetValue(), i);
				delete wsChar;
			}
		}

		// Scan the characters from the start of the file.
		fCoreStream->Seek(0, kSeekFromStart);
		fCoreStream->XferByte(oneChar);
		while (fCoreStream->GetStreamState()==kStreamStateGood)
		{
			switch (oneChar)
			{
				// the \n char is platform specific.
#if defined(WINDOWS)
				case kTextChar_CR:
#elif defined(MACINTOSH)
				case kTextChar_LF:
#endif				
				// end of line
				{
					{
						TRACEFLOW(kCHLPluginName, "dictionaryWord...\n");
						for (int32 i = 0; i < dictionaryWord.Length(); i++)
						{
							WideString* wsChar = dictionaryWord.Substring(i);
							std::string str;
							StringUtils::ConvertWideStringToUTF8(*wsChar, str);
							TRACEFLOW(kCHLPluginName, "%s, %x, %d\n", str.c_str(), dictionaryWord[i].GetValue(), i);
							delete wsChar;
						}
					}

					if (dictionaryWord [dictionaryWord.Length() - 1] == kTextChar_Period)
					{
						TRACEFLOW(kCHLPluginName, "dictionaryWordEndsWithPeriod...\n");
						dictionaryWordEndsWithPeriod = kTrue;
						dictionaryWord.Truncate(1);
					}

					if (rWord == dictionaryWord)
						found = kTrue;
					else
					{
						dictionaryWord = WideString("");
						dictionaryWordEndsWithPeriod = kFalse;
					}
					break;
				}
#if defined(WINDOWS)
				case kTextChar_LF:
				// ignore line feeds
				{
					break;
				}
#endif
				default: //data
				{
					dictionaryWord.Append(oneChar);
					break;
				}
			} // end switch
			
			// Break out if we find a match.
			if (found == kTrue)
			{
				break;
			}
			
			// Read the next character
			fCoreStream->XferByte(oneChar);
			
		} // end while streamstategood

		// If we didn't find the word...
		if (found == kFalse)
		{
			// And we reached the end of the file...
			if (fCoreStream->GetStreamState()==kStreamStateEOF)
				// Then the word is incorrect.
				nResult = kIncorrectWord;
		}
		else
		{
			endsWithPeriod = dictionaryWordEndsWithPeriod;
		}

	} while (false); // Only do once.

	return nResult;

}

ISpellingService::SpellResult	CHLSpelling::FindIncorrectSpaceError( const WideString &rParagraph, int32 startAt, int32 *pErrorStart, int32 *pErrorLength, WideStringList* pAlternatives  )
{
	WideString errorWord(L"tog ether");
	int32 errorIndex = rParagraph.IndexOf(errorWord, startAt);

	if (errorIndex >= 0)
	{
		//pAlternatives is an optional parameter. Check for nil
		if (pAlternatives)
		{
			WideString altWord(L"together");
			pAlternatives->push_back( altWord );
		}
		*pErrorStart = errorIndex;
		*pErrorLength = errorWord.CharCount();
		return (ISpellingService::SpellResult)kIncorrectSpaceError;
	}

	return kCorrect;
}

ISpellingService::SpellResult	CHLSpelling::FindError( const WideString &rParagraph, int32 startAt, int32 *pErrorStart, int32 *pErrorLength, WideStringList* pAlternatives, bool direction  )
{
	std::string str;
	StringUtils::ConvertWideStringToUTF8(rParagraph, str);
	ISpellingService::SpellResult spellResult = kCorrect;

	//FindIncorrectSpaceError is a very simplistic example to show how you can report your own customer errors.
	spellResult = FindIncorrectSpaceError(rParagraph, startAt, pErrorStart, pErrorLength, pAlternatives);
	if (spellResult != kCorrect)
		return spellResult;

	//Find first spelling error in rParagraph starting at startAt
	//Should use something like ICU to tokenize out the words. this example just looks for a space character
	bool16 bEndsWithPeriod = kFalse;
	int32 currentPos = 0, spacePos = -1; 
	
	TRACEFLOW(kCHLPluginName, " spacePos: %d rParagraph.Length: %d startAt: %d currentPos: %d\n", spacePos, rParagraph.Length(), startAt, currentPos);
	while ((spacePos+1 < rParagraph.Length()) && ((spacePos <= startAt) || (spacePos-currentPos == 0)))
	{
		currentPos = spacePos+1;
		spacePos = rParagraph.IndexOf(kTextChar_Space, currentPos);
		if (spacePos == -1)
		{
			spacePos = rParagraph.Length();
			break;
		}
	}

	while (spellResult == kCorrect && (spacePos-currentPos != 0) && (startAt <= currentPos))
	{
		TRACEFLOW(kCHLPluginName, "enter second while with spacePos: %d currentPos: %d\n", spacePos, currentPos);
		WideString* wordToCheck = rParagraph.Substring(currentPos, spacePos-currentPos);
		
		if (wordToCheck == nil)
			break;
		
		StringUtils::ConvertWideStringToUTF8(*wordToCheck, str);
		TRACEFLOW(kCHLPluginName, "word to check: %s\n", str.c_str());
		
		spellResult = Spell( *wordToCheck, pAlternatives, &bEndsWithPeriod);
		delete wordToCheck;

		if (spellResult != kCorrect)
		{
			*pErrorStart = currentPos;
			*pErrorLength = spacePos-currentPos;
			TRACEFLOW(kCHLPluginName, "exit FindError pErrorStart: %d pErrorLength: %d...\n", *pErrorStart, *pErrorLength);
			return spellResult;
		}

		//at end
		if (spacePos+1 >= rParagraph.Length())
			break;

		//find next word
		do
		{
			currentPos = spacePos+1;
			spacePos = rParagraph.IndexOf(kTextChar_Space, currentPos);
			if (spacePos == -1)
			{
				spacePos = rParagraph.Length();
				break;
			}
		} while ((spacePos+1 < rParagraph.Length()) && (spacePos-currentPos == 0));
	}

	return spellResult;
}

void	CHLSpelling::FindAllErrors( const WideString &rParagraph, int32 startAt, std::vector<ISpellingService::SpellingError> *pSpellingErrors )
{
	ISpellingService::SpellingError spellingError;
	spellingError.spellingErrorType = ISpellingService::SpellResult(-1); 
	while (spellingError.spellingErrorType != ISpellingService::kCorrect && startAt < rParagraph.Length())
	{
		spellingError.spellingErrorType = FindError( rParagraph, startAt, &spellingError.errorStart, &spellingError.errorLength, nil );
		if (spellingError.spellingErrorType != ISpellingService::kCorrect)
			pSpellingErrors->push_back(spellingError);
		startAt = spellingError.errorStart + spellingError.errorLength;
	}
}

// General includes: 
#include "CErrorStringService.h" 

// Project includes: 
#include "CHLID.h"

/** From SDK sample; Provides error string service for CHL plugin that 
    maps this plug-in's ErrorCode's to error strings defined in the 
    UserErrorTable ODFRez statement in CHL.fr. 

    @ingroup basicpersistinterface 
*/ 
class CHLErrorStringService : public CErrorStringService 
{ 
public: 
    /** Constructor; this is where we specify the pluginID and the resourceID for the 
        UserErrorTable resource that is associated with this implementation. 
        @param boss interface pointer from boss object on which this interface is aggregated. 
     */ 
    CHLErrorStringService(IPMUnknown* boss): 
        CErrorStringService(boss, kCHLPluginID, kSDKDefErrorStringResourceID) {} 

    /** Destructor 
     */ 
    virtual ~CHLErrorStringService(void) {} 
}; 

/* Make the implementation available to the application. 
*/ 
CREATE_PMINTERFACE(CHLErrorStringService, kCHLErrorStringServiceImpl) 


// End, CHLSpelling.cpp

