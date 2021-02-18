//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PlugIn.h $
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
#ifndef __PlugIn__
#define __PlugIn__


#include "GetPlugIn.h"
#include "IPlugIn.h"

/** PlugIn supplies the default implementation of IPlugIn. Unless your plug-in has 
	special needs, you can reuse the PlugIn directly. Otherwise, you may need to
	override it.
	
	To reuse PlugIn, just make your GetPlugIn function return a PlugIn. Here's an
	example of how that works:
	<pre>
	static PlugIn gPlugIn;
	IPlugIn *GetPlugIn()
	{
		return &gPlugIn;
	}
	</pre>
	
	To override, just make your own class that inherits from PlugIn, and return that
	instead:
	<pre>
	class MyPlugIn : public PlugIn
	{
		void FixUpData(IDocument *doc);
	};
	static MyPlugIn gPlugIn;
	IPlugIn *GetPlugIn()
	{
		return &gPlugIn;
	}
	</pre>
	
	@see IPlugIn
*/
class PlugIn : public IPlugIn {
public:
	PlugIn();
	~PlugIn();
	
	/** Returns the pluginID that corresponds to your plug-in. It's set up by the application
		at the time the plug-in is loaded. Please use this instead of GetResourceFile() whenever possible.
		Don't override this.
	*/
	virtual PluginID GetPluginID() const
		{ return fPluginID; }

	/** Returns the resource file that corresponds to your plug-in. It's set up by the application
		at the time the plug-in is loaded. Don't override this.
	*/
	virtual IDFile GetResourceFile() const;
	
	/** Sets up the session pointer, and returns kTrue.
	*/
	virtual bool16 Load(ISession* theSession);
	
	/** Unload nils out the session pointer. You shouldn't need to override this.
	*/
	virtual bool16 Unload();
	
	/** Load all the factory functions (e.g., implementations) associated with your plug-in. 
		Do not override this. For internal use only.
	*/
	virtual void LoadFactories(PluginID ownerComponent, ISession *theSession);
	
	/** Default implementation returns kFalse. 
	*/
	virtual bool16 LoadAtStartup();
	
	/** Default implementation returns kTrue.
	*/
	virtual bool16 CanUnload() const;
	
	/** Default implementation does nothing. Override this if your plug-in needs to fix up
		data in the document @see IPlugIn.
	*/
	virtual void FixUpData(IDocument *doc);
	
	/** Called by the ObjectModel at the time the plug-in is loaded.
		Don't override this.
	*/
	virtual void SetPluginID(PluginID pluginID);
#ifdef MACINTOSH
	virtual void SetBundleRef(CFBundleRef bundle);
#endif
		
	private:
		PluginID	fPluginID;
};


#endif // __PlugIn__
