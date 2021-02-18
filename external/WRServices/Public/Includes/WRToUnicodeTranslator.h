//========================================================================================
//
//	File:	WRToUnicodeTranslator.h
//
//	Author: prubini
//
//	Date:	1/19/00
//
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//
//========================================================================================

#ifndef __WRToUnicodeTranslator__
#define __WRToUnicodeTranslator__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRUnicodeTranslator.h"


#ifdef WR_MAC_ENV
#pragma options align=power
#endif

WRSERVICES_DECL void WRToUnicodeTranslatorInitialize();
WRSERVICES_DECL void WRToUnicodeTranslatorTerminate();

class WRSERVICES_DECL WRToUnicodeTranslator
{
protected:
	virtual ~WRToUnicodeTranslator() { }

public:
	typedef enum { kWRUT_GenericProcessing = 0 << 8, 
				   kWRUT_QuarkProcessing = 1 << 8,			
				   kWRUT_MSWordProcessing = 2 << 8,			
				   kWRUT_GreekSharedProcessing = 3 << 8
				} WRUTProcessingType;

	static WRToUnicodeTranslator* GetWRToUnicodeTranslator();

	// toStrLength is a number of unicode char, not of bytes
	// return the number of generated unicodes, or 0 if the buffer is too small
	// special case, if the output buffer is empty, that means that the transcoding was just to get a result len -> no error issued
	virtual WRInt32	CharToTextChar(const WRByteChar* fromString, WRInt32 fromStrLength, WRUnichar16* toString, WRInt32 toStrLength, WRCodePage codePage) = 0;		
	virtual WRInt32	CharToTextChar(const WRByteChar* fromString, WRInt32 fromStrLength, WRUnichar16* toString, WRInt32 toStrLength, WRFontDict* font, WRScriptID writingScript = -1) = 0;		

	virtual WRInt32	GlyphIDToTextChar(const WRGlyphID32 glyphID, WRUnichar16* toString, WRFontDict* fontDict, WRInt32 matchPolicy) = 0;		
		
	virtual WRInt32	GetTranslationLength(WRInt32 options, WRCodePage cp, WRFontDict* font, WRByteChar* input, WRInt32 inputlen) = 0;
				 
	// output is filled up to input is empty or output is full, 
	// input and inputlen are updated accordingly
	// outputlen is set to the num of WRUnichar16 written 
	virtual WRInt32	ChunkTranslate(WRInt32 options, WRCodePage cp, WRFontDict* font, WRByteChar*& input, WRInt32& inputlen, WRUnichar16* output, WRInt32& outputlen) = 0;
	
	// output is filled up to input is empty or output is full, 
	// outputlen is set to the num of WRUnichar16 written or to the required len if kOutputTooSmall
	virtual WRInt32	Translate(WRInt32 options, WRCodePage cp, WRFontDict* font, WRByteChar* input, WRInt32 inputlen, WRUnichar16* output, WRInt32& outputlen) = 0;

	// unicode 4 intf

	virtual WRInt32	CharToTextChar(const WRByteChar* fromString, WRInt32 fromStrLength, WRUnichar32* toString, WRInt32 toStrLength, WRCodePage codePage) = 0;		
	virtual WRInt32	CharToTextChar(const WRByteChar* fromString, WRInt32 fromStrLength, WRUnichar32* toString, WRInt32 toStrLength, WRFontDict* font, WRScriptID writingScript = -1) = 0;		

	virtual WRInt32	GlyphIDToTextChar(const WRGlyphID32 glyphID, WRUnichar32* toString, WRFontDict* fontDict, WRInt32 matchPolicy) = 0;		
		
	// output is filled up to input is empty or output is full, 
	// input and inputlen are updated accordingly
	// outputlen is set to the num of WRUnichar32 written 
	virtual WRInt32	ChunkTranslate(WRInt32 options, WRCodePage cp, WRFontDict* font, WRByteChar*& input, WRInt32& inputlen, WRUnichar32* output, WRInt32& outputlen) = 0;
	
	// output is filled up to input is empty or output is full, 
	// outputlen is set to the num of WRUnichar32 written or to the required len if kOutputTooSmall
	virtual WRInt32	Translate(WRInt32 options, WRCodePage cp, WRFontDict* font, WRByteChar* input, WRInt32 inputlen, WRUnichar32* output, WRInt32& outputlen) = 0;
} ;

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif //__WRToUnicodeTranslator__
