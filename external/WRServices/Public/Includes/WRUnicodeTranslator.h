//========================================================================================
//
//	File:	WRUnicodeTranslator.h
//
//	Author: Michel Hutinel
//
//	Date:	9/11/2000
//

//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//
//========================================================================================

#ifndef __WRUnicodeTranslator__
#define __WRUnicodeTranslator__

#include "WRConfig.h"
#include "WRDefines.h"

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

// Definitions of constantes used by WRToUnicodeTranslator and WRFromUnicodeTranslator
typedef enum {	kWRUT_NoError,
				kWRUT_CodepageNotSupportedError,
				kWRUT_OptionNoSupportedError,
				kWRUT_OutputTooSmallError,
				kWRUT_TranslationError,
				kWRUT_EscapeError,
				kWRUT_BreakOnMissingCharError,
				kWRUT_NotHandledError } WRUT_Error; // return codes

typedef enum {	kWRUT_ChunkMode = 1, // output is filled up to input is empty of output full, input and inputlen are updated accordingly
				kWRUT_UpdateOutputToWritten = 2,
				kWRUT_Escape = 4,
				kWRUT_CRLF = 8,
				kWRUT_OnlyOneChar = 0x10,
				kWRUT_EscapeFormatMask = 0xE0, // bits 0x20 to 0x80 are reserved for a format number to be used with numeric escape (max 8 formats)
				kWRUT_SpecialProcessingMask = 0x700,	// to unicode only
				kWRUT_MapRTLDigitsToF0xx = 0x1000,	// to unicode only
				kWRUT_ReversedOrder = 0x2000,			// to unicode only, to analyze AXt streams with multiglyph shapes in the reverse order (of against dir boxes)
				kWRUT_PreserveLineEndings = 0x4000,
				kWRUT_LittleEndian = 0x8000				// when relevant (UTF16)
			 } WRUT_TranscodingMode;

typedef enum { kWRUT_SkipFormat = 0 << 5, // from unicode only
			   kWRUT_AngleHEXFormat = 1 << 5,			
			   kWRUT_Angle0xHEXFormat = 2 << 5,		
			   kWRUT_QuestionMarksFormat = 3 << 5,  // from unicode only
			   kWRUT_BreakOnMissingChar = 4 << 5,  // from unicode only
			   kWRUT_NullCharFormat = 5 << 5  // from unicode only
			 } WRUT_TranscodingFormat;

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif //__WRUnicodeTranslator__
