//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CC15BuildNumber.h $
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
//  Copyright 2018 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __CC15BuildNumber_h__
#define __CC15BuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCC15VersionNumber 15.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCC15VersionNumberStr "15.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCC15UIVersionStr "2020"

// ----- This represents year based handle of the product to
//		 be presented to the user in splash screen.
// ----- This DOES NOT change when we have a dot release
//
#define kCC15CCVersionYearBasedHandleStr "2020"

// ----- This represents year based full version handle of the product to
//		 be presented to the user in about screen.
// ----- This DOES NOT change when we have a dot release
//
#define kCC15CCVersionYearBasedFullHandleStr "2020.0"


// ----- CC15_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change CC15_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kCC15VersionNumberForResourceStr
//		3. Update kCC15VersionCopyRightStr for the Mac
//		4. Update kCC15CFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kCC15AUMComponentVersionStr
//		6. Update kCC15CRAdobeProductVersionStr similar to kCC15CFBundleVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define CC15_DOT_RELEASE_NUMBER 3

#if CC15_DOT_RELEASE_NUMBER
#define kCC15VersionNumberForResourceStr "15.0.3"
#else
#define kCC15VersionNumberForResourceStr "15.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kCC15MajorVersionNumber RezLong(15)
#define kCC15MinorVersionNumber RezLong(0)
#define kCC15DotVersionNumber RezLong(CC15_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kCC15MajorVersionNumberForResource 15
#define kCC15MinorVersionNumberForResource 0
#define kCC15DotVersionNumberForResource CC15_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if CC15_DOT_RELEASE_NUMBER
#define kCC15VersionCopyRightStr "15.0.3, Copyright 1999-2019 Adobe Inc. All rights reserved."
#define kCC15CFBundleVersionStr "15030"
#else
#define kCC15VersionCopyRightStr "15.0, Copyright 1999-2019 Adobe Inc. All rights reserved."
#define kCC15CFBundleVersionStr "15000"
#endif
#endif

#ifdef WINDOWS
#define kCC15VersionCopyRightStr "Copyright 1999-2019 Adobe Inc. All rights reserved."
#define kCC15ShortCopyRightStr "Copyright 1999-2019 Adobe Inc."
#endif

// ----- Version string for Adobe Update Manager managed components
#if CC15_DOT_RELEASE_NUMBER
#define kCC15AUMComponentVersionStr	"15.0.3."
#else
#define kCC15AUMComponentVersionStr	"15.0.0."
#endif

// ----- Version string for Adobe Crash Reporter
#if CC15_DOT_RELEASE_NUMBER
#define kCC15CRAdobeProductVersionStr "15030"
#else
#define kCC15CRAdobeProductVersionStr "15000"
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kCC15MajorScriptVersionNumber	RezLong(15)
#define kCC15MinorScriptVersionNumber	RezLong(0)

// {AB344D7C-BFFF-4B8C-A3D0-F878FF5DAD80}
#define kInDesign15_0_CLSID				{ 0xab344d7c, 0xbfff, 0x4b8c, { 0xa3, 0xd0, 0xf8, 0x78, 0xff, 0x5d, 0xad, 0x80 } }
// {80162F74-766E-4AD1-B8E1-8C8F6897ED17}
#define kInDesignSUTypeLib15_0_CLSID	{ 0x80162f74, 0x766e, 0x4ad1, { 0xb8, 0xe1, 0x8c, 0x8f, 0x68, 0x97, 0xed, 0x17 } }
// {38E74CB3-2251-472E-A9C3-922526043955}
#define kInDesignMUTypeLib15_0_CLSID	{ 0x38e74cb3, 0x2251, 0x472e, { 0xa9, 0xc3, 0x92, 0x25, 0x26, 0x4, 0x39, 0x55 } }

// {9B2AA14D-2F31-4E18-AA8D-B35C083B6950}
#define kInCopy15_0_CLSID				{ 0x9b2aa14d, 0x2f31, 0x4e18, { 0xaa, 0x8d, 0xb3, 0x5c, 0x8, 0x3b, 0x69, 0x50 } }
// {B458D633-BD8A-42B4-B78C-B630C0F79EB9}
#define kInCopySUTypeLib15_0_CLSID		{ 0xb458d633, 0xbd8a, 0x42b4, { 0xb7, 0x8c, 0xb6, 0x30, 0xc0, 0xf7, 0x9e, 0xb9 } }
// {716EEF4F-735F-4F47-8CC7-99F3C0D67B40}
#define kInCopyMUTypeLib15_0_CLSID		{ 0x716eef4f, 0x735f, 0x4f47, { 0x8c, 0xc7, 0x99, 0xf3, 0xc0, 0xd6, 0x7b, 0x40 } }

// {24F00A91-FA8D-442E-9A2F-146801EA5896}
#define kInDesignServer15_0_CLSID		{ 0x24f00a91, 0xfa8d, 0x442e, { 0x9a, 0x2f, 0x14, 0x68, 0x1, 0xea, 0x58, 0x96 } }
// {A70458C9-42E2-45DD-B803-78CA0ECF8D85}
#define kInDesignServerSUTypeLib15_0_CLSID	{ 0xa70458c9, 0x42e2, 0x45dd, { 0xb8, 0x3, 0x78, 0xca, 0xe, 0xcf, 0x8d, 0x85 } }
// {EBDA5DD3-9249-46A7-8AE4-81D7052C285F}
#define kInDesignServerMUTypeLib15_0_CLSID	{ 0xebda5dd3, 0x9249, 0x46a7, { 0x8a, 0xe4, 0x81, 0xd7, 0x5, 0x2c, 0x28, 0x5f } }

#endif
