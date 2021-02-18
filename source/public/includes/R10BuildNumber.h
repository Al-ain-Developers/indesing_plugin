//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/R10BuildNumber.h $
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

#ifndef __R10BuildNumber_h__
#define __R10BuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR10VersionNumber 12.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR10VersionNumberStr "12.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kR10UIVersionStr "CC 2017"

// ----- This represents year based handle of the product to
//		 be presented to the user in splash screen.
// ----- This DOES NOT change when we have a dot release
//
#define kR10CCVersionYearBasedHandleStr "2017"

// ----- This represents year based full version handle of the product to
//		 be presented to the user in about screen.
// ----- This DOES NOT change when we have a dot release
//
#define kR10CCVersionYearBasedFullHandleStr "2017.0"


// ----- R10_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change R10_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kR10VersionNumberForResourceStr
//		3. Update kR10VersionCopyRightStr for the Mac
//		4. Update kR10CFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kR10AUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define R10_DOT_RELEASE_NUMBER 0

#if R10_DOT_RELEASE_NUMBER
#define kR10VersionNumberForResourceStr "12.0.1"
#else
#define kR10VersionNumberForResourceStr "12.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kR10MajorVersionNumber RezLong(12)
#define kR10MinorVersionNumber RezLong(0)
#define kR10DotVersionNumber RezLong(R10_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kR10MajorVersionNumberForResource 12
#define kR10MinorVersionNumberForResource 0
#define kR10DotVersionNumberForResource R10_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if R10_DOT_RELEASE_NUMBER
#define kR10VersionCopyRightStr "12.0.1, Copyright 1999-2016 Adobe. All rights reserved."
#define kR10CFBundleVersionStr "12010"
#define kR10CRAdobeProductVersionStr "12010"
#else
#define kR10VersionCopyRightStr "12.0, Copyright 1999-2016 Adobe. All rights reserved."
#define kR10CFBundleVersionStr "12000"
#define kR10CRAdobeProductVersionStr "12000"
#endif
#endif

#ifdef WINDOWS
#define kR10VersionCopyRightStr "Copyright 1999-2016 Adobe. All rights reserved."
#define kR10ShortCopyRightStr "Copyright 1999-2016 Adobe."
#endif

// ----- Version string for Adobe Update Manager managed components
#if R10_DOT_RELEASE_NUMBER
#define kR10AUMComponentVersionStr	"12.0.1."
#else
#define kR10AUMComponentVersionStr	"12.0.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kR10MajorScriptVersionNumber	RezLong(12)
#define kR10MinorScriptVersionNumber	RezLong(0)

// {D2F81071-18E2-4D19-8FDD-298CEABDB619}
#define kInDesign12_0_CLSID				{ 0xd2f81071, 0x18e2, 0x4d19, { 0x8f, 0xdd, 0x29, 0x8c, 0xea, 0xbd, 0xb6, 0x19 } }
// {6A706B9C-F2C7-4440-BA12-17ED72877645}
#define kInDesignSUTypeLib12_0_CLSID	{ 0x6a706b9c, 0xf2c7, 0x4440, { 0xba, 0x12, 0x17, 0xed, 0x72, 0x87, 0x76, 0x45 } }
// {31E4DE36-5972-4C7D-A781-08FDA261F9AD}
#define kInDesignMUTypeLib12_0_CLSID	{ 0x31e4de36, 0x5972, 0x4c7d, { 0xa7, 0x81, 0x8, 0xfd, 0xa2, 0x61, 0xf9, 0xad } }

// {C9A04F37-5761-401E-B1E6-9E6C206F4016}
#define kInCopy12_0_CLSID				{ 0xc9a04f37, 0x5761, 0x401e, { 0xb1, 0xe6, 0x9e, 0x6c, 0x20, 0x6f, 0x40, 0x16 } }
// {9DFA56AE-A5D2-4B92-A146-E02A05E981E8}
#define kInCopySUTypeLib12_0_CLSID		{ 0x9dfa56ae, 0xa5d2, 0x4b92, { 0xa1, 0x46, 0xe0, 0x2a, 0x5, 0xe9, 0x81, 0xe8 } }
// {23644B6C-08F9-46B8-97A3-E6746EC60796}
#define kInCopyMUTypeLib12_0_CLSID		{ 0x23644b6c, 0x8f9, 0x46b8, { 0x97, 0xa3, 0xe6, 0x74, 0x6e, 0xc6, 0x7, 0x96 } }

// {C62D9F67-2815-4C5D-9754-5CEAA121CDD8}
#define kInDesignServer12_0_CLSID		{ 0xc62d9f67, 0x2815, 0x4c5d, { 0x97, 0x54, 0x5c, 0xea, 0xa1, 0x21, 0xcd, 0xd8 } }
// {0BCB261B-D387-4BDA-BE85-A3FECD6884F1}
#define kInDesignServerSUTypeLib12_0_CLSID	{ 0xbcb261b, 0xd387, 0x4bda, { 0xbe, 0x85, 0xa3, 0xfe, 0xcd, 0x68, 0x84, 0xf1 } }
// {92BE3467-0FEE-4FAD-8E98-D6DF8730A096}
#define kInDesignServerMUTypeLib12_0_CLSID	{ 0x92be3467, 0xfee, 0x4fad, { 0x8e, 0x98, 0xd6, 0xdf, 0x87, 0x30, 0xa0, 0x96 } }

#endif
