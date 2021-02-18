//========================================================================================
//
//	File:	WRFromUnicodeTranslator.h
//
//	Author: prubini
//
//	Date:	03/22/2002
//
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//
//========================================================================================

#ifndef __WRFromUnicodeTranslator__
#define __WRFromUnicodeTranslator__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRUnicodeTranslator.h"


#ifdef WR_MAC_ENV
#pragma options align=power
#endif

WRSERVICES_DECL void WRFromUnicodeTranslatorInitialize();
WRSERVICES_DECL void WRFromUnicodeTranslatorTerminate();

class WRSERVICES_DECL WRFromUnicodeTranslator
{
protected:
	virtual ~WRFromUnicodeTranslator();

public:
	static WRFromUnicodeTranslator* GetWRFromUnicodeTranslator();

	virtual WRInt32		TextCharToChar(const WRUnichar16* fromString, WRInt32 fromStrLength, WRByteChar* toString, WRInt32 toStrLength, WRCodePage codePage) = 0; 
	virtual WRInt32		TextCharToChar(const WRUnichar16* fromString, WRInt32 fromStrLength, WRByteChar* toString, WRInt32 toStrLength, WRFontDict* font, WRScriptID writingScript = -1) = 0; 

	virtual WRInt32		TextCharToChar_Exact(const WRUnichar16* fromString, WRInt32 fromStrLength, WRByteChar* toString, WRInt32 toStrLength, 
											WRBool16& stoppedFlag, WRInt32& bytesTranslated, WRCodePage codePage) = 0;

	virtual WRInt32		TextCharToChar_Exact(const WRUnichar16* fromString, WRInt32 fromStrLength, WRByteChar* toString, WRInt32 toStrLength, 
											WRBool16& stoppedFlag, WRInt32& bytesTranslated, WRFontDict* font, WRScriptID writingScript = -1) = 0;

	virtual WRInt32		GetTranslationLength(WRInt32 options, WRCodePage cp, WRFontDict* font, WRUnichar16* input, WRInt32 inputlen) = 0;

	virtual WRInt32		ChunkTranslate(WRInt32 options,WRCodePage cp,WRFontDict* font,WRUnichar16*& input,WRInt32& inputlen, WRByteChar* output, WRInt32& outputlen) = 0;
	virtual WRInt32		Translate(WRInt32 options, WRCodePage cp, WRFontDict* font, WRUnichar16* input, WRInt32 inputlen, WRByteChar* output, WRInt32& outputlen) = 0;

	// unicode 4 intf
	virtual WRInt32		TextCharToChar(const WRUnichar32* fromString, WRInt32 fromStrLength, WRByteChar* toString, WRInt32 toStrLength, WRCodePage codePage) = 0; 
	virtual WRInt32		TextCharToChar(const WRUnichar32* fromString, WRInt32 fromStrLength, WRByteChar* toString, WRInt32 toStrLength, WRFontDict* font, WRScriptID writingScript = -1) = 0; 
	virtual WRInt32		TextCharToChar_Exact(const WRUnichar32* fromString, WRInt32 fromStrLength, WRByteChar* toString, WRInt32 toStrLength, 
											WRBool16& stoppedFlag, WRInt32& bytesTranslated, WRCodePage codePage) = 0;

	virtual WRInt32		TextCharToChar_Exact(const WRUnichar32* fromString, WRInt32 fromStrLength, WRByteChar* toString, WRInt32 toStrLength, 
											WRBool16& stoppedFlag, WRInt32& bytesTranslated, WRFontDict* font, WRScriptID writingScript = -1) = 0;

	virtual WRInt32		GetTranslationLength(WRInt32 options, WRCodePage cp, WRFontDict* font, WRUnichar32* input, WRInt32 inputlen) = 0;

	virtual WRInt32		ChunkTranslate(WRInt32 options,WRCodePage cp,WRFontDict* font,WRUnichar32*& input,WRInt32& inputlen, WRByteChar* output, WRInt32& outputlen) = 0;
	virtual WRInt32		Translate(WRInt32 options, WRCodePage cp, WRFontDict* font, WRUnichar32* input, WRInt32 inputlen, WRByteChar* output, WRInt32& outputlen) = 0;

} ;

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif // __WRFromUnicodeTranslator__

