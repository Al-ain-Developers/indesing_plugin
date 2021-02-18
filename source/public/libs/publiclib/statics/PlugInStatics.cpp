//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/statics/PlugInStatics.cpp $
//  
//  Owner: Michael Burbidge
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

#include "VCPlugInHeaders.h"

// ----- On Windows we can't compile these files into a library that is used both
//		 from plugins and from public because of the way exports work. So this file
//		 is set up to compile them for plugins, and PublicStatics.cpp is set up to
//		 compile them for public. [amb]

// ----- From PubPlugIn.lib.

#include "MemoryStatics.cpp"
#include "PlugIn.cpp"
#include "WPlugInMain.cpp"
#include "WResourceAccess.cpp"

// ----- From PubStatic.lib.

#include "IDFactory.cpp"
#include "InterfaceFactory.cpp"
#include "ClassFactory.cpp"

#if defined WINDOWS && !defined _CPPUNWIND
// If exceptions are turned off, Boost requires this.
#include "throw_exception.cpp"
#endif
