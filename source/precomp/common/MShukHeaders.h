//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/precomp/common/MShukHeaders.h $
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
//========================================================================================

#ifndef __MShukHeaders_h__
#define __MShukHeaders_h__

#include <cstdarg>
#include <cwctype>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cwchar>
#include <cctype>
#include <ctime>
#include <clocale>


	// define include guards for old c-style includes, so you can't use them on the mac, since
	// it won't work on windows.
	#define _STDARG_H
	#define __wctype_h
	#define _STDDEF_H
	#define _STDIO_H
	#define _STRING_H
	#define _STDLIB_H
	#define _MATH_H
	#define __wchar_h__
	#define _CTYPE_H
	#define _TIME_H
	#define _LOCALE_H

using std::size_t;
using std::FILE;

using std::memcpy;
using std::memmove;
using std::memcmp;
using std::memset;
using std::strlen;
using std::strcmp;
using std::sprintf;
using std::strcpy;
using std::strcat;
using std::strncmp;
using std::strncpy;
using std::strstr;
using std::fopen;
using std::fclose;
using std::fprintf;
using std::strspn;
using std::tm;
using std::time_t;
using std::clock;
using std::isalpha;
using std::isdigit;
using std::isspace;
using std::setlocale;
using std::toupper;
using std::tolower;
using std::localtime;
using std::mktime;
using std::time;

#endif
