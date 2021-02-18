//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/ShutdownNotifierHelper.h $
//  
//  Owner: Roey Horns
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
//  Purpose:	helper class that automatically unregisters shutdown notification functions
//  
//========================================================================================

#pragma once
#ifndef __ShutdownNotifierHelper__
#define __ShutdownNotifierHelper__

#include "IShutdownNotifier.h"

#pragma export on
class PUBLIC_DECL BaseShutdownNotifierHelper
{
	public:
	
		BaseShutdownNotifierHelper(ServiceID serviceID);
		~BaseShutdownNotifierHelper();
		
		bool8 Register(IShutdownNotifier::NotificationProcPtr func);		
		void Unregister();
	
	private:
		IShutdownNotifier::NotificationProcPtr 	fFunc;
		const ServiceID								kServiceID; 
		bool8						fRegistered;
};

#pragma export off
class ShutdownNotifierHelper : public  BaseShutdownNotifierHelper
{
public:
	ShutdownNotifierHelper():
	BaseShutdownNotifierHelper(kShutdownNotificationService )
	{}
};

#endif // __ShutdownNotifierHelper__
