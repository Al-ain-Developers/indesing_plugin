//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightProfileRules.h $
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
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"

#include "IPreflightRuleInfo.h"

/** Maintains a list of rules in a profile. Profiles can be in a database or not, so this
	interface maintains an array of refcounted IPreflightRuleInfo interfaces if it's an in-memory 
	profile, or a UIDList of rule bosses if it's in a database.
*/
class IPreflightProfileRules : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTPROFILERULES };

public:
	/** Get the number of rules in the list.
		@return The number of rules in the list.
	*/
	virtual int32 GetRuleCount() const = 0;

	/** Get one of the rules in the list.
		@param n The index of the rule you want.
		@return A refcounted rule info interface, or nil if n is out of bounds.
	*/
	virtual IPreflightRuleInfo* QueryNthRule(int32 n) const = 0;

	/** Get the rule in the list that corresponds to the given rule ID.
		@param ruleID The rule ID you're looking for.
		@return A refcounted rule info interface, or nil if the given rule doesn't appear in the profile.
	*/
	virtual IPreflightRuleInfo* QueryRuleByID(const PreflightRuleID& ruleID) const = 0;

	/** Get the location of a rule in the list (if it is in the list).
		@param iRule The rule you want to find.
		@return The index of the rule in the list, or -1 if it's not in the list.
	*/
	virtual int32 Location(const IPreflightRuleInfo* iRule) const = 0;

	/** Get the location of a rule in the list (if it is in the list).
		@param ruleID The ruleID you want to find.
		@return The index of the rule in the list, or -1 if it's not in the list.
	*/
	virtual int32 Location(const PreflightRuleID& ruleID) const = 0;
	
	/** Add a new rule; typically called with a rule created via a rule service. The rule must
		be in the same database as the profile (or no database if the profile is not in a database).

		@param iRule The rule you want to add. This interface is refcounted for in-memory profiles;
			it is NOT refcounted for database profiles, but the UID of the boss is added to the UIDList
			of this interface.
	*/
	virtual void AddRule(IPreflightRuleInfo* iRule) = 0;

	/** Remove a rule from the list.
		
		@param n The index of the rule you want to remove.
		@param deleteIT True to delete the rule boss from the database (ignored for in-memory profiles).
			False will remove the rule from the list but NOT delete the boss -- that's your responsibility.
			Useful if you want to move the rule to another profile, say.
	*/
	virtual void RemoveNthRule(uint32 n, bool deleteIt = kTrue) = 0;

	/** Removes all rules from the list.

		@param deleteThem True to delete the rules from the database. False to leave them -- but this
			is probably not what you want in most cases unless you've already taken ownership of all
			of them!
	*/
	virtual void RemoveAllRules(bool deleteThem = kTrue) = 0;

	/** Copies the rules from another list. This copies each rule and adds it to the list. Prior to
		this all existing rules are deleted (by RemoveAllRules(kTrue)). Note that this works for all
		combinations of in-memory and in-database profiles.

		@param iSrc The rules you want to copy from.
	*/
	virtual void CopyFrom(const IPreflightProfileRules* iSrc) = 0;

	/** Does a deep compare with another profile to determine equivalence. Equivalence is defined as
		having all the same rules with all the same parameters, although not necessarily in the same
		order.

		@param iOther IN The rules to compare against.
		@return kTrue if they're the same; kFalse otherwsise.
	*/
	virtual bool IsEqual(const IPreflightProfileRules* iOther) const = 0;

	/** Utility for updating all the rules data in case any of the rule implementations have changed
		and the parameters need to be modified. For each rule in the list it grabs the 
		IPreflightRuleUtilities interface and calls UpdateRuleData().
	*/
	virtual void UpdateAllRulesData() = 0;
};

