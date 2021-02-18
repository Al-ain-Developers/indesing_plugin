//========================================================================================
//  
//  File: WRClass.h
//  
//  Owner: Michel Hutinel
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRClass__
#define __WRClass__

#include "WRConfig.h"
#include "WRDefines.h"

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

/*
	MH 07/01/02: Strange def-undef sequence, why?
	- In SLO2, new is redefined (CF cSLO_MEMORY_DEBUG in SLOAlloc.h)
	- On Windows debug (case where cSLO_MEMORY_DEBUG is defined), the redefinition of new throws
	a compilation error when compiling operator new
*/
#if defined (new)
#define WR_slonew new
#undef new
#define new new
#endif

class WRSERVICES_DECL WRClass
{
public:
	void* operator new(size_t size);
	void operator delete(void* p);
};

#if defined (WR_slonew)
#undef new
#define new WR_slonew
#endif

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif /* __WRClass__ */
