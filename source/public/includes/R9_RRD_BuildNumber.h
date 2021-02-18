//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/R9_RRD_BuildNumber.h $
//  
//  Owner: Michael Burbidge
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  Copyright 1997-2014 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __R9_RRDBuildNumber_h__
#define __R9_RRDBuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR9_RRDVersionNumber 11.5 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR9_RRDVersionNumberStr "11.5"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR9_RRDUIVersionStr "CC 2015"

// ----- This represents year based handle of the product to
//		 be presented to the user in splash screen.
// ----- This DOES NOT change when we have a dot release
//
#define kR9_RRDCCVersionYearBasedHandleStr "2015"

// ----- This represents year based full version handle of the product to
//		 be presented to the user in about screen.
// ----- This DOES NOT change when we have a dot release
//
#define kR9_RRDCCVersionYearBasedFullHandleStr "2015.5"


// ----- R9_RRD_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change R9_RRD_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kR9_RRDVersionNumberForResourceStr
//		3. Update kR9_RRDVersionCopyRightStr for the Mac
//		4. Update kR9_RRDCFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kR9_RRDAUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define R9_RRD_DOT_RELEASE_NUMBER 5

#if R9_RRD_DOT_RELEASE_NUMBER
#define kR9_RRDVersionNumberForResourceStr "11.5.5"
#else
#define kR9_RRDVersionNumberForResourceStr "11.5"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kR9_RRDMajorVersionNumber RezLong(11)
#define kR9_RRDMinorVersionNumber RezLong(5)
#define kR9_RRDDotVersionNumber RezLong(R9_RRD_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kR9_RRDMajorVersionNumberForResource 11
#define kR9_RRDMinorVersionNumberForResource 5
#define kR9_RRDDotVersionNumberForResource R9_RRD_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if R9_RRD_DOT_RELEASE_NUMBER
#define kR9_RRDVersionCopyRightStr "11.5.5, Copyright 1999-2015 Adobe Systems Incorporated. All rights reserved."
#define kR9_RRDCFBundleVersionStr "11550"
#define kR9_RRDCRAdobeProductVersionStr "11550"
#else
#define kR9_RRDVersionCopyRightStr "11.5, Copyright 1999-2015 Adobe Systems Incorporated. All rights reserved."
#define kR9_RRDCFBundleVersionStr "11500"
#define kR9_RRDCRAdobeProductVersionStr "11500"
#endif
#endif

#ifdef WINDOWS
#define kR9_RRDVersionCopyRightStr "Copyright 1999-2015 Adobe Systems Incorporated. All rights reserved."
#define kR9_RRDShortCopyRightStr "Copyright 1999-2015 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if R9_RRD_DOT_RELEASE_NUMBER
#define kR9_RRDAUMComponentVersionStr	"11.5.5."
#else
#define kR9_RRDAUMComponentVersionStr	"11.5.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.

#define kR9_RRDMajorScriptVersionNumber	RezLong(11)
#define kR9_RRDMinorScriptVersionNumber	RezLong(5)

/* CLSID same as CC 11
// {9F938030-F435-4125-8E14-B334C6192D3A}
#define kInDesign11_0_CLSID				{ 0x9f938030, 0xf435, 0x4125, { 0x8e, 0x14, 0xb3, 0x34, 0xc6, 0x19, 0x2d, 0x3a } }
// {451AF4B6-5D30-4D46-95CE-E4F900BF2D44}
#define kInDesignSUTypeLib11_0_CLSID	{ 0x451af4b6, 0x5d30, 0x4d46, { 0x95, 0xce, 0xe4, 0xf9, 0x0, 0xbf, 0x2d, 0x44 } }
// {7C8B1C08-7618-477F-A2EC-D6DC4BCD6B06}
#define kInDesignMUTypeLib11_0_CLSID	{ 0x7c8b1c08, 0x7618, 0x477f, { 0xa2, 0xec, 0xd6, 0xdc, 0x4b, 0xcd, 0x6b, 0x6 } }

// {3F818DCF-B321-46BA-9376-8C9F19C8B7B2}
#define kInCopy11_0_CLSID				{ 0x3f818dcf, 0xb321, 0x46ba, { 0x93, 0x76, 0x8c, 0x9f, 0x19, 0xc8, 0xb7, 0xb2 } }
// {C64B3E03-1258-48F8-AB4D-5661A966E14A}
#define kInCopySUTypeLib11_0_CLSID		{ 0xc64b3e03, 0x1258, 0x48f8, { 0xab, 0x4d, 0x56, 0x61, 0xa9, 0x66, 0xe1, 0x4a } }
// {408EEDC4-9311-482A-9D64-8DB55F97370D}
#define kInCopyMUTypeLib11_0_CLSID		{ 0x408eedc4, 0x9311, 0x482a, { 0x9d, 0x64, 0x8d, 0xb5, 0x5f, 0x97, 0x37, 0xd } }

// {AE4167A3-35E4-4B93-A620-AD088ABEB207}
#define kInDesignServer11_0_CLSID		{ 0xae4167a3, 0x35e4, 0x4b93, { 0xa6, 0x20, 0xad, 0x8, 0x8a, 0xbe, 0xb2, 0x7 } }
// {6AA3B6C2-993B-4381-8E1A-5F739102DC30}
#define kInDesignServerSUTypeLib11_0_CLSID	{ 0x6aa3b6c2, 0x993b, 0x4381, { 0x8e, 0x1a, 0x5f, 0x73, 0x91, 0x2, 0xdc, 0x30 } }
// {DF0AF222-18E1-4912-BA4D-2C30F4C905BF}
#define kInDesignServerMUTypeLib11_0_CLSID	{ 0xdf0af222, 0x18e1, 0x4912, { 0xba, 0x4d, 0x2c, 0x30, 0xf4, 0xc9, 0x5, 0xbf } }
*/

#endif
