//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IMenuRegister.h $
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
#ifndef __IMenuRegister_h__
#define __IMenuRegister_h__

#include "IPMUnknown.h"
#include "PMLocaleId.h"
#include "ActionID.h"

//========================================================================================
// CLASS IMenuRegister
//========================================================================================

/** Provides a mechanism for plugins to register menus at first startup.
	Auto-register implementation in API should be used by plug-ins.
*/
class IMenuRegister : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_IMENUREGISTER };

	/** Called to invite component to register menus.
		@param localId identifiers locale of interest
	*/
	virtual void	RegisterMenus(const PMLocaleId& localId) = 0;
};

#endif // __IMenuRegister_h__
