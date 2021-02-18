//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/examplefiles/ListAllPerformanceMetrics.jsx $
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
//  
//========================================================================================

function ListAllMetrics()
{
	metricList = app.performanceMetrics;
	nMetrics = metricList.length;	
	for (var i = 0; i < nMetrics; i++)
	{
		metricID = metricList[i]; 

		// list the metric information, accessed by metric id...
		metricValue = app.performanceMetric(metricID);
		metricShortName = app.performanceMetricShortName(metricID);
		metricLongName = app.performanceMetricLongName(metricID);
		
		outString = " ID: " + String(metricID);
		outString += "  " + metricShortName+ " (" + metricLongName + ")" ;
		outString += " = " + String(metricValue);
		
		app.consoleout(outString);
	}
}

ListAllMetrics();

// The following code outputs the built-in metrics, accessed by name...
app.consoleout(app.performanceMetric(PerformanceMetricOptions.cpuTime)+"       CPU time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.numberOfThreads)+"      number of threads");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.overallSystemCPU)+"      overall system CPU");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.overallUserCPU)+"      overall user CPU");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.coreAllocationCount)+"      core allocation count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.coreMemorySize)+"      core memory size");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.residentMemorySize)+"      resident memory size");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.virtualMemorySize)+"      virtual memory size");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.currentMemoryMark)+"      current memory mark");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.handleCount)+"      handle count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.gdiObjectCount)+"      GDI object count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.heapAllocations)+"      heap allocations");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.heapAllocationsPeak)+"      heap allocations peak");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.memoryPurgeCount)+"      memory purge count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.memoryPurgeTime)+"      memory purge time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.bibAllocations)+"      BIB Allocations");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.bibAllocationsPeak)+"      BIB Allocations peak");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.bibCache)+"      BIB cache");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.bibCachePeak)+"      BIB cache peak");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.pdfAllocactions)+"      PDF allocactions");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.pdfAllocactionsPeak)+"      PDF allocactions peak");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.imageCacheAllocations)+"      image cache allocations");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.imageCacheAllocationsPeak)+"      image cache allocations peak");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.imageCacheFileBytesRead)+"      image cache file bytes read");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.imageCacheFileBytesWritten)+"      image cache file bytes written");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.imageCacheFileReadTime)+"      image cache file read time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.imageCacheFileWriteTime)+"      image cache file write time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.vxferalloc)+"      VXferAlloc");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.vxferallocpeak)+"      VXferAllocPeak");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.vxferbytesread)+"      VXferBytesRead");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.vxferbyteswritten)+"      VXferBytesWritten");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.vxferreadtime)+"      VXferReadTime");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.vxferwritetime)+"      VXferWriteTime");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.vxferfilebytesread)+"      VXferFileBytesRead");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.vxferfilebyteswritten)+"      VXFerFileBytesWritten");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.processIOBytesRead)+"      process IO bytes read");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.processIOBytesWritten)+"      process IO bytes written");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.agmxshowtime)+"      AGMXShowTime");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.databaseFileBytesRead)+"      database file bytes read");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.databaseFileBytesWritten)+"      database file bytes written");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.databaseFileReadTime)+"      database file read time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.databaseFileWriteTime)+"      database file write time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.dropShadowMemoryReadTime)+"      drop shadow memory read time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.dropShadowMemoryReadBytes)+"      drop shadow memory read bytes");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.dropShadowMemoryWriteTime)+"      drop shadow memory write time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.dropShadowMemoryWriteBytes)+"      drop shadow memory write bytes");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.dropShadowFileReadTime)+"      drop shadow file read time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.dropShadowFileReadBytes)+"      drop shadow file read bytes");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.dropShadowFileWriteTime)+"      drop shadow file write time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.dropShadowFileWriteBytes)+"      drop shadow file write bytes");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.changeManagerUpdateCallCount)+"      change manager update call count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.changeManagerUpdateCallTime)+"      change manager update call time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.snapshotCount)+"      snapshot count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.galleyCompositionTime)+"      galley composition time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.layoutCompositionTime)+"      layout composition time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.galleyCompositionCount)+"      galley composition count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.layoutCompositionCount)+"      layout composition count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.drawManagerDrawTime)+"      draw manager draw time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.drawManagerNumberOfInterrupts)+"      draw manager number of interrupts");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.snapshotReadWriteTime)+"      snapshot read write time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.newSnapshotTime)+"      new snapshot time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.databaseNewUIDCount)+"      database new UID count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.databaseInstantiateCount)+"      database instantiate count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.instanceCachePurgeCount)+"      instance cache purge count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.minisaveCount)+"      minisave count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.xmpFilterTime)+"      XMP filter time");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.snapshotReadWriteByteCount)+"      snapshot read write byte count");
app.consoleout(app.performanceMetric(PerformanceMetricOptions.databaseFilePageReads)+"      database file page reads");
