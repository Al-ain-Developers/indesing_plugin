//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ConditionalTextScriptID.h $
//  
//  Owner: Michele Stutzman
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

#ifndef __ConditionalTextScriptID__
#define __ConditionalTextScriptID__

#include "IDFactory.h"
#include "ConditionalTextID.h"


//----------------------------------------------------------------------------------------
// Scripting
//----------------------------------------------------------------------------------------
//START_IDS()
DECLARE_PMID(kScriptInfoIDSpace, kConditionTagObjectScriptElement,					kConditionalTextPrefix + 1)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kConditionTagColorPropertyScriptElement,			kConditionalTextPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteConditionTagMethodScriptElement,				kConditionalTextPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedConditionTagsPropertyScriptElement,		kConditionalTextPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kHiddenTextObjectScriptElement,					kConditionalTextPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kApplyConditionTagsMethodScriptElement,				kConditionalTextPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kConditionalTextPrefObjectScriptElement,			kConditionalTextPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kConditionalTextPrefObjectPropertyScriptElement,	kConditionalTextPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kShowConditionIndicatorsPropertyScriptElement,		kConditionalTextPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kConditionTagINXPolicies60MetadataScriptElement,	kConditionalTextPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kHiddenTextINXPolicies60MetadataScriptElement,		kConditionalTextPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kConditionTagMethodEnumScriptElement,				kConditionalTextPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kConditionTagMethodPropertyScriptElement,			kConditionalTextPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kConditionTagAppearanceEnumScriptElement,			kConditionalTextPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kConditionTagAppearancePropertyScriptElement,		kConditionalTextPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kConditionTagSetObjectScriptElement,				kConditionalTextPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kConditionIndicatorModeEnumScriptElement,			kConditionalTextPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kLoadConditionTagMethodScriptElement,				kConditionalTextPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedConditionSetPropertyScriptElement,			kConditionalTextPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedConditionSetMethodScriptElement,			kConditionalTextPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteConditionTagSetMethodScriptElement,			kConditionalTextPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kTagsConditionTagSetObjectPropertyScriptElement,	kConditionalTextPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kRedefineConditionTagSetMethodScriptElement,		kConditionalTextPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kConditionSetPairDefScriptElement,					kConditionalTextPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kConditionTagSetINXPolicies60MetadataScriptElement,kConditionalTextPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kConditionalTextPrefINXPolicies60MetadataScriptElement,kConditionalTextPrefix + 27)



//END_IDS()

//----------------------------------------------------------------------------------------
// ScripIDs
//----------------------------------------------------------------------------------------
enum ConditionalTextEnums
{
	c_ConditionTag =			'ctTg',
	c_ConditionTags =			'ctTs',
	p_ConditionTagColor =		'ctTc',
	p_AppliedConditionTags =	'apCt',
	e_ApplyConditionTags =		'Xact',
	c_HiddenText =				'hitx',
	c_HiddenTexts =				'hits',
	c_ConditionalTextOptionsPref = 'ctOp',
	p_ConditionalTextOptionsPref = 'pctO',
	p_ShowConditionIndicators =	'scdI',
	p_ConditionTagMethod =		'pCTm',
	p_ConditionTagAppearance =	'pCTa',
	en_HighlightIndicator =		'eHig',
	en_UnderlineIndicator =		'eUnl',
	en_ConditionTagMethod =		'eCTm',
	en_ConditionTagAppearance = 'eCTa',
	c_ConditionTagSet =			'ctSg',
	c_ConditionTagSets =		'ctSs',
	e_LoadConditionTags =		'ldCt',
	p_LoadConditionTagSets =	'plCs',
	p_AppliedConditionSet =		'apCS',
	p_SetConditions = 			'plTs',
	e_RedefineConditionSet =	'plRC',
	t_KeyConditionSetPairType =	'cSPt',
	en_ConditionIndicatorMode =	'eCIm',
	en_Show =					'eCIs',
	en_ShowAndPrint =			'eCIp',
	en_Hide =					'eCIh',
};

//----------------------------------------------------------------------------------------
// GUIDs
//----------------------------------------------------------------------------------------
// {0E485592-6A57-43a9-B2D8-633ED70B0BF4}
#define kConditionTag_CLSID { 0xe485592, 0x6a57, 0x43a9, { 0xb2, 0xd8, 0x63, 0x3e, 0xd7, 0xb, 0xb, 0xf4 } }
// {2A64F819-64F3-4ca9-9672-A33156AF9E44}
#define kConditionTags_CLSID { 0x2a64f819, 0x64f3, 0x4ca9, { 0x96, 0x72, 0xa3, 0x31, 0x56, 0xaf, 0x9e, 0x44 } }
// {8039D998-FA61-4242-83C5-CCF8A667A4B3}
#define kHiddenText_CLSID { 0x8039d998, 0xfa61, 0x4242, { 0x83, 0xc5, 0xcc, 0xf8, 0xa6, 0x67, 0xa4, 0xb3 } }
// {D1667251-E1CF-4dd3-9DF9-16FF0FE805AF}
#define kHiddenTexts_CLSID { 0xd1667251, 0xe1cf, 0x4dd3, { 0x9d, 0xf9, 0x16, 0xff, 0xf, 0xe8, 0x5, 0xaf } }
// {5AC60664-918C-49bd-A522-2290BCAB15E4}
#define kCondionalTextOptionsPref_CLSID { 0x5ac60664, 0x918c, 0x49bd, { 0xa5, 0x22, 0x22, 0x90, 0xbc, 0xab, 0x15, 0xe4 } }
// {b04b8670-ed1f-4df0-9e04-f5df88e9fc35}
#define kConditionTagSet_CLSID { 0xb04b8670, 0xed1f, 0x4df0, { 0x9e, 0x04, 0xf5, 0xdf, 0x88, 0xe9, 0xfc, 0x35 } }
// {f38b921e-24fe-4c0f-92ab-5712ba317e36}
#define kConditionTagSets_CLSID { 0xf38b921e, 0x24fe, 0x4c0f, { 0x92, 0xab, 0x57, 0x12, 0xba, 0x31, 0x7e, 0x36 } }



#endif //  __ConditionalTextScriptID__
