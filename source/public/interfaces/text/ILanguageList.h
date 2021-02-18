//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ILanguageList.h $
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
#ifndef __ILanguageList__
#define __ILanguageList__

#include "IPMUnknown.h"
#include "LinguisticID.h"
#include "LanguageID.h"


//----------------------------------------------------------------------------------------
// Interface ILanguageList
//----------------------------------------------------------------------------------------

class ILanguage;
class PMString;
class ICommand;

/** 
	The ILanguage is a persistent interface of the kLanguageBoss. It is used and referenced by the ILanguageList
	which is an interface of the application's and document's workspace.

	@ingroup text_ling
*/
class ILanguageList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILANGUAGELIST };

	/**	Returns number of languages in list. For the session this is the languages
		that are installed. For a document it may contain languages that are not
		presently installed but were available before.

		@return int32			number of languages.
	*/
	virtual	int32				GetLanguageCount() const = 0;

	/**	Returns the Nth addref'ed language.
		@param nNthLanguage		nth language. from 0 to < GetLanguageCount().
		@return ILanguage*		addrefed lanaguage.
	*/
	virtual	ILanguage *			QueryNthLanguage( int32 nNthLanguage  ) = 0;

	/**	Returns language given a lanaguage name.  QueryLanguage() doesn't creates a new language.

		@param rLanguageName	name of language. Corresponds to ILanguage::GetLanguageName().
		@return ILanguage*		addrefed lanaguage.
	*/
	virtual	ILanguage *			QueryLanguage( const PMString &rLanguageName ) = 0;

	/**	Returns the default lanuage.
		@return ILanguage*		addrefed lanaguage.
	*/
	virtual	ILanguage *			QueryDefaultLanguage() = 0;

	/**	Set the default language.
		@param pLanguage	language to set as default.
		@return bool16		kTrue if lanaguage set. kFalse if language is already default
							or language is not in Language list
	*/
	virtual	bool16				SetDefaultLanguage( const ILanguage *pLanguage ) = 0;
	
	/**	Creates a new language. It asserts and returns nil if the language already exists.
		Should only be called by NewLanguageCmd.
		@param UID			UID of new language.
		@return bool16		kTrue if lanaguage is added
	*/
	virtual	bool16				AddLanguage( UID nNewLanguage ) = 0;

	/**	Removes Language from list. This API is not currently used
		and may cause problems. DeleteLanguageCmd is not implemented.
		@param UID			UID of language to remove.
		@return bool16		kTrue if lanaguage is removed
	*/
	virtual	bool16				RemoveLanguage( UID nNewLanguage ) = 0;

	/**	Returns language given a lanaguage id. Doesn't creates a new language.
		Recommend using QueryLanguage with name. Language IDs will hopefully be
		deprecated in the future and only name will be used.

		@param nLanguageID		id of language. Corresponds to ILanguage::GetLanguageID().
		@return ILanguage*		addrefed lanaguage.
	*/
	virtual	ILanguage *			QueryLanguageByID(LanguageID nLanguageID) = 0;
};


#endif
