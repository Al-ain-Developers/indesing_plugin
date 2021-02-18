//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/ModifyCdlChartCmd.cpp $
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
#include "IBoolData.h"
#include "ISubject.h"

// General includes:
#include "Command.h"
#include "ErrorUtils.h"

// Project includes:
#include "CdlChartID.h"
#include "ICdlChartData.h"


/** A command to modify candle chart page item with stock market data.

	@ingroup candlechart
	
*/
class ModifyCdlChartCmd : public Command
{
public:
	/**	constructor.
	*/
	ModifyCdlChartCmd(IPMUnknown* boss);

	/** @return kFalse don't use this command if memory is low. 
	*/
	bool16 LowMemIsOK() const { return kFalse; }

protected:
	/** modify candle chart page item.
		@see Command::Do
	*/
	void Do();
	
	/** Do Notify.
		@see Command::DoNotify
	*/
	void DoNotify();

	/** Gives the name that shows up under the Edit menu and
		allows the user to undo or redo the command.

		@return pointer to a PMString allocated using the new operator. Deleted by caller.
		@see Command::CreateName
	*/
	PMString* CreateName();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(ModifyCdlChartCmd, kModifyCdlChartCmdImpl)

/* Constructor
*/
ModifyCdlChartCmd::ModifyCdlChartCmd(IPMUnknown* boss) :
	Command(boss)
{
}

/* Do
*/
void ModifyCdlChartCmd::Do()
{

	// Get the stock chart data	
	InterfacePtr<ICdlChartData> newChartData(this, UseDefaultIID());
	if (newChartData == nil)
	{
		return;
	}
	WideString theNameStr;
	newChartData->GetName(theNameStr);	

	// Get the stock chart data from the page item.	
	InterfacePtr<ICdlChartData> chartData(GetItemList()->GetRef(0), UseDefaultIID());

	// set chart data & name
	chartData->Set(newChartData->Get());
	chartData->SetName(theNameStr);

}

/* DoNotify
 This method broadcasts changes for observers. 
*/
void ModifyCdlChartCmd::DoNotify()
{
	// not necessary
}

/* CreateName
*/
PMString* ModifyCdlChartCmd::CreateName()
{
	PMString* string_name = new PMString(kModifyCdlChartCmdStringKey);
	return string_name;
}

// End, ModifyCdlChartCmd.cpp.


