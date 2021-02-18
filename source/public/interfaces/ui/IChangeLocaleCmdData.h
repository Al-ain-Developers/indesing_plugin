//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IChangeLocaleCmdData.h $
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
#ifndef __IChangeLocaleCmdData_h__
#define __IChangeLocaleCmdData_h__

#include "IPMUnknown.h"
#include "CommandID.h"
#include "PMLocaleId.h"

#ifdef ID_DEPRECATED
/** Changing the locale at runtime is not currently supported
*/
class IChangeLocaleCmdData : public IPMUnknown
{
public:
	virtual void Init(const PMLocaleId& newLocale) = 0;
	
	virtual void SetOldLocale(const PMLocaleId& oldLocale) = 0;
	
	virtual PMLocaleId GetNewLocale() = 0;
	virtual PMLocaleId GetOldLocale() = 0;
};

#endif

#endif // __IChangeLocaleCmdData_h__
