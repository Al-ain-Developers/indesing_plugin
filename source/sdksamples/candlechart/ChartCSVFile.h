//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/ChartCSVFile.h $
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

#ifndef __ChartCSVFile_h__
#define __ChartCSVFile_h__

// Interface includes:
#include "ICdlChartData.h"
#include "PMString.h"

// Forward declarations:
class IPMStream;

/** Loads a CSV file for stock chart data.

	@ingroup candlechart
	
*/
class ChartCSVFile
{
public:

	/** Load the given CSV file to prepare for create candle chart page item.
		@param inFile IN the CSV file to be streamed in.
		@param outName OUT is the candle chart name we are going to create (from file name).
		@param outChartData OUT is the stock data to be saved.
		@return kTrue if the CSV data is loaded successfully, otherwise kFalse.
	*/
	static bool16 LoadFile(IDFile& inFile, PMString& outName, CdlStockChartData& outChartData);

	/** Read the given CSV file into the stock data.
		@param inFile IN the CSV file to be streamed in.
		@param outChartData OUT is the stock data to be saved.
		@return kTrue if the CSV data is loaded successfully, otherwise kFalse.
	*/
	static bool16 ReadFile(IDFile& inFile, CdlStockChartData& outChartData);

private:

	/**	Remove LF char if there.
		@param inStream IN stream to be streamed in.
	*/
	static void RemoveLF(IPMStream* inStream);

	/** Read a line from stream and store as a string.
		@param inStream IN stream to be streamed in.
		@param outStr OUT the read line.
		@return kTrue if CSV load data successfully, otherwise kFalse.
	*/
	static bool16 ReadLine(IPMStream* inStream, PMString& outStr);

	/**	Read a header line of the CSV file stream.
		@param inStream IN stream be streamed in.
		@return kTrue if a line is read successfully, otherwise kFalse.
	*/
	static bool16 ReadHeader(IPMStream* inStream);

	/** Reading date string from stream until it reach to comma.
		@param inStream IN stream to be streamed in.
		@param outDate OUT the date read.
		@return kTrue if date is read successfully, otherwise kFalse.
	*/
	static bool16 ReadDate(IPMStream* inStream, PMString& outDate);

	/** Reading real number from stream until it reach to comma or LF.
		@param inStream IN stream to be streamed in.
		@param outValue OUT the value read. 
		@return kTrue if real number is read successfully, otherwise kFalse.
	*/
	static bool16 ReadDouble(IPMStream* inStream, double& outValue);
	
	/**	Read the entire body data until it reach to the end of file.
		@param inStream IN stream to be streamed in.
		@param outStockData OUT stock data read.
		@return kTrue if CSV data is read successfully, otherwise kFalse.
	*/
	static bool16 ReadData(IPMStream* inStream, CdlStockData& outStockData);
};

#endif // __ChartCSVFile_h__

