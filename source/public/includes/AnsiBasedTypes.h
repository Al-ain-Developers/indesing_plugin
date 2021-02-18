//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AnsiBasedTypes.h $
//  
//  Owner: Mouhammad Fakhoury
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
#ifndef __AnsiBasedTypes__
#define __AnsiBasedTypes__

// Types based on ANSI C built-in types only 
// ** These types are somewhat (but not totally) machine and compiler neutral **

/** 8 bit signed integer */
typedef signed char		int8;

/** 16 bit unsigned integer */
typedef unsigned short	uint16;
/** 16 bit signed integer */
typedef short			int16;

#if WINDOWS
	/** 32 bit unsigned integer */
	typedef unsigned long	uint32;
	/** 32 bit signed integer */
	typedef long			int32;
#else
	// On Mac64 long goes to 64bits
	#if __LP64__
		/** 32 bit unsigned integer */
		typedef unsigned int	uint32;
		/** 32 bit signed integer */
		typedef int				int32;
	#else
		/** 32 bit unsigned integer */
		typedef unsigned long	uint32;
		/** 32 bit signed integer */
		typedef long			int32;
	#endif
#endif

	/** unsigned char */
typedef unsigned char	uchar;
/** 8 bit unsigned integer */
typedef uchar			uint8;
/** 16 bit unsigned char */
typedef uint16			uchar16;

#if WINDOWS
	/** 64 bit integer */
		typedef __int64 int64;				
	/** 64 bit unsigned integer */
		typedef unsigned __int64 uint64;	
#else
	/** 64 bit integer */
		typedef long long int64;
	/** 64 bit unsigned integer */
		typedef unsigned long long uint64;
#endif

// Explicit boolean type declarations.
/** 8 bit bool (uses kTrue and kFalse rather than true and false) */
typedef uint8	bool8;
/** 16 bit bool (uses kTrue and kFalse rather than true and false) */
typedef int16	bool16;
/** 32 bit bool (uses kTrue and kFalse rather than true and false) */
typedef uint32	bool32;

// These are typedefs are here for AGM compatibility
/** 8 bit bool (used for AGM compatibility) */
typedef uint8	Bool8;
/** 16 bit bool (used for AGM compatibility) */
typedef int16	Bool16;
/** 32 bit bool (used for AGM compatibility) */
typedef uint32	Bool32;


#endif // __AnsiBasedTypes__


