//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/CTxtExpFileWriter.h $
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

#ifndef __CTxtExpFileWriter_H__
#define __CTxtExpFileWriter_H__

// General includes
#include "CPMUnknown.h"
#include "K2Assert.h"
#include "TextChar.h"

// Interface includes
#include "ITxtExpFileWriter.h"
#include "IPMStream.h"

// Project includes
#include "TxtExpID.h"



/** CTxtExpFileWriter
	Implements a fundamental ITxtExpFileWriter for "platform" (ASCII and ShiftJIS) encoded files. 
	Useful as a base implementation for the "platform" implementations of ITxtExtFileWriter.
	@ingroup textexportfilter
	
*/
class CTxtExpFileWriter: public CPMUnknown<ITxtExpFileWriter>
{
public:
	/** Constructor
	*/
	CTxtExpFileWriter(IPMUnknown* boss, uint8 script = -1);

	/** Destructor
	*/
	virtual ~CTxtExpFileWriter(void);


	/** Writes the textchar data to the given file stream.
		@param stream Stream to write to.
		@param tcbuf Pointer to a buffer of textchars to write. 
		@param bufSize Number of textchars to write.
		@return Number of textchars (not bytes) written to stream.
	*/
	virtual int32 WriteTextCharBuffer(IPMStream* stream, const textchar* tcbuf, const int32 bufSize);

private:
	uint8 fScript; // CTUnicodeTranslator script to use 
};

#endif // #ifndef __CTxtExpFileWriter_H__

// End, CTxtExpFileWriter.h




