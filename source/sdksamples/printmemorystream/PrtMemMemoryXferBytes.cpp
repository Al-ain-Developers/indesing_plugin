//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printmemorystream/PrtMemMemoryXferBytes.cpp $
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

#include "VCPlugInHeaders.h"			    

// Interface includes:
// none. 

// Project includes:
#include "PrtMemMemoryXferBytes.h"
#include "PrtMemID.h" // for kPrtMemPluginName

/* Constructor
*/
PrtMemMemoryXferBytes::PrtMemMemoryXferBytes(void) 
: 	fMyBuffer(nil),
	fCurrentMaxBuf(ePrtMemInitialMaxBuf),
	fAbsolutePositionInBuffer(0),
	fCountBytesStored(0),
	fStreamState(kStreamStateGood)
{
	fMyBuffer = new uint8 [fCurrentMaxBuf];
	ASSERT(fMyBuffer);
	memset(fMyBuffer, 0,fCurrentMaxBuf);
	TRACEFLOW(kPrtMemPluginName, "PrtMemMemoryXferBytes constructor\n");

}

/* Destructor
*/
PrtMemMemoryXferBytes::~PrtMemMemoryXferBytes(void)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemMemoryXferBytes destructor\n");
	this->dumpState();
	if (fMyBuffer)
	{
		delete [] fMyBuffer;
		fMyBuffer = nil;
	}
}

/* resizeBuffer
*/
void PrtMemMemoryXferBytes::resizeBuffer(uint32 newSize)
{
	do
	{
		bool16 preconditions = (newSize > ePrtMemInitialMaxBuf);
		if (preconditions == kFalse)
		{
			ASSERT_FAIL("preconditions are not met");
			break;
		}

		// create a new temporary buffer that is bigger. 
		// (Don't just resize by a little amount...)
		uint32 newTargetBufferSize = ePrtMemInitialMaxBuf + newSize;
		uint8* tempBuffer = new uint8 [newTargetBufferSize];
		if (tempBuffer == nil)
		{
			ASSERT_FAIL("new operator failed to allocate for tempBuffer");
			break;
		}
		// initialize the temp buffer data to 0
		memset(tempBuffer, 0, newSize);
		ASSERT(tempBuffer);
		// copy the data from existing buffer to temp buffer 
		memcpy(tempBuffer, this->fMyBuffer, this->fCurrentMaxBuf);

		// delete the buffer (member variable)
		delete [] fMyBuffer;
		// reassign member pointers and size
		this->fMyBuffer = tempBuffer;
		this->fCurrentMaxBuf = newTargetBufferSize;

		// Postconditions: fMyBuffer is not nil
		ASSERT(tempBuffer);

		// It is able to store newTargetBufferSize bytes
	} while (kFalse);
}


/* Read
*/
uint32 PrtMemMemoryXferBytes::Read(void* buffer, uint32 pnum)
{
	// TODO - test 
	// ipaterso: I've not tested this at all, as I've only use a Write stream
	// with this code
	uint32 numToTransfer = 0;
	do
	{
		if (buffer == nil)
		{
			ASSERT_FAIL("buffer is nil!");
			break;
		}
		
		uint32 numLeftInBuffer = this->fCountBytesStored - this->fAbsolutePositionInBuffer;
	
		if (pnum > numLeftInBuffer)
		{
			numToTransfer = numLeftInBuffer;
			fStreamState = kStreamStateEOF;
		}
		else
		{
			numToTransfer = pnum;
		}
		// Something like:
		// memcpy (buffer, <somewhere in buffer>, numToTransfer);
		bool16 canRead = (fAbsolutePositionInBuffer + numToTransfer) < fCurrentMaxBuf; 
		if (canRead)
		{
			memcpy(buffer, fMyBuffer + fAbsolutePositionInBuffer, numToTransfer);
		}
		else
		{
			ASSERT_FAIL("canRead is false, our buffer isn't big enough");
		}

	} while (false);
	return numToTransfer;

}


/* Write
*/
uint32 PrtMemMemoryXferBytes::Write(void* buffer, uint32 pnum)
{

	uint32 numToTransfer = 0;
	do
	{
		if (buffer == nil)
		{
			ASSERT_FAIL("buffer is nil!");
			break;
		}

		numToTransfer = pnum;
		// We want to add this data at fAbsolutePositionInBuffer...
		uint32 endOfWriteBytes = (this->fAbsolutePositionInBuffer + numToTransfer);
		bool16 noOverflow = endOfWriteBytes < fCurrentMaxBuf; 
		if (noOverflow == kFalse)
		{
			this->resizeBuffer(endOfWriteBytes + 1); 
		}
		noOverflow = endOfWriteBytes < fCurrentMaxBuf; 
		ASSERT(noOverflow);

		if (numToTransfer > 0 && noOverflow)
		{
			memcpy(this->fMyBuffer + this->fAbsolutePositionInBuffer, buffer, numToTransfer);
			this->fAbsolutePositionInBuffer += numToTransfer;
			if (fAbsolutePositionInBuffer > this->fCountBytesStored)
			{
				this->fCountBytesStored = this->fAbsolutePositionInBuffer;
			}
		}
	} while (false);
	return numToTransfer;
}

/* Seek
*/      
uint64 PrtMemMemoryXferBytes::Seek(int64 numberOfBytes, SeekFromWhere fromHere)
{
    // since it is implemented using single memory buffer, it is good to limit size < 2GB over single buffer
    ASSERT_MSG(numberOfBytes < std::numeric_limits<int32>::max(), "PrtMemMemoryXferBytes doesn't support more than 2 GB seek.");
	if (fStreamState == kStreamStateEOF)
	{
		fStreamState = kStreamStateGood;
	}
	switch (fromHere)
	{
	case kSeekFromStart:
		this->fAbsolutePositionInBuffer = numberOfBytes;
		break;
	case kSeekFromCurrent:
		this->fAbsolutePositionInBuffer = this->fAbsolutePositionInBuffer + numberOfBytes;
		break;
	case kSeekFromEnd:
		this->fAbsolutePositionInBuffer = this->fCountBytesStored + numberOfBytes;
		break;
	}
	return fAbsolutePositionInBuffer;
}

/* Flush
*/
void PrtMemMemoryXferBytes::Flush(void)
{
	// Do nothing. 
	// I guess we'd only care about this in file-based implementation,
	// at which point we'd flush to disk.
}

/* GetStreamState
*/  
StreamState PrtMemMemoryXferBytes::GetStreamState(void)
{
	return this->fStreamState;
}

/* SetEndOfStream
*/  
void PrtMemMemoryXferBytes::SetEndOfStream(void)
{
	this->fCountBytesStored = this->fAbsolutePositionInBuffer;
}

/* getBufferPtr
*/
const uint8* PrtMemMemoryXferBytes::getBufferPtr(void) const
{
	return this->fMyBuffer;
}

/* dumpState
*/
void PrtMemMemoryXferBytes::dumpState(void) const
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemMemoryXferBytes::dumpState()\n");
	TRACEFLOW(kPrtMemPluginName, "-- Abs. position in buffer = 0x%x\n", this->fAbsolutePositionInBuffer);
	TRACEFLOW(kPrtMemPluginName, "-- Bytes stored = 0x%x\n", this->fCountBytesStored);
	TRACEFLOW(kPrtMemPluginName, "-- Current maxbuf = 0x%x\n\n", this->fCurrentMaxBuf);
	PMString data;
	const int32 nbytes = 2048;
	data.SetXString(reinterpret_cast<const char*>(this->getBufferPtr()), nbytes);
	TRACEFLOW(kPrtMemPluginName, "First %d bytes: \n%s\n\n\n", nbytes, data.GetUTF8String().c_str());
}

// End, PrtMemMemoryXferBytes.cpp.

