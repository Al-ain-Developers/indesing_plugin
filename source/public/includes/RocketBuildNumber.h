//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/RocketBuildNumber.h $
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

#ifndef __RocketBuildNumber_h__
#define __RocketBuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kRocketVersionNumber 7.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kRocketVersionNumberStr "7.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kRocketUIVersionStr "CS5"

// ----- ROCKET_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change ROCKET_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kRocketVersionNumberForResourceStr
//		3. Update kRocketVersionCopyRightStr for the Mac
//		4. Update kRocketCFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kRocketAUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define ROCKET_DOT_RELEASE_NUMBER 5

#if ROCKET_DOT_RELEASE_NUMBER
#define kRocketVersionNumberForResourceStr "7.0.5"
#else
#define kRocketVersionNumberForResourceStr "7.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kRocketMajorVersionNumber RezLong(7)
#define kRocketMinorVersionNumber RezLong(0)
#define kRocketDotVersionNumber RezLong(ROCKET_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kRocketMajorVersionNumberForResource 7
#define kRocketMinorVersionNumberForResource 0
#define kRocketDotVersionNumberForResource ROCKET_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if ROCKET_DOT_RELEASE_NUMBER
#define kRocketVersionCopyRightStr "7.0.5, Copyright 2000-2010 Adobe Systems Incorporated. All rights reserved."
#define kRocketCFBundleVersionStr "7050"
#else
#define kRocketVersionCopyRightStr "7.0, Copyright 2000-2010 Adobe Systems Incorporated. All rights reserved."
#define kRocketCFBundleVersionStr "7000"
#endif
#endif

#ifdef WINDOWS
#define kRocketVersionCopyRightStr "Copyright 2000-2010 Adobe Systems Incorporated. All rights reserved."
#define kRocketShortCopyRightStr "Copyright 2000-2010 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if ROCKET_DOT_RELEASE_NUMBER
#define kRocketAUMComponentVersionStr	"7.0.5."
#else
#define kRocketAUMComponentVersionStr	"7.0.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kRocketMajorScriptVersionNumber	RezLong(7)
#define kRocketMinorScriptVersionNumber	RezLong(0)

// {ED36EA7C-9E21-43dc-BF9D-7E1879734358}
#define kInDesign7_0_CLSID			{ 0xed36ea7c, 0x9e21, 0x43dc, { 0xbf, 0x9d, 0x7e, 0x18, 0x79, 0x73, 0x43, 0x58 } }
// {12A6705F-0474-44db-B7F7-438793ED391C}
#define kInDesignSUTypeLib7_0_CLSID	{ 0x12a6705f, 0x474, 0x44db, { 0xb7, 0xf7, 0x43, 0x87, 0x93, 0xed, 0x39, 0x1c } }
// {0EAE2841-EABD-4550-BC0B-2C5097031493}
#define kInDesignMUTypeLib7_0_CLSID	{ 0xeae2841, 0xeabd, 0x4550, { 0xbc, 0xb, 0x2c, 0x50, 0x97, 0x3, 0x14, 0x93 } }

// {16B38B62-C41D-4c1a-B402-B199BBA39B13}
#define kInCopy7_0_CLSID			{ 0x16b38b62, 0xc41d, 0x4c1a, { 0xb4, 0x2, 0xb1, 0x99, 0xbb, 0xa3, 0x9b, 0x13 } }
// {62B27C3A-DDF8-40fe-AC27-76E3AB24129F}
#define kInCopySUTypeLib7_0_CLSID	{ 0x62b27c3a, 0xddf8, 0x40fe, { 0xac, 0x27, 0x76, 0xe3, 0xab, 0x24, 0x12, 0x9f } }
// {B04A8221-CDDD-4d99-AB18-C909F1D627F9}
#define kInCopyMUTypeLib7_0_CLSID	{ 0xb04a8221, 0xcddd, 0x4d99, { 0xab, 0x18, 0xc9, 0x9, 0xf1, 0xd6, 0x27, 0xf9 } }

// {96D10A00-63E3-423e-A223-DFC4BEA21206}
#define kInDesignServer7_0_CLSID			{ 0x96d10a00, 0x63e3, 0x423e, { 0xa2, 0x23, 0xdf, 0xc4, 0xbe, 0xa2, 0x12, 0x6 } }
// {7481A505-F036-4847-9437-3AE93CAEE0C5}
#define kInDesignServerSUTypeLib7_0_CLSID	{ 0x7481a505, 0xf036, 0x4847, { 0x94, 0x37, 0x3a, 0xe9, 0x3c, 0xae, 0xe0, 0xc5 } }
// {65CB9701-223D-4674-BB7C-77879B14CADC}
#define kInDesignServerMUTypeLib7_0_CLSID	{ 0x65cb9701, 0x223d, 0x4674, { 0xbb, 0x7c, 0x77, 0x87, 0x9b, 0x14, 0xca, 0xdc } }

#endif
