//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPSetPreferencesCmdData.h $
//  
//  Owner: Greg St. Pierre
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
#ifndef __IXPSetPreferencesCmdData__
#define __IXPSetPreferencesCmdData__

#include "XPID.h" // for IID_IXPSETPREFERENCESCMDDATA
#include "IPMUnknown.h"
#include "IXPPreferences.h"	//for BlendDevice

class IXPSetPreferencesCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXPSETPREFERENCESCMDDATA };
	
	// En-masse setter
	virtual void Set(
		IXPPreferences::BlendDevice blendDevice,
		PMReal const &displayEffectDPI,
		ICMSSettings::renderingIntent,
		PMReal const &angle,
		PMReal const &altitude
	) = 0;

	virtual IXPPreferences::BlendDevice GetBlendDevice() const = 0;
	virtual PMReal GetDisplayEffectDPI() const = 0;
	virtual ICMSSettings::renderingIntent GetBlendRenderingIntent() const = 0;
	virtual PMReal GetGlobalLightAngle() const = 0;
	virtual PMReal GetGlobalLightAltitude() const = 0;

	virtual void SetBlendDevice(IXPPreferences::BlendDevice z) = 0;
	virtual void SetDisplayEffectDPI(PMReal z) = 0;
	virtual void SetBlendRenderingIntent(ICMSSettings::renderingIntent intent) = 0;
	virtual void SetGlobalLightAngle(const PMReal& angle) = 0;
	virtual void SetGlobalLightAltitude(const PMReal& altitude) = 0;

	virtual bool32 ShouldSetBlendDevice() const = 0;
	virtual bool32 ShouldSetDisplayEffectDPI() const = 0;
	virtual bool32 ShouldSetBlendRenderingIntent() const = 0;
	virtual bool32 ShouldSetGlobalLightAngle() const = 0;
	virtual bool32 ShouldSetGlobalLightAltitude() const = 0;

};

#endif
