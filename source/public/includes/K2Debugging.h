//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2Debugging.h $
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
//  Abstract:	This file provides the access to assertions and trace messages.
//  Functions and macros have been moved to K2Assert.h and Trace.h
//  
//========================================================================================

#pragma once
#ifndef K2DEBUGGING_H
#define K2DEBUGGING_H

#include "BaseType.h"

#if MACINTOSH
//	#include <Debugging.h>
	#undef DEBUGSTR
	#undef check	// Debugging.h defines a "check" macro that conflicts with some methods in boost
#endif

#include "K2Assert.h"
#include "Trace.h"


// Synch with ANSI definitions.
#if defined(DEBUG) && defined(NDEBUG)
	#error DEBUG and NDEBUG are out of sync!	
#endif

#if !defined(DEBUG) && !defined(NDEBUG)
	#error DEBUG and NDEBUG are out of sync!				// $$$ need to set NDEBUG in release builds
#endif

// Synch with MSVC.
#if MSVC && defined(DEBUG) != defined(_DEBUG)
	#error DEBUG and _DEBUG are out of sync!
#endif

	
#endif	// K2DEBUGGING_H
