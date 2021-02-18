//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdaterui/IDataUpdaterUIDataModel.h $
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

#ifndef __IDataUpdaterUIDataModel_H__
#define __IDataUpdaterUIDataModel_H__

#include "IPMUnknown.h"
#include "DataUpdaterUIID.h"

/**
	Wrapper of DataUpdaterCSVFileHelper
	@ingroup xmldataupdaterui
*/
class IDataUpdaterUIDataModel : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATAUPDATERUIDATAMODEL };

	/**	Accessor for the root path
		@return PMString the name of the table
	 */
	virtual PMString GetTable() const =0 ;

	/**	Accessor for the root path
		@return PMString the name of the data file
	 */
	virtual PMString GetFileName() const =0 ;


	/**	Determine the number of records of the data
		@return Returns number of record
	 */
	virtual int32 GetRecordCount()=0; 

	/**	Determine the number of fields of a record
		@return Returns number of fields
	 */
	virtual int32 GetFieldCount()=0; 


	/**	Get the path associated with the specified child
		@param nthRec [IN] which record
		@param nthField [IN] specifies which field
		@return Returns path as string
	 */
	virtual PMString GetNthValue(int32 nthRec, int32 nthField)=0; 


	/**	Get the path associated with the specified child
		@param nthField [IN] specifies which field
		@return Returns path as string
	 */
	virtual PMString GetNthField( int32 nthField)=0; 

	/**	Determine the index of a field
		@param key [IN] specifies field string
		@return Returns index 
	 */
	virtual int32 GetFieldIndex(const PMString& field)=0; 

	/**	Has initialized
	 */
	virtual ErrorCode HasInitialized()=0;

	/**	Call when you change data file
	 */
	virtual ErrorCode Initialize(IDFile sysFile)=0;

};


#endif // __IDataUpdaterUIDataModel_H__

