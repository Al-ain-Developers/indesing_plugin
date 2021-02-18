//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AthosBuildNumber.h $
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

#ifndef __AthosBuildNumber_h__
#define __AthosBuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kAthosVersionNumber 8.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kAthosVersionNumberStr "8.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kAthosUIVersionStr "CS6"

// ----- ATHOS_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change ATHOS_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kAthosVersionNumberForResourceStr
//		3. Update kAthosVersionCopyRightStr for the Mac
//		4. Update kAthosCFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kAthosAUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define ATHOS_DOT_RELEASE_NUMBER 0

#if ATHOS_DOT_RELEASE_NUMBER
#define kAthosVersionNumberForResourceStr "8.0.1"
#else
#define kAthosVersionNumberForResourceStr "8.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kAthosMajorVersionNumber RezLong(8)
#define kAthosMinorVersionNumber RezLong(0)
#define kAthosDotVersionNumber RezLong(ATHOS_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kAthosMajorVersionNumberForResource 8
#define kAthosMinorVersionNumberForResource 0
#define kAthosDotVersionNumberForResource ATHOS_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if ATHOS_DOT_RELEASE_NUMBER
#define kAthosVersionCopyRightStr "8.0.1, Copyright 2000-2012 Adobe Systems Incorporated. All rights reserved."
#define kAthosCFBundleVersionStr "8010"
#else
#define kAthosVersionCopyRightStr "8.0, Copyright 2000-2012 Adobe Systems Incorporated. All rights reserved."
#define kAthosCFBundleVersionStr "8000"
#endif
#endif

#ifdef WINDOWS
#define kAthosVersionCopyRightStr "Copyright 2000-2012 Adobe Systems Incorporated. All rights reserved."
#define kAthosShortCopyRightStr "Copyright 2000-2012 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if ATHOS_DOT_RELEASE_NUMBER
#define kAthosAUMComponentVersionStr	"8.0.1."
#else
#define kAthosAUMComponentVersionStr	"8.0.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kAthosMajorScriptVersionNumber	RezLong(8)
#define kAthosMinorScriptVersionNumber	RezLong(0)

// {18207523-3CEA-4212-A829-14F7F5A3546B}
#define kInDesign8_0_CLSID			{ 0x18207523, 0x3cea, 0x4212, { 0xa8, 0x29, 0x14, 0xf7, 0xf5, 0xa3, 0x54, 0x6b } }
// {531EBB2B-227C-4732-A979-00052EFF35D5}
#define kInDesignSUTypeLib8_0_CLSID	{ 0x531ebb2b, 0x227c, 0x4732, { 0xa9, 0x79, 0x0, 0x5, 0x2e, 0xff, 0x35, 0xd5 } }
// {F4B43528-68EA-4c29-8A18-6FBD8E3C24C4}
#define kInDesignMUTypeLib8_0_CLSID	{ 0xf4b43528, 0x68ea, 0x4c29, { 0x8a, 0x18, 0x6f, 0xbd, 0x8e, 0x3c, 0x24, 0xc4 } }

// {BEB7139C-B6BC-4aef-A0EB-46CC4D4E431D}
#define kInCopy8_0_CLSID			{ 0xbeb7139c, 0xb6bc, 0x4aef, { 0xa0, 0xeb, 0x46, 0xcc, 0x4d, 0x4e, 0x43, 0x1d } }
// {D85AC85E-3C9E-4032-9B53-5C596599D958}
#define kInCopySUTypeLib8_0_CLSID	{ 0xd85ac85e, 0x3c9e, 0x4032, { 0x9b, 0x53, 0x5c, 0x59, 0x65, 0x99, 0xd9, 0x58 } }
// {2731F8BD-C3AE-49ec-BC19-C1C208AC41DC}
#define kInCopyMUTypeLib8_0_CLSID	{ 0x2731f8bd, 0xc3ae, 0x49ec, { 0xbc, 0x19, 0xc1, 0xc2, 0x8, 0xac, 0x41, 0xdc } }

// {E4D56F6F-26C2-48a2-ADC6-9650DB5EBAA6}
#define kInDesignServer8_0_CLSID			{ 0xe4d56f6f, 0x26c2, 0x48a2, { 0xad, 0xc6, 0x96, 0x50, 0xdb, 0x5e, 0xba, 0xa6 } }
// {A1C3F0A2-210D-473b-90EA-4F7E2F981994}
#define kInDesignServerSUTypeLib8_0_CLSID	{ 0xa1c3f0a2, 0x210d, 0x473b, { 0x90, 0xea, 0x4f, 0x7e, 0x2f, 0x98, 0x19, 0x94 } }
// {1AD16367-2368-4bb7-A8D9-388CAC9A844E}
#define kInDesignServerMUTypeLib8_0_CLSID	{ 0x1ad16367, 0x2368, 0x4bb7, { 0xa8, 0xd9, 0x38, 0x8c, 0xac, 0x9a, 0x84, 0x4e } }

#endif
