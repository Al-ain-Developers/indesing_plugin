//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UnicodeClass.h $
//  
//  Owner:
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
#ifndef __UnicodeClass__
#define __UnicodeClass__

#include "UniData.h"
#include "TextChar.h"

#pragma export on

/**
UnicodeClass is used for classification of Unicode characters used in InDesign.
It is primarily a wrapper around the ICU library.
@see IGlyphUtils.h for GetUnicodeName.
*/
class UnicodeClass
{
	public:

		/** Character Type.
			Bit-field used to classify characters into variable classes for processing. */
		enum CharacterType {
			kCharacterType_Unknown = 0,
			kCharacterType_DoubleByte = 0x0001,
			kCharacterType_Roman = 0x0002,
			kCharacterType_Upper = 0x0004,
			kCharacterType_Numeric = 0x0008,
			kCharacterType_Hiragana = 0x0010,
			kCharacterType_Katakana = 0x0020,
			kCharacterType_SmallKana = 0x0040,
			kCharacterType_Nobashi = 0x0080,
			kCharacterType_Kanji = 0x0100,
			kCharacterType_Symbol = 0x0200,
			kCharacterType_OpenParenthesis = 0x0400,
			kCharacterType_CloseParenthesis = 0x0800,
			kCharacterType_Period = 0x1000,
			kCharacterType_Comma= 0x2000,
			kCharacterType_MiddlePunc = 0x4000,
			kCharacterType_Other = 0x8000 };

		/** Letters.
			Not symbols or punctuation, only letters, but ALL letters: ideograph, kana, latin, greek, devanagari, etc.
			@return true if unicode character c is a letter. */
		PUBLIC_DECL static bool IsLetter(const UTF32TextChar& c);
		/** CJK Letters.
			All CJK letters: ideograph, kana, hangul, half-width kana, etc.
			@return true if unicode character c is a CJK letter. */
		PUBLIC_DECL static bool IsCJKLetter(const UTF32TextChar& c);
		/** Letters, but not CJK letters. E.g. latin, greek, hebrew, etc.
			@return true if unicode character c is a non-CJK letter. */
		PUBLIC_DECL static bool IsNonCJKLetter(const UTF32TextChar& c);

		/** Japanese Hiragana.
			@return true if unicode character c is hiragana. */
		PUBLIC_DECL static bool IsHiragana(const UTF32TextChar& c);

		/** Japanese Katakana.
			@return true if unicode character c is Katakana. */
		PUBLIC_DECL static bool IsKatakana(const UTF32TextChar& c);

		/** CJK unified ideographs.
			@return true if unicode character c is a CJK unified ideographs. */
		PUBLIC_DECL static bool IsCJKIdeograph(const UTF32TextChar& c);

		/** Chinese bopomofo.
			@return true if unicode character c is Chinese bopomofo. */
		PUBLIC_DECL static bool IsBopomofo(const UTF32TextChar& c);

		/** Korean jamo.
			@return true if unicode character c is Korean jamo. */
		PUBLIC_DECL static bool IsJamo(const UTF32TextChar& c);
		/** Korean hangul.
			@return true if unicode character c is Korean hangul. */
		PUBLIC_DECL static bool IsHangul(const UTF32TextChar& c);

		/** Numbers 0-9.
			@return true if unicode character c is 0-9. */
		PUBLIC_DECL static bool IsRomanDigit(const UTF32TextChar& c);
		/** Japanese Kanji numbers.
			@return true if unicode character c is a Japanese Kanji numeral. */
		PUBLIC_DECL static bool IsJapaneseNumber(const UTF32TextChar& c);
		/** Any numbers.
			@return true if unicode character c is a number in any script. */
		PUBLIC_DECL static bool IsAnyNumber(const UTF32TextChar& c);

		/** White Space.
			@return true if unicode character c is white space: spaces, tabs, etc. */
		PUBLIC_DECL static bool IsWhiteSpace(const UTF32TextChar& c);

		/** Combining marks.
			@return true if unicode character c is any kind of combining mark (mostly diacritics). */
		PUBLIC_DECL static bool IsCombiningMark(const UTF32TextChar& c);

		/** Diacritics.
			@return true if the unicode character c is a diacritic according to WRUDGetCharacterProperty. */
		PUBLIC_DECL static bool IsDiacritic_WorldReady(const UTF32TextChar& c);

		/** Punctuation.
			@return true if unicode character c is any kind of punctuation. */
		PUBLIC_DECL static bool IsPunctuation(const UTF32TextChar& c);
		/** Punctuation dash.
			@return true if unicode character c is any kind of dash */
		PUBLIC_DECL static bool IsPunctuationDash(const UTF32TextChar& c);
		/** Open punctuation.
			@return true if unicode character c is any kind of opening punctuation mark.  */
		PUBLIC_DECL static bool IsPunctuationOpen(const UTF32TextChar& c);
		/** Closing punctuation.
			@return true if unicode character c is any kind of closing punctuation mark. */
		PUBLIC_DECL static bool IsPunctuationClose(const UTF32TextChar& c);
		/** Initial quotation mark.
			@return true if unicode character c is any kind of initial quotation punctuation. */
		PUBLIC_DECL static bool IsPunctuationInitialQuote(const UTF32TextChar& c);
		/** Final quotation mark.
			@return true if unicode character c is any kind of final quotation punctuation. */
		PUBLIC_DECL static bool IsPunctuationFinalQuote(const UTF32TextChar& c);
		/** Mid-word punctuation. Used for word counting mostly.
			@return true if unicode character c is any kind of mid-word punctuation. */
		PUBLIC_DECL static bool IsMidWordPunctuation(const UTF32TextChar& c);

		/** Symbol.
			@return true if unicode character c is any kind symbol character. */
 		PUBLIC_DECL static bool IsSymbol(const UTF32TextChar& c);
		/** Math symbol.
			@return true if unicode character c is any kind of math symbol */
		PUBLIC_DECL static bool IsSymbolMath(const UTF32TextChar& c);
		/** Currency symbol.
			@return true if unicode character c is any kind of currency symbol. */
		PUBLIC_DECL static bool IsSymbolCurrency(const UTF32TextChar& c);

		/** Greek.
			@return true if unicode character c is a Greek character. */
		PUBLIC_DECL static bool IsGreek(const UTF32TextChar& c);
		/** Cyrillic.
			@return true if unicode character c is a Cyrillic character. */
		PUBLIC_DECL static bool IsCyrillic(const UTF32TextChar& c);
		/** Thai.
			@return true if unicode character c is a Thai character. */
		PUBLIC_DECL static bool IsThai(const UTF32TextChar& c);

		/** Locale.
		@return int corresponding to the locale to which the character belongs. */
		PUBLIC_DECL static int GetLocale(const UTF32TextChar& c);

		/** Uppercase.
			@return the uppercase variant of the unicode character c. */
		PUBLIC_DECL static UTF32TextChar ToUpper(const UTF32TextChar& c);
		/** Is uppercase.
			@return true if the unicode character c is uppercase. */
		PUBLIC_DECL static bool IsUppercase(const UTF32TextChar& c);
		static bool IsUpper(const UTF32TextChar& c)
			{ return IsUppercase(c); }
		static bool CanChangeToUppercase(const UTF32TextChar& c)
			{ return ToUpper(c) != c; }

		/** Lowercase.
			@return the lowercase variant of the unicode character c. */
		PUBLIC_DECL static UTF32TextChar ToLower(const UTF32TextChar& c);
		/** Is lowercase.
			@return true if the unicode character c is lowercase. */
		PUBLIC_DECL static bool IsLowercase(const UTF32TextChar& c);
		static bool IsLower(const UTF32TextChar& c)
			{ return IsLowercase(c); }
		static bool CanChangeToLowercase(const UTF32TextChar& c)
			{ return ToLower(c) != c; }

		/** Title case.
			For unicode characters that have the idea of 2 glyphs (u1CB = Nj, u1F2 = Dz, etc).
			NOTE: for lowercase letters in general, ToTitle does NOT capitalize them.
			@return the title-case variant of 2-letter unicode character c.
			*/
		PUBLIC_DECL static UTF32TextChar ToTitle(const UTF32TextChar& c);
		/** Is title case.
			For unicode characters that have the idea of 2 glyphs (u1CB = Nj, u1F2 = Dz, etc).
			@return whether the unicode character c is a 2-letter title-case unicode character.
			*/
		PUBLIC_DECL static bool IsTitlecase(const UTF32TextChar& c);
		static bool CanChangeToTitlecase(const UTF32TextChar& c)
			{ return ToLower(c) != c; }

		/** Starts uppercase.
			@return true if the unicode character c is uppercase or title case. */
		PUBLIC_DECL static bool StartsUppercase(const UTF32TextChar& c);

		/**  Full width (CJK).
			@ return true if unicode character c is full width (1 em-box). */
		PUBLIC_DECL static bool IsCJKFullWidth(const UTF32TextChar& c);
		/**  To full width (CJK).
			@ return the full-width variant (if one exists) of the unicode character c. */
		PUBLIC_DECL static UTF32TextChar ToFullWidthVariant(const UTF32TextChar& c);

		/** Is narrow variant.
			NOT the same as !ISCJKFullWidth().
			@return true if the unicode character c is the narrow variant as another character. */
		static bool IsNarrowVariant(const UTF32TextChar& c)
			{ return IsVariant(c, kUnidataBit_Narrow); }
		/** To narrow variant.
			@return the narrow variant of the unicode character c. */
		PUBLIC_DECL static UTF32TextChar ToNarrowVariant(const UTF32TextChar& c);

		/** To first base chararacter.
			@return the unicode character the results from stripping off the lowest priority diacritical mark.
		*/
		PUBLIC_DECL static UTF32TextChar ToFirstBaseChar(const UTF32TextChar& c);
		/** To ultimate base chararacter.
			@return the unicode character the results from stripping off all diacritical marks.
		*/
		PUBLIC_DECL static UTF32TextChar ToUltimateBaseChar(const UTF32TextChar& c);

		/** Get character type.
			@return a classification of the unicode character c.
		*/
		PUBLIC_DECL static CharacterType GetCharacterType(const UTF32TextChar& c);

		/** High surrogate.
			@return true if the UTF16 character c is a high surrogate. */
		static bool IsHighSurrogate(UTF16TextChar c)
			{ return (c >= kTextChar_HighSurrogateStart && c <= kTextChar_HighSurrogateEnd); }
		/** Low surrogate.
			@return true if the UTF16 character c is a low surrogate. */
		static bool IsLowSurrogate(UTF16TextChar c)
			{ return (c >= kTextChar_LowSurrogateStart && c <= kTextChar_LowSurrogateEnd); }
		/** Is surrogate.
			@return true if the UTF16 character c is a high or low surrogate. */
		static bool IsSurrogate(UTF16TextChar c)
			{ return (IsHighSurrogate(c) || IsLowSurrogate(c)); }

		PUBLIC_DECL static bool IsVariationSelector(const UTF32TextChar& c);

		/** Basic Latin (low ascii).
			@ return true if unicode character c is low ascii */
		static bool IsBasicLatin(const UTF32TextChar& c)
			{ return (/*c is unsigned: c.GetValue() >= 0x0000 &&*/ c.GetValue() <= 0x007F); }
		/** Latin 1.
			@ return true if unicode character c is in the Latin 1 unicode group.  */
		static bool IsLatin1(const UTF32TextChar& c)
			{ return (c.GetValue() >= 0x0080 && c.GetValue() <= 0x00FF); }

		/** Latin extended A.
			@ return true if unicode character c is in the Latin extended A unicode group.  */
		static bool IsLatinExtendedA(const UTF32TextChar& c)
			{ return (c.GetValue() >= 0x0100 && c.GetValue() <= 0x017F); }
		/** Latin extended B.
			@ return true if unicode character c is in the Latin extended B unicode group.  */
		static bool IsLatinExtendedB(const UTF32TextChar& c)
			{ return (c.GetValue() >= 0x0180 && c.GetValue() <= 0x024F); }

		/** Superscript, subscript
			@ return true if unicode character c is a unicode superscript or subscript.  */
		static bool IsSuperscriptOrSubscript(const UTF32TextChar& c)
			{ return (c.GetValue() == 0x00B2 || c.GetValue() == 0x00B3 || c.GetValue() == 0x00B9 ||
					  (c.GetValue() >= 0x1D62 && c.GetValue() <= 0x1D6A) ||
					  (c.GetValue() >= 0x2070 && c.GetValue() <= 0x209F)); }

		/** IgnoreCharacterDetails.
			What type of characters should be "ignored" by IsIgnoredCharacter. */
		enum IgnoreCharacterDetails {
				kIgnoreZeroWidthOnly = 0,			/** zero-width stuff, break run-in, indent-here */
				kIgnoreDiscretionaryHyphens = 0x01,	/** discretionary hyphens */
				kIgnoreCalculatedText = 0x02,		/** page number, section name, footnote */
				kIgnoreTableCharacters = 0x04,		/** table, table continued */
				kIgnoreInlineGraphics = 0x08,		/** inline graphic */
				kIgnoreNewLine = 0x010,				/** CR, LF */
				kIgnoreSpecialGlyph = 0x020,			/** roman & non-roman */
				kIgnoreUnicodeVariation = 0x040,		/** unicode variation sequence characters */

				kIgnoreNonLegal = kIgnoreTableCharacters + kIgnoreInlineGraphics + kIgnoreNewLine,
				kIgnoreSpellingIgnorable  = 0x07F	/** everything listed above */
			};
		/** The set of "characters" that occupy spots in the model that should be treated neither as
			whitespace nor as an actual character.  These include markers in the text that the user
			would not consider as something that they had entered into the text.  This set does NOT
			include inline graphic markers or table markers, which always take up a position in the
			visible text */
		PUBLIC_DECL static bool IsIgnoredCharacter(const UTF32TextChar& n, IgnoreCharacterDetails ignoreDischy = kIgnoreDiscretionaryHyphens);

		PUBLIC_DECL static bool IsHebrewLetter(const UTF32TextChar& c);
		PUBLIC_DECL static bool IsArabicLetter(const UTF32TextChar& c);

#ifdef ID_DEPRECATED

		/** vertical variants from CJK fonts */
		static bool IsVerticalVariant(const UTF32TextChar& c)
			{ return IsVariant(c, kUnidataBit_Vertical); }

		/** both same class (letter, symbol, punctuation) */
		PUBLIC_DECL static bool IsSameClass(const UTF32TextChar& c1, const UTF32TextChar& c2);

		/** Is Same Subclass.
			Are both characters the same subclass (katakana, dash, currency).
			@return true of both characters c1 and c2 are members of the same character subclass. */
		PUBLIC_DECL static bool IsSameSubclass(const UTF32TextChar& c1, const UTF32TextChar& c2);

		/** To alternate chararacter.
			Example: Greek Omega == Ohm Symbol
			@return an alternate unicode character for the character c.
		*/
		PUBLIC_DECL static UTF32TextChar ToAlternateChar(const UTF32TextChar& c);
#endif

	private:
		PUBLIC_DECL static uint16 FindEntry(const UTF32TextChar& c);
		PUBLIC_DECL static uint16 FindEntry(const UTF32TextChar& c, UTF32TextChar* upper, UTF32TextChar* lower);

		PUBLIC_DECL static bool IsOfClass(const UTF32TextChar& c, uint16 key, uint16 bits);
		PUBLIC_DECL static bool IsOfClass(const UTF32TextChar& c, uint16 key);
		static bool IsVariant(const UTF32TextChar& c, uint16 bits)
			{ return (FindEntry(c) & bits) == bits; }
};


#pragma export off

#endif
		// __UnicodeClass__

