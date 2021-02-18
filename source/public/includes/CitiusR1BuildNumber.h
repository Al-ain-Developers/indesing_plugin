//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CitiusR1BuildNumber.h $
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

#ifndef __CitiusR1BuildNumber_h__
#define __CitiusR1BuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCitiusR1VersionNumber 9.2 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCitiusR1VersionNumberStr "9.2"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCitiusR1UIVersionStr "CC"

// ----- CITIUSR1_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change CITIUSR1_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kCitiusR1VersionNumberForResourceStr
//		3. Update kCitiusR1VersionCopyRightStr for the Mac
//		4. Update kCitiusR1CFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kCitiusR1AUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define CITIUSR1_DOT_RELEASE_NUMBER 0

#if CITIUSR1_DOT_RELEASE_NUMBER
#define kCitiusR1VersionNumberForResourceStr "9.2.1"
#else
#define kCitiusR1VersionNumberForResourceStr "9.2"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kCitiusR1MajorVersionNumber RezLong(9)
#define kCitiusR1MinorVersionNumber RezLong(2)
#define kCitiusR1DotVersionNumber RezLong(CITIUSR1_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kCitiusR1MajorVersionNumberForResource 9
#define kCitiusR1MinorVersionNumberForResource 2
#define kCitiusR1DotVersionNumberForResource CITIUSR1_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if CITIUSR1_DOT_RELEASE_NUMBER
#define kCitiusR1VersionCopyRightStr "9.2.1, Copyright 1999-2013 Adobe Systems Incorporated. All rights reserved."
#define kCitiusR1CFBundleVersionStr "9210"
#else
#define kCitiusR1VersionCopyRightStr "9.2, Copyright 1999-2013 Adobe Systems Incorporated. All rights reserved."
#define kCitiusR1CFBundleVersionStr "9200"
#endif
#endif

#ifdef WINDOWS
#define kCitiusR1VersionCopyRightStr "Copyright 1999-2013 Adobe Systems Incorporated. All rights reserved."
#define kCitiusR1ShortCopyRightStr "Copyright 1999-2013 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if CITIUSR1_DOT_RELEASE_NUMBER
#define kCitiusR1AUMComponentVersionStr	"9.2.1."
#else
#define kCitiusR1AUMComponentVersionStr	"9.2.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kCitiusR1MajorScriptVersionNumber	RezLong(9)
#define kCitiusR1MinorScriptVersionNumber	RezLong(2)

// {79036985-B46A-4874-AFE3-0794F82EBC02}
#define kInDesign9_2_CLSID			{ 0x79036985, 0xb46a, 0x4874, { 0xaf, 0xe3, 0x7, 0x94, 0xf8, 0x2e, 0xbc, 0x2 } }
// {78E1EAAF-8284-4700-A70D-2D7535CB33E0}
#define kInDesignSUTypeLib9_2_CLSID	{ 0x78e1eaaf, 0x8284, 0x4700, { 0xa7, 0xd, 0x2d, 0x75, 0x35, 0xcb, 0x33, 0xe0 } }
// {678DE2BD-524B-4094-AD05-2461B4066470}
#define kInDesignMUTypeLib9_2_CLSID	{ 0x678de2bd, 0x524b, 0x4094, { 0xad, 0x5, 0x24, 0x61, 0xb4, 0x6, 0x64, 0x70 } }

// {8222E421-8EDD-49EE-ACC5-18C7372A844B}
#define kInCopy9_2_CLSID			{ 0x8222e421, 0x8edd, 0x49ee, { 0xac, 0xc5, 0x18, 0xc7, 0x37, 0x2a, 0x84, 0x4b } }
// {590FB685-EE09-4AD8-B1BB-824E65BBC185}
#define kInCopySUTypeLib9_2_CLSID	{ 0x590fb685, 0xee09, 0x4ad8, { 0xb1, 0xbb, 0x82, 0x4e, 0x65, 0xbb, 0xc1, 0x85 } }
// {D5163CE9-D7F2-4E3B-95F5-B3F7AD818A5A}
#define kInCopyMUTypeLib9_2_CLSID	{ 0xd5163ce9, 0xd7f2, 0x4e3b, { 0x95, 0xf5, 0xb3, 0xf7, 0xad, 0x81, 0x8a, 0x5a } }

// {EECAB475-1481-4EFD-A75B-1DDB38B0BFD9}
#define kInDesignServer9_2_CLSID			{ 0xeecab475, 0x1481, 0x4efd, { 0xa7, 0x5b, 0x1d, 0xdb, 0x38, 0xb0, 0xbf, 0xd9 } }
// {D8A37369-4213-4B59-AD8F-6F19F90851E4}
#define kInDesignServerSUTypeLib9_2_CLSID	{ 0xd8a37369, 0x4213, 0x4b59, { 0xad, 0x8f, 0x6f, 0x19, 0xf9, 0x8, 0x51, 0xe4 } }
// {2AC167B8-BE3F-43CB-9A77-D5E33743C81D}
#define kInDesignServerMUTypeLib9_2_CLSID	{ 0x2ac167b8, 0xbe3f, 0x43cb, { 0x9a, 0x77, 0xd5, 0xe3, 0x37, 0x43, 0xc8, 0x1d } }

#endif
