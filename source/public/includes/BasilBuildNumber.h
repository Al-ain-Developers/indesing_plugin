//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BasilBuildNumber.h $
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

#ifndef __BasilBuildNumber_h__
#define __BasilBuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kBasilVersionNumber 6.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kBasilVersionNumberStr "6.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kBasilUIVersionStr "CS4"

// ----- BASIL_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change BASIL_DOTRELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kBasilVersionNumberForResourceStr
//		3. Update kBasilVersionCopyRightStr for the Mac
//		4. Update kBasilCFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kBasilAUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define BASIL_DOT_RELEASE_NUMBER 5

#if BASIL_DOT_RELEASE_NUMBER
#define kBasilVersionNumberForResourceStr "6.0.5"
#else
#define kBasilVersionNumberForResourceStr "6.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kBasilMajorVersionNumber RezLong(6)
#define kBasilMinorVersionNumber RezLong(0)
#define kBasilDotVersionNumber RezLong(BASIL_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kBasilMajorVersionNumberForResource 6
#define kBasilMinorVersionNumberForResource 0
#define kBasilDotVersionNumberForResource BASIL_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2006, 2000-2007, etc.
#ifdef MACINTOSH
#if BASIL_DOT_RELEASE_NUMBER
#define kBasilVersionCopyRightStr "6.0.5, Copyright 2000-2009 Adobe Systems Incorporated. All rights reserved."
#define kBasilCFBundleVersionStr "6050"
#else
#define kBasilVersionCopyRightStr "6.0, Copyright 2000-2008 Adobe Systems Incorporated. All rights reserved."
#define kBasilCFBundleVersionStr "6000"
#endif
#endif

#ifdef WINDOWS
#define kBasilVersionCopyRightStr "Copyright 2000-2009 Adobe Systems Incorporated. All rights reserved."
#define kBasilShortCopyRightStr "Copyright 2000-2009 Adobe Systems Incorporated."
#endif

// ----- Version string for Adobe Update Manager managed components
#if BASIL_DOT_RELEASE_NUMBER
#define kBasilAUMComponentVersionStr	"6.0.5."
#else
#define kBasilAUMComponentVersionStr	"6.0.0."
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kBasilMajorScriptVersionNumber	RezLong(6)
#define kBasilMinorScriptVersionNumber	RezLong(0)

// {4D8E7D87-0103-42f6-BE82-598C7E90A42C}
#define kInDesign6_0_CLSID			{ 0x4d8e7d87, 0x103, 0x42f6, { 0xbe, 0x82, 0x59, 0x8c, 0x7e, 0x90, 0xa4, 0x2c } }
// {274E835E-7501-4bb0-A2CE-A4BDB5231D29}
#define kInDesignSUTypeLib6_0_CLSID	{ 0x274e835e, 0x7501, 0x4bb0, { 0xa2, 0xce, 0xa4, 0xbd, 0xb5, 0x23, 0x1d, 0x29 } }
// {1243A2D3-A9B9-44a8-97B5-AEB4DF0A366B}
#define kInDesignMUTypeLib6_0_CLSID	{ 0x1243a2d3, 0xa9b9, 0x44a8, { 0x97, 0xb5, 0xae, 0xb4, 0xdf, 0xa, 0x36, 0x6b } }

// {4B4C0051-0B3E-4f13-A740-DE1043818D4D}
#define kInCopy6_0_CLSID			{ 0x4b4c0051, 0xb3e, 0x4f13, { 0xa7, 0x40, 0xde, 0x10, 0x43, 0x81, 0x8d, 0x4d } }
// {69585992-251C-4d2d-86EE-679018A1F146}
#define kInCopySUTypeLib6_0_CLSID	{ 0x69585992, 0x251c, 0x4d2d, { 0x86, 0xee, 0x67, 0x90, 0x18, 0xa1, 0xf1, 0x46 } }
// {B4BA0CA2-8BE6-4f36-82CC-863B1A38BA1E}
#define kInCopyMUTypeLib6_0_CLSID	{ 0xb4ba0ca2, 0x8be6, 0x4f36, { 0x82, 0xcc, 0x86, 0x3b, 0x1a, 0x38, 0xba, 0x1e } }

// {FFFB358A-2A39-42fe-B60B-192ABBB9BD67}
#define kInDesignServer6_0_CLSID			{ 0xfffb358a, 0x2a39, 0x42fe, { 0xb6, 0xb, 0x19, 0x2a, 0xbb, 0xb9, 0xbd, 0x67 } }
// {D9731276-D677-4e7b-8CC2-18CDD655B79E}
#define kInDesignServerSUTypeLib6_0_CLSID	{ 0xd9731276, 0xd677, 0x4e7b, { 0x8c, 0xc2, 0x18, 0xcd, 0xd6, 0x55, 0xb7, 0x9e } }
// {838F7B29-0994-42e4-AFA9-D911830A28E9}
#define kInDesignServerMUTypeLib6_0_CLSID	{ 0x838f7b29, 0x994, 0x42e4, { 0xaf, 0xa9, 0xd9, 0x11, 0x83, 0xa, 0x28, 0xe9 } }

#endif
