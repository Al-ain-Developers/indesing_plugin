//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CitiusBuildNumber.h $
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

#ifndef __CitiusBuildNumber_h__
#define __CitiusBuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCitiusVersionNumber 9.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCitiusVersionNumberStr "9.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCitiusUIVersionStr "CC"

// ----- CITIUS_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change CITIUS_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kCitiusVersionNumberForResourceStr
//		3. Update kCitiusVersionCopyRightStr for the Mac
//		4. Update kCitiusCFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kCitiusAUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define CITIUS_DOT_RELEASE_NUMBER 0

#if CITIUS_DOT_RELEASE_NUMBER
#define kCitiusVersionNumberForResourceStr "9.0.1"
#else
#define kCitiusVersionNumberForResourceStr "9.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kCitiusMajorVersionNumber RezLong(9)
#define kCitiusMinorVersionNumber RezLong(0)
#define kCitiusDotVersionNumber RezLong(CITIUS_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kCitiusMajorVersionNumberForResource 9
#define kCitiusMinorVersionNumberForResource 0
#define kCitiusDotVersionNumberForResource CITIUS_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if CITIUS_DOT_RELEASE_NUMBER
#define kCitiusVersionCopyRightStr "9.0.1, Copyright 1999-2013 Adobe Systems Incorporated. All rights reserved."
#define kCitiusCFBundleVersionStr "9010"
#else
#define kCitiusVersionCopyRightStr "9.0, Copyright 1999-2013 Adobe Systems Incorporated. All rights reserved."
#define kCitiusCFBundleVersionStr "9000"
#endif
#endif

#ifdef WINDOWS
#define kCitiusVersionCopyRightStr "Copyright 1999-2013 Adobe Systems Incorporated. All rights reserved."
#define kCitiusShortCopyRightStr "Copyright 1999-2013 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if CITIUS_DOT_RELEASE_NUMBER
#define kCitiusAUMComponentVersionStr	"9.0.1."
#else
#define kCitiusAUMComponentVersionStr	"9.0.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kCitiusMajorScriptVersionNumber	RezLong(9)
#define kCitiusMinorScriptVersionNumber	RezLong(0)

// {FB6F0F4B-0467-4F63-88EC-3960B8E1B3EE}
#define kInDesign9_0_CLSID			{ 0xfb6f0f4b, 0x467, 0x4f63,  { 0x88, 0xec, 0x39, 0x60, 0xb8, 0xe1, 0xb3, 0xee } }
// {9E61B153-90BE-4DAA-B154-ECE420857936}
#define kInDesignSUTypeLib9_0_CLSID	{ 0x9e61b153, 0x90be, 0x4daa, { 0xb1, 0x54, 0xec, 0xe4, 0x20, 0x85, 0x79, 0x36 } }
// {1707CE5D-4839-4F8E-A97B-61E39E5FD702}
#define kInDesignMUTypeLib9_0_CLSID	{ 0x1707ce5d, 0x4839, 0x4f8e, { 0xa9, 0x7b, 0x61, 0xe3, 0x9e, 0x5f, 0xd7, 0x2 } }

// {36D2C968-E574-46E9-9B29-E70739574BC8}
#define kInCopy9_0_CLSID			{ 0x36d2c968, 0xe574, 0x46e9, { 0x9b, 0x29, 0xe7, 0x7, 0x39, 0x57, 0x4b, 0xc8 } }
// {2756EFCE-114A-47A4-9CD9-0D3F921A335B}
#define kInCopySUTypeLib9_0_CLSID	{ 0x2756efce, 0x114a, 0x47a4, { 0x9c, 0xd9, 0xd, 0x3f, 0x92, 0x1a, 0x33, 0x5b } }
// {B4C9FE56-1E77-4C77-9D2F-93E57D06A21E}
#define kInCopyMUTypeLib9_0_CLSID	{ 0xb4c9fe56, 0x1e77, 0x4c77, { 0x9d, 0x2f, 0x93, 0xe5, 0x7d, 0x6, 0xa2, 0x1e } }

// {BF1D00C0-4FAD-4ADF-884F-2130F68D982C}
#define kInDesignServer9_0_CLSID			{ 0xbf1d00c0, 0x4fad, 0x4adf, { 0x88, 0x4f, 0x21, 0x30, 0xf6, 0x8d, 0x98, 0x2c } }
// {1A571FCA-47D6-4D6B-8C26-BD313D2231D6}
#define kInDesignServerSUTypeLib9_0_CLSID	{ 0x1a571fca, 0x47d6, 0x4d6b, { 0x8c, 0x26, 0xbd, 0x31, 0x3d, 0x22, 0x31, 0xd6 } }
// {BB5B41DE-32D1-4047-90AD-31F29D39A52B}
#define kInDesignServerMUTypeLib9_0_CLSID	{ 0xbb5b41de, 0x32d1, 0x4047, { 0x90, 0xad, 0x31, 0xf2, 0x9d, 0x39, 0xa5, 0x2b } }

#endif
