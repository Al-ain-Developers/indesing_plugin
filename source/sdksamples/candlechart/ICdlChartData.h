//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/ICdlChartData.h $
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

#ifndef __ICdlChartData_h__
#define __ICdlChartData_h__

// Interface includes:
#include "IPMUnknown.h"

// General includes:
#include "K2Vector.tpp"

// Project includes:
#include "CdlChartID.h"

/**	Candle chart stock price data.
	@ingroup candlechart
*/
class CdlStockData
{
public:
	/** This typedef allows CdlStockData to be put into a K2Vector as an object, 
	  	so that proper cleanup happens when destroyed..
	 */
	typedef object_type data_type;

	/** Opening price. */
	double          open;
	/** Daily high price */
	double          high;
	/** Daily low price */
	double          low;
	/** Closing price */
	double          close;
	/** Trading volume */
	double          volume;

	/** Equality operator */
	inline bool16   operator==(const CdlStockData& inData) const;
};

/** K2Vector of CdlStockData.
*/
typedef K2Vector<CdlStockData> CdlStockChartData;


/* operator ==
*/
inline bool16 CdlStockData::operator==(const CdlStockData& inData) const
{
	return	(open == inData.open && 
			 high == inData.high &&
			 low == inData.low &&
			 close == inData.close &&
			 volume == inData.volume);
}


/**	From SDK sample; interface with methods to get/set stock chart data for candle chart page item.
	@ingroup candlechart
*/
class ICdlChartData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICDLCHARTDATA };

	/**	Set the chart data to be set to candle chart page item.
		@param CdlStockChartData IN The data to be set. 
	*/
	virtual void Set(const CdlStockChartData& inStockData) = 0;

	/** Get the chart data used in candle chart page item.
		@return The candle chart data.
	*/
	virtual  CdlStockChartData Get() const = 0;

	/** Set name for the chart.
		@param inName IN Name to be display on panel.
	*/
	virtual void SetName(const WideString& inName) = 0;

	/** Get name of the chart.
		@param outName OUT Name that is set on the page item.
	*/
	virtual void GetName(WideString& outName) const = 0;
};

#endif // __ICdlChartData_h__


