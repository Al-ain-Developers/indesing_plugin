//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CobaltBuildNumber.h $
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

#ifndef __CobaltBuildNumber_h__
#define __CobaltBuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCobaltVersionNumber 5.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCobaltVersionNumberStr "5.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCobaltUIVersionStr "CS3"

// ----- Cobalt_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change Cobalt_DOTRELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kCobaltVersionNumberForResourceStr
//		3. Update kCobaltVersionCopyRightStr for the Mac
//		4. Update kCobaltCFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kCobaltAUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define Cobalt_DOT_RELEASE_NUMBER 5

#if Cobalt_DOT_RELEASE_NUMBER
#define kCobaltVersionNumberForResourceStr "5.0.5"
#else
#define kCobaltVersionNumberForResourceStr "5.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kCobaltMajorVersionNumber RezLong(5)
#define kCobaltMinorVersionNumber RezLong(0)
#define kCobaltDotVersionNumber RezLong(Cobalt_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kCobaltMajorVersionNumberForResource 5
#define kCobaltMinorVersionNumberForResource 0
#define kCobaltDotVersionNumberForResource Cobalt_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2006, 2000-2007, etc.
#ifdef MACINTOSH
#if Cobalt_DOT_RELEASE_NUMBER
#define kCobaltVersionCopyRightStr "5.0.5, Copyright 2000-2008 Adobe Systems Incorporated. All rights reserved."
#define kCobaltCFBundleVersionStr "5050"
#else
#define kCobaltVersionCopyRightStr "5.0, Copyright 2000-2007 Adobe Systems Incorporated. All rights reserved."
#define kCobaltCFBundleVersionStr "5000"
#endif
#endif

#ifdef WINDOWS
#define kCobaltVersionCopyRightStr "Copyright 2000-2008 Adobe Systems Incorporated. All rights reserved."
#define kCobaltShortCopyRightStr "Copyright 2000-2008 Adobe Systems Incorporated."
#endif


// ----- WinSoft Version copyright strings are different for different platforms
#if 1 //qME

#ifdef MACINTOSH
#if Cobalt_DOT_RELEASE_NUMBER
#define kWinsoftVersionCopyRightStr "5.0.1, Copyright 2000-2007 WinSoft SA. All rights reserved."
#define kWinsoftCFBundleVersionStr "5010"
#else
#define kWinsoftVersionCopyRightStr "5.0, Copyright 2000-2007 WinSoft SA. All rights reserved."
#define kWinsoftCFBundleVersionStr "5000"
#endif
#endif

#ifdef WINDOWS
#define kWinsoftVersionCopyRightStr "Copyright 2000-2007 WinSoft SA. All rights reserved."
#define kWinsoftShortCopyRightStr "Copyright 2000-2007 WinSoft SA."
#endif

#endif

// ----- Version string for Adobe Update Manager managed components
#if Cobalt_DOT_RELEASE_NUMBER
#define kCobaltAUMComponentVersionStr	"5.0.5."
#else
#define kCobaltAUMComponentVersionStr	"5.0.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kCobaltMajorScriptVersionNumber	RezLong(5)
#define kCobaltMinorScriptVersionNumber	RezLong(0)

// {1041D8C8-B5E8-49c1-A0DD-9E593B1EB5D5}
#define kInDesign5_0_CLSID			{ 0x1041d8c8, 0xb5e8, 0x49c1, { 0xa0, 0xdd, 0x9e, 0x59, 0x3b, 0x1e, 0xb5, 0xd5 } }
// {666F676B-7790-4b6f-B691-EC43C6F94C18}
#define kInDesignSUTypeLib5_0_CLSID	{ 0x666f676b, 0x7790, 0x4b6f, { 0xb6, 0x91, 0xec, 0x43, 0xc6, 0xf9, 0x4c, 0x18 } }
// {B694A47E-004D-48e0-AE77-B37A9CC18760}
#define kInDesignMUTypeLib5_0_CLSID	{ 0xb694a47e, 0x4d, 0x48e0, { 0xae, 0x77, 0xb3, 0x7a, 0x9c, 0xc1, 0x87, 0x60 } }

// {333C0F34-917D-4a47-A6C5-20E5A0C30A73}
#define kInCopy5_0_CLSID			{ 0x333c0f34, 0x917d, 0x4a47, { 0xa6, 0xc5, 0x20, 0xe5, 0xa0, 0xc3, 0xa, 0x73 } }
// {CE457EAB-54C7-4f71-A933-ECF164ACBF8B}
#define kInCopySUTypeLib5_0_CLSID	{ 0xce457eab, 0x54c7, 0x4f71, { 0xa9, 0x33, 0xec, 0xf1, 0x64, 0xac, 0xbf, 0x8b } }
// {B3D25BCD-BD62-45e7-AF53-787B8506F8C5}
#define kInCopyMUTypeLib5_0_CLSID	{ 0xb3d25bcd, 0xbd62, 0x45e7, { 0xaf, 0x53, 0x78, 0x7b, 0x85, 0x6, 0xf8, 0xc5 } }

// {2534EC3C-0DB7-4dec-BDAF-551EBD00DC77}
#define kInDesignServer5_0_CLSID			{ 0x2534ec3c, 0xdb7, 0x4dec, { 0xbd, 0xaf, 0x55, 0x1e, 0xbd, 0x0, 0xdc, 0x77 } }
// {7EEF86AA-2100-4e6f-B12B-F4B717CAC88E}
#define kInDesignServerSUTypeLib5_0_CLSID	{ 0x7eef86aa, 0x2100, 0x4e6f, { 0xb1, 0x2b, 0xf4, 0xb7, 0x17, 0xca, 0xc8, 0x8e } }
// {B4217DFC-5199-4344-9002-7E6E2507C3D6}
#define kInDesignServerMUTypeLib5_0_CLSID	{ 0xb4217dfc, 0x5199, 0x4344, { 0x90, 0x2, 0x7e, 0x6e, 0x25, 0x7, 0xc3, 0xd6 } }

#endif
