//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvChangeOptionsCmdData.cpp $
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

// Interface Includes

// Implementation Includes
#include "CPMUnknown.h"
#include "K2Vector.tpp"

// Project includes:
#include "IPnlTrvChangeOptionsCmdData.h"

/** Persistent implementation of interface IPnlTrvChangeOptionsCmdData. 
	It is used by the command to change the options for this plug-in.

	
	@ingroup paneltreeview

*/
class PnlTrvChangeOptionsCmdData : 
	public CPMUnknown<IPnlTrvChangeOptionsCmdData>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PnlTrvChangeOptionsCmdData(IPMUnknown* boss);

	/** 
		Destructor
	*/
	virtual ~PnlTrvChangeOptionsCmdData() {}

	/** Add option to list of options stored on this.
		@param newVal [IN] new  value to append to list.
	*/
	virtual void AddOption(const PMString& newVal); 

	/** Accessor for option at zero-based index in list of options
		@param index [IN] position of interest
		@return option at given position, or empty string if invalid index
	*/
	virtual PMString GetNthOption(const int32 index); 

	/** Accessor for size of options list
		@return size of list of options
	*/
	virtual int32 GetOptionCount() { return fOptions.size(); }

private:
	bool16 validate(const int32 index);
	K2Vector<PMString> fOptions;
};	

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PnlTrvChangeOptionsCmdData, kPnlTrvChangeOptionsCmdDataImpl)

/*	Constructor
*/
PnlTrvChangeOptionsCmdData::PnlTrvChangeOptionsCmdData(IPMUnknown* boss) :
	CPMUnknown<IPnlTrvChangeOptionsCmdData>(boss)
{
}


/* AddOption
*/
void PnlTrvChangeOptionsCmdData::AddOption(const PMString& newVal) 
{ 
	fOptions.push_back(newVal); 
}


/* GetNthOption
*/
PMString PnlTrvChangeOptionsCmdData::GetNthOption(const int32 index)
{ 
	ASSERT(validate(index));
	if(this->validate(index))
	{
		return fOptions[index]; 
	}
	return PMString();
}


/* validate
*/
bool16 PnlTrvChangeOptionsCmdData::validate(const int32 index)  
{
	return index >= 0 && index < fOptions.size();
}

//	end, File:	PnlTrvChangeOptionsCmdData

