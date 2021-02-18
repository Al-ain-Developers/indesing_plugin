//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PlatformChar.h $
//  
//  Owner: Margie Vogel
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
#ifndef __PLATFORMCHAR__
#define __PLATFORMCHAR__

#define USE_CHARCOUNTER_CLASS 0
#define USE_PLATFORMCHAR_CLASS 1

#if USE_CHARCOUNTER_CLASS
class CharCounter
{
public:
	CharCounter()
	{ fNumChars = 0; };

	CharCounter(int32 value)
	{ fNumChars = value; };

	inline void Set(int32 value)
	{ fNumChars = value; }

	inline int32 GetInt32() const
	{ return (fNumChars); }

	//----------OPERATORS---------------

	operator int32() const
		{ return fNumChars; }
		
	int32& operator = (const int32 &newValue)
		{ fNumChars = newValue; return fNumChars; }

	inline bool16 operator == (const CharCounter &value) const
		{ return (value.GetInt32() == fNumChars);}
	inline bool16 operator != (const CharCounter &value) const
		{ return (value.GetInt32() != fNumChars);}
	
	inline bool16 operator < (const CharCounter &value) const
		{ return (fNumChars < value.GetInt32());}
	inline bool16 operator > (const CharCounter &value) const
		{ return (fNumChars > value.GetInt32());}

	inline bool16 operator <= (const CharCounter &value) const
		{ return (fNumChars <= value.GetInt32()); }
	inline bool16 operator >= (const CharCounter &value) const
		{ return (fNumChars >= value.GetInt32()); }

	inline CharCounter& operator ++ ()
		{ fNumChars++; return *this; }
	inline CharCounter operator ++ (int)
		{ CharCounter temp = *this; ++*this; return temp; }
	inline CharCounter operator += (const CharCounter &value)
		{ return (fNumChars += value.GetInt32()); }
	inline CharCounter operator + (const CharCounter &value) const
		{ return (fNumChars + value.GetInt32()); }
	inline CharCounter& operator -- ()
		{ fNumChars--; return *this; }
	inline CharCounter operator -- (int)
		{ CharCounter temp = *this; --*this; return temp; }
	inline CharCounter operator -= (const CharCounter &value)
		{ return (fNumChars -= value.GetInt32()); }
	inline CharCounter operator - (const CharCounter &value) const
		{ return (fNumChars - value.GetInt32()); }

	inline CharCounter operator / (const CharCounter &value) const
		{ return (fNumChars / value.GetInt32()); }

	inline CharCounter operator * (const CharCounter &value) const
		{ return (fNumChars * value.GetInt32()); }

private:
	int32 fNumChars;
};

	// TODO: Take these out, use implicit convertion operator
inline int32 CharCounter_GetInt32(CharCounter i) 
	{ return i.GetInt32(); }
inline void CharCounter_SetInt32(CharCounter i, int32 newValue) 
	{ i.Set(newValue); }
#else
typedef int32 CharCounter;

inline int32 CharCounter_GetInt32(CharCounter i) 
	{ return i; }
inline void CharCounter_SetInt32(CharCounter i, int32 newValue) 
	{ i = newValue; }
#endif

class PMString;
class PlatformChar
{
public:
	PlatformChar()
	{ fPlatformChar = 0; fScript = -1; };

	PlatformChar(char inChar, int8 script = -1)
	{ fPlatformChar = inChar; fScript = script; }

	PlatformChar(uchar16 inChar, int8 script = -1)
	{ fPlatformChar = inChar; fScript = script; }

	PlatformChar(uchar highByte, uchar lowByte, int8 script = -1)
	{ Set(highByte, lowByte, script); };

	/**	Set value of PlatformChar
		@param highByte		high byte of 2-byte character. 0 if not 2-byte.
		@param lowByte		low byte of 2-byte character.
		@param script		encoding of character. -1 if you don't care.
	 */
	inline void Set(uchar highByte, uchar lowByte, int8 script = -1)
	{
		fPlatformChar = highByte<<8 | lowByte;
		fScript = script;
#ifdef DEBUG //following function will assert if fPlatformChar is invalid
		IsValidCharForScript();
#endif
	}
	
	/**	Set value of PlatformChar
		@param inChar	character value.
		@param script		encoding of character. -1 if you don't care.
	 */
	inline void Set(uchar16 inChar, int8 script = -1)
  	{
  		fPlatformChar = inChar;
  		fScript = script;
  #ifdef DEBUG //following function will assert if fPlatformChar is invalid
  		IsValidCharForScript();
  #endif
  	}

	/**	Set value of PlatformChar
		@param inChar	character value.
		@param script		encoding of character. -1 if you don't care.
	 */
	inline void Set(char inChar, int8 script = -1)
	{ fPlatformChar = inChar; fScript = script; }

	/**	Set value of PlatformChar
		@param inChar	character value.
		@param script		encoding of character. -1 if you don't care.
	 */
	inline void Set(uchar inChar, int8 script = -1)
	{ fPlatformChar = inChar; fScript = script; }

	/**	Set value of PlatformChar from Unicode.
		@param uniChar	unicode value
	 */
	PUBLIC_DECL void SetFromUnicode(textchar uniChar);

	/**	Is PlatformChar 2-byte.
		@return bool16 kTrue if 2-byte
	 */
	inline bool16 IsTwoByte() const
	{ return (fPlatformChar & 0xFF00); }

	/**	Is lower ASCII
		@return bool16 kTrue is char is < 128
	 */
	inline bool16 IsLowASCII() const
	{ return (fPlatformChar < 128); }

	/**	Is character between '0' and '9'
		@return bool16 kTrue if number
	 */
	inline bool16 IsNumber() const
	{ return (fPlatformChar >= '0' && fPlatformChar <= '9'); }

	/**	Character is a valid representation of hex.
		@return bool16 kTrue if character can be hex number
	 */
	inline bool16 IsHexNumber() const
	{ return ((fPlatformChar >= '0' && fPlatformChar <= '9')
				|| (fPlatformChar >= 'a' && fPlatformChar <= 'f')
				|| (fPlatformChar >= 'A' && fPlatformChar <= 'F') ); }

	/**	Character is alphabetic
		@return bool16	kTrue if is alphabetic
	 */
	inline bool16 IsAlpha() const
	{ return ((fPlatformChar >= 'a' && fPlatformChar <= 'z') || (fPlatformChar >= 'A' && fPlatformChar <= 'Z')); }

	/**	Character is upper case
	@return bool16 kTrue if upper case
	 */
	PUBLIC_DECL bool16 IsUpper() const;

	/**	Character is lower case
		@return bool16 kTrue if lower case
	 */
	PUBLIC_DECL bool16 IsLower() const;

	/**	Return upper case version of character
		@return PlatformChar	Upper case character
	 */
	PUBLIC_DECL PlatformChar ToUpper() const;

	/**	Return lower case version of character
		@return PlatformChar	lower case character
	 */
	PUBLIC_DECL PlatformChar ToLower() const;

	// character == methods
	inline bool16 IsSpace() const
	{ return (fPlatformChar == ' '); }
	inline bool16 IsComma() const
	{ return (fPlatformChar == ','); }
	inline bool16 IsDash() const
	{ return (fPlatformChar == '-'); }
	inline bool16 IsPeriod() const
	{ return (fPlatformChar == '.'); }
	inline bool16 IsColon() const
	{ return (fPlatformChar == ':'); }
	inline bool16 IsSemiColon() const
	{ return (fPlatformChar == ';'); }
	inline bool16 IsBackSlash() const
	{ return (fPlatformChar == '\\'); }
	inline bool16 IsTilde() const
	{ return (fPlatformChar == '~'); }
	inline bool16 IsLineBreakChar() const
	{ return (fPlatformChar == '\r' || fPlatformChar == '\n'); }
	inline bool16 IsChar(char compareChar) const
	{ return (fPlatformChar == compareChar); }

	inline uchar HighByte() const
	{ return (uchar)(fPlatformChar >> 8); }
	inline uchar LowByte() const
	{ return (uchar)(fPlatformChar & 0x00FF); }
	
	// this is used in epsparsecolor.cpp
	//	to compare hex values. That code really shouldnt be
	//	using a PMString as it seems to be parse a bunch of
	//	data. should remove this method.
	/**	Get a uchar from PlatformChar
		this is only for special cases where you know
		you have a one byte string and you want to get
		its uchar value.

		@return uchar - value
	 */
	PUBLIC_DECL uchar GetAsOneByteChar() const;

	/**	Return the platform-encoded value
		@return uchar16		value
	 */
	uchar16 GetValue() const { return fPlatformChar; };
	
	inline int32 GetScript() const
	{ return (fScript); }


	/**	Get value as hex string
		@return PMString	hex representation of PlatformChar
	 */
	PUBLIC_DECL PMString *GetAsHexString() const;
	
	typedef enum {
		kNoError = 0,
		kNotNumber
	} ConversionError; 
	/**	Get as number.
		Sets pError to a ConversionError if the character cannot be converted.
		@param pError	error
		@return int16	Number
	 */
	PUBLIC_DECL int16 GetAsNumber( ConversionError *pError = nil ) const;
	PUBLIC_DECL void SetFromNumber(int16 number);
	
	
	inline bool16 IsValid() const
	{ return (fPlatformChar != 0); }
	

	/**	Check if character high and low bytes are valid if 2-byte script
		@param script	script to check. If -1 internal script value is used.
		@return bool16	kTrue if character is valid.
	 */
	PUBLIC_DECL bool16 IsValidCharForScript(int32 script = -1) const;

	/**	Check if character can be represented in unicode with script
		@param script	script to check. If -1 internal script value is used.
		@return bool16	kTrue if character can be represented in unicode with script.
	 */
	PUBLIC_DECL bool16 IsValidInUnicode(int32 script = -1) const;
	
		
	//----------OPERATORS---------------
		
	inline bool16 operator == (const PlatformChar &value) const
		{ return (value.GetValue() == fPlatformChar);}
	inline bool16 operator != (const PlatformChar &value) const
		{ return (value.GetValue() != fPlatformChar);}
	
	inline bool16 operator < (const PlatformChar &value) const
		{ return (fPlatformChar < value.GetValue());}
	inline bool16 operator > (const PlatformChar &value) const
		{ return (fPlatformChar > value.GetValue());}

	inline bool16 operator <= (const PlatformChar &value) const
		{ return (fPlatformChar <= value.GetValue()); }
	inline bool16 operator >= (const PlatformChar &value) const
		{ return (fPlatformChar >= value.GetValue()); }

	inline PlatformChar& operator ++ ()
		{ fPlatformChar++; return *this; }
	inline PlatformChar operator ++ (int)
		{ PlatformChar temp = *this; ++*this; return temp; }
	inline PlatformChar operator += (const PlatformChar &value)
		{ return PlatformChar(fPlatformChar += value.GetValue(), fScript); }
	inline PlatformChar operator + (const PlatformChar &value) const
		{ return PlatformChar((uchar16)(fPlatformChar + value.GetValue()), fScript); }
	inline PlatformChar& operator -- ()
		{ fPlatformChar--; return *this; }
	inline PlatformChar operator -- (int)
		{ PlatformChar temp = *this; --*this; return temp; }
	inline PlatformChar operator -= (const PlatformChar &value)
		{ return PlatformChar(fPlatformChar -= value.GetValue(), fScript); }
	inline PlatformChar operator - (const PlatformChar &value) const
		{ return PlatformChar((uchar16)(fPlatformChar - value.GetValue()), fScript); }

private:
	uchar16	fPlatformChar;
	int8		fScript;
};
#endif
