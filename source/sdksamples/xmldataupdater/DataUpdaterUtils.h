//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterUtils.h $
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

#ifndef __DataUpdaterUtils__
#define __DataUpdaterUtils__

// Interfaces:
#include "IXMLTagList.h"


/** From SDK sample; Utility methods for the xmldataupdater plug-in.

	@ingroup xmldataupdater
*/
class DataUpdaterUtils
{
public:

//	Text manipulation
	/**
		Replace the given range of text with the WideString supplied.
		@param iTextModel is the text model contant to be manipulated.
		@param textIndex is where the starting text to be replaced.
		@param length is the range of text to be replaced.
		@param val is the text to replace the old text.
		@return	ErrorCode of the processed command result.
	*/
	static ErrorCode ReplaceText(ITextModel* iTextModel, const TextIndex& textIndex, int32 length, const boost::shared_ptr<WideString>& wideVal);

    /** Acquire XMLDataUpdater XML Tags. Create new tag if they have not been created before
		@param tagList XML tag list of a document.
		@param tagName is the name of XML tag.
    */
	static UIDRef AcquireOneTag(IXMLTagList* tagList,const WideString& tagName );

	/**
		Tag the specified range of text with XML tag, and create one attribtue with attribute value.

		@param tagUID XML tag UID used to tag the text.
		@param story is the story of the text to be manipulated.
		@param startIndex is the starting index at which the text is to be tagged.
		@param endIndex is the ending index at which the text is to be tagged.
		@param attrName is the attribute name of the XML element be created.
		@param attrValue is the value of the attribute of the XML element be created.
		@return	the error code of command processing result.
	*/
	static ErrorCode TagTextWithAttributeValue(UID tagUID, 
									UIDRef story, TextIndex startIndex, TextIndex endIndex, 
									const WideString attrName, const WideString attrValue);
};

#endif // __DataUpdaterUtils__

// End, DataUpdaterUtils.h


