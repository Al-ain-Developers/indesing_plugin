//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightResultNodeData.h $
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

#include "IPreflightObject.h"
#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPreflightRuleInfo.h"
#include "IPreflightResultNodeInfo.h"

/** This interface "lives" on the result node created by IPreflightAggregatedResultsUtils.
	It serves as the data for the IPreflightResultNodeInfo, which is the generic accessor
	used by the rest of the preflight UI. So this is an implementation-dependent interface
	that isn't required/guaranteed on other IPreflightResultNodeInfo implementations.

	The purpose of this interface is to allow for reasonable setup of a result node because
	they tend to carry a lot of data/strings that are painful to construct and pass in one
	step.

	This interface lives on the kPreflightResultNodeBoss which exists only in memory.
*/

class IPreflightResultNodeData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRESULTNODEDATA };

	typedef enum
	{
		kFieldRequired,		// "Required: xxx"
		kFieldProblem,		// "Problem: xxx"
		kFieldFix			// "Fix: xxx"
	} InfoField;

public:

	/** Sets the object.
	*/
	virtual void SetObjectID(const PreflightObjectID& objID) = 0;

	/** Gets the object.
	*/
	virtual const PreflightObjectID& GetObjectID() const = 0;

	/** Sets the root sorting value automatically based on the rule. 
	*/
	virtual void SetRootSortValue(const PreflightRuleID& ruleID) = 0;

	/** Sets the root sorting value. This is used to control the sorting of nodes in the trees.
		For nodes with object IDs this isn't required unless you want to force results above
		or below the natural sorting ranges. 
	*/
	virtual void SetRootSortValue(const PMString& s) = 0;

	/** Sets the name, ie the string that appears in the tree view itself.
	*/
	virtual void SetName(const PMString& name) = 0;

	/** @return the name, ie the string that appears in the tree view itself.
	*/
	virtual PMString GetName() const = 0;

	/** Get the sorting string. This determines the sort order compared to others at the same
		hierarchy level.

		@return A string that is used for sorting purposes.
	*/
	virtual PMString GetSortValue() const = 0;

	/** Get a unique string -- a hash, basically -- which uniquely identifies the node apart from
		all others in a given results set. Typically this is built using the rule ID, object ID hash,
		etc. This is used to support mapping of results between invalidations in the UI since the
		IPreflightResultNode::NodeID can vary.

		@return A unique identifier string.
	*/
	virtual WideString GetUniqueString() const = 0;

	/** Appends an info string.
		@param whichField IN The prefix to put before the string. If kFieldCustom no prefix is added.
		@param s IN The string to add.
	*/
	virtual void AddInfoString(InfoField whichField, const PMString& s) = 0;

	/** Appends an info string with a custom field name.
		@param label IN The label for the field. Do not include a colon, just the string.
		@param s IN The string to add.
	*/
	virtual void AddInfoString(const PMString& fieldLabel, const PMString& s) = 0;

	/** Gets the single string representing the concatenated info string.
	*/
	virtual PMString GetInfoText() const = 0;

	/** Gets the strings as a vector.
		@param pairs OUT Receives a vector of description pairs
	*/
	virtual void GetDescriptionPairs(IPreflightResultNodeInfo::DescriptionPairVector& pairs) const = 0;

	/** Get the node type that is reported via IPreflightResultNodeInfo.
		@return the node type.
	*/
	virtual IPreflightResultNodeInfo::NodeType GetNodeType() const = 0;

	/** Set the node type reported via IPreflightResultNodeInfo.
		@param t IN The new node type.
	*/
	virtual void SetNodeType(IPreflightResultNodeInfo::NodeType t) = 0;

	/** Get the page number that is reported via IPreflightResultNodeInfo.
		@return the page number, or empty string if there is none.
	*/
	virtual PMString GetPageNumber() const = 0;

	/** Set the page number reported via IPreflightResultNodeInfo.
		@param sPage IN The new page number string.
	*/
	virtual void SetPageNumber(const PMString& sPage) = 0;
};

