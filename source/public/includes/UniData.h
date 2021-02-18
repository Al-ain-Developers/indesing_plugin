//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UniData.h $
//  
//  Owner: emenning
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
#ifndef __Unidata__
#define __Unidata__


// format bits are BBBB | CCCC | KKKK | SSSS
// B ==> bits for additional classification
// C ==> character classification
// S ==> classification subclass
// K ==> extra
enum {	kUnidata_Mark = 0x0100,
		kUnidata_MarkArabic = 0x010F,
		kUnidata_MarkHebrew = 0x0105,

		kUnidata_Number = 0x0200,
//			kUnidata_NumberUpper = 0x0201, kUnidata_NumberLower = 0x0202,		roman numerals ??

		kUnidata_Space = 0x0300,
			kUnidata_LineBreak = 0x0301, kUnidata_ParagraphBreak = 0x0302, kUnidata_ZeroSpace = 0x0304,

		kUnidata_Other = 0x0400,

		kUnidata_Letter = 0x0500, kUnidata_LetterUpper = 0x0501, kUnidata_LetterLower = 0x0502,
			kUnidata_LetterTitle = 0x0504, kUnidata_LetterModifier = 0x0508,
			kUnidata_CJKHiragana = 0x0509, kUnidata_CJKKatakana = 0x050A,
			kUnidata_CJKIdeograph = 0x050B,
			kUnidata_CJKBopomofo = 0x050C,
			kUnidata_CJKHangul = 0x050D, kUnidata_CJKJamo = 0x050E,
			kUnidata_LetterArabic = 0x050F,
			kUnidata_LetterHebrew = 0x0505,

		kUnidata_Punctuation = 0x0600, kUnidata_PunctuationDash = 0x0601,
			kUnidata_PunctuationOpen = 0x0602, kUnidata_PunctuationClose = 0x0603,
			kUnidata_PunctuationInitialQuote = 0x0604, kUnidata_PunctuationFinalQuote = 0x0605,
			kUnidata_PunctuationArabic = 0x060F,
			kUnidata_PunctuationDashArabic = 0x060E,
			kUnidata_PunctuationOpenArabic = 0x060D,
			kUnidata_PunctuationCloseArabic = 0x060C,
			kUnidata_PunctuationHebrew = 0x0605, // 2007/02/16 mhmh: same as kUnidata_PunctuationFinalQuote ???
			kUnidata_PunctuationDashHebrew = 0x0606,
			kUnidata_PunctuationOpenHebrew = 0x0607,
			kUnidata_PunctuationCloseHebrew = 0x0608,

		kUnidata_Symbol = 0x0700, kUnidata_SymbolMath = 0x0701, kUnidata_SymbolCurrency = 0x0702,
		kUnidata_SymbolArabic = 0x070F,
		kUnidata_SymbolHebrew = 0x0705,

		kUnidataBit_Wide = 0x1000,
		kUnidataBit_Narrow = 0x2000,
		kUnidataBit_Vertical = 0x4000,
		kUnidataBit_BaseChar = 0x8000,

		kUnidataBit_BaseCharIsAlternate = 0x0010,
			kUnidataBit_AlternateChar = 0x8010,

		kUnidataMask_Subclass = 0x000F,
		kUnidataMask_Extra = 0x00F0,
		kUnidataMask_Class = 0x0F00,
		kUnidataMask_Bits = 0xF000
};


// format 0 ==> whole table is 1 flag  e.g. { kUnidataFormat0, kUnidata_Symbol };
// format 1 ==> whole table has 256 flags e.g. { kUnidataFormat1, kUnidata_Symbol, kUnidata_Punctuation... };
// format 2 ==> whole table has 256 flags, 256 case alternates (upper & lower combined)
// format 3 ==> 256 flags & 256 width alternates (wide or narrow variant)
// format 4 ==> 256 flags, 256 case alternates, 256 width alternates
//
// currently having both a capital AND a lower alternate for 1 letter or both a wide & narrow
// alternate for 1 letter is NOT supported
//
enum { kUnidataFormat0, kUnidataFormat1, kUnidataFormat2,
		kUnidataFormat3, kUnidataFormat4 };

extern const unsigned short* kUnicodeTable[256];


#endif
		// __Unidata__
