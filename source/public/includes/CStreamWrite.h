//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CStreamWrite.h $
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

#pragma once
#ifndef __CStreamWrite__
#define __CStreamWrite__

#include "IPMStream.h"
#include "HelperInterface.h"

class IXferBytes;
class CStreamRead;

#pragma export on

class PUBLIC_DECL CStreamWrite : public IPMStream
{
public:
	CStreamWrite(IPMUnknown *boss);
	virtual ~CStreamWrite();

	virtual uchar XferByte(uchar& chr) ;
	virtual int32 XferByte(uchar *buf, int32 num) ;

	virtual bool16 XferBool(bool16& chr) ;
	virtual int32 XferBool(bool16 *buf, int32 num) ;

	virtual int16 XferInt16(int16& i) ;
	virtual int32 XferInt16(int16 *buf, int32 num) ;

	virtual int32 XferInt32(int32& i) ;
	virtual int32 XferInt32(int32 *buf, int32 num) ;

	virtual int64 XferInt64(int64& i) ;

	virtual uintptr_t XferPointer(uintptr_t& i);

	virtual ClassID XferID(ClassID& i) ;
	virtual int32 XferID(ClassID *buf, int32 num) ;

	virtual ImplementationID XferID(ImplementationID& i) ;
	virtual int32 XferID(ImplementationID *buf, int32 num) ;

	virtual WidgetID XferID(WidgetID& i) ;
	virtual int32 XferID(WidgetID *buf, int32 num) ;

	virtual PluginID XferID(PluginID& i) ;
	virtual int32 XferID(PluginID *buf, int32 num) ;

	virtual PMIID XferID(PMIID& i) ;
	virtual int32 XferID(PMIID *buf, int32 num) ;

	virtual ActionID XferID(ActionID& i);
	virtual int32 XferID(ActionID *buf, int32 num);

	virtual ScriptElementID XferID(ScriptElementID& i);
	virtual int32 XferID(ScriptElementID *buf, int32 num);

	virtual ScriptID XferID(ScriptID& i);
	virtual int32 XferID(ScriptID *buf, int32 num);

	virtual LinkClientID XferID(LinkClientID& i);
	virtual int32 XferID(LinkClientID *buf, int32 num);

	virtual UID XferObject(UID& u);
	virtual int32 XferObject(UID *buf, int32 num);

	virtual UID XferReference(UID& u);
	virtual int32 XferReference(UID *buf, int32 num);

	virtual PMReal& XferRealNumber(PMReal& r);
	virtual int32 XferRealNumber(PMReal *buf, int32 num);

	virtual void Comment(const char* comment);

	virtual int64 Seek(int64 numberOfBytes, SeekFromWhere fromHere) ;
	virtual void SetEndOfStream();
	virtual void Flush();

	virtual StreamState GetStreamState();

	virtual bool16 IsReading() const ;
	virtual bool16 IsWriting() const ;
	virtual bool16 IsWritingForDuplication(IDataBase**) const ;

	virtual void SetSwapping(bool16 swapping);
	virtual bool16 GetSwapping() const;

	void SetXferBytes(IXferBytes *xferBytes)	{ fXferBytes = xferBytes; }

protected:
	IXferBytes *GetXferBytes()	{ return fXferBytes; }
	virtual bool16 Open();
	virtual void Close();

private:
	int32 XferByteReverse(uchar *buf, int32 num) ;

private:
	IXferBytes*		fXferBytes;
	bool16			fSwapping;

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
