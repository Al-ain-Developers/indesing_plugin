//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/IColorPresetsSettings.h $
//  
//  Owner: James Jardee-Borquist
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

#ifndef __IColorPresetsSettings__
#define __IColorPresetsSettings__

#if PRAGMA_ONCE
#pragma once
#endif

#include "ICMSManager.h"
#include "ICMSProfile.h"
#include "ICMSSettings.h"
#include "IPMUnknown.h"

#include "ACEColorMgmtID.h"

//========================================================================================
// CLASS IColorPresetsSettings
//========================================================================================

class IColorPresetsSettings : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORPRESETSSETTINGS };
	
	virtual bool16 SavePresetFile(const IDFile &sysFile) = 0;
	
	virtual bool16 GetEmulate1xCMSOff() const = 0;
	virtual void SetEmulate1xCMSOff(bool16 emulate1xCMSOff) = 0;
	
	virtual bool16 GetIsCustom() const = 0;
	virtual void SetIsCustom(bool16 isCustom) = 0;
	
	virtual void GetPresetName(PMString &presetName) const = 0;
	virtual void SetPresetName(const PMString &presetName) = 0;
	
	virtual void GetPresetPath(PMString &presetPath) const = 0;
	virtual void SetPresetPath(const PMString &presetPath) = 0;
	
	virtual void GetDescription(PMString &description) const = 0;
	virtual void SetDescription(const PMString &description) = 0;
	
	virtual ICMSProfile *QueryWorkingRGB() const = 0;
	virtual void SetWorkingRGB(ICMSProfile *iCMSProfile) = 0;
	virtual void SetWorkingRGB(const PMString &workingRGB) = 0;
	virtual void SetWorkingRGB(ICMSProfile::profileCode profileCode) = 0;
	
	virtual ICMSProfile *QueryWorkingCMYK() const = 0;
	virtual void SetWorkingCMYK(ICMSProfile *iCMSProfile) = 0;
	virtual void SetWorkingCMYK(const PMString &workingCMYK) = 0;
	virtual void SetWorkingCMYK(ICMSProfile::profileCode profileCode) = 0;
	
	virtual ICMSManager::CMSPolicy GetPolicyRGB() const = 0;
	virtual void SetPolicyRGB(ICMSManager::CMSPolicy policyRGB) = 0;
	
	virtual ICMSManager::CMSPolicy GetPolicyCMYK() const = 0;
	virtual void SetPolicyCMYK(ICMSManager::CMSPolicy policyCMYK) = 0;
	
	virtual bool16 GetMismatchAskOpening() const = 0;
	virtual void SetMismatchAskOpening(bool16 mismatchAskOpening) = 0;
	
	virtual bool16 GetMismatchAskPasting() const = 0;
	virtual void SetMismatchAskPasting(bool16 mismatchAskPasting) = 0;
	
	virtual bool16 GetMissingAskOpening() const = 0;
	virtual void SetMissingAskOpening(bool16 missingAskOpening) = 0;
	
	virtual uint32 GetEngineCMS() const = 0;
	virtual void SetEngineCMS(uint32 engineCMS) = 0;
	
	virtual uint32 GetEngineCMM() const = 0;
	virtual void SetEngineCMM(uint32 engineCMM) = 0;
	
	virtual ICMSSettings::renderingIntent GetIntent() const = 0;
	virtual void SetIntent(ICMSSettings::renderingIntent intent) = 0;
	
	virtual bool16 GetKPC() const = 0;
	virtual void SetKPC(bool16 kpc) = 0;

	virtual void UpdateExternalFile() = 0; // used internally
	virtual void GetExternalFile(IDFile& sysFile) = 0; // returns the sysfile used to store current setup
};

#endif // __IColorPresetsSettings__

// End, IColorPresetsSettings.h.
