//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartData.cpp $
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
#include "IPMStream.h"

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "CdlChartID.h"
#include "ICdlChartData.h"

/**	Handles stock data (open, high, low, close, volume).

	@ingroup candlechart
	
*/
class CdlChartData : public CPMUnknown<ICdlChartData>
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CdlChartData(IPMUnknown* boss);

	/** The stock data to be used in candle chart can be given with this method.
		@param inStockData IN can holds number of StockData in array. The data has to be set before calling this method.
	*/
	virtual void Set(const CdlStockChartData& inStockData);

	/** Retreives stock data in array.
	*/
	virtual CdlStockChartData Get() const;


	/** Sets name for the chart.
		@param inNameStr IN string of the name to give.
	*/
	virtual void SetName(const WideString& inNameStr);

	/**	Gets name from the chart.
		@param outNameStr OUT string for the name to be given.
	*/
	virtual void GetName(WideString& outNameStr) const;

	/**	Reads and writes chart data to be displayed.
		@param stream IN contains the stream to be written or read.
		@param implementation IN the implementation ID.
	*/
	void ReadWrite(IPMStream* stream, ImplementationID implementation);

private:
	WideString fNameStr;
	CdlStockChartData fStockData;
};


CREATE_PERSIST_PMINTERFACE(CdlChartData, kCdlChartDataImpl)

/*	Constructor
*/
CdlChartData::CdlChartData(IPMUnknown* boss) 
	: CPMUnknown<ICdlChartData>(boss)
{
	fStockData.clear();
}

/*	Set
*/
void CdlChartData::Set(const CdlStockChartData& inStockData)
{
	if (fStockData != inStockData)
	{
		PreDirty ();
		fStockData = inStockData;
		
	}
}

/*	Get
*/
CdlStockChartData CdlChartData::Get() const
{
	return fStockData;
}

/*	ReadWrite
*/
void CdlChartData::ReadWrite(IPMStream* stream, ImplementationID implementation)
{
		
	//	REMINDER: 
	//	If you change the arrangement of persistent data in this method, 
	//	remember to update the format number in the PluginVersion resource.
	//	(See the CdlChartID.h file for the plug-in specific format numbers.) 


	int16   version = 0x01;
	stream->XferInt16(version);

	fNameStr.ReadWrite(stream);

	int16 stockDataLength = fStockData.size();
	stream->XferInt16(stockDataLength);

	CdlStockData data;
	PMReal  c;

	if (stream->IsReading())
	{
		fStockData.clear();
		fStockData.reserve(stockDataLength);

		for (int16 i = 0; i < stockDataLength; i++)
		{
			stream->XferRealNumber(c);
			data.open = ToDouble(c);
			stream->XferRealNumber(c);
			data.high = ToDouble(c);
			stream->XferRealNumber(c);
			data.low = ToDouble(c);
			stream->XferRealNumber(c);
			data.close = ToDouble(c);
			stream->XferRealNumber(c);
			data.volume = ToDouble(c);
			fStockData.push_back(data);              
		}
	}
	else
	{
		for (int16 i = 0; i < stockDataLength; i++)
		{
			data = fStockData[i];

			c = data.open;
			stream->XferRealNumber(c);
			c = data.high;
			stream->XferRealNumber(c);
			c = data.low;
			stream->XferRealNumber(c);
			c = data.close;
			stream->XferRealNumber(c);
			c = data.volume;
			stream->XferRealNumber(c);
		}
	}
}


/*	SetName
*/
void CdlChartData::SetName(const WideString& inNameStr)
{
	PreDirty ();
	fNameStr = inNameStr;
	//fNameStr.SetTranslatable(kFalse);
	
}

/*	GetName
*/
void CdlChartData::GetName(WideString& outNameStr) const
{
	outNameStr = fNameStr;
}

// End, CdlChartData.cpp.
