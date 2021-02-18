//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MBaseResourceAccess.h $
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

#pragma once
#ifndef __MBaseResourceAccess__
#define __MBaseResourceAccess__

#include "IResourceAccess.h"	
#include <boost/shared_ptr.hpp>

// Forward declares
class PMString;
class ResourceLock;

/** Macintosh implementation class behind MResourceAccess.

		MResourceAccess is a shallow implementation that is compiled into every plugin and shared library
		so that every plugin has it's own copy of the static data used to retain the resource file information
		for a plugin. MBaseResourceAccess contains the majority of the actual implementation.
		
		@see ResourceEnabler, MResourceAccess
*/
class PUBLIC_DECL MBaseResourceAccess : public IResourceAccess
{
public:

	/** Data structure used to keep track of the resource file info for a plugin or shared library */
	struct ResourceFileInfo {
		/** a flag to indicate that a resource file was not specified */
		bool16 fDefaultAccess;	
		/** how many clients have the resource file open */
		int16 fOpenCount;
		/** refnum of the resource file, if open */
		ResFileRefNum fRefNum;
		/** Is this plugin bundled  */
		bool16 fUseBundle;
		/** the plugin's resource file */
		IDFile* fRsrcFile;
		/** the plugin's bundle */
		CFBundleRef fBundleRef;
	};
	
	/** Unused - implementation simply asserts */
	MBaseResourceAccess();
	/** Uses the resource file local to the plugin containing the call (passed in resFileInfo).
			Assertion violation if SetResourceFile or SetPluginBundle hasn't been called.
	*/
	MBaseResourceAccess(ResourceFileInfo* resFileInfo);
	/** Uses the specified resource file.
			Assumes that the IDFile* will be valid as long as "this" is valid.
	*/
	MBaseResourceAccess(const IDFile *resourceFile, ResourceFileInfo*);
	/** Uses the specified bundle's resources.
			Assumes that the CFBundleRef will be valid as long as "this" is valid.
	*/
	MBaseResourceAccess(const CFBundleRef bundleRef, ResourceFileInfo*);
	/** Uses the specified plugin's resources.
			Assumes that the plugin is loaded as long as "this" is valid.
	*/
	MBaseResourceAccess(PluginID plugin, ResourceFileInfo*);

	/** Closes the resource file (or caches it). */
	virtual ~MBaseResourceAccess();
	
	/** Retrieves the resource file - note that there will not be one if a Mac based plugin is bundled. */
	virtual const IDFile *GetResourceFile();

	/** Retrieves the resource file info which can be used to determine if a resource file or bundle is being used
			and to obtain them.
	*/
	ResourceFileInfo*		GetResourceFileInfo() { return(fResourceFileInfo); }
	
	/** Called during runtime initialization to set up the resource file for the application. Should only be called once. 
	*/
	static void SetAppResource(const int16 appRefNum);

private:
	static int16 	gAppRefNum;	// refNum for the applications resource file (always open).

	void OpenResourceFileWithRetry();
	bool16 OpenResourceFile();
	void CloseResourceFile();

	ResourceFileInfo	*fPluginResourceFileInfo;
	ResourceFileInfo 	*fResourceFileInfo;
	int16 fPreviousRefNum;
	
	boost::shared_ptr<ResourceLock> fResourceLock; // needed because of the shared global resource handler
};

#endif // __MPlugInResourceAccess__
