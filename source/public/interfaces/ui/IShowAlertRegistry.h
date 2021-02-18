//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IShowAlertRegistry.h $
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
//  Description: Implements the registry for "don't-show-this-alert-again" booleans.
//  
//========================================================================================

#pragma once
#ifndef __IShowAlertRegistry__
#define __IShowAlertRegistry__

#include "HelperInterface.h"
#include "K2Vector.h"
#include "IPMStream.h"

/**
	This interface implements the "don't-show" registry, which controls which alerts are 
	shown and which are not, based on the user's previous checking of "don't show this 
	alert again" checkbox in many alerts, as well as the "show all alerts again" option 
	in preferences, which brings them all back to life.

	The interface lives on the application workspace.

	@see IShowAlertRegistryUtils
*/

class IShowAlertRegistry : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISHOWALERTREGISTRY };
		
		/** Set all alerts to show.
		*/
		virtual void Clear() = 0;

		/** Get whether to show a specific alert.
			@param alertID The ID you're interested in.
			@return kTrue if the alert is enabled; kFalse if not.
		*/
		virtual bool32 GetShouldShow(int32 alertID) const = 0;
		
		/** Set a specific alert to show or not-show.
			@param alertID The ID you're interested in.
			@param shouldShow kTrue to enable the alert; kFalse to disable it.
		*/
		virtual void SetShouldShow(int32 alertID, bool32 shouldShow) = 0;
};

#endif // __IShowAlertRegistry__