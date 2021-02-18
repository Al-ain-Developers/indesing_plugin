//========================================================================================
//  
//  File: OptycaTypes.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2007 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#ifndef __OptycaTypes__
#define __OptycaTypes__

#include "WRConfig.h"
#include "WRDefines.h"

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

enum { kNominal,kIsolated,kInitial,kMedial,kFinal,kLastAllograph };

typedef enum {	kNativeDigits = -1,
				kDefaultDigits,
				kArabicDigits,
				kHindiDigits,
				kFarsiDigits,
				kFullFarsiDigits,
				kThaiDigits, 
				kLaoDigits, 
				kDevanagariDigits,
				kBengaliDigits,
				kGurmukhiDigits,
				kGujaratiDigits,
				kOriyaDigits,
				kTamilDigits,
				kTeluguDigits,
				kKannadaDigits,
				kMalayalamDigits,
				kTibetanDigits,
				kKhmerDigits,
				kBurmeseDigits,
				kArabicDigitsRTL,
				kLastDigitSet } WRDigitSet;
typedef enum { kWRCapNormal = 0, kWRCapSmallLowercase, kWRCapAll, kWRCapSmallEverything, kWRSmallAll, kWRTitleCap } WRCapitalizeMode;
typedef enum { kWRPosNormal = 0, kWRPosSuperscript, kWRPosSubscript, kWRPosSuperior, kWRPosInferior, kWRPosNumerator, kWRPosDenominator } WRPositionMode;

typedef enum { 
	kWRGlyphClass_Unknown,
	kWRGlyphClass_ArabicDot,
	kWRGlyphClass_ArabicHamza,
	kWRGlyphClass_ArabicSpacingHamza,
	kWRGlyphClass_ArabicEnhancer, // shadda
	kWRGlyphClass_ArabicVowel,
	kWRGlyphClass_ArabicPunct,
	kWRGlyphClass_ArabicOrnament,
	kWRGlyphClass_HebrewNikud,
	kWRGlyphClass_HebrewDot,
	kWRGlyphClass_HebrewTeamim
}WRGlyphClass;


#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
