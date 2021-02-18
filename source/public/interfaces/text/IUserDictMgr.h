//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IUserDictMgr.h $
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
#ifndef __IUserDictMgr__
#define __IUserDictMgr__

#include "IPMUnknown.h"

//----------------------------------------------------------------------------------------
// Interface IUserDictMgr
//----------------------------------------------------------------------------------------

class IUserDictService;
class PMString;
class ILanguage;

/** 
	@ingroup text_dict
*/
class IUserDictMgr : public IPMUnknown
{
public:

	/** 
		OBSOLETE
	*/
	virtual	void					Install( const PMString &rPath ) = 0;

	/** 
		Gets total count of supported languages.

		@return int32			count of supported languages. 
	*/
	virtual	int32				GetLanguageCount() const = 0;

	/** 
		Queries the language of the n'th service.

		@param nNth			nth service to find language for, nth is 0 based and < GetLanguageCount()

		@return ILanguage*	the language of the nth service. 
	*/
	virtual	ILanguage	*			QueryNthLanguage( int32 nNth ) = 0;
	
	/**
		Returns whether the specified language is supported or not.

		@param pLanguage		Language to see if supported.

		@return bool16			kTrue if the specified language is supported.
	*/
	virtual	bool16				HasLanguage( const ILanguage * pLanguage ) const = 0;

	/**
		Returns the user dict service for the specified language.

		@param pLanguage		Language to get user dict service for.

		@return IUserDictService*		User dict service for the specified language.
	*/
	virtual	IUserDictService*		QueryServiceOfLanguage( const ILanguage * pLanguage ) = 0;
};

#endif
