//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/files/MResourceAccess.cpp $
//  
//  Owner: robin briggs
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

#include "MResourceAccess.h"
#include "IWidgetParent.h"
#include "IControlView.h"
#include "ISysFileData.h"
#include "Trace.h"
#include "IPlugIn.h"
#include "IPlugInList.h"
#include "ISession.h"
#include "PMString.h"

//========================================================================================
//	Class MResourceAccess
//	
//	A copy of this implementation is linked into in EVERY plugin, so that each plugin
//	can have its own copy of gPluginResourceFileInfo.
//========================================================================================

// Refers to the resource file associated with every plugin
MResourceAccess::ResourceFileInfo MResourceAccess::gPluginResourceFileInfo = { kTrue, 0, -1, kFalse, NULL, NULL};

#ifdef DEBUG
	extern int64 ts_TotalNumResourceAccesses;
#endif

MResourceAccess::MResourceAccess() :
	MBaseResourceAccess(&gPluginResourceFileInfo)
#ifdef DEBUG
	,fOldNumResAccesses(ts_TotalNumResourceAccesses)
#endif	
{
}

MResourceAccess::MResourceAccess(const IDFile *resourceFile) :
	MBaseResourceAccess(resourceFile, &gPluginResourceFileInfo)
#ifdef DEBUG
	,fOldNumResAccesses(ts_TotalNumResourceAccesses)
#endif	
{
}

MResourceAccess::MResourceAccess(const CFBundleRef bundleRef) :
	MBaseResourceAccess(bundleRef, &gPluginResourceFileInfo)
#ifdef DEBUG
	,fOldNumResAccesses(ts_TotalNumResourceAccesses)
#endif	
{
}

MResourceAccess::MResourceAccess(PluginID plugin) :
	MBaseResourceAccess(plugin, &gPluginResourceFileInfo)
#ifdef DEBUG
	,fOldNumResAccesses(ts_TotalNumResourceAccesses)
#endif	
{
}

MResourceAccess::~MResourceAccess()
{
#ifdef DEBUG
	ASSERT_MSG(fOldNumResAccesses< ts_TotalNumResourceAccesses,"No resources accessed - do you need this resource enabler?");
#endif	
}


void MResourceAccess::SetResourceFile(const IDFile *theFile)
{
	//
	// This is used to setup a global  resource file for this module.  Its really meant to be called only once.
	//
	ASSERT_MSG( gPluginResourceFileInfo.fOpenCount <= 0, "SetResourceFile: Cannot set a  global resource file; The current one is in use/open" );
	
	gPluginResourceFileInfo.fOpenCount = 0;	
	gPluginResourceFileInfo.fRefNum = -1;

	if (theFile)
	{
		*gPluginResourceFileInfo.fRsrcFile = *theFile;
		gPluginResourceFileInfo.fUseBundle = kFalse;
		gPluginResourceFileInfo.fDefaultAccess = kFalse;
	}
	else 
		gPluginResourceFileInfo.fDefaultAccess = kTrue;
}

void MResourceAccess::SetPluginBundle(const CFBundleRef bundleRef)
{
	//
	// This is used to setup a global  resource file for this module.  Its really meant to be called only once.
	//
	ASSERT_MSG( gPluginResourceFileInfo.fOpenCount <= 0, "SetPluginBundle: Cannot set a  global resource file; The current one is in use/open" );
	
	gPluginResourceFileInfo.fOpenCount = 0;	
	gPluginResourceFileInfo.fRefNum = -1;

	if (bundleRef)
	{
		gPluginResourceFileInfo.fBundleRef = bundleRef;
		gPluginResourceFileInfo.fUseBundle = kTrue;
		gPluginResourceFileInfo.fDefaultAccess = kFalse;
	}
	else 
		gPluginResourceFileInfo.fDefaultAccess = kTrue;
}

MResourceAccessCleanerUpper::MResourceAccessCleanerUpper(char * dylibName) 
: fDylibName(dylibName) 
{
#ifdef MAC_RUNTIME_DEBUG
	char buffer[512];
	strcpy(&buffer[1], "Dylib StaticConstructor: ");
	if (fDylibName)
		strcat(&buffer[1], fDylibName);
	buffer[0] = strlen(&buffer[1]);
	DebugStr((const unsigned char*) buffer);
#endif
}

MResourceAccessCleanerUpper::~MResourceAccessCleanerUpper()
{
#ifdef MAC_RUNTIME_DEBUG
	char buffer[512];
	strcpy(&buffer[1], "Dylib StaticDestructor: ");
	if (fDylibName)
		strcat(&buffer[1], fDylibName);
	buffer[0] = strlen(&buffer[1]);
	DebugStr((const unsigned char*) buffer);
#endif

	if (MResourceAccess::gPluginResourceFileInfo.fRsrcFile)
		delete MResourceAccess::gPluginResourceFileInfo.fRsrcFile;
}
