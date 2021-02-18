//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AnnaBuildNumber.h $
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

#ifndef __AnnaBuildNumber_h__
#define __AnnaBuildNumber_h__

// ----- kVersionNumberStr represents the product version number in the form it will
//		 be presented to the user.
// ----- kDocVersionNumberStr represents the product version number in the form it will
//		 be presented to the user when opening/saving documents.

#define kAnnaVersionNumberStr "2.0"
#define kDocVersionNumberStr "2.0"

// ----- kVersionNumber is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.

#define kAnnaVersionNumber 2.0 

// ----- Used for plug-in actual and expected version numbers
#define kAnnaMajorVersionNumber RezLong(2)
#define kAnnaMinorVersionNumber RezLong(1) // bumped up for Jekyll final release

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kAnnaMajorVersionNumberForResource 2
#define kAnnaMinorVersionNumberForResource 0

// ----- Version copyright strings are different for different platforms

// When updating version strings, the copyright years are cumulative.
// e.g. in the future the year string will look like 2000-2003, 2000-2004, etc.
#ifdef MACINTOSH
#define kAnnaVersionCopyRightStr "2.0, Copyright 2000-2002 Adobe Systems Incorporated. All rights reserved."
#endif
#ifdef WINDOWS
#define kAnnaVersionCopyRightStr "Copyright 2000-2002 Adobe Systems Incorporated. All rights reserved."
#define kAnnaShortCopyRightStr "Copyright 2000-2002 Adobe Systems Incorporated."

//	{0FE80759-A114-4d6d-A0CE-15EADB074478}
#define kInDesign2_0_CLSID	{ 0xfe80759, 0xa114, 0x4d6d, { 0xa0, 0xce, 0x15, 0xea, 0xdb, 0x7, 0x44, 0x78 } }
//	{ADD27947-E3C0-4823-B826-BEC1C1654078}
#define kInDesignTypeLib2_0_CLSID	{ 0xadd27947, 0xe3c0, 0x4823, { 0xb8, 0x26, 0xbe, 0xc1, 0xc1, 0x65, 0x40, 0x78 } }

// {F977BF0B-3E08-4d63-8E6C-F95C3D4B3C43}
#define kInCopy2_0_CLSID	{ 0xf977bf0b, 0x3e08, 0x4d63, { 0x8e, 0x6c, 0xf9, 0x5c, 0x3d, 0x4b, 0x3c, 0x43 } }
// {8C87642B-4637-4ce5-8E90-19467A7E89DE}
#define kInCopyTypeLib2_0_CLSID	{ 0x8c87642b, 0x4637, 0x4ce5, { 0x8e, 0x90, 0x19, 0x46, 0x7a, 0x7e, 0x89, 0xde } }

#endif


#endif
