//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/ICdlChartFacade.h $
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

#ifndef __ICdlChartFacade_H_DEFINED__
#define __ICdlChartFacade_H_DEFINED__


// Interface includes:
#include "IPMUnknown.h"

// Project includes:
#include "CdlChartID.h"


/** Facade that wraps the commands needed to manage this
	plug-in's attributes.

	The implementation techniques shown in this class allow
	client suites to be called.
	See the CandleChartUI plug-in.
	
	@ingroup candlechart
	@see CandleChartUI
 */
class ICdlChartFacade : public IPMUnknown
{
public:

	/** Default interface identifier for UseDefaultIID 
		@see UseDefaultIID
	*/
	enum { kDefaultIID = IID_ICDLCHARTFACADE };


	/**	CreateCandleChart
		@param layerRef IN layer on which to create the candle chart.
		@param csvFile IN csv file containing the data used to create the candle chart.
		@param startPoint IN start point in pasteboard coordinates.
		@param endPoint IN end point in pasteboard coordinates.
	*/
	virtual ErrorCode CreateCandleChart(const UIDRef& layerRef, 
										const IDFile& csvFile, 
										const PMPoint& startPoint, 
										const PMPoint& endPoint) const = 0;

};


#endif	// __ICdlChartFacade_H_DEFINED__