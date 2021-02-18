//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPIDataPersist.cpp $
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
#include "IPMStream.h"

// General includes
#include "CPMUnknown.h"

// Project includes:
#include "BPIID.h"
#include "IBPIData.h"

/** Persistent implementation of IBPIData used by clients who need 
	to store the value in documents and other kinds of databases.

	@ingroup basicpersistinterface
	
*/

class BPIDataPersist : public CPMUnknown<IBPIData>
{
public:
	/**
		Constructor.

		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BPIDataPersist(IPMUnknown* boss);

	/**
		See IBPIData.
	*/
	virtual const WideString&	Get();

	/**
		See IBPIData.
	*/
	virtual void Set(const WideString& value);

	/**
		Because this is a persistent interface, it must support the ReadWrite method. This method is used for 
		both writing information out to the database and reading information in from the database.

		Note: the first thing we read/write here is a version number.  It is used to identify which plug-in
		is used to write out this BPI data.  Since this is the first version of the BPI plug-in, thus the version
		number is 1, and then followed by the BPI data.  Later if there is a newer version of this plug-in which
		will write out an extra field of data, then we can just come to this routine, and check the version number
		of the doc, and then read in the data accordingly.  this will make sure the newer plug-in is backward
		compatible with an older version of document.  Lastly, since the version number should be the first thing
		to read in for this interface, all the new data should be append at the bottom.

		@param stream contains the stream to be written or read.
		@param implementation the implementation ID.
	*/
	void ReadWrite(IPMStream* stream, ImplementationID implementation);

private:
	WideString	fData;
};

/*	Make the implementation available to the application. Note that persistent
	implementations use a different macro to the CREATE_PMINTERFACE macro used
	by non persistent implementations.
*/
CREATE_PERSIST_PMINTERFACE(BPIDataPersist, kBPIDataPersistImpl)

/*
*/
BPIDataPersist::BPIDataPersist(IPMUnknown* boss)
: CPMUnknown<IBPIData>(boss) , fData("")  			
{

}

/*
*/
void BPIDataPersist::Set (const WideString& value)
{
	if (value != fData) {
		PreDirty ();
		fData = value;
	}
}

/*
*/
const WideString& BPIDataPersist::Get()
{
	return fData;
}

/*
*/
void BPIDataPersist::ReadWrite(IPMStream* stream, ImplementationID implementation)
{
	// These methods will read if the stream is a 'read-stream'
	// and write if the stream is a write stream:
	int16	version = 0x01;
	stream->XferInt16(version);
	fData.ReadWrite(stream);
}


