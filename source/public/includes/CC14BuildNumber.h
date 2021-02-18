//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CC14BuildNumber.h $
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

#ifndef __CC14BuildNumber_h__
#define __CC14BuildNumber_h__

// ----- This is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCC14VersionNumber 14.0 

// ----- This string is primarily used as the key in the Windows registry,
//		as well as for application registration on startup.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCC14VersionNumberStr "14.0"

// ----- This represents the product version number in the form it will
//		 be presented to the user. You will see it used in the
//		 Windows application window frame, for example.
//		It is also used by OLEAutomation as part of the application version key.
//
// ----- This DOES NOT change when we have a dot release
//
#define kCC14UIVersionStr "CC 2019"

// ----- This represents year based handle of the product to
//		 be presented to the user in splash screen.
// ----- This DOES NOT change when we have a dot release
//
#define kCC14CCVersionYearBasedHandleStr "2019"

// ----- This represents year based full version handle of the product to
//		 be presented to the user in about screen.
// ----- This DOES NOT change when we have a dot release
//
#define kCC14CCVersionYearBasedFullHandleStr "2019.0"


// ----- CC14_DOT_RELEASE_NUMBER represents the product dot
//		release version.
//		All necessary changes for a dot release update can be
//		done in this file by following these directions.
//
// ----- To update a dot release:
//		1. Change CC14_DOT_RELEASE_NUMBER to non-zero
// 			(If you want 4.0.2 change it to 2.)
//		2. Update kCC14VersionNumberForResourceStr
//		3. Update kCC14VersionCopyRightStr for the Mac
//		4. Update kCC14CFBundleVersionStr for the Mac (4.0.1 would be "4010")
//		5. Update kCC14AUMComponentVersionStr
// 
// At a minimum, you must then rebuild AppFramework, ApplicationUI
// InDesign, InCopy, & InDesignServer. Rebuilding plugins will
// update their Windows resources and Mac plist settings so that,
// for example, the Finder or Explorer will correctly display version info.
//
#define CC14_DOT_RELEASE_NUMBER 0

#if CC14_DOT_RELEASE_NUMBER
#define kCC14VersionNumberForResourceStr "14.0.1"
#else
#define kCC14VersionNumberForResourceStr "14.0"
#endif

// ----- Used for plug-in actual and expected version numbers
#define kCC14MajorVersionNumber RezLong(14)
#define kCC14MinorVersionNumber RezLong(0)
#define kCC14DotVersionNumber RezLong(CC14_DOT_RELEASE_NUMBER)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kCC14MajorVersionNumberForResource 14
#define kCC14MinorVersionNumberForResource 0
#define kCC14DotVersionNumberForResource CC14_DOT_RELEASE_NUMBER


// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2009, 2000-2010, etc.
#ifdef MACINTOSH
#if CC14_DOT_RELEASE_NUMBER
#define kCC14VersionCopyRightStr "14.0.1, Copyright 1999-2018 Adobe. All rights reserved."
#define kCC14CFBundleVersionStr "14010"
#else
#define kCC14VersionCopyRightStr "14.0, Copyright 1999-2018 Adobe. All rights reserved."
#define kCC14CFBundleVersionStr "14000"
#endif
#endif

#ifdef WINDOWS
#define kCC14VersionCopyRightStr "Copyright 1999-2018 Adobe. All rights reserved."
#define kCC14ShortCopyRightStr "Copyright 1999-2018 Adobe."
#endif

// ----- Version string for Adobe Update Manager managed components
#if CC14_DOT_RELEASE_NUMBER
#define kCC14AUMComponentVersionStr	"14.0.1."
#else
#define kCC14AUMComponentVersionStr	"14.0.0."
#endif

// ----- Version string for Adobe Crash Reporter
#if CC14_DOT_RELEASE_NUMBER
#define kCC14CRAdobeProductVersionStr "14010"
#else
#define kCC14CRAdobeProductVersionStr "14000"
#endif

// ----- Scripting DOM Version
// To define a new version of the Scripting DOM:
// For a dot release, add a new major and minor script version number, and new typelib CLSIDs.
// For a minor version release, also add new application CLSIDs.
// Note: This assumes that kUIVersionStr also changes for a minor version release.
#define kCC14MajorScriptVersionNumber	RezLong(14)
#define kCC14MinorScriptVersionNumber	RezLong(0)

// {A170ADCC-478A-4A57-AF03-845434246AD7}
#define kInDesign14_0_CLSID				{ 0xa170adcc, 0x478a, 0x4a57,{ 0xaf, 0x3, 0x84, 0x54, 0x34, 0x24, 0x6a, 0xd7 } }
// {C9C63DCB-3E22-4B34-B4F6-E884C9C4333D}
#define kInDesignSUTypeLib14_0_CLSID	{ 0xc9c63dcb, 0x3e22, 0x4b34,{ 0xb4, 0xf6, 0xe8, 0x84, 0xc9, 0xc4, 0x33, 0x3d } }
// {C12DDD4E-6CDC-4C7B-AE0E-A98E01E0FA59}
#define kInDesignMUTypeLib14_0_CLSID	{ 0xc12ddd4e, 0x6cdc, 0x4c7b,{ 0xae, 0xe, 0xa9, 0x8e, 0x1, 0xe0, 0xfa, 0x59 } }

// {3106132C-61B5-4F5F-B1BD-58BC6AE4376E}
#define kInCopy14_0_CLSID				{ 0x3106132c, 0x61b5, 0x4f5f,{ 0xb1, 0xbd, 0x58, 0xbc, 0x6a, 0xe4, 0x37, 0x6e } }
// {61B7463E-A5D4-43C8-B52F-B0606F89D9ED}
#define kInCopySUTypeLib14_0_CLSID		{ 0x61b7463e, 0xa5d4, 0x43c8,{ 0xb5, 0x2f, 0xb0, 0x60, 0x6f, 0x89, 0xd9, 0xed } }
// {115C75FE-6A9A-4AF1-ACBA-285155A3A051}
#define kInCopyMUTypeLib14_0_CLSID		{ 0x115c75fe, 0x6a9a, 0x4af1,{ 0xac, 0xba, 0x28, 0x51, 0x55, 0xa3, 0xa0, 0x51 } }

// {CE7A178C-C019-4749-8FA5-45A847E01EAF}
#define kInDesignServer14_0_CLSID		{ 0xce7a178c, 0xc019, 0x4749,{ 0x8f, 0xa5, 0x45, 0xa8, 0x47, 0xe0, 0x1e, 0xaf } }
// {F6C596DE-7BCB-4398-B674-0983482D5F44}
#define kInDesignServerSUTypeLib14_0_CLSID	{ 0xf6c596de, 0x7bcb, 0x4398,{ 0xb6, 0x74, 0x9, 0x83, 0x48, 0x2d, 0x5f, 0x44 } }
// {52EFCA0C-4C98-49B5-B3C9-CA8CD56749DA}
#define kInDesignServerMUTypeLib14_0_CLSID	{ 0x52efca0c, 0x4c98, 0x49b5,{ 0xb3, 0xc9, 0xca, 0x8c, 0xd5, 0x67, 0x49, 0xda } }

#endif
