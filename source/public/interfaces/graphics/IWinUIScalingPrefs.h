//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IWinUIScalingPrefs.h $
//  
//  Owner: anagarw
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
//  Copyright 2014 Adobe Systems Incorporated. All rights reserved.
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
#ifndef __IWinUIScalingPrefs__
#define __IWinUIScalingPrefs__

#include "IPMUnknown.h"
#include "AppUIID.h"

//________________________________________________________________________________________
//	CLASS DECLARATIONS
//	InDesign only supports UI scaling of 100%, 150% and 200%. 
//	If the OS level scaling is set to 125%, then InDesign UI can either be displayed at 100%(Lower) or 150%(Higher) using custom scaling.
//_________________________________________________________________________________

class IWinUIScalingPrefs : public IPMUnknown
{		
public:
	enum { kDefaultIID = IID_IWINUISCALINGPREFS }; 

	typedef enum {kLower=0, kHigher} ScalingFactorPref;

	//Get the preference which indicates whether the custom scaling needs to be done for Windows UI
	virtual bool16 GetScaleUserInterface() = 0;
	
	//Set the preference which indicates whether the custom scaling needs to be done for Windows UI
	virtual void SetScaleUserInterface(const bool16& state) = 0;

	//Get the preference which indicates whether lower or higher supported scaling is to be chosen for Windows UI
	virtual ScalingFactorPref GetScalingFactorPref() = 0;
	
	//Set the preference which indicates whether lower or higher supported scaling is to be chosen for Windows UI
	virtual void SetScalingFactorPref(const ScalingFactorPref& pref) = 0;
};

#endif
