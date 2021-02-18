//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPlugIn.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __IPLUGIN__
#define __IPLUGIN__

class ISession;
class IPlugIn;
class IDocument;

/** GetPlugInFunc is the signature for the single function exported by the
	plug-in. It just exists so the application can get a pointer to the
	plug-in's IPlugIn object and callback to it.
*/
typedef IPlugIn *(*GetPlugInFunc)();


/** Every plug-in must supply an implementation of IPlugIn, although often a 
	plug-in may choose to use the base class PlugIn if there's no need to
	override anything. IPlugIn is the main entry point to the plug-in.
	
	THIS IS NOT A STANDARD BOSS INTERFACE. It does not inherit from IPMUnknown.
	It is a regular C++ object.
	
	If your plug-in has no need to override anything in IPluIn, it can
	just supply the following code:
	
<pre>
#include "PlugIn.h"
#include "GetPlugIn.h"

static PlugIn gPlugIn;

// This is the main entry point from the application to the plug-in.
// The application calls this function when the plug-in is installed 
// or loaded. This function is called by name, so it must be called 
// GetPlugIn, and defined as C linkage.
IPlugIn *GetPlugIn()
{
	return &gPlugIn;
}

	To override the default IPlugIn implementation with your own,
	just have your GetPlugIn function return an IPlugIn that you
	supply. Your IPlugIn should inherit from PlugIn. Here's an
	example:

class MyPlugin : public PlugIn
{
public:
	virtual bool16 CanUnload();
};

static MyPlugin gPlugIn;

IPlugIn *GetPlugIn()
{
	return &gPlugIn;
}
</pre>

	@ingroup arch_om
*/
class IPlugIn INHERITFROM {
public:
	/**
	Enumerates the different types of thread support a plugin can have
	*/
	typedef enum { kUnknownThreadingPolicy=0, kMainThreadOnly=1, kMultipleThreads=2 } ThreadingPolicy;
	/** Called when the application loads the plug-in. Typically a plug-in
		that needs to do some action at startup should use IStartupShutdownService.
		The plug-in should override Load only if there is some global state 
		which, if missing, would cause the plug-in to be useless.
	
		@param theSession pointer to the global session, which is the root
			of the object hierarchy.
		@return bool16 kTrue if plug-in loaded OK, false otherwise. 
	*/
	virtual bool16 Load(ISession* theSession) = 0;
	
	/** Called when the application is shutting down. Typically a plug-in
		that needs to do some action at shutdown should use IStartupShutdownService.
		Under rare circumstances, your plug-in may be asked to Unload if 
		there are certain types of system errors on the Mac. If you want to
		override this and prevent the unload, you need to override CanUnload 
		to return false.

		@return bool16 kTrue 
	*/
	virtual bool16 Unload() = 0;
	
	/** Returns kTrue if the plugin needs to get loaded on every startup.
		Most plug-ins are not loaded at startup, they only get loaded
		the first time they are accessed. You may override this behavior
		and force the plug-in to load at startup by returning true. Note
		that this will introduce a performance penalty to the user, since
		startup will be slower even the user never needed the plug-in.

		@return bool16 kTrue to force plug-in to load at startup.
	*/
	virtual bool16 LoadAtStartup() = 0;
	
	/** The plugin is asked whether it is currently OK to unload it.
		Under rare circumstances, your plug-in may be asked to Unload if 
		there are certain types of system errors on the Mac. If you want to
		override this and prevent the unload, you need to override CanUnload 
		to return false.
		
		@return bool16 kTrue to proceed with the unload, kFalse to prevent unloading
	*/
	virtual bool16 CanUnload() const = 0;
	
	/** FixUpData is called when the application opens a document which
		contains data that was originally supplied by this plug-in, and
		was subsequently edited during a session when the plug-in was not 
		loaded. This is a chance for the plugin to update or remove
		any data that became stale due to these changes.
		
		@param IDocument* document being opened
	*/
	virtual void FixUpData(IDocument *doc) = 0;

	/** GetPlugIn()->GetPluginID() can be called at runtime to get the pluginID of the currently executing plugin
		
		@return PluginID of the plugin. Please use this instead of calling GetResourceFile() to create a ResourceEnabler.
	*/
	virtual PluginID GetPluginID() const = 0;

	/** Internal Use Only */
	// Called by the ObjectModel to inform the plugin of it's pluginID.
	// do not override this method -- use the default implementation in PlugIn.
	virtual void SetPluginID(PluginID pluginID) = 0;

#ifdef MACINTOSH
	/** Internal Use Only */
	// Called by the ObjectModel to inform the plugin of it's CFBundleRef.
	// do not override this method -- use the default implementation in PlugIn.
	virtual void SetBundleRef(CFBundleRef bundle) = 0;
#endif
	
	/** Internal Use Only */
	// Returns the resource file of the plugin. You should not need 
	// to override this method -- use the default implementation in PlugIn.
	virtual IDFile GetResourceFile() const = 0;
	
	/** Internal Use Only */
	// The plugin should install the factory methods for the
	// classes it contains. You should not need to override
	// this method -- use the default implementation in PlugIn.
	virtual void LoadFactories(PluginID ownerComponent, ISession *theSession) = 0;
	

protected:
	virtual ~IPlugIn();	
};


#endif // __IPLUGIN__
