//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/FileBytesOutStream.cpp $
//  
//  Owner: gxiao 
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "FileBytesOutStream.h"

#ifdef MACINTOSH
#include "MacFileUtils.h"
#include "CoreFileUtils.h"
#endif

FileBytesOutStream::FileBytesOutStream(int32 bufferSize) :
#ifdef MACINTOSH
	fHandle(-1),
#else
    fHandle(0),
#endif
	fUsedBufferBytes(0),
	fWriteBuffer(nil)
{
	fBufferSize = bufferSize;
	fWriteBuffer = new char [fBufferSize];
}

FileBytesOutStream::~FileBytesOutStream()
{
#ifdef MACINTOSH
    if (fHandle != -1)
#else
	if (fHandle)
#endif
		Close();

	delete [] fWriteBuffer;
	fWriteBuffer = nil;
}


// write-only file byte output stream
uint32 FileBytesOutStream::Write(void *buffer, uint32 length)
{
#ifdef MACINTOSH
	ASSERT_MSG(fHandle != -1, "fHandle is nil");
#else
	ASSERT_MSG(fHandle != 0, "fHandle is nil");
#endif

	if (!FlushBuffer(length))
		return 0;

	if (length > fBufferSize)
		length = WriteBytes(buffer, length);
	else
	{
		ASSERT_MSG(fWriteBuffer != nil, "FileXferBytes::Write - nil buffer");
		ASSERT_MSG(fUsedBufferBytes + length <= fBufferSize, "FileXferBytes::Write - overflowing buffer");
		
		memcpy(&fWriteBuffer[fUsedBufferBytes], buffer, length);
		fUsedBufferBytes += length;
	}
	
	return length;
}


bool16 FileBytesOutStream::FlushBuffer(uint32 length)
{
	bool16 result = true;
	
	if (fUsedBufferBytes > 0 && length > fBufferSize - fUsedBufferBytes)
	{
		long nout = WriteBytes(fWriteBuffer, fUsedBufferBytes);
		result = nout == fUsedBufferBytes;
		fUsedBufferBytes = 0;
	}
	
	return result;
}


#ifdef WINDOWS
bool16 FileBytesOutStream::Open(IDFile& sysFile)
{
	// Close the current file if it has been opened.
	// have to do this before allocating the buffer, as 'Close()' will release the buffer.
	if (fHandle) 
		Close();
 
	fHandle = CreateFile(sysFile.GrabTString(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);

	if ( fHandle == INVALID_HANDLE_VALUE )
		return kFalse;
	else
		SetFilePointer (fHandle, 0, 0, FILE_BEGIN);
	
	return kTrue;
}


void FileBytesOutStream::Close()
{
	FlushBuffer(fBufferSize);
	ASSERT_MSG(fHandle != 0, "fHandle is nil");

	CloseHandle (fHandle);
	fHandle = 0;
}


void FileBytesOutStream::Flush()
{
	FlushBuffer(fBufferSize);
	ASSERT_MSG(fHandle != 0, "fHandle is nil");
	FlushFileBuffers(fHandle);
}


uint32 FileBytesOutStream::WriteBytes(void* buffer, uint32 length)
{
	ASSERT_MSG(fHandle != 0, "fHandle is nil");

	// Tests have shown that writing 64K bytes at a time is faster than writing lots of data
	const uint32 kOptimalWriteSize = 64 * 1024UL;
	uint32 pos = 0L;
	uint32 nout;
	uchar *bufPtr = (uchar *)buffer;
	do
	{
		nout = length - pos;
		if ( nout > kOptimalWriteSize )
			nout = kOptimalWriteSize;
		else if ( nout > 0x00001000 )
		{
			/* If copyBufferSize is greater than 4K bytes, make it a multiple of 4k bytes */
			/* This will make writes on local volumes faster */
			nout &= 0xfffff000;
		}
		WriteFile (fHandle, bufPtr + pos, nout, &nout, NULL);
				
		pos += nout;
	} while ( pos < length && nout != 0 );
	
	return pos;
}
#endif

#ifdef MACINTOSH
bool16 FileBytesOutStream::Open(IDFile& sysFile)
{
	if (fHandle != -1)
		Close();

	OSErr err;
	sysFile.MakeFile(false, &err);

	// If the file was created or already exists, then set the type and creator information
	if (err == noErr || err == dupFNErr)
	{
		// Ignore all file system errors - if everything else worked the filesystem probably doesn't support it
		MacFileUtils::SetCreatorAndType(sysFile, 'TEXT', 'CWIE');
	}

	AString8 sysFilePath;
	CoreFileUtils::AFileToUTF8(sysFile, sysFilePath);
    
	fHandle = open(sysFilePath.c_str(), O_WRONLY | O_EXLOCK | O_NONBLOCK | O_CLOEXEC);
    
	if (fHandle == -1 && (errno == ENOTSUP || errno == EOPNOTSUPP))
		fHandle = open(sysFilePath.c_str(), O_WRONLY | O_NONBLOCK | O_CLOEXEC);

	if (fHandle == -1)
	{
		return kFalse;
	}
	else
		ftruncate(fHandle, (off_t) 0);

	return kTrue;
}

void FileBytesOutStream::Close()
{
	FlushBuffer(fBufferSize);
	ASSERT_MSG(fHandle != -1, "fHandle is nil");

    close(fHandle);
	fHandle = -1;
}

void FileBytesOutStream::Flush()
{
	FlushBuffer(fBufferSize);
    fsync(fHandle);
}

uint32 FileBytesOutStream::WriteBytes(void* buffer, uint32 length)
{
	// Tests have shown that writing 64K bytes at a time is faster than writing lots of data
	const uint32 kOptimalWriteSize = 64 * 1024UL;

	uint32 pos = 0L;
	uchar *bufPtr = (uchar *)buffer;
	ssize_t nout;
	do
	{
		nout = length - pos;
		if ( nout > kOptimalWriteSize )
			nout = kOptimalWriteSize;
		else if ( nout > 0x00001000 )
		{
			/* If copyBufferSize is greater than 4K bytes, make it a multiple of 4k bytes */
			/* This will make writes on local volumes faster */
			nout &= 0xfffff000;
		}
        
        nout = pwrite(fHandle, (void *)(bufPtr + pos), (size_t)nout, (off_t) 0);
		
        if(nout <= 0)
            break;
        
		pos += nout;
	} while ( pos < length);
		
	return pos;
}
#endif
