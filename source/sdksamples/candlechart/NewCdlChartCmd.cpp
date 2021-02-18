//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/NewCdlChartCmd.cpp $
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
#include "ICommandSequence.h"
#include "IDocument.h"
#include "IGeometry.h"
#include "IGraphicAttributeUtils.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "IPathUtils.h"
#include "ISpread.h"
#include "ISpreadList.h"
#include "ISubject.h"
#include "ISwatchList.h"
#include "ISwatchUtils.h"

// General includes:
#include "Command.h"
#include "ErrorUtils.h"
#include "IPathUtils.h"
#include "TransformUtils.h"

// Project includes:
#include "CdlChartID.h"
#include "ICdlChartData.h"


/** A command to place candle chart page item with stock market data.

	@ingroup candlechart
	
*/
class NewCdlChartCmd : public Command
{
public:
	/**	Browse the file system for a comma separated values file.
		@param outFile is the CSV file that opens.
		@return kTrue if a CSV file is found, otherwise kFalse.
	*/
	NewCdlChartCmd(IPMUnknown* boss);

	/** @return kFalse don't use this command if memory is low. 
	*/
	bool16 LowMemIsOK() const { return kFalse; }

protected:
	/** Place candle chart page item.
		@see Command::Do
	*/
	void Do();

	/** Gives the name that shows up under the Edit menu and
		allows the user to undo or redo the command.

		@return pointer to a PMString allocated using the new operator. Deleted by caller.
		@see Command::CreateName
	*/
	PMString* CreateName();

	/** Point the command target to the workspace. 
		Default targeting via item list doesn't work with this command.
		@see Command::SetUpTarget
	*/
	void SetUpTarget();	
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(NewCdlChartCmd, kNewCdlChartCmdImpl)

/* Constructor
*/
NewCdlChartCmd::NewCdlChartCmd(IPMUnknown* boss) :
	Command(boss)
{
}

/* SetUpTarget
*/
void NewCdlChartCmd::SetUpTarget()
{
	InterfacePtr<INewPageItemCmdData> data(this, UseDefaultIID());
	if (data != nil)
	{
		SetTarget(data->GetDataBase());
	}
}

/* Do
*/
void NewCdlChartCmd::Do()
{
	ICommandSequence* cmdSeq = nil;

	/* This command is never called from a tracker, comment out this block.
	// Allows Do to be called from the tracker before the command is posted, to
	// force creation of the page item.
	if (GetCommandState() == kDone)
	{
		return;
	}*/

	// Get INewPageItemCmdData for accessing frame rectangle
	InterfacePtr<INewPageItemCmdData> newItemCmdData(this, UseDefaultIID());
	if (newItemCmdData == nil)
	{
		ASSERT_FAIL("cannot create command to apply stoke weight");
		return;
	}

	// Creating the actual page item
	PMRect frameRect(newItemCmdData->GetPointList()[0], newItemCmdData->GetPointList()[1]);
	UIDRef newSplineItem = Utils<IPathUtils>()->CreateRectangleSpline(
			UIDRef(newItemCmdData->GetDataBase(), newItemCmdData->GetParent()),
			frameRect, INewPageItemCmdData::kGraphicFrameAttributes,
			newItemCmdData->GetItemClass());

	// Get the stock chart data	
	InterfacePtr<ICdlChartData> chartData(this, UseDefaultIID());
	if (chartData == nil)
	{
		return;
	}

	WideString theNameStr;
	chartData->GetName(theNameStr);	

	// Get the stock chart data from the page item just created.	
	InterfacePtr<ICdlChartData> newChartData(newSplineItem, UseDefaultIID());
	
	// set chart data & name
	newChartData->Set(chartData->Get());
	newChartData->SetName(theNameStr);

	// create stroke command
	UIDList newSplineItemList(newSplineItem);
	InterfacePtr<ICommand> strokeWeightCmd(
			Utils<IGraphicAttributeUtils>()->CreateStrokeWeightCommand(
			PMReal(1.0), &newSplineItemList, kTrue, kTrue));
	if (strokeWeightCmd == nil)
	{
		ASSERT_FAIL("cannot create command to apply stoke weight");
		return;
	}

	// beginnning of command sequence
	cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	if (cmdSeq == nil)
	{
		return;
	}
	// process the stroke command
	if (CmdUtils::ProcessCommand(strokeWeightCmd) == kFailure)
	{
		ASSERT_FAIL("error processing command to apply stroke weight");
		CmdUtils::EndCommandSequence(cmdSeq);
		return;
	}

	InterfacePtr<ISwatchList> swatchList(Utils<ISwatchUtils>()->QueryActiveSwatchList());
	if (swatchList == nil)
	{
		ASSERT_FAIL("ISwatchList* nil");
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
		CmdUtils::EndCommandSequence(cmdSeq);
		return;
	}

	UID blackUid = swatchList->GetBlackSwatchUID();
	InterfacePtr<ICommand> strokeRenderingCmd(
			Utils<IGraphicAttributeUtils>()->CreateStrokeRenderingCommand(
			blackUid, &newSplineItemList, kTrue, kTrue));
	if (strokeRenderingCmd == nil)
	{
		ASSERT_FAIL("cannot create command to apply stoke rendering");
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
		CmdUtils::EndCommandSequence(cmdSeq);
		return;
	}

	// process the stroke command
	if (CmdUtils::ProcessCommand(strokeRenderingCmd) == kFailure)
	{
		ASSERT_FAIL("error processing command to apply stroke rendering");
		CmdUtils::EndCommandSequence(cmdSeq);
		return;
	}

	CmdUtils::EndCommandSequence(cmdSeq);

	// set the item list
	this->SetItemList(UIDList(newSplineItem));
}

/* CreateName
*/
PMString* NewCdlChartCmd::CreateName()
{
	PMString* string_name = new PMString(kNewCdlChartCmdStringKey);
	return string_name;
}

// End, NewCdlChartCmd.cpp.


