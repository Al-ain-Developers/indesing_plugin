//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IToolRegister.h $
//  
//  Owner: lance bushore
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
#ifndef __IToolRegister__
#define __IToolRegister__

#include "PMLocaleId.h"

/** Interface to provide a standard hook for plugins to register tools. Allows plugin to add any 
	number of tools to the current tool manager. Note that this could be called multiple 
	times in a session for different locales, and it is possible to register different
	tools for different locales.
*/
class IToolRegister : public IPMUnknown
{
public:
	/** Add appropriate tools to the toolmanager.
		@param localeID identifies locale of interest
	*/
	virtual bool16 Startup(const PMLocaleId& localeId) = 0;
};


#endif


