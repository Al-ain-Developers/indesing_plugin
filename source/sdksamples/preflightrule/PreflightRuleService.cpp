//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightrule/PreflightRuleService.cpp $
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

#include "IPreflightProfile.h"
#include "IPreflightRuleData.h"
#include "IPreflightRuleService.h"
#include "IPreflightRuleUtilities.h"
#include "IPreflightRuleVisitor.h"

#include "CPMUnknown.h"
#include "IPMStream.h"
#include "CreateObject.h"

#include "SDKRuleTable.h"
#include "PreflightRuleConsts.h"

class PreflightRuleService : CPMUnknown<IPreflightRuleService>
{
public:
    PreflightRuleService(IPMUnknown* iBoss);

	/** See IPreflightRuleService::GetAllRules
	*/
    virtual PreflightRuleIDVector GetAllRules() const;

	/** See IPreflightRuleService::CreateRule
	*/
	virtual IPreflightRuleInfo* CreateRule(const PreflightRuleID& ruleID, IDataBase* db) const;

	/** See IPreflightRuleService::GetRuleCategory
	*/
	virtual PMString GetRuleCategory(const PreflightRuleID& ruleID) const;

	/** See IPreflightRuleService::GetRuleSortValue
	*/
	virtual PMString GetRuleSortValue(const PreflightRuleID& ruleID) const;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PreflightRuleService, kPreflightRuleServiceImpl);

PreflightRuleService::PreflightRuleService(IPMUnknown* iBoss)	: CPMUnknown<IPreflightRuleService>(iBoss)
{
}

PreflightRuleIDVector PreflightRuleService::GetAllRules() const
{
	// Note: We're typically called only once per session for this list so there's no
	// sense in trying to cache the result..

	PreflightRuleIDVector rules;

	for(int32 n = 0; n < kNumSDKRules; n++)
	{
		rules.push_back(PreflightRuleID(kSDKRules[n].fStringID));
	}

	return rules;
}

IPreflightRuleInfo* PreflightRuleService::CreateRule(const PreflightRuleID& ruleID, IDataBase* db) const
{
	PMString desc, plugin;
	ClassID bossID = 0;

	for(int32 n = 0; n < kNumSDKRules; n++)
	{
		if (ruleID == PreflightRuleID(kSDKRules[n].fStringID))
		{
			desc = kSDKRules[n].fDesc;
			bossID = kSDKRules[n].fBossID;
			break;
		}
	}

	if (bossID == 0)
	{
		ASSERT_FAIL("PreflightRuleService::CreateRule: This rule ID isn't one I recognize.");
		return nil;
	}

	IPreflightRuleInfo* iRule = (IPreflightRuleInfo*)CreateObject(db, bossID, IID_IPREFLIGHTRULEINFO);
	if (!iRule)
	{
		ASSERT_FAIL("Unable to create SDK rule boss. OK to continue but something's amiss in preflight.");
		return iRule;
	}

	iRule->SetRuleID(ruleID);

	plugin = "InDesign SDK Rule Set";

	iRule->SetRuleDescription(desc);
	iRule->SetPluginDescription(plugin);

	InterfacePtr<IPreflightRuleVisitor> ruleVisitor(iRule, UseDefaultIID());
	if(ruleVisitor)
	{
		ruleVisitor->UpdateRuleData();
	}
	
	return iRule;
}

PMString PreflightRuleService::GetRuleCategory(const PreflightRuleID& ruleID) const
{
	return PMString(kCategorySDKKey);
}

PMString PreflightRuleService::GetRuleSortValue(const PreflightRuleID& ruleID) const
{
	return PMString("");
}
