//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ISetShowAlertRegistryCmdData.h $
//  
//  Owner: Matt Phillips
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
//  Description: Cmd Data for the SetShowAlertRegistry command (set/clear).
//  
//========================================================================================

#pragma once
#ifndef __ISetShowAlertRegistryCmdData__
#define __ISetShowAlertRegistryCmdData__

/**
	This interface provides the data for the SetShowAlertRegistry command.

	@see IShowAlertRegistry
	@see IShowAlertRegistryUtils
*/

class ISetShowAlertRegistryCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISETSHOWALERTREGISTRYCMDDATA };
		
		/**	Sets the alert ID to show/not-show.  Passing -1 will clear all alerts.
			@param alertID The ID of the alert, or -1 to clear all alerts.
		 */
		virtual void SetAlertID(int32 alertID) = 0;

		/**	Gets the alert ID to show/not-show.
			@return The ID of the alert.
		 */
		virtual int32 GetAlertID() const = 0;
		
		/** Sets whether to show or not-show the specified alert the next time it is
			activated.  If the specified alert ID is -1, this parameter is ignored 
			(assumes kTrue).
			@param shouldShow kTrue to show the alert next time.  kFalse to disable the alert.
		*/
		virtual void SetShouldShow(int32 shouldShow) = 0;

		/** Indicates the show/not-show state for the command.
			@return kTrue if the alert will be enabled, kFalse if disabled.
		*/
		virtual int32 GetShouldShow() const = 0;
};

#endif // __ISetShowAlertRegistryCmdData__