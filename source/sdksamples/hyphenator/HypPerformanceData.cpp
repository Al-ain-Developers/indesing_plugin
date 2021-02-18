//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypPerformanceData.cpp $
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

// Interface includes:

// General includes:

// Project includes:
#include "HypPerformanceData.h"

/** Implementation with methods to access performance data for Hyphenator. 
 @ingroup hyphenator
*/

uint64 HypPerformanceData::fHypMax = 0;
uint64 HypPerformanceData::fHypTotal = 0;
boost::mutex HypPerformanceData::fMutex;

/**	Get the maximum number of hyphenations in any word.
 */
uint64 HypPerformanceData::GetHypMax()
{
	return fHypMax;
}

/**	Set the maximum number of hyphenations in any word.
 @param data of maximum number of hyphenations.
 */
void HypPerformanceData::SetHypMax(uint64 data)
{
	boost::mutex::scoped_lock lock(fMutex);
	fHypMax = data;
}

/**	Increment the maximum number of hyphenations in any word.
 */
void HypPerformanceData::IncrementHypMax()
{
	boost::mutex::scoped_lock lock(fMutex);
	++fHypMax;
}
		
/**	Get the total number of hyphenation calls.
 */
uint64 HypPerformanceData::GetHypTotal()
{
	return fHypTotal;
}
		
/**	Set the total number of hyphenation calls.
 @param data of total number of hyphenation calls.
 */
void HypPerformanceData::SetHypTotal(uint64 data)
{
	boost::mutex::scoped_lock lock(fMutex);
	fHypTotal = data;
}
		
/**	Increment the total number of hyphenation calls.
 */
void HypPerformanceData::IncrementHypTotal()
{
	boost::mutex::scoped_lock lock(fMutex);
	++fHypTotal;
}

// End, HypPerformanceData.cpp