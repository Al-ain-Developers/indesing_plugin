//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IActionRegister.h $
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
//  
//  Purpose of interface:
//  Provide a mechanism for plugins to register actions at first startup.
//  
//========================================================================================

#pragma once
#ifndef __IActionRegister__
#define __IActionRegister__

#include "IPMUnknown.h"
#include "PMLocaleId.h"
#include "ActionID.h"

/** Interface responsible for registering actions strings during startup
*/
class IActionRegister : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_IACTIONREGISTER };

	/**  add appropriate actions to the ActionManager. This is called at the first startup by the action initializer.
		 This is called for bosses that support kActionRegisterService
		@param localeId which locale we're registering for
	*/
	virtual void	RegisterActions(const PMLocaleId& localId) = 0;
};

#endif // __IActionRegister__
