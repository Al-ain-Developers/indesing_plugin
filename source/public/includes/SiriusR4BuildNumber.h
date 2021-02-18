//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SiriusR4BuildNumber.h $
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

#ifndef __SiriusR4BuildNumber_h__
#define __SiriusR4BuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kSiriusR4VersionNumber 10.2

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kSiriusR4VersionNumberStr "10.2"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kSiriusR4UIVersionStr "CC 2014"

// ----- This represents year based handle of the product to
//		 be presented to the user in splash screen.
// ----- This DOES NOT change when we have a dot release
//
#define kSiriusR4CCVersionYearBasedHandleStr "2014"

// ----- This represents year based full version handle of the product to
//		 be presented to the user in about screen.
// ----- This DOES NOT change when we have a dot release
//
#define kSiriusR4CCVersionYearBasedFullHandleStr "2014.2"


// ----- SIRIUSR4_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change SIRIUSR4_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kSiriusR4VersionNumberForResourceStr
//		3. Update kSiriusR4VersionCopyRightStr for the Mac
//		4. Update kSiriusR4CFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kSiriusR4AUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define SIRIUSR4_DOT_RELEASE_NUMBER 0

#if SIRIUSR4_DOT_RELEASE_NUMBER
#define kSiriusR4VersionNumberForResourceStr "10.2.1"
#else
#define kSiriusR4VersionNumberForResourceStr "10.2"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kSiriusR4MajorVersionNumber RezLong(10)
#define kSiriusR4MinorVersionNumber RezLong(2)
#define kSiriusR4DotVersionNumber RezLong(SIRIUSR4_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kSiriusR4MajorVersionNumberForResource 10
#define kSiriusR4MinorVersionNumberForResource 2
#define kSiriusR4DotVersionNumberForResource SIRIUSR4_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if SIRIUSR4_DOT_RELEASE_NUMBER
#define kSiriusR4VersionCopyRightStr "10.2.0, Copyright 1999-2014 Adobe Systems Incorporated. All rights reserved."
#define kSiriusR4CFBundleVersionStr "10200"
#define kSiriusR4CRAdobeProductVersionStr "10200"
#else
#define kSiriusR4VersionCopyRightStr "10.2, Copyright 1999-2014 Adobe Systems Incorporated. All rights reserved."
#define kSiriusR4CFBundleVersionStr "10200"
#define kSiriusR4CRAdobeProductVersionStr "10200"
#endif
#endif

#ifdef WINDOWS
#define kSiriusR4VersionCopyRightStr "Copyright 1999-2014 Adobe Systems Incorporated. All rights reserved."
#define kSiriusR4ShortCopyRightStr "Copyright 1999-2014 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if SIRIUSR4_DOT_RELEASE_NUMBER
#define kSiriusR4AUMComponentVersionStr	"10.2.0."
#else
#define kSiriusR4AUMComponentVersionStr	"10.2.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kSiriusR4MajorScriptVersionNumber	RezLong(10)
#define kSiriusR4MinorScriptVersionNumber	RezLong(2)

/* CLSID same as CC 10

// {F568BB1D-B37F-4E06-8F24-D9DF91D22DC1}
#define kInDesign10_0_CLSID			{ 0xf568bb1d, 0xb37f, 0x4e06, { 0x8f, 0x24, 0xd9, 0xdf, 0x91, 0xd2, 0x2d, 0xc1 } }
// {8A1622E3-F934-4088-975C-E36525105470}
#define kInDesignSUTypeLib10_0_CLSID	{ 0x8a1622e3, 0xf934, 0x4088, { 0x97, 0x5c, 0xe3, 0x65, 0x25, 0x10, 0x54, 0x70 } }
// {0EBA0E45-D7DC-4FDD-AE3B-0D33687B4F6A}
#define kInDesignMUTypeLib10_0_CLSID	{ 0xeba0e45, 0xd7dc, 0x4fdd, { 0xae, 0x3b, 0xd, 0x33, 0x68, 0x7b, 0x4f, 0x6a } }

// {7CE54714-42C9-455D-A12D-4F05CC5F1324}
#define kInCopy10_0_CLSID			{ 0x7ce54714, 0x42c9, 0x455d, { 0xa1, 0x2d, 0x4f, 0x5, 0xcc, 0x5f, 0x13, 0x24 } }
// {144B1F24-F645-45DF-ACAE-5991459D5039}
#define kInCopySUTypeLib10_0_CLSID	{ 0x144b1f24, 0xf645, 0x45df, { 0xac, 0xae, 0x59, 0x91, 0x45, 0x9d, 0x50, 0x39 } }
// {374893ED-558F-462C-A7C8-EE7CD2D599DD}
#define kInCopyMUTypeLib10_0_CLSID	{ 0x374893ed, 0x558f, 0x462c, { 0xa7, 0xc8, 0xee, 0x7c, 0xd2, 0xd5, 0x99, 0xdd } }

// {95CAF428-93E4-4722-8800-946A2BE7D906}
#define kInDesignServer10_0_CLSID			{ 0x95caf428, 0x93e4, 0x4722, { 0x88, 0x0, 0x94, 0x6a, 0x2b, 0xe7, 0xd9, 0x6 } }
// {78916798-11B8-46B6-90D6-612392FDC956}
#define kInDesignServerSUTypeLib10_0_CLSID	{ 0x78916798, 0x11b8, 0x46b6, { 0x90, 0xd6, 0x61, 0x23, 0x92, 0xfd, 0xc9, 0x56 } }
// {98740D4C-DD46-4098-82CF-FCA7BBDE3415}
#define kInDesignServerMUTypeLib10_0_CLSID	{ 0x98740d4c, 0xdd46, 0x4098, { 0x82, 0xcf, 0xfc, 0xa7, 0xbb, 0xde, 0x34, 0x15 } }
*/

#endif
