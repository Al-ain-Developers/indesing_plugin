//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textimportfilter/JISFileReader.cpp $
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
#include "CTxtImpFileReader.h"
#include "CTUnicodeTranslator.h"
#include "Utils.h"
#include "IEncodingUtils.h"

// Project includes
#include "TxtImpID.h"

/*
Each file reader will be in a boss 
*/
/** JISFileReader
	Provides a full implementation for an JIS file reader, by 
	supplying the GetNextTextChar method.
	
	@ingroup textimportfilter	
	
*/
class JISFileReader : public CTxtImpFileReader
{
public:
	/** Constructor
	*/
	JISFileReader(IPMUnknown* boss);

	/** Gets the next UTF16TextChar.
	*/
	virtual UTF16TextChar GetNextTextChar(void);

	/** States for the JIS state machine.  In the TextImportFilter sample, 
	we are only using this to keep track of the current state of the 
	JISFileReader. 
	
	For this sample plug-in, we are using the ISO-2022-JP standard. 
	
	For more details on the ISO-2022-JP standard and related JIS encodings, 
	refer to the following IETF RFCs:
	\li RFC 1468: <I>Japanese Character Encoding for Internet Messages</I>, 
		which covers ISO-2022-JP, which includes ASCII, JIS-Roman, 
		JIS C 6226-1978 and JIS X 0208-1983. (http://www.ietf.org/rfc/rfc1468.txt)
	
	\li RFC 1554: <I>ISO-2022-JP2: Multilingual Extension of 
		ISO-2022-JP</I>, which extends ISO-2022-JP by adding GB2312-80 and 
		KS X 1001:1992, and by includubg ISO-2022-JP1, as documented in 
		RFC 2237. (http://www.ietf.org/rfc/rfc1554.txt)
	 
	\li RFC 2237: <I>Japanese Character Encoding for Internet Messages</I>, 
		which covers ISO-2022-JP1, an extension to ISO-2022-JP which 
		adds JIS X 0212-1990. (http://www.ietf.org/rfc/rfc2237.txt)
	*/
	enum JIS_States
	{
		kInASCII,
		kInEscSeqByte1, 
		kInEscSeqByte2D, 
		kInEscSeqByte2P, 
		kInJIS_Old,			// Older JIS standard (JIS C 6226-1978)
		kInJIS_New,			// Newer JIS standard (JIS X 0208-1983)
		kInJIS_Roman		// JIS Roman (veri similar to ASCII)
	};
	
	//	For reference: ISO-2022-JP JIS escape codes 
	//	[ESC](B[1byte]  (kInJIS_ASCII) (use this by default, instead of kInJIS_Roman)
	//	[ESC](J[1byte]  (kInJIS_Roman)
	//	[ESC]$B[2bytes] (kInJIS_New)
	//	[ESC]$@[2bytes] (kInJIS_Old)

private:
    /** Converts a JIS buffer to a UTF16TextChar buffer.
		This only works on JIS, and does not support other ISO-2022 encodings (e.g. KR, CN)
		@param cbuf The uchar array with data in it.
		@param charCount Number of uchars in cbuf.
		@param tcbuf The UTF16TextChar array to copy into. Must be allocated prior to calling.
		@param UTF16TextCharCount size of the tcbuf.
		@return Number of UTF16TextChars actually copied into tcbuf
	*/
	int32 JISToTextChar(const uchar* cbuf, int32 charCount, UTF16TextChar* tcbuf, int32 UTF16TextCharCount);
		// start with ASCII, but keep static
	JISFileReader::JIS_States fState ; 
		// in case cbuf runs out in the middle of a dual byte
	uchar fprevReadFirstByte ; 

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(JISFileReader, kJISFileReaderImpl);

/* JISFileReader Constructor
*/
JISFileReader::JISFileReader(IPMUnknown* boss)
 : CTxtImpFileReader(boss),
	fState (JISFileReader::kInASCII), 
	fprevReadFirstByte (0) 
{}

/* GetNextTextChar
*/
UTF16TextChar JISFileReader::GetNextTextChar(void)
{
    // assume we are returning  NULL (tells caller there is no more to do)
    UTF16TextChar theChar = kTextChar_Null;
	do 
	{
		// this might be the first time this is called.  
		// If so, allocate memory for uchar and UTF16TextChar buffers.
		if (!fCBuf) 
		{
			fCBuf = new uchar[kTxtImpBufferSize+1];
			if (!fCBuf) 
			{
				// still not allocated - exit.
				ASSERT_MSG(fCBuf, "fCBuf is nil!");
				break;
			}
		}
		if (!fTCBuf) 
		{
			fTCBuf = new UTF16TextChar[kTxtImpBufferSize+1];
			if (!fTCBuf) 
			{
				// still not allocated - exit.
				ASSERT_MSG(fTCBuf, "fTCBuf is nil!");
				break;
			}
		}

		if (fCurrMarker == fEndOfReadMarker)
		{
			// reached the end of the internal read buffer, 
			// so go read more text from the stream
			int32 readCount = fStream->XferByte(fCBuf, kTxtImpBufferSize);
	
			// check if anything was read
			if (readCount > 0)
			{
				// Do our own JIS conversion into a fTCBuf
				int32 theLength = this->JISToTextChar((const uchar*)fCBuf, readCount, 
													  fTCBuf, readCount);
	
				if (theLength > 0) 
				{
					// properly converted to UNICODE, get the next char
					fEndOfReadMarker = theLength;
					fCurrMarker = 0;
					theChar  = fTCBuf[fCurrMarker++];
				}
				else 
				{ 
					// no conversions were done (something went wrong?) so return NULL char 
					break; // theChar = kTextChar_Null at this point
				}
			}
			else 
			{ 
				// no more text to read! so return NULL char 
				break; // theChar = kTextChar_Null at this point
			}
		}
		else
		{
			// the current mark is behind the EndOfRead mark, 
			// so just pull a char from the buffer
			theChar  = fTCBuf[fCurrMarker++];  
		}

	} while (kFalse);

	return theChar;
}


	
/* JISToTextChar
*/
int32 JISFileReader::JISToTextChar(const uchar* cbuf, int32 charCount, UTF16TextChar* tcbuf, int32 UTF16TextCharCount)
{
	int32 cbufIndex = 0, 
		  sjbufIndex = 0,
		  theLength = 0; // assume that we couldn't convert any 
    uchar ch = 0;
    uchar* shiftJISbuf = nil;

	do 
	{
		if ((!cbuf) || (charCount <= 0)) 
		{
			ASSERT_FAIL("JISFileReader::JISToTextChar : cbuf (uchar) is nil or the caller says the buffer size <= 0");
			break;
		}
		if ((!tcbuf) || (UTF16TextCharCount <= 0))
		{
			ASSERT_FAIL("JISFileReader::JISToTextChar : tcbuf (UTF16TextChar) is nil or the caller says the buffer size <= 0");
			break;
		}

		// allocate space to hold shifJIS data temporarily.
		shiftJISbuf = new uchar[charCount+1];
		if (!shiftJISbuf)
		{
			ASSERT_FAIL("JISFileReader::JISToTextChar : not enough memory to allocate temporary ShiftJIS buffer!");
			break;
		}
			
	
		/* State machine transition chart:
		
		   current state -- data byte --> next state
		   -------------    ---------     ----------
		   kInASCII         0x1B(ESC)  	  kInEscSeqByte1
							other         (take the databyte)
		   kInJIS_Old       0x1B(ESC)  	  kInEscSeqByte1
							other         (take the next two bytes)
		   kInJIS_New       0x1B(ESC)  	  kInEscSeqByte1
							other         (take the next two bytes)
		   kInJIS_Roman     0x1B(ESC)  	  kInEscSeqByte1
							other         (take the databyte)
		   kInEscSeqByte1   '$'           kInEscSeqByte2D
							'('           kInEscSeqByte2P
							other         kInASCII (???Invalid???)
		   kInEscSeqByte2D  'B'           kInJIS_New
							'@'           kInJIS_Old
							other         kInASCII (???Invalid???)
		   kInEscSeqByte2P  'J'           kInJIS_Roman
							'B'           kInASCII
							other         kInASCII (???Invalid???)
							
		   
		   Temporary encoding transformation prior to UNICODE transformation
		   
		   current state  #bytes to copy  conversion
		   -------------  --------------  ----------
		   kInASCII       1				  Don't do anything
		   kInJIS_Old     2               EncodingUtils::JIS2ShiftJIS
		   kInJIS_New     2               EncodingUtils::JIS2ShiftJIS
		   kInJIS_Roman   1               Don't do anything
		*/
	
		// process all characters until we reach the end.
		do
		{
			// get the next char to watch
			ch = cbuf[cbufIndex++];
	
			// the JIS state machine...
			switch (fState)
			{
			case kInASCII:
			case kInJIS_Roman:
				switch (ch) 
				{
				case 0x1B:
					fState = kInEscSeqByte1;
					break;
				default:
					// copy one databyte
					shiftJISbuf[sjbufIndex++] = ch;
					break;
				}
				break;
	
			case kInJIS_Old:
			case kInJIS_New:
			
				switch (ch)
				{
				case 0x1B:
					fState = kInEscSeqByte1;
					break;
				default:
					// copy two databytes
	
					uchar hiByte = 0, 
						  loByte = 0;
					UTF16TextChar jChar = 0;
					
					if (fprevReadFirstByte)
					{
						// pick up from our last processing...
	 
						// copy in the first byte from the previous read
						hiByte = fprevReadFirstByte;
						// reset the previous first byte
						fprevReadFirstByte = 0;
						// copy current byte
						loByte = ch;
					}
					else
					{
						// proceed as normal...
	
						// get the first databyte    
						hiByte = ch;
						// try to move on to 2nd byte.
						// but first check location in cbuf
						if (cbufIndex < charCount)
						{
							// still within cbuf, so we could safely get the next byte
							loByte = cbuf[cbufIndex++];
						}
						else
						{
							// at the end of the buffer, so set a static flag
							// so we could defer until the next read. 
							fprevReadFirstByte = hiByte;
						}
					}
	
					if (fprevReadFirstByte == 0) 
					{
						// we have a full character, so we can 
						// convert JIS to ShiftJIS and store in shiftJISbuf
						jChar = ((UTF16TextChar)hiByte << 8) + loByte;
						Utils<IEncodingUtils>()->JIS2ShiftJIS(jChar);
						shiftJISbuf[sjbufIndex++] = (uchar)((jChar & 0xFF00) >> 8);
						shiftJISbuf[sjbufIndex++] = (uchar)(jChar & 0x00FF);
					}
	
					break;
				}
				break;
	
			case kInEscSeqByte1:
				switch (ch) 
				{
				case '$':
					fState = kInEscSeqByte2D;
					break;
				case '(':
					fState = kInEscSeqByte2P;
					break;
				default:
					// this is either another ISO-2022 encoding or invalid JIS
					// so just revert to kInASCII and take the byte
					fState = kInASCII;
					shiftJISbuf[sjbufIndex++] = ch;
					break;
				}
				break;
	
			case kInEscSeqByte2D:
				switch (ch) 
				{
				case 'B':
					fState = kInJIS_Old;
					break;
				case '@':
					fState = kInJIS_New;
					break;
				default:
					// this is either another ISO-2022 encoding or invalid JIS
					// so just revert to kInASCII and take the byte
					fState = kInASCII;
					shiftJISbuf[sjbufIndex++] = ch;
					break;
				}
				break;
	
			case kInEscSeqByte2P:
				switch (ch) 
				{
				case 'J':
					fState = kInJIS_Roman;
					break;
				case 'B':
					fState = kInASCII;
					break;
				default:
					// this is either another ISO-2022 encoding or invalid JIS
					// so just revert to kInASCII and take the byte
					fState = kInASCII;
					shiftJISbuf[sjbufIndex++] = ch;
					break;
				}
				break;
			} // switch (fState)...

		} while ((cbufIndex < charCount) && (ch != 0));
	
		// This is set to 'kCTJapaneseScript', as defined in a private header file.
		// This is for the temporary ShiftJIS conversion.
		uint8 script = 1; 
		
		// convert shitJIS buf to UTF16TextChar buffer (UNICODE)
		// 'sjbufIndex' has the buffer size
		theLength = ::CTUnicodeTranslator::Instance()->CharToTextChar
					(reinterpret_cast<const char *>(shiftJISbuf), sjbufIndex, 
					 tcbuf, UTF16TextCharCount, script);
					 
	
	} while (kFalse);
	
	// cleanup
	if (shiftJISbuf != nil)
	{
		delete [] shiftJISbuf;
	}

	return theLength;
}


// End, JISFileReader.cpp.


