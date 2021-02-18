//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/IDataUpdaterFacade.h $
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

#ifndef __IDataUpdaterFacade_h__
#define __IDataUpdaterFacade_h__

// Interface includes:
#include "IPMUnknown.h"

class ITextModel;
class RangeData;

// Project includes:
#include "DataUpdaterID.h"

/** From SDK sample; Abstract facade interface that encapsulates XMLDataUpdater features
	and functionality.

	@ingroup xmldataupdater
*/
class IDataUpdaterFacade : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATAUPDATERFACADE };
	

	/** Determine if data can be inserted.
		@param iTextModel IN the text model of the target story.
		@param textIndex IN the start of the range of text to examine.
		@param length the IN length of the range of text to examine.
		Return kSuccess if tag can be inserted, other ErrorCode otherwise.
	*/	
	virtual bool16 CanInsertData(ITextModel* iTextModel, TextIndex textIndex, int32 length) = 0;

	/** 
		Insert a xml tagged data.
		@pre IDataUpdaterFacade::CanInsertData == kTrue
		@param iTextModel IN the text model of the target story.
		@param textIndex IN the start of the range of text to examine.
		@param length the IN length of the range of text to examine.
		@param table IN the table for the data tag (see IDataUpdaterDataTagTextAttr::SetTable).
		@param record IN the key for the data tag (see IDataUpdaterDataTagTextAttr::SetKey).
		@param field IN the field for the data tag (see IDataUpdaterDataTagTextAttr::SetField).
		@param value IN the value for the data tag (see IDataUpdaterDataTagTextAttr::SetValue).
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode InsertData(ITextModel* iTextModel, TextIndex& textIndex, int32 length, const WideString& table, const WideString& record, const WideString& field, const WideString& value ) = 0;

	/** 
		Create all data for each value in the given CSV file.
		@pre IDataUpdaterFacade::CanInsertData == kTrue
		@param iTextModel IN the text model of the target story.
		@param textIndex IN the position in the text to insert the data.
		@param file IN CSV file containing the data.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode InsertAllData(ITextModel* iTextModel, TextIndex& textIndex, const IDFile& file) = 0;


	/** 
		Look for XML tagged data in all stories in the given document and update their values if they 
		can be updated with the data from new file.
		@param docUIDRef IN the target document.
		@param file IN CSV file containing data to be used to update xmldataupdater data tags in the document.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode UpdateData(const UIDRef& docUIDRef, const IDFile& file) = 0;

};

#endif
