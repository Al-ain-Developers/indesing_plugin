//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IExperimentalFeaturesPrefs.h $
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
#ifndef __IExperimentalFeaturesPrefs__
#define __IExperimentalFeaturesPrefs__

#include "IPMUnknown.h"
#include "AppUIID.h"

//________________________________________________________________________________________
//	CLASS DECLARATIONS
//	InDesign allows for enabling and disabling features which are released on an experimental basis.
//_________________________________________________________________________________

class IExperimentalFeaturesPrefs : public IPMUnknown
{		
public:
	enum { kDefaultIID = IID_IEXPERIMENTALFEATURESPREFS }; 

	/**
	Returns the preference which indicates whether the Publish Online feature is to be enabled.
	@return the preference which indicates whether the Publish Online feature is to be enabled.
	*/
	virtual bool16 GetEnablePublishOnline() const = 0;
	
	/**
	Sets the preference which indicates whether the Publish Online feature is to be enabled
	@param state		IN The flag which indicates whether the Publish Online feature is to be enabled
	*/
	virtual void SetEnablePublishOnline(bool16 state) = 0;

	/**
	Returns the flag which indicates whether the Publish Online feature Preference is enabled
	@return the flag which indicates whether the Publish Online feature Preference is enabled
	*/
	virtual bool16 GetEnablePublishOnlinePref() const = 0;

	/**
	Sets the flag which indicates whether the Publish Online feature Preference is enabled
	@param state     IN The flag which indicates whether the Publish Online feature Preference is enabled
	*/
	virtual void SetEnablePublishOnlinePref(bool16 state) = 0;
};

#endif
