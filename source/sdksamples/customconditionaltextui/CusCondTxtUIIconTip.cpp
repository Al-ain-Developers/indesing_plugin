//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltextui/CusCondTxtUIIconTip.cpp $
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
//  
//  Contains the main implementation of the ITip interface for widgets
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IActiveContext.h"
#include "IControlView.h"
#include "AbstractTip.h"
#include "IWidgetParent.h"
#include "IDataBase.h"
#include "IWorkspace.h"
#include "UIDNodeID.h"
// Project includes:
#include "CusCondTxtUIID.h"
#include "ITreeNodeIDData.h"
#include "ICustomConditionTag.h"

class CusCondTxtIconTip  : public AbstractTip
{			
public:
	CusCondTxtIconTip( IPMUnknown *boss );
	virtual ~CusCondTxtIconTip();

	virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

CREATE_PMINTERFACE( CusCondTxtIconTip, kCusCondTxtUIIconTipImpl )


/* Constructor
*/
CusCondTxtIconTip::CusCondTxtIconTip(IPMUnknown *boss):
	AbstractTip(boss)
{
}

/* Destructor
*/
CusCondTxtIconTip::~CusCondTxtIconTip()
{
}

/* GetTipText 
*/
PMString CusCondTxtIconTip::GetTipText(const PMPoint& mouseLocation)
{
	PMString activeTip = "";
	do
	{	
		InterfacePtr<IControlView> controlView(this, UseDefaultIID());
		if (controlView == nil)
		{
			ASSERT_FAIL("IControlView is invalid");
			return "";
		}
		
		WidgetID widgetID = controlView->GetWidgetID();
		if (widgetID == kInvalidWidgetID)
		{
			ASSERT_FAIL("WidgetID is invalid");
			return "";
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

		TreeNodePtr<UIDNodeID>    uidNode(holderData->Get());
		if (uidNode == nil)
		{
			ASSERT_FAIL("UIDNodeID is invalid");
			break;
		}
		
		InterfacePtr<ICustomConditionTag> customConditionTag( ::GetDataBase(ws), uidNode->GetUID(), UseDefaultIID());		
		switch(widgetID.Get())
		{
		case kConditionTagIsPrintedStateWidgetId:
			if(customConditionTag->IsPrintVisible())
			{
				activeTip = kCusCondTxtUIPrintedIconVisibleStringKey;
			}
			else
			{
				activeTip = kCusCondTxtUIPrintedIconInvisibleStringKey;
			}
			break;
			
		case kConditionTagIsIdmlStateWidgetId:
			if(customConditionTag->IsIdmlVisible())
			{
				activeTip = kCusCondTxtUIIdmlIconVisibleStringKey;
			}
			else
			{
				activeTip = kCusCondTxtUIIdmlIconInvisibleStringKey;
			}	
			break;
			
		default:
			activeTip = "";
		}			

	} while (false);

	return activeTip;
} 

