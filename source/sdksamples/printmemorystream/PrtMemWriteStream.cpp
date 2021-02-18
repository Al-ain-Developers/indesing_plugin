//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printmemorystream/PrtMemWriteStream.cpp $
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

// Interface includes:
// none.

// Implementation Includes
#include "CStreamWrite.h" 

// Project includes:
#include "PrtMemID.h"
#include "PrtMemMemoryXferBytes.h"

/** Implements IPMStream over a memory buffer
	@ingroup printmemorystream
*/
class PrtMemWriteStream : public CStreamWrite
{
public:
	/**	Constructor.
	 * 	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PrtMemWriteStream(IPMUnknown* boss);

	/**	Destructor.
	*/
	virtual ~PrtMemWriteStream(void);

private:
	/**	Our implementation of IXferBytes.
	 * 	Note that this instance is allocated when this class is constructed.
	*/
	PrtMemMemoryXferBytes fPrtMemMemoryXferBytes;   
};

// CREATE_PMINTERFACE
//	Binds the C++ implementation class onto its ImplementationID 
// 	making the C++ code callable by the application.
CREATE_PMINTERFACE(PrtMemWriteStream, kPrtMemWriteStreamImpl)


/* Constructor
*/
PrtMemWriteStream::PrtMemWriteStream(IPMUnknown* boss) 
: CStreamWrite(boss)
{
	this->SetXferBytes(&fPrtMemMemoryXferBytes);
}

/* Destructor
*/
PrtMemWriteStream::~PrtMemWriteStream(void) 
{
}


// End, PrtMemWriteStream.cpp.

