//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPatientUserPreference.h $
//  
//  Owner: Yeming Liu
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
//  
//  Purpose:	Interface for handling patient user preference. This is a session preference. 
//  
//========================================================================================

#pragma once
#ifndef __IPATIENTUSERPREFERENCE__
#define __IPATIENTUSERPREFERENCE__

/** Minimum delay for patient user */
#define kMinPatientUserDelay	-1

/** Maximum delay for patient user */
#define kMaxPatientUserDelay	10000

#ifndef __ODFRC__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- ID.h files -----

#include "LayoutID.h"

/**
   This is a data interface to allow clients to get/set widget id.
*/
class IPatientUserPreference : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPATIENTUSERPREFERENCE };
		
		typedef enum { kPatientUserModeOff = -1, 
			           kPatientUserWithNoDelay = 0, 
					   kPatientUserWithFastDelay = 330, // milliseconds
					   kPatientUserWithStandardDelay = 500, // milliseconds
					   kPatientUserWithLongDelay = 1000 // milliseconds
		             } PatientUserDelayMode;

		/**
		   Set patient user delay time.
		   If milliseconds is set as negative value(< 0), then it turns off patient user mode.

           @param uint32 --- milliseconds for patient user delay, e.g., 500 milliseconds for 1/2 second.
		*/
		virtual void SetPatientUserDelayTime(const int32& milliseconds) = 0;

		/**
		   Get patient user delay time

           @return uint32.
		*/
		virtual int32 GetPatientUserDelayTime() const = 0;
};

#endif  // __ODFRC__
#endif //__IPATIENTUSERPREFERENCE__
