//========================================================================================
//  
//  File: WRStrSafe.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 2010 - 2010 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRStrSafe__
#define __WRStrSafe__
#include <stdio.h>
#include "WRConfig.h"

class WRSERVICES_DECL WRStrSafe
{
public:
	enum { kNoError, kBufferOverflow, kInvalidParam };
	static int strncpy( char *strDest, size_t numberOfElements, const char *strSource,  size_t count );
	static int strncat( char *strDest, size_t numberOfElements, const char *strSource,  size_t count );
	static int strcpy(char *strDestination, size_t numberOfElements, const char *strSource);
	static int strcat(char *strDestination, size_t numberOfElements, const char *strSource);
	static int wcscpy(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource);
	static int wcscat(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource);
	static int fopen( FILE** pFile,  const char *filename, const char *mode);
	static int sprintf( char *buffer, size_t sizeOfBuffer, const char *format, ...);
	static int sscanfloatlist(const char *buffer, float* res, int avail);
	static int sscanintlist(const char *buffer, int* res, int avail);
};
#endif
