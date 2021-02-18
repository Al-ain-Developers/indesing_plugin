//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IInitializer.h $
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
//  Purpose of Interface:
//  Client code for registering some item associated with a plug-in.
//  Registration of strings, panels, menus, etc. can be done using 
//  this mechanism.
//  
//========================================================================================

#pragma once
#ifndef __IInitializer__
#define __IInitializer__

#include "IPMUnknown.h"
#include "ShuksanID.h"

    /**
    The IInitializer interface is used for registering resources of a particular
    type that may appear in multiple plug-ins. Each Initializer handles a single 
    resource type. The application loops through all the plug-ins, calling all the 
    initializers on each plug-in. Each Initializer finds the resources that it cares 
    about, and does whatever processing is necessary. For instance, panels are added 
    using a PanelInitializer, and menus are added using a MenuInitializer. 
   	*/
   	
class IInitializer: public IPMUnknown {
public:
		/** There are two times when Initializers may be called, either early in 
		startup, or later. Each Initializer needs to declare when it wants to be
		called. */
	enum InitializerType { kEarly, kLate };

		/** Return wheter this initializer is an early or late initializer. That is,
		//	is it called before of after the service registry. **/
	virtual InitializerType GetType(void) const = 0;

		/** Open is called before plug-ins are initialized to allow
		   the initializer to set up state that is reused across
		   multiple calls to Register. The server will call Open, followed by
		   zero or more Register calls, followed by a Close. 
		@param localeId		The locale we're registering
		*/
	virtual void Open(const PMLocaleId& localeId) = 0;
		/** Close is called before plug-ins are initialized to allow
		   the initializer to set up and tear down state that is reused across
		   multiple calls to Register. The server will call Open, followed by
		   zero or more Register calls, followed by a Close. 
		@param localeId		The locale we're registering
		*/
	virtual void Close(const PMLocaleId& localeId) = 0;
	
		/** Called by application once for each plug-in, to register the resources
		    supplied by the plug-in. Resource file will already be open. 
		@param plugin		The plug-in we're registering
		@param localeId		The locale we're registering
		*/
	virtual void Register(PluginID plugin, const PMLocaleId& localeId) = 0;
//	virtual Unregister(PluginID plugin) = 0;

		/** Each initializer is called once for each plug-in, and the priority
			controls the order in which the initializers are called for each 
			plug-in. Lower numbers means this initializer is run first; higher 
			numbers move initializer to later in the startup sequence. 
		@return The initializer's priority: specifies whether it is called after or before other initializers.
		*/
	virtual PMReal Priority() const = 0;
};


#endif // __IInitializer__