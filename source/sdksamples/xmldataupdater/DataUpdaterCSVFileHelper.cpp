//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterCSVFileHelper.cpp $
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

// Interfaces:

// General:
#include "StreamUtil.h"
#include "FileUtils.h"

// Project:
#include "DataUpdaterID.h"
#include "DataUpdaterCSVFileHelper.h"
#include "DataUpdaterConst.h"
/**
	@ingroup xmldataupdater

	@ingroup xmldataupdaterui
*/
// Filename/path parsing characters
const char kchar_WinPathSeparator = '\\';
const char kchar_ExtensionSeparator = '.';
const char kchar_TableNameSeparator = '_';

/*
*/
DataUpdaterCSVFileHelper::DataUpdaterCSVFileHelper()
{
}

/*
*/
DataUpdaterCSVFileHelper::~DataUpdaterCSVFileHelper()
{
}


/*	Load
*/
ErrorCode DataUpdaterCSVFileHelper::Load(const IDFile& file)
{
	ErrorCode result = kDataUpdaterOpenFileErrorCode;

	// We'll use a do-while(false) to break out on errors:
	do {

		// Open the file as a stream:
		InterfacePtr<IPMStream> iPMStream(StreamUtil::CreateFileStreamRead(file));
		if (iPMStream == nil) {
			break;
		}
		
		// Verify that the file contains comma separated values.  
		result = this->Verify(iPMStream);
		if (result != kSuccess)
		{
			// It doesn't.  Close the stream and return.
			iPMStream->Close();
			break;
		}

		// Load the CSV file header record into fFields:
		int32 fieldsPerRecord = LoadFields(iPMStream);

		// Load the remainder of the CSV file into fKeys and fValues
		LoadKeysAndValues(iPMStream, fieldsPerRecord);

	 	// The stream will be at EOF if everything is OK:
		bool16 loaded = iPMStream->GetStreamState() == kStreamStateEOF;

		// Set up fTableName and fFileName
		LoadDone(file);

		// Close the stream:
		iPMStream->Close();

		if (!loaded) {
			break;
		}

		result = kSuccess;

	} while (false); // Only do once.

	return result; // Indicates whether we were successful.
}

/*	Verify
*/
ErrorCode DataUpdaterCSVFileHelper::Verify(IPMStream* iPMStream)
{
	ErrorCode errFlag = kSuccess;

	// Reset the stream to the start of the file
	iPMStream->Seek(0, kSeekFromStart);

	// Process the stream
	int32 charCount = 0;		// total count of chars read
	int32 fieldsPerRecord = 0;	// number of fields in line 1 (field headers)
	uchar oneChar(0);					
	PMString workString = "";
	
	// Scan the characters in the first line
	iPMStream->XferByte(oneChar);
	while (iPMStream->GetStreamState()==kStreamStateGood)
	{
		switch (oneChar)
		{
#if defined(WINDOWS)
			case kuchar_CR:
#elif defined(MACINTOSH)
			case kuchar_LF:
#endif
			case kuchar_Separator: // end of field
			{
				workString.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
				if (!workString.empty())
				{
					fieldsPerRecord++;
					workString.Clear();				
				}
				else
				{
					// blank field names not allowed
					errFlag = kDataUpdaterFileFormatErrorCode;
				}
				break;
			}

			default: //data
			{
				workString.Append((char)oneChar);
				charCount++;
				break;
			}	
		} // end switch
		
		// Apply some checks
		if (workString.GetPlatformString().length() > 255 || charCount > 4096)
		{
			// Too long.
			errFlag = kDataUpdaterFileFormatErrorCode;
		}
			
#if defined(WINDOWS)
		if (errFlag != kSuccess || oneChar == kuchar_CR)
#elif defined(MACINTOSH)
		if (errFlag != kSuccess || oneChar == kuchar_LF)
#endif
		{
			break;
		}	
			
		// Read the next character
		iPMStream->XferByte(oneChar);
		
	} // end while
	
	// Don't continue if we've already got an error:
	if (errFlag == kSuccess)
	{		
		// We're okay. Scan the next line & check it has the same number of fields:
		charCount = 0;
		int32 line2FieldCount = 0;
		int32 charsInField = 0;
		iPMStream->XferByte(oneChar);
		while (iPMStream->GetStreamState() == kStreamStateGood)
		{
			switch (oneChar)
			{
#if defined(WINDOWS)
				case kuchar_CR:
#elif defined(MACINTOSH)
				case kuchar_LF:
#endif
				case kuchar_Separator: // end of field
				{
					line2FieldCount++;
					charsInField = 0;
					break;
				}

				default: //data
				{
					charsInField++;
					charCount++;
					break;
				}	
			} // end switch
			
			// Apply some checks on the csv data
			if (charsInField > 255 || charCount > 4096)
			{
				errFlag = kDataUpdaterFileFormatErrorCode;
			}
				
			
#if defined(WINDOWS)
			if (errFlag != kSuccess || oneChar == kuchar_CR)
#elif defined(MACINTOSH)
			if (errFlag != kSuccess || oneChar == kuchar_LF)
#endif
			{
				break;
			}
					
			// Read the next character
			iPMStream->XferByte(oneChar);
			
		} // end while
		
		if (errFlag == kSuccess)
		{
			if (line2FieldCount != fieldsPerRecord)
			{
				errFlag = kDataUpdaterFileFormatErrorCode;
			}
		}

	}
	return errFlag;
}

/*	LoadFields
*/
int32 DataUpdaterCSVFileHelper::LoadFields(IPMStream* iPMStream)
{
	// We'll return the fieldsPerRecord.
	int32 fieldsPerRecord = 0;

	// Reset the stream to the start of the file
	iPMStream->Seek(0, kSeekFromStart);

	// Process the stream
	uchar oneChar(0);
	PMString workString;
	workString.SetTranslatable(kFalse);

	// The first line of the file contains the names of the column fields
	// These fields are read into the "Fields" widget

	// Scan the characters in the first line:
	iPMStream->XferByte(oneChar);
	while (iPMStream->GetStreamState()==kStreamStateGood)
	{
		switch (oneChar)
		{
#if defined(WINDOWS)
				case kuchar_CR:
#elif defined(MACINTOSH)
				case kuchar_LF:
#endif
				case kuchar_Separator: // end of field
					{
						workString.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
						workString.SetTranslatable(kFalse);
						this->fFields.push_back(WideString(workString));
						workString.Clear();
						fieldsPerRecord++;
						break;
					}

				default: //data
					{
						workString.Append((char)oneChar);
						break;
					}
		} // end switch

		// End of line?

#if defined(WINDOWS)
		if (oneChar == kuchar_CR)
#elif defined(MACINTOSH)
		if (oneChar == kuchar_LF)
#endif
		{
			break;
		}

		// Read the next character
		iPMStream->XferByte(oneChar);

	} // end while streamstategood


	return fieldsPerRecord;
}

/*	LoadKeysAndValues
*/
void DataUpdaterCSVFileHelper::LoadKeysAndValues
(
	IPMStream* iPMStream, 
	int32 fieldsPerRecord
)
{
	// Process the stream
	uchar oneChar(0);
	PMString workString;
	workString.SetTranslatable(kFalse);

	int32 fieldNumber = 1;
	int32 recordNumber = 1;
	iPMStream->XferByte(oneChar);

	while (iPMStream->GetStreamState()==kStreamStateGood)
	{
		switch (oneChar)
		{
		case kuchar_Separator: // end of field
			{
				if (fieldNumber <= fieldsPerRecord)
				{
					// Add the string to the values drop down
					workString.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
					workString.SetTranslatable(kFalse);
					fValues.push_back(WideString(workString));
					if (fieldNumber == 1)
					{
						fKeys.push_back(WideString(workString));
					}
				}

				TRACEFLOW("XMLDataUpdater", "DataUpdaterCSVFileHelper::Load() record [%d], field [%d] %s\n", recordNumber, fieldNumber, workString.GetUTF8String().c_str());
				fieldNumber++;
				workString = WideString(kWideString_DataUpdaterNull);
				break;

			}

#if defined(WINDOWS)
		case kuchar_CR: // end of record
#elif defined(MACINTOSH)
		case kuchar_LF:
#endif
			{
				TRACEFLOW("XMLDataUpdater", "DataUpdaterCSVFileHelper::Load() record [%d], field [%d] %s\n", recordNumber, fieldNumber, workString.GetUTF8String().c_str());
				if (fieldNumber == fieldsPerRecord)
				{
					workString.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
					workString.SetTranslatable(kFalse);
					fValues.push_back(WideString(workString));
				}
				else
				{
					// Pad the values if the record ended prematurely
					for (int32 iter = 0; iter < fieldsPerRecord - fieldNumber; iter++)
					{
						workString =  kWideString_DataUpdaterValueNotFound;
						workString.SetTranslatable(kFalse);
						fValues.push_back(WideString(workString));
					}
				}
				workString = kWideString_DataUpdaterNull;
				fieldNumber = 1;
				recordNumber++;
				break;
			}

#if defined(WINDOWS)
		case kuchar_LF: // ignore line feeds
			{
				break;
			}
#endif

		default: //data
			{
				workString.Append((char)oneChar);
				break;
			}
		} // end switch

		// Next character
		iPMStream->XferByte(oneChar);
	} // while streamstategood

	if (workString != kWideString_DataUpdaterNull && iPMStream->GetStreamState()==kStreamStateEOF)
	{
		if (fieldNumber <= fieldsPerRecord)
		{
			TRACEFLOW("XMLDataUpdater", "DataUpdaterCSVFileHelper::Load() record [%d], field [%d] %s\n", recordNumber, fieldNumber, workString.GetUTF8String().c_str());

			// Add the string to the values drop down
			workString.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
			workString.SetTranslatable(kFalse);
			fValues.push_back(WideString(workString));

			if (fieldNumber == 1)
			{
				// Add the string to the keys drop down
				fKeys.push_back(WideString(workString));
			}

			// Pad the values if the record ended prematurely
			for (int32 iter = 0; iter < fieldsPerRecord - fieldNumber ; iter++)
			{
				workString = kWideString_DataUpdaterValueNotFound;
				workString.SetTranslatable(kFalse);
				fValues.push_back(WideString(workString));
			}
		}
	}
}

/*	LoadDone
*/
void DataUpdaterCSVFileHelper::LoadDone(const IDFile& file)
{

	// Okay, now get the info and set it:
	PMString fileName;
	FileUtils::GetFileName(file, fileName);

	// Extract the table name from the file name
	// The file name has the form:
	//  <TableName>[_<Qualifier>][.csv]
	// e.g.
	//  Products_May.csv
	//  Products_Jun.csv
	//  Products.csv
	//  Products
	PMString tableName;

	// First make the table name eveything before the file extension
	{

		int32 i = fileName.IndexOfCharacter(kchar_ExtensionSeparator);
		if (i > 0)
		{
			PMString* tmp = fileName.Substring(0, i);
			tableName = *tmp;
			delete tmp;
		}
		else
			tableName = fileName;
	}

	// Now make the table name everything before the underscore
	{
		int32 i = tableName.IndexOfCharacter(kchar_TableNameSeparator);
		if (i > 0)
		{
			PMString* tmp = tableName.Substring(0, i);
			tableName = *tmp;
			delete tmp;
		}
	}

	// Save the table name 
	tableName.SetTranslatable(kFalse);
	fTableName = WideString(tableName);

	// Save the file name 
	fileName.SetTranslatable(kFalse);
	fFileName = fileName;
}

// end DataUpdaterCSVFileHelper.cpp

