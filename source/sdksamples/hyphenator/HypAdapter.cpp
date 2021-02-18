//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypAdapter.cpp $
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

// Interface includes:
#include "ILanguage.h"
#include "IHyphenationService.h"
#include "IStringData.h"

// General includes:
#include "IHyphenatedWord.h"
#include "TextCharBuffer.h"
#include "WideString.h"
#include "PMString.h"
#include "LanguageID.h"
#include "TextChar.h"
#include "K2Vector.tpp"
#include "CTUnicodeTranslator.h"

// Project includes:
#include "Hyp.h"
#include "HypAdapter.h"
#include "HypHyphenatedWord.h"
#include "HypID.h"

/* Placeholder for vendor code.
*/
PMString HypAdapter::GetDictionaryFolderPath()
{
	return PMString("/invalidfolder/");
}

/* Placeholder for vendor code.
*/
void HypAdapter::Install(Hyp::HyphenationServices& hyphenationServices, const PMString& rPath)
{
	TRACEFLOW("Hyphenator", "HypAdapter::Install(rPath=\"%s\")-->In\n", rPath.GetUTF8String().c_str());

	// Create hyphenation services for supported languages here.

	// Create service for language name "English: USA".
	this->installService(hyphenationServices,
		rPath,
		MakeLanguageID(kLanguageEnglish, kSubLanguageEnglishUS),
		"English: USA", // language name(string translation provided by plug-in Linguistics.rpln).
		"English",		// primary language name (string translation provided by plug-in Linguistics.rpln).
		"USA");			// sub language name (no string translation required).

	// Create service for language name "Spanish: Castilian".
	this->installService(hyphenationServices,
		rPath,
		MakeLanguageID(kLanguageSpanish, kSubLanguageSpanish),
		"Spanish: Castilian",
		"Spanish",
		"Castilian");

	// Localisation notes:

	// The sub language name (USA) does not require a localised
	// string translation. But when it is concatenated like this
	//		PrimaryLanguageName + ": " + SubLanguageName
	// it must form a language name (English: USA) which is
	// localisable string .

	// If you are adding languages the Linguistics.rpln plug-in does
	// not provide string translations for add string translations
	// for the primary language name and the language names to
	// your string translation tables. For example to add Scots
	// and Irish Gaelic your string table would contain:
	/*
		"Gaelic",			"Gaelic",
		"Gaelic: Scots",	"Gaelic: Scots",
		"Gaelic: Irish",	"Gaelic: Irish",
	*/

	// Language name translations provided by the Linguistics.rpln
	// plug-in:
	/*
		"Neutral", "Neutral",

		"Arabic", "Arabic",
		"Arabic: Saudi Arabia", "Arabic: Saudi Arabia",
		"Arabic: Iraq", "Arabic: Iraq",
		"Arabic: Egypt", "Arabic: Egypt",
		"Arabic: Libya", "Arabic: Libya",
		"Arabic: Algeria", "Arabic: Algeria",
		"Arabic: Morocco", "Arabic: Morocco",
		"Arabic: Tunisia", "Arabic: Tunisia",
		"Arabic: Oman", "Arabic: Oman",
		"Arabic: Yemen", "Arabic: Yemen",
		"Arabic: Syria", "Arabic: Syria",
		"Arabic: Jordan", "Arabic: Jordan",
		"Arabic: Lebanon", "Arabic: Lebanon",
		"Arabic: Kuwait", "Arabic: Kuwait",
		"Arabic: United Arab Emirates", "Arabic: United Arab Emirates",
		"Arabic: Bahrain", "Arabic: Bahrain",
		"Arabic: Qatar", "Arabic: Qatar",
		"Algerian ",			"Algerian ",

		"Afrikaans", "Afrikaans",
		"Albanian", "Albanian",
		"Basque", "Basque",
		"Bulgarian", "Bulgarian",
		"Byelorussian", "Byelorussian",
		"Catalan", "Catalan",

		"Chinese", "Chinese",
		"Chinese: Taiwan", "Chinese: Taiwan",
		"Chinese: PR China", "Chinese: PR China",
		"Chinese: Hong Kong", "Chinese: Hong Kong",
		"Chinese: Singapore", "Chinese: Singapore",

		"Chinese: Traditional", "Chinese: Traditional",		//We want these two for now
		"Chinese: Simplified", "Chinese: Simplified",

		"Croatian", "Croatian",
		"Czech", "Czech",
		"Danish", "Danish",

		"Dutch", "Dutch: Old Rules",
		"nl_NL_2005", "Dutch: 2005 Reform",
		"Dutch: Belgian", "Dutch: Belgian",

		"English", "English",
		"English: USA", "English: USA",
		"English: USA Legal", "English: USA Legal",
		"English: USA Medical", "English: USA Medical",
		"English: UK", "English: UK",
		"English: Australian", "English: Australian",
		"English: Canadian", "English: Canadian",
		"English: New Zealand", "English: New Zealand",
		"English: Irish", "English: Irish",
		"English: South Africa", "English: South Africa",
		"English: Jamaica", "English: Jamaica",
		"English: Carribean", "English: Carribbean",

		"US English", "US English",
		"UK English", "UK English",

		"Estonian", "Estonian",
		"Faeroese", "Faeroese",
		"Farsi", "Farsi",
		"Finnish", "Finnish",

		"French", "French",
		"French: Belgian", "French: Belgian",
		"French: Canadian", "French: Canadian",
		"French: Swiss", "French: Swiss",
		"French: Luxembourg", "French: Luxembourg",
		"France French",		"France French",

		"German", "German",
		"German: Traditional", "German: Old Rules",
		"German: Reformed", "German: 1996 Reform",
		"de_DE_2006", "German: 2006 Reform",
		"German: Swiss", "German: Swiss",
		"de_CH_2006", "German: Swiss 2006 Reform",
		"German: Austrian", "German: Austrian",
		"German: Luxembourg", "German: Luxembourg",
		"German: Liechtenstein", "German: Liechtenstein",
		"Germany German",		"Germany German",

		"Greek", "Greek",
		"Hebrew", "Hebrew",
		"Hungarian", "Hungarian",
		"Icelandic", "Icelandic",
		"Indonesian", "Indonesian",

		"Italian", "Italian",
		"Italian: Swiss", "Italian: Swiss",

		"Japanese", "Japanese",
		"Japanese(Not Spell Checked)", "Japanese(Not Spell Checked)",

		"Korean", "Korean",
		"Korean: Johab", "Korean: Johab",

		"Latvian", "Latvian",
		"Lithuanian", "Lithuanian",

		"Norwegian", "Norwegian",
		"Norwegian: Bokmal", "Norwegian: Bokmal",
		"Norwegian: Nynorsk", "Norwegian: Nynorsk",

		"Polish", "Polish",

		"Portuguese", "Portuguese",
		"Portuguese: Brazilian", "Portuguese: Brazilian",

		"Romanian", "Romanian",
		"Russian", "Russian",
		"Slovak", "Slovak",
		"Slovenian", "Slovenian",
		"Serbian", "Serbian",
		"Serbian: Latin", "Serbian: Latin",
		"Serbian: Cyrillic", "Serbian: Cyrillic",

		"Spanish", "Spanish",
		"Spanish: Castilian", "Spanish", //Proximity's Spanish is not region specific. Bug 1427412
		"Spanish: Mexican", "Spanish: Mexican",
		"Spanish: Modern", "Spanish: Modern",
		"Spanish: Guatemala", "Spanish: Guatemala",
		"Spanish: Costa Rica", "Spanish: Costa Rica",
		"Spanish: Panama", "Spanish: Panama",
		"Spanish: Dominican Republic", "Spanish: Dominican Republic",
		"Spanish: Venezuela", "Spanish: Venezuela",
		"Spanish: Colombia", "Spanish: Colombia",
		"Spanish: Peru", "Spanish: Peru",
		"Spanish: Argentina", "Spanish: Argentina",
		"Spanish: Ecuador", "Spanish: Ecuador",
		"Spanish: Chile", "Spanish: Chile",
		"Spanish: Uruguay", "Spanish: Uruguay",
		"Spanish: Paraguay", "Spanish: Paraguay",
		"Spanish: Bolivia", "Spanish: Bolivia",

		"Swedish", "Swedish",
		"Thai", "Thai",
		"Turkish", "Turkish",
		"Ukrainian", "Ukrainian",
	*/

	TRACEFLOW("Hyphenator", "HypAdapter::Install()-->Out\n");
}

/* Placeholder for vendor code.
*/
IHyphenatedWord* HypAdapter::Hyphenate(const TextCharBuffer& rWord, uint16 nMinTail, uint16 nMinHead, const LinguisticServiceMode& serviceMode, const LanguageID& languageID)
{
	TRACEFLOW("Hyphenator", "HypAdapter::Hyphenate(%s, %d, %d, 0x%x, 0x%x)-->In\n",
		PMString(rWord.begin_raw(), rWord.CharCount()).GetUTF8String().c_str(),
		nMinTail,
		nMinHead,
		serviceMode, // see LinguisticID.h
		languageID); // see LanguageID.h

	IHyphenatedWord* result = nil;
	do {
		// Check if we should be hyphenating.
		// For example, we could be called with kLinkguisticService_Nothing
		// if the paragraph is set to not hyphenate.
		if (serviceMode == kLinguisticService_Nothing) {
			break;
		}

		// Hyphenate.
		Hyp::HyphenationPoints hyphenationPoints;
		this->findHyphenationPoints(rWord, nMinTail, nMinHead, serviceMode, languageID, hyphenationPoints);

		// If there are no hyphenation points we are done.
		if (hyphenationPoints.size() == 0) {
			break;
		}

		// Represent as an IHyphenatedWord.
		result = new HypHyphenatedWord(rWord, nMinTail, nMinHead, hyphenationPoints);

	} while(false);
	TRACEFLOW("Hyphenator", "HypAdapter::Hyphenate()-->Out result=0x%x\n", result);
	return(result);
}

/* Placeholder for vendor code.
*/
PMString HypAdapter::getDictionaryFile(const LanguageID& languageID)
{
	return PMString("invalidfile");
}

/* Placeholder for vendor code.
*/
void HypAdapter::installService(Hyp::HyphenationServices& hyphenationServices, const PMString& rPath, const LanguageID& languageID, const PMString& languageName, const PMString& primaryLanguageName, const PMString& subLanguageName)
{
	TRACEFLOW("Hyphenator", "HypAdapter::installService(languageName=\"%s\")-->In\n", languageName.GetUTF8String().c_str());
	do {
		// Configure the service.
		InterfacePtr<ILanguage> language(::CreateObject2<ILanguage>(kHypHyphenationServiceBoss));
		ASSERT(language != nil);
		if (language == nil) {
			break;
		}
		language->SetLanguageID(languageID);
		language->SetLanguageName(languageName);
		language->SetPrimaryLanguageName(primaryLanguageName);
		language->SetSubLanguageName(subLanguageName);
		InterfacePtr<IHyphenationService> hyphenationService(language, UseDefaultIID());
		ASSERT(hyphenationService != nil);
		if (hyphenationService == nil) {
			break;
		}
		hyphenationService->Set(rPath+this->getDictionaryFile(languageID));

		//Set language vendor name
		InterfacePtr<IStringData> stringData(language, UseDefaultIID());
		if (stringData)
		{
			const PMString serviceName(kHypLinguisticServiceName, PMString::kTranslateDuringCall);
			stringData->Set(serviceName);
		}
		// Add the service to collection.
		hyphenationServices.push_back(language);
	}
	while (false);
	TRACEFLOW("Hyphenator", "HypAdapter::installService()-->Out\n");
}

/* Placeholder for vendor code.
*/
void HypAdapter::findHyphenationPoints(const TextCharBuffer& rWordIn, uint16 nMinTail, uint16 nMinHead, const LinguisticServiceMode& serviceMode, const LanguageID& languageID, Hyp::HyphenationPoints& hyphenationPoints)
{
	TextCharBuffer	rWord(rWordIn);

	// Scan the characters and selectively generate hyphenation points.
	for(int32 i = 0; rWord.CharCount() > 0; i++, rWord.RemoveFirst())
	{
		Hyp::HyphenQuality hyphenQuality = IHyphenatedWord::kNoHyphenPoint;
		switch(rWord.First().GetValue()) {
			case kTextChar_HyphenMinus:
			case kTextChar_UnicodeHyphen:
			case kTextChar_FigureDash:
			case kTextChar_HorizontalBar:
			case kTextChar_EmDash:
			case kTextChar_EnDash: {
					hyphenQuality = IHyphenatedWord::kHardHyphenPoint;
					break;
			}
			case kTextChar_DiscretionaryHyphen: {
				hyphenQuality = IHyphenatedWord::kDiscretionaryHyphenPoint;
				break;
			}
			case kTextChar_Solidus:
			case kTextChar_ReverseSolidus:
			case kTextChar_Ellipse:
			case kTextChar_FlushSpace:
			case kTextChar_EnSpace:
			case kTextChar_EmSpace:
			case kTextChar_FigureSpace:
			case kTextChar_PunctuationSpace:
			case kTextChar_ThinSpace:
			case kTextChar_HairSpace:
			case kTextChar_HardSpace:
			case kTextChar_ZeroSpaceBreak: {
				hyphenQuality = IHyphenatedWord::kUnpreferredHyphenPoint;
				break;
			}
		}
		if (hyphenQuality == IHyphenatedWord::kNoHyphenPoint) {
			continue;
		}
		hyphenationPoints.push_back(Hyp::HyphenationPoint(i, hyphenQuality));
	}

	// Add regular hyphenation points at indexes nMinHead and wordLength-nMinTail
	// if these points are not hyphenated already.
	int32 wordLength = rWordIn.CharCount();
	Hyp::HyphenIndex hyphenIndex = nMinHead;
	Hyp::HyphenationPoints::iterator findIter = K2find(hyphenationPoints.begin(), hyphenationPoints.end(), hyphenIndex);
	if (findIter == hyphenationPoints.end()) {
		hyphenationPoints.push_back(Hyp::HyphenationPoint(hyphenIndex, IHyphenatedWord::kRegularHyphenPoint));
	}
	hyphenIndex = wordLength - nMinTail;
	findIter = K2find(hyphenationPoints.begin(), hyphenationPoints.end(), hyphenIndex);
	if (findIter == hyphenationPoints.end()) {
		hyphenationPoints.push_back(Hyp::HyphenationPoint(hyphenIndex, IHyphenatedWord::kRegularHyphenPoint));
	}

	std::sort(hyphenationPoints.begin(), hyphenationPoints.end());
}

/*
*/
char* HypAdapter::textCharToChar(const TextCharBuffer& rWord)
{
	char* result = new char [rWord.CharCount()+1];
	::CTUnicodeTranslator::Instance()->TextCharToChar(rWord.begin_raw(), rWord.CharCount(), result, rWord.CharCount());
	result [rWord.CharCount()] = '\0';
	return result;
}

// End, HypAdapter.h
