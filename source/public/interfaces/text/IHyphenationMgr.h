//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHyphenationMgr.h $
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
#ifndef __IHyphenationMgr__
#define __IHyphenationMgr__

#include "IPMUnknown.h"
#include "LinguisticID.h"

//----------------------------------------------------------------------------------------
// Interface IHyphenationMgr
//----------------------------------------------------------------------------------------
class IHyphenationService;
class ILanguage;
class PMString;

/** 
	@ingroup text_hyphen
*/
class IHyphenationMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPHENATIONMGR };

	/**
		Installs the spelling engine, rPath usually contains the path with the dictionaries.

		@param rPath			Path to directories. may not be needed depending on service
	*/
	virtual	void			Install( const PMString &rPath ) = 0;

	/**
		Returns the count of supported languages.

		@return					count of supported languages.
	*/
	virtual	int32		GetLanguageCount() const = 0;

	/**
		Returns the language of the nth service.

		@param nth				nth service to find language for, nth is 0 based and < GetLanguageCount()

		@return					Returns the language of the nth service.
	*/
	virtual	ILanguage	*	QueryNthLanguage( int32 nNth ) = 0;

	/**
		returns whether nLanguage is supported or not.

		@param pLanguage		Language to see if supported.

		@return					returns kTrue if nLanguage is supported.
	*/
	virtual	bool16		HasLanguage( const ILanguage * pLanguage ) const = 0;

	/**
		Returns the hyphenation service for that language.

		@param pLanguage		language to get hyphenation service for.
		@param nth				nth service for language. nth is 0 based and < GetServiceOfLanguageCount().

		@return					hyphenation service for language.
	*/
	virtual	IHyphenationService*	QueryServiceOfLanguage( const ILanguage * pLanguage, int32 nth = 0 ) = 0;

	/**
        Returns the count of hyphenation services for a language.

        @param pLanguage        language to get count for

        @return                    Count of hyphenation services for language.
    */
    virtual    int32        GetServiceOfLanguageCount( const ILanguage * pLanguage ) = 0;

};

#endif
