//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/ChartCSVFile.cpp $
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
#include "IOpenFileDialog.h"

// General includes:
#include "DocumentID.h"
#include "StreamUtil.h"
#include "SysFileList.h"
#include "SDKFileHelper.h"

// Project includes:
#include "ChartCSVFile.h"


static const SysOSType kSysOSType_CSVFileType = 'TEXT';
static const PMString kPMString_CSVFileFamily("CSV");
static const PMString kPMString_CSVFileExtension("CSV");

static const char k_UNIXDELCHAR = '/';
static const char k_MACDELCHAR = ':';
static const char k_WINDELCHAR = '\\';


/*	LoadFile
*/
bool16 ChartCSVFile::LoadFile(IDFile& inFile, PMString& outName, CdlStockChartData& outChartData)
{
	bool16 success = kFalse;
	do
	{
		// get the name of the path
		SDKFileHelper fileHelper(inFile);
		PMString pathNameStr = fileHelper.GetPath();
		if (pathNameStr.empty())
			break;
		// ipaterso commented out Watson 1149689
		// pathNameStr.SetTranslated();

		// initialize outName
		if (!outName.empty())
			outName.Clear();
		for (int i=pathNameStr.WCharLength()-1 ; i>=0 ; i--)
		{
			if (pathNameStr[i] == k_UNIXDELCHAR ||
				pathNameStr[i] == k_MACDELCHAR ||
				pathNameStr[i] == k_WINDELCHAR)
			{
				break;
			}
			outName.Insert(pathNameStr[i], 0);
		}
        // Read data from the file
		if (!ChartCSVFile::ReadFile(inFile, outChartData))
		{
			break;
		}

		// success
		success = kTrue;

	} while (kFalse);

	return success;
}


/*	ReadFile
*/
bool16 ChartCSVFile::ReadFile(IDFile& inFile, CdlStockChartData& outChartData)
{
	bool16 success = kFalse;

	CdlStockData stockData;
	do
	{
		// Open the file as a stream:
		InterfacePtr<IPMStream> iStream(StreamUtil::CreateFileStreamRead(inFile));
		if (iStream == nil)
		{
			ASSERT_FAIL("Couldn't create stream for file");
			break;
		}

		// Read header
		if (!ReadHeader(iStream))
			break;

		// Read chart data
		while (iStream->GetStreamState() == kStreamStateGood)
		{
			if (ReadData(iStream, stockData))
				outChartData.push_back(stockData);
			else
				break;
		}

		// Close the stream
		iStream->Close();

		// success
		success = kTrue;

	} while (kFalse);

	return success;
}


/*	RemoveLF
*/
void ChartCSVFile::RemoveLF(IPMStream* inStream)
{
	uchar       ch(0);
	if (inStream->GetStreamState() == kStreamStateGood)
	{
		inStream->XferByte(ch);
		if (ch != 0x0a)
		{
			inStream->Seek(-1, kSeekFromCurrent);
		}
	}
}

/*	ReadLine
*/
bool16 ChartCSVFile::ReadLine(IPMStream* inStream, PMString& outStr)
{
	outStr.Clear();
	outStr.SetTranslatable(kFalse);
	uchar ch(0);
	while (inStream->GetStreamState() == kStreamStateGood)
	{
		inStream->XferByte(ch);
		if (ch == 0x0a || ch == 0x0d)
		{
			if (ch == 0x0d)
			{
				RemoveLF(inStream);		// in case CR LF
			}
			return kTrue;
		}
		outStr.Append((char)ch);
	}
	return kFalse;
}

/*	ReadHeader
*/
bool16 ChartCSVFile::ReadHeader(IPMStream* inStream)
{
	PMString headerStr("Date,Open,High,Low,Close,Volume", PMString::kEncodingASCII);
	PMString lineStr;
	if (!ReadLine(inStream, lineStr))
	{
		return kFalse;
	}

	if (!lineStr.IsEqual(headerStr, kFalse))
	{
		return kFalse;
	}

	return kTrue;
}

/*	ReadDate
*/
bool16 ChartCSVFile::ReadDate(IPMStream* inStream, PMString& outDate)
{
	outDate.Clear();
	outDate.SetTranslatable(kFalse);
	uchar ch(0);
	while (inStream->GetStreamState() == kStreamStateGood)
	{
		inStream->XferByte(ch);
		if (ch == ',')
		{
			return kTrue;
		}
		outDate.Append((char)ch);
	}
	return kFalse;
}

/*	ReadDouble
*/
bool16 ChartCSVFile::ReadDouble(IPMStream* inStream, double& outValue)
{
	uchar ch(0);
	PMString valueStr;
	valueStr.SetTranslatable(kFalse);
	while (inStream->GetStreamState() == kStreamStateGood)
	{
		inStream->XferByte(ch);
		if (ch == ',' || ch == 0x0a || ch == 0x0d)
		{
			if (ch == 0x0d)
			{
				RemoveLF(inStream);		// in case CR LF
			}

			outValue = valueStr.GetAsDouble();
			return kTrue;
		}
		valueStr.Append((char)ch);
	}
	outValue = 0;
	return kFalse;
}

/*	ReadData
*/
bool16 ChartCSVFile::ReadData(IPMStream* inStream, CdlStockData& outStockData)
{
	PMString dayStr;

	if (!ReadDate(inStream, dayStr))
	{
		return kFalse;
	}
	if (!ReadDouble(inStream, outStockData.open))
	{
		return kFalse;
	}
	if (!ReadDouble(inStream, outStockData.high))
	{
		return kFalse;
	}
	if (!ReadDouble(inStream, outStockData.low))
	{
		return kFalse;
	}
	if (!ReadDouble(inStream, outStockData.close))
	{
		return kFalse;
	}
	if (!ReadDouble(inStream, outStockData.volume))
	{
		return kFalse;
	}

	return kTrue;
}

// End, ChartCSVFile.cpp.
