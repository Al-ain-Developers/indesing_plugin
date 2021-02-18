//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartFacade.cpp $
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
#include "INewPageItemCmdData.h"

// Project includes:
#include "ICdlChartFacade.h"
#include "ChartCSVFile.h"



class CdlChartFacade : public CPMUnknown<ICdlChartFacade>
{
public:

	/** Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CdlChartFacade(IPMUnknown* boss);

	/**	Destructor
	*/
	virtual ~CdlChartFacade() {}


	/**	CreateCandleChart
		@param layerRef IN layer on which to create the candle chart.
		@param csvFile IN csv file containing the data used to create the candle chart.
		@param startPoint IN start point in pasteboard coordinates.
		@param endPoint IN end point in pasteboard coordinates.
	*/
	virtual ErrorCode CreateCandleChart(const UIDRef& layerRef,  
										const IDFile& csvFile, 
										const PMPoint& startPoint, 
										const PMPoint& endPoint) const;

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CdlChartFacade, kCdlChartFacadeImpl)



/* CreateCandleChart
 */
 CdlChartFacade::CdlChartFacade(IPMUnknown* boss) : CPMUnknown<ICdlChartFacade>(boss)
{
}



/* CreateCandleChart
 */
ErrorCode CdlChartFacade::CreateCandleChart(const UIDRef& layerRef,
											const IDFile& csvFile, 
											const PMPoint& startPoint, 
											const PMPoint& endPoint) const
{
	// Assume failure...
	ErrorCode status = kFailure;

	do
	{
		CdlStockChartData newStockData;
		PMString fileNameStr;

		// Read the file and store the data into newStockData
		IDFile theFile = csvFile;
		if (!ChartCSVFile::LoadFile(theFile, fileNameStr, newStockData))
		{
			ASSERT_FAIL("can't import candle chart data");
			break;
		}

		// Creating a command to place new candle stock chart page item
		InterfacePtr<ICommand> newCdlChartCmd(CmdUtils::CreateCommand(kNewCdlChartCmdBoss));
		if (newCdlChartCmd == nil)
		{
			ASSERT_FAIL("ICommand pointer nil");
			break;
		}

		// Obtain data setting interface for later use
		InterfacePtr<INewPageItemCmdData> newData(newCdlChartCmd, UseDefaultIID());
		if (newData == nil)
		{
			ASSERT_FAIL("INewPageItemCmdData pointer nil");
			break;
		}

		// Create the geometry for the new page item.
		PMPointList points;
		points.push_back(startPoint);
		points.push_back(endPoint);

		// Set options to fire the command
		newData->Set(layerRef.GetDataBase(), kCdlChartPageItemBoss, layerRef.GetUID(), points); 

		// Get ICdlChartData interface for setting chart data.
		InterfacePtr<ICdlChartData> cdlChartData(newCdlChartCmd, UseDefaultIID());
		if (cdlChartData == nil)
		{
			ASSERT_FAIL("cdlChartData pointer nil");
			break;
		}

		// Set actual chart data read from CSV file
		cdlChartData->Set(newStockData);
		cdlChartData->SetName(WideString(fileNameStr));

		// Process the command	
		status = CmdUtils::ProcessCommand(newCdlChartCmd);
		ASSERT(status == kSuccess);

	} while (false);
	return status;

}
