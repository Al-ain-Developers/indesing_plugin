//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/streaming/CStreamRead.cpp $
//  
//  Owner: jargast
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

#include "VCPublicHeaders.h"

#include "CStreamRead.h"
#include "IXferBytes.h"
#include "Swap.h"

#if 1				// ##rk: rkCONVERSION HACK!!!
#include "TextID.h"
#include "TextOnPathID.h"
#endif

DEFINE_HELPER_METHODS(CStreamRead)

CStreamRead::CStreamRead(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	fXferBytes(nil),
	fSwapping(kFalse)
{
}

CStreamRead::~CStreamRead()
{
	Close();
}


StreamState CStreamRead::GetStreamState()
{
	return fXferBytes->GetStreamState();
}


uchar CStreamRead::XferByte(uchar& chr)
{
	fXferBytes->Read (&chr, 1);

	return chr;
}



int32 CStreamRead::XferByte(uchar *buf, int32 num)
{
	return fXferBytes->Read (buf, num);
}


int32 CStreamRead::XferByteReverse(uchar *buf, int32 num)
{
	int32 numRead = 0;

	for (int32 i = (num - 1); i >= 0; --i)
	{
		int32 count = fXferBytes->Read(&buf[i], 1);
		if (count == 0)
		{
			// Input error, quit now.
			break;
		}

		++numRead;
	}

	return numRead;
}



bool16 CStreamRead::XferBool(bool16& chr)
{
	int16 data(0);
	XferInt16(data);
	ASSERT_MSG(data == kFalse || data == kTrue, "CStreamRead::XferBool - this isn't a bool you are reading. Something's wrong.");
	return chr = (bool16)data;
}



int32 CStreamRead::XferBool(bool16 *boolbuf, int32 num)
{
	return XferInt16((int16*)boolbuf, num);
}



int16 CStreamRead::XferInt16(int16& i)
{
	int16 b(0);
	fXferBytes->Read(&b, 2);
	i = fSwapping ? ByteSwapReverse::SwapInt16(b) : b;

	return i;
}



int32 CStreamRead::XferInt16(int16 *buf, int32 num)
{
	int32 numread = fXferBytes->Read (buf, num * 2);

	if ( fSwapping )
	{
		for ( int i = 0; i < num; i++, buf++ )
		{
			*buf = ByteSwapReverse::SwapInt16 (*buf);
		}
	}

	return numread / 2;
}



int32 CStreamRead::XferInt32(int32& i)
{
	int32 b(0);
	fXferBytes->Read(&b, 4);
	i = fSwapping ? ByteSwapReverse::SwapInt32 (b) : b;

	return i;
}



int32 CStreamRead::XferInt32(int32 *buf, int32 num)
{
	int32 numread = fXferBytes->Read (buf, num * 4);

	if ( fSwapping )
	{
		for ( int i = 0; i < num; i++, buf++ )
		{
			*buf = ByteSwapReverse::SwapInt32 (*buf);
		}
	}

	return numread / 4;
}



int64 CStreamRead::XferInt64(int64& i)
{
	uint32 temph(0);
	temph = XferInt32((int32&)temph);

	uint32 templ(0);
	templ = XferInt32((int32&)templ);

	i = ((uint64)temph << 32) + templ;

	return i;
}

uintptr_t CStreamRead::XferPointer(uintptr_t& i)
{
//	ASSERT_FAIL("need more asserts");
	if (sizeof(uintptr_t) == sizeof(int32))
	{
		int32	temp(0);
		XferInt32(temp);
		i = static_cast<uintptr_t>(temp);
	}
	else if (sizeof(uintptr_t) == sizeof(int64))
	{
		int64	temp64(0);
		XferInt64(temp64);
		i = static_cast<uintptr_t>(temp64);
	}

	return i;
}

ClassID CStreamRead::XferID(ClassID& i)
{
	return XferInt32((int32&)i.Get());
}



int32 CStreamRead::XferID(ClassID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


ImplementationID CStreamRead::XferID(ImplementationID& i)
{
	return XferInt32((int32&)i.Get());
}



int32 CStreamRead::XferID(ImplementationID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


WidgetID CStreamRead::XferID(WidgetID& i)
{
	return XferInt32((int32&)i.Get());
}



int32 CStreamRead::XferID(WidgetID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


PluginID CStreamRead::XferID(PluginID& i)
{
	return XferInt32((int32&)i.Get());
}



int32 CStreamRead::XferID(PluginID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


PMIID CStreamRead::XferID(PMIID& i)
{
	return XferInt32((int32&)i.Get());
}



int32 CStreamRead::XferID(PMIID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


int32 CStreamRead::XferID(ActionID *buf, int32 count)
{
	for (int32 i = 0; i < count; ++i)
		XferID(buf[i]);
	return count;
}



ActionID CStreamRead::XferID(ActionID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}


int32 CStreamRead::XferID(ScriptElementID *buf, int32 count)
{
	for (int32 i = 0; i < count; ++i)
		XferID(buf[i]);
	return count;
}



ScriptElementID CStreamRead::XferID(ScriptElementID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}

int32 CStreamRead::XferID(ScriptID *buf, int32 count)
{
	for (int32 i = 0; i < count; ++i)
		XferID(buf[i]);
	return count;
}



ScriptID CStreamRead::XferID(ScriptID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}



LinkClientID CStreamRead::XferID(LinkClientID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}

int32 CStreamRead::XferID(LinkClientID *buf, int32 count)
{
	for (int32 i = 0; i < count; ++i)
		XferID(buf[i]);
	return count;
}



UID CStreamRead::XferReference(UID& u)
{
	int32	u2 = (int32)u.Get();
	u = (UID)XferInt32(u2);
	return u;
}



int32 CStreamRead::XferReference(UID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferReference(buf[i]);
	return num;
}


UID CStreamRead::XferObject(UID& u)
{
	int32	u2 = (int32)u.Get();
	u = (UID)XferInt32(u2);
	return u;
}

int32 CStreamRead::XferObject(UID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferObject(buf[i]);
	return num;
}



PMReal& CStreamRead::XferRealNumber(PMReal& r)
{
	double dblVal(0.0);

	if (fSwapping)
	{
		XferByteReverse ((uchar*)&dblVal, sizeof(double));
	}
	else
	{
		XferByte ((uchar*)&dblVal, sizeof(double));
	}

	r = dblVal;
	return r;
}



int32 CStreamRead::XferRealNumber(PMReal *buf, int32 num)
{
	int32 i = 0;

	while ( GetStreamState() == kStreamStateGood && i < num )
	{
		XferRealNumber (*buf);

		i++;
		buf++;
	}

	return i;
}

void CStreamRead::Comment(const char* comment)
{
}

int64 CStreamRead::Seek(int64 numberOfBytes, SeekFromWhere fromHere)
{
	return fXferBytes->Seek (numberOfBytes, fromHere);
}

void CStreamRead::Flush()
{
	fXferBytes->Flush();
}




bool16 CStreamRead::IsReading() const
{
	return kTrue;
}



bool16 CStreamRead::IsWriting() const
{
	return kFalse;
}



void CStreamRead::SetSwapping(bool16 swapping)
{
	fSwapping = swapping;

	//TODO: Set swapping for complement?
}



bool16 CStreamRead::GetSwapping() const
{
	return fSwapping;
}


bool16 CStreamRead::Open()
{
	return kTrue;
}

void CStreamRead::Close()
{
}

void CStreamRead::SetEndOfStream()
{
	fXferBytes->SetEndOfStream();
}

