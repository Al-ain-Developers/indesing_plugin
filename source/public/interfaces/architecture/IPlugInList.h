//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPlugInList.h $
//  
//  Owner: Robin Briggs
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
//  Purpose:
//  Manages plug-ins: registering, loading, unloading, dependencies, etc.
//  
//========================================================================================

#pragma once
#ifndef __IPLUGINLIST__
#define __IPLUGINLIST__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "IPlugIn.h"

class PMString;
class PlugInData;
class DependencyList;
class IPlugInIterator;
class PluginMetadata;

/**
    The plug-in list maintains a list of all the currently installed plug-ins. It is
    used to manage the plug-ins, and to return information about them. The application,
    and the Public, WidgetBin, and ObjectModel libraries are treated as plug-ins for
    the purposes of the list, and are considered to be "standard components". All items
    on this list can be uniquely identified by PluginID.
    
    There is a single implementation of IPlugInList 
	that is an interface off the global session (kSessionBoss), referenced by session.

	@ingroup arch_om
	@see kSessionBoss
	@see ISession
*/
class IPlugInList : public IPMUnknown	{
public:
	enum { kDefaultIID = IID_IPLUGINLIST };

		/** Look up a plugin by name.
        @param name        The name of the plug-in. 
        @return the PluginID of the plug-in, or kInvalidPlugin if it's not found.
        */
	virtual PluginID GetPluginID(const PMString& name) const = 0;

		/** Return the name of a particular plug-in 
		@param whichPlugIn	PluginID of the plug-in
		@return the name of the plug-in, or an empty string if the plug-in is not found.
		*/
	virtual const PMString& GetPluginName(PluginID whichPlugIn) const = 0;
		
		/** Return the location of the plug-in's executable. 
		@param whichPlugIn	PluginID of the plug-in
		@param path			path of the plug-in is returned here, if it was found
		@return kTrue if the plug-in is found, kFalse otherwise.
		*/
	virtual bool16 GetPathName(PluginID whichPlugIn, IDFile *path) const = 0;
		
#ifdef MACINTOSH
		/** Return a CFBundleRef corresponding to the plug-in. 
		@param whichPlugIn	PluginID of the plug-in
		@param bundleRef			CFBundleRef of the plug-in is returned here, if it was found. Do not Release this.
		@return kTrue if the plug-in is found, kFalse otherwise.
		*/
	virtual bool16 GetCFBundleRef(PluginID whichPlugIn, CFBundleRef& bundleRef) const = 0;
#endif

		/** Return the number of plug-ins in the list. Some of these may not be currently active. 
		@return number of plug-ins currently installed
		*/
	virtual int32 GetPluginCount() const = 0;

		/** Return the n'th plug-in in the list
		@param n	The index of the plug-in
		@return PluginID of the plug-in, if there is one, kInvalidPlugin otherwise.
		*/
	virtual PluginID GetNthPlugin(int32 n) const = 0;

		/** Return true if the supplied plug-in ID is a core component of the application
		@param whichPlugin	The ID of the component or plug-in we want to find out about
		@return kTrue if the pluginID is to the application or Public, WidgetBin, or ObjectModel libraries, return kFalse otherwise.
		*/
	virtual bool16 IsStandardComponent(PluginID whichPlugin) const = 0;
		
		/** Return the plug-in's major and minor version numbers. 
		@param whichPlugIn		The plug-in we want to find out about
		@param majorVersion		Return value: high word of the plug-in's version is returned here
		@param minorVersion		Return value: low word of the plug-in's version is returned here 
		@return kTrue if the plug-in is found, kFalse otherwise
		*/
	virtual bool16 GetVersionNumber(PluginID whichPlugIn, int32& majorVersion, int32& minorVersion) const = 0;

		/** Return the x.y.z.w type version string used for Update Manager versioning
		@param whichPlugIn		The plug-in we want to find out about
		@return The version string of the plug-in, or nil if there was no error.
		*/
	virtual const PMString *GetAUMVersionString(PluginID whichPlugin) const = 0;

		/** Return the format number of the plug-in.
		@param whichPlugIn		The plug-in we want to find out about
		@param majorVersion		Return value: high word of the plug-in's format is returned here
		@param minorVersion		Return value: low word of the plug-in's format is returned here 
		@return kTrue if the plug-in is found, kFalse otherwise
		*/
	virtual bool16 GetLastFormatVersion(PluginID whichPlugin, int32& majorVersion, int32& minorVersion) const = 0;
		/** Return the version of the app the plug-in was built for. The plug-in can run when installed in
		any version of the application whose major version number matches the expected major version number, 
		and whose minor version number is greater to or equal to the expected minor version number.
		@param whichPlugIn		The plug-in we want to find out about
		@param majorVersion		Return value: high word of the application's version is returned here
		@param minorVersion		Return value: low word of the application's version is returned here 
		@return kTrue if the plug-in is found, kFalse otherwise
		*/
	virtual bool16 GetAppExpectedVersionNumber(PluginID whichPlugIn, int32& majorVersion, int32& minorVersion) const = 0;

		/** Returns a magic cookie containing info about the plug-in's dependencies. You can 
		call GetNthComponent and GetNthVersion to get useful info out of the cookie.
		@param whichPlugIn		The plug-in we want to find out about
		@return a dependency list if the plug-in is found and has dependencies, nil otherwise
        @see #GetNthComponent
        @see #GetNthVersion
		*/
	virtual const DependencyList *GetDependentInfo(PluginID whichPlugIn) const = 0;

		/** Returns the PluginID of the i'th component in the dependency info. Call this
			to find out what plug-ins a plug-in is dependent on (after you've already called GetDependentInfo).
		@param dependentInfo		The list of the dependecies from the plug-in we're interested in
		@param n					The index into the list for the particular dependency we want
		@return The pluginID of the n'th plug-in in dependentInfo, of kInvalidPlugin if the index is invalid
		*/
	virtual PluginID GetNthComponent(const DependencyList *dependentInfo, int32 n) const = 0;

		/** Returns the version number of the i'th component in the dependency info. 
		@param dependentInfo		The list of the dependecies from the plug-in we're interested in
		@param n					The index into the list for the particular dependency we want
		@param majorVersion			Return value: high word of the expected version number for the dependency plug-in is returned here
		@param minorVersion			Return value: low word of the expected version number for the dependency plug-in is returned here
		@return kTrue if the index is valid, kFalse otherwise
		*/
	virtual bool16 GetNthVersion(const DependencyList *dependentInfo, int32 n, int32& majorVersion, int32& minorVersion) const = 0;

		/** Return the error string that resulted from loading the plug-in
		@param whichPlugIn		The plug-in we want to find out about
		@return The error string that resulted from loading the plug-in, or nil if there was no error.
		*/
	virtual const PMString *GetErrorString(PluginID whichPlugin) const = 0;

		/** Return the runtime error string that resulted from loading the plug-in
		@param whichPlugIn		The plug-in we want to find out about
		@return The error string that resulted from loading the plug-in, or nil if there was no error.
		*/
	virtual const PMString *GetRuntimeErrorString(PluginID whichPlugin) const = 0;
	
		/** Returns the registration error string, if there was an error registering.
		@param whichPlugIn		The plug-in we want to find out about
		@return The error string that resulted from loading the plug-in, or nil if there was no error.
		*/
	virtual const PMString *GetRegistrationErrorString(PluginID whichPlugin) const = 0;

		/** Returns meta data about the plug-in.
		@param whichPlugIn		The plug-in we want to find out about
		@return PluginMetaData*	The metadata, or nil if either the plug-in wasn't found,
								or the plug-in doesn't have metadata.
		*/
	virtual const PluginMetadata* GetPluginMetadata(PluginID whichPlugin) const = 0;
	
		/** Returns true if the plug-in is loaded. The plug-ins are loaded on demand, so if the
		plug-in has not yet been queried for, then the plug-in is not loaded.
		@param whichPlugIn		The plug-in we want to find out about
		@return kTrue if the plug-in is currently loaded, kFalse otherwise.
		*/
	virtual bool16 IsLoaded(PluginID whichPlugIn) const = 0;

		/** The plug-in failed to load. This will be true only if the system has tried to
		   load the plug-in. It may be false simply because the system hasn't tried to
		   load it yet.
		@param whichPlugIn		The plug-in we want to find out about
		@return kTrue if the plug-in is failed to load, kFalse otherwise.
		*/
	virtual bool16 LoadFailed(PluginID whichPlugIn) const = 0;
		/** Returns true if the plugin has been loaded at least once. Will return false
		   if the plugin failed to load or if the object model hasn't had to load it yet.
		@param whichPlugIn		The plug-in we want to find out about
		@return kTrue if the plug-in is has ever been loaded, kFalse otherwise.
		*/
	virtual bool16 HasBeenLoaded(PluginID whichPlugIn) const = 0;

		/** Returns true if the plugin matches the current product. 
		@param whichPlugIn		The plug-in we want to find out about
		@return kTrue if the plug-in the plugin matches the current product. 
		*/
	virtual bool16 MatchCurrentProduct(PluginID whichPlugIn) const = 0;

		/** Returns true if the plugin matches current feature set. 
		@param whichPlugIn		The plug-in we want to find out about
		@return kTrue if the plug-in the plugin matches the feature set. 
		*/
	virtual bool16 MatchCurrentFeatureSet(PluginID whichPlugIn) const = 0;
		
		/** FOR INTERNAL USE ONLY. Load the plug-in. Opens up the DLL, loads 
			the factories, and calls the plug-in's Load function. The plug-in's 
			root object is returned on success, nil is returned if the load fails.
	    	If the plug-in is already loaded, Load just returns the root object.
		@param whichPlugIn		The plug-in we want to load
		@return The plug-in's IPlugIn* root if the Load is successful, nil otherwise. 
		*/
	virtual IPlugIn *Load(PluginID whichPlugIn) = 0;

		/** FOR INTERNAL USE ONLY. Return an iterator to iterate plug-in list.
			Caller must call delete on the iterator when finished with it.
		*/
	virtual IPlugInIterator *CreateIterator() const = 0;
		
#ifdef DEBUG
	typedef enum UnloadStatus { kUnloadNormal, kUnloadFrequently, kUnloadNever } UnloadStatus;
	virtual void SetUnloadStatus(UnloadStatus status) = 0;
	virtual const PlugInData *GetPlugInData( PluginID pluginID ) const = 0;
	virtual	void Unload(PluginID whichPlugIn) = 0;	
	virtual void Register(PluginID whichPlugin) = 0;
	virtual void Unregister(PluginID whichPlugin) = 0;
#endif

	virtual IPlugIn::ThreadingPolicy GetThreadingPolicy(PluginID whichPlugIn) const = 0;
	/** FOR INTERNAL USE ONLY. Compares the plugin list data from pluginListFile to the current version.  
		@param pluginListFile	Location of plugin-list data file.
		@returns kTrue if the lists are same. kFalse if different.
	*/
	virtual	bool16	ComparePluginListToFileStream(const IDFile& pluginListFile) const = 0;

	/** FOR INTERNAL USE ONLY. Writes the current list of plug-in data to pluginListFile.
		@param pluginListFile	Location of plugin-list data file.
		@returns kSuccess or kFailure.
	*/
	virtual ErrorCode StreamPluginListToFile(const IDFile& pluginListFile) const = 0;

	/** FOR INTERNAL USE ONLY. Loads plug-ins whose threading policy is kMultipleThreads.
	*/
	virtual void LoadMultipleThreadPolicyPlugins() const = 0;
};

	/** FOR INTERNAL USE ONLY
	*/
class IPlugInIterator INHERITFROM
{
	public:
		// This object should be deleted when you are all done with it.
		virtual ~IPlugInIterator() {}

		// An iterator iterates over plugins. Next() returns
		// the plug-in ID of the next plug-in, or kInvalidPlugin if there are
		// no more plug-ins.
		virtual PluginID Next() = 0;
};


#endif // __IPLUGINLIST__
