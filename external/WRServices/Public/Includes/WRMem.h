//========================================================================================
//  
//  File: WRMem.h
//  
//  Owner: Michel Hutinel
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRMem__
#define __WRMem__

#include "WRConfig.h"
#include "WRDefines.h"


/* 
InitWRMem
*/
WRSERVICES_DECL WRBool	InitWRMem(WRMemObj* memObj);

/* 
DeleteWRMem
*/
WRSERVICES_DECL void	DeleteWRMem(void);

/* 
GetWRMemObj
*/
WRSERVICES_DECL WRMemObj*	GetWRMemObj(void);

/* 
WRMalloc 
*/
WRSERVICES_DECL void*	WRMalloc( size_t size );

/* 
WRRealloc 
*/
WRSERVICES_DECL void*	WRRealloc( void* ptr, size_t newSize, size_t oldSize );

/* 
WRFree 
*/
WRSERVICES_DECL void	WRFree( void* ptr );

WRSERVICES_DECL void	WRHeapCheck();

#endif /* __WRMem__ */
