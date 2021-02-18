//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightAggregatedResultsUtils.h $
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
#include "Utils.h"
#include "IPreflightAggregatedResults.h"
#include "IPreflightProcess.h"

class IPreflightResultRecordTable;
class IPreflightResultRecord;
class IPreflightResultNodeData;
class IPreflightResultNodeInfo;

/**	Utilities that rules use to create aggregated results. These are normally called from
	IPreflightRuleVisitor::AggregateResults() but may be appropriate in some other cases too.

	@see IPreflightAggregatedResults
	@see IPreflightRuleVisitor
*/
class IPreflightAggregatedResultsUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTAGGREGATEDRESULTSUTILS };

public:
	typedef InterfacePtr<IPreflightResultRecordTable> ResultTableIFP;
	typedef K2Vector<ResultTableIFP> VectorOfTables;
	typedef K2Vector<int32> VectorOfIndices;

	/** Flags for ApplyAllStandardAggregations et al. */
	enum 
	{
		/** Aggregate records with the same object, but different subparts, together. Without this flag, 
			different subparts are kept as separate records. Note that with this flag set, if you have
			a plurality of values and subparts, after aggregation you won't know which subparts 
			contributed which values, if that's important to you.
		*/
		kAggregateDifferentSubparts = (1L<<0),

		/** Applies to ApplyAllStandardAggregations and AggregateContiguousTextRanges. Normally
			text ranges are only aggregated if they have the same criteria, values, subparts, 
			and aux strings. Passing this flag eliminates values as a distinguishing factor.
			Of course, values will be combined.
		*/
		kAggregateTextRangesWithDifferentValues = (1L<<1),

		/** Applies to ApplyAllStandardAggregations and AggregateContiguousCells. Normally
			cells are only aggregated if they have the same criteria, values, subparts, 
			and aux strings. Passing this flag eliminates values as a distinguishing factor.
			Of course, values will be combined.
		*/
		kAggregateCellsWithDifferentValues = (1L<<2),

		/** Applies to ApplyAllStandardAggregations. Normally at the end of the aggregation process
			a final pass is made that looks for different subparts but with the same value. For example
			you might have a stroke and fill that share the same value (eg colorspace). In these cases
			the final pass merges the two records together to form a single record with a plurality of 
			subpart but single value.

			By setting this flag you retard the final pass check.
		*/
		kDoNotAggregateSingluarValueSubparts = (1L<<3)
	};

public:
	/** Create an empty preflight aggregated results tree.

		@return A refcounted results tree.
	*/
	virtual IPreflightAggregatedResults* CreateAggregatedResults() const = 0;

	/** Create an empty preflight results record. You'll need to fill in all the details.
		This isn't typically done except private to the utilities, but there's no reason
		you can't create your own.

		@return A refcounted record.
	*/
	virtual IPreflightResultRecord* CreatePreflightResultRecord() const = 0;

	/** Create an empty preflight results record table. This isn't typically done except 
		private to the utilities, but there's no reason you can't create your own and
		add records to it.

		@return A refcounted record table interface.
	*/
	virtual IPreflightResultRecordTable* CreatePreflightResultRecordTable() const = 0;

	/** Create an empty preflight result node info. This is a kPreflightResultNodeBoss so you can
		query for IPreflightResultNodeData to fill in the details.

		@return A refcounted IPreflightResultNodeInfo interface.
	*/
	virtual IPreflightResultNodeInfo* CreatePreflightResultNodeInfo() const = 0;

	/** Given a set of result nodes from a process, create a Result Record table. This is usually
		the starting point for rule result aggregation.

		@param iProcess IN The process.
		@param resultsNodes IN The vector of result node IDs.
		@return A refcounted result record table. Will be nil if result node vector is empty or
			some kind of error occurs.
	*/
	virtual IPreflightResultRecordTable* CreateTableFromNodes
		(
			const IPreflightProcess* iProcess, 
			const IPreflightProcess::NodeIDVector& resultNodes
		) const = 0;

	/** Applies "standard" aggregations and consolidations for a given table. In general the
		results you get from a preflight visit can be large especially when considering 
		objects like text runs. This method consolidates (aggregates) entries that share
		common traits, like contiguous text runs with the same criteria and artwork in
		placed content.

		Typically this is called immediately after CreateTableFromNodes, but not necessarily.
		In some cases you may wish to do your own prefiltering into tables and then call this
		method to avoid aggregation together of entries you do *not* want to be autogrouped.
		In general, after calling this method, you will not have process node information
		(if the nodes have been aggregated there is no longer one unique value), and values
		and subparts may have been aggregated together.

		(More explanation to follow.)

		@param iProcess IN The process. This is required in order to deal with artwork and
			other entities where we need to look at the result node hierarchy.
		@param iTable
	*/
	virtual const IPreflightResultRecordTable* ApplyAllStandardAggregations
		(
			const IPreflightProcess* iProcess, 
			const IPreflightResultRecordTable* iTable,
			uint32 aggregationFlags = 0
		) const = 0;

	/** This is one of the methods called from ApplyAllStandardAggregations. It "uplevels"
		all marking operation records into their related higher-level selectable objects, 
		namely page items, text runs, and table cells. The subpart for these upleveled
		entries will be any known subpart (eg kPreflightOSP_NativeStroke).

		This method will combine unlike values together but will not by default combine
		unlike subparts. Passing kAggregateDifferentSubparts will allow subpart aggregation
		but then you won't be able to tell which subpart a given value came from if there
		is a plurality of both.

		@param iProcess IN The process; required in order to walk the process nodes to find
			the parents of marking operations.
		@param iTable IN The table to aggregate.
		@param aggregationFlags IN Flags; only kAggregateDifferentSubparts applies here.
		@return A refcounted aggregated table (the original table is unaffected). Note that
			if no aggregations occurred, this will be the same as iTable (but still 
			refcounted).
	*/
	virtual const IPreflightResultRecordTable* AggregateMarkingOperationsToUsefulObjects
		(
			const IPreflightProcess* iProcess, 
			const IPreflightResultRecordTable* iTable,
			uint32 aggregationFlags = 0
		) const = 0;

	/** This is one of the methods called from ApplyAllStandardAggregations. It finds 
		text runs and ranges that are contiguous and have the same criteria, values, aux
		strings, and subparts. If kAggregateTextRangesWithDifferentValues is passed, values 
		are not considered for aggregation purposes.

		@param iTable IN The table to aggregate.
		@param aggregationFlags IN Flags; only kAggregateTextRangesWithDifferentValues applies here.
		@return A refcounted aggregated table (the original table is unaffected). Note that
			if no aggregations occurred, this will be the same as iTable (but still 
			refcounted).
	*/
	virtual const IPreflightResultRecordTable* AggregateContiguousTextRanges
		(
			const IPreflightResultRecordTable* iTable,
			uint32 aggregationFlags = 0
		) const = 0;

	/** This is one of the methods called from ApplyAllStandardAggregations. It finds 
		table cells that are contiguous either horizontally or vertically, AND have the 
		same criteria, values, aux strings, and subparts. If kAggregateCellsWithDifferentValues 
		is passed, values are not considered for aggregation purposes.

		@param iTable IN The table to aggregate.
		@param horizontally IN If true, aggregates ranges together that share the same rows
			and are contiguous in columns. If false, aggregates ranges together that share
			the same columns and are contiguous in rows.
		@param aggregationFlags IN Flags; only kAggregateCellsWithDifferentValues applies here.
		@return A refcounted aggregated table (the original table is unaffected). Note that
			if no aggregations occurred, this will be the same as iTable (but still 
			refcounted).
	*/
	virtual const IPreflightResultRecordTable* AggregateContiguousCells
		(
			const IPreflightResultRecordTable* iTable,
			bool horizontally,
			uint32 aggregationFlags
		) const = 0;

	/** This is one of the methods called from ApplyAllStandardAggregations. 

		It aggregates together all records which differ only in subparts. This is to allow
		for neater presentation of results when all subparts otherwise share the same
		failure cases.

		@param iTable IN The table to aggregate.
		@param aggregationFlags IN Flags. None apply here but leaving for future expansion.
		@return A refcounted aggregated table (the original table is unaffected). Note that
			if no aggregations occurred, this will be the same as iTable (but still 
			refcounted).
	*/
	virtual const IPreflightResultRecordTable* AggregateDifferentSubpartsSameEverythingElse
		(
			const IPreflightResultRecordTable* iTable,
			uint32 aggregationFlags = 0
		) const = 0;

	/** Builds a second table that consists of the specified indices from the first table.
		This method is pretty fast because it's only managing refcounts on the records, not
		actually copying their data.

		@param iSrcTable IN The table from which you want to copy records.
		@param indices IN The indices from the table you want to copy.
		@return A refcounted table, or nil if indices is empty or an error occurs.
	*/
	virtual const IPreflightResultRecordTable* CreateSubTable
		(
			const IPreflightResultRecordTable* iSrcTable,
			const VectorOfIndices& indices
		) const = 0;

	/** Builds a second table by putting in it only records with a particular criteria.
		This method is pretty fast because it's only managing refcounts on the records, not
		actually copying their data.

		@param invertCriteria IN If true, invert the selection; ie put in only entries whose
			criteria is NOT criteriaID.
	*/
	virtual IPreflightResultRecordTable* CreateSubTableByCriteria
		(
			const IPreflightResultRecordTable* iSrc, 
			ClassID criteriaID,
			bool invertCriteria = kFalse
		) const = 0;

	/** Builds a set of derivative tables corresponding to unique values of criteria.
		This is useful if you want to give parent-child results where the parents are
		unique criteria. This is typically done when you have numerous criteria and want
		to share a common formatting subroutine.

		@param iSrcTable IN The source table from which you want to sort records.
		@param tables OUT Receives the array of tables, where each table corresponds to
			all records from iSrcTable with the same criteria.
	*/
	virtual void CreateTablesByCriteria
		(
			const IPreflightResultRecordTable* iSrcTable,
			VectorOfTables& tables
		) const = 0;

	/** Builds a set of derivative tables corresponding to unique values of aux string.
		This is useful if you want to give parent-child results where the parents are
		unique aux strings. Eg if you're presenting results grouped by font name, you can
		put the font name in the aux string when visiting nodes then use this method to 
		build aggregated results accordingly.

		@param iSrcTable IN The source table from which you want to sort records.
		@param tables OUT Receives the array of tables, where each table corresponds to
			all records from iSrcTable with the same aux string.
	*/
	virtual void CreateTablesByAuxString
		(
			const IPreflightResultRecordTable* iSrcTable,
			VectorOfTables& tables
		) const = 0;

	/** Builds a set of derivative tables corresponding to unique object IDs. This is
		commonly used if you want to guarantee a single node for each object (and if 
		there are multiple violations per object you want to put that information in
		the info strings as concatenated results).

		@param iSrcTable IN The source table from which you want to sort records.
		@param tables OUT Receives the array of tables, where each table corresponds to
			all records from iSrcTable with the same object ID.
	*/
	virtual void CreateTablesByObject
		(
			const IPreflightResultRecordTable* iSrcTable,
			VectorOfTables& tables
		) const = 0;
	
	/** Returns true if the record corresponds to placed content (or child marks).
	*/
	virtual bool IsPlacedContent(const IPreflightResultRecord* iRec) const = 0;

	/** Formats the given value (in points) as an X measure.
		@param iProcess IN The process. This is required in order to get the document's unit of
			measure settings to use when formatting the given value.
		@param x IN The value (in points) to format.
		@return A string formatted as an X measure.
	*/
	virtual PMString FormatXMeasure(const IPreflightProcess* iProcess, const PMReal& x) const = 0;

	/** Formats the given value (in points) as a Y measure.
		@param iProcess IN The process. This is required in order to get the document's unit of
			measure settings to use when formatting the given value.
		@param y IN The value (in points) to format.
		@return A string formatted as a Y measure.
	*/
	virtual PMString FormatYMeasure(const IPreflightProcess* iProcess, const PMReal& y) const = 0;

	/** Formats the given value (in points) as a line width.
		@param iProcess IN The process. This is required in order to get the document's unit of
			measure settings to use when formatting the given value.
		@param x IN The value (in points) to format.
		@return A string formatted as a line width.
	*/
	virtual PMString FormatLineMeasure(const IPreflightProcess* iProcess, const PMReal& x) const = 0;

	/** Formats the given value (in ppi) as a text size.
		@param iProcess IN The process. This is required in order to get the document's unit of
			measure settings to use when formatting the given value.
		@param x IN The value (in ppi) to format.
		@return A string formatted as a text size.
	*/
	virtual PMString FormatTextSizeMeasure(const IPreflightProcess* iProcess, const PMReal& x) const = 0;

	/** Formats the given value (in ppi) as a resolution.
	*/
	virtual PMString FormatResolution(const PMReal& x) const = 0;

	/** Formats the value as an integer. Should generally be used for actual integer values.
		Will round to the nearest integer. Result is a non-translatable string.
	*/
	virtual PMString FormatAsInteger(const PMReal& x) const = 0;

	virtual PMString GetSubpartsDescription
		(
			const IPreflightResultRecord* iRec, 
			bool forceTranslation = kTrue
		) const = 0;

	/** Creates and adds a criteria node, which is just a heading corresponding to the rule
		or criteria. This node does 

		@param iResults IN The results tree pointer.
		@param parentID IN The node under which you want to add the new node.
		@param nodeText IN The name of the node (appears in the tree).
		@param ruleID IN The rule ID to assign to the criteria node. This is needed for node-ordering purposes.
		@return The ID of the newly created node, or 0 on failure.
	*/
	virtual IPreflightAggregatedResults::NodeID AddCriteriaNode
		(
			IPreflightAggregatedResults* iResults, 
			IPreflightAggregatedResults::NodeID parentID, 
			const PMString& nodeText,
			const PreflightRuleID& ruleID
		) const = 0;

	/** Creates a node corresponding to a violating object. The name of the node is automatically
		generated based on the object, as are the automatic selection capabilities. You can fill 
		in explanatory text by querying IPreflightResultNodeData and adding in additional strings.

		This does not add the node to the tree. To do that use AddResultsNode() where you can
		specify the parent.

		@param objID IN The object to use for the node.
		@return A refcounted node.
	*/
	virtual IPreflightResultNodeInfo* CreateViolationNode
		(
			const PreflightObjectID& objID
		) const = 0;

	/** Creates a node that is both criteria AND violation. This is used when a rule can have only
		a single violation node, so we combine criteria and violation together.

		This does not add the node to the tree. To do that use AddResultsNode() where you can
		specify the parent.

		@param objID IN The object that represents the violation (typically the document).
		@param nodeName IN The name of the node (criteria).
		@param ruleID IN The rule ID to assign to the criteria node. This is needed for node-ordering purposes.
	*/
	virtual IPreflightResultNodeInfo* CreateCriteriaAndViolationNode
		(
			const PreflightObjectID& objID,
			const PMString& nodeName,
			const PreflightRuleID& ruleID
		) const = 0;

	/** Creates a generic (just a name) node. This node has no object by default, just
		a name; so typically it's used for some kind of grouping.

		Note that this creates the record but doesn't add it to the tree. When you're done
		setting it up, call AddResultsNode().

		@param nodeName IN The name of the node (shown in the tree).
		@param ruleID IN The rule ID to assign to the node. This is needed for node-ordering purposes.
			If you know for sure this node will never compete for order, or the name is sufficient, you
			can pass PreflightRuleID(). Or you can pass PreflightRuleID() and then use  
			IPreflightAggregatedResultData::SetRootSortValue() to have complete control.
		@return A refcounted results node from which you can also get IPreflightResultNodeData.
	*/
	virtual IPreflightResultNodeInfo* CreateGenericNode
		(
			const PMString& nodeName,
			const PreflightRuleID& ruleID
		) const = 0;

	/** Adds a result node to the aggregated results tree. For now this is simply a wrapper around
		iResults->AddNode() but in the future we may add some additional verification or utility,
		so in general you should work through this API.

		Note that within the parent, the children are auto-ordered according to their sort values.

		@param iResults IN The results tree to which you want to add the node.
		@param parentID IN The node that the new node should be a child of.
		@param iInfo IN The node info pointer. The results tree addrefs this and holds onto it until
			the tree is destroyed.
		@return The new Node ID in the tree.
	*/
	virtual IPreflightAggregatedResults::NodeID AddResultsNode
		(
			IPreflightAggregatedResults* iResults, 
			IPreflightAggregatedResults::NodeID parentID, 
			IPreflightResultNodeInfo* iInfo
		) const = 0;

	/** Adds a proxy criteria and proxy nodes. If your rule visits artwork but finds that a proxy
		is being drawn instead of the placed content, and wants to report it as a proxy violation,
		you can use this utility to auto-build the generic node and children.

		@param iResults IN The results tree to which you want to add the nodes.
		@param parentID IN The node that the new nodes should be a child of.
		@param iProxyTable IN The table of proxies, typically created via CreateTablesByCriteria or
			CreateSubTableByCriteria, using kPreflightRC_GraphicProxy as the parameter.
		@param criteriaName IN The text to use for the generic node under which the individual 
			proxy nodes are listed.
		@param ruleID IN The rule ID to assign to the criteria node. This is needed for node-ordering purposes.
		@return The new Node ID in the tree.
	*/
	virtual void AddProxyCriteriaAndNodes
		(
			IPreflightAggregatedResults* iResults, 
			IPreflightAggregatedResults::NodeID parentID, 
			const IPreflightResultRecordTable* iProxyTable, 
			const PMString& criteriaName,
			const PreflightRuleID& ruleID
		) const = 0;
};



