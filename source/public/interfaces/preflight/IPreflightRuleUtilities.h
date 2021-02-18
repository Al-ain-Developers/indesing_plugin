//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightRuleUtilities.h $
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
#include "IPreflightRuleInfo.h"
#include "PackageAndPreflightID.h"

/** This interface sits ON THE RULE (it's not a singleton utilties boss) because the services
	it provides are unique to the rule. For example, duplicating a rule may require additional
	intelligence based on the party who wrote the rule.

	The methods on this interface are meant for functions that you usually have no need to
	override, but we want to be sure that if you do need to, you can. Most rules will use the
	stock implementation (kPreflightRuleUtilitiesImpl).

	Methods that are virtually always overridden are found on IPreflightRuleVisitor.
*/
class IPreflightRuleUtilities : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRULEUTILITIES };

public:
	/** Make a copy of this rule and its instance data in the specified database. If
		iDB == nil then create one in memory.

		@param iDB The database in which the copy should be created. If nil, create it in memory.
		@return A refcounted copy.
	*/
	virtual IPreflightRuleInfo* DuplicateRule(IDataBase* iDB) const = 0;

	/** This is called when the rule is being deleted. If your rule needs to delete
		child objects, it should do so in order to avoid UID leaks. This only applies to
		rules in databases, not in-memory copies.
	*/
	virtual void DeletingRule() = 0;

	/** Compare this rule to another. This is a deep compare of data. It should return true
		if the rules have the same data, even if the data isn't necessarily in the same order.
	*/
	virtual bool IsEqual(const IPreflightRuleInfo* iOther) const = 0;
};

