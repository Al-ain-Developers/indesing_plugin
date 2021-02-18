//========================================================================================
//  
//  File: WRAllocPool.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRALLOCPOOL__
#define __WRALLOCPOOL__

#include "WRMem.h"
#include "WRClass.h"

#ifndef WRASSERT
  #ifdef WRSERVICES_BUILD
  #include "WRDebug.h"
  #else
  #define WRASSERT(a,b) 
  #endif
#endif
/*
#ifdef WRSERVICES_BUILD
#include "WRMem.h"
#include "WRDebug.h"
#else

#define WRMalloc(s) malloc(s)
#define WRFree(p) free(p)
#define WRRealloc(p,nw,old) realloc(p,nw)
#define WRASSERT(a,b) 
#endif
*/

class IWRMultiProcessing;

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

struct Chunk
{
	Chunk*		fNext;
	int			fLeft;
	char		fData[1];
} ;

class WRSERVICES_DECL WRAllocPool : public WRClass
{
public:

	WRAllocPool(int blockSize, int chunkSize,IWRMultiProcessing* multi = NULL);
	virtual ~WRAllocPool();

	void*		Alloc();
	void 		Free(void*);


protected:
	WRMutex*			fMutex;
	IWRMultiProcessing*	fMulti;
	int		fBlockSize;
	int		fChunkSize;
	void*	fFreeList;
	Chunk*	fChunkList;
};


#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
