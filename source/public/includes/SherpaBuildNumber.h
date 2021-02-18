//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SherpaBuildNumber.h $
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

#ifndef __SherpaBuildNumber_h__
#define __SherpaBuildNumber_h__

// ----- kVersionNumberStr represents the product version number in the form it will
//		 be presented to the user.

#define kSherpaVersionNumberStr "1.5"

// ----- kVersionNumber is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.

#define kSherpaVersionNumber 1.5 

// ----- Used for plug-in actual and expected version numbers
#define kSherpaMajorVersionNumber RezLong(1)
#define kSherpaMinorVersionNumber RezLong(5)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kSherpaMajorVersionNumberForResource 1
#define kSherpaMinorVersionNumberForResource 5

// ----- Version copyright strings are different for different platforms

#ifdef MACINTOSH
#define kSherpaVersionCopyRightStr "1.5, Copyright 2001 Adobe Systems Incorporated. All rights reserved."
#endif

//	{823B2956-B330-11d3-94BD-00C04FA349C7}
#define kInDesign1_5_CLSID	{ 0x823b2956, 0xb330, 0x11d3, { 0x94, 0xbd, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
//	{823B2957-B330-11d3-94BD-00C04FA349C7}
#define kTypeLib1_5_CLSID	{ 0x823b2957, 0xb330, 0x11d3, { 0x94, 0xbd, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }

#endif
