//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/OdinBuildNumber.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __OdinBuildNumber_h__
#define __OdinBuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kOdinVersionNumber 7.5 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kOdinVersionNumberStr "7.5"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kOdinUIVersionStr "CS5.5"

// ----- ROCKET_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change ROCKET_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kOdinVersionNumberForResourceStr
//		3. Update kOdinVersionCopyRightStr for the Mac
//		4. Update kOdinCFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kOdinAUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define ODIN_DOT_RELEASE_NUMBER 0

#if ODIN_DOT_RELEASE_NUMBER
#define kOdinVersionNumberForResourceStr "7.5.1"
#else
#define kOdinVersionNumberForResourceStr "7.5"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kOdinMajorVersionNumber RezLong(7)
#define kOdinMinorVersionNumber RezLong(5)
#define kOdinDotVersionNumber RezLong(ODIN_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kOdinMajorVersionNumberForResource 7
#define kOdinMinorVersionNumberForResource 5
#define kOdinDotVersionNumberForResource ODIN_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if ODIN_DOT_RELEASE_NUMBER
#define kOdinVersionCopyRightStr "7.5.1, Copyright 2000-2011 Adobe Systems Incorporated. All rights reserved."
#define kOdinCFBundleVersionStr "7510"
#else
#define kOdinVersionCopyRightStr "7.5, Copyright 2000-2011 Adobe Systems Incorporated. All rights reserved."
#define kOdinCFBundleVersionStr "7500"
#endif
#endif

#ifdef WINDOWS
#define kOdinVersionCopyRightStr "Copyright 2000-2011 Adobe Systems Incorporated. All rights reserved."
#define kOdinShortCopyRightStr "Copyright 2000-2011 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if ODIN_DOT_RELEASE_NUMBER
#define kOdinAUMComponentVersionStr	"7.5.1."
#else
#define kOdinAUMComponentVersionStr	"7.5.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kOdinMajorScriptVersionNumber	RezLong(7)
#define kOdinMinorScriptVersionNumber	RezLong(5)

// {ED36EA7C-9E21-43dc-BF9D-7E1879734358}
#define kInDesign7_5_CLSID			{ 0x11b39ea8, 0x97c0, 0x48b6, { 0x8b, 0xd2, 0x4a, 0xa6, 0x63, 0x2f, 0x8d, 0x9e } }
// {12A6705F-0474-44db-B7F7-438793ED391C}
#define kInDesignSUTypeLib7_5_CLSID	{ 0x3f5870bc, 0x3c44, 0x4bc9, { 0xa7, 0x79, 0x84, 0xb7, 0xc8, 0x1d, 0x89, 0xaf } }
// {0EAE2841-EABD-4550-BC0B-2C5097031493}
#define kInDesignMUTypeLib7_5_CLSID	{ 0x45422903, 0x2be2, 0x4718, { 0x9c, 0xa6, 0xa8, 0xea, 0x8e, 0x8e, 0x5f, 0x97 } }

// {16B38B62-C41D-4c1a-B402-B199BBA39B13}
#define kInCopy7_5_CLSID			{ 0x25d2a0e2, 0x4373, 0x4cf3, { 0x8d, 0xf9, 0xeb, 0x2, 0xfc, 0x96, 0x74, 0x55 } }
// {62B27C3A-DDF8-40fe-AC27-76E3AB24129F}
#define kInCopySUTypeLib7_5_CLSID	{ 0x5200cd1e, 0x5dae, 0x4942, { 0xb3, 0xcd, 0xe0, 0xd1, 0x45, 0x62, 0x1f, 0xbb } }
// {B04A8221-CDDD-4d99-AB18-C909F1D627F9}
#define kInCopyMUTypeLib7_5_CLSID	{ 0xf11c0fa8, 0x723b, 0x41fd, { 0x8a, 0xd6, 0x4d, 0x69, 0xab, 0x84, 0xde, 0x14 } }

// {96D10A00-63E3-423e-A223-DFC4BEA21206}
#define kInDesignServer7_5_CLSID			{ 0x34701ebc, 0x5975, 0x411c, { 0x8a, 0x45, 0xe7, 0x8e, 0x9, 0x34, 0xaa, 0xdd } }
// {7481A505-F036-4847-9437-3AE93CAEE0C5}
#define kInDesignServerSUTypeLib7_5_CLSID	{ 0x520a7a21, 0x59b9, 0x4825, { 0x93, 0x64, 0xdb, 0x29, 0xfa, 0x1c, 0x29, 0xca } }
// {65CB9701-223D-4674-BB7C-77879B14CADC}
#define kInDesignServerMUTypeLib7_5_CLSID	{ 0x88f1db87, 0xaced, 0x47ff, { 0x9e, 0x98, 0x1d, 0x9f, 0x36, 0x4a, 0x6b, 0x15 } }

#endif
