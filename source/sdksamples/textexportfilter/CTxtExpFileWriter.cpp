//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/CTxtExpFileWriter.cpp $
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

// General includes
#include "CTxtExpFileWriter.h"
#include "CTUnicodeTranslator.h"

// Project includes
#include "TxtExpID.h"



// no CREATE_PM_INTERFACE since we are not going to instantiate this class directly.

/* Constructor
*/
CTxtExpFileWriter::CTxtExpFileWriter(IPMUnknown* boss, uint8 script)
 : CPMUnknown<ITxtExpFileWriter>(boss), fScript(script) 
{
}

/* Destructor
*/
CTxtExpFileWriter::~CTxtExpFileWriter(void)
{
}

/* WriteTextCharBuffer
*/
int32 CTxtExpFileWriter::WriteTextCharBuffer(IPMStream* stream, const textchar* tcbuf, const int32 bufSize)
{
	int32 written = bufSize;
	
	do {
		int32 ucbufSize = bufSize * 2; 
		uchar* buf = new uchar[ucbufSize+1]; // make it large enough
		if (!buf) 
		{
			ASSERT_FAIL("CTxtExpFileWriter::WriteTextCharBuffer : can't allocate memory for uchar buffer");
			written = 0;
			break;
		}
		// Convert to platform encoding ...
		int32 ucCount = CTUnicodeTranslator::Instance()->TextCharToChar(tcbuf, bufSize, 
																		(char*)buf, ucbufSize, fScript);
		if (ucCount == 0) 
		{
			ASSERT_FAIL("CTxtExpFileWriter::WriteTextCharBuffer : TextCharToChar converted to 0 bytes");
			written = 0;
			break;
		}
				
		// write to stream
		int32 ucWritten = stream->XferByte((uchar*)buf, ucCount); 
		if (!ucWritten) 
		{
			ASSERT_MSG(ucWritten, "CTxtExpFileWriter::WriteTextCharBuffer : wrote 0 bytes to stream");
			written = 0;
			// don't break here, contiunue
		}
		else
		{
			// allocate a temporary textchar buffer to find out
			// how many textchars were actually written
			textchar* temptcBuf = new textchar[bufSize+1];
			if (!temptcBuf) 
			{
				ASSERT_FAIL("CTxtExpFileWriter::WriteTextCharBuffer : couldn't allocate memory for temp tcBuf");
				// just assume that bufSize was written out
				written = bufSize;
				// don't break here, contiunue
			}
			else
			{
				// translate back to UNICODE based on how many bytes were written, 
				// so we could tell the caller how many textchars were ACTUALLY written to stream.
				written = CTUnicodeTranslator::Instance()->CharToTextChar((char*)buf, ucWritten, 
																		  temptcBuf, bufSize, fScript);
				delete [] temptcBuf;
			}
		}

		if (buf) 
		{
			delete [] buf;
		}
	} while (kFalse);
	
	return written;
}

// End, CTxtExpFileWriter.cpp




