//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/JISFileWriter.cpp $
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
#include "CPMUnknown.h"
#include "ITxtExpFileWriter.h"
#include "CTUnicodeTranslator.h"
#include "Utils.h"

// Interface includes
#include "IEncodingUtils.h"

// Project includes
#include "TxtExpID.h"
#include "TxtExpUtils.h"



/** ESC sequence for ASCII
	@ingroup textexportfilter

*/
const uchar* kEscASCII =     (uchar*)"\x1B(B\0";
/** ESC sequence for JIS Roman
	@ingroup textexportfilter
*/
const uchar* kEscJIS_Roman = (uchar*)"\x1B(J\0";	// 3 bytes
/** ESC sequence for Older JIS standard (JIS C 6226-1978)
	@ingroup textexportfilter

*/
const uchar* kEscJIS_Old =   (uchar*)"\x1B$@\0";	// 3 bytes
/** ESC sequence for Newer JIS standard (JIS X 0208-1983)
	@ingroup textexportfilter
*/
const uchar* kEscJIS_New =   (uchar*)"\x1B$B\0";	// 3 bytes


/** JISFileWriter
	Implements ITxtExpFileWriter for JIS encoded files.
	For details on the supported JIS encodings, refer to JISFileWriter::JIS_States.

	@ingroup textexportfilter

*/
class JISFileWriter: public CPMUnknown<ITxtExpFileWriter>
{
public:
	/** Constructor
	*/
	JISFileWriter(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~JISFileWriter(void);


	/** Writes the textchar data to the given file stream.
		@param stream Stream to write to.
		@param tcbuf Pointer to a buffer of textchars to write.
		@param bufSize Number of textchars to write.
		@return Number of textchars (not bytes) written to stream.
	*/
	virtual int32 WriteTextCharBuffer(IPMStream* stream, const textchar* tcbuf, const int32 bufSize);

	/** States for the JIS state machine.  In the TextExportFilter sample,
	we are only using this to keep track of the current state of the
	JISFileWriter.

	For more detailed use of this enum, refer to another sample where it
	is used: TextImportFilter\Source\JISFileReader.cpp.

	For this sample plug-in, we are using the ISO-2022-JP standard.

	For more details on the ISO-2022-JP standard and related JIS encodings,
	refer to the following IETF RFCs:
	<LI>
		RFC 1468: <I>Japanese Character Encoding for Internet Messages</I>,
		which covers ISO-2022-JP, which includes ASCII, JIS-Roman,
		JIS C 6226-1978 and JIS X 0208-1983.
		(http://www.ietf.org/rfc/rfc1468.txt)
	</LI>
	<LI>
		RFC 1554: <I>ISO-2022-JP2: Multilingual Extension of
		ISO-2022-JP</I>, which extends ISO-2022-JP by adding GB2312-80 and
		KS X 1001:1992, and by includubg ISO-2022-JP1, as documented in
		RFC 2237.
		(http://www.ietf.org/rfc/rfc1554.txt)
	</LI>
	<LI>
		RFC 2237: <I>Japanese Character Encoding for Internet Messages</I>,
		which covers ISO-2022-JP1, an extension to ISO-2022-JP which
		adds JIS X 0212-1990.
		(http://www.ietf.org/rfc/rfc2237.txt)
	</LI>

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
	uchar* fBuf; // hold JIS chars before writing to stream
	int32  fPos; // position holder in JIS char buffer
	int32  fSize; // size of fBuf, so we don't overstep our bounds
	JISFileWriter::JIS_States fState; // start with ASCII, but keep static
	IPMStream* fCurrentStream;	// hold onto stream to use.

	/** Allocates private buffer space to hold JIS characters.
		Also initializes some of the buffer related private member variables.
		@param bufSize Number of textchars to hold. The actual size of the buffer is calculated within.
		@return ErrorCode Returns kSuccess if successful.
	*/
	ErrorCode CreateJISBuffer(const int32 bufSize);

	/** Destroys private buffer space and resets related private member variables.
		@return ErrorCode Returns kSuccess if successful.
	*/
	ErrorCode DestroyJISBuffer(void);

	/** Inserts the appropriate JIS ESC sequence, only if 'state' is different than
		the current state.  If different, it also switches the current state.
		@param state The new state in the state machine to switch to.
		@return ErrorCode Returns kSuccess if successful.
	*/
	ErrorCode InsertEscSequenceIfNeeded(const JISFileWriter::JIS_States state);

	/** Inserts a uchar into the private JIS buffer.  Watches out if we are
	    overstepping array bounds.
		@param uc uchar to insert into private JIS buffer.
		@return ErrorCode Returns kSuccess if successful.
	*/
	ErrorCode InsertCharInBuffer(const uchar uc);

	/** Inserts an array of uchars into the private JIS buffer, by calling
		InsertCharInBuffer the necessary number of times, as indicated by
		'arraySize'.
		@param pc Pointer to uchar array to insert.
		@param arraySize Number of uchars in 'pc'.
		@return ErrorCode Returns kSuccess if successful.
	*/
	ErrorCode InsertCharArrayInBuffer(const uchar* pc, const int32 arraySize);

	/** Inserts a textchar into the private JIS buffer, by calling
		InsertCharInBuffer for the upper and lower byte. The ordering is
		ALWAYS big endian.
		@param tc textchar to insert.
		@return ErrorCode Returns kSuccess if successful.
	*/
	ErrorCode InsertJISCharInBuffer(const textchar tc);

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(JISFileWriter, kJISFileWriterImpl);


/* Constructor
*/
JISFileWriter::JISFileWriter(IPMUnknown* boss)
 : 	CPMUnknown<ITxtExpFileWriter>(boss),
	fBuf(nil),
	fPos(0),
	fState(JISFileWriter::kInASCII),
	fCurrentStream(nil),
	fSize(0)
{
}

/* Destructor
*/
JISFileWriter::~JISFileWriter(void)
{
	if (fBuf)
	{
		delete []fBuf;
		fBuf = nil;
	}
}


/* WriteTextCharBuffer
	STEPS:
	(0)  Creaate a private JIS buffer. and check textchar classification.
	(1) CATEGORY 1: If textchar is ASCII or TAB, insert the char into JIS buffer.
	     If needed, escape it with kEscASCII and change state to kInASCII.
    (2) CATEGORY 2: If at the end of a line, and if needed, terminate with kEscASCII
	     and change state to kInASCII before inserting CR and/or LF into JIS buffer.
	(3) CATEGORY 3:If we get this far, assume Japanese char, so convert textchar to ShiftJIS,
	     If needed, escape it with kInJIS_New and change state to kInJIS_New.
	(3a) If converted ShiftJIS is a single-byte katakana, convert to
	     dual-byte ShiftJIS katanana first.
	(3b) Convert ShiftJIS char to JIS, and insert into JIS buffer.

*/
int32 JISFileWriter::WriteTextCharBuffer(IPMStream* stream, const textchar* tcbuf, const int32 bufSize)
{
	ErrorCode rc = kFailure;
	int32 written = 0;

	if (fCurrentStream != stream)
	{
		// a new stream is passed in!
		// reset the state machine, and store the new stream.
		fState = kInASCII;
		fCurrentStream = stream;
	}

	do {

		textchar tc = kTextChar_Null;

		// STEP 0: create a private memory buffer to store JIS chars.
		rc = CreateJISBuffer(bufSize);
		if (rc != kSuccess)
		{
			break;
		}

		// iterate thru each UNICODE char and process to JIS standards.
		for (int32 i = 0 ; i < bufSize ; i++)
		{
			// get the current textchar
			tc = tcbuf[i];

			// the next move depends on character classification.

			if (((tc >= kTextChar_Space) && (tc <= 0x7F)) ||
				(tc == kTextChar_Tab))
			{
				// CATEGORY 1: Character class ==> ASCII

				rc = InsertEscSequenceIfNeeded(kInASCII);
				if (rc != kSuccess)
				{
					break;
				}
				rc = InsertCharInBuffer((const uchar)(tc & 0xFF));
				if (rc != kSuccess)
				{
					break;
				}
			}
			else if (tc == kTextChar_CR)
			{
				// CATEGORY 2: Character class ==> ASCII Carriage Return
				// NOTE: #if defined(MACINTOSH), then the routine that calls
				// this method won't insert a CR into the textchar array,
				// so we should only end up here if we are on Windows.
				// Therefore, on the Mac, we need to insert the ASCII ESC
				// sequence when an LF is encountered (see below).
				rc = InsertEscSequenceIfNeeded(kInASCII);
				if (rc != kSuccess)
				{
					break;
				}
				rc = InsertCharInBuffer((const uchar)(tc & 0xFF));
				if (rc != kSuccess)
				{
					break;
				}
			}
			else if (tc == kTextChar_LF)
			{
				// CATEGORY 2: Character class ==> ASCII Linefeed
#if defined(MACINTOSH)
				// NOTE: On the Mac, we didn't get the ASCII ESC sequence.
				rc = InsertEscSequenceIfNeeded(kInASCII);
				if (rc != kSuccess)
				{
					break;
				}
#endif
				rc = InsertCharInBuffer((const uchar)(tc & 0xFF));
				if (rc != kSuccess)
				{
					break;
				}
			}
			else
			{
				// CATEGORY 3: Character class ==> (assume) Japanese character
				rc = InsertEscSequenceIfNeeded(kInJIS_New);
				if (rc != kSuccess)
				{
					break;
				}

				// convert to ShiftJIS first, then further classify.
				Utils<IEncodingUtils>()->Unicode2ShiftJIS(tc);
                // if the lower byte is 0, tc is byte swapped! So we must un-swap.
				if (GETLOBYTE(tc) == 0)
				{
					tc = SWAPWORD(tc);
				}
				textchar jisChar = kTextChar_Null;

				// check if character is Hankaku (single-byte) katakana
				if ((tc >= 0xA1) && (tc <= 0xDF))
				{
					// CATEGORY 3A: Hankaku (single-byte) katakana.
					// There is no direct conversion to JIS for these characters,
					// so convert to dual-byte katakana first.
					textchar nextChar = tcbuf[i+1];
					TxtExpUtils::Modifier modifier = TxtExpUtils::None;

                    if ((nextChar == kTextChar_HalfWidthKatakanaVoicedMark) ||
                        (nextChar == kTextChar_HalfWidthKatakanaSemiVoicedMark))
					{
						// advance pointers, we are eating up the dakuten/handakuten
						i++;
						written++;
						modifier = (nextChar == kTextChar_HalfWidthKatakanaVoicedMark) ?
									TxtExpUtils::Dakuten : TxtExpUtils::Handakuten ;
					}
                    // convert to zenkaku
					jisChar = TxtExpUtils::HankakuToZenkaku(tc, modifier);
                    // if not found, take the converted ShiftJIS directly
                    if (!jisChar)
                    {
                        jisChar = tc;
                    }
				}
                else
                {
                    jisChar = tc;
                }

				// convert to JIS then insert in buffer
				Utils<IEncodingUtils>()->ShiftJIS2JIS(jisChar);
				rc = InsertJISCharInBuffer(jisChar);
				if (rc != kSuccess)
				{
					break;
				}
			}

			// we got this far without any breaks,
			// so increment textchar counter
			written++;
		}

		// the end of the buffer must be in the ASCII state.
		// since we don't know how many times this method will get called
		// from the caller, it would be safe for us to assume that this IS
		// the last write to the stream, and go ahead and add this ASCII
		// ESC sequence.
		rc = InsertEscSequenceIfNeeded(kInASCII);
		if (rc != kSuccess)
		{
			break;
		}

        // write the buffer to stream
		// at this point, 'fBuf' should have 'fPos'-many uchars in it
		int32 ucharsWritten = fCurrentStream->XferByte(fBuf, fPos);

		if (ucharsWritten == 0)
		{
			// reset textchar counter to 0
			written = 0;
			ASSERT_FAIL("JISFileWriter::WriteTextCharBuffer : No uchars were written to stream.  Something went wrong in IPMStream->XferByte().");
			// don't break, keep going.
		}

	} while (kFalse);

	// we are done with the JIS buffer, so clean it up.
	DestroyJISBuffer();

	return written;
}


/* CreateJISBuffer

	Regarding the uchar buffer size:
	We need to make the buffer large enough for the worst cases.

	* Case: one dual-byte (2 bytes) char per line (terminated with CR and/or LF).
	You would have a line that looks like this:
	[ESC]$B[2bytes][ESC](J[CR][LF]
	The extra ESC sequence is added to ensure that the CR/LF is handled
	properly by any JIS-aware programs.
	(Windows) A 4-byte character sequence requires 10-bytes in a JIS file. (2.5x)
	(Mac) A 3-byte character sequence requires 9-bytes in a JIS file. (3x)

   	* Case: where dual-byte (2 bytes) and ASCII (1 byte) chars alternate.
	You would have a sequence that looks like this:
	...[ESC]$B[2bytes][ESC](J[1byte]...
	A 3-byte character sequence requires 9-bytes in a JIS file. (3x)
	If the last character in the sequence is a dual-byte char, then
	we need an extra escape code to switch back to ASCII (add 3 bytes).

	* Case: combining the two above:
	[ESC]$B[2bytes][ESC](J[1byte][CR][LF]
	A 5-byte character sequence requires 11-bytes in a JIS file. (2.2x)

	The worst case scenario is a 3x growth in the buffer size (in bytes).

	Space for an extra terminating ASCII ESC sequence and the null
	terminator is added for extra padding.
*/
const int32 kJISGrowthFactor = 3;
ErrorCode JISFileWriter::CreateJISBuffer(const int32 bufSize)
{
	// To find out more about how we arrived at this formula for ucharbufSize,
	// see comment before the start of this method.
	int32 ucharbufSize = bufSize * kJISGrowthFactor + static_cast<int32>(strlen((char*)kEscASCII)) + 1;
	ErrorCode rc = kFailure;

	DestroyJISBuffer();

	if (bufSize <= 0)
	{
		ASSERT_FAIL("JISFileWriter::CreateJISBuffer : Can't create buffer of size <=0");
	}
	else
	{
		// allocate a buffer "large enough" for JIS chars.
		fBuf = new uchar[ucharbufSize];
		if (!fBuf)
		{
			ASSERT_FAIL("JISFileWriter::CreateJISBuffer : Couldn't create buffer");
		}
		else
		{
			// set buffer related member variables
			fSize = ucharbufSize;
			// NOTE: fPos was already cleared in DestroyJISBuffer
			rc = kSuccess;
		}
	}
	return rc;
}

/* DestroyJISBuffer
*/
ErrorCode JISFileWriter::DestroyJISBuffer(void)
{
	if (fBuf)
	{
		delete []fBuf;
		// reset buffer related member variables
		fPos = 0;
		fSize = 0;
		fBuf = nil;
	}
	return kSuccess;
}

ErrorCode JISFileWriter::InsertEscSequenceIfNeeded(const JISFileWriter::JIS_States state)
{
	// assume sucess
	ErrorCode rc = kSuccess;

	if (fState != state)
	{
		// change current state
		fState = state;

		// insert the appropriate ESC sequence based on state
		switch (state)
		{
		case kInASCII:
			rc = InsertCharArrayInBuffer(kEscASCII, static_cast<int32>(strlen((char*)kEscASCII)));
			break;
		case kInJIS_Roman:
			rc = InsertCharArrayInBuffer(kEscJIS_Roman, static_cast<int32>(strlen((char*)kEscJIS_Roman)));
			break;
		case kInJIS_Old:
			rc = InsertCharArrayInBuffer(kEscJIS_Old, static_cast<int32>(strlen((char*)kEscJIS_Old)));
			break;
		case kInJIS_New:
			rc = InsertCharArrayInBuffer(kEscJIS_New, static_cast<int32>(strlen((char*)kEscJIS_New)));
			break;
		default:
			ASSERT_FAIL("JISFileWriter::InsertEscSequenceIfNeeded : invalid state was passed in - skipping the insertion of ESC sequence");
			break;
		}
	}
	return rc;
}


/* InsertCharInBuffer
*/
ErrorCode JISFileWriter::InsertCharInBuffer(const uchar uc)
{
	ErrorCode rc = kFailure;
	if (!fBuf)
	{
		ASSERT_FAIL("JISFileWriter::InsertCharInBuffer : fBuf is nil!  Can't insert uchar.");
	}
	else if (fPos >= fSize)
	{
		ASSERT_FAIL("JISFileWriter::InsertCharInBuffer : fPos >= fSize!  We are overstepping bounds of fBuf, skipping insert.");
	}
	else
	{
		// put the character in the buffer
		fBuf[fPos++] = uc;
		rc = kSuccess;
	}
	return rc;
}

/* InsertCharArrayInBuffer
*/
ErrorCode JISFileWriter::InsertCharArrayInBuffer(const uchar* pc, const int32 arraySize)
{
	ErrorCode rc = kFailure;
	int32 i = 0;
	if (pc)
	{
		do
		{
			rc = InsertCharInBuffer(pc[i++]);
		} while ((rc == kSuccess) && (i < arraySize));
	}
	else
	{
		ASSERT_FAIL("JISFileWriter::InsertCharArrayInBuffer : uchar* pc is nil! Skipping insert.");
	}
	return rc;
}

/* InsertJISCharInBuffer
*/
ErrorCode JISFileWriter::InsertJISCharInBuffer(const textchar tc)
{
	ErrorCode rc = kFailure;
	// insert upperbyte
	rc = InsertCharInBuffer((const uchar)((tc >> 8) & 0xFF));
	if (rc == kSuccess)
	{
		// insert lower byte
		rc = InsertCharInBuffer((const uchar)(tc & 0xFF));
	}
	return rc;
}


// End, JISFileWriter.cpp




