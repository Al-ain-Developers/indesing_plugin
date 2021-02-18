#include "VCPlugInHeaders.h"			    

// Interface includes:
// none. 

// Project includes:
#include "IDHAMemoryXferBytes.h"
//#include "IDHAMemID.h" // for kPrtMemPluginName

/* Constructor
*/
IDHAMemoryXferBytes::IDHAMemoryXferBytes(void) 
: 	fMyBuffer(nil),
	fCurrentMaxBuf(eIDHAInitialMaxBuf),
	fAbsolutePositionInBuffer(0),
	fCountBytesStored(0),
	fStreamState(kStreamStateGood)
{
	fMyBuffer = new char [fCurrentMaxBuf];
	ASSERT(fMyBuffer);
	memset(fMyBuffer, 0,fCurrentMaxBuf);
}

/* Destructor
*/
IDHAMemoryXferBytes::~IDHAMemoryXferBytes(void)
{
	if (fMyBuffer)
	{
		delete [] fMyBuffer;
		fMyBuffer = nil;
	}
}

/* resizeBuffer
*/
void IDHAMemoryXferBytes::resizeBuffer(uint32 newSize)
{
	do
	{
		bool16 preconditions = (newSize > eIDHAInitialMaxBuf);
		if (preconditions == kFalse)
		{
			ASSERT_FAIL("preconditions are not met");
			break;
		}

		// create a new temporary buffer that is bigger. 
		// (Don't just resize by a little amount...)
		uint32 newTargetBufferSize = eIDHAInitialMaxBuf + newSize;
		char* tempBuffer = new char [newTargetBufferSize];
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
uint32 IDHAMemoryXferBytes::Read(void* buffer, uint32 pnum)
{
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
		if (numToTransfer > 0)
			memcpy(buffer, fMyBuffer + fAbsolutePositionInBuffer, numToTransfer);

		fAbsolutePositionInBuffer += numToTransfer;

	} while (false);
	return numToTransfer;

}



/* Write
*/
uint32 IDHAMemoryXferBytes::Write(void* buffer, uint32 pnum)
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
uint64 IDHAMemoryXferBytes::Seek(int64 numberOfBytes, SeekFromWhere fromHere)
{
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
void IDHAMemoryXferBytes::Flush(void)
{
}

/* GetStreamState
*/  
StreamState IDHAMemoryXferBytes::GetStreamState(void)
{
	return this->fStreamState;
}

/* SetEndOfStream
*/  
void IDHAMemoryXferBytes::SetEndOfStream(void)
{
	this->fCountBytesStored = this->fAbsolutePositionInBuffer;
}

/* getBufferPtr
*/
const char* IDHAMemoryXferBytes::getBufferPtr(void) const
{
	return this->fMyBuffer;
}

// End, IDHAMemoryXferBytes.cpp.

