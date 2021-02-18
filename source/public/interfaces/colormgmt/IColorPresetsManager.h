//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/IColorPresetsManager.h $
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

#ifndef __IColorPresetsManager__
#define __IColorPresetsManager__

#if PRAGMA_ONCE
#pragma once
#endif

#include "ICMSManager.h"
#include "ICMSProfile.h"
#include "ICMSSettings.h"
#include "IPMUnknown.h"

#include "ACEColorMgmtID.h"

//========================================================================================
// CLASS IColorPresetsManager
//========================================================================================

class IColorPresetsManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORPRESETSMANAGER };
	
	enum
	{
		kBadIndex = -1
	};
	
	/** Returns the local presets directory, ie the one local to the current user.

		@param sysFile OUT Receives the directory.
		@return kTrue if successful, kFalse if error.
	*/
	virtual bool16 GetPresetsDirectory(IDFile &sysFile) const = 0;

	/** Returns the global presets directory, ie the one at the system level.

		@param sysFile OUT Receives the directory.
		@return kTrue if successful, kFalse if error.
	*/
	virtual bool16 GetGlobalPresetsDirectory(IDFile &sysFile) const = 0;

	/** Indicates whether the given file is in one of the presets directories.

		@param theFile IN The file you're interested in.
		@return kTrue if the file is in one of the presets directories; kFalse otherwise.
	*/
	virtual bool16 FileIsInPresetsDirectory(const IDFile &theFile) const = 0;
	
	virtual bool16 ReadPresetFiles() = 0;
	
	virtual bool16 UpdatePresetFiles() = 0;
	
	virtual bool16 LoadPresetFile(const IDFile &sysFile) = 0;
	virtual bool16 SavePresetFile(int32 index, const IDFile &sysFile) = 0;
	
	virtual int32 GetNumPresets() = 0;
	
	virtual int32 GetPresetIndex(const IDFile &sysFile) = 0;
	/**
		Returns the index of the default preset, which is the preset that the application
		should default to when it starts up with no information about what preset is
		selected (that information, in turn, is provided by ACE).  Note that the default preset
		depends on the current locale.
		
		@return The preset index.
	*/
	virtual int32 GetDefaultPresetIndex() = 0; 
	
	virtual void GetPresetName(int32 index, PMString &name) = 0;
	
	virtual void GetPresetPath(int32 index, PMString &path) = 0;
	
	virtual void GetDescription(int32 index, PMString &description) = 0;
	virtual void SetDescription(int32 index, const PMString &description) = 0;
	
	virtual ICMSProfile *QueryWorkingRGB(int32 index) = 0;
	virtual void SetWorkingRGB(int32 index, ICMSProfile *profile) = 0;
	virtual void SetWorkingRGB(int32 index, const PMString &workingRGB) = 0;
	virtual void SetWorkingRGB(int32 index, ICMSProfile::profileCode profileCode) = 0;
	
	virtual ICMSProfile *QueryWorkingCMYK(int32 index) = 0;
	virtual void SetWorkingCMYK(int32 index, ICMSProfile *profile) = 0;
	virtual void SetWorkingCMYK(int32 index, const PMString &workingCMYK) = 0;
	virtual void SetWorkingCMYK(int32 index, ICMSProfile::profileCode profileCode) = 0;
	
	virtual ICMSManager::CMSPolicy GetPolicyRGB(int32 index)  = 0;
	virtual void SetPolicyRGB(int32 index, ICMSManager::CMSPolicy policyRGB) = 0;
	
	virtual ICMSManager::CMSPolicy GetPolicyCMYK(int32 index) = 0;
	virtual void SetPolicyCMYK(int32 index, ICMSManager::CMSPolicy policyCMYK) = 0;
	
	virtual bool16 GetMismatchAskOpening(int32 index) = 0;
	virtual void SetMismatchAskOpening(int32 index, bool16 mismatchAskOpening) = 0;
	
	virtual bool16 GetMismatchAskPasting(int32 index) = 0;
	virtual void SetMismatchAskPasting(int32 index, bool16 mismatchAskPasting) = 0;
	
	virtual bool16 GetMissingAskOpening(int32 index) = 0;
	virtual void SetMissingAskOpening(int32 index, bool16 missingAskOpening) = 0;
	
	virtual uint32 GetEngineCMS(int32 index) = 0;
	virtual void SetEngineCMS(int32 index, uint32 engineCMS) = 0;
	
	virtual uint32 GetEngineCMM(int32 index) = 0;
	virtual void SetEngineCMM(int32 index, uint32 engineCMM) = 0;
	
	virtual ICMSSettings::renderingIntent GetIntent(int32 index) = 0;
	virtual void SetIntent(int32 index, ICMSSettings::renderingIntent intent) = 0;
	
	virtual bool16 GetKPC(int32 index) = 0;
	virtual void SetKPC(int32 index, bool16 kpc) = 0;
	
	/**	The followings for internal use only.
	*/
	
	/**
		 Returns the number of 'recommended' presets tracked by the manager. These
		 presets are guaranteed to come before other presets in the list.
	 */
	virtual uint32 GetRecommendedPresetCount() const = 0;

	/**
		 Unload the custom loaded settings file. There should be at most one custom loaded
		 preset file. Therefore there's no need to specify which one.
		 @return return true if preset unloaded successfully.
	 */
	virtual bool16 UnloadCustomPresetFile () = 0;
};

#endif // __IColorPresetsManager__

// End, IColorPresetsManager.h.
