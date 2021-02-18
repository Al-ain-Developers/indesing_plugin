//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IThesaurusService.h $
//  
//  Owner: hhorton
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
#ifndef __IThesaurusService__
#define __IThesaurusService__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "LinguisticID.h"

//----------------------------------------------------------------------------------------
// Interface IThesaurusService
//----------------------------------------------------------------------------------------

class WideString;
typedef K2Vector<WideString> WideStringList;

/** 
	struct ThesDefinition

	container of thesaurus information for a single lookup word's thesaurus definition
	a lookup word may have multiple ThesDefinitions
*/
struct ThesDefinition
{
	typedef object_type data_type;

	inline bool16	operator==( const ThesDefinition& rData ) const;
	
	WideString		fDefinitionStr;			/** definition of the lookup word in this definition context*/
	WideString		fPartOfSpeechStr;		/** part of speech for the lookup word in this definition context */	
	WideString		fInflectionStr;			/** inflection of the lookup word in this thesaurus context */
										
	WideStringList	fSynonyms;				/** synonyms word list */
	WideStringList	fAntonyms;				/** antonyms word list */
	WideStringList	fComparedWords;			/** compared word list */
	WideStringList	fRelatedWords;			/** see also word list */
	WideStringList	fContrastingWords;		/** contrasting word list */
};

/** list of ThesDefinitions */
typedef K2Vector<ThesDefinition> ThesDefinitionList;

/** comparison operator for ThesDefinition */
inline bool16 ThesDefinition::operator==( const ThesDefinition& rData ) const
{
	return	fDefinitionStr == rData.fDefinitionStr && 
			fPartOfSpeechStr == rData.fPartOfSpeechStr &&
			fInflectionStr == rData.fInflectionStr &&
			fSynonyms == rData.fSynonyms &&
			fComparedWords == rData.fComparedWords &&
			fRelatedWords == rData.fRelatedWords &&
			fContrastingWords == rData.fContrastingWords &&
			fAntonyms == rData.fAntonyms;
}

/** Thesaurus Record, the lookup word and a thes definition list of all available definitions */
struct ThesRecord
{
	WideString			fLookupStr;		/** lookup word */
	ThesDefinitionList	fDefinitions;	/** list of ThesDefinitions */
};

/** 
	@ingroup text_dict
*/
class IThesaurusService : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ITHESAURUSSERVICE};

	/** Thesaurus results enum */
	enum ThesResult {kSuccess, kFailure, kThesError};

	/** Thesaurus word list types enum */
	enum ThesWordListEnum {kSynonyms, kAntonyms, kComparedWords, kRelatedWords, kContrastingWords };

	/** Get the thesaurus record for the word

		@param rWord			IN word to lookup
		@param thesRecord		OUT ThesRecord for the lookup word.

		@return					kTrue if the ThesRecord was found.
	*/
	virtual	bool16 GetThesRecord(const PMString &rWord, ThesRecord& thesRecord) = 0;
	
	/** Get the synonyms list for the lookup word

		@param rWord		IN word to lookup
		@param wList		OUT the 'synonyms' wordlist. 

		@return				kTrue if the list was found.
	*/
	virtual	bool16 GetSynonyms(const PMString &rWord, WideStringList& wList) = 0;

	/** Get the antonyms list for the lookup word

		@param rWord		IN word to lookup
		@param wList		OUT the 'antonyms' wordlist. 

		@return				kTrue if the list was found.
	*/
	virtual	bool16 GetAntonyms(const PMString &rWord, WideStringList& wList) = 0;

	/** Get the near synonyms (related words) list for the lookup word

		@param rWord		IN word to lookup
		@param wList		OUT the 'near synonyms' (related) wordlist. 

		@return				kTrue if the list was found.
	*/
	virtual	bool16 GetNearSynonyms(const PMString &rWord, WideStringList& wList) = 0;

	/** Get the near antonyms (contrasting words) list for the lookup word

		@param rWord		IN word to lookup
		@param wList		OUT the 'near antonyms' (contrasted) wordlist.

		@return				kTrue if the list was found.
	*/
	virtual	bool16 GetNearAntonyms(const PMString &rWord, WideStringList& wList) = 0;

	/** Get the see also list for the lookup word

		@param rWord		IN word to lookup
		@param wList		OUT the 'see also' (compared) wordlist.

		@return				kTrue if the list was found.
	*/
	virtual	bool16 GetSeeAlsoWords(const PMString &rWord, WideStringList& wList) = 0;
	
	/** Get the alternate suggestions list for the lookup word, 
	       normally used if the lookup word was not found

		@param rWord		IN word to lookup
		@param wList		OUT the 'alternate suggestions' wordlist.

		@return				kTrue if the list was found.
	*/
	virtual	bool16 GetAltSuggestions(const PMString &rWord, WideStringList& wList) = 0;

	/** Set the thesaurus filename

		@param rThesFileName	IN filename to set

		@return					kTrue if the filename was set.
	*/
	virtual	bool16 Set(const PMString &rThesFileName) = 0;
};

#endif
