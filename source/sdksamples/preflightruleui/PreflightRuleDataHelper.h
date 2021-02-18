//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightruleui/PreflightRuleDataHelper.h $
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

#pragma once


class IPreflightRuleData;

/** Helper class for manipulating the rule data
*/
class PreflightRuleDataHelper
{
public:
	
	/** Allow font to be used
		@param ruleRef IN The object that caused the change
		@param fontName IN The font name
	*/
	static void AllowFont(IPreflightRuleData* iRuleData, const WideString& fontName);
	
	/** Disallow font to be used
		@param ruleRef IN The object that caused the change
		@param fontName IN The font name
	*/
	static void DisallowFont(IPreflightRuleData* iRuleData, const WideString& fontName);	
	
	/** Font is allowed or not
		@param ruleRef IN Preflight rule data object 
		@param fontName IN The font name
		@return allowed or not
	*/
	static bool16 IsAllowed(IPreflightRuleData*, const WideString& fontName);
	
	/** Notify "Preflight Profiles" dialog that rule data was changed
		@param changeBy IN The object that caused the change 
	*/
	static void NotifyRuleDataChanged(IPMUnknown* changeBy);
};

