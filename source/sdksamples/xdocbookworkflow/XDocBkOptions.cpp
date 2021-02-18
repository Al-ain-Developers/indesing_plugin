//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkOptions.cpp $
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
#include "IXDocBkOptions.h"

// General includes:
#include "CPMUnknown.h"


/** Class to persist a list of options to the session workspace.
	XDocBkOptions is a persistent implementation of interface IXDocBkOptions.
	@ingroup xdocbookworkflow
*/
class XDocBkOptions : public CPMUnknown<IXDocBkOptions>
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	XDocBkOptions(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~XDocBkOptions() {}

	/** Method to add in an options to the list of persistent options
		@see IXDocBkOptions
	*/
	virtual void AddOption(const WideString& newVal,  const int32 indexWhere); 

	/** GetNthOption
		@see IXDocBkOptions
	*/
	virtual WideString GetNthOption(const int32 index); 

	
	virtual int32 GetOptionCount();
	/** Persistence related method; reads from or writes to given stream
		@param s IN the persistent in and out stream.
		@param prop IN the implementation ID 			
	*/
	virtual void ReadWrite(IPMStream* s, ImplementationID prop);

private:
	bool16 validate(const int32 index);

	K2Vector<WideString> fPersistentOptionList;
};

/*	CREATE_PERSIST_PMINTERFACE
	This macro creates a persistent class factory for the given class name
	and registers the ID with the host.
*/
CREATE_PERSIST_PMINTERFACE(XDocBkOptions, kXDocBkOptionsImpl)

/*	Constructor
	The preference state is set to kFalse for the application 
	workspace. The preference state for a new document is set
	to the application preference state.
*/
XDocBkOptions::XDocBkOptions(IPMUnknown* boss) : CPMUnknown<IXDocBkOptions>(boss)   
{
}

/* AddOption
*/
void XDocBkOptions::AddOption(const WideString& newVal, const int32 indexWhere) 
{ 
	PreDirty ();
	if (indexWhere < 0 || indexWhere >= fPersistentOptionList.size())
	{
		fPersistentOptionList.push_back(newVal); 
	}
	else
	{
		fPersistentOptionList[indexWhere] =  newVal;
	}
	
}

/* GetNthOption
*/
WideString XDocBkOptions::GetNthOption(const int32 index)
{   
	if (this->validate(index))
	{
		return fPersistentOptionList[index]; 
	}
	return WideString();
}

int32 XDocBkOptions::GetOptionCount()
{   
	return fPersistentOptionList.size(); 
}

/* ReadWrite
*/
void XDocBkOptions::ReadWrite(IPMStream* s, ImplementationID prop)
{
	/* 	
	//	REMINDER: 
	//	If you change the arrangement of persistent data in this method, 
	//	remember to update the format number in the PluginVersion resource. 
	//	(See the XDocBkID.h file for the plug-in specific format numbers.) 
	*/
	int32 numOptions(0);
	if (s->IsReading())
	{
		s->XferInt32(numOptions);
		fPersistentOptionList.clear();
		fPersistentOptionList.reserve(numOptions);
		for (int32 i = 0; i < numOptions; i++)
		{
			WideString tempOption;
			// Read in from the stream
			tempOption.ReadWrite(s);
			fPersistentOptionList.push_back(tempOption);
		}               
	}
	else
	{
		numOptions = fPersistentOptionList.size();
		s->XferInt32(numOptions);
		for (int32 i=0; i < numOptions; i++)
		{
			// Write out the option to the stream
			fPersistentOptionList[i].ReadWrite(s);
		}
	}
}

/* validate
*/
bool16 XDocBkOptions::validate(const int32 index)  
{
	return (index >= 0) && (index < fPersistentOptionList.size());
}

// End, XDocBkOptions.cpp.
