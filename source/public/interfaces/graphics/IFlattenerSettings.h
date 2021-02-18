//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IFlattenerSettings.h $
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
#ifndef __IFlattenerSettings__
#define __IFlattenerSettings__

#include "IPMUnknown.h"
#include "XPID.h"
#include "IGenericSettings.h"

const PMReal kMinFlattenerLevel (0.0);
const PMReal kMaxFlattenerLevel (1.0);

class IFlattenerSettings : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXPFLATTENERSETTINGS };

	// Flattener overrides (only applies on a spread)
	enum 
	{
		kOverrideEnable				= (1L<<0),
		kOverrideLevel 				= (1L<<1),
		kOverrideInternalDPI		= (1L<<2),
		kOverrideExternalDPI		= (1L<<3),
		kOverrideMapDPI				= (1L<<4),
		kOverridePathDPI			= (1L<<5)
	};
	// Get/Set field overrides (kOverride*)
	virtual uint32 GetFlattenerOverrides() const = 0;
	virtual void SetFlattenerOverrides(uint32 overrides) = 0;
	// Get/Set flag overrides (kFlOpt*)
	virtual uint32 GetFlagOverrides() const = 0;
	virtual void SetFlagOverrides(uint32 overrides) = 0;
	
	// Defeats flattener altogether
	virtual bool32 IsFlattenerEnabled() const = 0;
	virtual void SetFlattenerEnabled(bool32 enabled) = 0;

	// Range: 1 (rasterize everything) to 5 (rasterize minimally).  Default is 3.
	enum FlattenerLevel
	{
		kLow = 1,
		kMedLow,
		kMedium,
		kMedHigh,
		kHigh
	};

	virtual PMReal GetFlattenerLevel() const = 0;
	virtual void SetFlattenerLevel(PMReal level) = 0;

	// This is the new, preferred method for obtaining flattener level.  It uses
	// a UI scale of 0 to 100, though the actual stored number here is 0 to 1.
	virtual FlattenerLevel GetOldFlattenerLevel() const = 0;
	virtual void SetOldFlattenerLevel(FlattenerLevel level) = 0;
	
	enum 
	{
		kFlOptUseTextOutlines 					= (1L<<0),
		kFlOptkAllowShadingOutput				= (1L<<1),
		kFlOptkAllowLevel3ShadingOutput			= (1L<<2),
		kFlOptkUseTransparentBackground			= (1L<<3),
		kFlOptkConvertStrokeToFill				= (1L<<4),
		kFlOptkPlanarizeOpaqueRegions			= (1L<<5),
		kFlOptkInterleavedFlattening			= (1L<<6),
		kFlOptkClipComplexRegions				= (1L<<7)
	};

	virtual int32 GetFlattenerFlags() const = 0;
	virtual void SetFlattenerFlags(int32 flags) = 0;

	// Flattener rasterizing resolutions: These determine the DPI used within
	// the flattener when rasterizing.  Note: a value of 0 for any of the following
	// DPIs means "auto."  This means that either the default or a value based on
	// the resolution and line screen of the device is used, assuming it's known.
	//
	//	- Internal DPI: Used for smoothshades.  Default is 150.
	virtual PMReal GetFlattenerInternalDPI() const = 0;
	virtual void SetFlattenerInternalDPI(PMReal dpi) = 0;
	//	- External DPI: Used for edges.  Default is 300.
	virtual PMReal GetFlattenerExternalDPI() const = 0;
	virtual void SetFlattenerExternalDPI(PMReal dpi) = 0;
	//	- Map DPI: Used for the hash map of the page. Default is 2 dpi.
	virtual PMReal GetFlattenerMapDPI() const = 0;
	virtual void SetFlattenerMapDPI(PMReal dpi) = 0;
	//	- Path DPI: Used for rasterizing paths?  Default is 800.
	virtual PMReal GetFlattenerPathDPI() const = 0;
	virtual void SetFlattenerPathDPI(PMReal dpi) = 0;

	// Convenience method
	virtual void Copy(IFlattenerSettings const *other) = 0;

	// retrieve a generalized form of the settings.
	virtual IGenericSettings* GetSettings() const = 0;

	// is it equal
	virtual bool16 Equals(IFlattenerSettings const* pOther) = 0;
};


// settings for defaults.  Used in both new ws responder and in ui for spread overrides.
#define XPDefaultFlatStyle_ExternalLow 288.0
#define XPDefaultFlatStyle_InternalLow 144.0
#define XPDefaultFlatStyle_OldLevelLow IFlattenerSettings::kMedHigh
#define XPDefaultFlatStyle_LevelLow 0.75
#define XPDefaultFlatStyle_FlagsLow  IFlattenerSettings::kFlOptkConvertStrokeToFill

#define XPDefaultFlatStyle_ExternalMed 300.0
#define XPDefaultFlatStyle_InternalMed 150.0
#define XPDefaultFlatStyle_OldLevelMed IFlattenerSettings::kMedHigh
#define XPDefaultFlatStyle_LevelMed 0.75
#define XPDefaultFlatStyle_FlagsMed ( IFlattenerSettings::kFlOptkConvertStrokeToFill | IFlattenerSettings::kFlOptkClipComplexRegions )

#define XPDefaultFlatStyle_ExternalHigh 1200.0
#define XPDefaultFlatStyle_InternalHigh 300.0
#define XPDefaultFlatStyle_OldLevelHigh IFlattenerSettings::kHigh
#define XPDefaultFlatStyle_LevelHigh 1.0
#define XPDefaultFlatStyle_FlagsHigh IFlattenerSettings::kFlOptkClipComplexRegions

#define XPDefaultFlatStyle_ExternalLowJp 300.0
#define XPDefaultFlatStyle_InternalLowJp 150.0
#define XPDefaultFlatStyle_ExternalMedJp 400.0
#define XPDefaultFlatStyle_InternalMedJp 200.0
#define XPDefaultFlatStyle_ExternalHighJp 1200.0
#define XPDefaultFlatStyle_InternalHighJp 400.0

#endif //!def __IFlattenerSettings__
