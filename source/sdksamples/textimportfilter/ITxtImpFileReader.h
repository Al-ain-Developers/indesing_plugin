//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textimportfilter/ITxtImpFileReader.h $
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

#ifndef __ITxtImpFileReader__H__
#define __ITxtImpFileReader__H__

// includes
#include "TxtImpID.h"


/** Size of internal buffer for the file reader implementations.
	For this sample, this is set at 4,096, since many DMA page buffers
	on PCs and Macintoshes are allocated at 4kByte (=4,096) chunks.
	The actual memory space occupied depends on the data type, which could be
	uchar (1 byte each) or UTF16TextChar (2 bytes each).
*/
const int32 kTxtImpBufferSize = 4096;


/** From SDK sample; interface provides a means to read characters (as UNICODE) out of a text file.
	To implement ITxtImpFileReader, you can use the partial implementation, CTxtImpFileReader,
	which is also part of this sample.
	
	
*/
class ITxtImpFileReader: public IPMUnknown
{
public:
	
	/** Options for the various types of Japanese/Roman text file encodings.
	*/
	enum Encoding 
	{
		/** Invalid encoding.  Value = -1 */ 
		kTxtImpEncodingInvalid = -1,
        /** ASCII encoding.  Value = 0 */ 
		kTxtImpEncodingASCII,      
		/** RESERVED - do not use */ 
		kTxtImpEncodingRESERVED,	
		/** ShiftJIS encoding.  Value = 2 */ 
		kTxtImpEncodingShiftJIS,	
		/** JIS encoding.  Value = 3 */ 
		kTxtImpEncodingJIS, 		
		/** EUC encoding. (not supported) Value = 4 */ 
		kTxtImpEncodingEUCJP,
		/** Unicode 16-bit Big Endian (Default for PowerPC Macintosh). Value = 5 */ 
		kTxtImpEncodingUTF16BE,
		/** Unicode 16-bit Little Endian (Default for Intel). Value = 5 */ 
		kTxtImpEncodingUTF16LE
	};
	

	enum { kDefaultIID = IID_ITXTIMPFILEREADER };

	/** Sets the stream to read.
	*/
	virtual void SetStream(IPMStream* stream) = 0;

	/** Returns the stream (file) size in bytes.
	*/	
	virtual int32 GetFileSizeInBytes(void) = 0;

	/** Returns the next UNICODE char, or kTextChar_Null if EOF.
	*/
	virtual UTF16TextChar GetNextTextChar(void) = 0;
};

#endif // ifndef __ITxtImpFileReader__H__

// End, ITxtImpFileReader.h




