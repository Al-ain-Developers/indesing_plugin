//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMUtils.h $
//  
//  Owner: Eric_Kenninga
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
#ifndef __PMUTILS__
#define __PMUTILS__

#ifndef __PMTYPES__
#include "PMTypes.h"
#endif

inline uchar HighByte(uint16 b)
	{ return (uchar)(b >> 8); }
inline uchar LowByte(uint16 b)
	{ return (uchar)(b & 0x00FF); }

inline uint16 LoWrd(uint32 l)
	{ return (uint16)(l); }
inline uint16 HiWrd(uint32 l)
	{ return (uint16)(l >> 16); }

template <class T> 
inline T minimum(const T& a1, const T& b1)
	{ return a1 < b1 ? a1 : b1; }

template <class T> 
inline T maximum(const T& a1, const T& b1)
	{ return b1 < a1 ? a1 : b1; }

//inline int32 abs(int32 a)
//	{ return a < 0 ? -a : a; }

inline int32 sign(double a)
	{ return (a > 0.0 ? 1 : (a == 0.0 ? 0 : -1)); }

inline int32 sign(int32 a)
	{ return (a > 0 ? 1 : (a == 0 ? 0 : -1)); }

inline bool32 Even(int32 x)
	{ return (bool32)(!(x & 1)); }
inline bool32 Odd(int32 x)
	{ return (bool32)(x & 1); }

const double kFixedScale = 65536.0;
const double kInverseFixedScale = 0.0000152587890625;

// Inbound Conversions
inline PMReal ToRealNumber(Fixed fx)
	{ return int32(fx) * kInverseFixedScale; }

// Reset FPU exception register.
// Fix for bug# 306191. Win95/98 printer drivers reset the floation point
// exceptions on Windows. This causes floating point exceptions to be translated
// to Windows structured exceptions. We don't want this. This is *not* the default
// behavior in K2. [jshankar 5/26/99]
#if defined(WINDOWS)
 
inline void ResetFPUException()
{
	if (kDefaultFPUExceptions != _control87(0,0)) 
#if !defined(_WIN64)
		_control87( kDefaultFPUExceptions, 0xfffff );
#else
		 // on 64 bit architecture  changing the floating point precision is not supported 
		 // so _MCW_PC flag is not supported . Also _MCW_IC flag is not supported on 64 bit architecture
		_control87( kDefaultFPUExceptions, _MCW_DN | _MCW_EM | _MCW_RC);
#endif
}

#elif defined(MACINTOSH)

inline void ResetFPUException()
{
	// do nothing on Macintosh 
}

#endif

// Convenience define for element count for a C-array
#define ELEM_COUNT(array)	(sizeof(array)/sizeof(array[0]))


#endif // PMUTILS
