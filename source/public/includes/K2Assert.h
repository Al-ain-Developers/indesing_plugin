//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2Assert.h $
//  
//  Owner: ???
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
//  
//  Summary:   	Debugging functions and macros.
//  Written by: Jesse Jones (from Whisper)
//  
//  Abstract:	This file provides the following macros:
//  
//  ASSERT(p) - No-op in release builds. In debug builds drops into the
//  debugger if p is false.
//  
//  COMPILE_CHECK(p) - An ASSERT that fires at compile time. This is useful
//  for doing things like verifying the layout of items within a struct.
//  Note that this check is also done in release builds.
//  
//  ASSERT_MSG(predicate, str) - Drops into the debugger 
//  if p is false, and displays the string.
//  
//  ASSERT_UNIMPLEMENTED() - Drops into the debugger and
//  displays a string saying "Unimplemented function in [file] at [line]".
//  
//  ASSERT_FAIL(formatStr) - Drops into the debugger, and displays 
//  the string.
//  
//  FORMAT_ARGS(formatStr, arg1, arg2, ...) - Does printf-style formatting on the 
//  arguments, and returns the resulting string. Used in confunction with
//  ASSERT_MSG and ASSERT_FAIL when you want formatted output, e.g.:
//  ASSERT_MSG(!success, FORMAT_ARGS("Operation %s failed! Try %s.", opName, tryName));
//  
//========================================================================================

#pragma once
#ifndef K2ASSERT_H
#define K2ASSERT_H

#if defined(DEBUG)
#ifndef ID_ENABLE_DEBUGGING
#error ID_ENABLE_DEBUGGING is not defined in DEBUG.
#endif
#endif

#include "OMTypes.h"

#pragma export on

#if !defined( _lint) && !defined( __GNUC__)
	#define COMPILE_CHECK(p)				{struct _CC {char a[(p) ? 1 : -1];};} 0
#else
	#define COMPILE_CHECK(p)					
#endif

//#ifdef PRERELEASE

#ifdef ID_ENABLE_DEBUGGING
#ifdef MACINTOSH
	typedef void (*ShowAssertFnc)(const char* msg);
	RUNTIME_DECL void ClientShowAssert(const char* msg);
	RUNTIME_DECL void ServerShowAssert(const char* msg);
#endif
#ifdef WINDOWS
	typedef void (*ShowAssertFnc)(const char* mesg, const char* file, int32 line);
	RUNTIME_DECL void ClientShowAssert(const char* mesg, const char* file, int32 line);
	RUNTIME_DECL void ServerShowAssert(const char* mesg, const char* file, int32 line);
#endif
	RUNTIME_DECL void InitializeDebugging(ShowAssertFnc showAssertFnc);	
	RUNTIME_DECL void TerminateDebugging();	
	
	RUNTIME_DECL void BreakToDebugger();			
	RUNTIME_DECL void BreakStrToDebugger(const char* mesg, const char* file = nil, int32 line = 0);
	
	RUNTIME_DECL bool16 IsDebuggerRunning();

	class DebugLog;
	RUNTIME_DECL DebugLog& GetTraceLog();				// contains a list of sinks used by trace, and optionally, asserts
	RUNTIME_DECL bool16 GetLogAsserts();				// asserts will be logged via ::GetTraceLog(), defaults to false
	RUNTIME_DECL void SetLogAsserts(bool16 arg);		// asserts will be logged via ::GetTraceLog(), defaults to false
	RUNTIME_DECL bool16 GetBreakOnAssert();			// asserts will cause the app to break, defaults to true
	RUNTIME_DECL void SetBreakOnAssert(bool16 val);			// asserts will cause the app to break, defaults to true

	RUNTIME_DECL bool16 GetIntenseDebugging();						// enables costly debug checks, defaults to false
	RUNTIME_DECL void SetIntenseDebugging(bool16 intense);			// enables costly debug checks, defaults to false
	RUNTIME_DECL bool16 GetDisableCloseVerify();					// disable pub verification on close
	RUNTIME_DECL void SetDisableCloseVerify(bool16 disable);		// disable pub verification on close
	RUNTIME_DECL bool16 GetSuppressDebugUI();						// disable any debug UI - used for buildacceptance loop to avoid blocking UI
	RUNTIME_DECL void SetSuppressDebugUI(bool16 suppress);			// disable any debug UI - used for buildacceptance loop to avoid blocking UI
		
		// C++ style assert
	RUNTIME_DECL void ASSERT_STD_FUNC(const char* message, const char* file, int32 line);
	#define ASSERT(p)						!(p) ? ASSERT_STD_FUNC(#p, __FILE__, __LINE__) : (void) 0

		// Assert with standard string for unimplemented functionality
	#define ASSERT_UNIMPLEMENTED()			ASSERT_UNIMPLEMENTED_FUNC(__FILE__, __LINE__)
	RUNTIME_DECL void ASSERT_UNIMPLEMENTED_FUNC(const char* file, int32 line);

		// Asserts with user-defined messages
	RUNTIME_DECL char *FORMAT_ARGS(const char *msg, ...);		
	RUNTIME_DECL void ASSERT_FUNC(const char* str, const char* file, int32 line);
	#define ASSERT_MSG(p,msg)  !(p) ? ASSERT_FUNC((msg), __FILE__, __LINE__) : (void) 0
	#define ASSERT_FAIL(msg)		ASSERT_FUNC((msg),  __FILE__, __LINE__)

#else

    #define ASSERT_MSG(p, msg)				((void) 0)
	#define	ASSERT(p)						((void) 0) 
	#define ASSERT_UNIMPLEMENTED()	 		((void) 0) 
	#define ASSERT_FAIL(msg)				((void) 0) 	

#endif


#pragma export off

#endif	// K2ASSERT_H
