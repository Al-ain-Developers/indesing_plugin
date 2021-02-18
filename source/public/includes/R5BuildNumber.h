//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/R5BuildNumber.h $
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

#ifndef __R5BuildNumber_h__
#define __R5BuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR5VersionNumber 11.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR5VersionNumberStr "11.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR5UIVersionStr "CC 2015"

// ----- This represents year based handle of the product to
//		 be presented to the user in splash screen.
// ----- This DOES NOT change when we have a dot release
//
#define kR5CCVersionYearBasedHandleStr "2015"

// ----- This represents year based full version handle of the product to
//		 be presented to the user in about screen.
// ----- This DOES NOT change when we have a dot release
//
#define kR5CCVersionYearBasedFullHandleStr "2015.0"


// ----- R5_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change R5_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kR5VersionNumberForResourceStr
//		3. Update kR5VersionCopyRightStr for the Mac
//		4. Update kR5CFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kR5AUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define R5_DOT_RELEASE_NUMBER 1

#if R5_DOT_RELEASE_NUMBER
#define kR5VersionNumberForResourceStr "11.0.1"
#else
#define kR5VersionNumberForResourceStr "11.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kR5MajorVersionNumber RezLong(11)
#define kR5MinorVersionNumber RezLong(0)
#define kR5DotVersionNumber RezLong(R5_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kR5MajorVersionNumberForResource 11
#define kR5MinorVersionNumberForResource 0
#define kR5DotVersionNumberForResource R5_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if R5_DOT_RELEASE_NUMBER
#define kR5VersionCopyRightStr "11.0.1, Copyright 1999-2015 Adobe Systems Incorporated. All rights reserved."
#define kR5CFBundleVersionStr "11010"
#define kR5CRAdobeProductVersionStr "11010"
#else
#define kR5VersionCopyRightStr "11.0, Copyright 1999-2015 Adobe Systems Incorporated. All rights reserved."
#define kR5CFBundleVersionStr "11000"
#define kR5CRAdobeProductVersionStr "11000"
#endif
#endif

#ifdef WINDOWS
#define kR5VersionCopyRightStr "Copyright 1999-2015 Adobe Systems Incorporated. All rights reserved."
#define kR5ShortCopyRightStr "Copyright 1999-2015 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if R5_DOT_RELEASE_NUMBER
#define kR5AUMComponentVersionStr	"11.0.1."
#else
#define kR5AUMComponentVersionStr	"11.0.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kR5MajorScriptVersionNumber	RezLong(11)
#define kR5MinorScriptVersionNumber	RezLong(0)

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

#endif
