//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPerformanceMetric.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IPerformanceMetric__
#define __IPerformanceMetric__

#include "IPMUnknown.h"
#include "PerformanceMetricsID.h"
#include "K2Vector.h"
#include "PMString.h"

/** 
	Abstract base class for a performance metric service provider implementation. 

	This implementation is queried for at startup on kPerformanceMetricService service providers.
	The performance metric they describe will be registered with the performance monitoring framework.
*/
class IPerformanceMetric : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPERFORMANCEMETRIC } ;

	typedef K2Vector< PerformanceMetricID > PerformanceMetricIDList;

	/** Return a list of performance metric ids this implementation defines. Called at services startup time.
		@return PerformanceMetricIDList.
	*/
	virtual void GetMetricInfo(PerformanceMetricIDList &metricIDs) = 0;


	/** Return the short name of the specified performance metric id. This is used as the 
		name of the performance counter registered with PerfMon on Windows.
		@param metricID [IN] - the id of the metric being queried for; will be one of the ids returned from GetMetricInfo.
		@return short name PMString.
	*/
	virtual PMString GetMetricShortName(PerformanceMetricID metricID) = 0;

	/** Return the long name of the specified performance metric id. This is used as the 
		description of the performance counter registered with PerfMon on Windows.
		@param metricID [IN] - the id of the metric being queried for; will be one of the ids returned from GetMetricInfo.
		@return long name PMString.
	*/
	virtual PMString GetMetricLongName(PerformanceMetricID metricID) = 0;

	/** Called when the specified performance metric is about to be de-registered. 
		@param metricID [IN] - the id of the metric being deregistered; will be one of the ids returned from GetMetricInfo.
	*/
	virtual void DeRegisterMetric(PerformanceMetricID metricID) = 0;

	/** Called to get the current value of the specified metric. 
		@param metricID [IN] - the id of the metric being queried for; will be one of the ids returned from GetMetricInfo.
		@return current value scaled to fit in a uint64.
	*/
	virtual uint64 GetMetricValue(PerformanceMetricID metricID) = 0;


	/** Reset the current value of the specified performance metric.
		@param metricID [IN] - the id of the metric being reset; will be one of the ids returned from GetMetricInfo.
		@return nothing.
	*/
	virtual void ResetMetric(PerformanceMetricID metricID) = 0;
	
} ;

#endif
