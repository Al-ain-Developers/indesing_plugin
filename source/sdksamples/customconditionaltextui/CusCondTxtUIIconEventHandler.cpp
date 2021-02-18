//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltextui/CusCondTxtUIIconEventHandler.cpp $
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
#include "IWidgetParent.h"
#include "IPanelControlData.h"
#include "ITreeNodeIDData.h"
#include "ICommand.h"
#include "IActiveContext.h"
#include "IWorkspace.h"

// General includes:
#include "CEventHandler.h"
#include "IconRsrcDefs.h"
#include "UIDNodeID.h"
#include "Utils.h"

// Project includes:
#include "CusCondTxtFacade.h"
#include "CusCondTxtUIID.h"
#include "CusCondTxtRezDefs.h"
#include "ICustomConditionTag.h"
#include "IConditionTag.h"
#include "ICusCondTxtFacade.h"

class CusCondTxtIconEventHandler : public CEventHandler{
public:
	CusCondTxtIconEventHandler(IPMUnknown *boss): CEventHandler(boss){};
	virtual ~CusCondTxtIconEventHandler() {}
	virtual bool16 LButtonDn(IEvent* e);

};


CREATE_PMINTERFACE(CusCondTxtIconEventHandler, kCusCondTxtUIIconEventHandlerImpl)

/* LButtonDn 
*/
bool16 CusCondTxtIconEventHandler::LButtonDn(IEvent* e)
{
	bool16 rtValue = kFalse;
	do
	{
		InterfacePtr<IControlView> controlView(this, UseDefaultIID());
		if (controlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			break;
		}

		InterfacePtr<IWidgetParent> iWidgetParent(this, UseDefaultIID());
		if (iWidgetParent == nil)
		{
			ASSERT_FAIL("IWidgetParent is invalid");
			break;
		}

		InterfacePtr<ITreeNodeIDData> holderData(iWidgetParent->GetParent(), UseDefaultIID());
		if (holderData == nil)
		{
			ASSERT_FAIL("ITreeNodeIDData is invalid");
			break;
		}

		IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
		if (context == nil)
		{
			ASSERT_FAIL("IActiveContext is invalid");
			break;
		}
		IWorkspace *ws = context->GetContextWorkspace();
		if (ws == nil)
		{
			ASSERT_FAIL("IWorkspace is invalid");
			break;
		}
		IDataBase* db = ::GetDataBase(ws);
		if (db == nil)
		{
			ASSERT_FAIL("IDataBase is invalid");
			break;
		}

		TreeNodePtr<UIDNodeID> uidNode(holderData->Get());
		if (uidNode == nil)
		{
			ASSERT_FAIL("UIDNodeID is invalid");
			break;
		}
		
		InterfacePtr<ICustomConditionTag> customConditionTag( ::GetDataBase(ws), uidNode->GetUID(), UseDefaultIID());
		if (customConditionTag == nil)
		{
			ASSERT_FAIL("CusCondTxtIconEventHandler::SetProperty: customConditionTag invalid");
			break;
		}
		
		switch(controlView->GetWidgetID().Get())
		{
		case kConditionTagIsPrintedStateWidgetId:
			if(customConditionTag->IsPrintVisible())
			{			
				controlView->SetRsrcID(kNoIcon);
			}
			else
			{
				controlView->SetRsrcID(kIsPrintedIndicatorRsrcID);
			}
			//CusCondTxtFacade::SetPrintVisibility(::GetUIDRef(customConditionTag), !customConditionTag->IsPrintVisible());
			Utils<ICusCondTxtFacade>()->SetPrintVisibility(::GetUIDRef(customConditionTag), !customConditionTag->IsPrintVisible());
			break;
			
		case kConditionTagIsIdmlStateWidgetId:
			if(customConditionTag->IsIdmlVisible())
			{			
				controlView->SetRsrcID(kNoIcon);
			}
			else
			{
				controlView->SetRsrcID(kIsIdmlIndicatorRsrcID);
			}
			//CusCondTxtFacade::SetIDMLVisibility(::GetUIDRef(customConditionTag), !customConditionTag->IsIdmlVisible());
			Utils<ICusCondTxtFacade>()->SetIDMLVisibility(::GetUIDRef(customConditionTag), !customConditionTag->IsIdmlVisible());
			break;
		}	

		controlView->SetRsrcPluginID(kCusCondTxtUIPluginID);
		controlView->Invalidate();
		
		rtValue = kTrue;

	} while (false);

	return rtValue;
}
