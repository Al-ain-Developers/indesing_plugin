//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/UNICODEFileWriter.cpp $
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

// Project includes
#include "TxtExpID.h"

/** UNICODEFileWriter
	Implements ITxtExpFileWriter for UNICODE encoded files. 
	
	@ingroup textexportfilter
	
*/
class UNICODEFileWriter: public CPMUnknown<ITxtExpFileWriter>
{
public:
	/** Constructor
	*/
	UNICODEFileWriter(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~UNICODEFileWriter(void);


	/** Writes the textchar data to the given file stream.
		@param stream Stream to write to.
		@param tcbuf Pointer to a buffer of textchars to write. 
		@param bufSize Number of textchars to write.
		@return Number of textchars (not bytes) written to stream.
	*/
	virtual int32 WriteTextCharBuffer(IPMStream* stream, const textchar* tcbuf, const int32 bufSize);

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(UNICODEFileWriter, kUNICODEFileWriterImpl);


/* Constructor
*/
UNICODEFileWriter::UNICODEFileWriter(IPMUnknown* boss)
 : CPMUnknown<ITxtExpFileWriter>(boss)
{
}

/* Destructor
*/
UNICODEFileWriter::~UNICODEFileWriter(void)
{
}



/* WriteTextCharBuffer
*/
int32 UNICODEFileWriter::WriteTextCharBuffer(IPMStream* stream, const textchar* tcbuf, const int32 bufSize)
{
	// We are already given a UNICODE buffer, so write the entire buffer without converting.
    // This will write the data in the byte order for the platform. 
    // If on Windows, this will write in little endian. 
    // If on Mac, this will write in big endian.
	int32 written = stream->XferInt16((int16*)tcbuf, bufSize);
	return written;
}

// End, UNICODEFileWriter.cpp




