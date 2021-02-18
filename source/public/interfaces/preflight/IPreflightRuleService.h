//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightRuleService.h $
//  
//  Owner: Matt Phillips
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
//  The rule service is responsible for registering ownership of rules according to their
//  Rule IDs and creating rule objects corresponding to them.
//  
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPreflightRuleInfo.h"

class IPreflightRuleService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRULESERVICE };

public:
	/** Provide a list of all the rules (by their IDs) that you offer. This is used to 
		create lists of rules to present to the user, as well as to build a master table
		for use when parsing through XML rule data looking for the right rule service to
		instantiate that rule.

		@return A vector of preflight rule IDs that your service offers.
	*/
	virtual PreflightRuleIDVector GetAllRules() const = 0;

	/** Get the category a given rule belongs to. Categories are used to organize the UI and results
		by grouping together like rules. If you return an empty string the rule will not appear
		in the UI or aggregated results.

		See PreflightStringConstants for a list of the standard ones if you want your rule to
		appear alongside the InDesign native ones. But you can come up with whatever you like; 
		if you want all your rules to appear under your company name, you can certainly do that.
		The list of categories is built dynamically at startup based on the rule services 
		available.

		@param ruleID The rule you're interested in.
		@return The category string. 
	*/
	virtual PMString GetRuleCategory(const PreflightRuleID& ruleID) const = 0;

	/** Get the sorting string for a given rule. This allows rules to be ordered in a consistent
		and designed manner. This is similar to how menu items are arranged but uses a string
		similar to how many other elements are sorted in the preflight APIs.

		@return The sort string. 
	*/
	virtual PMString GetRuleSortValue(const PreflightRuleID& ruleID) const = 0;

	/**	Given the provided rule ID, create a rule boss that corresponds to it. The new
		rule should be initialized to default values. If the database passed is nil, create
		an in-memory rule; otherwise create one in the specified database.

		@param ruleID IN The ID of the rule.
		@param db IN The database in which the rule boss should be created (nil if in memory).
		@return A refcounted rule info interface on the new boss. Nil indicates failure.
	*/
	virtual IPreflightRuleInfo* CreateRule(const PreflightRuleID& ruleID, IDataBase* db) const = 0;
};