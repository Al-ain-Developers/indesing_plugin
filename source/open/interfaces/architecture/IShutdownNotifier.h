//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/architecture/IShutdownNotifier.h $
//  
//  Owner: roey horns
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
#ifndef __IShutdownNotifier__
#define __IShutdownNotifier__

 // the purpose of this service is to notify objects about program termination
 

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IShutdownNotifier : public IPMUnknown
{
	public:
		typedef void (*NotificationProcPtr)(void);
		
		virtual void RegisterNotificationProc(NotificationProcPtr proc) = 0;
		virtual void UnregisterNotificationProc(NotificationProcPtr proc) = 0;
};

#endif
