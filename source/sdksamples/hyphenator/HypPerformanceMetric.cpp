//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypPerformanceMetric.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

#include "K2Vector.tpp"

// Project includes:
#include "HypID.h"
#include "IPerformanceMetric.h"
#include "HypPerformanceData.h"

/** 	
*/
class HypPerformanceMetric : public IPerformanceMetric
{
public:
	/**	constructor.
	*/
	HypPerformanceMetric(IPMUnknown* boss);

	virtual void GetMetricInfo(PerformanceMetricIDList &metricIDs);


	/** Return the short name of the specified performance metric id. This is used as the 
		name of the performance counter registered with PerfMon on Windows.
		@param metricID [IN] - the id of the metric being queried for; will be one of the ids returned from GetMetricInfo.
		@return short name PMString.
	*/
	virtual PMString GetMetricShortName(PerformanceMetricID metricID);

	/** Return the long name of the specified performance metric id. This is used as the 
		description of the performance counter registered with PerfMon on Windows.
		@param metricID [IN] - the id of the metric being queried for; will be one of the ids returned from GetMetricInfo.
		@return long name PMString.
	*/
	virtual PMString GetMetricLongName(PerformanceMetricID metricID);

	/** Called when the specified performance metric is about to be de-registered. 
		@param metricID [IN] - the id of the metric being deregistered; will be one of the ids returned from GetMetricInfo.
	*/
	virtual void DeRegisterMetric(PerformanceMetricID metricID);

	/** Called to get the current value of the specified metric. 
		@param metricID [IN] - the id of the metric being queried for; will be one of the ids returned from GetMetricInfo.
		@return current value scaled to fit in a uint64.
	*/
	virtual uint64 GetMetricValue(PerformanceMetricID metricID);


	/** Reset the current value of the specified performance metric.
		@param metricID [IN] - the id of the metric being reset; will be one of the ids returned from GetMetricInfo.
		@return nothing.
	*/
	virtual void ResetMetric(PerformanceMetricID metricID);

DECLARE_HELPER_METHODS()

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(HypPerformanceMetric, kHypPerformanceMetricImpl)
DEFINE_HELPER_METHODS(HypPerformanceMetric)

/* Constructor
*/
HypPerformanceMetric::HypPerformanceMetric(IPMUnknown* boss) :		
	HELPER_METHODS_INIT(boss)
{
}


/** GetMetricInfo
	Add this plug-ins metric ids to the end of the id list
*/
void HypPerformanceMetric::GetMetricInfo(PerformanceMetricIDList &metricIDs)
{
	metricIDs.push_back(kHypMetricMaxID);
	metricIDs.push_back(kHypMetricTotalID);
}


/** GetMetricShortName
	returns the short name for the metric
*/
PMString HypPerformanceMetric::GetMetricShortName(PerformanceMetricID metricID)
{
	PMString returnValue("");

	switch (metricID.Get()) 
	{
		case kHypMetricMaxID: 
			returnValue = PMString("Hyphenation Max");
			break;
		case kHypMetricTotalID: 
			returnValue = PMString("Hyphenation Total");
			break;
	}

	return returnValue;
}

/** GetMetricLongName
	returns the description of the metric
*/
PMString HypPerformanceMetric::GetMetricLongName(PerformanceMetricID metricID) 
{
	PMString returnValue("");

	switch (metricID.Get()) 
	{
		case kHypMetricMaxID: 
			returnValue = PMString("The maximum number of hyphenations in any word");
			break;
		case kHypMetricTotalID: 
			returnValue = PMString("The total number of hyphenation calls");
			break;
	}

	return returnValue;
}


/** DeRegisterMetric
	Cleans up
*/
void HypPerformanceMetric::DeRegisterMetric(PerformanceMetricID /*metricID*/) 
{
	// This is where you clean up.  We don't have any dynamic data, so we're doing nothing
}


/** GetMetricValue
	returns the value of the metric
*/
uint64 HypPerformanceMetric::GetMetricValue(PerformanceMetricID metricID)
{
	uint64	returnValue = 0;
	
	switch (metricID.Get()) 
	{
		case kHypMetricMaxID: 
			returnValue = HypPerformanceData::GetHypMax();
			break;
		case kHypMetricTotalID: 
			returnValue = HypPerformanceData::GetHypTotal();
			break;
	}

	return returnValue; 
}


/** ResetMetric
	resets the metrics to zero
*/
void HypPerformanceMetric::ResetMetric(PerformanceMetricID metricID) 
{
	switch (metricID.Get()) 
	{
		case kHypMetricMaxID: 
			HypPerformanceData::SetHypMax(0);
			break;
		case kHypMetricTotalID: 
			HypPerformanceData::SetHypTotal(0);
			break;
	}
}

