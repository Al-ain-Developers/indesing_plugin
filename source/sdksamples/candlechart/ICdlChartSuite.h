//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/ICdlChartSuite.h $
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

#ifndef __ICdlChartSuite_h__
#define __ICdlChartSuite_h__

// Interface includes:
#include "IPMUnknown.h"

// General includes:
// none.

// Project includes:
#include "CdlChartID.h"
#include "ICdlChartData.h"

// Forward declarations:
class PMString;

/** From SDK sample; suite interface that extends the capability of the selection
	so that it can manipulate the value of ICdlChartData associated with the 
	objects that are currently selected.

	@ingroup candlechart
	
	@see Selection fundamentals chapter in Programming Guide
*/
class ICdlChartSuite : public IPMUnknown
{
//	Data Types
public:
	enum { kDefaultIID = IID_ICDLCHARTSUITE };

//	Member functions
	/** Check if it is able to get name of the chart.
		@return kTrue if the caller can apply IBPIData to the objects that are currently selected, kFalse otherwise.
	*/
	virtual bool16 CanGetChartName() = 0;

	/** Apply the given value for CdlStockChartData to the objects that are currently selected.
		@pre ICdlChartSuite::CanGetChartName returns kTrue
		@param outChartName OUT the name of the stock chart data.
		@return kSuccess if the value was applied successfully, kFailure otherwise.
	*/
	virtual ErrorCode GetChartName(WideString& outChartName) = 0;
};

#endif // _ICdlChartSuite_

// End, ICdlChartSuite.h


