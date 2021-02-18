//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FiredrakeBuildNumber.h $
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

#ifndef __FiredrakeBuildNumber_h__
#define __FiredrakeBuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kFiredrakeVersionNumber 4.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kFiredrakeVersionNumberStr "4.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kFiredrakeUIVersionStr "CS2"

// ----- FIREDRAKE_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change FIREDRAKE_DOTRELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kFiredrakeVersionNumberForResourceStr
//		3. Update kFiredrakeVersionCopyRightStr for the Mac
//		4. Update kFiredrakeCFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kFiredrakeAUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define FIREDRAKE_DOT_RELEASE_NUMBER 5

#if FIREDRAKE_DOT_RELEASE_NUMBER
#define kFiredrakeVersionNumberForResourceStr "4.0.5"
#else
#define kFiredrakeVersionNumberForResourceStr "4.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kFiredrakeMajorVersionNumber RezLong(4)
#define kFiredrakeMinorVersionNumber RezLong(0)
#define kFiredrakeDotVersionNumber RezLong(FIREDRAKE_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kFiredrakeMajorVersionNumberForResource 4
#define kFiredrakeMinorVersionNumberForResource 0
#define kFiredrakeDotVersionNumberForResource FIREDRAKE_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2006, 2000-2007, etc.
#ifdef MACINTOSH
#if FIREDRAKE_DOT_RELEASE_NUMBER
#define kFiredrakeVersionCopyRightStr "4.0.5, Copyright 2000-2007 Adobe Systems Incorporated. All rights reserved."
#define kFiredrakeCFBundleVersionStr "4050"
#else
#define kFiredrakeVersionCopyRightStr "4.0, Copyright 2000-2007 Adobe Systems Incorporated. All rights reserved."
#define kFiredrakeCFBundleVersionStr "4000"
#endif
#endif

#ifdef WINDOWS
#define kFiredrakeVersionCopyRightStr "Copyright 2000-2007 Adobe Systems Incorporated. All rights reserved."
#define kFiredrakeShortCopyRightStr "Copyright 2000-2007 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if FIREDRAKE_DOT_RELEASE_NUMBER
#define kFiredrakeAUMComponentVersionStr	"4.0.5."
#else
#define kFiredrakeAUMComponentVersionStr	"4.0.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kFiredrakeMajorScriptVersionNumber	RezLong(4)
#define kFiredrakeMinorScriptVersionNumber	RezLong(0)
//#define kFiredrakeDot1MajorScriptVersionNumber	RezLong(4)
//#define kFiredrakeDot1MinorScriptVersionNumber	RezLong(1)

// {ED820E2C-869D-4450-8CDF-5CDEA074DB09}
#define kInDesign4_0_CLSID			{ 0xed820e2c, 0x869d, 0x4450, { 0x8c, 0xdf, 0x5c, 0xde, 0xa0, 0x74, 0xdb, 0x9 } }
// {18A21D91-24BB-4d8c-BE3C-30710041F9B9}
#define kInDesignSUTypeLib4_0_CLSID	{ 0x18a21d91, 0x24bb, 0x4d8c, { 0xbe, 0x3c, 0x30, 0x71, 0x0, 0x41, 0xf9, 0xb9 } }
// {76F2D6F7-B0CE-475a-8F59-2E4C59B54157}
#define kInDesignMUTypeLib4_0_CLSID	{ 0x76f2d6f7, 0xb0ce, 0x475a, { 0x8f, 0x59, 0x2e, 0x4c, 0x59, 0xb5, 0x41, 0x57 } }
// {EBBFD18C-01F1-4a0b-87CC-C04512E2FEBE}
//#define kInDesignSUTypeLib4_1_CLSID	{ 0xebbfd18c, 0x1f1, 0x4a0b, { 0x87, 0xcc, 0xc0, 0x45, 0x12, 0xe2, 0xfe, 0xbe } }
// {45109991-7E51-494c-8CBE-6C07F3E6A4E8}
//#define kInDesignMUTypeLib4_1_CLSID	{ 0x45109991, 0x7e51, 0x494c, { 0x8c, 0xbe, 0x6c, 0x7, 0xf3, 0xe6, 0xa4, 0xe8 } }

// {05582C29-F4B7-45f5-A8A3-C0014067E12C}
#define kInCopy4_0_CLSID			{ 0x5582c29, 0xf4b7, 0x45f5, { 0xa8, 0xa3, 0xc0, 0x1, 0x40, 0x67, 0xe1, 0x2c } }
// {5B0257B1-F49F-41aa-9E9B-C914733C597D}
#define kInCopySUTypeLib4_0_CLSID	{ 0x5b0257b1, 0xf49f, 0x41aa, { 0x9e, 0x9b, 0xc9, 0x14, 0x73, 0x3c, 0x59, 0x7d } }
// {1A5D7139-616E-4068-AF67-2B3BA72C7343}
#define kInCopyMUTypeLib4_0_CLSID	{ 0x1a5d7139, 0x616e, 0x4068, { 0xaf, 0x67, 0x2b, 0x3b, 0xa7, 0x2c, 0x73, 0x43 } }
// {474BA61E-5D7E-436b-92E8-D79A69722DDF}
//#define kInCopySUTypeLib4_1_CLSID	{ 0x474ba61e, 0x5d7e, 0x436b, { 0x92, 0xe8, 0xd7, 0x9a, 0x69, 0x72, 0x2d, 0xdf } }
// {A74A7FF2-595E-4a97-8C06-32E9DFF9FB37}
//#define kInCopyMUTypeLib4_1_CLSID	{ 0xa74a7ff2, 0x595e, 0x4a97, { 0x8c, 0x6, 0x32, 0xe9, 0xdf, 0xf9, 0xfb, 0x37 } }

// {43DA8339-B483-4d10-AEED-5AF642C44786}
#define kInDesignServer4_0_CLSID			{ 0x43da8339, 0xb483, 0x4d10, { 0xae, 0xed, 0x5a, 0xf6, 0x42, 0xc4, 0x47, 0x86 } }
// {6C10970D-C4A7-4e4d-B994-99BBC3EA64B4}
#define kInDesignServerSUTypeLib4_0_CLSID	{ 0x6c10970d, 0xc4a7, 0x4e4d, { 0xb9, 0x94, 0x99, 0xbb, 0xc3, 0xea, 0x64, 0xb4 } }
// {242A9A03-6C8B-4aca-BBF5-3398EDBEAB9C}
#define kInDesignServerMUTypeLib4_0_CLSID	{ 0x242a9a03, 0x6c8b, 0x4aca, { 0xbb, 0xf5, 0x33, 0x98, 0xed, 0xbe, 0xab, 0x9c } }
// {7B7534B6-3558-4d3b-9E4D-0B2AD33380E1}
//#define kInDesignServerSUTypeLib4_1_CLSID	{ 0x7b7534b6, 0x3558, 0x4d3b, { 0x9e, 0x4d, 0xb, 0x2a, 0xd3, 0x33, 0x80, 0xe1 } }
// {A751D796-8081-4b50-A085-C8687043540F}
//#define kInDesignServerMUTypeLib4_1_CLSID	{ 0xa751d796, 0x8081, 0x4b50, { 0xa0, 0x85, 0xc8, 0x68, 0x70, 0x43, 0x54, 0xf } }

#endif
