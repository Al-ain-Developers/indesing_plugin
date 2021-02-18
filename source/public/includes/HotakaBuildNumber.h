//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HotakaBuildNumber.h $
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

#ifndef __HotakaBuildNumber_h__
#define __HotakaBuildNumber_h__

// ----- kVersionNumberStr represents the product version number in the form it will
//		 be presented to the user.

#define kHotakaVersionNumberStr "1.0J"

// ----- kVersionNumber is for scripting and should be a 'reasonable' floating-point
//		 representation of the product version number.

#define kHotakaVersionNumber 1.0 

// ----- Used for plug-in actual and expected version numbers
#define kHotakaMajorVersionNumber RezLong(1)
#define kHotakaMinorVersionNumber RezLong(kHotakaLine+0)

// ----- Numbers for 'vers', FILEVERSION and PRODUCTVERSION resources. 
#define kHotakaMajorVersionNumberForResource 1
#define kHotakaMinorVersionNumberForResource kHotakaLine+0

// ----- Version copyright strings are different for different platforms
//		 if these don't seem right, talk to ijohnsto and smcadoo

#ifdef MACINTOSH
#define kHotakaVersionCopyRightStr "1.0J, Copyright 2001 Adobe Systems Incorporated. All rights reserved."
#endif

#endif
