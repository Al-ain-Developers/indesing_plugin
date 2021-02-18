//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDictionaryUtils.h $
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
#ifndef __IDictionaryUtils__
#define __IDictionaryUtils__

#include "IPMUnknown.h"

#include "LinguisticID.h"
#include "K2Vector.h"
#include "KeyValuePair.h"

class IDocument;
class WideString;
class PMString;
class ILanguage;
class HyphenExceptionsList;
class IScript;
class IUserDict;
class IScriptRequestData;

typedef K2Vector<KeyValuePair<int32, int32> >	HyphenPoints;		// sorted


#include "ITextUtils.h" //for FuncIsWordChar

/** Utilities related to dictionaries.
	e.g.
	<pre>Utils&lt;IDictionaryUtils&gt;()->GetUserDictStringList( ... ) ;</pre>
	@ingroup text_util 
	@ingroup text_dict
*/
class IDictionaryUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDICTIONARYUTILS };
	
	virtual bool16 	GetAllUserDictsStringList(HyphenExceptionsList& list, bool16 bMerge) const = 0;
	virtual void 	CopyUserDictsToDocument(IDocument * doc) const = 0;
	virtual bool16 	CheckForAndHandleHyphConflicts(IDocument * doc, HyphenExceptionsList& heList) const = 0;
	virtual bool16	GetProximityWord( const PMString& rNewWord, WideString *pWord, HyphenPoints *pPoints ) const = 0;

	/** 
		Imports the words into the user dictionary.

		@param pLang			language of user dictionary to import into
		@param userDict			user dictionary to import into
		@param nProvider		not used. send in kDefaultLinguisticProvider
		@param userDoctFile		file to import words from. If nil then open file dialog is used. Only text files are supported.
		@param replaceOldDict	words are removed from userDict before importing.
		@param ignoreRanking	if kTrue then a word that matches a word already in the dictionary but has different
								hyphenation points will not be added to the userDict.
		@param isDictWordChar	if nil default(PMCharFilters::SpellingIsUserDictChar) will be used. 
		@param caseSensitive	if kTrue words with different casing will be added. 

		@return bool16			kFalse if there was an error importing. 
	*/
	virtual bool16 	ImportUserDict( ILanguage* pLang, IUserDict* userDict, ClassID nProvider, IDFile *userDoctFile = nil, bool16 replaceOldDict = kTrue, bool16 ignoreRanking = kFalse, FuncIsWordChar isDictWordChar = nil, bool16 caseSensitive = kFalse ) const = 0;

	/** 
		Exports the words of the user dictionary.

		@param pLang			language of user dictionary to export
		@param userDict			user dictionary to export
		@param nProvider		not used. send in kDefaultLinguisticProvider
		@param userDoctFile		file to save words in. If nil then save dialog is used

		@return bool16			kFalse if there was an error exporting. 
	*/
	virtual bool16 	ExportUserDict( ILanguage* pLang, IUserDict* userDict, ClassID nProvider, IDFile *userDoctFile = nil ) const = 0;

	//For Scripting
	virtual int32	 GetNumUserDicts() const = 0 ;
	virtual IScript* QueryUserDictByName( const IScriptRequestData* data, const PMString& name ) const = 0 ;
	virtual IScript* QueryUserDictByLanguageIndex( const IScriptRequestData* data, int32 n ) const = 0 ;
	virtual IScript* QueryUserDictByIndex( const IScriptRequestData* data, int32 n ) const = 0 ;
};


#endif	// __IDictionaryUtils__
