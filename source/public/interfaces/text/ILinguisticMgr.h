//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ILinguisticMgr.h $
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
#ifndef __ILinguisticMgr__
#define __ILinguisticMgr__

#include "IPMUnknown.h"
#include "LanguageID.h"
#include "LinguisticID.h"


//----------------------------------------------------------------------------------------
// Interface ILinguisticMgr
//----------------------------------------------------------------------------------------
class IK2ServiceProvider;
class IHyphenationService;
class ISpellingService;
class IThesaurusService;
class IPhoneticService;
class IUserDictService;
class PMString;
class ILanguage;

#define	kDefaultLinguisticProvider	0

/** 
	The LinguisticMgr is able to support many Linguistic systems (like Proximity and Info) 
	at the same time. A Linguistic System contains a set of services: hyphenation, spelling,
	thesaurus and user dictionaries. 
	To be able to mix the Linguistic Systems you should ask the LinguisticMgr for a particular
	service with a language specification. The connections between a language and a service will
	be administrated in the workspace of the application.
	@ingroup text_ling
*/
class ILinguisticMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINGUISTICMGR };
	enum Services	{ kHyphenation, kSpelling, kPhonetic, kThesaurus };
	

	//---------SERVICE QUERY ROUTINES-----------------

	/** 
		Query for the simple hyphenation service
		The simple hyphenation service ranks MinTail, MinHead, hard hyphens and discretionary hyphens.

		@return	IHyphenationService		hyphenation service
	*/
	virtual	IHyphenationService	*	QuerySimpleHyphenationService() = 0;

	/** 
		Query for the associated hyphenation service of a language
		If nProvider is not kDefaultLinguisticProvider this provider is preferred.

		@param pLanguage	language to get hyphenation service for
		@param nProvider	If nProvider is not kDefaultLinguisticProvider this provider is preferred

		@return	IHyphenationService		hyphenation service
	*/
	virtual	IHyphenationService	*	QueryHyphenationService( const ILanguage *pLanguage, ClassID nProvider = kDefaultLinguisticProvider ) = 0;

	/** 
		Query for the associated spelling service of a language
		If nProvider is not kDefaultLinguisticProvider this provider is preferred.

		@param pLanguage	language to get spelling service for
		@param nProvider	If nProvider is not kDefaultLinguisticProvider this provider is preferred

		@return	ISpellingService		spelling service
	*/
	virtual	ISpellingService	*	QuerySpellingService( const ILanguage *pLanguage, ClassID nProvider = kDefaultLinguisticProvider ) = 0;

	/** 
		Query for the associated thesaurus service of a language
		If nProvider is not kDefaultLinguisticProvider this provider is preferred.

		@param pLanguage	language to get thesaurus service for
		@param nProvider	If nProvider is not kDefaultLinguisticProvider this provider is preferred

		@return	IThesaurusService		thesaurus service
	*/
	virtual	IThesaurusService	*	QueryThesaurusService( const ILanguage *pLanguage, ClassID nProvider = kDefaultLinguisticProvider ) = 0;

	/** 
		Query for the associated user dictionary service of a language
		If nProvider is not kDefaultLinguisticProvider this provider is preferred.

		@param pLanguage	language to get user dictionary service for
		@param nProvider	If nProvider is not kDefaultLinguisticProvider this provider is preferred

		@return				user dictionary service
	*/
	virtual	IUserDictService	*	QueryUserDictService( const ILanguage *pLanguage, ClassID nProvider = kDefaultLinguisticProvider ) = 0;


	//---------SERVICE ITERATING ROUTINES-----------------

	/** 
		Get count of services for a language

		@param nWhich		which service to get a count of
		@param pLanguage	language to get a count for

		@return int32		count of services
	*/
	virtual	int32				GetServicesCount(ILinguisticMgr::Services nWhich,
									const ILanguage *pLanguage) const = 0;

	/** 
		Query for nth spelling service for a specific language

		@param pLanguage	language to get spelling service for
		@param nService		From 0 to < GetServicesCount
		@param pServiceName	OUT - String to place service name into.

		@return ISpellingService	spelling service
	*/
	virtual	ISpellingService *	QueryNthSpellingService( const ILanguage *pLanguage, int32 nService,
									PMString *pServiceName = nil ) const = 0;
	/** 
		Query for nth hyphenation service for a specific language

		@param pLanguage	language to get hyphenation service for
		@param nService		From 0 to < GetServicesCount
		@param pServiceName	OUT - String to place service name into.

		@return IHyphenationService	hyphenation service
	*/
	virtual	IHyphenationService *	QueryNthHyphenationService( const ILanguage *pLanguage, int32 nService,
									PMString *pServiceName = nil ) const = 0;


	/** 
		Query for nth Thesaurus service for a specific language

		@param pLanguage	language to get Thesaurus service for
		@param nService		From 0 to < GetServicesCount
		@param pServiceName	OUT - String to place service name into.

		@return IThesaurusService	Thesaurus service
	*/
	virtual	IThesaurusService *	QueryNthThesaurusService( const ILanguage *pLanguage, int32 nService,
									PMString *pServiceName = nil ) const = 0;


	//---------LANGUAGE ITERATING ROUTINES-----------------

	/** 
		Get count of languages in session ILanguageList

		@return int32		count of languages
	*/
	virtual	uint32				GetLanguageCount() const = 0;

	/** 
		Query for nth language in session ILanguageList

		@param nNthLanguage		from 0 to < GetLanguageCount()

		@return ILanguage		nth language
	*/
	virtual	ILanguage *			QueryNthLanguage( uint32 nNthLanguage  ) = 0;

	/** 
		Query for language by name in session ILanguageList

		@param rLanguageName	name of language. corresponds to ILanguage::GetLanguageName().

		@return ILanguage		language with name
	*/
	virtual	ILanguage *			QueryLanguage( const PMString &rLanguageName  ) = 0;


	//---------LINGUISTIC SERVICE ROUTINES-----------------

	/**	
		Get the default linguistic provider.

		@param IK2ServiceProvider		linguistic provider
	*/
	virtual	IK2ServiceProvider *		QueryDefaultProvider() = 0;

	/**	
		Returns the installed kLinguisticService for the class id.
	
		@param nClass			class id of linguistic service

		@param IK2ServiceProvider		linguistic provider
	*/
	virtual	IK2ServiceProvider *		QueryProviderByClassID( ClassID nClass ) = 0;


	//---------DISCOURAGED ROUTINES-----------------
	// These routines may be deprecated in the future.

	/**	
		Fills pName with the name that uses the languageid according to a hard coded list of names.
	
		NOT RECOMMENDED - there can be multiple unique language names with the same language id
		Use name as unique identifier not languageid. Language IDs will hopefully be
		deprecated in the future and only name will be used.

		@param nLanguageID		corresponds to ILanguage::GetLanguageID()
		@param pName			language name. corresponds to ILanguage::GetLanguageName()
		@param pPrimaryName		primary language name. corresponds to ILanguage::GetPrimaryLanguageName()
		@param pSubName			sub language name. corresponds to ILanguage::GetSubLanguageName()

		@return bool16			false if unknown.
	*/
	virtual	bool16				GetLanguageName( LanguageID nLanguage, PMString *pName, PMString *pPrimaryName = nil,
									PMString *pSubName = nil ) const = 0;
	
	/**	
		Returns the installed ILanguage for the LanguageID according to a hard coded list of names.
	
		NOT RECOMMENDED - there can be multiple unique language names with the same language id
		Recommend using QueryLanguage(rLanguageName). Language IDs will hopefully be
		deprecated in the future and only name will be used.

		@param nLanguageID		corresponds to ILanguage::GetLanguageID()
	*/
	virtual	ILanguage *			QueryLanguageByID( LanguageID nLanguageID  ) = 0;

	// obsolete call pServices->GetServiceProviderCount( kLinguisticService ) instead
	virtual	int32				GetProviderCount() const = 0;

	// obsolete call pServices->QueryNthServiceProvider( kLinguisticService, nService ) instead
	virtual	IK2ServiceProvider *		QueryNthProvider( int32 nService ) = 0;

	// obsolete use ILanguage QuerySpellingService and QueryHyphenationService
	virtual	IK2ServiceProvider	*	QueryDefaultService( ILinguisticMgr::Services nWhich, const ILanguage *pLanguage ) = 0;

	// obsolete use SERVICE QUERY ROUTINES above
	virtual	IK2ServiceProvider	*	QueryNthService( ILinguisticMgr::Services nWhich, const ILanguage *pLanguage,
										uint32 nNthService  ) = 0;

	// obsolete use ILanguage SetSpellingService and SetHyphenationService
	virtual	bool16				SetDefaultService( ILinguisticMgr::Services nWhich, const ILanguage *pLanguage,
										const IK2ServiceProvider *pProvider ) = 0;

	// obsolete call GetServicesCount instead
	virtual	uint32				GetServiceCount( ILinguisticMgr::Services nWhich, const ILanguage *pLanguage ) const = 0;
};


#endif
