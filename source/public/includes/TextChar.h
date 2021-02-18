//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextChar.h $
//  
//  Owner: EricM
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
#ifndef __TEXTCHAR__
#define __TEXTCHAR__

#include "BaseType.h"

// these are all unicode values:

const textchar kTextChar_Null				= 0x0000;

//const textchar kTextChar_Unused			= 0x0001;
//const textchar kTextChar_Unused			= 0x0002;
const textchar kTextChar_BreakRunInStyle	= 0x0003;
const textchar kTextChar_FootnoteMarker	= 0x0004;
const textchar kTextChar_EndnoteMarker  = 0x0005;
//const textchar kTextChar_Unused			= 0x0006;

const textchar kTextChar_IndentToHere		= 0x0007;
const textchar kTextChar_RightAlignedTab	= 0x0008;
const textchar kTextChar_Tab				= 0x0009;

const textchar kTextChar_LF					= 0x000A;
const textchar kTextChar_SoftCR				= kTextChar_LF;
//const textchar kTextChar_Unused			= 0x000B;
//const textchar kTextChar_Unused			= 0x000C;
const textchar kTextChar_CR					= 0x000D;
//const textchar kTextChar_Unused			= 0x000E;
//const textchar kTextChar_Unused			= 0x000F;
//const textchar kTextChar_Unused			= 0x0010;
//const textchar kTextChar_Unused			= 0x0011;
//const textchar kTextChar_Unused			= 0x0012;
//const textchar kTextChar_Unused			= 0x0013;
//const textchar kTextChar_Unused			= 0x0014;
//const textchar kTextChar_Unused			= 0x0015;
const textchar kTextChar_Table				= 0x0016;	// table anchor character
const textchar kTextChar_TableContinued		= 0x0017;	// table middle

//const textchar kTextChar_Cancel			= 0x0018;
const textchar kTextChar_PageNumber			= 0x0018;	// kTextChar_Cancel;
const textchar kTextChar_AutoText				= 0x0018;	// kTextChar_Cancel;
//const textchar kTextChar_EndOfMedium		= 0x0019;
const textchar kTextChar_SectionName		= 0x0019;	// kTextChar_EndOfMedium;
//const textchar kTextChar_Substitute		= 0x001A;
const textchar kTextChar_NonRomanSpecialGlyph = 0x001A;	// kTextChar_Substitute;
const textchar kTextChar_Space				= 0x0020;

const textchar kTextChar_ExclamationMark	= 0x0021;
const textchar kTextChar_QuotationMark 		= 0x0022;	// U+0022, QUOTATION MARK, The Unicode Standard 2.0, 7-7
const textchar kTextChar_NumberSign			= 0x0023;
const textchar kTextChar_DollarSign			= 0x0024;
const textchar kTextChar_PercentSign		= 0x0025;
const textchar kTextChar_Ampersand			= 0x0026;
const textchar kTextChar_Apostrophe 		= 0x0027;	// U+0027, APOSTROPHE, The Unicode Standard 2.0, 7-7
const textchar kTextChar_LeftParenthesis	= 0x0028;
const textchar kTextChar_RightParenthesis	= 0x0029;
const textchar kTextChar_Asterisk			= 0x002A;
const textchar kTextChar_PlusSign			= 0x002B;
const textchar kTextChar_Comma				= 0x002C;
const textchar kTextChar_HyphenMinus		= 0x002D;
const textchar kTextChar_Period				= 0x002E;
const textchar kTextChar_Solidus			= 0x002F;

const textchar kTextChar_Zero				= 0x0030;		// used for figure space width
const textchar kTextChar_Colon				= 0x003A;
const textchar kTextChar_Semicolon			= 0x003B;
const textchar kTextChar_LessThanSign		= 0x003C;
const textchar kTextChar_EqualsSign			= 0x003D;
const textchar kTextChar_GreaterThanSign	= 0x003E;
const textchar kTextChar_QuestionMark		= 0x003F;

const textchar kTextChar_CommercialAt		= 0x0040;
const textchar kTextChar_LeftSquareBracket	= 0x005B;
const textchar kTextChar_ReverseSolidus		= 0x005C;
const textchar kTextChar_RightSquareBracket	= 0x005D;
const textchar kTextChar_CircumflexAccent	= 0x005E;
const textchar kTextChar_Underscore			= 0x005F;
const textchar kTextChar_GraveAccent		= 0x0060;
const textchar kTextChar_LeftCurlyBracket	= 0x007B;
const textchar kTextChar_RightCurlyBracket	= 0x007D;
const textchar kTextChar_VerticalLine		= 0x007C;
const textchar kTextChar_Tilde				= 0x007E;

const textchar kTextChar_HardSpace		= 0x00A0;		// non-breaking, justifying space.  See u202f
const textchar kTextChar_CentSign			= 0x00A2;
const textchar kTextChar_PoundSign		= 0x00A3;
const textchar kTextChar_CurrencySign		= 0x00A4;
const textchar kTextChar_YenSign			= 0x00A5;
const textchar kTextChar_BrokenBar		= 0x00A6;
const textchar kTextChar_SectionSign		= 0x00A7;
const textchar kTextChar_Diaeresis			= 0x00A8;
const textchar kTextChar_CopyrightSign		= 0x00A9;
const textchar kTextChar_LeftDblAngQuote	= 0x00AB;	// The Unicode Standard 2.0, 7-11
const textchar kTextChar_NotSign			= 0x00AC;
const textchar kTextChar_DiscretionaryHyphen= 0x00AD;
const textchar kTextChar_RegisteredSign		= 0x00AE;
const textchar kTextChar_Macron				= 0x00AF;
const textchar kTextChar_DegreeSign			= 0x00B0;
const textchar kTextChar_SuperscriptTwo		= 0x00B2;
const textchar kTextChar_PilchrowSign		= 0x00B6;	// paragraph
const textchar kTextChar_MiddleDot			= 0x00B7;
const textchar kTextChar_SuperscriptOne		= 0x00B9;
const textchar kTextChar_RightDblAngQuote	= 0x00BB;	// The Unicode Standard 2.0, 7-11
const textchar kTextChar_EssZed				= 0x00DF;
const textchar kTextChar_LetterYWithDiaeresis	= 0x00FF;
const textchar kTextChar_CapIwithDotAbove	= 0x0130;
const textchar kTextChar_Caron				= 0x02C7;		// hacek

const textchar kTextChar_GreekOmega			= 0x03A9;
const textchar kTextChar_GreekPi				= 0x03C0;

// Hebrew Characters
const textchar kTextChar_HebrewMaqaf			= 0x05BE; 	// The Unicode Standard 2.0, 7-66
const textchar kTextChar_HebrewGeresh		= 0x05F3; 	// The Unicode Standard 2.0, 7-66
const textchar kTextChar_HebrewGershayim		= 0x05F4; 	// The Unicode Standard 2.0, 7-66
const textchar kTextChar_HebrewSofPasuk		= 0x05C3; 	// The Unicode Standard 2.0, 7-66

// Arabic punctuation
const textchar kTextChar_ArabicComma			= 0x060C; 	// The Unicode Standard 2.0, 7-66
const textchar kTextChar_ArabicSemicolon		= 0x061B; 	// The Unicode Standard 2.0, 7-66
const textchar kTextChar_ArabicQuestionMark	= 0x061F; 	// The Unicode Standard 2.0, 7-66
const textchar kTextChar_ArabicKashida		= 0x0640; 	// The Unicode Standard 2.0, 7-66

const textchar kTextChar_ThaiSaraAa			= 0x0e32;
const textchar kTextChar_ThaiSaraAm			= 0x0e33;
const textchar kTextChar_ThaiNikhahit			=0x0e4d;

const textchar kTextChar_FlushSpace		= 0x2001;	// stole em quad
const textchar kTextChar_EnSpace			= 0x2002;
const textchar kTextChar_EmSpace			= 0x2003;
const textchar kTextChar_ThirdSpace		= 0x2004;
const textchar kTextChar_QuarterSpace		= 0x2005;
const textchar kTextChar_SixthSpace		= 0x2006;
const textchar kTextChar_FigureSpace		= 0x2007;
const textchar kTextChar_PunctuationSpace	= 0x2008;
const textchar kTextChar_ThinSpace		= 0x2009;
const textchar kTextChar_HairSpace		= 0x200A;
const textchar kTextChar_ZeroSpaceBreak	= 0x200B;
//const textchar kTextChar_ZeroSpaceNoBreak	= 0xFEFF;

const textchar kTextChar_ZeroWidthNonJoiner	= 0x200C;
const textchar kTextChar_ZeroWidthJoiner		= 0x200D;
const textchar kTextChar_LeftToRightMark		= 0x200E;
const textchar kTextChar_RightToLeftMark		= 0x200F;

const textchar kTextChar_UnicodeHyphen	= 0x2010;
const textchar kTextChar_NoBreakHyphen	= 0x2011;
const textchar kTextChar_FigureDash		= 0x2012;
const textchar kTextChar_EnDash			= 0x2013;
const textchar kTextChar_EmDash			= 0x2014;
const textchar kTextChar_HorizontalBar		= 0x2015;

const textchar kTextChar_LeftDoubleQuotationMark	= 0x201C;	// U+201C, LEFT DOUBLE QUOTATION MARK, The Unicode Standard 2.0, 7-155
const textchar kTextChar_RightDoubleQuotationMark	= 0x201D;	// U+201D, RIGHT DOUBLE QUOTATION MARK, The Unicode Standard 2.0, 7-156
const textchar kTextChar_LeftSingleQuotationMark	= 0x2018;	// U+2018, LEFT SINGLE QUOTATION MARK, The Unicode Standard 2.0, 7-155
const textchar kTextChar_RightSingleQuotationMark			= 0x2019;	// U+2019, RIGHT SINGLE QUOTATION MARK, The Unicode Standard 2.0, 7-155
const textchar kTextChar_DoubleLow9QuotationMark			= 0x201E;	// U+201E,  DOUBLE LOW-9 QUOTATION MARK, The Unicode Standard 2.0, 7-156
const textchar kTextChar_DoubleHighReversed9QuotationMark	= 0x201F;	// U+201F,  DOUBLE HIGH-REVERSED-9 QUOTATION MARK, The Unicode Standard 2.0, 7-156
const textchar kTextChar_SingleLow9QuotationMark				= 0x201A;	// U+201A,  SINGLE LOW-9 QUOTATION MARK, The Unicode Standard 2.0, 7-155
const textchar kTextChar_SingleHighReversed9QuotationMark	= 0x201B;	// U+201B,  SINGLE HIGH-REVERSED-9 QUOTATION MARK, The Unicode Standard 2.0, 7-155

const textchar kTextChar_Dagger				= 0x2020;
const textchar kTextChar_DoubleDagger		= 0x2021;
const textchar kTextChar_Bullet				= 0x2022;
const textchar kTextChar_TwoDotLeader		= 0x2025;
const textchar kTextChar_Ellipse				= 0x2026;		// Actually, it's "ellipsis"
const textchar kTextChar_Ellipsis				= 0x2026;
const textchar kTextChar_Point					= 0x2027;

const textchar kTextChar_LineSeparator		= 0x2028;
const textchar kTextChar_ParagraphSeparator	= 0x2029;

const textchar kTextChar_LeftToRightEmbedding		= 0x202A;
const textchar kTextChar_RightToLeftEmbedding		= 0x202B;
const textchar kTextChar_PopDirectionalFormatting	= 0x202C;
const textchar kTextChar_LeftToRightOverride		= 0x202D;
const textchar kTextChar_RightToLeftOverride		= 0x202E;

const textchar kTextChar_NarrowNoBreakSpace	= 0x202F;		// non-justifying non-breaking space
const textchar kTextChar_PerMileSign			= 0x2030;
const textchar kTextChar_Prime				= 0x2032;
const textchar kTextChar_DoublePrime			= 0x2033;

const textchar kTextChar_LeftSingleAngQuote	= 0x2039;	// The Unicode Standard 2.0
const textchar kTextChar_RightSingleAngQuote	= 0x203A;	// The Unicode Standard 2.0

const textchar kTextChar_MedMathSpace		= 0x205F;	// 4/18 EM
const textchar kTextChar_WordJoiner			= 0x2060;
const textchar kTextChar_InvisibleSeparator	= 0x2063;

const textchar kTextChar_WonSign				= 0x20A9;	// korean currency

	// many of these are for the faked mappings to the symbol font!
const textchar kTextChar_DegreeCelsius		= 0x2103;
const textchar kTextChar_DegreeFahrenheit		= 0x2109;
const textchar kTextChar_TrademarkSign		= 0x2122;
const textchar kTextChar_OhmSymbol			= 0x2126;
const textchar kTextChar_RightArrow			= 0x2192;
const textchar kTextChar_DownArrow			= 0x2193;
const textchar kTextChar_PartialDiff		= 0x2202;
const textchar kTextChar_MathDelta			= 0x2206;
const textchar kTextChar_Product			= 0x220F;
const textchar kTextChar_Summation			= 0x2211;
const textchar kTextChar_Radical			= 0x221A;
const textchar kTextChar_Integral			= 0x222B;
const textchar kTextChar_ApproxEqual		= 0x2248;
const textchar kTextChar_NotEqual			= 0x2260;
const textchar kTextChar_LessEqual			= 0x2264;
const textchar kTextChar_GreaterEqual		= 0x2265;
const textchar kTextChar_Infinity			= 0x221E;
const textchar kTextChar_Diamond			= 0x25CA;
const textchar kTextChar_DottedCircle		= 0x25CC; 

const textchar kTextChar_WRPointedIndex		= 0x261E;
const textchar kTextChar_WDPointedIndex		= 0x261F;
const textchar kTextChar_MusicSharpSign		= 0x266F;
const textchar kTextChar_CheckmarkSign		= 0x2713;

//CJK support
const textchar kTextChar_IdeographicSpace	= 0x3000;
const textchar kTextChar_CJKStart			= kTextChar_IdeographicSpace;
const textchar kTextChar_ClosingMark        = 0x3006;
const textchar kTextChar_CJKPostalMarkFace	= 0x3020;
const textchar kTextChar_CJKCompatibilityEnd = 0x33FF;
const textchar kTextChar_CJKHalfFullStart	= 0xFF01;
const textchar kTextChar_CJKHalfIdeographicFullStop = 0xFF61;
const textchar kTextChar_CJKHalfIdeographicComma = 0xFF64;
const textchar kTextChar_CJKHalfFullEnd		= 0xFF9F;

//CJK symbols and punctuation

const textchar kTextChar_IdeographicComma				= 0x3001;
const textchar kTextChar_IdeographicFullStop			= 0x3002;
const textchar kTextChar_IterationMark					= 0x3005;
const textchar kTextChar_LeftAngleBracket				= 0x3008;
const textchar kTextChar_RightAngleBracket				= 0x3009;
const textchar kTextChar_LeftDoubleAngleBracket			= 0x300A;
const textchar kTextChar_RightDoubleAngleBracket		= 0x300B;
const textchar kTextChar_LeftCornerBracket				= 0x300C;
const textchar kTextChar_RightCornerBracket				= 0x300D;
const textchar kTextChar_LeftWhiteCornerBracket			= 0x300E;
const textchar kTextChar_RightWhiteCornerBracket		= 0x300F;
const textchar kTextChar_LeftBlackLenticularBracket		= 0x3010;
const textchar kTextChar_RightBlackLenticularBracket	= 0x3011;
const textchar kTextChar_PostalMark						= 0x3012;
const textchar kTextChar_leftTortoiseShellBracket		= 0x3014;
const textchar kTextChar_RightTortoiseShellBracket		= 0x3015;
const textchar kTextChar_LeftWhiteLenticularBracket		= 0x3016;
const textchar kTextChar_RightWhiteLenticularBracket	= 0x3017;
const textchar kTextChar_leftWhiteTortoiseShellBracket	= 0x3018;
const textchar kTextChar_RightWhiteTortoiseShellBracket	= 0x3019;
const textchar kTextChar_LeftWhiteSquareBracket			= 0x301A;
const textchar kTextChar_RightWhiteSquareBracket		= 0x301B;
const textchar kTextChar_WaveDash						= 0x301C;

//Japanese Kinsoku characters
const textchar kTextChar_HiraganaSmallA				= 0x3041;
const textchar kTextChar_HiraganaSmallI				= 0x3043;
const textchar kTextChar_HiraganaSmallU				= 0x3045;
const textchar kTextChar_HiraganaSmallE				= 0x3047;
const textchar kTextChar_HiraganaSmallO				= 0x3049;
const textchar kTextChar_HiraganaSmallTsu			= 0x3063;
const textchar kTextChar_HiraganaSmallYa			= 0x3083;
const textchar kTextChar_HiraganaSmallYu			= 0x3085;
const textchar kTextChar_HiraganaSmallYo			= 0x3087;
const textchar kTextChar_HiraganaSmallWa			= 0x308E;
const textchar kTextChar_KatakanaHiraganaVoicedSoundMark	= 0x309B;
const textchar kTextChar_KatakanaHiraganaSemiVoicedSoundMark= 0x309C;
const textchar kTextChar_HiraganaIterationMark			= 0x309D;
const textchar kTextChar_HiraganaVoicedIterationMark	= 0x309E;

const textchar kTextChar_KatakanaSmallA				= 0x30A1;
const textchar kTextChar_KatakanaSmallI				= 0x30A3;
const textchar kTextChar_KatakanaSmallU				= 0x30A5;
const textchar kTextChar_KatakanaSmallE				= 0x30A7;
const textchar kTextChar_KatakanaSmallO				= 0x30A9;
const textchar kTextChar_KatakanaGa					= 0x30AC;
const textchar kTextChar_KatakanaGi					= 0x30AE;
const textchar kTextChar_KatakanaGu					= 0x30B0;
const textchar kTextChar_KatakanaGe					= 0x30B2;
const textchar kTextChar_KatakanaGo					= 0x30B4;
const textchar kTextChar_KatakanaSa					= 0x30B5;
const textchar kTextChar_KatakanaZa					= 0x30B6;
const textchar kTextChar_KatakanaZi					= 0x30B8;
const textchar kTextChar_KatakanaZu					= 0x30BA;
const textchar kTextChar_KatakanaZe					= 0x30BC;
const textchar kTextChar_KatakanaZo					= 0x30BE;
const textchar kTextChar_KatakanaTa					= 0x30BF;
const textchar kTextChar_KatakanaDa					= 0x30C0;
const textchar kTextChar_KatakanaTi					= 0x30C1;
const textchar kTextChar_KatakanaDi					= 0x30C2;
const textchar kTextChar_KatakanaTu					= 0x30C4;
const textchar kTextChar_KatakanaDu					= 0x30C5;
const textchar kTextChar_KatakanaTe					= 0x30C6;
const textchar kTextChar_KatakanaDe					= 0x30C7;
const textchar kTextChar_KatakanaTo					= 0x30C8;
const textchar kTextChar_KatakanaDo					= 0x30C9;
const textchar kTextChar_KatakanaSmallTsu			= 0x30C3;
const textchar kTextChar_KatakanaHa					= 0x30CF;
const textchar kTextChar_KatakanaBa					= 0x30D0;
const textchar kTextChar_KatakanaPa					= 0x30D1;
const textchar kTextChar_KatakanaHi					= 0x30D2;
const textchar kTextChar_KatakanaBi					= 0x30D3;
const textchar kTextChar_KatakanaPi					= 0x30D4;
const textchar kTextChar_KatakanaHu					= 0x30D5;
const textchar kTextChar_KatakanaBu					= 0x30D6;
const textchar kTextChar_KatakanaPu					= 0x30D7;
const textchar kTextChar_KatakanaHe					= 0x30D8;
const textchar kTextChar_KatakanaBe					= 0x30D9;
const textchar kTextChar_KatakanaPe					= 0x30DA;
const textchar kTextChar_KatakanaHo					= 0x30DB;
const textchar kTextChar_KatakanaBo					= 0x30DC;
const textchar kTextChar_KatakanaPo					= 0x30DD;
const textchar kTextChar_KatakanaSmallYa			= 0x30E3;
const textchar kTextChar_KatakanaSmallYu			= 0x30E5;
const textchar kTextChar_KatakanaSmallYo			= 0x30E7;
const textchar kTextChar_KatakanaSmallWa			= 0x30EE;
const textchar kTextChar_KatakanaWo					= 0x30F2;
const textchar kTextChar_KatakanaVu					= 0x30F4;
const textchar kTextChar_KatakanaVa					= 0x30F7;
const textchar kTextChar_KatakanaVi					= 0x30F8;
const textchar kTextChar_KatakanaVe					= 0x30F9;
const textchar kTextChar_KatakanaVo					= 0x30FA;
const textchar kTextChar_KatakanaMiddleDot			= 0x30FB;
const textchar kTextChar_KatakanaSmallKa			= 0x30F5;
const textchar kTextChar_KatakanaSmallKe			= 0x30F6;
const textchar kTextChar_KatakanaHiraganaProlongedSoundMark	= 0x30FC;
const textchar kTextChar_KatakanaIterationMark				= 0x30FD;
const textchar kTextChar_KatakanaVoicedIterationMark		= 0x30FE;

// ideographs
const textchar kTextChar_CJKIdeographExtensionAStart	= 0x3400;
const textchar kTextChar_CJKIdeographExtensionAEnd	= 0x4DB5;
const textchar kTextChar_CJKUnifiedIdeographsStart	= 0x4E00;
const textchar kTextChar_CJKUnifiedIdeographsEnd	= 0x9FA5;

// surrogates
const textchar kTextChar_HighSurrogateStart			= 0xD800;	// includes private use 0xDB80 - 0xDBFF
const textchar kTextChar_HighSurrogateEnd			= 0xDBFF;
const textchar kTextChar_LowSurrogateStart			= 0xDC00;
const textchar kTextChar_LowSurrogateEnd			= 0xDFFF;

const textchar kTextChar_CJKCompatibilityIdeographsStart	= 0xF900;
const textchar kTextChar_CJKCompatibilityIdeographsEnd		= 0xFA6A;

const textchar kTextChar_CJKEnd						= 0xFAFF; // this is misleading: there are non-CJK things in the range below this

// other stuff
const textchar kTextChar_SymbolPi			= 0xF636;

const textchar kTextChar_ffLigature			= 0xFB00;
const textchar kTextChar_fiLigature			= 0xFB01;
const textchar kTextChar_flLigature			= 0xFB02;
const textchar kTextChar_ffiLigature		= 0xFB03;
const textchar kTextChar_fflLigature		= 0xFB04;

//const textchar kTextChar_AppleSymbol		= 0xFDFF;
// I was told that the apple symbol was FDFF, but CoolType was calling it E0F0.

// Unicode Variation Selectors
const textchar kTextChar_VariationSelector1				= 0xFE00;
const textchar kTextChar_VariationSelector2				= 0xFE01;
const textchar kTextChar_VariationSelector3				= 0xFE02;
const textchar kTextChar_VariationSelector4				= 0xFE03;
const textchar kTextChar_VariationSelector5				= 0xFE04;
const textchar kTextChar_VariationSelector6				= 0xFE05;
const textchar kTextChar_VariationSelector7				= 0xFE06;
const textchar kTextChar_VariationSelector8				= 0xFE07;
const textchar kTextChar_VariationSelector9				= 0xFE08;
const textchar kTextChar_VariationSelector10			= 0xFE09;
const textchar kTextChar_VariationSelector11			= 0xFE0A;
const textchar kTextChar_VariationSelector12			= 0xFE0B;
const textchar kTextChar_VariationSelector13			= 0xFE0C;
const textchar kTextChar_VariationSelector14			= 0xFE0D;
const textchar kTextChar_VariationSelector15			= 0xFE0E;
const textchar kTextChar_VariationSelector16			= 0xFE0F;

// Vertical forms
const textchar kTextChar_VerticalTwoDotLeader			= 0xFE30;
const textchar kTextChar_VerticalEmDash					= 0xFE31;
const textchar kTextChar_VerticalEnDash					= 0xFE32;
const textchar kTextChar_VerticalLowLine				= 0xFE33;
const textchar kTextChar_VerticalWavyLowLine			= 0xFE34;
const textchar kTextChar_VerticalLeftParenthesis		= 0xFE35;
const textchar kTextChar_VerticalRIghtParenthesis		= 0xFE36;
const textchar kTextChar_VerticalLeftCurlyBracket		= 0xFE37;
const textchar kTextChar_VerticalRightCurlyBracket		= 0xFE38;
const textchar kTextChar_VerticalLeftTortoiseShell		= 0xFE39;
const textchar kTextChar_VerticalRightTortoiseShell		= 0xFE3A;
const textchar kTextChar_VerticalLeftBlackLenticularBracket		= 0xFE3B;
const textchar kTextChar_VerticalRightBlackLenticularBracket	= 0xFE3C;
const textchar kTextChar_VerticalLeftDoubleAngleBracket			= 0xFE3D;
const textchar kTextChar_VerticalRightDoubleAngleBracket		= 0xFE3E;
const textchar kTextChar_VerticalLeftAngleBracket				= 0xFE3F;
const textchar kTextChar_VerticalRightAngleBracket				= 0xFE40;
const textchar kTextChar_VerticalLeftCornerBracket				= 0xFE41;
const textchar kTextChar_VerticalRightCornerBracket				= 0xFE42;
const textchar kTextChar_VerticalLeftWhiteCornerBracket			= 0xFE43;
const textchar kTextChar_VerticalRightWhiteCornerBracket		= 0xFE44;

const textchar kTextChar_ZeroSpaceNoBreak						= 0xFEFF;

const textchar kTextChar_FullWidthExclamationMark		= 0xFF01;
const textchar kTextChar_FWAsciiBegin					= kTextChar_FullWidthExclamationMark;
const textchar kTextChar_FullWidthDollarSign			= 0xFF04;
const textchar kTextChar_FullWidthPercentSign			= 0xFF05;
const textchar kTextChar_FullWidthLeftParenthesis		= 0xFF08;
const textchar kTextChar_FullWidthRightParenthesis		= 0xFF09;
const textchar kTextChar_FullWidthComma					= 0xFF0C;
const textchar kTextChar_FullWidthStop					= 0xFF0E;
const textchar kTextChar_FullWidthDigitZero				= 0xFF10;
const textchar kTextChar_FullWidthDigitNine				= 0xFF19;
const textchar kTextChar_FullWidthColon					= 0xFF1A;
const textchar kTextChar_FullWidthSemiColon				= 0xFF1B;
const textchar kTextChar_FullWidthQuestionMark			= 0xFF1F;
const textchar kTextChar_FullWidthCommercialAt			= 0xFF20;
const textchar kTextChar_FullWidthLeftSqaureBracket		= 0xFF3B;
const textchar kTextChar_FullWidthRightSqaureBracket	= 0xFF3D;
const textchar kTextChar_FullWidthLeftCurlyBracket		= 0xFF5B;
const textchar kTextChar_FullWidthRightCurlyBracket		= 0xFF5D;
const textchar kTextChar_FWAsciiEnd						= 0xFF5F;

const textchar kTextChar_HWKatakanaWo					= 0xFF66;
const textchar kTextChar_HalfWidthKatakanaBegin			= kTextChar_HWKatakanaWo;
const textchar kTextChar_HalfWidthKatakanaU				= 0xFF73;
const textchar kTextChar_HalfWidthKatakanaKa			= 0xFF76;
const textchar kTextChar_HalfWidthKatakanaKi			= 0xFF77;
const textchar kTextChar_HalfWidthKatakanaKu			= 0xFF78;
const textchar kTextChar_HalfWidthKatakanaKe			= 0xFF79;
const textchar kTextChar_HalfWidthKatakanaKo			= 0xFF7A;
const textchar kTextChar_HalfWidthKatakanaSa			= 0xFF7B;
const textchar kTextChar_HalfWidthKatakanaSi			= 0xFF7C;
const textchar kTextChar_HalfWidthKatakanaSu			= 0xFF7D;
const textchar kTextChar_HalfWidthKatakanaSe			= 0xFF7E;
const textchar kTextChar_HalfWidthKatakanaSo			= 0xFF7F;
const textchar kTextChar_HalfWidthKatakanaTa			= 0xFF80;
const textchar kTextChar_HalfWidthKatakanaTi			= 0xFF81;
const textchar kTextChar_HalfWidthKatakanaTu			= 0xFF82;
const textchar kTextChar_HalfWidthKatakanaTe			= 0xFF83;
const textchar kTextChar_HalfWidthKatakanaTo			= 0xFF84;
const textchar kTextChar_HalfWidthKatakanaHa			= 0xFF8A;
const textchar kTextChar_HalfWidthKatakanaHi			= 0xFF8B;
const textchar kTextChar_HalfWidthKatakanaHu			= 0xFF8C;
const textchar kTextChar_HalfWidthKatakanaHe			= 0xFF8D;
const textchar kTextChar_HalfWidthKatakanaHo			= 0xFF8E;
const textchar kTextChar_HalfWidthKatakanaEnd			= 0xFF9D;
const textchar kTextChar_HalfWidthKatakanaVoicedMark	= 0xFF9E;
const textchar kTextChar_HalfWidthKatakanaSemiVoicedMark = 0xFF9F;
const textchar kTextChar_FullWidthCentSign				= 0xFFE0;
const textchar kTextChar_FullWidthYenSign				= 0xFFE5;
const textchar kTextChar_HalfWidthKatakanaWa			= 0xFF9C;
const textchar kTextChar_ObjectReplacementCharacter		= 0xFFFC;	// Placeholder in text for an otherwise unspecified object
const textchar kTextChar_Inline = kTextChar_ObjectReplacementCharacter;
const textchar kTextChar_ReplacementCharacter			= 0xFFFD;	// an incoming character whose value is unrepresentable in Unicode
const textchar kTextChar_SpecialGlyph = kTextChar_ReplacementCharacter;
const textchar kTextChar_ByteOrderingCharacter			= 0xFFFE;		// either FFFE or FEFF depending on byte order
const textchar kTextChar_InvalidCharacter				= 0xFFFF;

// private use area. Corporate grows down, user grows up.
// I guess we're corporate... The font group, apple, etc are using the private area too.
// Japanese gaiji characters use this area!! But becuase of a current bug in CoolType's
// unicode conversion this is not currenly conflicting. CoolType converts sjis F040 to E040 which
// is wrong. It should convert sjis F040 to E000. - mvogel 4/11/00
const textchar kTextChar_PrivateZoneStart = 0xE000;
const textchar kTextChar_PrivateZoneEnd = 0x0F8FF;

// These constants were used to represent special values in the document through Hotaka build 79
const textchar kOBSOLETETextChar_Inline = 0xE000;
const textchar kOBSOLETETextChar_SpecialGlyph = 0xE001;	// glyph specified by attributes
const textchar kOBSOLETETextChar_PageNumber = 0xE002;		// in PM: #define CH_PAGE_NUMBER 0x18 // from memo to Microsoft.
const textchar kOBSOLETETextChar_SectionName = 0xE003;
const textchar kOBSOLETETextChar_NonRomanSpecialGlyph = 0xE004;	// non-Roman glyph specified by attributes

// These are used only by Find/Change, and are not stored in a document
const textchar kTextChar_AnyCharacter = 0xE006;		// wildcard used in search and replace for any character
const textchar kTextChar_AnyLetter = 0xE007;		// wildcard used in search and replace for any roman alphabet (a-z, A-Z)
const textchar kTextChar_AnyDigit = 0xE008;			// wildcard used in search and replace for any roman digit (0 to 9)
const textchar kTextChar_WhiteSpace = 0xE009;		// wildcard used in search and replace for any type of space
const textchar kTextChar_AnyKanji = 0xE00A;			// wildcard used in search for any Japanese Kanji (Chinese-style) character
const textchar kTextChar_ColumnBreak = 0xE00B;		// used in xml export
const textchar kTextChar_PageBreak = 0xE00C;		// used in xml export
const textchar kTextChar_FrameBoxBreak = 0xE00D;
const textchar kTextChar_OddPageBreak = 0xE00E;
const textchar kTextChar_EvenPageBreak = 0xE00F;
const textchar kTextChar_AnySingleQuote = 0xE010;
const textchar kTextChar_AnyDoubleQuote = 0xE011;
const textchar kTextChar_PageCountVariable = 0xE012;
const textchar kTextChar_ChapterNumberVariable = 0xE013;
const textchar kTextChar_CreationDateVariable = 0xE014;
const textchar kTextChar_ModificationDateVariable = 0xE015;
const textchar kTextChar_FileNameVariable = 0xE016;
const textchar kTextChar_OutputDateVariable = 0xE017;
const textchar kTextChar_RunningHeaderPSVariable = 0xE018;
const textchar kTextChar_CustomTextVariable = 0xE019;
const textchar kTextChar_AnyVariable = 0xE020;
const textchar kTextChar_AnyPageNumber = 0xE021;
const textchar kTextChar_NextPageNumber = 0xE022;
const textchar kTextChar_PreviousPageNumber = 0xE023;
const textchar kTextChar_AnyBreak = 0xE024;
const textchar kTextChar_CurrentPageNumber = 0xE025;
const textchar kTextChar_CBContentsFormatted = 0xE026;    // formatted clipboard contents
const textchar kTextChar_CBContentsUnformatted = 0xE027;  // unformatted clipboard contents
const textchar kTextChar_DoubleLeftQuote = 0xE028;		// Language dependent double left quote
const textchar kTextChar_DoubleRightQuote = 0xE029;		// Language dependent double right quote
const textchar kTextChar_SingleLeftQuote = 0xE02A;		// Language dependent single left quote
const textchar kTextChar_SingleRightQuote = 0xE02B;		// Language dependent single right quote
const textchar kTextChar_IndexMarker = 0xE02C;
const textchar kTextChar_RunningHeaderCSVariable = 0xE02D;
const textchar kTextChar_DoubleStraightQuote = 0xE02E;
const textchar kTextChar_SingleStraightQuote = 0xE02F;
const textchar kTextChar_MetadataCaptionVariable = 0xE030;

//These are used only by Style Sets and not stored in a document
const textchar kTextChar_StyleGroupPathSeparator = 0xE00B;	// character used to separate difference component of a style set path.
const textchar kTextChar_ScriptStylePathSeparator = kTextChar_Colon;


//================================================================================
// Text character classification functions
//================================================================================

typedef bool16 (*CharacterClassifierFcn)(textchar c);

#pragma export on

/** Here are some utility functions specific to the way we handle characters. */
namespace TextChar {

	/** @return the low-ascii characters that have meaning to InDesign.
		includes both standard values like "tab", "carriage return" and
		special ones like "IndentToHere", "Table" */
	PUBLIC_DECL bool16 IsK2SpecificChar(const UTF32TextChar& c);

	/** We are free to use otherwise unspecified characters to represent objects
		and unspecifiable characters */
	inline bool16 IsIllegalControlChar(const UTF32TextChar& n)
		{ return (n < kTextChar_Space && !IsK2SpecificChar(n)); }
}


#ifdef MACINTOSH
#ifdef __MACH__
extern "C" int wcsicmp (const wchar_t *s1, const wchar_t *s2);
extern "C" int stricmp (const char *s1, const char *s2);
#else
PUBLIC_DECL int wcsicmp (const wchar_t *s1, const wchar_t *s2);
PUBLIC_DECL int stricmp (const char *s1, const char *s2);
#endif

PUBLIC_DECL int strnicmp (const char *s1, const char *s2, int count);
#endif


#pragma export off

#endif
