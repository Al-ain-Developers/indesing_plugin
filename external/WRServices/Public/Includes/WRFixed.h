//========================================================================================
//  
//  File: WRFixed.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRFixed__
#define __WRFixed__

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

inline WRFloat			WRFixedToFloat(WRFixed n) { return (float)n /65536; }
inline WRFixed			WRFloatToFixed(WRFloat n) { return (int) (n * 65536); }

WRFixed WRFixedMul(WRFixed a,WRFixed b);
WRFixed WRFixedDiv(WRFixed a,WRFixed b);

inline WRFixed WRFixedAbs(WRFixed a) { return (a>=0) ? a : -a; }


#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
