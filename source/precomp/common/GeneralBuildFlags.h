//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/precomp/common/GeneralBuildFlags.h $
//  
//  Owner: Lonnie Millett
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/10 09:08:52 $
//  
//  $Revision: #3 $
//  
//  $Change: 1088733 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  ADOBE CONFIDENTIAL
//  
//  For CodeWarrior the symbol __INTEL__ is defined if building for Windows.
//  If using Visual C++ then _MSC_VER is defined. [amb-cwi86]
//  
//  make sure we get MACINTOSH or WINDOWS defined correctly for ODFRC
//  
//========================================================================================

#pragma once
#ifdef __ODFRC__
	#ifdef __WINDOWS__
		#ifndef WINDOWS
			#define WINDOWS 1
		#endif
	#else
		#ifndef MACINTOSH
			#define MACINTOSH 1
		#endif
	#endif
#endif

#if defined _WIN32 && defined _MSC_VER
	// The Microsoft Visual C++ compiler is being used to generate
	// code for the WIN32 platform.
	//
	// The Visual C++ compiler by default defines WIN32 and _WINDOWS but
	// we don't need these defined in the project settings.  Instead we
	// count on the fact that the compiler internally defines _WIN32 and
	// _MSC_VER.  We define WINDOWS ourself right here.

#define WINDOWS 1

#ifndef PMRESOURCE
#include "VCSettings.h"
#endif

#elif defined UNIX

#elif !defined WINDOWS && !defined __INTEL__
	// Building for Macintosh
//pragma once on - causes boost problems and weird behaviour
#define MACINTOSH 1
#endif

// Move the actual compiler macros to a central location - djb
//	see http://gcc.gnu.org/wiki/Visibility
#ifdef __GNUC__
	#define DLL_IMPORT_DECL __attribute__ ((visibility("default")))
	#define DLL_EXPORT_DECL __attribute__ ((visibility("default")))
	#define LOCAL_DECL 	__attribute__ ((visibility("hidden")))
	#define INTERFACE_DECL 	__attribute__ ((visibility("default")))
#elif defined _WIN32 && defined _MSC_VER
	#define DLL_IMPORT_DECL __declspec(dllimport)
	#define DLL_EXPORT_DECL __declspec(dllexport)
	#define LOCAL_DECL
	#define INTERFACE_DECL
#endif

// This keyword is for code that is obsolete, but is present so that client
// code can still run. We anticipate that what is DEPRECATED in version x, 
// will be removed completely in version x + 1.
#define ID_DEPRECATED

#define USEPMTYPES 1
#define SKIPOMPARSE 1
#if !defined(OLDROUTINENAMES)
	#define OLDROUTINENAMES	0
#endif

// Should undef (i.e. comment out) before product ships!!!
// See comments in PMNew.cpp about this flag. This flag is for internal use only and should not be defined in 3rd party plug-ins.
//#define INTERNAL_TEST_WITH_PLATFORM_ALLOCATOR 1

// Turned OFF on 09 November, 2020 for 16.0.1
//#define PRERELEASE	1		//Please undef before product ships!!!

// Use this flag to create a build that will turn off the
// "edited with prerelease" flag in the Content Manager.
#define BRIDGEBUILD	0

// Turned OFF on 9 November, 2020 for 16.0.1
// Should undef before product ships!!!
//#define BENCHMARK_ONLY 1  //Used for benchmark specific code

#ifdef DEBUG

    #define ID_ENABLE_DEBUGGING 1
    #undef  DISABLE_TRACE_MENU          // not meaningful for debug builds, defined for release builds
    #undef  DISABLE_ASSERT_PROMPTS      // not meaningful for debug builds, defined for release builds

#else // Release

//Internal use: Turn on to get some debugging features to work in release builds (e.g. traces, asserts). Requires complete recompilation of code
//Turn off before shipping
//    #define ID_ENABLE_DEBUGGING         1

    #if defined (ID_ENABLE_DEBUGGING)
        #define DISABLE_TRACE_MENU      1   // disable traces menu in release build.
        #define DISABLE_ASSERT_PROMPTS  1   // disable assert prompts in release build.
    #endif // ID_ENABLE_DEBUGGING

#endif // DEBUG

#if defined(ID_ENABLE_DEBUGGING) // following are commnon to debug and release

//    #define ENABLE_ALL_TRACES           1   // enable this flag only to log all type of traces in a special folder
//    #define ENABLE_TRACE_FILES_DIVISION 1   // enable this to put trace logs in individual files, with name same as category and works with ENABLE_ALL_TRACES

    #if !defined (DISABLE_TRACE_MENU)
        #define ENABLE_TRACE_MENU       1   // enable traces menu if the disabling is off.
    #endif


//    #define TRACE_TEXT_M2M_VALIDATION   1   // enable this flag to let Text subsystem do the special m2m validation and log appropriately

#endif // ID_ENABLE_DEBUGGING

//#define REMOVED_JBX_FOR_CS3	1	// Used for jbx
//#ifndef qME
//#define qME 1
//#endif
#if !defined(qME)
#define DISPLAY_CELLS_IN_STORY 1
#endif

