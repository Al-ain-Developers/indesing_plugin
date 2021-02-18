//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/IColorPresetsSettingsData.h $
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

#ifndef __IColorPresetsSettingsData__
#define __IColorPresetsSettingsData__

#if PRAGMA_ONCE
#pragma once
#endif

#include "ICMSManager.h"
#include "ICMSSettings.h"

#include "ACEColorMgmtID.h"

class ICMSProfile;

//========================================================================================
// CLASS IColorPresetsSettingsData
//========================================================================================

class IColorPresetsSettingsData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORPRESETSSETTINGSDATA };
	
	virtual void SetEmulate1xCMSOff(bool16 emulate1xCMSOff) = 0;
	virtual bool16 GetEmulate1xCMSOff() const = 0;

	virtual void SetIsCustom(bool16 isCustom) = 0;
	virtual bool16 GetIsCustom() const = 0;

	virtual void SetPresetName(const PMString &presetName) = 0;
	virtual const PMString &GetPresetName() const = 0;

	virtual void SetPresetPath(const PMString &presetPath) = 0;
	virtual const PMString &GetPresetPath() const = 0;

	virtual void SetDescription(const PMString &description) = 0;
	virtual const PMString &GetDescription() const = 0;

	virtual void SetWorkingRGB(ICMSProfile *workingRGB) = 0;
	virtual ICMSProfile *GetWorkingRGB() const = 0;

	virtual void SetWorkingRGBName(const PMString &workingRGBName) = 0;
	virtual const PMString &GetWorkingRGBName() const = 0;

	virtual void SetWorkingRGBCode(ICMSProfile::profileCode workingRGBCode) = 0;
	virtual ICMSProfile::profileCode GetWorkingRGBCode() const = 0;

	virtual void SetWorkingCMYK(ICMSProfile *workingCMYK) = 0;
	virtual ICMSProfile *GetWorkingCMYK() const = 0;

	virtual void SetWorkingCMYKName(const PMString &workingCMYKName) = 0;
	virtual const PMString &GetWorkingCMYKName() const = 0;

	virtual void SetWorkingCMYKCode(ICMSProfile::profileCode workingCMYKCode) = 0;
	virtual ICMSProfile::profileCode GetWorkingCMYKCode() const = 0;

	virtual void SetPolicyRGB(ICMSManager::CMSPolicy policyRGB) = 0;
	virtual ICMSManager::CMSPolicy GetPolicyRGB() const = 0;

	virtual void SetPolicyCMYK(ICMSManager::CMSPolicy policyCMYK) = 0;
	virtual ICMSManager::CMSPolicy GetPolicyCMYK() const = 0;

	virtual void SetMismatchAskOpening(bool16 mismatchAskOpening) = 0;
	virtual bool16 GetMismatchAskOpening() const = 0;

	virtual void SetMismatchAskPasting(bool16 mismatchAskPasting) = 0;
	virtual bool16 GetMismatchAskPasting() const = 0;

	virtual void SetMissingAskOpening(bool16 missingAskOpening) = 0;
	virtual bool16 GetMissingAskOpening() const = 0;

	virtual void SetEngineCMS(uint32 engineCMS) = 0;
	virtual uint32 GetEngineCMS() const = 0;

	virtual void SetEngineCMM(uint32 engineCMM) = 0;
	virtual uint32 GetEngineCMM() const = 0;

	virtual void SetIntent(ICMSSettings::renderingIntent intent) = 0;
	virtual ICMSSettings::renderingIntent GetIntent() const = 0;

	virtual void SetKPC(bool16 kpc) = 0;
	virtual bool16 GetKPC() const = 0;
};

#endif // __IColorPresetsSettingsData__

// End, IColorPresetsSettingsData.h.
