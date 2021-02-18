//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/files/WResourceAccess.cpp $
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
//========================================================================================

#include "WResourceAccess.h"

WResourceAccess::ResourceFileInfo WResourceAccess::gPluginResourceFileInfo;

WResourceAccess::WResourceAccess() :
	WBaseResourceAccess( &gPluginResourceFileInfo )
{
}

WResourceAccess::WResourceAccess(IDFile *resourceFile) :
	WBaseResourceAccess( resourceFile, &gPluginResourceFileInfo )
{
}

WResourceAccess::WResourceAccess(PluginID pluginID) :
	WBaseResourceAccess( pluginID, &gPluginResourceFileInfo )
{
}

WResourceAccess::~WResourceAccess()
{
}


void WResourceAccess::SetResourceFile(const IDFile *theFile)
{
	//
	// This is used to setup a global  resource file for this module.  Its really meant to be called only once.
	//
		ASSERT_MSG( gPluginResourceFileInfo.fOpenCount <= 0, "SetResourceFile: Cannot set a  global resource file; The current one is in use/open" );
		
		gPluginResourceFileInfo.fOpenCount = 0;	
		gPluginResourceFileInfo.fResourceHandle = NULL;

	if (theFile)	{
		gPluginResourceFileInfo.fRsrcFile = *theFile;
		gPluginResourceFileInfo.fDefaultAccess = kFalse;
	}else 
		gPluginResourceFileInfo.fDefaultAccess = kTrue;

}


