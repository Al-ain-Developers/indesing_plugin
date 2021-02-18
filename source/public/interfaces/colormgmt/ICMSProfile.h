//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ICMSProfile.h $
//  
//  Owner: fhaberma
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

#ifndef __ICMSProfile__
#define __ICMSProfile__

#if PRAGMA_ONCE
#pragma once
#endif

#include "IPMUnknown.h"
#include "ColorMgmtID.h" // IID_ICMSPROFILE

class PMString;

class ICMSProfile : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICMSPROFILE };

	// There are three ways used to categorize profiles:
	// - profileSpace identifies the space of the profile (RGB, CMYK, etc).
	// - profileClass identifies the device class of the profile (Printer, Monitor, etc).
	// - profileCategory identifies the application's use of the profile in terms of
	//							which 'slot' it might appear in (monitor, sep printer, comp, etc).
	
	enum profileSpace {
		kSpaceUnknown,	
		kSpaceGray,
		kSpaceRGB,
		kSpaceCMYK,
		kSpaceLAB,
		kSpaceXYZ,
		kSpaceHiFi2,
		kSpaceHiFi3,
		kSpaceHiFi4,
		kSpaceHiFi5,
		kSpaceHiFi6,
		kSpaceHiFi7,
		kSpaceHiFi8
	};

	enum profileClass {
		kClassUnknown,
		kClassPrinter,
		kClassScanner,
		kClassMonitor,
		kClassGeneric,			// Not associated with a particular class; like abstract.
		kClassNamedColor,
		// The following are used when searching for profiles:
		kClassAnyInput,		// Matches any input capable profile
		kClassAnyOutput,		// Matches any output capable profile
		kClassSimulation		// Matches any profile capable of simulation
	};

	// Note: While not used in this class, the following enum is used by other
	// interfaces which refer to ICMSProfile.  This seems like the most logical
	// place to put it so that all the other code has access to the enum.
	enum profileCategory {	
		kRGBSource=0, 
		kCMYKSource,
		kLABSource,
		kMonitorDestination,
		kObsolete1,	// was composite
		kObsolete2,	// was separations
		kOther
	};

	enum profileSourceType {
		kSourceTypeInvalid = 0,				// Unknown or invalid
		kSourceTypeFromDisk,					// Directly pulled from system
		kSourceTypeEmbeddedInImage,		// Comes from an image
		kSourceTypeEmbeddedInDocument,	// Was on system, now embedded in doc
		kSourceTypeBuiltInGray,				// Provided by application
		kSourceTypeBuiltInRGB,				// Provided by application
		kSourceTypeBuiltInCMYK,				// Provided by application
		kSourceTypeBuiltInLAB,				// Provided by application
		kSourceTypeVirtual					// Created on-the-fly
	};

	enum profileCode
	{
		kProfileCodeNull		= 0,
		
		kProfileCodeMonitor		= 'mRGB',
		
	    kProfileCodeSystemRGB	= 'sysR',
	    kProfileCodeSystemCMYK	= 'sysC',
	    kProfileCodeSystemGray	= 'sysG', 
	    
	    kProfileCodeMaxEnum		= 0xFFFFFFFFL	// Force enum to be 32-bits wide.
	};
	
	// These methods get basic info about the profile that most clients would require.
	virtual void GetName(PMString& name) = 0;		
	virtual profileSpace GetColorSpace() = 0;
	virtual profileClass GetClass() = 0;

	// These methods deal with the source data for the profile.  These are typically
	// used by internal code and preflighting plugins.
	virtual profileSourceType GetSourceType() = 0;
	virtual void GetFileName(PMString& fileName) = 0;
	virtual void GetFullPathFileName(PMString& filePath) = 0;
	virtual void *GetProfileData(uint32 *pLength = nil) = 0;
	virtual void ReleaseProfileData(void* data) = 0;
	virtual void SetImageProfileUID(const UID uid) = 0;
	virtual UID GetImageProfileUID() = 0;
	
#ifdef DEBUG
virtual void DumpToDebugWindow() = 0;
#endif
	
};

#endif // __ICMSProfile__

// End, ICMSProfile.h.
