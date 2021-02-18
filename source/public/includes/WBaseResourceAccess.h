//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WBaseResourceAccess.h $
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

#pragma once
#ifndef __WBASERESOURCEACCESS__
#define __WBASERESOURCEACCESS__


#include "IResourceAccess.h"
#include "IDFile.h"
#include <boost/thread/recursive_mutex.hpp>

class IControlView;

#pragma export on

/** Windows implementation class behind WResourceAccess.

		WResourceAccess is a shallow implementation that is compiled into every plugin and shared library
		so that every plugin has it's own copy of the static data used to retain the resource file information
		for a plugin. WBaseResourceAccess contains the majority of the actual implementation.
		
		@see ResourceEnabler, WResourceAccess
*/
class PUBLIC_DECL WBaseResourceAccess : public IResourceAccess
{
public:
	/** Data structure used to keep track of the resource file info for a plugin or shared library */
	class PUBLIC_DECL ResourceFileInfo
	{
		public:
			ResourceFileInfo();
			bool16 fNoOp;
			/** a flag to indicate that a resource file was not specified */
			bool16 fDefaultAccess;	
			/** how many clients have the resource file open */
			int16 fOpenCount;
			/** refnum of the resource file, if open */
			HRSRC fResourceHandle;
			/** the plugin's resource file */
			IDFile fRsrcFile;	
	};	
	
	/** Unused - implementation simply asserts */
	WBaseResourceAccess();
	/** Uses the resource file local to the plugin containing the call (passed in resFileInfo).
			Assertion violation if SetResourceFile or SetPluginBundle hasn't been called.
	*/
	WBaseResourceAccess(ResourceFileInfo*);
	/** Uses the specified resource file.
			Assumes that the IDFile* will be valid as long as "this" is valid.
	*/
	WBaseResourceAccess(IDFile *resourceFile, ResourceFileInfo*);
	/** Uses the specified plugin's resources.
			Assumes that the plugin is loaded as long as "this" is valid.
	*/
	WBaseResourceAccess(const PMString& pluginName, ResourceFileInfo*);
	/** Uses the specified plugin's resources.
			Assumes that the plugin is loaded as long as "this" is valid.
	*/
	WBaseResourceAccess(PluginID pluginID, ResourceFileInfo*);

	/** Closes the resource file (or caches it). */
	virtual ~WBaseResourceAccess();
	
	/** Retrieves the resource file. */
	virtual const IDFile *GetResourceFile();

	/** Retrieves the resource file info.
	*/
	ResourceFileInfo *GetResourceFileInfo() { return(fResourceFileInfo); }

	/** Retrieves the current resource handle.
	*/
	HRSRC GetResourceHandle() const;

private:
		void OpenResourceFile();
		void CloseResourceFile();

		ResourceFileInfo *fResourceFileInfo;
		ResourceFileInfo *fPluginResourceFileInfo;
		HRSRC fPreviousResourceHandle;

		// Lock to block multiple threads to access resources in the same time
		// This is not really needed on Windows - we should remove this when we will get rid of the shared handle
		// and make resources accessible only from ResourceEnablers
		class ResourceLock : private boost::noncopyable
		{
		public:
			ResourceLock(boost::recursive_mutex& mutex, int32& lockCounter);
			~ResourceLock();
		private:
			boost::recursive_mutex::scoped_lock fLock;
			int32& fCounter;
		};

		ResourceLock fResourceLock; // needed because of the shared global resource handler
};

#pragma export off

#endif
