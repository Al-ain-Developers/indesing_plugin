//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IAlertHandler.h $
//  
//  Owner: Dave Burnard (was Matt Joss)
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
#ifndef __IALERTHANDLER__
#define __IALERTHANDLER__

#include "IPMUnknown.h"
#include "widgetid.h"

/** Provides the interface to allow clients to suppress the alert dialogs.  
		This interface should be attached to a boss with a service provider interface. 
		
		If alerts are set to not show, rather than showing an alert we ask the service registry for a list of IAlertHandlers, 
		and ask them to handle the alert instead. They can then choose which button to press in the alert. Note that
		this mechanism can't be used to supress startup alerts, since the object model isn't built yet.
*/
class IAlertHandler : public IPMUnknown 
{
	public:
		enum { kDefaultIID = IID_IALERTHANDLER };
	
		/** Does this handler want to override the alert? */
		virtual bool16 WantToOverrideAlert() = 0;

		/** Turn overriding on/off for this handler. */
		virtual void SetOverrideAlert(bool16 override) = 0;

		/** Called to override a specific alert dialog.  
				All of the strings are non-translated strings.

			@return which button number should be pressed
		*/
		virtual int16 HandleAlert(const PMString& message, 
															const PMString& button1String,
															const PMString& button2String,
															const PMString& button3String,
															int16 defaultButton) = 0;

};

#endif // __IALERTHANDLER__
