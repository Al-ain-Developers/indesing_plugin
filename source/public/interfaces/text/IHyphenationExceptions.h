//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHyphenationExceptions.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef _H_IHyphenationExceptions
#define _H_IHyphenationExceptions

#include "IPMUnknown.h"
#include "TextID.h"

class ILanguage;
class TextCharBuffer;
class HyphenExceptions;
class HyphenExceptionsList;
class IHyphenatedWord;

class IHyphenationExceptions: public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IHYPHENATIONEXCEPTIONS };
	
		/**	
			Sets default hyphenation exceptions list.
			
			@param list		Hyphenation exceptions list to set as default.
		 */
		virtual 	void 	SetDefaultHyphenationExceptionsList(const HyphenExceptionsList& list) = 0;
		
		/**	
			Gets hyphenation exceptions list.
			
			@param list		[OUT] Hyphenation exceptions list retrieved.
		 */
		virtual  	void 	GetHyphenationExceptionsList(HyphenExceptionsList& list) const  = 0;
		/**	
			Sets hyphenation exceptions list.
			
			@param list		Hyphenation exceptions list to set to.
		 */
		virtual 	void 	SetHyphenationExceptionsList(const HyphenExceptionsList& list) = 0;
		
		/**	
			Gets hyphenation exceptions by specific language.
			
			@param hyphenExceptions		[OUT] Hyphenation exceptions returned.
			@param lang					language for which to retrieve hyphenation exceptions.
		 */
		virtual		bool16	GetHyphenExceptionsByLanguage(const HyphenExceptions **hyphenExceptions, const ILanguage* lang) const = 0;
		/**	
			Sets hyphenation exceptions for specific language.
			
			@param hyphenExceptions		Hyphenation exceptions to set to.
			@param lang					language for which to set hyphenation exceptions.

			@return bool16				kTrue if successfully set the hyphenation exceptions for the language.
		 */
		virtual		bool16	SetHyphenExceptionsByLanguage(const HyphenExceptions& hyphenExceptions, const ILanguage* lang) = 0;

		/**	
			Returns the length of hyphenation exceptions list.
			
			@return int32					Length of hyphenation exceptions list.
		 */
		virtual		int32	GetNumHyphExceptionStructs(void) const = 0;

		/**	
                	Gets hyphenation information for a word from the hyphenation exceptions.

	                @param trimmed          word to hyphenate
	                @param lang             language to hyphenate in
	                @param nMinTail         number of characters at end without hyphen point
	                @param nMinHead         number of characters at beginning without hyphen point
			
			@return IHyphenatedWord*		Hyphenated word found or nil.
		 */
		virtual		IHyphenatedWord* LookupExceptionWord(const TextCharBuffer &trimmed, const ILanguage* lang, int16 minTail, int16 minHead) const = 0;
};

#endif /* _H_IHyphenationExceptions */
