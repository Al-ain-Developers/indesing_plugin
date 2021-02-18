//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstUtils.cpp $
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

// Interface includes
#include "ICommand.h"
#include "IIntData.h"

// General includes
#include "CmdUtils.h"

// PstLst Includes
#include "IPstLstData.h"
#include "IPstLstUIDList.h"
#include "PstLstUtils.h"
#include "PstLstID.h"


/*	PstLstUtils::DoCreateNewData
*/
ErrorCode PstLstUtils::DoCreateNewData(const UIDList& pageItemListToAddTo, const WideString& name, UIDList& newItemsList)
{
	ErrorCode result = kPstLstInternalError;
	do
	{
		UIDList nonConstPageItemListToAddTo(pageItemListToAddTo);
		// check input parameters
		if (newItemsList.GetDataBase() == nil || nonConstPageItemListToAddTo.GetDataBase() == nil)
		{
			ASSERT_FAIL("one of the input UIDLists does not have a valid database associated with it");
			break;
		}
		// PREREQUISITE: newItemsList should have the same database as itemListToAddTo
		if (newItemsList.GetDataBase() != nonConstPageItemListToAddTo.GetDataBase())
		{
			ASSERT_FAIL("the two UIDList parameters have different databases!");
			break;
		}
		
		// clear the item list we are going to pass back
		newItemsList.Clear();

		RemoveNonPstLstItems(nonConstPageItemListToAddTo);

		// If there are no items in the incoming list, then don't do anything.
		if (nonConstPageItemListToAddTo.Length() == 0)
		{
			TRACEFLOW(kPstLstPluginName, "PstLstUtils::DoCreateNewData: No valid page items to process\n");
			result = kSuccess;
			break;
		}

		// item list and settings information are ok, create the command.
		InterfacePtr<ICommand> iPstlstCommand(CmdUtils::CreateCommand(kPstLstNewDataCmdBoss));
		if (iPstlstCommand == nil)
		{
			// For some reason we couldn't get our PstLstNewDataCmd command pointer, so assert and
			// issue a user warning and leave:
			ASSERT_FAIL("PstLstNewDataCmd invalid");
			break;
		}

		iPstlstCommand->SetItemList(nonConstPageItemListToAddTo);
		InterfacePtr<IPstLstData> iCmdData(iPstlstCommand, UseDefaultIID());		
		if (iCmdData == nil)
		{
			// For some reason we couldn't get our IPstLstData pointer, so assert and
			// issue a user warning and leave:
			ASSERT_FAIL("IPstLstData invalid");
			break;
		}
		
		// updating the attributes of the label
		iCmdData->SetName(name);

		// Finally, the command is processed:
		result = CmdUtils::ProcessCommand(iPstlstCommand);

		if (result == kSuccess)
		{
			// get the resulting item list from the command
			// so we can pass it back
			UIDList resultingItemList = iPstlstCommand->GetItemListReference();
			int32 n = resultingItemList.Length();
			for (int32 i = 0 ; i < n ; i++)
			{
				newItemsList.Append(resultingItemList[i]);
			}
		}
	}
	while (kFalse);
	return result;
}


/* DoGetName
*/
ErrorCode PstLstUtils::DoGetName(const UIDRef& pstLstItemRef, WideString& name)
{
	ErrorCode result = kPstLstInternalError;
	do
	{
		// get the IPstLstData
		InterfacePtr<IPstLstData> pstLstData(pstLstItemRef, UseDefaultIID());
		if (pstLstData == nil)
		{
			ASSERT_FAIL("could not query IPstLstData");
			break;
		}
		// get the name
		const WideString pstLstDataName = pstLstData->GetName();
		name = pstLstDataName;
		result = kSuccess;

	} while (false);
	return result;
}

/* DoSetName
*/
ErrorCode PstLstUtils::DoSetName(UIDList& pstLstDataList, const WideString& name)
{
	ErrorCode result = kPstLstInternalError;
	do
	{
		// check input parameters
		if (pstLstDataList.GetDataBase() == nil)
		{
			ASSERT_FAIL("pstLstDataList does not have a valid database associated with it");
			break;
		}
		
		
		// If there are no items in the incoming list, then don't do anything.
		if (pstLstDataList.Length() == 0)
		{
			TRACEFLOW(kPstLstPluginName, "PstLstUtils::DoSetName: No valid page items to apply kPstLstModifyDataCmdBoss\n");
			result = kSuccess;
			break;
		}

		// create the command
		InterfacePtr<ICommand> modifyDataCmd(CmdUtils::CreateCommand(kPstLstModifyDataCmdBoss));
		if (modifyDataCmd == nil)
		{
			ASSERT_FAIL("kPstLstModifyDataCmdBoss invalid");
			break;
		}
		// set the items to modify in the command's item list
		modifyDataCmd->SetItemList(pstLstDataList);
		
		// set the command data
		InterfacePtr<IPstLstData> cmdData(modifyDataCmd, UseDefaultIID());		
		if (cmdData == nil)
		{
			ASSERT_FAIL("IPstLstData invalid");
			break;
		}
	
		// update the attributes of the label - in this case, the name
		cmdData->SetName(name);

		// Finally, the command is processed:
		result = CmdUtils::ProcessCommand(modifyDataCmd);
	} while (false);
	return result;

}


void PstLstUtils::RemoveNonPstLstItems(UIDList& pageItemList)
{
	// remove items (from the end) that do not have IPstLstUIDList
	// IPstLstUIDList is only aggregated onto kDrawablePageItemBoss.
	int32 item = pageItemList.Length();
	while (item-- > 0)
	{
		InterfacePtr<IPstLstUIDList> iUIDList(pageItemList.GetRef(item), UseDefaultIID());
		if (iUIDList == nil)
		{
			pageItemList.Remove(item);
		}
	}
}

/* AllPstLstAreEmpty
*/
bool16 PstLstUtils::AllPstLstAreEmpty(const UIDList& itemList)
{
	bool16 result = true;
	const int32 listLength = itemList.Length();
	for (int32 i = 0; i < listLength; i++)
	{
		InterfacePtr<IPstLstUIDList> iPstLstUIDList(itemList.GetRef(i), UseDefaultIID());
		if (iPstLstUIDList != nil)
		{
			if (iPstLstUIDList->GetUIDList()->Length() != 0)
			{
				result = false;
				break; // for-loop
			}
		}
	}
	return result;
}



// End, PstLstUtils.cpp.
