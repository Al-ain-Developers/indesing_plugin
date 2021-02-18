//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/statics/AATPlugInStatics.cpp $
//  
//  Owner: Kristina Roberts
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCAATPlugInHeaders.h"

// ----- On Windows we can't compile these files into a library that is used both
//		 from plugins and from public because of the way exports work. So this file
//		 is set up to compile them for plugins, and PublicStatics.cpp is set up to
//		 compile them for public. [amb]

#include "AATXMLTagDefs.cpp"
#include "QAFileXMLTagDefs.cpp"
#include "CAATDataWidgetGroupDefs.cpp"

// ----- From PubPlugIn.lib.

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
