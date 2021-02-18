//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textimportfilter/ASCIIFileReader.cpp $
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

// Project includes
#include "TxtImpID.h"

/*
Each file reader will be in a boss 
*/
/** ASCIIFileReader
	Provides a full implementation for an ASCII file reader, by 
	supplying the GetNextTextChar method.
	
	@ingroup textimportfilter	
	
*/
class ASCIIFileReader : public CTxtImpFileReader
{
public:
	/** Constructor
	*/
	ASCIIFileReader(IPMUnknown* boss);

	/** Gets the next UTF16TextChar.
	*/
	virtual UTF16TextChar GetNextTextChar(void);
    
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(ASCIIFileReader, kASCIIFileReaderImpl);

/* ASCIIFileReader Constructor
*/
ASCIIFileReader::ASCIIFileReader(IPMUnknown* boss)
 : CTxtImpFileReader(boss) {}

/* GetNextTextChar
*/
UTF16TextChar ASCIIFileReader::GetNextTextChar(void)
{
    // assume we are returning NULL (tells caller there is no more to do)
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
				// CTUnicodeTranslator::CharToTextChar translates an entire buffer into Unicode characters.
				int32 theLength = ::CTUnicodeTranslator::Instance()->CharToTextChar
								(reinterpret_cast<const char *>(fCBuf), readCount, fTCBuf, readCount, -1);
				
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

// End, ASCIIFileReader.cpp.


