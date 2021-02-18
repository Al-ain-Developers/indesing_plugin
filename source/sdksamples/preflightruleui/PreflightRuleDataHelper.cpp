//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightruleui/PreflightRuleDataHelper.cpp $
//  
//  Owner: InDesign Developer Technologies
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

// General includes
#include "CAlert.h"
#include "CObserver.h"

//Interface includes
#include "IPreflightRuleData.h"
#include "ISubject.h"
#include "IWidgetParent.h"
#include "IStringListData.h"
#include "IPreflightRuleUI.h"
#include "IDialogController.h"
#include "IPreflightProfileRules.h"
#include "IWidgetUtils.h"

// Implem includes
#include "PreflightRuleUIID.h"
#include "PreflightRuleConsts.h"
#include "PreflightRuleDataHelper.h"
#include "SDKRuleTable.h"

void PreflightRuleDataHelper::AllowFont(IPreflightRuleData* ruleData, const WideString& fontName)
{
	do {
		if(PreflightRuleDataHelper::IsAllowed(ruleData, fontName))
			break;
			
		if(ruleData == nil)
		{
			ASSERT_FAIL("Miss IPreflightRuleData interface");
			break;
		}
		
		bool exist = false;
		ScriptData data;
		ruleData->GetData (kSDKFontRuleParameter, ScriptData(), data, &exist);
		if(!exist || data.GetType() != ScriptData::s_list)
			break;
			
		ScriptListData scrListData;
		data.GetList(scrListData);
		WideString disallowedName;

		for(ScriptListData::iterator f = scrListData.begin(), l = scrListData.end(); f != l; ++f)
		{			
			f->GetWideString(disallowedName);
			if(fontName == disallowedName)
			{
				scrListData.erase(f);
				data.SetList(scrListData);
				ruleData->SetData(kSDKFontRuleParameter, data);
				break;
			}
		}
	} while(false);
}

void PreflightRuleDataHelper::DisallowFont(IPreflightRuleData* ruleData, const WideString& fontName)
{
	do {
		if(!PreflightRuleDataHelper::IsAllowed(ruleData, fontName))
			break;
			
		if(ruleData == nil)
		{
			ASSERT_FAIL("Miss IPreflightRuleData interface");
			break;
		}
		
		bool exist = false;
		ScriptData data;
		ruleData->GetData (kSDKFontRuleParameter, ScriptData(), data, &exist);
		if(!exist || data.GetType() != ScriptData::s_list)
			break;
			
		ScriptListData scrListData;
		data.GetList(scrListData);
		
		ScriptData tmpData(fontName);
		scrListData.push_back(tmpData);
		data.SetList(scrListData);

		ruleData->SetData(kSDKFontRuleParameter, data);
	} while(false);
}

bool16 PreflightRuleDataHelper::IsAllowed(IPreflightRuleData* ruleData, const WideString& fontName)
{
	do {	
		if(ruleData == nil)
		{
			ASSERT_FAIL("Miss IPreflightRuleData interface");
			break;
		}
		
		bool exist = false;
		ScriptData data;
		ruleData->GetData (kSDKFontRuleParameter, ScriptData(), data, &exist);
		if(!exist || data.GetType() != ScriptData::s_list)
			break;
			
		ScriptListData scrListData;
		data.GetList(scrListData);
		WideString disallowedName;
		for(int32 i = 0; i < scrListData.size(); ++i)
		{			
			scrListData[i].GetWideString(disallowedName);
			if(fontName == disallowedName)
				return kFalse;
		}
	} while(false);

	return kTrue;
}

void PreflightRuleDataHelper::NotifyRuleDataChanged(IPMUnknown* changeBy)
{
	do {
		InterfacePtr<IWidgetParent> iWidgetParent(changeBy, UseDefaultIID());
		ASSERT(iWidgetParent);
		if(!iWidgetParent)
		{
			break;
		}

		//Get the IDialogController interface of "Preflight Profiles" dialog
		InterfacePtr<IDialogController>	iDlg (static_cast<IDialogController*> (iWidgetParent->QueryParentFor (IID_IDIALOGCONTROLLER)));
		if(!iDlg)
		{
			break;
		}
		
		InterfacePtr<ISubject> iDlgSubject(iDlg, UseDefaultIID());
		if (iDlgSubject)
		{
			InterfacePtr<IControlView>	iDataUIView (changeBy, UseDefaultIID ());
			if (iDataUIView->GetWidgetID () != kPreflightRuleUIDataPanelWidgetID)
			{
				iDataUIView.reset (static_cast<IControlView*>(Utils<IWidgetUtils> ()->QueryRelatedWidget (changeBy, kPreflightRuleUIDataPanelWidgetID, IID_ICONTROLVIEW)));
			}
			ASSERT (iDataUIView != nil);
			iDlgSubject->Change (kProfileCustomRuleDataChangeMessage, IID_IPROFILEDLGUTILS, (void*)iDataUIView);
		}
		
	} while(false);	
}

