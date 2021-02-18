//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterUtils.cpp $
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
#include "ITextModel.h"
#include "XMLReference.h"

// General:
#include "ITextModelCmds.h"
#include "IXMLTagCommands.h"
#include "IXMLElementCommands.h"
#include "IXMLAttributeCommands.h"
#include "CmdUtils.h"

// Project:
#include "DataUpdaterUtils.h"
#include "DataUpdaterConst.h"

/*
// ReplaceText
// Replace the given range of text with the WideString supplied.
*/
ErrorCode DataUpdaterUtils::ReplaceText(ITextModel* iTextModel, const TextIndex& textIndex, int32 length, const boost::shared_ptr<WideString>& wideVal)
{

	// Never ever try to replace the last character in a story.
	// It is always a carriage return so leave it well alone.
	if (textIndex + length == iTextModel->TotalLength())
		length--;

	ErrorCode err = kFailure;

	// Create a command to replace the string
	// Ownership of the buffer wideVal is passed to the command. It 
	// will delete it when it is no longer required
    InterfacePtr<ITextModelCmds>textModelCmds(iTextModel,UseDefaultIID());
	InterfacePtr<ICommand> iCmd(textModelCmds->ReplaceCmd(textIndex, length, wideVal, nil));
	ASSERT_MSG( iCmd != nil, "cmd is invalid.");
	err = (iCmd != nil) ? kSuccess : kFailure;
	if (err == kSuccess)
		err = CmdUtils::ProcessCommand(iCmd);

	return err;
}



// Acquire XMLDataUpdater XML Tags. Create new tag if they have not been created before.
UIDRef DataUpdaterUtils::AcquireOneTag(IXMLTagList* tagList,const WideString& tagName )
{
	UIDRef retval;
	WideString tagNameWide(tagName);
	do {
		if(!tagList) 
			break;
		
		UID existingTagUID  = tagList->GetTag(tagNameWide);
		if(existingTagUID == kInvalidUID) 
		{
			UID createdTagUID = kInvalidUID;
			ErrorCode err = Utils<IXMLTagCommands>()->CreateTag (::GetUIDRef(tagList), 
															tagNameWide,
															kInvalidUID, 
															&createdTagUID);

			ASSERT(err == kSuccess);
			ASSERT(createdTagUID != kInvalidUID);
			retval = UIDRef(::GetDataBase(tagList), createdTagUID);

		} 
		else {
			retval = UIDRef(::GetDataBase(tagList), existingTagUID);
		}

	} while(kFalse);

	return retval;
}

ErrorCode DataUpdaterUtils::TagTextWithAttributeValue(UID tagUID, 
									UIDRef story, TextIndex startIndex, TextIndex endIndex, 
									const WideString attrName, const WideString attrValue)
{
	ErrorCode status = kFailure;

	do
	{		
		XMLReference createdElement;
		status = Utils<IXMLElementCommands>()->CreateElement(tagUID, story, startIndex, endIndex, kInvalidXMLReference, &createdElement);
		if(status != kSuccess) 
			break;

		Utils<IXMLAttributeCommands> attributeFacade;
		if(!attributeFacade) 
			break;

		status = attributeFacade->CreateAttribute(createdElement,(WideString)attrName, (WideString)attrValue);
		if(status != kSuccess) 
			break;

	} while (false);

	return status;
}
// End DataUpdaterUtils.cpp

