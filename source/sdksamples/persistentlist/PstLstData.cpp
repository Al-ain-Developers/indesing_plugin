//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstData.cpp $
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

class IPMStream;

/** PstLstData is the non-persistent IPstLstData implementation.

	@ingroup persistentlist
	
*/
class PstLstData : public CPMUnknown<IPstLstData>
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PstLstData(IPMUnknown* boss);

		/**
			This function returns IPstLstData's only data member, fName.
			@return WideString the data member this interface carries.
		*/
		virtual const WideString&	GetName();

		/**
			This function set its only data member with the parameter passed in.
			@param theData data to be set
		*/
		virtual void SetName
		(
			const WideString& theData 
		);

		/** See IPstLstData::SetParent.
		*/
		virtual void SetParent(const UID parent);
		
		/** See IPstLstData::GetParent.
		*/
		virtual UID	GetParent() const;

	private:
		WideString	fName;
		UID			fParent;

};

CREATE_PMINTERFACE(PstLstData, kPstLstDataImpl)

/*	PstLstData::PstLstData
*/
PstLstData::PstLstData(IPMUnknown* boss)
: CPMUnknown<IPstLstData>(boss), fParent(kInvalidUID)
{
}

/*	PstLstData::SetName
*/
void PstLstData::SetName(const WideString& newData)
{
	if (fName != newData)
		fName = newData;
}

/*	PstLstData::GetName
*/
const WideString& PstLstData::GetName()
{
	return fName;
}

/*
*/
void PstLstData::SetParent(const UID parent)
{
	if (fParent != parent) {
		fParent = parent;
	}
}

/*
*/
UID PstLstData::GetParent() const
{
	return fParent;
}
