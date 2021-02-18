//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FormatNumber.h $
//  
//  Owner: Robin Briggs
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

#pragma once
#ifndef __FormatNumber__
#define __FormatNumber__

#include "CrossPlatformTypes.h"

// Major format number.

#define kK2MajorFormatNumber				RezLong(0)	// Major format number for any new persistent data in 1.0
#define kSherpaMajorFormatNumber			RezLong(1)	// Major format number for any new persistent data in 1.5
#define kHotakaMajorFormatNumber			RezLong(2)	// Major format number for any new persistent data in 1.0J
#define kKeystoneMajorFormatNumber			RezLong(3)	// Major format number for any new persistent data in keystone branch
#define kAnnaMajorFormatNumber				RezLong(4)	// Major format number for any new persistent data in 2.0
#define kDragontailMajorFormatNumber		RezLong(5)	// Major format number for any new persistent data in 3.0
#define kFiredrakeMajorFormatNumber			RezLong(6)	// Major format number for any new persistent data in 4.0
#define kCobaltMajorFormatNumber			RezLong(7)	// Major format number for any new persistent data in 5.0
#define kBasilMajorFormatNumber				RezLong(8)	// Major format number for any new persistent data in 6.0
#define kRocketMajorFormatNumber			RezLong(9)	// Major format number for any new persistent data in 7.0
#define kOdinMajorFormatNumber				RezLong(10)	// Major format number for any new persistent data in 7.5
#define kAthosMajorFormatNumber				RezLong(11)	// Major format number for any new persistent data in 8.0
#define kCitiusMajorFormatNumber			RezLong(12)	// Major format number for any new persistent data in 9.0
#define kSiriusMajorFormatNumber			RezLong(13)	// Major format number for any new persistent data in 10.0
#define kR5MajorFormatNumber				RezLong(14)	// Major format number for any new persistent data in 11.0
#define kR7MajorFormatNumber				RezLong(15)	// Major format number for any new persistent data in 11.2 - added only for a UI pref change that did not write to document
#define kR10MajorFormatNumber				RezLong(16)	// Major format number for any new persistent data in 12.0
#define kR12MajorFormatNumber				RezLong(17)	// Major format number for any new persistent data in 13.0
#define kR13MajorFormatNumber				RezLong(18)	// Major format number for any new persistent data in 13.0 - extra added, either this or previous would work, but if you move to this for your plug-in - don't go back to kR12MajorFormatNumber later
#define kCC14MajorFormatNumber				RezLong(19)	// Major format number for any new persistent data in 14.0
#define kCC15MajorFormatNumber				RezLong(20)	// Major format number for any new persistent data in 15.0
#define kCC15_1MajorFormatNumber			RezLong(21)	// Major format number for any new persistent data in 15.0
#define kCC16MajorFormatNumber				RezLong(22) // Major format number for any new persistent data in 16.0

#define kCurrentMajorFormatNumber			kCC16MajorFormatNumber


// The final K2 minor format version.
#define kLastK2MinorVersionNumber			RezLong(307)


// Initial minor format numbers for each release
#define kHotakaInitialMinorFormatNumber		RezLong(1)
#define kAnnaInitialMinorFormatNumber		RezLong(1)
#define kDragontailInitialMinorFormatNumber	RezLong(1)
#define kFiredrakeInitialMinorFormatNumber	RezLong(1)
#define kCobaltInitialMinorFormatNumber		RezLong(1)
#define kBasilInitialMinorFormatNumber		RezLong(1)
#define kRocketInitialMinorFormatNumber		RezLong(1)
#define kOdinInitialMinorFormatNumber		RezLong(1)
#define kAthosInitialMinorFormatNumber		RezLong(1)
#define kCitiusInitialMinorFormatNumber		RezLong(1)
#define kSiriusInitialMinorFormatNumber		RezLong(1)
#define kR5InitialMinorFormatNumber			RezLong(1)
#define kR7InitialMinorFormatNumber			RezLong(1)
#define kR10InitialMinorFormatNumber		RezLong(1)
#define kR12InitialMinorFormatNumber		RezLong(1)
#define kR13InitialMinorFormatNumber		RezLong(1)
#define kCC14InitialMinorFormatNumber		RezLong(1)
#define kCC15InitialMinorFormatNumber		RezLong(1)
#define kCC16InitialMinorFormatNumber		RezLong(1)


#endif  // __FormatNumber__
