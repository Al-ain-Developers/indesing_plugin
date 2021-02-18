//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PerformanceStats.h $
//  
//  Owner: jshankar
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Contains API for getting performance statistics.
//  
//========================================================================================

#pragma once
#ifndef __PerformanceStats__
#define __PerformanceStats__

#include "OMTypes.h"
#include "IPerformanceMetric.h"

class PUBLIC_DECL PerformanceStats
{
public:
	enum EDoWhat { eGetValue, eResetValue /* if applicable */};

	typedef uint64 (*CallBack)(EDoWhat doWhat, void *refPtr, PerformanceMetricID counter);

	static uint64	GetValue(PerformanceMetricID counter);
	static void		ResetValue(PerformanceMetricID counter);

	static void		RegisterCounter(PerformanceMetricID counter, CallBack callback, void* refPtr, const PMString &shortName, const PMString &longName);
	static void		RegisterCounter(PerformanceMetricID counter, ClassID counterProvider, const PMString &shortName, const PMString &longName);

	static void		DeRegisterCounter(PerformanceMetricID counter);


	static void		GetAllMetricIDs(IPerformanceMetric::PerformanceMetricIDList &metrics);
		/** 
			returns a list of all currently available metrics - note this is volatile - just because there is an ID in this list, 
			doesn't mean that counter will still be active when you query its value
		 */

	static PMString	GetMetricShortName(PerformanceMetricID counter);
	static PMString	GetMetricLongName(PerformanceMetricID counter);
	static void		Startup();
	static void		Shutdown();
};

class StaticPerfCallbackRegister
{
public:
	StaticPerfCallbackRegister(PerformanceMetricID counter, PerformanceStats::CallBack callback, void* refPtr, const PMString &shortName, const PMString &longName) :
		fCounterID(counter)
	{
		PerformanceStats::RegisterCounter(counter, callback, refPtr, shortName, longName);
	}
	~StaticPerfCallbackRegister()
	{
		PerformanceStats::DeRegisterCounter(fCounterID) ;
	}
private:
	PerformanceMetricID		fCounterID;
};

#endif // __PerformanceStats__

