//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightRuleInfo.h $
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

class IPreflightProfile;

/** A rule ID is a unique ID in all the world identifying the rule. This string does not
	appear in the UI anywhere. So if you're generating your own IDs you should prefix them
	with a company name or use another suitable strategy. We use strings for unique IDs rather 
	than ClassIDs because otherwise scripts would have no obvious way of generating IDs 
	that are unique..
*/
typedef WideString PreflightRuleID;

/** Vectors of IDs are used in many places so this seems like the logical place to define it.
*/
typedef K2Vector<PreflightRuleID> PreflightRuleIDVector;

/** This interface maintains the high-level information about a rule. Other interfaces on the
	same boss provide other critical information and functionality.

	@see IPreflightRuleData which defines the rule's parameters (if any) in a dictionary format.
	@see IPreflightRuleVisitor which is the functional part of the rule, performing checks against
		document data.
	@see IPreflightRuleUtilities is an interface that provides additional rule services such as
		life cycle callbacks, duplication, and so on.
*/
class IPreflightRuleInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRULEINFO };

	/** Alert status. Note that at this time only kDisabled and kError are used/honored. We
		may use the other options in a future version of the feature.
	*/
	typedef enum { kDisabled, kInfo, kWarning, kError } AlertStatus;

public:
	/** Establish a link to the parent profile, since we need to walk the tree from
		time to time.. plus the child needs to be able to tell the parent about changes
		to the rule and plugin descriptions.

		@param iParent IN The parent. Note that we do NOT refcount this interface to avoid
			circular references.
	*/
	virtual void SetParentProfile(IPreflightProfile* iParent) = 0;

	/** Get the parent profile for this rule.
		@return The parent profile. This DOES refcount the interface (thus Query).
	*/
	virtual IPreflightProfile* QueryParentProfile() const = 0;

	/** Set the ID for this rule. The ID is a unique string that identifies the rule.
		(The string does not appear in the UI anywhere.)
		@param ruleID IN The new ID.
	*/
	virtual void SetRuleID(PreflightRuleID ruleID) = 0;

	/** Get the unique ID for this rule.
		@return The ID.
	*/
	virtual PreflightRuleID GetRuleID() const = 0;

	/** Set the alert status. At the moment this only uses two values: kDisabled and
		kError. kDisabled means the rule is not active; kError means it is.
		@param newStatus IN The new status.
	*/
	virtual void SetAlertStatus(AlertStatus newStatus) = 0;

	/** Get the alert status. At the moment this only uses two values: kDisabled and
		kError. kDisabled means the rule is not active; kError means it is.
		@return The current active status of the rule.
	*/
	virtual AlertStatus GetAlertStatus() const = 0;

	/** Not currently used but might be in future.
		@param isFullOnly IN Full preflight flag.
	*/
	virtual void SetIsFullPreflightModeOnly(bool isFullOnly) = 0;

	/** Not currently used but might be in future.
		@return Full preflight flag.
	*/
	virtual bool IsFullPreflightModeOnly() const = 0;

	/** Set the backup string we'll display if the plugin is missing later.
		@param desc IN The new description.
	*/
	virtual void SetRuleDescription(const PMString& desc) = 0;

	/** Get the backup string we'll display if the plugin is missing later.
		@return The backup description string.
	*/
	virtual PMString GetRuleDescription() const = 0;
	
	/** Set the backup plugin string we'll display if the plugin is missing later.
		@param desc IN The backup plugin description string.
	*/
	virtual void SetPluginDescription(const PMString& desc) = 0;

	/** Get the backup plugin string we'll display if the plugin is missing later.
		@return The backup plugin description string.
	*/
	virtual PMString GetPluginDescription() const = 0;

	/** Utility: copy the settings from another interface (except the parent link).
		@param iSrc IN The source data from which to copy.
	*/
	virtual void CopyFrom(const IPreflightRuleInfo* iSrc) = 0;

	/** Determines whether the properties are the same as another (not including the parent link).
		@param iOther IN The other info interface to compare against.
		@return kTrue if they're equal; kFalse otherwise.
	*/
	virtual bool IsEqual(const IPreflightRuleInfo* iOther) const = 0;
};

