//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/TxtExpSuiteTextCSB.cpp $
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

// Interface headers
#include "ITextTarget.h"
#include "ITextModel.h"
#include "ITextFocus.h"
#include "IComposeScanner.h"
#include "ProgressBar.h"
#include "WideString.h"

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "TxtExpID.h"
#include "ITxtExpSuite.h"
#include "TxtExpUtils.h"
// General includes
#ifdef WIN32
#include <minmax.h>
#else
#define min(a,b) ((a<b)?a:b)
#endif

/** 
	ITxtExpSuite implementation for text concrete selection boss (CSB)
	that supports the export of text when a text selection is active.

	This implementation looks at the text selection and figures out the text
	to be exported. It then stream our the text to a file
	
	@ingroup textexportfilter
	
	@see ITxtExpSuite
*/
class TxtExpSuiteTextCSB : public CPMUnknown<ITxtExpSuite>
{
public:
	/** Constructor
	*/
	TxtExpSuiteTextCSB(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~TxtExpSuiteTextCSB(void);

	/** see ITxtExpSuite::CanExportText
	*/
	virtual bool16 CanExportText(const PMString& formatName);

	/** see ITxtExpSuite::DoExportText
	*/
	virtual ErrorCode DoExportText(IPMStream *fileStreamWrites, ITxtExpFileWriter::Encoding encoding);
private:
	/**
	Write the text contained in the ITextFocus to the output file stream
	@param stream, the file stream to be written out.
	@param encoding, the encoding to be written out.
	@param focus, ITextFocus that contains the text to be written out to file
	@return kSuccess if the write file operation is successful
	*/
	ErrorCode WriteFile(IPMStream* stream, const ITxtExpFileWriter::Encoding encoding, ITextFocus* focus);
	/**
	Takes a text buffer and make sure proper line ending is at the end of line for different platform
	@param ws, the WideString buffer to be processed.
	*/
	void ProcessTextCharBuffer(WideString& ws);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE (TxtExpSuiteTextCSB, kTxtExpSuiteTextCSBImpl)

/*
*/
TxtExpSuiteTextCSB::TxtExpSuiteTextCSB(IPMUnknown* boss) :
	CPMUnknown<ITxtExpSuite>(boss)
{
}

/*
*/
TxtExpSuiteTextCSB::~TxtExpSuiteTextCSB(void)
{
}

/*
*/
bool16 TxtExpSuiteTextCSB::CanExportText(const PMString& formatName)
{
	InterfacePtr<ITextTarget> iTextTarget(this, UseDefaultIID());
	InterfacePtr<ITextFocus> textFocus(iTextTarget->QueryTextFocus());
	ASSERT(textFocus != nil);
	if(textFocus)
	{
		if ( formatName == PMString(kTxtExpFormatNameKey) )
		{
			return kTrue;
		}
	}

	return kFalse;
}

/*
*/
ErrorCode TxtExpSuiteTextCSB::DoExportText(IPMStream *fileStreamWrites, ITxtExpFileWriter::Encoding encoding)
{
	ErrorCode result = kFailure;
	InterfacePtr<ITextTarget> iTextTarget(this, UseDefaultIID());
	InterfacePtr<ITextFocus> textFocus(iTextTarget->QueryTextFocus());
	ASSERT(textFocus != nil);
	if(textFocus)
		result = WriteFile(fileStreamWrites, encoding, textFocus);
	return result;
}

/* WriteFile
*/
ErrorCode TxtExpSuiteTextCSB::WriteFile(IPMStream* stream, const ITxtExpFileWriter::Encoding encoding, ITextFocus* focus)
{
	ASSERT_MSG(stream, "TxtExpFilter::WriteFile : stream is nil!");
	ASSERT_MSG(focus,  "TxtExpFilter::WriteFile : text focus is nil!");
	
	// assume success
	ErrorCode rc = kSuccess; 

	// get the ITextModel from the focus and the composeScanner
	InterfacePtr<ITextModel> model(focus->QueryModel());
	if (!model) 
	{
		ASSERT_FAIL("TxtExpFilter::WriteFile : model is nil");
		return kFailure;
	}
	InterfacePtr<IComposeScanner> composeScanner(model, IID_ICOMPOSESCANNER);
	if (!composeScanner) 
	{
		ASSERT_FAIL("TxtExpFilter::WriteFile : composeScanner is nil");
		return kFailure;
	}
	
	// get the start position to locate the cursor 
	TextIndex startPos = focus->GetStart(nil); 
    // get the length of the selected part
	int32 len = focus->Length();
	if (len == 0) 
	{
		// ASSUMPTION: If a text range (1 or more chars) isn't selected 
		// in the text focus, assume the user wants to export all of the 
		// text in the story.
		startPos = 0;
		len = model->TotalLength();
	}
	
	const int32 kTxtExpUpdateInterval = 32;

	do 
	{
		int32 pos = 0,		// pointer to current location in the text focus selection (relative to 'len')
			written = 0, 	// count of how many textchars were written during each write
			bufSize = 0, 	// size of textchar buffer, as returned by IComposeScanner::QueryDataAt
			chunkSize = 0, 	// size of textchar buffer to write, as returned by ProcessTextCharBuffer
			chunk2BProcessed = 0;	// local copy of chunkSize

		// get the appropriate writer for the selected encoding
		ITxtExpFileWriter* writer = TxtExpUtils::QueryTxtExpFileWriter(encoding);
		
		if (writer)
		{
			// we got a writer, so proceed!

			bool16 bDisplayProgress = kFalse;
			bool16 bWasCancelled = kFalse;
			
			// initialize progress bar, but show only if needed
			RangeProgressBar bar(kTxtExpProgressBarTitleKey, 1, len, bDisplayProgress);
			
			if (bDisplayProgress) 
			{
				bar.SetTaskText(kTxtExpInProgressStringKey); // Set the task title.
				bWasCancelled = kFalse;
			}
			// get the textchar from the selected part, write into the buffer
			// write in small chunks until all written.
			do {
				// get a chunk of text from IComposeScanner
				TextIterator iter = composeScanner->QueryDataAt(startPos + pos, nil, &bufSize);

				// take the smallest of kTxtExpBufferSize, 'bufSize',
				// the remaining range 
				chunkSize = min(kTxtExpBufferSize, min(bufSize, len - pos));

				// copy the UNICODE data to a temp WideString
				WideString tempWS;
				iter.AppendToStringAndIncrement(&tempWS, chunkSize);

				// keep a copy, as chunkSize will be 
				// modified by ProcessTextCharBuffer
				chunk2BProcessed = chunkSize;

				// check if we are ready to write
				if (chunkSize > 0) 
				{
					// we have our textchar buff and size, so proceed

					// update progress bar periodically and check for cancellations
					if (pos % kTxtExpUpdateInterval == 0)
					{
						bar.SetPosition(pos);
					}
					if (bar.WasCancelled())
					{   
						bWasCancelled = kTrue;
						break;
					}
				    // process CR and LF for each platform. 
					// NOTE: chunkSize could be modified here.
					ProcessTextCharBuffer(tempWS);
					chunkSize = tempWS.CharCount();
                    
					if (tempWS.empty() == kFalse) 
					{
						int32 numUTF16s = 0;
						const UTF16TextChar* bufferToWrite = tempWS.GrabUTF16Buffer(&numUTF16s);
						// do the writer specfic writes.  The encoding conversion happens within.
						// NOTE: There is a potential hazard in manipulating UTF16s 
						// in the WriteTextCharBuffer() method.  There may be a bug when a
						// UNICODE codepoint beyond the BMP (U+0000 - FFFF) is passed in.
						written = writer->WriteTextCharBuffer(stream, bufferToWrite, numUTF16s);
						ASSERT_MSG(written == chunkSize, "TxtExpFilter::WriteFile : wrote less textchars than I thought...");
						
						// Advance tcbuf pointer by number of textchars that were to be processed
						pos += chunk2BProcessed;
					}
					else
					{
						ASSERT_FAIL("TxtExpFilter::WriteFile : tempWS is empty! If there wasn't anything else to write, the program should not have gotten here.");
					}

				} // if ((chunkSize > 0) && (tcbuf != nil))...
				// continue while the stream is still being written, and the
				// user hasn't cancelled.
			} while ((written > 0) && 
					 (chunk2BProcessed > 0) && 
					 !bWasCancelled && 
					 (len > pos));
			// We are done with the file writer. Release it
			writer->Release();
		}
		else
		{
			ASSERT_FAIL(FORMAT_ARGS("TxtExpFilter::WriteFile : couldn't find a FileWriter for encoding format %d!", (int32)encoding));
			rc = kFailure;
			break;
		}
		
	} while (kFalse); // single loop
	return rc;
}

/* ProcessTextCharBuffer
	NOTE: Modifies the caller's WideString.
*/
void TxtExpSuiteTextCSB::ProcessTextCharBuffer(WideString& buf)
{
#if defined(MACINTOSH)
		// do nothing special
#elif defined(WIN32)
	if (buf.CharCount() > 0)
	{
		// if there is an LF without a CR beforehand, we need to insert a CR.
		int32 position = 0; // of current iterator
		WideStringConstUTF32Iter iter = buf.begin();
		WideStringConstUTF32Iter last = buf.end();
		UTF32TextChar prevChar = kTextChar_Null; // so that we reject the first char.
		while (iter < last) 
		{
			UTF32TextChar currChar = *iter;
			if ((prevChar != kTextChar_CR) && 
				(currChar == kTextChar_LF))
			{
				buf.Insert(UTF32TextChar(kTextChar_CR), position);
				iter = buf.begin() + position;
				last = buf.end();
			}

			prevChar = currChar;
			++iter;
			++position; // WideStringConstUTF32Iter::position() is debug only...
		}
    }
#endif
}
// End, TxtExpSuiteTextCSB.cpp.

