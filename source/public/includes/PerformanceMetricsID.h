//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PerformanceMetricsID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the generic page item plug-in
//  
//========================================================================================

#ifndef __PerformanceMetricsID__
#define __PerformanceMetricsID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPerformanceMetricsIDPrefix	RezLong(0x1E400)

// <Plugin ID>
DECLARE_PMID(kPlugInIDSpace, kPerformanceMetricsPluginID, kPerformanceMetricsIDPrefix + 1)


// <Class ID>
DECLARE_PMID(kClassIDSpace, kPerformanceMetricsScriptProviderBoss, 				kPerformanceMetricsIDPrefix + 0)
DECLARE_PMID(kClassIDSpace, kPerformanceMetricsStartupShutdownBoss, 			kPerformanceMetricsIDPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPerformanceMetricsIdleTaskBoss,					kPerformanceMetricsIDPrefix + 2)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IPERFORMANCECOUNTERS, 						kPerformanceMetricsIDPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IPERFORMANCEMETRIC, 						kPerformanceMetricsIDPrefix + 1)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kPerformanceMetricsScriptProviderImpl, 	kPerformanceMetricsIDPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kPerformanceMetricsStartupShutdownImpl, 	kPerformanceMetricsIDPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPerformanceCountersImpl, 					kPerformanceMetricsIDPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPerformanceMetricProviderImpl, 			kPerformanceMetricsIDPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPerformanceMetricsIdleTaskImpl, 			kPerformanceMetricsIDPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPerformanceMetricsAppObserverImpl, 		kPerformanceMetricsIDPrefix + 5)

// <Script Element ID>
DECLARE_PMID(kScriptInfoIDSpace, kServerSystemStatusMethodScriptElement,		kPerformanceMetricsIDPrefix + 1)	//obsolete - use kSystemStatusMethodScriptElement
DECLARE_PMID(kScriptInfoIDSpace, kServerMemoryStatsMethodScriptElement,			kPerformanceMetricsIDPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kServerSystemMethodScriptElement,				kPerformanceMetricsIDPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kServerDumpBetweemMarksMethodScriptElement,	kPerformanceMetricsIDPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kServerDumpFromMarkMethodScriptElement,		kPerformanceMetricsIDPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kPerformanceMetricShortNameMethodScriptElement,kPerformanceMetricsIDPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kPerformanceMetricLongNameMethodScriptElement,	kPerformanceMetricsIDPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kSystemStatusMethodScriptElement,				kPerformanceMetricsIDPrefix + 8)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kServerStatisticsSelectorEnumScriptElement,	kPerformanceMetricsIDPrefix + 100)	//obsolete
DECLARE_PMID(kScriptInfoIDSpace, kPerformanceMetricsSelectorEnumScriptElement,	kPerformanceMetricsIDPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kPerformanceMetricsPropertyScriptElement,		kPerformanceMetricsIDPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kInt64TypeDefScriptElement,					kPerformanceMetricsIDPrefix + 103)	// todo: maybe this belongs in ScriptingID.h?

enum PerformanceMetricScriptIDs
{
	t_Int64Type						=	'I64T',
	e_SystemStatus					=	'SSta',
	e_PerformanceMetric				=	'PMet',
	p_PerformanceMetrics			=	'PMts',
	e_PerformanceMetricShortName	=	'PMSn',
	e_PerformanceMetricLongName		=	'PMLn',
	e_ServerDumpFromMarkEvent	 	=	'SDFm',
	e_ServerDumpBetweenMarksEvent	=	'SDBm',
	e_ServerMemoryStatistics		=	'SMSt',
} ;

// <Service ID>
// Service IDs:
DECLARE_PMID(kServiceIDSpace, kPerformanceMetricService,						kPerformanceMetricsIDPrefix + 1)

// <Performance Metric IDs>
DECLARE_PMID(kPerformanceMetricIDSpace,	kHeapAllocPerfID,						kPerformanceMetricsIDPrefix + 1)
DECLARE_PMID(kPerformanceMetricIDSpace,	kHeapAllocPeakPerfID,					kPerformanceMetricsIDPrefix + 2)
DECLARE_PMID(kPerformanceMetricIDSpace,	kMemPurgeCountPerfID,					kPerformanceMetricsIDPrefix + 3)
DECLARE_PMID(kPerformanceMetricIDSpace,	kMemPurgeTimePerfID,					kPerformanceMetricsIDPrefix + 4)	
DECLARE_PMID(kPerformanceMetricIDSpace,	kBIBAllocPerfID,						kPerformanceMetricsIDPrefix + 5)
DECLARE_PMID(kPerformanceMetricIDSpace,	kBIBAllocPeakPerfID,					kPerformanceMetricsIDPrefix + 6)
DECLARE_PMID(kPerformanceMetricIDSpace,	kBIBCachePerfID,						kPerformanceMetricsIDPrefix + 7)
DECLARE_PMID(kPerformanceMetricIDSpace,	kBIBCachePeakPerfID,					kPerformanceMetricsIDPrefix + 8)
DECLARE_PMID(kPerformanceMetricIDSpace,	kPDFAllocPerfID,						kPerformanceMetricsIDPrefix + 9)
DECLARE_PMID(kPerformanceMetricIDSpace,	kPDFAllocPeakPerfID,					kPerformanceMetricsIDPrefix + 10)
DECLARE_PMID(kPerformanceMetricIDSpace,	kImageCacheAllocPerfID,					kPerformanceMetricsIDPrefix + 11)
DECLARE_PMID(kPerformanceMetricIDSpace,	kImageCacheAllocPeakPerfID,				kPerformanceMetricsIDPrefix + 12)
DECLARE_PMID(kPerformanceMetricIDSpace,	kImageCacheFileBytesReadPerfID,			kPerformanceMetricsIDPrefix + 13)
DECLARE_PMID(kPerformanceMetricIDSpace,	kImageCacheFileBytesWrittenPerfID,		kPerformanceMetricsIDPrefix + 14)
DECLARE_PMID(kPerformanceMetricIDSpace,	kImageCacheFileReadTimePerfID,			kPerformanceMetricsIDPrefix + 15)
DECLARE_PMID(kPerformanceMetricIDSpace,	kImageCacheFileWriteTimePerfID,			kPerformanceMetricsIDPrefix + 16)
DECLARE_PMID(kPerformanceMetricIDSpace,	kVXferAllocPerfID,						kPerformanceMetricsIDPrefix + 17)
DECLARE_PMID(kPerformanceMetricIDSpace,	kVXferAllocPeakPerfID,					kPerformanceMetricsIDPrefix + 18)
DECLARE_PMID(kPerformanceMetricIDSpace,	kVXferBytesReadPerfID,					kPerformanceMetricsIDPrefix + 19)
DECLARE_PMID(kPerformanceMetricIDSpace,	kVXferBytesWrittenPerfID,				kPerformanceMetricsIDPrefix + 20)
DECLARE_PMID(kPerformanceMetricIDSpace,	kVXferReadTimePerfID,					kPerformanceMetricsIDPrefix + 21)
DECLARE_PMID(kPerformanceMetricIDSpace,	kVXferWriteTimePerfID,					kPerformanceMetricsIDPrefix + 22)
DECLARE_PMID(kPerformanceMetricIDSpace,	kVXferFileBytesReadPerfID,				kPerformanceMetricsIDPrefix + 23)
DECLARE_PMID(kPerformanceMetricIDSpace,	kVXFerFileBytesWrittenPerfID,			kPerformanceMetricsIDPrefix + 24)
DECLARE_PMID(kPerformanceMetricIDSpace,	kProcessIOBytesReadPerfID,				kPerformanceMetricsIDPrefix + 25)
DECLARE_PMID(kPerformanceMetricIDSpace,	kProcessIOBytesWrittenPerfID,			kPerformanceMetricsIDPrefix + 26)
DECLARE_PMID(kPerformanceMetricIDSpace,	kAGMXShowTimePerfID,					kPerformanceMetricsIDPrefix + 27)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDBFileBytesReadPerfID,					kPerformanceMetricsIDPrefix + 28)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDBFileBytesWritePerfID,				kPerformanceMetricsIDPrefix + 29)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDBFileReadTimePerfID,					kPerformanceMetricsIDPrefix + 30)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDBFileWriteTimePerfID,					kPerformanceMetricsIDPrefix + 31)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDropShadowMemReadTimePerfID,			kPerformanceMetricsIDPrefix + 32)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDropShadowMemReadBytesPerfID,			kPerformanceMetricsIDPrefix + 33)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDropShadowMemWriteTimePerfID,			kPerformanceMetricsIDPrefix + 34)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDropShadowMemWriteBytesPerfID,			kPerformanceMetricsIDPrefix + 35)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDropShadowFileReadTimePerfID,			kPerformanceMetricsIDPrefix + 36)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDropShadowFileReadBytesPerfID,			kPerformanceMetricsIDPrefix + 37)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDropShadowFileWriteTimePerfID,			kPerformanceMetricsIDPrefix + 38)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDropShadowFileWriteBytesPerfID,		kPerformanceMetricsIDPrefix + 39)
DECLARE_PMID(kPerformanceMetricIDSpace,	kChangeMgrUpdateCallCountPerfID,		kPerformanceMetricsIDPrefix + 40)
DECLARE_PMID(kPerformanceMetricIDSpace,	kChangeMgrUpdateCallTimePerfID,			kPerformanceMetricsIDPrefix + 41)
DECLARE_PMID(kPerformanceMetricIDSpace,	kSnapshotCountPerfID,					kPerformanceMetricsIDPrefix + 42)
DECLARE_PMID(kPerformanceMetricIDSpace,	kGalleyCompositionTimePerfID,			kPerformanceMetricsIDPrefix + 43)
DECLARE_PMID(kPerformanceMetricIDSpace,	kLayoutCompositionTimePerfID,			kPerformanceMetricsIDPrefix + 44)
DECLARE_PMID(kPerformanceMetricIDSpace,	kGalleyCompositionCountPerfID,			kPerformanceMetricsIDPrefix + 45)
DECLARE_PMID(kPerformanceMetricIDSpace,	kLayoutCompositionCountPerfID,			kPerformanceMetricsIDPrefix + 46)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDrawMgrDrawTimePerfID,					kPerformanceMetricsIDPrefix + 47)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDrawMgrNumInterruptsPerfID,			kPerformanceMetricsIDPrefix + 48)
DECLARE_PMID(kPerformanceMetricIDSpace,	kSnapshotReadWriteTimePerfID,			kPerformanceMetricsIDPrefix + 49)
DECLARE_PMID(kPerformanceMetricIDSpace,	kNewSnapshotTimePerfID,					kPerformanceMetricsIDPrefix + 50)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDBNewUIDCountPerfID,					kPerformanceMetricsIDPrefix + 51)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDBInstantiateCountPerfID,				kPerformanceMetricsIDPrefix + 52)
DECLARE_PMID(kPerformanceMetricIDSpace,	kInstanceCachePurgeCountPerfID,			kPerformanceMetricsIDPrefix + 53)
DECLARE_PMID(kPerformanceMetricIDSpace,	kMinisaveCountPerfID,					kPerformanceMetricsIDPrefix + 54)
DECLARE_PMID(kPerformanceMetricIDSpace,	kXMPFilterTimePerfID,					kPerformanceMetricsIDPrefix + 55)
DECLARE_PMID(kPerformanceMetricIDSpace,	kSnapshotReadWriteByteCountPerfID,		kPerformanceMetricsIDPrefix + 56)
DECLARE_PMID(kPerformanceMetricIDSpace,	kDBFilePageReadsPerfID,					kPerformanceMetricsIDPrefix + 57)
DECLARE_PMID(kPerformanceMetricIDSpace, kLastRevInfoCountPerfID,				kPerformanceMetricsIDPrefix + 58)
DECLARE_PMID(kPerformanceMetricIDSpace,	kLastRevInfoReadWriteTimePerfID,		kPerformanceMetricsIDPrefix + 59)
DECLARE_PMID(kPerformanceMetricIDSpace,	kNewLastRevInfoTimePerfID,				kPerformanceMetricsIDPrefix + 60)
DECLARE_PMID(kPerformanceMetricIDSpace,	kLastRevInfoReadWriteByteCountPerfID,	kPerformanceMetricsIDPrefix + 61)

DECLARE_PMID(kPerformanceMetricIDSpace,	kCPUTimePerfID,							kPerformanceMetricsIDPrefix + 62)
DECLARE_PMID(kPerformanceMetricIDSpace,	kNThreadsPerfID,						kPerformanceMetricsIDPrefix + 63)
DECLARE_PMID(kPerformanceMetricIDSpace,	kOverallSystemCPUTimePerfID,			kPerformanceMetricsIDPrefix + 64)
DECLARE_PMID(kPerformanceMetricIDSpace,	kOverallUserCPUTimePerfID,				kPerformanceMetricsIDPrefix + 65)
DECLARE_PMID(kPerformanceMetricIDSpace,	kCoreAllocationsPerfID,					kPerformanceMetricsIDPrefix + 66)
DECLARE_PMID(kPerformanceMetricIDSpace,	kCoreSizePerfID,						kPerformanceMetricsIDPrefix + 67)
DECLARE_PMID(kPerformanceMetricIDSpace,	kResidentSizePerfID,					kPerformanceMetricsIDPrefix + 68)
DECLARE_PMID(kPerformanceMetricIDSpace,	kVirtualSizePerfID,						kPerformanceMetricsIDPrefix + 69)
DECLARE_PMID(kPerformanceMetricIDSpace,	kHandleCountPerfID,						kPerformanceMetricsIDPrefix + 70)
DECLARE_PMID(kPerformanceMetricIDSpace,	kGDIObjectCountPerfID,					kPerformanceMetricsIDPrefix + 71)
DECLARE_PMID(kPerformanceMetricIDSpace,	kMemoryMarkPerfID,						kPerformanceMetricsIDPrefix + 72)
DECLARE_PMID(kPerformanceMetricIDSpace, kLayoutSlowDrawFramesPerfID,			kPerformanceMetricsIDPrefix + 73)
DECLARE_PMID(kPerformanceMetricIDSpace, kLayoutAvgFPSPerfID,					kPerformanceMetricsIDPrefix + 74)
#endif // __PerformanceMetricsID__
