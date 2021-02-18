//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/IAutoCorrectUtils.h $
//  
//  Owner: Heath Horton
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

#ifndef __IAutoCorrectUtils__
#define __IAutoCorrectUtils__

#include "Utils.h"
#include "SpellingServiceID.h"

#include "IXMLOutStream.h"
#include "ILanguage.h"

/** Utilities for auto correct
*/
class IAutoCorrectUtils : public IPMUnknown 
{
public:
	enum	{kDefaultIID = IID_IAUTOCORRECTUTILS};

	/**	Exports the auto correct XML for the specified language to 
		@param IDFile 
		@param LanguageID 
		@param IXMLOutStream::eEncodingType 
		@return ErrorCode result of the export
		*/
	virtual ErrorCode	ExportAutoCorrectXML(const IDFile& file, ILanguage* language, IXMLOutStream::eEncodingType encoding = IXMLOutStream::kUTF16) = 0;
	
	/**	Imports the auto correct XML for the specified language 
		@param IDFile 
		@param LanguageID 
		@param IXMLOutStream::eEncodingType 
		@return ErrorCode result of the export
		*/
	virtual ErrorCode	ImportAutoCorrectXML(const IDFile& file) = 0;
	
	
	/**		*/
	virtual	bool16		GetAutocorrectPresetsDirectory(IDFile& acDir) = 0;
	virtual	bool16		GetAutocorrectPrefsDirectory(IDFile& acDir) = 0;

	/**	Will copy the autocorrect file path naem to the PMString, generates the filename based on the languageID
		Will also set up the IDFile
		*/	
	virtual bool16		GetAutocorrectPresetsFile(IDFile& acFile, ILanguage* language, PMString& autoCorrectFileName) = 0;
	virtual bool16		GetAutocorrectPrefsFile(IDFile& acFile, ILanguage* language, PMString& autoCorrectFileName) = 0;

	virtual void ImportAllAutoCorrectFiles() const = 0;
};
	
#endif // __IAutoCorrectUtils__
