//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/ITxtExpFileWriter.h $
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

#ifndef __ITxtExpFileWriter__H__
#define __ITxtExpFileWriter__H__

// includes
#include "TxtExpID.h"
#include "IPMStream.h"
#include "TextChar.h"

/** Size of internal buffer for the file writer implementations.
	For this sample, this is set at 2,048, since many DMA page buffers
	on PCs and Macintoshes are allocated at 4kByte (=4,096) chunks.
	The actual memory space occupied depends on the data type, which could be
	uchar (1 byte each) or textchar (2 bytes each).
	@ingroup textexportfilter
*/
const int32 kTxtExpBufferSize = 2048;

/** From SDK sample; interface to help write characters to a text file.
	To implement ITxtExpFileWriter, you can use the partial implementation, CTxtExpFileWriter,
	which is also part of this sample.
	
	@ingroup textexportfilter
	
*/
class ITxtExpFileWriter: public IPMUnknown
{
public:
	/** Options for the various types of Japanese/Roman text file encodings.
	*/
	enum Encoding
	{
		/**-1 */ kTxtExpEncodingInvalid = -1,
        /** 0 */ kTxtExpEncodingASCII,
		/** 1 */ kTxtExpEncodingUNICODE,
		/** 2 */ kTxtExpEncodingShiftJIS,
		/** 3 */ kTxtExpEncodingJIS, 
		/** 4 (not supported) */ kTxtExpEncodingEUC
	};

	enum { kDefaultIID = IID_ITXTEXPFILEWRITER };

	/** Writes the textchar data to the given file stream.
		@param stream Stream to write to.
		@param tcbuf Pointer to a buffer of textchars to write. 
		@param bufSize Number of textchars to write.
		@return Number of textchars (not bytes) written to stream.
	*/
	virtual int32 WriteTextCharBuffer(IPMStream* stream, const textchar* tcbuf, const int32 bufSize) = 0;
};

#endif // ifndef __ITxtExpFileWriter__H__
// End, ITxtExpFileWriter.h




