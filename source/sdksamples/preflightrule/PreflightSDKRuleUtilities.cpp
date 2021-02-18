//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightrule/PreflightSDKRuleUtilities.cpp $
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
#include "IPreflightRuleUtilities.h"
#include "IPreflightRuleData.h"
#include "CPMUnknown.h"
#include "CreateObject.h"
#include "PreflightRuleDataHelper.h"
#include "PreflightRuleConsts.h"
#include "PreflightRuleID.h"

class PreflightSDKRuleUtilities : CPMUnknown<IPreflightRuleUtilities>
{
private:

public:
    PreflightSDKRuleUtilities(IPMUnknown* iBoss);

	/** See IPreflightRuleUtilities::DuplicateRule
	*/
    virtual IPreflightRuleInfo* DuplicateRule(IDataBase* iDB) const;

	/** See IPreflightRuleUtilities::DeletingRule
	*/
    virtual void DeletingRule();

	/** See IPreflightRuleUtilities::IsEqual
	*/
    virtual bool IsEqual(const IPreflightRuleInfo* iOther) const;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PreflightSDKRuleUtilities, kPreflightSDKRuleUtilitiesImpl);

PreflightSDKRuleUtilities::PreflightSDKRuleUtilities(IPMUnknown* iBoss) : CPMUnknown<IPreflightRuleUtilities>(iBoss) 
{
}

IPreflightRuleInfo* PreflightSDKRuleUtilities::DuplicateRule(IDataBase* iDB) const
{
	IPreflightRuleInfo* iCopy = (IPreflightRuleInfo*)::CreateObject(iDB, ::GetClass(this), IID_IPREFLIGHTRULEINFO);
	InterfacePtr<IPreflightRuleInfo> iSrc(this, UseDefaultIID());

	InterfacePtr<IPreflightRuleData> iCopyData(iCopy, UseDefaultIID());
	InterfacePtr<IPreflightRuleData> iSrcData(iSrc, UseDefaultIID());

	iCopy->CopyFrom(iSrc);
	iCopyData->CopyFrom(iSrcData);

	return iCopy;
}

void PreflightSDKRuleUtilities::DeletingRule()
{
}

bool PreflightSDKRuleUtilities::IsEqual(const IPreflightRuleInfo* iOther) const
{
	InterfacePtr<const IPreflightRuleInfo> iMyInfo(this, UseDefaultIID());
	if (!iOther || !iMyInfo || !iMyInfo->IsEqual(iOther)) 
		return kFalse;

	InterfacePtr<const IPreflightRuleData> iMyData(this, UseDefaultIID());
	InterfacePtr<const IPreflightRuleData> iOtherData(iOther, UseDefaultIID());
	if (!iMyData || !iOtherData || !iMyData->IsEqual(iOtherData)) 
		return kFalse;

	return kTrue;
}

