//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BuildNumber.h $
//  
//  Owner: Peter Boctor
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/11 00:08:50 $
//  
//  $Revision: #5 $
//  
//  $Change: 1088802 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __BUILDNUMBER__ 
#define __BUILDNUMBER__

#include "CrossPlatformTypes.h"

//----------------------------------------------------------------------------------------
// Only use spaces as separators (no tabs) in these defines to make automated parsing
// and extraction of the build and change numbers easier.
//----------------------------------------------------------------------------------------
#define kBuildNumber 109
#define kBuildNumberStr "109"
#define kChangeNumberStr "1088747"


//----------------------------------------------------------------------------------------
// Create a new file and add it to the end of the list for each new InDesign product version.
//----------------------------------------------------------------------------------------
#include "K2BuildNumber.h"
#include "SherpaBuildNumber.h"
#include "HotakaBuildNumber.h"
#include "AnnaBuildNumber.h"
#include "DragontailBuildNumber.h"
#include "FiredrakeBuildNumber.h"
#include "CobaltBuildNumber.h"
#include "BasilBuildNumber.h"
#include "RocketBuildNumber.h"
#include "OdinBuildNumber.h"
#include "AthosBuildNumber.h"
#include "CitiusBuildNumber.h"
//#include "CitiusR0BuildNumber.h"
//#include "CitiusR1BuildNumber.h"
#include "SiriusBuildNumber.h"
#include "SiriusR3BuildNumber.h"
#include "SiriusR4BuildNumber.h"
#include "R5BuildNumber.h"
#include "R7BuildNumber.h"
#include "R8BuildNumber.h"
#include "R9BuildNumber.h"
#include "R10BuildNumber.h"
#include "R11BuildNumber.h"
#include "R12BuildNumber.h"
#include "R13BuildNumber.h"
#include "CC14BuildNumber.h"
#include "CC15BuildNumber.h"
#include "CC15_1BuildNumber.h"
#include "CC16BuildNumber.h"

//----------------------------------------------------------------------------------------
// Now, build the overall definitions from the most recently included file.
//----------------------------------------------------------------------------------------

#define kVersionNumber					kCC16VersionNumber
#define kVersionNumberStr				kCC16VersionNumberStr
#define kVersionNumberForResourceStr	kCC16VersionNumberForResourceStr
#define kUIVersionStr					kCC16UIVersionStr
#define kCCVersionYearBasedHandleStr	kCC16CCVersionYearBasedHandleStr
#define kCCVersionYearBasedFullHandleStr	kCC16CCVersionYearBasedFullHandleStr
#define kMajorVersionNumber				kCC16MajorVersionNumber
#define kMinorVersionNumber				kCC16MinorVersionNumber
#define kDotVersionNumber				kCC16DotVersionNumber
#define kMajorVersionNumberForResource	kCC16MajorVersionNumberForResource
#define kMinorVersionNumberForResource	kCC16MinorVersionNumberForResource
#define kDotVersionNumberForResource	kCC16DotVersionNumberForResource
#define kVersionCopyRightStr			kCC16VersionCopyRightStr
#ifdef WINDOWS
#define kShortCopyRightStr				kCC16ShortCopyRightStr
#endif
#ifdef DEBUG
#define kAUMComponentVersionStr			kCC16AUMComponentVersionStr kBuildNumberStr "D"
#else
#define kAUMComponentVersionStr			kCC16AUMComponentVersionStr kBuildNumberStr
#endif
#ifdef DEBUG
#define kVersionNumberForAboutStr		kCC16VersionNumberForResourceStr "D"
#else
#define kVersionNumberForAboutStr		kCC16VersionNumberForResourceStr
#endif
#ifdef MACINTOSH
#define kApplicationCFBundleVersionStr	kCC16CFBundleVersionStr
#endif

//used for reporting version to crash reporter
#define kCRAdobeProductBuild            "Adobe Product Build"
#define kCRAdobeProductVersion          "Adobe Product Version"
#define kCRAdobeProductVersionStr       kCC16CRAdobeProductVersionStr

// Display name for Adobe Crash Reporter
#define kCRAdobeInDesignDisplayNameStr	kCC16CRAdobeInDesignDisplayNameStr
#define kCRAdobeInCopyDisplayNameStr	kCC16CRAdobeInCopyDisplayNameStr

// Update this if scripting DOM changes in feature bearing updates as well.
#define kMajorScriptVersionNumber		kCC16MajorScriptVersionNumber
#define kMinorScriptVersionNumber		kCC16MinorScriptVersionNumber

// Used for the application registry key (version number sub-key) on windows.
// HKLM\Software\Adobe\<Application>\<version number>
//
// NOTE: This should not be changed for dot releases, but should be revisited at the time of next major release.
//
#define kAppVersionNumberKeyStr			kCC16VersionNumberStr

// Used in ESInit::GetXPEPSpecifier, it specifies the indesign version number used to
// (i)  Read Bridge CC startup scripts 
// (ii) For incoming bridge talk messages.
// 
// NOTE: This should not be changed for dot releases, but should be revisited at the time of next major release.
// 
#define kXPEPSpecifierVersionNumberStr	kCC16VersionNumberStr

// Used in IDDroverApp::GetAppInternalVersion, it specifies the folder name for drover app preferences
// NOTE: This should not be changed for dot releases, but should be revisited at the time of next major release.
#define kDroverAppInternalVersionNumberStr			kCC16VersionNumberStr

// Used in SettingsMigrationManager::DoesUserWantAutoMigration, to check if user has specified to auto-migrate settings post-install
// NOTE: This should not be changed for dot releases, but should be revisited at the time of next major release.
#define kAutoMigratePrefsVersionNumberStr			kCC16VersionNumberStr

// Specifies the feature branch name for prerelease builds
#define kFeatureBranchStr			"Mainline"

// Strings for FeatureSet preferences
#define kFeatureSetStr "Feature Set Locale Setting"

#ifdef MACINTOSH
	#ifdef PRERELEASE
			#define kDevelopmentStage development
	#else		
			#define kDevelopmentStage release
	#endif
#endif

#endif
