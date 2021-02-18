//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ITouchWorkspacePrefs.h $
//  
//  Owner: Sameer Manuja
//  
//  $Author $
//  
//  $DateTime $
//  
//  $Revision $
//  
//  $Change $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2015 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __ITouchWorkspacePrefs__
#define __ITouchWorkspacePrefs__

#include "IPMUnknown.h"
#include "AppUIID.h"

//________________________________________________________________________________________
//	CLASS DECLARATIONS
//_________________________________________________________________________________

class ITouchWorkspacePrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITOUCHWORKSPACEPREFS };

	// Get preference whether to automatically switch to Touch Workspace when kayboard is detached
	virtual bool16 GetSwitchOnKeyboardDetach() = 0;

	// Set preference whether to automatically switch to Touch Workspace when kayboard is detached
	virtual void SetSwitchOnKeyboardDetach(bool16 state) = 0;

	//internal use only
	virtual bool16 GetSwitchToTWSAlertShownOnFirstLaunch() = 0;
	virtual void SetSwitchToTWSAlertShownOnFirstLaunch(bool16 state) = 0;
};

#endif // __ITouchWorkspacePrefs__
