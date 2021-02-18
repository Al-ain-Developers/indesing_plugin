//========================================================================================
//
//	File:	ShukHeaders.cp
//
//	Author: ?
//
//	Date:	
//
//	$Revision: #2 $
//
//	$Header: //depot/devtech/16.0.x/plugin/source/precomp/common/ShukHeaders.cp#2 $
//
//	Copyright 1997 Adobe Systems Incorporated. All rights reserved. 
//
//========================================================================================
#ifndef __ShukHeaders_cp__
#define __ShukHeaders_cp__

#include <boost/config.hpp>

#if defined WINDOWS
#include "WShukHeaders.h"
#elif defined MACINTOSH
#ifndef INCLUDED_MEMORY_STATICS
// Each prefix header needs to #include "MemoryStatics.h" very early so that we get
// our always_inline definition of new and delete.  If that is forgotten, and we don't get
// those definitions, we might end up calling the runtime library's new/delete.  Resulting
// new/delete mismatches will be reported as leaks in the debug build and that's annoying.
#error No custom new/delete definitions.  Did you forget to #include "MemoryStatics.h" as the first thing in the prefix header for your project?
#endif
#include "MShukHeaders.h"
#elif defined UNIX
#include "UShukHeaders.h"
#else
#endif

#include "AnsiBasedTypes.h"

#include "StaticReference.h"

#include "PMTypes.h"
#include "CrossPlatformTypes.h"
#include "K2Assert.h"
#include "PMUtils.h"

#include "IPMUnknown.h"

#include "InterfacePtr.h"

#include "OMFactoryCtor.h"
#include "K2Vector.h"
#include "PMReal.h"
#include "PMMatrix.h"
#include "CmdUtils.h"
#include "HelperInterface.h"
#include "CPMUnknown.h"
#include "CreateObject.h"

#include "IDPath.h"
#include "IDFile.h"

#endif
