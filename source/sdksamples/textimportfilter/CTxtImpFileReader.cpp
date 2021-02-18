//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textimportfilter/CTxtImpFileReader.cpp $
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

// Project includes
#include "TxtImpID.h"


/* CTxtImpFileReader constructor
*/
CTxtImpFileReader::CTxtImpFileReader(IPMUnknown* boss)
 :  CPMUnknown<ITxtImpFileReader>(boss), 
    fStream(nil),
    fTCBuf(nil),
	fCBuf(nil),
    fLen(0),
	fCurrMarker(0),
	fEndOfReadMarker(0)
{}


/* CTxtImpFileReader destructor
*/
CTxtImpFileReader::~CTxtImpFileReader(void)
{
	// cleanup UTF16TextChar buffer
	if (fTCBuf) 
	{ 
		delete []fTCBuf; 
      	fTCBuf = nil;
	}

	// cleanup char buffer
	if (fCBuf) 
	{ 
		delete []fCBuf; 
    	fCBuf = nil;
	} 
}


/* OpenFile
*/
void CTxtImpFileReader::SetStream(IPMStream* stream)
{
	// open stream
	fStream = stream;
	ASSERT_MSG(fStream, "CTxtImpFileReader ctor - fStream is nil!");

	fLen = GetFileSizeInBytes();
}

/* GetFileSizeInBytes
*/
int32 CTxtImpFileReader::GetFileSizeInBytes(void)
{
	ASSERT_MSG(fStream, "CTxtImpFileReader::GetFileSizeInBytes - fStream is nil!");

	// get current position
	int32 curr = fStream->Seek(0, kSeekFromCurrent);

	// goto end of stream, and get the byte count
	int32 endOfStream = fStream->Seek(0, kSeekFromEnd);
	
	// go back to the original spot
	fStream->Seek(curr, kSeekFromStart);

	return endOfStream;
}

// End, CTxtImpFileReader.cpp.


