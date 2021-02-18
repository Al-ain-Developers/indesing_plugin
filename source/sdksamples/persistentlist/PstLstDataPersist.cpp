//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstDataPersist.cpp $
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

// API includes
#include "HelperInterface.h"
#include "CPMUnknown.h"

// Project includes:
#include "IPstLstData.h"
#include "IPMStream.h"

/** PstLstDataPersist is the persistent IPstLstData implementation.

	@ingroup persistentlist
	
*/

class PstLstDataPersist : public CPMUnknown<IPstLstData>
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PstLstDataPersist(IPMUnknown* boss);

		/**
			This function returns its only data member, fName.
			@return WideString the data member this interface carries.
		*/
		virtual const WideString&	GetName();

		/**
			This function set its only data member with the parameter passed in.
			@param theData data to be set
		*/
		virtual void SetName(const WideString& theData);

		/** See IPstLstData::SetParent
		*/
		virtual void SetParent(const UID parent);
		
		/** See IPstLstData::GetParent
		*/
		virtual UID	GetParent() const;

		/**
			Because this is a persistent interface, it must support the ReadWrite method. This method is used for 
			both writing information out to the database and reading information in from the database.

			Note: the first thing we read/write here is a version number.  It is used to identify which plug-in
			is used to write out this IPstLstData.  Since this is the first version of the PstLst plug-in, thus the version
			number is 1, and then followed by the IPstLstData.  Later if there is a newer version of this plug-in which
			will write out an extra field of data, then we can just come to this routine, and check the version number
			of the doc, and then read in the data accordingly.  this will make sure the newer plug-in is backward
			compatible with an older version of document.  Lastly, since the version number should be the first thing
			to read in for this interface, all the new data should be append at the bottom.

			@param stream contains the stream to be written or read.
			@param implementation the implementation ID.
		*/
		void ReadWrite(IPMStream* stream, ImplementationID implementation);

	private:
		WideString	fName;
		UID			fParent;
};

CREATE_PERSIST_PMINTERFACE(PstLstDataPersist, kPstLstDataPersistImpl)

/*	PstLstDataPersist::PstLstDataPersist
*/
PstLstDataPersist::PstLstDataPersist(IPMUnknown* boss)
	: CPMUnknown<IPstLstData>(boss), 
	  fParent(kInvalidUID),
	  fName("")
{
}

/*	PstLstDataPersist::SetName
*/
void PstLstDataPersist::SetName(const WideString& newData)
{
	if (fName != newData)
	{
		PreDirty ();
		fName = newData;
	}
}

/*	PstLstDataPersist::GetName
*/
const WideString& PstLstDataPersist::GetName()
{
	return fName;
}

/*
*/
void PstLstDataPersist::SetParent(const UID parent)
{
	if (fParent != parent) {
		PreDirty ();
		fParent = parent;
		
	}
}

/*
*/
UID PstLstDataPersist::GetParent() const
{
	return fParent;
}

/*	PstLstDataPersist::ReadWrite
*/
void PstLstDataPersist::ReadWrite(IPMStream* stream, ImplementationID implementation)
{
	/* 	
	//	REMINDER: 
	//	If you change the arrangement of persistent data in this method, 
	//	remember to update the format number in the PluginVersion resource. 
	//	(See the PstLstID.h file for the plug-in specific format numbers.) 
	*/
	fName.ReadWrite(stream);
	stream->XferReference(fParent); // <<-- Added at InDesign CS2 
}
