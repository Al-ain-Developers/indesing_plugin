//========================================================================================
//  
//  File: WRFloat.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRFloat__
#define __WRFloat__

#include <math.h>
#ifdef WR_MAC_ENV
#pragma options align=power
#endif

inline WRFloat WRFloatAbs(WRFloat a) { return (a>=0) ? a : -a; }

const WRFloat kWRPI = (WRFloat)3.14159265358979323846;

const WRFloat kWRDegreesToRadians = (kWRPI / 180);
const WRFloat kWRRadiansToDegrees = (180 / kWRPI);

inline WRFloat WRFloatMax(WRFloat a, WRFloat b) { return a >= b ? a : b; }
inline WRFloat WRFloatMin(WRFloat a, WRFloat b) { return a < b ? a : b; }
inline WRFloat WRFloatSqrt(WRFloat a) { return WRFloat(sqrt(a)); }
inline WRFloat WRFloatCos(WRFloat a) { return WRFloat(cos(a)); }
inline WRFloat WRFloatATan2(WRFloat a, WRFloat b) { return WRFloat(atan2(a,b)); }
inline WRFloat WRFloatATan(WRFloat a) { return WRFloat(atan(a)); }

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
