//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/ShiftJISFileWriter.cpp $
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

// Project includes
#include "TxtExpID.h"


/** ShiftJISFileWriter
	Implements ITxtExpFileWriter for ShiftJIS encoded files. 
	
	@ingroup textexportfilter
	
*/
class ShiftJISFileWriter: public CTxtExpFileWriter
{
public:
	/** Constructor
	*/
	ShiftJISFileWriter(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~ShiftJISFileWriter(void);


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
CREATE_PMINTERFACE(ShiftJISFileWriter, kShiftJISFileWriterImpl);


/* Constructor
   NOTE: 1 means "Japanese" for the CTUnicodeTranslator
*/
ShiftJISFileWriter::ShiftJISFileWriter(IPMUnknown* boss)
 : CTxtExpFileWriter(boss, 1) {}



/* Destructor
*/
ShiftJISFileWriter::~ShiftJISFileWriter(void)
{
}


/* WriteTextCharBuffer
*/
int32 ShiftJISFileWriter::WriteTextCharBuffer(IPMStream* stream, const textchar* tcbuf, const int32 bufSize)
{
	// call the parent class' method
	int32 written = CTxtExpFileWriter::WriteTextCharBuffer(stream, tcbuf, bufSize);
	
	// if there is any extra processing, place code here.
	
	return written;
}

// End, ShiftJISFileWriter.cpp




