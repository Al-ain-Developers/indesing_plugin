//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkChangeOptionsCmd.cpp $
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
#include "ICusDtLnkOptions.h"
#include "IIntData.h"
#include "ISubject.h"
// General includes:
#include "CmdUtils.h"
#include "Command.h"
#include "ErrorUtils.h"
#include "CusDtLnkID.h"

/** Implementation of command to change preferences relating to this plug-in

	@ingroup customdatalink
*/
class CusDtLnkChangeOptionsCmd : public Command
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.*/
	CusDtLnkChangeOptionsCmd(IPMUnknown* boss);

protected:

	/** Do
	 	@see Command::Do
	*/
	virtual void Do();
	
	/**
		@see Command::DoNotify
	*/
	virtual  void DoNotify();

	/** CreateName
	 	@see Command::CreateName
	*/
	virtual PMString* CreateName();

private:
	PMIID fPMIIDChanged;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CusDtLnkChangeOptionsCmd, kCusDtLnkChangeOptionsCmdImpl)

/* Constructor
*/
CusDtLnkChangeOptionsCmd::CusDtLnkChangeOptionsCmd(IPMUnknown* boss) : Command(boss)	
{
}

/* Do
*/
void CusDtLnkChangeOptionsCmd::Do()
{
	ErrorCode status = kFailure;
	do                      
	{
		InterfacePtr<ICusDtLnkOptions> cmdData(this, UseDefaultIID());
		ASSERT(cmdData);
		if (!cmdData) {
			break;
		}

		InterfacePtr<IIntData> pmiidIntData(this, IID_ICUSDTLNKPMIIDINTDATA);
		ASSERT(pmiidIntData);
		if(!pmiidIntData) {
			break;
		}
		PMIID pmiid(pmiidIntData->Get());
		fPMIIDChanged = pmiid;
		//Get the ItemList
		const UIDList* itemList = this->GetItemList();
		if (itemList == nil || itemList->IsEmpty()) {
			break;
		}
		UIDRef uidRef = itemList->GetRef(0);

		InterfacePtr<ICusDtLnkOptions> iCusDtLnkOptions(uidRef, pmiid);
		ASSERT(iCusDtLnkOptions);
		if (!iCusDtLnkOptions) {
			break;
		}
		
		
		for (int32 i=0; i < cmdData->GetKeyValuePairCount(); i++) {
			const WideString& key = cmdData->GetNthKey(i);
			const WideString val = cmdData->GetValueFromKey(key);
			iCusDtLnkOptions->AddKeyValuePair(key, val);
		}
		status = kSuccess;

	} while (kFalse);       

	// Handle any errors
	if (status != kSuccess) {
		ErrorUtils::PMSetGlobalErrorCode(status);
	}
}


/* CreateName
*/
PMString* CusDtLnkChangeOptionsCmd::CreateName()
{
	return new PMString(kCusDtLnkChangeOptionsCmdKey);
}


/*
*/
void CusDtLnkChangeOptionsCmd::DoNotify()
{
	// Broadcast on the subject (which is workspace, prob)
	// with IID of options interface we changed, 
	// 
	InterfacePtr<ISubject> subject(GetItemListReference().GetRef(0), UseDefaultIID());
	if(subject) {
		subject->ModelChange(kCusDtLnkChangeOptionsCmdBoss, this->fPMIIDChanged, this);
	}
}

// End, CusDtLnkChangeOptionsCmd.cpp.


