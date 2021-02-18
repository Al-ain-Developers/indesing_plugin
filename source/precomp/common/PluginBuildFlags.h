//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/precomp/common/PluginBuildFlags.h $
//  
//  Owner: Lonnie Millett
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

#pragma once

#include "GeneralBuildFlags.h"

#define RUNTIME_DECL 		DLL_IMPORT_DECL
#define PUBLIC_DECL			DLL_IMPORT_DECL
#define DATABASE_DECL		DLL_IMPORT_DECL
#define TESTLIB_DECL		DLL_IMPORT_DECL
#define WIDGET_DECL			DLL_IMPORT_DECL
#define DV_WIDGET_DECL		DLL_IMPORT_DECL

#define PLUGIN_DECL			DLL_EXPORT_DECL

#define TEXTPANELLIB_DECL	DLL_IMPORT_DECL
#define FDTLIB_DECL			DLL_IMPORT_DECL
#define INCOPYLIB_DECL		DLL_IMPORT_DECL
#define PATHTYPELIB_DECL	DLL_IMPORT_DECL

// Used to explicitly set visibility of local classes/structs to appease GCC 4.2
#define PRIVATE_DECL		LOCAL_DECL

// PLUGIN enables correct resource and quickdraw global access.
// While a plugin is in fact a shared library, PLUGIN is considered
// less strict than using the symbol SHAREDLIBRARY, which is also
// used to turn off some application specific behavior in plugins
// (such as the installation of test menus).
#define PLUGIN 1
