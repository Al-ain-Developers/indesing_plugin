//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypAdapter.h $
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

#ifndef __HypAdapter__
#define __HypAdapter__

#include "IHyphenationService.h"		// for LinguisticServiceMode
#include "Hyp.h"
#include "LanguageID.h"


class TextCharBuffer;
class IHyphenatedWord;

/** Placeholder for vendor code to adapt vendor hyphenation to the
	linguistic API. A dummy implementation is provided that creates
	two regular hyphenation points, one at the index given by
	parameter nMinHead and the other at the index given by the
	word length - parameter nMinTail. For example if Hyphenate
	were called like this for the word elizabeth:
		Hyphenate("elizabeth", 3, 3, ...

	hyphenation points would be created that could result in the
	word being hyphenated as eli-zab-eth. The implementation also
	respects and creates hyphenation points for discretionary hyphens
	or hard coded hyphens passed in the word.

	Notes:

	To convert the Unicode text to ASCII before presenting a word to
	an ASCII hyphenator check out HypAdapter::textCharToChar.

	Converting Unicode to a PMString then using PMString::GetPlatformString().c_str()
	to get ASCII is likely to lead to bugs. Unicode character codes that
	have no ASCII equivalent appear encoded in the string returned by
	GetPlatformString().c_str.

	The following characters may be presented as part of the word to be
	hyphenated if they are not preceeded or followed by a word break
	character. 	If such characters must be stripped from the word before
	presenting it to a hyphenator re-adjust the hyphenation points so they
	are relative to the word passed by the application:
		kTextChar_FlushSpace
		kTextChar_EnSpace
		kTextChar_EmSpace
		kTextChar_FigureSpace
		kTextChar_PunctuationSpace
		kTextChar_ThinSpace
		kTextChar_HairSpace
		kTextChar_HardSpace
		kTextChar_ZeroSpaceBreak
		kTextChar_ZeroSpaceNoBreak
		kTextChar_EnDash
		kTextChar_EmDash
		kTextChar_Ellipse
		kTextChar_UnicodeHyphen
		kTextChar_NoBreakHyphen
		kTextChar_FigureDash
		kTextChar_HorizontalBar
		kTextChar_LeftDoubleQuotationMark
		kTextChar_RightDoubleQuotationMark
		kTextChar_DoubleLow9QuotationMark
		kTextChar_DoubleHighReversed9QuotationMark
		kTextChar_LeftDblAngQuote
		kTextChar_RightDblAngQuote
		kTextChar_LeftSingleQuotationMark
		kTextChar_RightSingleQuotationMark
		kTextChar_SingleLow9QuotationMark
		kTextChar_SingleHighReversed9QuotationMark

	@ingroup hyphenator

 */
class HypAdapter
{
public:
	/** @return path to folder containing dictionary data files,
		empty string if you don't have any. The path you return here is made
		available on your linguistic service's ILinguisticServiceData interface
		in the service registry. It's also passed back to you when HypAdapter::Install
		is called.
	 */
	virtual PMString			GetDictionaryFolderPath();

	/** Create hyphenation service boss objects (kHypHyphenationServiceBoss)
		supported languages. Called by HypHyphenationMgr.
		@param hyphenationServices OUT collection in which to return created services.
		@param rPath IN path to dictionary folder.
	*/
	virtual	void				Install(Hyp::HyphenationServices& hyphenationServices, const PMString& rPath);

	/**	Hypenate the given word. Parameters nMinHead and nMinTail specify the range of indexes
		in the word where hyphen breaks are permitted.  For example, by specifying 3 for these
		values, the word kitten could be hyphenated kit-ten. i.e.

		kit-ten

		0	1	2	3	4	5

		k	i	t	t	e	n

		0	0	1	0	0	0 (where 1 indicates valid hyphen index)

		A hyphen index is the position before the hyphen: i.e. kit-ten has a hyphen index = 2.

		Given i is a valid hyphen index it will lie in this range:

		nMinHead: 	i >=(nMinHead - 1)			for nMinHead = 3, first i would be 2 (>= 3-1)

		nMinTail: 	i < (wordLength - nMinTail)	for nMinTail = 3, last i would be 2 (< 6-3)

		@param rWord to be hyphenated.
		@param nMinTail the minimum number of characters at the end of a word after a hyphen.
		@param nMinHead the minimum number of characters at the start of a word before a hyphen.
		@param serviceMode is the type of hyphenation desired (algorithmic, dictionary,
		see LinguisticID.h). The value passed is controlled by text attribute kTextAttrHyphenModeBoss.
		@param languageID the language of the word (see LanguageID.h).
		@return hypenated word (see HypHyphenatedWord).
	 */
	virtual	IHyphenatedWord*	Hyphenate(const TextCharBuffer& rWord, uint16 nMinTail, uint16 nMinHead, const LinguisticServiceMode& serviceMode, const LanguageID& languageID);

protected:
	/**	Create hyphenation service (kHypHyphenationServiceBoss) for given language.
		@param hyphenationServices OUT collection created service to be added to.
		@param rPath to dictionary folder (if any).
		@param languageID
		@param languageName
		@param primaryLanguageName
		@param subLanguageName
	  */
	virtual void				installService(Hyp::HyphenationServices& hyphenationServices, const PMString& rPath, const LanguageID& languageID, const PMString& languageName, const PMString& primaryLanguageName, const PMString& subLanguageName);

	/** @param languageID
		@return the name of the dictionary file for the given language.
		The filename returned here is concatenated with the folder
		returned by GetDictionaryFolderPath and gets passed to your
		hyphenation service (IHyphenationService::Set()).
	 */
	virtual PMString			getDictionaryFile(const LanguageID& languageID);

	/**	Analyse the given word and return hyphenationPoints giving the index and type of
		each point.
		@param rWord
		@param nMinTail
		@param nMinHead
		@param serviceMode
		@param languageID
		@param hyphenationPoints for the given word.
	*/
	virtual	void				findHyphenationPoints(const TextCharBuffer& rWord, uint16 nMinTail, uint16 nMinHead, const LinguisticServiceMode& serviceMode, const LanguageID& languageID, Hyp::HyphenationPoints& hyphenationPoints);

	/** @param rWord Unicode word to be converted to ASCII.
		@return ASCII equivalent of Unicode word.
	 */
	virtual char* textCharToChar(const TextCharBuffer& rWord);
};

#endif // __HypAdapter__

