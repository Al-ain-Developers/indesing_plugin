//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FormatID.h $
//  
//  Owner: Steve Pellegrin
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
//  Purpose of Interface:
//  Specifies format numbers for file format conversion.
//  
//========================================================================================

#ifndef __FormatID__
#define __FormatID__

// ----- Interfaces -----

#include "IPMStream.h"


#pragma export on
class PUBLIC_DECL FormatID
{
public:
   	typedef base_type data_type;

	FormatID() :
		fMajorNumber(0),
		fMinorNumber(0)
		{}
	FormatID(int32 majorNumber, int32 minorNumber) :
		fMajorNumber(majorNumber),
		fMinorNumber(minorNumber)
		{}		
	FormatID(const FormatID &other) :
		fMajorNumber(other.fMajorNumber),
		fMinorNumber(other.fMinorNumber)
		{}
	FormatID(IPMStream *s) :
		fMajorNumber(0),
		fMinorNumber(0)
	{
		if (s->IsReading()) ReadWrite(s);
	}

	int32 GetMajorVersion() const
		{ return fMajorNumber; }
	void SetMajorVersion(int32 m)
		{fMajorNumber =m;}
	int32 GetMinorVersion() const 
		{ return fMinorNumber; }
	void SetMinorVersion(int32 m)
		{fMinorNumber = m;}

	bool16 IsUnknown() const
		{return ((fMajorNumber == 0) && (fMinorNumber == 0));}
	void SetUnknown()
		{fMajorNumber = fMinorNumber = 0;}

	bool16 operator <(const FormatID& other) const
		{return (fMajorNumber == other.fMajorNumber) ? (fMinorNumber < other.fMinorNumber) : (fMajorNumber < other.fMajorNumber);}
	bool16 operator >(const FormatID& other) const
		{return (fMajorNumber == other.fMajorNumber) ? (fMinorNumber > other.fMinorNumber) : (fMajorNumber > other.fMajorNumber);}
	bool16 operator ==(const FormatID& other) const
		{return (fMajorNumber == other.fMajorNumber) && (fMinorNumber == other.fMinorNumber);}
	bool16 operator !=(const FormatID& other) const
		{return !(*this == other);}		
	bool16 operator <=(const FormatID& other) const
		{return !(*this > other);}
	bool16 operator >=(const FormatID& other) const
		{return !(*this < other);}
		
	void ReadWrite(IPMStream *s)
		{s->XferInt32(fMajorNumber);
		 s->XferInt32(fMinorNumber);}

private:
	int32		fMajorNumber;
	int32		fMinorNumber;
};
#pragma export off

#endif // __FormatID__

