//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUIDlgController.cpp $
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
#include "IActiveContext.h"
#include "IIntData.h"
#include "ISelectionUtils.h"
#include "IUIDListData.h"

// API includes:
#include "CAlert.h" // For Alert
#include "CDialogController.h"
#include "K2Vector.tpp"

// Project includes:
#include "PstLstUIID.h"
#include "PstLstUIUtils.h" // for the contants
#include "IPstLstSuite.h"
#include "IPstLstData.h"

#if __INTEL_COMPILER || MACINTOSH
#include "K2Vector.tpp"
#endif

/** 
	Implements the dialog that is used for both creating and modifying a string associated with a page item.
  
  	@ingroup persistentlist
	
*/
class PstLstUIDlgController : public CDialogController
{
public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PstLstUIDlgController(IPMUnknown* boss);

		/**
			The dialog used in this plug-in is shared between Modify and New operations, so in the
			InitializeFields, the dialog needs to be initialized with proper mode.
			@param context See IDialogController::InitializeDialogFields
		*/
		void InitializeDialogFields(IActiveContext* context) ;

		/**
			Add the string to the list, or edit the existing string.

			@param context See IDialogController::ApplyDialogFields
			@param widgetId identifies the widget that caused this method to by invoked (the 'OK' button.)
		*/
		void ApplyDialogFields(IActiveContext* context, const WidgetID& widgetId);
		
private:
	int32 fMode;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstUIDlgController, kPstLstUIDlgControllerImpl)

/*	PstLstUISelectionObserver Constructor
*/
PstLstUIDlgController::PstLstUIDlgController(IPMUnknown* boss)
: CDialogController(boss)
, fMode(kPstLstNew)
{
}

/*	PstLstUIDlgController::InitializeDialogFields
*/
void PstLstUIDlgController::InitializeDialogFields(IActiveContext* context) 
{

	// We'll use a do-while(0) loop so we can break out if we have an
	// invalid pointer:	
	do
	{
		if (!context)
		{
			ASSERT_FAIL("PstLstUIDialogController::InitializeDialogFields -- IActiveContext* is nil");
			break;
		}
		CDialogController::InitializeDialogFields(context);
		
		// Determine if the dialog is for new or modify
		InterfacePtr<IIntData> iMode(this, UseDefaultIID());
		if (iMode == nil)
		{
			ASSERT_FAIL("IIntData ptr is nil, can't set dialog mode");
			break;
		}
		fMode = iMode->Get();

		SetTextControlData(kPstLstUIEditBoxWidgetID, "");

		if (fMode == kPstLstModify)
		{
            InterfacePtr<IUIDListData> editList(this, IID_IUIDLISTDATA);
			UIDList selectUIDList (*(editList->GetRef()));
			InterfacePtr<IPstLstData> pstLstData(editList->GetRef()->GetRef(0), UseDefaultIID());
			if (pstLstData)
			{
				// get the name
				const WideString pstLstDataName = pstLstData->GetName();
				PMString textData(pstLstDataName);
				textData.SetTranslatable(kFalse);
				SetTextControlData(kPstLstUIEditBoxWidgetID, textData);
			}
		}
	} while (kFalse); // Only do this once.

}

/*	PstLstUIDlgController::ApplyDialogFields
*/
void PstLstUIDlgController::ApplyDialogFields(IActiveContext *context, const WidgetID& widgetId)
{

	// We'll use a do-while(0) loop so that we may exit gracefully if there is a pointer
	// that is invalid:
	// There are 2 stages to this action, the first involves removing all the items that don't
	// support the IPstLstData interface from the list of selected items. The second involves updating
	// all the page item IPstLstData interfaces to reflect the new values

	do
	{
		// Retrieve the values set in the dialog
		PMString theData = GetTextControlData(kPstLstUIEditBoxWidgetID);
        InterfacePtr<IUIDListData> editList(this, IID_IUIDLISTDATA);
		UIDList selectUIDList (*(editList->GetRef()));

		if (fMode == kPstLstNew)
		{
			InterfacePtr<ICommand> iPstlstCommand(CmdUtils::CreateCommand(kPstLstNewDataCmdBoss));
			if (iPstlstCommand == nil)
			{
				ASSERT_FAIL("PstLstNewDataCmd invalid");
				break;
			}

			iPstlstCommand->SetItemList(selectUIDList);
			InterfacePtr<IPstLstData> iCmdData(iPstlstCommand, UseDefaultIID());
			if (iCmdData == nil)
			{
				// For some reason we couldn't get our IPstLstData pointer, so assert and
				// issue a user warning and leave:
				ASSERT_FAIL("IPstLstData invalid");
				break;
			}

			// updating the attributes of the label
			iCmdData->SetName(WideString(theData));

			// Finally, the command is processed:
			ErrorCode	err = CmdUtils::ProcessCommand(iPstlstCommand);
			if (err != kSuccess)
				CAlert::WarningAlert(kPstLstUINewCmdFailedKey);

		}
		else if (fMode == kPstLstModify)
		{

			// create the command
			InterfacePtr<ICommand> modifyDataCmd(CmdUtils::CreateCommand(kPstLstModifyDataCmdBoss));
			if (modifyDataCmd == nil)
			{
				ASSERT_FAIL("kPstLstModifyDataCmdBoss invalid");
				break;
			}
			// set the items to modify in the command's item list
			modifyDataCmd->SetItemList(selectUIDList);
			
			// set the command data
			InterfacePtr<IPstLstData> cmdData(modifyDataCmd, UseDefaultIID());		
			if (cmdData == nil)
			{
				ASSERT_FAIL("IPstLstData invalid");
				break;
			}
		
			// update the attributes of the label - in this case, the name
			cmdData->SetName(WideString(theData));

			// Finally, the command is processed:
			ErrorCode err = CmdUtils::ProcessCommand(modifyDataCmd);
			if (err != kSuccess)
				CAlert::WarningAlert(kPstLstUIModifyCmdFailedKey);
		}
		
	} while (kFalse); // Only do this once.

}



