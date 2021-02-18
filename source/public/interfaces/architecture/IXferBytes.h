//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IXferBytes.h $
//  
//  Owner: Robin Briggs
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
//  Purpose:
//  This is the underlying data model for streaming. Handles the connection
//  between the stream and the backend buffer storage system (file, database 
//  record, memory, etc.).	
//  
//  THIS IS NOT A STANDARD BOSS INTERFACE
//  
//========================================================================================

#pragma once
#ifndef __IXFERBYTES__
#define __IXFERBYTES__

#include "IPMStream.h"

/** IXferBytes is a very simple streaming protocol that underlies the streaming classes.
	Generally you do not need to access it directly, but it can be useful if you are 
	want to have a read-write stream, or if you need to implement a new stream implementation.
	@see IPMStream
*/
class IXferBytes 
{

public:
	virtual ~IXferBytes()
		{}
		
		/** Read the next num bytes from the stream into the buffer.
			Returns the number of bytes that were read in, this can be
			less than the number requested if end of stream or some other
			error is encountered.
			@param buffer where to put the data read in
			@param num number of bytes requested to read
			@return uint32 number of bytes actually read.
		*/
	virtual uint32 Read(void *buffer, uint32 num) = 0;
	
		/** Write num bytes from the buffer into the stream at the
			current location. Returns the number of bytes that were
			actually written out.
			@param buffer contains the data to write
			@param num number of bytes requested to write
			@return uint32 number of bytes actually written
		*/
	virtual uint32 Write(void *buffer, uint32 num) = 0;
	
		/** Set the stream's current location. Returns the current (new)
			position as an offset from the start of the stream.
			@param numberOfBytes how far to seek
			@param fromHere seek relative to this point (start, current, or end)
			@return uint32 new location, returned relative to the start of the stream
		*/
	virtual uint64 Seek(int64 numberOfBytes, SeekFromWhere fromHere) = 0;

		/** Flush all pending output out to the stream.
		*/
	virtual void Flush() = 0;
	
		/** Get the stream status (how to check for end of file).
		*/
	virtual StreamState GetStreamState() = 0;
	
		/** Truncate the stream at the current location. Any read past
			this point will encounter end of stream.
		*/
	virtual void SetEndOfStream() = 0;
};

#endif // __IXFERBYTES__
