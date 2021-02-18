//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GlobalTime.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __GlobalTime__
#define __GlobalTime__

// Forward declare
class PMString;

#pragma export on

/**
NOTE: Do not use GlobalTime for new code, please use IDTime instead.
      GlobalTime has problems with time on the Mac due to the way daylight
	  savings time is handled.

GlobalTime provides time features in a core way.

GlobalTime is based on a uint64 bit number.  It matches NT's FILETIME, the number
of 100 nanoseconds since January 1, 1601, and it is UTC based.

@see IDTime
@author Steve Flenniken
*/
class GlobalTime
{
public:
	typedef object_type data_type;

	/** Value that represents one second.
	*/
	enum {kOneSecond = 10000000};

	GlobalTime(){fTime = 0;};

	/** Method to set the stored time to the specified time value.
        @param time is the value to set.  It is equivalent to NT's FILETIME.
	*/
	GlobalTime(uint64 time) {SetTime(time);};

#if MACINTOSH
	/** Macintosh only method to set the stored time to the specified time value.
        @param macseconds is the value to set.  It is equivalent to the Macintosh time value,
		the number of seconds since midnight, January, 1, 1904 and it is in local time.
	*/
	GlobalTime(uint32 macseconds) {SetTime(macseconds);};
#endif

	PUBLIC_DECL ~GlobalTime();

	/** Method to set the stored time to the specified time value.
        @param time is the value to set.  It is equivalent to NT's FILETIME.
	*/
	void SetTime(uint64 time) {fTime = time;};

	/** Method to set the stored time to the specified time value.
        @param year is a year value, for example 2005. The year must be greater than 1601.
		@param month is a value from 1 to 12, where January = 1, February = 2, and so on.
		@param day is the day of the week. A value from 0 to 6 where Sunday = 0, Monday = 1, and so on.
		@param hour is the current hour in 24 hour time.
		@param minute is the current minute.
		@param second is the current second.
        @return 0 the method was successful, otherwise return non-zero.
	*/
	PUBLIC_DECL int32 SetTime(int32 year, int32 month, int32 day, int32 hour,
		int32 minute, int32 second);

#if MACINTOSH
	/** Macintosh only method to set the stored time to the specified time value.
        @param macseconds is the value to set.  It is equivalent to the Macintosh time value,
		the number of seconds since midnight, January, 1, 1904 and it is in local time.
	*/
	PUBLIC_DECL void SetTime(uint32 macseconds);

	/** Macintosh only method to convert Macintosh seconds to a GlobalTime value.
        @param macseconds is the value to set.  It is equivalent to the Macintosh time value,
		the number of seconds since midnight, January, 1, 1904 and it is in local time.
        @return a uint64 that represents the GlobalTime value.
	*/
	PUBLIC_DECL uint64 MacSecondsToFileTime(uint32 macseconds) const;

	/** Macintosh only method to convert a GlobalTime value to Macintosh seconds.
        @param time is the GlobalTime value to convert.
        @return a uint32 that represents the Macintosh seconds.
	*/
	PUBLIC_DECL uint32 FileTimeToMacSeconds(uint64 time) const;
#endif

	/** Method to get the uint64 GlobalTime value.
        @return a uint64 that represents the GlobalTime value.
	*/
	uint64 GetTime() const {return fTime;};

	/** Method to get the time components that the GlobalTime represents.
		All parameters are optional, pass nil when you do not want a value.
		See SetTime for the parameter meanings.
        @param year value to get
        @param month value to get
        @param day value to get
        @param hour value to get
        @param minute value to get
        @param second value to get
        @param day of week (e.g. Tuesday) value to get (1 = Sunday.. 7 = Saturday)
        @return 0 the method was successful, otherwise return non-zero.
	*/
	PUBLIC_DECL int32 GetTime(int32 *year, int32 *month, int32 *day, int32 *hour,
		int32 *minute, int32 *second, int32* dayOfWeek = nil) const;

	/** Method to set the stored time to the current time.
	*/
	PUBLIC_DECL void CurrentTime();

	/** Method to get a date string that represents the stored GlobalTime.
		The string returned is dependent on your system and system's settings.
        @param s is the string to fill in.
        @param shortform is true then you get a short date string, otherwise you get a long date string.
        @return 0 the method was successful, otherwise return non-zero.
	*/
	PUBLIC_DECL int32 DateToString(PMString &s, bool16 shortform) const;

	/** Method to get a time string that represents the stored GlobalTime.
		The string returned is dependent on your system and system's settings.
        @param s is the string to fill in.
        @return 0 the method was successful, otherwise return non-zero.
	*/
	PUBLIC_DECL int32 TimeToString(PMString &s) const;

	/** Method to stream out the GlobalTime value.
        @param s is the stream to write to.
	*/
	PUBLIC_DECL void ReadWrite(IPMStream *s);

	/** Method to determine whether the stored time plus the specified time is in the past.
        @param timeinterval is the time value to add to the current stored time. You can use
		kOneSecond for the timeinterval parameter.
        @return true when the value is in the past.
	*/
	PUBLIC_DECL bool16 IsHistory(uint64 timeinterval) const;

	/** Method to determine whether two GlobalTime values are equal.
        @return true when the values are equal.
	*/
	bool16 operator == (const GlobalTime &gt) const {return fTime == gt.fTime;};

	/** Method to determine whether two GlobalTime values are not equal.
        @return true when the values are not equal.
	*/
	bool16 operator != (const GlobalTime &gt) const {return fTime != gt.fTime;};

	/** Method to determine whether two GlobalTime values are less than each other.
        @return true when the values are less than each other.
	*/
	bool16 operator < (const GlobalTime &gt) const {return fTime < gt.fTime;};

	/** Method to determine whether two GlobalTime values are greater than each other.
        @return true when the values are greater than each other.
	*/
	bool16 operator > (const GlobalTime &gt) const {return fTime > gt.fTime;};

#if DEBUG
	/** DEBUG only method to test this class.
        @return 0 the method was successful, otherwise return non-zero.
	*/
	PUBLIC_DECL bool16 Test() const;
#endif

private:
	uint64 GetCurrentSystemTime() const;
	uint64 XferInt64(IPMStream *s, uint64 &value) const;

#if MACINTOSH
	int32 GetGMTDelta() const;
#endif

	uint64 fTime;
};

#pragma export off

#endif
