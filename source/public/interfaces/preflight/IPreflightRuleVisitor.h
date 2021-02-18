//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightRuleVisitor.h $
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
//  This interface sits on a rule boss and deals with navigating and visiting nodes in 
//  the preflight OM.
//  
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPreflightObject.h"
#include "IPreflightProcess.h"
#include "IPreflightAggregatedResults.h"
#include "IPreflightRuleData.h"

class IPreflightVisitInfo;

/** This is the single most important interface to understand if you're writing a rule.
	The IPreflightRuleVisitor interface is usually a nonpersistent interface that provides
	the dynamic model behavior for the rule. It sits on a rule boss created by your rule 
	service along with the persistent data.

	This is one of two interfaces that are typically implemented on a rule using something
	other than the standard implementations (more on the standard implementations below).

	The methods in this interface are mostly for the inspection of objects and reporting
	and formatting of results, but a few utilities that require dynamic, rule-specific
	implementations also reside here. Namely UpdateRuleData(). 
	
	The other dynamic, rule-specific interface on a rule boss is IPreflightRuleUI, which
	provides services for the presentation of rule parameters to the user in the profile
	editing dialog. Since we like to separate model and UI behaviors into separate plugins, 
	IPreflightRuleUI is usually an Add-In implementation onto the rule boss in the UI plugin.

	Other interfaces on the rule boss include:

	- IPreflightRuleInfo: Generally static (after construction) information about the rule 
		such as its description, plugin description, etc.
	- IPreflightRuleData: Stores the rule parameters. You don't have to use this for your
		persistent data but it makes a lot of the UI much easier to implement. The stock
		implementation (IPreflightRuleDataImpl) is usually all you'll need.
	- IPreflightRuleUtilities: Utilities for rule operations that are typically handled
		by the stock implementation (kPreflightRuleUtilitiesImpl) but you can override if
		you need special treatment.
*/

class IPreflightRuleVisitor : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRULEVISITOR };

public:
	/** Return a vector of class IDs that you're interested in visiting.
		@return A vector of class IDs.
	*/
	virtual PreflightObjectClassIDVector GetClassesToVisit() const = 0;

	/**	This method is called when it's time to visit an object whose class you
		said you were interested in via GetClassesToVisit.

		@param iInfo An information and reporting structure.
	*/
	virtual void Visit(IPreflightVisitInfo* iInfo) = 0;

	/** Given a list of previously reported nodes in the process database, determine their
		presentation in the user interface (and reporting, which is why this is in the model
		interface and not in the rule UI interface).

		@param iProcess The process from which you can get the "raw" results.
		@param resultNodes The vector of result nodes reported by your rule.
		@param iResults The aggregated results database to add nodes to.
		@param parentID The node in the results database under which you should add your result nodes.

		@see IPreflightAggregatedResults
		@see IPreflightResultNodeInfo
	*/
	virtual void AggregateResults
		(
			const IPreflightProcess* iProcess,
			const IPreflightProcess::NodeIDVector& resultNodes,
			IPreflightAggregatedResults* iResults,
			IPreflightAggregatedResults::NodeID parentID
		) const = 0;

	/** This is called at startup for application-level rules and at document open time for 
		document-level rules. It gives the plugin a chance to review the data in the rule
		and make any updates based on version changes.

		Normally the rule data is stored as a key/value dictionary in IPreflightRuleData
		on the same boss.
	*/
	virtual void UpdateRuleData() = 0;

	/** This is called to check a parameter for the rule and should be called before setting the value.
		It validate the proposed value for the specified key and 
		returns an error code indicating the error, ususally out of range or invalid paragtmers.

		Normally the rule data is stored as a key/value dictionary in IPreflightRuleData
		on the same boss.

		@param key is the data key.
		@param proposedValue is the value for the specified key to be validated.
		@return an error code or kSuccess.
	*/
	virtual ErrorCode ValidateRuleData(const IPreflightRuleData::Key& key, const ScriptData& proposedValue) const = 0;
};



