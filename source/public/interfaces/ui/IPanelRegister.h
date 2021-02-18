//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPanelRegister.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IPanelRegister__
#define __IPanelRegister__

#include "PMLocaleId.h"
#include "ShuksanID.h"

/** Interface that provides a mechanism for plugins to register palette panels they implement with
	the application core. 
	
	Each plugin that implements a panel must implement a boss that has an IPanelRegister
	interface. Don't aggregate this interface into other bosses, but put it in its own boss.
	We iterate the object model to find those which has the side effect of creating a boss,
	which is probably not what you want when aggregated into something like a panel.
*/
class IPanelRegister : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPANELREGISTER };

	/** Called the first time the application is run. The plugin should load and register
		panels from this method.
		@param localeId specifies locale in which application is starting up
	*/
	virtual bool16		Startup(const PMLocaleId& localeId) = 0;
 
};


#endif


