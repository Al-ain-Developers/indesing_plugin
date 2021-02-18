//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvt/WritePDFVTDataSourceInfoCmd.cpp $
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

// General includes:
#include "Command.h"
#include "ErrorUtils.h"

#include "PDFVTID.h"

#include "IDataSourceData.h"

/** Command that stores persistent data to the document.
*/
class WritePDFVTDataSourceInfoCmd : public Command
{
public:
	/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	WritePDFVTDataSourceInfoCmd(IPMUnknown* boss);

	/** Desturctor.
	*/
	virtual ~WritePDFVTDataSourceInfoCmd();

	/** See CommandLLLowMemIsOK
			@return bool16
	*/
	bool16 LowMemIsOK(void) const
	{ return kFalse; }

protected:
	/** Execute the main behavior of the command.
			@see Command::Do
	*/
	virtual void Do(void);

	/** Notify interested observers.
		In our case, we broadcase nothing.
		@see Command::DoNotify
	*/
	virtual void DoNotify(void);

	/** Report the name of the command
		@see Command::CreateName
	*/
	virtual PMString* CreateName(void);
};

CREATE_PMINTERFACE(WritePDFVTDataSourceInfoCmd, kWritePDFVTDataSourceInfoCmdImpl)

WritePDFVTDataSourceInfoCmd::WritePDFVTDataSourceInfoCmd(IPMUnknown* boss) : Command(boss)
{
}

WritePDFVTDataSourceInfoCmd::~WritePDFVTDataSourceInfoCmd(void)
{
}

void WritePDFVTDataSourceInfoCmd::Do(void)
{
	ErrorCode err = kSuccess;
	do
	{
		InterfacePtr<IDataSourceData> cmdData(this, UseDefaultIID());
		if (cmdData == nil)
		{
			err = kFailure;
			ASSERT_FAIL("datasourcedata is nil");
			break;
		}

		int32 itemCount = fItemList.Length();

		for (int32 count = 0; count < itemCount; count++)
		{
			InterfacePtr<IDataSourceData> dataSourceData(fItemList.GetRef(count), UseDefaultIID());			
			dataSourceData->SetPath(cmdData->GetPath());
			dataSourceData->SetCIP4Mapping(cmdData->GetCIP4Mapping());			
		}
	} while(kFalse);

	if (err != kSuccess)
	{
		ErrorUtils::PMSetGlobalErrorCode(err);
	}
}

void WritePDFVTDataSourceInfoCmd::DoNotify(void)
{
}

PMString* WritePDFVTDataSourceInfoCmd::CreateName(void)
{	
	PMString* string = new PMString(kPDFVTWriteDataSourceInfoCmdKey);
	return string;
}