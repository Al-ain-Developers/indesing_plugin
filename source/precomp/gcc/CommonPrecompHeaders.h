//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/precomp/gcc/CommonPrecompHeaders.h $
//  
//  Owner: Dave Burnard
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#include "GeneralBuildFlags.h"
#include "MemoryStatics.h"
#include "AnsiBasedTypes.h"

#ifdef MACINTOSH
#include "MacOSSDK_AvoidTypeCollisions.h"

//#include <Carbon/Carbon.h>
#define ID_NOCARBON_ALLOWED //#define to denote remaining Carbon code and references.
#define __CARBON__ //Prevent Carbon from being included
#define __DRAG__ //Prevent Drag manager from being included
#define __HIDATABROWSER__ //Prevent Drag manager from being included

#include <ApplicationServices/ApplicationServices.h> //CoreGraphics, CoreText, HIShape, Pasteboard Manager
//#include <ApplicationServices/../Frameworks/CoreGraphics.framework/Headers/CoreGraphics.h>
//#include <ApplicationServices/../Frameworks/HIServices.framework/Headers/HIShape.h>	//HIShape
//#include <ApplicationServices/../Frameworks/HIServices.framework/Headers/Pasteboard.h>	//Pasteboard Manager

#include <Carbon/../Frameworks/OpenScripting.framework/Headers/AppleScript.h> // OpenScripting/AppleScript

#include <Carbon/../Frameworks/HIToolbox.framework/Headers/CarbonEventsCore.h> // for EventRef

#ifdef ID_UI_PRECOMPILE
	#include <Cocoa/Cocoa.h>
#endif

#endif
