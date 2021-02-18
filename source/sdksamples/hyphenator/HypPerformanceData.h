//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypPerformanceData.h $
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

#pragma once

#ifndef __HypPerformanceData_h__
#define __HypPerformanceData_h__

#include <boost/thread/mutex.hpp>

/**	Class with methods to aceess performance data for Hyphenator.
 @ingroup hyphenator
 */
class HypPerformanceData
{
public:
	/**	Get the maximum number of hyphenations in any word.
	 */
	static uint64 GetHypMax();
	
	/**	Set the maximum number of hyphenations in any word.
	 @param data of maximum number of hyphenations.
	 */
	static void SetHypMax(uint64 data);
	
	/**	Increment the maximum number of hyphenations in any word.
	 */
	static void IncrementHypMax();
	
	/**	Get the total number of hyphenation calls.
	 */
	static uint64 GetHypTotal();
	
	/**	Set the total number of hyphenation calls.
	 @param data of total number of hyphenation calls.
	 */
	static void SetHypTotal(uint64 data);
	
	/**	Increment the total number of hyphenation calls.
	 */
	static void IncrementHypTotal();
	
private:
	static boost::mutex fMutex;
	static uint64 fHypMax;
	static uint64 fHypTotal;
	
};

#endif // __HypPerformanceData_h__


