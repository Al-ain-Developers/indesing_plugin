//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/streaming/CStreamWrite.cpp $
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

#include "CStreamWrite.h"
#include "IXferBytes.h"
#include "Swap.h"
#include "K2Assert.h"
#include "SystemUtils.h"
#include "IContentTracker.h"

#if 1				// ##rk: rkCONVERSION HACK!!!
#include "TextID.h"
#include "TextOnPathID.h"
#endif

DEFINE_HELPER_METHODS(CStreamWrite)

CStreamWrite::CStreamWrite(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	fXferBytes(nil),
	fSwapping(kFalse)
{
}


CStreamWrite::~CStreamWrite()
{
	Close();
}


StreamState CStreamWrite::GetStreamState()
{
	return fXferBytes->GetStreamState();
}


uchar CStreamWrite::XferByte(uchar& chr)
{
	fXferBytes->Write (&chr, 1);

	return chr;
}



int32 CStreamWrite::XferByte(uchar *buf, int32 num)
{
	return fXferBytes->Write (buf, num);
}


int32 CStreamWrite::XferByteReverse(uchar *buf, int32 num)
{
	int32 numWritten = 0;

	for (int32 i = (num - 1); i >= 0; --i)
	{
		int32 count = fXferBytes->Write(&buf[i], 1);
		if (count == 0)
		{
			// Output error, quit now.
			break;
		}

		++numWritten;
	}

	return numWritten;
}


// until we have not completly switched to bool16 the original
// implementation of XferBool keeps us from being able to open
// a windows pub on the mac. (Roey 10-8-97)

bool16 CStreamWrite::XferBool(bool16& chr)
{
	ASSERT_MSG(chr == kFalse || chr == kTrue, "CStreamWrite::XferBool - this isn't a bool you are writing");
	int16	data = (chr == kFalse ? kFalse : kTrue);
	return chr = (bool16) XferInt16(data);
}

int32 CStreamWrite::XferBool(bool16 *buf, int32 num)
{
	ASSERT_FAIL("Warning: Using XferBool(bool16 *buf, int32 num) is currently not crossplatfom savvy");
	return XferInt16((int16*)buf, num);
}

// original code
/*
bool16 CStreamWrite::XferBool(bool16& chr)
{
	return (bool16)XferInt16((int16&)chr);
}

int32 CStreamWrite::XferBool(bool16 *buf, int32 num)
{
	return XferInt16((int16*)buf, num);
}
*/


int16 CStreamWrite::XferInt16(int16& i)
{
	if ( !fSwapping )
	{
		fXferBytes->Write (&i, 2);
	}
	else
	{
		uint16 b = ByteSwapReverse::SwapInt16 (i);
		fXferBytes->Write (&b, 2);
	}

	return i;
}



int32 CStreamWrite::XferInt16(int16 *buf, int32 num)
{
	int32 i = 0;

	if ( !fSwapping )
	{
		i = fXferBytes->Write (buf, num * 2) / 2;
	}
	else
	{
		while ( i < num )
		{
			int16 b;

			b = ByteSwapReverse::SwapInt16 (*buf);

			fXferBytes->Write (&b, 2);

			i++;
			buf++;
		}
	}

	return i;
}



int32 CStreamWrite::XferInt32(int32& i)
{
	if ( !fSwapping )
	{
		fXferBytes->Write (&i, 4);
	}
	else
	{
		int32 b = ByteSwapReverse::SwapInt32 (i);
		fXferBytes->Write (&b, 4);
	}

	return i;
}



int32 CStreamWrite::XferInt32(int32 *buf, int32 num)
{
	int32 i = 0;

	if ( !fSwapping )
	{
		i = fXferBytes->Write (buf, num * 4) / 4;
	}
	else
	{
		while ( i < num )
		{
			int32 b;

			b = ByteSwapReverse::SwapInt32 (*buf);

			fXferBytes->Write (&b, 4);

			i++;
			buf++;
		}
	}

	return i;
}



int64 CStreamWrite::XferInt64(int64& i)
{
#define Hiuint32(a) ((uint32)(a >> 32))
#define Louint32(a) ((uint32)(a))

	uint32 temph = Hiuint32(i);
	XferInt32((int32&)temph);

	uint32 templ = Louint32(i);
	XferInt32((int32&)templ);

	return i;
}

uintptr_t CStreamWrite::XferPointer(uintptr_t& i)
{
	ASSERT_IF_WRITING_TO_DOCUMENT(this);
	ASSERT_IF_WRITING_TO_DEFAULTS(this);

	if (sizeof(uintptr_t) == sizeof(int32))
	{
		int32	temp = static_cast<int32>(i);
		XferInt32(temp);
	}
	else if (sizeof(uintptr_t) == sizeof(int64))
	{
		int64	temp64 = static_cast<int64>(i);
		XferInt64(temp64);
	}

	return i;
}

ClassID CStreamWrite::XferID(ClassID& i)
{

	InterfacePtr<IContentTracker> contentTracker(this, IID_ICONTENTTRACKER);
	if (contentTracker != nil)
			contentTracker->AddClass(i);

	XferInt32((int32&)i.Get());

	return i;
}


int32 CStreamWrite::XferID(ClassID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


ImplementationID CStreamWrite::XferID(ImplementationID& i)
{
	InterfacePtr<IContentTracker> contentTracker(this, IID_ICONTENTTRACKER);
	if (contentTracker != nil)
			contentTracker->AddTag(i);

	XferInt32((int32&)i.Get());

	return i;
}


int32 CStreamWrite::XferID(ImplementationID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


WidgetID CStreamWrite::XferID(WidgetID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}


int32 CStreamWrite::XferID(WidgetID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


PluginID CStreamWrite::XferID(PluginID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}


int32 CStreamWrite::XferID(PluginID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


PMIID CStreamWrite::XferID(PMIID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}


int32 CStreamWrite::XferID(PMIID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferID(buf[i]);
	return num;
}


int32 CStreamWrite::XferID(ActionID *buf, int32 count)
{
	for (int32 i = 0; i < count; ++i)
		XferID(buf[i]);
	return count;
}



ActionID CStreamWrite::XferID(ActionID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}


int32 CStreamWrite::XferID(ScriptElementID *buf, int32 count)
{
	for (int32 i = 0; i < count; ++i)
		XferID(buf[i]);
	return count;
}



ScriptElementID CStreamWrite::XferID(ScriptElementID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}

int32 CStreamWrite::XferID(ScriptID *buf, int32 count)
{
	for (int32 i = 0; i < count; ++i)
		XferID(buf[i]);
	return count;
}



ScriptID CStreamWrite::XferID(ScriptID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}



LinkClientID CStreamWrite::XferID(LinkClientID& i)
{
	XferInt32((int32&)i.Get());

	return i;
}

int32 CStreamWrite::XferID(LinkClientID *buf, int32 count)
{
	for (int32 i = 0; i < count; ++i)
		XferID(buf[i]);
	return count;
}



UID CStreamWrite::XferReference(UID& u)
{
	return XferInt32 ((int32&)u);
}



int32 CStreamWrite::XferReference(UID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferReference(buf[i]);
	return num;
}



UID CStreamWrite::XferObject(UID& u)
{
	return XferInt32 ((int32&)u);
}



int32 CStreamWrite::XferObject(UID *buf, int32 num)
{
	for (int32 i = 0; i < num; ++i)
		XferObject(buf[i]);
	return num;
}




PMReal& CStreamWrite::XferRealNumber(PMReal& r)
{
	double dblVal = ::ToDouble (r);

	if ( fSwapping )
	{
		XferByteReverse ((uchar*)&dblVal, sizeof(double));
	}
	else
	{
		XferByte ((uchar*)&dblVal, sizeof(double));
	}


	return r;
}



int32 CStreamWrite::XferRealNumber(PMReal *buf, int32 num)
{
	int32 i = 0;

	while (i < num)
	{
		XferRealNumber (*buf);

		i++;
		buf++;
	}

	return i;
}


void CStreamWrite::Comment(const char* comment)
{
}


int64 CStreamWrite::Seek(int64 numberOfBytes, SeekFromWhere fromHere)
{
	return fXferBytes->Seek (numberOfBytes, fromHere);
}

void CStreamWrite::Flush()
{
	fXferBytes->Flush();
}



bool16 CStreamWrite::IsReading() const
{
	return kFalse;
}



bool16 CStreamWrite::IsWriting() const
{
	return kTrue;
}


bool16 CStreamWrite::IsWritingForDuplication(IDataBase**) const
{
	return kFalse;
}


void CStreamWrite::SetSwapping(bool16 swapping)
{
	fSwapping = swapping;
}



bool16 CStreamWrite::GetSwapping() const
{
	return fSwapping;
}



void CStreamWrite::SetEndOfStream()
{
	fXferBytes->SetEndOfStream();
}


bool16 CStreamWrite::Open()
{
	return kTrue;
}

void CStreamWrite::Close()
{
}
