//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterCSVFileHelper.h $
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

#ifndef __DataUpdaterCSVFileHelper_h__
#define __DataUpdaterCSVFileHelper_h__

// Interfaces:
#include "IPanelControlData.h"
#include "IPMStream.h"

// General:
#include "WideString.h"
#include "K2Vector.h"

/** From SDK sample; DataUpdaterCSVFileHelper is a helper class for handling CSV files.

	A naming convention has been adopted for CSV filenames so you can have several files 
	within the same folder that give values for the same table of data. The naming 
	convention is: 

		Table[_Qualifier][.csv]

	where:

		[] - optional 

	So Inventory_Apr.csv and Inventory_May.csv, would all 
	specify values from the same table of data "Inventory". 

	For example consider the file "Inventory_Apr.csv" with contents:
	<pre>
		SKU, Price, Description
		A175, ?0, Electric Drill
		B456, ?, Hammer
		A767, ?, Screwdriver
	</pre>

	The first line contains the names of the fields in the file. These are loaded into 
	the fFields member. The first column contains the key for each record and must be 
	unique. These are loaded into the fKeys member. All values, including keys, are 
	loaded into the fValues member.

	Note that all the values from the CSV file are cached in this class. 

	@ingroup xmldataupdater

	@ingroup xmldataupdaterui
*/
class DataUpdaterCSVFileHelper
{
public:
	/** Constructor.
	*/
	DataUpdaterCSVFileHelper();

	/** Destructor.
	*/
	virtual ~DataUpdaterCSVFileHelper();

public:
	/** Load the given CSV file.
		@param file CSV file containing data to be loaded.
		@return kSuccess on success, kDataUpdaterOpenFileErrorCode if file could not be opened,
		kDataUpdaterFileFormatErrorCode if file is not a CSV file, other ErrorCode otherwise.
	*/
	ErrorCode Load(const IDFile& file);

public:
	/** The first field per line in the CSV file is loaded here.
		This field contains the key for the CSV file record and should be unique in the CSV file.
	*/
	K2Vector<WideString> fKeys;

	/** Fields in the first line of the CSV file are loaded here.
		The first line contains the names of the fields in the file.
	*/
	K2Vector<WideString> fFields;

	/** All fields in the second and subsequent lines of the CSV file are loaded here.
	*/
	K2Vector<WideString> fValues;

	/** The name of the table the CSV file represents derived
		from the CSV file naming convention described above.
	*/
	WideString fTableName;

	/** The CSV file name.
	*/
	PMString fFileName;

private:
	/** 
		Verify that the given stream looks like a CSV file. 
		Required guarantees: incoming iPMStream must be valid. 
		@param iPMStream is CSV data stream to be verified.
		@return kSuccess if the stream is a valid CSV data, other ErrorCode otherwise.
	*/
	ErrorCode Verify(IPMStream* iPMStream);

	/** 
		Load the fields in first line of the CSV file into fFields. 
		@param iPMStream is CSV data stream to be verified.
		@return the number of fields for this record.
	*/
	int32 LoadFields(IPMStream* iPMStream);

	/** 
		Load the first field in each record into fKey and all fields in each record into 
		fValues.
		@param iPMStream is CSV data stream that contains the csvdata.
		@param fieldsPerRecord the number of fields for this record.
	*/
	void LoadKeysAndValues(IPMStream* iPMStream, int32 fieldsPerRecord);

	/** 
		Initialise fTableName and fFileName.
		@param file is the CSV file.
	*/
	void LoadDone(const IDFile& file);

};

#endif

// End, DataUpdaterCSVFileHelper.h

