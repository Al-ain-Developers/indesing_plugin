//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/ICHLUserDictUtils.h $
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

#pragma once

#ifndef __ICHLUserDictUtils__
#define __ICHLUserDictUtils__

#include "Utils.h"
#include "CHLID.h"
#include "IXMLOutStream.h"
#include "LanguageID.h"

class ILanguage;
class IUserDict;
class UserDictWordList;

/** Utilities for CHL User Dictionary
*/
class ICHLUserDictUtils : public IPMUnknown 
{
public:
	enum	{kDefaultIID = IID_ICHLUSERDICTUTILS};

	/**	Exports the CHL user dictionary XML for the specified language to 
		@param IDFile& 
		@param IUserDict* 
		@param UserDictWordList& 
		@param ILanguage* 
		@param IXMLOutStream::eEncodingType 
		@return ErrorCode result of the export
		*/
	virtual ErrorCode	ExportCHLUserDictXML(const IDFile& file, IUserDict* userDict, const UserDictWordList& userDictWordList, LanguageID languageID, IXMLOutStream::eEncodingType encoding = IXMLOutStream::kUTF16) = 0;
	
	/**	Imports the CHL user dictionary XML for the specified language 
		@param IDFile& 
		@param IUserDict* 
		@return ErrorCode result of the export
		*/
	virtual ErrorCode	ImportCHLUserDictXML(const IDFile& file, IUserDict* userDict) = 0;
};
	
#endif // __ICHLUserDictUtils__
