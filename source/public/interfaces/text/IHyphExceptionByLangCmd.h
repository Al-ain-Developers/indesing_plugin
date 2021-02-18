//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHyphExceptionByLangCmd.h $
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
#ifndef _H_IHyphExceptionByLangCmdData
#define _H_IHyphExceptionByLangCmdData


#include "IPMUnknown.h"
#include "IHyphenationExceptions.h"

class ILanguage;


/**
	Hyphenation Exceptions by Language Command Data interface.
	@ingroup text_hyphen
*/
class IHyphExceptionByLanguageCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IHYPHEXCEPTIONBYLANGUAGECMDDATA };

		/** Set the HyphenExceptions  and language.
			@param list is the Hyphenation Exceptions List.
			@param lang is the language affected.
		*/
		virtual void 		Set(const HyphenExceptions& list, const ILanguage * lang) = 0;

		/** GetHyphenationExceptions.
			@param he is the HyphenExceptions list that will be set by this method.
		*/
		virtual void 		GetHyphenationExceptions(HyphenExceptions& he) = 0;

		/** GetLanguage.
			@return the ILanguage interface affected by this command.
		*/
		virtual ILanguage * GetLanguage(void) = 0;
};


#endif /* _H_IHyphExceptionByLangCmdData */
