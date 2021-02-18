//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CC16BuildNumber.h $
//  
//  Owner: jangir
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2020 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __CC16BuildNumber_h__
#define __CC16BuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCC16VersionNumber 16.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCC16VersionNumberStr "16.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCC16UIVersionStr "2021"

// ----- This represents year based handle of the product to
//		 be presented to the user in splash screen.
// ----- This DOES NOT change when we have a dot release
//
#define kCC16CCVersionYearBasedHandleStr "2021"

// ----- This represents year based full version handle of the product to
//		 be presented to the user in about screen.
// ----- This DOES NOT change when we have a dot release
//
#define kCC16CCVersionYearBasedFullHandleStr "2021.0"


// ----- CC15_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change CC15_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kCC16VersionNumberForResourceStr
//		3. Update kCC16VersionCopyRightStr for the Mac
//		4. Update kCC16CFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kCC16AUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//

// ------ This flag will be used to check if this is dot release or not
#define CC16_DOT_RELEASE_NUMBER 1

#if CC16_DOT_RELEASE_NUMBER
#define kCC16VersionNumberForResourceStr "16.0.1"
#else
#define kCC16VersionNumberForResourceStr "16.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kCC16MajorVersionNumber RezLong(16)
#define kCC16MinorVersionNumber RezLong(0)
#define kCC16DotVersionNumber  RezLong(CC16_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kCC16MajorVersionNumberForResource 16
#define kCC16MinorVersionNumberForResource 0
#define kCC16DotVersionNumberForResource CC16_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if CC16_DOT_RELEASE_NUMBER
#define kCC16VersionCopyRightStr "16.0.1, Copyright 1999-2020 Adobe. All rights reserved."
#define kCC16CFBundleVersionStr "16010"
#else
#define kCC16VersionCopyRightStr "16.0, Copyright 1999-2020 Adobe. All rights reserved."
#define kCC16CFBundleVersionStr "16000"
#endif
#endif

#ifdef WINDOWS
#define kCC16VersionCopyRightStr "Copyright 1999-2020 Adobe. All rights reserved."
#define kCC16ShortCopyRightStr "Copyright 1999-2020 Adobe."
#endif

// ----- Version string for Adobe Update Manager managed components
#if CC16_DOT_RELEASE_NUMBER
#define kCC16AUMComponentVersionStr	"16.0.1."
#else
#define kCC16AUMComponentVersionStr	"16.0.0."
#endif
// ----- Version string for Adobe Crash Reporter
#if CC16_DOT_RELEASE_NUMBER
#define kCC16CRAdobeProductVersionStr	"16010"
#else
#define kCC16CRAdobeProductVersionStr	"16000"
#endif

// ----- Display name for Adobe Crash Reporter
#define kCC16CRAdobeInDesignDisplayNameStr	"Adobe InDesign 2021"
#define kCC16CRAdobeInCopyDisplayNameStr	"Adobe InCopy 2021"

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kCC16MajorScriptVersionNumber	RezLong(16)
#define kCC16MinorScriptVersionNumber	RezLong(0)

// 
#define kInDesign16_0_CLSID				{ 0x2c3995bf, 0x82f2, 0x483d, { 0x81, 0x4, 0xf2, 0x29, 0x0, 0xf9, 0x42, 0x8d } }
// {76F98E79-C12D-4C62-8B30-C10BCCDD6F96}
#define kInDesignSUTypeLib16_0_CLSID	{ 0x76f98e79, 0xc12d, 0x4c62, { 0x8b, 0x30, 0xc1, 0xb, 0xcc, 0xdd, 0x6f, 0x96 } }
// {CDD13F68-1CBC-47EB-BCC7-F35A8874299F}
#define kInDesignMUTypeLib16_0_CLSID	{ 0xcdd13f68, 0x1cbc, 0x47eb, { 0xbc, 0xc7, 0xf3, 0x5a, 0x88, 0x74, 0x29, 0x9f } }

// {22B843ED-7478-45ED-AD1F-B95E1F3BD07C}
#define kInCopy16_0_CLSID				{ 0x22b843ed, 0x7478, 0x45ed, { 0xad, 0x1f, 0xb9, 0x5e, 0x1f, 0x3b, 0xd0, 0x7c } }
// {43502033-4D52-4B48-A936-17DCE1618A4E}
#define kInCopySUTypeLib16_0_CLSID		{ 0x43502033, 0x4d52, 0x4b48, { 0xa9, 0x36, 0x17, 0xdc, 0xe1, 0x61, 0x8a, 0x4e } }
// {086FE31C-68EE-4D96-B38B-2CE6A1A337A7}
#define kInCopyMUTypeLib16_0_CLSID		{ 0x86fe31c, 0x68ee, 0x4d96, { 0xb3, 0x8b, 0x2c, 0xe6, 0xa1, 0xa3, 0x37, 0xa7 } }

// {CA6474A2-8CF8-4345-A8EC-0E3398BD7335}
#define kInDesignServer16_0_CLSID		{ 0xca6474a2, 0x8cf8, 0x4345, { 0xa8, 0xec, 0xe, 0x33, 0x98, 0xbd, 0x73, 0x35 } }
// {C9FDA445-332E-489B-9BED-96C563B451AF}
#define kInDesignServerSUTypeLib16_0_CLSID	{ 0xc9fda445, 0x332e, 0x489b, { 0x9b, 0xed, 0x96, 0xc5, 0x63, 0xb4, 0x51, 0xaf } }
// {7FF30520-A5D2-4D12-9B30-B6148B675116}
#define kInDesignServerMUTypeLib16_0_CLSID	{ 0x7ff30520, 0xa5d2, 0x4d12, { 0x9b, 0x30, 0xb6, 0x14, 0x8b, 0x67, 0x51, 0x16 } }

#endif
