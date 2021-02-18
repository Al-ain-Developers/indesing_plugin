//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPPreferences.h $
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
//========================================================================================

#pragma once
#ifndef __IXPPreferences__
#define __IXPPreferences__

#include "XPID.h" // for IID_IXPSETPREFERENCESCMDDATA
#include "IPMUnknown.h"
#include "ICMSSettings.h"	// for renderingIntent

/** Transparency preferences.
*/

class IXPPreferences : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXPSETPREFERENCESCMDDATA };
	
	// Blend Device (that is, which colorspace/profile is used for blending)
	enum BlendDevice
	{
		kInvalid = 0,
		
		kDocumentDefault,	// only applies in flattener settings, not prefs
		
		kDocumentRGB,
		kDocumentCMYK
	};
	virtual BlendDevice GetBlendDevice() const = 0;
	virtual void SetBlendDevice(BlendDevice dev) = 0;

	// The resolution used for transparency effects on screen. Default is 72dpi.
	virtual PMReal GetDisplayEffectDPI() const = 0;
	virtual void SetDisplayEffectDPI(PMReal res) = 0;

	virtual ICMSSettings::renderingIntent GetBlendRenderingIntent() const = 0;
	virtual void SetBlendRenderingIntent(ICMSSettings::renderingIntent intent) = 0;

	/** Get the global light angle.  This is the doc-wide 'synchronization' angle used
		for all effects that have "Use Global Light" checked.

		@return The global light angle.
	*/
	virtual PMReal GetGlobalLightAngle() const = 0;

	/** Set the global light angle.  This is the doc-wide 'synchronization' angle used
		for all effects that have "Use Global Light" checked.

		@param angle IN The new angle.
	*/
	virtual void SetGlobalLightAngle(const PMReal& angle) = 0;

	/** Get the global light altitude.  This is the doc-wide 'synchronization' altitude used
		for all effects that have "Use Global Light" checked.

		@return The global light altitude.
	*/
	virtual PMReal GetGlobalLightAltitude() const = 0;

	/** Set the global light altitude.  This is the doc-wide 'synchronization' altitude used
		for all effects that have "Use Global Light" checked.

		@param angle IN The new altitude.
	*/
	virtual void SetGlobalLightAltitude(const PMReal& altitude) = 0;


};

#endif