//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textimportfilter/TxtImpUtils.cpp $
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
#include "OMTypes.h"
#include "K2Assert.h"
#include "CreateObject.h"

// Project includes
#include "TxtImpUtils.h"
#include "TxtImpID.h"


/* QueryTxtImpFileReader (static)
*/
ITxtImpFileReader* TxtImpUtils::QueryTxtImpFileReader(ITxtImpFileReader::Encoding encoding)
{
	ITxtImpFileReader* reader = nil;
	PMIID iid(IID_ITXTIMPFILEREADER);

	switch (encoding) 
	{
		case ITxtImpFileReader::kTxtImpEncodingASCII:
			reader = static_cast<ITxtImpFileReader*>(::CreateObject(kASCIIFileReaderBoss, iid));
			break;
#if IS_BIG_ENDIAN_ARCH
		case ITxtImpFileReader::kTxtImpEncodingUTF16BE:
#elif IS_LITTLE_ENDIAN_ARCH
		case ITxtImpFileReader::kTxtImpEncodingUTF16LE:
#endif
			reader = static_cast<ITxtImpFileReader*>(::CreateObject(kUNICODEFileReaderBoss, iid));
			break;

		case ITxtImpFileReader::kTxtImpEncodingShiftJIS:
			reader = static_cast<ITxtImpFileReader*>(::CreateObject(kShiftJISFileReaderBoss, iid));
			break;

        case ITxtImpFileReader::kTxtImpEncodingJIS:
			reader = static_cast<ITxtImpFileReader*>(::CreateObject(kJISFileReaderBoss, iid));
			break;

		default:
			ASSERT_FAIL(FORMAT_ARGS("TxtImpUtils::QueryTxtImpFileReader: encoding type (%d) not supported.", encoding));
			break;
	}
	
	return reader;
}


/* DetectJapaneseEncodingType
	
	NOTE: This algorithm was adapted from a code sample printed in the 
	      book "CJKV Information Processing" (by Ken Lunde, 1999 edition) 
		  and is included in this sample with permission from the author.
		  Refer to page 428, int DetectCodeType(FILE *in).
*/
ITxtImpFileReader::Encoding TxtImpUtils::DetectJapaneseEncodingType(uchar* cbuf, int32 bufSize)
{
	uchar* p = cbuf;
	// by default, a file is deemed as ASCII
	ITxtImpFileReader::Encoding encoding = ITxtImpFileReader::kTxtImpEncodingASCII;

	do 
	{
		if (*p != 0x0)  // read one byte until end of buffer
		{
			if (*p == 0x1B) // ESC, maybe JIS
			{
				p++;
				if (*p == '$') // Maybe two-byte encoding
				{
					p++;
					if ((*p == 'B') || 
						(*p == '@'))
					{
						encoding = ITxtImpFileReader::kTxtImpEncodingJIS; 
					}
				}
			}
			else if ((*p >= 0x81 && *p <= 0x8D) || 
					 (*p >= 0x8F && *p <= 0x9F)) 
			{
				encoding = ITxtImpFileReader::kTxtImpEncodingShiftJIS;
			}
			else if (*p == 0x8E) // could be EUC half-width katakana
			{
				p++;
				if ((*p >= 0x40 && *p <= 0x7E) || 
					(*p >= 0x80 && *p <= 0xA0) || 
					(*p >= 0xE0 && *p <= 0xFC)) 
				{
					encoding = ITxtImpFileReader::kTxtImpEncodingShiftJIS;
				}
				else if (*p >= 0xA1 && *p <= 0xDF) 
				{
					// could be EUC or ShiftJIS - stay in the loop
					encoding = ITxtImpFileReader::kTxtImpEncodingInvalid; 
				}
			}
			else if (*p >= 0xA1 && *p <= 0xDF) 
			{
				p++;
				if (*p >= 0xF0 && *p <= 0xFE) 
				{
					encoding = ITxtImpFileReader::kTxtImpEncodingEUCJP;
				}
				else if (*p >= 0xA1 && *p <= 0xDF) 
				{
					encoding = ITxtImpFileReader::kTxtImpEncodingInvalid; // could be EUC or ShiftJIS
				}
				else if (*p >= 0xE0 && *p <= 0xEF) 
				{
					encoding = ITxtImpFileReader::kTxtImpEncodingInvalid; // could be EUC or ShiftJIS
					while ((*p >= 0x40) && 
						   (!*p) && 
						   (encoding == ITxtImpFileReader::kTxtImpEncodingInvalid))
					{
						if (*p>= 0x81) 
						{
							if ((*p <= 0x8D) || 
								(*p >= 0x8F && *p <= 0x9F)) 
							{
								encoding = ITxtImpFileReader::kTxtImpEncodingShiftJIS;
							}
							else if ((*p == 0xFD) || 
									 (*p == 0xFE))
							{
								encoding = ITxtImpFileReader::kTxtImpEncodingEUCJP;
							}
						}
						p++;
					}
				}
				else if (*p <= 0x9F) 
				{
					encoding = ITxtImpFileReader::kTxtImpEncodingShiftJIS;
				}
			}
			else if (*p >= 0xF0 && *p <= 0xFE) 
			{
				encoding = ITxtImpFileReader::kTxtImpEncodingEUCJP;
			}
			else if (*p >= 0xE0 && *p <= 0xEF) 
			{
				p++;
				if ((*p >= 0x40 && *p <= 0x7E) || 
					(*p >= 0x80 && *p <= 0xA0)) 
				{
					encoding = ITxtImpFileReader::kTxtImpEncodingShiftJIS;
				}
				else if ((*p == 0xFD) || 
						 (*p == 0xFE))
				{
					encoding = ITxtImpFileReader::kTxtImpEncodingEUCJP;
				}
				else if (*p >= 0xA1 && *p <= 0xFC) 
				{
						encoding = ITxtImpFileReader::kTxtImpEncodingInvalid; // could be EUC or ShiftJIS 
				}
			}

		} // if (*p != '\0')  
		
		// advance pointer
        ++p;

	} while (((encoding == ITxtImpFileReader::kTxtImpEncodingASCII) || 
			  (encoding == ITxtImpFileReader::kTxtImpEncodingInvalid)) &&  // Invalid == ambiguous
			 (*p != 0x0) && 
			 ((p - cbuf) < bufSize));


	// perform extra Unicode check
	ITxtImpFileReader::Encoding encodingBeforeUnicodeCheck = encoding; 

	if (encoding == ITxtImpFileReader::kTxtImpEncodingASCII ||
		encoding == ITxtImpFileReader::kTxtImpEncodingEUCJP)
	{
		// Since UNICODE is backwards compatible with ASCII, 
		// the detector might have determined the stream was ASCII.
		// Also, there is an overlap between EUC-JP and UNICODE, 
		// but since we don't supply any example files with EUC-JP, 
		// and don't support it, we are going to exclude this case. 
		// Therefore, we need to determine if the stream was really ASCII, or
		// if it was UNICODE.  
		// This is done by looking for 'some' bytes that are unique in UNICODE.
		// There is one caveat in this algorithm... If the stream contained only 
		// Japanese UNICODE characters (no Roman characters), the stream might have been 
		// mistaken as ShiftJIS.  But that's ok, all we need to know here
		// is whether we could import this stream.
		
		int32 i = 0;
		while (i < bufSize)
		{
			uchar ch = cbuf[i];
			// look for some chars only in UNICODE
			if ((ch == 0x0) || (ch >= 0xFD && ch <= 0xFE))
			{
				// distinguish between Unicode BE and LE (look for ASCII zero-padding bytes)

				if ((ch == 00) && (i % 2 == 0))
				{
#if IS_LITTLE_ENDIAN_ARCH
					TRACEFLOW(kTxtImpPluginName, "TxtImpUtils::DetectJapaneseEncodingType: Detected UTF-16 Big Endian text encoding - this ImportProvider does not support this encoding on this platform\n");
					encoding = ITxtImpFileReader::kTxtImpEncodingInvalid;
#else
					encoding = ITxtImpFileReader::kTxtImpEncodingUTF16BE;
#endif
					break; // out of while loop
				}
				else if ((ch == 00) && (i % 2 == 1))
				{
#if IS_BIG_ENDIAN_ARCH
					TRACEFLOW(kTxtImpPluginName, "TxtImpUtils::DetectJapaneseEncodingType: Detected UTF-16 Little Endian text encoding - this ImportProvider does not support this encoding on this platform\n");
					encoding = ITxtImpFileReader::kTxtImpEncodingInvalid;
#else
					encoding = ITxtImpFileReader::kTxtImpEncodingUTF16LE;
#endif
					break; // out of while loop
				}
			}
			++i;
		}
	}
	/* At this point, if (encoding == encodingBeforeUnicodeCheck),
		that means the Unicode check didn't find any zero-padded characters, 
		so let's just go with the current encoding.
		
		NOTE: This algorithm isn't failsafe - if a Japanese Unicode file doesn't have
		any of the ASCII-compatible characters in it, this algorithm won't detect
		either Unicode encoding.
	*/

	return encoding;
}

// End, TxtImpUtils.cpp.


