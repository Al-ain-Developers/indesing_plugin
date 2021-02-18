//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ILanguage.h $
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
#ifndef __ILanguage__
#define __ILanguage__

#include "IPMUnknown.h"

#include "PMTextUtils.h"
#include "UnicodeClass.h"

#include "ICUForwardDeclare.h"
#include "LanguageID.h"
#include "LinguisticID.h"
#include "OTFeature.h"
#include <map>


class PMString;
class IHyphenationService;
class ISpellingService;
class ITextModel;
class WideString;
class QuoteEntry;



/**
	The ILanguage is a persistent interface of the kLanguageBoss. It is used and referenced by the ILanguageList
	which is an interface of the application's and document's workspace.

	@ingroup text_ling
*/
class ILanguage : public IPMUnknown
{
public:
	enum 		{ kDefaultIID = IID_ILANGUAGE };

	enum		QuotationType { kSingle, kDouble };
	enum		QuotationPosition { kLeft, kRight };

	/**
		Gets the full language name i.e.: "English: US". This name needs to be unique.
		It is the identifier for a language.

		@return  PMString	The full language name i.e.: "English: US"
	*/
	virtual	const PMString &	GetLanguageName() const = 0;

	/**
		Gets the primary language name i.e.: "English".

		@return  PMString	The primary language name i.e.: "English".
	*/
	virtual	const PMString &	GetPrimaryLanguageName() const = 0;

	/**
		Gets the sub language name i.e.: "US".

		@return  PMString	The sub language name i.e.: "US".
	*/
	virtual	const PMString &	GetSubLanguageName() const = 0;

	/**
		Returns the LanguageID that classifies this language.

		If you need a unique identifier use GetLanguageName().
		Language IDs are a convience to check things like -
			GetPrimaryLanguageID(language->GetLanguageID()) == kLanguageDutch

		@return LanguageID        lanaguage id.
	*/
	virtual	LanguageID		GetLanguageID() const = 0;


	/**
		Sets the full language name i.e.: "English: US"

		@param  rName	The full language name i.e.: "English: US"
	*/
	virtual	void			SetLanguageName( const PMString &rName ) = 0;

	/**
		Sets the primary language name i.e.: "English".

		@param  rName	The primary language name i.e.: "English".
	*/
	virtual	void			SetPrimaryLanguageName( const PMString &rName ) = 0;

	/**
		Sets the sub language name i.e.: "US".

		@param  rName	The sub language name i.e.: "US".
	*/
	virtual	void			SetSubLanguageName( const PMString &rName ) = 0;

	/**
		Sets the LanguageID that classifies this language.

		Language IDs should not be used as an unique identifier. Use language name.

		@param nLanguage        lanaguage id.
	*/
	virtual	void 			SetLanguageID( const LanguageID nLanguage ) = 0;


	/**
		Copies the values from a different language

		@param  pLanguage	langauge to copy
	*/
	virtual	void			CopyFrom( const ILanguage *pLanguage ) = 0;

	/**
		Language names are equal. Does not compare settings in the language like quotes

		@return bool16		kTrue if languge names are equal
	*/
	virtual	bool16			IsEqual( const ILanguage *pLanguage ) const = 0;

	/**
		Returns the unicode value corresponding to the quote given the type and position.

		@param  nType		QuotationType (kDouble/kSingle),
		@param  nPosition	QuotationPosition (kLeft/kRight)

		@return UTF32TextChar		the unicode value of quote
	*/
	virtual	UTF32TextChar	GetQuotationMark( ILanguage::QuotationType nType, ILanguage::QuotationPosition nPosition ) = 0;

	/**
		Sets the Quote Entry.
		This uses the IQuotes interface on the same boss if the interface exists.

		@param  newQuoteEntry	entry

		@return bool16			kTrue if IQuotes interface was found on boss
	*/
	virtual	bool16			SetQuotationMarks( const QuoteEntry& newQuoteEntry ) = 0;

	/**
		Returns the Quote Entry object which contains four quotes.
		This uses the IQuotes interface on the same boss if the interface exists.

		@param  qe			quote entry

		@return bool16		kTrue if IQuotes interface was found on boss
	*/
	virtual	bool16 			GetQuotationMarks(QuoteEntry& qe) const = 0;

    /**
		Find the word at a text location.
		@see IComposeScanner.
		@see ITextUtils.

		@param pModel		The text model in question.
		@param nPosition	The text location in question.
		@param pLength		OUT the length of the word.
		@param aFunction	a function that determines what characters are considered word breaking.

		@return				the beginning location of the surrounding word.
	*/
	virtual	TextIndex		FindSurroundingWord( const ITextModel *pModel, TextIndex nPosition, int32 *pLength, FuncIsWordChar aFunction) const = 0;

	/**
		Find the word at a text location.
		@see IComposeScanner.
		@see ITextUtils.

		@param pModel		The text model in question.
		@param nPosition	The text location in question.
		@param pLength		OUT the length of the word.
		@param aFunction	a function that determines what characters are considered word breaking.

		@return				the beginning location of the surrounding word.
	*/
	virtual	TextIndex		FindSurroundingWordUsingWordCharFuncOnly( const ITextModel *pModel, TextIndex nPosition, int32 *pLength, FuncIsWordChar aFunction) const = 0;

	/**
		Gets the writing script of the language

		@return  int16		returns the writing script of the language like kCTRomanScript, see RealCoolType.h
	*/
	virtual	int16			GetWritingScript() const = 0;

	/**
		Gets the OpenType script tag for the language.

		See - http://partners.adobe.com/public/developer/opentype/index_tag1.html

		@return  const char*		returns the OpenType script tag for the language
	*/
	virtual	const char*		GetOpenTypeScriptTag() const = 0;

	/**
		Gets the OpenType language tag for the language.

		See - http://partners.adobe.com/public/developer/opentype/index_tag2.html

		@return  const char*		returns the OpenType language tag for the language
	*/
	virtual	const char*		GetOpenTypeLanguageTag() const = 0;

	/**
		AfterHyphenationCanChange returns information about hyphenation behavior for a language.
		Currently, only Dutch return kTrue -- meaning that some words hyphenate and the piece of the
		word AFTER the hyphenation break can change spelling.
		More languages change spelling before the break, but this is only for AFTER the break.

		@return whether the language can change spelling after the hyphenation break.
	*/
	virtual	bool16			AfterHyphenationCanChange() const = 0;

	/**
		Compares using language. Uses ICU locale and ICU collator to compare.
		See - http://icu.sourceforge.net/userguide/Collate_Intro.html

		@param	a		string to compare
		@param	b		string to compare
		@param	usePrefixPunctuation controls whether "!B" sorts before "A" or after. Before = use punctuation.
		@param	aLang	language of a. currently not used
		@param	bLang	language of b. currently not used
		@return int32	0 then a=b. 1 then a>b. -1 then a<b.
	*/
	virtual	int32			LinguisticCompare(const WideString& a, const WideString& b,
												LanguageID aLang = 0, LanguageID bLang = 0, bool16 usePrefixPunctuation = kFalse) const = 0;


#ifdef ID_DEPRECATED
	/**
		Compares using primary level (also called level-1 strength) sort for language.
		Uses ICU locale and ICU collator to compare.
		See - http://icu.sourceforge.net/userguide/Collate_Intro.html

		@param	a		string to compare
		@param	b		string to compare
		@param	aLang	language of a. currently not used
		@param	bLang	language of b. currently not used
		@return int32	0 then a=b. 1 then a>b. -1 then a<b.
	*/
	virtual	int32			LinguisticComparePrimary(const WideString& a, const WideString& b,
												LanguageID aLang = 0, LanguageID bLang = 0) const = 0;
#endif

	/**
		Get OpenType features required to render this language.

		@return OpenTypeFeatureList		features required for language
	*/
	virtual const OpenTypeFeatureList&	GetRequiredOTFeatureList() const = 0;

	/**
		Get locale to pass to ICU routines.
		See - http://icu.sourceforge.net/userguide/locale.html

		@return Locale		ICU locale
	*/
	virtual const ID_ICU_NAMESPACE::Locale&		GetICULocale() const = 0;

	/**
		Get ICU locale string by calling Locale.getName().

		@return std::string		ICU locale string
	*/
	virtual std::string GetICULocaleString() const = 0;

	/**
		Set locale to be used by routines like LinguisticCompare.
		SetLanguageID will overwrite the ICULocale so make sure you set it after calling
		SetLanguageID.

		@param Locale		ICU locale
	*/
	virtual void			SetICULocale(const ID_ICU_NAMESPACE::Locale &newLocale) = 0;

	/**
		Set locale to be used by routines like LinguisticCompare.
		SetLanguageID will overwrite the ICULocale so make sure you set it after calling
		SetLanguageID.

		@param Locale		ICU locale
	*/
	virtual void			SetICULocale(std::string newLocale) = 0;

	/**
		Set for spelling service for this language

		@param spellingService	spelling service to set for language
	*/
	virtual	void				SetSpellingService( ISpellingService *spellingService ) = 0;

	/**
		Query for spelling service for this language

		@param error				Name of missing spelling Provider. If this sting is empty
									and return in nil then this language did not have a spelling
									service and should not be considered an error. For example
									Japanese does not have a spelling service.

		@return ISpellingService	spelling service to use for language
	*/
	virtual	ISpellingService	*QuerySpellingService(PMString *error = nil) const = 0;

	/**
		Set for hyphenation service for this language

		@param hyphenationService	hyphenation service to set for language
	*/
	virtual	void				SetHyphenationService( IHyphenationService *hyphenationService ) = 0;

	/**
		Query for hyphenation service for this language

		@param error				Name of missing hyphenation Provider. If this sting is empty
									and return in nil then this language did not have a hyphenation
									service and should not be considered an error. For example
									Japanese does not have a hyphenation service.

		@return IHyphenationService	hyphenation service to use for language
	*/
	virtual	IHyphenationService	*QueryHyphenationService(PMString *error = nil) const = 0;

	/**
		Get string to use when hyphenating word. For most languages this is just kTextChar_HyphenMinus

		@param hyphenString		string to use when hyphenating a word
	*/
	virtual void GetHyphenString(WideString &hyphenString) const = 0;
};


/**
	LinguisticCompareMap is used to sort mapped PMStrings using
	ILangauge::LinguisticCompare
*/
struct appUILinguisticLessthan
{
  PUBLIC_DECL bool operator()(const PMString &s1, const PMString &s2) const;
};
typedef std::map<PMString,PMString, appUILinguisticLessthan> LinguisticCompareMap;



#endif
