//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdaterui/DataUpdaterUIDataModel.cpp $
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

// Interface includes

// Impl includes
#include "DataUpdaterCSVFileHelper.h"


// Project includes
#include "IDataUpdaterUIDataModel.h"


/**  Class representing a folder hierarchy. 
	@ingroup xmldataupdaterui
*/
class DataUpdaterUIDataModel : CPMUnknown<IDataUpdaterUIDataModel>
{
public:
	/** Default constructor */
	DataUpdaterUIDataModel(IPMUnknown* boss);

	/**	Destructor
	 */
	virtual ~DataUpdaterUIDataModel();

	/**	Accessor for the root path
		@return PMString the name of the table
	 */
	virtual PMString GetTable() const { return fDataFileHelper->fTableName ;}

	/**	Accessor for the root path
		@return PMString the name of the data file
	 */
	virtual PMString GetFileName() const { return fDataFileHelper->fFileName ;}


	/**	Determine the number of records of the data
		@return Returns number of record
	 */
	virtual int32 GetRecordCount(){ return fDataFileHelper->fKeys.size();}

	/**	Determine the number of records of the data
		@return Returns number of record
	 */
	virtual int32 GetFieldCount(){ return fDataFileHelper->fFields.size();}


	/**	Get the path associated with the specified child
		@param nthRec [IN] which record
		@param nthField [IN] specifies which field
		@return Returns path as string
	 */
	virtual PMString GetNthValue(int32 nthRec, int32 nthField); 

	/**	Get the path associated with the specified child
		@param nthField [IN] specifies which field
		@return Returns path as string
	 */
	virtual PMString GetNthField( int32 nthField) {return fDataFileHelper->fFields[nthField];} 

	/**	Determine the index of a field
		@param key [IN] specifies field string
		@return Returns index 
	 */
	virtual int32 GetFieldIndex(const PMString& field) {
		K2Vector<WideString>::const_iterator i = K2find(fDataFileHelper->fFields.begin(), fDataFileHelper->fFields.end(), WideString(field)); 
		return i != fDataFileHelper->fFields.end() ? i - fDataFileHelper->fFields.begin() : -1;
		} 

	/**	Has initialized
	 */
	virtual ErrorCode HasInitialized() {return fDataFileHelper != nil;};

	/**	Call when you change data file
	 */
	virtual ErrorCode Initialize(IDFile sysFile);


private:
	
	DataUpdaterCSVFileHelper * fDataFileHelper;


};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(DataUpdaterUIDataModel, kDataUpdaterUIDataModelImpl)


/* Constructor
*/
DataUpdaterUIDataModel::DataUpdaterUIDataModel(IPMUnknown* boss) : 
	CPMUnknown<IDataUpdaterUIDataModel>(boss),
	fDataFileHelper(nil)
{
}



	
/* Destructor
*/
DataUpdaterUIDataModel::~DataUpdaterUIDataModel()
{
	if (fDataFileHelper)
		delete fDataFileHelper;
}


/* deleteTree
*/
ErrorCode DataUpdaterUIDataModel::Initialize(IDFile sysFile) 
{
	if (fDataFileHelper)
		delete fDataFileHelper;
	fDataFileHelper = new DataUpdaterCSVFileHelper();
	return fDataFileHelper->Load(sysFile);
}



/* 
*/
PMString DataUpdaterUIDataModel::GetNthValue(int32 nthRec, int32 nthField)
{

	const int32 kFieldsPerRecord = fDataFileHelper->fFields.size();
	const int32 kMaxKeys = fDataFileHelper->fKeys.size();

	if (nthRec >= kMaxKeys ||  nthField >= kFieldsPerRecord)
		return PMString();

	int32 valueIndex = nthRec * kFieldsPerRecord + nthField;
	return fDataFileHelper->fValues [valueIndex];
}


//	end, File: DataUpdaterUIDataModel.cpp
