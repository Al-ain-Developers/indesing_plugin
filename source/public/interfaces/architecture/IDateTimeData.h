//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDateTimeData.h $
//  
//  Owner: 
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
#ifndef __IDateTimeData__
#define __IDateTimeData__

#include "IPMUnknown.h"

//Interfaces

//Utils & IDs
#include "LibraryProviderID.h"
#include "PMString.h"

/** Data interface to store global time.
	GlobalTime is based on a uint64 bit number.  It matches NT's FILETIME, the number
	of 100 nanoseconds since January 1, 1601, and it is UTC based.

	@ingroup arch_coredata 
	@see GlobalTime
*/
class IDateTimeData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDATETIMEDATA };
	
		/**	Set the time.
			@param date GlobalTime value of the date to set.
		*/
		virtual void				Set( uint64 date ) = 0;

		/** Get the time.
			@return GlobalTime value of the current time.
		*/
		virtual uint64			Get() const = 0;	
		/** Get the time as a string.
			@return GlobalTime formatted as a string.
		*/
		virtual PMString		GetAsString() const = 0;						
};

#endif
 