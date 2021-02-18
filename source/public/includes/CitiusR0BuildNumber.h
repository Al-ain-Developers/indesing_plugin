//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CitiusR0BuildNumber.h $
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

#ifndef __CitiusR0BuildNumber_h__
#define __CitiusR0BuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCitiusR0VersionNumber 9.1 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCitiusR0VersionNumberStr "9.1"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCitiusR0UIVersionStr "CC"

// ----- CITIUSR0_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change CITIUSR0_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kCitiusR0VersionNumberForResourceStr
//		3. Update kCitiusR0VersionCopyRightStr for the Mac
//		4. Update kCitiusR0CFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kCitiusR0AUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define CITIUSR0_DOT_RELEASE_NUMBER 0

#if CITIUSR0_DOT_RELEASE_NUMBER
#define kCitiusR0VersionNumberForResourceStr "9.1.1"
#else
#define kCitiusR0VersionNumberForResourceStr "9.1"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kCitiusR0MajorVersionNumber RezLong(9)
#define kCitiusR0MinorVersionNumber RezLong(1)
#define kCitiusR0DotVersionNumber RezLong(CITIUSR0_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kCitiusR0MajorVersionNumberForResource 9
#define kCitiusR0MinorVersionNumberForResource 1
#define kCitiusR0DotVersionNumberForResource CITIUSR0_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if CITIUSR0_DOT_RELEASE_NUMBER
#define kCitiusR0VersionCopyRightStr "9.1.1, Copyright 1999-2013 Adobe Systems Incorporated. All rights reserved."
#define kCitiusR0CFBundleVersionStr "9110"
#else
#define kCitiusR0VersionCopyRightStr "9.1, Copyright 1999-2013 Adobe Systems Incorporated. All rights reserved."
#define kCitiusR0CFBundleVersionStr "9100"
#endif
#endif

#ifdef WINDOWS
#define kCitiusR0VersionCopyRightStr "Copyright 1999-2013 Adobe Systems Incorporated. All rights reserved."
#define kCitiusR0ShortCopyRightStr "Copyright 1999-2013 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if CITIUSR0_DOT_RELEASE_NUMBER
#define kCitiusR0AUMComponentVersionStr	"9.1.1."
#else
#define kCitiusR0AUMComponentVersionStr	"9.1.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kCitiusR0MajorScriptVersionNumber	RezLong(9)
#define kCitiusR0MinorScriptVersionNumber	RezLong(1)

// {13F01800-82D9-4139-A725-C7A1B61F44D1}
#define kInDesign9_1_CLSID			{ 0x13f01800, 0x82d9, 0x4139, { 0xa7, 0x25, 0xc7, 0xa1, 0xb6, 0x1f, 0x44, 0xd1 } }
// {4957613D-FB55-40F2-8BF6-AD0D0F3F223D}
#define kInDesignSUTypeLib9_1_CLSID	{ 0x4957613d, 0xfb55, 0x40f2, { 0x8b, 0xf6, 0xad, 0xd, 0xf, 0x3f, 0x22, 0x3d } }
// {37755B4C-94A8-4553-8E0B-3B5562E29E40}
#define kInDesignMUTypeLib9_1_CLSID	{ 0x37755b4c, 0x94a8, 0x4553, { 0x8e, 0xb, 0x3b, 0x55, 0x62, 0xe2, 0x9e, 0x40 } }

// // {C5D071DA-8824-4363-A192-FC05F41B078C}
#define kInCopy9_1_CLSID			{ 0xc5d071da, 0x8824, 0x4363, { 0xa1, 0x92, 0xfc, 0x5, 0xf4, 0x1b, 0x7, 0x8c } }
// {763308AC-9F85-4BA9-AEFA-E5D31A8AE45C}
#define kInCopySUTypeLib9_1_CLSID	{ 0x763308ac, 0x9f85, 0x4ba9, { 0xae, 0xfa, 0xe5, 0xd3, 0x1a, 0x8a, 0xe4, 0x5c } }
// {5DE5C105-6AFE-4BEA-B1F2-C9DD96E5D161}
#define kInCopyMUTypeLib9_1_CLSID	{ 0x5de5c105, 0x6afe, 0x4bea, { 0xb1, 0xf2, 0xc9, 0xdd, 0x96, 0xe5, 0xd1, 0x61 } }

// {EC6B8413-E3E4-4D5C-A7EC-E661729FD262}
#define kInDesignServer9_1_CLSID			{ 0xec6b8413, 0xe3e4, 0x4d5c, { 0xa7, 0xec, 0xe6, 0x61, 0x72, 0x9f, 0xd2, 0x62 } }
// {5395E9DE-33EA-4413-93B8-A51AFB5E5D97}
#define kInDesignServerSUTypeLib9_1_CLSID	{ 0x5395e9de, 0x33ea, 0x4413, { 0x93, 0xb8, 0xa5, 0x1a, 0xfb, 0x5e, 0x5d, 0x97 } }
// {F60BEBF7-8156-4430-A6B0-DD676AAEF5B6}
#define kInDesignServerMUTypeLib9_1_CLSID	{ 0xf60bebf7, 0x8156, 0x4430, { 0xa6, 0xb0, 0xdd, 0x67, 0x6a, 0xae, 0xf5, 0xb6 } }

#endif
