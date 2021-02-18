//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2BuildNumber.h $
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

#ifndef __K2BuildNumber_h__
#define __K2BuildNumber_h__

// ----- kVersionNumberStr represents the product version number in the form it will
//		 be presented to the user.

#define kK2VersionNumberStr "1.0"

// ----- kVersionNumber is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.

#define kK2VersionNumber 1.0 

// ----- Used for plug-in actual and expected version numbers
#define kK2MajorVersionNumber RezLong(1)
#define kK2MinorVersionNumber RezLong(0)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kK2MajorVersionNumberForResource 1
#define kK2MinorVersionNumberForResource 0

// ----- Version copyright strings are different for different platforms

#ifdef MACINTOSH
#define kK2VersionCopyRightStr "1.0, Copyright 2001 Adobe Systems Incorporated. All rights reserved."
#endif

//	{ABD4CBB3-0CFE-11d1-801D-0060B03C02E4}
#define kInDesign1_0_CLSID	{ 0xabd4cbb3, 0x0cfe, 0x11d1, { 0x80, 0x1d, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }
//	{3A1D0763-FFA9-11d0-801A-0060B03C02E4}
#define kInDesignTypeLib1_0_CLSID	{ 0x3A1D0763, 0xFFA9, 0x11d0, { 0x80, 0x1A, 0x0, 0x60, 0xB0, 0x3C, 0x2, 0xE4 } }

//	{55BD39B6-E317-11d3-94C7-00C04FA349C7}
#define kInCopy1_0_CLSID	{ 0x55bd39b6, 0xe317, 0x11d3, { 0x94, 0xc7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
//	{55BD39B7-E317-11d3-94C7-00C04FA349C7}
#define kInCopyTypeLib1_0_CLSID	{ 0x55bd39b7, 0xe317, 0x11d3, { 0x94, 0xc7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }

#endif
