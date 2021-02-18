//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IMojikumiTable.h $
//  
//  Owner: nmccully
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
#ifndef __IMojikumiTable__
#define __IMojikumiTable__


#include "IPMUnknown.h"
#include "CTextEnum.h"
#include "CJKID.h"

class IKinsokuTable;
class IPMFont;

typedef int16	MojikumiClass;


class MojikumiElement {
	public:
		typedef base_type data_type;

		enum { kNumOfMojikumiPriority =	10 };

		MojikumiElement() : fMinimum(0.0), fDesired(0.0), fMaximum(0.0), fPriority(0), fAkiDoesntFloat(kFalse)
			{}

		bool16 operator==(const MojikumiElement& other) const
			{ return	(fMinimum == other.fMinimum && fDesired == other.fDesired && 
					 	fMaximum == other.fMaximum && fPriority == other.fPriority &&
					 	fAkiDoesntFloat == other.fAkiDoesntFloat); }
		bool16 operator!=(const MojikumiElement& other) const
			{ return !(*this == other); }

		MojikumiElement& operator*=(PMReal scale)
			{ fMinimum *= scale; fMaximum *= scale; fDesired *= scale; return *this; }
		MojikumiElement& operator+=(PMReal indent)
			{ fMinimum += indent; fMaximum += indent; fDesired += indent; return *this; }
						
		void	Clear()
			{ fMinimum = 0.0, fDesired = 0.0, fMaximum = 0.0, fPriority = 0, fAkiDoesntFloat = kFalse; }
	
		void	Set(PMReal min, PMReal des, PMReal max, int16 pri = 0, bool16 alt = kFalse)
			{	fMinimum = min, fDesired = des, fMaximum = max, fPriority = pri, fAkiDoesntFloat = alt; }
				
		PMReal	Minimum() const	{ return fMinimum; }
		PMReal	Desired() const	{ return fDesired; }
		PMReal	Maximum() const	{ return fMaximum; }
		int16	Priority() const	{ return fPriority; }
		bool16	IsAkiDoesntFloat() const	{ return fAkiDoesntFloat; }

		PMReal&	Minimum()	{ return fMinimum; }
		PMReal&	Desired()	{ return fDesired; }
		PMReal&	Maximum()	{ return fMaximum; }

		int16&	Priority()	{ return fPriority; }
		bool16&	IsAkiDoesntFloat()	{ return fAkiDoesntFloat; }

	private:		
		PMReal		fMinimum;
		PMReal		fDesired;
		PMReal		fMaximum;
		int16		fPriority;
		bool16		fAkiDoesntFloat;
};


class MojikumiBaseSpacing 
{
	public:
		typedef base_type data_type;
		MojikumiBaseSpacing()	: fMojikumiClass(0)	{}
		MojikumiElement	fBefore;
		MojikumiElement	fAfter;
		MojikumiClass	fMojikumiClass;
};

/** Used to override spacing in the Mojikumi table
*/
class MojikumiOverrideSpacing  : public MojikumiElement
{
	public:
		typedef base_type data_type;
		MojikumiOverrideSpacing() : fBaseClass(0), fSideClass(0), fIsAfter(kFalse)
			{}
		MojikumiOverrideSpacing(const MojikumiElement& o) : MojikumiElement(o), fBaseClass(0), fSideClass(0), fIsAfter(kFalse)
			{}
	
		void Set(MojikumiClass base, MojikumiClass side, bool16 after, 
					PMReal min, PMReal des, PMReal max, int16 pri = 0, bool16 alt = kFalse)
			{ MojikumiElement::Set(min, des, max, pri, alt); fBaseClass = base; fSideClass = side; fIsAfter = after; }

		MojikumiClass BaseClass() const	{ return fBaseClass; }
		MojikumiClass SideClass() const	{ return fSideClass; }
		bool16		  IsAfter() const	{ return fIsAfter; }

		MojikumiClass& BaseClass()	{ return fBaseClass; }
		MojikumiClass& SideClass()	{ return fSideClass; }
		bool16&		   IsAfter()	{ return fIsAfter; }

	private:
		MojikumiClass	fBaseClass;
		MojikumiClass	fSideClass;
		bool16			fIsAfter;
};


#define USE_KATAKANA_CLASS

// We changed the following name of character classes.
//	kJIS_Kana	->	kJIS_Hiragana
//	kJIS_EndOfLine	->	kJIS_EdgeOfLine
//	kJIS_EndOfParagraph	->	kJIS_TopOfParagraph
//
// And we added some JIS character classes

/**
   Character classes
*/
enum {	kJIS_Unknown = 0,
		// JISx4051 character class
		kJIS_OpenParen = 1,			// Open parenthesis
		kJIS_CloseParen = 2,		// Close parenthesis
		kJIS_Kinsoku = 3,			// Can't-begin-line characters
		kJIS_EndPunctuation = 4,	// End punctuation
		kJIS_MiddlePunctuation = 5,	// Middle punctuation
		kJIS_Period = 6,			// Period
		kJIS_NotSeparate = 7,		// Can't-be-separated characters
		kJIS_BeforeNumber = 8,		// Symbols proceding numbers
		kJIS_AfterNumber = 9,		// Symbols following numbers
		kJIS_FullSpace = 10,		// Double byte space
		kJIS_Hiragana = 11,			// Hiragana
		kJIS_OtherJ = 12,			// Other Japanese characters
		kJIS_WithSubscript = 13,	// Soejitsuki
		kJIS_WithRubi = 14,			// Parent characters of rubi
		kJIS_NumGroup = 15,			// Rensuuji - a group of numbers.
		kJIS_Symbol = 16,			// 
		kJIS_RomanSpace = 17,		// Roman space
		kJIS_RomanChar = 18,		// Roman characters
		kJIS_WarichuOpenParen = 19,	// Open parenthesis for Warichu
		kJIS_WarichuCloseParen = 20,	// Close parenthesis for Warichu

		// Added the following classes for K2J
		kJIS_Comma = 21,
		
		kJIS_EdgeOfLine = 22,		// Edge of line	-- top or end
		kJIS_TopOfParagraph = 23,	// Top of paragraph
		
		// Added two classes for K2J
		kJIS_FullNumber = 24,		// Double byte number
		kJIS_RomanNumber = 25,		// Single byte number
		
		// Extension class
		kJIS_CornerOpenBracket = 26,
		kJIS_RoundOpenParen = 27,
		kJIS_CornerCloseBracket = 28,
		kJIS_RoundCloseParen = 29,
		kJIS_RomanComma = 30,
		kJIS_RomanPeriod = 31,
		kJIS_Colon = 32,
		
		kJIS_Katakana = 33,
		
		kJIS_RomanOpenParen = 34,	// CID-mojikumi -- treat as kJIS_RomanChar otherwise
		kJIS_RomanCloseParen = 35,	// CID-mojikumi -- treat as kJIS_RomanChar otherwise
		
		kJIS_NumOfClasses = 36		// number of classes
	};

enum {	
		kMojikumi_Desired,	// Desired ratio of Mojikumi spacing
		kMojikumi_Minimum,	// Minimum ratio of Mojikumi spacing
		kMojikumi_Maximum,	// Maximum ratio of Mojikumi spacing
		kMojikumi_Priority	// Priority for Justification
	};
	
/** Specifies Mojikumi rules to be used
*/
enum {
		kDefaultMojikumiSet_None = 0,
		kDefaultMojikumiSet_01,
		kDefaultMojikumiSet_02,
		kDefaultMojikumiSet_03,
		kDefaultMojikumiSet_04,
		kDefaultMojikumiSet_05,
		kDefaultMojikumiSet_06,
		kDefaultMojikumiSet_07,
		kDefaultMojikumiSet_08,
		kDefaultMojikumiSet_09,
		kDefaultMojikumiSet_10,
		kDefaultMojikumiSet_11,
		kDefaultMojikumiSet_12,
		kDefaultMojikumiSet_13,
		kDefaultMojikumiSet_14,
		kDefaultMojikumiSet_15,		// Trad Chinese
		kDefaultMojikumiSet_16,		// Simp Chinese
		
		kDefaultMojikumiSet_Nums
};

/** Used with Mojikumi name table entries
*/
class IMojikumiTable : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMOJIKUMITABLE };
		
		typedef enum {
				kYakumonoSpacing_None = 0,
											// Min	Des	 Max
				kYakumonoSpacing_FixedHalf,			// 0.0, 0.0, 0.0
				kYakumonoSpacing_HalfToFull,		// 0.0, 0.0, 0.5
				kYakumonoSpacing_FullToHalf,		// 0.0, 0.5, 0.5
				kYakumonoSpacing_FixedFull,			// 0.5, 0.5, 0.5

				kYakumonoSpacing_HalfOrFull,		// 0.0, 0.0, 0.5 (not range)
				kYakumonoSpacing_FullOrHalf			// 0.0, 0.5, 0.5 (not range)
		} YakumonoSpacingSet;

		typedef enum {
				kYakumono_None,
				kYakumono_Okoshi,
				kYakumono_Uke,
				kYakumono_Middle
		} YakumonoKind;


		/** Get spacing width before character for Mojikumi
		*/
		virtual void GetBeforeSpacingWidth(MojikumiClass target, MojikumiClass previousClass, 
											PMReal charWidth, MojikumiElement *element,
											bool16 isVertical) const = 0;

		/** Get spacing width after character for Mojikumi
		*/
		virtual void GetAfterSpacingWidth(MojikumiClass target, MojikumiClass afterClass, 
											PMReal charWidth, MojikumiElement *element, 
											bool16 isVertical) const = 0;

		/** Get spacing rules before character for Mojikumi
		*/
		virtual bool16 GetBeforeSpacingRules(MojikumiClass target, MojikumiClass previousClass, 
											MojikumiElement *element) const = 0;

		/** Get spacing rules after character for Mojikumi
		*/
		virtual bool16 GetAfterSpacingRules(MojikumiClass target, MojikumiClass afterClass, 
											MojikumiElement *element) const = 0;

		/** Set spacing rules before character for Mojikumi
		*/
		virtual bool16 SetBeforeSpacingRules(MojikumiClass target, MojikumiClass previousClass, 
											const MojikumiElement &element) = 0;

		/** Set spacing rules after character for Mojikumi
		*/
		virtual bool16 SetAfterSpacingRules(MojikumiClass target, MojikumiClass afterClass, 
											const MojikumiElement &element) = 0;

		virtual bool16 GetBaseClassSpacingRules(int32 index, MojikumiClass *target, MojikumiBaseSpacing *element) const = 0;
		virtual bool16 GetOverrideSpacingRules(int32 index, MojikumiOverrideSpacing *element) const = 0;
		virtual int32 GetNumOfOverrideSpacingRules() const = 0;

		/** Copy spacing data from other Mojikumi table
		*/
		virtual void CopyMojikumiData(const IMojikumiTable *from) = 0;

		/** Return number of registered character classes
		*/
		virtual int32	GetNumOfCharacterClasses() const = 0;

		/** Get Mojikumi character class
		*/
		virtual MojikumiClass	GetCharacterClass(UTF32TextChar code, bool16 isVertical, const IKinsokuTable *kinsokuTable = nil, Text::GlyphID glyph = kInvalidGlyphID, const IPMFont * font = nil, bool16 * usedCID = nil) const = 0;
		
		/** Return kTrue if this mojikumi table has Tsume table
		*/
		virtual bool16 HasTsumeTable() const = 0;
		
		/** Get Tsume value. 
			Mojikumi aki and tsume are related: aki is the spacing the user sets for each character class,
			based on the widths _after_ tsume has been taken out. The tsume amount is the difference between
			the glyph width in the font and the width set by JIS X 4051 for that character, in em.
			Because of this dependency, tsume tables are attached to mojikumi tables, and accessing tsume amounts
			should be accomplished using IMojikumiTable::GetTsumeValue().
			@see ITsumeTable
			@see IPMFont
			@param chr the raw Unicode codepoint
			@param before the left side tsume amount in em (i.e. -0.5 means -1/2 the point size)
			@param after the right side tsume amount in em
			@param isVertical whether the character is being drawn upright in vertical text
			@param glyphID for CID-based mojikumi, the glyph ID being drawn
			@param font for CID-based mojikumi, the font being used. CID-based mojikumi and tsume uses an IPMFont and the glyphID.
			When passing glyphID, you must also pass an IPMFont *, or the CID will not be used and the amount for the raw
			Unicode will be returned.
		*/
		virtual bool16 GetTsumeValue(UTF32TextChar chr, PMReal *before, PMReal *after, bool16 isVertical, Text::GlyphID glyph = kInvalidGlyphID, const IPMFont * font = nil) const = 0;

		/** Get Tsume table UID
		*/
		virtual UID		GetTsumeTableUID() const = 0;

		/** Set Tsume table UID
		*/
		virtual void	SetTsumeTableUID(UID tsumeUID) = 0;

		/** Get Mojikumi character class list UID
		*/
		virtual UID		GetMojikumiClassListUID() const = 0;

		/** Set Mojikumi character class list UID
		*/
		virtual void	SetMojikumiClassListUID(UID classListUID) = 0;

		/** Set spacing at edge of line (top line and end line)
		*/
		virtual void SetSpacingAtEdgeOfLine(YakumonoSpacingSet lineEndComma = kYakumonoSpacing_None, 
											YakumonoSpacingSet lineEndPeriod = kYakumonoSpacing_None, 
											YakumonoSpacingSet lineEndParen = kYakumonoSpacing_None,
											YakumonoSpacingSet lineEndMidPunc = kYakumonoSpacing_None,
											YakumonoSpacingSet lineTopParen = kYakumonoSpacing_None,
											YakumonoSpacingSet paraTopParen = kYakumonoSpacing_None,
											int32 jisage = 0, bool16 ignoreParenJisage = kFalse ) = 0;

		/** Return kTrue if this mojikumi table is editable
		*/
		virtual bool16 GetEditability() const = 0;
		
		/** Get default chararacter class Index
		*/
		virtual int32 GetDefaultDoubleByteClassIndex() const = 0;
		virtual int32 GetDefaultSingleByteClassIndex() const = 0;
		virtual int32 GetBeginParagraphClassIndex() const = 0;
		virtual int32 GetEdgeOfLineClassIndex() const = 0;
		
		virtual int16	GetBasedOn() const = 0;
		virtual void	SetBasedOn(int16 which) = 0;
};

#endif
		// __IMojikumiTable__
		
		
