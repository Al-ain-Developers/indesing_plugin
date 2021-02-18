//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightRuleManager.h $
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
//  This is the main entry point into the preflight architecture.
//  
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"

#include "IPreflightRuleInfo.h"

class IPreflightRuleService;

/** This interface sits on the session and provides "manager level" access to the database
	that it maintains about the rules that it knows about (via rule services). Normally you
	get one of these via

		InterfacePtr<IPreflightRuleManager> iRuleMgr(Utils<IPreflightUtils>()->QueryRuleManager());

	The idea is that preflight rule services register all the rules they know about. This 
	manager collates this information and provides the API to access rules as if they are
	derived from a "super service." (Ie, you don't have to talk to the services directly.)
*/

class IPreflightRuleManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRULEMANAGER };

public:
	// These are called by the PreflightManager.
	virtual void Startup() = 0;
	virtual void Shutdown() = 0;

	/**	Register a rule service that failed during startup. Ror example,
		all script-based rules failed during startup since they require the scripting
		serivces and scripting info database to be completed first. This does not
		happen until the app completes all startup tasks.
		The calling client call this method to finish registering the rules.
		@param providerClassID is the service class ID for this rule service.
		@param ruleID is the missing rule ID to register. If the ruleID spcified is a null string, then
				all rules associated with the specified service should be register.
		@return kTrue if we successfully registered missing rule(s).
	*/
	virtual bool16 RegisterMissingRuleService (const ClassID& providerClassID, const PreflightRuleID& ruleID = PreflightRuleID ()) = 0;

	/** @return the list of all rules from all services.
	*/
	virtual PreflightRuleIDVector GetAllRuleIDs() const = 0;

	/** Given a rule ID, returns the service responsible for it.
		@param ruleID is the specified rule ID.
		@return the preflight rule service associated with the specified ruleID
	*/
	virtual IPreflightRuleService* QueryRuleService(const PreflightRuleID& ruleID) const = 0;

	/** Given a rule ID, create a rule boss in the specified database (nil for in-memory).
		@param ruleID is the specified rule ID.
		@param db is the database in which to create the rule
		@return the preflight rule for the specified ruleID
	*/
	virtual IPreflightRuleInfo* CreateRule(PreflightRuleID ruleID, IDataBase* db) const = 0;

	/** Get a list of all rule categories. Note that rules declare their own categories; this is 
		simply the union of all the returned strings.
		Also note: Rules that do not wish to appear in the UI return an empty category string.
		This method does not return an empty category string in the list of categories.

		@param allCategories OUT Receives the vector of strings. It's cleared before adding the entries.
	*/
	virtual void GetAllCategories(K2Vector<PMString>& allCategories) const = 0;

	/** Get a list of all the rule IDs declared under a given category.
		Note: Rule categories are the domain of Rule UI, which may not be available in a server environment
		or if the preflight UI plugin isn't present. Thus you should only assume that categories are valid
		for UI purposes.

		@param category IN The category you're interested in. Pass an empty string if you want to get
			a list of all the rules that returned an empty category string, ie they do not wish to appear
			in the UI.
		@param rules OUT Recevies the vector of rules. It's cleared before adding the entries.
	*/
	virtual void GetRulesInCategory(const PMString& category, PreflightRuleIDVector& rules) const = 0;

	/** Get the category a rule belongs to.
		Note: Rule categories are the domain of Rule UI, which may not be available in a server environment
		or if the preflight UI plugin isn't present. Thus you should only assume that categories are valid
		for UI purposes.

		@param ruleID IN The rule you're interested in.
		@return The category the rule belongs to.
	*/
	virtual PMString GetRuleCategory(const PreflightRuleID& ruleID) const = 0;

};


