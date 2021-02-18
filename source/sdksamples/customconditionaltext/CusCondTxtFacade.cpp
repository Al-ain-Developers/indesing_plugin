 //========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtFacade.cpp $
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
#include "IDocument.h"
#include "IWorkspace.h"
#include "IConditionalTextFacade.h"
#include "IConditionTagList.h"
#include "IBoolData.h"

// General includes:
#include "CmdUtils.h"
#include "UIDList.h"

// Project includes:
#include "CusCondTxtID.h"
#include "ICustomConditionTag.h"
#include "CusCondTxtFacade.h"


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
 */
CREATE_PMINTERFACE(CusCondTxtFacade, kCusCondTxtFacadeImpl)


/*
 */
CusCondTxtFacade::CusCondTxtFacade(IPMUnknown* boss) : CPMUnknown<ICusCondTxtFacade>(boss)
{
}

void CusCondTxtFacade::TurnOnConditionVisibility(IDocument* document)
{
	ASSERT(document);
	InterfacePtr<IWorkspace> docWorkspace(document->GetDocWorkSpace(), UseDefaultIID());	
	IDataBase* database = ::GetDataBase(docWorkspace);
	
	InterfacePtr<IConditionTagList> conditionList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(database));
	if(conditionList == nil)
		return;
						
	for (int32 i = 0; i < conditionList->GetCount(); i++) 
	{
		UIDRef conditionRef(database, conditionList->GetNthCondition(i));
		InterfacePtr<IBoolData> iTurnOffState(conditionRef, IID_ICUSCONDTURNOFFSTATE);
		ASSERT(iTurnOffState);	
		//true, Visiblity was turned off in TurnOffConditionVisibility()
		if(iTurnOffState->Get())
		{
			iTurnOffState->Set(kFalse);
			Utils<Facade::IConditionalTextFacade>()->SetConditionVisibleState(conditionRef, kTrue);
		}
	}
}
		
void CusCondTxtFacade::TurnOffConditionVisibility(IDocument* document, CustomConditionAttr cusCondAttr)
{
	ASSERT(document);
	InterfacePtr<IWorkspace> docWorkspace(document->GetDocWorkSpace(), UseDefaultIID());	
	IDataBase* database = ::GetDataBase(docWorkspace);
	
	InterfacePtr<IConditionTagList> conditionList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(database));
	if(conditionList == nil)
		return;
						
	for (int32 i = 0; i < conditionList->GetCount(); i++) 
	{
		UIDRef conditionRef(database, conditionList->GetNthCondition(i));
		InterfacePtr<ICustomConditionTag> cusCondTag(conditionRef, UseDefaultIID());		
		InterfacePtr<IBoolData> iTurnOffState(conditionRef, IID_ICUSCONDTURNOFFSTATE);
		ASSERT(iTurnOffState);
		iTurnOffState->Set(kFalse);
		
		bool16 cusCondVisible = kTrue;

		if(cusCondAttr == kPrintVisibility)
		{
			cusCondVisible = cusCondTag->IsPrintVisible();
		}
		else if(cusCondAttr == kIdmlVisibility)
		{
			cusCondVisible = cusCondTag->IsIdmlVisible();
		}
		
		bool16 visibleState;
		Utils<Facade::IConditionalTextFacade>()->GetConditionVisibleState(conditionRef, visibleState);
		if(cusCondVisible == kFalse && visibleState == kTrue)
		{
			Utils<Facade::IConditionalTextFacade>()->SetConditionVisibleState(conditionRef, kFalse);
			//Visiblity will be turned on by checking this value in TurnOnConditionVisibility()
			iTurnOffState->Set(kTrue);
		}
	}	
}

ErrorCode CusCondTxtFacade::SetPrintVisibility(const UIDRef& item, bool16 value)
{
	return SetCustomConditionData(item, kPrintVisibility, value);
}

ErrorCode CusCondTxtFacade::SetIDMLVisibility(const UIDRef& item, bool16 value)
{
	return SetCustomConditionData(item, kIdmlVisibility, value);
}
		
ErrorCode CusCondTxtFacade::SetCustomConditionData(const UIDRef& item, CustomConditionAttr cusCondAttr, bool16 value)
{
	ErrorCode result = kFailure;
	InterfacePtr<ICustomConditionTag> cusCondTag(item, UseDefaultIID());
	ASSERT(cusCondTag);
	if(!cusCondTag)
		return result;
		
	InterfacePtr<ICommand> condChangeCmd(CmdUtils::CreateCommand(kCusCondTxtChangeCmdBoss));
	if (condChangeCmd == nil)
	{
		ASSERT_FAIL("CusCondTxtFacade::SetProperty: condChangeCmd invalid");
		return result;
	}

	condChangeCmd->SetItemList(UIDList(item));

	InterfacePtr<IBoolData> printVisible(condChangeCmd, IID_ICUSCONDTXTPRINTVISIBLE);
	InterfacePtr<IBoolData> idmlVisible(condChangeCmd, IID_ICUSCONDTXTIDMLVISIBLE);
	
	if(cusCondAttr == kPrintVisibility)
	{
		printVisible->Set(value);
		idmlVisible->Set(cusCondTag->IsIdmlVisible());
	}
	else if(cusCondAttr == kIdmlVisibility)
	{
		printVisible->Set(cusCondTag->IsPrintVisible());
		idmlVisible->Set(value);
	}
	
	return CmdUtils::ProcessCommand(condChangeCmd);
}

