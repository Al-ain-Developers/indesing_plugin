//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printmemorystream/PrtMemMemoryXferBytes.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __PrtMemMemoryXferBytes_h__
#define __PrtMemMemoryXferBytes_h__

// Interface/General includes:
#include "IXferBytes.h" /* This is NOT an boss interface. */


/** Implements IXferBytes over a memory buffer. 
 * 	We associate this with a stream (IPMStream) by calling
 * 	at some point IPMStream::SetXferBytes
 * 	@ingroup printmemorystream
*/
class  PrtMemMemoryXferBytes : public IXferBytes 
{
public:
	/** Constructor
	*/
	PrtMemMemoryXferBytes(void);

	/** Destructor
	*/
	virtual ~PrtMemMemoryXferBytes(void);

	//--- The IXferBytes interface we must implement  ---

	/** See IXferBytes::Read
	*/
	virtual uint32 Read(void* buffer, uint32 num);

	/** See IXferBytes::Write
	*/
	virtual uint32 Write(void* buffer, uint32 num);

	/** See IXferBytes::Seek
	*/
	virtual uint64 Seek(int64 numberOfBytes, SeekFromWhere fromHere);

	/** See IXferBytes::Flush
	*/
	virtual void Flush(void);

	/** See IXferBytes::GetStreamState
	*/
	virtual StreamState GetStreamState(void);

	/** See IXferBytes::SetEndOfStream
	*/
	virtual void SetEndOfStream(void);

protected:
	const uint8*  getBufferPtr(void) const;
	void resizeBuffer(uint32 newSize);
	void dumpState(void) const;

private:

	StreamState fStreamState;
	uint32 fCountBytesStored;
	uint32 fAbsolutePositionInBuffer;
	uint8* fMyBuffer;
	uint32 fCurrentMaxBuf;

	enum
	{
		ePrtMemInitialMaxBuf = 1024*1024
	};
};

#endif // __PrtMemMemoryXferBytes_h__

// End, PrtMemMemoryXferBytes.h.
