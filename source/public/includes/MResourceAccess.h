//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MResourceAccess.h $
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
#ifndef __MResourceAccess__
#define __MResourceAccess__

#include "MBaseResourceAccess.h"

// This is required for the linker due to the friend declarations below.
extern "C" {
	void InitConnection();
	void TerminateConnection();
}

/** Macintosh implementation class behind the ResourceEnabler #define.

		MResourceAccess is a shallow implementation that is compiled into every plugin and shared library
		so that every plugin has it's own copy of the static data used to retain the resource file information
		for a plugin. MBaseResourceAccess contains the majority of the actual implementation.
		
		@see ResourceEnabler, MBaseResourceAccess
*/
class MResourceAccess : public MBaseResourceAccess
{
public:
	/** Uses the resource file local to the plugin containing the call.
			Assertion violation if SetResourceFile or SetPluginBundle hasn't been called.
	*/
	MResourceAccess();
	/** Uses the specified resource file.
			Assumes that the IDFile* will be valid as long as "this" is valid.
	*/
	MResourceAccess(const IDFile *resourceFile);
	/** Uses the specified bundle's resources.
			Assumes that the CFBundleRef will be valid as long as "this" is valid.
	*/
	MResourceAccess(const CFBundleRef bundleRef);
	/** Uses the specified plugin's resources.
			Assumes that the plugin is loaded as long as "this" is valid.
	*/
	MResourceAccess(PluginID plugin);

	/** Closes the resource file (or caches it). */
	~MResourceAccess();
	
	/** Called by the runtime to set up the resource file for a shared library. */
	static void SetResourceFile(const IDFile *rsrcFileLocation);
	/** Called by the runtime to set up the bundle for a plugin. */
	static void SetPluginBundle(const CFBundleRef bundleRef);
		
private:
	// The IDFile pointer in gPluginResourceFileInfo needs to be allocated very
	// early in InitConnection() and deallocated in TerminateConnection(). Make
	// the functions friends to give them access to gPluginResourceFileInfo.
	friend class PlugIn;
	friend class MResourceAccessCleanerUpper;
	friend void InitConnection();
	static ResourceFileInfo 	gPluginResourceFileInfo;

#ifdef DEBUG
	int32 fOldNumResAccesses; // to catch unneeded usages
#endif
};

// Used by the runtime to destruct the static MResourceAccess::gPluginResourceFileInfo a bit earlier than usual, 
//	to aid our leak tracking code.
class MResourceAccessCleanerUpper
{
public:
	MResourceAccessCleanerUpper(char * dylibName = nil);
	~MResourceAccessCleanerUpper();
	
	char* fDylibName;
};


#endif // __MResourceAccess__
