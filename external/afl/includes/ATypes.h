//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/ATypes.h $
//  
//  Owner: Michael Easter
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
#ifndef __ATypes__
#define __ATypes__

// Define some of the InDesign ANSI base types if not already defined
#ifndef __AnsiBasedTypes__
	/** 8 bit signed integer */
	typedef signed char			int8;

	/** 16 bit unsigned integer */
	typedef unsigned short		uint16;
	/** 16 bit signed integer */
	typedef short				int16;

	#if defined MACINTOSH && defined __LP64__
		/** 32 bit signed integer */
		typedef int				int32;
	#else
		/** 32 bit signed integer */
		typedef long			int32;
	#endif

	namespace adobe {
	namespace afl {
		#if defined MACINTOSH && defined __LP64__
			/** 32 bit unsigned integer */
			typedef unsigned int    uint32;
		#else
			/** 32 bit unsigned integer */
			typedef unsigned long	uint32;
		#endif
	}	// namespace afl
	}	// namespace adobe

	/** unsigned char */
	typedef unsigned char		uchar;
	/** 8 bit unsigned integer */
	typedef uchar				uint8;
	/** 16 bit unsigned char */
	typedef uint16				uchar16;

	#ifdef WINDOWS
		/** Windows 64 bit integer */
		typedef __int64				int64;
		/** Windows 64 bit unsigned integer */
		typedef unsigned __int64	uint64;
	#else
		/** Macintosh 64 bit integer */
		typedef long long			int64;
		/** Macintosh 64 bit unsigned integer */
		typedef unsigned long long	uint64;
	#endif
#endif	// #ifndef __AnsiBasedTypes__


// Define some of the InDesign base types if not already defined
#ifndef __BASETYPE__
	#if defined MACINTOSH || defined WINDOWS
		#include <limits.h>
	#else
		#include <climits>
	#endif

	namespace adobe {
	namespace afl {
		/** CString is a base type used for C-style strings. A C string
			is an array of bytes, terminated by a trailing null character.
			It is identical to the strings used in the C language.
		*/
		typedef char* CString;

		/** Constant CString
		 @see CString
		 */
		typedef const char*	ConstCString;

		/** WString is a base type for Unicode strings. A WString is an array of
			16-bit UTF16 characters, terminated by a trailing null character.
		*/
		typedef uchar16* WString;

		/** Constant WString
		 @see WString
		 */
		typedef const uchar16* ConstWString;
	}	// namespace afl
	}	// namespace adobe

	#if defined WINDOWS && defined __MWERKS__
		// Metrowerks i86 cross-compiler doesn't like consts in precompiled header files. [amb-cwi86]
		#define kMinInt8	((int8)SCHAR_MIN)
		#define kMaxInt8	((int8)SCHAR_MAX)
		#define kMinInt16	((int16)SHRT_MIN)
		#define kMaxInt16	((int16)SHRT_MAX)
		#define kMinInt32	((int32)LONG_MIN)
		#define kMaxInt32	((int32)LONG_MAX)

		#define kMaxUInt8	((uint8)UCHAR_MAX)
		#define kMaxUInt16	((uint16)USHRT_MAX)
		#define kMaxUInt32	((uint32)ULONG_MAX)
	#else
		//	there is a bug in the current (3.3) version of the gcc headers where __SCHAR_MAX__ is 
		//	not defined.
		#ifndef __SCHAR_MAX__
		#define __SCHAR_MAX__ 127
		#endif

		const int8	kMinInt8	= (int8)SCHAR_MIN;		// from limits.h
		const int8	kMaxInt8	= (int8)SCHAR_MAX;
		const uint8  kMaxUInt8	= (uint8)UCHAR_MAX;

		const int16 kMinInt16	= (int16)SHRT_MIN;
		const int16 kMaxInt16	= (int16)SHRT_MAX;
		const uint16 kMaxUInt16	= (uint16)USHRT_MAX;

		#if defined MACINTOSH && defined __LP64__
			const int32 kMinInt32	= (int32)INT_MIN;
			const int32 kMaxInt32	= (int32)INT_MAX;
			const adobe::afl::uint32 kMaxUInt32	= (adobe::afl::uint32)UINT_MAX;
		#else
			const int32 kMinInt32	= (int32)LONG_MIN;
			const int32 kMaxInt32	= (int32)LONG_MAX;
			const adobe::afl::uint32 kMaxUInt32	= (adobe::afl::uint32)ULONG_MAX;
		#endif
	#endif

	#if defined WINDOWS
		const int64	 kMinInt64	= (int64)_I64_MIN;
		const int64	 kMaxInt64	= (int64)_I64_MAX;
		const uint64 kMaxUInt64	= (uint64)_UI64_MAX;
	#else
        const int64 kMinInt64	= (int64)LONG_LONG_MIN;
        const int64 kMaxInt64	= (int64)LONG_LONG_MAX;
        const uint64 kMaxUInt64	= (uint64)ULONG_LONG_MAX;
	#endif

	//======================================================================
	// Other abstract types
	//======================================================================
	/** UTF16 character */
	typedef uchar16 textchar;
	/** UTF16 character */
	typedef uchar16 UTF16TextChar;
#endif	// #ifndef __BASETYPE__


namespace adobe {
namespace afl {
	/** File date and time.
		The time measured in 100-nanosecond intervals since January 1, 1601 (UTC).
	*/
	typedef uint64	ATime;
}	// namespace afl
}	// namespace adobe

#endif	// __ATypes__
