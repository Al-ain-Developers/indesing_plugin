//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblPrintPrefCmd.cpp $
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
#include "CmdUtils.h"
#include "Command.h"
#include "IBoolData.h"
#include "IWorkspace.h"

// Project includes:
#include "FrmLblID.h"

class FrmLblPrintPrefsCmd :	public Command
{
public:
	FrmLblPrintPrefsCmd(IPMUnknown* boss) : Command(boss){};

protected:
	/**
	@see Command::Do
	*/
	virtual void Do();

	PMString* CreateName();
};

CREATE_PMINTERFACE(FrmLblPrintPrefsCmd, kFrmLblPrintPrefsCmdImpl)

/* Do
*/
void FrmLblPrintPrefsCmd::Do()
{
	do{
		if (fItemList.Length() == 0)
		{
			ASSERT_FAIL("FrmLblPrintPrefsCmd::Do: empty item list");
			break;
		}

		InterfacePtr<IBoolData> boolData(this, IID_IFRMLBLPRINTBOOLDATA);
		if (boolData == nil)
		{
			ASSERT_FAIL("FrmLblPrintPrefsCmd::Do cannot get IBoolData for the command");		
			break;
		}

		//Expects the item is workspace, IID_IFRMLBLPRINTBOOLDATA add in it.
		InterfacePtr<IBoolData> printPrefs(fItemList.GetRef(0), IID_IFRMLBLPRINTBOOLDATA);
		if(printPrefs == nil)
		{				
			ASSERT_FAIL("Invalid print preference in kWorkSpaceBoss");
			break;
		}

		printPrefs->Set(boolData->Get());

	} while(kFalse);
}

PMString* FrmLblPrintPrefsCmd::CreateName()
{
	return new PMString(kFrmLblPrintPrefsCmdStringKey);
}
