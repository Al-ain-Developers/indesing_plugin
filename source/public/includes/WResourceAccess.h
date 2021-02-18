//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WResourceAccess.h $
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
//========================================================================================

#pragma once
#ifndef __WRESOURCEACCESS__
#define __WRESOURCEACCESS__


#include "WBaseResourceAccess.h"

/** Windows implementation class behind the ResourceEnabler #define.

		WResourceAccess is a shallow implementation that is compiled into every plugin and shared library
		so that every plugin has it's own copy of the static data used to retain the resource file information
		for a plugin. WBaseResourceAccess contains the majority of the actual implementation.
		
		@see ResourceEnabler, MBaseResourceAccess
*/
class WResourceAccess : public WBaseResourceAccess
{
public:
	/** Uses the resource file local to the plugin containing the call.
			Assertion violation if SetResourceFile hasn't been called.
	*/
	WResourceAccess();
	/** Uses the specified resource file.
			Assumes that the IDFile* will be valid as long as "this" is valid.
	*/
	WResourceAccess(IDFile *resourceFile);
	/** Uses the specified plugin's resources.
			Assumes that the plugin is loaded as long as "this" is valid.
	*/
	WResourceAccess(PluginID pluginID);
	
	/** Closes the resource file (or caches it). */
	~WResourceAccess();
	
	/** Called by the runtime to set up the resource file for a shared library or plugin. */
	static void SetResourceFile(const IDFile *rsrcFileLocation);

private:
		static ResourceFileInfo gPluginResourceFileInfo;
};


#endif
