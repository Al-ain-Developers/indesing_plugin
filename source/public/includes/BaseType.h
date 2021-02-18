//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BaseType.h $
//  
//  Owner: ?
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
//  ABSTRACT:
//  This file defines a set of base types for use by all PageMaker applications.
//  See the comments below for the different types.
//  
//========================================================================================

#pragma once
#ifndef __BASETYPE__
#define __BASETYPE__

#ifndef __AnsiBasedTypes__
#include "AnsiBasedTypes.h"
#endif

#include "K2TypeTraits.h" // For base_type

#if defined MACINTOSH || defined WINDOWS
#include <limits.h>
#else
#include <climits>
#endif

/** PString is a base type used for Pascal-style strings. A Pascal string
	is a string of platform encoded bytes, with a leading byte that contains
	the count for the string. It is identical to the Pascal strings used in
	Macintosh system API.
*/
typedef uchar *PString;			// pascal  string headed with count
typedef const uchar *ConstPString;			// pascal  string headed with count

/** CString is a base type used for C-style strings. A C string
	is an array of bytes, terminated by a trailing nul character.
	It is identical to the strings used in the C language.
*/
typedef char *CString;			// null terminated "C"  string
typedef const char *ConstCString;			// null terminated "C"  string

/** WString is a base type for Unicode strings. A WString is an array of
	16-bit characters, terminated by a trailing nul character.
*/
typedef uchar16 *WString;		// null terminated "Unicode"  string
typedef const uchar16 *ConstWString;		// null terminated "Unicode"  string


//	there is a bug in the current (3.3) version of the gcc headers where __SCHAR_MAX__ is
//	not defined.
#ifndef __SCHAR_MAX__
#define __SCHAR_MAX__ 127
#endif

const int8	kMinInt8 = (int8)SCHAR_MIN;		// from limits.h
const int8	kMaxInt8 = (int8)SCHAR_MAX;
const int16 kMinInt16 = (int16)SHRT_MIN;
const int16 kMaxInt16 = (int16)SHRT_MAX;

const uint8  kMaxUInt8 = (uint8)UCHAR_MAX;
const uint16 kMaxUInt16 = (uint16)USHRT_MAX;

#if MACINTOSH && __LP64__
	const int32 kMinInt32 = (int32)INT_MIN;
	const int32 kMaxInt32 = (int32)INT_MAX;

	const uint32 kMaxUInt32 = (uint32)UINT_MAX;
#else
	const int32 kMinInt32 = (int32)LONG_MIN;
	const int32 kMaxInt32 = (int32)LONG_MAX;

	const uint32 kMaxUInt32 = (uint32)ULONG_MAX;
#endif

#if WINDOWS
	const int64 kMinInt64 = (int64)_I64_MIN;
	const int64 kMaxInt64 = (int64)_I64_MAX;

	const uint64 kMaxUInt64 = (uint64)_UI64_MAX;
#else
	const int64 kMinInt64 = (int64)LONG_LONG_MIN;
	const int64 kMaxInt64 = (int64)LONG_LONG_MAX;

	const uint64 kMaxUInt64 = (uint64)ULONG_LONG_MAX;
#endif


//======================================================================
// Other abstract types
//======================================================================

/** TextIndex is the type used to represent the index location of character in an InDesign story. */
typedef int32 TextIndex;

/** textchar is the type used to represent the characters in an InDesign story. */
typedef uchar16 textchar;

/** UTF16TextChar is the type used for 16-bit Unicode characters. */
typedef uchar16 UTF16TextChar;

class IPMStream;

/** UTF32TextChar holds a 32-bit unicode character. The advantage of the 32-bit character
over the 16-bit character is that you don't have 2-character sequences for surrogate characters
as in 16-bit Unicode strings.
*/
class UTF32TextChar
{
	public:
		/** This is a base_type, meaning that it can be copied with a block-move */
		typedef base_type data_type;

		/** Default constructor */
		inline UTF32TextChar() : fCharacterValue() {}
		
		/** Constructor 32-bit char
			@param uint32	32 bit character value
		*/
		inline UTF32TextChar(uint32 c32) : fCharacterValue(c32) {}
		
		/** Constructor from 16-bit character representation
			@param hi	hi-order 16 bits of the 32-bit char
			@param low low-order 16 bits of the 32-bit char
		*/
		inline UTF32TextChar(UTF16TextChar hi, UTF16TextChar low)
				: fCharacterValue((hi - 0xD800) * 0x400 + (low - 0xDC00) + 0x10000) 
			{}
 
 		/** Constructor 32-bit const char
 			@param uint32 const character value
 		*/
 		inline UTF32TextChar(const UTF32TextChar &c) : fCharacterValue(c.fCharacterValue) {}

		/** Returns the 32 bit value of the character
			@return uint32 character value
		*/
		inline uint32 GetValue() const { return fCharacterValue; }
		
		/** Return the high order 16 bit value
			@return UTF16TextChar high order 16-bits
		*/
		inline UTF16TextChar CalcHighSurrogate() const { return (fCharacterValue > 0xFFFF ? static_cast<UTF16TextChar>((fCharacterValue - 0x10000) / 0x400 + 0xd800) : static_cast<UTF16TextChar>(fCharacterValue)); }
		
		/** Return the low order 16 bit value
			@return UTF16TextChar low order 16-bits
		*/
		inline UTF16TextChar CalcLowSurrogate() const { return (fCharacterValue > 0xFFFF ? static_cast<UTF16TextChar>((fCharacterValue - 0x10000) % 0x400 + 0xdc00) : static_cast<UTF16TextChar>(fCharacterValue)); }
		
		/** Convert the 32-bit character into an array of 16-bit values
			@param buf	pointer to array
			@param length int32* OUT contains length of array after conversion.
		*/
		inline void ToUTF16(UTF16TextChar * buf, int32 * len) const
		{
			buf[0] = CalcHighSurrogate();
			if (fCharacterValue > 0xFFFF && *len >= 2)
			{
				*len = 2;
				buf[1] = CalcLowSurrogate();
			}
			else
				*len = 1;
		}
		
		/** Equality comparison of two 32-bit characters
			@param c32 character to compare to
			@return true if the two characters are equal
		 */
		inline bool16 operator == (UTF32TextChar c32) const { return c32.fCharacterValue == fCharacterValue;}

		/** Inequality comparison of two 32-bit characters
			@param c32 character to compare to
			@return true if the two characters are not equal
		 */
		inline bool16 operator != (UTF32TextChar c32) const { return c32.fCharacterValue != fCharacterValue;}
		
		/** Value comparison of two 32-bit characters
			@param i character to compare to
			@return true if this is greater than or equal to than i
		*/
		inline bool16 operator >= (UTF32TextChar i) const { return fCharacterValue >= i.fCharacterValue; }
		
		/** Value comparison of two 32-bit characters
			@param i character to compare to
			@return true if this is less than or equal to than i
		*/
		inline bool16 operator <= (UTF32TextChar i) const { return fCharacterValue <= i.fCharacterValue; }
		
		/** Value comparison of two 32-bit characters
			@param i character to compare to
			@return true if this is greater than i
		*/
		inline bool16 operator > (UTF32TextChar i) const { return fCharacterValue > i.fCharacterValue; }

		/** Value comparison of two 32-bit characters
			@param i character to compare to
			@return true if this is less than i
		*/
		inline bool16 operator < (UTF32TextChar i) const { return fCharacterValue < i.fCharacterValue; }
		
		/** Assignment operator.
			@param value to assign to this
		*/
		inline UTF32TextChar& operator = (const UTF32TextChar& c) { fCharacterValue = c.fCharacterValue; return *this; }

		/** Returns kTrue if the value of this character can NOT be represented in 16 bits.
			In such a case, CalcHighSurrogate and CalcLowSurrogate can be used to get two consecutive 16-bit values that represent the codepoint
			@return kTrue if the value of this character requires more than 16 bits
		*/
		inline bool16 isExtraWide() const { return GetValue() > 0xffff;}

		/** Read or write out the value as a stream of 16-bit characters.
			@param s input or output stream
		*/
		PUBLIC_DECL void ReadWriteUTF16(IPMStream *s);

	protected:
		uint32 fCharacterValue;
};

	
	template <>
	struct CONVERSION_TO_THREADLOCALSTORAGE<UTF32TextChar> {
		static uint32 CONVERT(UTF32TextChar arg) {return arg.GetValue();}
	};

/** Invalid text index value; no text iindex will be negative. */
const TextIndex kInvalidTextIndex = -1;


/** Type used for identifying errors */
typedef int32 ErrorCode;

/** Default error values */
enum { 
	kSuccess = 0, 	/** OK */
	kFailure = 1, 	/** error occurred */
	kCancel = 2 	/** operation has been cancelled or aborted */
};


/** Resource Endian Wrappers are for representing integers in resources.  On Windows
    they are stored in memory as little endian.  On the Mac, they WERE stored in
	memory as big endian when ODFRC was still being built using PowerPC bits. However
	how that ODRFC is being built for the i386 architecture and spitting out resources
	as little endian, neither platforms require any endian swapping.  Any
	necessary swapping WAS handled transparently and they work mostly like the
	integer types they wrap.
**/

#if 0
	#if defined(MACINTOSH) && !defined(__POWERPC__)
		#define RESOURCE_ENDIAN_SWAPPING 1
	#else
		#define RESOURCE_ENDIAN_SWAPPING 0
	#endif
#else
	#define RESOURCE_ENDIAN_SWAPPING 0
#endif

template<typename T>
class ResourceEndianWrapper32
{
	uint32 fContent;

	uint32 EE (uint32 value) const
	{
		#if RESOURCE_ENDIAN_SWAPPING
			return ((value >> 24) & 0x000000ff) |
				   ((value >> 8)  & 0x0000ff00) |
				   ((value << 8)  & 0x00ff0000) |
				   ((value << 24) & 0xff000000);
		#else
			return value;
		#endif
	}

public:
	
	void Set (T value)
	{
		fContent = EE ((uint32) value);
	}
	
	T Get () const
	{
		return T (EE (fContent));
	}
	
	ResourceEndianWrapper32 (T value)
	{
		Set (value);
	}
	
	operator T () const
	{
		return Get ();
	}
};
		
template<typename T>
class ResourceEndianWrapper16
{
	uint16 fContent;

	uint16 EE (uint16 value) const
	{
		#if RESOURCE_ENDIAN_SWAPPING
			return ((value >> 8) & 0x00ff) |
				   ((value << 8) & 0xff00);
		#else
			return value;
		#endif
	}

public:
	
	void Set (T value)
	{
		fContent = EE ((uint16) value);
	}
	
	T Get () const
	{
		return T (EE (fContent));
	}
	
	ResourceEndianWrapper16 (T value)
	{
		Set (value);
	}
	
	operator T () const
	{
		return Get ();
	}
};

#if defined(MACINTOSH) && defined(__POWERPC__)
#define IS_BIG_ENDIAN_ARCH 1
#define IS_LITTLE_ENDIAN_ARCH 0
#else
#define IS_BIG_ENDIAN_ARCH 0
#define IS_LITTLE_ENDIAN_ARCH 1
#endif

namespace K2
{
	//	11/13/98	Roey
	//	Introduced this namespace to avoid possible conflicts
	//	with third party libraries.
	//	As we are adding more to this namespace it might become necessary
	//	to create a dedicated file for it.

	/** UIFlags is used to control what UI comes up during certain commands.
	*/
	typedef enum {
		kSuppressUI,	/** do not display any UI, under no circumstances */
		kMinimalUI,		/** only display the UI absolutely required to do the job */
		kFullUI			/** display every dialog etc. */
	} UIFlags;
}

using namespace K2;

#endif // __BASETYPE__
