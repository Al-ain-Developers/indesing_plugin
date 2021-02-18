//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/R13BuildNumber.h $
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
//  Copyright 1997-2014 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __R13BuildNumber_h__
#define __R13BuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR13VersionNumber 13.1 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR13VersionNumberStr "13.1"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR13UIVersionStr "CC 2018"

// ----- This represents year based handle of the product to
//		 be presented to the user in splash screen.
// ----- This DOES NOT change when we have a dot release
//
#define kR13CCVersionYearBasedHandleStr "2018"

// ----- This represents year based full version handle of the product to
//		 be presented to the user in about screen.
// ----- This DOES NOT change when we have a dot release
//
#define kR13CCVersionYearBasedFullHandleStr "2018.1"


// ----- R13_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change R13_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kR13VersionNumberForResourceStr
//		3. Update kR13VersionCopyRightStr for the Mac
//		4. Update kR13CFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kR13AUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define R13_DOT_RELEASE_NUMBER 0

#if R13_DOT_RELEASE_NUMBER
#define kR13VersionNumberForResourceStr "13.1.1"
#else
#define kR13VersionNumberForResourceStr "13.1"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kR13MajorVersionNumber RezLong(13)
#define kR13MinorVersionNumber RezLong(1)
#define kR13DotVersionNumber RezLong(R13_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kR13MajorVersionNumberForResource 13
#define kR13MinorVersionNumberForResource 1
#define kR13DotVersionNumberForResource R13_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if R13_DOT_RELEASE_NUMBER
#define kR13VersionCopyRightStr "13.1.1, Copyright 1999-2017 Adobe. All rights reserved."
#define kR13CFBundleVersionStr "13110"
#else
#define kR13VersionCopyRightStr "13.1, Copyright 1999-2017 Adobe. All rights reserved."
#define kR13CFBundleVersionStr "13100"
#endif
#endif

#ifdef WINDOWS
#define kR13VersionCopyRightStr "Copyright 1999-2017 Adobe. All rights reserved."
#define kR13ShortCopyRightStr "Copyright 1999-2017 Adobe."
#endif

// ----- Version string for Adobe Update Manager managed components
#if R13_DOT_RELEASE_NUMBER
#define kR13AUMComponentVersionStr	"13.1.1."
#else
#define kR13AUMComponentVersionStr	"13.1.0."
#endif

// ----- Version string for Adobe Crash Reporter
#if R13_DOT_RELEASE_NUMBER
#define kR13CRAdobeProductVersionStr "13110"
#else
#define kR13CRAdobeProductVersionStr "13100"
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kR13MajorScriptVersionNumber	RezLong(13)
#define kR13MinorScriptVersionNumber	RezLong(1)

/* CLSID same as CC 13
// {319D90DE-E047-47A3-B859-6EDC8E6C892C}
#define kInDesign13_0_CLSID				{ 0x319d90de, 0xe047, 0x47a3,{ 0xb8, 0x59, 0x6e, 0xdc, 0x8e, 0x6c, 0x89, 0x2c } }
// {A3BB4322-FF1B-4E64-A801-0998CF133906}
#define kInDesignSUTypeLib13_0_CLSID	{ 0xa3bb4322, 0xff1b, 0x4e64,{ 0xa8, 0x1, 0x9, 0x98, 0xcf, 0x13, 0x39, 0x6 } }
// {76D0151D-8121-4BB3-9B29-4D137776EE97}
#define kInDesignMUTypeLib13_0_CLSID	{ 0x76d0151d, 0x8121, 0x4bb3,{ 0x9b, 0x29, 0x4d, 0x13, 0x77, 0x76, 0xee, 0x97 } }

// {35B774D7-3140-49F4-B227-102A6785F481}
#define kInCopy13_0_CLSID				{ 0x35b774d7, 0x3140, 0x49f4,{ 0xb2, 0x27, 0x10, 0x2a, 0x67, 0x85, 0xf4, 0x81 } }
// {56EB06E5-6B83-4B50-992E-DAC8D67B9706}
#define kInCopySUTypeLib13_0_CLSID		{ 0x56eb06e5, 0x6b83, 0x4b50,{ 0x99, 0x2e, 0xda, 0xc8, 0xd6, 0x7b, 0x97, 0x6 } }
// {C4F6C872-D7BB-4828-89B9-092BDB23C5C5}
#define kInCopyMUTypeLib13_0_CLSID		{ 0xc4f6c872, 0xd7bb, 0x4828,{ 0x89, 0xb9, 0x9, 0x2b, 0xdb, 0x23, 0xc5, 0xc5 } }

// {74812DB7-FA97-43E0-97F5-87D1E47B76E4}
#define kInDesignServer13_0_CLSID		{ 0x74812db7, 0xfa97, 0x43e0,{ 0x97, 0xf5, 0x87, 0xd1, 0xe4, 0x7b, 0x76, 0xe4 } }
// {FCDD5C9C-63FB-4ECA-8B63-95A794A65BD1}
#define kInDesignServerSUTypeLib13_0_CLSID	{ 0xfcdd5c9c, 0x63fb, 0x4eca,{ 0x8b, 0x63, 0x95, 0xa7, 0x94, 0xa6, 0x5b, 0xd1 } }
// {F1C1A6D5-94BD-4400-869A-FACB20EDB232}
#define kInDesignServerMUTypeLib13_0_CLSID	{ 0xf1c1a6d5, 0x94bd, 0x4400,{ 0x86, 0x9a, 0xfa, 0xcb, 0x20, 0xed, 0xb2, 0x32 } }
*/

#endif
