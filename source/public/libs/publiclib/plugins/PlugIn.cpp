//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/plugins/PlugIn.cpp $
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

#include "PMTypes.h"
#include "PlugIn.h"
#include "ISession.h"
#include "IDFactory.h"
#include "ClassFactory.h"
#include "InterfaceFactory.h"
#include "ResourceEnabler.h"

IPlugIn :: ~IPlugIn()
{
}

PlugIn :: PlugIn() : fPluginID(kInvalidPlugin)
{
}

#ifdef BUILDING_PLUGIN_LIB // this is defined when building PublicPlugin.lib, but not when building PublicDylib.Lib
bool16 gFalse = kFalse;
void DontDeadStrip();
#endif

PlugIn :: ~PlugIn()
{
#ifdef MACINTOSH

#ifdef BUILDING_PLUGIN_LIB
	DontDeadStrip();	// force static constructors & destructors 
	if(MResourceAccess::gPluginResourceFileInfo.fRsrcFile)
		delete MResourceAccess::gPluginResourceFileInfo.fRsrcFile;
#endif

#endif
}


bool16 PlugIn :: LoadAtStartup()
{
	return kFalse;
}


bool16 PlugIn :: Load(ISession* theSession)
{
	#pragma unused(theSession)
	ASSERT_MSG(theSession != nil, "PlugIn::Load - theSession != nil");
		
	return kTrue;
}


void PlugIn :: LoadFactories(PluginID ownerPlugIn, ISession* theSession)
{
	#pragma unused(theSession)
	ASSERT_MSG(theSession != nil, "PlugIn::LoadFactories - theSession != nil");

#ifdef REGISTER_OM_IDS
	IDFactory::InstallIDs(ownerPlugIn);
#endif
	ClassFactory::InstallClasses(ownerPlugIn);
	InterfaceFactory::InstallInterfaces(ownerPlugIn);	
}

bool16 PlugIn::Unload()
{
	//Override this if you want something cool to happen on unloading your plugins
	return kTrue;
}


bool16 PlugIn::CanUnload() const
{
	return kTrue;
}

void PlugIn::SetPluginID(PluginID pluginID)
{
	fPluginID = pluginID;
}

#ifdef MACINTOSH
void PlugIn::SetBundleRef(CFBundleRef bundle)
{
#ifdef BUILDING_PLUGIN_LIB
	MResourceAccess::gPluginResourceFileInfo.fRsrcFile = new IDFile();
	ASSERT_MSG(MResourceAccess::gPluginResourceFileInfo.fRsrcFile != NULL, "MPluginUtils::InitConnection: Unable to allocate global resource file.");
	ASSERT_MSG (bundle != 0,"MPluginUtils::InitConnection: CFBundleCreate failed.");
	if (bundle)
		ResourceEnabler::SetPluginBundle(bundle);
#else
#pragma unused(bundle)
#endif
}
#endif

IDFile PlugIn :: GetResourceFile() const
{
	ResourceEnabler re;
	return *re.GetResourceFile();
}


void PlugIn :: FixUpData(IDocument *) 
{
	// Ignore
}

