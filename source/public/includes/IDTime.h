//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IDTime.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  This class provides cross-platform time handling.
//  
//========================================================================================

#pragma once
#ifndef __IDTime__
#define __IDTime__

// ----- Includes -----
#include "ATypes.h"

class IPMStream;

using namespace adobe::afl;


/**
 IDTime is based on an ATime, which is the time measured in 100-nanosecond
 intervals since January 1, 1601 (UTC). An IDTime that is exactly equal to
 an ATime of 0 (January 1, 1601 (UTC)) is considered to be invalid.
*/
class PUBLIC_DECL IDTime
{
public:
	typedef object_type data_type;

#ifdef WINDOWS
	/**
	 Converts an ATime to a UTC FILETIME.
	 @param time [IN] ATime to convert to a UTC FILETIME.
	 @return The resulting UTC FILETIME.
	*/
	static FILETIME ATimeToFILETIME(ATime time);

	/**
	 Converts a UTC FILETIME to an ATime.
	 @param fileTime [IN] UTC FILETIME to convert to an ATime.
	 @return The resulting ATime.
	*/
	static ATime FILETIMEToATime(FILETIME& fileTime);
#elif MACINTOSH
	/**
	 Converts an ATime to an AbsoluteTime
	 @param time [IN] ATime to convert to an AbsoluteTime
	 @return The resulting AbsoluteTime
	 */
	static CFAbsoluteTime ATimeToAbsoluteTime(ATime time);
	
	/**
	 Converts an AbsoluteTime to an ATime.
	 @param fileTime [IN] AbsoluteTime to convert to an ATime.
	 @return The resulting ATime.
	 */
	static ATime AbsoluteTimeToATime(CFAbsoluteTime time);
#endif
	

	/**
	 Default constructor.
	 Constructs an IDTime object with no valid time set.
	 */
	IDTime();

	/**
	 Constructor.
	 @param time [IN] Time to set the stored time to.
	*/
	IDTime(ATime time);

	/**
	 Copy constructor.
	 Constructs an IDTime object that is a copy of the given object.
	 @param time [IN] IDTime object to copy.
	 */
	IDTime(const IDTime& time);

	/**
	 Destructor.
	 Destroys the IDTime object.
	*/
	virtual ~IDTime();

	/**
	 Assignment operator.
	 Assigns the given time to this time.
	 @param rhs	[IN] Time to assign to this time.
	 @return Reference to this object.
	*/
	IDTime& operator=(const IDTime& rhs);

	/**
	 Swaps the given time with this time.
	 @param rhs	[IN] Time to swap with this time.
	*/
	void Swap(IDTime& rhs);

	/**
	 Equality operator.
	 Test whether this time is identical to the given time.
	 @param rhs	[IN] Time to compare to this time.
	 @return True if this time is equal to the given time, else false.
	*/
	bool operator==(const IDTime& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this time is not equal to the given time.
	 @param rhs	[IN] Time to compare to this time.
	 @return True if this time is not equal to the given time, else false.
	*/
	bool operator!=(const IDTime& rhs) const;

	/**
	 Less than operator.
	 Tests whether this time is less than the given time.
	 @param rhs	[IN] Time to compare to this time.
	 @return True if this time is less than the given time, else false.
	*/
	bool operator<(const IDTime& rhs) const;

	/**
	 Greater than operator.
	 Tests whether this time is greater than the given time.
	 @param rhs	[IN] Time to compare to this time.
	 @return True if this time is greater than the given time, else false.
	*/
	bool operator>(const IDTime& rhs) const;

	/**
	 Sets the stored time to the current UTC time.
	*/
	void CurrentTime();

	/**
	 Sets the stored time to the given time value.
	 @param time [IN] Time to set the stored time to.
	*/
	void SetTime(ATime time);

	/**
	 Returns the stored time as an ATime.
	 @return Stored time as an ATime.
	*/
	ATime GetTime() const;

	/**
	 Sets the stored time using the the given local time values.
	 @param year   [IN] Year; for example 2005 (> 1601).
	 @param month  [IN] Month (1 - 12), where January = 1, ..., December = 12.
	 @param day	   [IN] Day of the month (1 - 31).
	 @param hour   [IN] Hour (0 - 23).
	 @param minute [IN] Minute (0 - 59).
	 @param second [IN] Second (0 - 59).
	 @return True if the time was successfully set, else false.
	*/
	bool SetTime(int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second);

	/**
	 Gets the local time components that the IDTime represents. \\
	 All the parameters are optional; pass nil when you do not want a value.
	 @param year	  [OUT] Year; for example 2005 (> 1601).
	 @param month	  [OUT] Month (1 - 12), where January = 1, ..., December = 12.
	 @param day		  [OUT] Day of the month (1 - 31).
	 @param hour	  [OUT] Hour (0 - 23).
	 @param minute	  [OUT] Minute (0 - 59).
	 @param second	  [OUT] Second (0 - 59).
	 @param dayOfWeek [OUT] Day of the week (1 to 7), where Sunday = 1, ..., Saturday = 7.
	 @return True if the local time components were successfully retrieved, else false.
	*/
	bool GetTime(int32* year, int32* month, int32* day, int32* hour, int32* minute, int32* second, int32* dayOfWeek = nil) const;

	/**
	 Returns a local date string that represents the stored date. \\
	 The format of the returned string is dependent on your system and system's settings.
	 @param str		   [OUT] String to fill in.
	 @param bShortform [IN] If true, a short date string return. Otherwise, a long date string is returned.
	 @return True if the method succedes, else false.
	*/
	bool DateToString(WideString& str, bool bShortform) const;

	/**
	 Returns a local time string that represents the stored time. \\
	 The format of the returned string is dependent on your system and system's settings.
	 @param str [OUT] String to fill in.
	 @return True if the method succedes, else false.
	*/
	bool TimeToString(WideString& str) const;

	/**
	 Test whether this time is valid. \\
	 An IDTime that is exactly equal to an ATime of 0 (January 1, 1601 (UTC))
	 is considered to be invalid.
	 @return True if the time is valid, else false.
	*/
	bool IsValid() const;

	/**
	 Persistence-related method for saving or restoring the
	 state of an IDTime object instance.
	 @param iPMStream [IN] Stream to read the instance data from
						   or write the instance data to.
	*/
	void ReadWrite(IPMStream* s);

#ifdef MACINTOSH
	/**
	Enum to be used only on mac for MacDateString API because mac has four formats for date string
	namely short style, medium style, long style & full style
	*/
	enum DateFormatStyle {
		   kDateFormatShortStyle = 0, //e.g. “11/23/37”
		   kDateFormatMediumStyle = 1, //e.g. “Nov 23, 1937”
		   kDateFormatLongStyle = 2, //e.g. “November 23, 1937”
		   kDateFormatFullStyle = 3 //e.g. “Tuesday, April 12, 1952 AD”
	};

	/**
	 Returns a local date string that represents the stored date. \\
	 The format of the returned string is dependent on your system and system's settings.
	 @param str		   [OUT] String to fill in.
	 @param dateFormatStyle [IN] for details look at above mentioned enum DateFormatStyle
	 @return True if the method succeeds, else false.
	*/
	bool MacDateToString(WideString& str, const DateFormatStyle& dateFormatStyle) const;
#endif

private:
	uint64 XferInt64(IPMStream *s, uint64 &value) const;

	ATime fTime;
};


/** A "nil" value for an IDTime -- a valid IDTime will never be equal to kInvalidIDTime. */
extern PUBLIC_DECL const IDTime kInvalidIDTime;

#endif	// __IDTime__
