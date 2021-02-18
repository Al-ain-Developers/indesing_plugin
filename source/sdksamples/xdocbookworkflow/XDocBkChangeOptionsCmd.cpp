//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkChangeOptionsCmd.cpp $
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
#include "IXDocBkOptions.h"

// General includes:
#include "CmdUtils.h"
#include "Command.h"
#include "ErrorUtils.h"
#include "XDocBkID.h"

/** Implementation of command to change preferences relating to this plug-in

	@ingroup xdocbookworkflow
*/
class XDocBkChangeOptionsCmd : public Command
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.*/
	XDocBkChangeOptionsCmd(IPMUnknown* boss);

protected:

	/** Do
	 	@see Command::Do
	*/
	virtual void Do();
	
	/** CreateName
	 	@see Command::CreateName
	*/
	virtual PMString* CreateName();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XDocBkChangeOptionsCmd, kXDocBkChangeOptionsCmdImpl)

/* Constructor
*/
XDocBkChangeOptionsCmd::XDocBkChangeOptionsCmd(IPMUnknown* boss) : Command(boss)	
{
}

/* Do
*/
void XDocBkChangeOptionsCmd::Do()
{
	ErrorCode status = kFailure;
	do                      
	{
		InterfacePtr<IXDocBkOptions> cmdData(this, UseDefaultIID());
		ASSERT(cmdData);
		if (!cmdData) {
			break;
		}

		//Get the ItemList
		const UIDList* itemList = this->GetItemList();
		if (itemList == nil || itemList->IsEmpty()) {
			break;
		}
		UIDRef uidRef = itemList->GetRef(0);
		InterfacePtr<IXDocBkOptions> iXDocBkOptions(uidRef, UseDefaultIID());
		ASSERT(iXDocBkOptions);
		if (!iXDocBkOptions) {
			break;
		}
		int32 optionCount = cmdData->GetOptionCount();
		ASSERT(optionCount > 0);
		if (optionCount < 0) {
			break;
		}
		for (int32 i=0; i < optionCount; i++) {
			iXDocBkOptions->AddOption(cmdData->GetNthOption(i),i);
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
PMString* XDocBkChangeOptionsCmd::CreateName()
{
	return new PMString(kXDocBkChangeOptionsCmdKey);
}

// End, XDocBkChangeOptionsCmd.cpp.


