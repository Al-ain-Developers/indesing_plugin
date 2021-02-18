//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvChangeOptionsCmd.cpp $
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
#include "ISubject.h"
#include "IWorkspace.h"

// General includes:
#include "CmdUtils.h"
#include "ErrorUtils.h"
#include "Command.h"

// Project includes:
#include "PnlTrvID.h"
#include "IPnlTrvOptions.h"
#include "IPnlTrvChangeOptionsCmdData.h"


/** Implementation of command to change the preferences persisted to the 
	session workspace through our IPnlTrvOptions interface.

	
	@ingroup paneltreeview
*/

class PnlTrvChangeOptionsCmd : public Command
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.*/
	PnlTrvChangeOptionsCmd(IPMUnknown* boss);

protected:
	/** Performs notification. */
	virtual void DoNotify();

	/** Implements command. */
	virtual void Do();

	/** Sets command name. */
	virtual PMString* CreateName();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PnlTrvChangeOptionsCmd, kPnlTrvChangeOptionsCmdImpl)


/* Constructor
*/
PnlTrvChangeOptionsCmd::PnlTrvChangeOptionsCmd(IPMUnknown* boss) :
	Command(boss)
{
}


/* Do
*/
void PnlTrvChangeOptionsCmd::Do()
{
	ErrorCode status = kFailure;
	do						
	{
		InterfacePtr<IPnlTrvChangeOptionsCmdData> 
			cmdData (this, UseDefaultIID());
		ASSERT(cmdData);
		if (cmdData == nil)
		{
			break;
		}
		
		// Get the ItemList
		const UIDList* itemList = this->GetItemList();
		if (itemList == nil || itemList->IsEmpty())
		{
			break;
		}
		UIDRef uidRef = itemList->GetRef(0);
		InterfacePtr<IPnlTrvOptions> 
			iPnlTrvOptions(uidRef, UseDefaultIID());
		ASSERT(iPnlTrvOptions);
		if (iPnlTrvOptions == nil)
		{
			break;
		}

		ASSERT(cmdData->GetOptionCount()>0);

		for(int32 i=0; i < cmdData->GetOptionCount(); i++)
		{
			iPnlTrvOptions->AddOption(WideString(cmdData->GetNthOption(i)), i);
		}
		status = kSuccess;

	} while(kFalse);		

	// Handle any errors
	if (status != kSuccess)
	{
		ErrorUtils::PMSetGlobalErrorCode(status);
	}
}

/* DoNotify
*/
void PnlTrvChangeOptionsCmd::DoNotify()
{
	InterfacePtr<IWorkspace> theWorkSpace(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<ISubject> subject(theWorkSpace, IID_ISUBJECT);
	if (subject)
	{
		subject->ModelChange(kPnlTrvChangeOptionsCmdBoss, IID_IPNLTRVOPTIONS, this);
	}
}


/* CreateName
*/
PMString* PnlTrvChangeOptionsCmd::CreateName()
{
	return new PMString(kPnlTrvChangeOptionsCmdKey);
}


