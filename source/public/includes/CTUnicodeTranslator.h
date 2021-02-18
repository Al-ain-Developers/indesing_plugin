//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTUnicodeTranslator.h $
//  
//  Owner: Michiko Jessett
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
#ifndef __CTUNICODETRANSLATOR__
#define  __CTUNICODETRANSLATOR__

#pragma export on
#include "CTextEnum.h"
#include "BravoForwardDecl.h"

class UnicodeTranslateFromTo;

#ifdef MACINTOSH
	// faking symbols not in Type1 fonts but used to be faked on the mac.
bool16 IsFakedOutSymbolUnicode(UTF32TextChar c);
bool16 IsFakedOutSymbolPlatform(char c);
#endif


/**
	Translate platform string to Unicode and Unicode strings to platform.
*/
class PUBLIC_DECL CTUnicodeTranslator
{
	public:
		/**	Convert platform buffer to Unicode buffer.
			@param fromString		buffer to translate
			@param fromStrLength	length of fromString in bytes
			@param toString			OUT buffer to put translation
			@param toStrLength		length of UTF16TextChar allocated to toString.
			@param writingscript	script of fromString. if kDontKnowScript then LocaleSetting::GetSystemScript is
									used
			@return int32			number of UTF16TextChars written to toString
		 */
		int32 CharToTextChar(const char* fromString, int32 fromStrLength, UTF16TextChar* toString, int32 toStrLength,
			int32 writingscript = kDontKnowScript);

		/**	Convert Unicode buffer to platform buffer.
			@param fromString		buffer to translate
			@param fromStrLength	length of fromString in UTF16TextChars
			@param toString			OUT buffer to put translation
			@param toStrLength		length of bytes allocated to toString.
			@param writingscript	script of toString. if kDontKnowScript then LocaleSetting::GetSystemScript is
									used
			@return int32			number of bytes written to toString
		 */
		int32 TextCharToChar(const UTF16TextChar* fromString, int32 fromStrCharCount, char* toString,
			int32 toStrLength, int32 writingscript = kDontKnowScript); 

		/**	Convert Unicode buffer to platform buffer.
			@param fromString		buffer to translate
			@param fromStrLength	length of fromString in UTF16TextChars
			@param toString			OUT buffer to put translation
			@param toStrLength		length of bytes allocated to toString.
			@param stoppedFlag		OUT	translation was stopped
			@param bytesTranslated	OUT number of bytes translated
			@param writingscript	script of toString. if kDontKnowScript then LocaleSetting::GetSystemScript is
									used
			@return int32			number of bytes written to toString
		 */
		int32 TextCharToChar_Exact(const textchar* fromString, int32 fromStrCharCount, char* toString,
			int32 toStrLength, bool16& stoppedFlag, int32& bytesTranslated, int32 writingscript = kDontKnowScript);

		static CTUnicodeTranslator* Instance();
		static CTEncoding* GetUnicodeEncoding();
		static void DeleteInstance();
		
	protected:
		CTUnicodeTranslator(); 
		~CTUnicodeTranslator();
				UnicodeTranslateFromTo* DetermineFontIndependentTranslator(int32 script);


	private:
		static IDThreading::ThreadLocal<CTUnicodeTranslator	*> tl_UniTranslator;
		static IDThreading::ThreadLocalManagedObject<CCTEncoding> tl_Unicoding;
		
		int32				fToScript;
		int32				fFromScript;

		// For GlyphIDToTextChar
		
		UnicodeTranslateFromTo* fFontIndependentNonRoman;
		UnicodeTranslateFromTo* fFontIndependentRoman;
};

#pragma export off

#endif
