//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightResultRecord.h $
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
#include "IPreflightResultNodeInfo.h"
#include "IPreflightProcess.h"
#include "PackageAndPreflightID.h"

class IPreflightResultNodeInfo;
class PreflightXferStream;

/** This interface would normally be used by a preflight rule implementation.

	@see IPreflightRuleVisitor

	This interface has two main purposes: it records data for a preflight rule visit, and 
	later serves as a mechanism for organizing those results when aggregating. Normally a
	preflight result record is created in your rule visitor via 
	IPreflightVisitInfo::CreateResultRecord but if you want to create your own during
	results aggregation you can use IPreflightAggregatedResultsUtils::CreatePreflightResultRecord.

	@see IPreflightResultRecordTable
	@see IPreflightAggregatedResultsUtils

	The fields in the result record are meant to be generic in nature, ie rule-dependent.
	Their sole purpose is to aid in recording and aggregating records together. 
	In all cases the preflight result record is associated with a preflight object ID.
	In some cases that may be all you need, in which case your use of this interface is
	trivial. In other cases you'll want to record more detailed information about the
	violation. It's purely a question of what information you need to display later on
	during the aggregation phase, and/or whether that information is inexpensive to
	obtain later and therefore you don't care about recording it when you find the error.

	As an example, the font types rule records the name of the font in the aux string
	field, because that makes it easy later to create subtables by aux string value *and*
	it's mildly complex to re-obtain the font name later, so it's more efficient to record
	it in the Visit() phase.

	To save you the trouble of scanning through all the APIs below, the data stored in a 
	record includes:

	- The PreflightObjectID of the associated object
	- A vector of subpart IDs, indicating which subpart(s) are associated
	- A vector of PMReal values, which your rule can use however it likes
	- A criteria ID, which is typically used to indicate what category of failure this is,
			if your rule has mutliple failure categories
	- An aux string, which your rule can use however it likes
	- A process node, indicating the node in the related process is associated with
			this record (if any).
*/

class IPreflightResultRecord : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRESULTRECORD };

public:
	/** Set the related object ID. This is automatically set up for you if you're using
		IPreflightVisitInfo::CreateResultRecord().

		@param objid IN The object ID to set.
	*/
	virtual void SetObjectID(const PreflightObjectID& objid) = 0;

	/** Get the related object ID.
		@return the object ID. NOTE that this is const reference so be careful about the
			scope; if in doubt, copy to a local PreflightObjectID variable. The const
			reference is used here because it's moderately expensive to duplicate a 
			PreflightObjectID and the result is often passed to utiltities that take 
			a const reference, so we save a lot of copying.
	*/
	virtual const PreflightObjectID& GetObjectID() const = 0;

	/** Add a subpart to the record. Each record has a vector of subparts. This is normally 
		auto-setup by IPreflightAggregatedResultsUtils, but there's no reason you can't 
		make up your own subparts and apply them at the time you encounter the error.

		@param subpartID IN The subpart to add to the vector.
		@return true if the subpart was not already in the vector (ie the vector changed).
	*/
	virtual bool AddSubpart(ClassID subpartID) = 0;

	/** Merge a vector of subparts with the record's vector.
		@param subparts IN The vector of subparts to add.
		@return true if subparts were added (ie one or more were not already in there).
	*/
	virtual bool AddSubparts(const K2Vector<ClassID>& subparts) = 0;

	/** Merge another record's subparts into this record's vector.
		@param iOther IN The other record.
		@return true if subparts were added (ie one or more were not already in there).
	*/
	virtual bool AddSubparts(const IPreflightResultRecord* iOther) = 0;

	/** Get the subparts in this record's subpart vector.
		@param subparts OUT Receives the subpart vector.
	*/
	virtual void GetSubparts(K2Vector<ClassID>& subparts) const = 0;

	/** Determines whether the given subpart appears in the subpart vector.
		@param subpartID IN THe subpart you wish to test for.
		@return true iff subpartID appears in the subpart vector.
	*/
	virtual bool HasSubpart(ClassID subpartID) const = 0;

	/** Returns whether the subpart vector is of size 1 (ie, all of the subparts added have
		been the same value), and optionally returns what that common value is.

		@param commonID OUT If not nil, receives the common value if there is one, or 
			kInvalidClass if there isn't.
		@return true iff the subpart vector is of size 1, indicating that after aggregation
			there was no mixed subpart.
	*/
	virtual bool HasCommonSubpart(ClassID* commonID) const = 0;

	/** Add a value to the record. Each record has a vector of PMReal values. These are
		completely 'untyped' otherwise; what a value is depends entirely on your rule.
		However, preflight aggregation utilities will tend to aggregate together values.
		For example, if your value is the width of a stroke you encounter, the aggregation
		utilities may aggregate together records with everything else the same *except*
		the values; in that case the value vectors are merged.

		@param r IN The value to add to the vector.
		@return true if the value was not already in the vector (ie the vector changed).
	*/
	virtual bool AddValue(const PMReal& r) = 0;

	/** Merge a vector of values with the record's vector.
		@param values IN The vector of values to add.
		@return true if values were added (ie one or more were not already in there).
	*/
	virtual bool AddValues(const K2Vector<PMReal>& values) = 0;

	/** Merge another record's values into this record's vector.
		@param iOther IN The other record.
		@return true if values were added (ie one or more were not already in there).
	*/
	virtual bool AddValues(const IPreflightResultRecord* iOther) = 0;

	/** Get the values in this record's values vector.
		@param values OUT Receives the values vector.
	*/
	virtual void GetValues(K2Vector<PMReal>& values) const = 0;

	/** Get the minimum value found in the vector.
		@return the minimum value or 0 if there are no values.
	*/
	virtual PMReal GetMinValue() const = 0;

	/** Get the maximum value found in the vector.
		@return the maximum value or 0 if there are no values.
	*/
	virtual PMReal GetMaxValue() const = 0;

	/** Returns whether the values vector is of size 1 (ie, all of the values added have
		been the same value), and optionally returns what that common value is.

		@param pCommon OUT If not nil, receives the common value if there is one, or 
			0 if there isn't.
		@return true iff the value vector is of size 1, indicating that there are no mixed values.
	*/
	virtual bool HasCommonValue(PMReal* pCommon = nil) const = 0;

	/** Set the criteria for this record. A criteria ID is normally a way of distinguishing
		one kind of failure from another. For example the image resolution rule has different
		criteria IDs for each kind of image (color, gray, b&w). If your rule only has one
		kind of criteria you don't need to store this; it defaults to kPreflightRC_Default.
		Since criteria IDs are defined in plugin ID space you can add your own (should, really).

		@param criteriaID IN The criteria to set.
	*/
	virtual void SetCriteria(ClassID criteriaID) = 0;

	/** @return the criteria for this record.
	*/
	virtual ClassID GetCriteria() const = 0;

	/** Sets the aux string, which you can use for other sorting operations where criteria
		isn't the way you want to sort. For example if you want to store a font name you
		can put it in here and later present the violations arranged by that.

		Note that the IPreflightAggregatedResultsUtils aggregation methods will not aggregate 
		together any entries which have different aux strings.

		@param s IN The new aux string.
	*/
	virtual void SetAuxString(const PMString& s) = 0;

	/** @return the aux string for the record.
	*/
	virtual PMString GetAuxString() const = 0;

	/** Set the process node. This generally applies only to the first generation (pre-aggregation)
		results, since after aggregation there isn't usually a corresponding process database node.
		Normally you don't set this; the preflight visit info does at creation time.

		@param nodeID IN the process node ID.
	*/
	virtual void SetProcessNode(IPreflightProcess::NodeID nodeID) = 0;

	/** @return the associated process node ID. 0 if there is none.
	*/
	virtual IPreflightProcess::NodeID GetProcessNode() const = 0;

	/** Internal use only. Desrializes the record data from a blob that's stored in the preflight
		process database.

		@param s IN The serialization stream.
	*/
	virtual void ReadData(PreflightXferStream& s) = 0;

	/** Internal use only. Serializes the record data into a blob that's stored in the preflight
		process database.

		@param s IN The serialization stream.
	*/
	virtual void WriteData(PreflightXferStream& s) const = 0;
};

