//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightrule/SDKRuleTable.h $
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
//  
//  An array giving the details of the native rules. We need at least the boss and the
//  rule ID in this table because we need a lookup capability. And might as well throw
//  in the description since it's all kinda parallel.
//  
//  In addition to here you need the following for each rule:
//  
//========================================================================================

#pragma once

#include "IPreflightRuleData.h"
#include "PreflightRuleID.h"

typedef struct
{
    ClassID fBossID;
    const char* fStringID;
    const char* fDesc;
} PreflightRuleInfo;

static const char* const kSDKFontRuleID = "ADBE_SDK_Font_Rule";
static const char* const kSDKBlackOverprintRuleID = "ADBE_SDK_BlackOverprint_Rule";

static const PreflightRuleInfo kSDKRules[] =
{
    { kPreflightDisallowFontRuleBoss,		kSDKFontRuleID,					kSDKFontRuleDescriptionKey},
    { kPreflightBlackOverprintRuleBoss,		kSDKBlackOverprintRuleID,		kSDKBlackOverprintRuleDescKey}
};

const int32 kNumSDKRules = sizeof(kSDKRules) / sizeof(*kSDKRules);
											