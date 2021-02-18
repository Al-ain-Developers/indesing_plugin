//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPatientUserPrefsCmdData.h $
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
#ifndef __IPATIENTUSERPREFSCMDDATA__
#define __IPATIENTUSERPREFSCMDDATA__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- ID.h files -----

#include "LayoutID.h"

/**
   This is a data interface to allow clients to get/set widget id.
*/
class IPatientUserPrefsCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPATIENTUSERPREFSCMDDATA };
		
		/**
		   Set patient user delay time.

           @param uint32 --- milliseconds for patient user delay, e.g., 500 millisecons for 1/2 second.
		*/
		virtual void SetPatientUserDelayTime(const int32& milliseconds) = 0;

		/**
		   Get patient user delay time

           @return uint32.
		*/
		virtual int32 GetPatientUserDelayTime() const = 0;
};

#endif //__IPATIENTUSERPREFSCMDDATA__