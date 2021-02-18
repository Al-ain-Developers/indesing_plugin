//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHyphExceptionsPrefsCmdData.h $
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
#ifndef _H_IHyphExceptionsPrefsCmdData
#define _H_IHyphExceptionsPrefsCmdData

#include "IPMUnknown.h"
#include "IHyphExceptionsPrefs.h"

/**
	Hyphenation Exceptions Preferences Command Data interface.
	Used by kSetHyphExceptionsPrefsCmdBoss.
	@ingroup text_hyphen
*/
class IHyphExceptionsPrefsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPHEXCEPTIONPREFSCMDDATA };

		/** Set the parameters for the command.
			@param type is the preference for the user dictionary.
			@param storeInDocument specifies whether to store the user dictionary in the document.
			@param recompose specifies whether to recompose the document when user dictionary changes.
		*/
	virtual void 	Set(IHyphExceptionsPrefs::HyphPrefType type,
					bool16 storeInDocument,
					bool16 recompose) = 0;

		/** GetHyphExceptionType.
			@return the preference for the user dictionary.
		*/
	virtual IHyphExceptionsPrefs::HyphPrefType	GetHyphExceptionType(void) const = 0;

		/** GetStoreInDocument.
			@return the preference for whether to store the user dictionary in the document.
		*/
	virtual bool16	GetStoreInDocument(void) const = 0;

		/** GetRecompose.
			@return the preference for whether to recompose the document when user dictionary changes.
		*/
	virtual bool16	GetRecompose(void) const = 0;
};


#endif	/* _H_IHyphExceptionsPrefsCmdData */

