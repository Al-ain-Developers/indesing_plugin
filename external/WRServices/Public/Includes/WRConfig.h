//========================================================================================
//  
//  File: WRConfig.h
//  
//  Owner: Michel Hutinel
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRConfig__
#define __WRConfig__

// Should be enough on WINDOWS since we don't support 16bits system anymore
#if (defined(_WIN32) && _WIN32!=0)

/* The platform	*/
#ifndef WR_WIN_ENV
#define WR_WIN_ENV
#endif

/* The import-export directives */
#ifdef WRSERVICES_BUILD
	#ifdef ALLSERVICES_EXPORTS
		#define WRSERVICES_DECL __declspec(dllexport)
	#else
		#define WRSERVICES_DECL
	#endif
#else
	#ifdef WRSERVICES_STATIC_CLIENT
		#define WRSERVICES_DECL
	#else
		#ifdef WRSERVICES_STATIC_EXPORTING_CLIENT
			#define WRSERVICES_DECL  __declspec(dllexport)
		#else
			#define WRSERVICES_DECL __declspec(dllimport)
		#endif
	#endif
#endif

#define WREXPORT __cdecl
#define WRSTDCALL __stdcall
#define WREXPORTPTR WREXPORT
#define WRCALLBACK __cdecl
#define WRCALLBACKDECL WREXPORT
#define WR_LITTLE_ENDIAN

#else

#if defined(macintosh) || defined(MACINTOSH) || defined(MAC) || defined(_MAC) || (defined(TARGET_OS_MAC) && TARGET_OS_MAC != 0)

#ifndef macintosh
#define macintosh 1
#endif

#ifndef MACINTOSH
#define MACINTOSH 1
#endif

/* The platform	*/
#ifndef WR_MAC_ENV
#define WR_MAC_ENV
#endif

/* The import-export directives */
#ifdef WRSERVICES_STATIC_CLIENT
	#define WRSERVICES_DECL
#else
	#define WRSERVICES_DECL __attribute__((visibility("default")))
#endif

#define WREXPORT
#define WRSTDCALL
#define WREXPORTPTR
#define WRCALLBACK
#define WRCALLBACKDECL

#ifdef __LITTLE_ENDIAN__
#define WR_LITTLE_ENDIAN
#endif
#ifdef __BIG_ENDIAN__
#define WR_BIG_ENDIAN
#endif

#else // MACINTOSH

/* Unix platform */
#if defined(__unix__) || defined(unix)

#ifndef WR_UNIX_ENV
#define WR_UNIX_ENV
#endif

#if (!defined(__sun__) && !defined(__hpux) && !defined(_AIX))
#include <features.h>
#endif

/* Byte order */
#include <ctype.h>
#if defined(__sparc__) || defined (__hpux) || defined(_AIX)
#	define WR_BIG_ENDIAN
#elif defined(__i386__) || defined(__x86_64__) || defined(__ia64__) || \
(defined(__mips__) && defined(__MIPSEL__)) || \
	defined(__alpha__) || defined(__alpha) || \
defined(__SYMBIAN32__) || defined(__arm__)
#	define WR_LITTLE_ENDIAN
#else
#include <endian.h>
#	if __BYTE_ORDER == __LITTLE_ENDIAN
#		define WR_LITTLE_ENDIAN
#	elif __BYTE_ORDER == __BIG_ENDIAN
#		define WR_BIG_ENDIAN
#	else
#		error Byte order unknown.
#	endif
#endif     

/* GNU/Linux/Sun/HPUX/AIX */
#if defined(__gnu_linux__) || defined(__linux__) || defined(__sun__) || defined (__hpux) ||defined(_AIX)

/* The import-export directives */
#define WRSERVICES_DECL
#define WREXPORT
#define WRSTDCALL
#define WREXPORTPTR
#define WRCALLBACK
#define WRCALLBACKDECL

#else
#error unix variant not supported

#endif //GNU/Linux/Sun/HPUX/AIX

#else
#error platform not supported
#endif // __unix__
#endif // MACINTOSH
#endif // _WIN32

template <class T>					
inline void WRUNUSED(const volatile T&)	{}		// Note that this generates no code on Mac or Win (if inlining is on).

#ifdef WR_LITTLE_ENDIAN
#define WR_SWAP_SHORT(x) ((((x) & 0xFF00) >> 8) | ((x) << 8))
#else
#define WR_SWAP_SHORT(x) (x)
#endif
// Shared library support
#if defined(WR_WIN_ENV)
	#define	WR_DLLEXPORT	__declspec(dllexport)
	#define	WR_DLLIMPORT	__declspec(dllimport)
	#define WR_DLLLOCAL
	#define WR_DLLPUBLIC
#elif defined(WR_MAC_ENV)
	#define WR_DLLIMPORT
	#ifdef GCC_HASCLASSVISIBILITY
		#define WR_DLLEXPORT	__attribute__ ((visibility("default")))
		#define WR_DLLLOCAL		__attribute__ ((visibility("hidden")))
		#define WR_DLLPUBLIC	__attribute__ ((visibility("default")))
	#else
		#define WR_DLLEXPORT
		#define WR_DLLLOCAL
		#define WR_DLLPUBLIC
	#endif
#elif defined(AIX_PLATFORM) || defined(HP_PLATFORM) || defined(LINUX_PLATFORM) || defined(SOLARIS_PLATFORM)	
	#define	WR_DLLIMPORT	
        #ifdef GCC_HASCLASSVISIBILITY
           #define WR_DLLEXPORT  __attribute__ ((visibility("default")))
           #define WR_DLLLOCAL   __attribute__ ((visibility("hidden")))
           #define WR_DLLPUBLIC  __attribute__ ((visibility("default")))
        #else
          #define WR_DLLEXPORT
	  #define WR_DLLLOCAL
	  #define WR_DLLPUBLIC
        #endif
#else
	#error Unsupported Platform	
#endif
#endif // __WRConfig__
